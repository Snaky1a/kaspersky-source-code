/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file TaskClassesList.cpp
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ����������� ������ ������ �������� ������� �����.
 *
 */

#include "std/sch/common.h"
#include "std/sch/errors.h"
#include "private.h"

#include "taskclasseslist.h"

namespace KLSCH {

	const int SchTaskClassesDescArrayIncreseValue = 10; // ���������� ��������� ��� ���������� �������

	//!\brief �����������.
	TaskClassesList::TaskClassesList( )
	{
		taskClasses			= NULL;
		maxtaskClassesNum	= 0;
	}
	
	//!\brief ����������. 
	TaskClassesList::~TaskClassesList( )
	{
		if ( taskClasses!=NULL ) delete []taskClasses;
		taskClasses = NULL;
		maxtaskClassesNum = 0;
	}
	
	/** ��������� � ������ ��������� ���������� ������ ����� */		
	TaskClassesList::ListUnit *TaskClassesList::AddDescUnit( const TaskClassId ctId,
		int waitTime /*= c_Undefined*/ )
	{
		ListUnit *foundUnit = GetDescUnit( ctId );
		if ( foundUnit!=NULL ) return foundUnit;	// ��� ����

		foundUnit = GetFreeUnit();

		foundUnit->ctId		= ctId;
		foundUnit->waitTime	= waitTime;

		Trace( 5, "TaskClassesList::AddDescUnit. TaskClassId - %d WaitTime - %d\n", 
			ctId, waitTime );

		return foundUnit;
	}

	/** ��������� WaitTime ��� ���������� ������ �����. ���� ������ ��� ������� ������ �����
	*    ��� �� �������, �� ������� ������.
	*/
	TaskClassesList::ListUnit *TaskClassesList::SetDescUnitWaitTime( const TaskClassId ctId,
			int waitTime /*= c_Undefined */ )
	{
		ListUnit *foundUnit = AddDescUnit( ctId, waitTime );

		foundUnit->waitTime = waitTime;

		Trace( 5, "TaskClassesList::SetDescUnitWaitTime. TaskClassId - %d WaitTime - %d\n", 
			ctId, waitTime );

		return foundUnit;
	}
	
	/** ��������� ��������� ���������� ������ ����� */
	TaskClassesList::ListUnit *TaskClassesList::SetDescUnitParams( TaskClassId ctId,
		time_t nextExecutesec, int nextExecutemsec, TaskId nextTaskId )
	{
		ListUnit *foundUnit = GetDescUnit( ctId );
		if ( foundUnit==NULL ) return NULL;		// �� �����

		Trace( 5, "TaskClassesList::SetDescUnitParams. TaskClassId - %d nextExecutesec - %d nextExecutemsec - %d nextTaskId - %d olValues - %d %d %d\n", 
			ctId, nextExecutesec, nextExecutemsec, nextTaskId, foundUnit->nextExecutesec, foundUnit->nextExecutemsec,
			foundUnit->nextTaskId );

		foundUnit->nextExecutesec  = nextExecutesec;
		foundUnit->nextExecutemsec = nextExecutemsec;
		foundUnit->nextTaskId	   = nextTaskId;		

		return foundUnit;
	}
	
	/** ���������� ��������� ���������� ������ ����� */		
	TaskClassesList::ListUnit *TaskClassesList::GetDescUnit( const TaskClassId ctId )
	{
		int foundPos = (-1);

		if ( taskClasses!=NULL ) 
		{
			// find in list
			for( foundPos = 0; foundPos < maxtaskClassesNum; foundPos++ )				
				if ( taskClasses[foundPos].ctId == ctId ||
					taskClasses[foundPos].ctId == c_Undefined ) break;				
		}

		if ( foundPos==(-1) || foundPos==maxtaskClassesNum ||
			taskClasses[foundPos].ctId == c_Undefined ) return NULL;

		else return &(taskClasses[foundPos]);
	}
	
