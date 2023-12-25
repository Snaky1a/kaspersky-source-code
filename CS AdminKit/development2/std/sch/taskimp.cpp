/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file TaskImp.cpp
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ����������� ������ ������ ��� ������� �������-�������������.
 *
 */

#include <ctime>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "std/thr/sync.h"
#include "std/trc/trace.h"
#include "std/sch/common.h"
#include "std/sch/errors.h"
#include "std/sch/schedule.h"
#include "std/sch/taskparams.h"
#include "std/time/kltime.h"
#include "std/sch/millisecondsschedule.h"

#include "taskimp.h"
#include "private.h"


//!\brief ��������������� ����� ��� ��������� ���������� ������
class SchedulerThreadPriority
{
public:
	SchedulerThreadPriority() { settingNewPriorityFlag = false; }

	void SetNewPriority( KLSCH::Task::TaskThreadPriority ttPriority )
	{
#ifdef _WIN32
		// ��������� ������� ��������� ������
		threadPrevPriority = GetThreadPriority( GetCurrentThread() );
		settingNewPriorityFlag = true;

		int newThreadPriority = THREAD_PRIORITY_NORMAL;
		if ( ttPriority==KLSCH::Task::TP_Low )
			newThreadPriority = THREAD_PRIORITY_LOWEST;
		if ( ttPriority==KLSCH::Task::TP_Hight )
			newThreadPriority = THREAD_PRIORITY_HIGHEST;

		SetThreadPriority( GetCurrentThread(), newThreadPriority );
#endif	
	}

	void RestorePrioroty()
	{
#ifdef _WIN32
		if ( settingNewPriorityFlag )
		{
			SetThreadPriority( GetCurrentThread(), threadPrevPriority );
			settingNewPriorityFlag = false;
		}
#endif
	}

protected:
	int		threadPrevPriority;
	bool	settingNewPriorityFlag;
};

namespace KLSCH {

			
	enum State {
			Created,			///< ������ ������ ��� ������� � ��� �� ������ � Scheduler
			Scheduled,			///< ������ ���������� � ��������� �������� ������
			WaitForRunning,		///< ������ ������ ������� �������
			Running,			///< ������ �����������
			Suspended,			///< ������ ������� �������������� ( ��. Scheduler::SuspendTask )
			Completed,			///< ������ ��� ����������� � ������ ����������� �� ����� ( �� ������ �� ���������� )
			Deleted				///< ������ ������� ( ��������� �� ������ ����� ������� ����� )
		};

	// ������������ ��� ������ ��������� ������ ( ������ ��� ������� )
	char STATE_STR_DESC[10][32] = { "Created", "Scheduled", "WaitForRunning", "Running",
								"Suspended", "Completed", "Deleted" };


	//! \brief ������������.
	TaskImp::TaskImp( )
	{		
		InitializeVars();
	}

	TaskImp::TaskImp( TaskId id, TaskClassId cid )
	{
		InitializeVars();
		tId = id;
		cId = cid;
	}

	const TaskImp &TaskImp::operator = ( const TaskImp &t )
	{
		tId = t.tId;
		cId = t.cId;
		maxExecuteTime	= t.maxExecuteTime;

		if ( t.schedule!=NULL ) t.schedule->Clone( &schedule );
		else schedule = NULL;
		if ( t.params!=NULL ) params = t.params->Clone( );
		else params = NULL;

		nextExeTime = t.nextExeTime; nextExemsec = t.nextExemsec;			
		lastExeTime = t.lastExeTime; lastExemsec = t.lastExemsec;

		state		= t.state;		

		startSysTick = t.startSysTick;
		func		 = t.func;
		func2		 = t.func2;

		threadCntx   = t.threadCntx;
		delAfterRun	 = t.delAfterRun;

		startDeltaTimeout = t.startDeltaTimeout;
		preparativeTimeout = t.preparativeTimeout;
		preparativeStart = t.preparativeStart;
		if ( t.accessorySchedule!=NULL ) t.accessorySchedule->Clone( &accessorySchedule );
		else accessorySchedule = NULL;
		
		taskThreadPriority = t.taskThreadPriority;

		return *this;
	}

	void TaskImp::InitializeVars()				//!< �������������� ���������� ����������
	{
		tId = 0;
		cId = 0;
		maxExecuteTime = c_Infinite;
		schedule	= NULL;
		params		= NULL;

		nextExeTime = nextExemsec = c_Undefined;
		lastExeTime = lastExemsec = c_Undefined;

		state		= Created;		

		startSysTick = 0;
		func		 = NULL;
		func2		 = NULL;
		threadCntx	 = NULL;
		startDeltaTimeout = 0;
		preparativeTimeout = 0;
		preparativeStart = false;
		accessorySchedule = NULL;
		taskThreadPriority = TP_Normal;

		delAfterRun  = false;
	}

	//!\brief ����������. ������� ������ Schedule.
	TaskImp::~TaskImp( )
	{
		if ( schedule!=NULL ) delete schedule;
		if ( params!=NULL ) delete params;
		if ( accessorySchedule!=NULL ) delete accessorySchedule;
	}

    //!\brief ������������� ������������� ������.
	Errors TaskImp::SetTaskId( TaskId id )
	{
		tId = id;
		return ERR_NONE;
	}	
	
	//!\brief ���������� ������������� ������.
	Errors TaskImp::GetTaskId( TaskId& id ) const
	{
		id = tId;
		return ERR_NONE;
	}	
	
	//!\brief ������������� ������������� ������ ������.
	Errors TaskImp::SetClassId( TaskClassId cid )
	{
		cId = cid;
		return ERR_NONE;
	}	
	
	//!\brief ���������� ������������� ������ ������.
	Errors TaskImp::GetClassId( TaskClassId& cid ) const
	{
		cid = cId;
		return ERR_NONE;
	}	
	
	//!\brief ���������� ������� ��������� ������.
	Errors TaskImp::GetCurrentState( TaskImp::State& s ) const
	{
		s = state;
		return ERR_NONE;
	}
	
	//!\brief ������������� ���������� ��� ������� ������.
	Errors TaskImp::SetSchedule( Schedule* s )
	{
		if ( schedule!=NULL ) delete schedule;
		s->Clone( &schedule );		
		return ERR_NONE;
	}
	
	//!\brief ���������� ��������� �� ���������� ��� ������� ������.
	Errors TaskImp::GetSchedule( const Schedule ** s) const
	{
		*s = schedule;
		return ERR_NONE;
	}
	
	//!\brief ������������� callback ��� ������� ������.
	Errors TaskImp::SetCallback( TaskCallback cb)
	{
		func = cb;
		return ERR_NONE;
	}

	//!\brief ������������� ����������� callback ��� ������� ������.
	Errors TaskImp::SetCallback2( TaskCallback2 cb)
	{
		func2 = cb;
		return ERR_NONE;
	}
	
	//!\brief ���������� ������������� callback ��� ������� ������.
	Errors TaskImp::GetCallback( TaskCallback& cb ) const
	{
		cb = func;
		return ERR_NONE;
	}
	
	//!\brief ������������� ��������� ��� ������� ������.
	Errors TaskImp::SetTaskParams( TaskParams* par )
	{
		if ( par==NULL ) return ERR_INVALID_OBJECT;
		params = par->Clone(); // �������� ���������
		return ERR_NONE;
	}
	
	//!\brief ���������� ����� ���������� ��� ������� ������.
	Errors TaskImp::GetTaskParams( const TaskParams** par ) const
	{
		*par = params;
		return ERR_NONE;
	}

	//!\brief ������������� ��������� � ������� ����� ���������� ����� ������� ������ (msec).
    Errors TaskImp::SetStartDeltaTimeout( int timeOut )
	{
		if ( timeOut<0 ) return ERR_TIME_INTERVAL;
		
		startDeltaTimeout = timeOut;
		return ERR_NONE;
	}

