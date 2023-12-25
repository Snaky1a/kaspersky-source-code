/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file PKG/Packages.h
 * \author ������ ��������
 * \date 16:22 19.11.2002
 * \brief ��������� ��� ��������, ����������� � �������� ��������������� �������.
 *
 */

#ifndef _KLPKG_H__872AC7A0_D727_4032_946A_963AA70B1EEC__
#define _KLPKG_H__872AC7A0_D727_4032_946A_963AA70B1EEC__

#include <kca/prss/settingsstorage.h>
#include <srvp/pkg/pkgcfg.h>
#include <srvp/admsrv/admsrv.h>

// �������� ������ �������� ������������ �������� � SS
// <Product name> <Ver> <KLPLG_SSSECTION_NAME_INSTALLER>
#define KLPLG_SSSECTION_NAME_INSTALLER		L"InstallerSettings"		

// ��������� ������������
#define INSTALLER_PARAM_SERVER_NAME			L"ServerName"
#define INSTALLER_PARAM_SERVER_PORT			L"ServerPort"
#define INSTALLER_PARAM_SERVER_SSL_PORT		L"ServerSSLPort"
#define INSTALLER_PARAM_USE_SSL				L"UseSSLConnection"
#define INSTALLER_PARAM_NO_REBOOT			L"DelayReboot"
#define INSTALLER_PARAM_PRESUMED_GROUP_NAME	L"PresumedGroupName"
#define INSTALLER_PARAM_USE_PROXY			L"UseProxy"					// BOOL_T
#define INSTALLER_PARAM_PROXY_ADDRESS		L"ProxyServerAddress"		// STRING_T
#define INSTALLER_PARAM_PROXY_USER			L"ProxyServerUser"			// STRING_T
#define INSTALLER_PARAM_PROXY_PASSWORD		L"ProxyServerPassword"		// STRING_T
#define INSTALLER_PARAM_ALLOW_NETBIOS_NAME_SERVICE	KLNAG_ALLOW_NETBIOS_NAME_SERVICE	// STRING_T
#define INSTALLER_PARAM_OPEN_PORT_IN_WFW	KLNAG_SP_OPEN_PORT_IN_WFW	// STRING_T

#define INSTALLER_PARAM_SRV_CERTIFICATE		L"ServerCert"	// BINARY_T

#define PACKAGES_FOLDER_NAME				L"Packages"
#define PACKAGES_UNINSTALL_FOLDER_NAME		L"Uninstall"

namespace KLPKG {
	const wchar_t FAKE_PRODUCT_NAME_FOR_EXECUTABLE_PACKAGE[] = L"executable_package";
	const wchar_t FAKE_PRODUCT_VERSION_FOR_EXECUTABLE_PACKAGE[] = L"1.0.0.0";

    /*!
        \brief ������� c_RecordNewPackageDone ����������� ��� ���������� ������������ �������� ������, � �.�. ��� ������
		    c_evpPkgAsyncId, STRING_T - ������������� �������, ���������-���������� ����
			c_evpPkgAsyncError, PARAMS_T - ��������������� ������, ���� ��� �������� ��� �������� ������ (����� �������������).
			c_evpPkgId, INT_T - ������������� ���������� ������ (����� ������������� - ��� ������).
    */
	const wchar_t c_RecordNewPackageDone []=L"KLPKG_RecordNewPackageDone ";
		const wchar_t c_evpPkgAsyncId[]=L"KLPKG_evpPkgAsyncId"; // STRING_T
		const wchar_t c_evpPkgAsyncError[]=L"KLPKG_evpPkgAsyncError"; // PARAMS_T
		const wchar_t c_evpPkgId[]=L"KLPPT_evpPkgId"; // INT_T
	
	typedef struct 
	{
		long nPackageId;
		std::wstring wstrName;
		std::wstring wstrProductName;
		std::wstring wstrProductVersion;
		std::wstring wstrPackagePath;
		AVP_longlong llSize;
		time_t tCreationTime;
		time_t tModificationTime;
		std::wstring wstrSettingsStorageDescr;
		std::wstring wstrProductDisplName;
		std::wstring wstrProductDisplVersion;
	} package_info_t;

