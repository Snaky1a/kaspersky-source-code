#if !defined(CKAHREDIRECTOR_H__INCLUDED_)
#define CKAHREDIRECTOR_H__INCLUDED_

// Connection redirector
namespace CKAHCR
{
    typedef LPVOID HPROXY;
    typedef LPVOID HPORTLIST;
    typedef LPVOID HEXCLUDE;

	// ��������� Redirector
	CKAHUMMETHOD Start ();

	// ������������� Redirector
	CKAHUMMETHOD Stop ();

	// ���������������� Redirector (��� ������� ������ �������������)
	CKAHUMMETHOD Pause ();

	// ������������ ������ Redirector (��� ������� ������ �������������)
	CKAHUMMETHOD Resume ();

    // ������������� �����, ����� ������� Redirector ������ ���� ��������, ���� ����� �� ����� ��������
    CKAHUMMETHOD SetWatchdogTimeout (DWORD timeout_sec);

    // ������������ ������
    CKAHUMMETHOD RegisterProxy(USHORT port, DWORD pid, OUT HPROXY * phproxy);

    // ������������ ������
    CKAHUMMETHOD RegisterProxy2(USHORT port, USHORT serv_port, DWORD pid, OUT HPROXY * phproxy);

    // ���������� �������� CrAskConnection � ��ReplyConnection, ����� ������������ ����������
    // �� �������� ����� �������� ��������.
#pragma pack( push, 1 )
    typedef struct _AskConnection {    
        unsigned long   m_Ver;          // ��� ���������
        unsigned long   m_Size;         // ������ ���������

        _ip_addr_t      m_rIp;
        unsigned short  m_rPort;
        unsigned long   m_PID;
    } AskConnection ;

    typedef struct _ReplyConnection {
        unsigned long   m_Status;       // ������ ���������� � ��������. ( KL_STATUS )
        __int64         m_ID;           // ID ����������. ( ��� �������������� �������������� � �������������� )
    } ReplyConnection;

#pragma pack( pop )

    // ��������������� ������
    CKAHUMMETHOD Proxy_Unregister(IN HPROXY hproxy);

    // ��������� ���� � ������ ������ ���������������
    CKAHUMMETHOD Proxy_AddPort (IN HPROXY hproxy, USHORT port);

    // ������� ���� �� ������ ����� ���������������
    CKAHUMMETHOD Proxy_RemovePort (IN HPROXY hproxy, USHORT port);

    // �������� ������� ������ ������ ���������������
    CKAHUMMETHOD Proxy_GetPortList ( IN HPROXY hproxy, OUT HPORTLIST * phlist );

    // ������� ����� ������ ������ ���������������
    CKAHUMMETHOD PortList_Delete ( IN HPORTLIST hlist );

    // �������� ������ ������ ������ ���������������
    CKAHUMMETHOD PortList_GetSize ( IN HPORTLIST hlist, OUT int * psize );

    // �������� ������� ������ ������ ���������������
    CKAHUMMETHOD PortList_GetItem ( IN HPORTLIST hlist, IN int n, OUT USHORT * pport );
    
    // ��������� ���������� �������� 
    CKAHUMMETHOD Proxy_AddExclude     ( IN CKAHUM::IP* host, IN USHORT port, IN wchar_t* ImagePath, IN ULONG ImagePathSize, OUT HEXCLUDE* phex);

    // ������� ���������� ��������
    CKAHUMMETHOD Proxy_RemoveExclude  ( IN HEXCLUDE hex );

    CKAHUMMETHOD Associate_Conn( 
                            IN ULONG lIp1, IN USHORT lPort1, IN ULONG rIp1, IN USHORT rPort1,
                            IN ULONG lIp2, IN USHORT lPort2, IN ULONG rIp2, IN USHORT rPort2 );

    CKAHUMMETHOD Drv_GetFlags( ULONG* flags );

    CKAHUMMETHOD Drv_SetQuitEvent();

};



#endif // !defined(CKAHREDIRECTOR_H__INCLUDED_)
