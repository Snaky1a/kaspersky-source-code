#ifndef _GLOBAL_ENVIRONMENT_H
#define _GLOBAL_ENVIRONMENT_H

/*!
*		
*		
*		(C) 2003 Kaspersky Lab 
*		
*		\file	glbenvir.h
*		\brief	������������� ���������� ���������� ��� ���������������� ��������
*		
*		\author Andrew Sobko
*		\date	12.09.2003 11:02:21
*		
*		
*		
*/		

#include <ntifs.h>

extern ULONG	gDrvFlags;
// ���� ������������ �������
extern PSHORT NtBuildNumber;

// ��������� �� ��������� ������
extern PVOID BaseOfNtDllDll;
extern PVOID BaseOfNtOsKrnl;
extern PVOID BaseOfHal;

extern int gFSNeedRescan;

// �������� ����� � ��������� ��������
extern ULONG ProcessNameOffset;

//! \fn				: InitGlobalEnvironment
//! \brief			: ������������������� ������
//! \return			: TRUE - ��� ������ ������� �������������������� / FALSE - ��� ���� ������������� ������ ���������
BOOLEAN
InitGlobalEnvironment();


VOID
LoadDriverFlags(VOID);

#endif //_GLOBAL_ENVIRONMENT_H