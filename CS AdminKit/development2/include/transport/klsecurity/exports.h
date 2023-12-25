/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	klsecurity/exports.h
 * \author	Mikhail Karmazine
 * \date	28.02.2003 12:44:11
 * \brief	�������������� �������, ������� ������ ������������ ��� ����������
 *              ���������� klsecurity.
 *          ������ ����� ���������� �� ������ �������� �� ������ ��������� (�� KLCSC,
 *          KLCSS, � �.�.), ����� �� ���� ����������� ������������ ��������� 
 *          ���� �� ����� (�.�. ���������������� klsecurity ����� ����������� 
 *          � ����� ����� ����������).
 *
 *          !!!!!!!!!!!!  ����� �����:   !!!!!!!!!!!!!
 *          ����� ����������� � ������ ���� ������� ����� ������ �����������,
 *          ��������� ������ ������� �� ������ ��������. ��� ���������� ����� 
 *          ������� ���� �� ������ ������ �� � ���� Exports.def, ���������  
 *          ��� ����� ������� ����� ordinals, �� ������ ordinals ��� ������ 
 *          �������.
 */

#ifndef __KLSECURITY_EXPORTS_H__
#define __KLSECURITY_EXPORTS_H__

#include <string>
#include "std/base/kldefs.h"
#include "kca/prci/componentid.h"
#include "transport/avt/acedecl.h"
#include "transport/klsecurity/common.h"

#ifdef KLSECURITY_EXPORTS
# define KLSECURITY_DECL     KLSTD_DLLEXPORT
#else
# define KLSECURITY_DECL     KLSTD_DLLIMPORT
#endif

/*!
  \brief	KLSEC_GetDLLType - ���������� ��� DLL

  \return	KLSEC::DLLType 
*/
KLSECURITY_DECL KLSEC::DLLType KLSEC_GetDLLType();
typedef KLSEC::DLLType (*KLSEC_PGetDLLType)();


/*!
  \brief	KLSEC_GetDLLVersion - ���������� ������ DLL

  \return	KLSEC::DLLVersion 
*/
KLSECURITY_DECL KLSEC::DLLVersion KLSEC_GetDLLVersion();
typedef KLSEC::DLLVersion (*KLSEC_PGetDLLVersion)();



/*!
  \brief	KLSEC_GetACLDeclForComponent
    ���������� ������ �� �������� KLAVT::ACE_DECLARATION � ������ ����� �������.
    (���� ������ ����� ����� �������� � ������� KLAVT_CreateACL ��� ���������
    �������, ���������������� ���������� ACL) �����-���� �������� �� ��������
    ����������� ������� ��������� �� �����.

    ����� ������ ������ ����� ������� � ����������, � ����� ������ ������� ��
        ID ���������� � ��������, ������� �� ����� ��� ��� ����������.

    !!!!!!! ������� �� ����������� ����������, � ���������� ��������� true/false !!!!!

  \param	LPRCI::ComponentId compId - ID ����������.
  \param	const KLAVT::ACE_DECLARATION** ppAceDeclList - ������ � ��������� ACE
  \param	int* pnAceCount [out] - ������ �������
  \return	bool - true ���� ��� ������, false � ��������� ������.
*/

KLSECURITY_DECL bool KLSEC_GetACLDeclForComponent(
							const KLPRCI::ComponentId&			compId,
							const KLAVT::ACE_DECLARATION**		ppAceDeclList,
							long*								pnAceCount);

typedef bool (*KLSEC_PGetACLDeclForComponent)(
							const KLPRCI::ComponentId&			compId,
							const KLAVT::ACE_DECLARATION**		ppAceDeclList,
							long*								pnAceCount);


KLSECURITY_DECL bool KLSEC_GetACLDeclForComponentTask(
							const KLPRCI::ComponentId&			compId,
							const std::wstring&					wstrTaskName,
							const KLAVT::ACE_DECLARATION**		ppAceDeclList,
							long*								pnAceCount);

typedef bool (*KLSEC_PGetACLDeclForComponentTask)(
							const KLPRCI::ComponentId&			compId,
							const std::wstring&					wstrTaskName,
							const KLAVT::ACE_DECLARATION**		ppAceDeclList,
							long*								pnAceCount);

typedef struct
{
    const wchar_t*  szwType;
    long            lType;
    long            lSubType;
}KLSEC_SECTION_DESC, *PKLSEC_SECTION_DESC;


KLSECURITY_DECL bool KLSEC_GetACLDeclForSection(
                            const KLSEC_SECTION_DESC&           type,
                            const wchar_t*                      szwProduct,
                            const wchar_t*                      szwVersion,
                            const wchar_t*                      szwSection,
							const KLAVT::ACE_DECLARATION**		ppAceDeclList,
							long*								pnAceCount);

typedef bool (*KLSEC_PGetACLDeclForSection)(
                            const KLSEC_SECTION_DESC&           type,
                            const wchar_t*                      szwProduct,
                            const wchar_t*                      szwVersion,
                            const wchar_t*                      szwSection,
							const KLAVT::ACE_DECLARATION**		ppAceDeclList,
							long*								pnAceCount);

KLSECURITY_DECL bool KLSEC_GetACLDeclForAction(
							AVP_dword							dwActionGroupID,
							const KLAVT::ACE_DECLARATION**		ppAceDeclList,
							long*								pnAceCount);

typedef bool (*KLSEC_PGetACLDeclForAction)(
							AVP_dword							dwActionGroupID,
							const KLAVT::ACE_DECLARATION**		ppAceDeclList,
							long*								pnAceCount);


/*!
  \brief	����������� ������, ���������� ACL
*/
KLSECURITY_DECL void KLSEC_FreeACL(
							const KLAVT::ACE_DECLARATION*		pAceDeclList);

typedef void (*KLSEC_PFreeACL)(
							const KLAVT::ACE_DECLARATION*		pAceDeclList);


/*!
  \brief	��������� ����� ACL
  \param	pAceDeclList [in]
  \return	-1 � ������ ������, ����� �����
*/
KLSECURITY_DECL long KLSEC_GetACLLen(
							const KLAVT::ACE_DECLARATION* pAceDeclList);

typedef long (*KLSEC_PGetACLLen)(
							const KLAVT::ACE_DECLARATION* pAceDeclList);


#endif //__KLSECURITY_EXPORTS_H__

// Local Variables:
// mode: C++
// End:
