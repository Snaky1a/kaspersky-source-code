/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file WNF/WindowsNetInfo.h
 * \author ������ �������
 * \date 2002
 * \brief ��������� ��� ��������� ���������� � Windows - ����.
 *
 */

#ifndef KLWNF_WINDOWSNETINFO_H
#define KLWNF_WINDOWSNETINFO_H

#include <time.h>
#include <string>
#include <list>

#include <std/base/klbase.h>

namespace KLWNF {

	typedef std::list<std::wstring> OBJ_LIST;

    //! ����������� ��������� ���� ����������� � Windows - ����
	// ��� UNIX ������ ������������ ���� CT_SERVER_UNIX � ���� �� ������
	// CT_SERVER_FREEBSD | CT_SERVER_LINUX
    enum ComputerType {
		CT_WORKSTATION = 0x00000001,
		CT_SERVER = 0x00000002,
		CT_SQLSERVER = 0x00000004,
		CT_DOMAIN_CTRL = 0x00000008,
		CT_DOMAIN_BAKCTRL = 0x00000010,
		CT_TIME_SOURCE = 0x00000020,
		CT_AFP = 0x00000040,
		CT_NOVELL = 0x00000080,
		CT_DOMAIN_MEMBER = 0x00000100,
		CT_PRINTQ_SERVER = 0x00000200,
		CT_DIALIN_SERVER = 0x00000400,
		CT_XENIX_SERVER = 0x00000800,
		CT_SERVER_UNIX = CT_XENIX_SERVER,
		CT_NT = 0x00001000,
		CT_WFW = 0x00002000,
		CT_SERVER_FREEBSD = CT_WFW,
		CT_SERVER_MFPN = 0x00004000,
		CT_SERVER_NT = 0x00008000,
		CT_POTENTIAL_BROWSER = 0x00010000,
		CT_BACKUP_BROWSER = 0x00020000,
		CT_MASTER_BROWSER = 0x00040000,
		CT_DOMAIN_MASTER = 0x00080000,
		CT_SERVER_OSF = 0x00100000,
		CT_SERVER_VMS = 0x00200000,
		CT_SERVER_LINUX = CT_SERVER_VMS,
		CT_WINDOWS = 0x00400000,  /* Windows95 and above */
		CT_DFS = 0x00800000,  /* Root of a DFS tree */
		CT_CLUSTER_NT = 0x01000000,  /* NT Cluster */
		CT_DCE = 0x10000000,  /* IBM DSS (Directory and Security Services) or equivalent */
		CT_ALTERNATE_XPORT = 0x20000000,  /* return list for alternate transport */
		CT_LOCAL_LIST_ONLY = 0x40000000,  /* Return local list only */
		CT_DOMAIN_ENUM = 0x80000000,
		CT_ALL = 0xFFFFFFFF  /* handy for NetServerEnum2 */
    };

    //! ����������� ���� �� - �������� ��� �����������
    enum PlatformType {
        P_DOS, 
        P_OS2, 
        P_NT, 
        P_OSF, 
        P_VMS,
		P_NOVELL,
		P_LINUX,
		P_FREEBSD,
		P_WIN_MOBILE,
		P_SYMBIAN_MOBILE
    };

    //! ����������� ���� ���������� �������������
    enum PrivilegeLevel {
        PL_GUEST,
        PL_USER,
        PL_ADMINISTRATOR
    };

    //! ���������� �� ������� AD
    struct ADObjectInfo {
        std::wstring name;						// ��� �������.
        std::wstring guid;						// GUID �������.
		std::wstring accountName;				// sAMAccountName
		std::wstring dNSHostName;				// DNS Host Name
		std::wstring domainDistName;			// ActiveDS DNS distinguished domain name ("DC=avp,DC=ru")
        std::wstring distinguishedName;         // ActiveDS distinguished name
        
		KLSTD::CAutoPtr<KLSTD::KLBase> handle;	// Handle �������
    };

	typedef std::list<ADObjectInfo> AD_OBJ_LIST;

    //! ���������� � ������� ������� � ����.

    struct ComputerInfo {

		ComputerInfo(): 
			ip(0),
			ctype(CT_WORKSTATION),
			ptype(P_NT),
			versionMajor(0),
			versionMinor(0)
		{
		}
		