	/** ���������� ���������� ��������� ����� ����� � ������� ��� ��������� */
	TaskClassesList::ListUnit *TaskClassesList::GetNextDescUnit( const TaskClassId ctId, time_t currTime, int currTimeMSec,
		int waitTime )
	{
		if ( taskClasses==NULL ) return NULL;

		ListUnit *foundUnit = NULL;
		if ( ctId!=0 )
		{
			// ����� ���������� ������
			foundUnit = GetDescUnit( ctId );
		}
		else
		{
			// ��� ��� ������ = 0 ( �.�. ������ �� ����� ������ )
			// ������� ������ � ���������� �������� �������
			time_t	minNextExecutesec = taskClasses[0].nextExecutesec;
			int		minNextExecutemsec = taskClasses[0].nextExecutemsec;

			// find in list
			int minPos = 0;
			for( int pos = 1; pos < maxtaskClassesNum; pos++ )
			{
				if ( taskClasses[pos].ctId == c_Undefined ) break;
				if ( minNextExecutesec==0 ||
					(minNextExecutesec>taskClasses[pos].nextExecutesec) ||
					(minNextExecutesec==taskClasses[pos].nextExecutesec &&
					 minNextExecutemsec>taskClasses[pos].nextExecutemsec) )
				{
					minNextExecutesec = taskClasses[pos].nextExecutesec;
					minNextExecutemsec = taskClasses[pos].nextExecutemsec;
					minPos = pos;
				}
			}

			foundUnit = &(taskClasses[minPos]);
		}
		if ( foundUnit==NULL ) return NULL;		// �� �����

		if ( waitTime==0 ) 
		{
			// ���� �� ������� ����� �� ����� �� �������� ������ ���� ��� ���� �� �������, 
			//	�� ����� ������� ( ����� � ������ �������� )
			if ( foundUnit->waitTime>0 ) waitTime = foundUnit->waitTime;
			else
				waitTime = taskClasses[0].waitTime; 
		}		

		if ( waitTime!=c_Infinite ) waitTime += currTimeMSec; // ��������� msec � timeOut

		if ( foundUnit->nextExecutesec!=0 && CompareTimes( currTime, waitTime, 
			foundUnit->nextExecutesec, foundUnit->nextExecutemsec )>=0) // � ������� ������ ���� ������ ��� �����������
		{
			Trace( 6, "TaskClassesList::GetNextDescUnit. TaskClassId - %d nextExecutesec - %d nextExecutemsec - %d nextTaskId - %d\n", 
				foundUnit->ctId, foundUnit->nextExecutesec, foundUnit->nextExecutemsec, 
				foundUnit->nextTaskId );

			return foundUnit;
		}
		else
		{
			Trace( 6, "TaskClassesList::GetNextDescUnit. NULL\n" ); 
			return NULL;	// ���� ������ ��� ��������� ���
		}
	}

	/** �������� �� ���� ���������� */
	TaskClassesList::ListUnit *TaskClassesList::GetFirst(  )
	{
		ListUnit *foundUnit = GetDescUnit( 0 );
		return foundUnit;
	}

	TaskClassesList::ListUnit *TaskClassesList::GetNext( TaskClassId prevCid )
	{
		int foundPos = (-1);

		if ( taskClasses!=NULL ) 
		{
			// ���� ����������
			for( foundPos = 0; foundPos < maxtaskClassesNum; foundPos++ )				
				if ( taskClasses[foundPos].ctId == prevCid ) break;
		}

		if ( foundPos!=(-1) && foundPos < ( maxtaskClassesNum - 1 ) ) // ����� ������� ��� ��������� �� ���������
		{
			foundPos++; 
			if ( taskClasses[foundPos].ctId == c_Undefined ) return NULL;
			else return &(taskClasses[foundPos]);
		}
		else
			return NULL;
	}	

	/** ���������� ��������� ����� */
	TaskClassesList::ListUnit *TaskClassesList::GetFreeUnit()
	{
		int foundPos = (-1);

		if ( taskClasses!=NULL ) 
		{
			// find in list
			for( foundPos = 0; foundPos < maxtaskClassesNum; foundPos++ )				
				if ( taskClasses[foundPos].ctId == c_Undefined ) break;				
		}

		if ( foundPos==(-1) || foundPos==maxtaskClassesNum ) 
		{
			// �������� ������
			ListUnit *savePtr = taskClasses;
			
			foundPos = maxtaskClassesNum;

			maxtaskClassesNum += SchTaskClassesDescArrayIncreseValue;
			
			taskClasses = new TaskClassesList::ListUnit[maxtaskClassesNum];
						
			if ( savePtr ) 
			{
				memcpy( taskClasses, savePtr, 
					sizeof(TaskClassesList::ListUnit)*(maxtaskClassesNum-SchTaskClassesDescArrayIncreseValue) );
				delete []savePtr;
			}
		}

		return &(taskClasses[foundPos]);
	}

}	// end namespace KLSCH
