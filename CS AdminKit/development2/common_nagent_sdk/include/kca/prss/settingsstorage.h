/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file PRSS/SettingsStorage.h
 * \author ������ ��������
 * \date 2002
 * \brief ������� ��������� ������ Product Settings Storage.
 *
 */

#ifndef KLPRSS_SETTINGSSTORAGE_H
#define KLPRSS_SETTINGSSTORAGE_H


namespace KLPRSS
{

	/*!
		\brief	������������ �����, � ��������, ������ ����� ��������,
				������, ������ (��� �������� �������).
	*/
	const int c_nMaxNameLength=31;


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

};


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


#endif // KLPRSS_SETTINGSSTORAGE_H
