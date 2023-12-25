#ifndef __FSDrvLib_H
#define __FSDrvLib_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif


// �������� �������� � ����������� ����������
// �� �������� �� DLLMain �� ��� Service manager-� ���� ������� �� ��������
BOOL __cdecl FSDrvInterceptorInit(void);	

// �������������� ���������� � �������� ��������
void __cdecl FSDrvInterceptorDone(void);	

// ����������� �������� ������ ��� ���������� ��� ��������
BOOL __cdecl FSDrvInterceptorRegisterInvisibleThread(void);	

// �������������� �������� ������ ��� ���������� ��� ��������
void __cdecl FSDrvInterceptorUnregisterInvisibleThread(void);

BOOL __cdecl FSDrvInterceptorSetActive(BOOL bActive);


// -----------------------------------------------------------------------------------------
// extended api
BOOL __cdecl FSDrvInterceptorInitEx(DWORD AppFlags, ULONG AppID, ULONG Priority, ULONG CacheSize);
BOOL __cdecl FSDrvInterceptorInitTsp(void);	
//BOOL FSDrvInterceptorThreadSubProcesssing(PVOID pPageSet);	//PTHREAD_PAGE_SET pPageSet
//BOOL FSDrvVirtualLock(LPVOID lpAddress,SIZE_T dwSize);
//BOOL FSDrvVirtualUnLock(LPVOID lpAddress,SIZE_T dwSize);
typedef void* ORIG_HANDLE; //������� ����� � ������� ������
ORIG_HANDLE __cdecl FSDrvTSPRegister(SIZE_T max_size); //����������� ����������� ������� ������ (In bytes)+ �������� 
BOOL __cdecl FSDrvTSPUnregister(ORIG_HANDLE hOrig); // �����������
BOOL __cdecl FSDrvTSPLock(ORIG_HANDLE hOrig,SIZE_T real_size,DWORD min_number_of_shadows); //������� ������ ������� , �������� ���������� ����� �����.
BOOL __cdecl FSDrvTSPThreadEnter(ORIG_HANDLE hOrig); // ���� ���� ��������� ����� � ����,����������. ���� ��� - ������� � �������� 
BOOL __cdecl FSDrvTSPThreadLeave(ORIG_HANDLE hOrig); // ��������� ����� ����� �� ������ ����������
BOOL __cdecl FSDrvTSPSetMinShadows(ULONG MinShadows); // min shadow

BOOL __cdecl FSDrv_GetDiskStat(unsigned __int64* pTimeCurrent, unsigned __int64* pTotalWaitTime);
// -----------------------------------------------------------------------------------------
// Using this method is NOT recomended!
HANDLE __cdecl FSDrvGetDeviceHandle();
HANDLE __cdecl FSDrvGetWhistlerUpHandle();
ULONG __cdecl FSDrvGetAppID();


#ifdef __cplusplus
}
#endif

#endif __FSDrvLib_H
