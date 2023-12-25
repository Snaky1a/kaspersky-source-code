/*!
*		
*		
*		(C) 2003 Kaspersky Lab 
*		
*		\file	session.h
*		\brief	
*		
*		\author ��������� �������
*		\date	29.04.2005 14:57:48
*		
*		
*/		
#if !defined(_SESSION_PROXY_INCLUDED_H_)
#define _SESSION_PROXY_INCLUDED_H_
#include <Prague/prague.h>
#include <Prague/iface/i_io.h>

#include <boost/utility.hpp>
#include <http/message.h>
#include <TrafficMonitor2/TrafficProtocoller.h>
///////////////////////////////////////////////////////////////////////////////
namespace http
{
///////////////////////////////////////////////////////////////////////////////
namespace tp = TrafficProtocoller;
///////////////////////////////////////////////////////////////////////////////
/**
 * \breif	- ������ �����, �������������� �������� ������ �� ������ �����������
 **/
class session
		: private boost::noncopyable
{
public:
	/**
	 * \breif ��������� ��������� ������
	 */
	enum state
	{
		alive_		= tp::psKeepAlive,		//! ����������� ��������� �������
		stop_		= tp::psProcessFinished,//! ������������ ��������� �������, ������� � ����� �������������� �������
		close_		= tp::psCloseConnection,//! ����� �� ��������� ������� �� ������� ������
		unknown_	= tp::psUnknown,		//! ����������� ������ �� ����������� ��������� HTPP, ������� � ����� �������������� �������
		terminate_
	};
	session(hOBJECT monitor, void* ctx);
	//! return client process id
	unsigned long client_id() const;
	//! �������� ������������� ������. ���������� ���������� ������������ ����
	size_t send(http::message_type type, hIO packet);
	//! ��������� ����� � ���������� ��������� �������
	size_t stop(http::message_type type, hIO packet);
	//! ��������� ������
	size_t break_off(http::message_type type);
	//! ��������� ����� � ���������� ��������� ������� �� ������� ����������
	size_t close(http::message_type type, hIO packet);
	//! ��������� ����� �� ���������� ���� ����� � ������� ������
	bool skip_that(char const* url, char const* content_type = 0);

	~session();
private:
	size_t do_send(http::message_type type, hIO packet, state st = alive_);
private:
	hOBJECT				traffic_monitor_;	
	void*				ctx_;							//! ������ ���� session_t
};
///////////////////////////////////////////////////////////////////////////////
}//namesapce http
#endif//!defined(_SESSION_PROXY_INCLUDED_H_)