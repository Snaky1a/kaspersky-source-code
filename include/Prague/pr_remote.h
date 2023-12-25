// -------------------------------------------
/*!
 * (C) 2002 Kaspersky Lab 
 * 
 * \file	Remote.h
 * \author	Pavel Mezhuev
 * \date	05.12.2002 10:25:41
 * \brief	��������� ��� ���������� �������������� ���������.
 * 
 */
// -------------------------------------------

#ifndef __PR_REMOTE_H
#define __PR_REMOTE_H

#include <Prague/prague.h>
#include <Prague/pr_loadr.h>

#if defined (_WIN32)
#	ifdef DISTRIBUTED_PRODUCT_EXPORT
#		define PR_API EXTERN_C __declspec(dllexport)  
#	else
#		define PR_API EXTERN_C __declspec(dllimport) 
#   endif
#else
#   include <string.h>
#   include <stdio.h>
#	define PR_API EXTERN_C pr_call 
#endif


typedef tDWORD tSESSION;		// ���������� ������
typedef tDWORD tPROCESS;		// ���������� ��������
typedef tDWORD tLIBRARY;		// ���������� ����������

#define PID_REMOTE_PRAGUE	        ((tPID)12345)

#define PR_PROCESS_LOCAL			(tDWORD)(0)		// ���������������� ���������� �������� ��������
#define PR_PROCESS_ANY				(tDWORD)(-1)	// ���������������� ���������� ��� ������ ��������
#define PR_PROCESS_ALL				(tDWORD)(-2)	// ���������������� ����������
#define PR_PROCESS_ALL_IMPERSONATED	(tDWORD)(-3)	// ���������������� ����������

#define PR_SESSION_LOCAL			(tDWORD)(-1)	// ���������������� ���������� ��������� ������
#define PR_SESSION_ACTIVE			(tDWORD)(-2)	// ���������������� ���������� �������� ������
#define PR_SESSION_ALL			    (tDWORD)(-3)	// 
#define PR_SESSION_BY_USER_TOKEN	(tDWORD)(-4)	// ���������������� ���������� ��� ������ �� ������������ ������

#define PR_CREATE_IN_PARENTAL_PROCESS	  (tDWORD)(1)
#define PR_CREATE_IN_IMPERSONATED_PROCESS (tDWORD)(2)
#define PR_CREATE_IN_SPECIFIED_PROCESS    (tDWORD)(4)

#define IID_REMOTE_STUB		        0x81000000
#define IID_REMOTE_PROXY	        0x82000000
#define IID_REMOTE_ROOT		        0x83000000

#define PR_REMOTE_MODULE_NAME       "prremote.dll"
#define cpnPRAGUE_REMOTE_API        ((tSTRING)("cpnPRAGUE_REMOTE_API"))

#define pgPROXY_CREATE_REMOTE        mPROPERTY_MAKE_GLOBAL(pTYPE_BOOL, 0x000000ff)

// -------------------------------------------
// Local prague

#define PR_FLAG_DEFAULT					0x00000000
#define PR_FLAG_UNLOAD_LOADER		0x80000000

// ��� ������������� ����� ��� ������ � �������� � Low Integrity (�������� ������ IE7)
// ����� ���������� ���� ����. (�� ��� ������ ������������)
#define PR_FLAG_LOW_INTEGRITY_PROCESS 0x40000000

// ��� ����, ����� ����� �������� � �������� � Low Integrity, ���� (�������) ������� � 
// Medium ��� High Integrity ������ ��������� ���� ����. (�� ��� ������ ������������)
#define PR_FLAG_LOW_INTEGRITY_HELPER  0x20000000

typedef struct tag_PRInitParams
{
	tDSKMAppId* app_id;
	tPTR        ctx;
	tERROR (*init_clb)(hROOT root, tPTR ctx, tBOOL remote);
} PRInitParams;

