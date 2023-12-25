#ifndef _EVQUEUE_H
#define _EVQUEUE_H

/*!
*		
*		
*		(C) 2001-3 Kaspersky Lab 
*		
*		\file	evqueue.h
*		\brief	��������� ������� ��� �������� (������� �������, ������������ ������� ���������, etc...)
*		
*		\author Sergey Belov, Andrew Sobko
*		\date	11.09.2003 17:06:58
*		
*		�������� ����� ��������� �������
*		1. ���������� ������ ������� � ������� (QueueAdd)
*		2. ���������� ������� � ����� ������� (PulseEventToSubClientSafe)
*		3. ������������ ������� � ����� ������ (GetEventForClient)
*		4. ��������� ��������� ������� �������� (EventSetVerdict)
*/		


#include "osspec.h"
#include "klsecur.h"

#include "hook/avpgcom.h"

//+ ------------------------------------------------------------------------------------------
//+ ���������� �������� ��� ������� ��������� �������
extern ULONG gDeadLocks;
extern ULONG gReplyWaiterEnters;
//+ ------------------------------------------------------------------------------------------

//! \fn				: InitEventList
//! \brief			: ������������� ������� �������
//! \return			: TRUE - ������� / FALSE - ����
//! \param          : PEVENT_LIST pEvList - �������
BOOLEAN
InitEventList(PEVENT_LIST pEvList);

//! \fn				: DoneEventList
//! \brief			: ������������ ������� (��� ������� ����� ������� ������� �� ���������)
//! \return			: 
//! \param          : PEVENT_LIST pEvList - �������
void
DoneEventList(PEVENT_LIST pEvList);

//! \fn				: ReleaseMarkedEvents
//! \brief			: ������������ ������������� ����������� ������� (��-�� ����������...)
//! \return			: 
//! \param          : ULONG AppID - ������������� �������
//! \param          : PEVENT_LIST pEvList - ������
//! \param          : ULONG ProcessID - ��������� �������
void
ReleaseMarkedEvents(ULONG AppID, PEVENT_LIST pEvList, ULONG ProcessID);

//! \fn				: ReleaseEvents
//! \brief			: �������� ���� ������� � ������� (��� ������� ����� ������� ������� �� ���������)
//! \return			: 
//! \param          : ULONG AppID - ������������� �������
//! \param          : PEVENT_LIST pEvList - �������
void
ReleaseEvents(ULONG AppID, PEVENT_LIST pEvList);

void
ReleasePopupEventsByProcess(PEVENT_LIST pEvList, ULONG ProcessId, ULONG HookId);

//! \fn				: SkipEventForClient
//! \brief			: ���������� ������ ��������������� ������� � ������� (������� ������� �� ���������)
//! \return			: STATUS_SUCCESS - ������� ���������� / STATUS_NOT_FOUND - ��� ������� � �������
//! \param          : ULONG AppID - ������������� �������
NTSTATUS
SkipEventForClient(ULONG AppID);

//! \fn				: GetEventForClient
//! \brief			: ������������ � ����������� �������� �������
//! \return			: TRUE - ������� ������������� / FALSE ���� ��� ���������
//! \param          : PGET_EVENT pGetEvent - ����� ��� ������������
//! \param          : PEVENT_TRANSMIT pEventTransmit - �������
//! \param          : DWORD* pOutputBufferLength - �� ����� ������ ������, �� ������ ������ ������ �������
BOOLEAN
GetEventForClient(PGET_EVENT pGetEvent, PEVENT_TRANSMIT pEventTransmit, DWORD* pOutputBufferLength);

//! \fn				: EventSetVerdict
//! \brief			: ��������� ���������� ��������� ������� (����� ������� �� �������, ��������� -> �����������)
//! \return			: STATUS_SUCCESS - ������� / STATUS_UNSUCCESSFUL - �� ���������� (��� �������, etc..)
//! \param          : PSET_VERDICT pSetVerdict - ��������� �� �������
NTSTATUS
EventSetVerdict(PSET_VERDICT pSetVerdict);

//! \fn				: YeldEventForClient
//! \brief			: ������� �� ��������� ������� � ������� �� ����������� ������� (����������� ��������� ������ �� 
//! ������������� ������
//! \return			: STATUS_SUCCESS - ������� / STATUS_NOT_FOUND - ������� �� �������, ������ ������
//! \param          : PYELD_EVENT pYeldEvent - ��������� �� ������ �������
//! \param          : ULONG InYeldSize - ������ ������� ������
//! \param          : PCHAR OutputBuffer - ��������� �� �������������� ������
//! \param          : DWORD* pOutDataLen - �� ����� ������ ��������� ������, �� ������ ������ �������� ������
NTSTATUS
YeldEventForClient(PYELD_EVENT pYeldEvent, ULONG InYeldSize, PCHAR OutputBuffer, DWORD* pOutDataLen);

