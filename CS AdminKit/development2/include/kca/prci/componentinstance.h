/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file PRCI/ComponentInstance.h
 * \author ������ ��������
 * \date 2002
 * \brief ������� ��������� ������ Product Component Instance (PRCI).
 *
 */

#ifndef KLPRCI_COMPONENTINSTANCE_H
#define KLPRCI_COMPONENTINSTANCE_H

#include <string>

#include "std/base/kldefs.h"
#include "std/err/error.h"
#include "std/par/params.h"

#include "componentid.h"
#include "kca/prci/prci_const.h"
#include "kca/prci/productsettings.h"
#include "producttaskscontrol.h"
#include "productstatistics.h"

namespace KLPRCI
{
		//const wchar_t c_ComponentProcessEnvironmentFormatStr[] = L"componentId=";	
	// ��� ���������� ���������, � ������� ��������� componentId
	const wchar_t c_szwEnvComponentIdName[]=L"KLCOMPONENTID_F55AB293C1A7494D90268A7F20BA5D15";
	const wchar_t c_szwEnvAsyncIdName[]=L"KLASYNCID_23494E258D2641A9A867CD6084B62C8D";

	/*!
		\brief ��������� ����������� DLL.
		DLL ������������������ � ������ MSF_CANBESTARTED ������ ��������������
		������� KLPRCIDLLCMP_INIT � KLPRCIDLLCMP_DEINIT (��. ����). 
        
        ����� ���� ������� ������������ � ��������� ��������, �.�. ������������ 
        �� ����� ��� ���� ���� ����� ��������� ������ ����� �� ���� �������.
        �� ������� KLPRCIDLLCMP_INIT, KLPRCIDLLCMP_DEINIT ������ ���������
        ������ ����������, ��� ����� ��������� � ����������� ��� ������������.

	*/

	/*!
		\brief �������������  ����������. ������ ���, ����� ������������� �����
		���������� ������������ � DLL, ���������� ������ ������� �
		��������������� ������������ ����������. ��������� componentId �
		startingParams ������������� ��� ���������� �������� � �������
		KLPRCI_CreateDllComponentInstance.
			������ InitComponent ��������� ������ ��������������������� �
		����� �� ������� ����������.
        
        ������ ������� ������ ��������� ������ ����������!

		EXTERN_C __declspec(dllexport)
			void KLPRCIDLLCMP_INIT(
								KLPRCI::ComponentId&	componentId,
								KLPAR::Params*			startingParams,
								KLERR::Error**			error)
		{			
			//��������� �����-���� ��������
			//.............................
		};

      \param	componentId [in/out] 
	  \param	startingParams [in] 
	  \param	error [out] 

	*/

	#define KLPRCIDLLCMP_INIT			KLPRCI_InitComponent
	
	typedef void (*InitComponent)(
						KLPRCI::ComponentId&	componentId,
						KLPAR::Params*			startingParams,
						KLERR::Error**			error);



	/*!
		\brief ��������������� ����������.
		������� ������ ������� ���������� ������ �� ����������
		��������������� ���������� ���������� componentId, �.�. ���������������
		�� ������� ������ ������� ������� ����� FreeLibrary.
        
        ������ ������� ������ ��������� ������ ����������!

	EXTERN_C __declspec(dllexport)
		void KLPRCIDLLCMP_DEINIT(const KLPRCI::ComponentId&	componentId)
		{			
			//��������� �����-���� ��������
			//.............................
		};
	
	*/

	#define KLPRCIDLLCMP_DEINIT			KLPRCI_DeinitComponent

	typedef void (*DeinitComponent)(
						const KLPRCI::ComponentId&	componentId);



    //! ��������� ��������� ����������. 
    enum ComponentInstanceState {		

        /*! ��������� �� �������.
		*/
		STATE_INACTIVE,

		/*! ��������� ������ ��� �������. � ���������� ��� ������� �����.
			������������ ������������� ��� ������������ ComponentInstance.
			������ ��������� �� ������� ������������� ���������������. 
		*/
        STATE_CREATED,

		/*! ��������� ����������������. ����� ��������� ������� ���������
			��������� ���������� �������� ����� (����� ������ ��������).
		*/
        STATE_INITIALIZING,  

		/*! ��������� �������� ������������� � ����� � ���������� �����.
			������� ����� ���� ������� ������ ����� ��������� ������� ���������.
		*/
        STATE_RUNNING,

		/*! ��������� ������������ ���� ������.
		*/
        STATE_SUSPENDING,

		/*!
			��������� ����� ���������������.  ��������� ������� ���������
			�����, �� ������� ������� ���� �� �����.
		*/
		STATE_DEINITIALIZING,

		/*!
			��������� ��������� ������ � ����������. ����� ��������� �������
			��������� ��������� �������� ���� ��������� �����.
		*/
        STATE_FAILURE,

		/*!
			��������� ���������� ���� ������. ����� ��������� �������
			��������� ��������� �������� ���� ��������� �����.
		*/
        STATE_SHUTTING_DOWN,

		/*!
			��������� ���������. ������������ ������������� ��� ��������
			ComponentInstance. ������ ��������� �� ������� �������������
			���������������.
		*/
		STATE_DESTROYED
    };

    enum InstanceAction{
		/*!
			���������� ����������.
		*/
        INSTANCE_STOP,

		/*!
			������������� ����������
		*/
        INSTANCE_SUSPEND,

		/*!
			����������� ����������
		*/
        INSTANCE_RESUME,

		/*
			�� �������� �� ����� ���������� ������ � �� ����� ������ ��
			���������.
		*/
		INSTANCE_AUTOSTOP,

		/*
			����� ������� ������������.
		*/
		INSTANCE_TIMEOUTSTOP
    };


    typedef void (*InstanceControlCallback)(
					void*			context,
					InstanceAction	action);


    /*!
    * \brief ������� ��������� ������ Product Component Instance (PRCI).
    *  
    *  ������ ��������� �������� ������ ����� ��� ������� ����������������� ���������
    *  �������� "����������� �����������".  ����������� ������-���� ���������� ��������
    *  ����� �������� �������� ���������������� ������� ����������������� ������� � �����
    *  ����������.
    *
    *  ����������� �������� �������� ���� ����������� ����, ���� ������������ ����������.
    *  ���������� ��������� (component instance) �������� ����������� �������� ���������
    *  ��� ������� �����������������.
    *
    *  ��� �������������� ������������� ���������� ���������� ���������� ������ �������
    *  ������ ������ ComponentInstance ������� ������������ ��������� �������� � �������
    *  �����������������.  ���������� ��������� �������� ������ ����� ��� ���������� 
    *  ����������������� � ��� ���������������� ������� ����������������� ���������� �
    *  �������������� ����� ����������.
    *
    *  ���������� ���������������� ������ �������� �� ����� ����������.  �����������
    *  ��������� ��������� ����� ������ � ���� �� ����������, � ���� ������ ����������
    *  ���������������� �� ���������� InstanceId, �������� ������� ��������� ��� 
    *  ����������� ������ � ���� �� ���� � ������ ������ ��������.
    *
    *  
    *
    */
    
    /*
        ������ �������� ComponentInstance ��������� ��������� ��������.
        1. ����� ������� ComponentInstance::SetInstanceControlCallback,
           ProductTasksControl::SetRunTasksCallback,
           ProductTasksControl::SetTasksControlCallback,
           ProductTasksControl::CallRunTasksCallback,
           ProductSettings::SubscribeOnSettingsChange,
           ProductSettings::CancelSettingsChangeSubscription.
        2. �������� ������ � ����� ����� ������� ComponentProxy � AgentProxy.
        3. ��������� � SettingsStorage, EventStorage � TasksStorage
    */

    class KLSTD_NOVTABLE ComponentInstance: public KLSTD::KLBaseQI
	{
    public:


	/*!
	  \brief	���������� ������������� ����������.

	  \param	componentId [out] ������������� ����������
	*/
		virtual void GetComponentId(KLPRCI::ComponentId &componentId) = 0;
    /*!
      \brief	���������� ��������� ������� ���������� ����������.
				���� ��������� ��� ������� �������, �� ��������� Params, ������ � ����������� ������,
				����� ��������� ���������� KLPRCI::c_WasStartedByAgent. � ��������� ������ ��� �����
				������ ���������.
      \param	ppParams [out] ��������� ������� ���������� ����������.
				������� ��������� � ������ ��������� ������.

    */
		virtual void GetStartParameters(KLPAR::Params** ppParams)=0;

    /*!
      \brief ���������� ������������� ����������.

      ������������� ���������� �������� ���������� ��� ���� ����������� ������
      � ���� �� ����, ������������� ������ � ���� �� ��������. �������������
      ���������� ������ ������ ����.
      \param wstrID [out] ������������� ����������.
 
    */

        virtual void GetInstanceId(std::wstring& wstrID) const  = 0;


    /*!
      \brief ���������� �����, � ������� �������� ���������� ��������� ������
                ���������� ������ ����������������� � ����� ���������� ������.

      \return   ������������ ����� ���������� � ���������� ������ (msec) ���
                KLSTD_INFINITE, ���� ��������� �� ���������� ����������.
      
      \exception ������ ����� �� ����������� ����������.
 
    */
        virtual long GetPingTimeout() const  = 0;


    /*!
      \brief ������� ���������� ������ ����������������� � ����� ���������� ������.

    */

        virtual void Ping() const  = 0;


    /*!
      \brief ���������� ������� ��������� ����������.

      \return ��������� ����������.
 
    */

        virtual ComponentInstanceState GetState() const  = 0;


    /*!
      \brief ������������� ������� ��������� ����������.

      \param state [in] ������� ��������� ����������.
 
    */

        virtual void SetState(ComponentInstanceState state)  = 0;




    /*!
      \brief ���������� ������ ������ ProductSettings ��� ��������� �������� ����������.

       \param settings [out] ��������� ����������.

    */

        virtual void GetSettings(KLPRCI::ProductSettings** ppSettings) = 0;

    /*!
      \brief ���������� ������ ������ ProductTasksControl, ������������ ��� 
            ���������� ����������� ���������������� �����.

       \param ppTasks [out] ������ ��� ������ � ����������������� ��������.

    */

        virtual void GetTasksControl(KLPRCI::ProductTasksControl** ppTasks) = 0;

    /*!
      \brief ���������� ������ ������ ProductStatistics, ������������ ���
            �������������� ����������� ���������� ����� ������.

       \param ppStatistics [out] ������ ��� �������������� ����������� ���������� ������.

    */

       virtual void GetStatistics(KLPRCI::ProductStatistics** ppStatistics) = 0;

    /*!
		\brief ������������� callback-������� ��� ��������.

        \param context   [in] ������, ������������ � Callback - �������
		\param callback  [in]  Callback - ������� ��� ��������.
	*/
       virtual void	SetInstanceControlCallback(
						void*					context,
                        InstanceControlCallback	callback)  = 0;

	/*!
		\brief ������� ��������� ������� �������� �� ������ ��� �������.

		\param eventType        [in]  ��� �������.
        \param eventBody        [in]  ��������� ��������� �������.
		\return true - ���� �� ������ ��� ������� ���� ��������
	*/
	   virtual bool CheckEventsSubscription( 
						const std::wstring &eventType, 
						KLPAR::Params * eventBody = NULL ) = 0;

    /*!
		\brief ������� ��� ���������� �������.

        \param eventType        [in]  ��� ������� ��� ����������.
        \param eventBody        [in]  ��������� �������.
        \param lifetime         [in]  ����� ����� ������� (msec).
	*/
		virtual void Publish(
				const std::wstring&	eventType, 
				KLPAR::Params*		eventBody,
				long				lifetime) = 0;



