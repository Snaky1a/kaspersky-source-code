// (�) ������ ����, 2006
#include <fltkernel.h>
#include <ntstrsafe.h>
#include <stdio.h>
#include "avzbc.h"
#include "avz.h"
#include "main.h"

#pragma warning(disable:4995)	// deprecated functions

extern "C" PWORD NtBuildNumber; // ����� ������ NT

// global filter object
extern "C" PFLT_FILTER g_pFilterObj;

// ��������� ���������
PRESET_UNICODE_STRING (usImagePath,       CSTRING (ImagePath));
// ��� ����� ��� ����������������
UNICODE_STRING		usLogFile;
// ���� � ����� ��� ���������
UNICODE_STRING		usQrPath;
// ������� ����, ��� ���������������� ���������
BOOLEAN EnableLog = FALSE;
// ������� ����, ��� �������� ��������
BOOLEAN EnableQr  = FALSE;
BOOLEAN AnsiLog   = TRUE;
// ������� ���������
int QrCounter = 1;
// ������ ���������� �������������� �����
DWORD LastFileSize = 0;

static BOOLEAN g_bLogInited = FALSE;
static PFLT_INSTANCE g_pLogFileInstance = NULL;
static HANDLE g_hLogFile = NULL;
static PFILE_OBJECT g_pLogFileObject = NULL;

// ��������� ������ �������� Size ���� ��� Unicode ������ 
VOID AllocateUnicodeString(PUNICODE_STRING us, USHORT Size)
{
	if (!us) return;
	__try {
		us->Length = 0;
		us->MaximumLength = 0;
		us->Buffer = (PWSTR)ExAllocatePool(PagedPool, Size);
		if (us->Buffer) {
			us->Length = 0;
			us->MaximumLength = Size;
		}
	} __except(EXCEPTION_EXECUTE_HANDLER) {	}
}

// ������������ ������ Unicode ������
VOID FreeUnicodeString(PUNICODE_STRING us)
{
	if (!us) return;
	__try {
		if (us->MaximumLength > 0 && us->Buffer) 
			ExFreePool(us->Buffer);
		us->Length = 0;
		us->MaximumLength = 0;
	} __except(EXCEPTION_EXECUTE_HANDLER) {	}
}

// �������  Unicode ������ ��������� � ����� 0 
VOID ClearUnicodeString(PUNICODE_STRING us)
{
	if (!us) return;
	__try {
		if (us->MaximumLength > 0 && us->Buffer) 
			memset(us->Buffer, 0, us->MaximumLength);
		us->Length = 0;
	} __except(EXCEPTION_EXECUTE_HANDLER) {	}
}

VOID AddToLog(WCHAR *txt, PUNICODE_STRING txt1, ULONG *StatusCode)
{
	NTSTATUS status;
	
	// ��������, ��������� �� ����������������
	if (!EnableLog) return;

	if ( !g_bLogInited )
	{
		OBJECT_ATTRIBUTES logfileOA;
		IO_STATUS_BLOCK ioSB;

		g_pLogFileInstance = GetInstanceForFile( &usLogFile );
		if ( !g_pLogFileInstance )
			return;

		InitializeObjectAttributes(
			&logfileOA,
			&usLogFile,
			OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,
			NULL,
			NULL
			);

		status = FltCreateFile(
			g_pFilterObj,
			g_pLogFileInstance,
			&g_hLogFile,
			SYNCHRONIZE | DELETE | FILE_APPEND_DATA | FILE_WRITE_ATTRIBUTES,
			&logfileOA,
			&ioSB,
			NULL,
			FILE_ATTRIBUTE_NORMAL,
			FILE_SHARE_READ,
			FILE_SUPERSEDE,
			FILE_SYNCHRONOUS_IO_NONALERT,
			NULL,
			0,
			0
			);
		if ( !NT_SUCCESS(status) )
			FltObjectDereference( g_pLogFileInstance );
		else
		{
			status = ObReferenceObjectByHandle(
				g_hLogFile,
				0,
				*IoFileObjectType,
				KernelMode,
				(PVOID *) &g_pLogFileObject,
				NULL
				);
			if ( !NT_SUCCESS(status) )
			{
				FltClose( g_hLogFile );
				FltObjectDereference( g_pLogFileInstance );
				return;
			}
			else
				g_bLogInited = TRUE;
		}
	}

	// ����� ������
	WCHAR			Buffer[1024], CodeTxt[20];
	ULONG          BuffSize = 0;
	// ������� ������ ������
	RtlZeroMemory(&Buffer, sizeof(Buffer));
	// ����������� ������
	wcscpy(Buffer, txt);
	// ���������� ������ �������������� ������
	if (txt1 != NULL && txt1->Buffer != NULL) {
		__try {
			for (int i = 0; i < txt1->Length / 2; i++)
				if (txt1->Buffer[i] == 0)
					txt1->Buffer[i] = L'*';
		} __except(EXCEPTION_EXECUTE_HANDLER) {}
		wcscat(Buffer, (wchar_t *)txt1->Buffer);
	}
	// ���������� ��������
	if (StatusCode != NULL) {
		if (*StatusCode == 0)
			wcscat(Buffer, L" - succeeded");
		else {
			wcscat(Buffer, L" - failed (0x");
			swprintf(CodeTxt, L"%X", *StatusCode);
			wcscat(Buffer, (wchar_t *)CodeTxt);
			wcscat(Buffer, L")");
		}
	}
	// ���������� � ���� CRLF	
	wcscat(Buffer, L"\r\n");
	BuffSize = (ULONG) wcslen(Buffer) * 2;

	ULONG cbWritten;

	zDbgPrint("%S", Buffer);
	if (AnsiLog) {
		// �������������� ������ � ANSI
		ANSI_STRING		AnsiString;
		UNICODE_STRING     UnicodeString;

		RtlInitUnicodeString(&UnicodeString, Buffer);
		if (RtlUnicodeStringToAnsiString(&AnsiString, &UnicodeString, TRUE) == STATUS_SUCCESS)	  
			// ������ AnsiString 
			status = FltWriteFile(
				g_pLogFileInstance,
				g_pLogFileObject,
				NULL,
				AnsiString.Length,
				AnsiString.Buffer,
				0,
				&cbWritten,
				NULL,
				NULL
				);
	}
	else 
		// ������ ������ c UNICODE �������
		status = FltWriteFile(
			g_pLogFileInstance,
			g_pLogFileObject,
			NULL,
			BuffSize,
			Buffer,
			0,
			&cbWritten,
			NULL,
			NULL
		);
}

// �������� ����� �������
NTSTATUS zRegDeleteKey(IN PUNICODE_STRING pusRegistryPath)
{
	// ��������� �� ������ ������������ - ����� �����
	if (!MmIsAddressValid(pusRegistryPath)) return STATUS_UNSUCCESSFUL;
	zDbgPrint("zRegDeleteKey (%S)", pusRegistryPath->Buffer);
	// ���������� ��������� ������� "���� ������"
	OBJECT_ATTRIBUTES ob;
	InitializeObjectAttributes(&ob, pusRegistryPath, OBJ_CASE_INSENSITIVE + OBJ_KERNEL_HANDLE + OBJ_FORCE_ACCESS_CHECK, NULL, NULL);
	NTSTATUS ns;
	HANDLE KeyHandle;
	// �������� �����
	ns = ZwOpenKey(&KeyHandle, DELETE, &ob);
	zDbgPrint("ZwOpenKey  = %X", ns);
	if (NT_SUCCESS(ns)) {
		ns = ZwDeleteKey(KeyHandle);
		zDbgPrint("ZwDeleteKey  = %X", ns);
		ZwClose(KeyHandle);
	}
	return ns;
}
BOOLEAN IsValidHexNumber(IN PUNICODE_STRING pusStr)
{
	if (!MmIsAddressValid(pusStr)) return FALSE;
	for (int i = 0; i < pusStr->Length / 2; i++) 
		switch (pusStr->Buffer[i]) {
		case L'0' : break;		case L'1' : break;		case L'2' : break;
		case L'3' : break;		case L'4' : break;		case L'5' : break;
		case L'6' : break;		case L'7' : break;		case L'8' : break;
		case L'9' : break;		case L'A' : break;		case L'B' : break;
		case L'C' : break;		case L'D' : break;		case L'E' : break;
		case L'F' : break;		case L'a' : break;		case L'b' : break;
		case L'c' : break;		case L'd' : break;		case L'e' : break;
		case L'f' : break;
		default:
			return FALSE;
	}
	return TRUE;
}

// ���������� ������ - ������ �������� � �.�.
VOID PrepareParamString(IN PUNICODE_STRING pusStr)
{
	//return;
	UNICODE_STRING usTmp;
	// ��������� ��������� ������
	AllocateUnicodeString(&usTmp, pusStr->MaximumLength);
	__try {
		ClearUnicodeString(&usTmp);
		int Poz = 0;
		// ���� ������� ������ � ������ ��������
		for (int i = 0; i < pusStr->Length / 2; i++) 
			if (pusStr->Buffer[i] != L'\\') {
				// ��� �� ���������� ? ����� ��������
				usTmp.Buffer[Poz] = pusStr->Buffer[i];
				Poz++;
			} 
			else {
				// ������ - � ������ ������������ ������
				if ((pusStr->Length / 2) - i < 6) {
					usTmp.Buffer[Poz] = pusStr->Buffer[i];
					Poz++;
					continue;				
				}
				i++; // ������� �����
				if (pusStr->Buffer[i] != L'u')	{ // ������ - �� ������ ������ ���� ������ u
					i--;
					usTmp.Buffer[Poz] = pusStr->Buffer[i];
					Poz++;
					continue;				
				}
				i++; // ������� "u"
				// ��������� ��������� ������
				UNICODE_STRING usTmpNum;
				AllocateUnicodeString(&usTmpNum, 16);
				ClearUnicodeString(&usTmpNum);
				// ������ 4� �������� - ��� Unicode �������
				for (int j = 0; j<4; j++)
					usTmpNum.Buffer[j] = pusStr->Buffer[i+j];
				usTmpNum.Length = 8;
				// ������� ���� � ������
				i += 3;
				// �������������� ���� � �����
				ULONG Value = 0;
				// ������� ����������� ���� � ������ ��� ������� �������� �����������
				if (IsValidHexNumber(&usTmpNum) && RtlUnicodeStringToInteger(&usTmpNum, 16, &Value) == STATUS_SUCCESS) {
					zDbgPrint("Value = %X", Value);
					usTmp.Buffer[Poz] = (WCHAR)(WORD)Value;
					Poz++;
				} else 
				{
					i -= 5;
					for (int j = 0; j<6; j++) {
						usTmp.Buffer[Poz] = pusStr->Buffer[i];
						Poz++;
						i++;
					}	
					i--;
				};				
				// ������������ ��������� ������
				FreeUnicodeString(&usTmpNum);
			}		
			usTmp.Length = Poz * 2;
			zDbgPrint("Prepared buffer = %S, length = %X", usTmp.Buffer, usTmp.Length);
			// ����������� ���������� ������ � ���������)
			RtlCopyUnicodeString(pusStr, &usTmp);
	} __except(EXCEPTION_EXECUTE_HANDLER) {	return; }
	// ������������ ��������� ������
	FreeUnicodeString(&usTmp);
}

