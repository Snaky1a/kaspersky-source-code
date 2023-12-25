/*!
 * (C) 2005 "Kaspersky Lab"
 *
 * \file network.h
 * \author ����� �����������
 * \date 2005
 * \brief ������� ��������� ������ ������ � �����
 * 
 */


#ifndef KLNET_NETWORK_H
#define KLNET_NETWORK_H

#include <string>
#include <list>

#include <std/par/params.h>

#include "errors.h"

namespace KLNET {	

	class Network
	{
	public:
		/*!
			\brief ������� �������� Wake On Lan ������ �� ��������� ����
		
			\param pMacAddrs [in] ������ MAC ������� ����������
				������ ������� ������ hex ����
		   
			 \exception NETERR_INVALID_PARAMETER
			 
			 \return true - ������ ��� ������� ���������, false - ������ ��������
		*/
		virtual bool SendWakeOnLanSignal( KLPAR::ArrayValue *pMacAddr ) = 0;

		/*!
			\brief ������� ���������� ����������� �������� RDP ����������
		 
			 \return true - �������� �������� RDP ����������
		*/
		virtual bool IsRDPConnectionEnabled() = 0;

		/*!
			\brief ������� ��������� ���������� ��� �������� RDP ����������

			\param hostAddr [in] ����� �����,  � ������� ���������� ������� ����������
		 
			\exception NETERR_INVALID_PARAMETER, NETERR_ERR_START_RDP_APPS
		*/
		virtual void CallRDPConnetionApps( const std::wstring &hostAddr ) = 0;
		
		/*!
			\brief ������� ���������� ���������� c������ ( shutdown )
		*/
		virtual void ShutdownLocalSystem() = 0;
		
		/*!
			\brief ������� ���������� �������� Wake On Lan ������ �� ��������� ����
		*/
		virtual void SendWakeOnLanSignalAsync( KLSTD::CAutoPtr<KLPAR::ArrayValue> pMacAddr ) = 0;
		
		/*!
			\brief ������� ���������� ���������� c������ ( shutdown ) c ��������������� �������
		*/
		virtual void ShutdownLocalSystemEx( bool bForce, bool bRestart ) = 0;

	};

} // end namespace KLNET

DECLARE_MODULE_INIT_DEINIT2( KLCSTR_DECL, KLNET );

/*\brief ���������� ��������� �� ���������� ������ ������ Network */
KLCSTR_DECL KLNET::Network *KLNET_GetNetwork();

#endif // KLNET_NETWORK_H