/*!
  \brief ������������� ��������� �������������� Prague.
		���������� �������, ��� ������������� Prague � ������� ��������.
		���� ����� ��� ��� ������, �� ������ ���������� ������� ������.

    \param flags		  [in]  ����� �������������. 

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRInitialize(tDWORD flags, PRInitParams* params);

/*!
  \brief ���������� ������� ��� �������������� Prague.

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRDeinitialize();

/*!
  \brief �������� ������ �������� Prague.
	����� �������� ����� "PRInitialize".

    \param root           [out]  ������ ��������. 

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRGetRoot(hROOT *root);

/*!
  \brief ��������� ������ ��������.

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRStopServer();

/*!
  \brief ���������������� ������

    \param port			  [in]  ����� ����� ��� ����������. 

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRRegisterServer(tDWORD port);

/*!
  \brief ���������������� ������ ��� ����������� ��� �������������
	� ����� ���������� ��������.

    \param name			  [in]  ������������� �������. 
    \param object         [in]  �������������� ������. 

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRRegisterObject(tSTRING name, hOBJECT object);

/*!
  \brief ���������������� ������.

    \param object         [in]  ������������������ ������. 

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRUnregisterObject(hOBJECT object);

/*!
  \brief ���������������� ���������� � ������� �������� ������� �� pid-�.

    \param pid			  [in]  ������������� �������. 
    \param flags          [in]  ����� ��������. 
    \param process        [in]  ������� ��� ��������. 

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRRegisterCreationInfo(tPID pid, tDWORD flags, tPROCESS process, tSTRING exe_name);

PR_API tERROR PRUregisterCreationInfo(tPID pid);

/*!
  \brief ������� ������� � ��������� ������

    \param session_id     [in]  ������������� ������. 
    \param exec_path      [in]  ��� ����� ��� �������. 
    \param exec_args      [in]  ��������� ��� �������. 
    \param timeout        [in]  ������� �������� �������. 
    \param process        [out] ���������� ��������. 

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRCreateProcess(tSESSION session_id, tSTRING exec_path, tSTRING exec_args, tDWORD timeout, tBOOL child, tPROCESS *process);

/*!
  \brief ������ �� �������� ��������

    \param process        [in] ���������� ��������. 

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRCloseProcessRequest(tPROCESS process);

/*!
  \brief ������ �� �������� ��������

    \param process        [in] ���������� ��������. 

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PREstablishConnections(tSTRING name);

/*!
  \brief ������ �� �������� ��������

    \param process        [in] ���������� ��������. 

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRIsSystemProcess(tPROCESS process);

/*!
  \brief ������� �������-���� ��� ������� � ��������� ������

    \param session_id     [in]  ������������� ������. 
    \param exec_path      [in]  ��� ����� ��� �������. 
    \param exec_args      [in]  ��������� ��� �������. 
    \param object_name    [in]  ��� �������, ����������� �������� ����� ���������.
    \param timeout        [in]  ������� �������� �������. 
    \param process        [out] ������ �� ������. 

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRCreateObjectProxy(tSESSION session_id, tSTRING exec_path, tSTRING exec_args, tDWORD timeout, tSTRING object_name, hOBJECT *proxy);

/*!
  \brief ��������� �������� �������.

    \param process		  [in]  ���������� ��������. 
    \param object         [in]  ������������ ������. 
    \param new_obj		  [out] ��������� ������. � ������, ���� ������ ������ � ������ ��������, �� ��� ������ �� ������.
    \param iid			  [in]  ������������� ����������.
    \param pid			  [in]  ������������� �������.
    \param subtype		  [in]  ������ ����������.

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRCreateObject(tPROCESS process, hOBJECT object, hOBJECT* new_obj, tIID iid, tPID pid, tDWORD subtype);

PR_API tERROR PRCreateObjectQuick(tPROCESS process, hOBJECT object, hOBJECT* new_obj, tIID iid, tPID pid, tDWORD subtype);


// -------------------------------------------
// Remote prague

PR_API tERROR PRRegisterHost(tSTRING host, tDWORD port, tPROCESS *process);

/*!
  \brief �������� ������ �� ������ �������� � �������� ��������.

    \param process		  [in]  ���������� ��������. 
    \param root           [out] ������ ��������.

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRGetRootProxy(tPROCESS process, hROOT *root);

/*!
  \brief �������� ������ �� ������ � �������� ��������, � �������� ���������������.

    \param process		  [in]  ���������� ��������. 
    \param name			  [in]  ������������� �������. 
    \param object         [out] ���� ����� ���������� � ������ ��������,
									�� ������� Prague-object,
									����� ������ �� ������ � ������ ��������.

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRGetObjectProxy(tPROCESS process, tSTRING name, hOBJECT *object);

/*!
  \brief �������� ���������� ���������, � ������� ������ ������.

    \param object         [in] ������.
    \param process        [out] ������������ ���������� ��������.

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRGetObjectProcess(hOBJECT object, tPROCESS *process);

/*!
  \brief ���������� ������� ����� ������������� �������.

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRReleaseObjectProxy(hOBJECT object);


PR_API tERROR PRAddRefObjectProxy(hOBJECT object);

/*!
  \brief ��������� callback �� ������ ����������.

    \param object         [in] ������ �� ������.
    \param callback       [in] Callback �� ������ ����������.
    \param context        [in] �������� ������ callback'�.

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRSetRunDownCallback(hOBJECT object, void (*callback)(hOBJECT object, void *context), void *context);

/*!
  \brief ��������� �������� ������ �� ������.

    \param object         [in] ������ �� ������.

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRIsValidProxy(hOBJECT object);

// -------------------------------------------

typedef struct tag_PRRemoteAPI
{
	tERROR (pr_call *Initialize)(tDWORD flags, PRInitParams* params);
	tERROR (pr_call *Deinitialize)();
	tERROR (pr_call *GetRoot)(hROOT *root);

	tERROR (pr_call *StopServer)();
	tERROR (pr_call *RegisterServer)(tDWORD port);
	tERROR (pr_call *RegisterHost)(tSTRING host, tDWORD port, tPROCESS *process);
	tERROR (pr_call *RegisterObject)(tSTRING name, hOBJECT object);
	tERROR (pr_call *UnregisterObject)(hOBJECT object);

	tERROR (pr_call *CreateProcess)(tSESSION session_id, tSTRING exec_path, tSTRING exec_args, tDWORD timeout, tBOOL child, tPROCESS *process);
	tERROR (pr_call *CreateObjectProxy)(tSESSION session_id, tSTRING exec_path, tSTRING exec_args, tDWORD timeout, tSTRING object_name, hOBJECT *proxy);
	tERROR (pr_call *CloseProcessRequest)(tPROCESS process);

	tERROR (pr_call *CreateObject)(tPROCESS process, hOBJECT object, hOBJECT* new_obj, tIID iid, tPID pid, tDWORD subtype);
	tERROR (pr_call *CreateObjectQuick)(tPROCESS process, hOBJECT object, hOBJECT* new_obj, tIID iid, tPID pid, tDWORD subtype);

	tERROR (pr_call *GetRootProxy)(tPROCESS process, hROOT *root);
	tERROR (pr_call *GetObjectProxy)(tPROCESS process, tSTRING name, hOBJECT *object);
	tERROR (pr_call *GetObjectProcess)(hOBJECT object, tPROCESS *process);
	tERROR (pr_call *ReleaseObjectProxy)(hOBJECT object);
	tERROR (pr_call *AddRefObjectProxy)(hOBJECT object);
	tERROR (pr_call *SetRunDownCallback)(hOBJECT object, void (*callback)(hOBJECT object, void *context), void *context);
	tERROR (pr_call *IsValidProxy)(hOBJECT object);

	tERROR (pr_call *EstablishConnections)(tSTRING name);
	tERROR (pr_call *IsSystemProcess)(tPROCESS process);

	tERROR (pr_call *RegisterCreationInfo)(tPID pid, tDWORD flags, tPROCESS process, tSTRING exe_name);
	tERROR (pr_call *UregisterCreationInfo)(tPID pid);

	tERROR (pr_call *ImpersonateAsAdmin)(hOBJECT object);

	tPTR    dummy[7]; // for expandable architecture
} PRRemoteAPI;

/*!
  \brief �������� PRRemoteAPI.

    \param api         [out] PRRemoteAPI.

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR PRGetAPI(PRRemoteAPI *api);

// -------------------------------------------
// Remote library

/*!
  \brief �������� ���������� ���������� � �������� ��������.
	���� process=NULL, �� ������ ����� � ������� ��������.
	���� ���������� ��� ��������, �� ���������� ����� ��������� �� ���.

    \param process         [in]  ���������� ��������. 
    \param name           [in]  ������ �������� ����������. 
    \param library		  [out] ���������� ����������. 

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR RLGetLibrary(tPROCESS process, tSTRING name, tLIBRARY *library);

// �������� ���������������� �������
#define INVOKE_HANDLER	"InvokeHandler"

// �������� ������� ��� ������ "RLInvokeMethod"
typedef void (*PRInvokeHandler)(tDWORD method, void *param, tDWORD param_size);

/*!
  \brief ������� ����� INVOKE_HANDLER � �������� ����������.

    \param library		  [in]  ���������� ����������. 
    \param method         [in]  ������������� ������. 
    \param param          [in,out]  ��������� ������, ������ ���� ���������. 
    \param param_size     [in]  ������ ������ ����������. 

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR RLInvokeMethod(tLIBRARY library, tDWORD method, void *param, tDWORD param_size);

/*!
  \brief ���������� ������� ����� ������������� ����������.

    \param library		  [in]  ���������� ����������. 

    \return ��� �������� ���������� - errOK.
*/
PR_API tERROR RLReleaseLibrary(tLIBRARY library);


