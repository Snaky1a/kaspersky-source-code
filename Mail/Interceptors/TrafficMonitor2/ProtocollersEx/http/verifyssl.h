/*!
*		
*		
*		(C) 2003 Kaspersky Lab 
*		
*		\file	verifyssl.h
*		\brief	��������� ����� �� ������� �������������� � SSL
*		
*		\author ��������� �������
*		\date	11.05.2005 18:30:14
*		
*		
*/		
#if !defined(_SSL_VERIFY_INCLUDED_H_)
#define _SSL_VERIFY_INCLUDED_H_
#include "action.h"
#include <boost/utility.hpp>
///////////////////////////////////////////////////////////////////////////////
namespace http
{
///////////////////////////////////////////////////////////////////////////////
/**
 * \breif	-	������������ ��������
 *				����������� ������ ����� �� ����� ���� �������, ��� ���
 *				� ������������ ���������� ���������� ������, ����� ��������
 *				������� ���������������
 */
class verify_ssl
		: private boost::noncopyable
		, public action_hierarchy<action_list>
{
public:
	explicit verify_ssl(message& msg);
	virtual void do_action(http::response_message&);
	DEFINE_DEFAULT_ACTION(request_message)
	DEFINE_DEFAULT_ACTION(message)
	bool get() const { return is_ssl_; }
private:
	typedef bool (verify_ssl::*unspecified_bool_type)() const;

public:
	operator unspecified_bool_type() const
	{
		return is_ssl_ ? &verify_ssl::get: false;
	}
private:
	bool	is_ssl_;
};
///////////////////////////////////////////////////////////////////////////////
}//namespace http
///////////////////////////////////////////////////////////////////////////////
#endif