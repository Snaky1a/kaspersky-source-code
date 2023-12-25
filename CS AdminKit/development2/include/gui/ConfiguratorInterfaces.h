#ifndef __CONFIGURATOR_INTERFACES_H__
#define __CONFIGURATOR_INTERFACES_H__

#include <std/base/klbase.h>

#ifdef CLASSES_EXPORT
#define CALL_SPEC __declspec(dllexport)
#else
#define CALL_SPEC __declspec(dllimport)
#endif

namespace KLPlugin
{
	// �������� ��������� - ����������� ����-�������� �������� � �� ��������� �������������
	const wchar_t RWM_KLAKCON_PPN_PAGE_MODIFIED[] = L"RWM_KLAKCON_PPN_PAGE_MODIFIED";
	const wchar_t RWM_KLAKCON_PPN_PAGE_UNMODIFIED[] = L"RWM_KLAKCON_PPN_PAGE_UNMODIFIED";

	// �������� ��������� - ����������� �������� ������� � ������������ �������� ����������� (��� ������� WKS6)
	// wParam = WCHAR_T* - ��������� ������������� �����������
	const wchar_t RWM_KLAKCON_PPN_ACTIVATE_SUBPAGE[] = L"RWM_KLAKCON_PPN_ACTIVATE_SUBPAGE";

	// �������� ��������� - ����������� �������� ������� � ������������ � ����� "������ ��������"
	// wParam == 1 - ����� ReadOnly
	// lParam = LPARAM* pResult �� ������ ��������� �������� 1 - ���� ��������� ���������� � 0 - � ��������� ������ 
	const wchar_t RWM_KLAKCON_PPN_SET_READONLY[] = L"RWM_KLAKCON_PPN_SET_READONLY";
	
	// ����� ����������� ��������������� ������� �������� (������� IEnumInterfaces::QueryInterface())
	const wchar_t KAV_INTERFACE_PROPERTY_SHEET[] = L"IPropertySheet";
	const wchar_t KAV_INTERFACE_POLICY_SETTINGS[] = L"POLICY_SETTINGS";
	const wchar_t KAV_INTERFACE_LOCAL_SETTINGS[] = L"LOCAL_SETTINGS";
	const wchar_t KAV_INTERFACE_TASK_PARAMS[] = L"TASK_PARAMS";
	
	// ���� ����� ����� �������� ���������� �����. 
	// ������������� ������ ����� �� ��������� ������. ��� ���������� �������� �������� �����
	// QueryInterface � ppInterface == NULL : QueryInterface(KAV_INTERFACE_AGENT_PROXY, NULL);
	const wchar_t KAV_INTERFACE_AGENT_PROXY[] = L"AGENT_PROXY";

	const wchar_t KAV_INTERFACE_DATA_PROTECTION[] = L"DATA_PROTECTION";
	const wchar_t KAV_INTERFACE_LICENSING[] = L"LICENSING";
	const wchar_t KAV_INTERFACE_HOSTS[] = L"HOSTS";							// Added in NodesHost v5.0 MP2
	const wchar_t KAV_INTERFACE_TASKS_STORAGE[] = L"HOST_TASKS";			// Added in NodesHost v5.0 MP3
	
	// ���� ����� ����� �������� ���������� �����. 
	// ������������� ������ ����� �� ��������� ������. ��� ���������� �������� �������� �����
	// QueryInterface � ppInterface == NULL : QueryInterface(KAV_INTERFACE_GUI_CALLS, NULL);
	const wchar_t KAV_INTERFACE_GUI_CALLS[] = L"GUI_CALLS";					// Added in NodesHost v6.0 MP2

	// Added in NodesHost v5.0 MP4
	// ���������� ��������� KLPKG::PackageConfigurator (include/srvp/pkg/pkgcfg.h)
	const wchar_t KAV_INTERFACE_PACKAGE_SETTINGS[] = L"PACKAGE_SETTINGS";

	// brief ��������� ��� �������� ������ ����������� ������.
	interface IEnumInterfaces
	{
		virtual ~IEnumInterfaces (){};
		virtual BOOL QueryInterface( LPCWSTR lpszName, void** ppInterface ) const PURE; 
	};
	
