// IDServer.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To merge the proxy/stub code into the object DLL, add the file 
//      dlldatax.c to the project.  Make sure precompiled headers 
//      are turned off for this file, and add _MERGE_PROXYSTUB to the 
//      defines for the project.  
//
//      If you are not running WinNT4.0 or Win95 with DCOM, then you
//      need to remove the following define from dlldatax.c
//      #define _WIN32_WINNT 0x0400
//
//      Further, if you are running MIDL without /Oicf switch, you also 
//      need to remove the following define from dlldatax.c.
//      #define USE_STUBLESS_PROXY
//
//      Modify the custom build rule for IDServer.idl by adding the following 
//      files to the Outputs.
//          IDServer_p.c
//          dlldata.c
//      To build a separate proxy/stub DLL, 
//      run nmake -f IDServerps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"

#include <datatreeutils/dtutils.h>
#include <property/property.h>

#include <initguid.h>
#include "..\IDServerInterface.h"
#include "dlldatax.h"

#include "IDServer_i.c"
#include "PragueIDServer.h"

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

#include "RegisterDlg.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_PragueIDServer, CPragueIDServer)
END_OBJECT_MAP()

class CIDServerApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIDServerApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CIDServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CIDServerApp, CWinApp)
	//{{AFX_MSG_MAP(CIDServerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CIDServerApp theApp;

BOOL CIDServerApp::InitInstance()
{
#ifdef _MERGE_PROXYSTUB
    hProxyDll = m_hInstance;
#endif
    _Module.Init(ObjectMap, m_hInstance, &LIBID_IDSERVERLib);

		::DTUT_Init_Library( malloc, free );
		::DATA_Init_Library( malloc, free );

    return CWinApp::InitInstance();
}

int CIDServerApp::ExitInstance()
{
    _Module.Term();
    return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
    if (PrxDllCanUnloadNow() != S_OK)
        return S_FALSE;
#endif
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
    if (PrxDllGetClassObject(rclsid, riid, ppv) == S_OK)
        return S_OK;
#endif
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	SCODE bResult = CRegistryIdServer::PerformRegister() ? S_OK : SELFREG_E_CLASS;
	if ( bResult == S_OK ) {
#ifdef _MERGE_PROXYSTUB
		HRESULT hRes = PrxDllRegisterServer();
		if (FAILED(hRes))
				return hRes;
#endif
		// registers object, typelib and all interfaces in typelib
		return _Module.RegisterServer(TRUE);
	}
	return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
    PrxDllUnregisterServer();
#endif
    return _Module.UnregisterServer(TRUE);
}