// -------------------------------------------
#if defined(__cplusplus)

#include "iface/i_root.h"

class CPRRemotePrague : public PRRemoteAPI
{
public:
#if defined (_WIN32)
	CPRRemotePrague(HINSTANCE hModule, tDWORD nFlags = 0) : m_root(NULL)
	{
		Init(hModule, nFlags);
	}
#else
	CPRRemotePrague(tDWORD nFlags, PRInitParams* params = NULL) : m_root(NULL) 
	{
		Init(nFlags);
	}
#endif
	~CPRRemotePrague()
	{
		Deinit();
	}

#if defined (_WIN32)
	tERROR Init(LPCSTR strPath, tDWORD nFlags = 0, PRInitParams* params = NULL)
	{
		m_hModule = LOAD_LIBRARY(strPath);
		if( !m_hModule )
			m_hModule = LOAD_LIBRARY(PR_REMOTE_MODULE_NAME);
		return InitRoot(nFlags, params);
	}


	tERROR Init(HINSTANCE hModule, tDWORD nFlags = 0, PRInitParams* params = NULL)
	{
		tCHAR szLoadPath[MAX_PATH];
		if (!GetModuleFileNameA(hModule, szLoadPath, sizeof(szLoadPath)))
			*szLoadPath = 0;
		tCHAR* pModuleName = strrchr(szLoadPath, '\\');
		if (!pModuleName)
			pModuleName = szLoadPath;
		else
			pModuleName++;
		strcpy_s(pModuleName, szLoadPath + countof(szLoadPath) - pModuleName, PR_REMOTE_MODULE_NAME);
		m_hModule = LOAD_LIBRARY(szLoadPath);

		if( !m_hModule )
			m_hModule = LOAD_LIBRARY(PR_REMOTE_MODULE_NAME);
		return InitRoot(nFlags, params);
	}

#else
	tERROR Init(tDWORD nFlags = 0, PRInitParams* params = NULL)
	{
		m_hModule = LOAD_LIBRARY("pr_remote." SHARED_EXT);
		return InitRoot(nFlags, params);
	}
#endif

	tERROR InitRoot(tDWORD nFlags = 0, PRInitParams* params = NULL)
	{
		if( !m_hModule )
			return m_err = errMODULE_NOT_FOUND;

		tERROR ( *hGetAPI )(PRRemoteAPI *api) = NULL;
		*(void**)&hGetAPI = GET_SYMBOL(m_hModule, "PRGetAPI");
		if( hGetAPI )
			m_err = hGetAPI(this);
		else
			Deinitialize = NULL;

		if( PR_SUCC(m_err) )
			m_err = Initialize(!nFlags ? PR_LOADER_FLAG_FORCE_PLUGIN_SEARCH : nFlags, params);
		if( PR_SUCC(m_err) )
			m_err = GetRoot(&m_root);
		if( PR_SUCC(m_err) )
			g_root = m_root;

		return m_err;
	}

	void Deinit()
	{
		if( m_hModule )
		{
			if( Deinitialize )
				Deinitialize();
//			UNLOAD_LIBRARY(m_hModule);
			m_hModule = NULL;
		}
	}

	CPRRemotePrague() : m_hModule(NULL), m_root(g_root)
	{
		if( !m_root )
			return;

		tPROPID nProp;
		m_err = CALL_Root_RegisterCustomPropId(m_root, &nProp, cpnPRAGUE_REMOTE_API, pTYPE_PTR);
		if( PR_SUCC(m_err) )
		{
			PRRemoteAPI* pAPI = NULL;
			tDWORD size = sizeof(pAPI);

			m_err = CALL_SYS_PropertyGet(m_root, &size, nProp, &pAPI, size);

			if( pAPI )
				memcpy(this, pAPI, sizeof(PRRemoteAPI));
			else
				m_err = errINTERFACE_NOT_FOUND;
		}
	}

	tERROR LoadProxyStub(tSTRING strModule)
	{
		if( PR_FAIL(m_err) ) return m_err;
		return CALL_Root_LoadModule(m_root, NULL, strModule, (tDWORD)strlen(strModule), cCP_ANSI);
	}

	tERROR GetError()          { return m_err; };
	operator hROOT() const     { return m_root; };
	hROOT operator ->() const  { return m_root; };

private:
#if defined (_WIN32)
	HMODULE   m_hModule;
#else
        void*     m_hModule;
#endif
	hROOT     m_root;
	tERROR    m_err;
};

template <class Type = hOBJECT>
class CPRRemoteProxy
{
public:
	CPRRemoteProxy(CPRRemotePrague& pPrague) :
		m_pPrague(pPrague),
		m_strProxyName(NULL),
		m_hProxyObj(NULL)
	{
	}
	
	CPRRemoteProxy(CPRRemotePrague& pPrague, tSTRING strProxyName) :
		m_pPrague(pPrague),
		m_strProxyName(NULL),
		m_hProxyObj(NULL)
	{
		Init(strProxyName);
	}

	bool Init(tSTRING strProxyName)
	{
		if (!(hROOT)m_pPrague)
			return false;
		tDWORD len = (tDWORD)strlen(strProxyName) + 1;
		if( PR_FAIL(CALL_SYS_ObjHeapAlloc((hROOT)m_pPrague, (tPTR*)&m_strProxyName, len)) )
			return false;
		memcpy(m_strProxyName, strProxyName, len);
		return true;
	}

	~CPRRemoteProxy()
	{
		if( m_strProxyName && (hROOT)m_pPrague )
			CALL_SYS_ObjHeapFree((hROOT)m_pPrague, m_strProxyName);
		Detach();
	}

	bool operator !() const { return !m_hProxyObj; }
	operator Type() const   { return m_hProxyObj; }
	operator bool() const   { return !!m_hProxyObj; }
	Type operator ->()      { return m_hProxyObj; }

	bool IsValid()
	{
		return m_hProxyObj && PR_SUCC(m_pPrague.IsValidProxy((hOBJECT)m_hProxyObj));
	}

	bool Attach()
	{
		Detach();
		if (!(hROOT)m_pPrague)
			return false;
		return PR_SUCC(m_pPrague.GetObjectProxy(PR_PROCESS_ANY, m_strProxyName, (hOBJECT*)&m_hProxyObj));
	}

	void Detach()
	{
		if( m_hProxyObj )
			m_pPrague.ReleaseObjectProxy((hOBJECT)m_hProxyObj);
		m_hProxyObj = NULL;
	}

	bool Refresh(bool* bCreated = NULL)
	{
		if( IsValid() )
		{
			if( bCreated ) *bCreated = false;
			return true;
		}
		if( Attach() )
		{
			if( bCreated ) *bCreated = true;
			return true;
		}
		return false;
	}

private:
	CPRRemotePrague& m_pPrague;
	tSTRING     m_strProxyName;
	Type        m_hProxyObj;
};

#endif // __cplusplus

// -------------------------------------------

#endif  // __PR_REMOTE_H
