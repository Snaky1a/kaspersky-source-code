/*!
 * (C) 2005 "Kaspersky Lab"
 *
 * \file securitypolicyproxy.h
 * \author ����� �����������
 * \date 2005
 * \brief ������ ���������� ��� �������� ���� �������
 */


#if !defined(KLSPLP_SECURITYPOLICYPROXY)
#define KLSPLP_SECURITYPOLICYPROXY

#include <std/base/klbase.h>
#include <transport/spl/securitypolicy.h>

namespace KLSPL
{
	class KLSTD_NOVTABLE SecurityPolicyProxy : public KLSTD::KLBaseQI 
	{
    public:

		/*!
			\brief ���������� ������ ���� ������� � ������� �����������������

			\param permsList [out] ������ ����
		*/
		virtual void GetServerPermissions( KLSPL::SecurityPolicy::PermissionsList &permsList ) = 0;

		/*!
			\brief ������������� ����� ������� � ������� �����������������

			\param permsList [in] ������ ����
			\param bCheckCurrentUserRights [in] ���� �������� ���� �������� ������������ ����� ��������� ���� �������. ���� ����� ��������� 
					������ ������������ �������� ����� �� ������ � ������ ����� �� ����� ��������� ���������� KLSPL::SPLERR_USER_WILL_LOSE_WRITE_RIGHTS
		*/
		virtual void SetServerPermissions( const KLSPL::SecurityPolicy::PermissionsList &permsList, 
			bool bCheckCurrentUserRights = false ) = 0;


		/*!
			\brief ���������� ������ ���� ������� � ������ �����������������

			\param groupId [in] ������������� ������ �����������������
			\param permsList [out] ������ ����
		*/
		virtual void GetGroupPermissions( const long groupId, 
			KLSPL::SecurityPolicy::PermissionsList &permsList ) = 0;

		/*!
			\brief ������������� ����� ������� � ������ �����������������

			\param groupId [in] ������������� ������ �����������������
			\param permsList [in] ������ ����
			\param bCheckCurrentUserRights [in] ���� �������� ���� �������� ������������ ����� ��������� ���� �������. ���� ����� ��������� 
					������ ������������ �������� ����� �� ������ � ������ ����� �� ����� ��������� ���������� KLSPL::SPLERR_USER_WILL_LOSE_WRITE_RIGHTS
		*/
		virtual void SetGroupPermissions( const long groupId, 
			const KLSPL::SecurityPolicy::PermissionsList &permsList, 
			bool bCheckCurrentUserRights = false ) = 0;

	};
}

#endif // !defined(KLSPLP_SECURITYPOLICYPROXY)