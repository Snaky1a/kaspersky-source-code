/*!
 * (C) 2002 Kaspersky Lab 
 * 
 * \file	errors.h
 * \author	Andrew Kazachkov
 * \date	11.10.2002 17:10:39
 * \brief	�������� ����� ������, ������������ ������� Product Component Proxy (PRCP).
 * 
 */


#ifndef KLPRCP_ERRORS_H
#define KLPRCP_ERRORS_H

#include "std/err/errintervals.h"
#include "std/err/error.h"

namespace KLPRCP {

    enum ErrorCodes {
        ERR_CANT_CONNECT = KLPRCPERRSTART + 1,
		ERR_NOT_INITIALIZED
    };


    //! ������������ ����� ������ ������ Product Component Proxy. 
    //  ����� �� ������� ������ ����� ������� ���������� � ���� ����� ������.
    const struct KLERR::ErrorDescription c_errorDescriptions [] = {
        {ERR_CANT_CONNECT,			L"Cannot connect to the component instance '%ls'"},
		{ERR_NOT_INITIALIZED,		L"Component hasn't initialized yet."},
        {0,0}
    };

}

#endif
