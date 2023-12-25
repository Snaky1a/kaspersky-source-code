/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file ThreadsPool.h
 * \author ����� �����������
 * \date 2002
 * \brief ��������� ���� �������
 * 
 */

#ifndef KLTP_THREADSPOOL_H
#define KLTP_THREADSPOOL_H

#include "std/base/klbase.h"

namespace KLTP {	

    const int c_DefaultNumberOfPoolsThreads = 8;

/*!
 * \brief ��������� ���� �������
 * 
 */	
	class ThreadsPool  
	{
	public:

		typedef int WorkerId;

		/*\brief ������ "��������" ���� ������� */
		class Worker : public KLSTD::KLBase
		{
		public:
			virtual int RunWorker( WorkerId wId ) = 0;
		};

		/*\brief ���*/
		enum WorkerType {
			RunOnce,			//! ����� RunWorker ����� ������ ������ ���� ��� 
			RunNormal			//! ���������� ������. ������� ����� ���������� �� ��� ���
								// ���� �� ����� ������ ����� DeleteWorker. ������� 
								// ����� ���� ������������ �������� �� ��������� �������
		};
		
		/*\brief ���*/
		enum WorkerPriority {						
			PriorityLow,				//! ������ ��������� ���������� 									
					//! ( ��� ���������� ���������� �� ����� 20% ���� ������� ���� � ������� �� ����� 10 ������� )
			PriorityNormal			//! ���������� ��������� ���������� ������� 
		};

		/*\brief ������*/
		enum WorkerStatus {
			WaitStatus,
			RunStatus,
			RunInWaitingMode
		};

		virtual ~ThreadsPool() {}
		
		/*!
			\brief ������� ������������� ���� �������.
	
			\param maxNumberOfThreads [in] ������������ ���������� �������.
					���� ������ ��������� ����� 0 ������������ single thread ������.
		*/
        virtual void Init( int maxNumberOfThreads = c_DefaultNumberOfPoolsThreads ) = 0;

		/*!
			\brief ������������� ������ ���� �������
		*/
		virtual void Stop( ) = 0;

		/*!
			\brief ������� �������� ���������� ���� �������.
				
			� ������ ������ ������� ������������� ��������� ���� ������������������
			��������. ����� ������ ������� ������������ ����������� ������ � ����� 
			������� � ������������� ������.			

			����� ������ ������� �������� � ������������ ������ ���� 
			������������������ �������.
		*/
		virtual void DoProcessing( void *param, int threadNum ) = 0;

		/*!
			\brief ������� ���������� "��������" � ��� �������.

			����������� ��� ������ ������ ������� ������� ����� ����������
			������������ �� ���� ������� ����.
			
			����������� ������� ( RunWorker )  �� ������ ����������� �������� ������� 
			�� ������ ���������� ����������� ��������. ���� �� ������ ������ � 
			������� ��� ������ �� ����������, ������� ������ ���������� ������� ����������.

			\param workerName [in] ��� "��������"			
			\param worker [in] "�������"
			\param serializableRun [in] ���� true �� callback �� ����� ������ ������������
					�� ������ ������� ����
			\param periodTime [in] ������ ������� ������� ( � ������������ )
			\param wtype [in] ��� �������
			\return ������������� ����� ������� � ���� �������
		*/
		virtual void AddWorker( WorkerId *workerId, const wchar_t *workerName, 
			Worker *worker, WorkerType wtype = RunNormal,
			bool serializableRun = true, int periodTime = (-1) ) = 0;

		/*!
			\brief ������� ���������� ���������� "��������" � ��� �������.

			������ ��� "��������" ���� ���������� � ����� ����������.
			������������ ��� ����������� ������� ��������� "�������" ( �������� ������������ �
			"�������" ������� Eventing )
		*/
		virtual void AddWaitingWorker( WorkerId *workerId, const wchar_t *workerName, 
			Worker *worker, bool serializableRun = true, bool createThreadForWorker = false,
			bool runWorkerOnlyInCreatedThread = true ) = 0;

		/*!
			\brief ���������������� ������ ����������� �������.

			����� ������ �������, ���������������� ���������� ���������������,
			���������� �� ����� �� ������ ResumeWorker

			\param workerId [in] ������������� �������
			\return ��������� ��������. flase - � ����� ��������������� ������� ���
		*/
		virtual bool SuspendWorker( WorkerId workerId ) = 0;

		/*!
			\brief �������������� ������ ���������������� �������.

			\param workerId [in] ������������� �������
			\return ��������� ��������. flase - � ����� ��������������� ������� ���
		*/
		virtual bool ResumeWorker( WorkerId workerId ) = 0;

		/*!
			\brief ������� ������� ������� �� ���� �����

			������ ������� ������� ����� ����������� ������� �� ������ � ����������� 
			�������� ������� - context.
		
			\param workerId [in] ������������� �������
			\return ��������� ��������. flase - � ����� ��������������� ������� ���
		*/
		virtual bool DeleteWorker( WorkerId workerId ) = 0;

		/*!
			\brief ���������� ������� ������
		*/
		virtual bool GetWorkerInfo( WorkerId workerId, int &poolsThreadsNumber,
			WorkerStatus &status ) = 0;

		/*!
			\brief ������� �������� �������� ������ ���� � ��������� 'in use'

			\param workerId [in] ������������� �������
		*/
		virtual void SetWorkerState( WorkerId workerId, bool inUse ) = 0;

		/*
			\brief ���������� ���-�� ������� � ���� �������
		*/
		virtual int GetThreadsNumber() = 0;
		
		/*!
			\brief ������� ���������� "��������" � ��� �������.
		*/
		virtual void AddWorker2( WorkerId *workerId, const wchar_t *workerName, 
			Worker *worker, WorkerType wtype = RunNormal,
			bool serializableRun = true, int periodTime = (-1),
			WorkerPriority priority = PriorityNormal ) = 0;
		
	};

} // end namespace KLTP


/*
	\brief ������� ���������� ��������� �� ���������� ThreadsPool
*/
KLCSC_DECL KLTP::ThreadsPool *KLTP_GetThreadsPool();


#endif // !defined(KLTP_THREADSPOOL_H)
