/*!
 * (C) 2005 "Kaspersky Lab"
 *
 * \file spl/common.h
 * \author ����� �����������
 * \date 2005
 * \brief ����� ������������ ������ SPL
 */

#if !defined(KLSPL_COMMON)
#define KLSPL_COMMON

#define KLSPL_GET_SESSION_ID(nSessionId)\
	{	nSessionId = (-1);\
		KLSTD::CAutoPtr<KLWAT::ClientContext> _pContext;\
		if(KLSTD_GetGlobalThreadStore()->IsObjectHere(KLWAT_SEC_CONTEXT))\
		{\
			KLSTD_GetGlobalThreadStore()->GetStoredObject(KLWAT_SEC_CONTEXT,\
													(KLSTD::KLBase**)&_pContext);\
			KLSTD_ASSERT_THROW(_pContext);\
			_pContext->GetUserInfo(nSessionId);\
		}\
	}

#define KLSPL_GET_USER_INFO(wstrUserSystemId,nSessionId,wstrAccessMapHash)\
	{	nSessionId = (-1);\
		KLSTD::CAutoPtr<KLWAT::ClientContext> _pContext;\
		if(KLSTD_GetGlobalThreadStore()->IsObjectHere(KLWAT_SEC_CONTEXT))\
		{\
			KLSTD_GetGlobalThreadStore()->GetStoredObject(KLWAT_SEC_CONTEXT,\
													(KLSTD::KLBase**)&_pContext);\
			KLSTD_ASSERT_THROW(_pContext);\
			_pContext->GetUserInfo(wstrUserSystemId,nSessionId,wstrAccessMapHash);\
		}\
	}

namespace KLSPL {
	
	const wchar_t KLADMINS_GROUPNAME[]		= L"KLAdmins";
	const wchar_t KLOPERATORS_GROUPNAME[]	= L"KLOperators";
	const wchar_t KLADMINS_DOMAIN_GROUPNAME[]		= L"\\KLAdmins";
	const wchar_t KLOPERATORS_DOMAIN_GROUPNAME[]	= L"\\KLOperators";
	const wchar_t ADMINISTRATORS_GROUPNAME[]= L"Administrators";
	const wchar_t EVERYONE_GROUPNAME[]		= L"Everyone";
	
	/*
		\brief ���� �������������� ��������
	*/
	enum OperationType
	{
		Read						= 0x1,
		Write						= 0x2,
		Execute						= 0x4,
		Reserved1					= 0x8,
		Reserved2					= 0x10,
		Reserved3					= 0x20,
		Reserved4					= 0x40,
		Reserved5					= 0x80,
		Reserved6					= 0x100,
		Reserved7					= 0x200,		
		ChangeSecurityRights		= 0x400,
		ChangeEventsRegistration	= 0x800,
		ChangeEventsNotification	= 0x1000,
		RemoteInstallAccessKLApps	= 0x2000,
		RemoteInstallAccessUtility	= 0x4000,
		ChangeServersHierarchy		= 0x8000		
	};

	/*
		\brief ������� ����� ��������
	*/
	typedef unsigned long PermissionMask;

	/*
		\brief ����� ������� ��������������� � �����������
	*/
	class Permissions : public KLSTD::KLBase
	{
	public:
		virtual PermissionMask Allow() = 0;
		virtual PermissionMask Deny() = 0;
		virtual std::wstring GetUserAccountName() = 0;
	};


} // namespace KLSPL

#endif // !defined(KLSPL_COMMON)
