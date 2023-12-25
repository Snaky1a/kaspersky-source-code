/*!
*		
*		
*		(C) 2003 Kaspersky Lab 
*		
*		\file	analyzerimpl.cpp
*		\brief	���������� ������, �������� ����������� �������� ��������
*				���������� ������ ������ � ��������� � ���������� ������
*				�������(����������) ������������� HTTP ���������.
*				���������� ��������� ����������� � ����� http.hpp.
*				�������� ��������� ��. RFC 2616
*		
*		\author ��������� �������
*		\date	25.04.2005 17:02:25
*		
*		
*/
#define NOMINMAX
#pragma warning(disable : 4275)
#include <windows.h>
#include <Prague/wrappers/io_helpers.h>
#include "message.hpp"
#include "http.hpp"
#include "analyzerimpl.h"
#include "stream_error.h"
#include <fstream>
#include "dump.hpp"
///////////////////////////////////////////////////////////////////////////////
namespace
{
/**������������ ������ ������ ������� - 8��*/
unsigned int const MAX_PARSE_BUFFER_SIZE = 0x2000;
}//unnamed namespace
///////////////////////////////////////////////////////////////////////////////
namespace spirit = boost::spirit;
///////////////////////////////////////////////////////////////////////////////
http::analyzer::analyzer()
		: cache_(0x2000)
		, supp_(0)
		, error_(stream_error::nothing_todo())
{
}
///////////////////////////////////////////////////////////////////////////////
http::analyzer::analyzer(support_persistent* supp)
		: cache_(0x2000)
		, supp_(supp)
		, error_(stream_error::nothing_todo())
{
}
///////////////////////////////////////////////////////////////////////////////
http::analyzer::~analyzer()
{
}
///////////////////////////////////////////////////////////////////////////////
http::recognition http::analyzer::recognize(char const* begin, char const* end) const
{
	//! ���������� ���������� ������ CRLF, ���� ����� ���������� ��� ������� � ���,
	//! ��� ��������� ������� ������ 1.0 ����� �������� �������������� CRLF ��� 
	//! POST �������, � ���������� ���������� BNF ����� ���������� ������ � �������
	spirit::parse_info<> info = spirit::parse(begin, end, +eol_tolerant_p);
	if(info.hit)
		begin = info.stop;
	http::request::data_type data;
	http::request req(&data);
	info = spirit::parse(begin, end, req);
	
	recognition rcg = do_recognize(data, info.hit, info.stop, begin, end);

	if (not_mine == rcg)
	{
		// ��������, � �� HTTP ���������� �� ���?
		http::request_ext::data_type data;
		http::request_ext req(&data);
		info = spirit::parse(begin, end, req);
		if (info.hit)
			rcg = its_mine;
	}
	//��� ������������� ������ ������������� �� ������� �� �������
	//��� ��� �������� ������ ������������ ��������
	return rcg;
}
///////////////////////////////////////////////////////////////////////////////
size_t http::analyzer::recovery_error(char const* begin, char const* end)
{
	size_t used_bytes(0);
	http::recognizer<http::request_data> r;
	http::request::data_type req_data;
	http::request req(&req_data);
	http::message_recognizer<http::request, http::recognizer<http::request_data> > req_msg(req, r);
	char const* tmp = http::find_message(begin, end, req_msg);
	if(tmp == end)
	{
		http::recognizer<http::response_data> r;
		http::response::data_type resp_data;
		http::response resp(&resp_data);
		http::message_recognizer<http::response, http::recognizer<http::response_data> > resp_msg(resp, r);
		tmp = http::find_message(begin, end, resp_msg);
	}
	used_bytes += (tmp - begin);//! ������ ������
	return used_bytes;
}
///////////////////////////////////////////////////////////////////////////////
/**
 * �������� �� �������� ������ ������ ��������� ���������, ���� �� �������
 * �������� �� �������� ������(������), ���� �� ��������, request\response
 * ���������, �� ����� ��������� ����������, ��������� � ���, ��� �������
 * ����� �� ����������� ��������� HTTP
 * 
 * � ������ �� ������ ������� �������� �������� request ���������, � �����
 * response ���������, ��� �� ������� �������, ��� ��� ��� request-��
 * ����� �������� ������ ������ 3-10 ������ ��������, �� ������������
 * �������������� �������.
 * �������� force ������ ������ �� ��������� response ���������, ��� ���
 * � ������ ��� ������ ���������� � ���������� �������� ����������� ���������
 * ��������� ��������� � �������� �������, ��� ��� �������� ��������, �����
 * ��������� �� ��������� �������� ��-�� ���������
 * ���������� CRLF(������ Microsoft-IIS/6.0)
 */
std::pair<size_t, bool> http::analyzer::do_extract(std::auto_ptr<message>& msg, char const* begin
								, char const* end, bool force)
{
	message_type type(http::request_type);
	method_type method(_unknown);
	size_t used_bytes(0);
	bool litter(false);
	//! ���������� ���������� ������ CRLF, ���� ����� ���������� ��� ������� � ���,
	//! ��� ��������� ������� ������ 1.0 ����� �������� �������������� CRLF ��� 
	//! POST �������, � ���������� ���������� BNF ����� ���������� ������ � �������
	spirit::parse_info<> info = spirit::parse(begin, end, +eol_tolerant_p);
	if(info.hit)
	{
		used_bytes += info.length;
		begin = info.stop;
	}
	//! �������� �������� request/response ���������
	header_t* hdrs = 0;
	response_data resp_data;
	request_data req_data;
	request req(&req_data);
	info = spirit::parse(begin, end, req);
	http::recognition request_result(do_recognize(req_data, info.hit, info.stop, begin, end));
	if(request_result == its_mine)//! ������ ������ ��������� ��� request message
	{
		hdrs = &req_data.hdrs;//! �������� message-header ��� ������� ������
		type = request_type;  //! ���������� ��� ������ ��� request
		method = request_method(req_data.method);
	}
	else
	{
		resp_data.scode = 0;
		http::response resp(&resp_data);
		info = spirit::parse(begin, end, resp);
		recognition  response_result(do_recognize(resp_data, info.hit, info.stop, begin, end));
		if(response_result == its_mine)
		{//! ������ ������ ��������� ��� response message
			hdrs = &resp_data.hdrs;	//! �������� message-header ��� ������� ������
			type = response_type;	//! ���������� ��� ������ ��� request
		}
		else if(response_result == likely_mine
				&& force
				&& !resp_data.hdrs.empty())
		{//! ������ �������� ��������� ��� response message
			//! ��� ������ ���������
			hdrs = &resp_data.hdrs;	//! �������� message-header ��� ������� ������
			type = response_type;	//! ���������� ��� ������ ��� request
		}

		if (not_mine == response_result && not_mine == request_result)
		{
			request_ext req_ext(&req_data);
			info = spirit::parse(begin, end, req_ext);
			
			if (info.hit)
			{
				// ������� ����������
				hdrs = &req_data.hdrs;
				type = request_type;
				method = request_method(req_data.method);
			}

			http::recognition request_ext_result = info.hit? its_mine : not_mine;

			//! ���������� ��������, ��� ��� �������� ����� � �������, �����������
			//! ��������� ��������� HTTP. ��� ����������, ���� ����� ������� ��������
			//! �� HTTP ���������(rfc2616), � ����� �������� �� ���� �� ��� ����������,
			//! �������� WebDav, ������� ��������� ����� �������� � �������.
			if(response_result == not_mine
				&& request_result == not_mine
				&& request_ext_result == not_mine
				&& used_bytes == 0)//! ���������, ��� ����� ���� ������� ����� ��������� �� CRLF
			{
				//! �������� ��������, ����� ������ HTTP ������ ���������� �� ������� ���������� ������
				//! ����� �������� ��� ������ http ������� VxWorks 5.4. ���� ������ � ��������� RESPONSE
				//! ������������� message-body HTTP ������.
				//! n���� ��������� ����� ���� ��������� - http://img.mail.ru/r/vir.gif?1993331897
				//! �������� ����������� �������� HTTP.
				//! �������� �������� ����� �� �� ������ �������� �����, ����� �������� ����� ������ ����������!????
				used_bytes += this->recovery_error(begin, end);
				if(dump<7>::need_dump() && used_bytes)//! ���������� ����� � ����
					//! �������� - ���� used_bytes == 0, ������������ �������� [begin, begin + used_bytes) �����������!!!!
					dump<7>("!litter", this).write(begin, begin + used_bytes);
				if(used_bytes)//! ��������� ��������� ������ � ������ ������������� ���������
				{
					litter = true;//! ���������� ������� ���� ��� ��� ������ � ��������� ����� �� ������ ��� �������
					error_(begin, begin + used_bytes);
				}
			}
		}
	}
	//! ������ ����� ���������, ���� ��������� � �.�. � �.�.
	if(hdrs)
	{
		//! ��������� ������� ��������, ���� persistent connection
		if(supp_)
			method = (type == request_type)
						? (supp_->request_method(method), method) 
						: supp_->request_method();
		//todo: ������� ����������� �� ������ �����,
		//		��� ��� ��������� ���� ����������� ������ response message
		size_t real_size(end - info.stop);//! �������� ������ ���������� ������)
		size_t content_size(0);
		header_t::iterator tit = hdrs->find(field_name(_TRANSFER_ENCODING));
		header_t::iterator cit = hdrs->find(field_name(_CONTENT_LENGTH));
		bool is_transfer_encoding(tit != hdrs->end());
		//! Content-Length ������ ��������������, ���� ������ Transfer-Encoding
		bool is_content_length((cit != hdrs->end()) && !is_transfer_encoding);
		if(is_content_length && !is_transfer_encoding)//! ������� ���� Content-Length
			content_size = http::buffer_cast<int>(cit->second, 0);//! � ���������� ���� Transfer-Encoding
		//! check HEAD request in the request queue for persistent connection
		if(type == response_type && method == _head)//LENGTh MUSt BE ZERO FOR ALL RESPONSE
		{
			content_size = 0;//! for HEAD request response body MUST be zero
			is_content_length = true;//! the content length was specified and equals zero
		}
		//! calculate message length see rfc2616/paragraph 4.4
		if(type == response_type && content_size == 0 && !is_content_length)
		{//! ����������� ������, ���� �� ���� � ��������� Content-Length
			if(!(resp_data.scode > 99 && resp_data.scode < 200)
				&& !(resp_data.scode == 204 || resp_data.scode == 304))
				content_size = unspecified_length;
			//! ��������� response �� handshake ��� SSL
			vector_ptr reason(http::buffer_cast<vector_ptr>(resp_data.reason, 0));
			reason->push_back(0);
			if(detect_ssl_handshake_response(resp_data.scode, _strlwr(&(*reason)[0])))
				content_size = 0;
		}
		char const* end_of = info.stop + std::min(content_size, real_size);
		//! ������� ��������� c ������ ����������
		msg = create_message(type, content_size, begin, info.stop, 0, 0, method);
		char const* content_begin = info.stop;
		char const* content_end = content_begin + std::min(content_size, real_size);
		if(content_begin != content_end)//! ��������� ���������� � ���������
			real_size = msg->append(content_begin, content_end);
		//! ��������� ����� ���� ����������� �� �������� ������
		used_bytes += (info.stop - begin) + std::min(content_size, real_size);
	}
	return std::make_pair(used_bytes, litter);
}
///////////////////////////////////////////////////////////////////////////////
std::auto_ptr<http::message> http::analyzer::do_extract(http::message* msg, bool force)
{
	std::auto_ptr<message> local_msg;
	if(!cache_.empty())
	{
		bool completed(msg ? msg->complete() : false);
		bool nothing(false);//���� ���������� ����������� � true, �� � ���� ��� ������� ��������� ������
		cache_iterator it(cache_.begin());
		while(it != cache_.end() && !completed && !nothing)
		{
			//std::copy(it, it + chunk_size, tmp.begin());
			if(!msg)
			{
				std::pair<size_t, bool> const& result = do_extract(local_msg, it, cache_.end(), force);
				size_t used_bytes(result.first);
				if(!local_msg.get())//� ���� ���� ��������� ���������, �� �� �� �����
				{
					//! ���������� ������, ������� ���� ��������� ��� ��������� �������� ������
					//! �� ��� ������, ���� � ��� ������ ������������ ������, extract �����
					//! ����������� � ����������� � ������������� ����������
					nothing = (used_bytes == 0);
					it += used_bytes;
					//! � ������ ���� �����, ������� ����� ������� �� ����, ��� ��� ��� ��� ��������� �� ����������
					if(result.second)
					{
						cache_.erase(cache_.begin(), it);
						it = cache_.begin();
					}
				}
				else
				{
					msg = local_msg.get();
					it += used_bytes;
				}
			}
			else
			{
				size_t size(msg->append(it, cache_.end()));
				it += size;//! ������������ ������� ��������
				completed = msg->complete();
				//assert(completed || size != 0);
			}
		}
		//! ������� �� ���� ������ ��������� � ���������
		if(msg || !nothing)
			cache_.erase(cache_.begin(), it);
	}
	return local_msg;
}
///////////////////////////////////////////////////////////////////////////////
std::auto_ptr<http::message> http::analyzer::extract(bool force) { return do_extract(0, force); }
///////////////////////////////////////////////////////////////////////////////
void http::analyzer::extract(http::message& msg) { do_extract(&msg, false); }
///////////////////////////////////////////////////////////////////////////////
void http::analyzer::enqueue(char const* begin, char const* end)
{
	cache_.append(begin, end);
}
///////////////////////////////////////////////////////////////////////////////
//! size_t real_size - �������������� ������ �������� ����������� �� ������ http ������
std::auto_ptr<http::message> http::analyzer::create_message(http::message_type type
														 , size_t real_size		//! �������������� ������ ��������
														 , char const* hdr_begin
														 , char const* hdr_end
														 , char const* begin
														 , char const* end
														 , method_type request_method)
{
	typedef prague::IO<char>::iterator iterator;
	std::auto_ptr<message> msg;
	std::auto_ptr<std::vector<char> > header(new std::vector<char>);
	prague::IO<char> content(prague::create_temp_io());
	http::request_data req_data;
	http::response_data resp_data;
	header_t* hdrs = 0;
	header->reserve(hdr_end - hdr_begin);//! reserve space for header buffer
	header->insert(header->end(), hdr_begin, hdr_end);//! fill up header buffer
	content.insert(content.end(), begin, end);//! fill up content as single unit

	switch(type)
	{
	case request_type:
		{
			http::request req(&req_data);
			char const* local_beg = &(*header)[0];
			char const* local_end = local_beg + header->size();
			spirit::parse_info<> info = spirit::parse(local_beg, local_end, req);
			msg = std::auto_ptr<message>(new request_message(req_data, header, content, real_size));
			hdrs = &req_data.hdrs;
		}
		break;
	case response_type:
		{
			http::response resp(&resp_data);
			char const* local_beg = &(*header)[0];
			char const* local_end = local_beg + header->size();
			spirit::parse_info<> info = spirit::parse(local_beg, local_end, resp);
			msg = std::auto_ptr<message>(new response_message(resp_data, header, content, real_size, request_method));
			hdrs = &resp_data.hdrs;
		}
		break;
	default:
		throw std::runtime_error("http message type is undefined");
	}
	//! detect is packet has chunked message-body
	header_t::iterator tit = hdrs->find(field_name(_TRANSFER_ENCODING));
	if(tit != hdrs->end())
	{
		std::string const& s = http::buffer_cast<std::string>(tit->second, 0);
		if(_stricmp(s.c_str(), _CHUNKED) == 0)
			msg = std::auto_ptr<message>(new chunked_message(msg));
	}
	return msg;
}
///////////////////////////////////////////////////////////////////////////////
//! return cached data and clear internal cache
std::auto_ptr<std::deque<char> > http::analyzer::flush()
{
	std::auto_ptr<std::deque<char> > tmp(new std::deque<char>(cache_.size()));
	std::copy(cache_.begin(), cache_.end(), tmp->begin());
	cache_.erase(cache_.begin(), cache_.end());
	return tmp;
}
///////////////////////////////////////////////////////////////////////////////
http::analyzer* http::analyzer::clone() const
{
	return new analyzer(this->supp_); 
}
///////////////////////////////////////////////////////////////////////////////
http::support_persistent* http::analyzer::support_keep_alive(http::support_persistent* supp)
{
	support_persistent* tmp = this->supp_;
	this->supp_ = supp;
	return tmp;
}
///////////////////////////////////////////////////////////////////////////////