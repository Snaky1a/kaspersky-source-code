#ifndef _SYSCALLS_H
#define _SYSCALLS_H

/*!
*		
*		
*		(C) 2001-3 Kaspersky Lab 
*		
*		\file	syscalls.h
*		\brief	�������� ������� ������ Ring3 -> Ring0
*		
*		\author Sergey Belov
*		\date	12.09.2003 12:36:02
*		
*		Example:	
*		
*		
*		
*/		



#include "osspec.h"
#include "hook/avpgcom.h"

#include "filter.h"
#include "InvThread.h"
#include "tspv2.h"
#include "evqueue.h"

//+ ������� ������

extern
NTSTATUS
DoExternalDrvRequest (
	PEXTERNAL_DRV_REQUEST pInRequest,
	ULONG InRequestSize,
	PVOID pOutRequest,
	ULONG OutRequestSize,
	ULONG *pRetSize
	);
//+ ------------------------------------------------------------------------------------------
#ifdef _HOOK_VXD_
	#define KLIF_DeviceID		0x415B	// from Microsoft specially for KLIF
extern __EXC__ DDB The_DDB;
#endif

//+ ������ / ...
extern BOOLEAN SysCallsInited;
extern ULONG DirectSysCallStartId;

//! \fn				: InitSysCalls
//! \brief			: ������������� ������ �������
//! \return			: STATUS_SUCCESS - ������� / ���� ������
//! \param          : VOID
NTSTATUS
InitSysCalls(VOID);

//! \fn				: DoneSysCalls
//! \brief			: ��������� ������������ (� ������ ������ �������� �� �����������)
//! \return			: 
//! \param          : VOID
VOID
DoneSysCalls(VOID);

//! \fn				: GetAddrOfShadowTable
//! \brief			: ����� shadow ������� ��������� ��������
//! \return			: ����� �������
ULONG
GetAddrOfShadowTable();

#endif //_SYSCALLS_H