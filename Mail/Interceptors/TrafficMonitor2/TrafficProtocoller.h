/*!
*		
*		
*		(C) 2002 Kaspersky Lab 
*		
*		\file	TrafficProtocoller.h
*		\brief	���� ���� ��������� ��������� ������ ������� ����� ���������������� (������) � ��������������
*		
*		\author Vitaly DVi Denisov
*		\date	24.01.2005 12:51:39
*		
*		Example:	
		��������� ������������ ��� �������� ������ � ��������� ����� ������ ������.
		������ ���������� � ������ ���������� ����������-������� � �������.
		������� ������:
		1. ProxySession: ������� ������ ��������� session_t m_hSessionCtx. ���������� ������ � ���� �������:
				tDWORD dwSessionCtx[po_last];
				memset(dwSessionCtx, 0, po_last*sizeof(tDWORD));
				dwSessionCtx[po_ProxySession] = (tDWORD)this;
				m_hSessionCtx.pdwSessionCtx = dwSessionCtx;
				m_hSessionCtx.dwSessionCtxCount = po_last;
		2. ProxySession: ���������� ������������ � ������ ����� ������:
				sysSendMsg( 
					pmcTRAFFIC_PROTOCOLLER, 
					pmSESSION_START, 
					0, 
					&m_hSessionCtx, 
					SER_SENDMSG_PSIZE 
					);
		3. Protocoller: �������� ������ ��� ������, ��������������� � ������ �������, 
		   � ��������� ��������� � ������� m_hSessionCtx.pdwSessionCtx:
  				CSessionData* pSessionData = new CSessionData(this);
				if ( pSessionData )
					phSessionCtx->pdwSessionCtx[po_SMTP] = (tDWORD)pSessionData;
		4. ProxySession: ��� ������ ������ �� ������� ��� �� ������� ���������� ��� ������ ������������� 
		   ��� ������������� ���������:
				detect_t hDetectParams;
				hDetectParams.assign(m_hSessionCtx, false);
				hDetectParams.dsDataSource = dsDataSource;
				hDetectParams.pLastReceivedData = pLastReceivedData;
				hDetectParams.ulLastReceivedData = ulLastReceivedData;
				hDetectParams.pdcDetectCode = &dcDetectCode;
				hDetectParams.phDetectorHandle = &m_hProtocoller;
				err = m_InitParams.hParent->sysSendMsg( 
					pmcTRAFFIC_PROTOCOLLER, 
					pmDETECT, 
					0, 
					&hDetectParams, 
					SER_SENDMSG_PSIZE 
					);
				if ( PR_FAIL(err) ) 
				{
					dcDetectCode = dcNeedMoreInfo;
					m_hProtocoller = NULL;
				}
		5. Protocoller: ���������� ����� ��������� ������� � ���������� ������� ������. 
		   ��� ���� ������� ���������, ��� ������ ������� ����� ��������� ������ ����������� ������, � �����������
		   ��� ������, "��������" �� ����� �����. ���������: ������ ������� ������ ��������� � �������� ������������
		   ����������� ������. �.�. ����� ������ ������ "������->������" ���������� ������������ ��� ������������ � ������
		   ������� ������ �� ������ "������->������".
		   ����� ����, ���� �� ���� ����� ������������ ������ �������� ������, ��� ������������ ����� ��������� 
		   ������� ���������.
		   ���� ����������� ���������� ���������� ���� ��������, �� ������ 
		   ����������: 
				*hDetectParams.pdcDetectCode = dcProtocolDetected;
				hDetectParams.phDetectorHandle = this;
				return errOK_DECIDED; //���� ��� �������� ���������� ����� ������ �������������.
		   ���� ����������� ���������� ���������� ������� ������ �������� ������, �� ������ 
		   ����������:
				*hDetectParams.pdcDetectCode = dcDataDetected;
				hDetectParams.phDetectorHandle = this;
				return errOK_DECIDED; //���� ��� �������� ���������� ����� ������ �������������.
		6. ProxySession: ���� ��� ������������ ������� �� ��������� pmDETECT 
				hDetectParams.pdcDetectCode == dcNeedMoreInfo, 
		   ������� �������� ������������ ����� ������, �� ��������� ��� ��� ������� ��������.
		7. ProxySession: ���� ����������� ������ �� ��������� pmDETECT 
				hDetectParams.pdcDetectCode == dcProtocolUnknown, 
		   ����� (� ����� �����������) ��������� ������ ����������� �� ���������� ��������� 
		   (� ���������, ��� �� ���������� � ������ ������� sysSendMsg).
		8. ProxySession: ���� ����������� ������ �� ��������� pmDETECT 
				hDetectParams.pdcDetectCode == dcProtocolDetected, 
		   ����� (� ����� �����������) ��������� ��� ��������� ������������ �� ���������� ��������� 
		   (� ���������, ��� �� ���������� � ������ ������� sysSendMsg).
		9. ProxySession: ���� ����������� ������ �� ��������� pmDETECT 
				hDetectParams.pdcDetectCode == dcDataDetected, 
		   ������� ��� ��������� ������ �������� ������� ������������ �� ���������:
				process_status_t psStatus;
				process_t hProcessParams;
				hProcessParams.assign(m_hSessionCtx, false);
				hProcessParams.dsDataSource = dsDataSource;
				hProcessParams.pData = pLastReceivedData;
				hProcessParams.ulDataSize = ulLastReceivedData;
				hProcessParams.phDetectorHandle = &m_hProtocoller;
				hProcessParams.psStatus = &psStatus;
				err = m_hProtocoller->sysSendMsg( 
					pmcTRAFFIC_PROTOCOLLER, 
					pmPROCESS, 
					0, 
					&hProcessParams, 
					SER_SENDMSG_PSIZE 
					);
				if ( psStatus == psProcessFailed ) 
				{
					detect_code_t& dcDetectCode = m_dcTraffic;
					dcDetectCode = dcNeedMoreInfo;
					m_hProtocoller = NULL;
					err = errOBJECT_NOT_FOUND;
				}
		10. Protocoller: ����������� ����������� � ���� ������, ���������� � ��������� pmPROCESS,
		    � ������������ ��. �� ����� ���������� � ��������� �� ����� ���������� ����� ������
			� ������ (��������, ��� ����������� ����������� ����� ����� �������� � ��������)
			���������� pmKEEP_ALIVE
				process_msg_t process_msg;
				process_msg.assign(pSession, false);
				process_msg.dsDataTarget = dsServer;
				process_msg.psStatus = psKeepAlive;
				process_msg.hData = pSessionData->m_Data;
				err = sysSendMsg( 
					pmcTRAFFIC_PROTOCOLLER, 
					pmKEEP_ALIVE, 
					0, 
					&process_msg, 
					SER_SENDMSG_PSIZE 
					);
		11. ProxySession: � ������ ������� ��������� pmKEEP_ALIVE ������ �������� ���������� 
		    ������ � ��������� �����������:
				do
				{
					if ( PR_SUCC(err= ppmCommand->hData->SeekRead(&dwRead, pos, data, 1024)) && dwRead )
					{
						pos += dwRead;
						tINT nSend = send( to, data, dwRead, 0 );
					}
				}
				while( PR_SUCC(err) && dwRead  );
		12. Protocoller: �� ��������� ��������� ����������� ������ �������� ������������ ������ � ������:
				process_msg_t process_msg;
				process_msg.assign(pSession, false);
				process_msg.dsDataTarget = dsServer;
				process_msg.psStatus = psProcessFinished;
				process_msg.hData = pSessionData->m_Data;
				err = sysSendMsg( 
					pmcTRAFFIC_PROTOCOLLER, 
					pmPROCESS_FINISHED, 
					0, 
					&process_msg, 
					SER_SENDMSG_PSIZE 
					);
		13. ProxySession: � ������ ������� ��������� pmPROCESS_FINISHED ������ �������� ���������� 
		    ������ � ��������� �����������, � ��������� ������������ ������ ������� ������������ �� ���������:
				if ( ppmCommand->psStatus == psProcessFinished )
				{
					m_dcTraffic = dcNeedMoreInfo;
					m_hProtocoller = NULL;
				}
				do
				{
					if ( PR_SUCC(err= ppmCommand->hData->SeekRead(&dwRead, pos, data, 1024)) && dwRead )
					{
						pos += dwRead;
						tINT nSend = send( to, data, dwRead, 0 );
					}
				}
				while( PR_SUCC(err) && dwRead  );
		14. ProxySession: ��� ������� ��������� ���������� ������������ �� ��������� ������:
				sysSendMsg( 
					pmcTRAFFIC_PROTOCOLLER, 
					pmSESSION_STOP, 
					0, 
					&m_hSessionCtx, 
					SER_SENDMSG_PSIZE 
					);
		15. Protocoller: ��� ������������ ������ �������� ������, ��������� � ������������� �������:
				delete ((session_t*)p_par_buf)->pdwSessionCtx[po_SMTP];
				((session_t*)p_par_buf)->pdwSessionCtx[po_SMTP] = NULL;
*		
*		
*		
*/		



