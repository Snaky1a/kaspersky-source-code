/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file TaskClassesList.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ���������� ������ ������� ����� ( ������������ ��� ��������������� ����� ).
 *
 */


#ifndef KL_TASK_CLASSES_LIST_H
#define KL_TASK_CLASSES_LIST_H

#include <ctime>

#include "std/sch/common.h"
#include "std/sch/errors.h"

#include "std/sch/task.h"

namespace KLSCH {

   /*!
    * \brief ������ ����� ������������.
    *
    */ 

	class TaskClassesList
	{
    public:

		/*! \struct ListUnit
			\brief ������������ ��� �������� ���������� ����������� � ����������� ������ �����
		*/
		struct ListUnit {

			ListUnit()
			{
				ctId = c_Undefined;
				nextExecutesec = 0;
				nextExecutemsec = 0;
				nextTaskId = c_Undefined;
			}

			TaskClassId		ctId;	//!< ������������� ������ �����
			int			waitTime;	//!< ����� �������� ��� ������� ������ �����

			/** �������� ��������� ������ ��� ������� */
			time_t	nextExecutesec;	//!< ����� ��������� ������� ������ ������� ������
			int    nextExecutemsec;

			TaskId		nextTaskId;	//!< ������������� ��������� ������ ������� ������
		};
		
		/*!
            \brief �����������.
        */
		TaskClassesList( );

		/*!
            \brief ����������. 
				   ����������� ������ ������� �����.				   
        */
        ~TaskClassesList( );
		
		/** ��������� � ������ ��������� ���������� ������ ����� */		
		ListUnit *AddDescUnit( const TaskClassId ctId,
			int waitTime = c_Undefined );

		/** ��������� WaitTime ��� ���������� ������ �����. ���� ������ ��� ������� ������ �����
		*    ��� �� �������, �� ������� ������.
		*/
		ListUnit *SetDescUnitWaitTime( const TaskClassId ctId,
			int waitTime = c_Undefined );

		/** ��������� ��������� ���������� ������ ����� */
		ListUnit *SetDescUnitParams( TaskClassId ctId,
			time_t nextExecutesec, int nextExecutemsec, TaskId nextTaskId );

		/** ���������� ��������� ���������� ������ ����� */		
		ListUnit *GetDescUnit( const TaskClassId ctId );

		/** ���������� ���������� ��������� ����� ����� � ������� ��� ��������� */
		ListUnit *GetNextDescUnit( const TaskClassId ctId, time_t currTime, int currTimeMSec, 
			int waitTime );

		/** �������� �� ���� ���������� */
		ListUnit *GetFirst(  );
		ListUnit *GetNext( TaskClassId prevCid );
		        
	private:
		/** ���������� ���������� */

		ListUnit	*taskClasses;		//!< ������������ ������ �������� ������� �����		
		int			 maxtaskClassesNum; //!< ���������� ���������� ��������� � ������� taskClasses

	protected:
		/** class helper functions */

		/** ���������� ��������� ����� */
		TaskClassesList::ListUnit *GetFreeUnit();

    };

}	// end namespace KLSCH

#endif // KL_TASK_CLASSES_LIST_H