//! \fn				: GetEventSizeForClient
//! \brief			: ��������� ������� ����� ������ ��� ������� ���������������� �������
//! \return			: 
//! \param          : ULONG AppID - ������������� �������
//! \param          : DWORD *pSize - ��������� �� �����, ���� ����� ������� ��������� (0 - �� �������)
void
GetEventSizeForClient(ULONG AppID, DWORD *pSize);

//! \fn				: QueueAdd
//! \brief			: �������� ����� ������� � ������� ��� ���������
//! \return			: ��������� �� ���� ������ �������
//! \param          : PFILTER_EVENT_PARAM pEventParam - ������ �� ������������
//! \param          : PEVENT_LIST pEvList - ������� ������� �������
//! \param          : PFILTER_SUB pFilterSub - ������ �� �������
//! \param          : ULONG YeldTimeout - ������������ ����� ��������� �������
//! \param          : DWORD EventFlags - ������, ���������� ��� ����������
//! \param          : DWORD dwClientFalgs - ������ � �������
//! \param          : PEVENT_OBJECT_INFO pEventObject - ��������������� � �������� ������
PQELEM
QueueAdd(PFILTER_EVENT_PARAM pEventParam, PEVENT_LIST pEvList, PFILTER_SUB pFilterSub, ULONG YeldTimeout, 
		 DWORD EventFlags, DWORD dwClientFalgs, PEVENT_OBJECT_INFO pEventObject);

//! \fn				: DoEventRequest
//! \brief			: �������������� ������� ��� ��������� ������� (+ ��������� ��������� ������� � �������)
//! \return			: 
//! \param          : PEVENT_OBJECT_REQUEST pInRequest - ������ �� ���������
//! \param          : PVOID pOutRequest - ��������� ���������
//! \param          : ULONG OutRequestSize - ������ ��������� ������
//! \param          : DWORD* pOutDataLen - ������ �������� ������
NTSTATUS
DoEventRequest(PEVENT_OBJECT_REQUEST pInRequest, PVOID pOutRequest, ULONG OutRequestSize, DWORD* pOutDataLen);

//+ ------------------------------------------------------------------------------------------

//! \fn				: ReplyWaiter
//! \brief			: ������� ��������� �������� ������ �� ��������� ��������� �������
//! \return			: 
//! \param          : PQSUBCLIENT pSubClient - ���������, ����������� �������
//! \param          : PEVENT_LIST pEvList - ������� �������
//! \param          : PQELEM pEventElem - �������
//! \param          : PCHAR pUrl - ���. ���.:  ��� �������
//! \param          : ULONG AppID - ���. ���.: ������������� �������
//! \param          : peReplyWaiter peReply - ��������� �� ��������� ��������� �������
VERDICT
ReplyWaiter(PQSUBCLIENT pSubClient, PEVENT_LIST pEvList, PQELEM pEventElem, PCHAR pUrl, ULONG AppID, 
			peReplyWaiter peReply);

//! \fn				: PulseEventToSubClientSafe
//! \brief			: ����������� ������� � ���������� ������� (������� ����� ���� �� �������� � �������)
//! \return			: 
//! \param          : PQSUBCLIENT pSubClient - ��������� ���������
//! \param          : BOOLEAN bWhistlerUp - ��� ������� ������������� (WhistlerUp / WhistlerChanged)
//! \param          : DWORD DeadLockWatchDog - ����� �� �������� �������
//! \param          : ULONG AppID - ������������� ����������
BOOLEAN
PulseEventToSubClientSafe(PQSUBCLIENT pSubClient, BOOLEAN bWhistlerUp, DWORD DeadLockWatchDog, ULONG AppID);

//! \fn				: BlueScreenReq
//! \brief			: ������ � ������� � Ring0
//! \return			: ��������� �������
//! \param          : PFILTER_EVENT_PARAM pEventParam - ������ �������
//! \param          : PCHAR pUrl - ��������� �������� �������
VERDICT
BlueScreenReq(PFILTER_EVENT_PARAM pEventParam, PCHAR pUrl);

#ifdef __DBG__
//! \fn				: ShowEventsInfo
//! \brief			: ��������� �������, ������� ������� � ������� � DebugOutput
//! \return			: 
//! \param          : PEVENT_LIST pEvList - ������� �������
void
ShowEventsInfo(PEVENT_LIST pEvList);
#endif

//+ ------------------------------------------------------------------------------------------
//! \fn				: ImpersonateThreadForClient
//! \brief			: ������������������ ������� ����� ��� ����� ��� ���������� �������
//! \return			: 
//! \param          : PIMPERSONATE_REQUEST pImperonate - ������ �� ����������������
NTSTATUS
ImpersonateThreadForClient(PIMPERSONATE_REQUEST pImperonate);

#endif // _EVQUEUE_H