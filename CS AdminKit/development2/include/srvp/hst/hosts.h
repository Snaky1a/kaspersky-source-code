/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file HST/Hosts.h
 * \author ������ ��������
 * \date 2002
 * \brief ��������� ��� ��������� ���������� � ����������� � ���������� ���� 
 *        ������� �����������������.
 *
 */

#ifndef KLHST_HOSTS_H
#define KLHST_HOSTS_H

#include <time.h>
#include <string>
#include <vector>
#include <map>

#include <std/base/klbase.h>
#include <std/hstd/hostdomain.h>
#include <std/par/params.h>
#include <kca/prss/settingsstorage.h>
#include <kca/prts/tasksstorage.h>
#include <kca/prcp/agentproxy.h>

#include <srvp/evp/eventpropertiesclient.h>
#include <transport/ev/ev_general.h>

#include <srvp/admsrv/admsrv.h>
#include <srvp/grp/groups.h>
#include <srvp/updsrv/updsrv.h>
#include <srvp/licsrv/licsrv.h>
#include <srvp/pol/policies.h>

//#include <../apps/server/errors.h"
//#include "../naginst/errors.h"

namespace KLHST
{
	const wchar_t c_szwUnknownDomain[]=L"*";
    //! ������������ ��������� ����� ������� � ����
	typedef enum
	{
		DT_WIN_DOMAIN=KLSTD::KLDT_WIN_DOMAIN,
		DT_WIN_WORKGROUP=KLSTD::KLDT_WIN_WORKGROUP
	}DomainType;

//    enum DomainType {
  //      DT_WIN_DOMAIN,  ///< Windows NT �����
    //    DT_WIN_WORKGROUP,  ///< ������� ������ Windows NT
//    };

    //! ������������ ��������� ��������� ���������� � ����.
    enum ComputerStatus {
        CS_VISIBLE =            0x00000001, ///< ��������� ������� � ������������ � ����.
        CS_ADDEDTOGROUP =       0x00000002, ///< ��������� �������� � ������
        CS_AGENTINSTALLED =     0x00000004, ///< �� ��������� ������������� ����� �����������������
        CS_AGENTISALIVE =       0x00000008, ///< ����� ����������������� ��������� ������������� 
        CS_PRODUCTINSTALLED =   0x00000010, ///< �� ��������� ������������� rtp.
        CS_INROAMINGMODE =      0x00000020  ///< ��������� � ������ roaming mode
    };

    //! ������������ ��������� ��������������� ������� ����������.
    typedef enum
    {
        CSID_OK =        0x00000000,
        CSID_CRITICAL =  0x00000001,
        CSID_WARNING =   0x00000002
    }ComputerStatusID;
    
    typedef enum
    {
        SMC_HOST_OUT_OF_CONTROL = 0x00000001,
        SMC_RPT_NOT_RUNNING     = 0x00000002,
        SMC_AV_NOT_RUNNING      = 0x00000004,
        SMC_VIRUSES             = 0x00000008,
        SMC_RPT_DIFFERS         = 0x00000010,
        SMC_NO_AV_SOFTWARE      = 0x00000020,
        SMC_OLD_FSCAN           = 0x00000040,
        SMC_OLD_AV_BASES        = 0x00000080,
        SMC_OLD_LAST_CONNECT    = 0x00000100,
        SMC_OLD_LICENSE         = 0x00000200,
        SMC_UNCURED             = 0x00000400
    }StatusMaskCondition;
    

    typedef enum
    {
        MaskRtpState_Stopped                = 0x00010000,
        MaskRtpState_Suspended              = 0x00020000,
        MaskRtpState_Starting               = 0x00040000,
        MaskRtpState_Running                = 0x00080000,
        MaskRtpState_Running_MaxProtection  = 0x00100000,
        MaskRtpState_Running_MaxSpeed       = 0x00200000,
        MaskRtpState_Running_Recomended     = 0x00400000,
        MaskRtpState_Running_Custom         = 0x00800000,
        MaskRtpState_Failure                = 0x01000000
    }RtpStateMask;


	const wchar_t c_hst_array_hosts[] = L"KLHST_WKS_HOSTS";  // ��� ��������� '������ ������'
	const wchar_t c_hst_array_results[] = L"KLHST_WKS_RESULTS";  // 

//! ����� ����� � ���������� Params � ���������� � ������� ������� � ����.

    //! INT_T, ������������� ������ � ���� ������
    const wchar_t c_wks_id[]			= L"KLHST_WKS_ID";  
    //! INT_T, ������������� ������, � ������� ������� ������ ���������.
    const wchar_t c_wks_groupId[]		= L"KLHST_WKS_GROUPID"; 
    //! TIME_T, ����� ��������� ��������� ��� ��������� � ����
    const wchar_t c_wks_lastVisible[]	= L"KLHST_WKS_LAST_VISIBLE"; 
    //! TIME_T, ��������� ����� ���������� ���������� � ����������
    const wchar_t c_wks_lastInfoUpdate[]= L"KLHST_WKS_LAST_INFOUDATE"; 
    //! INT_T, ������� ��������� ���������� �� ������������ ComputerStatus.
    const wchar_t c_wks_status[]		= L"KLHST_WKS_STATUS";
    //! TIME_T ��������� ����� ��������� ���������� �����������
    const wchar_t c_wks_lastUpdate[]	= L"KLHST_WKS_LAST_UPDATE"; 
    //! TIME_T ��������� ����� ���������� � ������� �������
    const wchar_t c_wks_lastNagentConnected[] = L"KLHST_WKS_LAST_NAGENT_CONNECTED";
    //! BOOL_T ���� false, �� ������ ����� ����� ���������� � ������� ������� ����� ������� �����
    const wchar_t c_wks_keepConnection[]	= L"KLHST_WKS_KEEP_CONNECTION";
    //! ������������ ��� ����������, ��������������� ��� ������ ���������
    const wchar_t c_wks_display_name[]	= L"KLHST_WKS_DN";	// STRING_T
    //! ��� ����������
    const wchar_t c_wks_name[]			= L"KLHST_WKS_HOSTNAME"; // STRING_T
    //! NetBIOS-��� ����������     
    const wchar_t c_wks_win_name[]		= L"KLHST_WKS_WINHOSTNAME";			// STRING_T
    //! ��� Windows-������
    const wchar_t c_wks_domain[]		= L"KLHST_WKS_WINDOMAIN";		// STRING_T
    const wchar_t c_wks_win_domain[]	= L"KLHST_WKS_WINDOMAIN";	// STRING_T
    //!
    const wchar_t c_wks_win_domain_type[]	= L"KLHST_WKS_WINDOMAIN_TYPE";		// STRING_T
    //! DNS-�����
    const wchar_t c_wks_dnsDomain[]		= L"KLHST_WKS_DNSDOMAIN";		// STRING_T
    //! DNS - ���
    const wchar_t c_wks_dnsName[]		= L"KLHST_WKS_DNSNAME";		// STRING_T
    //! ��� ���������� (��. )
    const wchar_t c_wks_ctype[]			= L"KLHST_WKS_CTYPE";			// INT_T
    //! ��� ��������� (��. )
    const wchar_t c_wks_ptype[]			= L"KLHST_WKS_PTYPE";			// INT_T
    //! ������� ����� ������ ��
    const wchar_t c_wks_versionMajor[]	= L"KLHST_WKS_OS_VER_MAJOR";	// INT_T
    //! ������� ����� ������ ��
    const wchar_t c_wks_versionMinor[]	= L"KLHST_WKS_OS_VER_MINOR";	// INT_T
    //! ����� ����� with network byte order
    const wchar_t c_wks_ip[]			= L"KLHST_WKS_IP";			// INT_T
    //! �������������� ��� �����
    const wchar_t c_wks_presumed_groupname[]= L"KLHST_WKS_PRESUMED_GROUPNAME";			// INT_T
    //! ����� ���������� ������� ������������ ����������
    const wchar_t c_wks_lastFullScan [] = L"KLHST_WKS_LAST_FULLSCAN"; //DATE_TIME_T
    //! ���������� ����������� �������
    const wchar_t c_wks_VirusCount[] = L"KLHST_WKS_VIRUS_COUNT";//LONG_T
    //! ������ rtp-������
    const wchar_t c_wks_RtpState[] = L"KLHST_WKS_RTP_STATE";//INT_T
    //! ��� ������ rtp-������
    const wchar_t c_wks_RtpErrorCode[] = L"KLHST_WKS_RTP_ERROR_CODE";//INT_T
    //! Hosts's public key
    const wchar_t c_wks_public_key[] = L"KLHST_WKS_PKEY";

    //! User comments for host
    const wchar_t c_wks_comment[] = L"KLHST_WKS_COMMENT";   //STRING_T
    
    //! ����� ����� (�����������) with host byte order
    const wchar_t c_wks_ip_long[]			= L"KLHST_WKS_IP_LONG";			// LONG_T
    
    //! ����� �����, ���������� ��� �������� (�����������) with host byte order
    const wchar_t c_wks_connect_ip_long[]			= L"KLHST_WKS_CONNECT_IP_LONG";			// LONG_T
    
    //! (starting from Mantainance Pack 3)
    const wchar_t c_wks_from_unassigned[] = L"KLHST_WKS_FROM_UNASSIGNED"; // BOOL_T

    //! (starting from v 7)
    const wchar_t c_wsk_UncuredCount[] = L"KLHST_WKS_UNCURED_COUNT"; //LONG_T

    //! ID ������� ����� (ComputerStatusID)
    const wchar_t c_wks_status_id[]		= L"KLHST_WKS_STATUS_ID"; //INT_T

    /*!
        ����� ������� �����. ��� i � ����� ������� ��������, 
        ��� i-�� ������� ���� ��������.
        ��������� �������:
        ��� �������
        0.  �������� ����� � ���������� ����������� (�� ����� � ����, �� ����� �� ����������� � ��������).
        1.  �� �������� RTP ������ �� ����������, � ��� ���� ���������� ���������.
        2.  �� ���������� �� ��������� ��������� (�� �������������, �� �� ����������).
        3.  ����� ��������� �� ���������� ������� ����� ��� N.  ����� N �������� ��������������� (KLSRV_HSTSTAT_SP_VIRUSES). 
        4.  ������� RTP ������ ���������� �� ��������� ���������������, � ��� ���� ���������� ��������� (KLSRV_HSTSTAT_SP_RPT_DIFFERS).
        5.  �� ��������� �� ����������� ������������ ������ (����� ���� ��������� ��� WKS, FS). 
        6.  ��������� �� ������������ ����� N ����, � ��� ���� ���������� ���������. ����� N ������������� ��������������� (KLSRV_HSTSTAT_OLD_FSCAN).
        7.  ������������ ���� �� ����������� N ����, � ��� ���� ���������� ���������. ����� N ������������� ��������������� (KLSRV_HSTSTAT_OLD_AV_BASES).
        8.  ��������� �� ������������� � ������� � ������� N ����, � ��� ���� ���������� ������� �����.  ����� N ������������� ��������������� (KLSRV_HSTSTAT_OLD_LAST_CONNECT).
        9.  �������� �������� (��� ������� Critical), �� ��������� �������� �������� ����� N ����. ����� N ������������� ��������������� (KLSRV_HSTSTAT_OLD_LICENSE).
        10. ����� ������������ �� ���������� �������� ����� ��� N. ����� N �������� ��������������� (KLSRV_HSTSTAT_SP_UNCURED). 

        � ������ ������������� ������ ������ �������, ������� �����
        �������, ���������� �������� GetPrimaryStatusCondition.
    */
    const wchar_t c_wks_status_mask[]		= L"KLHST_WKS_STATUS_MASK"; //INT_T
    

    //! Full version of network agent installed on host (KLADMSRV_SV70 and higher)
    const wchar_t c_wks_nagent_version[]		= L"KLHST_WKS_NAG_VERSION"; //STRING_T

    //! Full version of anti-virus with rtp installed on host (KLADMSRV_SV70 and higher)
    const wchar_t c_wks_rtp_av_version[]		= L"KLHST_WKS_RTP_AV_VERSION"; //STRING_T

    //! AV bases date of anti-virus with rtp installed on host (KLADMSRV_SV70 and higher)
    const wchar_t c_wks_rtp_av_bases_time[]		= L"KLHST_WKS_RTP_AV_BASES_TIME"; //DATETIME_T
    
   
    //!Following fields may be used only while searching for hosts    
        //!product name
        const wchar_t c_wks_product_name[] = L"KLHST_WKS_PRODUCT_NAME";//STRING_T
        //!product version
        const wchar_t c_wks_product_version[] = L"KLHST_WKS_PRODUCT_VERSION";//STRING_T
        //!product display version
        const wchar_t c_wks_product_display_version[] = L"KLHST_WKS_PRODUCT_DISPLAY_VERSION";//STRING_T
        //!product AV bases record count
        const wchar_t c_wks_product_avbases_records[] = L"KLHST_WKS_AV_BASES_RECORDS";//INT_T
        //!product AV bases date
        const wchar_t c_wks_product_avbases_date[] = L"KLHST_WKS_AV_BASES_DATE";//DATETIME_T
		//!competitor_product name
        const wchar_t c_wks_competitor_product_name[] = L"KLHST_WKS_COMPETITOR_PRODUCT_NAME";//STRING_T
		//!inventory_product strId
        const wchar_t c_inventory_product_strid[] = L"KLHST_INVENTORY_PRODUCT_STRID";//STRING_T
		//!inventory_product name
        const wchar_t c_inventory_product_name[] = L"KLHST_INVENTORY_PRODUCT_NAME";//STRING_T
		//!inventory_product version
        const wchar_t c_inventory_product_display_version[] = L"KLHST_INVENTORY_PRODUCT_DISPLAY_VERSION";//STRING_T
		//!inventory_product publisher
        const wchar_t c_inventory_product_publisher[] = L"KLHST_INVENTORY_PRODUCT_PUBLISHER";//STRING_T
		//!inventory_product_install_date
        const wchar_t c_inventory_product_install_date[] = L"KLHST_INVENTORY_PRODUCT_INSTALL_DATE";//DATE_TIME_T
		//!inventory_product_install_dir
        const wchar_t c_inventory_product_install_dir[] = L"KLHST_INVENTORY_PRODUCT_INSTALL_DIR";//STRING_T
		//!inventory_patch name
        const wchar_t c_inventory_patch_name[] = L"KLHST_INVENTORY_PATCH_NAME";//STRING_T
		//!inventory_patch version
        const wchar_t c_inventory_patch_display_version[] = L"KLHST_INVENTORY_PATCH_DISPLAY_VERSION";//STRING_T
		//!inventory_patch publisher
        const wchar_t c_inventory_patch_publisher[] = L"KLHST_INVENTORY_PATCH_PUBLISHER";//STRING_T
        //!ads OU
        const wchar_t c_wks_ad_org_unit[] = L"KLHST_AD_ORGUNIT";//INT_T
        
        //! hosts belongs to the specified unit or it's subunit
        const wchar_t c_wks_ad_org_unit_grandparent[] = L"KLHST_AD_ORGUNIT_GP";//INT_T

        //! hosts belongs to the specified group or it's subgroup
        const wchar_t c_wks_groupId_grandparent[] = L"KLHST_WKS_GROUPID_GP";//INT_T
        
        //! network agent installation id (see KLNAG_INSTALLATION_ID), search-only
        const wchar_t c_wks_nagent_instid[] = L"KLHST_NAG_INSTID";//STRING_T
        
        //! host has uncured objects (starting from v 7)
        const wchar_t c_wks_uncured_present[] = L"KLHST_UNCURED_PRESENT"; //BOOL_T

        /*! status bits (for search only)
            c_wks_status_mask_bit* is non-zero if corrsponding bit is set 
            otherwise c_wks_status_mask_bit* is zero

            DEPRECATED, use biwise operation instead
        */
        const wchar_t c_wks_status_mask_bit0[]		= L"KLHST_WKS_STATUS_MASK_0"; //INT_T
        const wchar_t c_wks_status_mask_bit1[]		= L"KLHST_WKS_STATUS_MASK_1"; //INT_T
        const wchar_t c_wks_status_mask_bit2[]		= L"KLHST_WKS_STATUS_MASK_2"; //INT_T
        const wchar_t c_wks_status_mask_bit3[]		= L"KLHST_WKS_STATUS_MASK_3"; //INT_T
        const wchar_t c_wks_status_mask_bit4[]		= L"KLHST_WKS_STATUS_MASK_4"; //INT_T
        const wchar_t c_wks_status_mask_bit5[]		= L"KLHST_WKS_STATUS_MASK_5"; //INT_T
        const wchar_t c_wks_status_mask_bit6[]		= L"KLHST_WKS_STATUS_MASK_6"; //INT_T
        const wchar_t c_wks_status_mask_bit7[]		= L"KLHST_WKS_STATUS_MASK_7"; //INT_T
        const wchar_t c_wks_status_mask_bit8[]		= L"KLHST_WKS_STATUS_MASK_8"; //INT_T

    /*!
        ��� ����������, ��������� �������������
        ����� �������� (����������� � ��������� �������)
               1. ip-�������
               2. ��������������� �����
               3. ������������ ������
               4. ������ NetBIOS
               5. ������ DNS
    */
    const wchar_t   c_wks_anyname_array[]     = L"KLHST_WKS_ANYNAME";     //SRING_T
    
    /*! \brief  ���������� � ������� ���������� ����� �� �����.
    ���������:

		c_spRtTsksInfo	//PARAMS_T
			<ProductName>	//PARAMS_T
				KLHST::c_spProductVersion	//STRING_T
				KLHST::c_spRtTskArray		//PARAMS_T|ARRAY_T 
					KLHST::c_tsk_State		//INT_T
					KLHST::c_tsk_StorageId	// STRING_T
    */    
    
    /*! \brief  ���������� � ������� ��������� �� �����.
    ���������:
        c_spHstAppInfo
            <product>
                <version>
                    c_spHstAppState - ��. ComponentInstanceState
                    c_spHstAppStateTime - ���� � ����� ���������� ���������� �������                            
    */
    const wchar_t c_spHstAppInfo[] = L"KLHST_APP_INFO";    //PARAMS_T
    const wchar_t c_spHstAppState[] = L"KLHST_APP_STATE";    //INT_T
    const wchar_t c_spHstAppStateTime[] = L"KLHST_APP_STATE_TIME";    //DATE_TIME_T
    
