#ifndef _SECURITY_H_
#define _SECURITY_H_

/*!
*		
*		
*		(C) 2001-3 Kaspersky Lab 
*		
*		\file	klsecur.h
*		\brief	security - sid, ����������������...
*		
*		\author Sergey Belov, Andrew Sobko
*		\date	12.09.2003 11:18:11
*		
*		
*/		


#include "osspec.h"
#ifdef _HOOK_NT_

//! \fn				: InitImpersonate
//! \brief			: ������������ ���������� ������
//! \return			: TRUE - ������� / FALSE - ���� �������������
//! \param          : VOID
BOOLEAN
InitImpersonate(VOID);

//! \fn				: Security_CaptureContext
//! \brief			: ��������� �������� ��� ����������� ������
//! \return			: STATUS_SUCCESS - �������� �������� / ���� ������
//! \param          : PETHREAD OrigTh - �����
//! \param          : SECURITY_CLIENT_CONTEXT *pClientContext - ����� ��� ���������
NTSTATUS
Security_CaptureContext(PETHREAD OrigTh, SECURITY_CLIENT_CONTEXT *pClientContext);

//! \fn				: Security_ReleaseContext
//! \brief			: ���������� security ��������
//! \return			: 
//! \param          : SECURITY_CLIENT_CONTEXT *pClientContext - ��������
void
Security_ReleaseContext(SECURITY_CLIENT_CONTEXT *pClientContext);

//! \fn				: MyImpersonateClient
//! \brief			: ������������������� �����
//! \return			: 
//! \param          : IN PETHREAD  ServerThread  OPTIONAL - ����� ��� ���������������� (���� �� ������ �� �������)
//! \param          : IN PSECURITY_CLIENT_CONTEXT  ClientContext - ssecurity ��������
NTSTATUS
MyImpersonateClient(IN PETHREAD  ServerThread, IN PSECURITY_CLIENT_CONTEXT  ClientContext);

BOOLEAN
SeGetLuid(PLUID pLuid);

//! \fn				: SeGetSID
//! \brief			: �������� SID �������� ������������
//! \return			: 
//! \param          : PSID pSid - ��������� �� ����� ��� SID-�
//! \param          : ULONG* pSidLength - �� ����� ����� �����, �� ������ - ����� SID-�
BOOLEAN
SeGetSID(PSID pSid, ULONG* pSidLength);

/*NTSTATUS
SA_GetData(HANDLE hFile, PVOID psa_info, ULONG* sa_info_len);

NTSTATUS
SA_SetData(HANDLE hFile, PVOID psa_info, ULONG sa_info_len);


NTSTATUS
SA_ClearValidFlag(PWCHAR pwchFile, ULONG namelen);

VOID
SA_PatchSecrDescr(PISECURITY_DESCRIPTOR pidescr);*/

#endif // _HOOK_NT_

#endif // _SECURITY_H_