	/*!
	  \brief ������ ����������� � ������, ������������ � ��������:
	  
				��� ������ �������					�������� ����������				��� ����������		��������������
				GROUP_POLICY						POLICY_SETTINGS					SettingsStorage		��������� ��������� ��������
				LOCAL_POLICY						LOCAL_SETTINGS					SettingsStorage		��������� ��������� ��������
													POLICY_SETTINGS*				SettingsStorage		��������� ��������� ��������
													AGENT_PROXY*					AgentProxy			��������� � ������ ������ (��� ���������)
				TASKS								TASK_PARAMS						Params				��������� ������
													POLICY_SETTINGS*				SettingsStorage		��������� ��������� ��������
				�������� ������						Params*							Params				�������� ������ ��� ��������������
				�������� ������						ChangesParams*					Params				���������� ������
				�������� ������						Settings*						Params				��������� ������� (������ �������, etc)
				
			* - ��������� ����� �������������
	*/

	/*!
		\brief ��������� ��������
	*/
	interface IKLConfiguratorPage : public KLSTD::KLBase
	{
		virtual ~IKLConfiguratorPage (){};

		/*!
			\brief �������� � ����� �������� ����� �����������, ����������� ��� ��� ������. 
			���� � ������ ����������� ����������, ����������� ������,
			������������ ���������� KLERR::Error (KLSTD::STDE_BADPARAM)
			������������ ���� �������� ���������� � �� ��������� �������������
			�������� ���������, ������������������� � ������ L"RWM_KLAKCON_PPN_PAGE_MODIFIED"
		*/
		virtual void SetInterfaces( IEnumInterfaces* pIEnumInterfaces ) PURE; 

		/*!
			\brief ���������� handle ���� ��������
		*/
		virtual HWND GetPageHWND() const PURE;

		/*!
			\brief ���������� TRUE, ���� �����-�� �������� � ���� �������� ���� �������� �������������,
			�� ��� ��������� ��� �� ���� ���������. � ��������� ������ ������������ FALSE.
		*/
		virtual BOOL IsPageDirty() const PURE;

		/*!
			\brief ���������� ��� ������� ���������� ��������� (��� ������� ������ Apply, OK)
			���� � ������� ��������� ��������� �� �������, ������������ ���������� KLERR::Error (KLSTD::STDE_BADFORMAT)
		*/
		virtual void Apply() PURE;

		/*!
			\brief ���������� ��� ������� ���������� ��������� (��� ������� ������ Apply, OK) ��� �������� 
			������������ ��������� ������������� ������. ���������� TRUE ���� ������ ���������.
			���������� � ��������� �������:
				1. � ������ KLPlugin::IKLConfigurator::PROPERTY_PAGE - 
						��� ������� Apply, Ok ��� ��� ������������ �� ������ ��������
				2. � ������ KLPlugin::IKLConfigurator::WIZARD97_PAGE - ��� ������� ������ Next
		*/
		virtual BOOL ValidateUserInput() PURE;

		/*!
			\brief ���������� ��� ���������� ������, ���������� ����� � ��������
		*/
		virtual void NotifyDataUpdated() PURE;

		/*!
			\brief ���������� � ������ ��������� ��������. ���������� TRUE, ����
			��������� ��������, � FALSE, ���� ��������� ����������
		*/
		virtual BOOL NotifyPageSelecting() PURE;

		/*!
			\brief ���������� ����� ����, ��� �������� ����� ��������
		*/
		virtual void NotifyPageSelected() PURE;

		/*!
			\brief ���������� � ������ ����������� ��������. ���������� TRUE, ����
			����������� ��������, � FALSE, ���� ����������� ����������
		*/
		virtual BOOL NotifyPageDeselecting() PURE;

		/*!
			\brief ���������� ��� ������� ��������� �������� �� ���������.
			�������� �� ��������� ���� ��������� ����������� � storage � ��������� �� �����.
			���� ������� ��������� �������� �� �������, ������������ ���������� KLERR::Error (KLSTD::STDE_BADFORMAT)
		*/
		virtual void ApplyDefaultData() PURE;		
	};


	/*! 
		\brief �������������, ������������� ��� ��������/������ �� ��������.
		��������! ������� �������, �� ������� ��������� ���������, ������ ����
		���������� �� ������� �������� ������������ ���� �������.
	*/
	typedef KLSTD::CAutoPtr<IKLConfiguratorPage> IKLConfiguratorPagePtr;


/*! Group Policy structure
   
	 ��� �������� ������ ��������� �������� � �������� ������������ ��������� ����������:
    ��������� ������:
        <container1_name>
         +---<var1_name>=value1 //type1
         +---<var2_name>=value2 //type2


    ��������������� �� ��������� ��������:
        <container1_name>                              //PARAMS
         +---<c_szwSPS_Value>                          //PARAMS_T
         |          +---<var1_name>                    //PARAMS_T
         |               +---<c_szwSPS_Value>=value1   //type1
         |               +---c_szwSPS_Mandatory        //BOOL_T
         |               +---c_szwSPS_Locked           //BOOL_T
         |               +---c_szwSPS_LockedPolicyName //STRING_T
         |               +---c_szwSPS_LockedGroupName  //STRING_T
         |          +---<var2_name>                    //PARAMS_T
         |               +---<c_szwSPS_Value>=value2   //type2
         |               +---c_szwSPS_Mandatory        //BOOL_T
         |               +---c_szwSPS_Locked           //BOOL_T
         |               +---c_szwSPS_LockedPolicyName //STRING_T
         |               +---c_szwSPS_LockedGroupName  //STRING_T
         +---c_szwSPS_Mandatory                        //BOOL_T
         +---c_szwSPS_Locked                           //BOOL_T
         +---c_szwSPS_LockedPolicyName                 //STRING_T
         +---c_szwSPS_LockedGroupName                  //STRING_T

	//Mandatory attributes
		 // value
		 static const wchar_t c_szwSPS_Value[]=L"KLPRSS_Val";        //
		 // is value mandatory
		 static const wchar_t c_szwSPS_Mandatory[]=L"KLPRSS_Mnd";    //BOOL_T
	//Optional attributes
		 // is value locked ?
		 static const wchar_t c_szwSPS_Locked[]=L"KLPRSS_ValLck";    //BOOL_T
		 // policy name (if value is locked)
		 static const wchar_t c_szwSPS_LockedPolicyName[]=L"KLPRSS_ValLckPolicy";//STRING_T
		 // group name (if value is locked)
		 static const wchar_t c_szwSPS_LockedGroupName[]=L"KLPRSS_ValLckGroup";//STRING_T
*/

/*! Local Policy structure
   
	 ��� �������� ������ ��������� �������� � �������� ������������ ��������� ����������:
			- � ���������� ��������� �������� ���������� �������� �������� � ������� � ������
			  � ���, ������������ � ������������� ��� ���������� ����������
			- ��� �������� ����� �����������, �������� ��� ������� �������� ������� �� ��������
			  ��������� ��������, ���� ��� ���� ��������� ���� c_szwSPS_Locked ��������� TRUE, 
			  ��� �� �������� ��������� ��������, ���� ���� c_szwSPS_Locked ��������� ��������
			  ��������� FALSE. � ������ c_szwSPS_Locked == TRUE �� �������� ��������� ��������
			  ���������� ����� �������� c_szwSPS_LockedPolicyName � c_szwSPS_LockedGroupName. 
*/

/*! Task Params structure
   
	 ��� �������� ������ ������ � �������� ������������ ��������� ����������:
			- � ���������� ������ ���������� ������� ��������� Params �� ���������� ��������,
			  ������������������ �������, ������������� � ������������� ��� ���������� ����������
			- ��� �������� ����� �����������, �������� ��� ������� �������� ������� �� ��������
			  ��������� ��������, ���� ��� ���� ��������� ���� c_szwSPS_Locked ��������� TRUE, 
			  ��� �� �������� ������, ���� ���� c_szwSPS_Locked ��������� ��������
			  ��������� FALSE. � ������ c_szwSPS_Locked == TRUE �� �������� ��������� ��������
			  ���������� ����� �������� c_szwSPS_LockedPolicyName � c_szwSPS_LockedGroupName. 
*/