    const wchar_t c_spHostLocation[]=L"KLHST_LOCATION";
    const wchar_t c_spHostInstanceId[]=L"KLHST_INSTANCEID";
	
	//! ���������� � �������
	const wchar_t c_tsk_Type[]=L"taskType";				//STRING_T
	const wchar_t c_tsk_State[]=L"taskState";			//INT_T
    const wchar_t c_tsk_Completion[]=L"taskCompletion"; //INT_T
	const wchar_t c_tsk_Id[]=L"taskId";					//INT_T
	const wchar_t c_tsk_StorageId[]=L"taskStorageId";	//STRING_T

	//! ���������� �� �����������
	const wchar_t c_inst_State[]=L"instState";			//INT_T
	const wchar_t c_inst_Statistics[]=L"instStatistics";//PARAMS_T
	
	const wchar_t c_spProductName[]=L"klhst-ProductName";		//STRING_T
	const wchar_t c_spProductVersion[]=L"klhst-ProductVersion";	//STRING_T
	const wchar_t c_spComponentName[]=L"klhst-ComponentName";	//STRING_T
	const wchar_t c_spInstanceId[]=L"klhst-InstanceId";			//STRING_T

	const wchar_t c_spRtTsksInfo[]=L"klhst-rt-TskInfo";	//PARAMS_T|ARRAY_T	
	const wchar_t c_spRtTskCmpIndex[]=L"klhst-rt-TskCmpIndex";//INT_T
	const wchar_t c_spRtTskInstIndex[]=L"klhst-rt-TskInstIndex";//INT_T	
	const wchar_t c_spRtTskArray[]=L"klhst-rt-TskArray";//PARAMS_T|ARRAY_T
	const wchar_t c_spRtInstInfo[]=L"klhst-rt-InstInfo";	//PARAMS_T
	const wchar_t c_spRtInstInfoArray[]=L"klhst-rt-InstInfoArray";	//PARAMS_T|ARRAY_T
	const wchar_t c_spRtCmpArray[]=L"klhst-rt-CmpArray";//STRING_T|ARRAY_T
	const wchar_t c_spRtInstArray[]=L"klhst-rt-InstArray";//STRING_T|ARRAY_T
	const wchar_t c_spRtPrdNamesArray[]=L"klhst-rt-PrdNamesArray";//STRING_T|ARRAY_T		

    //! TIME_T ����� ���������� ����� � ����
    const wchar_t c_wks_Created[]	= L"KLHST_WKS_CREATED"; 

    //! host has update agent installed, BOOL_T
    const wchar_t c_wks_HasUpdateAgent[] = L"HST_HAS_UPDATE_AGENT";

    /*!
    * \brief ��������� ��� ��������� ���������� � ����������� � ���� 
    *        ������� �����������������.
    *
    */

	typedef struct
	{
		std::wstring	wstrName;
		DomainType		nType;
	}domain_info_t;

	typedef struct
	{
        std::wstring	wstrName;       //host id
		std::wstring	wstrWinHostName;    //windows host name
		ComputerStatus	nType;
	}host_info_t;

	typedef struct
	{
		std::wstring	wstrName;
		std::wstring	wstrVersion;
	}product_info_t;


    /*!
      \brief	������� ���������� �������� ������������

      \param	unsigned mask
      \return	inline int 
    */
    inline int GetPrimaryStatusCondition(unsigned mask)
    {
        if(!mask || mask > 2047)
            return -1;
        size_t i;
        for(i = 0; i < 10 && !(mask & 1); ++i, mask >>= 1);
        return i;
    };

    class KLSTD_NOVTABLE Hosts : public KLSTD::KLBaseQI
    {
    public:

    /*!
      \brief ���������� ������ Windows ������� � ����
       
        \param domains [out] ������ ������� � ����.
    */
        virtual void GetDomains (std::vector<domain_info_t>& domains)  = 0;


    /*!
      \brief ���������� ������ ���� ������� ������� � ������.

        ���������� ���������� �� ����������� ������. ������ �����
        ���������� ������ ������ ������� ������� � ������, ���� ����
        ������� ������� ������ ���������.

        \param domain       [in]  ��� ������.
        \param hosts        [out] ������ ������� �������, ������������������ � ������.
       
    */
        virtual void GetDomainHosts(
                            const std::wstring&         domain,
                            std::vector<host_info_t>&   hosts)=0;


    /*!
      \brief ���������� ���������� � ����������

        \param wstrHostName [in]  ��� ���������� (�� ��� NetBIOS !!! ).
        \param fields       [in]  ������ �����, ������� ��������� �������� (� �.�. c_spHstAppInfo � c_spHstTskInfo)
        \param info         [out] ���������� � ����������.
		
		\exception STDE_NOTFOUND ��������� ��������� �� ������
       
    */
        virtual void GetHostInfo(						
						const std::wstring& wstrName,
						const wchar_t**		fields,
						int					size,
						KLPAR::Params**     info) = 0;

    /*!
     \brief ��������� ����� ����� � ���� ������.
	 
	   \param domain       [in]  ��� ������.
	   \param type       [in]  ��� ������.
	 \exception STDE_EXIST ����� � ��������� ������ ��� ����������.
    */		
		virtual void AddDomain(
						const std::wstring&	domain,
						DomainType			nType)=0;

    /*!
      \brief ������� ����� �� ���� ������.

        \param domain       [in]  ��� ������.
    */
		virtual void DelDomain(const std::wstring&	domain)=0;

    /*!
      \brief ��������� ����� ��������� � ���� ������.

        \param info         [in] ���������� � ����������.
						�������� ����� ��������� ��������� ��������.
							������������:
                                c_wks_display_name,
                                c_wks_groupId,
							�������������� :
                                c_wks_win_domain,
                                c_wks_dnsName,
                                c_wks_dnsDomain
								c_wks_lastVisible,
								c_wks_lastInfoUpdate,
								c_wks_lastUpdate,
								c_wks_status,
								c_wks_ctype,
								c_wks_ptype,
								c_wks_versionMajor,
								c_wks_versionMinor,
								c_wks_ip,
                                c_wks_keepConnection
							������ �������� ������������.
        \return ������������� ������������ �����
    */
        virtual std::wstring AddHost(KLPAR::Params* pInfo)=0;
		
