/*!
* (C) 2002 "Kaspersky Lab"
*
* \file WorkingThread.cpp
* \author ����������� �����
* \date 2002
* \brief ���������� �������� ������ ����������
*
*/

#include "std/thr/sync.h"
#include "std/thr/thread.h"
#include "std/err/klerrors.h"

#include "workingthread.h"
#include "threadspoolmanager.h"

namespace KLTP {

	/*!
	* \brief ������� ����� ���������� 
	*/	

	const wchar_t c_WorkingThreadName[] = L"WorkingThread";

	const wchar_t KLCS_MODULENAME[] = L"KLTP";

	class WorkingThreadImp : public KLSTD::KLBaseImpl<WorkingThread>
	{
	public:

		WorkingThreadImp( int num, KLTP::ThreadsPool *threadsPool )
		{
			number = num;

			taskParams = NULL;
			taskThreadsPool = threadsPool;

			curState = WorkingThread::ThreadNotStarted;

			criticalSec = NULL;
			KLSTD_CreateCriticalSection( &criticalSec );						

			timeToDie = false;
			thread = NULL;
			manager = NULL;
			m_threadNumber = (-1);
			threadId = (-1);
			m_threadStopped = false;
		}

		~WorkingThreadImp()
		{
			timeToDie = true;			

			if ( thread!=NULL )
			{
				KLERR_BEGIN
					
					// ���� ��������� ������
					thread->Join();

				KLERR_ENDT(3)
			}

			criticalSec->Release();			

			if ( thread!=NULL ) delete thread;
		}

		//\brief ������� ���������� ������ ������
		void StartThread( ThreadsPoolManager *man )
		{
			if ( thread!=NULL ) return;

			manager = man;

			KLSTD_CreateThread( &thread );

			thread->Start( c_WorkingThreadName, ThreadStub, this );
		}

		//\brief ������� ���������� ������� ������ ( ��� �������� ��������� ������ ������ )
		void StopThread()
		{
			timeToDie = true;
		}

		//\brief ������� ���������� ����������� �� ������� �����
		bool IsStopped()
		{
			KLSTD::AutoCriticalSection autoUnlocker( criticalSec );

			if ( thread!=NULL )
			{
				return m_threadStopped;
			}
			else return true;
		}



		//\brief ��������� ������� ����� �� ���������� ������������ ������
		void NewTask( void *params )
		{
			KLSTD::AutoCriticalSection autoUnlocker( criticalSec );

			taskParams = params;

			curState = WorkingThread::Working;
			
		}

		//\brief ���������� ������� ��������� ������
		WorkingThread::ActionState GetCurrentState()
		{
			KLSTD::AutoCriticalSection autoUnlocker( criticalSec );

			return curState;
		}

		//\brief ������ ����� ��� ������� ������ ( �� ��������� ����� (-1) )
		void SetWorkingThreadNumber( int wNum )
		{
			KLSTD::AutoCriticalSection autoUnlocker( criticalSec );

			m_threadNumber = wNum;
		}

		//\brief ���������� ��������� ������
		void *GetParams()
		{
			KLSTD::AutoCriticalSection autoUnlocker( criticalSec );

			return taskParams;
		}

		//\brief ��������� �������� �� ������� �����, ������� WorkingThread
		bool IsCurrentThread()
		{
			KLSTD::AutoCriticalSection autoUnlocker( criticalSec );

			if ( threadId==(-1) ) return false;
			if ( threadId==KLSTD_GetCurrentThreadId() ) return true;

			return false;
		}

		//\brief ������� ������
		void Run( )
		{
			threadId = KLSTD_GetCurrentThreadId();

			while(1)
			{
				if ( timeToDie ) break;	// ����������� �����
				
				// ������������ ������������ ������
				if ( taskThreadsPool!=NULL )
					taskThreadsPool->DoProcessing( taskParams, m_threadNumber );
				else
				{
					// �������� ������� ��������� ������
					KLSTD::AutoCriticalSection autoUnlocker( criticalSec );

					taskParams = NULL;
					taskThreadsPool = NULL;

					curState = WorkingThread::Free;
					manager->FreeTask( this );
				}
			}

			
			m_threadStopped = true;
		}

		static unsigned long KLSTD_THREADDECL ThreadStub( void *argp )
		{
			((WorkingThreadImp *)argp)->Run();
			return 0;
		}

	private:

		KLSTD::CriticalSection *criticalSec;	//!< ��� ������� � ���������� ������
		
		void* taskParams;			//!< ��������� ������� ������
		KLTP::ThreadsPool *taskThreadsPool;	//!< ��� �������

		WorkingThread::ActionState  curState;			//!< ������� ��������� ������

		int			number;				//!< ����� ������ � ���� �������

		KLSTD::Thread *thread;			//!< �����
		int			   threadId;

		bool		timeToDie;			//!< ������� ���������� ������ ������

		ThreadsPoolManager *manager;	//!< �������� �������

		int			m_threadNumber;		//!< ����� ������
			
		bool		m_threadStopped;	//!< ����� ����������

	protected:

	};

} // end namespace KLTP

/*
	\breif ������� ������� ������ ������ WorkingThread
*/
void KLTP_CreateWorkingThread( KLTP::WorkingThread **workingThread, int threadNum,
								KLTP::ThreadsPool *threadPool )
{
	KLSTD_CHKOUTPTR(workingThread);

	*workingThread = new KLTP::WorkingThreadImp( threadNum, threadPool );

	KLSTD_CHKMEM(*workingThread);
}
