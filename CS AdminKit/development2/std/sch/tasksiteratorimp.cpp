/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file TasksIteratorImp.cpp
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ����������� ������ ������-��������� ���
 *        ��������� ������ �����.
 *
 */

#include <ctime>
#include <stdio.h>

#include "std/sch/common.h"
#include "std/sch/errors.h"
#include "schedulerimp.h"

#include "std/sch/task.h"
#include "tasksiteratorimp.h"

#include "private.h"

namespace KLSCH {

	//!\brief �����������.	
	TasksIteratorImp::TasksIteratorImp()
	{
		scheduler=NULL;
	}
	
	//!\brief ����������.
	TasksIteratorImp::~TasksIteratorImp()
	{	
		if ( scheduler!=NULL ) scheduler->NotifyIteratorDestroy( this );
	}
	
	//! \brief ������� ������������� ���������.
	void TasksIteratorImp::Init( SchedulerImp *sch, TaskList *lst, TaskClassId fCid,
		bool hanging )
	{
		if ( scheduler!=NULL ) scheduler->NotifyIteratorDestroy( this );

		scheduler	= sch;
		taskList	= lst;	
		currentTid  = c_Undefined;
		filterCid   = fCid;
		onlyHanging = hanging;
	}

	//!\brief ������������� �������� �� ������ ������.
    Errors TasksIteratorImp::Reset()
	{
		currentTid  = c_Undefined;

		return ERR_NONE;
	}

    //!\brief ���������� ����������� ��������� �� ��������� ������ � ������.
    Errors TasksIteratorImp::Next( const Task ** t, bool& hasMoreTasks )
	{
		if ( scheduler==NULL || taskList==NULL ) return ERR_INVALID_OBJECT;

//        XTRACE( "+1 " );
		LightMutex::AutoUnlock  autoUnlock( &scheduler->GetInternalMutex() );
//        XTRACE( "+2 " );

		hasMoreTasks = false;
		*t = NULL;
		
		TaskList::ListUnit *findUnit = taskList->GetNextUnit( currentTid, filterCid );

		if ( findUnit!=NULL )
		{
			if ( onlyHanging && !findUnit->task.IsTaskHanging() ) 
				findUnit = NULL;
			else
			{				
				findUnit->task.GetTaskId( currentTid );
				
				TaskList::ListUnit *nextUnit = taskList->GetNextUnit( currentTid, filterCid );
				if ( nextUnit!=NULL && onlyHanging && !nextUnit->task.IsTaskHanging() ) 
					nextUnit = NULL;
				
				if ( nextUnit ) hasMoreTasks = true;
				
				*t = &(findUnit->task);
			}
		}

		return ERR_NONE;
	}

}	// end namespace KLSCH

/*
	\brief ����� ��� �������� ������� Scheduler
*/
KLSCH::TasksIterator *KLSCH_CreateTasksIterator()
{
	return new KLSCH::TasksIteratorImp;
}
