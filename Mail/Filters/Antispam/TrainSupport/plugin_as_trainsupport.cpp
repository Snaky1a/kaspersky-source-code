// AVP Prague stamp begin( Interface header,  )
// -------- ANSI C++ Code Generator 1.0 --------
// -------- Tuesday,  25 September 2007,  15:40 --------
// -------------------------------------------
// Copyright � Kaspersky Lab 1996-2006.
// -------------------------------------------
// Project     -- Not defined
// Sub project -- Not defined
// Purpose     -- Not defined
// Author      -- Denisov
// File Name   -- plugin_as_trainsupport.cpp
// -------------------------------------------
// AVP Prague stamp end



// AVP Prague stamp begin( Header includes,  )
#include <Prague/prague.h>
#include <Prague/iface/i_root.h>
// AVP Prague stamp end



// AVP Prague stamp begin( Plugin extern and export declaration,  )
extern tERROR pr_call AS_TrainSupport_Register( hROOT root );
extern tERROR pr_call AddressBookExtractor_Register( hROOT root );

// AVP Prague stamp end



// AVP Prague stamp begin( Plugin definitions,  )
PR_MAKE_TRACE_FUNC;

hROOT  g_root = NULL;

tBOOL __stdcall DllMain( tPTR hInstance, tDWORD dwReason, tERROR* pError ) {
	// tDWORD count;

	switch( dwReason ) {
		case DLL_PROCESS_ATTACH:
		case DLL_PROCESS_DETACH:
		case DLL_THREAD_ATTACH :
		case DLL_THREAD_DETACH :
			break;

		case PRAGUE_PLUGIN_LOAD :
			g_root = (hROOT)hInstance;
			*pError = errOK;
			//resolve  my imports
			//if ( PR_FAIL(*pError=CALL_Root_ResolveImportTable(g_root,&count,import_table_variable...,PID_AS_TRAINSUPPORT)) ) {
			//   PR_TRACE(( g_root, prtERROR, "cannot resolve import table for ..." ));
			//   return cFALSE;
			//}

			//register my exports
			//CALL_Root_RegisterExportTable( g_root, &count, export_table_..., PID_AS_TRAINSUPPORT );

			//register my custom property ids
			//if ( PR_FAIL(*pError=CALL_Root_RegisterCustomPropId(g_root,&some_propid_variable,"some_property_name",pTYPE_DWORD)) ) {
			//  PR_TRACE(( g_root, prtERROR, "cannot register custom property ..." ));
			//  return cFALSE;
			//}

			// register my interfaces
			if ( PR_FAIL(*pError=AS_TrainSupport_Register(g_root)) ) {
				PR_TRACE(( g_root, prtERROR, "cannot register \"AS_TrainSupport\" interface"));
				return cFALSE;
			}
			
			if ( PR_FAIL(*pError=AddressBookExtractor_Register(g_root)) ) {
				PR_TRACE(( g_root, prtERROR, "cannot register \"AddressBookExtractor\" interface"));
				return cFALSE;
			}
			break;

		case PRAGUE_PLUGIN_UNLOAD :
			// free system resources
			// unregister my custom property ids -- you can drop it, kernel do it by itself
			// release    my imports		         -- you can drop it, kernel do it by itself
			// unregister my exports		         -- you can drop it, kernel do it by itself
			// unregister my interfaces          -- you can drop it, kernel do it by itself
			g_root = NULL;
			break;
	}
	return cTRUE;
}
// AVP Prague stamp end



