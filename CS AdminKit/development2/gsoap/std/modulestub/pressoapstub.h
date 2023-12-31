/*!
 * (C) "Kaspersky Lab"
 *
 * \file pressoapstub.h
 * \author Generated by createsoapheader.pl
 * \brief SOAP stub declaration and registration code
 */

#include "soapH.h"

#include "std/gsoap/stubrouter.h"

/* Declaration of functions */

int KLPRES_ResetSubscriptionsIteratorStub(  struct soap *soap, xsd__wstring sServerObjectID,
									  SOAPComponentId cidFilter,
                                      xsd__int  nTimeout,
									  struct KLPRES_RESET_SUBSCRIPTIONS_ITERATOR_RESPONSE &rc);

int KLPRES_ReleaseSubscriptionsIteratorStub(  struct soap *soap, xsd__wstring sServerObjectID,
									  xsd__wstring sSubscrIteratorId,
									  struct KLPRES_RELEASE_SUBSCRIPTIONS_ITERATOR_RESPONSE &rc);

int KLPRES_GetNextSubscriptionStub(  struct soap *soap,  xsd__wstring sServerObjectID,
							    xsd__wstring sSubscrIteratorId,
							    struct KLPRES_GET_NEXT_SUBSCRIPTION_RESPONSE &rc);

int KLPRES_AddSubscriptionStub(  struct soap *soap, xsd__wstring sServerObjectID,
						   xsd__wstring sSubscriptionID,
						   bool bPersistent, 
						   param__params parSubscription,
						   struct KLPRES_ADD_SUBSCRIPTION_RESPONSE &rc);

int KLPRES_UpdateSubscriptionStub(  struct soap *soap, xsd__wstring sServerObjectID,
							  xsd__wstring sSubscriptionID,
							  param__params parSubscription,
							  struct param_error& rc);

int KLPRES_PauseSubscriptionStub(  struct soap *soap, xsd__wstring sServerObjectID,
							  xsd__wstring sSubscriptionID,
							  struct param_error& rc);

int KLPRES_ResumeSubscriptionStub(  struct soap *soap, xsd__wstring sServerObjectID,
							  xsd__wstring sSubscriptionID,
							  struct param_error& rc);

int KLPRES_RemoveSubscriptionStub(  struct soap *soap, xsd__wstring sServerObjectID,
							  xsd__wstring sSubscriptionID, 
							  struct param_error& rc);

int KLPRES_ResetEventsIteratorStub(  struct soap *soap, xsd__wstring sServerObjectID,
							   xsd__wstring sSubscriptionID,
							   struct param_error &rc);

int KLPRES_SetEventsIteratorStub(  struct soap *soap, xsd__wstring sServerObjectID,
							 xsd__wstring sSubscriptionID,
							 long eventID,
							 struct param_error &rc);

int KLPRES_ResetEventsIteratorExStub(  struct soap *soap, xsd__wstring sServerObjectID,
								 xsd__wstring sSubscriptionID,
								 struct KLPRES_RESET_EVENTS_ITERATOR_EX_RESPONSE &rc);

int KLPRES_SetEventsIteratorExStub(  struct soap *soap, xsd__wstring sServerObjectID,
							   xsd__wstring sSubscriptionID,
							   long eventID,
							   struct KLPRES_SET_EVENTS_ITERATOR_EX_RESPONSE &rc);

int KLPRES_MoveToEventWithIndexStub(  struct soap *soap, xsd__wstring sServerObjectID,
							    xsd__wstring sSubscriptionID,
							    long nIndex,
								struct param_error &rc);

int KLPRES_GetEventsCountStub(  struct soap *soap, xsd__wstring sServerObjectID,
						  xsd__wstring sSubscriptionID,
						  struct KLPRES_GET_EVENTS_COUNT_RESPONSE &rc);

int KLPRES_GetNextEventsChunkStub(  struct soap *soap, xsd__wstring sServerObjectID,
							  xsd__wstring sSubscriptionID,
							  struct KLPRES_GET_NEXT_EVENTS_CHUNK_RESPONSE &rc);

int KLPRES_ClearEventsListStub(  struct soap *soap, xsd__wstring sServerObjectID,
						   xsd__wstring sSubscriptionID, 
						   struct param_error& rc);

int KLPRES_DeleteEventsStub(  struct soap *soap, xsd__wstring sServerObjectID,
						xsd__wstring sSubscriptionID, 
						long nStopEventID, 
						struct param_error& rc);

int KLPRES_DeleteOneEventByIDStub(  struct soap *soap, xsd__wstring sServerObjectID,
							  xsd__wstring sSubscriptionID, 
							  long nEventID, 
						      struct param_error& rc);

int KLPRES_DeleteRangesStub(  struct soap *soap, xsd__wstring sServerObjectID,
						xsd__wstring sSubscriptionID, 
						param__params parRanges, 
                        struct param_error& rc);

int KLPRES_RemoveExpiredEventsStub(  struct soap *soap, xsd__wstring sServerObjectID,
							   xsd__wstring sSubscriptionID, 
							   struct param_error& rc);

int KLPRES_GetEventStorageFileSizeStub(  struct soap *soap, xsd__wstring sServerObjectID,
									xsd__wstring sSubscriptionID, 
									struct KLPRES_GET_EVENT_STORAGE_FILE_SIZE_RESPONSE& rc);

namespace KLPRES
{

	struct KLSTRT::SOAPStubFunc pres_funcs_ptrs[22]=
	{
		{ L"KLPRES_ResetSubscriptionsIterator",		 (void*)KLPRES_ResetSubscriptionsIteratorStub },
		{ L"KLPRES_ReleaseSubscriptionsIterator",		 (void*)KLPRES_ReleaseSubscriptionsIteratorStub },
		{ L"KLPRES_GetNextSubscription",		 (void*)KLPRES_GetNextSubscriptionStub },
		{ L"KLPRES_AddSubscription",		 (void*)KLPRES_AddSubscriptionStub },
		{ L"KLPRES_UpdateSubscription",		 (void*)KLPRES_UpdateSubscriptionStub },
		{ L"KLPRES_PauseSubscription",		 (void*)KLPRES_PauseSubscriptionStub },
		{ L"KLPRES_ResumeSubscription",		 (void*)KLPRES_ResumeSubscriptionStub },
		{ L"KLPRES_RemoveSubscription",		 (void*)KLPRES_RemoveSubscriptionStub },
		{ L"KLPRES_ResetEventsIterator",		 (void*)KLPRES_ResetEventsIteratorStub },
		{ L"KLPRES_SetEventsIterator",		 (void*)KLPRES_SetEventsIteratorStub },
		{ L"KLPRES_ResetEventsIteratorEx",		 (void*)KLPRES_ResetEventsIteratorExStub },
		{ L"KLPRES_SetEventsIteratorEx",		 (void*)KLPRES_SetEventsIteratorExStub },
		{ L"KLPRES_MoveToEventWithIndex",		 (void*)KLPRES_MoveToEventWithIndexStub },
		{ L"KLPRES_GetEventsCount",		 (void*)KLPRES_GetEventsCountStub },
		{ L"KLPRES_GetNextEventsChunk",		 (void*)KLPRES_GetNextEventsChunkStub },
		{ L"KLPRES_ClearEventsList",		 (void*)KLPRES_ClearEventsListStub },
		{ L"KLPRES_DeleteEvents",		 (void*)KLPRES_DeleteEventsStub },
		{ L"KLPRES_DeleteOneEventByID",		 (void*)KLPRES_DeleteOneEventByIDStub },
		{ L"KLPRES_DeleteRanges",		 (void*)KLPRES_DeleteRangesStub },
		{ L"KLPRES_RemoveExpiredEvents",		 (void*)KLPRES_RemoveExpiredEventsStub },
		{ L"KLPRES_GetEventStorageFileSize",		 (void*)KLPRES_GetEventStorageFileSizeStub },
		{ L"", NULL },
	};

	void RegisterGSOAPStubFunctions()
	{
		KLSTRT::RegisterGSOAPStubFunctions( pres_funcs_ptrs, (sizeof(pres_funcs_ptrs)/sizeof(pres_funcs_ptrs[0])) );
	}

	void UnregisterGSOAPStubFunctions()
	{
		KLSTRT::UnregisterGSOAPStubFunctions( pres_funcs_ptrs, (sizeof(pres_funcs_ptrs)/sizeof(pres_funcs_ptrs[0])) );
	}

} // end namespace KLPRES
