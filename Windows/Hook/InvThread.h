#ifndef __INVISIBLE_THREADS_H
#define __INVISIBLE_THREADS_H

/*!
*		
*		
*		(C) 2001-3 Kaspersky Lab 
*		
*		\file	InvThread.h
*		\brief	��������� ������
*		
*		\author Andrew Sobko
*		\date	12.09.2003 11:04:30
*		
*		1. �������� ������ �� �����������
*		2. ����������� ������ ��� ���������� (����������� ������������� �����������)
*		3. ������ �������� ����������� � ������
*		
*/		




#ifdef _HOOK_NT_
#include <ntifs.h>
#endif

#include "client.h"

//! \fn				: GlobalInvThreadInit
//! \brief			: ������������� ���������� ������
//! \return			: 
VOID
GlobalInvThreadInit();

//! \fn				: GlobalInvThreadDone
//! \brief			: ������������ ���������� ������
//! \return			: 
VOID
GlobalInvThreadDone();
//+ ------------------------------------------------------------------------------------------

//! \fn				: IsInvisibleThread
//! \brief			: �������� ������ �� �����������
//! \return			: TRUE - ����� ���������������� ��� ��������� / FALSE - '�����' �����
//! \param          : ULONG ThreadID - ������������� ������
BOOLEAN
IsInvisibleThread(ULONG ThreadID);

//! \fn				: InvisibleReleaseAll
//! \brief			: ����������������� ��� ������
//! \return			: 
//! \param          : VOID
VOID
InvisibleReleaseAll(VOID);

//! \fn				: AddInvisibleThread
//! \brief			: ���������������� ����� ��� ���������
//! \return			: STATUS_SUCCESS - ������� / STATUS_UNSUCCESSFUL - ���� ��� �����������
//! \param          : ULONG ThreadID
NTSTATUS
AddInvisibleThread(ULONG ThreadID);

//! \fn				: DelInvisibleThread
//! \brief			: ����������������� �����
//! \return			: 
//! \param          : ULONG ThreadID - ������������� ������
//! \param          : BOOLEAN bHardFlash - ���� TRUE �� ����� ����������������� ��� ����� ���������� ����������� 
//						(�������������� ��������������. � �������, ��� �������� ������)
NTSTATUS
DelInvisibleThread(ULONG ThreadID, BOOLEAN bHardFlash);

//! \fn				: InvisibleTransmit
//! \brief			: ������� API ��� ������ � ���������� �������� (����������, ��������, etc...)
//! \return			: STATUS_SUCCESS - ������� / ���� ������
//! \param          : PINVISIBLE_TRANSMIT pInvTransmit - ������
//! \param          : PINVISIBLE_TRANSMIT pInvTransmitOut - ��������� ���������
NTSTATUS
InvisibleTransmit(PINVISIBLE_TRANSMIT pInvTransmit, PINVISIBLE_TRANSMIT pInvTransmitOut);


VOID
InvProc_RemoveFromList (
	HANDLE ProcessId
	);

VOID
InvProc_CheckNewChild (
	HANDLE ParentProcessId,
	HANDLE ProcessId
	);


#endif // __INVISIBLE_THREADS_H