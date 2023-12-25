////////////////////////////////////////////////////////////////////
//
//  OCXStd.h
//  AVP ActiveX standard code implementation
//  AVP ActiveX stuff
//  Victor Matiouchenkov [victor@avp.ru], Kaspersky Labs. 1999
//  Copyright (c) Kaspersky Labs
//
////////////////////////////////////////////////////////////////////
#ifndef __OCXSTD_H__
#define __OCXSTD_H__

#include <Stuff\PArray.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define IMPLEMENT_ALLOCATION																									\
																																							\
static void *OCXMalloc( size_t size ) {																				\
	void *pAlloc = malloc( size );																							\
	if ( !pAlloc )																															\
		THROW(new CMemoryException());																						\
	return pAlloc;																															\
}																																							\
																																							\
static void OCXFree( void *pointer ) {																				\
	free( pointer );																														\
}																																							\

//////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
��������� ��������� ��������� WM_HELP.
���������� :
��������� WM_HELP �������� � ����, � ������� �������� ������ � ��������, ����� SendMessage.
���������� CWnd::OnHelpInfo (wincore.cpp) ��������� ����� ���� �, ���� �� �� WS_CHILD,
��� �������� ��������� � ������� Help � ������� ���� ����������. � ��������� ������
��������� ��������� ������ �� ���� ���������.
������, ���� �� OCX ������� "�������", �� ��� ������ ������ � ���� subclass-����
�, �����������, ������ �������� ����������� ���������� ��� ���������. ��� ���������.
��� ���� ��� ���������� ����� � ������ COleControlSite. ��� ���� ���������.
�� COleControlSite �������� ��� ����� ���� ������ �� WS_BORDER | WS_TABSTOP � ���������
� ����� ���������� ����������. � ���������� �� �� ��������� �������� ��� ����������
� ��� ������� ������ �������� �� ���������. ��� ���� ���������.
�� ������ ��� ���������� �����������. CWnd ���������� ����� � COleControlSite, � � ����
�� ���������� WS_CHILD!
������ ����������� ������� ��������� VK_MENU, ��� �� ��������� CWnd ��������� ���� ���������
(��. Wincore.cpp::CWnd::OnHelpInfo).
*/


#define IMPLEMENT_HELPMSG_HOOKCODE																						\
																																							\
static UINT						g_nEnterHelpMode = ::RegisterWindowMessage( _T("AvpOCXEnterHelpMode") ); \
static CCriticalSection g_TlsCritSect;																				\
static DWORD g_TlsIndex = 0xFFFFFFFF;																					\
static DWORD g_TlsCount = 0;																									\
																																							\
																																							\
struct CHelpTlsStruct {																												\
	HHOOK					m_hHelpMsgHook;																								\
	CPArray<CWnd>	m_pHelpMsgWnd;																								\
	bool					m_bHelpMsgHookProcessing;																			\
	bool					m_bHelpMsgHooked;																							\
	CHelpTlsStruct();																														\
};																																						\
																																							\
CHelpTlsStruct::CHelpTlsStruct() :																						\
	m_pHelpMsgWnd(0, 1, false) {																								\
	m_hHelpMsgHook = 0;																													\
	m_bHelpMsgHookProcessing = false;																						\
	m_bHelpMsgHooked = false;																										\
}																																							\
																																							\
static BOOL InitContext() {																										\
	CCriticalSection::CLock lock( g_TlsCritSect );															\
																																							\
	if ( g_TlsIndex == 0xFFFFFFFF )																							\
		g_TlsIndex = ::TlsAlloc();																								\
																																							\
	if ( g_TlsIndex == 0xFFFFFFFF ) {																						\
		return FALSE;																															\
	}																																						\
																																							\
	return TRUE;																																\
}																																							\
																																							\
static CHelpTlsStruct *SetContext() {																					\
	CCriticalSection::CLock lock( g_TlsCritSect );															\
																																							\
	CHelpTlsStruct *pTls = new CHelpTlsStruct();																\
	if ( !::TlsSetValue(g_TlsIndex, pTls) ) {																		\
		::TlsFree( g_TlsIndex );																									\
		g_TlsIndex = 0xFFFFFFFF;																									\
		g_TlsCount = 0;																														\
																																							\
		delete pTls;																															\
		return NULL;																															\
	}																																						\
																																							\
	g_TlsCount++;																																\
																																							\
	return pTls;																																\
}																																							\
																																							\
																																							\
