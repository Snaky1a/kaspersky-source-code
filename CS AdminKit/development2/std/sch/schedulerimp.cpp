/*!
* (C) 2002 "Kaspersky Lab"
*
* \file SchedulerImp.cpp
* \author ����� �����������
* \date 2002
* \brief ������� ��������� ������-������������
*
*  ������ ���� �������� ���������� ������ Scheduler.
*  ������-����������� ��������� ���������� ������ � �������� ������ �� ����������
*  � ������������ ������ �������.  ������ �������� ������ ������ ������ Scheduler
*  ���������� � ����� CS AdminKit\DESIGN\Modules\Scheduler.doc
*
*/
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "schedulerimp.h"
#include "std/thr/sync.h"
#include "std/time/kltime.h"

namespace KLSCH {

	//!\brief �����������.
	SchedulerImp::SchedulerImp( int waitTime /*= c_Infinite*/ )
	{	
		suspendMode     = false;

		createdIteratorsNum = 0;
		needFreeDelTask = false;

		internalTaskIdCounter = INT_MAX / 2;

        // by the way, usage of virtual functions in constructor is bad
        // practice:
		SetWaitTime( waitTime, 0 );	//��������� ����� ��� Scheduler timeout
	}

	//!\brief ����������.
	SchedulerImp::~SchedulerImp( )
	{      
      for (iterator i = wtc_list.begin(); i != wtc_list.end(); ++i ) {
        delete (*i);
      }
      wtc_list.erase( wtc_list.begin(), wtc_list.end() );
	}
	
    //!\brief ����� ��������� ����� ������ � ������ �����.      
	Errors SchedulerImp::AddTask( const Task *t, TaskId& id_ptr )
	{
		TaskId newTaskId;
		bool taskIdFromClient = true;

		LightMutex::AutoUnlock autoUnlock( &mutex );

		// ���������� task id
		t->GetTaskId( newTaskId );
		if ( newTaskId==0 ) 
			newTaskId = internalTaskIdCounter++, taskIdFromClient = false;

		// ��������� ������ ����� ��� ������� id
		TaskList::ListUnit *taskUnit = NULL;
		bool findRes = taskList.FindTask( &taskUnit, newTaskId );
		if ( findRes && taskIdFromClient ) return ERR_ID_EXISTS; // taskId �� ������� �� ������

		// ���������� ������������� ����� Id
		while( findRes )
		{
			newTaskId = internalTaskIdCounter++;
			findRes = taskList.FindTask( &taskUnit, newTaskId );
		}

		TaskList::ListUnit *newTaskUnit = taskList.AddTask( t );

		if ( !taskIdFromClient ) newTaskUnit->task.SetTaskId( newTaskId ); // ��������� ����� TaskId

		Trace( 4, "New task was added. TaskId - %d\n", newTaskId );

		newTaskUnit->task.CalculateNextExecutionTime();
		newTaskUnit->task.SetCurrState( Task::Scheduled );

		WriteTaskNextExecutionTime( newTaskUnit );

		id_ptr = newTaskId;
		
		return ERR_NONE;
	}
	
    //!\brief ������� ������ � �������� ���������������.
	Errors SchedulerImp::DelTask( const TaskId id )
	{
		TaskList::ListUnit *taskUnit = NULL;
		Task::State currState;

		LightMutex::AutoUnlock autoUnlock( &mutex );

		// ���� ������ �� ���������� ������
		bool findRes = taskList.FindTask( &taskUnit, id );
		if ( !findRes ) return ERR_NO_TASK_ID;
	
 		taskUnit->task.GetCurrentState( currState );

		taskUnit->task.SetCurrState( Task::Deleted ); // ��� ���������� ��������� RemoveTaskFromWork

		// ���� wtc ������� ����� ����� ��� ������
		if ( currState==Task::WaitForRunning || currState==Task::Running )
			RemoveTaskFromWork( id, taskUnit, true  );
		else
			RemoveTaskFromWork( id, taskUnit, false );

		
		if ( createdIteratorsNum==0 && currState!=Task::Running && currState!=Task::WaitForRunning )
			// ������� ������ �� ������
			taskList.DeleteTask( id ); 
		else
		{
			taskUnit->task.SetCurrState( Task::Deleted );
			if ( createdIteratorsNum!=0) needFreeDelTask = true;
		}

		return ERR_NONE;
	}

