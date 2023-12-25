/********************************************************************
	created:	2006/05/05
	created:	5:5:2006   18:54
	filename: 	c:\SourceSafe\Windows\Hook\TestProjects\Keylogger\kdprint\user\client\kdprint.c
	file path:	c:\SourceSafe\Windows\Hook\TestProjects\Keylogger\kdprint\user\client
	file base:	kdprint
	file ext:	c
	author:		������ �������
	
	purpose:	����-������� ������ KDPrint'�
*********************************************************************/

#include <windows.h>
#include <winioctl.h>
#include "..\..\kdshared.h"
#include "..\..\kdctl.h"
#include "kdprint_cli.h"

static volatile LONG gKDPrintReferenceCount = 0;

static HANDLE g_hKDPrintMutex = NULL;
static HANDLE g_hKDPrintFileMapping = NULL;
static PKDPRINT_SECTION g_pKDPrintFileMapping = NULL;
static HANDLE g_hKDPrintThread = NULL;

static volatile BOOL g_bKDPrintTerminateThread = FALSE;

ULONG NTAPI ThreadRoutine(PVOID Context)
{
	KDPRINT_CALLBACK Callback = (KDPRINT_CALLBACK)Context;

	while (!g_bKDPrintTerminateThread)
	{
		ULONG WaitResult;

		WaitResult = WaitForSingleObject(g_hKDPrintMutex, 2000);
		if (WaitResult == WAIT_OBJECT_0)
		{
			ULONG CurrOffset = 0;
			BOOL bBreak = FALSE;

// ���������..
			while (CurrOffset < g_pKDPrintFileMapping->m_BufferTop)
			{
				PCHAR CurrStr = &g_pKDPrintFileMapping->m_Buffer[CurrOffset];

// ��� ����� ������ ������ ��� ���������� ������� ������� � ���� ������ � KD3 (����� GetMessage/PeekMessage)
				ReleaseMutex(g_hKDPrintMutex);
				Callback(CurrStr);
				WaitResult = WaitForSingleObject(g_hKDPrintMutex, 2000);
				if (WaitResult != WAIT_OBJECT_0)
				{
					bBreak = TRUE;
					break;
				}

				CurrOffset += strlen(CurrStr)+1;
			}

			if (bBreak)
				break;

// ��� ��������			
			g_pKDPrintFileMapping->m_BufferTop = 0;

			ReleaseMutex(g_hKDPrintMutex);
		}

		Sleep(20);
	}

	return 0;
}

BOOL Client_InitKDPrint(KDPRINT_CALLBACK Callback)
{
	HANDLE hMutex;
	HANDLE hFileMapping;
	HANDLE hThread;
	PKDPRINT_SECTION pFileMapping;

// ������� ������ � ������� ���� ���
	if (gKDPrintReferenceCount)
	{
		InterlockedIncrement((PLONG)&gKDPrintReferenceCount);
		return TRUE;
	}

	hMutex = CreateMutex(NULL, FALSE, U_MUTEX_NAME);
	if (hMutex == INVALID_HANDLE_VALUE)
		return FALSE;

	hFileMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE | SEC_COMMIT, 0,
		sizeof(KDPRINT_SECTION), U_FILEMAPPING_NAME);
	if (!hFileMapping)
	{
		CloseHandle(hMutex);
		return FALSE;
	}
// ���������..
	pFileMapping = (PKDPRINT_SECTION)MapViewOfFile(hFileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, sizeof(KDPRINT_SECTION));
	if (!pFileMapping)
	{
		CloseHandle(hFileMapping);
		CloseHandle(hMutex);
		return FALSE;
	}

	g_bKDPrintTerminateThread = FALSE;
	hThread = CreateThread(NULL, 0, ThreadRoutine, Callback, CREATE_SUSPENDED, NULL);
	if (!hThread)
	{
		UnmapViewOfFile(pFileMapping);
		CloseHandle(hFileMapping);
		CloseHandle(hMutex);
		return FALSE;
	}
		
	g_hKDPrintMutex = hMutex;
	g_hKDPrintFileMapping = hFileMapping;
	g_pKDPrintFileMapping = pFileMapping;
	g_hKDPrintThread = hThread;

// ��������� ������� �������������
	InterlockedIncrement((PLONG)&gKDPrintReferenceCount);

	ResumeThread(hThread);

	return TRUE;
}

BOOL Client_InitKDPrintDevice(PCHAR ControlDeviceName)
{
	HANDLE hControlDevice;
	KDPRINT_INIT_INPARAM Params;
	DWORD cbReturned;
	BOOL bResult = TRUE;

// ���� �� �������������� �������, �������� ��� ioctl
// lib'� DDK �� ������������ ZwOpenMutant, � �������� �� �� ������� �������� �������..
// ����-������� ������� ������� ������ � ������� �� �����
	hControlDevice = CreateFile(ControlDeviceName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hControlDevice == INVALID_HANDLE_VALUE)
		return FALSE;

	Params.m_hSectionMutant = g_hKDPrintMutex;
	Params.m_hSection = g_hKDPrintFileMapping;
	bResult = DeviceIoControl(hControlDevice, IOCTL_INIT_KDPRINT, &Params, sizeof(Params), NULL, 0, &cbReturned, NULL);

	CloseHandle(hControlDevice);

	return bResult;
}

void Client_UnInitKDPrint()
{
	if (gKDPrintReferenceCount == 0)
		return;

	if (InterlockedDecrement((PLONG)&gKDPrintReferenceCount) == 0)
	{
		g_bKDPrintTerminateThread = TRUE;
		WaitForSingleObject(g_hKDPrintThread, INFINITE);

		UnmapViewOfFile(g_pKDPrintFileMapping);
		CloseHandle(g_hKDPrintFileMapping);
		CloseHandle(g_hKDPrintMutex);
	}
}
