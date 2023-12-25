#ifndef __USERSETTINGS_SCANNERS_H__
#define __USERSETTINGS_SCANNERS_H__

#include "DEFS.H"
#include "BaseMarshal.h"

#pragma warning(disable : 4251) // 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable : 4275) // non - DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#pragma warning(disable : 4786) // 'identifier' : identifier was truncated to 'number' characters in the debug information

//! ���� �������� ������������.
enum AVP_OT
{
	AVP_OT_MYCOMPUTER	= 1,
	AVP_OT_DRIVE		= 2,
	AVP_OT_FOLDER		= 3,
	AVP_OT_FILE			= 4,
	AVP_OT_MAIL			= 5,
	AVP_OT_REMOVABLE	= 6,
	AVP_OT_STARTUP		= 7,
	AVP_OT_QUARANTINED_SCAN_AND_CURE = 8,
	AVP_OT_QUARANTINED_SCAN_ONLY = 9,
	AVP_OT_MEMORY_WITHOUT_BUDDIES = 10,
	AVP_OT_DIRECT		= 11,
	AVP_OT_MEMORY		= 12,
	AVP_OT_HARDDRIVES	= 13,
	AVP_OT_BOOT_SECTORS = 14,
	AVP_OT_BOOTCURE_RESULT = 15,
	AVP_OT_BOOT_SECTORS_FIXED = 16,
	AVP_OT_BOOT_SECTORS_REMOVABLE = 17,
	AVP_OT_NETDRIVES = 18,
	AVP_OT_ALL_QUARANTINE = 19,
	
	
	AVP_OT_FAKE			= 255,
};

//! ���� ������������.
enum EScanType
{
	eScanType_All			= 0x1,	//!< ����������� ��� �����.
	eScanType_Infectable	= 0x2,	//!< ����������� ��� �����, ������� ����� ���� ��������.
	eScanType_InfectableExt	= 0x3,	//!< ����������� ��� ����� � �����������, ������� ����� ���� ��������.
};
IMPLEMENT_MARSHAL_ENUM(EScanType);

//! ���� ������ iChecker.
enum EICheckerType
{
	eICheckerType_Off		= 0x1,	//!< iChecker ��������.
	eICheckerType_ShortQ	= 0x2,	//!< iChecker � ������ Short Quarantine.
	eICheckerType_LongQ		= 0x3,	//!< iChecker � ������ Long Quarantine.
};
IMPLEMENT_MARSHAL_ENUM(EICheckerType);

//========================================================================================
namespace Private
{
	struct CCIFACEEXPORT CExcludedProcessObject_v1 : public CCBaseMarshal<PID_USER_SETTINGS_EXCLUDED_PROCESS_OBJECT>
	{
		CExcludedProcessObject_v1()
		{
			memset(m_ProcessHash, 0, sizeof(m_ProcessHash));
		}

		std::wstring m_ProcessName;			//!< ��� ����� ��������.
		std::wstring m_ProcessDir;			//!< ����� ��������. ����� �������� �����.
		std::wstring m_OriginalProcessPath;	//!< ���� � �����, ��� �������� �������� ���.
		unsigned char m_ProcessHash[16];

		bool operator==(const CExcludedProcessObject_v1 &that) const
		{
			return m_ProcessName == that.m_ProcessName &&
					m_ProcessDir == that.m_ProcessDir &&
					m_OriginalProcessPath == that.m_OriginalProcessPath &&
					memcmp(m_ProcessHash, that.m_ProcessHash, 16) == 0;
		}
		bool operator!=(const CExcludedProcessObject_v1 &that) const
		{
			return !operator==(that);
		}

		PoliType &MarshalImpl(PoliType &pt)
		{
			return BaseMarshal::MarshalImpl(pt) 
					<< m_ProcessName
					<< m_ProcessDir
					<< m_OriginalProcessPath
					<< SIMPLE_DATA_SER(m_ProcessHash);
		}
	};
}

typedef DeclareExternalName<Private::CExcludedProcessObject_v1> CExcludedProcessObject;

//========================================================================================
namespace Private
{
	struct CCIFACEEXPORT CExcludedProcesses_v1 : public CCBaseMarshal<PID_USER_SETTINGS_EXCLUDED_PROCESSES>
	{
		std::vector<CExcludedProcessObject> m_Processes;

		bool operator==(const CExcludedProcesses_v1 &that) const
		{
			return m_Processes == that.m_Processes;
		}
		bool operator!=(const CExcludedProcesses_v1 &that) const
		{
			return !operator==(that);
		}

		PoliType &MarshalImpl(PoliType &pt)
		{
			return BaseMarshal::MarshalImpl(pt) << m_Processes;
		}
	};
}

typedef DeclareExternalName<Private::CExcludedProcesses_v1> CExcludedProcesses;

//========================================================================================
namespace Private
{
	//! �������������� ��������� On-Access Scanner ��� Personal Pro.
	struct CCIFACEEXPORT CUserSettingsOAS_v1: public CCBaseMarshal < PID_USER_SETTINGS_OAS >
	{
		EScanType		m_eScanType;		//!< ��� ������������.
		bool			m_bScanFixed;		//!< ���� ������������ ������� ������.
		bool			m_bScanRemovable;	//!< ���� ������������ ����������� ������.
		bool			m_bScanNetwork;		//!< ���� ������������ ������� ������.
		bool			m_bScanOle;			//!< ���� ������������ ��������� OLE-��������.
		bool			m_bScanPacked;		//!< ���� ������������ ����������� ��������.
		bool			m_bScanSfxArchived;	//!< ���� ������������ ��������������������� �������.
		EICheckerType	m_eUseIChecker;		//!< ���� ������������� ���������� iChecker.
		EICheckerType	m_eUseIStreams;		//!< ���� ������������� ���������� iStreams.
		
		
		PoliType & MarshalImpl ( PoliType & pt )
		{
			return BaseMarshal::MarshalImpl ( pt ) << m_eScanType << m_bScanFixed << m_bScanRemovable
				<< m_bScanNetwork << m_bScanOle << m_bScanPacked << m_bScanSfxArchived << m_eUseIChecker
				<< m_eUseIStreams;
		}
	};
	struct CCIFACEEXPORT CUserSettingsOAS_v2: public DeclareNextVersion<CUserSettingsOAS_v1>
	{
		enum ERTPUserAction
		{
			eUserAction_DenyAccessAskUser		=	0x1,
			eUserAction_DenyAccessDoNotAskUser	=	0x2,
			eUserAction_Recommended			    =	0x3,
			eUserAction_AutoDel				    =	0x4,
			eUserAction_CureDeleteIfNotCured	=	0x5,
			eUserAction_Quarantine				=	0x6  // for suspics only
		};

		bool			m_bScanBootSectors;		//!< ���� ������������ boot ��������.
		bool			m_bScanTimeLimit;		//!< ���� ����������� ������� ������������.
		int				m_nMaxScanTimeSec;		//!< ������������ ����� ������������ � ��������.
		ERTPUserAction  m_eUserAction;			//!< �������� ��� ����������� �������.
		ERTPUserAction	m_eUserSuspiciousAction;//!< �������� ��� ��������������� ��������� (PPro only).

		PoliType & MarshalImpl ( PoliType & pt )
		{
			return BaseMarshal::MarshalImpl ( pt ) << m_bScanBootSectors << m_bScanTimeLimit
				<< m_nMaxScanTimeSec << SIMPLE_DATA_SER(m_eUserAction) << SIMPLE_DATA_SER(m_eUserSuspiciousAction);
		}
	};
	struct CCIFACEEXPORT CUserSettingsOAS_v3 : public DeclareNextVersion<CUserSettingsOAS_v2>
	{
		CUserSettingsOAS_v3() :
			m_bEnableExcludedProcesses(true)
		{
		}

		bool m_bEnableExcludedProcesses;		// ������������ ������ ����������� ���������
		CExcludedProcesses m_ExcludedProcesses; // ����������� ��������
												// ������ �� ������ �� �� �������, �� �� ���������

		PoliType &MarshalImpl(PoliType &pt)
		{
			return BaseMarshal::MarshalImpl(pt) << m_bEnableExcludedProcesses << m_ExcludedProcesses;
		}
				
	};	
} // namespace Private

struct CCIFACEEXPORT CUserSettingsOAS : public DeclareExternalName<Private::CUserSettingsOAS_v3>
{
	CUserSettingsOAS ();

	bool operator == (const CUserSettingsOAS& Settings) const;
	
	bool IsDefault() const;

	void PPro_SetMaximalProtection();
	void PPro_SetRecommended();
	void PPro_SetMaximalSpeed();

	bool PPro_IsMaximalProtection() const;
	bool PPro_IsRecommended() const;
	bool PPro_IsMaximalSpeed() const;
};


