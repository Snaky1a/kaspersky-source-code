/*!
 * (C) 2006 Kaspersky Lab
 * 
 * \file	cisco_const.h
 * \author	Eugene Rogozhnikov
 * \date	17.10.2006 17:14:53
 * \brief	
 * 
 */

#ifndef __CISCO_CONST_H__
#define __CISCO_CONST_H__

//! ��� ���������� ��� CISCO
#define KLCISCO_COMPONENT_NAME   L"CISCO_NAC"

//! ������ �������� ��� CISCO
#define KLCISCO_SETTINGS   L"CISCO_NAC"

//#define KLCISCO_INSTALLED   L"CiscoNACInstalled" // BOOL

//! ���� PVS-�������
#define KLCISCO_PVS_PORT   L"PVSPort" // INT
#define KLCISCO_PVS_PORT_DEFAULT   18000 // INT

//! ����� �����������, ��� ������
#define KLCISCO_HEALTHY_RULE   L"HealthyRule"
#define KLCISCO_CHECKUP_RULE   L"CheckUpRule"
#define KLCISCO_QUARANTINE_RULE   L"QuarantineUpRule"
#define KLCISCO_INFECTED_RULE   L"InfectedUpRule"

//! ����� �����������, ��� �������

// ��������
#define KLCISCO_TEST_CONDITION   L"Test"
#define KLCISCO_TEST2_CONDITION   L"Test2"

#define KLCISCO_AV_INSTALLED_CONDITION		L"AVSoftwareInstalled"
#define KLCISCO_AV_RUNNING_CONDITION		L"AVSoftwareRunning"
#define KLCISCO_HAS_RTP_CONDITION			L"HasRTP"
#define KLCISCO_RTP_STATE_CONDITION			L"RTPState"
#define KLCISCO_LAST_FSCAN_CONDITION		L"LastFScanDate"
#define KLCISCO_BASES_DATE_CONDITION		L"BasesDate"
#define KLCISCO_LAST_CONNECTED_CONDITION	L"LastConnectedDate"

//! ����� �������� �������
#define KLCISCO_RULE_CONDITION_CHECK   L"check"	// BOOL
#define KLCISCO_RULE_CONDITION_OPERATION   L"operation"	// INT - KLCISCO::AttributeCompareOperation
#define KLCISCO_RULE_CONDITION_VALUE   L"value"	// ������� �� �������

namespace KLCISCO
{
	//23668 - �������� Kaspersky Lab �������� �� IANA (http://www.iana.org/assignments/enterprise-numbers)
	const unsigned long VENDOR_ID = 23668;
	// APP_NUM = 3 �������� ������������ ����������. ������ NAC_AVP_Spec_v2.pdf, ��� 5
	const unsigned short APP_NUM = 3;


	//////////////////////////////////////////////////////////////////////////////
	// �������� ����� �� NAC_AVP_Spec_v2.pdf, ��� 7
	enum PostureToken
	{
		PT_HEALTHY = 0,
		PT_CHECKUP = 10,
		PT_QUARANTINE = 20,
		//PT_TRANSITION,
		PT_INFECTED = 30,
		PT_UNKNOWN = 100
	};
/*	enum PostureToken
    {
        PT_HEALTHY = 0,
        PT_CHECKUP,
        PT_QUARANTINE,
		PT_TRANSITION,
		PT_INFECTED,
		PT_UNKNOWN
    }; */

	enum AttributeCompareOperation
	{
		ACO_EQUAL = 0,
		ACO_NOT_EQUAL,
		ACO_LESS,
		ACO_LESS_OR_EQUAL,
		ACO_GREATER,
		ACO_GREATER_OR_EQUAL,
		ACO_IN,
		ACO_NOT_IN
	};

	typedef enum
    {
        MaskRtpState_Stopped                = 0x00010000,
        MaskRtpState_Suspended              = 0x00020000,
        MaskRtpState_Starting               = 0x00040000,
        MaskRtpState_Running                = 0x00080000,
        MaskRtpState_Running_MaxProtection  = 0x00100000,
        MaskRtpState_Running_MaxSpeed       = 0x00200000,
        MaskRtpState_Running_Recomended     = 0x00400000,
        MaskRtpState_Running_Custom         = 0x00800000,
        MaskRtpState_Failure                = 0x01000000
    } RtpStateMask;

}; // namespace KLCISCO

#endif //__CISCO_CONST_H__