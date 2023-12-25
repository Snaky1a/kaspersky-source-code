// CodeGen.h : Declaration of the CCodeGen

#ifndef __SRCGEN_H_
#define __SRCGEN_H_

#include "resource.h"       // main symbols
#include "..\PCGInterface.h"
#include <ifaceinfo.h>
#include "Options.h"
#include <stuff\parray.h>


class ATL_NO_VTABLE CCodeGen;

/////////////////////////////////////////////////////////////////////////////
// CCodeGen
class ATL_NO_VTABLE CCodeGen : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCodeGen, &CLSID_PragueCodeGen>,
	public IPragueCodeGen
{

public:
	CCodeGen();
	~CCodeGen();

DECLARE_REGISTRY_RESOURCEID(IDR_SRCGEN)
DECLARE_NOT_AGGREGATABLE(CCodeGen)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCodeGen)
	COM_INTERFACE_ENTRY(IPragueCodeGen)
END_COM_MAP()

// IPragueCodeGen
public:
	STDMETHOD (GetDescription)                  ( BYTE** description );
	STDMETHOD (GetVendor)                       ( BYTE** vendor );
	STDMETHOD (GetVersion)                      ( BYTE** version );
	STDMETHOD (GetInfo)                         ( DWORD* len, BYTE** info );
	STDMETHOD (GetPrototypeOptionTemplate)      ( DWORD* len, BYTE** options );
	STDMETHOD (GetImplementationOptionTemplate) ( DWORD* len, BYTE** options );
	STDMETHOD (GetProjectOptions)               ( DWORD* len, BYTE** buffer );
	STDMETHOD (SetObjectTypes)                  ( DWORD len, BYTE* objtypes );
	STDMETHOD (StartProject)                    ( DWORD len, BYTE* buffer );
	STDMETHOD (EndProject)                      (  );
	STDMETHOD (PrototypeGenerate)               ( DWORD clen, BYTE* cont, DWORD olen, BYTE* options );
	STDMETHOD (ImplementationGenerate)          ( DWORD clen, BYTE* contents, DWORD olen, BYTE* options );
	STDMETHOD (EditNode)                        ( HWND dad, DWORD* len, BYTE** node );
	STDMETHOD (GetErrorString)                  ( HRESULT err, BYTE** err_str );

private:
  CStdTypeInfo m_types;
  CPluginInfo  m_plugin;
  CFaceInfo    m_iface;
	COptions     m_opt;
	
private:
	HRESULT     ExtractTemplate( UINT id, DWORD* len, BYTE** output );
	HRESULT     ExtractString( UINT id, BYTE** output );
  HRESULT     LoadContents( DWORD len, BYTE* contents );
  HRESULT     LoadOptions( DWORD len, BYTE* options );
};            

#endif //__SRCGEN_H_