        std::wstring name;			///< ��� ����������.
        std::wstring domain;		///< ��� ������, � ������� ������ ���������.
        std::wstring dnsDomain;		///< DNS ����� ��� ����������
        std::wstring dnsName;		///< DNS ��� ����������
        ComputerType ctype;			///< ��� ����������
        PlatformType ptype;			///< ��������� ��� �� �� ����������.
        int versionMajor;			///< ������� ����� ������ �� �� ����������
        int versionMinor;			///< ������� ����� ������ �� �� ����������
        int ip;						///< IP ����� ����������
    };

    //! ���������� � ������������ ������
    struct UserInfo {
        std::wstring name;			///< ��� ������������ (login).
        std::wstring domain;		///< ��� ������, � ������� ������ ������������.
        PrivilegeLevel pLevel;		///< ������� ���������� ������������.
        time_t lastLogon;			///< ����� ���������� logon ������������.
        time_t lastLogoff;			///< ����� ���������� logoff ������������.
 
    };

	struct ComputerInfo2000 {
		ComputerInfo2000(const wchar_t* pszName = L""):
			name(pszName?pszName:L"")
		{
		}
		std::wstring name;
		std::wstring fullDnsName;		// DNS ��� � ������� (comp1.avp.ru)
	};
	typedef std::list<ComputerInfo2000> OBJ_LIST2000;

    /*!
    * \brief ��������� ��� ����� ���������� � Windows - ����.
    *
    *  ������ ������ ������������� ������� ���������� � Windows - ����,
    *  � ������� �������� ����������, ������������ ������.  ������� ���������
    *  ������ Windows - ����:
    *
    *  1. Windows - ���� ������� �� ������ ������� � ������� �����.
    *  2. � Windows - ���� ������������ ���� Windows NT (2000, XP) ������� �������,
    *   ���� Windows 95 (98,Me) ����������.
    *  3. ������ ����� �������� � ���� ����� Windows NT (2000, XP) ������� ������� �
    *    ����� ���������������� accounts.
    *  4. ��������� ����������� ������� ����������������� �������������� ������ ���
    *    �����������, �� ������� �������� ������������, �������� � �����.
    *  5. ��������� ����� �� ������� � ����� (� ������������, ���������� �� 
    *    ����������), �� ��� ���� ������� ����������������� ����� ��������� 
    *    �������� ��� ������ ����������, ���� ����������� ������ ����� ��������� 
    *    �������.
    *  6. ��������� ����� ��������� ��������:
    *       �) NetBios ��� (���������� � Windows - ����).
    *       b) DNS ���.
    *       �) DNS �����.
    *       d) ��� ������ ���� ������� ������, � ������� ������ ��������� 
    *           (�� �����������).
    *       e) IP �����.
    *
    *
    *  ��� ����� ���������� ������������ ��������� �������:
    *
    *  1. ����������� ������ (��� ��������� ���������� � Windows NT �����������
    *     � �������������, ������������������ � ������).
    *  2. Browser service (��� ��������� ������ �������������� � ���� ������� �����
    *     � �������, � ����� Windows 95 (98,Me) ����������� � Windows NT �����������,
    *     �� �������� � �����.
    *
    *   ������ ������� ������ ����� ����������� ���������� ����� �� ��������������
    *   �����.  ��� ����� ��������� ��� ������������� ������ ����������.
    *
    *  
    *  
    */


    class WindowsNetInfo : public KLSTD::KLBase {
    public:

    /*!
      \brief ���������� ������ ������� ����� � ����

        \param workgroups [out] ������ ������� ����� � ����.
      
		���������� ���������� �� WinError.h � LMErr.h (��. WNetEnumResource)
    */
        virtual void GetWorkgroups (OBJ_LIST & workgroups)  = 0;

    /*!
      \brief ���������� ������ ������� � ����
       
        \param domains [out] ������ ������� � ����.

		���������� ���������� �� WinError.h � LMErr.h (��. WNetEnumResource)
    */
        virtual void GetDomains (OBJ_LIST & domains)  = 0;


