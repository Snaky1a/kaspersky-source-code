/*!
 * (C) 2002 Kaspersky Lab 
 * 
 * \file	prcp/AgentProxy.h
 * \author	Andrew Kazachkov
 * \date	01.10.2002 13:51:07
 * \brief	��������� ������ ����������������� ��� ��������� ����������� ��������.
 * 
 */

#ifndef KLPRCP_AGENTPROXY_H
#define KLPRCP_AGENTPROXY_H

#include <string>

#include "std/err/error.h"
#include "std/par/params.h"
#include "kca/prci/componentid.h"
#include "kca/prci/componentinstance.h"
#include "kca/prts/tasksstorage.h"
#include "kca/pres/eventsstorage.h"
#include "kca/prcp/componentproxy.h"
//#include <bl/agentbusinesslogic.h>

namespace KLPRCP {

	const wchar_t c_CID_ProductName[]	= KLPRCI_PRODUCT_NAME;
	const wchar_t c_CID_Version[]		= KLPRCI_PRODUCT_VERSION;
	const wchar_t c_CID_ComponentName[] = KLPRCI_COMPONENT_NAME;
	const wchar_t c_CID_InstanceId[]	= KLPRCI_INSTANCE_ID;

	const wchar_t c_LauncherComponentId[]	= L"LauncherComponentId";
	const wchar_t c_AsyncId[]				= KLPRCI_ASYNCID;

	const wchar_t c_EventComponentStarted[]		= L"ComponentStarted";
	const wchar_t c_EventComponentShutdowned[]	= L"ComponentShutdowned";

	//! ������� � ��������� dialup ����������
	const wchar_t c_EventDialupConnectionEstablished[]	= L"Dialup Established";
	const wchar_t c_EventDialupConnectionBroken[]		= L"Dialup Broken";

	const wchar_t c_evpUID[]=L"KLPRCP_UID";

	//! ������� � ���������� ������� ������ �� TS
	const wchar_t c_EventTaskTsResult[]=L"KLPRCP_EVENT_TASK_TS_RESULT";
	/*!
		���� ������� ����� ��������� ���������:
		c_evpUID
		����� ����,
		- � ������ ������
			KLBLAG::c_szwServerProduct		- ��� �������� 
			KLBLAG::c_szwServerVersion		- ������ �������� 
			KLBLAG::c_szwServerComponent	- ��� ����������
			KLBLAG::c_szwServerTaskName		- ��� ������
			KLBLAG::c_szwServerInstance		- ��� ���������� ����������, �� ������� ���� �������� ������
			�KLBLAG::_szwTaskId				- ������������� ���������� ������
		- � ������ �������
			KLBLAG::c_szwErrorInfo			- 
				KLBLAG::c_szwErrorModule	- ��� ������, � ������� ��������� ������
				KLBLAG::c_szwErrorCode		- ��� ������
				KLBLAG::c_szwErrorMsg		- ��������� �� ������
				KLBLAG::c_szwErrorFileName	- ��� �����, � ������� �������� ������
				KLBLAG::c_szwErrorLineNumber	- ������, �� ������� ��������� ������
	*/
    
    const wchar_t c_EventPingTimeoutElapsed[]=L"KPRCP_PING_TIMEOUT_ELAPSED";
    /*!
        c_CID_ProductName
        c_CID_Version
        c_CID_ComponentName
        c_CID_InstanceId
    */


	/*!
		\brief ����� ��� ������ StartComponentEx.
	*/

	enum{		
		SCF_AUTOSTOP=1,			/*!	��������� ���������� �������� �������
									INSTANCE_AUTOSTOP ������ ���, ����� �������
									������ �� ���� ��������� �� 1 � 0 (�.�. �
									���� ��� �� ����� ������, � �� �������� ��
									����� ������).
								*/

		SCF_SYNC=2,				/*!	���������� ������: ����� �� ����� ����������,
									���� ���������� ��������� �� �������������������.
								*/

		SCF_SHAREPROCESS=8,		/*!	������ ��� ����������� ���� MTF_DLL. ���������
									����� �������� � �������� ������������ ��������,
									� ������� ��� ������ �����.
								*/
		SCF_LOADTOAGENT=0		/*!	������ ��� ����������� ���� MTF_DLL. ���������
									����� �������� � �������� ������������ ������.
									��� �������� ������������ �� ���������.
								*/
	};


	/*!
		\brief ���� ������ (������ ��� ����������� ���� MTF_EXE).
	*/


	enum{
		/*! ������ ��� ����������� ���� MTF_EXE. ��������� ����� ������� �
			��������� �����-������ ������. ��� �������� ������������ ��
			���������.
		*/
		LT_SHAREAGENTLOGON=0,	


		/*!	������ ��� ����������� ���� MTF_EXE. ��������� ����� ������� �
			��������� ������� ������ ����, ��������� ����� StartComponentEx.
			����� �������������� ��������� � ������ LT_LOADPROFILE.
		*/	
		LT_LOGON_THIS=1,


		/*! ������ ��� ����������� ���� MTF_EXE. ��� ������� ���������� �����
			������� ����� logon session � ��������� szwUser, szwDomain,
			szwPassword. ����� �������������� ��������� � ������
			LT_LOADPROFILE. ������� ������ ������ ����� �����
			SE_INTERACTIVE_LOGON_NAME. 
		*/
		LT_LOGON_INTERACTIVE=2,	


		/*! ������ ��� ����������� ���� MTF_EXE. ��� ������� ���������� �����
			������� ����� logon session � ��������� szwUser, szwDomain,
			szwPassword. ����� �������������� ��������� � ������
			LT_LOADPROFILE. ������� ������ ������ ����� �����
			SE_SERVICE_LOGON_NAME.
		*/
		LT_LOGON_SERVICE=3,

		/*!	������ ��� ����������� ���� MTF_EXE. �������� ������� �������
			������. ������������ ��� LT_SHAREAGENTLOGON.
		*/
		LT_LOADPROFILE=0x80000000
	};


    /*!
    * \brief ������� ��������� ������ �����������������.
    *  
    *  ������ ��������� ������������� ���������������� ������ ����������������� 
    *  ��� ������ ����������� ��������. 
    *
    */


    class KLSTD_NOVTABLE AgentProxy : public ComponentProxy
	{
    public:

    /*!
      \brief
			��������� ��������� �������� ���������� ��� ���������. 
		��������� ������ ������������ � ������� ComponentInstanceStarted.
		������������� ���������� ������������ ���������� ���������� ���
		���������� ���������. ������� ComponentInstanceStarted �������� ����
		asyncId � ���������������, ���������� ��������.
			� ������ ������������ �������, ������ ����� ������, ��� ���������
		������ ��� ���������, ������� �� ����������, ������ ������������
		�� ��� �������.
			���� ����� ����������, ����� ����� ���������� ����� �������
		������� ComponentInstanceStarted ��� ����������� ����������, ��� �
		������ ��������� �������� lAsyncTimeout (� ���� ������ ����� ���������
		���������� KLSTD::STDE_TIMEOUT) - ������������� �� �������
		ComponentInstanceStarted ��� �������������.

       
        \param id		[in/out] ������������� ���������� ��� �������.
        \param pParameters	[in] ��������� ��� ������ ����������.
        \param wstrAsyncId	[in] ���������� ������������� ��� ������������ 
									������� � ������ ����������.  ��� ��������
									���������� � ���� asyncId � ���� �������
									ComponentInstanceStarted. ������ ��������
									�������� ������������ ������ � ������,
									���� ��������� ������� ��������� (������
									���� SCF_SYNC).
		\param dwFlags		[in] ����� SCF_*.
		\param lAsyncTimeout[in] ������������ ����� ������ � �������������
									����������, ��. ������ �������� ������������,
									���� �� ������ ���� SCF_SYNC.
		\param lTimeoutStop	[in] ����� ����� ���������� ��������� � ����������
									����������, ����� ������� �� �������
									������� INSTANCE_TIMEOUTSTOP (���� �������
									����� KLSTD_INFINITE, �� �������), ��.
		\param lLogonType	[in] ��� ������. ������������, ���� ��� ����������
									������� ��  MTF_EXE. ���� �� �������� LT_*.									
		\param szwUser		[in] ��� ������� ������, ��� ������� ����� �������
									���������. ������������, ���� lLogonType ��
									����� LT_LOGON_INTERACTIVE. ������ ���
									����������� ���� MTF_EXE.
		\param szwDomain	[in] ��� ������. ������������, ���� lLogonType ��
									����� LT_LOGON_INTERACTIVE.
		\param szwPassword	[in] ������.������������, ���� lLogonType ��
									����� LT_LOGON_INTERACTIVE.
    */

       virtual void StartComponentEx( 
						KLPRCI::ComponentId&	id,
						KLPAR::Params*			pParameters,
						std::wstring			wstrAsyncId,
						AVP_dword				dwFlags,
						long					lAsyncTimeout,
						long					lTimeoutStop=KLSTD_INFINITE,
						long					lLogonType=LT_SHAREAGENTLOGON,
						const wchar_t*			szwUser=NULL,
						const wchar_t*			szwDomain=NULL,
						const wchar_t*			szwPassword=NULL)  = 0;

    /*!
      \brief ��������� ��������� ��������.  
      
        ����� �����������. ��������� ������ ������������ � ������� 
        ComponentInstanceStarted.  ������������� ����� ������������
        ���������� ���������� ������� �����������������. �������
        ComponentInstanceStarted �������� ���� asyncId � ���������������,
        ���������� ��������.  ����� ������� ������ ����� ������, ��� ���������
        ������ ��� ���������, ������� �� ����������.

       
        \param id           [in]  ������������� ���������� ��� �������.
        \param pParameters  [in]  ��������� ��� ������ ����������.
        \param asyncId      [in]  ���������� ������������� ��� ������������ 
                                  ������� � ������ ����������.  ��� ��������
                                  ���������� � ���� asyncId � ���� �������
                                  ComponentInstanceStarted.
		\param bAutoStop	[in]  ���� true, �� ��������� ����������
									�������� ������� INSTANCE_AUTOSTOP ������
									���, ����� ������� ������ �� ���� ���������
									�� 1 � 0 (�.�. � ���� ��� �� ����� ������,
									� �� �������� �� ����� ������).
		\param bStartInThisProcess [in] ���� true, �� ���������� ����� �������� � 
									������ ���������� ������ ������� ��������, ����
									false ���������� ����� �������� � ������
									�������� ������.
		\param lTimeoutStop	[in]  ����� ����� ���������� ��������� � ����������
									����������, ����� ������� �� �������
									������� INSTANCE_TIMEOUTSTOP (���� �������
									����� KLSTD_INFINITE, �� �������).

    */
       virtual void StartComponent( 
		   const KLPRCI::ComponentId&	id,
		   KLPAR::Params*				pParameters,
		   std::wstring					asyncId,
		   bool							bAutoStop=true,
		   bool							bStartInThisProcess = false,
		   long							lTimeoutStop=KLSTD_INFINITE)  = 0;

	/*!
      \brief ��������� ��������� ��������.  
      
        ����� ����������. ������ �������, ���� ��������� �� ����� ������� �������.
        � ������, ���� �������� timeout �� ������ ����������, ������ ��������
        ��������������� ���������� STDE_TIMEOUT.
       
        \param id        [in/out] ������������� ���������� ��� �������.
									� ������ ��������� �������, ���� id.instanceId ����������� 
									��������������� ����������� ����������.
        \param pParameters  [in]  ��������� ��� ������ ����������.
        \param timeout      [in]  ������������ ����� ������ � ������������� ���������� (msec).
                                  ���� �������� timeout < 0, �� ����� �������� �����������.
		\param bAutoStop	[in]  ���� true, �� ��������� ����������
									�������� ������� INSTANCE_AUTOSTOP ������
									���, ����� ������� ������ �� ���� ���������
									�� 1 � 0 (�.�. � ���� ��� �� ����� ������,
									� �� �������� �� ����� ������).
		\param lTimeoutStop	[in]  ����� ����� ���������� ��������� � ����������
									����������, ����� ������� �� �������
									������� INSTANCE_TIMEOUTSTOP (���� �������
									����� KLSTD_INFINITE, �� �������).

    */
       virtual void StartComponentSync( 
				KLPRCI::ComponentId&		id,
				KLPAR::Params*				pParameters,
				long						timeout=KLSTD_INFINITE,
				bool						bAutoStop=true,
				bool						bStartInThisProcess = false,
				long						lTimeoutStop=KLSTD_INFINITE) = 0;



    /*!
      \brief ���������� ������ ���������� ����� �����������.  
      
        \param filter       [in]  ������ �� ������������� ���������� ��� ��������� ������.
        \param components   [out] ������ ��������������� ���������� ����� �����������.

    */

       virtual void GetComponentsList(
		   const KLPRCI::ComponentId&			filter,
		   std::vector<KLPRCI::ComponentId>&	components) = 0;

    /*!
      \brief ���������, ������� �� ������ ���������.
       
        \param id      [in]  ������������� ����������.
		\return		true -- �������

    */
        virtual bool IsComponentStarted(
					const KLPRCI::ComponentId&	id)  = 0;


	/*!
	  \brief	���������� ���������� � ����������.

	  \param	id [in]			������������� ���������� ����������
	  \param	ppParams [out]	��������� � ���������� ���������� ����������.
				����� ��������� ��������
					KLPRCI::c_AutoStopAllowed, BOOL_T,	��������� ����������
						�������� ������� INSTANCE_AUTOSTOP ������ ���, �����
						������� ������ �� ���� ��������� �� 1 � 0 (�.�. � ����
						��� �� ����� ������, � �� �������� �� ����� ������).
					KLPRCI::c_TimeoutStopAllowed, INT_T, ����� ����� ����������
						��������� � ���������� ����������, ����� ������� �� �������
						������� INSTANCE_TIMEOUTSTOP (���� ������� ����������� �
						���������� ��� ����� KLSTD_INFINITE, �� �������).
	*/
		virtual void GetInstanceInfo(
					const KLPRCI::ComponentId&	id,
					KLPAR::Params**				ppParams)=0;

    /*!
      \brief ����������� ������� �� ��������� ���������� � 
            ������������� ������� � ������������� callback ��� ��������� ����������.
       
        ���� ������ �� ������ ���� �� ���������� �������� (��� ��������, ������,
        ��� ����������, ������������� ����������, ��� �������), 
        �� ���������� ������� �� ����� ��������� 
        �� ������������.  ��� ������� �� ��������� ������� �������� ������������
        ������ �� ��������� �����, �� ���� ���� ���� ���� � � ������� � � ������� �
        ��� ���� �����, �� ������� ������������ ����������.

        ������ ����� ����������� �� ��������� ����� �������.  � ���� ������ �� �������
        ��������� ����������� ��� ������� �� ���������� �� �������� �������� �������.

        \param componentFilter  [in]  ������ �� �������������� ����������� ��� 
                                        �������� �� �������.
		\param eventType        [in]  ��� �������.
        \param eventBodyFilter  [in]  ������ �� ��������� �������.
        \param callback         [in]  Callback - ������� ��� ��������� ���������� � 
                                        ������������� �������.
        \param context          [in]  �������� �������� ��� �������� � callback - �������.
                                      ������ ��������� ������ ���� ���������� ��� �����
                                      ��������.
        \param hSubscribe       [out] ������������� �������� ��� ����������� ����������� ��������.

    */

       virtual void SubscribeEx( 
                        const KLPRCI::ComponentId&	componentFilter, 
                        const std::wstring&			eventType,
                        const KLPAR::Params*		eventBodyFilter,
                        EventCallback				callback,
                        void*						context,
						KLPRCI::HSUBSCRIBE&			hSubscribe) = 0;


    /*!
      \brief ���������� �������� ������� �� ������� ������������� ����.
       
        ������������ �������� ���� �������� ��� ������� AgentProxy, 
        ��������� ������� ��������� � �����������, ����������� � ������ ������.

        \param hSubscribe   [in] ������������� ��������, ���������� � SubscribeEx.
    */

       virtual void StopSubscriptionEx(KLPRCI::HSUBSCRIBE hSubscribe)  = 0;


    /*!
      \brief ���������� ������ ������ TasksStorage ��� ������ �� ������� ���������������
                � ���������� �����.
       
        \param storage       [out] ������ ������ TasksStorage.

    */
        virtual void GetTasksStorage( 
                        KLPRTS::TasksStorage ** storage)  = 0;


    /*!
      \brief ���������� ������ ������ EventsStorage ��� ������ �� ������� c������,
            �������������� � �������������� ������.
       
        \param storage       [out] ������ ������ EventsStorage.

    */
        virtual void GetEventsStorage( 
                        KLPRES::EventsStorage ** storage)  = 0;

	/*!
		
      \brief ������� ����� ������ ComponentProxy ��� ���������� �������� ����������.

        ���� ��������� ����������� �������� � �������������� ����������, ����������� �
        ��������� id, �� ������������ ��������� �� ������������ ���������.
       
        \param id      [in]  ������������� ���������� ��������� proxy ����������.
        \param proxy   [out] Proxy - ������ ��� ����������.

    */
        virtual void CreateComponentProxy( 
							const KLPRCI::ComponentId & id,
							ComponentProxy ** proxy) = 0;

	/*!		
		\brief ��������� ������ �� ��������� �����.

        \param wstrTaskId	[in]	������������� ������ � ���������
		\param lTimeout		[in]	������� �������� ������� ������, ��
        \param idComponent	[out]	������������� ����������
        \param wstrTaskName	[out]	��� ������
        \param lTaskId		[out]	������������� ���������� ������
	*/

		virtual void StartTasksFromTS(
						const std::wstring&			wstrTaskId,
						long						lTimeout,
						KLPRCI::ComponentId&		idComponent,
						std::wstring&				wstrTaskName,
						long&						lTaskId) = 0;

    };
}

/*!
	\brief ����� ��� �������� ������� ������ AgentProxy. ������� ������-
		������������� ������ ����������������� ��� ������������� �����������
		��������.

	\param wstrProductName [in] ��� ��������.
	\param wstrVersion [in] ������ ��������.
	\param proxy [out] ��������� �� ����������, � ������� ����� �������
		��������� �� ��������� ������.
*/

KLCSKCA_DECL void KLPRCP_CreateAgentProxy(
							const std::wstring&		wstrProductName,
							const std::wstring&		wstrVersion,
							KLPRCP::AgentProxy**	ppAgentProxy);

/*!
  \brief
	��������� ���������� ���������, ������������� � ���� ��� � ��������
	������������ ��������. ��������� ������ ������������ � �������
	ComponentInstanceStarted.
   
    \param id		[in/out] ������������� ���������� ��� �������.
    \param pParameters	[in] ��������� ��� ������ ����������.
    \param wstrAsyncId	[in] ���������� ������������� ��� ������������ 
								������� � ������ ����������.  ��� ��������
								���������� � ���� asyncId � ���� �������
								ComponentInstanceStarted.
	\param dwFlags		[in] ����� SCF_*: SCF_AUTOSTOP.
	\param lAsyncTimeout[in] ������ �������� ������������.
	\param lTimeoutStop	[in] ����� ����� ���������� ��������� � ����������
								����������, ����� ������� �� �������
								������� INSTANCE_TIMEOUTSTOP (���� �������
								����� KLSTD_INFINITE, �� �������), ��.
*/

KLCSKCA_DECL void KLPRCP_LoadInProcessComponent(
						KLPRCI::ComponentId&	id,
						KLPAR::Params*			pParameters,
						std::wstring			wstrAsyncId,
						AVP_dword				dwFlags,
						long					lAsyncTimeout,
						long					lTimeoutStop=KLSTD_INFINITE);


KLCSKCA_DECL bool KLPRCP_UnloadInProcessComponent(KLPRCI::ComponentId& id);

#endif // KLPRCP_AGENTPROXY_H
