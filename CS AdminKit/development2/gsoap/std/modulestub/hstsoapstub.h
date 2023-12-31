/*!
 * (C) "Kaspersky Lab"
 *
 * \file hstsoapstub.h
 * \author Generated by createsoapheader.pl
 * \brief SOAP stub declaration and registration code
 */

#include "soapH.h"

#include "std/gsoap/stubrouter.h"

/* Declaration of functions */

int klhst_UseKeepConnectionStub(  struct soap *soap, 
					xsd__wstring		host,
					struct klhst_UseKeepConnectionResponse&r);

int klhst_AddHostsStub(  struct soap *soap, 
					param__params	info,
					struct klhst_AddHostsResponse&r);

int klhst_GetHostTasksStub(  struct soap *soap, 
					xsd__wstring		host,
					xsd__wstring		product,
					xsd__wstring		version,
					xsd__int			lifetime,
					struct klhst_GetHostTasksResponse&r);

int klhst_GetDomainsStub(  struct soap *soap, 
					void* _,
					struct klhst_GetDomainsResponse&r);

int klhst_GetDomainHostsStub(  struct soap *soap, 
					xsd__wstring domain,
					struct klhst_GetDomainHostsResponse&r);

int klhst_GetHostInfoStub(  struct soap *soap, 
					  xsd__wstring		name,
					  klhst_wstrings	fields,
					  struct klhst_GetHostInfoResponse&r);

int klhst_AddDomainStub(  struct soap *soap, 
					  xsd__wstring		domain,
					  xsd__int			type,
					  struct klhst_AddDomainResponse&r);

int klhst_DelDomainStub(  struct soap *soap, 
					  xsd__wstring		domain,
					  struct klhst_DelDomainResponse&r);

int klhst_AddHostStub(  struct soap *soap, 
					  param__params		info,
					  struct klhst_AddHostResponse&r);

int klhst_DelHostStub(  struct soap *soap, 
					  xsd__wstring		name,
					  struct klhst_DelHostResponse&r);

int klhst_UpdateHostStub(  struct soap *soap, 
					  xsd__wstring		name,
					  param__params		info,
					  struct klhst_UpdateHostResponse&r);

int klhst_GetHostProductsStub(  struct soap *soap, 
					  xsd__wstring		name,
					  struct klhst_GetHostProductsResponse&r);

int klhst_SS_ReadStub(  struct soap *soap, 
				  xsd__wstring	name,
				  xsd__wstring	type,
				  xsd__wstring	product,
				  xsd__wstring	version,
				  xsd__wstring	section,
				  xsd__int		timeout,
				  struct klhst_SS_ReadResponse&r);

int klhst_SS_WriteStub(  struct soap *soap, 
					xsd__wstring	name,
					xsd__wstring	type,
					xsd__wstring	product,
					xsd__wstring	version,
					xsd__wstring	section,
					xsd__int		flags,
					param__params	data,
					xsd__int		timeout,
					struct klhst_SS_WriteResponse&r);

int klhst_SS_CreateSectionStub(  struct soap *soap, 
					xsd__wstring	name,
					xsd__wstring	type,
					xsd__wstring	product,
					xsd__wstring	version,
					xsd__wstring	section,
					xsd__int		timeout,
					struct klhst_SS_CreateSectionResponse&r);

int klhst_SS_DeleteSectionStub(  struct soap *soap, 
					xsd__wstring	name,
					xsd__wstring	type,
					xsd__wstring	product,
					xsd__wstring	version,
					xsd__wstring	section,
					xsd__int		timeout,
					struct klhst_SS_DeleteSectionResponse&r);

int klhst_SS_GetNamesStub(  struct soap *soap, 
					xsd__wstring	name,
					xsd__wstring	type,
					xsd__wstring	product,
					xsd__wstring	version,
					xsd__int		timeout,
					struct klhst_SS_GetNamesResponse&r);

int klhst_CallGetRunTimeInfoStub(  struct soap *soap, 
					xsd__wstring	name,
					param__params filter,
					struct klhst_CallGetRunTimeInfoResponse&r);

int klhst_CallGetStaticInfoStub(  struct soap *soap, 
					xsd__wstring	name,
					param__params filter,
					struct klhst_CallGetStaticInfoResponse&r);

int klhst_CallGetStatisticsStub(  struct soap *soap, 
					xsd__wstring	name,
					param__params filter,
					struct klhst_CallGetStatisticsResponse&r);

int klhst_CallGetInstancePortStub(  struct soap *soap, 
					xsd__wstring	name,
					xsd__wstring	product,
					xsd__wstring	version,
					xsd__wstring	component,
					xsd__wstring	instance,
					struct klhst_CallGetInstancePortResponse&r);

int klhst_NotifyTaskStub(  struct soap *soap, 
                        xsd__wstring	name,
                        struct klhst_NotifyTaskResponse& r);

int klupdt_GetUpdatesInfoStub(  struct soap *soap, 
                    param__params filter,
					struct klupdt_GetUpdatesInfoResponse&r);

int klupdt_SetBundleOptionsStub(  struct soap *soap, 
                    param__params paramOptions,
					struct klupdt_SetBundleOptionsResponse&r);

int klupdt_SetGeneralOptionsStub(  struct soap *soap, 
                    param__params paramOptions,
					struct klupdt_SetGeneralOptionsResponse&r);

int klupdt_GetGeneralOptionsStub(  struct soap *soap, 
                    param__params data,
					struct klupdt_GetGeneralOptionsResponse&r);

int klupdt_GetAvailableUpdatesInfoStub(  struct soap *soap, 
					xsd__wstring wstrLocalization,
					struct klupdt_GetAvailableUpdatesInfoResponse&r);

int klupdt_GetRequiedUpdatesInfoStub(  struct soap *soap, 
					int nDummy,
					struct klupdt_GetRequiedUpdatesInfoResponse&r);

int kllicsrv_GetKeysInfoStub(  struct soap *soap, 
                    klhst_wstrings              fields,
                    xsd__wstring	            filter,
                    xsd__int                    lTimeout,
                    param__params	            options,
                    struct kllicsrv_GetKeysInfoResponse&r);

int kllicsrv_GetKeyInfoStub(  struct soap *soap, 
                    klhst_wstrings          fields,
					klhst_field_order_array	fieldsToOrder,
                    xsd__wstring	        serial,
                    xsd__int                lTimeout,
                    struct kllicsrv_GetKeyInfoResponse&r);

int kllicsrv_DeleteKeyInfoStub(  struct soap *soap, 
                    xsd__wstring	        serial,
                    struct kllicsrv_DeleteKeyInfoResponse&r);

int kllicsrv_InstallKeyStub(  struct soap *soap, 
                    param__params	        keyinfo,
                    struct kllicsrv_InstallKeyResponse&r);

int kllicsrv_UninstallKeyStub(  struct soap *soap, 
                    param__params	        keyinfo,
                    struct kllicsrv_UninstallKeyResponse&r);

int kllicsrv_GetKeyDataStub(  struct soap *soap, 
                    param__params	        indata,
                    struct kllicsrv_GetKeyDataResponse&r);

int kllicsrv_AdjustFlexibleKeyStub(  struct soap *soap, 
                    param__params	        keyinfo,
                    struct kllicsrv_AdjustFlexibleKeyResponse&r);

int kllicsrv_EnumKeysStub(  struct soap *soap, 
                    klhst_wstrings          fields,
					klhst_field_order_array	fieldsToOrder,
                    param__params	        options,
                    xsd__int                lTimeout,
                    struct kllicsrv_EnumKeysResponse&r);

int klhst_MoveRulesAddRuleStub(  struct soap *soap, 
                    param__params ruleinfo,
                    struct klhst_MoveRulesAddRuleResponse&r);

int klhst_MoveRulesUpdateRuleStub(  struct soap *soap, 
                    xsd__int            nRule,
                    param__params       ruleinfo,
                    struct klhst_MoveRulesUpdateRuleResponse&r);

int klhst_MoveRulesDeleteRuleStub(  struct soap *soap, 
                    xsd__int    nRule,
                    struct klhst_MoveRulesDeleteRuleResponse&r);

int klhst_MoveRulesSetRulesOrderStub(  struct soap *soap, 
                    klhst_rule_order_array  arr,
                    struct klhst_MoveRulesSetRulesOrderResponse&r);

int klhst_MoveRulesGetRuleStub(  struct soap *soap, 
                    xsd__int    nRule,
                    struct klhst_MoveRulesGetRuleResponse&r);

int klhst_MoveRulesGetRulesStub(  struct soap *soap, 
                    klhst_wstrings  fields,
                    struct klhst_MoveRulesGetRulesResponse&r);

namespace KLHST
{

	struct KLSTRT::SOAPStubFunc hst_funcs_ptrs[43]=
	{
		{ L"klhst_UseKeepConnection",		 (void*)klhst_UseKeepConnectionStub },
		{ L"klhst_AddHosts",		 (void*)klhst_AddHostsStub },
		{ L"klhst_GetHostTasks",		 (void*)klhst_GetHostTasksStub },
		{ L"klhst_GetDomains",		 (void*)klhst_GetDomainsStub },
		{ L"klhst_GetDomainHosts",		 (void*)klhst_GetDomainHostsStub },
		{ L"klhst_GetHostInfo",		 (void*)klhst_GetHostInfoStub },
		{ L"klhst_AddDomain",		 (void*)klhst_AddDomainStub },
		{ L"klhst_DelDomain",		 (void*)klhst_DelDomainStub },
		{ L"klhst_AddHost",		 (void*)klhst_AddHostStub },
		{ L"klhst_DelHost",		 (void*)klhst_DelHostStub },
		{ L"klhst_UpdateHost",		 (void*)klhst_UpdateHostStub },
		{ L"klhst_GetHostProducts",		 (void*)klhst_GetHostProductsStub },
		{ L"klhst_SS_Read",		 (void*)klhst_SS_ReadStub },
		{ L"klhst_SS_Write",		 (void*)klhst_SS_WriteStub },
		{ L"klhst_SS_CreateSection",		 (void*)klhst_SS_CreateSectionStub },
		{ L"klhst_SS_DeleteSection",		 (void*)klhst_SS_DeleteSectionStub },
		{ L"klhst_SS_GetNames",		 (void*)klhst_SS_GetNamesStub },
		{ L"klhst_CallGetRunTimeInfo",		 (void*)klhst_CallGetRunTimeInfoStub },
		{ L"klhst_CallGetStaticInfo",		 (void*)klhst_CallGetStaticInfoStub },
		{ L"klhst_CallGetStatistics",		 (void*)klhst_CallGetStatisticsStub },
		{ L"klhst_CallGetInstancePort",		 (void*)klhst_CallGetInstancePortStub },
		{ L"klhst_NotifyTask",		 (void*)klhst_NotifyTaskStub },
		{ L"klupdt_GetUpdatesInfo",		 (void*)klupdt_GetUpdatesInfoStub },
		{ L"klupdt_SetBundleOptions",		 (void*)klupdt_SetBundleOptionsStub },
		{ L"klupdt_SetGeneralOptions",		 (void*)klupdt_SetGeneralOptionsStub },
		{ L"klupdt_GetGeneralOptions",		 (void*)klupdt_GetGeneralOptionsStub },
		{ L"klupdt_GetAvailableUpdatesInfo",		 (void*)klupdt_GetAvailableUpdatesInfoStub },
		{ L"klupdt_GetRequiedUpdatesInfo",		 (void*)klupdt_GetRequiedUpdatesInfoStub },
		{ L"kllicsrv_GetKeysInfo",		 (void*)kllicsrv_GetKeysInfoStub },
		{ L"kllicsrv_GetKeyInfo",		 (void*)kllicsrv_GetKeyInfoStub },
		{ L"kllicsrv_DeleteKeyInfo",		 (void*)kllicsrv_DeleteKeyInfoStub },
		{ L"kllicsrv_InstallKey",		 (void*)kllicsrv_InstallKeyStub },
		{ L"kllicsrv_UninstallKey",		 (void*)kllicsrv_UninstallKeyStub },
		{ L"kllicsrv_GetKeyData",		 (void*)kllicsrv_GetKeyDataStub },
		{ L"kllicsrv_AdjustFlexibleKey",		 (void*)kllicsrv_AdjustFlexibleKeyStub },
		{ L"kllicsrv_EnumKeys",		 (void*)kllicsrv_EnumKeysStub },
		{ L"klhst_MoveRulesAddRule",		 (void*)klhst_MoveRulesAddRuleStub },
		{ L"klhst_MoveRulesUpdateRule",		 (void*)klhst_MoveRulesUpdateRuleStub },
		{ L"klhst_MoveRulesDeleteRule",		 (void*)klhst_MoveRulesDeleteRuleStub },
		{ L"klhst_MoveRulesSetRulesOrder",		 (void*)klhst_MoveRulesSetRulesOrderStub },
		{ L"klhst_MoveRulesGetRule",		 (void*)klhst_MoveRulesGetRuleStub },
		{ L"klhst_MoveRulesGetRules",		 (void*)klhst_MoveRulesGetRulesStub },
		{ L"", NULL },
	};

	void RegisterGSOAPStubFunctions()
	{
		KLSTRT::RegisterGSOAPStubFunctions( hst_funcs_ptrs, (sizeof(hst_funcs_ptrs)/sizeof(hst_funcs_ptrs[0])) );
	}

	void UnregisterGSOAPStubFunctions()
	{
		KLSTRT::UnregisterGSOAPStubFunctions( hst_funcs_ptrs, (sizeof(hst_funcs_ptrs)/sizeof(hst_funcs_ptrs[0])) );
	}

} // end namespace KLHST
