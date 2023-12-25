/*!
 * (C) 2002 Kaspersky Lab 
 * 
 * \file	prcp_const.h
 * \author	Andrew Kazachkov
 * \date	01.10.2002 12:34:51
 * \brief	��������� ������ Product Component Proxy (PRCP).
 * 
 */

#ifndef KLPRCP_PRCP_CONST_H
#define KLPRCP_PRCP_CONST_H

#include <time.h>
#include <string>
#include <vector>

#include "std/err/error.h"
#include "std/par/params.h"

namespace KLPRCP {	

	const wchar_t c_szwProxyName[]=L"klprcp-Proxy";
    const wchar_t c_szwTransparentProxyName[]=L"klprcp-TransparentProxy";


    /*!
		\brief ����� ����������, ��������� � ������������.
	*/

	const wchar_t c_EventComponentState[]=L"ComponentState";



	/*!
		� ���� ���� �������, ����������� � ������� ������ Publish 
		����������� ��������� ��������:
	*/
	
	/*! ���������� ����������� (������������� � ������� ������������� �������
		�� 0 �� 999
	*/
	const wchar_t c_szwEventMilliseconds[] = L"klprci-milliseconds"; // INT_T

	/*! ����� ������� (� ������ ������� ������).
	*/   
    const wchar_t c_szwEventNumber[] = L"klprci-evt-number"; // INT_T

	/*!
		��� ������� � �������/������������ ���������� ������ � �����������.

		c_EventConnectionName - ��� ��������� ���������� � ���������� � ������� ���� 
			�����������/������������
	*/
	const wchar_t c_EventRemoteConnectionName[]	= L"KLPRCP_EVENT_CONNECTION_NAME";

	const wchar_t c_EventConnectionBroken[] = L"KLPRCP_CONNECTION_BROKEN";
	const wchar_t c_EventConnectionEstablished[] = L"KLPRCP_CONNECTION_ESTABLISHED";
}

#endif // KLPRCI_PRCP_CONST_H
