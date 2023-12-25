/*!
*		
*		
*		(C) 2003 Kaspersky Lab 
*		
*		\file	processor.cpp
*		\brief	���������� ������, ����������� �� ��������� HTTP �������.
*		
*		\author ��������� �������
*		\date	29.04.2005 14:54:01
*		
*		
*/
#define NOMINMAX
#pragma warning(disable:4786)
#include <windows.h>
#include <Prague/prague.h>
#include <http/analyzerimpl.h>
#include <http/stream_error.h>
#include <Prague/wrappers/io_helpers.h>
#include <cassert>
#include <AntiPhishing/plugin/p_antiphishingtask.h>
#include "processor.h"
#include "session.h"
#include "service_proxy.h"
#include <http/takeurl.h>
#include <http/verifyssl.h>
#include <http/skip_app.h>
#include "http_utils.h"
#include <fstream>
#include <http/dump.hpp>


///////////////////////////////////////////////////////////////////////////////
namespace
{
///////////////////////////////////////////////////////////////////////////////
/** 
 * ����� ��� ����� ����� response ������, ���� ������������ �� request �����
 * �� ��� ��������� � "����������"
 */
char const skip_request[] = "skipped request";
/** ����� � ������������*/
clock_t const PROCESSING_YIELD_TIMEOUT = 10000;
///////////////////////////////////////////////////////////////////////////////
}//namesapce unnamed
///////////////////////////////////////////////////////////////////////////////
http::processor::processor(std::auto_ptr<processing_strategy> strategy
						   , std::auto_ptr<session> proxy
						   , std::auto_ptr<analyzer> anlz
						   , clock_t timeout)
						: proxy_(proxy)
						, strategies_(2)
						, analyzers_(2)
						, url_(skip_request, skip_request + sizeof(skip_request))
						, timeout_(timeout)
						, processing_stage_(stgNone)
{
	queue_.reserve(0x40);
	anlz->support_keep_alive(this);
	strategy->set(this);
	strategies_[to_server] = boost::shared_ptr<http::processing_strategy>(strategy->clone());
	strategies_[to_client] = boost::shared_ptr<http::processing_strategy>(strategy->clone());
	analyzers_[to_server] = boost::shared_ptr<http::analyzer>(anlz->clone());
	analyzers_[to_client] = boost::shared_ptr<http::analyzer>(anlz->clone());
	analyzers_[to_server]->error_strategy(stream_error::passthough_stream(to_server, this));
	analyzers_[to_client]->error_strategy(stream_error::passthough_stream(to_client, this));
}
///////////////////////////////////////////////////////////////////////////////
http::processor::~processor()
{
	try
	{
		// ������ delayed notifier ����� ���-�� ������������, ����������������
		sync::local_mutex::scoped_lock lock(mutex_);
		std::auto_ptr<std::deque<char> > const& to_server_cache = do_analyzer(to_server).flush();
		std::auto_ptr<std::deque<char> > const& to_client_cache = do_analyzer(to_client).flush();
		if(dump<1>::need_dump())
		{
			if(to_server_cache.get()&& !to_server_cache->empty())
				dump<1>("!cache_to_server", proxy_.get()).write(to_server_cache->begin(), to_server_cache->end());
			if(to_client_cache.get()&& !to_client_cache->empty())
				dump<1>("!cache_to_client", proxy_.get()).write(to_client_cache->begin(), to_client_cache->end());
		}
	}
	catch(...)
	{
	}
	// ��� ����������� ������� ������� processor ����� delayed_notifier
	// ������ �������� ��� ����� ��� ������ mutex_ - ����� deadlock
	strategies_.clear();
	PR_TRACE((0, prtIMPORTANT, "http\tprocessor %p exiting"));
	// ������������� �������� (��. task.cpp, ��������, pmSESSION_STOP � pmPROCESS)
	sync::local_mutex::scoped_lock lock(mutex_);
}
///////////////////////////////////////////////////////////////////////////////
bool http::processor::skip_that(char const* url) const { return proxy_->skip_that(url); }
///////////////////////////////////////////////////////////////////////////////
bool http::processor::skip_message(message const& msg) const
{
	skip_application skipped(const_cast<http::message&>(msg));
	return skipped;
}
///////////////////////////////////////////////////////////////////////////////
http::detection_code http::processor::detect(char const* begin, char const* end, msg_direction direction)
{
	if(dump<1>::need_dump())
		dump<102>("!detect", proxy_.get()).write(begin, end);
	recognition result(do_analyzer(direction).recognize(begin, end));
	return static_cast<detection_code>(result);
}

