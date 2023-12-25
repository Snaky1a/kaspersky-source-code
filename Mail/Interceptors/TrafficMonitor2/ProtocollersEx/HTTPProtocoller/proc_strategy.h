/*!
*		
*		
*		(C) 2005 Kaspersky Lab 
*		
*		\file	proc_strategy.h
*		\brief	����������� ��������� ��� ��������� ��������� ���������
*		
*		\author Vladislav Ovcharik
*		\date	28.09.2005 9:32:06
*		
*		
*/		
#if !defined(PROCESSING_STRATEGY_H_INCLUDED)
#define PROCESSING_STRATEGY_H_INCLUDED
#include <memory>
///////////////////////////////////////////////////////////////////////////////
namespace http
{
///////////////////////////////////////////////////////////////////////////////
//! forward declaration
class message;
class analyzer;
struct service_proxy;
struct preprocessing;
enum msg_direction;
///////////////////////////////////////////////////////////////////////////////
//! ����������� ��������� ��������� ������
enum process_state
{
	unspecified		= 0,	//! ��������� �� ���������� ��� �������� ��������������� ������
	need_process	= 1,	//! ����� ������ ���� ��������� � � ���� ����� �������� �������� ���������� ��������
	skip_process	= 2		//! ����� �� ������ ��������������, ��� ��� ������ ��� �� ��� ��������
};
///////////////////////////////////////////////////////////////////////////////
/**
 * abstarct interface
 * need to get integrate status for message
 */
struct __declspec(novtable) message_policy
{
	/**
	 * replace processing message forcedly
	 */
	virtual message* replace(std::auto_ptr<message> msg) = 0;
	/**
	 * return true if processing should be completed
	 */
	virtual bool can_complete(message const&) const = 0;
	/**
	 * return true if message should be processed on the AVS
	 */
	virtual bool need_processing(message const&) const = 0;
protected:
	~message_policy() {}
};
///////////////////////////////////////////////////////////////////////////////
/**
 * abstract interface
 * need to build content to examine its in the antivirus service
 */
struct __declspec(novtable) content_policy
{
	/**
	 * return message content dependes from av-engine type
	 */
	virtual hIO build(message const&);
	/**
	 * ���������� ������������� ����� AVS ������ "��������" hIO
	 * �������� ����� ������ ������� ������������� �������� ����������
	 * AVS, ������� ���������� ������ �� ��������� ����� ���������!!!
	 */
	virtual hIO replace(message&, hIO);
protected:
	~content_policy() {}
};
///////////////////////////////////////////////////////////////////////////////
/**
 * ����������� ��������� ��� ������ ��������� � ASCII �����
 */
struct __declspec(novtable) assemble_policy
{
	/**
	 * �� ��������� �������� ��������
	 */
	virtual hIO assemble(message const&, bool full = false) const = 0;
	/**
	*/
	virtual hIO pre_assemble(message const&) const = 0;
	/**
	 * ���������� true, ���� ������ ����� ��������� ��� ���� ������� �
	 * ASCII �����.
	 */
	virtual bool has_assembled(message const&) const = 0;
protected:
	~assemble_policy() {}
};
///////////////////////////////////////////////////////////////////////////////
/**
 * ���������� ��������� ��������� ��������� ���������
 * ������������� ������� ��� ��������� ��������� � ������������ ������
 * ������������� ��������, ������������ ������ ��������� ��� ��������� ���������
 */
struct __declspec(novtable) processing_strategy
{
	/** 
	 * return not zero pointer to a message
	 * if we can extract message for preprocessing
	 */
	virtual http::message *extract_message(analyzer& anlz, msg_direction direction, bool is_ssl, bool force) = 0;
	/** 
	 * return true if message should be processed
	*/
	virtual bool can_process(const http::message &msg) const = 0;
	/**
	 * reinit internal state to process next available message
	 */
	virtual void reprocess() = 0;
	/**
	 * set a new pre-processing object
	 */
	virtual http::preprocessing* set(preprocessing* preproc) = 0;
	/**
	 * return current processing message
	 */
	virtual message const* msg() const = 0;
	/**
	 * return reference to abstract Anti-virus engine service
	 */
	virtual http::service_proxy const& service() const = 0;
	/**
	* return reference to abstract Anti-virus engine service used for prescan
	*/
	virtual http::service_proxy const& pre_av_service() const = 0;
	/**
	 * return reference to message policy
	 */
	virtual http::message_policy& msg_policy() = 0;
	/**
	 * return reference to message content policy to get message content
	 * as you need
	 */
	virtual http::content_policy& cnt_policy() = 0;
	/**
	 * return reference to assemble policy to assemble your message as you need
	 */
	virtual http::assemble_policy const& asm_policy() const = 0;
	/** should be virtual and public*/
	virtual ~processing_strategy() {}
	/** clone existing object*/
	virtual processing_strategy* clone() const = 0;
};
///////////////////////////////////////////////////////////////////////////////
}//namespace htpp
///////////////////////////////////////////////////////////////////////////////
#endif//!defined(PROCESSING_STRATEGY_H_INCLUDED)