    /*!
      \brief ������� ��������� �� ���� ������.

        \param name         [in]  ��� ���������� (�� ��� NetBIOS !!! ).
       
    */
        virtual void DelHost(
                    const std::wstring & name )=0;

    /*!
      \brief ��������� ���������� � ��������� � ���� ������.

        \param name         [in]  ��� ���������� (�� ��� NetBIOS !!! ).
        \param info         [in]  ���������� � ����������.
						��������� ����� ��������� ��������� ��������.
								c_wks_name,
								c_wks_dnsName,
								c_wks_win_domain,
								c_wks_dnsDomain
								c_wks_lastVisible,
								c_wks_lastInfoUpdate,
								c_wks_lastUpdate,
								c_wks_status,
								c_wks_ctype,
								c_wks_ptype,
								c_wks_versionMajor,
								c_wks_versionMinor,
								c_wks_ip,
                                c_wks_keepConnection
							������ �������� ������������.
			
			 \except STDE_NOTFOUND ����� �� ������
       
    */
        virtual void UpdateHost(
              const std::wstring & name,
              KLPAR::Params  * info )=0;


    /*!
      \brief ���������� ���������� � ������ ��������� �� ����.

        \param name         [in]  ��� ���������� (�� ��� NetBIOS !!! ).
        \param ppProducts   [out] 
                c_hst_array_hosts   //ARRAY_T|PARAMS_T
                    ������ ������� ������� �������� ���� c_spProductName �
                    c_spProductVersion, ����� ����, ����� ��������������
                    ��������� ���� (��. prss/settingsstorage.h):
                        KLPRSS_PRODVAL_INSTALLTIME
                        KLPRSS_PRODVAL_LASTUPDATETIME
                        KLPRSS_PRODVAL_DISPLAYNAME
                        KLPRSS_PRODVAL_BASEDATE
                        KLPRSS_PRODVAL_BASEINSTALLDATE
                        KLPRSS_PRODVAL_BASERECORDS
                        KLPRSS_PRODVAL_VERSION
    */
        virtual void GetHostProducts(
                const std::wstring&     name,
                KLPAR::Params**         ppProducts)=0;

    /*!
      \brief ���������� ���������� � ���������� ��������� �� ����.

        \param name         [in]  ��� ���������� (�� ��� NetBIOS !!! ).
		\param type         [in]  ��� ���������.
        \param settings     [out] ��������� ���������� �� ��������� ����.
       
    */
        virtual void GetHostSettings(
						const std::wstring & name,
						const std::wstring & type,
						KLPRSS::SettingsStorage  ** settings )=0;


    /*!
      \brief ���������� ���������� � �������, ������������ ��� ������� ����.

        \param name         [in]  ��� ���������� (�� ��� NetBIOS !!! ).
        \param tasks        [out] ������, ������������ ��� ���������� �� ��������� ����.
       
    */
        virtual void GetHostTasks(
				const std::wstring&		name,
				const std::wstring&		product,
				const std::wstring&		version,
				KLPRTS::TasksStorage**	tasks,
				long					lLifetime = 20) = 0;
		
    /*!
      \brief ���������� ���������� ��������� �������
        \param name         [in]  ��� ���������� (�� ��� NetBIOS !!! ).
		\param pFilter      [in]  ������. ����� ��������� ���������:
			1. ��������� ���������� � ���������� �������
				c_spRtTsksInfo	//PARAMS_T
					-��������� ���������� �� ������� ���������, ���� ���������
					 �_spRtPrdNamesArray �����������, ������������ ����������
					 �� ������� ���� ���������
					 �_spRtPrdNamesArray		//STRING_T|ARRAY_T
					-��������� ���������� �� c_spProductVersion
					 KLHST::c_spProductVersion	//STRING_T
					-��������� ���������� �� c_tsk_Type
					 KLHST::c_tsk_Type			//STRING_T
					-��������� ���������� �� c_tsk_State
					 KLHST::c_tsk_State			//INT_T
					-��������� ���������� �� c_tsk_Id
					 KLHST::c_tsk_Id				//INT_T
					-��������� ���������� �� c_tsk_StorageId
					 KLHST::c_tsk_StorageId		// STRING_T
			2. ��������� ���������� � ���������� ����������� �����������
				c_spRtInstInfo	//PARAMS_T
					-��������� ���������� �� ����������� ����������� ���������,
					 ���� ��������� �_spRtPrdNamesArray �����������,
					 ������������ ���������� �� ����������� ���� ���������
					 �_spRtPrdNamesArray		//STRING_T|ARRAY_T
					-��������� ���������� �� c_spProductVersion
					 KLHST::c_spProductVersion	//STRING_T
					-��������� ���������� �� c_spComponentName
					 KLHST::c_spComponentName	//STRING_T
					-��������� ���������� �� c_spInstanceId
					 KLHST::c_spInstanceId		//STRING_T
					-��������� ���������� �� c_inst_Statistics. 
					 KLHST::c_inst_Statistics	//PARAMS_T
					-��������� ���������� �� c_inst_State
					 KLHST::c_inst_State		//INT_T
            3. ��������� ���������� � ���������� �����������
                c_spHstAppInfo
		\param ppTasksInfo  [out] ���������� ��������� �������. �����
			��������� ���������:		
			1. � ���������� �������
				c_spRtTsksInfo	//PARAMS_T
					<ProductName>	//PARAMS_T
						KLHST::c_spProductVersion	//STRING_T
						KLHST::c_spRtTskArray		//PARAMS_T|ARRAY_T 
							KLHST::c_tsk_Type		//STRING_T
							KLHST::c_tsk_State		//INT_T
							KLHST::c_tsk_Id			//INT_T
							KLHST::c_tsk_StorageId	// STRING_T
							KLHST::c_spRtTskCmpIndex	//INT_T
							KLHST::c_spRtTskInstIndex	//INT_T
					KLHST::c_spRtCmpArray			//ARRAY_T|STRING_T
					KLHST::c_spRtInstArray			//ARRAY_T|STRING_T
			2. � ���������� ����������� �����������
				c_spRtInstInfo	//PARAMS_T
					<ProductName>	//PARAMS_T
						KLHST::c_spProductVersion	//STRING_T
						KLHST::c_spRtInstInfoArray	//PARAMS_T|ARRAY_T 
							KLHST::c_spComponentName//STRING_T
							KLHST::c_spInstanceId	//STRING_T
							KLHST::c_inst_Statistics//PARAMS_T
							KLHST::c_inst_State		//INT_T
            3. � ���������� �����������
                c_spHstAppInfo
                <product>
                    <version>
                        c_spHstAppState - ��. ComponentInstanceState
                        c_spHstAppStateTime - ���� � ����� ���������� ���������� �������                            


          \exception    KLSRV::KLSRV_ERR_NO_HOST_ADDRESS - ������� ���������� ����� �����.
          \exception    KLSRV::KLSRV_ERR_HOST_NOT_RESPONDING - ���� �� ��������
    */
		virtual void GetHostRuntimeInfo(
								const std::wstring&	name,
								KLPAR::Params*		pFilter,
								KLPAR::Params**		ppTasksInfo,
                                KLSTD::KLBaseQI*    pConnDesc = NULL) = 0;


