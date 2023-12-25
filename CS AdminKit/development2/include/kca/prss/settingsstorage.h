/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file PRSS/SettingsStorage.h
 * \author ������ ��������
 * \date 2002
 * \brief ������� ��������� ������ Product Settings Storage.
 *
 */
/*KLCSAK_PUBLIC_HEADER*/

#ifndef KLPRSS_SETTINGSSTORAGE_H
#define KLPRSS_SETTINGSSTORAGE_H

/*KLCSAK_BEGIN_PRIVATE*/
#include <string>

#include "std/err/error.h"
#include "std/base/klstdutils.h"
#include "std/par/params.h"
#include "std/par/value.h"
#include "std/base/klbase.h"
#include "std/io/klio.h"
#include <avp/klids.h>
/*KLCSAK_END_PRIVATE*/

namespace KLPRSS
{
/*KLCSAK_BEGIN_PRIVATE*/
	enum SS_TYPE{
		SS_SETTINGS=0,	// ��������� �������� �����������
		SS_PRODINFO=1,	// ��������� ���������� � ��������� � �����������
		SS_RUNTIME=2	// ��������� ���������� � ���������� �����������
	};
    
	enum SS_OPEN_TYPE{
        SSOT_DIRECT=0,
        SSOT_CURRENT_USER,
        SSOT_LOCAL_MACHINE,
        SSOT_SMART
	};
    
    enum DataChangeType
    {
        DCT_UNKNOWN,
        DCT_CHANGED,
        DCT_ADDED,
        DCT_REMOVED
    };
/*KLCSAK_END_PRIVATE*/

	/*!
		\brief	������������ �����, � ��������, ������ ����� ��������,
				������, ������ (��� �������� �������).
	*/
	const int c_nMaxNameLength=31;

/*KLCSAK_BEGIN_PRIVATE*/
/*!
	\brief	��������� ��� ������ � ����������.
*/

	//! ����� �������� ����������, �� ��������� � ���������� ���������
	#define KLPRSS_PRODUCT_CORE				L".core"
	
	//! ����� �������� ���������� ����������� �� ������
	#define KLPRSS_VERSION_INDEPENDENT		L".independent"

	//! ���������� � �������� � �����
	#define KLPRSS_COMPONENT_PRODUCT		L".product"

/*!
	\brief	����� ��������� ���������. ��� ���������, ����������
			������ � ������������� ����������, ���������� �����
			well-known name, ������� ������������ ��� ��������� InstanceID
			(��. ���� PRCI/ComponentId.h).
*/

	#define KLPRSS_COMPONENT_AGENT			KLCS_COMPONENT_AGENT
	#define KLPRSS_COMPONENT_SERVER			KLCS_COMPONENT_SERVER

/*!
	\brief ��������� ��������� SS_RUNTIME. ������ ���������� ���������� �
	��������������� �����, �� ������� ���������� � ��������� SS_RUNTIME
	��� ��� ��� ��������� ����� ���� ��������. ������ ����� �������
    ������������ �������� KLPRCI_GetRuntimeInfo.

    ������ <product>,<version>, KLPRSS_SECTION_COMMON_SETTINGS
    KLPRSS_VAL_INSTANCES    -   ParamsValue, ���������� ��� ������� �� ����������� ParamsValue,
								(��� ��������� � Instance ID) �� ���������� ������:

    	KLPRSS_VAL_LASTSTART	- ��������� ����� ������� ����������, ��� DATE_TIME_T.
    	KLPRSS_VAL_LASTSTOP     - ��������� ����� ���������� ������ ����������, DATE_TIME_T								    
    	KLPRSS_VAL_INSTANCEPORT - ����� ���������� ����� ��� ���������� � ����������������
    				                ����������� ����������, INT_T.
		KLPRSS_VAL_CONNECTIONNAME - ��� ����������, STRING_T.
        KLPRSS_VAL_CONNTYPE       - ��� ����������, INT_T
		KLPRSS_VAL_PID - ������������� ��������, � �������� ������������
					�������� �������� ���������.
*/

/*!
	\brief ��������� ��������� SS_PRODINFO. ������ ���������� ���������� �
	��������������� �����, �� ������� ���������� � ��������� SS_PRODINFO
	��������, ��� ��� ��� ��������� ����� ���� ��������. ������ ����� �������
	������������ �������:
		KLPRSS_GetComponentInfo,
		KLPRSS_RegisterComponent,
		KLPRSS_UnregisterComponent,
		KLPRSS_GetProductInfo,
		KLPRSS_RegisterProduct,
		KLPRSS_UnregisterProduct


    ������������ ��������� ����������� ������� �������� ��������:    
    KLPRSS_SECTION_COMMON_SETTINGS - �������� ���������� � ��������� �
                    ����������� ��������.  ���������� �������� ����� ����
                    ���� ����������� ������, ���� ������������ �����������.
                    ���� ������ �������� ��������� �����������, �� ������
                    ���������� ��� ������� ���������� ��������. ���
                    ���������� ��������� � ������ ����������. 

        KLPRSS_COMPONENT_PRODUCT (PARAMS_T) - �������� ����������� ���������� �
            ��������.  �������� ��������� ����:    
            KLPRSS_PRODVAL_INSTALLFOLDER - �������� ����� ��������, STRING_T
            KLPRSS_PRODVAL_INSTALLTIME   - ����� ���������� ����������� ��������, DATE_TIME_T.
            KLPRSS_PRODVAL_LASTUPDATETIME- ����� ���������� ���������� ��������, DATE_TIME_T.
            KLPRSS_PRODVAL_DISPLAYNAME   - ������������ ��� �������� ��� ������ ���������, STRING_T.
	        KLPRSS_PRODVAL_BASEFOLDER    - ����� ������������ ���, �������� STRING_T	
            KLPRSS_PRODVAL_BASEDATE      - ���� ������������ ���, DATE_TIME_T.
            KLPRSS_PRODVAL_BASEINSTALLDATE-���� ���������� ������������ ���, DATE_TIME_T.
            KLPRSS_PRODVAL_BASERECORDS   - ���������� ������� � ������������ �����, INT_T
            KLPRSS_PRODVAL_KEYFOLDER     - ����� � �������, STRING_T
            KLPRSS_PRODVAL_LOCID         - ����������� ��������, STRING_T
	        KLPRSS_PRODVAL_VERSION       - ������ ��������, STRING_T
            KLPRSS_PRODVAL_OS_NAME       - �������� ��, STRING_T
            KLPRSS_PRODVAL_OS_VERSION    - ������ ��, STRING_T
            KLPRSS_PRODVAL_OS_RELEASE    - ����� ��, STRING_T
            
            KLPRSS_VAL_MODULETYPE        -
            KLPRSS_VAL_CUSTOMNAME        -
            KLPRSS_VAL_FILENAME          -
            KLPRSS_VAL_FILEPATH          -
            KLPRSS_VAL_ACCEPTED_CMDS     - �������������� ������� (��. CSF_ACCEPT_*)
            KLPRSS_VAL_LOCAL_ONLY        - product cannot be remotely administrated

	
        <component name> -  �������� ��������� ����:    
            KLPRSS_VAL_NAME			- ��� ����������, STRING_T.
            KLPRSS_VAL_VERSION		- ������ ����������, STRING_T.
            KLPRSS_VAL_INSTALLTIME	- ����� ���������� ����������� ����������, ��� DATE_TIME_T.
            KLPRSS_VAL_MODULETYPE   - ��� ������, INT_T
            KLPRSS_VAL_STARTFLAGS   - �����, INT_T
            KLPRSS_VAL_FILENAME		- ��� ����� ����������. STRING_T.
            KLPRSS_VAL_FILEPATH		- ��� ����������, ��� ��������� ���� ����������.  STRING_T.
            KLPRSS_VAL_CUSTOMNAME   -
            KLPRSS_VAL_WELLKNOWNNAME
            KLPRSS_VAL_TASKS		- ������ ���� �����, ������� ����� ��������� ���� 
                                       ��������� ARRAY_T<STRING_T>.
            KLPRSS_VAL_TASKS_COMPLEMENTED
            KLPRSS_VAL_EVENTS		- ������ ����� �������, ������� ����� ������������ ����
                                       ���������.  ARRAY_T<STRING_T>.
            KLPRSS_VAL_KILLTIMEOUT  -
            KLPRSS_VAL_PINGTIMEOUT  -
    */

	/*!
		\brief	����������� ������.
	*/

	#define KLPRSS_SECTION_PRODUCT_INFO		L"ProductInfo"
	#define KLPRSS_SECTION_COMMON_SETTINGS	L"CommonSettings"
/*KLCSAK_END_PRIVATE*/

	//! ���������� � ������������ ������ � Product Info Settings Storage
	#define KLPRSS_SECTION_LIC_INFO			L"LicensingInfo"
	    //! ���������� �� �������� ������������ �����
	    #define KLPRSS_VAL_LIC_KEY_CURRENT		L"CurrentKey"
	    //! ���������� � ��������� ������������ �����
	    #define KLPRSS_VAL_LIC_KEY_NEXT			L"NextKey"

    /*! application components-to-update list section KLPRSS_SECTION_PRODCOMP
        Section contains KLPRSS_VAL_PRODCOMPS variable which is array of params
        Each array item has at least two variables:
            KLPRSS_VAL_NAME     component name
            KLPRSS_VAL_VERSION  component version
    */
    #define KLPRSS_SECTION_PRODCOMP			L"ProductComponents"
        //!array of params that contain components info
        #define KLPRSS_VAL_PRODCOMPS        L"Components"   //ARRAY_T|PARAMS_T

    #define KLPRSS_SECTION_PRODFIXES		L"ProductFixes"
            //KLCONN_VAL_FIXES


	/*!
		\brief	����������� ����������.
	*/

	#define KLPRSS_VAL_NAME					L"Name"
	#define KLPRSS_VAL_VERSION				L"Version"
	#define KLPRSS_VAL_INSTALLTIME			L"InstallTime"
	#define KLPRSS_VAL_MODULETYPE			L"ModuleType"
	#define KLPRSS_VAL_STARTFLAGS			L"StartFlags"
	#define KLPRSS_VAL_FILENAME				L"FileName"
	#define KLPRSS_VAL_FILEPATH				L"FilePath"
	#define KLPRSS_VAL_CUSTOMNAME			L"CustomName"
	#define KLPRSS_VAL_WELLKNOWNNAME		L"WellKnown"
	#define KLPRSS_VAL_TASKS				L"Tasks"
    #define KLPRSS_VAL_TASKS_COMPLEMENTED	L"TasksComplemented"
	#define KLPRSS_VAL_EVENTS				L"Events"
	#define KLPRSS_VAL_KILLTIMEOUT			L"KillTimeout"
    #define KLPRSS_VAL_PINGTIMEOUT			L"PingTimeout"
    #define KLPRSS_VAL_ACCEPTED_CMDS        L"AcceptedCmds"
    #define KLPRSS_VAL_LOCAL_ONLY           L"LocalOnly"


	#define KLPRSS_VAL_INSTANCES			L"Instances"
	#define KLPRSS_VAL_LASTSTART			L"LastStartTime"
	#define KLPRSS_VAL_LASTSTOP				L"LastStopTime"
	#define KLPRSS_VAL_INSTANCEPORT			L"InstancePort"
    #define KLPRSS_VAL_CONNTYPE			    L"ConnectionType"
	#define KLPRSS_VAL_CONNECTIONNAME		L"ConnectionName"    
	#define KLPRSS_VAL_PID					L"Pid"

/*KLCSAK_BEGIN_PRIVATE*/
	enum{
		MTF_EXE=1,
		MTF_DLL=2,
		MTF_NTSERVICE=4,
		MTF_DCOM=8,
        MTF_UNUSED1 = 16, //Don't use
        MTF_CONNECTOR = 32,
		MTF_DCOM_OUTOFPROC=MTF_DCOM|MTF_EXE,
		MTF_DCOM_INPROCESS=MTF_DCOM|MTF_DLL,
		MTF_DCOM_SERVICE=MTF_DCOM|MTF_NTSERVICE,        
        MTF_CONNECTOR_DLL = MTF_CONNECTOR | MTF_DLL
	};

	enum{
		MSF_CANBESTARTED=1,
		MSF_FAULTRESTART=2,
		MSF_MULTIPLE=4,
		MSF_KILLONFAULT=8,
        MSF_EVENTONFAULT=16,
        MSF_CONNECTOR_STH = 32  //Don't use
	};
    
    enum{        
        CSF_ACCEPT_PAUSE_RESUME=1,
        CSF_ACCEPT_STOP=2
    };

    #define KLPRSS_COMPONENET_INFO_VERSION  0x00000003 // version 0.3

	struct ComponentInfo{
		ComponentInfo()
			:	nStructVersion(KLPRSS_COMPONENET_INFO_VERSION)
			,	tmInstallTime(0)
			,	dwModuleType(0)
			,	dwStartFlags(0)
			,	lKillTimeout(0)
            ,   lPingTimeout(0)
		{
			;
		};
		//! Version. Must be KLPRSS_COMPONENET_INFO_VERSION
		const int					nStructVersion;

		//! Comonent's name
		std::wstring				wstrComponentName;
		
		//! Component's version (for example L"4.2.2.5")
		std::wstring				wstrVersion;
		
		//! Installation time
		time_t						tmInstallTime;
		
		//! File name (E.g. L"KAVEx.dll")
		std::wstring				wstrFileName;
		
		//! File directory (E.g. L"C:\\Program Files\\Kaspersky Lab\\Kaspersky Anti-Virus for MS Exchange Server\\")
		std::wstring				wstrFileDirectory;	
		;
		/*!
			Contents depends on dwModuleType value.
			- Service name if component is a service (E.g. L"Kaspersky AV MAPI Service for MS Exchange"),
			- CLSID or ProgID if component is a COM-object
				(E.g. L"{5168048A-2599-4103-AEB6-E0025CF12192}" or L"KAVE2.KaveManager")
			- command line (name with path and optionally with arguments) otherwise
				(e.g. C:\\Program Files\\Kaspersky Lab\\Kaspersky Anti-Virus for MS Exchange Server\\KAVEx.dll").
		*/
		std::wstring				wstrCustomName;

		/*!
			Well-known component's name. If the component doesn't have one,
				wstrWellKnown is an empty string.
		*/
		std::wstring				wstrWellKnown;

		/*!
			Following values can be used:
				MTF_EXE,			- executable which can be run directly
				MTF_DLL,			- dynamic library
				MTF_NTSERVICE,		- windows nt/2000/xp service which must be started through SCM
				MTF_DCOM_OUTOFPROC,	- COM out-of-process server
				MTF_DCOM_INPROCESS,	- COM in-process server
				MTF_DCOM_SERVICE	- COM service server
		*/
		AVP_dword					dwModuleType;

		/*!
			Following flags can be set:
				MSF_CANBESTARTED	- Component can be started by agent
				MSF_FAULTRESTART	- Component should be restarted in case of failure
				MSF_MULTIPLE		- Component can have multiple instances
				MSF_KILLONFAULT		- Component's process should be killed in
										case of failure after timeout lKillTimeout
                MSF_EVENTONFAULT    - Event will be published in case of failure
		*/
		AVP_dword					dwStartFlags;

		//! vector of strings - names of tasks supported by the component
		std::vector<std::wstring>	pwstrTasks;

		//! vector of strings - names of events generated by the component
		std::vector<std::wstring>	pwstrEvents;		

		//! valid only for MTF_EXE, 
		long						lKillTimeout;

        /*! how often component should send pings im milliseconds,
            KLSTD_INFINITE means no pings needed, 0 means default value
        */
        long                        lPingTimeout;

		//! vector of strings - parameters of these tasks are complemented with those in SS
		std::vector<std::wstring>	pwstrSsDataTasks;		

	};

/*!
	\brief ��������� ��������� SS_SETTINGS.
	��������� �������� � ��������� �������� ������������ ����� ���������
	��������:
	
	ProductName1 -> 
		ProductVersion1
		ProductVersion2 ->
			Section1
			Section2
			SectionN
	ProductName2 ->
	
	
	ProductName ������������ ����� ������ � ��������� ��������  (��������,
	Kaspersky Antivirus).	
	ProductVersion ������������ ����� ������ � ������� �������� (��������,
	"4.0").
	Section1,...SectionN ������������ ���������� ������� �������� �������� � 
	����������������� �������.
*/
	
    class SettingsStorage;

    //!obsolete
    void KLCSKCA_DECL _GetNames(
            KLPRSS::SettingsStorage*    pSs,
            const wchar_t*			    name, 
            const wchar_t*              version,
            std::vector<std::wstring>&	vecNames);

    /*!
    * \brief ��������� ������ Product Settings Storage (thread-safe).
    *  
    *  Settings Storage ������������ ��� �������������� ����������, �������������� �
    *  ������ �������� ���������� �������� "����������� �����������".
    *
    *  ������ ������ ���������� ��������������� ��������� �������� ��������� � �����
    *  �������� �������� � ������� � ���������.  ��������� �������� �������������� �
    *  ���� ���������� KLPAR::Params.  �������� ������������� ������ ���������� ���������
    *  � ��������� �� ������ � ������.
    *
    *  ������ ��������� ��������� (� ������� ������ ������ ��������) �� ������ � ������ 
    *  ������ �������������.  �������������, ��� ������ ������ ������ ���������
    *  ���������� ������������� ������ �� ��������� ��������.  ������ �������� ������
    *  �� ������ �� �������������.
    */

   
    class KLSTD_NOVTABLE SettingsStorage: public KLSTD::KLBaseQI
    {
    public:

    /*!
	\brief ������ ������ �� ��������� ��������.

	������ ����� ������ ��������� �������� �� ��������� ��������.  

	��������� ������������ � ���� ��������� �� ������ ������ KLPAR::Params, 
	������� ��������� � heap. ����� ������ ����� ������ ������ �������� �� 
	�������� ������������� ������� KLPAR::Params.

	\param name    [in] ��� �������� ��� ������ ������ (����� ������ �� ������
		��������� c_nMaxNameLength).
	\param version [in] ������ �������� ��� ������ ������ (����� ������ ��
		������ ��������� c_nMaxNameLength).
	\param section [in] ������ �������� �������� ��� ������ ������ (�����
		������ �� ������ ��������� c_nMaxNameLength).

	\exception KLPRSS::NOT_EXIST ���� �� ������� name, version ��� section.

    */

        virtual void Read(
            const wchar_t* name, 
            const wchar_t* version,
            const wchar_t* section,
			KLPAR::Params** ppParams) = 0;
        
    /*!
		\brief ��������� �������� �������� � ��������� ��������.
		������ ����� ��������� �������� �������� �������� � ��������� ��������.  ����
		�������� �������� � ����� ������ ����������, � ���� �����������
		��������.  ���� ��������� �������� � ����� ������ �� ����������, 
		������������ ���������� NOT_EXIST.

		\param name     [in] ��� �������� ��� ������ ������ (����� ������ ��
			������ ��������� c_nMaxNameLength).
		\param version  [in] ������ �������� ��� ������ ������ (����� ������ ��
			������ ��������� c_nMaxNameLength).
		\param section  [in] ������ �������� �������� ��� ������ ������ (�����
			������ �� ������ ��������� c_nMaxNameLength).
		\param settings [in] ����� ��������� ��������. ����� �������� ������
			����� �������� �������� � ������ ������.

		\exception KLPRSS::NOT_EXIST ���� �� ������� name, version ��� section.
		\exception STDE_NOTPERM �������������, ���� ��������� ������� � ������
			������-������.

    */

        virtual void Update(
            const wchar_t* name, 
            const wchar_t* version,
            const wchar_t* section,
            KLPAR::Params * settings ) = 0;


    /*!
	\brief ��������� ����� ��������� � ��������� ��������.

	������ ����� ��������� ����� ��������� �������� � ��������� ��������.  ����
	�������� �������� � ����� ������ ����������, ������������ 
	���������� ALREADY_EXIST.

	\param name     [in] ��� �������� ��� ���������� ������ (����� ������ ��
		������ ��������� c_nMaxNameLength).
	\param version  [in] ������ �������� ��� ���������� ������ (����� ������ ��
		������ ��������� c_nMaxNameLength).
	\param section  [in] ������ �������� �������� ��� ���������� ������ (�����
		������ �� ������ ��������� c_nMaxNameLength).
	\param settings [in] ����� ��������� ��������.

	\exception KLPRSS::NOT_EXIST ���� �� ������� name, version ��� section.
	\exception STDE_NOTPERM �������������, ���� ��������� ������� � ������
		������-������.

    */

        virtual void Add(
            const wchar_t* name, 
            const wchar_t* version,
            const wchar_t* section,
            KLPAR::Params * settings ) = 0;


    /*!
	\brief �������� ������������ ��������� �������� � 
		 ��������� ��������� � ��������� ��������, ���� ��� �� ����������.


	\param name     [in] ��� �������� ��� ������ �������� (����� ������ ��
		������ ��������� c_nMaxNameLength).
	\param version  [in] ������ �������� ���  ������ �������� (����� ������ ��
		������ ��������� c_nMaxNameLength).
	\param section  [in] ������ �������� �������� ��� ������ �������� (�����
		������ �� ������ ��������� c_nMaxNameLength).
	\param settings [in] ����� ��������� ��������.

	\exception KLPRSS::NOT_EXIST ���� �� ������� name, version ��� section.
	\exception STDE_NOTPERM �������������, ���� ��������� ������� � ������
		������-������ (����� ������ �� ������ ��������� c_nMaxNameLength).
    */

        virtual void Replace(
            const wchar_t* name, 
            const wchar_t* version,
            const wchar_t* section,
            KLPAR::Params * settings ) = 0;



    /*!
	\brief ������� ������ �������� �������� � ��������� ��������.

	������ ����� ������� ������ �������� �������� � ����������� ��� �����
	�������� ��������, ���������� � ��������� settings.  ���� ������� � �����
	������ �� ����������, ������������ ���������� NOT_EXIST.

	\param name     [in] ��� �������� ��� �������� ������ (����� ������ ��
		������ ��������� c_nMaxNameLength).
	\param version  [in] ������ �������� ��� �������� ������ (����� ������ ��
		������ ��������� c_nMaxNameLength).
	\param section  [in] ������ �������� �������� ��� �������� ������ (�����
		������ �� ������ ��������� c_nMaxNameLength).
	\param settings [in] ����� ��������� �������� � ��������� ������

	\exception KLPRSS::NOT_EXIST ���� �� ������� name, version ��� section.
	\exception STDE_NOTPERM �������������, ���� ��������� ������� � ������
		������-������.
    */

        virtual void Clear(
            const wchar_t* name, 
            const wchar_t* version,
            const wchar_t* section,
            KLPAR::Params * settings ) = 0;

    /*!
	\brief ������� ��������� �������� � ��������� ��������.

	������ ����� ������� ��������� �������� � �������, ����������� � 
	��������� settings. ����� name, version, section �� ������ ���� �������
	c_nMaxNameLength � ������ ������ �������, � ����� �� ������ ���������
	������� \/:*?\"<>.

	�������� � ���������� �������� ��� �������� ������ ���� EMPTY_T.

	\param name     [in] ��� �������� ��� �������� ������ (����� ������ ��
		������ ��������� c_nMaxNameLength).
	\param version  [in] ������ �������� ��� �������� ������ (����� ������ ��
		������ ��������� c_nMaxNameLength).
	\param section  [in] ������ �������� �������� ��� �������� ������ (�����
		������ �� ������ ��������� c_nMaxNameLength).
	\param settings [in] ����� �������� �������� ��� ��������.

	\exception KLPRSS::NOT_EXIST ���� �� ������� name, version ��� section.
	\exception STDE_NOTPERM �������������, ���� ��������� ������� � ������ ������-������.
    */

        virtual void Delete(
            const wchar_t* name, 
            const wchar_t* version,
            const wchar_t* section,
            KLPAR::Params * settings ) = 0;

    /*!
	\brief ������� ������ �������� �������� � ��������� ��������. 
		���� ������ �������� � ����� ������ ��� ����������, ������������ 
		���������� ALREADY_EXIST.
        ����� name, version, section �� ������ ���� ������� c_nMaxNameLength � 
        �� ������ ��������� ������� \/:*?\"<>.

		������ �������� ������.

		//.....................
		#include <prss/errors.h> //����� ���������� ����������� KLPRSS_MAYEXIST
		
		//.....................

		//������������ ������� ������� �������� MY_PRODUCT_NAME
		KLPRSS_MAYEXIST(pStorage->CreateSection(
										MY_PRODUCT_NAME,
										L"",
										L""));

		//������������ ������� ������� ������ �������� MY_PRODUCT_VERSION
		KLPRSS_MAYEXIST(pStorage->CreateSection(
										MY_PRODUCT_NAME,
										MY_PRODUCT_VERSION,
										L""));

		//������������ ������� ������ MY_COMPONENT_NAME
		KLPRSS_MAYEXIST(pStorage->CreateSection(
										MY_PRODUCT_NAME,
										MY_PRODUCT_VERSION,
										MY_COMPONENT_NAME));		
		

	\param name     [in] ��� �������� ��� �������� ������� �������� (�����
		������ �� ������ ��������� c_nMaxNameLength).
	\param version  [in] ������ �������� ��� �������� ������� �������� (�����
		������ �� ������ ��������� c_nMaxNameLength). ���� ������ ������, ��
		����� ������ ������ �������� �������� name.
	\param section  [in] ������ �������� �������� ��� �������� �������
		�������� (����� ������ �� ������ ��������� c_nMaxNameLength). ����
		������ ������, �� ����� ������ ������ ������ �������� version.

	\exception KLPRSS::NOT_EXIST ���� �� ������� name ��� version.
	\exception KLPRSS::ALREADY_EXIST ���� ��������� ������ ��� ����������.
	\exception STDE_NOTPERM �������������, ���� ��������� ������� � ������ ������-������.
    */

        virtual void CreateSection(
            const wchar_t* name, 
            const wchar_t* version,
            const wchar_t* section ) = 0;

    /*!
	\brief ������� ������ �������� �������� � ��������� ��������. 
		���� ������� �������� � ����� ������ �� ����������, ������������ 
		���������� NOT_EXIST.

	\param name     [in] ��� �������� ��� �������� ������� �������� (�����
		������ �� ������ ��������� c_nMaxNameLength).
	\param version  [in] ������ �������� ��� �������� ������� �������� (�����
		������ �� ������ ��������� c_nMaxNameLength).
	\param section  [in] ������ �������� �������� ��� �������� (����� ������ ��
		������ ��������� c_nMaxNameLength).

	\exception KLPRSS::NOT_EXIST ���� �� ������� name ��� version.
	\exception STDE_NOTPERM �������������, ���� ��������� ������� � ������
		������-������.
    */

        virtual void DeleteSection(
            const wchar_t* name, 
            const wchar_t* version,
            const wchar_t* section ) = 0;

    /*!
      \brief ������������� timeout �� �������� ��� ���������� ��������.

      � ������, ���� ������� ������� �� ����� �������� ������ � ��������� ������
      ������ �������������� timeout, ����� ������� � ��������� ���������� ����������
      STDE_TIMEOUT. �������� ����-���� �� ��������� KLSTD_INFINITE. 

      \param timeout [in]  �������� ����-����, ��.

    */

        virtual void SetTimeout( long timeout )  = 0;



	/*!
	\brief	���������� ����� ���������
	\param name     [in]	��� ��������. ���� ������ ������, �� � ���������
		names ����� ��������� ������ ��� ���������.
	\param version  [in]	������ ��������. ���� ������ ������, �� � ���������
		names ����� ��������� ������ ������ �������� � ������ name.
	\param	names [out] ���� ������ name � version �� ������, �� ������ ���
		������.

	\exception KLPRSS::NOT_EXIST ���� �� ������� name ��� version.
	*/
		virtual void GetNames(
            const wchar_t*			name, 
            const wchar_t*			version,
            KLSTD::AKWSTRARR&       names) = 0;


	/*!
	\brief	���������� �������� ��������. ��� ����������� �������������.
	*/
		virtual void AttrRead(
            const wchar_t*	name, 
            const wchar_t*	version,
            const wchar_t*	section,
			const wchar_t*	attr,
			KLPAR::Value**  ppValue) const =0;


    /*!
      \brief	��������� ����� ��������� ��� �������� ������ ���������� 
                � �������� ��������, ��. KLPRSS_CreateSettingsStorage.

    */
        virtual void CreateSettingsStorage(
					const wchar_t*              location,
					AVP_dword                   dwCreationFlags,
					AVP_dword                   dwAccessFlags,
					KLPRSS::SettingsStorage**   ppStorage) = 0;

        virtual void Read2(
            const wchar_t*  name, 
            const wchar_t*  version,
            const wchar_t*  section,
            KLPAR::Params*  pExtra,
			KLPAR::Params** ppParams) = 0;

        //!obsolete
        void Read(
            const std::wstring & name, 
            const std::wstring & version,
            const std::wstring & section,
			KLPAR::Params** ppParams)
        {
            this->Read(name.c_str(), version.c_str(), section.c_str(), ppParams);
        };
        
        void Update(
            const std::wstring & name, 
            const std::wstring & version,
            const std::wstring & section,
            KLPAR::Params * settings )
        {
            this->Update(name.c_str(), version.c_str(), section.c_str(), settings);
        };

        void Add(
            const std::wstring & name, 
            const std::wstring & version,
            const std::wstring & section,
            KLPAR::Params * settings )
        {
            this->Add(name.c_str(), version.c_str(), section.c_str(), settings);
        };

        void Replace(
            const std::wstring & name, 
            const std::wstring & version,
            const std::wstring & section,
            KLPAR::Params * settings )
        {
            this->Replace(name.c_str(), version.c_str(), section.c_str(), settings);
        };

        void Clear(
            const std::wstring & name, 
            const std::wstring & version,
            const std::wstring & section,
            KLPAR::Params * settings )
        {
            this->Clear(name.c_str(), version.c_str(), section.c_str(), settings);
        };

        void Delete(
            const std::wstring & name, 
            const std::wstring & version,
            const std::wstring & section,
            KLPAR::Params * settings )
        {
            this->Delete(name.c_str(), version.c_str(), section.c_str(), settings);
        };

        void CreateSection(
            const std::wstring & name, 
            const std::wstring & version,
            const std::wstring & section )
        {
            this->CreateSection(name.c_str(), version.c_str(), section.c_str());
        };

        void DeleteSection(
            const std::wstring & name, 
            const std::wstring & version,
            const std::wstring & section )
        {
            this->DeleteSection(name.c_str(), version.c_str(), section.c_str());
        };

        void GetNames(
            const std::wstring&			name, 
            const std::wstring&			version,
            std::vector<std::wstring>&	vecNames)
        {
            _GetNames(this, name.c_str(), version.c_str(), vecNames);
        };

        void AttrRead(
            const std::wstring&		name, 
            const std::wstring&		version,
            const std::wstring&		section,
            const std::wstring&		attr,
            KLPAR::Value**			ppValue) const
        {
            this->AttrRead(
                name.c_str(), 
                version.c_str(), 
                section.c_str(),
                attr.c_str(),
                ppValue);
        };


        void CreateSettingsStorage(
            const std::wstring&         location,
            AVP_dword                   dwCreationFlags,
            AVP_dword                   dwAccessFlags,
            KLPRSS::SettingsStorage**   ppStorage)
        {
            this->CreateSettingsStorage(
                location.c_str(), 
                dwCreationFlags, 
                dwAccessFlags, 
                ppStorage);
        };

        void Read2(
            const std::wstring& name, 
            const std::wstring& version,
            const std::wstring& section,
            KLPAR::Params*      pExtra,
            KLPAR::Params**     ppParams)
        {
            this->Read2(
                    name.c_str(), 
                    version.c_str(), 
                    section.c_str(), 
                    pExtra, 
                    ppParams);
        };

    };

    struct ss_server_t
    {
        std::wstring product, version, id;
    };

    enum ss_formatid_t
    {
        SSF_ID_DEFAULT = -1,
        SSF_ID_SOAPXML = 0,
        SSF_ID_BINPAR = 1,
        SSF_ID_SEMIPACKED = 2
    };

    struct ss_format_t
    {
        ss_format_t(ss_formatid_t id = SSF_ID_DEFAULT)
            :   nSize(sizeof(ss_format_t))
            ,   nVersion(1)
            ,   id(id)
        {;};

        int             nSize;
        int             nVersion;
        ss_formatid_t   id;
    };
    /*KLCSAK_END_PRIVATE*/
};

/*KLCSAK_BEGIN_PRIVATE*/
/*!
    \brief ����� ��� �������� ������� ������ SettingsStorage.

        ��������� ��������� �������� �� ������, ����������� ��������
        � ��������� location.  ������ ������ location ������������
        ���������� ����������� ��������� ��������. ����� ��������
        ��������� �������� ������� � heap ����� ������ ������ 
        SettingsStorage � ���������� ��������� �� ����.

    \param location [in] ������������ ��������� ��������.
	\param dwCreationFlags [in] ����� ���� ������� ��������� ������:
		KLSTD::AF_READ (����� ������), KLSTD::AF_WRITE (����� ������).
	\param dwAccessFlags [in] ���� �� ��������: KLSTD::CF_OPEN_EXISTING,
		KLSTD::CF_CREATE_NEW, KLSTD::CF_OPEN_ALWAYS
	\param ppStorage [out] ��������� �� ����������, � ������� ����� �������
		��������� �� ��������� ������.
*/


KLCSKCA_DECL void KLPRSS_CreateSettingsStorage(
					const std::wstring&         location,
					AVP_dword                   dwCreationFlags,
					AVP_dword                   dwAccessFlags,
					KLPRSS::SettingsStorage**   ppStorage,
                    KLPRSS::ss_server_t*        pServerId=NULL);

KLCSKCA_DECL void KLPRSS_CreateSettingsStorageDirect(
					const std::wstring& location,
					AVP_dword dwCreationFlags,
					AVP_dword dwAccessFlags,
					KLPRSS::SettingsStorage** ppStorage,
                    const std::wstring& wstrSSUser=L"");


KLCSKCA_DECL void KLPRSS_CreateSettingsStorage2(
					const std::wstring&         location,
					AVP_dword                   dwCreationFlags,
					AVP_dword                   dwAccessFlags,
					KLPRSS::SettingsStorage**   ppStorage,
                    KLPRSS::ss_server_t*        pServerId=NULL,
                    const KLPRSS::ss_format_t*  pFormat = NULL);

KLCSKCA_DECL void KLPRSS_CreateSettingsStorageDirect2(
					const std::wstring&         location,
					AVP_dword                   dwCreationFlags,
					AVP_dword                   dwAccessFlags,
					KLPRSS::SettingsStorage**   ppStorage,
                    const std::wstring&         wstrSSUser=L"",
                    const KLPRSS::ss_format_t*  pFormat = NULL);

/*!
  \brief	��������� ��������� �������� ��� ������. ��������� ������
		������������.

  \param		const std::wstring& location
  \param		KLPRSS::SettingsStorage** ppStorage
*/

KLSTD_INLINEONLY void KLPRSS_OpenSettingsStorageR(
									const std::wstring& location,
									KLPRSS::SettingsStorage** ppStorage)
{
	KLPRSS_CreateSettingsStorage(
							location,
							KLSTD::CF_OPEN_EXISTING,
							KLSTD::AF_READ,
							ppStorage);
};

/*!
  \brief	��������� ��������� �������� ��� ������/������. ��������� ������
			������������.

  \param		const std::wstring& location
  \param		KLPRSS::SettingsStorage** ppStorage
*/

KLSTD_INLINEONLY void KLPRSS_OpenSettingsStorageRW(
								const std::wstring& location,
								KLPRSS::SettingsStorage** ppStorage)
{
	KLPRSS_CreateSettingsStorage(
										location,
										KLSTD::CF_OPEN_ALWAYS,
										KLSTD::AF_READ|KLSTD::AF_WRITE,
										ppStorage);
};

/*!
  \brief	��������� ��������� �������� ��� ������/������.
			���� ��������� �� ����������, �� ����� �������.

  \param		const std::wstring& location
  \param		KLPRSS::SettingsStorage** ppStorage
*/

KLSTD_INLINEONLY void KLPRSS_CreateNewSettingsStorage(
					const std::wstring& location,
					KLPRSS::SettingsStorage** ppStorage)
{
	KLPRSS_CreateSettingsStorage(
										location,
										KLSTD::CF_OPEN_ALWAYS,
										KLSTD::AF_READ|KLSTD::AF_WRITE,
										ppStorage);
};

/*!
  \brief	Registers the component by adding registration record to the main
			settings storage.

  \param	wstrProductName [IN] Name of the product
  \param	wstrProductVersion [IN] Version of the product (e.g. 1.0)
  \param	ci [IN] structure ComponenteInfo with registration information.
  \param	lTimeout [IN] Time to wait for access to the main storage

  \exception	KLPRSS::ERR_UNDEFINED path to the main settings storage cannot be obtained
*/
KLCSKCA_DECL void KLPRSS_RegisterComponent(
					const std::wstring&				wstrProductName,
					const std::wstring&				wstrProductVersion,
					const KLPRSS::ComponentInfo&	ci,
					long							lTimeout=KLSTD_INFINITE);

/*!
	\brief	Unregisters the component by deleting registration record to the
			main settings storage.

	\param	wstrProductName [IN] - Name of the product
	\param	wstrProductVersion [IN] - Version of the product (e.g. 1.0)
	\param	ci [IN] - structure ComponenteInfo with registration information.
	\param	wstrComponentName [IN]  - name of the component to unregister
	\param	lTimeout [IN] Time to wait for access to the main storage

	\exception	KLPRSS::ERR_UNDEFINED path to the main settings storage cannot
		be obtained
	\exception	KLPRSS::ERR_NOTREGISTERED component's registration record was
		not found
*/
KLCSKCA_DECL void KLPRSS_UnregisterComponent(
					const std::wstring&		wstrProductName,
					const std::wstring&		wstrProductVersion,
					const std::wstring&		wstrComponentName,
					long					lTimeout=KLSTD_INFINITE);


/*!
	\brief	Acquires information about the component.

	\param	wstrProductName [IN] - Name of the product
	\param	wstrProductVersion [IN] - Version of the product (e.g. 1.0)
	\param	wstrComponentName [IN]  - name of the component to get information for
	\param	ci [OUT] - structure ComponenteInfo.
	\param	lTimeout [IN] Time to wait for access to the main storage

	\exception	KLPRSS::ERR_UNDEFINED path to the main settings storage cannot
		be obtained
	\exception	KLPRSS::ERR_NOTREGISTERED component's registration record was
		not found
	\exception	KLPRSS::ERR_BADREGISTRATION component was not registered
		properly
				
*/

KLCSKCA_DECL void KLPRSS_GetComponentInfo(
					const std::wstring&		wstrProductName,
					const std::wstring&		wstrProductVersion,
					const std::wstring&		wstrComponentName,
					KLPRSS::ComponentInfo&	ci,
					long					lTimeout=KLSTD_INFINITE);
/*KLCSAK_END_PRIVATE*/

/*!
	\brief ���������� � ��������.
*/
    
    //! �������� ����� �������� STRING_T
    #define KLPRSS_PRODVAL_INSTALLFOLDER    L"Folder"

    //! KLPRSS_PRODVAL_INSTALLTIME
    #define KLPRSS_PRODVAL_INSTALLTIME      KLPRSS_VAL_INSTALLTIME

    //! KLPRSS_PRODVAL_LASTUPDATETIME
    #define KLPRSS_PRODVAL_LASTUPDATETIME   L"LastUpdateTime"

    //! KLPRSS_PRODVAL_DISPLAYNAME
    #define KLPRSS_PRODVAL_DISPLAYNAME      L"DisplayName"

	//! ����� ������������ ��� �������� STRING_T
	#define KLPRSS_PRODVAL_BASEFOLDER		L"BaseFolder"

    //! ���� ������������ ���, DATE_TIME_T.
    #define KLPRSS_PRODVAL_BASEDATE         L"BaseDate"
	
    //! ���� ���������� ������������ ���, DATE_TIME_T.
    #define KLPRSS_PRODVAL_BASEINSTALLDATE  L"BaseInstallDate"

    //! ���������� ������� � ������������ �����, INT_T
    #define KLPRSS_PRODVAL_BASERECORDS      L"BaseRecords"

	//! ����� � ������� STRING_T
	#define KLPRSS_PRODVAL_KEYFOLDER		L"KeyFolder"
	
	//! ����������� ��������	STRING_T
	#define KLPRSS_PRODVAL_LOCID			L"LocID"

	//! Product full version in w.x.y.z format, STRING_T
	#define KLPRSS_PRODVAL_VERSION			L"ProdVersion"

	//! Connector full version in w.x.y.z format, STRING_T
	#define KLPRSS_CONNECTOR_VERSION        L"ConnectorVersion"

	//! Connector flags, INT_T
	#define KLPRSS_CONNECTOR_FLAGS          L"ConnectorFlags"

	//! Connector component name, STRING_T
	#define KLPRSS_CONNECTOR_COMPONENT_NAME L"ConnectorComponentName"

	//! Connector instance id, STRING_T
	#define KLPRSS_CONNECTOR_INSTANCE_ID    L"ConnectorInstanceId"

	//! �������� ��				STRING_T
	#define KLPRSS_PRODVAL_OS_NAME			L"OsName"

	//! ������ ��				STRING_T
	#define KLPRSS_PRODVAL_OS_VERSION		L"OsVersion"

	//! ����� ��				STRING_T
	#define KLPRSS_PRODVAL_OS_RELEASE		L"OsRelease"

/*KLCSAK_BEGIN_PRIVATE*/
/*!
	\brief	Acquires information about the product.

	\param	wstrProductName [IN] - Name of the product
	\param	wstrProductVersion [IN] - Version of the product (e.g. 1.0)
	\param	ppData [OUT] - pointer to variable which will receive a pointer to
			the container Params.
	\param	lTimeout [IN] Time to wait for access to the main storage

	\exception	KLPRSS::ERR_UNDEFINED path to the main settings storage cannot
					be obtained
	\exception	KLPRSS::ERR_NOTREGISTERED product's registration record was not
					found
	\exception	KLPRSS::ERR_BADREGISTRATION product was not registered properly
				
*/

KLCSKCA_DECL void KLPRSS_GetProductInfo(
					const std::wstring&		wstrProductName,
					const std::wstring&		wstrProductVersion,
					KLPAR::Params**			ppRegData,
					long					lTimeout=KLSTD_INFINITE);


KLCSKCA_DECL void KLPRSS_GetProductInfo2(
                    KLPRSS::SettingsStorage*    pStorage,
					const std::wstring&		    wstrProductName,
					const std::wstring&		    wstrProductVersion,
					KLPAR::Params**			    ppRegData);

/*!
  \brief	Registers product.

  \param	wstrProductName [IN] - Name of the product to register
  \param	wstrProductVersion [IN] - Version of the product (e.g. 1.0)
  \param	ppData [OUT] - pointer to the container Params with registration
				data.
  \param	lTimeout [IN] Time to wait for access to the main storage

  \exception	KLPRSS::ERR_UNDEFINED path to the main settings storage cannot
					be obtained
*/

KLCSKCA_DECL void KLPRSS_RegisterProduct(
					const std::wstring&		wstrProductName,
					const std::wstring&		wstrProductVersion,
					KLPAR::Params*			pRegData,
					long					lTimeout=KLSTD_INFINITE);

/*!
  \brief	Unregisters product.

  \param	wstrProductName [IN] - Name of the product to unregister
  \param	wstrProductVersion [IN] - Version of the product (e.g. 1.0)
  \param	lTimeout [IN] Time to wait for access to the main storage

  \exception	KLPRSS::ERR_NOTREGISTERED component's registration record was
					not found
  \exception	KLPRSS::ERR_UNDEFINED path to the main settings storage cannot
					be obtained
*/

KLCSKCA_DECL void KLPRSS_UnregisterProduct(
					const std::wstring&		wstrProductName,
					const std::wstring&		wstrProductVersion,
					long					lTimeout=KLSTD_INFINITE);


namespace KLPRSS
{
	struct product_version_t
	{
		std::wstring product;
		std::wstring version;
		/////////////////////////////

		product_version_t(){;};

		product_version_t(const std::wstring& p, const std::wstring& v)
			:	product(p)
			,	version(v)
		{;}

		product_version_t(const product_version_t& x)
			:	product(x.product)
			,	version(x.version)
		{;}

		
        int Compare(const product_version_t& x) const
        {
            int c=product.compare(x.product);
            if(c != 0)return c;
            return version.compare(x.version);
        };

		bool operator == (const product_version_t& x) const
		{
            return Compare(x) == 0;
		};

		bool operator < (const product_version_t& x) const
		{
            return Compare(x) < 0;
		};
	};
};




/*!
  \brief	���������� ����� � ������ ������������� ���������.

  \param	vecProducts [out] ����� � ������ ������������� ���������
  \param	lTimeout [in] ����� �������� ������� � ���������, ��

  \exception	KLPRSS::ERR_UNDEFINED ���� � ��������� �� ��������
*/
KLCSKCA_DECL void KLPRSS_GetInstalledProducts(
			std::vector<KLPRSS::product_version_t>&	vecProducts,
			long									lTimeout=KLSTD_INFINITE);

/*!
  \brief	���������� ����� ������������� ����������� ������� ��������

  \param	wstrProductName [in] ��� ��������
  \param	wstrProductVersion [in] ������ ��������
  \param	vecComponents [out] ����� � ������ ������������� �����������
  \param	lTimeout [in] ����� �������� ������� � ���������, ��

  \exception	KLPRSS::ERR_UNDEFINED ���� � ��������� �� ��������
*/
KLCSKCA_DECL void KLPRSS_GetInstalledComponents(
					const std::wstring&			wstrProductName,
					const std::wstring&			wstrProductVersion,
					std::vector<std::wstring>&	vecComponents,
					long						lTimeout=KLSTD_INFINITE);

/*!
	\brief	Function acquires location of specified settings storage.

	\param	nType [IN]	��� ��������� (��. ������������ SS_TYPE)
	\return	location  of main settings storage
	\exception	KLPRSS::ERR_UNDEFINED path to the main settings storage cannot
		be obtained
*/

KLCSKCA_DECL std::wstring KLPRSS_GetSettingsStorageLocation(
                                KLPRSS::SS_TYPE      nType=KLPRSS::SS_SETTINGS,
                                KLPRSS::SS_OPEN_TYPE nOpenType=KLPRSS::SSOT_SMART);


KLCSKCA_DECL std::wstring KLPRSS_GetPolicyLocation(
                                const std::wstring&    wstrProduct,
                                const std::wstring&    wstrVersion);


KLCSKCA_DECL std::wstring KLPRSS_GetPrivateSettingsLocation(
                                const std::wstring&    wstrProduct,
                                const std::wstring&    wstrVersion);


//! ��� ������� �������� � ������������ �� �� �������.
#define KLPRSS_PRODUCT_NAME				KLPRSS_PRODUCT_CORE
#define KLPRSS_VERSION_CURRENT			KLPRSS_VERSION_INDEPENDENT

/*KLCSAK_END_PRIVATE*/

#endif // KLPRSS_SETTINGSSTORAGE_H
