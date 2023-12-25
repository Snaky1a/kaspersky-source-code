// AVP Prague stamp begin( Interface header,  )
// -------- Tuesday,  26 October 2004,  17:09 --------
// File Name   -- (null)i_avpg.cpp
// Copyright � Kaspersky Lab 1996-2004.
// -------------------------------------------
// AVP Prague stamp end



// AVP Prague stamp begin( Header ifndef,  )
#if !defined( __i_avpg__37b13221_ae7b_11d4_b757_00d0b7170e50 )
#define __i_avpg__37b13221_ae7b_11d4_b757_00d0b7170e50
// AVP Prague stamp end



// AVP Prague stamp begin( Header includes,  )
#include <Prague/iface/i_string.h>
// AVP Prague stamp end

#include <Prague/pr_vtbl.h>


// AVP Prague stamp begin( Interface comment,  )
// AVPG interface implementation
// Short comments -- �������� ���������� ��� �������������� � ���������-�������������
//    ��������� ������������� ������ � �������� avpg (sys/vxd) ��������� ������������� � �������� ������� ����������� ������� �������� ��� ��������� ����������� � �������� � �������� ������� (��������, ������, �������� ������, ��������������, ��������); ��������� ������ �� ������� �������; ����������������� ��������� �������.
// AVP Prague stamp end



// AVP Prague stamp begin( Interface menonic identificator,  )
#define IID_AVPG  ((tIID)(61004))
// AVP Prague stamp end



// AVP Prague stamp begin( Interface typedefs,  )
typedef tDWORD                         tAVPG_CLIENT_ACTIVITY_MODE; // ����� ���������� �������
typedef tDWORD                         tAVPG_PROCESS_OBJECT_RESULTS; // �������� ���������� ��������� �������
// AVP Prague stamp end



// AVP Prague stamp begin( Interface constants,  )

// ACTIVITY_MODE_PROPERTY_CONSTANT
// ��������� ��� �������� ��������� ��������� �������
#define cAVPG_CLIENT_ACTIVITY_MODE_SLEEP ((tAVPG_CLIENT_ACTIVITY_MODE)(0)) // ������� ��� ������� �� ������������ �������������
#define cAVPG_CLIENT_ACTIVITY_MODE_ACTIVE ((tAVPG_CLIENT_ACTIVITY_MODE)(1)) // ������ ������� � ������ ������������ ������� �� ��������� ���������� �������

// EVENT ATTRIBUTES
// �������� ��������� ������� �������
// �������� ������� ��� ��������������� �������
#define cAVPG_EVENT_DEFINITION_PROP    ((tSTRING)("i_avpg event definiton")) // ��������� ���������� ������ � �������
#define cAVPG_USER_DEFINITION_PROP     ((tSTRING)("i_avpg User info")) // ��������� ������������, ���������� �������
#define cAVPG_PROCESS_DEFINITION_PROP  ((tSTRING)("i_avpg Process")) // �������� ��� ��������, ���������� �������, � ANSI ���������
#define cAVPG_THREAD_DEFINITION_PROP   ((tSTRING)("i_avpg Thread definition")) // �������� ������ � ������� ������ ��������������� �������
#define cAVPG_PROP_OBJECT_MODIFIED     ((tSTRING)("i_avpg_object modified")) // ������� ������� �������� � ���������������� ��� �� ��� ������ �� ��������� �������
#define cAVPG_PROP_EVENT_PROCESSID     ((tSTRING)("i_avpg_event process id")) // ProcessID �������������� ��������
#define cAVPG_CRUSER_DEFINITION_PROP   ((tSTRING)("i_avpg creator User info")) // ��������� ������������, ���������� �������

// Notification messages
// ��������������� ���������
// ��� ��������� ����������� �� ������� ������, ��������������� �������
#define pmc_AVPG                       ((tDWORD)(1222188959)) // ������������� ������ ��������������� ���������
#define pm_AVPG_NOTIFY_THREAD_STARTED  ((tDWORD)(201)) // ������ ����� ������� �����
#define pm_AVPG_NOTIFY_THREAD_STOPPED  ((tDWORD)(202)) // ������� ����� ����� ���������� ����� ��������� �����������
#define pm_AVPG_NOTIFY_MISSED_OBJECT   ((tDWORD)(203)) // ��� ��������� ������� ����������� �� ������������ ��������� ������� �� ��������� �������� �������
#define pm_AVPG_NOTIFY_FOREACHTHREAD   ((tDWORD)(204)) // ��������� ��������� � ���������� ��������� ��� ������� �������� ������ (in/out)
#define pm_AVPG_NOTIFY_VOLUME_MOUNTED  ((tDWORD)(205)) // �������� �������� ����������� ������ ����
#define pm_AVPG_NOTIFY_DRIVER_CONNECTION_IS_BROKEN ((tDWORD)(206)) // ��������� ��� �� �����-���� ���������� �������� �������� ����� ��������� ������� �� ������������
#define pm_AVPG_NOTIFY_WRITEBOOT_DETECTED ((tDWORD)(207)) // ����������� � ��������� ��������� �������� ����
#define pm_AVPG_NOTIFY_CACHESIZE_CHANGED ((tDWORD)(208)) // ����������� ��� ��� ����������� ����������� ������� ������������� ������ ���� (�������� ������...)
#define pm_AVPG_NOTIFY_TERMINATE_PROCESS_DETECTED ((tDWORD)(209)) // ������� ��� ������ ������� �������� ���������� �����
#define pm_AVPG_NOTIFY_FORMAT_TRACK    ((tDWORD)(210)) // ����������� � �������������� ��������� �������� ����

// Object processing
// ������ �� ��������� ������� ��� �������
#define pm_AVPG_PROCEED_OBJECT         ((tDWORD)(301)) // ������ �� ��������� �������

// Control messages
// ����������� ���������
#define pmc_AVPG_CONTROL               ((tDWORD)(1222188960)) // ����������� ��������� ��� ���������� �������
#define pm_AVPG_CONTROL_PROCESS_PROTECTION_ON ((tDWORD)(401)) // �������� ������ ��� �������� ��������
#define pm_AVPG_CONTROL_PROCESS_PROTECTION_OFF ((tDWORD)(402)) // ��������� ������ ��� �������� ��������
#define pm_AVPG_CONTROL_PROCESS_PROTECTION_QUERY ((tDWORD)(403)) // ������ �� ������� ��������� ������
#define pm_AVPG_CONTROL_INCREASEUNSAFE ((tDWORD)(404)) // ���������� ������� ����������� �������� ��� ������������� ��������� �������
#define pm_AVPG_CONTROL_DECREASEUNSAFE ((tDWORD)(405)) // ��������� ������� ������������ �������� ��� ������������� ��������� �������
#define pm_AVPG_CONTROL_SET_STAT_LOGFILENAME ((tDWORD)(501)) // ���������� ��� ����� � ������� �� ����������
#define pm_AVPG_CONTROL_SET_PREVERDICT ((tDWORD)(601)) // ���������� ��������������� Verdict ��� ��������������� �������
#define pm_AVPG_CONTROL_GETEVENT_THREAD_ID ((tDWORD)(602)) // ��������� �������� ������������� ������, ���������������� ������ �������
#define pm_AVPG_CONTROL_PREFETCH       ((tDWORD)(603)) // ���������� ��������������� ������� (prefetch) ��� �������� �����
#define pm_AVPGS_INCOME               ((tDWORD)(0x8cdea98d))
#define pm_AVPG_CONTROL_CHECKBACKUP   ((tDWORD)(604)) // ��������� ����� �������� � �������
#define pm_AVPG_CONTROL_SKIPBACKUP    ((tDWORD)(605)) // �� ��������� ����� �������� � �������
#define pm_AVPG_CONTROL_GET_PROCESS_HASH ((tDWORD)(606)) // ������ ��� ��������� ����� ��������

// Return codes for pm_AVPG_PROCEED_OBJECT
// ���� �������� ��� ��������������� �������
#define cAVPG_RC_ALLOW                 ((tAVPG_PROCESS_OBJECT_RESULTS)(0)) // ��������� ���������� ��������� �������. ������� ��������� �� ����������
#define cAVPG_RC_ALLOW_CACHE           ((tAVPG_PROCESS_OBJECT_RESULTS)(1)) // ��������� ���������� ��������� �������. ������ ��������� � ���
#define cAVPG_RC_DENY_ACCESS           ((tAVPG_PROCESS_OBJECT_RESULTS)(2)) // ��������� ���������� ��������� �������
#define cAVPG_RC_DELETE_OBJECT         ((tAVPG_PROCESS_OBJECT_RESULTS)(3)) // ��������� ���������� ��������� �������. ����� ��������� ������ �������
#define cAVPG_RC_KILL_PROCESS          ((tAVPG_PROCESS_OBJECT_RESULTS)(4)) // ��������� ���������� ��������� �������. ����� ��������� ���������� �������, ��������� �������
#define cAVPG_RC_GO_DELAYED            ((tAVPG_PROCESS_OBJECT_RESULTS)(5)) // ��������� ���������� ��������� �������. ������� ��������������� �� ��������� ���������� ���������

// - statistic property
// custom �������� �� ����� ����������
// ��� �������� ��������������� �� hString - ������� ������ � ������ ��������������� ������� (����� �������� LogFileName)
#define cAVPG_STAT_TIME_EVENT_START_PROCESSING ((tSTRING)("i_avpg Event start processing")) // ��������� ����� ���������� (PerfomanceTimer)
#define cAVPG_STAT_TIME_BEFORE_CREATE_IO ((tSTRING)("i_avpg Before create io")) // ����� ������� ����� ��������� IO
#define cAVPG_STAT_TIME_BEFORE_CHECK1  ((tSTRING)("i_avpg Before engine 1 check")) //  --
#define cAVPG_STAT_TIME_BEFORE_CHECK2  ((tSTRING)("i_avpg Before engine 2 check")) //  --
#define cAVPG_STAT_TIME_BEFORE_CHECK3  ((tSTRING)("i_avpg Before engine 3 check")) //  --
#define cAVPG_STAT_TIME_EVENT_END_PROCESSING ((tSTRING)("i_avpg Event end processing")) // ��������������� �� ������ ����� ��������� ���������� ��������
#define cAVPG_STAT_RESULT_CREATE_IO    ((tSTRING)("i_avpg Create IO result")) //  --
#define cAVPG_STAT_RESULT_PROCESSING1  ((tSTRING)("i_avpg Processing1")) //  --
#define cAVPG_STAT_RESULT_PROCESSING_VERDICT ((tSTRING)("i_avpg Processing result")) //  --
#define cAVPG_STAT_TIME_ICHECKER_READ  ((tSTRING)("i_avpg IChecker read")) //  --
#define cAVPG_STAT_TIME_EVENT_VERDICT_TIME ((tSTRING)("i_avpg Event verdict time")) //  --

// - Custom origin
#define cAVPG_PROP_CUSTOM_ORIGIN       ((tSTRING)("i_avpg custom origin")) // �������� ��� �������� Origin ��� ������� hString
#define cAVPG_PROP_DOS_DEVICE_NAME     ((tSTRING)("i_avpg dos device name")) //  --

// - custom io
#define cAVPG_PROP_CUSTOM_IO           ((tSTRING)("i_avpg allow create special io")) // like MiniKavIO
#define cAVPG_PROP_STEAMED_FIXED_MEDIA ((tSTRING)("i_avpg streamed fixed media")) // ������������� ��������, ������������� ��� ��������, ����������� �� FIXED ������ � �������� �������� �������������� Alternative Data Streams (ADS)
#define cAVPG_PROP_DELAYED_PROCESSING  ((tSTRING)("i_avpg this is delayed processing")) // ��������� �������� ��� ������ cAVPG_RC_GO_DELAYED

// -
#define cAVPG_WORKING_MODE_ON_ACCESS   ((tDWORD)(0)) //  --
#define cAVPG_WORKING_MODE_ON_MODIFY   ((tDWORD)(1)) //  --
// AVP Prague stamp end



// AVP Prague stamp begin( Interface defined messages,  )
// AVP Prague stamp end



// AVP Prague stamp begin( Interface defined errors,  )
// AVP Prague stamp end



// AVP Prague stamp begin( RPC start declaration,  )
#if defined( __RPC__ )
	typedef tUINT hAVPG;
#else
// AVP Prague stamp end



// AVP Prague stamp begin( Interface forward declaration,  )
struct iAVPGVtbl;
typedef struct iAVPGVtbl iAVPGVtbl;
// AVP Prague stamp end



// AVP Prague stamp begin( Object declaration,  )
#if defined( __cplusplus ) && !defined(_USE_VTBL)
	struct cAVPG;
	typedef cAVPG* hAVPG;
#else
	typedef struct tag_hAVPG 
	{
		const iAVPGVtbl*   vtbl; // pointer to the "AVPG" virtual table
		const iSYSTEMVtbl* sys;  // pointer to the "SYSTEM" virtual table
	} *hAVPG;
#endif // if defined( __cplusplus )
// AVP Prague stamp end



// AVP Prague stamp begin( RPC_ end declaration,  )
#endif // if defined( __RPC__ )
// AVP Prague stamp end



// AVP Prague stamp begin( Private definitions begin,  )
#if !defined( AVPG_PRIVATE_DEFINITION )
// AVP Prague stamp end



// AVP Prague stamp begin( Interface function forward declarations,  )


	typedef   tERROR (pr_call *fnpAVPG_ChangeActivityMode)  ( hAVPG _this, tBOOL* result, tAVPG_CLIENT_ACTIVITY_MODE ActivityMode ); // -- ��������� ������ ����������;
	typedef   tERROR (pr_call *fnpAVPG_YieldEvent)          ( hAVPG _this, hOBJECT EventObject, tDWORD YieldTimeout ); // -- ������������� ��������� �������;
	typedef   tERROR (pr_call *fnpAVPG_ResetDriverCache)    ( hAVPG _this );                // -- ������� ���� ��������;
	typedef   tERROR (pr_call *fnpAVPG_ForEachThreadNotify) ( hAVPG _this, tDWORD* result, tDWORD* pNotifyParamData, tDWORD NotifyParamDataSize ); // -- �������� ��������� �������� ��������� pm_AVPG_NOTIFY_FOREACHTHREAD �� ������ ������� ������;
	typedef   tERROR (pr_call *fnpAVPG_StopAllDogsThread)   ( hAVPG _this, tDWORD* result );                // -- ������� ���������� ����� ��������� ���� ������� �������;
	typedef   tERROR (pr_call *fnpAVPG_AddInvisibleFile)    ( hAVPG _this, tSTRING szFileName ); // -- ���������� ��������� �������� ��� ��� ���������;
	typedef   tERROR (pr_call *fnpAVPG_CreateIO)            ( hAVPG _this, hOBJECT* result, hSTRING hObjectName ); // -- ������� IO �� ���������� �����;
	typedef   tERROR (pr_call *fnpAVPG_CopyConext)          ( hAVPG _this, hOBJECT SourceObject, hOBJECT DestinationObject ); // -- ����������� ����������� ��������� �������� ��� ��������� ��������;


// AVP Prague stamp end



