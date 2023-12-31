/*!
 * (C) "Kaspersky Lab"
 *
 * \file prsspsoapstub.h
 * \author Generated by createsoapheader.pl
 * \brief SOAP stub declaration and registration code
 */

#include "soapH.h"

#include "std/gsoap/stubrouter.h"

/* Declaration of functions */

int klprssp_SS_ReadStub(  struct soap *soap, 
    xsd__wstring	storage_descr,
    xsd__wstring	name,
    xsd__wstring	version,
    xsd__wstring	section,
    struct klprssp_SS_ReadResponse&r );

int klprssp_SS_WriteStub(  struct soap *soap, 
					xsd__wstring	storage_descr,
					xsd__wstring	name,
					xsd__wstring	version,
					xsd__wstring	section,
					param__params	data,
					xsd__int		operation_type,  
					struct klprssp_SS_WriteResponse&r);

int klprssp_SS_SectionOperationStub(  struct soap *soap, 
					xsd__wstring	storage_descr,
					xsd__wstring	name,
					xsd__wstring	version,
					xsd__wstring	section,
					xsd__int		operation_type,
					struct klprssp_SS_SectionOperationResponse&r);

int klprssp_SS_GetNamesStub(  struct soap *soap, 
					xsd__wstring	storage_descr,
					xsd__wstring	name,
					xsd__wstring	version,
					struct klprssp_SS_GetNamesResponse&r);

int klprssp_SS_ApplyChangesStub(  struct soap *soap, 
					xsd__wstring	storage_descr,
					struct klprssp_SS_ApplyChangesResponse&r);

int klprssp_ReleaseSSStub(  struct soap *soap, 
                    xsd__wstring    storage_descr,
                    struct klprssp_ReleaseSSResponse&r );

namespace KLPRSSP
{

	struct KLSTRT::SOAPStubFunc prssp_funcs_ptrs[7]=
	{
		{ L"klprssp_SS_Read",		 (void*)klprssp_SS_ReadStub },
		{ L"klprssp_SS_Write",		 (void*)klprssp_SS_WriteStub },
		{ L"klprssp_SS_SectionOperation",		 (void*)klprssp_SS_SectionOperationStub },
		{ L"klprssp_SS_GetNames",		 (void*)klprssp_SS_GetNamesStub },
		{ L"klprssp_SS_ApplyChanges",		 (void*)klprssp_SS_ApplyChangesStub },
		{ L"klprssp_ReleaseSS",		 (void*)klprssp_ReleaseSSStub },
		{ L"", NULL },
	};

	void RegisterGSOAPStubFunctions()
	{
		KLSTRT::RegisterGSOAPStubFunctions( prssp_funcs_ptrs, (sizeof(prssp_funcs_ptrs)/sizeof(prssp_funcs_ptrs[0])) );
	}

	void UnregisterGSOAPStubFunctions()
	{
		KLSTRT::UnregisterGSOAPStubFunctions( prssp_funcs_ptrs, (sizeof(prssp_funcs_ptrs)/sizeof(prssp_funcs_ptrs[0])) );
	}

} // end namespace KLPRSSP