    /*!
      \brief ���������� ������ AgentProxy ��� ������� ����.

        \param name         [in]  ��� ����������.
        \param agent        [out] AgentProxy.

          \exception    KLSRV::KLSRV_ERR_NO_HOST_ADDRESS - ������� ���������� ����� �����.
          \exception    KLSRV::KLSRV_ERR_HOST_NOT_RESPONDING - ���� �� ��������
          \exception    KLSRV::KLNAG_ERR_APP_NOT_RUNNING - ���������� (product v. version) �� ��������       
    */
        virtual void GetHostAgentProxy(
						const std::wstring&		name,
						const std::wstring&		product,
						const std::wstring&		version,
						KLPRCP::AgentProxy**	agent,
                        KLSTD::KLBaseQI*        pConnDesc = NULL)=0;

        /*!
          \brief    
			\param  vectSeverities - ������ �� �������� ������� (��. c_NFXXXXDescr)					
					!!! �������������� ������ ��������� ����������� ���������� Hosts !!!
		*/
        virtual void GetHostEventPropertiesProxy(
            const std::wstring&		                    domain,
			const std::wstring&		                    name,
			const std::wstring&		                    product,
			const std::wstring&		                    version,
            const std::vector<std::wstring>&            vect_fields,
	        const std::vector<KLCSP::field_order_t>&    vect_fields_to_order,
	        long                                        lifetime,
	        KLEVP::EventProperties**                    ppEventProperties,
			const std::vector<std::wstring> &			vectSeverities) =0;

        virtual void GetGroups(KLGRP::Groups** ppGroups) =0;
        virtual void GetUpdates(KLUPDSRV::Updates** ppUpdates) =0;
        virtual void GetLicSrv(KLLICSRV::SrvLicences** ppLicSrv) =0;
        virtual void GetPol(KLPOL::Policies** ppPolicies) =0;
        
        virtual void GetComponentTransportName(std::wstring& wstrTransportName)=0;

        /*!
          \brief    ��������� ������������� ���������� � ��������� wstrSSType
                    ���������. ����� ����������, �.�. ����� �� ����������
                    ���������� �� ��� ���, ���� �� ���������� ����� ��
                    ��������� �������: ������������� �� ������ ��
                    ����� ��� ��� �� ��������� ������.

          \param    name - ��� ���������� (�� ��� NetBIOS !!! ).
          \param    wstrSSType - ������������� ��������� (������ ������
                        ��������, ��� ��������� �������� ������������� ��� ����
                        ��������)
          \param    lWaitTimeout - ������������ ����� �������� � �� - �����
                        ������� ����
          \param    bCancelWait - ������ � ����������, �� ������� ���������
                        ������ ���������, �������� true �������� � ����������
                        �������� ���������� � ������������ ����������
                        STDE_CANCELED.

          \exception    KLSTD::STDE_CANCELED - �������� ���� ��������
          \exception    KLSTD::STDE_TIMEOUT - ���� ������� lWaitTimeout
          \exception    KLSRV::KLSRV_ERR_NO_HOST_ADDRESS - ������� ���������� ����� �����.
          \exception    KLSRV::KLSRV_ERR_HOST_NOT_RESPONDING - ���� �� ��������
        */
        virtual void ForceSynchronizationSync(
						const std::wstring&		name,
                        const std::wstring&     wstrSSType,
                        long                    lWaitTimeout,
                        volatile bool*          bCancelWait=NULL) = 0;

        /*!
          \brief    �������� ��������� ���������� �� �������� �����.

          \param    name - ��� �����
          \param    wstrProductName - ��� ����������
          \param    wstrProductName - ������ ����������
          \param    lWaitTimeout - ������������ ����� �������� � �� - �����
                        ������� ����
          \param    bCancelWait - ������ � ���������� �������� true �������� �
                        ���������� �������� � ������������ ����������
                        STDE_CANCELED.

          \exception    KLSRV::KLSRV_ERR_NO_HOST_ADDRESS - ������� ���������� ����� �����.
          \exception    KLSRV::KLSRV_ERR_HOST_NOT_RESPONDING - ���� �� ��������
          \exception    KLSTD::STDE_CANCELED - �������� ���� ��������
          \exception    KLSTD::STDE_TIMEOUT - ���� ������� lWaitTimeout
          \exception    KLNAG::KLNAG_ERR_APP_NOTINSTALLED - ���������� �� �����������
          \exception    KLNAG::KLNAG_ERR_APP_NOT_RUNNABLE - ���������� �� ������������ ������ �����
          \exception    KLNAG::KLNAG_ERR_APP_STOPPED_UNEXPECTEDLY - ���������� ����������� � ���������� �����������

          \return   true, ���� ���������� ���� ��������;
                    false - ���� ���������� ��� ��������
        */
        virtual bool StartProduct(
					const std::wstring&		name,
                    const std::wstring&     wstrProductName,
                    const std::wstring&     wstrProductVersion,
                    long                    lWaitTimeout,
                    volatile bool*          bCancelWait=NULL) = 0;


