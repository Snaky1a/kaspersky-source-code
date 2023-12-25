/*!
 * (C) 2002 Kaspersky Lab 
 * 
 * \file	TSK\GroupTaskClient.h
 * \author	Mikhail Karmazine
 * \date	16:29 25.12.2002
 * \brief	������������ ����, ���������� ��������� GroupTask'��
 * 
 */

#ifndef __GROUPTASKCLIENT_H__
#define __GROUPTASKCLIENT_H__

#include <std/base/kldefs.h>
#include <srvp/tsk/grouptaskcontrol.h>

/*!
  \brief ������� proxy-������ ������ KLTSK::GroupTaskControl

    \param wstrURL      [in] ����� soap-�������
    \param ppGroupTaskControlProxy   [out] ��������� �� ������ ������ KLTSK::GroupTaskControlProxy
*/

KLCSSRVP_DECL void KLTSK_CreateGroupTaskControlProxy(
                        const wchar_t*  szwAddress,
                        KLTSK::GroupTaskControl**           pp,
                        const unsigned short* pPorts=NULL,
                        bool            bUseSsl = true);

KLCSSRVP_DECL bool KLSRV_IsServerGroupTaskId( const std::wstring & wstrTSId );


#endif // __GROUPTASKCLIENT_H__