namespace Private
{

class CCIFACEEXPORT CUserSettingsODS_v1 : public CCBaseMarshal<PID_USER_SETTINGS_ODS>
{
public:
	enum EODSUserAction
    {
		eUserAction_Ask						= 0x2,
		eUserAction_AutoRec					= 0x3,
		eUserAction_AutoDel					= 0x4,
		eUserAction_ReportOnly				= 0x5,
		eUserAction_TIF						= 0x6,
		eUserAction_CureDeleteIfNotCured	= 0x7,
		eUserAction_Quarantine				= 0x8  // for suspics only
	};
	
	//! ������� ������������.
	enum EODSScanLevel
	{
		eScanLevel_Max          = 0x1,
		eScanLevel_Rec          = 0x2,
		eScanLevel_Min          = 0x3,
		eScanLevel_Custom       = 0x4, //!< ������� ��� Personal Pro.

		eScanLevel_Last
	};
	
	
	EODSUserAction                  m_UserAction;
	//! � Personal Pro ������ ������ �� ��������� ������ � GUI.	������������ �������������� � ������������ � �������.
	EODSScanLevel                   m_ScanLevel;
	bool                            m_blScanSectors;
	bool                            m_blScanMemory;
	bool                            m_blScanPacked;
	bool                            m_blScanArchives;
	bool                            m_blScanStartup;
	bool                            m_blScanMail;
	bool					        m_blExcludeEnable;
	std::vector < std::wstring >    m_ExcludeMaskDeprecated;
	bool							m_blOkInfoEventsOff;
    bool                            m_bDoNotAskPassword;
	
	virtual PoliType& MarshalImpl(PoliType& pt)
	{
		return BaseMarshal::MarshalImpl  (pt)<<SIMPLE_DATA_SER(m_UserAction)<<SIMPLE_DATA_SER(m_ScanLevel)<<m_blScanSectors<<\
			m_blScanMemory<<m_blScanPacked<<m_blScanArchives<<m_blScanStartup<<m_blScanMail<<m_blExcludeEnable<<m_ExcludeMaskDeprecated<<m_blOkInfoEventsOff << m_bDoNotAskPassword;
	}
	
};

// ��� ��� �� ����������� ����������, ��� ���� ����� �����...
class CCIFACEEXPORT CUserSettingsODS_v2 : public DeclareNextVersion<CUserSettingsODS_v1>
{
};	

class CCIFACEEXPORT CUserSettingsODS_v3 : public DeclareNextVersion<CUserSettingsODS_v2>
{
public:
	// ��������� Personal Pro
	EScanType		m_eScanType;	//!< ��� ������������.
	bool			m_bUseSizeLimit;	//!< ���� ����������� �� ������ ����������� ������.
	DWORD			m_dwSizeLimit;		//!< ����������� �� ������ ����������� ������ � ������.
	bool			m_bUseTimeLimit;	//!< ���� ����������� �� ����� ������������ �����.
	DWORD			m_dwTimeLimit;		//!< ����������� �� ����� ������������ ����� � ��������.
	bool			m_bScanSfxArchived;	//!< ���� ������������ ��������������������� �������.
	bool			m_bScanOle;			//!< ���� ������������ ��������� OLE-��������.
	bool			m_bScanNtfsStreams;	//!< ���� ������������ �������������� NTFS-�������.
	EICheckerType	m_eUseIChecker;		//!< ���� ������������� ���������� iChecker
	EICheckerType	m_eUseIStreams;		//!< ���� ������������� ���������� iStreams
	bool			m_bScanPlainMail;	//!< ���� ������������ �������� ������.
	bool			m_bScanMailDB;		//!< ���� ������������ �������� ���.

	virtual PoliType& MarshalImpl(PoliType& pt)
	{
		BaseMarshal::MarshalImpl (pt);
		return pt << m_eScanType
			<< m_bUseSizeLimit << m_dwSizeLimit << m_bUseTimeLimit << m_dwTimeLimit
			<< m_bScanSfxArchived << m_bScanOle << m_bScanNtfsStreams
			<< m_eUseIChecker << m_eUseIStreams
			<< m_bScanPlainMail << m_bScanMailDB;
	}
};

class CCIFACEEXPORT CUserSettingsODS_v4 : public DeclareNextVersion<CUserSettingsODS_v3>
{
public:
	EODSUserAction m_UserSuspiciousAction;	//!< �������� ��� �������������� ��������. (PPro only)
	
	virtual PoliType& MarshalImpl(PoliType& pt)
	{
		return BaseMarshal::MarshalImpl (pt) << SIMPLE_DATA_SER(m_UserSuspiciousAction);
	}
};

class CCIFACEEXPORT CUserSettingsODS_v5 : public DeclareNextVersion<CUserSettingsODS_v4>
{
public:
	bool	m_blScanSectorsOnFixedOnStartup;
	bool	m_blScanMemoryOnStartup;
	bool	m_blScanStartupOnStartup;
	bool	m_blScanSectorsOnRemovableOnStartup;
	
	virtual PoliType& MarshalImpl(PoliType& pt)
	{
		return BaseMarshal::MarshalImpl (pt) 
				<< m_blScanSectorsOnFixedOnStartup
				<< m_blScanMemoryOnStartup
				<< m_blScanStartupOnStartup
				<< m_blScanSectorsOnRemovableOnStartup;
	}
};

}

class CCIFACEEXPORT CUserSettingsODS: public DeclareExternalName<Private::CUserSettingsODS_v5>
{
public:
	CUserSettingsODS ();

	void SetRecommended ();
	bool IsExclude () const;
	bool IsDefault() const;

	void PPro_SetMaximalProtection();
	void PPro_SetRecommended();
	void PPro_SetMaximalSpeed();
	
	bool PPro_IsMaximalProtection() const;
	bool PPro_IsRecommended() const;
	bool PPro_IsMaximalSpeed() const;
};

namespace Private {

//! �������������� ��������� Mail Checker ��� Personal Pro.
struct CCIFACEEXPORT CUserSettingsMC_v1: public CCBaseMarshal < PID_USER_SETTINGS_MC >
{
	//! ���� �������� ��� ����������� ��������� ���������.
	enum EMCInfectedAction
	{
		eMCInfectedAction_Disinfect = 0x1,	//!< ������, ������� ���� �� �������.
		eMCInfectedAction_Delete = 0x2,		//!< �������.
	};
	
	//! ���� �������� ��� ����������� ��������� ���������.
	enum EMCSuspiciousAction
	{
		eMCSuspiciousAction_Quarantine = 0x1,	//!< �������� � ��������.
		eMCSuspiciousAction_Delete = 0x2,		//!< �������.
	};

	EScanType			m_eScanType;		//!< ��� ������������.
	EMCInfectedAction	m_eInfectedMailAction;	//!< �������� �� ���������� �������.
	EMCSuspiciousAction	m_eSuspiciousMailAction;	//!< �������� �� ������������� �������.
	bool	m_bScanOutlookIncoming;	//!< ���� ������������ �������� ����� Outlook.
	bool	m_bScanOutlookOutgoing;	//!< ���� ������������ ��������� ����� Outlook.
	bool	m_bScanPop3;			//!< ���� ������������ POP3-�������.
	DWORD	m_dwPop3Port;			//!< ���� POP3.
	bool	m_bScanSmtp;			//!< ���� ������������ SMTP-�������.
	DWORD	m_dwSmtpPort;			//!< ���� SMTP.
	bool	m_bScanArchives;		//!< ���� ������������ �������.
	bool	m_bLimitArchiveSize;	//!< ���� ����������� ������� ����������� �������.
	DWORD	m_nMaxArchiveSizeMb;	//!< ������������ ������ ������������ ������ � ����������.
	bool	m_bScanTimeLimit;		//!< ���� ����������� ������� ������������.
	int		m_nMaxScanTimeSec;		//!< ������������ ����� ������������ � ��������.
	bool	m_bScanAttachedMailBases;//!< ���� ������������ ������������ ������ �������� ��������.
	bool	m_bUseIChecker;			//!< ���� ������������� IChecker.

	PoliType & MarshalImpl ( PoliType & pt )
    {
        return BaseMarshal::MarshalImpl ( pt ) << m_eScanType
			<< SIMPLE_DATA_SER(m_eInfectedMailAction) << SIMPLE_DATA_SER(m_eSuspiciousMailAction)
			<< m_bScanOutlookIncoming << m_bScanOutlookOutgoing << m_bScanPop3 << m_dwPop3Port
			<< m_bScanSmtp << m_dwSmtpPort << m_bScanArchives << m_bLimitArchiveSize
			<< m_nMaxArchiveSizeMb << m_bScanTimeLimit << m_nMaxScanTimeSec << m_bScanAttachedMailBases
			<< m_bUseIChecker;
	}
};
}

struct CCIFACEEXPORT CUserSettingsMC: public DeclareExternalName<Private::CUserSettingsMC_v1>
{
	CUserSettingsMC();
	bool operator == (const CUserSettingsMC& Settings) const;
	
	bool IsDefault() const
	{
		return *this == CUserSettingsMC();
	}

	void PPro_SetMaximalProtection();
	void PPro_SetRecommended();
	void PPro_SetMaximalSpeed();
	