static CHelpTlsStruct *GetContext() {																					\
	if ( g_TlsIndex != 0xFFFFFFFF || InitContext() ) {													\
		CHelpTlsStruct *pTls = (CHelpTlsStruct *)::TlsGetValue( g_TlsIndex ); 		\
		if ( !pTls )																															\
			pTls = ::SetContext();																									\
		return pTls;																															\
	}																																						\
	return NULL;																																\
}																																							\
																																							\
																																							\
static void RemoveContext() {																									\
	CHelpTlsStruct *pTls = ::GetContext();																			\
	if ( pTls ) {																																\
		delete pTls;																															\
		::TlsSetValue( g_TlsIndex, 0 );																						\
																																							\
		{																																					\
			CCriticalSection::CLock lock( g_TlsCritSect );													\
			if ( g_TlsCount )																												\
				g_TlsCount--;																													\
																																							\
			if ( !g_TlsCount ) {																										\
				::TlsFree( g_TlsIndex );																							\
				g_TlsIndex = 0xFFFFFFFF;																							\
			}																																				\
		}																																					\
	}																																						\
}																																							\
																																							\
																																							\
																																							\
LRESULT CALLBACK CallWndProc( int nCode, WPARAM wParam,  LPARAM lParam ) {		\
	CHelpTlsStruct *pTls = ::GetContext();																			\
	if ( pTls ) {																																\
		if ( nCode == HC_ACTION && !pTls->m_bHelpMsgHookProcessing ) {						\
			pTls->m_bHelpMsgHookProcessing = true;																	\
    																																					\
			CWPSTRUCT *msg = (CWPSTRUCT *)lParam;																		\
			if ( msg->message == WM_SYSCOMMAND ) {																	\
				for ( int i=0,c=pTls->m_pHelpMsgWnd.Count(); i<c; i++ ) {							\
					::SendMessage( pTls->m_pHelpMsgWnd[i]->GetSafeHwnd(), 							\
												 g_nEnterHelpMode, 																		\
												 WPARAM(msg->wParam == SC_CONTEXTHELP), 0 );					\
				}																																			\
			}																																				\
																																							\
			if ( msg->message == WM_HELP ) {																				\
				for ( int i=0,c=pTls->m_pHelpMsgWnd.Count(); i<c; i++ ) {							\
					if ( pTls->m_pHelpMsgWnd[i]->GetSafeHwnd() == msg->hwnd &&					\
							 ::IsWindowVisible(msg->hwnd) ) {																\
						HWND hWndParent = ::GetParent( msg->hwnd );												\
						if ( hWndParent ) {																								\
							BYTE pbKeyState[256];																						\
							::GetKeyboardState((LPBYTE) &pbKeyState);												\
							pbKeyState[VK_MENU] |= 0x80;																		\
							::SetKeyboardState((LPBYTE) &pbKeyState);												\
							pTls->m_bHelpMsgHooked = true;																	\
							break;																													\
						}																																	\
					}																																		\
					if ( ::GetParent(pTls->m_pHelpMsgWnd[i]->GetSafeHwnd()) == msg->hwnd &&			\
							 ::IsWindowVisible(msg->hwnd) ) {																\
						if ( pTls->m_bHelpMsgHooked ) {																		\
							BYTE pbKeyState[256];																						\
							::GetKeyboardState((LPBYTE) &pbKeyState);												\
							pbKeyState[VK_MENU] &= ~0x80;																		\
							::SetKeyboardState((LPBYTE) &pbKeyState);												\
							pTls->m_bHelpMsgHooked = false;																	\
							break;																													\
						}																																	\
					}																																		\
				}																																			\
			}																																				\
																																							\
			pTls->m_bHelpMsgHookProcessing = false;																	\
		}																																					\
	}																																						\
  return ::CallNextHookEx( pTls->m_hHelpMsgHook, nCode, wParam, lParam );			\
}																																							\
																																							\


//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define IMPLEMENT_HELPMSG_UNHOOK(pWnd)																				\
																																							\
CHelpTlsStruct *pTls = ::GetContext();																				\
if ( pTls ) {																																	\
	if ( pTls->m_pHelpMsgWnd.Count() )																				  \
		pTls->m_pHelpMsgWnd.RemoveObj( pWnd );																		\
																																							\
	if ( !pTls->m_pHelpMsgWnd.Count() ) {																				\
		if ( pTls->m_hHelpMsgHook ) {																							\
			::UnhookWindowsHookEx( pTls->m_hHelpMsgHook );													\
			pTls->m_hHelpMsgHook = 0;																								\
		}																																					\
		::RemoveContext();																												\
	}																																						\
}																																							\
																																							\

//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define IMPLEMENT_HELPMSG_HOOK(pWnd)																					\
																																							\
CHelpTlsStruct *pTls = ::GetContext();																				\
if ( pTls ) {																																	\
	pTls->m_pHelpMsgWnd.Add( this );																						\
																																							\
	if ( !pTls->m_hHelpMsgHook )																								\
		pTls->m_hHelpMsgHook = ::SetWindowsHookEx( WH_CALLWNDPROC, 								\
																				 CallWndProc, NULL, 									\
																				 ::GetCurrentThreadId() );						\
																																							\
}																																							\
																																							\

//////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
��������� ��������� ���������� ���������.
��������� :
*/

#define IMPLEMENT_DLGMSG_HOOKCODE																								\
																																								\
static CPArray<CWnd>	g_pDlgMsgWnd(0, 1, false);																\
static HHOOK					g_hDlgMsgHook = 0;																				\
static bool						g_bDlgMsgHookProcessing = false;													\
																																								\
LRESULT CALLBACK MessageHookProc( int code, WPARAM wParam, LPARAM lParam ) {		\
  if ( code == MSGF_DIALOGBOX && !g_bDlgMsgHookProcessing ) {										\
		AFX_MANAGE_STATE(_afxModuleAddrThis);																	      \
    g_bDlgMsgHookProcessing = true;																							\
    																																						\
    MSG *msg = (MSG *)lParam;																										\
    if ( ((msg->message >= WM_KEYFIRST && msg->message <= WM_KEYLAST) || 				\
				  (msg->message >= WM_MOUSEFIRST && msg->message <= WM_MOUSELAST)) &&		\
					msg->message != WM_CHAR ) {				                                    \
			for ( int i=0,c=g_pDlgMsgWnd.Count(); i<c; i++ ) {												\
        if ( /*(g_pDlgMsgWnd[i]->GetSafeHwnd() == msg->hwnd ||										\
					    ::IsChild(g_pDlgMsgWnd[i]->GetSafeHwnd(), msg->hwnd)) &&*/					\
						 ::IsWindowVisible(g_pDlgMsgWnd[i]->GetSafeHwnd()) ) {							\
					if ( g_pDlgMsgWnd[i]->PreTranslateMessage(msg) ) {										\
						g_bDlgMsgHookProcessing = false;																		\
						return 1;																														\
					}																																			\
				}																																				\
			}																																					\
		}																																						\
																																								\
    g_bDlgMsgHookProcessing = false;																						\
  }																																							\
																																								\
  return ::CallNextHookEx( g_hDlgMsgHook, code, wParam, lParam );								\
}																																								\


//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define IMPLEMENT_DLGMSG_UNHOOK(pWnd)																				  \
																																							\
if ( g_pDlgMsgWnd.Count() )																										\
	g_pDlgMsgWnd.RemoveObj( pWnd );																							\
																																							\
if ( !g_pDlgMsgWnd.Count() && g_hDlgMsgHook ) {																\
  ::UnhookWindowsHookEx( g_hDlgMsgHook );																			\
  g_hDlgMsgHook = NULL;																												\
}																																							\
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define IMPLEMENT_DLGMSG_HOOK(pWnd)																						\
																																							\
g_pDlgMsgWnd.Add( pWnd );																											\
																																							\
if ( !g_hDlgMsgHook )																													\
	g_hDlgMsgHook = ::SetWindowsHookEx( WH_MSGFILTER, 													\
																			MessageHookProc, NULL,									\
																			::GetCurrentThreadId() );								\

//////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //__OCXSTD_H__