	enum IncompatibleAppInfoType{
		IAI_PLAIN_TEXT
	};

	const wchar_t c_IncompatibleAppInfoType[]=L"KLPKG_IncompatibleAppInfoType"; // INT_T
	const wchar_t c_IncompatibleAppInfoPlainText[]=L"KLPKG_IncompatibleAppInfoPlainText"; // STRING_T

    class KLSTD_NOVTABLE Packages : public KLSTD::KLBaseQI {
    public:
		/*!
		  \brief ���������� ������ ��������� ������� ��� ��������� �����������
       
			\param packages [out] ������ ��������� ������� 
		*/
		virtual void GetPackages( std::vector<package_info_t>& packages ) = 0;



		/*!
		  \brief �������� ������ �������� ������
       
			\param wstrSettingsStorageDescr [in] ���������� ���
						��������� SettingsStorage

			\param ppSettings [out] ��������� - ��������� SettingsStorage.
		*/
		virtual void GetPackageSettings( const std::wstring& wstrSettingsStorageDescr,
				KLPRSS::SettingsStorage** ppSettings ) = 0;



		/*!
		  \brief ��������������� �����
       
			\param nPackageId [in]         id ������ 
			\param wstrNewPackageName [in] ����� ��� 
		*/
		virtual void RenamePackage(
			long nPackageId,
			const std::wstring& wstrNewPackageName ) = 0;
		


		/*!
		  \brief ������ ���� � ������� �����, � ������� ����� ����������� ����������� 
					��� �������� ������ ������. � ����� ������ ���� ����� �������� �� ���������
					������ � ������������ (����� � ������).
       
			\param wstrProductName [in] - ��� �������� � ������������

			\param wstrProductVersion [in] - ������ �������� � ������������

			\param wstrFolder [out] - ���� � ������� �����
		*/
		virtual void GetIntranetFolderForNewPackage(
			const std::wstring& wstrProductName,
			const std::wstring& wstrProductVersion,
			std::wstring& wstrFolder ) = 0;



		/*!
		  \brief ������� ����� � ����������� �� ��������� �� ��������� ������������,
					������������� � �����, ���� � ������� ������� ��� ������
					������ GetIntranetFolderForNewPackage(...) .
       
			\param wstrFolder [in] - ����, �� �������� �������� ����������� (������� ��� ������ 
					GetIntranetFolderForNewPackage(...)  )

			\param wstrProductName [in] - ��� �������� � ������������

			\param wstrProductVersion [in] - ������ �������� � ������������

			\param packageInfoNew [out] - ������ � ������ �� �������, ��������� � 
					����������� ������ ���� �������.

		*/
		virtual void RecordNewPackage(
            const std::wstring& wstrNewPackageName,
			const std::wstring& wstrFolder,
			const std::wstring& wstrProductName,
			const std::wstring& wstrProductVersion,
			const std::wstring& wstrProductDisplName,
			const std::wstring& wstrProductDisplVersion,
			package_info_t& packageInfoNew ) = 0;


		/*!
		  \brief ������� �����
       
			\param wstrPackageName [in] - ��� ������, ����������� ��������
		*/
		virtual void RemovePackage( long nPackageId ) = 0;

		/*!
			\brief ���������� ���� � ������ � ����� ������ �������
				
				  \param long nPackageId [in] - ��-� ������
		*/
		virtual std::wstring GetIntranetFolderForPackage(long nPackageId) = 0;
	};	
	
    class KLSTD_NOVTABLE Packages2 : public Packages {
    public:
		typedef struct 
		{
			long lTaskId;
			std::wstring wstrTaskName;
			long lGroupId;
			std::wstring wstrGroupName;
		} task_info_t;

		/*!
		  \brief ������� �����
       
			\param nPackageId [in] - ������������� ������, ����������� ��������
			\param vecDependTasks [out] - ������ ��������� �����

				\return - true � ������ ������
		*/
		virtual bool RemovePackage2(
			long nPackageId, 
			std::vector<task_info_t>& vecDependTasks) = 0;

