/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file ThreadsPool.cpp
 * \author ����� �����������
 * \date 2002
 * \brief ���������� ���� �������
 * 
 */
#include "std/base/kldefs.h"
#include "std/trc/trace.h"
#include "std/err/error.h"
#include "std/err/klerrors.h"
#include "std/time/kltime.h"

#include <list>
#include <vector>
#include <algorithm>

#include "std/thr/sync.h"

#include "std/tp/threadspool.h"
#include "threadspoolmanager.h"

//#include "../wat/windowsauthentication.h"

#define USE_ThreadsPoolAutoUnlocker KLSTD::AutoCriticalSection autoUnlocker( m_pCricSec );

namespace KLTP {	

	const wchar_t *KLCS_MODULENAME = L"KLTP";

	ThreadsPool *globalThreadsPool = NULL;

/*!
 * \brief ��������� ���� �������
 * 
 */	
	class ThreadsPoolImp : public ThreadsPool
	{
	public:
		
		enum WorkerState {
			WorkerWaiting,			
			WorkerSuspending
		};

		ThreadsPoolImp()
		{
			m_pCricSec = NULL;
			KLSTD_CreateCriticalSection( &m_pCricSec );
			internalCounter = 1;
			m_threadsManager = NULL;
			m_threadInUseCounter = 0;
			m_numThreads = 0;
			m_runOnlySystemWorkers = false;
			m_threadPoolGrowthTime = 0;
			m_numLowPriorityUseThreads = 0;
		}

		~ThreadsPoolImp()
		{
			Stop();
			if ( m_pCricSec ) m_pCricSec->Release();
		}
		
		//!\brief ������� ������������� ���� �������.
        virtual void Init( int maxNumberOfThreads )
		{
			if ( m_threadsManager!=NULL ) return;

			if ( maxNumberOfThreads<=0 ) return;
			if ( maxNumberOfThreads>c_MaxAllowablePoolsThreads ) 
				maxNumberOfThreads = c_MaxAllowablePoolsThreads;

			m_pTMRelSem = 0;
			KLSTD_CreateSemaphore( &m_pTMRelSem, 1 );

			KLTP_CreateThreadsPoolManager( &m_threadsManager, 
				maxNumberOfThreads, this );

			for( int tc = 0; tc < maxNumberOfThreads; tc++ )
				m_threadsManager->AddThread( NULL ); // ��������� ������ ��� ������� ������ DoProcessing

			m_numThreads = maxNumberOfThreads;
			m_currentMaxLowPriorityThreads = m_numThreads>>2;
		}

		virtual void Stop( )
		{
			KLTP::ThreadsPoolManager *saveThreadsManager = NULL;;

			{
				USE_ThreadsPoolAutoUnlocker;

				if ( m_threadsManager==NULL ) return;
				saveThreadsManager = m_threadsManager;
				m_threadsManager = NULL;
			}

			m_pTMRelSem->Wait();

			saveThreadsManager->Release();
		}

		//!\brief ������� �������� ���������� ���� �������.
		virtual void DoProcessing( void *params, int threadNum )
		{
			// ��������� �� ���� ������� � �������� ������ �� ������ ����
			std::vector<WorkerId> workerIdsList;
			WorkerId saveMaxWorkerId;
			WorkerId waitingWorkerId = (WorkerId)params;
			if ( waitingWorkerId!=0 ) params = NULL;

			{
				USE_ThreadsPoolAutoUnlocker;

				WorkersList::iterator it = m_workersList.begin();
				for(;it!=m_workersList.end();++it)				
					workerIdsList.push_back((*it)->wId);							

				saveMaxWorkerId = internalCounter;
			}

			if ( workerIdsList.size()==0 )
			{
				KLSTD_Sleep( 10 );
				return;
			}

			bool someWorkerRun = false;
			// ������ ����� ����� ����������� � �������� ������ ������ �����
			std::vector<WorkerId> newWorkerIdsList;
			do
			{	
				std::vector<WorkerId>::iterator it = workerIdsList.begin();
				for( ; it!=workerIdsList.end(); ++it )
				{
					WorkerDesc *fwDesc = NULL;
					bool bRunLowPriorityWorker = false;
					{
						USE_ThreadsPoolAutoUnlocker;

						bool bCanCallLowPriorityWorker = true;
						if ( m_numLowPriorityUseThreads>=m_currentMaxLowPriorityThreads ) bCanCallLowPriorityWorker = false;
						
						WorkersList::iterator wit = FindWorkerIteratorById( (*it) );
						if ( wit!=m_workersList.end() )
						{
							fwDesc = (*wit);

							if ( m_runOnlySystemWorkers && fwDesc->m_waitingWorker==false ) 
								continue;	// �� ������ ������ ������������ ������ ��������� worker'�

							if ( fwDesc->m_priority==PriorityLow && !bCanCallLowPriorityWorker ) continue;
							
							if ( !fwDesc->IsNeedToRun( waitingWorkerId ) ) continue;	// ����� ���������� "��������"
							fwDesc->PrepareToRun( threadNum );
							if ( fwDesc->m_priority==PriorityLow ) 
							{
								bRunLowPriorityWorker = true;
								m_numLowPriorityUseThreads++;
							}
						}					
					}
					
					if ( fwDesc ) {

						someWorkerRun = true;
						bool needSetState = (fwDesc->m_waitingWorker==false);
						WorkerId saveWorkerId = fwDesc->wId;

						if ( needSetState ) SetWorkerState( saveWorkerId, true );

						fwDesc->RunWorker();		
						
#ifdef _DEBUG
//						KLSTD::CAutoPtr<KLWAT::AuthServer> pAuthServer;
//						KLWAT_GetGlobalAuthServer( &pAuthServer );
//						KLSTD_CHKMEM(pAuthServer);
//						KLASSERT( pAuthServer->IsThreadImpersonated()==false );
#endif
						WorkerType saveWType = fwDesc->wtype;

						fwDesc->AfterRun();

						if ( saveWType==RunOnce )
						{
							// ������� �������� �� ������
							DeleteWorker( saveWorkerId );
						}

						if ( needSetState ) SetWorkerState( saveWorkerId, false );
					}

					{
						USE_ThreadsPoolAutoUnlocker;

						if ( bRunLowPriorityWorker ) m_numLowPriorityUseThreads--;
					}
				}

				newWorkerIdsList.clear();

				{
					// ��������� �� ��������� �� ����� ������ � ������
					USE_ThreadsPoolAutoUnlocker;
	
					WorkersList::iterator it = m_workersList.begin();
					for(;it!=m_workersList.end();++it)	{
						if ( (unsigned)(*it)->wId>=(unsigned)saveMaxWorkerId &&
							std::find(workerIdsList.begin(), workerIdsList.end(), (*it)->wId)==
							workerIdsList.end() ) 
						{							
							newWorkerIdsList.push_back( (*it)->wId );
						}
					}
					saveMaxWorkerId = internalCounter;
				}

				workerIdsList = newWorkerIdsList;

			} while( workerIdsList.size()!=0 );

			if ( !someWorkerRun ) KLSTD_Sleep( 10 );
		}

		//!\brief ������� ���������� callback ������� � ��� �������.
		virtual void AddWorker2( WorkerId *workerId, const wchar_t *workerName, 
			Worker *worker, WorkerType wtype = RunNormal,
			bool serializableRun = true, int periodTime = (-1),
			WorkerPriority priority = PriorityNormal )
		{
			USE_ThreadsPoolAutoUnlocker;

			if ( internalCounter==(-1) ) internalCounter++;
			WorkerId newWorkerId = internalCounter++;

			WorkerDesc *wDesc = new WorkerDescImp( newWorkerId, worker, serializableRun,
				periodTime, wtype, priority );

			KLTRACE3( L"TP", L"ThreadsPool::AddWorker wId - %d WorkerName - '%ls' Type - %d\n", 
				newWorkerId, workerName, RunNormal );

			if ( wDesc ) m_workersList.push_back( wDesc );

			*workerId = newWorkerId;
		}


		//!\brief ������� ���������� callback ������� � ��� �������.
		virtual void AddWorker( WorkerId *workerId, const wchar_t *workerName, 
			Worker *worker, WorkerType wtype = RunNormal,
			bool serializableRun = true, int periodTime = (-1) )
		{
			AddWorker2( workerId, workerName, worker, wtype, serializableRun, periodTime );
		}


		//!\brief ������� ���������� ���������� "��������" � ��� �������.
		virtual void AddWaitingWorker( WorkerId *workerId, const wchar_t *workerName, 
			Worker *worker, bool serializableRun = true, bool createThreadForWorker = false,
			bool runWorkerOnlyInCreatedThread = false )
		{
			USE_ThreadsPoolAutoUnlocker;

			if ( internalCounter==(-1) ) internalCounter++;
			WorkerId newWorkerId = internalCounter++;

			WorkerDesc *wDesc = new WorkerDescImp( newWorkerId, worker, serializableRun,
				(-1), RunNormal, PriorityNormal );

			wDesc->m_waitingWorker = true;
			wDesc->m_useOneThread = createThreadForWorker;
			wDesc->m_runOnlyInCreatedThread = runWorkerOnlyInCreatedThread;

			KLTRACE3( L"TP", L"ThreadsPool::AddWorker wId - %d WorkerName - '%ls' Type - %d\n", 
				newWorkerId, workerName, RunNormal);

			if ( wDesc ) m_workersList.push_back( wDesc );

			if ( createThreadForWorker && m_threadsManager!=NULL )
			{
				KLTRACE1( L"TP", L"ThreadsPool. Add new thread in ThreadsPool for useOneThread worker. Current number of threads - %d\n",
					m_numThreads );

				m_threadsManager->AddThread( (void*)newWorkerId ); // ��������� �����
			}

			*workerId = newWorkerId;
		}

		//!\brief ���������������� ������ ����������� �������.
		virtual bool SuspendWorker( WorkerId workerId )
		{
			WorkerDesc *wDesc = NULL;
			{
				USE_ThreadsPoolAutoUnlocker;

				wDesc = FindWorkerById( workerId );
				if ( wDesc==NULL ) return false;
				
				if ( wDesc->wstate == WorkerSuspending ) return true;
				if ( wDesc->wtype==ThreadsPool::RunOnce ) return false;

				//!< ������� ��������� ������ ���� ���������� � ������ ������ �������
				wDesc->wstate = WorkerSuspending;
			}

			// ���� ���������� ������� ���������
			if ( wDesc->serializableRun )
			{
				wDesc->pRunCricSec->Enter();
				wDesc->pRunCricSec->Leave();

			}
			else
			{
				wDesc->pRunSem->Wait();
				wDesc->pRunSem->Post();
			}

			return true;
		}

		//!\brief �������������� ������ ���������������� �������.
		virtual bool ResumeWorker( WorkerId workerId )
		{
			USE_ThreadsPoolAutoUnlocker;

			WorkerDesc *wDesc = FindWorkerById( workerId );
			if ( wDesc==NULL ) return false;

			if ( wDesc->wstate == WorkerSuspending ) 			
				wDesc->wstate = WorkerWaiting;
			else return false;

			return true;
		}

		//!\brief ������� ������� ������� �� ���� �����
		virtual bool DeleteWorker( WorkerId workerId )
		{
			WorkerDesc *wDesc = NULL;
			{
				USE_ThreadsPoolAutoUnlocker;

				WorkersList::iterator it = FindWorkerIteratorById( workerId );
				if ( it==m_workersList.end() ) return false;
				else
				{	
					wDesc = (*it);
					if ( wDesc->wstate==WorkerSuspending ) return false; 
					if ( wDesc->wtype==RunOnce ) 
					{
						if ( wDesc->descDeleting ) return false;	// ������ worker ��� ��������
						wDesc->descDeleting = true;
					}
					else m_workersList.erase( it );
				}
			}

			if ( wDesc!=NULL )
			{
				if ( wDesc->wtype==RunOnce ) 
				{
					// ���� ������� ������� Worker'�
					wDesc->pRunSem->Wait();

					// ������� ��������� �� ������
					USE_ThreadsPoolAutoUnlocker;
					
					WorkersList::iterator it = FindWorkerIteratorById( workerId );
					if ( it==m_workersList.end() ) return false;
					else m_workersList.erase( it );
				}

				if ( wDesc->serializableRun ) 
				{
					wDesc->pRunCricSec->Enter();
					wDesc->pRunCricSec->Leave();
                } 
				else 
				{
					wDesc->pRunSem->Wait();
                }

				// ���� ���������� ������� �������� ��� WorkerDesc
				wDesc->WaitOperationEnd();

				wDesc->Release();
				return true;
			}

			return false;
		}

		//!\brief ������� �������� �������� ������ ���� � ��������� 'in use'
		virtual void SetWorkerState( WorkerId workerId, bool inUse )
		{
			KLERR_BEGIN
				
			bool needAddNewWorkerThread = false;
			bool needDelNonusedWorkerThread = false;
			KLTP::ThreadsPoolManager *pTPM = NULL;			
			{
				USE_ThreadsPoolAutoUnlocker;

				if ( inUse ) m_threadInUseCounter++;
				else m_threadInUseCounter--;

				if ( (m_numThreads - m_threadInUseCounter) <= c_ThreadReserveNumber &&
					m_numThreads < c_MaxAllowablePoolsThreads ) 
				{
					needAddNewWorkerThread = true;
					m_numThreads++;					// ���������� ���� �����					
					m_threadPoolGrowthTime = KLSTD::GetSysTickCount();
					m_currentMaxLowPriorityThreads = m_numThreads>>2;
				}

				if ( (m_numThreads - m_threadInUseCounter) >= (c_ThreadReserveNumber * 2) + 1 &&
					m_numThreads > c_DefaultNumberOfPoolsThreads )
				{
					if ( KLSTD::DiffTickCount(KLSTD::GetSysTickCount(), m_threadPoolGrowthTime) > c_ThreadPoolDeleteThreadTimeout )
					{
						needDelNonusedWorkerThread = true;
						m_numThreads--;
						m_currentMaxLowPriorityThreads = m_numThreads>>2;
					}
				}

				if ( m_numThreads >= c_MaxAllowablePoolsThreads &&
					(m_numThreads - m_threadInUseCounter) <= ( c_ThreadReserveNumber + 1 ) )				
					m_runOnlySystemWorkers = true;
				else 
					m_runOnlySystemWorkers = false;

				if ( m_numThreads >= c_MaxAllowablePoolsThreads && needAddNewWorkerThread )
				{
					KLTRACE1( L"TP", L"ERROR in ThreadsPool. Max number of threads was exceeded\n" );
				}

				if ( m_threadsManager!=NULL ) 
				{
					pTPM = m_threadsManager;
					m_pTMRelSem->Wait();
				}
			}
	
			if ( needAddNewWorkerThread && pTPM!=NULL ) // ���������� ���� �����
			{
				KLTRACE1( L"TP", L"ThreadsPool. Add new thread in ThreadsPool. Current number of threads - %d\n",
					m_numThreads );

				KLERR_BEGIN
					pTPM->AddThread( NULL ); // ��������� �����
				KLERR_ENDT( 3 )
			}

			if ( needDelNonusedWorkerThread && pTPM!=NULL )
			{
				KLTRACE1( L"TP", L"ThreadsPool. Delete thread in ThreadsPool. Current number of threads - %d\n",
					m_numThreads );

				KLERR_BEGIN
					pTPM->DeleteNonusedThread(); 
				KLERR_ENDT( 3 )
			}

			if ( pTPM!=NULL ) m_pTMRelSem->Post();
			
			KLERR_ENDT( 1 )
		}

		//\brief ���������� ���-�� ������� � ���� �������
		virtual int GetThreadsNumber()
		{
			USE_ThreadsPoolAutoUnlocker;

			return m_numThreads;			
		}
		
	protected:
		// ���������� ���������� ������
		

		class WorkerDesc : public KLSTD::KLBase
		{
		public:
			void Init( WorkerId id, Worker	*wrk, bool sRun, int pTime, 
				WorkerType type, WorkerPriority p )
			{
				wId = id, worker = wrk, wtype = type, wstate = WorkerWaiting;
				serializableRun = sRun;
				periodTime = pTime;
				firstStartFlag = true;
				dontRunWorker = false;
				lastRunTime = 0;
				if ( worker ) worker->AddRef();
				runNumberNow = 0, runCounter = 0;
				m_waitingWorker = false;
				m_useOneThread = false;
				m_runOnlyInCreatedThread = false;
				descDeleting = false;
				pRunCricSec = NULL;
				m_priority = p;
				KLSTD_CreateCriticalSection( &pRunCricSec );
				pRunSem = NULL;
				if ( type==RunOnce )
				{
					serializableRun = true;
					KLSTD_CreateSemaphore( &pRunSem, 0 );
				}
				else
					KLSTD_CreateSemaphore( &pRunSem, 1 );

				pSerCricSec = NULL;
				KLSTD_CreateCriticalSection( &pSerCricSec );

				m_threadNum = (-1);
			}
			~WorkerDesc()
			{
				if ( worker ) worker->Release();

				if ( pRunCricSec ) pRunCricSec->Release();
				if ( pSerCricSec ) pSerCricSec->Release();

				if ( pRunSem ) pRunSem->Release();
			}
			bool IsNeedToRun( WorkerId waitingWorkerId )
			{
				KLSTD::AutoCriticalSection autoUnlocker( pSerCricSec );

				if ( dontRunWorker ) return false;
				if ( serializableRun && runNumberNow!=0 ) return false;

				if ( waitingWorkerId!=0 && /*m_waitingWorker && �� ������ ������ ����� ����������� ������ waiter ����� ( ��� ������� ����������� ���� deadlock) */ 
					wId!=waitingWorkerId ) 
					return false;	// �� ������ ������ ������ ����������� ������ ������������� ������ ������

				if ( m_useOneThread && 
					( !m_runOnlyInCreatedThread || waitingWorkerId!=wId ) ) 
					return false;	// ������ ��������� ������ � ����� ������

				if ( periodTime>0 ) 
				{
					if ( firstStartFlag || 
						 KLSTD::DiffTickCount(KLSTD::GetSysTickCount(), lastRunTime) >= (unsigned)periodTime )
					{
						firstStartFlag = false;
						lastRunTime = KLSTD::GetSysTickCount();
						return true;
					}
					else return false;
				}
				
				return true;
			}
			void PrepareToRun( int threadNum )
			{
				KLSTD::AutoCriticalSection autoUnlocker( pSerCricSec );

				if ( runNumberNow==0 ) {
					if ( serializableRun )
						pRunCricSec->Enter();
					else
						pRunSem->Wait();
                }
				AddRef();
				runNumberNow++;
				m_threadNum = threadNum;
				if ( wtype==RunOnce ) 
				{
					pRunSem->Post();		// ���������� ������� ����, ��� RunOnce worker �������
					dontRunWorker = true;
				}
			}
			int RunWorker()
			{
				int res = 0;
				if ( worker )
				{
					KLERR_BEGIN

						res = worker->RunWorker( wId );

					KLERR_ENDT( 3 )

					runCounter++;
				}
				return res;
			}
			void AfterRun()
			{
				KLSTD::AutoCriticalSection autoUnlocker( pSerCricSec );

				m_threadNum = (-1);
				runNumberNow--;
				if ( runNumberNow==0 ) {
					if ( serializableRun )
						pRunCricSec->Leave();
					else
						pRunSem->Post();
                }
				this->Release();
			}
			void WaitOperationEnd()
			{
				KLSTD::AutoCriticalSection autoUnlocker( pSerCricSec );
			}
			
			WorkerId	wId;
			Worker		*worker;
			WorkerType	wtype;
			WorkerState	wstate;			
			unsigned int volatile runNumberNow;		//!< ���-�� ������������ ���������� �������
			unsigned long volatile runCounter;		//!< ����� ���-�� ��������
			KLSTD::Semaphore	   *pRunSem;		//!< ������������ ��� �������� ���������
			KLSTD::CriticalSection *pRunCricSec;
			KLSTD::CriticalSection *pSerCricSec;	//!< ������������ ��� �������� ���������
			bool		serializableRun;			//!< ���������������� ����� callback'�� 
			int			periodTime;					//!< ����� ������� ������� (� ������������)


			unsigned long		lastRunTime;				//!< ��������� ����� ������� "��������" � �����
			bool				firstStartFlag;			//!< ������� ������� �������

			bool				m_waitingWorker;	//!< ������� ������� �������
			bool				m_useOneThread;		//!< ������� ������������� ���������� ������ 
								// ( � ������ ������ �� ����� ���������� ������ ������ ������� )
			bool				m_runOnlyInCreatedThread;
			WorkerPriority		m_priority;			//!< ��������� worker'�
			int					m_threadNum;
			bool				dontRunWorker;			//!< ������ ������ ������ ��������� �� ����
			bool				descDeleting;			//!< ������� ���������� �������� ( ������������ ������ ��� RunOnce )
		};

		class WorkerDescImp : public KLSTD::KLBaseImpl<WorkerDesc>
		{
		public:
			WorkerDescImp( WorkerId id, Worker	*wrk, bool serializableRun, 
				int periodTime, WorkerType type, WorkerPriority priority )
			{
				Init( id, wrk, serializableRun, periodTime, type, priority);
			}
		};

		typedef std::list<WorkerDesc *> WorkersList;

		KLSTD::CriticalSection	*m_pCricSec;			//!< ��� ������� � ���������� ������

		WorkerId				internalCounter;	//!< ������� ���������������
		WorkersList				m_workersList;		//!< ������ ������ ���� �������

		int						m_numThreads;		//!< ���������� ������� � ���� 

		int						m_threadInUseCounter;	//! ������� ������� � ������ ThreadInUse

		bool					m_runOnlySystemWorkers;	//! ����������� ������ ��������� ������

		KLTP::ThreadsPoolManager		*m_threadsManager;	//!< �������� �������� ������� ��
		KLSTD::CAutoPtr<KLSTD::Semaphore>	m_pTMRelSem;	

		unsigned long			m_threadPoolGrowthTime;		//! ����� ���������� ���������� ���� �������

		int						m_numLowPriorityUseThreads;		//! ������� ���-�� ������� � ������� � ������ ������ ����������� worker'� � ������ �����������
		int						m_currentMaxLowPriorityThreads;	//! ������������ ���-�� ������� ��������� ��� ����������������� worker'��

	private:
		// ��������������� ������� ������
		WorkerDesc *FindWorkerById( WorkerId wid )
		{
			WorkersList::iterator it = m_workersList.begin();
			for(;it!=m_workersList.end();++it)
			{
				if ( (*it)->wId==wid ) return (*it);
			}
			return NULL;
		}
		WorkersList::iterator FindWorkerIteratorById( WorkerId wid )
		{
			WorkersList::iterator it = m_workersList.begin();
			for(;it!=m_workersList.end();++it)
			{
				if ( (*it)->wId==wid ) return it;
			}
			return m_workersList.end();
		}
		bool DeleteWorkerFromList( WorkerId wid )
		{
			WorkersList::iterator it = m_workersList.begin();
			for(;it!=m_workersList.end();++it)
			{
				if ( (*it)->wId==wid ) return true;
			}

			return false;
		}

		/*!
			\brief ���������� ������� ������
		*/
		bool GetWorkerInfo( WorkerId workerId, int &poolsThreadsNumber, 
			WorkerStatus &status )
		{
			USE_ThreadsPoolAutoUnlocker;

			WorkersList::iterator it = m_workersList.begin();
			for(;it!=m_workersList.end();++it)
			{
				if ( (*it)->wId==workerId ) 
				{
					poolsThreadsNumber = (*it)->m_threadNum;
					return true;
				}
			}

			return false;
		}
	};

} // end namespace KLTP

/*
	\breif ������� ������� ������ ������ ThreadsPool
*/
void KLTP_CreateThreadsPool( KLTP::ThreadsPool **threadsPool )
{
	KLSTD_CHKOUTPTR(threadsPool);

	*threadsPool = new KLTP::ThreadsPoolImp();	
	(*threadsPool)->Init( KLTP::c_DefaultNumberOfPoolsThreads );

	KLSTD_CHKMEM(*threadsPool);
}

/*
	\brief ������� ���������� ��������� �� ���������� ThreadsPool
*/
KLCSC_DECL KLTP::ThreadsPool *KLTP_GetThreadsPool()
{
	KLASSERT( KLTP::globalThreadsPool!=NULL );

	return KLTP::globalThreadsPool;
}

IMPLEMENT_MODULE_INIT_DEINIT(KLTP)

//\brief ������� ������������� ����������.
IMPLEMENT_MODULE_INIT_BEGIN(KLTP)

	KLTP_CreateThreadsPool( &KLTP::globalThreadsPool );

IMPLEMENT_MODULE_INIT_END()

/*\brief ������� ���������� ���������� ������ ������ ThreadsPool*/
IMPLEMENT_MODULE_DEINIT_BEGIN(KLTP)

	KLTP::ThreadsPool *saveP = KLTP::globalThreadsPool;
	KLTP::globalThreadsPool = NULL;
	saveP->Stop();
	delete saveP;

IMPLEMENT_MODULE_DEINIT_END()
