/*!
 * (C) "Kaspersky Lab"
 *
 * \file invsoapstub.h
 * \author Generated by createsoapheader.pl
 * \brief SOAP stub declaration and registration code
 */

#include "soapH.h"

#include "std/gsoap/stubrouter.h"

/* Declaration of functions */

int klinv_GetInvProductsListStub(  struct soap *soap,  
	struct klinv_GetInvProductsListResponse&r);

int klinv_GetInvPatchesListStub(  struct soap *soap,  
	struct klinv_GetInvPatchesListResponse&r);

int klinv_GetHostInvProductsListStub(  struct soap *soap,  
	xsd__int	hostId,
	struct klinv_GetHostInvProductsListResponse&r);

int klinv_GetHostInvPatchesListStub(  struct soap *soap,  
	xsd__int	hostId,
	struct klinv_GetHostInvPatchesListResponse&r);

int klinv_GetSrvCompetitorIniFileInfoListStub(  struct soap *soap,  
		xsd__wstring	wstrType,
		struct klinv_GetSrvCompetitorIniFileInfoListResponse&r);

int klinv_ResetIteratorStub(  struct soap *soap, 
		xsd__wstring	wstrFilter,
		klinv_wstring_array		fields,
		klinv_field_order_array	fields_to_order,
		xsd__int					lifetime,
		struct klinv_ResetIteratorResponse&r);

int klinv_GetRecordCountStub(  struct soap *soap, 
		xsd__wstring	iteratorId,
		struct klinv_GetRecordCountResponse&r);

int klinv_GetRecordRangeStub(  struct soap *soap, 
		xsd__wstring	iteratorId,
		xsd__int		nStart,
        xsd__int		nEnd,
		struct klinv_GetRecordRangeResponse&r);

int klinv_ReleaseIteratorStub(  struct soap *soap, 
		xsd__wstring	iteratorId,
		struct klinv_ReleaseIteratorResponse&r);

namespace KLINV
{

	struct KLSTRT::SOAPStubFunc inv_funcs_ptrs[10]=
	{
		{ L"klinv_GetInvProductsList",		 (void*)klinv_GetInvProductsListStub },
		{ L"klinv_GetInvPatchesList",		 (void*)klinv_GetInvPatchesListStub },
		{ L"klinv_GetHostInvProductsList",		 (void*)klinv_GetHostInvProductsListStub },
		{ L"klinv_GetHostInvPatchesList",		 (void*)klinv_GetHostInvPatchesListStub },
		{ L"klinv_GetSrvCompetitorIniFileInfoList",		 (void*)klinv_GetSrvCompetitorIniFileInfoListStub },
		{ L"klinv_ResetIterator",		 (void*)klinv_ResetIteratorStub },
		{ L"klinv_GetRecordCount",		 (void*)klinv_GetRecordCountStub },
		{ L"klinv_GetRecordRange",		 (void*)klinv_GetRecordRangeStub },
		{ L"klinv_ReleaseIterator",		 (void*)klinv_ReleaseIteratorStub },
		{ L"", NULL },
	};

	void RegisterGSOAPStubFunctions()
	{
		KLSTRT::RegisterGSOAPStubFunctions( inv_funcs_ptrs, (sizeof(inv_funcs_ptrs)/sizeof(inv_funcs_ptrs[0])) );
	}

	void UnregisterGSOAPStubFunctions()
	{
		KLSTRT::UnregisterGSOAPStubFunctions( inv_funcs_ptrs, (sizeof(inv_funcs_ptrs)/sizeof(inv_funcs_ptrs[0])) );
	}

} // end namespace KLINV
