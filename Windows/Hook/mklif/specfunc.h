#ifndef __SPEC_PROC_H
#define __SPEC_PROC_H

#include "pch.h"

//! \fn				: SpecialFileProcessing
//! \brief			: �������� ������ �� ������ �� ����� �� ������ �������� + ��������� ��������� �������� ��������
//! \return			: void 
void
SpecialFileProcessingInit ();

void
SpecialFileProcessingDone ();

void
SpecialFileProcessingGo ();


NTSTATUS
SpecFileRequest(
	PSPECFILEFUNC_REQUEST pSpecRequest,
	ULONG ReqSize,
	PVOID OutputBuffer,
	ULONG OutputBufferLength,
	ULONG_PTR* pOutSize );

NTSTATUS
ReadFile (
	HANDLE FileHandle,
	PVOID Buffer,
	ULONG ToRead,
	PLARGE_INTEGER pOffset,
	PULONG pRead
	);

#endif // __SPEC_PROC_H