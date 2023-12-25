/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	wat/common.h
 * \author	Mikhail Karmazine
 * \date	06.02.2003 11:44:00
 * \brief	����������, ����� ��� ����� namespace'� KLWAT
 * 
 */

#ifndef __KLWAT_COMMON_H__
#define __KLWAT_COMMON_H__

#include <std/base/kldefs.h>
#include <std/base/klbase.h>
#include <transport/spl/common.h>
#include <string>

namespace KLWAT
{
	/*!
		\brief ClientContext - �����, ������������� ����� ����� ����������� ���������,
            ����������� � ������� ������ AuthServer. �������, ����������� ���� ���������,
            ����� ���� �������� � ������� AuthServer::GenClientContext(). 
            ����� ����� ������ ���������, �� � ������� (������� �������� ���� ������) ����������
            ����� ForgetClient.
	*/
    class KLSTD_NOVTABLE ClientContext : public KLSTD::KLBase
    {
    public:
        virtual ~ClientContext () {};
		
		/*!
          \brief	�������� ��������
		*/
		virtual void CopyTo( ClientContext **ppCntx ) = 0;

        /*!
          \brief	GetClientIdentity - ���������� ���������� ID, �������
          ����� ������������ ��� ������� ������� AuthServer.

          \return	std::wstring - ���������� ID
        */
        virtual std::wstring GetClientIdentity() = 0;

		/*!
          \brief	��������� ������ �������
        */
		virtual void SetPermissions( KLSPL::Permissions *perms ) = 0;

		/*!
          \brief	���������� ������ ������� ( NULL ���� �� ���������� )
        */
		virtual KLSPL::Permissions *GetPermissions() = 0;
		
		/*!
          \brief	��������� ����������������� ���������� ������������
        */
		virtual void SetUserInfo( const std::wstring &wstrUserSystemId, long nUserAccessMapId,
				const std::wstring &wstrAccessMapHash ) = 0;

		/*!
          \brief	���������� ����������������� ���������� ������������
        */
		virtual void GetUserInfo( std::wstring &wstrUserSystemId, long &nUserAccessMapId,
				std::wstring &wstrAccessMapHash ) = 0;

		/*!
          \brief	���������� ����������������� ���������� ������������
        */
		virtual void GetUserInfo( long &nUserAccessMapId ) = 0;
    };
	
    /*!
	    \brief AuthenticationType - ��� ��������������. 
            atOS - �������������� ������������ ���������� ��
            atCustom - ����������� �������������� ����� ���/������
    */
    enum AuthenticationType { atOS, atCustom };
}

#if defined(__unix) || defined(_MBCS) || defined(N_PLAT_NLM)
# define KLWAT_OFF
#endif // _MBCS

#endif //__KLWAT_COMMON_H__

// Local Variables:
// mode: C++
// End:
