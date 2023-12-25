// ProxySession.h: interface for the CProxySession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROXYSESSION_H__1E87F3B9_3C38_49E7_81D9_34DB62CBAF45__INCLUDED_)
#define AFX_PROXYSESSION_H__1E87F3B9_3C38_49E7_81D9_34DB62CBAF45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mail/structs/s_mc_trafficmonitor.h>
#include <prague/pr_wrappers.h>
#include "TransparentSocket.h"
#include "SimpleBufferWindow.h"
#include "ReadWriteSocket.h"
#include "ProxySessionManager.h"

using namespace TrafficProtocoller;
class CProxySessionManager;

// ������� ������� start �������������
#define     FPS_START_SENT              0x1
// ������� ������� stop �������������
#define     FPS_STOP_SENT               0x2
// ����������� ���������� � ��������
#define     FPS_SERVER_CONNECTED        0x4
// ����������� ���������� � ��������
#define     FPS_CLIENT_CONNECTED        0x8
// ��������� ���������� � ��������
#define     FPS_SERVER_DISCONNECTED     0x10
// ��������� ���������� � ��������
#define     FPS_CLIENT_DISCONNECTED     0x20
// � ������� ���� �����, � ������� �� ��������.
#define     FPS_HAS_THREAD              0x40
// ������� ������� �� ����
#define     FPS_FIRST_SELECT            0x80
// �������� ��������� ��� �������������
#define     FPS_CTX_ALLOCATED           0x100
// ������ ����������� � ssl �����
#define     FPS_SWITCHED_SSL            0x200

#define     FPS_GOT_KAVSEND             0x400
#define     FPS_GOT_KAVSVC              0x800
#define     FPS_GOT_KAVCONN_ID          0x1000
// ������ ��������� ������������������� � ������ � ������
#define     FPS_ESTABLISHED             0x2000
// ������ � ��������� �������
#define     FPS_FINISH                  0x4000
// ���������� �������. ����� �������.
#define     FPS_DONE                    0x8000



class CProxySession
{
public:	
    CProxySession( hOBJECT hParent = NULL , CProxySessionManager* manager = NULL, HANDLE StopEvent = NULL );
	virtual ~CProxySession();

    ULONG                   m_Flags;    // ����� ������

    DWORD                   m_dwCDCount; // client data count;

    bool                    m_bInWaitSessionList;

    CProxySessionManager*   m_manager;
    cStringObj              m_szSSLCacheFolder;    
    HANDLE                  m_hStopEvent;
    hOBJECT                 m_hParent;

    DWORD                   m_ThreadID;
    HANDLE                  m_ThreadHandle;

    CTransparentSocket      m_server;            // ����� �������
    CTransparentSocket      m_client;            // ����� �������

    tINT                    m_ServerPort;
    SOCKET                  m_AcceptedSock;
    SOCKET                  m_ConnectSocket;

    char                    m_rIp[50];              // ��������� ����� ���������� ����������
    char                    m_lIp[50];              // ��������� ����� ���������� ����������
    char                    m_Localhost[50];        // ��������� ����� ����������� ����������

    CSimpleBufferWindow*    m_Buf_Client;
    CSimpleBufferWindow*    m_Buf_Server;

    ClearCallbackData*      m_ccdClient;
    ClearCallbackData*      m_ccdServer;

    __int64                 m_ID;                   // ID ��� �����������
    ULONG                   m_StartTime;
    

    tERROR  ParseKavsendBuffer  ( char* Buf, int nRecv );
    tERROR  ParseKavsvcBuffer   ( char* Buf, int nRecv );
    tERROR  ParseKavconnIdBuffer( char* Buf, int nRecv );

    tERROR  StartProtocollers();
    tERROR  StopProtocollers();    
	
	tERROR ReceiveProtocollerCommand(
        IN hOBJECT p_send_point, 
        IN process_msg_t* ppmCommand
        );
	tERROR SendProtocollerDetect(
		IN data_source_t dsDataSource,   // �������� ������
		IN tVOID* pLastReceivedData,     // ����� � ������� ��� ������
		IN tULONG ulLastReceivedData     // ������ ������
		);
	tERROR SendProtocollerDetectEx(
		IN data_source_t dsDataSource,   // �������� ������
		IN tVOID* pDataBuffer,           // ������ ����� � ������� ��� ������ (��� ������, ���������� � ����������� dsDataSource � ��������� dcProtocolLikeDetected)
		IN tULONG ulDataBuffer,          // ������ ������� ������
		IN tVOID* pLastReceivedData,     // ����� � ������� ��� ������ (���������� � ����� ������� ������)
		IN tULONG ulLastReceivedData     // ������ ������
		);
	tERROR SendProtocollerProcess(
		IN data_source_t dsDataSource,   // �������� ������
		IN tVOID* pLastReceivedData,     // ����� � ������� ��� ���������
		IN tULONG ulLastReceivedData     // ������ ������
		);
	tERROR PseudoStop(
		IN hOBJECT hProtocoller          // ������ ������ � ����������� ������������
		);

    static void ClearCallback(CSimpleBufferWindow* _this, tDWORD context, tVOID* data);


    tERROR          ReadKAVSEND();
    tERROR          DoConnect();    
    tINT            ProcessClient();
    
    void            MakeAlert();
    void            ProcessFirstSelect();

    bool            StartClient();    
    void            WaitExitThread();
    void            StopSession();
    void            ProcessExit();
    void            BreakKavsvcConnect();

    void            RemoveFromWaitSessionList();
    
	hOBJECT			m_hProtocoller;			// ��������� �� �������� �����������
	detect_code_t	m_dcDetectCode;			// ������� ��������� ���������
	session_t		m_hSessionCtx;			// �������� ������
	HANDLE			m_hCurrentUser;			// ����� �������� ������������ Windows (������� �������� ������� � ��������� PID)

	tBOOL NeedToSwitchToSSL(cTrafficSelfAskAction& szSSLCacheFolder);

private:
	struct send_buf_t {
        tBYTE*  buf;		// ��������� �� �����
        tSIZE_T	fullsize;	// �������������� ������ ��� ������

		send_buf_t();
		~send_buf_t();
		tBOOL ready();
		tBOOL alloc_more(hIO hData);
		tBOOL alloc_more(tSIZE_T size);
		tBOOL clear();
	};
	
	send_buf_t m_send_buf;	// ������������ ����� ��� �������� ������
	PRLocker   m_send_buf_cs; // ������ ������������� ��� m_send_buf
	SOCKET	   m_socketFromSave;		// ���������� ����� ��� ����������� ����� ��������� ������
};

// ��� ����������� CProxySession � ��������� ������ �������.
struct CDoneSession
{
    bool operator ()(CProxySession* pSession) 
    {
        if ( pSession->m_Flags & FPS_DONE )
        {
            if ( pSession->m_bInWaitSessionList )
            {
                pSession->RemoveFromWaitSessionList();
            }
            delete pSession;
            return true;
        }

        // �� �������������� �� ������. � KAVCONN_ID �� ������. ( ������� ������ ��� ������ ����������� )
        // � ���� ������ ����� �������, ��� ���-�� ����� �� ��� ( ������ ������ ���� ), ������ ������� � ����������.
        if ( 
            ( pSession->m_Flags & FPS_GOT_KAVSVC ) && 
            ( pSession->m_Flags & FPS_SERVER_CONNECTED ) &&
            !( pSession->m_Flags & FPS_GOT_KAVCONN_ID ) )
        {   
#ifdef _DEBUG
			const int seconds_timeout = 30;
#else
			const int seconds_timeout = 3;
#endif
            if ( GetTickCount() - pSession->m_StartTime > 1000 * seconds_timeout )
            {
                pSession->m_Flags |= FPS_FINISH;
            }
        }

        if ( pSession->m_Flags & FPS_FINISH )
        {
            pSession->WaitExitThread();
            pSession->ProcessExit();
            if ( pSession->m_bInWaitSessionList )
            {
                pSession->RemoveFromWaitSessionList();
            }

            delete pSession;
            return true;
        }

        return false; 
    } 
};

int
AssociateCR( SOCKET client, SOCKET server );

tBOOL GetParam(cStringObj& sBuf, cStringObj& sRes, tINT& nStart);

tBOOL ParseKAVSEND( 
                   IN tCHAR* Buf, 
                   IN tDWORD dwSize, 
                   OUT cStringObj& szServerName, 
                   OUT unsigned short& nPort,
                   OUT unsigned short& nMaskedPort,
                   OUT tDWORD& dwClientPID
                   );

LPCSTR GetDetectCodeString(tDWORD code);

#endif // !defined(AFX_PROXYSESSION_H__1E87F3B9_3C38_49E7_81D9_34DB62CBAF45__INCLUDED_)
