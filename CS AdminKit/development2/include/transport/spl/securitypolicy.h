/*!
 * (C) 2005 "Kaspersky Lab"
 *
 * \file securitypolicy.h
 * \author ����� �����������
 * \date 2005
 * \brief ��������� ������ ��� �������� ���� �������
 */

#if !defined(KLSPL_SECURITYPOLICY)
#define KLSPL_SECURITYPOLICY

#include <string>
#include <list>
#include <map>

#include <std/base/kldefs.h>
#include <std/base/klbase.h>
#include <std/par/params.h>
#include <std/tp/threadspool.h>

#include <transport/wat/common.h>

#include <transport/spl/common.h>

#define KLSPL_SEC_PERMISSIONS L"spl-security-permissions"

namespace KLSPL {

	const int c_AllMask = 0xFFFFFFFF;

	class SecurityPolicy : public KLSTD::KLBase
	{
	public:

		/*
			\brief ������� ������ ���� �������
		*/
		class PermissionUnit
		{
		public:			

			PermissionUnit()
			{
				Allow = Deny = 0;
				UserGroupFlag = false;
				Uneraseable = false;
				Readonly = false;				
			}

			PermissionUnit( const std::wstring &userOrUsergroupId, bool userGroupFlag,
				PermissionMask allow, PermissionMask deny, bool readonly = false,
				bool uneraseable = false )
			{				
				UserOrUsergroupId = userOrUsergroupId;
				UserGroupFlag = userGroupFlag;
				Allow = allow;
				Deny = deny;				
				Uneraseable = uneraseable;
				Readonly = readonly;				
			}

			PermissionUnit( const PermissionUnit &p )
			{
				sid = p.sid;
				UserOrUsergroupId = p.UserOrUsergroupId;
				Allow = p.Allow;
				Deny = p.Deny;
				UserGroupFlag = p.UserGroupFlag;
				Uneraseable = p.Uneraseable;
				Readonly = p.Readonly;				
			}

			std::wstring	sid;
			std::wstring	UserOrUsergroupId;
			bool			UserGroupFlag;
			bool			Readonly;
			bool			Uneraseable;
			PermissionMask	Allow;
			PermissionMask	Deny;			
		};

		typedef std::vector<PermissionUnit> PermissionsListType;

		/*
			\brief ����� �������
		*/
		class PermissionsList
		{
			public:

				PermissionsList()
				{
					InheritedFlag = false;
					VisibilityMask = c_AllMask;
				}

				PermissionsList( const PermissionsList &p )
				{
					Permissions = p.Permissions;
					InheritedFlag = p.InheritedFlag;
					VisibilityMask = p.VisibilityMask;
				}

				PermissionsListType	Permissions;
				bool				InheritedFlag;
				PermissionMask		VisibilityMask;
		};

		/*
			\brief ����� ������� ������
		*/
		class GroupsPermissions
		{
		public:
			GroupsPermissions() { Allow = Deny = 0; nGroupId = (-1); }

			GroupsPermissions( const GroupsPermissions &gp )
			{
				Allow = gp.Allow;
				Deny = gp.Deny;
				nGroupId = gp.nGroupId;
			}

			PermissionMask	Allow;
			PermissionMask	Deny;
			long			nGroupId;
		};

		typedef std::map<long, GroupsPermissions> GroupsPermissionsMap;
		

		/*
			\brief �������� ����� ( ������ ��������������� ������������ ����� �� �������� ������ ) 
		*/
		typedef std::vector<long>	GroupHierarchy;


		/*
			\brief Callback ����� ��� ��������� ���������� �� �������� ����� 
				� �������������� �������� ������ ������
		 */
		class GroupsInfoControl : public KLSTD::KLBaseQI
		{
		public:
			virtual void GetGroupHierarchy( const long &groupId, 
				GroupHierarchy &groupHierarchy ) = 0;

			virtual void GetNagentGroups( const std::wstring &nagentId,
				GroupHierarchy &groupHierarchy ) = 0;

			virtual void GetChildServersGroup( const std::wstring &serverId,
				GroupHierarchy &groupHierarchy ) = 0;

			virtual void GetHostGroups( const std::wstring& wstrHostName,
				GroupHierarchy &groupHierarchy ) = 0;
		};

		/*
			\brief Callback ����� ��� ����������� �� ��������� ���� �������
		 */
		class Notifier : public KLSTD::KLBaseQI
		{
		public:
			virtual void SecuriryPolicyChangedNotify( const long &groupId ) = 0;
		};

		/*
			\brief ������������� ���������� ������ ������
		*/
		virtual void InitServer( const std::wstring &storagePath ) = 0;
		
		/*
			\brief ����� ������
		*/
		virtual bool IsServerMode() = 0;

		/*
			\brief ������������� ����� ������� ��� ������

			\param groupId [in] ������������� ������ ����������������� ( ���� empty �� ��������� ���� ��� "��������" ������ )
			\param groupHierarchy [in] �������� ����� ��� ������ groupId
			\param permissions [in] ����� �������

			\exception SPLERR_WRONG_PERMISSIONS_FORMAT
		*/
		virtual void SetPermissions( const long &groupId,
			const PermissionsList &permissions, bool bCheckUserRights = false ) = 0;

		/*
			\brief ��������� ����� ������� ��� ������

			\param groupId [in] ������������� ������ �����������������
			\param groupHierarchy [in] �������� ����� ��� ������ groupId
			\param permissions [out] ����� �������
		*/
		virtual void GetPermissions( const long &groupId, 
			PermissionsList &permissions ) = 0;

		/*
			\brief ��������� ����� ������� ��� �����

			\param hostId [in] ������������� ����� 
			\param permissions [out] ����� �������
		*/
		virtual void GetPermissions( const std::wstring &hostId, 
			PermissionsList &permissions ) = 0;

		/*
			\brief ������� ��� ��������� ������ ����� �������

			\param groupId [in] ������������� ������ �����������������
		 */
		virtual void DeleteGroupPermissions( const long &groupId ) = 0;

		/*
			\brief ��������� ����� ������� ��� �������� ������������ � ��� ��������� ������

			\param authClntContext [in] �������� ������������
			\param hostId [in] ������������� ����� 
			\param groupHierarchy [in] �������� ����� ��� ������ groupId			
			\param Allow [out] ����� ���������� ��������
			\param Deny [out] ����� ����������� ��������
		*/
		virtual void GetClientContextPermissionForGroup( 
			KLSTD::CAutoPtr<KLWAT::ClientContext> authClntContext, 
			const long &groupId,
			const GroupHierarchy *groupHierarchy, 
			Permissions **ppPerms ) = 0;

		/*
			\brief ��������� ����� ������� ��� �������� ������������ � ��� ���������� �����

			\param authClntContext [in] �������� ������������
			\param groupId [in] ������������� ������ �����������������
			\param groupHierarchy [in] �������� ����� ��� ������ groupId			
			\param Allow [out] ����� ���������� ��������
			\param Deny [out] ����� ����������� ��������
		*/
		virtual void GetClientContextPermissionForHost( 
			KLSTD::CAutoPtr<KLWAT::ClientContext> authClntContext, 
			const std::wstring &hostId,
			const GroupHierarchy *groupHierarchy, 
			Permissions **ppPerms ) = 0;

		/*
			\brief ��������� ����� ������� ��� �������� ������������ � 
			��� ���������� �������� ������

			\param authClntContext [in] �������� ������������
			\param remoteNagentName [in] ������������ �������� ������ ( transport name )
			\param ppPerms [out] ����� �������
		*/
		virtual void GetClientContextPermission(			
			const std::wstring &remoteNagentName, 
			Permissions **ppPerms ) = 0;

		/*
			\brief ��������� ����� ������� ��� �������� ������������ � 
			��� ���������� ������������ �������

			\param authClntContext [in] �������� ������������
			\param remoteServerName [in] ������������ ������������ ������� ( transport name  )
			\param ppPerms [out] ����� �������			
		*/
		virtual void GetClientContextPermissionChildServer(			
			const std::wstring &remoteServerName, 
			Permissions **ppPerms ) = 0;
		
		/*
			\brief ������������� callback ����� ��� ������ � ��������� �����

			\param pGroupControl [in] ��������� �� �����
		*/
		virtual void SetGroupsInfoControl( GroupsInfoControl *pGroupsInfoControl ) = 0;

		/*
			\brief ������� �������������/���������� �/�� backup'�
		 */
		virtual void GetStorageData( KLPAR::BinaryValue** ppData ) = 0;
		virtual void PutStorageData( KLPAR::BinaryValue* pData ) = 0;

		/*
			\brief ��������� ������ ���� ��� �����
				������ ������:
					nGroupId = (-1) ����� ��� ������� ����������������� � ��� ��� �����, ������� ��� � ������
					nGroupId = (������������� ������) - ����� ��� �����, � ������� ������������ ����� ������� ������� �����

			\param permsVect [out]
		*/
		virtual void GetGroupsPermissions( KLSTD::CAutoPtr<KLWAT::ClientContext> authClntContext, 
			GroupsPermissionsMap &permsMap ) = 0;


		/*
			\brief ���������� ��������� ������������� ������������� �� ����������� ��������� 
		*/
		virtual void GetUserSystemIdentifier( KLSTD::CAutoPtr<KLWAT::ClientContext> authClntContext,
			std::wstring &userId, std::vector<int> &customAccessVec ) = 0;


		/*
			\brief ������������� callback ����� ��� �����������

			\param pNotifier [in] ��������� �� �����
		*/
		virtual void SetNotifier( Notifier *pNotifier ) = 0;		
	};


} // namespace KLSPL


KLCSTR_DECL bool KLSPL_CreatePermissions( KLSPL::Permissions **ppPerms, 
			KLSPL::PermissionMask allow, KLSPL::PermissionMask deny,
			std::wstring &userAccountName );

KLCSTR_DECL KLSPL::SecurityPolicy *KLSPL_GetSecurityPolicy();

/*
	\brief ������� ������������/��������������� ����������
*/
DECLARE_MODULE_INIT_DEINIT2( KLCSTR_DECL, KLSPL );

#endif // !defined(KLSPL_SECURITYPOLICY)
