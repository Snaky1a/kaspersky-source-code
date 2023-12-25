#include <stdafx.h>
#include "kd3.h"
#include "msgthread.h"

HMODULE KD3::InjectDLLProcess(DWORD ProcessID, CHAR *DLLName)
{
	HMODULE hInjectedModule = NULL;

	HANDLE hTargetProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION |
		PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, ProcessID);
	if (!hTargetProcess)
		return FALSE;

	HMODULE hModule = GetModuleHandle("kernel32.dll");
	if (hModule)
	{
		DWORD DLLNameLen = strlen(DLLName);

// kernel32 ����� �������� �� ������ � ���� �� ������
		PVOID pfLoadLibraryA = GetProcAddress(hModule, "LoadLibraryA");
		if (pfLoadLibraryA)
		{
// �������� ������ � ������� �������� ��� ��� ���..
			PVOID pParam = VirtualAllocEx(hTargetProcess, NULL, DLLNameLen+1,
				MEM_COMMIT, PAGE_READWRITE);
			if (pParam)
			{
				DWORD cbWritten;
// ����� ��� ���
				if (WriteProcessMemory(hTargetProcess, pParam, DLLName,
					DLLNameLen+1, &cbWritten))
				{
// � ����� threadproc - LoadLibraryA, �������� - ������ � ������ ���
					HANDLE hThread = CreateRemoteThread(hTargetProcess, NULL, 0, (PTHREAD_START_ROUTINE)pfLoadLibraryA, pParam, 0, NULL);
					if (hThread)
					{
						WaitForSingleObject(hThread, INFINITE);
// � ��� exitcode ����� �����, ������������ LoadLibraryA
						GetExitCodeThread(hThread, (PDWORD)&hInjectedModule);
					}
				}

				VirtualFreeEx(hTargetProcess, pParam, 0, MEM_RELEASE);
			}
		}
	}

	CloseHandle(hTargetProcess);

	return hInjectedModule;
}

// ��� �������� �����, ��� � � �������..
BOOL KD3::EjectDLLProcess(DWORD ProcessID, HMODULE hModule2Eject)
{
	BOOL bResult = FALSE;

	HANDLE hTargetProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION |
		PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, ProcessID);
	if (!hTargetProcess)
		return FALSE;

	HMODULE hModule = GetModuleHandle("kernel32.dll");
	if (hModule)
	{
		PVOID pfFreeLibrary = GetProcAddress(hModule, "FreeLibrary");
		if (pfFreeLibrary)
		{
			if (hModule2Eject)
			{
				HANDLE hThread = CreateRemoteThread(hTargetProcess, NULL, 0, (PTHREAD_START_ROUTINE)pfFreeLibrary, hModule2Eject, 0, NULL);
				if (hThread)
				{
					WaitForSingleObject(hThread, INFINITE);
					bResult = TRUE;
				}
			}
		}
	}

	CloseHandle(hTargetProcess);

	return bResult;
}

BOOL KD3::AcquireDebugPrivelage()
{
	BOOL bResult = FALSE;

	HANDLE hToken;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return FALSE;

	LUID Luid;
	if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &Luid))
	{
		TOKEN_PRIVILEGES TokenPrivelege;
		TokenPrivelege.PrivilegeCount = 1;
		TokenPrivelege.Privileges[0].Luid = Luid;
		TokenPrivelege.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		AdjustTokenPrivileges(
			hToken,
			FALSE,
			&TokenPrivelege,
			sizeof(TokenPrivelege),
			NULL,
			NULL);

		if (GetLastError() == ERROR_SUCCESS)
			bResult = TRUE;
	}

	CloseHandle(hToken);

	return bResult;
}

// �� ���������� � ��� ��������..
BOOL KD3::CheckProcName(PTCHAR ProcName)
{
	return	!!_tcsicmp(ProcName, _T("csrss.exe")) &&
			!!_tcsicmp(ProcName, _T("smss.exe")) &&
			!!_tcsicmp(ProcName, _T("services.exe")) &&
			!!_tcsicmp(ProcName, _T("svchost.exe"));
}

BOOL KD3::Start()
{
	TCHAR DLLPath[512];
	if (!(GetModuleFileName(AfxGetInstanceHandle(), DLLPath, sizeof(DLLPath)/sizeof(TCHAR)) &&
		PathRemoveFileSpec(DLLPath)))
		return FALSE;
	_tcscat(DLLPath, _T("\\kd3dll.dll"));

	if (!AcquireDebugPrivelage())
		ATLTRACE("KD3: SeDebugPrivelage not acquired\n");

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, GetCurrentProcessId());
	if (hSnapshot == INVALID_HANDLE_VALUE)
		return FALSE;

	PROCESSENTRY32 PE;
	PE.dwSize = sizeof(PROCESSENTRY32);

	NumProcs = 0;

	if (!Process32First(hSnapshot, &PE))
		return FALSE;

	HMODULE hModule;
	do
	{
// ���������� Idle � System
		if (PE.th32ProcessID == 0 || PE.th32ProcessID == 4)
			continue;

		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE,
			PE.th32ProcessID);
		if (hProcess)
		{
			TCHAR ProcName[512];
// ���������� csrss, smss, services, svchost
			if (GetModuleBaseName(hProcess, NULL, ProcName, sizeof(ProcName)/sizeof(TCHAR)))
			{
				if (!CheckProcName(ProcName))
				{
					ATLTRACE("KD3: bypassed PID:%d \"%s\"\n", PE.th32ProcessID, ProcName);
					continue;
				}

				hModule = InjectDLLProcess(PE.th32ProcessID, DLLPath);
				if (hModule)
				{
					Procs[NumProcs].PID = PE.th32ProcessID;
					Procs[NumProcs].hModule = hModule;

					NumProcs++;
				}
			}

			CloseHandle(hProcess);
		}
		else
			ATLTRACE("KD3: failed to open PID:%d\n", PE.th32ProcessID);
	}
	while (Process32Next(hSnapshot, &PE));
		
	CloseHandle(hSnapshot);

	return !!NumProcs;
}

void KD3::Stop()
{
	CMsgThread MsgThread;
// ����� �������� �� ��������
	MsgThread.Start();

	for (DWORD i = 0; i < NumProcs; i++)
		EjectDLLProcess(Procs[i].PID, Procs[i].hModule);

	MsgThread.Stop();
}
