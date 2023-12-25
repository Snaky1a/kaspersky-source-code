/*!
*		
*		
*		(C) 2002 Kaspersky Lab 
*		
*		\file	mailchecker_types.h
*		\brief	���� �������� ��� MailCommon[Prague], ���������� �� cSerializable

		\
		|
		+-+ hMTMSettings
		  +-+ hMailTaskParams[]
		    +- szMailTaskType
		    +- dwThreadCount
		    +- szFilterList
		    +-+ hMailFilterParams[]
		      +- szFilterName
		      +- hMailPluginParams ("process_params")
			  +-+ hMailFilterResultActions[]
			    +- szResultName				
			    +- dwResultId					
			    +- PrimaryAction				
			    +- szPlaceholderTemplate		
			    +- NextFilter					
			    +- bStopProcessing				
			    +- TotalPrimaryAction			
			    +- szAdminNotifyAddress		
			    +- szNotifyFromAddress			
			    +- szNotifyAdminTemplate		
			    +- szNotifyRecipientTemplate	
			    +- szNotifySenderTemplate		

*		
*		\author Vitaly DVi Denisov
*		\date	24.12.2003 17:29:52
*		
*		
*/		


#ifndef _MAILCHECKER_TYPES_H_
#define _MAILCHECKER_TYPES_H_

#pragma warning(disable:4786)

// Prague headers
#include <prague.h>      // Prague main header: types, system intrface, errors etc...
//#include <iface/i_os.h>
//#include <iface/i_serializer.h>
//#include <iface/i_engine.h>
#include <map>
//#include <iface/i_mailtask.h>
//#include <iface/i_mailfilter.h>
//#include <pr_err.h>
//#include <ppp.h>

#include <structs/s_mc.h>
#include <string>
#include <vector>



//
//	//! �������� �������� ��������, ������������ ��� �������� ������
//	typedef enum enum_PrimaryAction
//	{
//		mailpa_Pass = 0,
//		mailpa_DeleteObject,
//		mailpa_ChangeObjectToText
//		// mailpa_Disinfect - �� ����, ��� ����� ����� ����� �������
//	}	tPrimaryAction;
//
//	//! �������� �������� ��������, ������������ ��� �������
//	//! ����������� ���������� � <iface/i_mailtask.h>
//	//typedef enum enum_TotalPrimaryAction
//	//{
//	//	mailtpa_Pass = 0,
//	//	mailtpa_DeleteOrBlockMessage,
//	//	mailtpa_RejectMessage,
//	//	mailtpa_PassMessageAsAttachment - �� ����, ��� ����� ����� ����� ������� ���
//	//}	tTotalPrimaryAction;
//
//	//////////////////////////////////////////////////////////////////////////
//	//
//	//			+ MC
//	//			+-+ MailPlugins
//	//			  +-+ 40002					// PID ������� (���������� ����� ������ �� ����������, ������ ������ ������ ��������� ��� ����������� �������)
//	//			  | +- <plugin_params>		// ������������������� ��������� ������������� �������
//	//			  | +-+ PROCESS_OVERWRITE	// ������ ��� ���������� ���������� ��������������� (����� �������������)
//	//			  | | +- <process_params>	// ������������������� ��������� ���������������
//	//			  | +-+ PROCESS_DEFAULT		// ������ ������������� ���������� ��������������� (������������ ������)
//	//			  | | +- <process_params>
//	//			  | +-+ ProcessParams1		// ������ ���������� ��������������� (���������� ����� ������ �� ����������). � ������ ���������� ������ � �������� ������ (���� ���������� ����� ���������� ��������������� <process_params>) ������ ������ ����� �� �� ������ PROCESS_DEFAULT. �� ��������� ������ ���������� ��������������� ������� �������������� �� �������� ����������� �� ������ PROCESS_OVERWRITE.
//	//			  | | +- <process_params>
//	//			  | ...
//	//			  | |
//	//			  | +-+ ProcessParams(N)
//	//			  |   +- <process_params>
//	//			  ...
//	//			  |
//	//			  +-+ PID_XXX
//	//			    +- <plugin_params>
//	//			    +-+ PROCESS_DEFAULT
//	//			      +- <process_params>
//	//
//
//
//	//
//	//////////////////////////////////////////////////////////////////////////
//
//
//	struct cMailFilterParams;
//
//	//! ��������� �������� �� ���������� �������
//	struct cMailFilterResultActions : public cSerializable 
//	{
//		cMailFilterResultActions() : 
//			cSerializable(),
//			szResultName				(""),
//			dwResultId					(0),
//			PrimaryAction				(mailpa_Pass),
//			szPlaceholderTemplate		(L""),
//			szNextFilter				(""),
//			bStopProcessing				(cFALSE),
//			TotalPrimaryAction			(mailtpa_Pass),
//			bSendReportToAdmin			(cFALSE),
//			szAdminNotifyAddress		(L""),
//			szNotifyFromAddress			(L""),
//			szNotifyAdminTemplate		(L""),
//			bSendReportToRecipient		(cFALSE),
//			szNotifyRecipientTemplate	(L""),
//			bSendReportToSender			(cFALSE),
//			szNotifySenderTemplate		(L"")
//			{m_unique = SERID_MAILFILTERRESULTACTIONS_SETTINGS;};
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
//			{m_unique = SERID_MAILFILTERRESULTACTIONS_SETTINGS;};
//			
//		std::string szResultName;				//!< ��� ���������� ����������
//		tDWORD dwResultId;						//!< ������������� ���������� ����������
//		//////////////////////////////////////////////////////////////////////////
//		// primary action is following next
//		tPrimaryAction PrimaryAction;			//!< �������� �������� � �������� 
//		std::wstring szPlaceholderTemplate;		//!< ������ ����������� ������
//		//////////////////////////////////////////////////////////////////////////
//		std::string szNextFilter;				//!< ��������� �� ��������� ������ (�.�. = "")
//		tBOOL bStopProcessing;					//!< ��������� ����������
//		//////////////////////////////////////////////////////////////////////////
//		// total actions are following next (used only for "bStopProcessing == cTRUE")
//		tTotalPrimaryAction TotalPrimaryAction;	//!< �������� ������� �������� 
//		tBOOL bSendReportToAdmin;				//!< �������� �� ����� ��������������?
//		std::wstring szAdminNotifyAddress;		//!< ����� �������������� ��� �������� �������
//		std::wstring szNotifyFromAddress;		//!< ����� �������������� ���� �� �������� ������� (�.�. = szAdminNotifyAddress)
//		std::wstring szNotifyAdminTemplate;		//!< ������ ������ ��������������
//		tBOOL bSendReportToRecipient;			//!< �������� �� ����� ����������?
//		std::wstring szNotifyRecipientTemplate;	//!< ������ ������ ����������
//		tBOOL bSendReportToSender;				//!< �������� �� ����� �����������?
//		std::wstring szNotifySenderTemplate;	//!< ������ ������ �����������
//	};
//
//	//! ��������� runtime-������� (�������� ���������� ������ �������) + ��������� ��������������� ������� ("process_params")
//	struct cMailFilterParams : public cSerializable 
//	{
//		cMailFilterParams() : 
//			cSerializable(),
//			dwPID( PID_ANY ),
//			szFilterName (""),
//			process_params ("")
//			{m_unique = SERID_MAILFILTER_SETTINGS;};
//
//		cMailFilterParams( const cMailFilterParams& o ) : 
//			cSerializable(),
//			dwPID( o.dwPID ),
//			szFilterName ( o.szFilterName ),
//			process_params ( o.process_params )
//			{m_unique = SERID_MAILFILTER_SETTINGS;};
//			
//		tDWORD dwPID;							//!< ������������� ��������� �������. ��������� ������� ������� ����������� � ���������� iRegistry �������� i_task.h::pgTASK_CONFIG � ����������� �����
//		std::string szFilterName;				//!< ���������� ��� runtime-������� 
//		std::string process_params;				//!< ������� ��� ����� �������, ���������� ��������� ������� �������. 
//	};
//
//	//! ������ ��������
//	struct cMBLParams :  cSerializable
//	{
//		cMBLParams() :
//			cSerializable(),
//			szMailTaskType( "" ),
//			szMailFilterList (""),
//			szMailPartFilterList (""),
//			ulThreadCount( 1 )
//			{m_unique = SERID_MBL_SETTINGS;};
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
//			{m_unique = SERID_MBL_SETTINGS;}
//			
//		std::string szMailTaskType;				//!< ��� ������ �������� ����������
//		typedef std::vector<tDWORD> MailInterceptorLoaders_t;
//		MailInterceptorLoaders_t MailInterceptorLoaders;	//!< ������ �������� ������������� (PID'� �� �����������)
//		std::string szMailFilterList;			//!< ������������� ������ �������� ������ ������ (����� �������� cMailFilterParams::szFilterName ����� �����������)
//		std::string szMailPartFilterList;		//!< ������������� ������ �������� ������ ����� ������ (����� �������� cMailFilterParams::szFilterName ����� �����������)
//		tULONG ulThreadCount;					//!< ���������� �������, � ������� ������ ����������� �������� MBL
//		typedef std::vector<cMailFilterParams> MailFilterParams_t;
//		MailFilterParams_t MailFilters;			//!< ��������� ���������� (������ ������)
//		MailFilterParams_t MailPartFilters;		//!< ��������� ���������� (������ ����� ������)
//	};
//
//	//! ��������� MTM (MailTaskManager)
//	struct cMTMParams : public cSerializable
//	{
//		cMTMParams() :
//			cSerializable(),
//			dwProtectionLevel(PROT_RECOMMENDED)
//			{m_unique = SERID_MTM_SETTINGS;};
//
//		cMTMParams( const cMTMParams& o ) :
//			cSerializable(),
//			dwProtectionLevel( o.dwProtectionLevel ),
//			MailPlugins( o.MailPlugins ),
//			MBLs( o.MBLs )
//			{m_unique = SERID_MTM_SETTINGS;};
//
//		tDWORD dwProtectionLevel;				//!< ������� ������
//		typedef std::vector<tPID> MailPluginParams_t;
//		MailPluginParams_t MailPlugins;			//!< ������ ��������
//		typedef std::vector<cMBLParams> MBLParams_t;
//		MBLParams_t MBLs;						//!< ������ �������� � ��������� ����������
//	};