		/*!
		  \brief	���������� �������� ����������. 
			����� ������� ������ �������� � ������������ ������ �������
			KLPRCIDLLCMP_DEINIT � �������� ����������. ����� ������� ������
			����� ���������, ��������, ������ ������� InstanceControlCallback,
			� ����� �� ������� INSTANCE_STOP.
			
			������ ����� �� ����� �������, ���� ��������� �� �������� � DLL.
			����� �� ����������� ����������.
		*/
		KLSTD_NOTHROW virtual void InitiateUnload() throw() = 0;
        
        KLSTD_NOTHROW virtual std::wstring GetLocation() throw() =0;


        /*!
          \brief	Method set state STATE_SHUTTING_DOWN and destroys 
                    ComponentInstance object.
                    \param bSuccess 
        */
        KLSTD_NOTHROW virtual void Close(bool bSuccess) throw() = 0;
        
    };
	
	//! �������� ������������
    class KLSTD_NOVTABLE SecContext : public KLSTD::KLBase
	{
	public:
		virtual bool ThreadImpersonate(bool bThrowException=true) = 0;
		virtual bool ThreadRevert(bool bThrowException=false) = 0;
	};
};


/*!
  \brief	������ ������� ������� �������� � �������� ��� ��������� ���������
            ������������, ��������������� ����� �������.

  \param	ppContext ��������� �� ����������, � ������� ����� ������� ���������
            �� ���������. 
  \return   ���������� true � ������ ������ � false � ������ �������.
  \exception ������� �� ����������� ����������.
*/
KLCSKCA_DECL bool KLPRCI_GetClientContext(KLPRCI::SecContext** ppContext);

namespace KLPRCI
{
	class AutoImpersonate
	{
	public:
		AutoImpersonate(KLPRCI::SecContext* pContext, bool bThrowIfFailed=true)
			:	m_pContext(pContext)
		{
			KLSTD_ASSERT(m_pContext);
			m_pContext->ThreadImpersonate(bThrowIfFailed);
		};

		~AutoImpersonate()
		{
			KLSTD_ASSERT(m_pContext);
			m_pContext->ThreadRevert(false);//< Cannot throw exception from destructor
		};
	protected:
		KLSTD::CAutoPtr<KLPRCI::SecContext>	m_pContext;
	};
};
/*!
    \brief ����� ��� �������� ������� ������ ComponentInstance.

    ������� ������-������������� ���������� ��� ������� �����������������.
    ������ ������ ������ ������� ������������� ����� ������������ ���������� 
    (���� componentId.instanceId) � ������� ������� KLPRCI_CreateInstanceId.

        \param componentId      [in]  ������������� ���������� ��� �������
                                        �����������������. 
		\param component		[out] ��������� �� ����� ��������� ������.
        \param pDesirablePorts  [in]  ������������ ���� ������ ����������� ��� �������������
										������ TCP/IP. ���� NULL, �� ���� ����� �����������
										�������������. ���� ��� �������� ����� �������� ��������,
										����� ����� ����������� ��������� ������������� ����.
		\param	szwAddress		[in] �����. ����� ��������� ��������� ��������:
            ���� NULL, ������ ������ ��� KLPRCI:: c_szAddrLocal -- ��������� �������� ������ ��������
            KLPRCI::c_szAddrAny - ��������� �������� ��� ��������, ��� � �� ����

		\exception	ERR_INSTNAME_EXISTS ��������� ���������� � ����� InstanceId ��� ����������.

*/
KLCSKCA_DECL void KLPRCI_CreateComponentInstance(
                    const KLPRCI::ComponentId&	componentId,
					KLPRCI::ComponentInstance**	component,
					unsigned short*				pDesirablePorts=NULL,
					const wchar_t*				szwAddress = NULL);

KLCSKCA_DECL void KLPRCI_CreateComponentInstance2(
                    const KLPRCI::ComponentId&	componentId,
                    const wchar_t*				szwAsyncId,
					KLPRCI::ComponentInstance**	component);