		/*!
		  \brief ���������� ����� ������� ��� login-script ����������
       
			\param nPackageId [in]         id ������ 
			\param wstrTaskId [in]         id ������ (���� �� �����, ��������� ����� GUID). 
		*/
		virtual std::wstring GetLoginScript( 
			long nPackageId,
			const std::wstring& wstrTaskId) = 0;

		/*!
		  \brief ������ ����� � ��� ��������� � ������������� ������������ �� ���������� ��������� �����������
       
			\param nPackageId [in]			id ������ (0 - ������ ��� ����� �������)
			\param bRebootImmediately[bool] ������������� ����������
			\param bAskForReboot[bool]		���������� ������������
			\param nAskForRebootPeriodInMin[int] ������ ������ ��������� � ������������� ������������ (� ���.)
			\param nForceRebootTimeInMin[int]	����� ������������ ������������ ��� ������������� ����� "���������� ������������"
			\param wstrAskRebootMsgText [in]	����� ��������� � ������������� ������������. 
		*/
		virtual void SetRebootOptions( 
			long nPackageId,
			bool bRebootImmediately,
			bool bAskForReboot,
			int nAskForRebootPeriodInMin,
			int nForceRebootTimeInMin,
			const std::wstring& wstrAskRebootMsgText) = 0;

		/*!
		  \brief ���������� ����� � ��� ��������� � ������������� ������������ �� ���������� ��������� �����������
       
			\param nPackageId [in]			id ������ (0 - ������ ��� ����� �������)
			\param bRebootImmediately[bool] ������������� ����������
			\param bAskForReboot[bool]		���������� ������������
			\param nAskForRebootPeriodInMin[int] ������ ������ ��������� � ������������� ������������ (� ���.)
			\param nForceRebootTimeInMin[int]	����� ������������ ������������ ��� ������������� ����� "���������� ������������"
			\param wstrAskRebootMsgText [in]	����� ��������� � ������������� ������������. 
		*/
		virtual void GetRebootOptions( 
			long nPackageId,
			bool& bRebootImmediately,
			bool& bAskForReboot,
			int& nAskForRebootPeriodInMin,
			int& nForceRebootTimeInMin,
			std::wstring& wstrAskRebootMsgText) = 0;
	};

    class KLSTD_NOVTABLE Packages3 : public Packages2 {
    public:
		/*!
		  \brief ������� ����� � ����������� �� ��������� �� ��������� ������������, 
					����������� ����� FT.
       
			\param wstrFileId [in] - ������������� ����� � FT

			\param wstrProductName [in] - ��� �������� � ������������

			\param wstrProductVersion [in] - ������ �������� � ������������

			\param packageInfoNew [out] - ������ � ������ �� �������, ��������� � 
					����������� ������ ���� �������.

		*/
		virtual void RecordNewPackage2(
            const std::wstring& wstrNewPackageName,
			const std::wstring& wstrFileId,
			const std::wstring& wstrProductName,
			const std::wstring& wstrProductVersion,
			const std::wstring& wstrProductDisplName,
			const std::wstring& wstrProductDisplVersion,
			package_info_t& packageInfoNew ) = 0;

			/*!
		  \brief �������� �������� ����� ����. ����� �������� ������.
       
			\param nPackageId [in]			-	id ������ 
			\param wszFileRelativePath [in]	-	������������� ���� � �����; NULL ��� �����, ���������� � .kpd
			\param ppData [out] ���������	-	�������� ����� ����� ��������.
		*/
		virtual void ReadPkgCfgFile(
			long nPackageId,
			wchar_t* wszFileRelativePath,
			KLSTD::MemoryChunk** ppChunk) = 0;

		/*!
		  \brief �������� �������� ����� ����. ����� �������� ������.
       
			\param nPackageId [in]			-	id ������ 
			\param wszFileRelativePath [in]	-	������������� ���� � �����; NULL ��� �����, ���������� � .kpd
			\param pData [in] ���������		-	�������� ����� ����� ��������.
		*/
		virtual void WritePkgCfgFile(
			long nPackageId,
			wchar_t* wszFileRelativePath,
			KLSTD::MemoryChunk* pChunk) = 0;

		/*!
		  \brief �������� ������ �������� �������� ������ 
       
			\param nPackageId [in]			-	id ������ 
			\param ppPackageConfigurator [out] ��������� - ��������� PackageConfigurator.
		*/
		virtual void GetPackageConfigurator(
			long nPackageId,
			KLPKG::PackageConfigurator** ppPackageConfigurator) = 0;

		/*!
		  \brief �������� ���������� � ������������ ����� � ������ 
       
			\param nPackageId [in]			-	id ������ 
			\param wstrKeyFileName [out] - ��� ����� �����
			\param ppMemoryChunk [out] - ���� �����
		*/
		virtual void GetLicenseKey(
			long nPackageId,
			std::wstring& wstrKeyFileName,
			KLSTD::MemoryChunk** ppMemoryChunk) = 0;

		/*!
		  \brief �������� ������������ ���� � �����
       
			\param nPackageId [in]			-	id ������ 
			\param wstrKeyFileName [in] - ��� ����� �����
			\param ppMemoryChunk [in] - ���� �����
		*/
		virtual void SetLicenseKey(
			long nPackageId,
			const std::wstring& wstrKeyFileName,
			KLSTD::MemoryChunk* pMemoryChunk,
			bool bRemoveExisting) = 0;

		/*!
		  \brief �������� KPD-����
       
			\param nPackageId [in]	  -	id ������ 
			\param ppMemoryChunk [in] - ���� �����
		*/
		virtual void ReadKpdFile(
			long nPackageId,
			KLSTD::MemoryChunk** ppChunk) = 0;

		/*!
		  \brief ��������� ������ � KPD-�����
       
			\param nPackageId [in]	  -	id ������ 
			\param wstrSection [in] - ��� ������
			\param wstrKey [in] - ��� ���������
			\param wstrDefault [in] - �������� ��������� �� ���������
			\param wstrValue [out] - �������� ���������
		*/
		virtual void GetKpdProfileString(
			long nPackageId,
			const std::wstring& wstrSection,
			const std::wstring& wstrKey,
			const std::wstring& wstrDefault,
			std::wstring& wstrValue) = 0;

		/*!
		  \brief �������� ������ � KPD-����
       
			\param nPackageId [in]	  -	id ������ 
			\param wstrSection [in] - ��� ������
			\param wstrKey [in] - ��� ���������
			\param wstrValue [in] - �������� ���������
		*/
		virtual void WriteKpdProfileString(
			long nPackageId,
			const std::wstring& wstrSection,
			const std::wstring& wstrKey,
			const std::wstring& wstrValue) = 0;
	};
	
    class KLSTD_NOVTABLE Packages4 : public Packages3 {
    public:
		/*!
		  \brief ������ ����� � ��� ��������� � ������������� ������������ �� ���������� ��������� �����������
       
			\param nPackageId [in]			id ������ (0 - ������ ��� ����� �������)
			\param bRebootImmediately[in] ������������� ����������
			\param bAskForReboot[in]		���������� ������������
			\param nAskForRebootPeriodInMin[in] ������ ������ ��������� � ������������� ������������ (� ���.)
			\param nForceRebootTimeInMin[in]	����� ������������ ������������ ��� ������������� ����� "���������� ������������"
			\param wstrAskRebootMsgText [in]	����� ��������� � ������������� ������������. 
			\param bForceAppsClosed [in]	����������� �������� ���������� (������������� ���������� �������������)
			\param parExtraParams [in] �������������� ���������
		*/
		virtual void SetRebootOptionsEx( 
			long nPackageId,
			bool bRebootImmediately,
			bool bAskForReboot,
			int nAskForRebootPeriodInMin,
			int nForceRebootTimeInMin,
			const std::wstring& wstrAskRebootMsgText,
			bool bForceAppsClosed,
			KLPAR::ParamsPtr parExtraParams) = 0;

		/*!
		  \brief ���������� ����� � ��� ��������� � ������������� ������������ �� ���������� ��������� �����������
       
			\param nPackageId [in]			id ������ (0 - ������ ��� ����� �������)
			\param bRebootImmediately[out] ������������� ����������
			\param bAskForReboot[out]		���������� ������������
			\param nAskForRebootPeriodInMin[out] ������ ������ ��������� � ������������� ������������ (� ���.)
			\param nForceRebootTimeInMin[out]	����� ������������ ������������ ��� ������������� ����� "���������� ������������"
			\param wstrAskRebootMsgText [out]	����� ��������� � ������������� ������������. 
			\param bForceAppsClosed [out]	����������� �������� ���������� (������������� ���������� �������������)
			\param parExtraParams [out] �������������� ���������
		*/
		virtual void GetRebootOptionsEx( 
			long nPackageId,
			bool& bRebootImmediately,
			bool& bAskForReboot,
			int& nAskForRebootPeriodInMin,
			int& nForceRebootTimeInMin,
			std::wstring& wstrAskRebootMsgText,
			bool& bForceAppsClosed,
			KLPAR::ParamsPtr& parExtraParams) = 0;
	};
	
    class KLSTD_NOVTABLE Packages5 : public Packages4 {
    public:
		/*
		  \brief ������� ����� � ����������� �� ��������� �� ��������� ������������, 
					����������� ����� FT.
       
			\param wstrFileId [in] - ������������� ����� � FT

			\param wstrProductName [in] - ��� �������� � ������������

			\param wstrProductVersion [in] - ������ �������� � ������������

			\param packageInfoNew [out] - ������ � ������ �� �������, ��������� � 
					����������� ������ ���� �������.
		*/
		virtual void RecordNewPackageAsync(
            const std::wstring& wstrNewPackageName,
			const std::wstring& wstrFileId,
			const std::wstring& wstrProductName,
			const std::wstring& wstrProductVersion,
			const std::wstring& wstrProductDisplName,
			const std::wstring& wstrProductDisplVersion,
			const std::wstring& wstrRequestId,
			KLADMSRV::AdmServerAdviseSink*  pSink,
            KLADMSRV::HSINKID&              hSink) = 0;

		/*
		  \brief ���������� ���������� � ������.
       
			\param nPackageId [in]			id ������ (0 - ������ ��� ����� �������)

			\param packageInfoNew [out] - ������ � ������ �� �������.
		*/
		virtual void GetPackageInfo(
			long nPackageId,
			package_info_t& packageInfoNew) = 0;
	};

    class KLSTD_NOVTABLE Packages6 : public Packages5 {
    public:
		/*
		  \brief ���������� ���������� � ������������� �����������.
       
			\param nPackageId [in]

			\param ppData [out] - ������ �� ������� ������������� ����������;
									��� ������ � c_IncompatibleAppInfoType (IncompatibleAppInfoType);
									������ � c_IncompatibleAppInfoPlainText

			\param bCanRemoveByInstaller [out] - �������������� �� ����� �������� ������������� ����������

			\return true, ���� ������ ������������� ���������� �������������, false - � ��������� ������
		*/
		virtual bool GetIncompatibleAppsInfo(
			long nPackageId,
			KLPAR::Params** ppData,
			bool& bCanRemoveByInstaller,
			bool& bRemoveByInstaller) = 0;
		
		/*
		  \brief ������ ��������� �������� ������������� ����������.
       
			\param nPackageId [in]			id ������

			\param bRemoveIncompatibleApps [in]	������� �� ������������� ����������

			\return true, ���� ��������� ������� ���������, false - ���� ��������� �� ��������������
		*/
		virtual bool SetRemoveIncompatibleApps(
			long nPackageId,
			bool bRemoveIncompatibleApps) = 0;
	};
}

KLCSSRVP_DECL void KLPKG_ParseSettingsStorageDescr(
	const std::wstring& wstrSettingsStorageDescr, 
	std::wstring& wstrSettingsStorageRelPath,
	long& nPackageId);

#endif // _KLPKG_H__872AC7A0_D727_4032_946A_963AA70B1EEC__
