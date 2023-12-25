// AVP Prague stamp begin( Interface header,  )
// -------- Friday,  27 July 2007,  12:46 --------
// File Name   -- (null)i_avpg2.cpp
// Copyright � Kaspersky Lab 1996-2006.
// -------------------------------------------
// AVP Prague stamp end



// AVP Prague stamp begin( Header ifndef,  )
#if !defined( __i_avpg2__a3e3c2f3_4379_4bb0_9c7d_190e3b9732c5 )
#define __i_avpg2__a3e3c2f3_4379_4bb0_9c7d_190e3b9732c5
// AVP Prague stamp end



// AVP Prague stamp begin( Header includes,  )
#include <Prague/pr_vtbl.h>
#include <Prague/iface/i_string.h>
// AVP Prague stamp end



// AVP Prague stamp begin( Interface comment,  )
// AVPG2 interface implementation
// Short comments -- �������� ���������� ��� �������������� � ���������-�������������
//    ������ 2 ���������� AVPG. ��������� ������������� ������ � �������� klif. ��������� �������� �� �������� ������� �������� ������� (��������/��������), ��������� �����, �� ������� ������ �������, � ���������/��������� ��� �������.
//
// AVP Prague stamp end



// AVP Prague stamp begin( Interface menonic identificator,  )
#define IID_AVPG2  ((tIID)(46002))
// AVP Prague stamp end



// AVP Prague stamp begin( Interface typedefs,  )
typedef tDWORD                         tAVPG2_CLIENT_ACTIVITY_MODE; // ����� ���������� �������
typedef tDWORD                         tAVPG2_PROCESS_OBJECT_RESULT_FLAGS; // ����� �������� ���������� ��������� �������
typedef tDWORD                         tAVPG2_WORKING_MODE; // ����� ������ ������������
// AVP Prague stamp end



// AVP Prague stamp begin( Interface constants,  )
#define cAVPG2_CLIENT_ACTIVITY_MODE_SLEEP ((tAVPG2_CLIENT_ACTIVITY_MODE)(0)) // ������� ��� ������� �� ������������ �������������
#define cAVPG2_CLIENT_ACTIVITY_MODE_ACTIVE ((tAVPG2_CLIENT_ACTIVITY_MODE)(1)) // ������ ������� � ������ ������������ ������� �� ��������� ���������� �������
#define cAVPG2_WORKING_MODE_ON_ACCESS  ((tAVPG2_WORKING_MODE)(0)) // �������� �������� � �������� �����
#define cAVPG2_WORKING_MODE_ON_MODIFY  ((tAVPG2_WORKING_MODE)(1)) // ���������������
#define cAVPG2_WORKING_MODE_ON_EXECUTE ((tAVPG2_WORKING_MODE)(2)) // �������� ������ �������� ������ �� ����������
#define cAVPG2_WORKING_MODE_ON_OPEN    ((tAVPG2_WORKING_MODE)(3)) // �������� ������ �������� �����
#define cAVPG2_WORKING_MODE_ON_SMART   ((tAVPG2_WORKING_MODE)(4)) // �������� ������ ������� �������� � ���������� ��������
#define cAVPG2_RC_ALLOW_ACCESS         ((tAVPG2_PROCESS_OBJECT_RESULT_FLAGS)(0x01)) // ��������� ���������� ��������� �������.
#define cAVPG2_RC_DENY_ACCESS          ((tAVPG2_PROCESS_OBJECT_RESULT_FLAGS)(0x02)) // ��������� ���������� ��������� �������
#define cAVPG2_RC_CACHE                ((tAVPG2_PROCESS_OBJECT_RESULT_FLAGS)(0x04)) // ������� ��������� ����������
#define cAVPG2_RC_DELETE_OBJECT        ((tAVPG2_PROCESS_OBJECT_RESULT_FLAGS)(0x08)) // ����� ��������� ������ �������
#define cAVPG2_RC_KILL_PROCESS         ((tAVPG2_PROCESS_OBJECT_RESULT_FLAGS)(0x10)) // ����� ��������� ���������� �������, ��������� �������
#define cAVPG2_PROP_CUSTOM_ORIGIN      ((tSTRING)("i_avpg2 custom origin")) // �������� ��� �������� Origin ��� ������� hString
#define cAVPG2_PROP_DOS_DEVICE_NAME    ((tSTRING)("i_avpg2 dos device name")) //  --
#define cAVPG2_PROP_USER_ACCESSED      ((tSTRING)("i_avpg2 User info")) // ��������� ������������, ���������� �������
#define cAVPG2_PROP_USER_CREATED       ((tSTRING)("i_avpg2 creator User info")) // ��������� ������������, ���������� �������
#define cAVPG2_PROP_PROCESS_ID         ((tSTRING)("i_avpg2 process id")) // ProcessID �������������� ��������
#define cAVPG2_PROP_BACKGROUND_PROCESSING ((tSTRING)("i_avpg2 this is background processing")) // �������� �� ������, ������� �� ��������� ������ � �������� �������
// AVP Prague stamp end



// AVP Prague stamp begin( Interface defined messages,  )

// message class
#define pmc_AVPG2 0x8a64093e //

	#define pm_AVPG2_PROCEED_OBJECT 0x00000101 // (257) -- ������ �� ��������� �������

	#define pm_AVPG2_NOTIFY_THREAD_STARTED 0x00000201 // (513) -- ������ ����� ������� �����

	#define pm_AVPG2_NOTIFY_THREAD_STOPPED 0x00000202 // (514) -- ������� ����� ����� ���������� ����� ��������� �����������

	#define pm_AVPG2_NOTIFY_DRIVER_CONNECTION_IS_BROKEN 0x00000203 // (515) -- ��������� ��� �� �����-���� ���������� �������� �������� ����� ��������� ������� �� ������������

	#define pm_AVPG2_NOTIFY_VOLUME_MOUNTED 0x00000204 // (516) -- �������� �������� ����������� ������ ����
// AVP Prague stamp end



// AVP Prague stamp begin( Interface defined errors,  )
// AVP Prague stamp end



// AVP Prague stamp begin( RPC start declaration,  )
#if defined( __RPC__ )
	typedef tUINT hAVPG2;
#else
// AVP Prague stamp end



// AVP Prague stamp begin( Interface forward declaration,  )
struct iAVPG2Vtbl;
typedef struct iAVPG2Vtbl iAVPG2Vtbl;
// AVP Prague stamp end



// AVP Prague stamp begin( Object declaration,  )
#if defined( __cplusplus ) && !defined(_USE_VTBL)
	struct cAVPG2;
	typedef cAVPG2* hAVPG2;
#else
	typedef struct tag_hAVPG2 
	{
		const iAVPG2Vtbl*  vtbl; // pointer to the "AVPG2" virtual table
		const iSYSTEMVtbl* sys;  // pointer to the "SYSTEM" virtual table
	} *hAVPG2;
#endif // if defined( __cplusplus )
// AVP Prague stamp end



// AVP Prague stamp begin( RPC_ end declaration,  )
#endif // if defined( __RPC__ )
// AVP Prague stamp end



// AVP Prague stamp begin( Private definitions begin,  )
#if !defined( AVPG2_PRIVATE_DEFINITION )
// AVP Prague stamp end



// AVP Prague stamp begin( Interface function forward declarations,  )


	typedef   tERROR (pr_call *fnpAVPG2_SetActivityMode)  ( hAVPG2 _this, tAVPG2_CLIENT_ACTIVITY_MODE ActivityMode ); // -- ��������� ������ ����������;
	typedef   tERROR (pr_call *fnpAVPG2_SetWorkingMode)   ( hAVPG2 _this, tAVPG2_WORKING_MODE WorkingMode ); // -- ��������� ������ ���������;
	typedef   tERROR (pr_call *fnpAVPG2_YieldEvent)       ( hAVPG2 _this, hOBJECT EventObject, tDWORD YieldTimeout ); // -- ������������� ��������� �������;
	typedef   tERROR (pr_call *fnpAVPG2_ResetDriverCache) ( hAVPG2 _this );                  // -- ������� ���� ��������;
	typedef   tERROR (pr_call *fnpAVPG2_CreateIO)         ( hAVPG2 _this, hOBJECT* phObject, hSTRING hObjectName ); // -- ������� IO �� ���������� �����;
	typedef   tERROR (pr_call *fnpAVPG2_SetPreverdict)    ( hAVPG2 _this, hOBJECT EventObject, tAVPG2_PROCESS_OBJECT_RESULT_FLAGS ResultFlags ); // -- ��������� �������� ��� �������� � ������ ��������� �������� ���������;
	typedef   tERROR (pr_call *fnpAVPG2_ResetBanList)     ( hAVPG2 _this );                  // -- ������� ���-����� �������������;
	typedef   tERROR (pr_call *fnpAVPG2_AddBan)           ( hAVPG2 _this, cSerializable* User ); // -- ���������� �������� ������������ � ���-���� �������������;


// AVP Prague stamp end



// AVP Prague stamp begin( Interface declaration,  )
struct iAVPG2Vtbl 
{
	fnpAVPG2_SetActivityMode   SetActivityMode;
	fnpAVPG2_SetWorkingMode    SetWorkingMode;
	fnpAVPG2_YieldEvent        YieldEvent;
	fnpAVPG2_ResetDriverCache  ResetDriverCache;
	fnpAVPG2_CreateIO          CreateIO;
	fnpAVPG2_SetPreverdict     SetPreverdict;
	fnpAVPG2_ResetBanList      ResetBanList;
	fnpAVPG2_AddBan            AddBan;
}; // "AVPG2" external virtual table prototype
// AVP Prague stamp end



// AVP Prague stamp begin( Private definitions end,  )
#endif // if !defined( AVPG2_PRIVATE_DEFINITION )
// AVP Prague stamp end



// AVP Prague stamp begin( Interface declared properties,  )
//! #define pgINTERFACE_VERSION     mPROPERTY_MAKE_GLOBAL( pTYPE_VERSION , 0x00000082 )
//! #define pgINTERFACE_COMMENT     mPROPERTY_MAKE_GLOBAL( pTYPE_STRING  , 0x00000083 )
#define pgWorkingThreadMaxCount mPROPERTY_MAKE_GLOBAL( pTYPE_DWORD   , 0x00001004 )
#define pgClientActivityMode    mPROPERTY_MAKE_GLOBAL( pTYPE_DWORD   , 0x00001006 )
#define pgWorkingMode           mPROPERTY_MAKE_GLOBAL( pTYPE_DWORD   , 0x00001007 )
// AVP Prague stamp end



// AVP Prague stamp begin( Defines to simplify interface method calls,  )
#if !defined( __cplusplus ) || defined(_USE_VTBL)
	#define CALL_AVPG2_SetActivityMode( _this, ActivityMode )                     ((_this)->vtbl->SetActivityMode( (_this), ActivityMode ))
	#define CALL_AVPG2_SetWorkingMode( _this, WorkingMode )                       ((_this)->vtbl->SetWorkingMode( (_this), WorkingMode ))
	#define CALL_AVPG2_YieldEvent( _this, EventObject, YieldTimeout )             ((_this)->vtbl->YieldEvent( (_this), EventObject, YieldTimeout ))
	#define CALL_AVPG2_ResetDriverCache( _this )                                  ((_this)->vtbl->ResetDriverCache( (_this) ))
	#define CALL_AVPG2_CreateIO( _this, phObject, hObjectName )                   ((_this)->vtbl->CreateIO( (_this), phObject, hObjectName ))
	#define CALL_AVPG2_SetPreverdict( _this, EventObject, ResultFlags )           ((_this)->vtbl->SetPreverdict( (_this), EventObject, ResultFlags ))
	#define CALL_AVPG2_ResetBanList( _this )                                      ((_this)->vtbl->ResetBanList( (_this) ))
	#define CALL_AVPG2_AddBan( _this, User )                                      ((_this)->vtbl->AddBan( (_this), User ))
#else // if !defined( __cplusplus )
	#define CALL_AVPG2_SetActivityMode( _this, ActivityMode )                     ((_this)->SetActivityMode( ActivityMode ))
	#define CALL_AVPG2_SetWorkingMode( _this, WorkingMode )                       ((_this)->SetWorkingMode( WorkingMode ))
	#define CALL_AVPG2_YieldEvent( _this, EventObject, YieldTimeout )             ((_this)->YieldEvent( EventObject, YieldTimeout ))
	#define CALL_AVPG2_ResetDriverCache( _this )                                  ((_this)->ResetDriverCache( ))
	#define CALL_AVPG2_CreateIO( _this, phObject, hObjectName )                   ((_this)->CreateIO( phObject, hObjectName ))
	#define CALL_AVPG2_SetPreverdict( _this, EventObject, ResultFlags )           ((_this)->SetPreverdict( EventObject, ResultFlags ))
	#define CALL_AVPG2_ResetBanList( _this )                                      ((_this)->ResetBanList( ))
	#define CALL_AVPG2_AddBan( _this, User )                                      ((_this)->AddBan( User ))
#endif // if !defined( __cplusplus )
// AVP Prague stamp end



// AVP Prague stamp begin( C++ interface declaration,  )
#if defined (__cplusplus) && !defined(_USE_VTBL)
	struct pr_abstract iAVPG2 
	{
		virtual tERROR pr_call SetActivityMode( tAVPG2_CLIENT_ACTIVITY_MODE ActivityMode ) = 0; // -- ��������� ������ ����������
		virtual tERROR pr_call SetWorkingMode( tAVPG2_WORKING_MODE WorkingMode ) = 0; // -- ��������� ������ ���������
		virtual tERROR pr_call YieldEvent( hOBJECT EventObject, tDWORD YieldTimeout ) = 0; // -- ������������� ��������� �������
		virtual tERROR pr_call ResetDriverCache() = 0; // -- ������� ���� ��������
		virtual tERROR pr_call CreateIO( hOBJECT* phObject, hSTRING hObjectName ) = 0; // -- ������� IO �� ���������� �����
		virtual tERROR pr_call SetPreverdict( hOBJECT EventObject, tAVPG2_PROCESS_OBJECT_RESULT_FLAGS ResultFlags ) = 0; // -- ��������� �������� ��� �������� � ������ ��������� �������� ���������
		virtual tERROR pr_call ResetBanList() = 0; // -- ������� ���-����� �������������
		virtual tERROR pr_call AddBan( cSerializable* User ) = 0; // -- ���������� �������� ������������ � ���-���� �������������
	};

	struct pr_abstract cAVPG2 : public iAVPG2, public iObj 
	{

		OBJ_IMPL( cAVPG2 );

		operator hOBJECT() { return (hOBJECT)this; }
		operator hAVPG2()   { return (hAVPG2)this; }

		tDWORD pr_call get_pgWorkingThreadMaxCount() { return (tDWORD)getDWord(pgWorkingThreadMaxCount); }
		tERROR pr_call set_pgWorkingThreadMaxCount( tDWORD value ) { return setDWord(pgWorkingThreadMaxCount,(tDWORD)value); }

		tAVPG2_CLIENT_ACTIVITY_MODE pr_call get_pgClientActivityMode() { tAVPG2_CLIENT_ACTIVITY_MODE value = {0}; get(pgClientActivityMode,&value,sizeof(value)); return value; }
		tERROR pr_call set_pgClientActivityMode( tAVPG2_CLIENT_ACTIVITY_MODE value ) { return set(pgClientActivityMode,&value,sizeof(value)); }

		tAVPG2_WORKING_MODE pr_call get_pgWorkingMode() { tAVPG2_WORKING_MODE value = {0}; get(pgWorkingMode,&value,sizeof(value)); return value; }
		tERROR pr_call set_pgWorkingMode( tAVPG2_WORKING_MODE value ) { return set(pgWorkingMode,&value,sizeof(value)); }

	};

#endif // if defined (__cplusplus) && !defined(_USE_VTBL)
// AVP Prague stamp end



// AVP Prague stamp begin( Header endif,  )
#endif // __i_avpg2__a3e3c2f3_4379_4bb0_9c7d_190e3b9732c5
// AVP Prague stamp end



