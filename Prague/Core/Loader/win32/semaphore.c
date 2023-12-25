// AVP Prague stamp begin( Interface header,  )
// -------- ANSI C Code Generator 2.0 --------
// -------- Wednesday,  31 May 2006,  15:24 --------
// -------------------------------------------
// Copyright � Kaspersky Lab 1996-2005.
// -------------------------------------------
// Project     -- Prague
// Sub project -- Loader
// Purpose     -- Win32 plugin finder/loader
// Author      -- petrovitch
// File Name   -- semaphore.c
// Additional info
//    This implementation finds loadable prague plugins in disk folder
// -------------------------------------------
// AVP Prague stamp end

#if defined (_WIN32)

// AVP Prague stamp begin( Private definitions,  )
#define Semaphore_PRIVATE_DEFINITION
// AVP Prague stamp end



// AVP Prague stamp begin( Includes for interface,  )
#include <Prague/prague.h>
#include "sem.h"
// AVP Prague stamp end



#include "loader.h"
#include <Prague/iface/i_mutex.h>
#include <wincompat.h>
#if defined (_WIN32)
	#include <service/sa.h>
	#include <stdio.h>
#else
	#include <unix/sa.h>
#endif

#define IMPEX_EXPORT_LIB
#include <Prague/iface/e_loader.h>

#define SEMAPHORE_PREFIX_A      "se_"
#define SEMAPHORE_PREFIX_A_SIZE	(sizeof(SEMAPHORE_PREFIX_A)-sizeof(tCHAR))


// AVP Prague stamp begin( Interface comment,  )
// Semaphore interface implementation
// Short comments -- Semaphore behaviour
// AVP Prague stamp end



// AVP Prague stamp begin( Data structure,  )
// Interface Semaphore. Inner data structure

typedef struct tag_SemData {
	HANDLE handle;     // handle of the Windows object
	tCHAR* name;       // name of the object
	tBOOL  open;       // do not try to create
	tDWORD count;      // band width
	tDWORD init_count; // initial semaphore count
	tDWORD curr_count; // current semaphore count
	tDWORD last_error; // last win error
	tBOOL  global;     // --
	tDWORD name_len;   // --
} SemData;

// AVP Prague stamp end



// AVP Prague stamp begin( Object declaration,  )

typedef struct tag_hi_Semaphore {
	const iSemaphoreVtbl* vtbl; // pointer to the "Semaphore" virtual table
	const iSYSTEMVTBL*    sys;  // pointer to the "SYSTEM" virtual table
	SemData*              data; // pointer to the "Semaphore" data structure
} *hi_Semaphore;

// AVP Prague stamp end



// AVP Prague stamp begin( Internal method table prototypes,  )
// AVP Prague stamp end



// AVP Prague stamp begin( Internal method table prototypes,  )
tERROR pr_call Semaphore_ObjectInitDone( hi_Semaphore _this );
tERROR pr_call Semaphore_ObjectClose( hi_Semaphore _this );
// AVP Prague stamp end



// AVP Prague stamp begin( Internal method table,  )
static iINTERNAL i_Semaphore_vtbl = {
	(tIntFnRecognize)         NULL,
	(tIntFnObjectNew)         NULL,
	(tIntFnObjectInit)        NULL,
	(tIntFnObjectInitDone)    Semaphore_ObjectInitDone,
	(tIntFnObjectCheck)       NULL,
	(tIntFnObjectPreClose)    NULL,
	(tIntFnObjectClose)       Semaphore_ObjectClose,
	(tIntFnChildNew)          NULL,
	(tIntFnChildInitDone)     NULL,
	(tIntFnChildClose)        NULL,
	(tIntFnMsgReceive)        NULL,
	(tIntFnIFaceTransfer)     NULL
};
// AVP Prague stamp end



// AVP Prague stamp begin( Interface function forward declarations,  )
typedef   tERROR (pr_call *fnpSemaphore_Lock)      ( hi_Semaphore _this, tDWORD timeout );     // -- locks synchronization object;
typedef   tERROR (pr_call *fnpSemaphore_Release)   ( hi_Semaphore _this );                     // -- unlocks synchronization object;
typedef   tERROR (pr_call *fnpSemaphore_ReleaseEx) ( hi_Semaphore _this, tDWORD count );       // -- unlocks synchronization object by indicated count;
// AVP Prague stamp end



// AVP Prague stamp begin( Interface declaration,  )
struct iSemaphoreVtbl {
	fnpSemaphore_Lock       Lock;
	fnpSemaphore_Release    Release;
	fnpSemaphore_ReleaseEx  ReleaseEx;
}; // "Semaphore" external virtual table prototype
// AVP Prague stamp end



// AVP Prague stamp begin( External method table prototypes,  )
tERROR pr_call Semaphore_Lock( hi_Semaphore _this, tDWORD p_timeout );
tERROR pr_call Semaphore_Release( hi_Semaphore _this );
tERROR pr_call Semaphore_ReleaseEx( hi_Semaphore _this, tDWORD p_count );
// AVP Prague stamp end



// AVP Prague stamp begin( External method table,  )
static iSemaphoreVtbl e_Semaphore_vtbl = {
	(fnpSemaphore_Lock)       Semaphore_Lock,
	(fnpSemaphore_Release)    Semaphore_Release,
	(fnpSemaphore_ReleaseEx)  Semaphore_ReleaseEx
};
// AVP Prague stamp end



// AVP Prague stamp begin( Forwarded property methods declarations,  )
tERROR pr_call Semaphore_PROP_get_name( hi_Semaphore _this, tDWORD* out_size, tPROPID prop, tCHAR* buffer, tDWORD size );
tERROR pr_call Semaphore_PROP_set_name( hi_Semaphore _this, tDWORD* out_size, tPROPID prop, tCHAR* buffer, tDWORD size );
// AVP Prague stamp end



// AVP Prague stamp begin( Global property variable declaration,  )
// Interface "Semaphore". Static(shared) property table variables
// AVP Prague stamp end



// AVP Prague stamp begin( Interface version,  )
#define Semaphore_VERSION ((tVERSION)1)
// AVP Prague stamp end



// AVP Prague stamp begin( Header includes,  )
#include <Prague/prague.h>
#include <Prague/iface/i_mutex.h>
#include <Prague/iface/i_root.h>
#include <Prague/plugin/p_win32loader.h>

#include <windows.h>
// AVP Prague stamp end



// AVP Prague stamp begin( Property table,  )
mPROPERTY_TABLE(Semaphore_PropTable)
	mSHARED_PROPERTY( pgINTERFACE_VERSION, Semaphore_VERSION )
	mSHARED_PROPERTY_PTR( pgINTERFACE_COMMENT, "semaphore synchronization object", 33 )
	mLOCAL_PROPERTY_WRITABLE_OI_FN( pgOBJECT_NAME, Semaphore_PROP_get_name, Semaphore_PROP_set_name )
	mLOCAL_PROPERTY_BUF( pgJUST_OPEN, SemData, open, cPROP_BUFFER_READ_WRITE | cPROP_WRITABLE_ON_INIT )
	mLOCAL_PROPERTY_BUF( pgBAND_WIDTH, SemData, count, cPROP_BUFFER_READ_WRITE | cPROP_WRITABLE_ON_INIT )
	mLOCAL_PROPERTY_BUF( pgINITIAL_COUNT, SemData, init_count, cPROP_BUFFER_WRITE | cPROP_WRITABLE_ON_INIT )
	mLOCAL_PROPERTY_BUF( pgCURRENT_COUNT, SemData, curr_count, cPROP_BUFFER_READ )
	mLOCAL_PROPERTY_BUF( pgLAST_OS_ERROR, SemData, last_error, cPROP_BUFFER_READ )
	mLOCAL_PROPERTY_BUF( pgGLOBAL, SemData, global, cPROP_BUFFER_READ_WRITE | cPROP_WRITABLE_ON_INIT )
mPROPERTY_TABLE_END(Semaphore_PropTable)
// AVP Prague stamp end



