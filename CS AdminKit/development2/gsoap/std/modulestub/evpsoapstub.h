/*!
 * (C) "Kaspersky Lab"
 *
 * \file evpsoapstub.h
 * \author Generated by createsoapheader.pl
 * \brief SOAP stub declaration and registration code
 */

#include "soapH.h"

#include "std/gsoap/stubrouter.h"

/* Declaration of functions */

int klevprop_ResetIteratorStub(  struct soap *soap, 
        xsd__int		            type,
        param__params		        paramIteratorDescr,
		klevprop_wstring_array		fields,
		klevprop_field_order_array	fields_to_order,
		xsd__int					lifetime,
		struct klevprop_ResetIteratorResponse&r);

int klevprop_GetRecordCountStub(  struct soap *soap, 
		xsd__wstring	iteratorId,
		struct klevprop_GetRecordCountResponse&r);

int klevprop_GetRecordRangeStub(  struct soap *soap, 
		xsd__wstring	iteratorId,
		xsd__int		nStart,
        xsd__int		nEnd,
		struct klevprop_GetRecordRangeResponse&r);

int klevprop_FindRecordByFirstCharsStub(  struct soap *soap, 
		xsd__wstring	iteratorId,
        xsd__wstring	wstrFieldToSearch,
        xsd__wstring	wstrFirstChars,
		struct klevprop_FindRecordByFirstCharsResponse
        &r);

int klevprop_DeletePropertiesStub(  struct soap *soap, 
		klevprop_int_array	id_array,
		struct klevprop_DeletePropertiesResponse&r);

int klevprop_InitiateDeleteStub(  struct soap *soap, 
		param__params	paramSettings,
		struct klevprop_InitiateDeleteResponse&r);

int klevprop_CancelDeleteStub(  struct soap *soap, 
		param__params	paramSettings,
		struct klevprop_CancelDeleteResponse&r);

int klevprop_ReleaseIteratorStub(  struct soap *soap, 
		xsd__wstring	iteratorId,
		struct klevprop_ReleaseIteratorResponse&r);

int klevproc_ProcessStub(  struct soap *soap, 
		param__params		parEventInfoArray,
		xsd__wstring		deliveryId,
		xsd__wstring		domain,
		xsd__wstring		hostName,
		xsd__wstring		agentId,
		struct klevproc_ProcessResponse&r);

int klevpnp_GetDefaultSettingsStub(  struct soap *soap, 
		void* _,
		struct klevpnp_GetDefaultSettingsResponse&r);

int klevpnp_SetDefaultSettingsStub(  struct soap *soap, 
		param__params	    paramDefaultSettings,
		struct klevpnp_SetDefaultSettingsResponse&r);

int klevpnp_TestNotificationStub(  struct soap *soap, 
    param__params    paramSettings,
	struct klevpnp_TestNotificationResponse&r);

int klevpnp_SetNotificationLimitsStub(  struct soap *soap, 
    param__params    paramSettings,
	struct klevpnp_SetNotificationLimitsResponse&r);

int klevpnp_GetNotificationLimitsStub(  struct soap *soap, 
    void* _,
	struct klevpnp_GetNotificationLimitsResponse&r);

int klevpnp_GetCommonPropertiesStub(  struct soap *soap, 
		void* _,
		struct klevpnp_GetCommonPropertiesResponse&r);

int klevpnp_GetGroupPropertiesStub(  struct soap *soap, 
		xsd__int			nGroupId,
		struct klevpnp_GetGroupPropertiesResponse&r);

int klevpnp_GetTaskPropertiesStub(  struct soap *soap, 
		xsd__wstring			wstrTaskId,
		struct klevpnp_GetTaskPropertiesResponse&r);

int klevpnp_SetCommonPropertiesStub(  struct soap *soap, 
		klevpnp_notification_descr_array	notificationDescrArray,
		struct klevpnp_SetCommonPropertiesResponse&r);

int klevpnp_SetGroupPropertiesStub(  struct soap *soap, 
		xsd__int							nGroupId,
		klevpnp_notification_descr_array	notificationDescrArray,
		struct klevpnp_SetGroupPropertiesResponse&r);

int klevpnp_SetTaskPropertiesStub(  struct soap *soap, 
		xsd__wstring			wstrTaskId,
		klevpnp_notification_descr_array	notificationDescrArray,
		struct klevpnp_SetTaskPropertiesResponse&r);

namespace KLEVP
{

	struct KLSTRT::SOAPStubFunc evp_funcs_ptrs[21]=
	{
		{ L"klevprop_ResetIterator",		 (void*)klevprop_ResetIteratorStub },
		{ L"klevprop_GetRecordCount",		 (void*)klevprop_GetRecordCountStub },
		{ L"klevprop_GetRecordRange",		 (void*)klevprop_GetRecordRangeStub },
		{ L"klevprop_FindRecordByFirstChars",		 (void*)klevprop_FindRecordByFirstCharsStub },
		{ L"klevprop_DeleteProperties",		 (void*)klevprop_DeletePropertiesStub },
		{ L"klevprop_InitiateDelete",		 (void*)klevprop_InitiateDeleteStub },
		{ L"klevprop_CancelDelete",		 (void*)klevprop_CancelDeleteStub },
		{ L"klevprop_ReleaseIterator",		 (void*)klevprop_ReleaseIteratorStub },
		{ L"klevproc_Process",		 (void*)klevproc_ProcessStub },
		{ L"klevpnp_GetDefaultSettings",		 (void*)klevpnp_GetDefaultSettingsStub },
		{ L"klevpnp_SetDefaultSettings",		 (void*)klevpnp_SetDefaultSettingsStub },
		{ L"klevpnp_TestNotification",		 (void*)klevpnp_TestNotificationStub },
		{ L"klevpnp_SetNotificationLimits",		 (void*)klevpnp_SetNotificationLimitsStub },
		{ L"klevpnp_GetNotificationLimits",		 (void*)klevpnp_GetNotificationLimitsStub },
		{ L"klevpnp_GetCommonProperties",		 (void*)klevpnp_GetCommonPropertiesStub },
		{ L"klevpnp_GetGroupProperties",		 (void*)klevpnp_GetGroupPropertiesStub },
		{ L"klevpnp_GetTaskProperties",		 (void*)klevpnp_GetTaskPropertiesStub },
		{ L"klevpnp_SetCommonProperties",		 (void*)klevpnp_SetCommonPropertiesStub },
		{ L"klevpnp_SetGroupProperties",		 (void*)klevpnp_SetGroupPropertiesStub },
		{ L"klevpnp_SetTaskProperties",		 (void*)klevpnp_SetTaskPropertiesStub },
		{ L"", NULL },
	};

	void RegisterGSOAPStubFunctions()
	{
		KLSTRT::RegisterGSOAPStubFunctions( evp_funcs_ptrs, (sizeof(evp_funcs_ptrs)/sizeof(evp_funcs_ptrs[0])) );
	}

	void UnregisterGSOAPStubFunctions()
	{
		KLSTRT::UnregisterGSOAPStubFunctions( evp_funcs_ptrs, (sizeof(evp_funcs_ptrs)/sizeof(evp_funcs_ptrs[0])) );
	}

} // end namespace KLEVP
