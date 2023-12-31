/*!
*		
*		
*		(C) 2003 Kaspersky Lab 
*		
*		\file	service_observer.h
*		\brief	��������� OBSERVER-� ��� ��������, ������������ � HTTP ����������
*		
*		\author ��������� �������
*		\date	22.06.2005 18:55:05
*		
*		
*/		
#if !defined(_SERVICE_OBSERVER_INCLUDED_H_)
#define _SERVICE_OBSERVER_INCLUDED_H_
///////////////////////////////////////////////////////////////////////////////
namespace http
{
///////////////////////////////////////////////////////////////////////////////
/**
 * \breif	- abstract observer interface
 */
struct __declspec(novtable) service_observer
{
	virtual bool processing_yield(clock_t* start, int direction) = 0;
};
///////////////////////////////////////////////////////////////////////////////
}//namespace http
///////////////////////////////////////////////////////////////////////////////
#endif//!defined(_SERVICE_OBSERVER_INCLUDED_H_)
///////////////////////////////////////////////////////////////////////////////