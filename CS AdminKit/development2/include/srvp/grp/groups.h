/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file GRP/Groups.h
 * \author ������ ��������
 * \date 2002
 * \brief ��������� ��� ��������� � �������������� ���������� � ���������� ������� 
 *        � ������� �����������������.
 *
 */

#ifndef KLGRP_GROUPS_H
#define KLGRP_GROUPS_H

#include <time.h>
#include <string>
#include <vector>

#include <std/base/klbase.h>
#include <std/par/params.h>
#include <srvp/admsrv/admsrv.h>
#include <server/srvinst/server_constants.h>

namespace KLGRP {
	
    const wchar_t c_grp_array_groups[] = L"groups";  // ��� ��������� '������ �����'
	const wchar_t c_grp_array_hosts[] = L"hosts";  // ��� ��������� '������ ������'

//! ����� ����� � ���������� Params � ���������� � ������.
    //! ������������� ������ � ���� ������
	const wchar_t c_grp_id[] = L"id";  //INT_T
	//! ��� ������.
    const wchar_t c_grp_name[] = L"name"; // STRING_T, 
	//! ������������� ������������ ������.
    const wchar_t c_grp_parentId[] = L"parentId"; // INT_T
	//! ����� ���� ������� ������
    const wchar_t c_grp_creationDate[] = L"creationDate"; // TIME_T
	//! ��������� ����� ���������� ���������� � ������
    const wchar_t c_grp_lastUpdate[] = L"lastUpdate"; // TIME_T
	//! ������ ����� ����������� � ������ (�� ���� ���������)
    const wchar_t c_grp_hostsNum[] = L"hostsNum"; // INT_T
	//! ������ ����� �������� ����� � ������ (�� ���� ���������)
    const wchar_t c_grp_childGroupsNum[] = L"childGroupsNum"; // INT_T   
	/*!
		������������� ������, � ������� ����� ������������� ���������
		����������, ���������� � ������ ������ - ��������� ������ UNASSIGNED.
		(������ ��� ����� - �������� ������ UNASSIGNED).
	*/
	const wchar_t c_grp_autoAddHost[] = L"autoAddHost"; //INT_T

    //! auto add hosts with active nagent only
    const wchar_t c_grp_autoAddNagentOnly[] = L"autoAddHostOnlyNagents";

	//! ����� ����, ����� ������� ���� ������� ���������� ��������� �� ������.
    const wchar_t c_grp_autoRemovePeriod[] = L"autoRemovePeriod"; // INT_T
	//! ����� ����, ����� ������� �������������� ���������� ��������� � ������������ ����������.
    const wchar_t c_grp_notifyPeriod[] = L"notifyPeriod"; // INT_T
	//! ������� ����������� ������ � ������ �����.
    const wchar_t c_grp_level[] = L"level"; // INT_T
	//! ���� �� ������������� �������������� ���������.
    const wchar_t c_grp_autoInstallPackageId[] = L"c_grp_autoInstallPackageId"; // ARRAY_T|INT_T

	//! host moving rule: adsunit
    const wchar_t c_grp_move_rule_adsunit[] = L"grp_mr_adsunit"; // INT_T    

	//! host moving rule: diapason
    const wchar_t c_grp_move_rule_diapason[] = L"grp_mr_diapason"; // INT_T

	//! host moving rule: unassigned group
    const wchar_t c_grp_move_rule_unassigned[] = L"grp_mr_unassigned"; // INT_T
	
    //! group full name
    const wchar_t c_grp_full_name[] = L"grp_full_name"; // STRING_T    
    //! enable full scan
    const wchar_t c_grp_enable_fscan[] = L"grp_enable_fscan"; // BOOL_T
    //!Hosts status "Critical" settings for group.
    const wchar_t c_grp_hoststat_critical[] = KLSRV_HSTSTAT_CRITICAL; //PARAMS_T
    //!Hosts status "Warning" settings for group.
    const wchar_t c_grp_hoststat_warning[] = KLSRV_HSTSTAT_WARNING; //PARAMS_T
    /*! 
        Hosts statuses "Critical" and "Warning" settings for group. 
        These Params has following  values:
            KLSRV_HSTSTAT_INHERITED (BOOL_T) Status settings are inherited from parent
            KLSRV_HSTSTAT_INHERITABLE (BOOL_T) Status settings may be inherited from parent
            KLSRV_HSTSTAT_LOCKED (BOOL_T) Status settings are locked (by policy). 
            KLSRV_HSTSTAT_MASK (INT_T) status mask
            KLSRV_HSTSTAT_SP_VIRUSES (INT_T)
            KLSRV_HSTSTAT_SP_RPT_DIFFERS (INT_T)
            KLSRV_HSTSTAT_OLD_FSCAN (INT_T)
            KLSRV_HSTSTAT_OLD_AV_BASES (INT_T)
            KLSRV_HSTSTAT_OLD_LAST_CONNECT (INT_T)
    */   


	//! ���������������� �������������� ����������� �����
	typedef enum{
		GROUPID_ROOT = 0,		//< ������ 'Groups'
		GROUPID_UNASSIGNED = 1,	//< ������ 'Unassigned'
		GROUPID_INVALID_ID = -1	//< �������� ������������� ������ (��������, ���� ����������� ������������ ������)
	}KLGRP_GROUPID;

	/*!
	* \brief ��������� ��� ��������� � �������������� ���������� � ����������
	*        ������� � ������� �����������������.
	*
	*   ������ - ��� ����� �����������, ������������ ��������������� ���
	*   �������� ����������. 
	*
	*   ������ ����� ���� ������� � ������ ������.
	*/

    class Groups : public KLSTD::KLBaseQI
	{
    public:
    /*!
      \brief ���������� ������ ���������� ����� � ����.

        ������ ������������ � ���� ���������� Params, ���������� ��������� ��������
        ��������� ��������� ������ �����. ��������� �������� ������ ���� ���� � ������
        groups(���������� � c_grp_array_groups), 
		������� ������������ ����� ������ (ARRAY_T) ����������� Params, ������ 
        ������� �� ������� ���������� ���� 'id', 'name' � 'groups'. ���� 'id' ��������
        ������������� ������ � ���� ������, ���� 'name' - ��� ������, � ���� 'groups'
        �������� ����������� ������ (ARRAY_T) �� ������� ��������� �����.  ���� 'groups'
        ����� �������������, ���� � ������� ������ ����������� ��������� ������.

        \param groups [out] ������ ����� � ����.
        \param parent [in]  ������������� ������������ ������. �� ��������� ������������
                            ������, ������� � �������� ������.
        \param depth  [in]  ������� ����������� ��� ��������� ������ �����.  �� ���������
                            ������������ ��� ������.
       
    */
		virtual void GetGroups ( 
                        KLPAR::Params**	groups,
                        long			parent = GROUPID_ROOT,
                        long			depth = 0 )  = 0;


    /*!
      \brief ���������� ���������� � ������.


        \param id   [in]    ������������� ������ ��� ��������� ����������.
        \param info [out]   ��������� � ���������� ������. 
		
		\except STDE_NOTFOUND ��������� ������ �� �������
       
    */
        virtual void GetGroupInfo ( long id, KLPAR::Params ** groups )  = 0;


    /*!
      \brief ��������� ����� ������.
       
        \param info [in] �������� ����������� ������.
				����� ���� ������ ��������� ��������:
						������������ ��������: c_grp_name, c_grp_parentId
						�������������� ��������:
												c_grp_autoAddHost,
												c_grp_autoInstall,
												c_grp_autoRemovePeriod,
												c_grp_notifyPeriod
				������ �������� ������������.
		\return ������������� ����������� ������

		\except STDE_NOTFOUND ������������ ������ �� �������
		\except STDE_EXIST ������ � ��������� ������ ��� ����������.
    */
        virtual long AddGroup (KLPAR::Params * info)  = 0;


    /*!
      \brief ������� ������.
       
        \param id [in] ������������� ��������� ������. 
        
		\except STDE_NOTEMPTY group contains objects that cannot be deleted
    */
        virtual void DelGroup ( long id )  = 0;
		


    /*!
      \brief ������������ �������� ������.
       
        \param id   [in] ������������� ���������� ������.
        \param info [in] ���������� �������� ������.
				�������� ����� ���� ��������� ��������:
												c_grp_name,
												c_grp_autoAddHost,
												c_grp_autoInstall,
												c_grp_autoRemovePeriod,
												c_grp_notifyPeriod,
												c_grp_parentId
						������ �������� ������������.

		\except STDE_EXIST ������ � ��������� ������ ��� ����������.
    */
        virtual void UpdateGroup ( long id, KLPAR::Params * info )  = 0;

    /*
        \brief ������������� �� ������ �������� ��������� ������ ����������� � ������.

        \param id       [in] ������������� ������ ��� ��������� ������ �����������.
        \param fields   [in] ������ ��������� ����������� ��� ���������.
		\param size		[in] ���������� ��������� ����������� ��� ���������.
        \param lifetime [in] ����� ����� ������� ����������� �� ������� (���) �����
                            ���������� ������� �������.
    */

        virtual void ResetGroupHostsIterator ( 
            long				id, 
			const wchar_t**		fields,
			int					size,
            long				lifetime = 20)  = 0;


    /*
        \brief �������� ���������� � ��������� ���������� � ������.

        \param nCount	[in, out] ���������� �������, ������� ���������� �������.
									���� �� ��������� ���������� ������� ��������� �������.
        \param info     [in] �������� ���������� c ������ c_grp_array_hosts ���� ARRAY_T.
							�������� ����� ������� ����� ��� PARAMS_T � �������� �������� ���������� � ������.
		\return	false, ���� ��������� ����� ������ �����������.

    */

        virtual bool GetNextGroupHost( long& nCount, KLPAR::Params ** info )  = 0;


    /*!
      \brief ���������� ���������� � ������.
       
        \param id       [in] ������������� ������ ��� ���������� �����������.
        \param hosts    [in] ������ ���� ����������� � ������.
    */
        virtual void AddHosts ( 
                        long								id, 
                        const std::vector<std::wstring>&	hosts )  = 0;

    /*!
      \brief ������� ���������� �� ������. ���������� ��������� �
            ����������� ������ Unassigned.
       
        \param id       [in] ������������� ������ ��� �������� �����������.
        \param hosts    [in] ������ ���� �����������.
    */
        virtual void RemoveHosts ( 
                        const std::vector<std::wstring>&	hosts )  = 0;



    /*!
      \brief ������������� ������ ����������� ��� ������.
        ��������� �������� ���������� KLHST::c_hst_array_hosts, ����������
        ������ ������

       
        \param id       [in] ������������� ������ ��� ����������� ������ �����������.
        \param hosts    [in] ������ ���� ����������� ��� ���������� � ������.
    */
        virtual void SetGroupHosts ( 
                        long						id, 
                        KLPAR::Params*				hosts)  = 0;



        /*!
          \brief	���������� ����� � ������ �� ������ �� ���� ��� ip-������.
            ���� ��������� ��� ������������� ������� ip-������, �� ������
            �������� ����� � ���� ���� � ���������� ip-�������. � ���������
            ������ ������ �������� ���������������� ���� ��������� �������:
                1. ���              (c_wks_name)
                2. ������������ ��� (c_wks_display_name)
                3. ��� NetBIOS      (c_wks_win_name)
                4. ��� DNS          (c_wks_dnsName)

          \param	pInfo - ������� ��������� Params - ������ ��������� ����������:
                        KLHST::c_wks_anyname_array - ������ ����� - "����" ������
                        KLHST::c_wks_groupId - ������������� ������, � �������
                            ��������������� ������ ���� ��������
          \param	pResults - �������� ��������� Params - �������� ����������
                        c_hst_array_results - ������ ������� �������, ���� i-� �������
                        ������� ������� ����� false, �� i-� ���� �������� �������
                        c_wks_anyname_array �� ������� ��������� � ������
                        (�� ������� ��������� ���).
        */
        virtual void ResolveAndMoveToGroup(
                        KLPAR::Params*  pInfo,
                        KLPAR::Params** pResults) = 0;
        

        /*!
          \brief	���������� �����, ����������� � ����� ������ lSrcGroupId
                    � ������ ������ lDstGroupId. ����������� ����������.

          \param	lSrcGroupId [in] ������-��������
          \param	lDstGroupId [in] ������-����������
          \param	pSink [in] ��������� �� KLADMSRV::AdmServerAdviseSink
          \param	hSink [out] ������������� ��������
        */
        virtual void MoveGroupHosts(
                                long                            lSrcGroupId,
                                long                            lDstGroupId,
                                KLADMSRV::AdmServerAdviseSink*  pSink,
                                KLADMSRV::HSINKID&              hSink) = 0;
        

        /*!
          \brief	�������� ������� ���������� ��������� ������� ��� ����
                    ������ ������ � ��������. ����������� ����������.

          \param	lGroupId [in] ������������� ������
          \param	pSink [in] ��������� �� KLADMSRV::AdmServerAdviseSink
          \param	hSink [out] ������������� ��������
        */
        virtual void ZeroVirusCount(
                                long                            lGroupId,
                                KLADMSRV::AdmServerAdviseSink*  pSink,
                                KLADMSRV::HSINKID&              hSink) = 0;

        /*!
          \brief	�������� ������� ���������� ��������� ������� ���
                    ��������� ������. ����������� ����������.

          \param	vecHosts [in] ������ ������
          \param	pSink [in] ��������� �� KLADMSRV::AdmServerAdviseSink
          \param	hSink [out] ������������� ��������
        */
        virtual void ZeroVirusCount(
                            const std::vector<std::wstring>&    vecHosts,
                            KLADMSRV::AdmServerAdviseSink*      pSink,
                            KLADMSRV::HSINKID&                  hSink) = 0;

    //OBSOLETE

        inline void AddHosts( 
                            long								id, 
                            const std::wstring&                 domain,
                            const std::vector<std::wstring>&	hosts )
        {
            AddHosts(id, hosts);
        };

        inline void RemoveHosts ( 
                        const std::wstring&                 domain,
                        const std::vector<std::wstring>&	hosts )
        {
            RemoveHosts(hosts);
        }
    };

    //OBSOLETE
	//! ���� �� ������������� �������������� ���������.
    const wchar_t c_grp_autoInstall[] = L"autoInstall"; // BOOL_T

}

/*!
  \brief ������� ������ ������ KLGRP::Groups

    \param groups      [out] ��������� �� ������ ������ KLGRP::Groups
*/
KLCSSRVP_DECL void KLGRP_CreateGroups(
								   const wchar_t*   szwAddress,
								   KLGRP::Groups ** ppGroups,
								   const unsigned short*  pPorts = NULL,
                                   bool             bUseSsl = true);


#endif // KLGRP_GROUPS_H