    //!\brief ���������� ��������� � ������� ����� ���������� ����� ������� ������ (msec).
    Errors TaskImp::GetStartDeltaTimeout(int& timeOut) const
	{
		timeOut = startDeltaTimeout;
		return ERR_NONE;
	}
	
	//!\brief ������������� timeout ��� ����������������� �������
    Errors TaskImp::SetPreparativeStartTimeout( int timeout )
	{
		if ( timeout<0 ) return ERR_TIME_INTERVAL;
				
		preparativeTimeout = timeout;
		if ( preparativeTimeout>0 ) preparativeStart = true;
		else preparativeStart = false;
		
		if ( accessorySchedule!=NULL ) delete accessorySchedule;
		accessorySchedule = NULL;

		return ERR_NONE;
	}

	//!\brief ���������� timeout ��� ����������������� �������
	Errors TaskImp::GetPreparativeStartTimeout( int &timeout ) const
	{
		timeout = preparativeTimeout;		
		return ERR_NONE;
	}
	
	//!\brief ������������� ������������ ����� ���������� ������ (msec).
	Errors TaskImp::SetMaxExecutionTime( int maxTime /* = 10000*/ )
	{
		maxExecuteTime = maxTime;
		return ERR_NONE;
	}
	
	//!\brief ���������� ������������ ����� ���������� ������ (msec).
	Errors TaskImp::GetMaxExecutionTime(int& maxTime) const
	{
		maxTime = maxExecuteTime;
		if ( maxTime<0 ) maxTime = 0;
		return ERR_NONE;
	}

	//!\brief ���������� ����� ����������� ������� ������.
    Errors TaskImp::GetRunningTime( int &msec )
	{
		msec = 0;
		if ( state!=Running || startSysTick==0 ) return ERR_TASK_STATE;
		
		msec = (KLSTD::GetSysTickCount()-startSysTick);
		
		return ERR_NONE;
	}
	
	//!\brief ������������� ��������� ����� ���������� ������.
	Errors TaskImp::SetLastExecutionTime( time_t sec /*= 0*/,  int msec /*= 0*/ )
	{
		lastExeTime = sec;
		lastExemsec = msec;

		return ERR_NONE;
	}
	
	//!\brief ���������� ��������� ����� ���������� ������.
	Errors TaskImp::GetLastExecutionTime( time_t& sec, int& msec ) const
	{
		sec = lastExeTime;
		msec = lastExemsec;
		if ( sec<0 ) sec = 0;
		if ( msec<0 ) msec = 0;

		return ERR_NONE;
	}
	
	//!\brief ���������� ��������z� ��������������� ����� ���������� ������.
	Errors TaskImp::GetNextExecutionTime( time_t& sec, int& msec )
	{
		if ( schedule==NULL ) return ERR_SCHEDULE;	

		if ( nextExeTime==c_Undefined )
			CalculateNextExecutionTime();

		sec = nextExeTime;
		msec = nextExemsec;
		if ( sec<0 ) sec = 0;
		if ( msec<0 ) msec = 0;

		return ERR_NONE;
	}

	//!\brief ������������� ���� �������� ������ ����� ����� �� ����������.
    Errors TaskImp::SetDelAfterRunFlag( bool delFlag )
	{
		delAfterRun = delFlag;
		return ERR_NONE;
	}


	//!\brief ���������� ���� �������� ������ ����� ����� �� ����������.
    Errors TaskImp::GetDelAfterRunFlag( bool &delFlag ) const
	{
		delFlag = delAfterRun;
		return ERR_NONE;
	}

	//!\brief ������������� ��������� ������ � ������� ������ ����������� ������.
	Errors TaskImp::SetTaskThreadPriority( TaskThreadPriority ttPriority )
	{
		taskThreadPriority = ttPriority;
		return ERR_NONE;
	}
	
	//!\brief ���������� ��������� ������ � ������� ������ ����������� ������.
	Errors TaskImp::GetTaskThreadPriority( TaskThreadPriority &ttPriority ) const
	{
		ttPriority = taskThreadPriority;
		return ERR_NONE;
	}
	
	//!\brief ���������� �������� ������, � ������� ������������� ���������� ������.
	Errors TaskImp::GetThreadContext( void **tCntx ) const
	{
		*tCntx = threadCntx;

		return ERR_NONE;
	}

	//!\brief ������� �������� ����� �������
	void TaskImp::Clone( Task **ppTask ) const
	{
		*ppTask = KLSCH_CreateTask();

		*((TaskImp *)*ppTask) = *this;
	}
	
	//!\brief ���������� ��������� �� ���������� ��� ������� ������ ���
	//		 ���������� �����������.
	Errors TaskImp::GetWritableSchedule( Schedule ** s)
	{
		*s = schedule;
		return ERR_NONE;
	}

	void TaskImp::CalculateNextExecutionTime( time_t currTime ) //!< ����������� ��������� ����� �������
	{
		int startDelta = 0;
		if ( currTime==0 ) time( &currTime );

		if ( delAfterRun )
		{
			time_t firstExeSec;	int firstExeMSec;
			bool runMissed;
			schedule->GetFirstExecutionTime( firstExeSec, firstExeMSec );
			schedule->GetRunMissedFlag( runMissed );

			if ( ( lastExeTime!=c_Undefined && lastExeTime!=0 && lastExeTime >= firstExeSec ) 
				|| ( firstExeSec < currTime && !runMissed ) )
			{
				nextExeTime = ULONG_MAX;	// ������ RunOnce ��� ���� ��������� ��� �� ����� ��� �������
				return;
			}
		}

		if ( startDeltaTimeout>0 ) 
		{
			startDelta = KLSTD_Random( 0, startDeltaTimeout );
		}
		
		//KLTRACE4( L"SCH", L"TaskImp::CalculateNextExecutionTime startDelta - %d startDeltaTimeout - %d\n", 
		//			startDelta, startDeltaTimeout );
		if ( preparativeStart && accessorySchedule!=NULL )
		{
			time_t saveNextExeTime = nextExeTime;			

			accessorySchedule->CalculateNextExecutionTime( nextExeTime, nextExemsec, currTime, 
				lastExeTime, lastExemsec, startDelta );
			if ( accessorySchedule!=NULL ) delete accessorySchedule;
			accessorySchedule = NULL;
			preparativeStart = false;

			// ������ �������� ������� ������� ������ ���� ����� ������� ��������������� ������
			// ���� ����� ��� ����� �� ���������� ( ������ ��� ��������� ��������� ���������� �����
			// ��������������� � �������� �������� ������ �� ���� ������� )
			long prepSec = preparativeTimeout / c_MillisecondsInSecond;
			long delta;
			if ( (saveNextExeTime + prepSec) < currTime )
			{
				delta = prepSec;
			}
			else
			{
				delta = (saveNextExeTime + prepSec) - currTime;
			}
			nextExeTime = currTime + delta;

		}
		else
		{
			schedule->CalculateNextExecutionTime( nextExeTime, nextExemsec, currTime, 
				lastExeTime, lastExemsec, startDelta );
			if ( preparativeTimeout>0 ) preparativeStart = true;
		}
		
		if ( preparativeStart && nextExeTime==c_Undefined && accessorySchedule==NULL )
			preparativeStart = false;

		if ( preparativeStart )
		{
			// ��������������� ������ ( ������������ ����� )
			long prepSec = preparativeTimeout / c_MillisecondsInSecond;
			time_t saveNextExeTime = nextExeTime;
			time_t saveNextExemsec = nextExemsec;

			if ( prepSec > nextExeTime ) nextExeTime = 0;
			else nextExeTime -= prepSec;

			if ( nextExeTime<currTime ) nextExeTime = currTime;

			// ������� ��������������� ����������
			if ( accessorySchedule!=NULL ) delete accessorySchedule;
			accessorySchedule = NULL;
			accessorySchedule = KLSCH_CreateMillisecondsSchedule();
			accessorySchedule->SetPeriod(0);
			accessorySchedule->SetFirstExecutionTime( saveNextExeTime, saveNextExemsec );
		}

		Trace( 4, "Next execution time has been calculated. TaskId - %d nextExeTime - %d nextExemsec - %d lastExeTime - %d lastExeMSec - %d\n", 
			tId, nextExeTime, nextExemsec, lastExeTime, lastExemsec  );
	}

	/** ����������� ��������� ����� ������� ����� Suspend ��������� */
	void TaskImp::CalculateNextTimeAfterSuspend( )
	{
		bool runMiss = false;
		if ( schedule ) schedule->GetRunMissedFlag( runMiss );

		if ( !runMiss ) CalculateNextExecutionTime( ); // ������ ��� �� runMissed �����
	}

	/** class helper functions */	
	void TaskImp::SetCurrState( State newState ) //!< ������������� ������� ��������� ������
	{		
		Trace( 4, "Task state has been changed. TaskId - %d OldState - '%s' NewState - '%s'\n", 
			tId, STATE_STR_DESC[state], STATE_STR_DESC[newState] );

		if ( state==Deleted ) return; // ������ �������� ������ ������ ���� ��� ��� Deleted

		state = newState;

		if ( state==Suspended )
		{
			bool runMiss = false;
			if ( schedule ) schedule->GetRunMissedFlag( runMiss );

			// ���������� ������ � �������������� ���������
			if ( !runMiss ) 
			{
				nextExeTime = c_Undefined;
				nextExemsec = c_Undefined;
				SetLastExecutionTime( c_Undefined, c_Undefined ); 			
			}
		}
	}
	
	void TaskImp::SetThreadContext( void *tCntx ) //!< ������������� �������� ������ ��� ������
	{
		threadCntx = tCntx;
	}

	void TaskImp::Call( TaskResults** result, bool &delTask )    //!< �������� callback ������
	{
		TaskThreadPriority saveTp = taskThreadPriority;
		SchedulerThreadPriority threadPriority;

		if ( saveTp!=TP_Normal ) {
			// ������������� ��������� ����������
			threadPriority.SetNewPriority( saveTp );
		}
		
		startSysTick = KLSTD::GetSysTickCount();

		if ( nextExeTime!=c_Undefined && !preparativeStart )
			lastExeTime = nextExeTime, lastExemsec = nextExemsec;

		if ( func2!=NULL )
		{
			TaskOptions to(preparativeStart,preparativeTimeout);
			func2( params, &to, result );
		}
		else
		{
			func( params, result );
		}

		if ( !preparativeStart ) delTask = delAfterRun;

		if ( saveTp!=TP_Normal ) {
			// �������������� ��������� ������
			threadPriority.RestorePrioroty();
		}

		Trace( 4, "Call task. TaskId - %d lastExeTime - %d preparativeStart - %d\n", tId, preparativeStart, 
			lastExeTime );

		startSysTick = 0;
	}

	bool TaskImp::IsTaskHanging() const		//!< ���������� �������� �� ������ ������ �������
	{
		if ( state!=Running || startSysTick==0 ) return false;

		if ( maxExecuteTime==c_Infinite ) return false;

		if ( KLSTD::DiffTickCount(KLSTD::GetSysTickCount(),startSysTick)>(unsigned)maxExecuteTime ) return true;
		else return false;
	}
	
}	// end namespace KLSCH

/*
	\brief ����� ��� �������� ������� Task
*/
KLSCH::Task *KLSCH_CreateTask()
{
	return new KLSCH::TaskImp();
}
