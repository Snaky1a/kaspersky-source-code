/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	wat/authserver.h
 * \author	Mikhail Karmazine
 * \date	06.02.2003 11:41:59
 * \brief	��������� KLWAT::AuthClient
 * 
 */

#ifndef __KLWAT_AUTHCLIENT_H__
#define __KLWAT_AUTHCLIENT_H__

#include <string>
#include <std/base/kldefs.h>
#include "common.h"
#include <std/par/params.h>

namespace KLWAT
{
   /*!
		\brief �����, ���������� �� ���������� ������� ��������������.
        ������:

            std::string strInData, strOutData;

            // server id may be any string which is constant during connection 
            // to server - server IP address, for example.
            pAuthClient->InitializeHandshake( L"my server", strOutData ); 

            bool bDone = false;
            std::wstring wstrClientIdAtServer;
            while( ! bDone )
            {
                if( ! strInData.empty() )  // at first loop strInData is empty
                {
                    bDone =
                        pAuthClient->HandshakeWithDataFromServer( L"my server", strInData, wstrClientIdAtServer, strOutData );
                }

                // pServerProxy->ProcessMessage() - placeholder for function which 
                // transmits strOutData to server, and receives back strInData.
                // wstrClientIdAtServer parameter is both input and output - at first call it is empty,
                // and ProcessMessage() assigns client id to it, and then assigned value shall be used in
                // consequent calls.
                pServerProxy->ProcessMessage( wstrClientIdAtServer, strOutData, strInData );
            }

        ����� ������ ����� ������ ������ ������� �� ������ wstrClientIdAtServer, �
        ����� �������� ������������, �������� AccessToken, � �.�.
    */
    class KLSTD_NOVTABLE AuthClient : public KLSTD::KLBase
    {
    public:
        virtual ~AuthClient () {};

        /*!
          \brief	ServerShallKnowClient
                        ���������, ��� �� ���������� �������� handshake � ������ ��������.
                        ���� ��, �� ����� �������� ������� GetClientIdAtServer()

          \param	wstrServerIdentity - ������������� �������.
          \return	bool - true ���� handshake ��� �����������, false otherwise.
        */
        virtual bool ServerShallKnowClient( const std::wstring & wstrServerIdentity ) = 0;

        virtual void InitializeHandshake( const std::wstring & wstrServerIdentity,
                                          std::string & strOutData ) = 0;

        virtual void InitializeBAHandshake( const std::wstring & wstrServerIdentity,
                                            const KLPAR::Params * pCustomCredentials,
                                            std::string & strOutData ) = 0;
        
        /*!
          \brief	HandshakeWithDataFromServer

          \param	wstrServerIdentity
          \param	strInData
          \param	strOutData  - ���� ���� ������� ������� true, ���������� ��� ����� ����
                ������� �� ������, ���� ����� strOutData>0
          \return	bool - ���������� true, ����� ������ ������� ��� ����������� ������ ��� 
                �������������� �� �������, �.�. �������� ��� ����� ������� ��� ������� ������
                    �� ����. �� ���� ����� strOutData>0, �� ��� ����� ���� �������� ���
                    ������ �� ������!!!!
        */
        virtual bool HandshakeWithDataFromServer( const std::wstring & wstrServerIdentity,
                                                  const std::string & strInData,
                                                  const std::wstring & wstrClientId,
                                                        std::string & strOutData ) = 0;

        /*!
          \brief	ForgetServer - ������� ������ �� ������ ��������� ��������.

          \param	wstrServerIdentity - ������������� �������.
        */
        virtual void ForgetServer( const std::wstring & wstrServerIdentity ) = 0;


        /*!
          \brief	GetClientIdAtServer - ���������� ID, ������� ���� �����������
                ��� ������� � ��������, ����� ���������������� ����.
                ������� handshake'� ������ ���� ��������, ����� ����� ��������� ����������.

          \param	const std::wstring & wstrServerIdentity - ������������� �������.
          \param	std::wstring & wstrClientId [out] - ID �������.
        */
        virtual void GetClientIdAtServer( const std::wstring & wstrServerIdentity,
                                          std::wstring & wstrClientId ) = 0;
    };
	const wchar_t c_szwClientCertFieldName[]= L"KLWAT_CLNT_CERT";
}

KLCSTR_DECL void KLWAT_CreateAuthClient( KLWAT::AuthClient **ppAuthClient, bool bMultithreaded = true );

KLCSTR_DECL void KLWAT_GetGlobalAuthClient( KLWAT::AuthClient **ppAuthClient );

#endif //__KLWAT_AUTHCLIENT_H__

// Local Variables:
// mode: C++
// End:
