/*!
* (C) 2002 "Kaspersky Lab"
*
* \file ThreadsPoolManager.cpp
* \author ����������� �����
* \date 2002
* \brief ���������� ��������� ������� ������� ����������
*
*/

#ifdef _WIN32
#pragma warning ( disable : 4786 ) // disable 'identifier was truncated to '255' characters in the debug information' warrning
#endif

#include <list>

#include "std/tp/threadspool.h"
#include "std/err/klerrors.h"
#include "threadspoolmanager.h"
#include "workingthread.h"

namespace KLTP {

	 class ThreadsPoolManagerImp : public KLSTD::KLBaseImpl<ThreadsPoolManager>
	 {
	 public:

		ThreadsPoolManagerImp()
		{
			criticalSec = NULL;
			KLSTD_CreateCriticalSection( &criticalSec );
			freeThrSem = NULL;
		}

		~ThreadsPoolManagerImp()
		{
			Stop();
		}


		void Stop()
		{
			ThreadsList::iterator it = threadsList.begin();

			while( it!=threadsList.end() )
			{
				// ��������� ��� ������� ������
				(*it)->Release();
				it = threadsList.erase(it);
			}

			it = stopingThreadsList.begin();
			while( it!=stopingThreadsList.end() )
			{				
				(*it)->Release();
				it = stopingThreadsList.erase(it);
			}

			freeThrSem->Release();
			criticalSec->Release();
		}

		//\brief �������������� ��������� �������
		void Init( int maxThrds, KLTP::ThreadsPool *threadPool )
		{
			if ( freeThrSem != NULL ) return;

			KLSTD::AutoCriticalSection autoUnlocker( criticalSec );

			if ( maxThrds<=0 ) maxThrds = c_DefualtMaxNumberOfThreads;

			for ( int tc = 0; tc < maxThrds; tc++ )
			{
				WorkingThread *wrkThrd = NULL;
				KLTP_CreateWorkingThread( &wrkThrd, tc, threadPool );
				threadsList.push_back( wrkThrd );
			}

			m_threadPool = threadPool;

			KLSTD_CreateSemaphore( &freeThrSem, maxThrds );
		}


		//\brief ��������� ������ �� ����������
		void AddThread( void *params, bool useTaskQueue = false )
		{
			if ( freeThrSem == NULL ) return;

			// ������������ ��� ������������� ������
			{
				KLSTD::AutoCriticalSection autoUnlocker( criticalSec );

				ThreadsList::iterator it = stopingThreadsList.begin();
				while( it!=stopingThreadsList.end() )
				{
					if ( (*it)->IsStopped() )
					{						
						(*it)->Release();
						it = stopingThreadsList.erase(it);
					}
					else ++it;
				}
			}

			bool reGet = true;
			while( reGet )
			{
				reGet = false;
				bool found = false;
				
				{
					KLSTD::AutoCriticalSection autoUnlocker( criticalSec );
					
					while( !found )
					{
						found = true;

						ThreadsList::iterator it = threadsList.begin();
						// ���� ��������� ������ ����� ������� �����
						int threadCounter = 0;
						for( ; it!=threadsList.end(); ++it, threadCounter++ )
						{
							WorkingThread::ActionState thrState = (*it)->GetCurrentState();
							/*						if ( thrState==WorkingThread::Free )
							{
							(*it)->NewTask( params );
							freeThrSem->Wait();
							break;
							}
							*/
							if ( thrState==WorkingThread::ThreadNotStarted )
							{
								(*it)->SetWorkingThreadNumber( threadCounter + 1 );
								(*it)->NewTask( params );
								(*it)->StartThread( this );								
								break;
							}
						}
						
						if ( it==threadsList.end() )
							found = false;
						
						if ( !found )
						{			
							WorkingThread *wrkThrd = NULL;
							KLTP_CreateWorkingThread( &wrkThrd, threadsList.size(), m_threadPool );
							threadsList.push_back( wrkThrd );
						}
					}
				}
				
				if ( !found )
				{
					// ��� ��������� �������
					if ( useTaskQueue )
					{
						// ��������� ������ � �������
						tasksList.push_back( params );
					}
					else
					{
						// ���� ������������ ������
						freeThrSem->Wait();
						reGet = true;
					}
				}
			}
		}

		void DeleteNonusedThread()
		{
			WorkingThread *fThread = NULL;

			{
				KLSTD::AutoCriticalSection autoUnlocker( criticalSec );
				
				// ���� ������ � ������� ��� ����������
				ThreadsList::iterator it = threadsList.begin();
				for( ; it!=threadsList.end(); ++it )
				{
					if ( (*it)->GetParams()==NULL && !(*it)->IsCurrentThread())
					{
						fThread = (*it);
						threadsList.erase(it);


						fThread->StopThread();	// �������� ������ �� ��������� ������
						stopingThreadsList.push_back( fThread );

						break;
					}
				}
			}
		}

		//\brief ������� ������������ �������� ������
		void FreeTask( WorkingThread *thr )
		{
			KLSTD::AutoCriticalSection autoUnlocker( criticalSec );

			// ���������� ������ ������
			freeThrSem->Post();

			if ( tasksList.size()!=0 )
			{
				void *params = *(tasksList.begin());

				if ( params!=NULL )
				{
					thr->NewTask( params );
					freeThrSem->Wait();
				}

				tasksList.pop_front();
			}				
		}

	 private:

		 typedef std::list<WorkingThread *> ThreadsList;		 


		 KLSTD::CriticalSection *criticalSec;	//<! ��� ������� � ���������� ������

		 ThreadsList			threadsList;	//!< ������ ������� ������
		 ThreadsList			stopingThreadsList;	//!< ������ ������������� �������
		 KLSTD::Semaphore	   *freeThrSem;		//!< ���� ��������� �������

		 typedef std::list<void *> TasksList;

		 TasksList tasksList;					//!< ������ ��������� �����

		 KLTP::ThreadsPool		*m_threadPool;
		 
	 };

} // end namespace KLTP

//\breif ������� ������� ������ ������ ThreadsPoolManager
void KLTP_CreateThreadsPoolManager( KLTP::ThreadsPoolManager **threadManager, int maxThrds,
									 KLTP::ThreadsPool *threadPool )
{
	KLSTD_CHKOUTPTR(threadManager);

	*threadManager = new KLTP::ThreadsPoolManagerImp( );

	KLSTD_CHKMEM(*threadManager);

	(*threadManager)->Init( maxThrds, threadPool );
}
