#ifndef __S_MC_H
#define __S_MC_H

#include <AV/structs/s_avs.h>
#include <Mail/iface/i_mailtask.h>
#include <Mail/plugin/p_mctask.h>
#include <ProductCore/structs/s_taskmanager.h>

//////////////////////////////////////////////////////////////////////////
//! �������� ���������, ���������� �� ������ (������� �����)
enum MailCheckerVerdicts_t
{
	mcv_MESSAGE_CHECKED				=	0x00000001 ,	// ��������� ���������
	mcv_MESSAGE_CHANGED				=	0x00000002 ,	// ��������� ���� �������� ��� ��������
	mcv_MESSAGE_AV_INFECTED			=	0x00000004 ,	// ���������: ��������� ������������
	mcv_MESSAGE_AV_WARNING			=	0x00000008 ,	// ���������: ��������� ������������� �� �����
	mcv_MESSAGE_AV_DISINFECTED		=	0x00000010 ,	// ���������: ��������� ��������
	mcv_MESSAGE_AV_SOME_SKIPPED		=	0x00000020 ,	// ���������: ��������� ������� � ������ �� ���� ���������
	mcv_MESSAGE_AS_SPAM				=	0x00000040 ,	// ��������: � ��������� ���������� ����
	mcv_MESSAGE_AS_PROBABLE_SPAM	=	0x00000080 ,	// ��������: ��������� ������������� �� ����
	mcv_MESSAGE_DELETED				=	0x00000100 ,	// ��������� ������� (IO ��� �������)
};
//! �������� ���������, ���������� �� ������ (������� �����)
//////////////////////////////////////////////////////////////////////////

//! �������� ����� ���������� �������� �����
enum MailCheckerDirectionTypes
{
	maildt_All = 0,
	maildt_Incoming,
	maildt_Outgoing
};

//-----------------------------------------------------------------------------
// cMCSettings structure

struct cMCSettings : public cProtectionSettings
{
	cMCSettings():
		cProtectionSettings(),
		m_bCheckTrafficMonitorMessages(cTRUE),
		m_bCheckExternalPluginMessages(cTRUE),
		m_bCheckIncomingMessagesOnly(cFALSE),
		m_bCheckMassMailer(cTRUE),
		m_dwMassMailerCount(5),
		m_dwMassMailerTimeout(5)
		{};

	DECLARE_IID_SETTINGS( cMCSettings, cProtectionSettings, PID_MCTASK );

	tBOOL		m_bCheckTrafficMonitorMessages;
	tBOOL		m_bCheckExternalPluginMessages;
	tBOOL		m_bCheckIncomingMessagesOnly;

	tBOOL		m_bCheckMassMailer;		//!< �������� ������ ����-��������
	tDWORD		m_dwMassMailerCount;	//!< ������������ ���������� ����� �� ��������� ���� m_dwMassMailerTimeout
	tDWORD		m_dwMassMailerTimeout;	//!< ��������� ���� ��� ������� ����-�������, �������
};

IMPLEMENT_SERIALIZABLE_BEGIN( cMCSettings, 0 )
	SER_BASE( cProtectionSettings,  0 )
	SER_VALUE( m_bCheckTrafficMonitorMessages, tid_BOOL,   "CheckTrafficMonitorMessages"  )
	SER_VALUE( m_bCheckExternalPluginMessages, tid_BOOL,   "CheckExternalPluginMessages"  )
	SER_VALUE( m_bCheckIncomingMessagesOnly,   tid_BOOL,   "CheckIncomingMessagesOnly"  )
	SER_VALUE( m_bCheckMassMailer,             tid_BOOL,   "CheckMassMailer" )
	SER_VALUE( m_dwMassMailerCount,            tid_DWORD,  "MassMailerCount" )
	SER_VALUE( m_dwMassMailerTimeout,          tid_DWORD,  "MassMailerTimeout" )
IMPLEMENT_SERIALIZABLE_END()


//struct cMCSettings : public cProtectionSettings
//{
//	cMCSettings():
//		cProtectionSettings(),
//		m_eDirectionType(maildt_All),
//		m_dwSMTPPort(25),
//		m_dwPOP3Port(110),
//		m_bCheckSMTPTraffic(cTRUE),
//		m_bCheckPOP3Traffic(cTRUE),
//		m_bCheckOutlookTraffic(cTRUE),
//		m_ulSettingsVersion(0)
//		{}
//
//	DECLARE_IID_SETTINGS( cMCSettings, cProtectionSettings, PID_MCTASK );
//
//	MailCheckerDirectionTypes m_eDirectionType;
//	tWORD	                  m_dwSMTPPort;
//	tWORD	                  m_dwPOP3Port;
//	tBOOL	                  m_bCheckSMTPTraffic;
//	tBOOL	                  m_bCheckPOP3Traffic;
//	tBOOL	                  m_bCheckOutlookTraffic;
//	tULONG	                  m_ulSettingsVersion;
//};
//
//IMPLEMENT_SERIALIZABLE_BEGIN( cMCSettings, 0 )
//	SER_BASE( cProtectionSettings,  0 )
//	SER_VALUE( m_eDirectionType,       tid_WORD,  "DirectionType" )
//	SER_VALUE( m_dwSMTPPort,           tid_WORD,  "SMTPPort" )
//	SER_VALUE( m_dwPOP3Port,           tid_WORD,  "POP3Port" )
//	SER_VALUE( m_bCheckSMTPTraffic,    tid_BOOL,  "CheckSMTPTraffic" )
//	SER_VALUE( m_bCheckPOP3Traffic,    tid_BOOL,  "CheckPOP3Traffic" )
//	SER_VALUE( m_bCheckOutlookTraffic, tid_BOOL,  "CheckOutlookTraffic" )
//	SER_VALUE( m_ulSettingsVersion,    tid_DWORD, "SettingsVersion" )
//IMPLEMENT_SERIALIZABLE_END()

//-----------------------------------------------------------------------------

//! �������� �������� ��������, ������������ ��� �������� ������
typedef enum
{
	mailpa_Pass = 0,
	mailpa_DeleteObject,
	mailpa_ChangeObjectToText
	// mailpa_Disinfect - �� ����, ��� ����� ����� ����� �������
}	tPrimaryAction;

typedef enum
{
	mcstruct_MAILFILTERRESULTACTIONS_SETTINGS = 1,
	mcstruct_MAILFILTER_SETTINGS		     ,
	mcstruct_MBL_SETTINGS                    ,
	mcstruct_MTM_SETTINGS                    ,
	mcstruct_MC_STATISTICS                   ,
	mcstruct_MC_PLUGINS                      ,
	mcstruct_MC_SETTINGS_VERSION             ,
	mcstruct_MC_PROCESS_PARAMS               ,
	mcstruct_MC_PluginSettings               ,
	mcstruct_LAST
} mcstruct_t;

//-----------------------------------------------------------------------------
// ������� � �������� ��������� ��������� ��������� (��� �������� ������� Process)
struct cMCProcessParams : public cSerializable
{
	cMCProcessParams():
		cSerializable(),
		p_dwTimeOut(-1),
		p_MailCheckerVerdicts(0),
		p_dwASReason(0)
		{}
			
	DECLARE_IID( cMCProcessParams, cSerializable, PID_MCTASK, mcstruct_MC_PROCESS_PARAMS );
		
	tDWORD p_dwTimeOut;				// [IN] �������
	tDWORD p_MailCheckerVerdicts;	// [OUT] MailCheckerVerdicts_t
	cStringObj p_szVirusName;       // [OUT] ��� ������, ���������� � ������
	tDWORD p_dwASReason;            // [OUT] ������� ��������� (asDetectReason_t)
};

IMPLEMENT_SERIALIZABLE_BEGIN( cMCProcessParams, 0 )
	SER_VALUE( p_dwTimeOut,           tid_DWORD,      "TimeOut" )
	SER_VALUE( p_MailCheckerVerdicts, tid_DWORD,      "MailCheckerVerdicts" )
	SER_VALUE( p_szVirusName,         tid_STRING_OBJ, "VirusName" )
	SER_VALUE( p_dwASReason,          tid_DWORD,      "ASReason"  )
IMPLEMENT_SERIALIZABLE_END()

//-----------------------------------------------------------------------------

struct cMCPluginSettings : public cSerializable
{
	cMCPluginSettings():
		m_bCheckOnDelivery(cTRUE),
		m_bCheckOnRead(cTRUE),
		m_bCheckOnSend(cTRUE)
	{}
	
	DECLARE_IID(cMCPluginSettings, cSerializable, PID_MCTASK, mcstruct_MC_PluginSettings);
	
	tBOOL m_bCheckOnDelivery;
	tBOOL m_bCheckOnRead;
	tBOOL m_bCheckOnSend;
};

IMPLEMENT_SERIALIZABLE_BEGIN( cMCPluginSettings, 0 )
	SER_VALUE( m_bCheckOnDelivery,       tid_BOOL,                   "CheckOnDelivery" )
	SER_VALUE( m_bCheckOnRead,           tid_BOOL,                   "CheckOnRead" )
	SER_VALUE( m_bCheckOnSend,           tid_BOOL,                   "CheckOnWriteComplete" )
IMPLEMENT_SERIALIZABLE_END()


#define npNO_NEED_TREATMENT ((tSTRING)("NO_NEED_TREATMENT")) // �������� �� ������ (��� ������ ��������) ��� ��������

//-----------------------------------------------------------------------------

