/*!
 * (C) 2002 Kaspersky Lab 
 * 
 * \file	cmpbase.h
 * \author	Andrew Kazachkov
 * \date	17.01.2003 12:12:11
 * \brief	
 * 
 */

#ifndef __KLCMPBASE_H__McbFFLi2d9afXFFbDHAg10
#define __KLCMPBASE_H__McbFFLi2d9afXFFbDHAg10

#include <std/tp/tpcmdqueue.h>
#include <std/thr/locks.h>
#include <std/base/klbaseqi_imp.h>
#include <kca/prci/componentinstance.h>
#include <map>

namespace KLBASECOMP
{

/*!
	\brief ��������� TaskBase
*/

	class KLSTD_NOVTABLE TaskBase
        :   public KLSTD::KLBaseQI
	{
	public:
		virtual const wchar_t* GetTaskName() = 0;
		/*!
		  \brief	OnControl

		  \param	KLPRCI::TaskAction action
		*/
		virtual void OnControl(KLPRCI::TaskAction action) = 0;

		/*!
		  \brief	OnExecute

		  \return	bool 
		*/
		virtual bool OnExecute() = 0;
	};

/*!
	\brief	
*/

	typedef enum
	{
		CMDID_NULL=0,
		CMDID_FINISH=1,
		CMDID_PING=2,
		CMDID_LAST=255
	}commandid_t;

	struct command_t
	{
		long							idCmd;	//	������������� �������
		long							nOption;//	����������� ���
		KLSTD::CAutoPtr<KLSTD::KLBase>	pData;	//	����������� ������        
	};

    struct command_ex_t : public command_t
    {
        command_t   cmd;
        bool        bSync;
    };

/*!
	\brief ��������� ComponentBaseCallbacks
*/
	
	class KLSTD_NOVTABLE ComponentBaseCallbacks
	{
	public:

		/*!
		  \brief	

		  \param	cmd [in]
		*/
		virtual bool OnCommand(command_t& cmd, bool bSync) = 0;
		/*!
		  \brief	������ ����� ���������� �� ������ Initialize ����� ��������
				���������� ComponentInstance. �� ������� �������� ����� �����
				���������������. ���� ����� ������� ����������� ��� ����������
				������������� ����������.				
				
				  � ������ ������������� ������ ������� ����������� ����������.
		*/
		virtual void OnInitialize() = 0;

		/*!
		  \brief	������ ����� ���������� �� ������ Deinitialize �����
				������������ ���������� ComponentInstance. ����� ����������
				������ � ��� ������, ���� ������� ��������� (�.� ��� ������ �
				�� �������� ����������) ����� OnInitialize. ���� ����� �������
				����������� ��� ���������� ��������������� ����������.
				
				  ����� �� ������ ����������� ����������.
		*/
		KLSTD_NOTHROW virtual void OnDeinitialize() throw() = 0;
		;

		/*!
		  \brief	���������� ���������� ��� �������� ������ ���������
		  \param	action �������
		*/
		virtual void OnInstanceControl(KLPRCI::InstanceAction action) = 0;

		/*!
		  \brief	���������� ���������� ��� �������� ������ �������.
					����������
					�� ��������� ���� ������ � ��������������� taskId �
					�������� � callback

		  \param	taskId	������������� ������
		  \param	action	�������
		*/
		virtual void OnTasksControl(long taskId, KLPRCI::TaskAction action) = 0;

		/*!
		  \brief	���������� ����� ������� ������ ����� ��������� ������ �
				������� taskName. ������� ��� ������� ������ ��� ���������
				����������.
					���� ������ � ����� �������� �� ��������������, �������
				����������� ���������� STDE_NOFUNC (������ KLSTD_NOTIMP()).

			\param	wstrTaskName[in]	��� ������
			\param	pTaskParams	[in]	��������� ������
			\param	idTask		[in]	������������� ����������� ������
			\param	lTimeout	[in]	����-��� ������ ������.
		*/
		virtual void OnRunTasks(
						const std::wstring&		wstrTaskName,
						KLPAR::Params*			pTaskParams,
						long					idTask,
						long					lTimeout)=0;


		virtual void OnSettingsChange(
						const std::wstring&	productName, 
						const std::wstring&	version,
						const std::wstring&	section, 
						const std::wstring&	parameterName,
						const KLPAR::Value*	oldValue,
						const KLPAR::Value*	newValue) = 0;
	};
/*!
	\brief ��������� ComponentBase
*/

	class KLSTD_NOVTABLE ComponentBase
	{
	public:
		/*!
		  \brief	������������� ComponentBase. ������ ������� ������
				��������, ���������� ComponentInstance � ���������� �����
				OnInitialize(), ������� ������� ����������� ��� ����������
				�������������.

		  \param	idComponent [in] ������������� ���������� ����������.
		  \param	bDllComponent [in] true, ���� ��������� � DLL
		  \param	pParams [in]
		  \param	pPorts  [in]
		*/
		virtual void Initialize(
					const KLPRCI::ComponentId&	idComponent,
					bool						bDllComponent,
					KLPAR::Params*				pParams,
					unsigned short*				pPorts=NULL,
                    const wchar_t*              szwAddress=KLPRCI::c_szAddrLocal) = 0 ;

		/*!
		  \brief	��������������� ComponentBase. ������������� ���������
				���������� STATE_SHUTTING_DOWN, ��������������� ����
				���������, ������������ �������, ������������ ��������
				���������� ���� �����, ���������� ����� OnDeinitialize,
				������������� ��������� ComponentInstance.
		*/
		virtual KLSTD_NOTHROW void Deinitialize() throw() = 0;

		/*!
		  \brief	������������� ���� ���������.
		*/
		virtual void SetStopFlag() = 0;

		/*!
		  \brief	���������� ���� ���������.
		*/
		virtual bool GetStopFlag() = 0;

		virtual bool IsShuttedDown() = 0;


		virtual KLPRCI::ComponentId get_ComponentId() = 0;

		virtual bool get_ComponentInstance(KLPRCI::ComponentInstance** ppInstance) = 0;

		virtual bool get_ProductTasksControl(KLPRCI::ProductTasksControl** ppTasksControl) = 0;

		virtual bool get_ProductStatistics(KLPRCI::ProductStatistics** ppStatistics) = 0;

		virtual bool get_ProductSettings(KLPRCI::ProductSettings** ppSettings) = 0;

		virtual bool SendCommand(command_t& cmd, bool bSync=false) = 0;

		virtual bool SendCommand(long idCmd, long nOption, KLSTD::KLBase* pData, bool bSync=false) = 0;
		
		virtual void LockTasksHost() = 0;

		virtual void UnlockTasksHost() = 0;

		virtual void LinkTask(long idTask, TaskBase* pTask) = 0;

		virtual bool UnlinkTask(long idTask) = 0;

		virtual void GetRunningTasks(std::vector<long>& vecTaskIds) = 0;

		virtual bool GetRunningTaskAt(long idTask, TaskBase** ppTask) = 0;
	};


/*!
	\brief ��������� 
*/

	class KLSTD_NOVTABLE ComponentBaseImp
		:	public ComponentBase
		,	public ComponentBaseCallbacks
		,	public KLTP::ThreadsPool::Worker
	{		
	public:
		ComponentBaseImp();
		virtual ~ComponentBaseImp();


	//���������� ComponentBase
		virtual void Initialize(
					const KLPRCI::ComponentId&	idComponent,
					bool						bDllComponent,
					KLPAR::Params*				pParams,
					unsigned short*				pPorts=NULL,
                    const wchar_t*              szwAddress=KLPRCI::c_szAddrLocal);

		KLSTD_NOTHROW void Deinitialize() throw();		
		void SetStopFlag();
		bool GetStopFlag();
		bool IsShuttedDown(){return m_bStopped;};
		KLPRCI::ComponentId get_ComponentId();
		bool get_ComponentInstance(KLPRCI::ComponentInstance** ppInstance);
		bool get_ProductTasksControl(KLPRCI::ProductTasksControl** ppTasksControl);
		bool get_ProductStatistics(KLPRCI::ProductStatistics** ppStatistics);
		bool get_ProductSettings(KLPRCI::ProductSettings** ppSettings);
		bool SendCommand(command_t& cmd, bool bSync=false);
		bool SendCommand(long idCmd, long nOption, KLSTD::KLBase* pData, bool bSync=false);
		;
		void LockTasksHost();
		void UnlockTasksHost();
		void LinkTask(long idTask, TaskBase* pTask);
		bool UnlinkTask(long idTask);
		void GetRunningTasks(std::vector<long>& vecTaskIds);
		bool GetRunningTaskAt(long idTask, TaskBase** ppTask);

	//���������� ComponentBaseCallbacks
	protected:
        void OnProcessCommand(command_ex_t& cmd);
		bool OnCommand(command_t& cmd, bool bSync);

		//!���������� �� ��������� ������ �� ������.
		void OnInitialize();

		//!���������� �� ��������� ������ �� ������.
		KLSTD_NOTHROW void OnDeinitialize() throw();

		/*!	���������� �� ��������� � ����� �� ������� INSTANCE_STOP ��������
			����� SetStopFlag()*/
		void OnInstanceControl(KLPRCI::InstanceAction action);

		//!���������� �� ��������� �������� ����� OnControl � ���������������� �������.
		void OnTasksControl(long taskId, KLPRCI::TaskAction action);

		//���������� �� ��������� ����������� ���������� STDE_NOFUNC
		void OnRunTasks(
						const std::wstring&		wstrTaskName,
						KLPAR::Params*			pTaskParams,
						long					idTask,
						long					lTimeout);

		//���������� �� ��������� ������ �� ������.
		void OnSettingsChange(
						const std::wstring&	productName, 
						const std::wstring&	version,
						const std::wstring&	section, 
						const std::wstring&	parameterName,
						const KLPAR::Value*	oldValue,
						const KLPAR::Value*	newValue);
	protected:
		KLSTD::CAutoPtr<KLPRCI::ComponentInstance>		m_pInstance;
		KLSTD::CAutoPtr<KLPRCI::ProductTasksControl>	m_pTasksControl;
		KLSTD::CAutoPtr<KLPRCI::ProductStatistics>		m_pStatistics;
		KLSTD::CAutoPtr<KLPRCI::ProductSettings>		m_pSettings;
		KLPRCI::ComponentId								m_idComponent;

	// ������� ComponentInstance
		static void InstanceControlCallback(
						void* context,
						KLPRCI::InstanceAction action);

		static void RunTasksCallback(
						void*					context,
						const std::wstring&		taskName,
						KLPAR::Params*			params,
						long					taskId,
						long					timeout);

		static void TasksControlCallback(
						void*				context,
						long				taskId,
						KLPRCI::TaskAction	action);

		static 	void SettingsChangeCallback(
						void*				context,
						const std::wstring&	productName, 
						const std::wstring&	version,
						const std::wstring&	section, 
						const std::wstring&	parameterName,
						const KLPAR::Value*	oldValue,
						const KLPAR::Value*	newValue );


	//���������� TasksHost
	//���������� KLTP::ThreadsPool
		int RunWorker(KLTP::ThreadsPool::WorkerId wId);
	//���������� 
	private:
	//���������� ������        
        typedef KLCMDQUEUE::CmdQueue<   command_ex_t, 
                                        command_ex_t&, 
                                        ComponentBaseImp > queue_t;
		typedef std::map<long, KLSTD::CAutoPtr<TaskBase> >	tasks_t;

        KLSTD::CPointer<KLSTD::ObjectLock>      m_pExtLock;
        KLSTD::CPointer<queue_t>                m_pQueue;
		tasks_t									m_Tasks;
		KLSTD::CAutoPtr<KLSTD::CriticalSection>	m_pDataCS, m_pCommandCS;
		volatile bool							m_bStopFlag, m_bStopped;
		volatile KLTP::ThreadsPool::WorkerId	m_idPingWorker;
		bool									m_bInitiaized;
	};

	class KLSTD_NOVTABLE TaskBaseBaseImp
		:	public TaskBase
        ,   public KLTP::ThreadsPool::Worker
    {
        ;
    };

	class KLSTD_NOVTABLE TaskBaseImp
		:	public TaskBaseBaseImp
	{
	protected:
		TaskBaseImp(bool bAutoImpersonate=true);
		virtual ~TaskBaseImp();
        KLSTD_INTERAFCE_MAP_BEGIN(KLBASECOMP::TaskBase)
        KLSTD_INTERAFCE_MAP_END()
		virtual void Initialize(long idTask, ComponentBase* pComponent);
		virtual int RunWorker(KLTP::ThreadsPool::WorkerId wId);
    protected:
        //overridables

        //do nothing by default
        virtual void OnInitialize();

        //do nothing by default
        virtual void OnDeinitialize();
	protected:		
		virtual void PreInitialize(long idTask, ComponentBase* pComponent);
		virtual void PostInitialize(long lTimeout=0);
		ComponentBase*									m_pComponent;
		KLSTD::CAutoPtr<KLPRCI::ComponentInstance>		m_pInstance;
		KLSTD::CAutoPtr<KLPRCI::ProductTasksControl>	m_pTasksControl;
		long											m_idTask;
	private:
		volatile KLTP::ThreadsPool::WorkerId			m_idMainWorker;		
		KLSTD::CAutoPtr<KLPRCI::SecContext>				m_pClientSecurityContext;
        const bool                                      m_bAutoImpersonate;
        bool											m_bHostLocked;
	};
    
    class KLSTD_NOVTABLE TaskBaseNoImpersonation : public TaskBaseImp
    {
    public:
        TaskBaseNoImpersonation()
            :   TaskBaseImp(false)
        {
            ;
        };
    };

};

#endif //__KLCMPBASE_H__McbFFLi2d9afXFFbDHAg10

// Local Variables:
// mode: C++
// End:


