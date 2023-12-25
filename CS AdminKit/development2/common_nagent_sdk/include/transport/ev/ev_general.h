#ifndef __KLEVP_GENERAL_H__DA8BB648_DA39_4de6_A5B5_992918B14BC4
#define __KLEVP_GENERAL_H__DA8BB648_DA39_4de6_A5B5_992918B14BC4

// ! brief ��.�������� ��������� KLEVP_EVENT_SEVERITY
#define KLEVP_EVENT_SEVERITY_INVALID_VALUE         0		// Invalid or ignored severity value

#define KLEVP_EVENT_SEVERITY_INFO                  1
#define KLEVP_EVENT_SEVERITY_WARNING               2
#define KLEVP_EVENT_SEVERITY_ERROR                 3
#define KLEVP_EVENT_SEVERITY_CRITICAL              4

namespace KLEVP
{
// ���������� ������� (��������)
	const wchar_t c_szwGnrlEvent_News[] = L"GNRL_EV_NEWS";
	const wchar_t c_szwGnrlEvent_VirusFound[] = L"GNRL_EV_VIRUS_FOUND";
    const wchar_t c_szwGnrlEvent_InfectedObjectFound[] = L"GNRL_EV_INFECTED_OBJECT_FOUND";
	const wchar_t c_szwGnrlEvent_SuspiciousFound[] = L"GNRL_EV_SUSPICIOUS_OBJECT_FOUND";
	const wchar_t c_szwGnrlEvent_PasswProtectedFound[] = L"GNRL_EV_PASSWD_ARCHIVE_FOUND";
    const wchar_t c_szwGnrlEvent_Quarantined[] = L"GNRL_EV_OBJECT_QUARANTINED";

	const wchar_t c_szwGnrlEvent_ObjectCured[] = L"GNRL_EV_OBJECT_CURED";
	const wchar_t c_szwGnrlEvent_ObjectDeleted[] = L"GNRL_EV_OBJECT_DELETED";
	const wchar_t c_szwGnrlEvent_ObjectNotCured[] = L"GNRL_EV_OBJECT_NOTCURED";
    const wchar_t c_szwGnrlEvent_ObjectBlocked[] = L"GNRL_EV_OBJECT_BLOCKED";
    const wchar_t c_szwGnrlEvent_ObjectPassed[] = L"GNRL_EV_OBJECT_PASSED";

	const wchar_t c_szwGnrlEvent_ProtLevelChanged[] = L"GNRL_EV_PTOTECTION_LEVEL_CHANGED";
	const wchar_t c_szwGnrlEvent_LicenseExpiration[] = L"GNRL_EV_LICENSE_EXPIRATION";
	const wchar_t c_szwGnrlEvent_Error[] = L"GNRL_EV_ERROR";
	const wchar_t c_szwGnrlEvent_InternalError[] = L"GNRL_EV_INTERNAL_ERROR";
	const wchar_t c_szwGnrlEvent_BasesExpired[] = L"GNRL_EV_ANTIVIRAL_BASES_EXPIRED";
	const wchar_t c_szwGnrlEvent_NodeWasRebooted[] = L"GNRL_EV_NETWORK_NODE_WAS_REBOOTED";
	const wchar_t c_szwGnrlEvent_FullscanNotification[] = L"GNRL_EV_FULLSCAN_STATUS_NOTIFICATION";
	const wchar_t c_szwGnrlEvent_ApplicationWasRestarted[] = L"GNRL_EV_APPLICATION_WAS_RESTARTED";
    const wchar_t c_szwGnrlEvent_FullScanCompleted[] = L"KLBL_EV_FSCAN_COMPLETED";

	const wchar_t c_szwGnrlEvent_AttackDetected[] = L"GNRL_EV_ATTACK_DETECTED";
	const wchar_t c_szwGnrlEvent_MacroBlocked[] = L"GNRL_EV_MACRO_BLOCKED";
	const wchar_t c_szwGnrlEvent_MacroAllowed[] = L"GNRL_EV_MACRO_ALLOWED";

    const wchar_t c_outbrpTime[]=L"KLEVP_c_outbrpTime"; //INT_T, ������
    const wchar_t c_outbrpAmount[]=L"KLEVP_c_outbrpAmount"; //INT_T, ���-��
    const wchar_t c_outbrpType[]=L"KLEVP_c_outbrpType"; //INT_T, KLEVP::EVirusOutbreakType
	/*!
        ������� c_szwGnrlEvent_VirusOutbreak ����������� ��� ���������� ������
            ���������� ��������� ������� � ������� �������
        ���������:
            c_outbrpTime,   INT_T, ������
            c_outbrpAmount, INT_T, ���-��
            c_er_severity, INT_T, �������� �������.
    */
    const wchar_t c_szwGnrlEvent_VirusOutbreak[] = L"GNRL_EV_VIRUS_OUTBREAK";


    const wchar_t c_er_array[] = L"KLEVP_EVENT_RANGE_ARRAY";  // ��� ��������� '������ �������'

    const wchar_t c_er_event_id[]                   = L"event_id"; // INT_T
    const wchar_t c_er_severity[]                   = L"GNRL_EA_SEVERITY"; // INT_T
    const wchar_t c_er_domain_name[]                = L"domain_name"; //  STRING_T
    const wchar_t c_er_group_name[]					= L"group_name"; //  STRING_T
    const wchar_t c_er_hostname[]                   = L"hostname"; //  STRING_T
    const wchar_t c_er_product_name[]               = L"product_name"; //  STRING_T
    const wchar_t c_er_product_version[]            = L"product_version"; //  STRING_T
    const wchar_t c_er_product_displ_version[]      = L"product_displ_version"; //  STRING_T
    const wchar_t c_er_event_type[]                 = L"event_type"; //  STRING_T
    const wchar_t c_er_event_type_display_name[]    = L"event_type_display_name"; //  STRING_T
    const wchar_t c_er_descr[]                      = L"GNRL_EA_DESCRIPTION"; //  STRING_T
    const wchar_t c_er_descr_display_name[]         = L"GNRL_EA_DESCRIPTION_DISP_NAME"; //  STRING_T ������������� Event description
    const wchar_t c_er_rise_time[]                  = L"rise_time"; // DATE_TIME_T
    const wchar_t c_er_body[]                       = L"body"; // PARAMS_T
    const wchar_t c_er_par1[]                       = L"GNRL_EA_PARAM_1"; // STRING_T
    const wchar_t c_er_par2[]                       = L"GNRL_EA_PARAM_2"; // STRING_T
    const wchar_t c_er_par3[]                       = L"GNRL_EA_PARAM_3"; // STRING_T
    const wchar_t c_er_par4[]                       = L"GNRL_EA_PARAM_4"; // STRING_T
    const wchar_t c_er_par5[]                       = L"GNRL_EA_PARAM_5"; // STRING_T
    const wchar_t c_er_par6[]                       = L"GNRL_EA_PARAM_6"; // STRING_T
    const wchar_t c_er_par7[]                       = L"GNRL_EA_PARAM_7"; // STRING_T
    const wchar_t c_er_par8[]                       = L"GNRL_EA_PARAM_8"; // STRING_T
    const wchar_t c_er_par9[]                       = L"GNRL_EA_PARAM_9"; // STRING_T
    const wchar_t c_er_locid[]                      = L"GNRL_EA_ID"; // INT_T
    const wchar_t c_er_completedPercent[]           = L"GNRL_COMPLETED_PERCENT";  // INT_T, ����������� �������
    const wchar_t c_er_hostDisplayName[]            = L"hostdn";  // STRING_T, windows-��� �����
    const wchar_t c_er_group_id[]					= L"group_id"; // INT_T
    const wchar_t c_er_task_old_state[]				= L"task_old_state"; // INT_T
    const wchar_t c_er_task_new_state[]				= L"task_new_state"; // INT_T
    const wchar_t c_er_task_display_name[]          = L"task_display_name"; //  STRING_T
    const wchar_t c_er_event_type_id[]              = L"event_type_id"; // INT_T, ������������� ���� �������

	enum EDetectionType
	{
		dtUnknown = 0,
		dtVIRUS = 60,
		dtTROJAN = 61,
		dtMALWARE = 62,
		dtBACKDOOR = 63,
		dtWORM = 64,
		dtRISKWARE = 65,
	};

	enum EEventTypeIdsBase{
		GNRL_Base =		0x0000,
		WKS6_Base =		0x1000,
		FS6_Base =		0x2000,
		FSEE6_Base =	0x3000,
		KLIN_Base =		0x4000,
		WKS7_Base =		0x5000,
		FS7_Base =		0x6000
	};

	enum EEventTypeGnrlIds{
		GNRL_Event_Unknown =					0x0000,
		GNRL_Event_Common =						0x0001,

		GNRL_Event_News =						0x0002,
		GNRL_Event_VirusFound =					0x0003,
		GNRL_Event_InfectedObjectFound =		0x0004,
		GNRL_Event_SuspiciousFound =			0x0005,
		GNRL_Event_PasswProtectedFound =		0x0006,
		GNRL_Event_Quarantined =				0x0007,	

		GNRL_Event_ObjectCured =				0x0008,
		GNRL_Event_ObjectDeleted =				0x0009, 
		GNRL_Event_ObjectNotCured =				0x000A,
		GNRL_Event_ObjectBlocked =				0x000B, 
		GNRL_Event_ObjectPassed =				0x000C,

		GNRL_Event_ProtLevelChanged =			0x000D,
		GNRL_Event_LicenseExpiration =			0x000E,
		GNRL_Event_Error =						0x000F,
		GNRL_Event_InternalError =				0x0010,
		GNRL_Event_BasesExpired =				0x0011,
		GNRL_Event_NodeWasRebooted =			0x0012,
		GNRL_Event_FullscanNotification =		0x0013,
		GNRL_Event_ApplicationWasRestarted =	0x0014,
		GNRL_Event_FullScanCompleted =			0x0015,

		GNRL_Event_AttackDetected =				0x0016,
		GNRL_Event_MacroBlocked =				0x0017,
		GNRL_Event_MacroAllowed =				0x0018,

		GNRL_Event_TaskStatePending =			0x0100,
		GNRL_Event_TaskStateScheduled =			0x0101,
		GNRL_Event_TaskStateRunning =			0x0102,
		GNRL_Event_TaskStateCompleted =			0x0103,
		GNRL_Event_TaskStateCompleted_Warning = 0x0104,
		GNRL_Event_TaskStateFailed =			0x0105
	};
}

/*! ��������� c_er_par1..c_er_par9 ��� ��������� ����� �������.
    UID - ���������� �������������, ����������� ��������� ����� �����
            ������������ ����������� ������� � ��������� ��� ���������.
    �������
        GNRL_EV_OBJECT_CURED
        GNRL_EV_OBJECT_DELETED
        GNRL_EV_PASSWD_ARCHIVE_FOUND
        GNRL_EV_OBJECT_QUARANTINED
        GNRL_EV_OBJECT_NOTCURED
    ���������
        GNRL_EA_PARAM_2 "��� �������"
        GNRL_EA_PARAM_6 UID

    �������
        GNRL_EV_SUSPICIOUS_OBJECT_FOUND
        GNRL_EV_VIRUS_FOUND

    ���������
    GNRL_EA_PARAM_2 "��� �������"
    GNRL_EA_PARAM_5 "��� ������"
    GNRL_EA_PARAM_6 UID

    �������
        GNRL_EV_VIRUS_FOUND

	���������
    GNRL_EA_PARAM_7 - ������������
    GNRL_EA_PARAM_8 - ��� ��������� (EDetectionType) � ���� ���������� �������������, ��������, L"61"


    �������
        GNRL_EV_ATTACK_DETECTED

	���������
    GNRL_EA_PARAM_1 - "��� �����"
    GNRL_EA_PARAM_2 - ��������
    GNRL_EA_PARAM_3 - IP-����� (��� ����������� ������� �����)  � ���� ���������� �������������, ��������, L"2886729929"
	GNRL_EA_PARAM_4 - ����

    ������ ��������� ���� ���������� c_er_par1..c_er_par9, ��� (�� ������
    GNRL_EV_*) ������� ������ �� ����� ��������� ��������� ��������:
        KLEVP::c_er_locid (INT_T)- ������������� ��������� ������ --
                ��� ����������� ��������
        KLEVP::c_er_par1...c_er_par9 (STRING_T) - ��������� ���������
                ������ c_er_locid (������)
        KLEVP::c_er_severity (INT_T) - ��������, ���� ��
                �������� KLEVP_EVENT_SEVERITY_*:
                    KLEVP_EVENT_SEVERITY_INFO,
                    KLEVP_EVENT_SEVERITY_WARNING,
                    KLEVP_EVENT_SEVERITY_ERROR,
                    KLEVP_EVENT_SEVERITY_CRITICAL.
        KLEVP::c_er_task_display_name (STRING_T) -
                ������������ ��� ������, � ���������� ������
                ������� ���� ������������ �������.
        KLEVP::c_er_descr (STRING_T) - �������� ������� (�� ����
                ��������� ������ � �������������� c_er_par1...c_er_par9).
        KLEVP::c_er_event_type_display_name (STRING_T)
                ������������� ��� ���� �������.
*/

#endif //__KLEVP_GENERAL_H__DA8BB648_DA39_4de6_A5B5_992918B14BC4
