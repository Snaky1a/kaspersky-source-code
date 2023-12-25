/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	avt/accesscheck.h
 * \author	Andrey Lashenkov
 * \date	17.12.2003 19:55:00
 * \brief	��������� ������� �������� ���� �������.
 * 
 */

#ifndef __KLAVT_ACCESSCHECK_H__
#define __KLAVT_ACCESSCHECK_H__

#include "accesscontrol.h"
//#include "transport/avtl/acllib.h"
#include "kca/prci/componentid.h"

KLCSTR_DECL bool KLAVT_AccessCheckForContext(
                KLWAT::ClientContext*           pContext,
	            const KLAVT::ACE_DECLARATION*   pAcl,
	            long                            nAcl,
                AVP_dword                       dwAccessMask,
                bool                            bThrowExceptions,
				const long						&lGroupId,
				const std::wstring				&hostId,
                const std::wstring*             pwstrBasicAuthLogin);


//!\brief ������� ����������� ���������� ������, ������������ security context �� thtread storage.
KLCSTR_DECL bool KLAVT_AccessCheck_InCall(
	        const KLAVT::ACE_DECLARATION*   pAcl,
	        long                            nAcl,
	        AVP_dword dwAccessMask, //!< ������� ����� ��������� ���� ������� (��. "ACLDecl.h")
	        bool bGenerateException = true, //!< ������������ �� ���������� KLSTD::STDE_NOACCESS, ��� ���������� false
			const long &lGroupId = (-1),	//!< ������������� ������ �����������������
			const std::wstring& hostId = L"",
            const std::wstring* pwstrBasicAuthLogin = NULL); //!< ����� basic-�������������� (������ ��������������� ������������ � ��������� ����������)

//!\brief ������� ����������� ���������� ������, ������������ security context �� thtread storage.
KLCSTR_DECL bool KLAVT_AccessCheckForAction_InCall(
	        AVP_dword dwActionGroupID, //!< ������������ ���������� ������ ������� (��. "ACLDecl.h")
	        AVP_dword dwAccessMasks, //!< ������� ����� ��������� ���� ������� (��. "ACLDecl.h")
	        bool bGenerateException = true, //!< ������������ �� ���������� KLSTD::STDE_NOACCESS, ��� ���������� false
            const std::wstring* pwstrBasicAuthLogin = NULL); //!< ����� basic-�������������� (������ ��������������� ������������ � ��������� ����������)

//!\brief ������� ����������� ���������� ������, ������������ security context �� thtread storage.
KLCSTR_DECL bool KLAVT_AccessCheckForActionInGroup_InCall(
	        AVP_dword dwActionGroupID, //!< ������������ ���������� ������ ������� (��. "ACLDecl.h")
	        AVP_dword dwAccessMasks, //!< ������� ����� ��������� ���� ������� (��. "ACLDecl.h")
			const long	&lGroupId,	//!< ������������� ������ �����������������
	        bool bGenerateException = true, //!< ������������ �� ���������� KLSTD::STDE_NOACCESS, ��� ���������� false
            const std::wstring* pwstrBasicAuthLogin = NULL); //!< ����� basic-�������������� (������ ��������������� ������������ � ��������� ����������)

//!\brief ������� ����������� ���������� ������, ������������ security context �� thtread storage.
KLCSTR_DECL bool KLAVT_AccessCheckForActionForHost_InCall(
	        AVP_dword dwActionGroupID, //!< ������������ ���������� ������ ������� (��. "ACLDecl.h")
	        AVP_dword dwAccessMasks, //!< ������� ����� ��������� ���� ������� (��. "ACLDecl.h")
			const std::wstring &wstrHostId,	//!< ������������� �����
	        bool bGenerateException = true, //!< ������������ �� ���������� KLSTD::STDE_NOACCESS, ��� ���������� false
	        const std::wstring* pwstrBasicAuthLogin = NULL); //!< ����� basic-�������������� (������ ��������������� ������������ � ��������� ����������)

KLCSTR_DECL bool KLAVT_AccessCheckForComponent_InCall(
            AVP_dword                       dwAccessMask,
            const KLPRCI::ComponentId&      id,
            bool                            bGenerateException = true);

/*
bool KLAVT_AccessCheckForComponent_AccessToken(
            KLWAT::AccessTokenHolder*       pToken,
            AVP_dword                       dwAccessMask,
            const KLPRCI::ComponentId&      id,
            bool                            bGenerateException = true);
*/

/*
//!\brief ������� ������� ����������� �� ������� ACE_DECLARATION.
bool KLAVT_AccessCheck(
	AVP_dword dwDisiredAccess, //!< ������� ����� ��������� ���� ������� (��. "ACLDecl.h")
	const KLAVT::ACE_DECLARATION* pAcl, //!< ��������� �� ������ ACE_DECLARATION (access control entries - ��. "ACLDecl.h")
	long nAcl, //!< ����� ��������� � ������� pAcl
	bool bGenerateException = true); //!< ������������ �� ���������� KLSTD::STDE_NOACCESS, ��� ���������� false

//!\brief ������� ������� ����������� ����� ��������� AccessControlList.
bool KLAVT_AccessCheck(
	AVP_dword dwDisiredAccess, //!< ������� ����� ��������� ���� ������� (��. "ACLDecl.h")
	KLSTD::CAutoPtr<KLAVT::AccessControlList> pAclObj, //!< ��������� AccessControlList
	bool bGenerateException = true); //!< ������������ �� ���������� KLSTD::STDE_NOACCESS, ��� ���������� false


//!\brief ������� ����������� ���������� ������, ������������ security context �� thtread storage.
bool KLAVT_AccessCheckForAction(
	AVP_dword dwActionGroupID, //!< ������������ ���������� ������ ������� (��. "ACLDecl.h")
	AVP_dword dwDisiredAccess, //!< ������� ����� ��������� ���� ������� (��. "ACLDecl.h")
	KLSTD::CAutoPtr<AVTL::AclLibrary> pSecLib = NULL, //!< ����������-��������� ACL (�� ��������� ��� default product)
	KLSTD::CAutoPtr<KLPRCI::SecContext> pSecContext = NULL, //!< Security-context
	const std::wstring* pwstrBasicAuthLogin = NULL, //!< ����� basic-�������������� (������ ��������������� ������������ � ��������� ����������)
	bool bGenerateException = true); //!< ������������ �� ���������� KLSTD::STDE_NOACCESS, ��� ���������� false

//!\brief ������� ����������� ���������� ������, ������������ ����� current thread.
bool KLAVT_AccessCheckForActionDirect(
	AVP_dword dwActionGroupID, //!< ������������ ���������� ������ ������� (��. "ACLDecl.h")
	AVP_dword dwDisiredAccess, //!< ������� ����� ��������� ���� ������� (��. "ACLDecl.h")
	KLSTD::CAutoPtr<AVTL::AclLibrary> pSecLib = NULL, //!< ����������-��������� ACL (�� ��������� ��� default product)
	bool bGenerateException = true); //!< ������������ �� ���������� KLSTD::STDE_NOACCESS, ��� ���������� false

//!\brief ������� ����������� ��� ����������, ������������ security context �� thtread storage.
bool KLAVT_AccessCheckForComponent(
	AVP_dword dwDisiredAccess, //!< ������� ����� ��������� ���� ������� (��. "ACLDecl.h")
	const KLPRCI::ComponentId& compId, //!< ������������� ����������
	KLSTD::CAutoPtr<AVTL::AclLibrary> pSecLib = NULL, //!< ����������-��������� ACL (�� ��������� ��� default product)
	KLSTD::CAutoPtr<KLPRCI::SecContext> pSecContext = NULL, //!< Security-context
	bool bGenerateException = true); //!< ������������ �� ���������� KLSTD::STDE_NOACCESS, ��� ���������� false

//!\brief ������� ����������� ��� ����������, ������������ ����� current thread.
bool KLAVT_AccessCheckForComponentDirect(
	AVP_dword dwDisiredAccess, //!< ������� ����� ��������� ���� ������� (��. "ACLDecl.h")
	const KLPRCI::ComponentId& compId, //!< ������������� ����������
	KLSTD::CAutoPtr<AVTL::AclLibrary> pSecLib = NULL, //!< ����������-��������� ACL (�� ��������� ��� default product)
	bool bGenerateException = true); //!< ������������ �� ���������� KLSTD::STDE_NOACCESS, ��� ���������� false
*/
#endif //__KLAVT_ACCESSCHECK_H__

// Local Variables:
// mode: C++
// End:
