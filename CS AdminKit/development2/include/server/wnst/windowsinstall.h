/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file WNST/WindowsInstall.h
 * \author ������ �������
 * \date 2002
 * \brief ��������� ��� ��������� ����������� ������ �� ���������� � Windows - ����.
 *
 */

#ifndef KLWNST_WINDOWSINSTALL_H
#define KLWNST_WINDOWSINSTALL_H

#include <time.h>
#include <string>
#include <vector>
#include <map>

#include <std/base/klbase.h>

namespace KLWNST {

    //! ��������� ���/������
    struct SecurityCtx {
        std::wstring login;
        std::wstring password;
		SecurityCtx(){};
		SecurityCtx(const std::wstring& lgn, const std::wstring& pwd): login(lgn), password(pwd){};
		bool operator == (const SecurityCtx& ctx) const {return ctx.login == login && ctx.password == password;}
    };

    //! ��������� ���� ������� � ����������� �����
    enum SharePermissions {
        SP_READ    =   0x00000001, ///< ������ ����� ��������� ���������� �����.
        SP_EXECUTE =   0x00000002, ///< ������ ����� ��������� ���������� ��������� �� ����������� �����
        SP_WRITE    = 0x00000004 ///< ������ ����� ������ ���������� �����.
    };

	typedef std::map<std::wstring, long> NetRes2ConnMap;

    /*!
    * \brief ��������� ��� ��������, ���������� � �������������� �������� ��������� �
            �������� �������.
    */    
    class NetResourceConnection : public KLSTD::KLBase
    {
    public:
    /*!
      \brief ������������� ������������ � ������ ��������. ��� ������
        ������� NetResourceConnection ����� ���� ������ ������ ���� ���.
        ����������� ������ ������������. ��� ������������ ������� ������������
        �����������.
        \param wstrResource       [in]  ���� � �������. ��������, "\\machine\" ��� "\\machine\�$"
        \param ctx                [in]  �������, �������� ��������� ��� ���� ������.
    */
        virtual void AddConnection(
            const std::wstring & wstrResource,
            const SecurityCtx & ctx,
            const std::wstring & wstrResourceDomain = L"",
			AVP_dword* pdwSystemErrorCode = NULL) = 0;

        virtual void AddConnectionEx(
			KLWNST::NetRes2ConnMap& mpNetRes2ConnMap,
			KLSTD::CAutoPtr<KLSTD::CriticalSection> pCS,
            const std::wstring & wstrResource,
            const SecurityCtx & ctx,
            const std::wstring & wstrResourceDomain = L"",
			AVP_dword* pdwSystemErrorCode = NULL) = 0;

        virtual void AddConnection2(
            const std::wstring & wstrResource,
            const std::vector<KLWNST::SecurityCtx>& vecSecCtxs,
            const std::wstring & wstrResourceDomain = L"",
			AVP_dword* pdwSystemErrorCode = NULL) = 0;

        virtual void AddConnectionEx2(
			KLWNST::NetRes2ConnMap& mpNetRes2ConnMap,
			KLSTD::CAutoPtr<KLSTD::CriticalSection> pCS,
            const std::wstring & wstrResource,
            const std::vector<KLWNST::SecurityCtx>& vecSecCtxs,
            const std::wstring & wstrResourceDomain = L"",
			AVP_dword* pdwSystemErrorCode = NULL) = 0;
    };
	

    struct security_descriptor;
	//typedef SECURITY_DESCRIPTOR security_descriptor;

    /*!
    * \brief ��������� ��� ��������� ����������� ������ �� ���������� � Windows - ����.
    *
    *   ������ ������������ ��� ������� ��������� �����������.  ��� �����������,
    *   ���������� ��� ����������� Windows NT (2000, XP), �������� ��������
    *   �������� ����������� � ������ ������� �� ��������� ������.
    *
    *   ��� �����������, ���������� ��� ����������� Windows 95, �������� ��������
    *   �������� ����������� ��� ������ login script ��� ������������ ������.
    *
    *   ��������� ����������� �������� ������ ��� ����������� � �������������,
    *   �������� � �����.
    *   
    *   ��� ���� ����� ������ ������� ������ ��������� ��������, ���������� ������
    *   �������� ���������������� �������.  �� ��������� ������������ ����� ��������
    *   ������, ��� ����� ����� �������������� ��� �������� ������� ������ WindowsInstall.
    *
    *   ������ ������� ������ ����� ����������� ���������� ����� �� ��������������
    *   �����.  ��� ����� ��������� ��� ������������� ������ ����������.
    * 
    *   !!! ����� �� �������� ThreadSafe !!! 
	*	!!! ��� ������� ������ ������� ��������� �������� ����� �������� ������� !!!
    */


    class WindowsInstall : public KLSTD::KLBase {
    public:


    /*!
      \brief ������������� ��� ������������ ������ ����������, ������� �����
            �������� � ������ ���������� login ������������.

        ���������� ���������������� �� ����� � ����������� ���������� �������.

        ���� ��� ������������ ������ ��� ��������� login script , �� ��������������
        login script ����� ������� ����� ������� ������������� ����������
        applPath ����������.


        \param domain       [in]  ��� ������.

       \param user         [in]  ��� ������������ ������.
        \param applPath     [in]  ��� ���������� � ����������� ����������.
        \param identity     [in]  ������������� ������. ���� ������ � �����
                                    �������������� ��� ����������, ��� ����� ��������.
        \param ctx          [in] �������, ������������ ��� ������� � ������
    */
        virtual void SetLoginScript (
            const std::wstring & domain,
            const std::wstring & user,
            const std::wstring & applPath,
            const std::wstring & identity,
            const SecurityCtx & ctx = SecurityCtx() ) = 0;


    /*!
      \brief ���������, ���� �� � login script'� ������������ ������ � ������������ identity

        \param domain       [in]  ��� ������.
        \param user         [in]  ��� ������������ ������.
        \param identity     [in]  ������������� ������. 
        \param ctx          [in] �������, ������������ ��� ������� � ������
        \return       true ���� ������ ����������
    */
        virtual bool UserHasLoginScript(
            const std::wstring& sDomainName,
            const std::wstring& sUser,
            const std::wstring & identity,
            const SecurityCtx & ctx = SecurityCtx() ) = 0;

    /*!
      \brief ������� ��� ������������ ������ ������ ����������, ��������������
            ����� ��� ������ ������ SetLoginScript.

        \param domain       [in]  ��� ������.
        \param user         [in]  ��� ������������ ������.
        \param identity     [in]  ������������� ������. 
        \param ctx          [in] �������, ������������ ��� ������� � ������
    */
        virtual void RemoveLoginScript (
            const std::wstring & domain,
            const std::wstring & user,
            const std::wstring & identity,
            const SecurityCtx & ctx = SecurityCtx() ) = 0;


    /*!
      \brief ������� ��� ���� ������������� ������ ������ ����������, ��������������
            ����� ��� ������ ������� SetLoginScript.

        \param domain       [in]  ��� ������.
        \param ctx          [in] �������, ������������ ��� ������� � ������
   */
        virtual void RemoveAllLoginScripts (
            const std::wstring & domain,
            const SecurityCtx & ctx = SecurityCtx() ) = 0;


   /*!
      \brief ������������ �� ��������� ������� ������� ������,
             ������� ���������������� �� ����� � ��������� ����������
             ������� �����������������.

        \param host         [in]  ��� ������� ������� � ������.
        \param name         [in]  ��� ������� �� ��������� ������.
        \param srvPath      [in]  ���� � ������������ ����� ������� �� ������� ������� � ������.
        \param args         [in]  ��������� ��������� ������ �� ��������� ������.
        \param comments     [in]  �������� ������� �� ��������� ������.
        \param ctx          [in]  Account, ��� ������� ����� ����������� ������.
       
    */
        virtual void InstallService(
            const std::wstring & host,
            const std::wstring & name,
            const std::wstring & srvPath,
			const std::wstring & args,
            const std::wstring & comments,
            const SecurityCtx  & ctx ) = 0;

   /*!
      \brief ������� �� ��������� ������� ������� ������,
             ������� ���������������� �� ����� � ��������� ����������
             ������� �����������������.

        \param host         [in]  ��� ������� ������� � ������.
        \param name         [in]  ��� ������� �� ��������� ������.
       
    */
        virtual void RemoveService(
            const std::wstring & host,

           const std::wstring & name ) = 0;

   /*!
      \brief ��������� �� ��������� ������� ������� ������,
             ������� ���������������� �� ����� � ��������� ����������
             ������� �����������������.

        \param host         [in]  ��� ������� ������� � ������.
        \param name         [in]  ��� ������� �� ��������� ������.
       
    */
        virtual void StartService(
            const std::wstring & host,
            const std::wstring & name ) = 0;

   /*!
      \brief ������� �� ������� ����������������� ����������� �����.

		\param host         [in]  ��� ����������
        \param name         [in]  ��� ����������� �����.
        \param path         [in]  ��������� ���� � ����������� �����.
        \param permissions  [in]  ������� ����� ��� ����������� ���� ������� 
                                    � ����������� �����.
        \param username		[in]  ��� ������������ ��� ������ ������� ����������� ������
    */
        virtual void CreateShare(const wchar_t* host,
								 const std::wstring & name,
								 const std::wstring & path,
								 SharePermissions permissions,
								 const std::wstring& username = L"everyone") = 0;

   /*!
      \brief ������� �� ������� ����������������� ����������� �����.

		\param host         [in]  ��� ����������
        \param name         [in]  ��� ����������� �����.
        \param psd          [in]  SECURITY_DESCRIPTOR c ������� ������� � ����������� �����
        \param username		[in]  ��� ������������ ��� ������ ������� ����������� ������
    */
		virtual void CreateShare(const wchar_t* host, 
								 const std::wstring& name, 
								 const std::wstring& path, 
								 security_descriptor* psd) = 0;

   /*!
      \brief ������� �� ������� ����������������� ����������� �����. ����������
             ��������� ���������� �� ��������.

		\param host         [in]  ��� ����������
        \param name         [in]  ��� ����������� �����.
       
    */
        virtual void DeleteShare(const wchar_t* host, 
								 const std::wstring & name ) = 0;

   /*!
      \brief ���������� ��������� ���� ��� ��������� ����������� �����

		\param host         [in]  ��� ����������
        \param name         [in]  ��� ����������� �����.
        \return				��������� ���� ��� ��������� ����������� �����
    */
		virtual std::wstring GetShareLocalPath(const wchar_t* host, 
											   const std::wstring& name) = 0;
	
   /*!
      \brief ������������ �� ��������� ������� ������� ������,
             ������� ���������������� �� ����� � ��������� ����������
             ������� �����������������.

        \param host         [in]  ��� ������� ������� � ������.
        \param name         [in]  ��� ������� �� ��������� ������.
        \param srvPath      [in]  ���� � ������������ ����� ������� �� ������� ������� � ������.
        \param args         [in]  ��������� ��������� ������ �� ��������� ������.
        \param comments     [in]  �������� ������� �� ��������� ������.
        \param ctx          [in]  Account, ��� ������� ����� ����������� ������.
		\param ulServiceType[in]  Specifies the type of service. This parameter must be one of the following service types. 
				SERVICE_FILE_SYSTEM_DRIVER		File system driver service. 
				SERVICE_KERNEL_DRIVER			Driver service. 
				SERVICE_WIN32_OWN_PROCESS		Service that runs in its own process. 
				SERVICE_WIN32_SHARE_PROCESS		Service that shares a process with other services. 

			If you specify either SERVICE_WIN32_OWN_PROCESS or SERVICE_WIN32_SHARE_PROCESS, 
			and the service is running in the context of the LocalSystem account, 
			you can also specify the following type. 
				SERVICE_INTERACTIVE_PROCESS		The service can interact with the desktop. 

		\param ulStartType	[in]  Specifies when to start the service. 
			This parameter must be one of the following start types.
				SERVICE_AUTO_START				A service started automatically by the service control manager 
												during system startup. 
				SERVICE_BOOT_START				A device driver started by the system loader. 
												This value is valid only for driver services. 
				SERVICE_DEMAND_START			A service started by the service control manager 
												when a process calls the StartService function. 
				SERVICE_DISABLED				A service that cannot be started. 
												Attempts to start the service result in the error code ERROR_SERVICE_DISABLED. 
				SERVICE_SYSTEM_START			A device driver started by the IoInitSystem function. 
												This value is valid only for driver services. 

		\param dependencies	[in]    !!! CURRENTLY UNSUPPORTED !!! 
			Pointer to a double null-terminated array of null-separated names of services or load ordering groups 
			that the system must start before this service. Specify NULL or an empty string if the service has 
			no dependencies. Dependency on a group means that this service can run if at least one member of the 
			group is running after an attempt to start all members of the group. 
			You must prefix group names with SC_GROUP_IDENTIFIER so that they can be distinguished from a service 
			name, because services and service groups share the same name space.

		\param ulErrorControl[in]   !!! CURRENTLY UNSUPPORTED !!! 
			Specifies the severity of the error if this service fails to start during startup, 
			and determines the action taken by the startup program if failure occurs. 
			This parameter must be one of the following values.
				SERVICE_ERROR_IGNORE			The startup program logs the error but continues the startup operation. 
				SERVICE_ERROR_NORMAL			The startup program logs the error and puts up a message box 
												pop-up but continues the startup operation. 
				SERVICE_ERROR_SEVERE			The startup program logs the error. 
												If the last-known-good configuration is being started, 
												the startup operation continues. 
												Otherwise, the system is restarted with the last-known-good configuration. 
				SERVICE_ERROR_CRITICAL			The startup program logs the error, if possible. 
												If the last-known-good configuration is being started, 
												the startup operation fails. Otherwise, the system is restarted 
												with the last-known good configuration. 
		\param sLoadOrderGroup[in]	!!! CURRENTLY UNSUPPORTED !!! 
		\param ulTagId		[out]	!!! CURRENTLY UNSUPPORTED !!! 
    */
        virtual void InstallServiceEx(
            const std::wstring & host,
            const std::wstring & name,
            const std::wstring & srvPath,
			const std::wstring & args,
            const std::wstring & comments,
            const SecurityCtx  & ctx,
			const unsigned long ulServiceType, 
			const unsigned long ulStartType,
			std::vector<std::wstring>& dependencies, 
			const unsigned long ulErrorControl, 
			const std::wstring& sLoadOrderGroup, 
			unsigned long* ulTagId = NULL) = 0;

		virtual std::wstring GetLogonScriptFolderPath(const std::wstring& sDomainName) = 0;
   };
}

/*!
  \brief ������� ������ ������ WindowsInstall

    \param ppWindowsInstall      [out] ��������� �� ������ ������ WindowsInstall
    \param ctx                   [in] Login, ��� ������� ����� �������� ������ ������.

*/
KLCSSRV_DECL void KLWNST_CreateWindowsInstall
    (   KLWNST::WindowsInstall **ppWindowsInstall,
        const KLWNST::SecurityCtx & ctx = KLWNST::SecurityCtx() );

KLCSSRV_DECL void KLWNST_CreateNetResourceConnection( KLWNST::NetResourceConnection **ppNetResourceConnection );

KLCSSRV_DECL bool KLWNST_GetLocalPathForNetworkSharePath(
    const std::wstring& wstrNetworkPath,
    std::wstring& wstrLocalPath);

#endif // KLWNST_WINDOWSINSTALL_H