#ifndef _TRAFFICPROTOCOLLER_H_
#define _TRAFFICPROTOCOLLER_H_

#include <prague/prague.h>
#include <prague/pr_cpp.h>
#include <prague/pr_serializable.h>
#include <prague/iface/i_io.h>
#include <mail/plugin/p_trafficmonitor.h>
#include "trafficprotocollertypes.h"

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

#define TRAFFIC_PROTOCOLLER_INTERFACE_VERSION    1       //!< ������ ���������� ����� ������ � ��������������

namespace TrafficProtocoller
{
	//! ����� ������� ���������� ������ ���� �������������, 
	//! ������� ����� �������� �� ��������.
	//! ��� ������ ���������� ��� ���������� ������ � ����������� ������
	//! � �������������
	enum protocoller_order_t
	{
		po_ProxySession = 0,             //!< �� ���� ������� ��������� �������� ����� ������
		po_SMTP,                         //!< SMTP
		po_POP3,                         //!< POP3
		po_IMAP4,                        //!< IMAP4
		po_NNTP,                         //!< NNTP
		po_HTTP,                         //!< HTTP
		po_FTP,                          //!< FTP
		po_MailWasher,                   //!< MailWasher (�������������� ����������� POP3)
		po_last,                          
	};

	#define pmcTRAFFIC_PROTOCOLLER 0x94d63274 //!< ����� ���������, �������� ������������ ������ � ������������
	//////////////////////////////////////////////////////////////////////////
	//
	// ������� ProxySession=>Protocoller
	//
	#define pmSESSION_START			0x80388a31   //!< ������ ������
	#define pmDETECT				0xa2a5a26a   //!< ������ �� �������������� �������
	#define pmDETECT_EX				0xfd21541    //!< ������ �� �������������� ������� (��� ��������� dcProtocolLikeDetected). ������ ���������������� �� ����� ���������. ��� ����� �� dcDataDetected ��� ����������� ������ ���������� � pmPROCESS.
	#define pmPROCESS				0x79705be3   //!< �������� ������ ��� ���������
	#define pmSESSION_STOP			0x220ac645   //!< ����� ������
	#define pmSESSION_PSEUDO_STOP	0xf01b6b48   //!< ���������� ������ (��������������� ������ ��� �����������, �� ����� ����� ������ ������ �� ����������)
	//
	// ������� ProxySession=>Protocoller
	//
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//
	// ������� Protocoller=>ProxySession
	//
	#define pmPROCESS_FINISHED		0x850eac8c		 //!< ������ �� ��������� ��������� ������
	#define pmKEEP_ALIVE			0xa8bdd659		 //!< ������� �� ���������� ������ ������
	#define pmSESSION_PSEUDO_STOP_REQUEST 0x2276f3ba //!< ������ �� ���������� (����������� ������ ��� �����������, �� ����� ����� ������ ������ �� ����������)
	//
	// ������� Protocoller=>ProxySession
	//
	//////////////////////////////////////////////////////////////////////////

	//! ��� ��������� ���������� � sysSendMsg 
	//! ��� �������� (pmSESSION_START)
	//! � ����������� (pmSESSION_STOP)
	//! ��������� ������ � ������������
	struct session_t : public cSerializable
	{
		session_t():
			dwInterfaceVersion(TRAFFIC_PROTOCOLLER_INTERFACE_VERSION),
			pdwSessionCtx(NULL),
			dwSessionCtxCount(0),
			nServerPort(0),
			dwClientPID(0),
			dwClientRequest(0),
			bSSL(cFALSE)
			{}
	    DECLARE_IID(session_t, cSerializable, PID_TRAFFICMONITOR, 100) ;
		IN tDWORD dwInterfaceVersion;        //!< ������ ���������� ����� ������ � ��������������
		IN OUT tPTR *pdwSessionCtx;          //!< ��������� �� ������ ���������� ������ (� ����� ������ � � �������������)
		IN tDWORD dwSessionCtxCount;         //!< ������ ������� ���������� ������ � ������������� (�.�. = ������������� ���������� �������������)
		cStringObj szServerName;             //!< ��� �������
		tINT nServerPort;                    //!< ���� �������
		tDWORD dwClientPID;                  //!< PID ��������, ��������������� ����������
		IN OUT tDWORD dwClientRequest;       //!< ������ �����, �������������� ������ � ���� ������ (�����). ���� (19 ��� 2005) �� ������������
		tBOOL bSSL;                          //!< �� ���� ������ ������������ SSL
	};

	//! ��� ��������� ���������� � sysSendMsg ��� �������������� ���������
	struct detect_t : public session_t
	{
		detect_t():
			dsDataSource(dsUnknown),
			pLastReceivedData(0),
			ulLastReceivedData(0),
			pdcDetectCode(0),
			phDetectorHandle(0),
			session_t()
			{}
	    DECLARE_IID(detect_t, session_t, PID_TRAFFICMONITOR, 101) ;
		IN data_source_t dsDataSource;   //!< �������� ������
		IN tVOID* pLastReceivedData;     //!< ����� � ������� ��� ������
		IN tULONG ulLastReceivedData;    //!< ������ ������
		OUT detect_code_t* pdcDetectCode;//!< ��������� �������������� ���������
		OUT hOBJECT* phDetectorHandle;   //!< ����� ������������
	};
	
	//! ��� ��������� ���������� � sysSendMsg ��� ������������ �������������� ��������� (������ ������������� �� ����� ��������� dcProtocolLikeDetected)
	struct detect_ex_t : public detect_t
	{
		detect_ex_t():
			pDataBuffer(0),
			ulDataBuffer(0),
			detect_t()
			{}
	    DECLARE_IID(detect_ex_t, detect_t, PID_TRAFFICMONITOR, 102) ;
		IN tVOID* pDataBuffer;           //!< ������ ����� � ������� ��� ������ (��� ������, ���������� � ����������� dsDataSource � ��������� dcProtocolLikeDetected)
		IN tULONG ulDataBuffer;          //!< ������ ������� ������
	};

	enum process_status_t
	{
		psProcessFailed = -1,                   //!< ��������� ������ ��� ���������. ������ ��������
		psUnknown = 0,                          //!< ������ ����������
		psProcessFinished = pmPROCESS_FINISHED, //!< ��������� ���������
		psKeepAlive = pmKEEP_ALIVE,             //!< ��������� ������������
		psCloseConnection,                      //!< ���������� ��������� ����������
		ps_last,
	};
	//! ��� ��������� ���������� � sysSendMsg ��� ��������� ������
	struct process_t : public session_t
	{
		process_t():
			dsDataSource(dsUnknown),
			pData(0),
			ulDataSize(0),
			session_t()
			{
			}
	    DECLARE_IID(process_t, session_t, PID_TRAFFICMONITOR, 103) ;
		IN data_source_t dsDataSource;   //!< �������� ������
		IN tVOID* pData;                 //!< ���� ������
		IN tULONG ulDataSize;            //!< ������ ����� ������
		IN hOBJECT* phDetectorHandle;    //!< ����� ������������ //TODO: ����� ������ ��� ��������������� ����� sysSendMsg
		OUT process_status_t* psStatus;  //!< ������ ��������
	};
	typedef data_source_t data_target_t;
	//! ��� ��������� ����������� � MsgReceive ��� ������� ������������ ������
	struct process_msg_t : public session_t
	{
		process_msg_t():
			dsDataTarget(dsUnknown),
			psStatus(psUnknown),
			hData(0),
			session_t()
			{
			}
	    DECLARE_IID(process_msg_t, session_t, PID_TRAFFICMONITOR, 104) ;
		IN data_target_t dsDataTarget;   //!< �������� ������
		IN process_status_t psStatus;    //!< ������ ��������
		IN hIO hData;                    //!< ������ ��� ���������
	};

	//! ��� ��������� ���������� � sysSendMsg ��� ��� ������ �� ������-��������� ������ (������������ ������ ������ ��������� �����������)
	struct pseudo_stop_t : public session_t
	{
		pseudo_stop_t():
			phProtocollerHandle(0),
			session_t()
			{}
	    DECLARE_IID(pseudo_stop_t, session_t, PID_TRAFFICMONITOR, 105) ;
		IN hOBJECT* phProtocollerHandle;	//!< ����� ������������, ������������ ���������
	};

	//! ��� ��������� ���������� ������������� � ������� �����-��������. ���������������� ������-������ ������ ������� errOK_DECIDED. ��� �������� errNO_DECIDERS ����������� ������ �������������� ���� ������, �������� ���������������
	struct anybody_here_t : public session_t
	{
		anybody_here_t():
			hProtocolType(po_ProxySession),
			session_t()
			{}
	    DECLARE_IID(anybody_here_t, session_t, PID_TRAFFICMONITOR, 106) ;
		protocoller_order_t hProtocolType;   //!< ��� ���������
		cStringObj szObjectName;             //!< ��� ������� (���� ��������). ��� HTTP - URL �������
		cStringObj szObjectType;             //!< Type ������� (���� ��������). ��� HTTP - ContentType �������
	};
}


#endif//_TRAFFICPROTOCOLLER_H_
