/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file Errors.h
 * \author ����� �����������
 * \date 2002
 * \brief �������� ����� ������ ��� ������ Transport.
 *
 */


#ifndef KLTR_ERRORS_H
#define KLTR_ERRORS_H

#include "std/err/errintervals.h"
#include "std/err/error.h"

#include <transport/tr/errlocids.h>

namespace KLTRAP {

	const wchar_t KLTRAP_ModuleName[] = L"TRAP";

	#define KLTR_THROW_ERROR( _code ) \
			KLERR_throwError(KLTRAP::KLTRAP_ModuleName, _code, __FILE__, __LINE__, NULL, NULL)

	#define KLTR_THROW_ERROR1( _code, _param1 ) \
			KLERR_throwError(KLTRAP::KLTRAP_ModuleName, _code, __FILE__, __LINE__, NULL, _param1)

	#define KLTR_THROW_ERROR2( _code, _param1, _param2 ) \
			KLERR_throwError(KLTRAP::KLTRAP_ModuleName, _code, __FILE__, __LINE__, NULL, _param1, _param2)

	#define KLTR_THROW_ERROR3( _code, _param1, _param2, _param3 ) \
			KLERR_throwError(KLTRAP::KLTRAP_ModuleName, _code, __FILE__, __LINE__, NULL, _param1, _param2, _param3 )


	#define KLTR_THROW_LOC1_ERROR( _code, _loccode, _locparam1 ) \
			KLERR_throwLocError( KLERR::ErrLocAdapt(_loccode, NULL, _locparam1),\
				KLTRAP::KLTRAP_ModuleName, _code, __FILE__, __LINE__, NULL );

	#define KLTR_THROW_LOC2_ERROR1( _code, _loccode, _param1, _locparam1, _locparam2 ) \
			KLERR_throwLocError( KLERR::ErrLocAdapt(_loccode, NULL, _locparam1, _locparam2),\
				KLTRAP_ModuleName, _code, __FILE__, __LINE__, NULL, _param1 );

	#define KLTR_THROW_LOC1_ERROR2( _code, _loccode, _param1, _param2, _locparam1 ) \
			KLERR_throwLocError( KLERR::ErrLocAdapt(_loccode, NULL, _locparam1),\
				KLTRAP_ModuleName, _code, __FILE__, __LINE__, NULL, _param1, _param2 );

    //! ������������ ����� ������ ������ TR. 
    enum Errors {
        TRERR_NONE = KLTRERRSTART+0, 
		TRERR_INVALID_PARAMETER,			/*!< �������� ��������� ������� */
		TRERR_WRONG_ADDR,					/*!< �������� ������� ����� */
		TRERR_CANT_ESTABLISH_CONNECTION,	/*!< ������ ������������ ���������� */
		TRERR_NOT_INITIALIZED,				/*!< ������ �� ��� ��������������� */
		TRERR_TRANSPORT_ERROR,				/*!< ������ ������������� ������ */
		TRERR_WRONG_METHOD,					/*!< ������ ����� �� �������������� �������� */
		TRERR_WRONG_METHOD_PARAMETERS,		/*!< �� ������ ��������� ������ */
		TRERR_CONN_ALREADY_EXISTS,			/*!< ���������� � ������ ������ ��� ���������� */
		TRERR_NOT_FOUND_CONNECTION,			/*!< ���������� �� ���� ������� */
		TRERR_CONN_HANSHAKE,				/*!< ������ � handshake ��������� */
		TRERR_REMOTE_CONN_ALREADY_EXISTS,	/*!< ������ ����������� ��� ���� �� ��������� ���� */
		TRERR_MAX_CONNECTIONS,				/*!< ��������� ������������ ���������� ���������� */
		TRERR_WRONG_CONNECTION_NAME,		/*!< �������� ��� ���������� */
		TRERR_LOCATION_ALREADY_EXISTS,		/*!< Listen location ��� ������ ���������� ��� ���������� */
		TRERR_NOT_SUPPORT,
		TRERR_AUTHENTICATION_FAILED,		/*!< ������ �������������� */
		TRERR_TIMEOUT,						/*!< ������� */
		TRERR_REMOTE_SERVER_IS_BUSY,		/*!< ������ ����� */
		TRERR_LOAD_CERT_ERR,				/*!< ������ �������� ������������ */
		TRERR_SSL_CONNECT_ERR,				/*!< ������ SSL ����������� */
		TRERR_SSL_SERVER_AUTH_ERR,			/*!< ������ SSL �������������� ������� */
		TRERR_CONN_BROKEN,					/*!< ��������� ������ ���������� */
		TRERR_HTTP_CONNECT_ERR,				/*!< ������ ����������� �� ��������� HTTP ��� ����� ������ */
		TRERR_METHOD_NOT_FOUND,				/*!< �� ��������� ������� �� ������ soap ����� */
		TRERR_TRANSPORT_SEND_ERROR,			/*!< ������ �������� �������� */
		TRERR_CONNECTION_OPERATION_ERROR,	/*!< ������ �������� ��� ����������� */
		TRERR_HOST_NOT_FOUND,				/*!< ������ ������ ����� */
		TRERR_ADDR_ALREADY_IN_USE,			/*!< ������ ����� ��� ������������ */
		TRERR_SOCKET_NOBUFS					/*!< ������������ ��������� ������ */
    }; 

	//! �������� ������ ������ TR	
	const KLERR::ErrorDescription c_errorDescriptions[]={
		
		{TRERR_NONE,						L"No error"},
		{TRERR_INVALID_PARAMETER,			L"Invalid function's parameter"},	
		{TRERR_WRONG_ADDR,					L"Wrong transport address. Address - '%ls'."},
		{TRERR_CANT_ESTABLISH_CONNECTION,	L"Transport couldn't establish connection. Location - '%ls'."},
		{TRERR_NOT_INITIALIZED,				L"Object haven't initialized"},
		{TRERR_TRANSPORT_ERROR,				L"Error was occured in trasnport layer. Error code - '%d'."},
		{TRERR_WRONG_METHOD,				L"This method don't support on server side. Method name - '%ls'."},		
		{TRERR_WRONG_METHOD_PARAMETERS,		L"Wrong parameters of method. Method name - '%ls'."},
		{TRERR_CONN_ALREADY_EXISTS,			L"Connection with name - '%ls' already exists."},
		{TRERR_NOT_FOUND_CONNECTION,		L"Connection wasn't found in Transport. Local name - '%ls' Remote name - '%ls'."},
		{TRERR_CONN_HANSHAKE,				L"Connection handshake hasn't been performed. Connection name - '%ls'."},
		{TRERR_REMOTE_CONN_ALREADY_EXISTS,	L"Connection already exists in remote process. Connection name - '%ls'."},
		{TRERR_MAX_CONNECTIONS,				L"The maximum number of connection was exceeded."},
		{TRERR_WRONG_CONNECTION_NAME,		L"Wrong format of connection name. Name can't start from '_' symbol. Connection name - '%ls'."},
		{TRERR_LOCATION_ALREADY_EXISTS,		L"Listen location - '%ls' for component - '%ls' already exists."},
		{TRERR_NOT_SUPPORT,					L"The function doesn't support in this configuration."},
		{TRERR_AUTHENTICATION_FAILED,		L"Authentication failed. ConnectionName - '%ls', Client - '%ls'."},
		{TRERR_TIMEOUT,						L"Request timeout. ConnectionName - '%ls', Client - '%ls'."},
		{TRERR_REMOTE_SERVER_IS_BUSY,		L"Remote server is busy. Connection name - '%ls'."},
		{TRERR_LOAD_CERT_ERR,				L"Error in process of loading SSL certifications. Location - '%ls'."},
		{TRERR_SSL_CONNECT_ERR,				L"SSL connect error. Location - '%hs'."},
		{TRERR_SSL_SERVER_AUTH_ERR,			L"SSL server authentication failed. Location - '%hs'."},
		{TRERR_CONN_BROKEN,					L"Connection has been broken or was closed by the programm. local - '%ls', remote - '%ls'."},
		{TRERR_HTTP_CONNECT_ERR,			L"Error in process of HTTP connection. Location - '%hs' HTTP proxy location - '%ls' Error msg - '%hs'."},
		{TRERR_METHOD_NOT_FOUND,			L"Error in processing of request on server side. SOAP method not found."},
		{TRERR_TRANSPORT_SEND_ERROR,		L"Error in processing of sending packet. Connection name or location - '%ls'."},
		{TRERR_CONNECTION_OPERATION_ERROR,	L"Error in operation. Connection name or location - '%ls'."},
		{TRERR_HOST_NOT_FOUND,				L"Error in socket operation. Host name cannot be found - '%hs'."},
		{TRERR_ADDR_ALREADY_IN_USE,			L"Error in socket operation. Address is already in use. Location - '%hs'."},
		{TRERR_SOCKET_NOBUFS,				L"Error in socket operation. No buffer space is available. Too many connections are opened. Location - '%hs'."},
        {0,0}
	};


} // namespace KLTRAP

#endif // KLTR_ERRORS_H

// Local Variables:
// mode: C++
// End:

