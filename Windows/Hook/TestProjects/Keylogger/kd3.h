#ifndef _KD3_H
#define _KD3_H
//----------------------------------------------------------------------------------------------

#define MAX_PROCS		1024

struct PROCESS
{
	HMODULE hModule;
	DWORD PID;
};

class KD3
{
private:
// ������ ��������� � ������� ��������������� kd3dll.dll
	PROCESS Procs[MAX_PROCS];
	DWORD NumProcs;

// �������� � �� �������� ���. ���������� �� hmodule.
	HMODULE InjectDLLProcess(DWORD ProcessID, CHAR *DLLName);
// �������� ��� �� �� ��������
	BOOL EjectDLLProcess(DWORD ProcessID, HMODULE hModule);
// ��������� SeDebugPrivalage ��� �������� ��������
	BOOL AcquireDebugPrivelage();
	BOOL CheckProcName(PTCHAR ProcName);
public:
	KD3()
	{
		NumProcs = 0;
	};

	~KD3() {};

	BOOL Start();

	void Stop();
};

//----------------------------------------------------------------------------------------------
#endif