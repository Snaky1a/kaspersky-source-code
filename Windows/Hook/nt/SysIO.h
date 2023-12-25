#ifndef __SYS_IO
#define __SYS_IO

/*!
*		
*		
*		(C) 2002-3 Kaspersky Lab 
*		
*		\file	SysIO.h
*		\brief	������������ �������� �������
*		
*		\author Andrew Sobko, Sergey Belov
*		\date	12.09.2003 12:51:00
*		
*		
*		
*		
*/		



#include <ntifs.h>

#include "../debug.h"
#include "../kldefs.h"
#include "../sysnamecache.h"
#include "../drvtypes.h"
#include "../InvThread.h"

#include "../hook/avpgcom.h"
#include "../hook/hookspec.h"

#include "glbenvir.h"
#include "../osspec.h"

#include "../client.h"
#include "../filter.h"
#include "../TSPv2.h"

#include "../r3.h"
#include "../namecache.h"

//+ ------------------------------------------------------------------------------------------
//! \fn				: SetSystemNotifiers
//! \brief			: ���������� ��������� ������������
//! \return			: 
VOID
SetSystemNotifiers();

// Gruzdev------------------------------------------------------------------------------------
//! \fn				: SetSystemNotifiers_Late
//! \brief			: ���������� ��������� ������������, ��������� ������� ������������ win32k.sys
//! \return			: �����/�������
BOOLEAN
SetSystemNotifiers_Late();


//! \fn				: RemoveSystemNotifiers
//! \brief			: ���������� ������� / ����� ��������� ������������ (�� �����������) 
//! \return			: 
VOID
RemoveSystemNotifiers();

//! \fn				: KLTerminateProcess
//! \brief			: ����� ��������� �������
//! \return			: 
//! \param          : IN HANDLE ProcessHandle - ����� ��������
//! \param          : IN ULONG ProcessExitCode - ��� �������� ��� ���������� ��������
NTSTATUS
KLTerminateProcess(IN HANDLE ProcessHandle, IN ULONG ProcessExitCode);

// ����� ������� ������� � ����� ������
#define KillCurrentProcess() KLTerminateProcess(NtCurrentProcess(), STATUS_FATAL_APP_EXIT)

NTSTATUS
SysFillPIDList(PVOID pOutRequest, ULONG OutRequestSize, ULONG *pRetSize);

NTSTATUS
SysFillSectionList (
	ULONG PID,
	PVOID pOutRequest,
	ULONG OutRequestSize,
	ULONG *pRetSize
	);

NTSTATUS
SysFillDrvList (
	PVOID pOutRequest,
	ULONG OutRequestSize,
	ULONG *pRetSize
	);

NTSTATUS
SysGetPrefetch(
	PVOID pOutRequest,
	ULONG OutRequestSize,
	ULONG *pRetSize);

NTSTATUS
SysFindInSectionHashes (
	LARGE_INTEGER hash );

VOID
AddSkipLockItem(
	PFILE_OBJECT pFileObject);

VOID
DelSkipLockItem(
	PFILE_OBJECT pFileObject);

NTSTATUS
DoDirectOpen (
	PHANDLE pHandle,
	PWSTR pOrigName,
	USHORT OrigNameLenInTchar
	);

VOID
KeyLoggers_CommonCheck();

NTSTATUS
SysGetAppPath (
	ULONG ProcessId,
	PWCHAR pOutRequest,
	ULONG OutRequestSize,
	PULONG pRetSize
	);

#endif //__SYS_IO