    /*!
      \brief ���������� ������ ���� ������� ������� � ������.

        ���������� ���������� �� ����������� ������. ������ �����
        ���������� ������ ������ ������� ������� � ������, ���� ����
        ������� ������� ������ ���������.

        \param domain       [in]  ��� ������.
        \param workstations [out] ������ ������� �������, ������������������ � ������.
       
		 ���������� ���������� �� WinError.h � LMErr.h (��. NetQueryDisplayInformation)
    */
        virtual void GetDomainWorkstations
            ( const std::wstring & domain,
              OBJ_LIST & workstations ) = 0;

    /*!
      \brief ���������� ������ ���� ������� ������� � ������.

        ���������� ���������� �� ����������� ������. ������ �����
        ���������� ������ ������ ������� ������� � ������, ���� ����
        ������� ������� ������ ���������.

        \param domain       [in]  ��� ������.
        \param workstations [out] ������ ������� �������, ������������������ � ������.
       
		 ���������� ���������� �� WinError.h � LMErr.h (��. NetQueryDisplayInformation)
    */
        virtual void GetDomainWorkstations2
            ( const std::wstring & domain,
              OBJ_LIST2000 & workstations ) = 0;

    /*!
      \brief ���������� ������ ���� ������� ������� � ������.

        ���������� ���������� �� Active Directory. ������ �����
        ���������� ������ ������ ������� ������� � ������, ���� ����
        ������� ������� ������ ���������.

        \param domain       [in]  ��� ������.
        \param workstations [out] ������ ������� �������, ������������������ � ������.
       
		 ���������� ���������� �� WinError.h � LMErr.h (��. NetQueryDisplayInformation)
    */
		virtual void GetADDomainWorkstations(const std::wstring& domain, 
											 OBJ_LIST2000& workstations) = 0;

    /*!
      \brief ���������� ������ ���� ����������� � ������� ������ ��� ������.

        ���������� ���������� �� browser service. ������ �����
        ���������� ������ �����������, �������������� �
        ������ ������ � ���� � ���������� � ������� ������ � ��������
        ������.  ��� ������� ������ ����� ��������� � ������ ������, 
        � ���� ������ ������������ ������ ���� �����������, ��������
        � ����� � �������������� ������ � ����.

        \param workgroup   [in]  ��� ������� ������ ���� ������.  
                                 ���� ������ - ������������ ��� ����������, 
                                 �� �������� �� � ���� ������� ������
                                 � �� � ���� �����.
        \param computers   [out] ������ �����������, �������������� � ������� ������
                                 ���� � ������ � ��������� ������.

		���������� ���������� �� WinError.h � LMErr.h (��. WNetEnumResource)
    */
        virtual void GetWorkgroupComputers
            ( const std::wstring & workgroup,
              OBJ_LIST & computers ) = 0;


    /*!
      \brief ���������� ������ ���� ����������� � ������� ������ ��� ������.

        ���������� ���������� �� browser service. ������ �����
        ���������� ������ �����������, �������������� �
        ������ ������ � ���� � ���������� � ������� ������ � ��������
        ������.  ��� ������� ������ ����� ��������� � ������ ������, 
        � ���� ������ ������������ ������ ���� �����������, ��������
        � ����� � �������������� ������ � ����.

        \param workgroup   [in]  ��� ������� ������ ���� ������.  
                                 ���� ������ - ������������ ��� ����������, 
                                 �� �������� �� � ���� ������� ������
                                 � �� � ���� �����.
        \param computers   [out] ������ �����������, �������������� � ������� ������
                                 ���� � ������ � ��������� ������.

		���������� ���������� �� WinError.h � LMErr.h (��. WNetEnumResource)
    */
        virtual void GetWorkgroupComputers2
            ( const std::wstring & workgroup,
              OBJ_LIST2000 & computers ) = 0;

    /*!
      \brief ���������� ������ �������������, ������������������ � ������.

        ���������� ���������� �� ����������� ������.

        \param domain       [in]  ��� ������.
        \param users        [in, out] ������ �������������, ������������������ � ������.
		\param bIncludeDisabledAccounts [in] ���������� � disabled accounts
       
		 ���������� ���������� �� WinError.h � LMErr.h (��. NetQueryDisplayInformation)
    */
        virtual void GetDomainUsers
            ( const std::wstring & domain,
              OBJ_LIST & users,
			  bool bIncludeDisabledAccounts ) = 0;


    /*!
      \brief ���������� ���������� � ����������, 
            ������������������ � ������ ��� ������� ������.

        ���������� ���������� �� Browser Service (NetServerGetInfo).

        \param workgroup    [in]  ��� ������� ������ ��� ������.
        \param name         [in]  ��� ����������.
        \param info         [out] ���������� � ����������.
       
		 ���������� ���������� �� WinError.h � LMErr.h (��. NetServerGetInfo)
    */
        virtual void GetComputerInfo
            ( const std::wstring & workgroup,
              const std::wstring & name,
              ComputerInfo & info ) = 0;


    /*!
      \brief ���������� ���������� � ������������, 
            ������������������ � ������.

        \param domain       [in]  ��� ������.
        \param name         [in]  ��� ������������.
        \param info         [out] ���������� � ������������.
       
		 ���������� ���������� �� WinError.h � LMErr.h (��. NetUserGetInfo)
    */
        virtual void GetUserInfo
            ( const std::wstring & domain,
              const std::wstring & name,
              UserInfo & info ) = 0;

    /*!
      \brief ���������� ���������� � �������������, ������������
            ������ ������� �������.

        ���������� ���������� ��� ������ ������
        ��������������� ������� ������� (NetWkstaGetInfo, NetWkstaUserEnum).

        \param name             [in]  ��� ����������.
        \param loggedInUsers    [out] ����� �������������, ������������ ������ ���������.
        \param domains          [out] ����� ������� �������������, ������������ ������ ���������. 
       
		 ���������� ���������� �� WinError.h � LMErr.h (��. NetWkstaUserEnum)
    */
        virtual void GetLoggedInUsers
            ( const std::wstring & ComputerName,
              OBJ_LIST & loggedInUsers,
              OBJ_LIST & domains ) = 0;

    /*!
      \brief ���������� ���������� � ������� ���� ������������, 
            ������������������� � ������.

        \param domain       [in]  ��� ������.
        \param name         [in]  ��� ������������.
        \param groups       [out] ������ ���������� �����, � ������� ������ ������������.
       
		 ���������� ���������� �� WinError.h � LMErr.h (��. NetUserGetGroups)
    */
        virtual void GetUserGroups
            ( const std::wstring & domain,
              const std::wstring & name,
              OBJ_LIST & groups ) = 0;

    /*!
      \brief ���������� ������ organizationalUnits �� ActiveDirectory

        \param OUs [out] ������ organizationalUnits �� ActiveDirectory.
      
		���������� ���������� �� WinError.h
    */
        virtual void GetADsOrganizationalUnits (const ADObjectInfo& parentAdObject, 
												AD_OBJ_LIST & OUs,
												bool bIncludeContainers = false)  = 0;

    /*!
      \brief ���������� ������ ����������� � ��������� organizationalUnits �� ActiveDirectory

        \param OUs [out] ������ �����������.
      
		���������� ���������� �� WinError.h
    */
        virtual void GetADsOrganizationalUnitComputers (const ADObjectInfo& parentAdObject, AD_OBJ_LIST & OUComps)  = 0;

	/*!
	  \brief ������������ ��� ������ � ������ NT4

		\param name			[in] distinguished domain name ("DC=avp,DC=ru")
		\return				[out] NT4 domain name
	*/
		virtual std::wstring DistDomainNameToNT4Name(const std::wstring& domain) = 0;
    };
}

/*!
  \brief ������� ������ ������ WindowsNetInfo

    \param wnetinfo      [out] ��������� �� ������ ������ WindowsNetInfo
*/
void KLWNF_CreateWindowsNetInfo(KLWNF::WindowsNetInfo **ppWindowsNetInfo, bool volatile* pbCancelEnumeration = NULL);

/*!
  \brief ������� ������ ������ WindowsNetInfo

	\param name			 [in] ��� ���������� (������������ ��� Win9x)
    \param info			 [out] ���������� � ����������
*/
void KLWNF_GetComputerInfo(const std::wstring& name, KLWNF::ComputerInfo& info);

#endif // KLWNF_WINDOWSNETINFO_H