	/*!
		\brief ��������� ������������� �������
	*/
	interface IKLConfigurator : public KLSTD::KLBase
	{
		virtual ~IKLConfigurator (){};

		/*!
			\brief Enumerator ����� �������. ������������ � ������ CreatePage (ePageType)
		*/
		typedef enum tagPAGE_TYPES
		{
			PROPERTY_PAGE,
			WIZARD97_PAGE
		} PAGE_TYPES;

		/*!
			\brief Enumerator ����� ��������������. ������������ � ������ CreateConfigurator (eConfiguratorType)
		*/
		typedef enum tagCONFIGURATOR_TYPES
		{
			GROUP_POLICY_CONFIGURATOR,
			LOCAL_POLICY_CONFIGURATOR,
			TASK_CONFIGURATOR,
			INSTALLER_CONFIGURATOR
		} CONFIGURATOR_TYPES;

		/*!
			\brief ���������� ���������� ������� ��� ������� �������������
		*/
		virtual unsigned long GetPagesCount() const PURE;

		/*!
			\brief ������� �������� � ������������ ��������
			����������� ������ ������ ���� ��������� �� �������� ������������ ���� �������
		*/
		virtual IKLConfiguratorPagePtr CreatePage(HWND hParent, unsigned long nIndex ) PURE;

		/*!
			\brief 
		*/
		virtual void GetPageHelpInfo(unsigned long nIndex, LPWSTR* pbstrHelpFilePath,long* pnHelpID)  const PURE;

		/*!
			\brief ���������� ��������� ��������
		*/
		virtual LPCWSTR GetPageTitle(unsigned long nIndex) const PURE;

		/*!
			\brief ���������� ������������ ��������
		*/
		virtual LPCWSTR GetPageSubtitle(unsigned long nIndex) const PURE;

		/*!
			\brief ���������� handle �����������, ��������������� �� ���������
		*/
		virtual HICON GetPageIcon(unsigned long nIndex) const PURE;

		/*!
			\brief �������� � ����� �������� ����� �����������, ����������� ��� ��� ������. 
			���� � ������ ����������� ����������, ����������� ������,
			������������ ���������� KLERR::Error (KLSTD::STDE_BADPARAM)
			������������ ���� �������� ���������� � �� ��������� �������������
			�������� ���������, ������������������� � ������ L"RWM_KLAKCON_PPN_PAGE_MODIFIED"
		*/
		virtual void SetInterfaces( IEnumInterfaces* pIEnumInterfaces ) PURE; 

		/*!
			\brief ���������� ��� ������� ��������� �������� �� ���������.
			�������� �� ��������� ���� ��������� ����������� � storage � ��������� �� �����.
			���� ������� ��������� �������� �� �������, ������������ ���������� KLERR::Error (KLSTD::STDE_BADFORMAT)
		*/
		virtual void ApplyDefaultData() PURE;		
	};

	
	/*! 
		\brief �������������, ������������� ��� �������� ������ �� ������������.
		��������! ������� ��������������, �� ������� ��������� ���������, ������ ����
		���������� �� ������� �������� ������������ ���� �������.
	*/
	typedef KLSTD::CAutoPtr<IKLConfigurator> IKLConfiguratorPtr;


	/*!
		\brief ��������� ������������. �������� ������ ����������� ���������� � �������� � �����������,
		����������, ������������ � ������� �������. �������� ����� �������, ����������� ���������, ��������� ������.
	*/
	interface IKLLocalizer
	{
		/*!
			\brief ���������� ���������� � �������, ��������������� �����������, ������� ��������� ������.
			���������� ���������� KLERR::Error (KLSTD::STDE_BADPARAM) � ������ �������� ������������ ������� ������.
			���������� ��������� ��������� ������� ������:
			UINT nResourceID ������������� ������� ��� ������ �������
			LPCWSTR lpszFormat ������ ��������������
			������ ������ �������������� ���������:

				<�����>%<����� ���������><�����>%<����� ���������><�����>%<����� ���������><�����>;;��������1;;��������2;;��������3;;

			��� ��������1, ��������2, ��������3 - �������������� �������� ����������

			Root Params
				|- wchar_t[] (L"event_id"):						INT_T				
				|- wchar_t[] (L"severity"):						INT_T		
				|- wchar_t[] (L"domain_name"):					STRING_T
				|- wchar_t[] (L"hostname"):						STRING_T
				|- wchar_t[] (L"product_name"):					STRING_T
				|- wchar_t[] (L"product_version"):				STRING_T
				|- wchar_t[] (L"event_type"):						STRING_T
				|- wchar_t[] (L"event_type_display_name"):	STRING_T			// �� ������������ ��� �����������
				|- wchar_t[] (L"descr"):							STRING_T			// �� ������������ ��� �����������
				|- wchar_t[] (L"rise_time"):						DATE_TIME_T
				|- wchar_t[] (L"body"):								PARAMS_T			// �� ������������ ��� �����������
				|- wchar_t[] (L"par1"):								STRING_T			// �������� ��������� ����������� � ����������� �� ���� �������
				|- wchar_t[] (L"par2"):								STRING_T			// �������� ��������� ����������� � ����������� �� ���� �������
				|- wchar_t[] (L"par3"):								STRING_T			// �������� ��������� ����������� � ����������� �� ���� �������
				|- wchar_t[] (L"par4"):								STRING_T			// �������� ��������� ����������� � ����������� �� ���� �������
				|- wchar_t[] (L"par5"):								STRING_T			// �������� ��������� ����������� � ����������� �� ���� �������
				|- wchar_t[] (L"par6"):								STRING_T			// �������� ��������� ����������� � ����������� �� ���� �������

			C�������� �������� ������:
			Root Params 1
				|-wchar_t[] (L"GNRL_EA_DESCRIPTION_DISP_NAME"):		STRING_T

			
			Root Params 2
				|- wchar_t[] (L"event_type_display_name"):	STRING_T			
				|- wchar_t[] (<par1>):								STRING_T			// �������� ��������� ����������� � ����������� �� ���� �������
				|- wchar_t[] (<par2>):								STRING_T			// �������� ��������� ����������� � ����������� �� ���� �������
				|- wchar_t[] (<par3>):								STRING_T			// �������� ��������� ����������� � ����������� �� ���� �������
				|- wchar_t[] (<par4>):								STRING_T			// �������� ��������� ����������� � ����������� �� ���� �������
				|- wchar_t[] (<par5>):								STRING_T			// �������� ��������� ����������� � ����������� �� ���� �������
				|- wchar_t[] (<par6>):								STRING_T			// �������� ��������� ����������� � ����������� �� ���� �������
		*/
		virtual void LocalizeEvent (UINT nResourceID, KLPAR::Params* pSrcParams, KLPAR::Params* pTrgParams1, KLPAR::Params* pTrgParams2 ) PURE; 

		/* ������ ������ ��� ������ ��� ��������*/
		virtual void LocalizeEvent (LPCWSTR lpszFormat, KLPAR::Params* pSrcParams, KLPAR::Params* pTrgParams1, KLPAR::Params* pTrgParams2 ) PURE; 
		
		/*!
			\brief 
			
			!!! OBSOLETE !!! �� ����� ��������� ��������

			���������� �������������� �������� ��������. �������� ��������� �������� �������� ��� ���� ���������.
			���������� ���������� KLERR::Error (KLSTD::STDE_BADPARAM) � ������ �������� ������������ ������� ������.
		*/
		virtual std::wstring GetLocalizedProductName (LPCWSTR lpszProductName, LPCWSTR lpszProductVersion) PURE;

		/*!
			\brief ���������� ���������� � ���������� ������ ����������, ������� ��������� ������.
			���������� ���������� KLERR::Error (KLSTD::STDE_BADPARAM) � ������ �������� ������������ ������� ������.
			���������� ��������� ��������� ������� ������:
			Root Params
				|- KLHST::c_spRtInstInfo:								PARAMS_T				// �� ������������ ��� �����������
					|- <ProductName>:										PARAMS_T				// ��� ��������=�������������� ��������
						|- KLHST::c_spProductVersion:					STRING_T				// ������ ��������
						|- KLHST::c_spRtInstInfo:						ARRAY_T
								|- Item0										PARAMS_T
								|		|- KLHST::c_spComponentName:	STRING_T				// ��� ���������� - used for defining componets -> structure of statistics
								|		|- KLHST::c_spInstanceId:		STRING_T				// �������������  ���������� ����������
								|		|- KLHST::c_inst_Statistics:	PARAMS_T				// ���������� ������� ���������� ����������
								|				|- <name1>:					type1					
								|				|- <name2>:					type2					// �������� ��������� � �� ����� �������� ����������� � ����������� �� ����������
								|			  ...														// (��. �� �������� � ��������� "�������� KCA ����������� ����������")
								|				|- <nameN>:					typeN
							................................
								|- ItemN										PARAMS_T
										|- KLHST::c_spComponentName:	STRING_T				// ��� ���������� - used for defining componets -> structure of statistics
										|- KLHST::c_spInstanceId:		STRING_T				// �������������  ���������� ����������
										|- KLHST::c_inst_Statistics:	PARAMS_T				// ���������� ������� ���������� ����������
												|- <name1>:					type1					
												|- <name2>:					type2					// �������� ��������� � �� ����� �������� ����������� � ����������� �� ����������
											  ...														// (��. �� �������� � ��������� "�������� KCA ����������� ����������")
												|- <nameN>:					typeN

			C�������� �������� ������:
			Root Params
				|- <LocStatDescription>:		PARAMS_T				// ���������� ������� ���������� ����������. �������� ���� - �������������� �������� ������ ����������
						|- <name1>:					type1					
						|- <name2>:					type2					// �������� ��������� � �� ����� �������� ����������� � ����������� �� ����������
					  ...														// (��. �� �������� � ��������� "�������� KCA ����������� ����������")
						|- <nameN>:					typeN


  			const wchar_t c_spRtInstInfo[]=L"klhst-rt-InstInfo";			//PARAMS_T
			const wchar_t c_spProductVersion[]=L"klhst-ProductVersion";	//STRING_T
			const wchar_t c_spRtTskArray[]=L"klhst-rt-TskArray";			//ARRAY_T<PARAMS_T>
			const wchar_t c_spComponentName[]=L"klhst-ComponentName";	//STRING_T
			const wchar_t c_spInstanceId[]=L"klhst-InstanceId";			//STRING_T
			const wchar_t c_inst_Statistics[]=L"instStatistics";			//PARAMS_T

		*/
		virtual void LocalizeStatistic (KLPAR::Params* pSrcParams, KLPAR::Params* pTrgParams) PURE;	

	};


	/*!
		\brief ��������� ������� � ����������� �������� ����������������.
		�������� ����� �������, ����������� ���������, ��������� ������.
	*/
	interface IKLAccessor
	{
		/*!
			\brief ������� ������ ������������� ��������� ����.
			����������� ������ ������ ���� ��������� �� �������� ������������ ���� �������
			��� �������� ������������� ��� ������, ���������� ��������� �� �������������
			�� ������ ��������� ������, � ��������� ������� ������ �������� ������ �� �����/
		*/
		virtual IKLConfiguratorPtr CreateConfigurator(IKLConfigurator::CONFIGURATOR_TYPES eConfiguratorType, 
																	 IKLConfigurator::PAGE_TYPES ePageType, 
																	 LPCWSTR lpszTaskID = NULL) PURE; 

		/*!
			\brief ���������� ������ �� ������ ������������. ����������� �� �������� ������� ����� �� �������.
		*/
		virtual IKLLocalizer* GetLocalizer() PURE; 


		/*!
			\brief ���������� ������ �����, �������������� ��������. �������� ��������� ������ ����� ��������� ���:
				Root Params
					|- wchar_t[] (L"Tasks"): ARRAY_T
							|- Item0
							|		|- wchar_t[] (L"Component"):			 STRING_T	// ��� ����������, ������������ ������ ������� ����
							|		|- wchar_t[] (L"TaskID"):				 STRING_T	// ������������� ������ (��. �������� � ��������� "�������� KCA ����������� ����������")
							|		|- wchar_t[] (L"LocalizedTaskName"): STRING_T	// �������������� ��� ������
							|- Item1
							|		|- wchar_t[] (L"Component"):			 STRING_T	// ��� ����������, ������������ ������ ������� ����
							|		|- wchar_t[] (L"TaskID"):				 STRING_T	// ������������� ������ (��. �������� � ��������� "�������� KCA ����������� ����������")
							|		|- wchar_t[] (L"LocalizedTaskName"): STRING_T	// �������������� ��� ������
						............														
							|- ItemN
									|- wchar_t[] (L"Component"):			 STRING_T	// ��� ����������, ������������ ������ ������� ����
									|- wchar_t[] (L"TaskID"):				 STRING_T	// ������������� ������ (��. �������� � ��������� "�������� KCA ����������� ����������")
									|- wchar_t[] (L"LocalizedTaskName"): STRING_T	// �������������� ��� ������
		*/
		virtual void GetTasks(KLPAR::Params* pParams) PURE; 

		/*!
			\brief ���������� ������ �������, �������������� ��������. �������� ��������� ������ ����� ��������� ���:
				Root Params
					|- wchar_t[] (L"Events"): ARRAY_T
							|- Item0
							|		|- wchar_t[] (L"Component"):			 STRING_T	// ��� ����������, ������������ ������� ������� ���� (STRING_T)
							|		|- wchar_t[] (L"EventID"):				 STRING_T	// ������������� ������� (��. �������� � ��������� "�������� KCA ����������� ����������")
							|		|- wchar_t[] (L"Severity")				 INT_T		// ID ����������� ������ [1-4]
							|		|- wchar_t[] (L"LocalizedEventIDName")STRING_T	// �������������� �������� ���� �������
							|- Item1
							|		|- wchar_t[] (L"Component"):			 STRING_T	// ��� ����������, ������������ ������� ������� ���� (STRING_T)
							|		|- wchar_t[] (L"EventID"):				 STRING_T	// ������������� ������� (��. �������� � ��������� "�������� KCA ����������� ����������")
							|		|- wchar_t[] (L"Severity")				 INT_T		// ID ����������� ������ [1-4]
							|		|- wchar_t[] (L"LocalizedEventIDName")STRING_T	// �������������� �������� ���� �������
						............														
							|- ItemN
									|- wchar_t[] (L"Component"):			 STRING_T	// ��� ����������, ������������ ������� ������� ���� (STRING_T)
									|- wchar_t[] (L"EventID"):				 STRING_T	// ������������� ������� (��. �������� � ��������� "�������� KCA ����������� ����������")
									|- wchar_t[] (L"Severity")				 INT_T		// ID ����������� ������ [1-4]
									|- wchar_t[] (L"LocalizedEventIDName")STRING_T	// �������������� �������� ���� �������

				��� �������� Severity ������������ ��������� ���������:
					
					1 - Information
					2 - Warning
					3 - Failure
					4 - Critical
		*/
		virtual void GetEvents(KLPAR::Params* pParams) PURE; 

		/*!
			\brief ���������� �������� ��������, ������������ ��������. 
		*/
		virtual LPCWSTR GetProductName() const PURE;

		/*!
			\brief ���������� �������� ������ ��������, ������������ ��������. 
		*/
		virtual LPCWSTR GetProductVersion() const PURE;
	};

	/*!
		\brief ��������� ������� � PropertySheet. 
	*/
	interface IPropertySheet  
	{
		virtual ~IPropertySheet (){};

		/*!
			\brief ���������� TRUE, ���� ���� Inherit �������, � ��������� ������ ���������� FALSE
		*/
		virtual BOOL IsInherit() const PURE;
	};

	/*!
		\brief ���������� ��������� ������� � ����������� �������� ����������������
	*/
	CALL_SPEC IKLAccessor* GetAccessor(); 

// ������ 2 - �������������� �������

	/*!
		\brief �������������� DLL �������
	*/
	CALL_SPEC void InitPlugin(); 

	/*!
		\brief ���������������� DLL �������
	*/
	CALL_SPEC void DeinitPlugin(); 
};

#endif // __CONFIGURATOR_INTERFACES_H__
