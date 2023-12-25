// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__B6CD96E4_9829_40B0_8B5F_6A62B00E5C8E__INCLUDED_)
#define AFX_STDAFX_H__B6CD96E4_9829_40B0_8B5F_6A62B00E5C8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define _SCL_SECURE_NO_DEPRECATE
#define _CRT_NON_CONFORMING_SWPRINTFS

#pragma warning (disable : 4786)

#include <windows.h>
#include <assert.h>
#include <tchar.h>
#include <rpc.h>

#include <string>
#include <map>
#include <vector>
#include <list>
#include <algorithm>

#include <stuffio/ioutil.h>

#include "stringdefs.h"

#include "../ckahcomm/ckahcomm.h"

#include <klsys/guards/guard.h>
using namespace KLSysNS;

extern Guard g_guardStorage;

extern CProgramExecutionLog log;
extern HANDLE g_hStopEvent;
extern bool g_bIsNT;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__B6CD96E4_9829_40B0_8B5F_6A62B00E5C8E__INCLUDED_)