//	//-----------------------------------------------------------------------------
//	// ��������� �������, ����������� ��� MailCommon
//
//	struct cMailPluginSettings_Common : public cSerializable
//	{
//		cMailPluginSettings_Common() :
//			bOptional (cTRUE)
//			{}
//
//		DECLARE_IID(cMailPluginSettings_Common, cSerializable, PID_MCTASK, mcstruct_MC_PLUGINS);
//
//		tBOOL bOptional;	//!< cFALSE - ����������  ��� ������ ��������� �������� ����� �������
//	};
//
//	/*
//	IMPLEMENT_SERIALIZABLE_BEGIN( cMailPluginSettings_Common )
//		SER_VALUE( cMailPluginSettings_Common, bOptional, tid_BOOL, "Optional" ),	//!< cFALSE - ����������  ��� ������ ��������� �������� ����� �������
//	IMPLEMENT_SERIALIZABLE_END( cMailPluginSettings_Common, 0 );
//	*/
//
//	//-----------------------------------------------------------------------------
//	//! ��������� �������� �� ���������� �������
//
//	struct cMailFilterParams;
//
//	struct cMailFilterResultActions : public cSerializable 
//	{
//		cMailFilterResultActions() : 
//			cSerializable(),
//			szResultName				(),
//			dwResultId					(0),
//			PrimaryAction				(mailpa_Pass),
//			szPlaceholderTemplate		(),
//			szNextFilter				(),
//			bStopProcessing				(cFALSE),
//			TotalPrimaryAction			(0),
//			bSendReportToAdmin			(cFALSE),
//			szAdminNotifyAddress		(),
//			szNotifyFromAddress			(),
//			szNotifyAdminTemplate		(),
//			bSendReportToRecipient		(cFALSE),
//			szNotifyRecipientTemplate	(),
//			bSendReportToSender			(cFALSE),
//			szNotifySenderTemplate		()
//			{}
//
//		cMailFilterResultActions( const cMailFilterResultActions& o ) : 
//			cSerializable(),
//			szResultName( o.szResultName ),
//			dwResultId( o.dwResultId ),
//			PrimaryAction( o.PrimaryAction ),
//			szPlaceholderTemplate( o.szPlaceholderTemplate ),
//			szNextFilter( o.szNextFilter ),
//			bStopProcessing( o.bStopProcessing ),
//			TotalPrimaryAction( o.TotalPrimaryAction ),
//			bSendReportToAdmin( o.bSendReportToAdmin ),
//			szAdminNotifyAddress( o.szAdminNotifyAddress ),
//			szNotifyFromAddress( o.szNotifyFromAddress ),
//			szNotifyAdminTemplate( o.szNotifyAdminTemplate ),
//			bSendReportToRecipient( o.bSendReportToRecipient ),
//			szNotifyRecipientTemplate( o.szNotifyRecipientTemplate ),
//			bSendReportToSender( o.bSendReportToSender ),
//			szNotifySenderTemplate( o.szNotifySenderTemplate )
//			{}
//
//		DECLARE_IID( cMailFilterResultActions, cSerializable, PID_MCTASK, mcstruct_MAILFILTERRESULTACTIONS_SETTINGS );
//			
//		cStringObj szResultName;				//!< ��� ���������� ����������
//		tDWORD dwResultId;						//!< ������������� ���������� ����������
//		//////////////////////////////////////////////////////////////////////////
//		// primary action is following next
//		tPrimaryAction PrimaryAction;			//!< �������� �������� � �������� 
//		cStringObj szPlaceholderTemplate;		//!< ������ ����������� ������
//		//////////////////////////////////////////////////////////////////////////
//		cStringObj szNextFilter;				//!< ��������� �� ��������� ������ (�.�. = "")
//		tBOOL bStopProcessing;					//!< ��������� ����������
//		//////////////////////////////////////////////////////////////////////////
//		// total actions are following next (used only for "bStopProcessing == cTRUE")
//		tTotalPrimaryAction TotalPrimaryAction;	//!< �������� ������� �������� 
//		tBOOL bSendReportToAdmin;				//!< �������� �� ����� ��������������?
//		cStringObj szAdminNotifyAddress;		//!< ����� �������������� ��� �������� �������
//		cStringObj szNotifyFromAddress;			//!< ����� �������������� ���� �� �������� ������� (�.�. = szAdminNotifyAddress)
//		cStringObj szNotifyAdminTemplate;		//!< ������ ������ ��������������
//		tBOOL bSendReportToRecipient;			//!< �������� �� ����� ����������?
//		cStringObj szNotifyRecipientTemplate;	//!< ������ ������ ����������
//		tBOOL bSendReportToSender;				//!< �������� �� ����� �����������?
//		cStringObj szNotifySenderTemplate;		//!< ������ ������ �����������
//	};
//
//	/*
//	IMPLEMENT_SERIALIZABLE_BEGIN( cMailFilterResultActions )
//		SER_COOL_SERIALIZER_IN_PLACE( cMailFilterResultActions, szResultName, &gCSS_str, tid_STRING, "ResultName" ),				//!< ��� ���������� ����������
//		//SER_VALUE( cMailFilterResultActions, dwResultId, tid_DWORD, "ResultId" ),						//!< ������������� ���������� ����������
//
//		//////////////////////////////////////////////////////////////////////////
//		// primary action is following next
//		SER_VALUE( cMailFilterResultActions, PrimaryAction, tid_DWORD, "PrimaryAction" ),			//!< �������� �������� � �������� 
//		SER_COOL_SERIALIZER_IN_PLACE( cMailFilterResultActions, szPlaceholderTemplate, &gCSS_wstr, tid_WSTRING, "PlaceholderTemplate" ),		//!< ������ ����������� ������
//
//		//////////////////////////////////////////////////////////////////////////
//		SER_COOL_SERIALIZER_IN_PLACE( cMailFilterResultActions, szNextFilter, &gCSS_str, tid_STRING, "NextFilter" ),				//!< ��������� �� ��������� ������ (�.�. = "")
//		SER_VALUE( cMailFilterResultActions, bStopProcessing, tid_BOOL, "StopProcessing" ),					//!< ��������� ����������
//
//		//////////////////////////////////////////////////////////////////////////
//		// total actions are following next (used only for "bStopProcessing == cTRUE")
//		SER_VALUE( cMailFilterResultActions, TotalPrimaryAction, tid_DWORD, "TotalPrimaryAction" ),	//!< �������� ������� �������� 
//		SER_VALUE( cMailFilterResultActions, bSendReportToAdmin, tid_BOOL, "SendReportToAdmin" ),				//!< �������� �� ����� ��������������?
//		SER_COOL_SERIALIZER_IN_PLACE( cMailFilterResultActions, szAdminNotifyAddress, &gCSS_wstr, tid_WSTRING, "AdminNotifyAddress" ),		//!< ����� �������������� ��� �������� �������
//		SER_COOL_SERIALIZER_IN_PLACE( cMailFilterResultActions, szNotifyFromAddress, &gCSS_wstr, tid_WSTRING, "NotifyFromAddress" ),		//!< ����� �������������� ���� �� �������� ������� (�.�. = szAdminNotifyAddress)
//
//		SER_COOL_SERIALIZER_IN_PLACE( cMailFilterResultActions, szNotifyAdminTemplate, &gCSS_wstr, tid_WSTRING, "NotifyAdminTemplate" ),		//!< ������ ������ ��������������
//		SER_VALUE( cMailFilterResultActions, bSendReportToRecipient, tid_BOOL, "SendReportToRecipient" ),			//!< �������� �� ����� ����������?
//		SER_COOL_SERIALIZER_IN_PLACE( cMailFilterResultActions, szNotifyRecipientTemplate, &gCSS_wstr, tid_WSTRING, "NotifyRecipientTemplate" ),	//!< ������ ������ ����������
//		SER_VALUE( cMailFilterResultActions, bSendReportToSender, tid_BOOL, "SendReportToSender" ),				//!< �������� �� ����� �����������?
//		SER_COOL_SERIALIZER_IN_PLACE( cMailFilterResultActions, szNotifySenderTemplate, &gCSS_wstr, tid_WSTRING, "NotifySenderTemplate" ),	//!< ������ ������ �����������
//	IMPLEMENT_SERIALIZABLE_END_KEY_NAME_BY_FIELD_VALUE( cMailFilterResultActions, dwResultId, tid_DWORD, 0 );
//	*/
//
//	//-----------------------------------------------------------------------------
//	//! ��������� runtime-������� (�������� ���������� ������ �������) + ��������� ��������������� ������� ("process_params")
//
//	struct cMailFilterParams : public cSerializable 
//	{
//		cMailFilterParams() : 
//			cSerializable(),
//			dwPID( PID_ANY ),
//			szFilterName (),
//			process_params ()
//			{}
//
//		cMailFilterParams( const cMailFilterParams& o ) : 
//			cSerializable(),
//			dwPID( o.dwPID ),
//			szFilterName ( o.szFilterName ),
//			process_params ( o.process_params )
//			{}
//			
//		DECLARE_IID( cMailFilterParams, cSerializable, PID_MCTASK, mcstruct_MAILFILTER_SETTINGS );
//
//		tDWORD dwPID;							//!< ������������� ��������� �������. ��������� ������� ������� ����������� � ���������� iRegistry �������� i_task.h::pgTASK_CONFIG � ����������� �����
//		cStringObj szFilterName;				//!< ���������� ��� runtime-������� 
//		cStringObj process_params;				//!< ������� ��� ����� �������, ���������� ��������� ������� �������. 
//	};
//
//	/*
//	IMPLEMENT_SERIALIZABLE_BEGIN( cMailFilterParams )
//		SER_VALUE( cMailFilterParams, dwPID, tid_DWORD, "PID" ),							//!< ������������� ��������� �������. ��������� ������� ������� ����������� � ���������� iRegistry �������� i_task.h::pgTASK_CONFIG � ����������� �����
//		//SER_COOL_SERIALIZER_IN_PLACE( cMailFilterParams, szFilterName, &gCSS_str, tid_STRING, "FilterName" ),				//!< ���������� ��� runtime-������� 
//		SER_COOL_SERIALIZER_IN_PLACE( cMailFilterParams, process_params, &gCSS_str, tid_STRING, "process_params" ),				//!< ������ ��� ����� �������, ���������� ��������� ������� �������. ��������� �������� ����� ��������� pGetProp
//	IMPLEMENT_SERIALIZABLE_END_KEY_NAME_BY_FIELD_VALUE( cMailFilterParams, szFilterName, tid_STRING, &gCSS_strByKey );
//	*/
//
//	//-----------------------------------------------------------------------------
//	//! ������ ��������
//
//	struct cMBLParams : public cSerializable
//	{
//		cMBLParams() :
//			cSerializable(),
//			szMailTaskType(),
//			szMailFilterList (),
//			szMailPartFilterList (),
//			ulThreadCount( 1 )
//			{}
//		
//		cMBLParams( const cMBLParams& o ) :
//			cSerializable(),
//			szMailTaskType( o.szMailTaskType ),
//			MailInterceptorLoaders( o.MailInterceptorLoaders ),
//			szMailFilterList( o.szMailFilterList ),
//			szMailPartFilterList( o.szMailPartFilterList ),
//			ulThreadCount( o.ulThreadCount ),
//			MailFilters( o.MailFilters ),
//			MailPartFilters( o.MailPartFilters )
//
//			{}
//			
//		DECLARE_IID( cMBLParams, cSerializable, PID_MCTASK, mcstruct_MBL_SETTINGS );
//
//		cStringObj szMailTaskType;				//!< ��� ������ �������� ����������
//		typedef cVector<tPID> MailInterceptorLoaders_t;
//		MailInterceptorLoaders_t MailInterceptorLoaders;	//!< ������ �������� ������������� (PID'� �� �����������)
//		cStringObj szMailFilterList;			//!< ������������� ������ �������� ������ ������ (����� �������� cMailFilterParams::szFilterName ����� �����������)
//		cStringObj szMailPartFilterList;		//!< ������������� ������ �������� ������ ����� ������ (����� �������� cMailFilterParams::szFilterName ����� �����������)
//		tULONG ulThreadCount;					//!< ���������� �������, � ������� ������ ����������� �������� MBL
//		typedef cVector<cMailFilterParams> MailFilterParams_t;
//		MailFilterParams_t MailFilters;			//!< ��������� ���������� (������ ������)
//		MailFilterParams_t MailPartFilters;		//!< ��������� ���������� (������ ����� ������)
//	};
//
//	/*
//	IMPLEMENT_SERIALIZABLE_BEGIN( cMBLParams )
//		SER_COOL_SERIALIZER( cMBLParams, MailInterceptorLoaders, &gCSV_dwByKey, tid_DWORD, "MailInterceptorLoaders" ),	//!< ������ �������� ������������� (PID'� �� �����������)
//		SER_COOL_SERIALIZER_IN_PLACE( cMBLParams, szMailFilterList, &gCSS_str, tid_STRING, "MailFilterList" ),			//!< ������������� ������ �������� ������ ������ (����� �������� cMailFilterParams::szFilterName ����� �����������)
//		SER_COOL_SERIALIZER_IN_PLACE( cMBLParams, szMailPartFilterList, &gCSS_str, tid_STRING, "MailPartFilterList" ),		//!< ������������� ������ �������� ������ ����� ������ (����� �������� cMailFilterParams::szFilterName ����� �����������)
//		SER_VALUE( cMBLParams, ulThreadCount, tid_DWORD, "ThreadCount" ),					//!< ���������� �������, � ������� ������ ����������� �������� MBL
//		SER_COOL_SERIALIZER( cMBLParams, MailFilters, &gCSV_MailFilterParams, tid_VOID, "MailFilters" ),			//!< ��������� ���������� (������ ������)
//		SER_COOL_SERIALIZER( cMBLParams, MailPartFilters, &gCSV_MailFilterParams, tid_VOID, "MailPartFilters" ),		//!< ��������� ���������� (������ ����� ������)
//	IMPLEMENT_SERIALIZABLE_END_KEY_NAME_BY_FIELD_VALUE( cMBLParams, szMailTaskType, tid_STRING, &gCSS_strByKey );
//	*/
//
//	//-----------------------------------------------------------------------------
//	//! ��������� MTM (MailTaskManager)
//
//	struct cMTMParams : public cSerializable
//	{
//		cMTMParams() :
//			cSerializable(),
//			dwProtectionLevel(0)
//			{}
//
//		cMTMParams( const cMTMParams& o ) :
//			cSerializable(),
//			dwProtectionLevel( o.dwProtectionLevel ),
//			MailPlugins( o.MailPlugins ),
//			MBLs( o.MBLs )
//			{}
//
//		DECLARE_IID( cMTMParams, cSerializable, PID_MCTASK, mcstruct_MTM_SETTINGS );
//
//		tDWORD dwProtectionLevel;				//!< ������� ������
//		typedef cVector<tPID> MailPluginParams_t;
//		MailPluginParams_t MailPlugins;			//!< ������ ��������
//		typedef cVector<cMBLParams> MBLParams_t;
//		MBLParams_t MBLs;						//!< ������ �������� � ��������� ����������
//	};
//
//	/*
//	IMPLEMENT_SERIALIZABLE_BEGIN( cMTMParams )
//		SER_VALUE( cMTMParams, dwProtectionLevel, tid_DWORD, "ProtectionLevel" ),
//		SER_COOL_SERIALIZER( cMTMParams, MBLs, &gCSV_MBLParams, tid_VOID, "MBLs" ),						//!< ������ �������� � ��������� ����������
//		SER_COOL_SERIALIZER( cMTMParams, MailPlugins, &gCSV_dwByKey, tid_DWORD, "MailPlugins" ),		//!< ������ ��������
//	IMPLEMENT_SERIALIZABLE_END( cMTMParams, 0 );
//	*/
//
//	//-----------------------------------------------------------------------------
//	//! ����������, ��������������� MailCommon
//
//	struct cMailCommonStatistics: public cTaskStatistics 
//	{
//		cMailCommonStatistics():
//			cTaskStatistics(),
//			m_szSenderName(),
//			m_nNumObjects(0),
//			m_timeLastObject(-1)
//		{}
//
//		cMailCommonStatistics& operator+=(const cMailCommonStatistics& o)
//		{
//			if ( m_szSenderName == o.m_szSenderName ) 
//			{
//				if ( -1 == m_timeStart ) 
//					m_timeStart = o.m_timeStart;
//				if ( -1 == m_timeFinish ) 
//					m_timeFinish = o.m_timeFinish;
//
//				m_nNumObjects += o.m_nNumObjects;
//				// m_nNumFiltersVerdicts
//				{
//					if ( o.m_nNumVerdicts.size() > m_nNumVerdicts.size() ) 
//						m_nNumVerdicts.resize( o.m_nNumVerdicts.size() );
//					for (tUINT i=0; i < m_nNumVerdicts.size(); i++)
//						m_nNumVerdicts[i] += o.m_nNumVerdicts[i];
//				}
//				m_timeLastObject = o.m_timeLastObject;
//			}
//			return *this;
//		}
//
//		DECLARE_IID( cMailCommonStatistics, cTaskStatistics , PID_MCTASK, mcstruct_MC_STATISTICS );
//
//		cStringObj        m_szSenderName;                   // ��� ���� �������, ������� ����������� ������ ����������. 
//																												// ��� ��������� �������� ���������� �������� ��� ������� ������
//		long              m_nNumObjects;                    // ���������� �������� �� �������� � MailCommon ��������
//		cVector<long>     m_nNumVerdicts;			        // ���������� ��������� (�� �����). TODO: �� ����� ������� ������� � ����� ������ ���������� � ������: ��� ����, ����� ��������� �������� ������ ��������, ���������� ������������ ������ ��� 99 ������ ���������!
//		__time32_t        m_timeLastObject;                 // ����� ��������� ���������� �������
//		
//	};
//
//	//-----------------------------------------------------------------------------
//
//	struct cMCSettingsVersion : public cSerializable
//	{
//		cMCSettingsVersion():
//			cSerializable(),
//			m_ulSettingsVersion(0)
//			{}
//
//		DECLARE_IID( cMCSettingsVersion, cSerializable, PID_MCTASK, mcstruct_MC_SETTINGS_VERSION );
//
//		tULONG	m_ulSettingsVersion;
//	};
//
//	IMPLEMENT_SERIALIZABLE_BEGIN( cMCSettingsVersion, 0 )
//		SER_VALUE( m_ulSettingsVersion, tid_BOOL, "SettingsVersion" )
//	IMPLEMENT_SERIALIZABLE_END()
//
//	//-----------------------------------------------------------------------------

#endif//  __S_MC_H
