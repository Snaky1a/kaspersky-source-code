/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file AGINST/AgentInstance.h
 * \author ����������� �����
 * \date 2002
 * \brief ��������� ���������� ������.
 *
 */

#ifndef KLAGINST_AGENTINSTANCE_H
#define KLAGINST_AGENTINSTANCE_H

#include <std/thr/locks.h>
#include <kca/prci/componentinstance.h>
#include <kca/prcp/agentproxy.h>
#include <transport/ev/eventsource.h>
#include <kca/prts/tasksstorage.h>
#include <kca/pres/eventsstorage.h>
#include <std/tmstg/timeoutstore.h>
#include <std/thr/locks.h>
#include <transport/tr/transport.h>

#include "./agent.h"

#include <soapH.h>

#include "agenterrors.h"


namespace KLAGINST {

    struct ScheduledTaskData : public KLSTD::RcClassImpl<KLSTD::KLBase>
	{
		KLPRCI::ComponentId				    m_idServer;
		KLPRCI::ComponentId				    m_idClient;
		std::wstring					    m_wsrTaskName;
		KLSTD::CAutoPtr<KLPAR::Params>	    m_pTaskParams;
		long							    m_lTimeout;
		std::wstring					    m_wstrUser;     //NOT IMPLEMENTED
		std::wstring					    m_wstrDomain;   //NOT IMPLEMENTED
		std::wstring					    m_wstrPassword; //NOT IMPLEMENTED
		std::wstring					    m_wstrUID;      //unique id for event recognition
        KLSTD::CAutoPtr<KLPRCI::SecContext> m_pContext;     //User's context
		std::wstring					    m_wstrTSID;     //Tasks storage task Id

        KLSTD::CAutoPtr<KLPAR::Params> Serialize();
	};

    typedef std::list< KLSTD::KLAdapt< KLSTD::CAutoPtr<ScheduledTaskData> > > schtskdata_t;

	class AginstAutoImpersonate
	{
	public:
		AginstAutoImpersonate(KLPRCI::SecContext* pContext/*, const char* file, int line*/)
			:	m_pContext(pContext)
		{
            if(m_pContext)
			    m_pContext->ThreadImpersonate();//botchery !!!

            /*
            try
            {
                if(m_pContext)
			        m_pContext->ThreadImpersonate();//botchery !!!
                ;
                wchar_t szUserName[256];
                unsigned long lUserName=256;
                GetUserNameW(szUserName, &lUserName);
                wchar_t szwBuffer[MAX_PATH*2]=L"";
                swprintf(szwBuffer, L"User: %ls\r\n"
                                    L"file: %hs\r\n"
                                    L"line: %u\r\n"
                                    L"pContext: 0x%X",
                                    szUserName,
                                    file,
                                    line,
                                    (void*)pContext);
                MessageBoxW(NULL,szwBuffer,L"",0x00200000L);
            }catch(KLERR::Error* pError)
            {
                MessageBoxW(NULL,pError->GetMsg(),L"",0x00200000L);
                pError->Release();
            };
            */            
		};

		~AginstAutoImpersonate()
		{
			if(m_pContext)
			    m_pContext->ThreadRevert(false);
		};
	protected:
		KLSTD::CAutoPtr<KLPRCI::SecContext>	m_pContext;
	};

    //#define KLAGINST_IMPERSONATE(_context)  KLAGINST::AginstAutoImpersonate _ai(_context, __FILE__, __LINE__)
    #define KLAGINST_IMPERSONATE(_context)  KLAGINST::AginstAutoImpersonate _ai(_context)

	/*!
    * \brief ������� ��������� ������ Agent Instance (AGINST).
    */

	const int c_AgentInstanceConnectTimeout = 500; // 0,5 sec

	const int	  c_MaxNumberOfAgentTasksThread			= 2;

	class AgentInstance: public KLPRCI::ComponentInstance
	{
	public:	
        //<-- Changed by andkaz 26.08.2003 17:14:54
        KLSTD_NOTHROW virtual long IsStopRequested() = 0;
        //-->
        /*
#ifdef KLSTD_WINNT
		virtual void AllocSecurityContext(long lTimeout, std::wstring& wstrId) = 0;
		virtual void CallContext(const std::wstring& wstrId, void* pData, int nData, KLSTD::MemoryChunk** ppChunk) = 0;
		virtual void ReleaseSecurityContext(const std::wstring& wstrId) = 0;
#endif
        */
		//<-- Changed by andkaz 03.04.2003 16:40:20

		KLSTD_NOTHROW virtual void Publish_StartTaskStorageTaskResult(
									const std::wstring&			wstrUID,
									const KLPRCI::ComponentId&	id,
									const std::wstring&			wstrTaskname,
									long						lTaskId) throw() = 0;

		KLSTD_NOTHROW virtual void Publish_StartTaskStorageTaskResult(
									const std::wstring&	wstrUID,
									KLERR::Error*	pError)throw() = 0;

		KLSTD_NOTHROW virtual void Publish_StartTaskStorageTaskResult(
									const std::wstring&		wstrUID,
									KLPAR::Params*			pBody)throw() = 0;

		virtual void StartTaskStorageTask(
									const std::wstring& wstrTaskId,
									const std::wstring& wstrUID,
									long				lTimeout,
									KLPRCI::SecContext* pSecContext,
									bool groupTaskFlag = false )= 0;
		// -->
		virtual void StartComponentTask(
                                    KLSTD::CAutoPtr<ScheduledTaskData> pData) = 0;

		virtual bool RunTasksThroughBL() = 0;

		virtual void StartComponentEx(
						KLPRCI::ComponentId		id,
						KLPRCI::ComponentId		statingCompId,
						KLPAR::Params*			pStartParams,
						const wchar_t*			szwAsyncId,
						AVP_dword				dwFlags,
						long					lTimeoutStop,
						AVP_dword				dwLogonType,
						const wchar_t*			szwUser,
						const wchar_t*			szwDomain,
						const wchar_t*			szwPassword,
                        KLPRCI::SecContext*     pContext
						/*KLTMSG::TimeoutObject*	pItem*/) = 0;

		//!\brief ������� ��������� ������� ����������
		virtual int TransportStatusCallback(
								KLTRAP::Transport::ConnectionStatus status, 
                                KLPRCI::ComponentId& remoteComponentName,
                                KLPRCI::ComponentId& localComponentName,
								bool remoteConnFlag ) = 0;

		
		virtual void GetComponentId(KLPRCI::ComponentId &componentId) = 0;

	/*!
      \brief ���������� ������������� ����������.

      ������������� ���������� �������� ���������� ��� ���� ����������� ������
      � ���� �� ����, ������������� ������ � ���� �� ��������. �������������
      ���������� ������ ������ ����.
      \param wstrID [out] ������������� ����������.
 
    */

        virtual void GetInstanceId(std::wstring& wstrID) const  = 0;


    /*!
      \brief ���������� �����, � ������� �������� ����� ������
                ���������� ������ ����������������� � ����� ���������� ������.

      \return ������������ ����� ���������� � ���������� ������ (msec).
 
    */

        virtual long GetPingTimeout() const  = 0;


    /*!
      \brief ������� ���������� ������� ����������������� � ����� ���������� ������.

    */

        virtual void Ping() const  = 0;


    /*!
      \brief ���������� ������� ��������� ������.

      \return ��������� ������.
 
    */

        virtual KLPRCI::ComponentInstanceState GetState() const  = 0;


    /*!
      \brief ������������� ������� ��������� ������.

      \param state [in] ������� ��������� ������.
 
    */

        virtual void SetState(KLPRCI::ComponentInstanceState state)  = 0;




    /*!
      \brief ���������� ������ ������ ProductSettings ��� ��������� �������� ������.

       \param settings [out] ��������� ������.

    */

        virtual void GetSettings(KLPRCI::ProductSettings** ppSettings) = 0;

    /*!
      \brief ���������� ������ ������ ProductTasksControl, ������������ ��� 
            ���������� ����������� ���������������� �����.

       \param tasks [out] ������ ��� ������ � ����������������� ��������.

    */

        virtual void GetTasksControl(KLPRCI::ProductTasksControl** ppTasks) = 0;

    /*!
      \brief ���������� ������ ������ ProductStatistics, ������������ ���
            �������������� ����������� ���������� ����� ������.

       \param statistics [out] ������ ��� �������������� ����������� ���������� ������.

    */

       virtual void GetStatistics(KLPRCI::ProductStatistics** ppStatistics) = 0;

    /*!
		\brief ������������� callback-������� ��� ��������.

        \param callback        [in]  Callback - ������� ��� ��������.
	*/
       virtual void	SetInstanceControlCallback(
						void*					context,
                        KLPRCI::InstanceControlCallback	callback)  = 0;

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
      \brief ��������� ��������� ��������.  
      
        ����� �����������. ��������� ������ ������������ � ������� 
        ComponentInstanceStarted.  ������������� ����� ������������
        ���������� ���������� ���� ������, ���������� ����� StartComponent,
        ���� ������� ����������������� (����� �����������������). 
       
        \param id      [in]  ������������� ���������� ��� �������.
		\param startingId [in] ������������� ����������, ������� ���������� ������ ����� ����������
		\param asyncId [in]  ������������� ������������ ������.

        \return  ������������� ���������� ����� ����������. 

    */
		virtual void StartComponent( const KLPRCI::ComponentId & id, KLPAR::Params *startingParams, 
			const KLPRCI::ComponentId & startingId, 
			const std::wstring asyncId, bool phisycalStart )  = 0;

    /*!
      \brief ���������� ������ ���������� ���������.

	   \param filter [in] ������ ��� ���������� �������
       \param componentsList [out]  ������ ���������� ���������.
    */
        virtual void GetStartedComponentsList ( const KLPRCI::ComponentId &filter,			 
			std::list<KLPRCI::ComponentId> &componentsList )  = 0;

    /*!
      \brief ���������, ������� �� ������ ���������.
       
        \param id      [in]  ������������� ����������.

    */
        virtual bool IsComponentStarted( 
                        const KLPRCI::ComponentId & id)  = 0;

       
	/*!
	  \brief ������� ���������� ��������� ��� ������� ����������.

	  \param componentId [in] ������������� ����������
	  \param startParams [out] ��������� �������
	*/
		virtual void GetComponentStartParameters( const KLPRCI::ComponentId &compId,
			KLPAR::Params **startParams ) = 0;

        virtual void StopAginst() =0 ;

	/*!
	  \brief ���������������� ������ scheduler'� ������	  
	*/
		virtual void SuspendScheduler() = 0;

	/*!
	  \brief ��������� scheduler'� ������	  
	*/
		virtual void StartScheduler( bool enableStartScheduledTasks = true ) = 0;
	
	/*!
	  \brief ������� ���������� �� ������ ������� ������ �� TS
	*/
		KLSTD_NOTHROW virtual void Publish_TaskStateFailure( const std::wstring & wstrTSTaskId,
			KLSTD::CAutoPtr<KLERR::Error> pError) = 0;
	};

} // end namespace KLAGINST

/*!
    \brief ����� ��� �������� ������� ������ AgentInstance.
*/
KLCSA_DECL void KLAGINST_CreateAgentInstance( const KLPRCI::ComponentId & agentComponentId,
											const std::wstring &taskStorageLoc,
											KLAGINST::AgentInstance ** agentInst,
											unsigned short* pDesirablePorts=NULL,
											bool checkDialupFlag = true,
											bool startSchedulerByAppStartEvent = false,
                                            KLSTD::LockCount*  pDeinitLock = NULL,
                                            AVP_dword       dwOptions = 0);

/*!
	\brief ���������� ��������� �� ���������� ������ ������ AgentInstance.
*/
void KLCSA_DECL KLAGINST_GetAgentInstance(
                        const wchar_t*         szwProduct,
                        const wchar_t*         szwVersion,
                        KLAGINST::AgentInstance**   ppAginst);

void KLCSA_DECL KLAGINST_SetAgentInstance(
                        const wchar_t*         szwProduct,
                        const wchar_t*         szwVersion,
                        KLAGINST::AgentInstance* pAginst);

KLCSA_DECL void KLAGINST_WaitForModuleRelease();

#endif // KLAGINST_AGENTINSTANCE_H