        /*!
          \brief    ������������� ��������� ���������� �� �������� �����.

          \param    name - ��� �����
          \param    wstrProductName - ��� ����������
          \param    wstrProductName - ������ ����������
          \param    lWaitTimeout - ������������ ����� �������� � �� - �����
                        ������� ����
          \param    bCancelWait - ������ � ���������� �������� true �������� �
                        ���������� �������� � ������������ ����������
                        STDE_CANCELED.

          \exception    KLSRV::KLSRV_ERR_NO_HOST_ADDRESS - ������� ���������� ����� �����.
          \exception    KLSRV::KLSRV_ERR_HOST_NOT_RESPONDING - ���� �� ��������
          \exception    KLSTD::STDE_CANCELED - �������� ���� ��������
          \exception    KLSTD::STDE_TIMEOUT - ���� ������� lWaitTimeout
          \exception    KLNAG::KLNAG_ERR_APP_NOTINSTALLED - ���������� �� �����������
          \exception    KLNAG::KLNAG_ERR_APP_NOT_STOPPABLE - ���������� �� ����������� ������ ���������

          \return   true, ���� ���������� ���� ������� �����������;
                    false - ���� ���������� �� ���� ��������
        */
        virtual bool StopProduct(
					const std::wstring&		name,
                    const std::wstring&     wstrProductName,
                    const std::wstring&     wstrProductVersion,
                    long                    lWaitTimeout,
                    volatile bool*          bCancelWait=NULL) = 0;

		
        /*!
          \brief    

			\param  vectSeverities - ������ �� �������� ������� (��. c_NFXXXXDescr)					
					!!! �������������� ������ ��������� ����������� ���������� Hosts !!!
		*/
        virtual void GetHostEventPropertiesProxy(
            const std::wstring&		                    domain,
			const std::wstring&		                    name,
			const std::wstring&		                    product,
			const std::wstring&		                    version,
	        const KLPAR::Params*                        pParamsIteratorDescr,
            const std::vector<std::wstring>&            vect_fields,
	        const std::vector<KLCSP::field_order_t>&    vect_fields_to_order,
	        long                                        lifetime,
	        KLEVP::EventProperties**                    ppEventProperties,
			const std::vector<std::wstring> &			vectSeverities) =0;


        //OBSOLETE
        inline void GetHostAgentProxy(
                        const std::wstring&		domain,
						const std::wstring&		name,
						const std::wstring&		product,
						const std::wstring&		version,
						KLPRCP::AgentProxy**	agent)
        {
            GetHostAgentProxy(
                            name,
                            product,
                            version,
                            agent,
                            NULL);
        };

		inline void GetHostRuntimeInfo(
                                const std::wstring&	domain,
								const std::wstring&	name,
								KLPAR::Params*		pFilter,
								KLPAR::Params**		ppTasksInfo)
        {
            GetHostRuntimeInfo(name, pFilter, ppTasksInfo);
        }

        inline void ForceSynchronizationSync(
                        const std::wstring&	    domain,
						const std::wstring&		name,
                        const std::wstring&     wstrSSType,
                        long                    lWaitTimeout,
                        volatile bool*          bCancelWait=NULL)
        {
            ForceSynchronizationSync(
                                    name,
                                    wstrSSType,
                                    lWaitTimeout,
                                    bCancelWait);
        }

        inline bool StartProduct(
                    const std::wstring&	    domain,
					const std::wstring&		name,
                    const std::wstring&     wstrProductName,
                    const std::wstring&     wstrProductVersion,
                    long                    lWaitTimeout,
                    volatile bool*          bCancelWait=NULL)
        {
            return StartProduct(
                            name,
                            wstrProductName,
                            wstrProductVersion,
                            lWaitTimeout,
                            bCancelWait);
        };

        inline bool StopProduct(
                    const std::wstring&	    domain,
					const std::wstring&		name,
                    const std::wstring&     wstrProductName,
                    const std::wstring&     wstrProductVersion,
                    long                    lWaitTimeout,
                    volatile bool*          bCancelWait=NULL)
        {
            return StopProduct(
                            name,
                            wstrProductName,
                            wstrProductVersion,
                            lWaitTimeout,
                            bCancelWait);
        }

        inline void AddHosts(KLPAR::Params* pData, KLPAR::Params** ppOutData)
        {
            KLSTD::CAutoPtr<KLGRP::Groups> pGroups;
            if(!QueryInterface(KLSTD_IIDOF(KLGRP::Groups), (void**)&pGroups))
                return;

            std::vector<std::wstring> vecNames;
            long idGroup = -1;
            {
                KLSTD::CAutoPtr<KLPAR::ArrayValue> pArray;
                pData->GetValue(c_hst_array_hosts, (KLPAR::Value**)&pArray);
                if(!pArray || pArray->GetType() != KLPAR::Value::ARRAY_T)
                    return;

                const int nSize = pArray->GetSize();
                vecNames.reserve(nSize);                
            
                for(int i=0; i < nSize; ++i)
                {
                    KLSTD::CAutoPtr<KLPAR::ParamsValue> pEntry;
                    pArray->GetAt(i, (KLPAR::Value**)&pEntry);
                    if(!pEntry || pEntry->GetType() != KLPAR::Value::PARAMS_T)
                        continue;
                    KLSTD::CAutoPtr<KLPAR::Params> pItem=pEntry->GetValue();
                    if(!pItem)
                        continue;                
                    idGroup = KLPAR::GetIntValue(pItem, KLHST::c_wks_groupId);
                    const std::wstring& wstrName =
                           KLPAR::GetStringValue(pItem, KLHST::c_wks_name);
                    vecNames.push_back(wstrName);
                }
                if(idGroup == -1 || vecNames.size() == 0)
                    return;
            };
            KLSTD::CAutoPtr<KLPAR::Params> pInData;
            {
                KLSTD::CAutoPtr<KLPAR::ArrayValue> pArray;
                KLPAR::CreateStringValueArray(vecNames, &pArray);

                KLPAR::param_entry_t pars[]=
                {
                    KLPAR::param_entry_t(KLHST::c_wks_anyname_array, pArray),
                    KLPAR::param_entry_t(KLHST::c_wks_groupId, idGroup)
                };
                KLPAR::CreateParamsBody(pars, KLSTD_COUNTOF(pars), &pInData);
            };

            pGroups->ResolveAndMoveToGroup(pInData, ppOutData);
        }

        inline void GetHostSettings(
                        const std::wstring& domain,
						const std::wstring & name,
						const std::wstring & type,
						KLPRSS::SettingsStorage  ** settings )
        {
            GetHostSettings(name, type, settings);
        };

        inline void UpdateHost(
                            const std::wstring& domain,
                            const std::wstring & name,
                            KLPAR::Params  * info )
        {
            UpdateHost(name, info);
        }

        inline void GetHostInfo(
                        const std::wstring& domain,
						const std::wstring& wstrName,
						const wchar_t**		fields,
						int					size,
						KLPAR::Params**     info)
        {
            GetHostInfo(
                        wstrName,
                        fields,
                        size,
                        info);
        };

        inline void GetHostProducts(
                const std::wstring&     domain,
                const std::wstring&     name,
                KLPAR::Params**         ppProducts)
        {
            GetHostProducts(name, ppProducts);
        };

        inline void GetHostTasks(
                const std::wstring&     domain,
				const std::wstring&		name,
				const std::wstring&		product,
				const std::wstring&		version,
				KLPRTS::TasksStorage**	tasks,
				long					lLifetime = 20)
        {
            GetHostTasks(
                        name,
                        product,
                        version,
                        tasks,
                        lLifetime);
        };
    };

    //!obsolete
    const wchar_t c_spHstTskInfo[] = L"KLHST_TSK_INFO";
    const wchar_t c_spHstTskStgId[] = L"KLHST_TSK_STGID";
    const wchar_t c_spHstTskState[] = L"KLHST_TSK_STATE";

    //! Network scanning type
    typedef enum
    {
        NST_AD = 1,     //! AD
        NST_MSN_FAST,   //! Ms network fast scanning
        NST_MSN_FULL,   //! Ms network full scanning
        NST_DPNS        //! Ip diapasons scanning
    }
    NetScanType;

    class KLSTD_NOVTABLE Hosts2 : public KLHST::Hosts
    {
    public:
        /*!
          \brief    ��������� ������������� ���������� � ��������� wstrSSType
                    ���������. ����� ����������, �.�. ����� �� ����������
                    ���������� �� ��� ���, ���� �� ���������� ����� ��
                    ��������� �������: ������������� �� ������ ��
                    ����� ��� ��� �� ��������� ������.

          \param    name - ��� ���������� (�� ��� NetBIOS !!! ).
          \param    wstrSSType - ������������� ��������� (������ ������
                        ��������, ��� ��������� �������� ������������� ��� ����
                        ��������)

          \exception    KLSTD::STDE_CANCELED - �������� ���� ��������
          \exception    KLSTD::STDE_TIMEOUT - ���� ������� lWaitTimeout
          \exception    KLSRV::KLSRV_ERR_NO_HOST_ADDRESS - ������� ���������� ����� �����.
          \exception    KLSRV::KLSRV_ERR_HOST_NOT_RESPONDING - ���� �� ��������
        */
        virtual void ForceSync(
						const std::wstring&		name,
                        const std::wstring&     wstrSSType,
                        KLADMSRV::AdmServerAdviseSink*      pSink,
                        KLADMSRV::HSINKID&                  hSink) = 0;

        /*!
          \brief    ��������� ����� � ������� �� ����-���.
                    Supported IDs for AdmServerAdviseSink::OnNotify
                        c_nAdviseSinkFailure
                        c_nAdviseSinkOK
                        c_nAdviseSinkCompletion
                    � ������� �� ������ AdmServerAdviseSink::ForceSync
                    �������� ��������� ������������� �� �����������, 
                     �������������� ������ ���������� � �������. 

          \param    vecHosts - ����� ������
          \param    wstrSSType - ������������� ��������� (������ ������
                        ��������, ��� ��������� �������� ������������� ��� ����
                        ��������)
        */
        virtual void AddHostsForSync(
                        const std::vector<std::wstring>&    vecHosts,
                        const std::wstring&                 wstrSSType,
                        KLADMSRV::AdmServerAdviseSink*      pSink,
                        KLADMSRV::HSINKID&                  hSink) = 0;

        /*!
          \brief    ��������� ����� � ������� �� ����-���.
                    Supported IDs for AdmServerAdviseSink::OnNotify
                        c_nAdviseSinkFailure
                        c_nAdviseSinkOK
                        c_nAdviseSinkCompletion
                    � ������� �� ������ AdmServerAdviseSink::ForceSync
                    �������� ��������� ������������� �� �����������, 
                     �������������� ������ ���������� � �������. 

          \param    idGroup - id ������ 
          \param    wstrSSType - ������������� ��������� (������ ������
                        ��������, ��� ��������� �������� ������������� ��� ����
                        ��������)
        */
        virtual void AddGroupHostsForSync(
                        long                    idGroup,
                        const std::wstring&     wstrSSType,
                        KLADMSRV::AdmServerAdviseSink*      pSink,
                        KLADMSRV::HSINKID&                  hSink) = 0;
       
        /*!
          \brief	Restarts specified network scanning type

          \param	type IN network scanning type
        */
        virtual void RestartNetworkScanning(KLHST::NetScanType type) = 0;
    };
}
/*!
	\brief ������� ������ ������ KLHST::Hosts

	\param szwAddress [in] ����� � ������� http://<host_name> [: <port_number>]
	\param ppHosts [out] ��������� �� ����������, � ������ ����� �������
		��������� �� ������ ������ KLHST::Hosts.
	\param pPorts [in] ������ �������������� ������ (����������� 0)
*/
KLCSSRVP_DECL void KLHST_CreateHosts(
						const wchar_t*  szwAddress,
						KLHST::Hosts ** ppHosts,
						const unsigned short* pPorts=NULL,
                        bool            bUseSsl = true);

KLCSSRVP_DECL void KLHST_CreateLocalHosts(KLHST::Hosts ** ppHosts);

#endif // KLHST_HOSTS_H
