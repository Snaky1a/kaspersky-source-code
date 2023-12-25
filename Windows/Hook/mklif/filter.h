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

#include "mtypes.h"
#include "osspec.h"
#include "structures.h"
#include "debug.h"

#include "evqueue.h"

#include "../hook/avpgcom.h"
#include "../hook/hookspec.h"

typedef struct _QFLT
{
    LIST_ENTRY		m_List;
	ULONG			m_ClientId;
	ULONG			m_HookID;
	ULONG			m_Mj;
	ULONG			m_Mi;
	ULONG			m_FilterID;
	PROCESSING_TYPE	m_ProcessingType;
	CHAR			m_pProcName[PROCNAMELEN];
	ULONG			m_Flags;
	ULONG			m_Timeout;
	__int64			m_Expiration;
	ULONG			m_ParamsCount;
	BYTE			m_Params[0];		// FILTER_PARAM 
}QFLT, *PQFLT;

//+ ------------------------------------------------------------------------------------------
//! \fn				: GlobalFiltersInit
//! \brief			: ������������� ������� ����������
//! \return			: 
//! \param          : void
BOOLEAN
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
//! \param          : ThreadID - ������������� ������
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
IsNeedFilterEventAsyncChk(ULONG HookID, ULONG FuncMj, ULONG FuncMi, PIRP Irp, BOOLEAN* pInvisible);
#endif

//! \fn				: FilterEvent
//! \brief			: ����������� �������
//! \return			: tefVerdict - ��������� ���������� (����������, ���������, etc...)
//! \param          : PFILTER_EVENT_PARAM pEventParam - ������ � �������
//! \param          : PEVENT_OBJ pEventObj - ��������������� � �������� ������ (�����������)
//! \param          : ULONG ClientId - ������ ������������� ������� ���� ������������� ������� (0 - ���� ����)
tefVerdict
FilterEventImp (
	PFILTER_EVENT_PARAM pEventParam,
	PEVENT_OBJ pEventObj,
	ULONG ClientId
	);

VERDICT
__stdcall
FilterEvent (
	PFILTER_EVENT_PARAM pEventParam,
	PEVENT_OBJ pEventObj
	);

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

NTSTATUS
SaveFiltersForApp (
	ULONG ClientID
	);

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
Filters_FreeAppFilters (
	ULONG ClientId
	);

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


ULONG CalcFilterTransmitSize ( 
	PFILTER_TRANSMIT pFltIn
	);

BOOLEAN
CheckEventParams (
	PFILTER_EVENT_PARAM pEvent,
	ULONG EventSize
	);

VOID
DrvRestartHook (
	);

VOID
Di_PauseClient (
	ULONG AppID,
	BOOLEAN bGoSleep
	);

NTSTATUS
Filters_GetCountFor (
	ULONG ClientID,
	PULONG pFiltersCount
	);

ULONG
Filters_CalcParamSize (
	PQFLT pQFlt,
	ULONG* pParamSize
	);

VOID
Filters_FillOutData (
	PFILTER_TRANSMIT pFilterOut,
	PQFLT pQFlt,
	ULONG FilterParamsSize
	);

PQFLT
Filters_Find (
	ULONG ClientId,
	ULONG FilterId
	);

PQFLT
Filters_FindNext (
	ULONG AppID,
	ULONG StartFilterId
	);

NTSTATUS
Filters_ChangeParams (
	ULONG ClientId,
	ULONG FilterId,
	ULONG ParamsCount,
	PFILTER_PARAM pParams
	);

void
Filters_Release (
	PQFLT pQFlt
	);

#endif // _FILTER_H