// ������ ��������� ������� � ��������� ������
NTSTATUS zReadRegStr(IN PUNICODE_STRING pusRegistryPath, IN PUNICODE_STRING pusParam, OUT PUNICODE_STRING pusValue)
{
	zDbgPrint("zReadRegStr");
	NTSTATUS res = STATUS_UNSUCCESSFUL;
	// �������� ����������
	if (!MmIsAddressValid(pusRegistryPath)) return STATUS_UNSUCCESSFUL;
	if (!MmIsAddressValid(pusParam)) return STATUS_UNSUCCESSFUL;
	if (!MmIsAddressValid(pusValue)) return STATUS_UNSUCCESSFUL;
	__try {
		// ���������� ��������� ������� "���� ������"
		OBJECT_ATTRIBUTES ob;
		InitializeObjectAttributes(&ob, pusRegistryPath, OBJ_CASE_INSENSITIVE, NULL, NULL);
		HANDLE KeyHandle;
		// �������� �����
		res = ZwOpenKey(&KeyHandle, KEY_QUERY_VALUE, &ob);
		zDbgPrint("ZwOpenKey  = %X", res);
		if (NT_SUCCESS(res)) {
			// ��������� ������ (��������� + ����� ������)
			KEY_VALUE_PARTIAL_INFORMATION *pKeyInfo;
			// ������ ������ ������
			ULONG InfoSize = sizeof(KEY_VALUE_PARTIAL_INFORMATION) + pusValue->MaximumLength;
			pKeyInfo = (KEY_VALUE_PARTIAL_INFORMATION *)ExAllocatePool(PagedPool, InfoSize);
			// ������ �������� ? ����� ������� ������ ������
			if (pKeyInfo != NULL) 
			{
				// ������ ����� 
				res = ZwQueryValueKey(KeyHandle, pusParam, KeyValuePartialInformation, pKeyInfo, InfoSize, &InfoSize);
				zDbgPrint("ZwQueryValueKey (%S) = %X, Type=%X", pusParam->Buffer, res, pKeyInfo->Type);
				if (res == STATUS_SUCCESS && 
					(pKeyInfo->Type == REG_SZ || pKeyInfo->Type == REG_EXPAND_SZ) && 
					pusValue->MaximumLength >= pKeyInfo->DataLength) 
				{
					RtlCopyMemory(pusValue->Buffer, pKeyInfo->Data, pKeyInfo->DataLength);
					pusValue->Length = (USHORT)pKeyInfo->DataLength-2;
					zDbgPrint("ZwQueryValueKey, STR = (%S)", pusValue->Buffer);
				}
				else
					res = STATUS_UNSUCCESSFUL;
				// ������������ ������
				ExFreePool(pKeyInfo);
			}
			ZwClose(KeyHandle);
		}
		return res; 
	} __except(EXCEPTION_EXECUTE_HANDLER) {	return STATUS_UNSUCCESSFUL; }
}

// �������� ����� � ��������� ������
NTSTATUS zDeleteFile(IN PUNICODE_STRING pusFileName)
{
	NTSTATUS status;
	PFLT_INSTANCE pInstance;
	HANDLE hFile = NULL;
	OBJECT_ATTRIBUTES fileOA;
	IO_STATUS_BLOCK ioSB;

	pInstance = GetInstanceForFile( pusFileName );
	if ( !pInstance )
		return STATUS_UNSUCCESSFUL;

	InitializeObjectAttributes(
		&fileOA,
		pusFileName,
		OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,
		NULL,
		NULL
		);
	status = FltCreateFile(
			g_pFilterObj,
			pInstance,
			&hFile,
			DELETE,
			&fileOA,
			&ioSB,
			NULL,
			FILE_ATTRIBUTE_NORMAL,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			FILE_OPEN,
			FILE_DELETE_ON_CLOSE,
			NULL,
			0,
			0
		);
	if ( NT_SUCCESS(status) )
		FltClose( hFile );

	FltObjectDereference( pInstance );

	return status;
}

// ����������� ������
NTSTATUS zCopyFile(IN PUNICODE_STRING pusFileName1, IN PUNICODE_STRING pusFileName2)
{
	LastFileSize = 0;

// get instances here
	PFLT_INSTANCE	pInstance1,
					pInstance2;

	pInstance1 = GetInstanceForFile( pusFileName1 );
	if ( !pInstance1 )
		return STATUS_UNSUCCESSFUL;
	pInstance2 = GetInstanceForFile( pusFileName2 );
	if ( !pInstance2 )
	{
		FltObjectDereference( pInstance1 );
		return STATUS_UNSUCCESSFUL;
	}

	NTSTATUS status;
	OBJECT_ATTRIBUTES	file1OA,
						file2OA;

	InitializeObjectAttributes(
		&file1OA,
		pusFileName1,
		OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,
		NULL,
		NULL
		);
	InitializeObjectAttributes(
		&file2OA,
		pusFileName2,
		OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,
		NULL,
		NULL
		);

	HANDLE	hFile1 = NULL,
			hFile2 = NULL;
	IO_STATUS_BLOCK ioSB;
	PFILE_OBJECT	pFileObject1 = NULL,
					pFileObject2 = NULL;
// �������� ��������� ����� �� ������
	status = FltCreateFile(
		g_pFilterObj,
		pInstance1,
		&hFile1,
		SYNCHRONIZE | FILE_READ_DATA,
		&file1OA,
		&ioSB,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 
		FILE_OPEN, 
		FILE_SYNCHRONOUS_IO_NONALERT, 
		NULL,
		0,
		0
		);
	if ( NT_SUCCESS(status) )
	{
		status = ObReferenceObjectByHandle(
			hFile1,
			0,
			*IoFileObjectType,
			KernelMode,
			(PVOID *) &pFileObject1,
			NULL
			);
		if ( NT_SUCCESS(status) )
		{
			// �������� �������� �����
			status = FltCreateFile(
				g_pFilterObj,
				pInstance2,
				&hFile2,
				SYNCHRONIZE | DELETE | FILE_WRITE_DATA | FILE_WRITE_ATTRIBUTES,
				&file2OA,
				&ioSB,
				NULL,
				FILE_ATTRIBUTE_NORMAL,
				FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 
				FILE_SUPERSEDE, 
				FILE_SYNCHRONOUS_IO_NONALERT, 
				NULL,
				0,
				0
				);
			if ( NT_SUCCESS(status) )
			{
				status = ObReferenceObjectByHandle(
					hFile2,
					0,
					*IoFileObjectType,
					KernelMode,
					(PVOID *) &pFileObject2,
					NULL
					);
				if ( NT_SUCCESS(status) )
				{
					// ��������� ������ ��� ������
					ULONG BufSize = 64 * 1024;
					PVOID Buf = ExAllocatePoolWithTag(PagedPool, BufSize, 'BFbz');
					if ( !Buf )
						status = STATUS_INSUFFICIENT_RESOURCES;
					else
					{
						ULONG cbRead;

						// *** ����������� ***
						do {
							// ������ � ����� ��������� ������ ������
							cbRead = 0;
							status = FltReadFile(
								pInstance1,
								pFileObject1,
								NULL,
								BufSize,
								Buf,
								0,
								&cbRead,
								NULL,
								NULL
								);

							if ( NT_SUCCESS(status) && 0 != cbRead )
							{
								ULONG cbWritten = 0;

								LastFileSize += cbRead;
								status = FltWriteFile(
									pInstance2,
									pFileObject2,
									NULL,
									cbRead,
									Buf,
									0,
									&cbWritten,
									NULL,
									NULL
									);
							}
						} while ( NT_SUCCESS(status) && BufSize == cbRead );

						ExFreePool( Buf );
					}

					ObDereferenceObject( pFileObject2 );
				}

				FltClose( hFile2 );
			}

			ObDereferenceObject( pFileObject1 );
		}

		FltClose( hFile1 );
	}

	FltObjectDereference( pInstance1 );
	FltObjectDereference( pInstance2 );

	return status;
}

// ���������������
NTSTATUS zDeleteDriverParams(IN PUNICODE_STRING pusRegistryPath)
{
	// ��������� �� ������ ������������ - ����� �����
	if (!MmIsAddressValid(pusRegistryPath)) return STATUS_UNSUCCESSFUL;
	zDbgPrint("zDeleteDriverKey = %S", pusRegistryPath->Buffer);
	NTSTATUS ns;
	// �������� ���������� �����, ����������� �� ���������� ��������
	ns = RtlDeleteRegistryValue(RTL_REGISTRY_ABSOLUTE, pusRegistryPath->Buffer, usImagePath.Buffer);
	ns = RtlDeleteRegistryValue(RTL_REGISTRY_ABSOLUTE, pusRegistryPath->Buffer, L"Start");
	ns = RtlDeleteRegistryValue(RTL_REGISTRY_ABSOLUTE, pusRegistryPath->Buffer, L"Type");
	ns = RtlDeleteRegistryValue(RTL_REGISTRY_ABSOLUTE, pusRegistryPath->Buffer, L"DisplayName");
	ns = RtlDeleteRegistryValue(RTL_REGISTRY_ABSOLUTE, pusRegistryPath->Buffer, L"ErrorControl");
	return STATUS_SUCCESS;
}

// �������� ��������
NTSTATUS zDeleteDriver(IN PUNICODE_STRING pusDriver, BOOLEAN DeleteFile)
{
	__try {
		ULONG ns = STATUS_UNSUCCESSFUL;
		// ��������� �� ������ ������������ - ����� �����
		if (!MmIsAddressValid(pusDriver)) return STATUS_UNSUCCESSFUL;
		if (!MmIsAddressValid(pusDriver->Buffer)) return STATUS_UNSUCCESSFUL;
		zDbgPrint("zDeleteDriver (%S)", pusDriver->Buffer);
		// ���������� ����� ��������
		WCHAR wszTmp[500] = L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\";
		wcscat(wszTmp, pusDriver->Buffer);
		UNICODE_STRING TmpKey;
		RtlInitUnicodeString(&TmpKey, wszTmp);
		// �������� ����� ��������
		if (DeleteFile) {
			UNICODE_STRING TmpUS;
			AllocateUnicodeString(&TmpUS, 1024);
			if (zReadRegStr(&TmpKey, &usImagePath, &TmpUS) == STATUS_SUCCESS) {
				ns = zDeleteFile(&TmpUS);
				AddToLog(L"Delete File ", &TmpUS, &ns);
			}
			FreeUnicodeString(&TmpUS);
		}
		// �������� ����� ������� ��������
		zDeleteDriverParams(&TmpKey);
		ns = zRegDeleteKey(&TmpKey);
		return ns;
	} __except(EXCEPTION_EXECUTE_HANDLER) {	return STATUS_UNSUCCESSFUL; }
}

// �������� �����
NTSTATUS zQuarantineFile(IN PUNICODE_STRING pusFileName)
{
	if (!EnableQr) 
		return STATUS_UNSUCCESSFUL;

	ULONG ns = STATUS_UNSUCCESSFUL, CopyNS;
	// ��������� ������ ��� �����
	PWCHAR TmpStr = NULL, Buffer = NULL;

	TmpStr = (PWCHAR)ExAllocatePool(PagedPool, 1024);
	if (TmpStr == NULL) 
		return STATUS_UNSUCCESSFUL;
	Buffer = (PWCHAR)ExAllocatePool(PagedPool, 1024);
	if (Buffer == NULL)
	{
		ExFreePool(TmpStr);
		return STATUS_UNSUCCESSFUL;
	}

	WCHAR FileName[64];		
	// ��������� ����� �����
	swprintf(FileName, L"bcqr%.5d", QrCounter);
	// ������ ����� DAT �����
	wcscpy(TmpStr, usQrPath.Buffer);
	wcscat(TmpStr, FileName);
	wcscat(TmpStr, L".dta");
	QrCounter++;
	zDbgPrint("DTA file name = (%S)", TmpStr);
	UNICODE_STRING TmpUS;	
	RtlInitUnicodeString(&TmpUS, TmpStr);
	// ����������� �����
	CopyNS = zCopyFile(pusFileName, &TmpUS);
	// **** �������� INI �����-�������� ****
	// ������ ����� INI �����
	wcscpy(TmpStr, usQrPath.Buffer);
	wcscat(TmpStr, FileName);
	wcscat(TmpStr, L".ini");
	RtlInitUnicodeString(&TmpUS, TmpStr);
	zDbgPrint("INI file name = (%S)", TmpUS.Buffer);

	NTSTATUS statusINI;

	PFLT_INSTANCE pInstance = GetInstanceForFile( &TmpUS );
	if ( pInstance )
	{
		// ���������� ��������� �����
		OBJECT_ATTRIBUTES inifileOA;
		HANDLE hINIFile = NULL;
		IO_STATUS_BLOCK ioSB;

		InitializeObjectAttributes(
			&inifileOA,
			&TmpUS,
			OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
			NULL,
			NULL
			);

		// ��������/�������� �����
		statusINI = FltCreateFile(
			g_pFilterObj,
			pInstance,
			&hINIFile,
			SYNCHRONIZE | DELETE | FILE_WRITE_DATA | FILE_WRITE_ATTRIBUTES,
			&inifileOA,
			&ioSB,
			NULL,
			FILE_ATTRIBUTE_NORMAL,
			0, 
			FILE_SUPERSEDE, 
			FILE_SYNCHRONOUS_IO_NONALERT, 
			NULL,
			0,
			0
			);
		zDbgPrint("INI: ZwCreateFile = (%X)", statusINI);
		if ( NT_SUCCESS(statusINI) )
		{
			PFILE_OBJECT pINIFileObject = NULL;

			statusINI = ObReferenceObjectByHandle(
				hINIFile,
				0,
				*IoFileObjectType,
				KernelMode,
				(PVOID *) &pINIFileObject,
				NULL
				);
			if ( NT_SUCCESS(statusINI) )
			{
				// ���������� ������ � ��������� �����
				wcscpy(Buffer, L"[InfectedFile]");
				wcscat(Buffer, L"\r\n");
				wcscat(Buffer, L"Src=");
				wcscat(Buffer, pusFileName->Buffer);
				wcscat(Buffer, L"\r\n");
				wcscat(Buffer, L"Infected=");
				wcscat(Buffer, FileName);
				wcscat(Buffer, L".dat");
				wcscat(Buffer, L"\r\n");
				wcscat(Buffer, L"Virus=BootCleaner quarantine");
				wcscat(Buffer, L"\r\n");
				WCHAR wszTmp[15];
				swprintf(wszTmp, L"Size=%i", LastFileSize);
				wcscat(Buffer, wszTmp);
				wcscat(Buffer, L"\r\n");
				swprintf(wszTmp, L"CopyStatus=%X", CopyNS);
				wcscat(Buffer, wszTmp);
				zDbgPrint("INI text = (%S)", Buffer);

				// �������������� ������ � �� UNICODE -> ANSI
				ANSI_STRING		AnsiString;
				UNICODE_STRING  UnicodeString;
				RtlInitUnicodeString(&UnicodeString, Buffer);
				if (RtlUnicodeStringToAnsiString(&AnsiString, &UnicodeString, TRUE) == STATUS_SUCCESS)	  
				{
					ULONG cbWritten;

					// ������ AnsiString 
					statusINI = FltWriteFile(
						pInstance,
						pINIFileObject,
						NULL,
						AnsiString.Length,
						AnsiString.Buffer,
						0,
						&cbWritten,
						NULL,
						NULL
						);
				}

				ObDereferenceObject( pINIFileObject );
			}

			FltClose(hINIFile);
		}

		FltObjectDereference( pInstance );
	}

	ExFreePool(TmpStr);
	ExFreePool(Buffer);

	return CopyNS;
}

// �������� ��������
NTSTATUS zQRDriver(IN PUNICODE_STRING pusDriver)
{
	__try {
		ULONG ns = STATUS_UNSUCCESSFUL;
		// ��������� �� ������ ������������ - ����� �����
		if (!MmIsAddressValid(pusDriver)) return STATUS_UNSUCCESSFUL;
		if (!MmIsAddressValid(pusDriver->Buffer)) return STATUS_UNSUCCESSFUL;
		zDbgPrint("zQrDriver (%S)", pusDriver->Buffer);
		// ���������� ����� ��������
		WCHAR wszTmp[500] = L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\";
		wcscat(wszTmp, pusDriver->Buffer);
		UNICODE_STRING TmpKey;
		RtlInitUnicodeString(&TmpKey, wszTmp);
		// ��������
		UNICODE_STRING TmpUS;
		AllocateUnicodeString(&TmpUS, 1024);
		if (zReadRegStr(&TmpKey, &usImagePath, &TmpUS) == STATUS_SUCCESS) {
			ns = zQuarantineFile(&TmpUS);
			AddToLog(L" Quarantine File ", &TmpUS, &ns);
		}
		FreeUnicodeString(&TmpUS);
		return ns;
	} __except(EXCEPTION_EXECUTE_HANDLER) {	return STATUS_UNSUCCESSFUL; }
}

// ���������� ��������
NTSTATUS zDisableDriver(IN PUNICODE_STRING pusDriver)
{
	__try {
		ULONG x = SERVICE_DISABLED;
		// ������ � �������� Start ���� 4
		return RtlWriteRegistryValue(RTL_REGISTRY_SERVICES,
			pusDriver->Buffer,
			L"Start",
			REG_DWORD,
			&x,
			4);
	} __except(EXCEPTION_EXECUTE_HANDLER) {	return STATUS_UNSUCCESSFUL; }
}

// ���������������
NTSTATUS zSelfDestroy(IN PUNICODE_STRING pusRegistryPath)
{
	// ��������� �� ������ ������������ - ����� �����
	if (!MmIsAddressValid(pusRegistryPath)) return STATUS_UNSUCCESSFUL;
	zDbgPrint("zSelfDestroy = %S", pusRegistryPath->Buffer);
	NTSTATUS ns;
	// �������� ������ ����� ��������
	UNICODE_STRING TmpUS;
	AllocateUnicodeString(&TmpUS, 1024);	
	if (zReadRegStr(pusRegistryPath, &usImagePath, &TmpUS) == STATUS_SUCCESS)
		zDeleteFile(&TmpUS);
	FreeUnicodeString(&TmpUS);
	// �������� ���������� �����, ����������� �� ���������� ��������
	ns = zDeleteDriverParams(pusRegistryPath);
	return ns;
}

// ��������� �������� ������. pusRegistryPath - ���� � "������", DeteteKey - ������� ���������� �������� �������
extern "C"
NTSTATUS ExecuteQuarantine(IN PUNICODE_STRING pusRegistryPath, IN BOOLEAN DeteteKey)
{
	// ���������� �����
	WCHAR wszTmp[100];
	UNICODE_STRING TmpKey, TmpUS;	
	AllocateUnicodeString(&TmpUS, 1024);
	// ********* ���� ��������� ����� � ��������� **********
	int i = 1;
	ULONG ns = 0;
	i = 1;
	while (i < 1024) 
	{
		// ���������� ����� ���������
		swprintf(wszTmp, L"QrSvc%i", i);
		RtlInitUnicodeString(&TmpKey, wszTmp);
		ClearUnicodeString(&TmpUS);
		// ������ ��������
		if (zReadRegStr(pusRegistryPath, &TmpKey, &TmpUS) != STATUS_SUCCESS) break;
		// �������� ��������
		PrepareParamString(&TmpUS);
		ns = zQRDriver(&TmpUS);
		AddToLog(L"Quarantine service file ", &TmpUS, &ns);
		// �������� ����� ������� � �������� 
		if (DeteteKey || ns == STATUS_SUCCESS)
			RtlDeleteRegistryValue(RTL_REGISTRY_ABSOLUTE, pusRegistryPath->Buffer, wszTmp);
		i++;
	}
	// ******* ���� ��������� ������ ******
	i = 1;
	while (i < 1024) 
	{
		// ���������� ����� ���������
		swprintf(wszTmp, L"QrFile%i", i);
		RtlInitUnicodeString(&TmpKey, wszTmp);
		ClearUnicodeString(&TmpUS);
		// ������ ��������
		if (zReadRegStr(pusRegistryPath, &TmpKey, &TmpUS) != STATUS_SUCCESS) break;
		// �������� �����
		ns = zQuarantineFile(&TmpUS);
		AddToLog(L"QuarantineFile ", &TmpUS, &ns);
		// �������� ����� ������� � ��������
		if (DeteteKey || ns == STATUS_SUCCESS)
			RtlDeleteRegistryValue(RTL_REGISTRY_ABSOLUTE, pusRegistryPath->Buffer, wszTmp);
		i++;
	}
	// ������������ ������
	FreeUnicodeString(&TmpUS);
	return STATUS_SUCCESS;
}

// ��������� ����������� ������. pusRegistryPath - ���� � "������", DeteteKey - ������� ���������� �������� �������
extern "C"
NTSTATUS ExecuteCopyFiles(IN PUNICODE_STRING pusRegistryPath, IN BOOLEAN DeteteKey)
{
	// ���������� �����
	WCHAR wszTmp[100];
	UNICODE_STRING TmpKey, TmpUS;	
	AllocateUnicodeString(&TmpUS, 1024);
	// ********* ���� ��������� ����� � ��������� **********
	int i = 1;
	ULONG ns = 0;
	while (i < 1024) 
	{
		// ���������� ����� ��������� 1
		swprintf(wszTmp, L"CpFileF%i", i);
		RtlInitUnicodeString(&TmpKey, wszTmp);
		ClearUnicodeString(&TmpUS);
		// ������ �������� 1
		if (zReadRegStr(pusRegistryPath, &TmpKey, &TmpUS) != STATUS_SUCCESS) break;
		// �������� ����� ������� 1 � ��������
		RtlDeleteRegistryValue(RTL_REGISTRY_ABSOLUTE, pusRegistryPath->Buffer, wszTmp);
		// ���������� ����� ��������� 2
		UNICODE_STRING TmpUS1;	
		AllocateUnicodeString(&TmpUS1, 1024);
		swprintf(wszTmp, L"CpFileT%i", i);
		RtlInitUnicodeString(&TmpKey, wszTmp);
		ClearUnicodeString(&TmpUS1);
		// ������ �������� 1
		if (zReadRegStr(pusRegistryPath, &TmpKey, &TmpUS1) != STATUS_SUCCESS) break;
		// ����������� �����
		ns = zCopyFile(&TmpUS, &TmpUS1);
		AddToLog(L"Copy File ", &TmpUS, &ns);
		FreeUnicodeString(&TmpUS1);
		// �������� ����� ������� 2 � ��������
		if (DeteteKey || ns == STATUS_SUCCESS)
			RtlDeleteRegistryValue(RTL_REGISTRY_ABSOLUTE, pusRegistryPath->Buffer, wszTmp);
		i++;
	}

	// ������������ ������
	FreeUnicodeString(&TmpUS);
	return STATUS_SUCCESS;
}

// ��������� �������� ������. pusRegistryPath - ���� � "������", DeteteKey - ������� ���������� �������� �������
extern "C"
NTSTATUS ExecuteDeleteFiles(IN PUNICODE_STRING pusRegistryPath, IN BOOLEAN DeteteKey)
{
	// ���������� �����
	WCHAR wszTmp[100];
	UNICODE_STRING TmpKey, TmpUS;	
	AllocateUnicodeString(&TmpUS, 1024);
	// ********* ���� ��������� ����� � ��������� **********
	int i = 1;
	ULONG ns = 0;
	// ******* ���� �������� ������ ******
	i = 1;
	while (i < 1024) 
	{
		// ���������� ����� ���������
		swprintf(wszTmp, L"DelFile%i", i);
		RtlInitUnicodeString(&TmpKey, wszTmp);
		ClearUnicodeString(&TmpUS);
		// ������ ��������
		if (zReadRegStr(pusRegistryPath, &TmpKey, &TmpUS) != STATUS_SUCCESS) break;
		// �������� �����
		ns = zDeleteFile(&TmpUS);
		AddToLog(L"DeleteFile ", &TmpUS, &ns);
		// �������� ����� ������� � ��������
		if (DeteteKey || ns == STATUS_SUCCESS)
			RtlDeleteRegistryValue(RTL_REGISTRY_ABSOLUTE, pusRegistryPath->Buffer, wszTmp);
		i++;
	}
	// ������������ ������
	FreeUnicodeString(&TmpUS);
	return STATUS_SUCCESS;
}

// ��������� �������� ���������. pusRegistryPath - ���� � "������", DeteteKey - ������� ���������� �������� �������
extern "C"
NTSTATUS ExecuteDeleteDrivers(IN PUNICODE_STRING pusRegistryPath, IN BOOLEAN DeteteKey)
{
	// ���������� �����
	WCHAR wszTmp[100];
	UNICODE_STRING TmpKey, TmpUS;	
	AllocateUnicodeString(&TmpUS, 1024);
	// ********* ���� ��������� ����� � ��������� **********
	int i = 1;
	ULONG ns = 0;

	// ******* ���� �������� ����� � ��������� ******
	while (i < 1024) 
	{
		// ���������� ����� ���������
		swprintf(wszTmp, L"DelSvc%i", i);
		RtlInitUnicodeString(&TmpKey, wszTmp);
		ClearUnicodeString(&TmpUS);
		// ������ ��������
		if (zReadRegStr(pusRegistryPath, &TmpKey, &TmpUS) != STATUS_SUCCESS) break;
		// �������� ��������
		PrepareParamString(&TmpUS);
		ns = zDeleteDriver(&TmpUS, TRUE);
		AddToLog(L"Delete Service & File ", &TmpUS, &ns);
		// �������� ����� ������� � �������� 
		if (DeteteKey || ns == STATUS_SUCCESS)
			RtlDeleteRegistryValue(RTL_REGISTRY_ABSOLUTE, pusRegistryPath->Buffer, wszTmp);
		i++;
	}

	// ������������ ������
	FreeUnicodeString(&TmpUS);
	return STATUS_SUCCESS;
}

// ��������� �������� ���������. pusRegistryPath - ���� � "������", DeteteKey - ������� ���������� �������� �������
extern "C"
NTSTATUS ExecuteREGOper(IN PUNICODE_STRING pusRegistryPath, IN BOOLEAN DeteteKey)
{
	// ���������� �����
	WCHAR wszTmp[100];
	UNICODE_STRING TmpKey, TmpUS;	
	AllocateUnicodeString(&TmpUS, 1024);
	// ********* ���� ��������� ����� � ��������� **********
	int i = 1;
	ULONG ns = 0;
	// ******* ���� �������� ����� � ��������� (�� ������ ����� �������) ******
	i = 1;
	while (i < 1024) 
	{
		// ���������� ����� ���������
		swprintf(wszTmp, L"DelSvcReg%i", i);
		RtlInitUnicodeString(&TmpKey, wszTmp);
		ClearUnicodeString(&TmpUS);
		// ������ ��������
		if (zReadRegStr(pusRegistryPath, &TmpKey, &TmpUS) != STATUS_SUCCESS) break;
		// �������� ��������
		PrepareParamString(&TmpUS);
		ns = zDeleteDriver(&TmpUS, false);
		AddToLog(L"Delete Service ", &TmpUS, &ns);
		// �������� ����� ������� � �������� 
		if (DeteteKey || ns == STATUS_SUCCESS)
			RtlDeleteRegistryValue(RTL_REGISTRY_ABSOLUTE, pusRegistryPath->Buffer, wszTmp);
		i++;
	}

	// ******* ���� �������� ������ ������� ******
	i = 1;
	while (i < 1024) 
	{
		// ���������� ����� ���������
		swprintf(wszTmp, L"DelRegKey%i", i);
		RtlInitUnicodeString(&TmpKey, wszTmp);
		ClearUnicodeString(&TmpUS);
		// ������ ��������
		if (zReadRegStr(pusRegistryPath, &TmpKey, &TmpUS) != STATUS_SUCCESS) break;
		// �������� �����
		ns = zRegDeleteKey(&TmpUS);
		AddToLog(L"Delete RegKey ", &TmpUS, &ns);
		// �������� ����� ������� � �������� 
		if (DeteteKey || ns == STATUS_SUCCESS)
			RtlDeleteRegistryValue(RTL_REGISTRY_ABSOLUTE, pusRegistryPath->Buffer, wszTmp);
		i++;
	}
	// ******* ���� ���������� ����� � ��������� ******
	i = 1;
	while (i < 1024) 
	{
		// ���������� ����� ���������
		swprintf(wszTmp, L"DisableSvc%i", i);
		RtlInitUnicodeString(&TmpKey, wszTmp);
		ClearUnicodeString(&TmpUS);
		// ������ ��������
		if (zReadRegStr(pusRegistryPath, &TmpKey, &TmpUS) != STATUS_SUCCESS) break;
		// ���������� ��������
		PrepareParamString(&TmpUS);
		ns = zDisableDriver(&TmpUS);
		AddToLog(L"Disable Service ", &TmpUS, &ns);
		// �������� ����� ������� � �������� 
		if (DeteteKey || ns == STATUS_SUCCESS)
			RtlDeleteRegistryValue(RTL_REGISTRY_ABSOLUTE, pusRegistryPath->Buffer, wszTmp);
		i++;
	}
	// ������������ ������
	FreeUnicodeString(&TmpUS);
	return STATUS_SUCCESS;
}

extern "C"
VOID AVZBCInit( __in PUNICODE_STRING pusRegistryPath )
{
	AllocateUnicodeString(&usLogFile, 1024);	
	AllocateUnicodeString(&usQrPath, 1024);

	// ������ �������� ����������������
	UNICODE_STRING TmpKey;	

	RtlInitUnicodeString(&TmpKey, L"LogFile");
	if (zReadRegStr(pusRegistryPath, &TmpKey, &usLogFile) == STATUS_SUCCESS) {
		zDbgPrint("LogFile = %S", usLogFile.Buffer);
		EnableLog = TRUE;
	}

	// ��������� ���������
	RtlInitUnicodeString(&TmpKey, L"QrPath");
	if (zReadRegStr(pusRegistryPath, &TmpKey, &usQrPath) == STATUS_SUCCESS) {
		zDbgPrint("QrPath = %S", usQrPath.Buffer);
		EnableQr = TRUE;
		AddToLog(L"Quarantine path: ", &usQrPath, NULL);
	}
}

extern "C"
VOID AVZBCUnInit()
{
	if ( g_bLogInited )
	{
		ObDereferenceObject( g_pLogFileObject );
		FltClose( g_hLogFile );
		FltObjectDereference( g_pLogFileInstance );
	}

	FreeUnicodeString(&usLogFile);	
	FreeUnicodeString(&usQrPath);		
}