	bool PPro_IsMaximalProtection() const;
	bool PPro_IsRecommended() const;
	bool PPro_IsMaximalSpeed() const;
};

namespace Private
{
	struct CCIFACEEXPORT CCODSScanObject_v1 : public CCBaseMarshal<PID_USER_SETTINGS_SCAN_OBJECT>
	{
		DWORD m_Type;
		std::wstring m_Name;
		
		virtual PoliType& MarshalImpl(PoliType& pt)
		{
			return BaseMarshal::MarshalImpl  (pt)<<m_Type<<m_Name;
		}
	};
	
	struct CCIFACEEXPORT CCODSScanObject_v2 : public DeclareNextVersion<CCODSScanObject_v1>
	{
		int m_Action;
		std::vector < unsigned char > m_DirectScanData; //m_Type = AVP_OT_DIRECT;
		
		virtual PoliType& MarshalImpl(PoliType& pt)
		{
			return BaseMarshal::MarshalImpl  (pt)<<m_Action<<m_DirectScanData;
		}
	};
	
	struct CCIFACEEXPORT CCODSScanObject_v3 : public DeclareNextVersion<CCODSScanObject_v2>
	{
		int m_ActionOnWarning;
		DWORD m_dwObjectUID;

		virtual PoliType& MarshalImpl(PoliType& pt)
		{
			return BaseMarshal::MarshalImpl  (pt)<<m_ActionOnWarning<<m_dwObjectUID;
		}
	};

	struct CCIFACEEXPORT CCODSScanObject_v4 : public DeclareNextVersion<CCODSScanObject_v3>
	{
		// ���� �������, �� � ������ ������������ �� m_Name, � m_ReportName (������� ��������� ������������ �����)
		std::wstring m_ReportName;
		
		virtual PoliType& MarshalImpl(PoliType& pt)
		{
			return BaseMarshal::MarshalImpl  (pt)<<m_ReportName;
		}
	};
}

typedef DeclareExternalName<Private::CCODSScanObject_v4> CCODSScanObject_Ser;

struct CCIFACEEXPORT CCODSScanObject : public CCODSScanObject_Ser
{
	CCODSScanObject ()
	{
	}
	
	CCODSScanObject ( DWORD Type, const std::wstring & Name = L"" )
	{
		m_Type = Type;
		m_Name = Name;
	}
	
	CCODSScanObject (int type, unsigned char * pDirectScanData, size_t nDataSize, int action )
	{
		m_Type = type;
		m_Action = action;
		if (nDataSize && pDirectScanData)
			m_DirectScanData.assign (pDirectScanData, pDirectScanData + nDataSize);
	}
	
	
};

namespace Private
{
	struct CCIFACEEXPORT CCODSScanObjects_v1 : public CCBaseMarshal<PID_USER_SETTINGS_SCAN_OBJECTS>
	{
		CCODSScanObjects_v1 ()
		{
		}
		
		CCODSScanObjects_v1 ( const CCODSScanObjects_v1 & That )
		{
			m_List = That.m_List;
		}
		
		std::list < CCODSScanObject > m_List;
		
		virtual PoliType & MarshalImpl(PoliType& pt)
		{
			return BaseMarshal::MarshalImpl  (pt)<<m_List;
		}
	};
	
}

typedef DeclareExternalName<Private::CCODSScanObjects_v1> CCODSScanObjects;

//////////////////////////////////////////////////////////////////////////

//FW
namespace Private
{
	struct CCIFACEEXPORT CUserSettingsFirewall_v1 : public CCBaseMarshal<PID_USER_SETTINGS_FIREWALL>
	{
		CUserSettingsFirewall_v1() :
			m_WorkingMode(wmAllowNotFiltered)
		{
		}

		enum WorkingMode
		{
			wmBlockAll,
			wmRejectNotFiltered,
			wmAskUser,
			wmAllowNotFiltered,
			wmAllowAll
		};
		
		WorkingMode m_WorkingMode;
		std::vector<BYTE> m_PacketRulesBlob;
		std::vector<BYTE> m_ApplicationRulesBlob;

		virtual PoliType & MarshalImpl(PoliType& pt)
		{
			return BaseMarshal::MarshalImpl(pt) 
						<< SIMPLE_DATA_SER(m_WorkingMode)
						<< m_PacketRulesBlob
						<< m_ApplicationRulesBlob;
		}
	};
}

typedef DeclareExternalName<Private::CUserSettingsFirewall_v1> CUserSettingsFirewall;

#endif // __USERSETTINGS_SCANNERS_H__