#ifndef __CLIENT_H
#define __CLIENT_H

/*!
*		
*		
*		(C) 2001-3 Kaspersky Lab 
*		
*		\file	client.h
*		\brief	����������� ����������� �������� � ��������, �������� ������, ����������� ��� ����������� �������� 
*		Ring0 - Ring3
*
*		\author Andrew Sobko
*		\date	11.09.2003 14:23:15
*		
*		�������� ����� ������ ������� - 
*		1. �������� ������ ���������� (IOCTLHOOK_GetVersion)
*		2. ����������� �������(IOCTLHOOK_RegistrApp)
*		3. ���������� �������� (��. filter.h)
*		4. ������� ����������� � �������� ����� (IOCTLHOOK_Activity -> _AS_GoActive)
*		5. �������� ������� �� ������� APP_REGISTRATION.m_WhistleUp
*		6. ��������� ������� (��. evqueu.h)
*		7. ������� ����������� � ������ ����� (IOCTLHOOK_Activity -> _AS_GoSleep)
*		8. �������� ��������
*		9. ���������� �� �������� (IOCTLHOOK_Activity -> _AS_Unload)
*
*		������ ������ ����� ����� ��������� ����������� ��� ������������� ��������. ����� ��� �����������:
*		1. ������� ��������			
*		2. ������� ��������������� �������
*		3. ���
*
*		����������� ����������:
*		1. �������� ��������� ����� ��� ������������ �������������� ��������
*
*/		

#include "osspec.h"
#include "structures.h"
#include "debug.h"

//+ ------------------------------------------------------------------------------------------

//! \fn				: ProcessDelayedQueue
//! \brief			: ������� �����, ������������ ��� �������� ���������� ��� ���������� ��������
//! \return			: 
extern VOID ProcessDelayedQueue();

//! \fn				: FS_CheckNewDevices
//! \brief			: ������� ����� ��� �������� �� ���������� ������ (��� �������� ����������� ���������)
//! \return			: 
extern void FS_CheckNewDevices();

//+ ------------------------------------------------------------------------------------------
//+ ����� ��������� �������

#define _INTERNAL_APP_STATE_NONE			0x000

// client connection status. if this bit setted mean that client connected
#define _INTERNAL_APP_STATE_CONNECTED		0x001

// client activity status. if this bit setted mean that cleint active (otherwise in SleepMode)
#define _INTERNAL_APP_STATE_ACTIVE			0x002

// client functional status. if this bit setted mean that client was connected but not responding
#define _INTERNAL_APP_STATE_DEAD			0x004

// client activity status. if this bit setted mean that client lifetime timeout expired
#define _INTERNAL_APP_STATE_WATCHDOGPAUSED	0x008

//+ ------------------------------------------------------------------------------------------
//+ ���������� ��������� � ���

#define _CL_CACHE_NOTCHECKED	-1
#define _CL_CACHE_NOTCACHED		0 
#define _CL_CACHE_CACHED_DIRTY	1
#define _CL_CACHE_CACHED		2

//+ ------------------------------------------------------------------------------------------
//+ ���������� ��������/��������� ��� ������� ��������� ��������
extern ULONG gActiveClientCounter;
extern BOOLEAN bClientsMutexInited;

//+ ------------------------------------------------------------------------------------------
//+ ��������� �����
#ifdef _HOOK_NT_ 
extern PVOID ActivityWatchDogThread;
#else
extern TIMEOUTHANDLE hActivityWatchDog;
#endif //_HOOK_NT_

//+ ------------------------------------------------------------------------------------------
//! \fn				: GlobalClientsInit
//! \brief			: ������������� ���������� ������, �������������� ����������������� ������� ��������
//! \return			: STATUS_UNSUCCESSFUL ���� ������������� �� ��������� / STATUS_SUCCESS - �������
//! \param          : void
NTSTATUS
GlobalClientsInit(void);

//! \fn				: GlobalClientsDone
//! \brief			: ������������ ���������� ������. ������ ���� ������� ��� ����� ���������� ������ GlobalClientsInit
//! \return			: 
//! \param          : void
void
GlobalClientsDone(void);

//! \fn				: AcquireClient
//! \brief			: ������ ������ � ������� (������ �� ����� ������� �� ������������)
//! \return			: PQCLIENT - ��������� �� ������ �� ������� / NULL ���� ������ �� ������
//! \param          : ULONG AppID - ������������� �������
PQCLIENT
AcquireClient(ULONG AppID);

//! \fn				: ReleaseClient
//! \brief			: ������������ ���������� ���������
//! \return			: 
//! \param          : PQCLIENT pClient - ���������, ���������� ����� AcquireClient
void
ReleaseClient(PQCLIENT pClient);

void
ReleaseClientAndSubClient(PQCLIENT pClient, PQSUBCLIENT pSubClient);

//! \fn				: IsExistClient
//! \brief			: �������� ������� ������� � ��������� ���������������	
//! \return			: TRUE ���� ������ / FALSE ���� �� ������
//! \param          : ULONG AppID - ������������� �������
BOOLEAN
IsExistClient(ULONG AppID);

//! \fn				: IsSubClientConnected
//! \brief			: �������� ��� ��������� ��������� ����� �������� �����������	
//! \return			: TRUE - ����������� ���������� / FALSE - ����������� �� ����������
//! \param          : PQSUBCLIENT pSubClient - ��������� �� ����������
BOOLEAN
IsSubClientConnected(PQSUBCLIENT pSubClient);

//! \fn				: ClientActivity
//! \brief			: ����������� ������� ��� ������� (��. APPSTATE_REQUEST)
//! \return			: TRUE - ������ ��������� �� ����� / FALSE � ���� ��������� ���� ������ (���������� ������)
//! \param          : PHDSTATE In - ����������� ����
//! \param          : PHDSTATE Out - ��������� ��������� ������� (������� �� ���� ������� �������)
BOOLEAN
ClientActivity(PHDSTATE In, PHDSTATE Out);

//! \fn				: RegisterAppFromSav
//! \brief			: �������������� ����������� ����� �� ������� (����������� �� ������ ��������)
//! \return			: TRUE - ������� / FALSE - ������ �� ������������
//! \param          : ULONG AppID - ������������� �������
//! \param          : PCLIENT_SAV pClientSav - ������ �� �������
BOOLEAN
RegisterAppFromSav(ULONG AppID, PCLIENT_SAV pClientSav);

//! \fn				: RegisterApplication
//! \brief			: ������� ����������� ������� �� Ring3
//! \return			: TRUE - ����������� ��������� / FALSE - ������ �� ���������
//! \param          : PAPP_REGISTRATION pReg - ������ �� �����������
//! \param          : PCLIENT_INFO pClientInfo - �������� ���� (�������� �������������, etc...)
BOOLEAN
RegisterApplication(PAPP_REGISTRATION pReg, PCLIENT_INFO pClientInfo);

//! \fn				: DisconnectClientByProcID
//! \brief			: ���������� ������� ��� �������� �������� (��������� ������)
//! \return			: 
//! \param          : ULONG ProcID - ������������� ���������� ��������
void
DisconnectClientByProcID(ULONG ProcID);

//! \fn				: DisconnectClientByThreadID
//! \brief			: ��������� ������ ��� �������� ������ (���������)
//! \return			: 
//! \param          : ULONG ThreadID - ������������� ���������� ������
void
DisconnectClientByThreadID(ULONG ThreadID);

//! \fn				: FreeUnusedClients
//! \brief			: �������� ������������ ������ �� ��������	(���������� �� �������� �� ���������� ������)
//! \return			: TRUE - ���� ��� ����� ���� ���� ������ / FALSE - �� ���� ������� ��������
//! \param          : void
BOOLEAN
FreeUnusedClients(void);

//! \fn				: GetClientPriority
//! \brief			: ��������� ���������� ������� (0 ���� ������ �� ������)
//! \return			: ���������
//! \param          : ULONG AppID - ������������� �������
ULONG
GetClientPriority(ULONG AppID);

//! \fn				: GetFreeSubClient
//! \brief			: ����� �������� ��������� � ����������� ���������
//! \return			: ��������� �� ������ �� ����������
//! \param          : PQCLIENT pClient - ������
PQSUBCLIENT
GetFreeSubClient(PQCLIENT pClient);

void
ReleaseSubClient(PQSUBCLIENT pSubClient);

//! \fn				: GetCurrentSubClient
//! \brief			: ��������� ������� ��� ������������������� �� ������ ��������/������
//! \return			: ��������� �� ����������
//! \param          : PQSUBCLIENT pSubClient - ������ ������ �����������
PQSUBCLIENT
GetCurrentSubClient(PQSUBCLIENT pSubClient);

//! \fn				: ClientSetFlowTimeout - �� ����������� (��������������)
//! \brief			: ��������� ���������� ��������
//! \return			: 
//! \param          : PFLOWTIMEOUT pFlow
void
ClientSetFlowTimeout(PFLOWTIMEOUT pFlow);

//! \fn				: ClientResetCache
//! \brief			: ������� ������ � ����
//! \return			: STATUS_SUCCESS - ������ � ���� ������� / STATUS_UNSUCCESSFUL - ������ ��� ��������� (
//! �� ������ ������, ������ �� ����� ����, etc...
//! \param          : ULONG AppID - ������������� �������
NTSTATUS
ClientResetCache(ULONG AppID);

//+ ------------------------------------------------------------------------------------------
//! \fn				: AcquireClientResource
//! \brief			: ������������ �������� � �������� ��������
//! \return			: 
void
AcquireClientResource(BOOLEAN bExclusive);

//! \fn				: ReleaseClientResource
//! \brief			: ��������������� �������� � �������� ��������
//! \return			: 
void
ReleaseClientResource();

//+ ------------------------------------------------------------------------------------------
//+ ������� ������ � �����
//+ ��� ���� �������: ExpirationTimeShift - ����� �� �������� ������� ������� � ������������

//! \fn				: Obj_CacheReset
//! \brief			: ������� ����
//! \return			: TRUE - ��� ������ / FALSE - ������ ��� ��������� �������
//! \param          : PQCLIENT pClient
BOOLEAN
Obj_CacheReset(PQCLIENT pClient);

//! \fn				: Obj_IsCached
//! \brief			: �������� ������ �� ������� � ����
//! \return			: �� CL_CACHE_??? ���������
//! \param          : PQCLIENT pClient - ��������� �� ���������� ������
//! \param          : DWORD dwVal - ������������� �������
//! \param          : BOOLEAN bNeedProtect - ��� ������� �������� TRUE
//! \param          : PVERDICT pVerdict - ���� ������ ������ � ���� �� ������� ����� �������� ��������������� �������
DWORD
Obj_IsCached(PQCLIENT pClient, DWORD dwVal, BOOLEAN bNeedProtect, PVERDICT pVerdict);

//! \fn				: Obj_CacheAdd
//! \brief			: ���������� ������� � ���
//! \return			: TRUE - ������ �������� / FALSE - ������ ��� ��������� �������
//! \param          : PQCLIENT pClient - ��������� �� ���������� ������
//! \param          : DWORD dwVal - ������������� �������
//! \param          : BOOLEAN bDirty - ������� ��� ����������� ������ � ��� �������� �������� �� ��������� (Obj_CacheUpdate)
//! \param          : VERDICT Verdict - ��������������� ������
//! \param          : ULONG ExpirationTimeShift - ����� ����� ������ � ���� (0 - �� ����������)
BOOLEAN
Obj_CacheAdd(PQCLIENT pClient, DWORD dwVal, BOOLEAN bDirty, VERDICT Verdict, ULONG ExpirationTimeShift);

//! \fn				: Obj_CacheUpdate
//! \brief			: �������� ��������������� ������ � ����
//! \return			: 
//! \param          : PQCLIENT pClient - ��������� �� ���������� ������
//! \param          : DWORD dwVal - ������������� �������
//! \param          : BOOLEAN bDirty - ���������� ������
//! \param          : VERDICT Verdict - ��������������� ������
//! \param          : ULONG ExpirationTimeShift - ����� ����� ������ � ���� (0 - �� ����������)
void
Obj_CacheUpdate(PQCLIENT pClient, DWORD dwVal, VERDICT Verdict, ULONG ExpirationTimeShift);

//! \fn				: Obj_CacheDel
//! \brief			: ������� ������ �� ����
//! \return			: 
//! \param          : PQCLIENT pClient - ��������� �� ���������� ������
//! \param          : DWORD dwVal - ������������� �������
BOOLEAN
Obj_CacheDel(PQCLIENT pClient, DWORD dwVal);

//+ ------------------------------------------------------------------------------------------
//! \fn				: ActivityWatchDogCheck
//! \brief			: �������� ������� (��������� �����)
//! \return			: 
//! \param          : VOID
VOID
ActivityWatchDogCheck(VOID);

//! \fn				: StartAWDog
//! \brief			: ��������� ��������� �����
//! \return			: STATUS_SUCCESS - ����� ������� / STATUS_UNSUCCESSFUL - ���� ��� �������
//! \param          : VOID
NTSTATUS
StartAWDog(VOID);

//! \fn				: StopAWDog
//! \brief			: ���������� ��������� �����
//! \return			: 
//! \param          : VOID
VOID
StopAWDog(VOID);


//+ ------------------------------------------------------------------------------------------
//+ ������ �������

//! \fn				: CalcCacheIDUnSens
//! \brief			: ������ ���� ��� ������ (��� ����� �������� - upperchar)
//! \return			: ���
//! \param          : ULONG size - ����� ������
//! \param          : BYTE* ptr - ��������� �� ������
//! \param          : const DWORD dwInitValue - ���������������� ��������
//! \param          : const BOOLEAN IsUnicode - ������� �������
DWORD
CalcCacheIDUnSens(ULONG size, BYTE* ptr, const DWORD dwInitValue, const BOOLEAN IsUnicode);

//! \fn				: CalcCacheID
//! \brief			: ������ ���� ��� ����� ������
//! \return			: ���
//! \param          : ULONG size - ����� �����
//! \param          : BYTE* ptr - ��������� �� ������
//! \param          : DWORD dwInitValue - ���������������� ��������
DWORD
CalcCacheID(ULONG size, BYTE* ptr, DWORD dwInitValue);


void SuspendSubClient(ULONG pkThread);
void ResumeSubClient(ULONG pkThread);

void ReleasePopupEventsForProcess(ULONG ProcessId, ULONG HookId);

#endif // __CLIENT_H