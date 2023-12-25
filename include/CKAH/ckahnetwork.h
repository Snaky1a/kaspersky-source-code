#if !defined(_CKAHNETWORK_H__INCLUDED_)
#define _CKAHNETWORK_H__INCLUDED_

// Firewall
namespace CKAHFW
{
    const int ADAPTERNAMELEN = 256;
    const int ADAPTERDESCLEN = 256;
    const int PHYSLEN = 8;

    struct Network
    {
        BOOL            HasIPv4;                            // ������� IPv4
        DWORD           IPv4;                               // IPv4-����� ����
        DWORD           Maskv4;                             // IPv4-����� ����
        BOOL            HasIPv6;                            // ������� IPv6
        CKAHUM::IPv6    IPv6;                               // IPv6-����� ����
        CKAHUM::IPv6    Maskv6;                             // IPv6-����� ����
        DWORD           Zones[CKAHUM::IPv6::MaxScopes];     // IPv6 zone indices ��� ���� scopes
        CHAR            AdapterName[ADAPTERNAMELEN];        // ��� ��������
        CHAR            AdapterDesc[ADAPTERDESCLEN];        // �������� ��������
        DWORD           PhysLength;
        BYTE            Phys[PHYSLEN];                      // MAC-����� ��������
    };

    typedef LPVOID HNETWORKLIST;

	// callback-������� ����������� �� ��������� ������������ ����
	typedef VOID (CALLBACK *NETWORKCHANGEPROC) (LPVOID lpContext);

    // ������������ ����

    // ���������� callback ��� ����������� �� ��������� ������������ ����
	CKAHUMMETHOD SetNetworkChangeCallback ( NETWORKCHANGEPROC NetworkChangeCallback, LPVOID lpContext );

    // �������� ������ �����
	CKAHUMMETHOD GetNetworkList ( HNETWORKLIST * phlist );

    // �������� ������ ������ �����
    CKAHUMMETHOD NetworkList_GetSize ( HNETWORKLIST hlist, int * psize );

    // �������� ������� ������� �����
    CKAHUMMETHOD NetworkList_GetItem ( HNETWORKLIST hlist, int n, Network * pnet );

    // ������� ������ �����
    CKAHUMMETHOD NetworkList_Delete ( HNETWORKLIST hlist );
};

#endif // !defined(_CKAHNETWORK_H__INCLUDED_)
