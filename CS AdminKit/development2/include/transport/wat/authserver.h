/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	wat/authserver.h
 * \author	Mikhail Karmazine
 * \date	06.02.2003 11:41:59
 * \brief	��������� KLWAT::AuthServer
 * 
 */

#ifndef __KLWAT_AUTHSERVER_H__
#define __KLWAT_AUTHSERVER_H__

#include <string>
#include <set>

#include "std/base/kldefs.h"
#include "std/par/params.h"
#include "./common.h"
#include "./osdep.h"

#define KLWAT_SEC_CONTEXT L"wat-security-context"

namespace KLWAT
{

	/*!
		\brief GroupVector - ����� ��������������� ����������������� �����. ��������, ��� �����
            ���� ������ Everyone, ��� Domain Admins, ��� Nagent.
	*/
    typedef std::vector<int> GroupVector;

	/*!
		\brief CustomAccessToken - "�����������" AccessToken. ��������
            � ���� ������ ����������������� �����, ������� �� ������������.
	*/
    struct CustomAccessToken
    {
        GroupVector vectGroups;
		std::wstring wstrLogin;
    };


	/*!
		\brief AccessTokenHolder - �������� � ���� � ������ ������ AccessToken.
            ������, ����������� ������ ���������, ������ ��������� AccessToken
            ��� ��������.
	*/
    class KLSTD_NOVTABLE AccessTokenHolder : public KLSTD::KLBase
	{
    public:
	    /*!
		    \brief GetType - ���������� ��� ��������������, ������������ ���
                ��������� AccessToken'�.

                ���� atOS, �� ����� �������� AccessToken, ���������� ��
                ������������ �������, �� ������������ ������� GetOSAccessToken(). 

                ���� atCustom, �� ����� �������� "�����������" AccessToken,
                ���������� � ���� ������ ����������������� �����. ������������
                ������� GetCustomGroupVector().
	    */      
        virtual AuthenticationType GetType() const = 0;


	    /*!
		    \brief GetOSAccessToken - ���������� AccessToken, ���������� ��
                ������������ �������.
                ����� �������, ������ ���� GetType() == atOS. � ���������
                ������ ��������� ASSERT.
	    */      
        virtual const OSAccessToken & GetOSAccessToken() const = 0;


	    /*!
		    \brief GetCustomAccessToken - ���������� ����������� AccessToken,
                ���������� � ���� ������ ����������������� �����. ������ ����� ����
                �����, ��� Everyone, Nagent, ��� Domain Admins.
                ����� �������, ������ ���� GetType() == atCustom. � ���������
                ������ ��������� ASSERT.
	    */      
        virtual const CustomAccessToken & GetCustomAccessToken() const = 0;
	};


	/*!
		\brief CustomCredentialsConverter - ������� CustomAccessToken, 
		������� �������� ������ ���������������� �����,      
		��������������� ���������� ����������.


	*/      
    class KLSTD_NOVTABLE CustomCredentialsConverter : public KLSTD::KLBaseQI
	{
    public:
	    /*!
		    \brief ConvertCustomCredetials - ���������
            �� ���� ����� ���������� credentials, ���������� � Params, �
            ������ CustomAccessToken, ������� �������� ������ ���������������� �����,
            ��������������� ���� credentials. ���� ����� ����� ����� ���������
            ����������..
        */
        virtual void ConvertCustomCredentials(
            const KLPAR::Params * pCustomCredetials,
            CustomAccessToken & customAccessToken,
			std::wstring &wstrUserName,
			std::wstring &wstrUserDomain,
			std::wstring &wstrUserPassword ) = 0;
	    /*!
		    \brief AdjustSSLCredetials - ���������
            �� ���� PublicKey ������� � ���������� �� Params, �
            ������ CustomAccessToken, ������� �������� ������ ���������������� �����,
            ��������������� ����� �������. ���� ����� ����� ����� ���������
            ����������..
        */
        virtual void AdjustSSLCredentials(
			void* pPublicKey,
			size_t nPublicKeySize,
            CustomAccessToken & customAccessToken) = 0;
    };
    
    const wchar_t c_szwEventsOnlyContext[]= L"KLWAT_CTX_EVENTS_ONLY";
    const wchar_t c_szwAdmServerContext[]= L"KLWAT_CTX_ADMSERVER";
    const wchar_t c_szwFooProcessContext[]= L"KLWAT_CTX_PROCESS";
    const wchar_t c_szwSlaveAdmServerContext[]= L"KLWAT_CTX_SLAVE_ADMSERVER";
    const wchar_t c_szwMasterAdmServerContext[]= L"KLWAT_CTX_MASTER_ADMSERVER";

	/*!
		\brief AuthServer - ��������� ����� ��������������. ��. AVT_TEST ���
        ������� �������������.
	*/
    class KLSTD_NOVTABLE AuthServer : public KLSTD::KLBase
    {
    public:
        virtual ~AuthServer () {};

        /*!
          \brief	HandshakeWithDataFromClient
             ���������� ��������� ������� ������, ����������� �� �������, ���������
                �������������������.

          \param	std::wstring & wstrClientIdentity [in/out] - �� ����� ��������
                        ���� ������ ������ - ����� ���������, ��� ��� ������ ����� �� ������� �������,
                        � ������������ ����� ID, ������� � ������������ � ���� ����������. ����
                        �������� �������� ��� ����� ID, ������� �������������� ��� ���������� ������
                        �� ������� �������.
          \param	const std::string & strInData [in] - ������ �� �������. ��� �������� 
                        ������ (���������� � �.�. non-printable characters), � ������ �� 
                        ������ ��������������� ��� NULL-terminated.
          \param	std::string & strOutData [out] - ������, ������� ���� �������� �������.
                        ��� �������� ������ (���������� � �.�. non-printable characters), �
                        ������ �� ������ ��������������� ��� NULL-terminated.
          \return	bool - ���������� true, ����� ������ �������� ����������������� �������.
        */
        virtual bool HandshakeWithDataFromClient( std::wstring & wstrClientIdentity,
                                                  const std::string & strInData,
                                                        std::string & strOutData  ) = 0;


        /*!
          \brief	GenClientContext - ���������� ������, ������������� ����� �����
            ����������� ���������, ����������� � ������� ������� �������.
            ����� ����� ������ ���������, �� � ������� ������� ����������
            ����� ForgetClient.

            ���� �����, ��������� ��������� ��� � ����� � ��� �� ID �������, ����������
            ��������� �� ���� � ��� �� ������.

          \param	wstrClientIdentity - ID �������, ���������� � �������� handshake'�.
          \return	KLSTD::CAutoPtr<ClientContext> - ������, ������������� ����� �����
            ����������� ���������.
        */
        virtual KLSTD::CAutoPtr<ClientContext>
            GenClientContext( const std::wstring & wstrClientIdentity ) = 0;		


        /*!
          \brief	ImpersonateThread Impersonate thread by client access token 
                received by handshake process.
                ����� ������ �������� ������ ��� ��������, ������������ windows-��������������

          \param	const std::wstring & wstrClientIdentity - ID �������, ����������
                � �������� handshake'�
        */
        virtual void ImpersonateThread( const std::wstring & wstrClientIdentity ) = 0;

        /*!
          \brief	IsThreadImpersonated - ���������, �� �������������� �� �����
                ��������, ������������ windows-��������������.
          \return	bool -  true  ���� ����� ��������������, false otherwise
        */
        virtual bool IsThreadImpersonated() = 0;

        /*!
          \brief	GetImpersonationToken() ���������� ����� � ���������, ������� ���� 
            �� ������ ������ ImpersonateThread()
                ����� ������ �������� ������ ��� ��������, ������������ windows-��������������
          \param	const std::wstring & wstrClientIdentity - ID �������, ����������
                � �������� handshake'�
        */
        virtual void RevertThread( const std::wstring & wstrClientIdentity ) = 0;

        /*!
          \brief	GetImpersonationToken() ���������� impersonation access token,
            ���������� � �������� handshake'�. ��� ���� �����, �� ��������
            ���������� ��� �������, �� ������ ���� ��������������.
                ����� ������ �������� ��� ��������, ������������ ��� ���� ��������������

          \param	const std::wstring & wstrClientIdentity - ID �������, ����������
                � �������� handshake'�
        */
        virtual KLSTD::CAutoPtr<AccessTokenHolder> GetImpersonationToken( const std::wstring & wstrClientIdentity ) = 0;