/*!
    \brief ����� ��� �������� ������� ������ ComponentInstance.

    ������� ������-������������� ���������� ��� ������� �����������������.

        \param componentId      [in]  ������������� ���������� ��� �������
                                        �����������������. 
		\param pParams		    [in]  ��������� ����������, ���������� �
									������� KLPRCIDLLCMP_INIT
		\param component		[out] ��������� �� ����� ��������� ������.
        \param pDesirablePorts  [in]  ������������ ���� ������ ����������� ��� �������������
										������ TCP/IP. ���� NULL, �� ���� ����� �����������
										�������������. ���� ��� �������� ����� �������� ��������,
										����� ����� ����������� ��������� ������������� ����.
		\param	szwAddress		[in] �����. ����� ��������� ��������� ��������:
            ���� NULL, ������ ������ ��� KLPRCI:: c_szAddrLocal -- ��������� �������� ������ ��������
            KLPRCI::c_szAddrAny - ��������� �������� ��� ��������, ��� � �� ����

		\exception	ERR_INSTNAME_EXISTS ��������� ���������� � ����� InstanceId ��� ����������.

*/
KLCSKCA_DECL void KLPRCI_CreateDllComponentInstance(
										const KLPRCI::ComponentId&	componentId,
										KLPAR::Params*				pParams,
										KLPRCI::ComponentInstance**	component,
										unsigned short*				pDesirablePorts=NULL,
										const wchar_t*				szwAddress = NULL);

/*!
    \brief ���������� ������������� ���������� ����������.

	������������� ���������� ���������� ������������ ����� ���������� ������,
		���������� ���������������� ��������� �� ���� ���� �����������.

	\param wstrWellKnownName [in] "Well-known name" ����������. ����������,
				���������� � ����� ���������� ����� "Well-known name", ��������,
				"Well-known name" ������ -- KLPRCI_WELLKNOWN_AGENT. ���� ���������
				�� ����� "Well-known name", szwWellKnownName ������ ���� ����� NULL.
	\return ������������� ���������� ����������
*/

KLCSKCA_DECL std::wstring KLPRCI_CreateInstanceId(const wchar_t* szwWellKnownName);


/*!
  \brief	KLPRCI_CreateRemoteInstanceId

  \param	szwRemoteHost DNS-��� ��������� �����.
  \param	szwWellKnownName ��. KLPRCI_CreateComponentInstance
*/
KLCSKCA_DECL std::wstring KLPRCI_CreateRemoteInstanceId(
									  const wchar_t* szwRemoteHost,
									  const wchar_t* szwWellKnownName);

/*!
  \brief ���������� ������������ ��� ������� �������� componentId

  �omponentId ���������� ����������� �������� ��������� environment ��������. �������������
  ���������� ���������� ������ � ������ ������� �������� ������� �����������������.

  \param	[out] �componentIt ������������� ���������

  \return false - ��� ������� ������� ������� ������������� ���������� �� ��� ������
*/
KLCSKCA_DECL bool KLPRCI_GetStartedProcessComponentId( KLPRCI::ComponentId &componentId );

//KLCSKCA_DECL std::string GetHostDnsName();


/*!
  \brief	Sets behaviour for case when module with absent/mismatched
            signature is attempted to be loaded.

  \param	bFailIfMismatched - fails to load such modules if true
*/
KLCSKCA_DECL void KLPRCI_SetSignCheckMode(bool bFailIfMismatched);

/*!
  \brief	Checks for module signature

  \param	hModule - HMODULE
*/
KLCSKCA_DECL void KLPRCI_CheckModuleSignature(void* hModule);


/*!
  \brief	KLPRCI_GetModuleSignCheckStatus

  \return	true if there is at least one module with absent/mismatched signature
*/
KLCSKCA_DECL bool KLPRCI_GetModuleSignatureMisMatch();

#endif // KLPRCI_COMPONENTINSTANCE_H

// Local Variables:
// mode: C++
// End:
