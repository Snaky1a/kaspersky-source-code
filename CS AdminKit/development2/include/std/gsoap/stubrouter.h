 /*!
 * (C) 2004 "Kaspersky Lab"
 *
 * \file stubrouter.h
 * \author ����� �����������
 * \date 2004
 * \brief ����������� ������� ��� ������ � stub ��������� gSOAP
 *
 */

#ifndef KLSTD_STUBROUTER_H
#define KLSTD_STUBROUTER_H

#include <string>
#include <map>

#include "std/base/kldefs.h"

//#include "soaph.h"

namespace KLSTRT{

	//!\brief �������� �������
	struct SOAPStubFunc
	{
		const wchar_t	*funcName;	//<- ��� �������
		void			*funcPtr;	//<- ��������� �� �������
	};

	//!< ������� ��/������������� ����������
	void InitStubRouter();
	void DeinitStubRouter();
		
	//!\brief ������������ gSOAP ������� ������
	KLCSC_DECL void RegisterGSOAPStubFunctions( SOAPStubFunc *array, int array_size );

	//!\brief ������� ������� �� ������ ������������������ gSOAP ������� ������
	KLCSC_DECL void UnregisterGSOAPStubFunctions( SOAPStubFunc *array, int array_size );

	//!\brief ���������� ��������� ������������������ �������
	KLCSC_DECL void *GetFunctionPtrByName( const wchar_t *funcName );

};

KLCSC_DECL int klstd_soap_serve(struct soap *);

#endif // KLSTD_STUBROUTER_H