        /*!
          \brief	ForgetClient - ������� ���������� ��������. ���� ���������� ������� ���,
            �� ���������� �� �������������.

          \param	const std::wstring & wstrClientIdentity
        */
        virtual void ForgetClient( const std::wstring & wstrClientIdentity ) = 0;
        
        /*!
          \brief	GetImpersonationToken() ���������� access token, 
                    ��������������� ��� �������� ���� �������. ��� ���� 
                    �����, �� �������� ���������� ��� �������, �� ������
                    ���� ��������������. ����� ������ �������� ��� 
                    ��������, ������������ ��� ���� ��������������

          \param	const std::wstring & wstrClientIdentity - ID �������, ����������
                � �������� handshake'�
        */
        virtual KLSTD::CAutoPtr<AccessTokenHolder> GetAccessCheckToken( const std::wstring & wstrClientIdentity ) = 0;

		/*!
          \brief	GenClientContext - ���������� ������, ������������� ����� �����
            ����������� ���������, ����������� � ������� ������� �������.
            ����� ����� ������ ���������, �� � ������� ������� ����������
            ����� ForgetClient.

            ���� �����, ��������� ��������� ��� � ����� � ��� �� ID �������, ����������
            ��������� �� ���� � ��� �� ������.

          \param	wstrClientIdentity - ID �������, ���������� � �������� handshake'�.
		  \param	customAccessToken - ���������������� ��������
          \return	KLSTD::CAutoPtr<ClientContext> - ������, ������������� ����� �����
            ����������� ���������.
        */
        virtual KLSTD::CAutoPtr<ClientContext> GenClientContext( const std::wstring & wstrClientIdentity, 
			const KLWAT::CustomAccessToken& customAccessToken ) = 0;		

    };
}

/*!
  \brief	KLWAT_CreateAuthServer - ������� ������ ���� KLWAT::AuthServer

  \param	KLWAT::AuthServer **ppAuthServer [out] - ���������
  \param	bool bMultithreaded = true [in] - obvious
  \return	void 
*/
KLCSTR_DECL void KLWAT_CreateAuthServer( KLWAT::AuthServer **ppAuthServer,
                                        bool bMultithreaded = true );

KLCSTR_DECL void KLWAT_GetGlobalAuthServer( KLWAT::AuthServer **ppAuthServer );

/*!
  \brief	KLWAT_SetCustomCredentialsConverter - ������������� ���������� 
        ��������� ��� custom credentials
*/
KLCSTR_DECL void KLWAT_SetCustomCredentialsConverter( KLWAT::CustomCredentialsConverter * pConverter );

/*!
  \brief	KLWAT_GetCurrentToken() ���������� access token,
    � ������� � ������ ������ �������� �����. ���� ����� ��������������,
    �� ��� access token, ������� �� ��������������. ���� ����� �� ��������������,
    �� ������������ access token ��������.
*/
KLCSTR_DECL KLSTD::CAutoPtr<KLWAT::AccessTokenHolder> KLWAT_GetCurrentToken();


/*!
  \brief	KLWAT_StorePrivateString - "���������" ��������� ������.
    ��� WINDOWS UNICODE - ���������� ������ ����������� ���-�� � �������,
    ���-�� ��� ���� ��������. �������� � ��������� ������ ����� ����� �����
    ��������� ������ BUILTIN/Administrators. ����������� ��. � MSDN, � ��������
    ������� LsaStorePrivateData() � LsaRetrievePrivateData().

  \param	onst std::wstring& wstrKey [in] - ����, �� �������� � ���������� ����� 
        ������������ ������.
  \param	const std::wstring& wstrPrivateString [in] - ����������� ������.
*/
KLCSTR_DECL void KLWAT_StorePrivateString(
    const std::wstring& wstrKey,
    const std::wstring& wstrPrivateString );


/*!
  \brief	KLWAT_RetrievePrivateString - ������ ������, ����������� ��������������
    �������� KLWAT_StorePrivateString.

  \param	onst std::wstring& wstrKey [in] - ����, �� ���� ��������� ������ ������.
  \param	const std::wstring& wstrPrivateString [out] - ���������.
*/
KLCSTR_DECL void KLWAT_RetrievePrivateString(
    const std::wstring& wstrKey,
          std::wstring& wstrPrivateString );

#endif //__KLWAT_AUTHSERVER_H__

// Local Variables:
// mode: C++
// End:
