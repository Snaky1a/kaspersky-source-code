/*!
 * (C) 2002 Kaspersky Lab 
 * 
 * \file	simp_comp.h
 * \author	Andrew Kazachkov
 * \date	10.10.2002 16:18:46
 * \brief	
 * 
 */

#ifndef _BASE_H__A7511925_019D_4f4a_B241_3515E33E4F1E
#define _BASE_H__A7511925_019D_4f4a_B241_3515E33E4F1E

#include <std/base/klstd.h>
#include <std/par/params.h>
#include <kca/prss/settingsstorage.h>
#include <kca/prci/componentinstance.h>

#include <map>

namespace SIMP_COMP
{
	/*!
		\brief	������� ����� ������ ����������.
	*/
	class KLSTD_NOVTABLE CTaskBase
	{
		friend class CTaskStorage;
	public:

		/*!
		  \brief	�����������

		  \param	pInstance		��������� ����������
		  \param	wstrTaskName	��� ������
		  \param	idTask			������������� ������
		*/
		CTaskBase(
				KLPRCI::ComponentInstance*	pInstance,
				const std::wstring			wstrTaskName,
				long						idTask,
				bool						bAutoImpersonate=true);

		virtual ~CTaskBase();
		/*!
		  \brief	���������� ���������� ��� �������� ������ ������ (����, �����, �������������, ...)
		  \param	action ������������� �������
		*/
		virtual void OnControl(KLPRCI::TaskAction action);
		/*!
		  \brief	���� ������ - ���������� � ��������� ���� (����������� � StartWorkingThread)
		  \return	��� ���������� ������, ������� ������ ����� ���������� ����
		*/
		virtual unsigned long Run()=0;
		
	protected:

		/*!
		  \brief	������ ����, � ������� ���������� ����� Run(). ������ ����� ����������
			������ CTaskStorage. � ������� ��������� ��� ���������������.
		*/
		virtual void StartWorkingThread();	

		/*!
		  \brief	��������� ����, � ������� ���������� ����� Run().
		*/
		static unsigned long KLSTD_THREADDECL threadproc(void *arpg);

		const std::wstring								m_wstrTaskName;
		const long										m_idTask;
		KLSTD::CAutoPtr<KLPRCI::ComponentInstance>		m_pInstance;
		KLSTD::CAutoPtr<KLPRCI::ProductTasksControl>	m_pTasksControl;
		std::auto_ptr<KLSTD::Thread>					m_pThread;
		KLSTD::CAutoPtr<KLPRCI::SecContext>				m_pClientSecurityContext;
		bool											m_bAutoImpersonate;
	public:
		volatile bool									m_bDone;
	};

	typedef std::map<long, CTaskBase*> tasks_t;

	/*!
		\brief	��������� �����.
	*/
	class CTaskStorage
	{
	public:		
		CTaskStorage();
		virtual ~CTaskStorage();
		

		/*!
		  \brief	���������� ��������� ��� ������������� ������� � ����������� m_mapTasks.
			������� ������ Lock() ������ ��������������� ����� Unlock(). ������������ ��������� 
			tasks_t* ������ ������������ ����� ������ ������ Unlock().
		  \return	��������� �� ����������� ��������������� ������ � ��������� �� ���� CTaskBase.
		*/
		tasks_t*	Lock();

		/*!
		  \brief	������������� ���������. 
		*/
		void		Unlock();

		/*!
		  \brief	���������� ������ � ���������

		  \param	������������� ������, ����������� � ���������.
		  \param	��������� �� CTaskBase* ������, ����������� � ���������.
		  \except	KLSTD::STDE_EXIST ������ � ��������������� idTask ��� ������� � ���������
		*/
		void		TaskNew(long idTask, CTaskBase* pTask);

     	void Clear();

	protected:
		KLSTD::CAutoPtr<KLSTD::CriticalSection>	m_pCS;
		tasks_t									m_mapTasks;
	};

	//! \brief ��������������� ����� ��� �������������� ������������� ��������� CTaskStorage.
	class AutoTaskStorage
	{
	public:
		AutoTaskStorage(CTaskStorage* pStorage, tasks_t* &tasks):
			m_pStorage(pStorage)
		{			
			tasks=pStorage->Lock();
		};
		virtual ~AutoTaskStorage()
		{
			m_pStorage->Unlock();
		};
	protected:
		CTaskStorage* m_pStorage;
	};


	//! \brief ������� ����� ������������ ����������
	class KLSTD_NOVTABLE CComponentBase
	{
	public:

		/*!
		  \brief	�����������

		  \param	idComponent ������������� ����������
		  \return	
		*/
		CComponentBase(const KLPRCI::ComponentId& idComponent);		
		virtual ~CComponentBase();
		;

		/*!
		  \brief	������������� CComponentBase, �������� ���������� ComponentInstance.
			��� ���������� ������������� ��������������� ������, ������������ m_pInstance,
			���������� ����������� ������ �����.
		*/
		virtual void Initialize();
		;

		/*!
		  \brief	���������� ���������� ��� �������� ������ ���������
		  \param	action �������
		*/
		virtual void OnInstanceControl(KLPRCI::InstanceAction action);

		/*!
		  \brief	���������� ���������� ��� �������� ������ �������. ����������
					�� ��������� ���������� � ���������, ���� ������ � ���������������
					taskId � �������� � callback

		  \param	taskId	������������� ������
		  \param	action	�������
		*/
		virtual void OnTasksControl(long taskId, KLPRCI::TaskAction action);


		/*!
		  \brief	���� ����������. ���������� �� ��������� �������� ����� ������.
			����� �� ������ �������� ���������� ������ ������. ����� �����������
			��� ���������� �������� m_pDoneSemaphore. ��� ������������� ������
			������������� ����������.

		  \return	��� ��������. ���������� �� ��������� ���������� 0.
		*/
		virtual unsigned long	Run();

		/*!
		  \brief	����� �������������� ������� m_pDoneSemaphore
		*/
		virtual void			Stop();


		/*!
		  \brief	���������� ����� ������� ������ ����� ��������� ������ � ������� taskName.
			���� ������ � ����� �������� �� ��������������, ������� ����������� ����������
			STDE_NOFUNC (������ KLSTD_NOTIMP() ).
			\param	taskName	��� ������
			\param	params		��������� ������
			\param	taskId		������������� ����������� ������
			\param	timeout		����-��� ������ ������.
		*/
		virtual void OnRunTasks(
						const std::wstring&		taskName,
						KLPAR::Params*			params,
						long					taskId,
						long					timeout)=0;
	protected:
		static void InstanceControlCallback(void* context, KLPRCI::InstanceAction action);

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

		const KLPRCI::ComponentId					m_idComponent;
		KLSTD::CAutoPtr<KLPRCI::ComponentInstance>	m_pInstance;
		KLSTD::CAutoPtr<KLSTD::Semaphore>			m_pDoneSemaphore;
		CTaskStorage								m_TaskStorage;
	};

};

#endif // _BASE_H__A7511925_019D_4f4a_B241_3515E33E4F1E
