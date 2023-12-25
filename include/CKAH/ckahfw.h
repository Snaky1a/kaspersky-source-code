#ifndef __CKAHFW_H__
#define __CKAHFW_H__

#include "ckahrules.h"

// Firewall
namespace CKAHFW
{
	//	Firewall rules
	
	CKAHUMMETHOD GetPacketRules (OUT HPACKETRULES *phRules);
	CKAHUMMETHOD SetPacketRules (IN HPACKETRULES hRules);

	CKAHUMMETHOD GetApplicationRules (OUT HAPPRULES *phRules);
	CKAHUMMETHOD SetApplicationRules (IN HAPPRULES hRules);

	CKAHUMMETHOD GetApplicationChecksum (IN LPCWSTR szwApplicationPath, OUT UCHAR Checksum[FW_HASH_SIZE]);
    CKAHUMMETHOD GetApplicationChecksumVersion (OUT PULONG pVersion);

	// �������� callback-������� ����������� � ������������ ��������� �������
	struct PacketRuleNotify
	{
		LPCWSTR     RuleName;			// ��� �������
		bool	    IsBlocking;			// ����� ������������ / ��������
		bool	    IsIncoming;			// �������� / ��������� �����
        bool        IsStream;           // 
        bool        IsStreamIncoming;   // �������� / ��������� �����
		UCHAR	    Proto;				// ��������
		CKAHUM::IP	RemoteAddress;		// ��������� IP-�����
		CKAHUM::IP	LocalAddress;		// ��������� IP-�����
		USHORT	    TCPUDPRemotePort;	// ��������� ���� (������ ��� ���������� TCP � UDP)
		USHORT	    TCPUDPLocalPort;	// ��������� ���� (������ ��� ���������� TCP � UDP)
		UCHAR	    ICMPType;			// ICMP ��� (������ ��� ��������� ICMP)
		UCHAR	    ICMPCode;			// ICMP ��� (������ ��� ��������� ICMP)
		bool	    Log;				// ������� � ������
		bool	    Notify;				// ��������� ������������ (���� �� ���� �� Log, Notify == true)
		__int64     Time;				// ����� ������� (UTC FILETIME)
		UCHAR*      pUserData;			// ���������������� ������ ������� (NULL ���� ������ ���)
		ULONG	    UserDataSize;		// ������ ���������������� ������ � ������
	};

	// �������� callback-������� ����������� � ������������ ������� ��� ���������� (Popup == false)
	// ��� ����������� ������� ���������� ���������� ��� ���������� ������� (Popup == true)
	// (*) - �� ������������ ��� ����������� ������� ���������� ���������� ��� ���������� ������� 
	struct ApplicationRuleNotify
	{
		LPCWSTR     RuleName;			// ��� ������� (*)
		LPCWSTR     ApplicationName;	// ��� ����������
        LPCWSTR     CommandLine;        // ��������� ������ ����������
		ULONG	    PID;				// PID ����������
		bool	    IsBlocking;			// ������������� / ��������� (*)
		bool	    IsIncoming;			// �����������
        bool        IsStream;           // 
        bool        IsStreamIncoming;   // �������� / ��������� �����
		UCHAR	    Proto;				// �������� (TCP ��� UDP)
		CKAHUM::IP	RemoteAddress;		// ��������� IP-�����
		CKAHUM::IP	LocalAddress;		// ��������� IP-�����
		USHORT	    RemotePort;			// ��������� ����
		USHORT	    LocalPort;			// ��������� ����
		bool	    Popup;				// ������ ������������ (������� ���) (���� Popup == true, �� Log � Notify == false)
		bool	    Log;				// ������� � ������
		bool	    Notify;				// ��������� ������������ (���� �� ���� �� Log, Notify == true, ���� Popup == false)
		__int64     Time;				// ����� ������� (UTC FILETIME)
		UCHAR*      pUserData;			// ���������������� ������ ������� (NULL ���� ������ ���) (*)
		ULONG	    UserDataSize;		// ������ ���������������� ������ � ������ (*)
	};

	// �������� callback-������� ����������� � �������������� ����������� ����� �����
	struct ChecksumChangedNotify
	{
		LPCWSTR ApplicationName;	// ��� ����������
		ULONG	PID;				// PID ����������
		__int64 Time;				// ����� ������� (UTC FILETIME)
		UCHAR	ApplicationOldChecksum[FW_HASH_SIZE]; // ����������� ����������� ����� ����������
		UCHAR	ApplicationNewChecksum[FW_HASH_SIZE]; // ����� ����������� ����� ����������
	};

	enum RuleCallbackResult
	{
		crBlock,
		crPass,
		crPassModifyChecksum // ����������� ��� �������� ��� CHECKSUMNOTIFYCALLBACK
	};		

	// callback-������� ����������� � ������������ ��������� �������
	typedef void (CALLBACK *PACKETRULENOTIFYCALLBACK) (LPVOID lpContext, const PacketRuleNotify *pNotify);

	// callback-������� ����������� � ������������ ������� ��� ����������
	typedef RuleCallbackResult (CALLBACK *APPLICATIONRULENOTIFYCALLBACK) (LPVOID lpContext, const ApplicationRuleNotify *pNotify);

	// callback-������� ����������� � �������������� ����������� ����� �����
	typedef RuleCallbackResult (CALLBACK *CHECKSUMNOTIFYCALLBACK) (LPVOID lpContext, const ChecksumChangedNotify *pNotify);

	// ��������� Firewall
	CKAHUMMETHOD Start (PACKETRULENOTIFYCALLBACK PacketRuleNotifyCallback, LPVOID lpPacketCallbackContext,
						APPLICATIONRULENOTIFYCALLBACK ApplicationRuleNotifyCallback, LPVOID lpApplicationCallbackContext,
						CHECKSUMNOTIFYCALLBACK ChecksumCallback, LPVOID lpChecksumCallbackContext);

	// ������������� Firewall
	CKAHUMMETHOD Stop ();

	// ���������������� Firewall (��� ������� ������ �������������)
	CKAHUMMETHOD Pause ();

	// ������������ ������ Firewall (��� ������� ������ �������������)
	CKAHUMMETHOD Resume ();

	CKAHUMMETHOD FixPid ();

	
	enum WorkingMode
	{
		wmBlockAll,
		wmRejectNotFiltered,
		wmAskUser,
		wmAllowNotFiltered,
		wmAllowAll
	};

	// ������������� ����� ������
	CKAHUMMETHOD SetWorkingMode (WorkingMode mode);

	// �������� ����� ������
	CKAHUMMETHOD GetWorkingMode (WorkingMode *mode);

    enum FilteringMode
    {
        fmMaxCompatibility,
        fmMaxSpeed
    };
    
    CKAHUMMETHOD SetFilteringMode( FilteringMode mode );

    CKAHUMMETHOD GetFilteringMode( FilteringMode mode );
};

#include "ckahports.h"
#include "ckahnetwork.h"

#pragma warning(default : 4200)

#endif