///////////////////////////////////////////////////////////////////////////////
/**
 * 1.	��� ����������� ������ � ������������� ������ ������,
 *		���������� ��������� ����������
 * 2.	���� ������� SSL �����, �� ���������� �� �������� ������ �������
 *		� ���������� �� ����������� ������ ������ ��� ����������� ��� �����
 * 3.	���� ������� ������������� ��� �������� - ��������� �����\�����,
 *		�� ���������� �� �������� ������ ������� � ���������� �� �����������
 *		������ ��� ����������� ��� �����
 */
bool http::processor::do_process(msg_direction direction, bool is_ssl, bool force)
{
	bool result(true);

	http::analyzer& cur_anlz = this->do_analyzer(direction);
	http::processing_strategy& cur_stg = this->do_strategy(direction);

	try
	{
		//! ������������ ����� ���������� ���������,
		//! ���� ���� ������ ���� ������������� �������� ��� ������� ����������
		if(message* msg = cur_stg.extract_message(cur_anlz, direction, is_ssl, force))
		{
			//! �������� URL ��������� � ���������� ���������
			take_url url(*msg, is_ssl);
			if(!url.get().empty())
				std::vector<char>(url.get()).swap(url_);
			if(msg->type() == response_type)
			{
				//! �������� IO ��� �������������
				prague::IO<char> pre_assembled(cur_stg.asm_policy().pre_assemble(*msg));
				if(pre_assembled.get())
				{
					//! ��������� �������������
					PR_TRACE((0, prtIMPORTANT, "http\tPerforming preprocessing on '%s'...", url_.empty() ? "" : &url_[0]));
					service_proxy const& service = cur_stg.pre_av_service();
					bool is_gzip = msg->contentencoding() == gzip_encoding;
					processing_stage_ = stgPreprocess;
					http::antivirus_result avr(service.antivirus(proxy_->client_id(), pre_assembled.get(), &url_[0], 0, 0, is_gzip));
					processing_stage_ = stgNone;
					if(avr.result & object_was_deleted)
					{
						PR_TRACE((0, prtALWAYS_REPORTED_MSG, "http\tMalware detected, closing connection"));
						detected_on_preprocessing_.clear();
						prague::IO<char> prev_io(cur_stg.cnt_policy().replace(*msg, prague::create_temp_io()));
						if(!cur_stg.asm_policy().has_assembled(*msg))
						{
							//! ��������� �� ���� �� ������������, ����� �������� ���������� ���������
							std::auto_ptr<message> local_msg(utils::make_default_forbidden_reply(&url_[0], avr.vir_name.get()));
							msg = cur_stg.msg_policy().replace(local_msg);
						}
						prague::IO<char> packet(cur_stg.asm_policy().assemble(*msg, true));
						proxy_->close(msg->type(), packet.get());
						cur_stg.reprocess();
						return result;
					}
					else if(avr.result & object_some_allowed)
					{
						PR_TRACE((0, prtIMPORTANT, "http\tMalware detected, but allowed by user"));
					}
					PR_TRACE((0, prtIMPORTANT, "http\tPreprocessing done"));
				}
			}
			if(force || cur_stg.can_process(*msg))
			{
				//! ���������� ������������, ��� ��� ������
				session::state procesor_state = session::alive_;
				bool complete = cur_stg.msg_policy().can_complete(*msg);
				//! ������ �� � ���������?
				if(cur_stg.msg_policy().need_processing(*msg))
				{
					service_proxy const& service = cur_stg.service();
					switch(msg->type())
					{
					case response_type:
						{
							hIO content(cur_stg.cnt_policy().build(*msg));
							size_t old_size((size_t)prague::IO<char>::size(content));
							http::antivirus_result avr;
							//! antivirus
							PR_TRACE((0, prtIMPORTANT, "http\tPerforming AV processing on '%s'...", url_.empty() ? "" : &url_[0]));
							bool is_gzip = msg->contentencoding() == gzip_encoding;
							processing_stage_ = stgProcess;
							avr = service.antivirus(proxy_->client_id(),
															content, &url_[0], this, direction, is_gzip);
							processing_stage_ = stgNone;
							if(avr.result & object_was_deleted)
							{
								PR_TRACE((0, prtALWAYS_REPORTED_MSG, "http\tMalware detected"));
								prague::IO<char> prev_io(cur_stg.cnt_policy().replace(*msg, prague::create_temp_io()));
								complete = true;
								if(!cur_stg.asm_policy().has_assembled(*msg))
								{
									//! ��������� �� ���� �� ������������, ����� �������� ���������� ���������
									std::auto_ptr<message> local_msg(utils::make_default_forbidden_reply(&url_[0], avr.vir_name.get()));
									msg = cur_stg.msg_policy().replace(local_msg);
								}
							}
							PR_TRACE((0, prtIMPORTANT, "http\tAV processing done"));
							//! send content to parental control
							if(avr.result == object_is_ok &&
								!service.parctl(proxy_->client_id(), content, msg, &url_[0], this, direction))
							{
								complete = true;
								procesor_state = session::close_;//! ���������� ���������
								std::auto_ptr<message> local_msg(utils::make_forbidden_message(&url_[0]));
								msg = cur_stg.msg_policy().replace(local_msg);
							}

							content = cur_stg.cnt_policy().build(*msg);
							size_t new_size((size_t)prague::IO<char>::size(content));
							if((avr.result & object_was_deleted) || new_size != old_size)//! ������ ��� �������
							{
								procesor_state = session::close_;//! ���������� ���������
								PR_TRACE((0, prtIMPORTANT, "http\tConnection will be closed"));
							}
						}
						break;
					case request_type:
						{
							//! ��������� url � web-antivirus'e. 
							if (!service.webav(proxy_->client_id(), &url_[0]))
							{
								complete = true;
								procesor_state = session::close_;//! ���������� ���������
								std::auto_ptr<message> local_msg(utils::make_forbidden_message(&url_[0]));
								msg = cur_stg.msg_policy().replace(local_msg);
							}
							//! ��������� url � ����-�������. ������������ ������ request ���������
							if (!service.antiphishing(proxy_->client_id(), &url_[0]))
							{
								complete = true;
								procesor_state = session::close_;//! ���������� ���������
								std::auto_ptr<message> local_msg(utils::make_forbidden_message(&url_[0]));
								msg = cur_stg.msg_policy().replace(local_msg);
							}
							//! ��������� url � ����-�������. 
							if (!service.adblock(proxy_->client_id(), &url_[0]))
							{
								complete = true;
								procesor_state = session::close_;//! ���������� ���������
								if (strstr(&url_[0], ".swf"))
									msg = cur_stg.msg_policy().replace(utils::make_empty_swf_reply());
								else
									msg = cur_stg.msg_policy().replace(utils::make_empty_image_reply());
							}
						}
					}
				}
				//! ��������� �� SSL � ��������� media ����, ������� �� ������ ����������, �������� �����/TV
				if(verify_ssl(*msg) || skip_application(*msg))
				{
					procesor_state = session::stop_; //! ���������� ��������� � �������� ��������������
					complete = true;
				}
				//! �������� �����
				prague::IO<char> packet(cur_stg.asm_policy().assemble(*msg, complete));
				//! �������� ������������ ����� ������ � ������
				switch(procesor_state)
				{
				case session::alive_:
					proxy_->send(msg->type(), packet.get());
					break;
				case session::stop_:
					proxy_->stop(msg->type(), packet.get());
					break;
				case session::close_:
					proxy_->close(msg->type(), packet.get());
					break;
				default:
					throw std::runtime_error("unspecified processor state");
				}
				if(complete) //! ���, ��������� ���������, ���������� ��������� ����������
					cur_stg.reprocess();
			}
		}
	}
	catch(std::exception&)
	{
		//! ���������� ��� ��� ������ ���������� � ������ 
		std::auto_ptr<std::deque<char> > const& cache = cur_anlz.flush();
		if(cache.get() && !cache->empty() && dump<7>::need_dump())
			dump<7>("!exception", proxy_.get()).write(cache->begin(), cache->end());
		//! ���������� ��������� ����������
		cur_stg.reprocess();
		result = false;
	}
	return result;
}
///////////////////////////////////////////////////////////////////////////////
tERROR http::processor::process_detection(cAskObjectAction *ask_action)
{
	//! ������� ���������� �� ����� ������������ ��������
	//! �� ��� �� ������, ��� � ��������
	switch(processing_stage_)
	{
	case stgPreprocess:
		//! ���������� ����� �������, ����� ���������� �� ��� ��������� ��������
		if(!ask_action->m_strDetectName.empty())
		{
			PR_TRACE((0, prtIMPORTANT, "http\t'%S' added to detected list", ask_action->m_strDetectName.data()));
			detected_on_preprocessing_.push_back(ask_action->m_strDetectName.data());
		}
		break;
	case stgProcess:
		//! ���� � ����������� ��� ������������������
		if(!ask_action->m_strDetectName.empty() &&
			std::find(detected_on_preprocessing_.begin(),
						detected_on_preprocessing_.end(),
						ask_action->m_strDetectName.data()) != detected_on_preprocessing_.end())
		{
			PR_TRACE((0, prtIMPORTANT, "http\t'%S' allowed by detected list", ask_action->m_strDetectName.data()));
			ask_action->m_nResultAction = ACTION_ALLOW;
			return errOK_DECIDED;
		}
		break;
	}
	return errOK;
}
///////////////////////////////////////////////////////////////////////////////
bool http::processor::process(char const* begin, char const* end, msg_direction direction, bool is_ssl)
{
	sync::local_mutex::scoped_lock lock(mutex_);
	if(dump<101>::need_dump())//! ���������� ����� � ����
		dump<101>("!input", proxy_.get()).write(begin, end);
	this->do_analyzer(direction).enqueue(begin, end);//! ��������� � �������
	return this->do_process(direction, is_ssl)
		|| this->do_process(static_cast<msg_direction>(!direction), is_ssl);//! ����������� ������� ���������
}
///////////////////////////////////////////////////////////////////////////////
/** ������������� ���������� ������� ���������*/
void http::processor::flush()
{
	/**
	 * ����� �����������,��� �� ������� �� ���� ����������.
	 * ��� ��� ������������� ������������, ��� ��� �� ��������� �������� �� ���������
	 */
	sync::local_mutex::scoped_lock lock(mutex_);
	try { this->do_process(to_server, false, true); } catch(...) { 0; }
	try { this->do_process(to_client, false, true); } catch(...) { 0; }
}
///////////////////////////////////////////////////////////////////////////////
bool http::processor::processing_yield(clock_t* start, int direction)
{
	clock_t ptime(clock() - (start ? *start : 0));
	bool timeout(ptime >= PROCESSING_YIELD_TIMEOUT);
	msg_direction cur_dir = static_cast<msg_direction>(direction);
	http::processing_strategy& cur_stg = this->do_strategy(cur_dir);
	message const* msg = cur_stg.msg();
	if(timeout && msg)//! timeout occurred
	{
		start ? *start = clock() : 0;
		prague::IO<char> packet(cur_stg.asm_policy().assemble(*msg));
		proxy_->send(msg->type(), packet.get());
	}
	return true;
}
///////////////////////////////////////////////////////////////////////////////
http::method_type http::processor::request_method() const
{
	//!	TODO: ���� ��� �������������� ��������
	method_type method(_unknown);
	if(!queue_.empty())
	{
		method = queue_.front();
		queue_.erase(queue_.begin());
	}
	return method;
}
///////////////////////////////////////////////////////////////////////////////
void http::processor::request_method(http::method_type method)
{
	//!	TODO: ���� ��� �������������� ��������
	queue_.push_back(method);
}
///////////////////////////////////////////////////////////////////////////////
void http::processor::passto(http::msg_direction dir, char const* beg, char const* end)
{
	prague::IO<char> packet(prague::create_temp_io());
	packet.insert(packet.end(), beg, end);
	proxy_->send((dir == to_server ? request_type : response_type), packet.get());
}
///////////////////////////////////////////////////////////////////////////////