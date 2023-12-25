#ifndef _FILTER_H
#define _FILTER_H

/*!
*		
*		
*		(C) 2001-3 Kaspersky Lab 
*		
*		\file	filter.h
*		\brief	������� ��������� �������
*		
*		\author Sergey Belov, Andrew Sobko
*		\date	11.09.2003 18:22:12
*		
*		�������� ����� ������ - 
*		1. ��� ������������ ������� ��������� �������� �� ��������� ����� (IsInvisibleThread) (�� �����������, 
*			�������� ��� �� ����� ��������� �� ���� 2)
*		2. ���������, ����� �� ������� ������������� (������� �������� IsNeedFilterEvent...)
*		3. ������������ ������ � �������� EVENT_TRANSMIT (������� ������� ������������ �������)
*		4. ������ �� ���������� (FilterEvent). ���� ��� ���������� ����� �������� ������ � ������� �� ����� ����� 
*			���������� �� ������ ��� ��������� ��������
*		5. ���������� �������
*		
*/		


#include "osspec.h"
#include "evqueue.h"

#include "hook/avpgcom.h"
#include "hook/hookspec.h"

extern BOOLEAN DrvRequestHook(ULONG HookID);
extern BOOLEAN DrvRequestUnhook(ULONG HookID);

//+ ------------------------------------------------------------------------------------------
//+ ������� �������� �������
extern BOOLEAN UnloadInProgress;

//+ ------------------------------------------------------------------------------------------
//+ ���������� �������� ��� ������� ����������
extern ULONG gFilterEventEntersCount;

//! \fn				: GlobalFiltersInit
//! \brief			: ������������� ������� ����������
//! \return			: 
//! \param          : void
void
GlobalFiltersInit(void);

//! \fn				: GlobalFiltersDone
//! \brief			: ������������ ���������� ������
//! \return			: 
//! \param          : void
void
GlobalFiltersDone(void);

//! \fn				: IsNeedFilterEvent
//! \brief			: �������� �� ������������� ���������� ������� (������� ��������) ��� �������� ������
//! \return			: TRUE - ��������� ������ �� ���������� / FALSE - ������� �� ����� �������������
//! \param          : ULONG HookID - ������������� ������������
//! \param          : ULONG FuncMj - ������������� �������
//! \param          : ULONG FuncMi - ������������� ����������
BOOLEAN __stdcall
IsNeedFilterEvent(ULONG HookID, ULONG FuncMj, ULONG FuncMi);

//! \fn				: IsNeedFilterEventEx
//! \brief			: �������� �� ������������� ���������� ������� (������� ��������) ��� ���������� ������
//! \return			: TRUE - ��������� ������ �� ���������� / FALSE - ������� �� ����� �������������
//! \param          : ULONG HookID - ������������� ������������
//! \param          : ULONG FuncMj - ������������� �������
//! \param          : ULONG FuncMi - ������������� ����������
//! \param          : ULONG ThreadID - ������������� ������
BOOLEAN __stdcall
IsNeedFilterEventEx(ULONG HookID, ULONG FuncMj, ULONG FuncMi, HANDLE ThreadID);

#ifdef _HOOK_NT_
//! \fn				: IsNeedFilterEventAsyncChk
//! \brief			: �������� �� ������������� ���������� ������� (������� ��������) ������������� ������ ����� ���� �� IRP
//! \return			: TRUE - ��������� ������ �� ���������� / FALSE - ������� �� ����� �������������
//! \param          : ULONG HookID - ������������� ������������
//! \param          : ULONG FuncMj - ������������� �������
//! \param          : ULONG FuncMi - ������������� ����������
//! \param          : PIRP Irp - ��������� ������
//! \param			: ��������� �������� �� ����������� ������
BOOLEAN
IsNeedFilterEventAsyncChk(ULONG HookID, ULONG FuncMj, ULONG FuncMi,PIRP Irp, BOOLEAN* pInvisible);
#endif

#ifdef CHECK_WHAT_AVPM_DO
// ��������� ������� (��� �������)
//! \fn				: IsNeedFilterEventNoInvCheck
//! \brief			: �������� �� ������������� ���������� ������� (������� ��������) ��� �������� �� ����������� ������
//! \return			: TRUE - ��������� ������ �� ���������� / FALSE - ������� �� ����� �������������
//! \param          : ULONG HookID - ������������� ������������
//! \param          : ULONG FuncMj - ������������� �������
//! \param          : ULONG FuncMi - ������������� ����������
BOOLEAN
IsNeedFilterEventNoInvCheck(ULONG HookID, ULONG FuncMj, ULONG FuncMi);
#endif

//! \fn				: FilterEvent
//! \brief			: ����������� �������
//! \return			: VERDICT - ��������� ���������� (����������, ���������, etc...)
//! \param          : PFILTER_EVENT_PARAM pEventParam - ������ � �������
//! \param          : PEVENT_OBJECT_INFO pEventObject - ��������������� � �������� ������ (�����������)
VERDICT __stdcall
FilterEvent(PFILTER_EVENT_PARAM pEventParam, PEVENT_OBJECT_INFO pEventObject);

//! \fn				: FilterTransmit
//! \brief			: ����� ����������� ��������� ������� (��������, �������, etc..)
//! \return			: STATUS_SUCCESS - ������� / ���� ������
//! \param          : PFILTER_TRANSMIT pFilterTransmitIn - ������� �����
//! \param          : PFILTER_TRANSMIT pFilterTransmitOut - ��������� ��������� �������
//! \param          : ULONG OutputBufferLength - ������ ��������� ������
NTSTATUS
FilterTransmit(PFILTER_TRANSMIT pFilterTransmitIn, PFILTER_TRANSMIT pFilterTransmitOut, ULONG OutputBufferLength);

//! \fn				: SaveFilters
//! \brief			: ��������� ������� ��� ���������� ������� � ������� (���������������� ������ ��� ������ ��������)
//! \return			: TRUE - ������� / FALSE - ���� ��� ����������
//! \param          : PQCLIENT pClient - ���������� ���������
BOOLEAN
SaveFilters(PQCLIENT pClient);

//! \fn				: LoadFilters
//! \brief			: ������������ ������� �� ������� ��� �������
//! \return			: STATUS_SUCCESS - ������� / ���� ������
NTSTATUS
LoadFilters();

//! \fn				: _FreeAppFilters
//! \brief			: ������� ������� ��� �������
//! \return			: 
//! \param          : PQCLIENT pClient - ���������� ���������
void
_FreeAppFilters(PQCLIENT pClient);
//+ ------------------------------------------------------------------------------------------

//! \fn				: GetSingleParamPtr
//! \brief			: ����� ��������� ������� �� ��������������
//! \return			: NULL - �������� �� ������ / ��������� �� ������
//! \param          : PFILTER_EVENT_PARAM pEventParam - ��������� �� �������
//! \param          : ULONG ParamID - ������������� ���������
PSINGLE_PARAM
GetSingleParamPtr(PFILTER_EVENT_PARAM pEventParam, ULONG ParamID);

//! \fn				: InitStartFiltering
//! \brief			: ������������ ������ ��� �������� ������� �� ���������� �� �������
//! \return			: 
//! \param          : PEXT_START_FILTERING pStartFiltering - ����������� ������
void
InitStartFiltering(PEXT_START_FILTERING pStartFiltering);

//! \fn				: MatchWithPatternW
//! \brief			: �������� ������ �� ����� (������)
//! \return			: TRUE - ��������� / FALSE - �� ��������� :)
//! \param          : PWCHAR Pattern - ������� (� ������� '*string*')
//! \param          : PWCHAR Name - ������������ ������
//! \param          : BOOLEAN CaseSensivity - ��������� �� �������� � ������ ��������
__inline BOOLEAN
MatchWithPatternW(PWCHAR Pattern, PWCHAR Name, BOOLEAN CaseSensivity);

#ifdef _HOOK_NT_
// dispatch filters
	void
	Di_PauseClient(ULONG AppID, BOOLEAN bGoSleep);
#else
	#define Di_PauseClient
#endif

#endif // _FILTER_H