	//!\brief ������������� ��������� ��� ��������� ������
	Errors SchedulerImp::SetPramsForTask( const TaskId id, TaskParams * par )
	{
		TaskList::ListUnit *taskUnit = NULL;	

		LightMutex::AutoUnlock autoUnlock( &mutex );

		// ���� ������ �� ���������� ������
		bool findRes = taskList.FindTask( &taskUnit, id );
		if ( !findRes ) return ERR_NO_TASK_ID;

		taskUnit->task.SetTaskParams( par );

		return ERR_NONE;
	}

	//!\brief ���������������� ������ ��������� ������.
    Errors SchedulerImp::SuspendTask( const TaskId id )
	{
		TaskList::ListUnit *taskUnit = NULL;

		LightMutex::AutoUnlock autoUnlock( &mutex );

		// ���� ������ �� ���������� ������
		bool findRes = taskList.FindTask( &taskUnit, id );
		if ( !findRes ) return ERR_NO_TASK_ID;

		taskUnit->task.SetCurrState( Task::Suspended );				

		RemoveTaskFromWork( id, taskUnit, true );			

		return ERR_NONE;
	}

	//!\brief ������������ ������ ���������������� ������ ��������� ������.
    Errors SchedulerImp::ResumeTask( const TaskId id )
	{
		TaskList::ListUnit *taskUnit = NULL;
		Task::State		currState;

		LightMutex::AutoUnlock autoUnlock( &mutex );

		// ���� ������ �� ���������� ������
		bool findRes = taskList.FindTask( &taskUnit, id );
		if ( !findRes ) return ERR_NO_TASK_ID;

		taskUnit->task.GetCurrentState( currState );
		if ( currState != Task::Suspended ) return ERR_TASK_STATE;

		// ���������� ������ ������� ������� ������		
		taskUnit->task.CalculateNextTimeAfterSuspend();
		taskUnit->task.SetCurrState( Task::Scheduled );

		WriteTaskNextExecutionTime( taskUnit );

		return ERR_NONE;
	}

	//!\brief ���������� ��������� ����� ������� ������.
	Errors SchedulerImp::GetTaskNextExecutionTime( const TaskId id, time_t& sec, int& msec )
	{
		TaskList::ListUnit *taskUnit = NULL;

		LightMutex::AutoUnlock autoUnlock( &mutex );

		// ���� ������ �� ���������� ������
		bool findRes = taskList.FindTask( &taskUnit, id );
		if ( !findRes ) return ERR_NO_TASK_ID;
		
		return taskUnit->task.GetNextExecutionTime( sec, msec );
	}

	//!\brief ��������� scheduler � ����� �������������.
	Errors SchedulerImp::Suspend( )
	{      
		LightMutex::AutoUnlock autoUnlock( &mutex );

		// �������� �� ���� WTC � ��������� ������ ������
        for ( iterator i = wtc_list.begin(); i != wtc_list.end(); ++i ) {
          if ( (*i)->wType == WaitingThreadContext::TASK_WAITING || 
               (*i)->wType == WaitingThreadContext::NO_TASK_WAITING ) {
            (*i)->tId = c_Undefined;
            (*i)->wType = WaitingThreadContext::LEAVE_WAITING;
            (*i)->sem.Post();
          }
        }

		suspendMode = true; // ������������� ������� ����������������� ������

		return ERR_NONE;
	}

	//!\brief �������� ����������� �� ������ ������������� � ����������.
	Errors SchedulerImp::Resume( )
	{
		LightMutex::AutoUnlock autoUnlock( &mutex );

		if ( !suspendMode ) return ERR_SCHEDULER_STATE;

		// ������������� ��� ��������� �������
		TaskClassesList::ListUnit *classUnit = taskClassesList.GetFirst();

		while( classUnit!=NULL )
		{
			classUnit->nextExecutesec  = 0;
			classUnit->nextExecutemsec = 0;
			classUnit->nextTaskId      = c_Undefined;

			TaskList::ListUnit *nextTaskDesc = taskList.FindNextTask( classUnit->ctId );
			if ( nextTaskDesc!=NULL )			
				WriteTaskNextExecutionTime( nextTaskDesc );

			classUnit = taskClassesList.GetNext( classUnit->ctId );
		}

		suspendMode = false;

		
		return ERR_NONE;
	}

	
    //!\brief ������� �������� ��� ��������� ������ �����.
	Errors SchedulerImp::CreateTasksIterator( TasksIterator *it, TaskClassId cid /* = 0*/ ) 
	{
		LightMutex::AutoUnlock autoUnlock( &mutex );
				
		((TasksIteratorImp *)(it))->Init( this, &taskList, cid, false );

		createdIteratorsNum++;

		return ERR_NONE;
	}
	
	
    //!\brief ������� �������� ��� ��������� ������ "���������" �����.	
	Errors SchedulerImp::CreateHangingTasksIterator( TasksIterator *it, TaskClassId cid /*= 0*/ )
	{
		LightMutex::AutoUnlock autoUnlock( &mutex );
				
		((TasksIteratorImp *)(it))->Init( this, &taskList, cid, true );

		createdIteratorsNum++;

		return ERR_NONE;
	}
	
	
    //!\brief ���������� ����� �����, ��������� ���������� ������ Scheduler.
	Errors SchedulerImp::GetTasksNumber( int& num, TaskClassId cid /* = 0*/) const
	{
		return ERR_NONE;
	}
	
	
    /*!\brief ������������� ������������ ����� �������� ������ �� ������ 
	���������� ������ (msec).
	*/
	Errors SchedulerImp::SetWaitTime( int waitTime /* = 10000 */, TaskClassId cid /* = 0 */ )
	{                 
		if ( cid<0 ) return ERR_TASK_CLASS_ID;

		LightMutex::AutoUnlock autoUnlock( &mutex );

		taskClassesList.SetDescUnitWaitTime( cid, waitTime );

		return ERR_NONE;
	}
	
	
    /*!\brief ���������� ������������ ����� �������� ������ �� ������ 
	���������� ������ (msec).
	*/
	Errors SchedulerImp::GetWaitTime( int& waitTime, TaskClassId cid /* = 0 */ )
	{
		LightMutex::AutoUnlock autoUnlock( &mutex );

		TaskClassesList::ListUnit *fUnit = taskClassesList.GetDescUnit( cid );

		if ( fUnit==NULL ) return ERR_TASK_CLASS_ID;

		waitTime = fUnit->waitTime;

		return ERR_NONE;
	}

    //!\brief ��������� ����� ������� �� ������� ���������� ������.
	Errors SchedulerImp::WaitTaskExecution(   
		TaskResults** result,
		void *threadContext,
		int waitTime /* = 0 */, 
		TaskClassId cid /* = 0 */,
		bool waitFlag /* = true */ )
	{
		if ( cid<0 ) return ERR_TASK_CLASS_ID;
		
		time_t	currentTime;
		time_t	currentTimeMSec = 0;
		time_t	executionTimeSec = (-1);	// ����� ������� ������ 
		int		executionTimeMsec = 0;
		TaskId	tId = c_Undefined;		// ������������� ������
		WaitingThreadContext *wtc = 0;
		bool repeate;					// ���� ��� �����
		TaskList::ListUnit *taskUnit = NULL;				
		
		do {			
			// �������� ������� �����
			time( &currentTime );

			currentTimeMSec = KLSTD::GetCurrentMilliseconds();

			repeate = false;
			taskUnit = NULL;

			{
				LightMutex::AutoUnlock autoUnlock( &mutex );

				if ( suspendMode ) return ERR_SUSPEND_MODE;

				Trace( 6, "\n\n\nScheduler::WaitTaskExecution ClientTaskContext - %d CurrentTime - %d CurrTimeMSec - %d\n", 
					threadContext, currentTime, currentTimeMSec );
				
				TaskClassesList::ListUnit *ctd = taskClassesList.GetNextDescUnit( cid, 
					currentTime, currentTimeMSec, waitTime );
				
				if ( ctd!=NULL ) // ����� ������
				{
					// ��������� ����� ������� ������
					executionTimeSec = ctd->nextExecutesec;
					executionTimeMsec = ctd->nextExecutemsec;
					tId = ctd->nextTaskId;

					taskList.FindTask( &taskUnit, tId );
					taskUnit->task.SetCurrState( Task::WaitForRunning );					
				}
				else
				{
					executionTimeSec = (-1);
					executionTimeMsec = 0;
					tId = c_Undefined;
				}
				
				if ( tId!=c_Undefined || waitFlag )
				{
					// ������� �������� ���������� ������
					wtc = GetFreeWTCUnit();
					
					wtc->tcId = cid;
					wtc->tId  = tId;

					// ��������� ������ �������� ( ������ ���� ��� ���� ������������ ������ )
					if ( tId==c_Undefined ) 
					{
						wtc->wType = WaitingThreadContext::NO_TASK_WAITING;
						// ������ ������ ���, ������� ����� ������ ��������� timeOut ������ ������
						TaskClassesList::ListUnit *foundUnit = taskClassesList.GetDescUnit( cid );
						if ( foundUnit==NULL ) foundUnit = taskClassesList.GetDescUnit( 0 );
						executionTimeSec  = currentTime;						
						if ( waitTime==0 ) executionTimeMsec = foundUnit->waitTime;
						else			   executionTimeMsec = waitTime;	
					}
					else wtc->wType = WaitingThreadContext::TASK_WAITING;

					// ��������� ����� ������� ������
					wtc->timeSec = executionTimeSec;
					wtc->timeMSec = executionTimeMsec;					
					
					wtc->clientThreadCntx = threadContext;
				}
				else
					return ERR_NO_MORE_TASKS;

				if ( ctd!=NULL )
				{
					// ��������� ��������� ����� �������
					ctd->nextExecutesec  = 0;
					ctd->nextExecutemsec = 0;
					ctd->nextTaskId      = c_Undefined;
					
					TaskList::ListUnit *nextTaskDesc = taskList.FindNextTask( cid );
					if ( nextTaskDesc!=NULL )
					{
						WriteTaskNextExecutionTime( nextTaskDesc );						
					}
				}
			} // ��������� mutex
			
			long waitingTime = CalculateWaitingTime( executionTimeSec, executionTimeMsec,
				currentTime, currentTimeMSec );

			Trace( 6, "Wait task procedure. WaitClassId - %d TaskId - %d WaitType - %d ClientThreadContext - %d StartSec - %d StartMSec - %d SemaphoreWaitTime - %d\n",
					wtc->tcId, wtc->tId, wtc->wType, wtc->clientThreadCntx, wtc->timeSec, wtc->timeMSec, waitingTime );

			// ���� �� ����������� ������� ������ ��� �� ������� ��������� ����� ���� ������
			bool res = false;

			if ( waitingTime!=0 ) // � ������������ ��������� ������ - ����� ��������� ������ ������							
				res = wtc->sem.Wait( waitingTime );

			if ( !res && tId!=c_Undefined ) // ����� ����� �� ���������, ��������� �� ������� ��������
			{
				{
					LightMutex::AutoUnlock autoUnlock( &mutex );

					if ( wtc->tId==c_Undefined ) // ������ ���� ������� ���� �� �� �����
					{
						Trace( 4, "While thread waiting task time this task was be deleted. WaitClassId - %d TaskId - %d WaitType - %d ClientThreadContext - %d SemaphoreWaitTime - %d\n",
							wtc->tcId, wtc->tId, wtc->wType, wtc->clientThreadCntx, waitingTime );
						// ����������� wtc
						FreeWTCUnit( wtc );
						if ( suspendMode ) return ERR_SUSPEND_MODE;
						return ERR_NO_MORE_TASKS; 
					}
					
					wtc->wType = WaitingThreadContext::TASK_RUNNING;
															
					// �������� ������
					taskUnit->task.SetThreadContext( threadContext );
					taskUnit->task.SetCurrState( Task::Running );

				} // ��������� mutex
				
				bool delAfterRunFlag = false;

				// ����� ������
				taskUnit->task.Call( result, delAfterRunFlag );

				{
					LightMutex::AutoUnlock autoUnlock( &mutex );

					Task::State curState;

					taskUnit->task.GetCurrentState( curState );
					taskUnit->task.SetThreadContext( NULL );

					if ( curState==Task::Deleted || delAfterRunFlag ) // ������ ���� ������� � �� ����� ����� �� �� ���������
					{						
						TaskId id;						
						// ������� ����� ��������� ��� �������� �������� �������
						taskUnit->task.GetTaskId( id );
						DelTask( id );
					}
					else
					{
						taskUnit->task.SetCurrState( Task::Scheduled );
										
						// ���������� ������ ������� ��������� ������� ���� ������				
						taskUnit->task.CalculateNextExecutionTime();
						WriteTaskNextExecutionTime( taskUnit );
					}
					
					// ����������� wtc
					FreeWTCUnit( wtc );
				}
			}
			else
				if ( res )
				{
					Trace( 4, "New task was added and this thread will try to get new task. WaitClassId - %d TaskId - %d WaitType - %d ClientThreadContext - %d SemaphoreWaitTime - %d\n",
						wtc->tcId, wtc->tId, wtc->wType, wtc->clientThreadCntx, waitingTime );
					
					// ��������� ����� ������ ( ���������� ������� ����� ������ ��� ���������� )
					// ��� ��������� ������� ������
					// ����������� wtc
					LightMutex::AutoUnlock autoUnlock( &mutex );
					
					if ( taskUnit!=NULL ) 
					{
						Task::State curState;
						taskUnit->task.GetCurrentState( curState );
						if ( curState==Task::Deleted ) // ������ ���� ������� � �� ����� ����� �� �� �����
						{						
							TaskId id;						
							// �������� �������
							taskUnit->task.GetTaskId( id );
							DelTask( id );
						}
						else
							taskUnit->task.SetCurrState( Task::Scheduled );
					}
					
					FreeWTCUnit( wtc );
					
					repeate = true;	
				}
				else 
				{
					// ����������� wtc
					LightMutex::AutoUnlock autoUnlock( &mutex );
					FreeWTCUnit( wtc );

					if ( suspendMode ) return ERR_SUSPEND_MODE;
					return ERR_NO_MORE_TASKS;
				}
			
		} while( repeate );
		
		return ERR_NONE;
	}
	
	/** class helper functions */

	/** ���������� ��������� ������ � ������� */
	SchedulerImp::WaitingThreadContext *SchedulerImp::GetFreeWTCUnit( )
	{      
        iterator i;

        for ( i = wtc_list.begin(); i != wtc_list.end(); ++i ) {
          if ( (*i)->wType == WaitingThreadContext::NO_WAITING ) {
            break;
          }
        }
        if ( i == wtc_list.end() ) {
          wtc_list.push_back( new WaitingThreadContext );
          i = wtc_list.end();
          --i;
        }
        return *i;
	}

	/** ���������� ������ ��������� �������� ������� ������ ����� */
	SchedulerImp::WaitingThreadContext *SchedulerImp::GetWaitingWTCByClassTaskId( const TaskClassId ctId )
	{      
		time_t classesMaxSec = 0;
		int    classesMaxMSec = 0;
		time_t commonMaxSec = 0;
		int    commonMaxMSec = 0;
        iterator comMaxPosTask = wtc_list.end(); // ������� ������������� � TASK_WAITING ����� 0
		iterator classMaxPosTask = wtc_list.end(); // ������� ������������� � TASK_WAITING ����� ctId
		iterator comPosNoTask = wtc_list.end(); // ������� � NO_TASK_WAITING ����� 0
		iterator classPosNoTask = wtc_list.end(); // ������� � NO_TASK_WAITING ����� ctId

		// ����� ������������ WTC �������������� �� ��������� �����������:
		//	1. ������� ��������� ������ ����� ����� ����� (�������� NO_TASK_WAITING) 
		//		( ���� ��� �� 2 )
		//  2. ������� ��������� ����� ����� ����� (0) ����� (�������� NO_TASK_WAITING) 		
		//  3. ������� ��������� ������ ����� ����� ����� (�������� TASK_WAITING) � 
		//      ���������� ��������������� �������� ������� ������ ( ���� ��� �� 4 )
		//  4. ������� ��������� ����� ����� ����� (0) ����� (�������� TASK_WAITING) 
		//		� ���������� ��������������� �������� ������� ������
		

        for ( iterator i = wtc_list.begin(); i != wtc_list.end(); ++i ) {
          WaitingThreadContext *wtc = *i;
          if ( wtc->tcId == ctId ) { // WTC ������� ������
            if ( wtc->wType == WaitingThreadContext::NO_TASK_WAITING ) {
              classPosNoTask = i;
              break; // ����� ������� �������
            } else if ( wtc->wType == WaitingThreadContext::TASK_WAITING ) {
              if ( classMaxPosTask != wtc_list.end() ) {
                if ( CompareTimes( classesMaxSec, classesMaxMSec,
                                   wtc->timeSec, wtc->timeMSec) <0 ) {
                  classesMaxSec = wtc->timeSec;
                  classesMaxMSec = wtc->timeMSec;
                  classMaxPosTask = i;
                }
              } else {
                classesMaxSec = wtc->timeSec;
                classesMaxMSec = wtc->timeMSec;
                classMaxPosTask = i;
              }
            }
          }
          if ( wtc->tcId == 0 ) { // WTC ������ ������
            if ( wtc->wType == WaitingThreadContext::NO_TASK_WAITING ) {
              comPosNoTask = i;
              break; // ����� ������� �������
            } else if ( wtc->wType == WaitingThreadContext::TASK_WAITING ) {
              if ( comMaxPosTask != wtc_list.end() ) {
                if ( CompareTimes( commonMaxSec, commonMaxMSec,
                                   wtc->timeSec, wtc->timeMSec)<0 ) {
                  commonMaxSec = wtc->timeSec;
                  commonMaxMSec = wtc->timeMSec;
                  comMaxPosTask = i;
                }								
              } else {
                commonMaxSec = wtc->timeSec;
                commonMaxMSec = wtc->timeMSec;
                comMaxPosTask = i;
              }
            }
          }				
        }

		// �������� �� ���������� �������� ���������� �������
		if ( classPosNoTask != wtc_list.end() )
          return *classPosNoTask;

		if ( comPosNoTask != wtc_list.end() )
          return *comPosNoTask;

		if ( classMaxPosTask != wtc_list.end() )
          return *classMaxPosTask;
		if ( comMaxPosTask != wtc_list.end() )
          return *comMaxPosTask;

		return NULL;
	}

	/** ����������� wtc */
	void SchedulerImp::FreeWTCUnit( WaitingThreadContext *wtc )
	{
		if ( wtc->wType	== WaitingThreadContext::LEAVE_WAITING )
			// ���������� ������� ( ��� ������ ������� ��������� Post � �� ��� ��������� Wait
			//  ������������� ������
			wtc->sem.Wait(0);

		wtc->wType				= WaitingThreadContext::NO_WAITING;
		wtc->clientThreadCntx	= NULL;
		wtc->tId				= c_Undefined;
		wtc->tcId				= c_Undefined;
	}

	/** ��������� ����� ������� ������ ������. ����������� ���������� WTC */
	void SchedulerImp::WriteTaskNextExecutionTime( TaskList::ListUnit *taskDesc )
	{		
		// �������� ��������� ����� �������
		time_t taskNextETimesec;
		int taskNextETimemsec;
		Errors err = taskDesc->task.GetNextExecutionTime( taskNextETimesec, taskNextETimemsec );
		if ( err!=ERR_NONE || taskNextETimesec==0 )
			taskDesc->task.SetCurrState( Task::Completed ); // ��� ������� ���������� �������
		else
		{
			int taskClassId;
			int taskId;
			taskDesc->task.GetClassId( taskClassId );
			taskDesc->task.GetTaskId( taskId );

			Trace( 4, "Scheduler::WriteTaskNextExecutionTime TaskId - %d\n", taskId );
			
			// ���������� ������� � ��������� ������ ����� � ������� ����� ������
			
			TaskClassesList::ListUnit *ctdUnit = taskClassesList.GetDescUnit( taskClassId );
			if ( ctdUnit==NULL ) 
				ctdUnit = taskClassesList.AddDescUnit( taskClassId );
			
			if ( ctdUnit->nextExecutesec==0 ||
				CompareTimes( ctdUnit->nextExecutesec, ctdUnit->nextExecutemsec,
					taskNextETimesec, taskNextETimemsec ) > 0 )
			{					
				TaskClassesList::ListUnit *newCtdUnit = taskClassesList.SetDescUnitParams( taskClassId,
					taskNextETimesec, taskNextETimemsec, taskId );							

				WaitingThreadContext *wtc = GetWaitingWTCByClassTaskId( taskClassId );
				if ( wtc==NULL )
					wtc = GetWaitingWTCByClassTaskId( 0 );				

				if ( wtc!=NULL )
				{
					Trace( 4, "Find WTC. WTC->clientCntx - %d tClassId - %d tId - %d timeSec - %d timeMSec - %d\n", 
							wtc->clientThreadCntx, wtc->tcId, wtc->tId, wtc->timeSec, wtc->timeMSec );

					// ��������� ��� ����� ���������� wtc ������ ��� ����� ��������� ������
					if ( CompareTimes( wtc->timeSec, wtc->timeMSec,
							taskNextETimesec, taskNextETimemsec + 500 ) > 0 )
					{
						Trace( 4, "Get new task for waiting thread. WTC->clientCntx - %d tClassId - %d tId - %d timeSec - %d timeMSec - %d\n", 
							wtc->clientThreadCntx, wtc->tcId, wtc->tId, wtc->timeSec, wtc->timeMSec );
						// �������� ���������� ������ ����� �������
						wtc->wType = WaitingThreadContext::LEAVE_WAITING;
						wtc->sem.Post();
					}
				}
			}				
		}
		
	}		

	/** �������� ������ ������ �� ������� ����������� �������� */
	void SchedulerImp::RemoveTaskFromWork( TaskId tId, TaskList::ListUnit *taskUnit, bool findInWTC )
	{
		if ( findInWTC )
		{          
          for ( iterator i = wtc_list.begin(); i != wtc_list.end(); ++i ) {
            if ( (*i)->tId == tId ) {
              // ������� ����� � ��������
              (*i)->tId   = c_Undefined;
              (*i)->wType = WaitingThreadContext::LEAVE_WAITING;
              (*i)->sem.Post();
            }
          }
		}

		// ��������� ��� �� ������ ������ � ������ ������� ����� ( ������� ��� ���������� )
		int cid;
		taskUnit->task.GetClassId(cid);
		TaskClassesList::ListUnit *foundUnit = taskClassesList.GetDescUnit( cid );

		if ( foundUnit==NULL ) {
			foundUnit = taskClassesList.GetDescUnit( 0 );
			cid = 0;
		}

		if ( foundUnit->nextTaskId==tId )
		{			
			// ��������� ��������� ����� �������
			foundUnit->nextExecutesec  = 0;
			foundUnit->nextExecutemsec = 0;
			foundUnit->nextTaskId      = c_Undefined;
			
			TaskList::ListUnit *nextTaskDesc = taskList.FindNextTask( cid );
			if ( nextTaskDesc!=NULL )			
				WriteTaskNextExecutionTime( nextTaskDesc );
		}
	}

	/** ���������� ������ �� ���������� mutex. ���������� ��� TasksIterator */
	LightMutex &SchedulerImp::GetInternalMutex()
	{
		return mutex;
	}

	/** ������� ����������� � ����������� ������� ��������. ���������� �� ������ TasksIterator */
	void SchedulerImp::NotifyIteratorDestroy( TasksIteratorImp *tIter )
	{
		LightMutex::AutoUnlock autoUnlock( &mutex );

		createdIteratorsNum--;

		if ( createdIteratorsNum==0 && needFreeDelTask )
		{
			// ������� �� ������ ��� ������ �� �������� deleted
			taskList.EraseAllDeletedTasks();
			needFreeDelTask = false;
		}
	}
		
} // namespace KLSCH

/*
	\brief ����� ��� �������� ������� Scheduler
*/
KLSCH::Scheduler *KLSCH_CreateScheduler( int waitTime /*= c_Infinite*/ )
{
	return new KLSCH::SchedulerImp( waitTime );
}