// AVP Prague stamp begin( Registration call,  )
// Interface "Semaphore". Register function
tERROR pr_call Semaphore_Register( hROOT root ) {
	tERROR error;

	PR_TRACE_A0( root, "Enter \"Semaphore::Register\" method" );

	error = CALL_Root_RegisterIFace(
		root,                                   // root object
		IID_SEMAPHORE,                          // interface identifier
		PID_WIN32LOADER,                        // plugin identifier
		0x00000000,                             // subtype identifier
		Semaphore_VERSION,                      // interface version
		VID_PETROVITCH,                         // interface developer
		&i_Semaphore_vtbl,                      // internal(kernel called) function table
		(sizeof(i_Semaphore_vtbl)/sizeof(tPTR)),// internal function table size
		&e_Semaphore_vtbl,                      // external function table
		(sizeof(e_Semaphore_vtbl)/sizeof(tPTR)),// external function table size
		Semaphore_PropTable,                    // property table
		mPROPERTY_TABLE_SIZE(Semaphore_PropTable),// property table size
		sizeof(SemData),                        // memory size
		IFACE_SYSTEM                            // interface flags
	);

	#ifdef _PRAGUE_TRACE_
		if ( PR_FAIL(error) )
			PR_TRACE( (root,prtDANGER,"ldr\tSemaphore(IID_SEMAPHORE) registered [%terr]",error) );
	#endif // _PRAGUE_TRACE_

	PR_TRACE_A1( root, "Leave \"Semaphore::Register\" method, ret %terr", error );
	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( Property method implementation, get_name )
// Interface "Semaphore". Method "Get" for property(s):
//  -- OBJECT_NAME
tERROR pr_call Semaphore_PROP_get_name( hi_Semaphore _this, tDWORD* out_size, tPROPID prop, tCHAR* buffer, tDWORD size ) {
	SemData* d;
	tERROR error = errOK;
	PR_TRACE_A0( _this, "Enter *GET* method get_name for property pgOBJECT_NAME" );
	
	d = _this->data;
	
	if ( d->name )
		*out_size = (tDWORD)strlen( d->name ) + 1;
	else
		*out_size = 1;

	if ( buffer ) {
		if ( size < *out_size )
			error = errBUFFER_TOO_SMALL;
		else if ( d->name )
			memcpy( buffer, d->name, *out_size );
		else
			*(tCHAR*)buffer = 0;
	}
	
	PR_TRACE_A2( _this, "Leave *GET* method get_name for property pgOBJECT_NAME, ret tDWORD = %u(size), %terr", *out_size, error );
	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( Property method implementation, set_name )
// Interface "Semaphore". Method "Set" for property(s):
//  -- OBJECT_NAME
tERROR pr_call Semaphore_PROP_set_name( hi_Semaphore _this, tDWORD* out_size, tPROPID prop, tCHAR* buffer, tDWORD size ) {
	tDWORD len;
	tERROR error = errOK;
	PR_TRACE_A0( _this, "Enter *SET* method set_name for property pgOBJECT_NAME" );

	len = 0;
	if ( !buffer != !size )
		error = errPARAMETER_INVALID;
	
	else {
		HANDLE heap = GetProcessHeap();
		SemData* d = _this->data;
		if ( buffer ) {
			for( ; len<size && buffer[len]; len++ )
				;
		}
		if ( d->name ) {
			HeapFree( heap, 0, d->name );
			d->name = 0;
		}
		if ( len ) {
			d->name_len = len + KL_MAX_PREFIX_A_SIZE + SEMAPHORE_PREFIX_A_SIZE + sizeof(tCHAR);
			d->name = HeapAlloc( heap, HEAP_ZERO_MEMORY, d->name_len );
			if ( d->name ) {
				memcpy( d->name, buffer, len );
				error = errOK;
			}
			else
				error = errNOT_ENOUGH_MEMORY;
		}
		else
			error = errOK;
	}

	*out_size = len;

	PR_TRACE_A2( _this, "Leave *SET* method set_name for property pgOBJECT_NAME, ret tDWORD = %u(size), %terr", *out_size, error );
	return error;
}
// AVP Prague stamp end




// AVP Prague stamp begin( Internal (kernel called) interface method implementation, ObjectInitDone )
// Extended method comment
//  Notification that all necessary properties have been set and object must go to operation state
// Result comment
//  Returns value differ from errOK if object cannot function properly
// Parameters are:
tERROR pr_call Semaphore_ObjectInitDone( hi_Semaphore _this ) {
	SemData* d;
	tERROR error;
	PR_TRACE_A0( _this, "Enter \"Semaphore::ObjectInitDone\" method" );

	d = _this->data;
	d->last_error = 0;

	#if defined(_DEBUG)
		if ( !d->name ) {
			d->name_len = KL_MAX_PREFIX_A_SIZE + SEMAPHORE_PREFIX_A_SIZE + 20;
			d->name = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, d->name_len );
			PrMakeUniqueString( d->name, d->name_len, 0 );
		}
	#endif

	if ( d->name && *d->name && !g_NObj.inited )
		PrMakeNamePrefixed( d->name, d->name_len, d->global, SEMAPHORE_PREFIX_A );

	if ( !d->count )
		d->init_count = d->count = 1;
	else if ( d->init_count > d->count )
		d->init_count = d->count;

	if ( d->open )
		d->handle = PrOpenSemaphore( SEMAPHORE_ALL_ACCESS, FALSE, d->name );
	else {
		HSA hSecure = 0;
		if ( g_bUnderNT )
			hSecure = SA_Create( SA_AUTHORITY_EVERYONE, SA_ACCESS_MASK_ALL );

		d->handle = PrCreateSemaphore( SA_Get(hSecure), d->init_count, d->count, d->name );

		if( hSecure )
			SA_Destroy(hSecure);
	}

	if ( d->handle )
		error = errOK;
	else {
		d->last_error = GetLastError();
		error=errOBJECT_NOT_INITIALIZED;
	}

	PR_TRACE_A1( _this, "Leave \"Semaphore::ObjectInitDone\" method, ret %terr", error );
	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( Internal (kernel called) interface method implementation, ObjectClose )
// Extended method comment
//  Kernel warns object it must be closed
// Behaviour comment
//  Object takes all necessary "before closing" actions
// Parameters are:
tERROR pr_call Semaphore_ObjectClose( hi_Semaphore _this ) {

	SemData* d;
	PR_TRACE_A0( _this, "Enter \"Semaphore::ObjectClose\" method" );

	d = _this->data;
	d->last_error = 0;
	if ( d->handle ) {
		CloseHandle( d->handle );
		d->handle = 0;
	}
	if ( d->name ) {
		HeapFree( GetProcessHeap(), 0, d->name );
		d->name = 0;
	}
	
	PR_TRACE_A0( _this, "Leave \"Semaphore::ObjectClose\" method, ret tERROR = errOK" );
	return errOK;
}
// AVP Prague stamp end



// AVP Prague stamp begin( External (user called) interface method implementation, Lock )
// Parameters are:
tERROR pr_call Semaphore_Lock( hi_Semaphore _this, tDWORD timeout ) {
	SemData* d;
	tERROR error;
	PR_TRACE_A0( _this, "Enter \"Semaphore::Lock\" method" );

	d = _this->data;
	d->last_error = 0;
	if ( d->handle ) {
		d->last_error = WaitForSingleObject( d->handle, timeout );
		switch( d->last_error ) {
			case WAIT_OBJECT_0  : error = errOK;             break;
			case WAIT_ABANDONED : error = errABANDONED;      break;
			case WAIT_TIMEOUT   : error = errTIMEOUT;        break;
			default             : error = errUNEXPECTED;     break;
		}
	}
	else
		error = errOBJECT_NOT_INITIALIZED;
	
	//	if ( PR_FAIL(error) )
	//		CALL_SYS_ErrorCodeSet( _this, error );

	PR_TRACE_A1( _this, "Leave \"Semaphore::Lock\" method, ret %terr", error );
	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( External (user called) interface method implementation, Release )
// Parameters are:
tERROR pr_call Semaphore_Release( hi_Semaphore _this ) {
	SemData* d;
	tERROR error;
	PR_TRACE_A0( _this, "Enter \"Semaphore::Release\" method" );

	d = _this->data;
	if ( !d->handle ) {
		error = errOBJECT_NOT_INITIALIZED;
		d->last_error = 0;
	}
	else if ( !ReleaseSemaphore(d->handle,1,(LONG*)&d->curr_count) ) {
		error = errUNEXPECTED;
//		d->last_error = GetLastError();
	}
	else {
		error = errOK;
//		d->last_error = 0;
	}
	
	//	if ( PR_FAIL(error) )
	//		CALL_SYS_ErrorCodeSet( _this, error );
	PR_TRACE_A1( _this, "Leave \"Semaphore::Release\" method, ret %terr", error );
	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( External (user called) interface method implementation, ReleaseEx )
// Parameters are:
tERROR pr_call Semaphore_ReleaseEx( hi_Semaphore _this, tDWORD count ) {
	SemData* d;
	tERROR error;
	PR_TRACE_A0( _this, "Enter \"Semaphore::ReleaseEx\" method" );

	d = _this->data;
	if ( !d->handle ) {
		error = errOBJECT_NOT_INITIALIZED;
		d->last_error = 0;
	}
	else if ( !ReleaseSemaphore(d->handle,count,(LONG*)&d->curr_count) ) {
		error = errUNEXPECTED;
//		d->last_error = GetLastError();
	}
	else {
		error = errOK;
//		d->last_error = 0;
	}
	
	//	if ( PR_FAIL(error) )
	//		CALL_SYS_ErrorCodeSet( _this, error );
	PR_TRACE_A1( _this, "Leave \"Semaphore::ReleaseEx\" method, ret %terr", error );
	return error;
}
// AVP Prague stamp end


#endif //_WIN32
