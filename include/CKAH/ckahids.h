#ifndef __CKAHIDS_H__
#define __CKAHIDS_H__

#include "ckahip.h"
#include "../../windows/Hook/Plugins/Include/attacknotify_api.h"

// IDS
namespace CKAHIDS
{
	// �������� callback-������� ����������� �� �����
	struct AttackNotify
	{
		ULONG	    AttackID;			// ������������� �����
		LPCWSTR	    AttackDescription;	// �������� ����� (����-��������������� ������-������)
		UCHAR	    Proto;				// ��������
		CKAHUM::IP	AttackerIP;			// IP-����� ����������
		USHORT	    LocalPort;			// ����
		ULONG	    ResponseFlags;		// ����� ������ (��. $/windows/Hook/Plugins/Include/attacknotify_api.h)
		__int64     Time;				// ����� ����� (UTC FILETIME)
	};

	// callback-������� ����������� �� �����
	typedef void (CALLBACK *ATTACKNOTIFYPROC) (LPVOID lpContext, const AttackNotify *pAttackNotify);

	// ��������� IDS
	CKAHUMMETHOD Start (ATTACKNOTIFYPROC AttackNotifyCallback,	// callback-������� ����������� �� �����
										LPVOID lpCallbackContext);			// �������� lpContext callback-�������

	// ������������� IDS
	CKAHUMMETHOD Stop ();

	// ���������������� IDS (��� ������� ������ �������������)
	CKAHUMMETHOD Pause ();

	// ������������ ������ IDS (��� ������� ������ �������������)
	CKAHUMMETHOD Resume ();

	// ���������� ����������� IDS

	// ������������� ��� ����� AttackID �������� ParmNum � �������� ParmValue
	CKAHUMMETHOD SetIDSParam (ULONG AttackID, ULONG ParmNum, ULONG ParmValue);
	// �������� ��� ����� AttackID �������� ParmNum � pParmValue
	CKAHUMMETHOD GetIDSParam (ULONG AttackID, ULONG ParmNum, PULONG pParmValue);
	// �������� ��� ����� AttackID ���������� ����������
	CKAHUMMETHOD GetIDSParamCount (ULONG AttackID, PULONG pParamCount);

	// ������������� ��������� ����������� �� ������
	// AttackID - ������������� �����, 0 - ��� ���� �� ���������
	// ResponseFlags - ����� �� $/windows/Hook/Plugins/Include/attacknotify_api.h
	// BanTime - ����� ������������ ���������� (� ��������)
	CKAHUMMETHOD SetIDSAttackNotifyParam (ULONG AttackID, ULONG ResponseFlags, ULONG BanTime);

    // ������������� ������ ����������� ��� �������������� ����� (����������� �� �����
    // ����� �� ����� ���������� ����, ��� ��������� ������)
    CKAHUMMETHOD SetIDSAttackNotifyPeriod (ULONG NotifyPeriod);

	// Banomet

    struct BannedHost
    {
        CKAHUM::IP  IP;                 // IP-�����
        __int64     BanTime;            // �����, ����� ��� ������� (UTC FILETIME)
    };

    typedef LPVOID HBANNEDLIST;

    // �������� ������ ���������� ������
    CKAHUMMETHOD GetBannedList ( OUT HBANNEDLIST * phList );

    // �������� ������ ������ ���������� ������
    CKAHUMMETHOD BannedList_GetSize ( IN HBANNEDLIST hList, OUT int * psize );

    // �������� ������� ������ ���������� ������ 
    CKAHUMMETHOD BannedList_GetItem ( IN HBANNEDLIST hList, IN int n, OUT BannedHost * pBannedHost );

    // ������� ������ ���������� ������
    CKAHUMMETHOD BannedList_Delete ( IN HBANNEDLIST hList );

	// ������������ ����� � ip-������� ip �� ����� mask
	CKAHUMMETHOD UnbanHost (IN CKAHUM::IP *pIp, IN CKAHUM::IP *pMask);

};

#endif