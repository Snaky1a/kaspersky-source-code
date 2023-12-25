#if !defined(_CKAHPORTS_H__INCLUDED_)
#define _CKAHPORTS_H__INCLUDED_

// Firewall
namespace CKAHFW
{
    const int APPNAMELEN = 1100;
    const int CMDLINELEN = 1100;
    // �������� �����

    struct OpenPort
    {
        UCHAR       Proto;               // ��������
        CKAHUM::IP  LocalIP;             // ��������� IP-�����
        USHORT      LocalPort;           // ��������� ����
        ULONG       PID;                 // PID ��������
        WCHAR       AppName[APPNAMELEN]; // �������� �������� (����-��������������� ������-������)
        WCHAR       CmdLine[CMDLINELEN]; // ��������� ������ (����-��������������� ������-������)
        ULONG       ActiveTime;          // ����� ���������� ����� (� ��������)
        __int64     InBytes;             // ���������� �������� ����
        __int64     OutBytes;            // ���������� ��������� ����                           
    };

    typedef LPVOID HOPENPORTLIST;

    // �������� ������ �������� ������
    CKAHUMMETHOD GetOpenPortList ( OUT HOPENPORTLIST * phlist );

    // �������� ������ ������ �������� ������
    CKAHUMMETHOD OpenPortList_GetSize ( IN HOPENPORTLIST hlist, OUT int * psize );

    // �������� ������� ������ �������� ������
    CKAHUMMETHOD OpenPortList_GetItem ( IN HOPENPORTLIST hlist, IN int n, OUT OpenPort * pport );

    // ������� ������ �������� ������
    CKAHUMMETHOD OpenPortList_Delete ( IN HOPENPORTLIST hlist );

    
    // ������������� ����������

    struct Connection
    {
        UCHAR       Proto;               // ��������
        CKAHUM::IP  LocalIP;             // ��������� IP-�����
        CKAHUM::IP  RemoteIP;            // ��������� IP-�����
        USHORT      LocalPort;           // ��������� ����
        USHORT      RemotePort;          // ��������� ����
        ULONG       PID;                 // PID ��������
        UCHAR       IsIncoming;          // �������� �� ���������� (1 - ��������, 0 - ���������)
        WCHAR       AppName[APPNAMELEN]; // �������� �������� (����-��������������� ������-������)
        WCHAR       CmdLine[CMDLINELEN]; // ��������� ������ (����-��������������� ������-������)
        ULONG       ActiveTime;          // ����� ���������� ����� (� ��������)
        __int64     InBytes;             // ���������� �������� ����
        __int64     OutBytes;            // ���������� ��������� ����                           
    };

    typedef LPVOID HCONNLIST;

    // �������� ������ ������������� ����������
    CKAHUMMETHOD GetConnectionList ( OUT HCONNLIST * phlist );

    // �������� ������ ������ ������������� ����������
    CKAHUMMETHOD ConnectionList_GetSize ( IN HCONNLIST hlist, OUT int * psize );

    // �������� ������� ������ ������������� ����������
    CKAHUMMETHOD ConnectionList_GetItem ( IN HCONNLIST hlist, IN int n, OUT Connection * pconn );

    // ������� ������ ������������� ����������
    CKAHUMMETHOD ConnectionList_Delete ( IN HCONNLIST hlist );

    // ��������� ������������� ����������
    CKAHUMMETHOD BreakConnection ( IN UCHAR Proto, IN CKAHUM::IP *pLocalIP, IN USHORT LocalPort, IN CKAHUM::IP *pRemoteIP, IN USHORT RemotePort );
    
    struct HostStat
    {
        __int64 inBytes;
        __int64 outBytes;
    };
    
    struct HostStatItem
    {
        CKAHUM::IP  HostIp;
        
        HostStat    TotalStat;
        HostStat    TcpStat;
        HostStat    UdpStat;
        HostStat    BroadcastStat; 
    };
    
    typedef LPVOID HHOSTSTATLIST;

    // �������� ������ ���������� ������
    CKAHUMMETHOD GetHostStatistics      ( OUT HHOSTSTATLIST * hlist );

    // �������� ������ ������ ���������� ������
    CKAHUMMETHOD HostStatistics_GetSize ( IN HHOSTSTATLIST hlist, OUT int * psize );

    // �������� ������� ������ ���������� ������
    CKAHUMMETHOD HostStatistics_GetItem ( IN HHOSTSTATLIST hlist, IN int n, OUT HostStatItem * pconn );

    // ������� ������ ���������� ������
    CKAHUMMETHOD HostStatistics_Delete  ( IN HHOSTSTATLIST hlist );

};

#endif // !defined(_CKAHPORTS_H__INCLUDED_)