// AVP Prague stamp begin( Interface declaration,  )
struct iAVPGVtbl 
{
	fnpAVPG_ChangeActivityMode   ChangeActivityMode;
	fnpAVPG_YieldEvent           YieldEvent;
	fnpAVPG_ResetDriverCache     ResetDriverCache;
	fnpAVPG_ForEachThreadNotify  ForEachThreadNotify;
	fnpAVPG_StopAllDogsThread    StopAllDogsThread;
	fnpAVPG_AddInvisibleFile     AddInvisibleFile;
	fnpAVPG_CreateIO             CreateIO;
	fnpAVPG_CopyConext           CopyConext;
}; // "AVPG" external virtual table prototype
// AVP Prague stamp end



// AVP Prague stamp begin( Private definitions end,  )
#endif // if !defined( AVPG_PRIVATE_DEFINITION )
// AVP Prague stamp end



// AVP Prague stamp begin( Interface declared properties,  )
//! #define pgINTERFACE_VERSION     mPROPERTY_MAKE_GLOBAL( pTYPE_VERSION , 0x00000082 )
//! #define pgINTERFACE_COMMENT     mPROPERTY_MAKE_GLOBAL( pTYPE_STRING  , 0x00000083 )
#define pgWorkingThreadMaxCount mPROPERTY_MAKE_GLOBAL( pTYPE_DWORD   , 0x00001004 )
#define pgDriverCacheSize       mPROPERTY_MAKE_GLOBAL( pTYPE_DWORD   , 0x00001005 )
#define pgClientActivityMode    mPROPERTY_MAKE_GLOBAL( pTYPE_DWORD   , 0x00001006 )
#define pgWorkingMode           mPROPERTY_MAKE_GLOBAL( pTYPE_DWORD   , 0x00001007 )
// AVP Prague stamp end



// AVP Prague stamp begin( Defines to simplify interface method calls,  )
#if !defined( __cplusplus ) || defined(_USE_VTBL)
	#define CALL_AVPG_ChangeActivityMode( _this, result, ActivityMode )                            ((_this)->vtbl->ChangeActivityMode( (_this), result, ActivityMode ))
	#define CALL_AVPG_YieldEvent( _this, EventObject, YieldTimeout )                               ((_this)->vtbl->YieldEvent( (_this), EventObject, YieldTimeout ))
	#define CALL_AVPG_ResetDriverCache( _this )                                                    ((_this)->vtbl->ResetDriverCache( (_this) ))
	#define CALL_AVPG_ForEachThreadNotify( _this, result, pNotifyParamData, NotifyParamDataSize )  ((_this)->vtbl->ForEachThreadNotify( (_this), result, pNotifyParamData, NotifyParamDataSize ))
	#define CALL_AVPG_StopAllDogsThread( _this, result )                                           ((_this)->vtbl->StopAllDogsThread( (_this), result ))
	#define CALL_AVPG_AddInvisibleFile( _this, szFileName )                                        ((_this)->vtbl->AddInvisibleFile( (_this), szFileName ))
	#define CALL_AVPG_CreateIO( _this, result, hObjectName )                                       ((_this)->vtbl->CreateIO( (_this), result, hObjectName ))
	#define CALL_AVPG_CopyConext( _this, SourceObject, DestinationObject )                         ((_this)->vtbl->CopyConext( (_this), SourceObject, DestinationObject ))
#else // if !defined( __cplusplus )
	#define CALL_AVPG_ChangeActivityMode( _this, result, ActivityMode )                            ((_this)->ChangeActivityMode( result, ActivityMode ))
	#define CALL_AVPG_YieldEvent( _this, EventObject, YieldTimeout )                               ((_this)->YieldEvent( EventObject, YieldTimeout ))
	#define CALL_AVPG_ResetDriverCache( _this )                                                    ((_this)->ResetDriverCache( ))
	#define CALL_AVPG_ForEachThreadNotify( _this, result, pNotifyParamData, NotifyParamDataSize )  ((_this)->ForEachThreadNotify( result, pNotifyParamData, NotifyParamDataSize ))
	#define CALL_AVPG_StopAllDogsThread( _this, result )                                           ((_this)->StopAllDogsThread( result ))
	#define CALL_AVPG_AddInvisibleFile( _this, szFileName )                                        ((_this)->AddInvisibleFile( szFileName ))
	#define CALL_AVPG_CreateIO( _this, result, hObjectName )                                       ((_this)->CreateIO( result, hObjectName ))
	#define CALL_AVPG_CopyConext( _this, SourceObject, DestinationObject )                         ((_this)->CopyConext( SourceObject, DestinationObject ))
#endif // if !defined( __cplusplus )
// AVP Prague stamp end



// AVP Prague stamp begin( C++ interface declaration,  )
#if defined (__cplusplus) && !defined(_USE_VTBL)
	struct pr_abstract iAVPG 
	{
		virtual tERROR pr_call ChangeActivityMode( tBOOL* result, tAVPG_CLIENT_ACTIVITY_MODE ActivityMode ) = 0; // -- ��������� ������ ����������
		virtual tERROR pr_call YieldEvent( hOBJECT EventObject, tDWORD YieldTimeout ) = 0; // -- ������������� ��������� �������
		virtual tERROR pr_call ResetDriverCache() = 0; // -- ������� ���� ��������
		virtual tERROR pr_call ForEachThreadNotify( tDWORD* result, tDWORD* pNotifyParamData, tDWORD NotifyParamDataSize ) = 0; // -- �������� ��������� �������� ��������� pm_AVPG_NOTIFY_FOREACHTHREAD �� ������ ������� ������
		virtual tERROR pr_call StopAllDogsThread( tDWORD* result ) = 0; // -- ������� ���������� ����� ��������� ���� ������� �������
		virtual tERROR pr_call AddInvisibleFile( tSTRING szFileName ) = 0; // -- ���������� ��������� �������� ��� ��� ���������
		virtual tERROR pr_call CreateIO( hOBJECT* result, hSTRING hObjectName ) = 0; // -- ������� IO �� ���������� �����
		virtual tERROR pr_call CopyConext( hOBJECT SourceObject, hOBJECT DestinationObject ) = 0; // -- ����������� ����������� ��������� �������� ��� ��������� ��������
	};

	struct pr_abstract cAVPG : public iAVPG, public iObj 
	{
		OBJ_IMPL( cAVPG );
		operator hOBJECT() { return (hOBJECT)this; }
		operator hAVPG()   { return (hAVPG)this; }

		tDWORD pr_call get_pgWorkingThreadMaxCount() { return (tDWORD)getDWord(pgWorkingThreadMaxCount); }
		tERROR pr_call set_pgWorkingThreadMaxCount( tDWORD value ) { return setDWord(pgWorkingThreadMaxCount,(tDWORD)value); }

		tDWORD pr_call get_pgDriverCacheSize() { return (tDWORD)getDWord(pgDriverCacheSize); }
		tERROR pr_call set_pgDriverCacheSize( tDWORD value ) { return setDWord(pgDriverCacheSize,(tDWORD)value); }

		tAVPG_CLIENT_ACTIVITY_MODE pr_call get_pgClientActivityMode() { tAVPG_CLIENT_ACTIVITY_MODE value = {0}; get(pgClientActivityMode,&value,sizeof(value)); return value; }
		tERROR pr_call set_pgClientActivityMode( tAVPG_CLIENT_ACTIVITY_MODE value ) { return set(pgClientActivityMode,&value,sizeof(value)); }

		tDWORD pr_call get_pgWorkingMode() { return (tDWORD)getDWord(pgWorkingMode); }
		tERROR pr_call set_pgWorkingMode( tDWORD value ) { return setDWord(pgWorkingMode,(tDWORD)value); }

	};

#endif // if defined (__cplusplus) && !defined(_USE_VTBL)
// AVP Prague stamp end



// AVP Prague stamp begin( Header endif,  )
#endif // __i_avpg__37b13221_ae7b_11d4_b757_00d0b7170e50
// AVP Prague stamp end



