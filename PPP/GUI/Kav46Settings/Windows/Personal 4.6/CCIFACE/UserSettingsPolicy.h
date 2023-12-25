#ifndef __USERSETTINGS_POLICY_H__
#define __USERSETTINGS_POLICY_H__

namespace Private
{
	//! ����� ������ ��� ��������� �������� �������� (��������/���������)
	struct CCIFACEEXPORT CMandatoryFlagSetStorage
	{
		CMandatoryFlagSetStorage()
		{
			memset(this, 0, sizeof(*this));
		}

		// CAVSettings
		bool m_bAVDBType;						// m_AVSettings.m_AVDBType

		// CUserSettingsGUI
		bool m_bTechnicalEmail;					// m_GUISettings.m_TechnicalEmail
		bool m_bUseMinBatteryChargePercent;		// m_GUISettings.m_bUseMinBatteryChargePercent
		bool m_bMinBatteryChargePercent;		// m_GUISettings.m_nMinBatteryChargePercent
		bool m_bDisableFullscanMailScanning;	// m_GUISettings.m_bDisableFullscanMailScanning
		bool m_bDoNotStartProduct;				// m_GUISettings.m_bDoNotStartProduct
		bool m_bOkInfoEventsOff;				// m_GUISettings.m_bOkInfoEventsOff
		bool m_bInteractWithUser;				// m_GUISettings.m_bInteractWithUser
		bool m_bIconAnimation;					// m_GUISettings.m_bIconAnimation
		bool m_bDoNotShowBalloons;				// m_GUISettings.m_bDoNotShowBalloons
		bool m_bStartGUIOnStart;				// m_GUISettings.m_bStartGUIOnStart
		bool m_bNotifyAVBasesExpiredPeriod1;	// m_GUISettings.m_nNotifyAVBasesExpiredPeriod1
		bool m_bNotifyAVBasesExpiredPeriod2;	// m_GUISettings.m_nNotifyAVBasesExpiredPeriod2
		bool m_bNotifyFullscanStatusPeriod1;	// m_GUISettings.m_nNotifyFullscanStatusPeriod1
		bool m_bNotifyFullscanStatusPeriod2;	// m_GUISettings.m_nNotifyFullscanStatusPeriod2
		bool m_bRestrictReportLife;				// m_GUISettings.m_bRestrictReportLife
		bool m_bPasswordHash;					// m_GUISettings.m_PasswordHash
//����� ��������:
		bool m_bReportOld;						// m_GUISettings.m_nReportOld
		bool m_bUninstallPasswordHash;			// m_GUISettings.m_UninstallPasswordHash
		bool m_bUseMaxSystemBusyLevel;			// m_GUISettings.m_bUseMaxSystemBusyLevel
		bool m_bMaxSystemBusyLevel;				// m_GUISettings.m_nMaxSystemBusyLevel
		bool m_bUseWatchDog;					// m_GUISettings.m_bUseWatchDog
		bool m_bSoundOff;						// m_GUISettings.m_bSoundOff
		bool m_bShowAdminTasks;					// m_GUISettings.m_bShowAdminTasks

		// CUserSettingsRTP
		bool m_bEnableExcludedProcesses;		// m_RTPSettings.m_OAS.m_bEnableExcludedProcesses
		bool m_bExcludedProcesses;				// m_RTPSettings.m_OAS.m_ExcludedProcesses

		// CQuarantineSettings
		bool m_bAutoScan;						// m_QuarantineSettings.m_bAutoScan
		bool m_bBMaxSizeOn;						// CBackupSettings.m_bMaxSizeOn
		bool m_bBMaxTimeOn;						// CBackupSettings.m_bMaxTimeOn
		bool m_bBAskFolderConfirmation;			// CBackupSettings.m_Restore.m_bAskFolderConfirmation
		bool m_bBMaxSize;						// CBackupSettings.m_nMaxSize
		bool m_bBOverflowAction;				// CBackupSettings.m_eOverflowAction
		bool m_bBFilesPath;						// CBackupSettings.m_FilesPath
		bool m_bBRestoreToRestoreFolder;		// CBackupSettings.m_Restore.m_bRestoreToRestoreFolder
		bool m_bBRestoreFolder;					// CBackupSettings.m_Restore.m_sRestoreFolder
		bool m_bBMaxTime;						// CBackupSettings.m_nMaxTime
		bool m_bQMaxSizeOn;						// CQuarantineSettings.m_bMaxSizeOn
		bool m_bQMaxTimeOn;						// CQuarantineSettings.m_bMaxTimeOn
		bool m_bQAskFolderConfirmation;			// CQuarantineSettings.m_Restore.m_bAskFolderConfirmation
		bool m_bQMaxSize;						// CQuarantineSettings.m_nMaxSize
		bool m_bQOverflowAction;				// CQuarantineSettings.m_eOverflowAction
		bool m_bQFilesPath;						// CQuarantineSettings.m_FilesPath
		bool m_bQRestoreToRestoreFolder;		// CQuarantineSettings.m_Restore.m_bRestoreToRestoreFolder
		bool m_bQRestoreFolder;					// CQuarantineSettings.m_Restore.m_sRestoreFolder
		bool m_bQMaxTime;						// CQuarantineSettings.m_nMaxTime

		// predefined tasks
		bool m_bAllowLaunchingPredefinedTasks;	// predefined tasks

		// riskware list
		bool m_bRiskwareList;					// ������ Riskware
		
		// Mail checker
		bool m_bMCIncomingMail;					// �������� �����
		bool m_bMCOutgoingMail;					// ��������� �����
		bool m_bMCScanObjects;					// ��� �������� �������� � excludes
		bool m_bMCActions;						// �������� ��� ����������� � ���������������
		bool m_bMCAdditional;					// ��������� ���������

		// OAS
		bool m_bOASScanScope;					// ��� ��������� (hard drives, rem. drives, net drives etc.)
		bool m_bOASScanObjects;					// ��� �������� �������� � excludes
		bool m_bOASActions;						// �������� ��� ����������� � ���������������
		bool m_bOASScanObjectsAux;				// ��� ��������� 2 (packed, self-extracted, OLE)
		bool m_bOASUseRiskwareList;				// ������������ �� ������ riskware
		bool m_bOASRestrictions;				// ����������� �� �����
		bool m_bOASICheckerIStreams;			// ������������� IChecer, IStreams

		// OG
		bool m_bOGActions;						// ��������

		// SC
		bool m_bSCActions;						// ��������
		
		// CKAH
		bool m_bCKAHSettings;					// ��� ��������� CKAH

		// Updater
		bool m_bUpdPatches;						// �����
		bool m_bUpdUpdateSources;				// ��������� ����������
		bool m_bRetranslation;					// ������������

		// ODS
		bool m_bODSScanScope;					// ��� ���������
		bool m_bODSScanObjects;					// ��� �������� �������� � excludes
		bool m_bODSActions;						// �������� ��� ����������� � ���������������
		bool m_bODSScanObjectsAux;				// ��� ��������� 2 (packed, self-extracted, OLE)
		bool m_bODSUseRiskwareList;				// ������������ �� ������ riskware
		bool m_bODSRestrictions;				// ����������� �� ����� � ������
		bool m_bODSICheckerIStreams;			// ������������� IChecer, IStreams
		
		bool m_bReserved[32];					// RFU

		bool operator==(const CMandatoryFlagSetStorage &that) const
		{
			return memcmp(this, &that, sizeof(*this)) == 0;
		}

		PoliType &MarshalImpl(PoliType &pt)
		{
			return pt
				<< m_bAVDBType
				<< m_bTechnicalEmail
				<< m_bDisableFullscanMailScanning
				<< m_bDoNotStartProduct
				<< m_bEnableExcludedProcesses
				<< m_bOkInfoEventsOff
				<< m_bInteractWithUser
				<< m_bIconAnimation
				<< m_bDoNotShowBalloons
				<< m_bStartGUIOnStart
				<< m_bNotifyAVBasesExpiredPeriod1
				<< m_bNotifyAVBasesExpiredPeriod2
				<< m_bNotifyFullscanStatusPeriod1
				<< m_bNotifyFullscanStatusPeriod2
				<< m_bRestrictReportLife
				<< m_bReportOld
				<< m_bExcludedProcesses
				<< m_bUninstallPasswordHash
				<< m_bAutoScan
				<< m_bBMaxSizeOn
				<< m_bBMaxTimeOn
				<< m_bBAskFolderConfirmation
				<< m_bBMaxSize
				<< m_bBOverflowAction
				<< m_bBFilesPath
				<< m_bBRestoreToRestoreFolder
				<< m_bBRestoreFolder
				<< m_bBMaxTime
				<< m_bQMaxSizeOn
				<< m_bQMaxTimeOn
				<< m_bQAskFolderConfirmation
				<< m_bQMaxSize
				<< m_bQOverflowAction
				<< m_bQFilesPath
				<< m_bQRestoreToRestoreFolder
				<< m_bQRestoreFolder
				<< m_bQMaxTime
				<< m_bAllowLaunchingPredefinedTasks
				<< m_bRiskwareList
				<< m_bMCIncomingMail
				<< m_bMCOutgoingMail
				<< m_bMCScanObjects
				<< m_bMCActions
				<< m_bMCAdditional
				<< m_bOASScanScope
				<< m_bOASScanObjects
				<< m_bOASActions
				<< m_bOASScanObjectsAux
				<< m_bOASUseRiskwareList
				<< m_bOASRestrictions
				<< m_bOASICheckerIStreams
				<< m_bOGActions
				<< m_bSCActions
				<< m_bUpdPatches
				<< m_bUpdUpdateSources
				<< m_bRetranslation
				<< m_bODSScanScope
				<< m_bODSScanObjects
				<< m_bODSActions
				<< m_bODSScanObjectsAux
				<< m_bODSUseRiskwareList
				<< m_bODSRestrictions
				<< m_bODSICheckerIStreams
				<< m_bUseMinBatteryChargePercent
				<< m_bMinBatteryChargePercent
				<< m_bUseMaxSystemBusyLevel
				<< m_bMaxSystemBusyLevel
				<< m_bUseWatchDog
				<< m_bSoundOff
				<< m_bShowAdminTasks
				<< m_bPasswordHash
				<< m_bCKAHSettings
				<< SIMPLE_DATA_SER(m_bReserved)
				;
		}
	};

	struct CCIFACEEXPORT CMandatoryFlagSet_v1 : 
			public CCBaseMarshal<PID_USER_SETTINGS_MANDATORY_FLAG_SET>, public CMandatoryFlagSetStorage
	{
		bool operator==(const CMandatoryFlagSet_v1 &that) const
		{
			return CMandatoryFlagSetStorage::operator==(that);
		}

        virtual PoliType &MarshalImpl(PoliType &pt)
		{
			BaseMarshal::MarshalImpl(pt);
			CMandatoryFlagSetStorage::MarshalImpl(pt);
			return pt;
		};
	};
}

typedef DeclareExternalName<Private::CMandatoryFlagSet_v1> CMandatoryFlagSet;

//////////////////////////////////////////////////////////////////////
// CPolicy
//////////////////////////////////////////////////////////////////////
class CCIFACEEXPORT CPolicy : public CBase
{
public:
	CUserSettings m_Settings;					// ��������
	CMandatoryFlagSet m_Flags;					// mandatory �����

	CPolicy();

	virtual int Store(LPPOLICY* ppPolicy) const;
	virtual int Load(LPPOLICY pPolicy);
};

#endif // __USERSETTINGS_POLICY_H__