//! \enum: cPLUGIN_RES_t
typedef enum {
	cPLUGIN_RES_DEFAULT				= -2,	//! �������������� �������. cMailFilterResultActions �� ������ �������� ����������� � ������ ���������������� �������� �� ����� ������ ��������.
	cPLUGIN_RES_FAIL	 			= -1,	//!	�������: ������. � ������� ��������� ������, ��-�� ������� ������ �� ��� ���� ��������
	cPLUGIN_RES_OK					= 0,	//!	�������: �����. ������� ���������� �� ���������, ������ ����.
	cPLUGIN_RES_FOUND				= 1,	//!	�������: ��������� ������� ���������� (��������, ������ �������).
	cPLUGIN_RES_DELETED				= 2,	//!	�������: ������� ���������� ��������� � ������� ������ (��������, ������ ������� �� ������).
	cPLUGIN_RES_SUSPICIOUS			= 3,	//!	�������: ���������� �� ������� ����������.
	cPLUGIN_RES_UNKNOWN				= 4,	//!	�������: ������� ������������ ����, ���������� ����������.
	cPLUGIN_RES_ENCRYPTED			= 5,	//!	�������: ������ ����������, ���������� ����������.
	cPLUGIN_RES_PASSWORD_PROTECTED	= 6,	//!	�������: ������ ���������. ���������� ����������.
} enumPLUGIN_RES_t;	//! ����� ����������� ��������� �������� ��������. ������ ����� �����������

//////////////////////////////////////////////////////////////////////////
//
// �������� �������� � ��������� ����. ������ ����� �����������
//
#define cszPLUGIN_RES_DEFAULT				"DEFAULT"
#define cszPLUGIN_RES_FAIL	 				"FAIL"
#define cszPLUGIN_RES_OK					"OK"
#define cszPLUGIN_RES_FOUND					"FOUND"
#define cszPLUGIN_RES_DELETED				"DELETED"
#define cszPLUGIN_RES_SUSPICIOUS			"SUSPICIOUS"
#define cszPLUGIN_RES_UNKNOWN				"UNKNOWN"
#define cszPLUGIN_RES_ENCRYPTED				"ENCRYPTED"
#define cszPLUGIN_RES_PASSWORD_PROTECTED	"PASSWORD_PROTECTED"
//
// �������� �������� � ��������� ����. ������ ����� �����������
//
//////////////////////////////////////////////////////////////////////////


typedef std::map< std::string, int > szPLUGIN_RES_t;
struct cPLUGIN_RES: public szPLUGIN_RES_t
{
	cPLUGIN_RES():
	szPLUGIN_RES_t()
	{
		(*this)[ cszPLUGIN_RES_DEFAULT				] = cPLUGIN_RES_DEFAULT				;
		(*this)[ cszPLUGIN_RES_FAIL					] = cPLUGIN_RES_FAIL				;
		(*this)[ cszPLUGIN_RES_OK					] = cPLUGIN_RES_OK					;
		(*this)[ cszPLUGIN_RES_FOUND				] = cPLUGIN_RES_FOUND				;
		(*this)[ "INFECTED"							] = cPLUGIN_RES_FOUND				;
		(*this)[ cszPLUGIN_RES_DELETED				] = cPLUGIN_RES_DELETED				;
		(*this)[ "CURED"							] = cPLUGIN_RES_DELETED				;
		(*this)[ cszPLUGIN_RES_SUSPICIOUS			] = cPLUGIN_RES_SUSPICIOUS			;
		(*this)[ cszPLUGIN_RES_UNKNOWN				] = cPLUGIN_RES_UNKNOWN				;
		(*this)[ cszPLUGIN_RES_ENCRYPTED			] = cPLUGIN_RES_ENCRYPTED			;
		(*this)[ cszPLUGIN_RES_PASSWORD_PROTECTED	] = cPLUGIN_RES_PASSWORD_PROTECTED	;
	}
}; //! ����� ����������� ��������� �������� �������� (��������� ������������). ������ ����� �����������
extern cPLUGIN_RES g_hPluginAnswers;


//	struct cMailCommonStatistics: public cCommonStatistics 
//	{
//		cMailCommonStatistics():
//			cCommonStatistics(),
//			m_szSenderName(""),
//			m_nNumObjects(0),
//			m_timeLastObject(-1)
//		{ m_unique = SERID_MC_STATISTICS; };
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
//					for (long i=0; i < m_nNumVerdicts.size(); i++)
//						m_nNumVerdicts.at(i) += o.m_nNumVerdicts.at(i);
//				}
//				m_timeLastObject = o.m_timeLastObject;
//			}
//			return *this;
//		}
//
//		std::string       m_szSenderName;                   // ��� ���� �������, ������� ����������� ������ ����������. 
//															// ��� ��������� �������� ���������� �������� ��� ������� ������
//		long              m_nNumObjects;                    // ���������� �������� �� �������� � MailCommon ��������
//		std::vector<long> m_nNumVerdicts;			        // ���������� ��������� (�� �����). TODO: �� ����� ������� ������� � ����� ������ ���������� � ������: ��� ����, ����� ��������� �������� ������ ��������, ���������� ������������ ������ ��� 99 ������ ���������!
//		time_t            m_timeLastObject;                 // ����� ��������� ���������� �������
//		
//	};

#endif //_MAILCHECKER_TYPES_H_