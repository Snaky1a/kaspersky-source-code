/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file Scheduler.h
 * \author ����� �����������
 * \date 2002
 * \brief ������� ��������� ������-������������
 *
 *  ������ ���� �������� �������� ������������ ���������� ������-������������ Scheduler.
 *  ������-����������� ��������� ���������� ������ � �������� ������ �� ����������
 *  � ������������ ������ �������.  ������ �������� ������ ������ ������ Scheduler
 *  ���������� � ����� CS AdminKit\DESIGN\Modules\Scheduler.doc
 *
 */


#ifndef KLSCH_H
#define KLSCH_H

#include "std/base/klbase.h"

#include "std/sch/common.h"
#include "std/sch/task.h"
#include "std/sch/tasksiterator.h"

namespace KLSCH {

/*!
 * \brief ������� ��������� ������ Scheduler.  �������� ���������������� ������
 *		  ���� �������� � ����� ����������.
 */ 

    class Task;
    class TasksIterator;
    class TaskResults;

	class Scheduler
	{

    public:

	/*!
	  \brief ����������� ����������.
	 */
		virtual ~Scheduler() {}
	
	/*!
      \brief ����� ��������� ����� ������ � ������ �����.

      Scheduler �������� �������� ������ �� ���������� ������ �
      ���������� ������� ������������� ����������� ������. ������
      ����� �������� ������������� ������ � ���������� id_ptr. �
      ���� ������ Scheduler ���� ������� ������ � �������� ���������������,
      ���� ���������� ������ ERR_ID_EXISTS ���� ������ � �����
      ��������������� ��� ����������.

      \param t		[in]  �������� ����������� ������.
      \param id_ptr [out] ��������� �� ����������, ������� ����� ����������������� 
						  ��������������� ����� ����������� ������. ���� � ������� Task
						  �������� TaskId �������� ( ��. ����� SetTaskId ) �� �� � �����
						  ����������� � �������� �������������� ������ ( �������������� 
						  ��������� �������������� ������������ �� ����� ).
      \return ��� ������

    */
      
        virtual Errors AddTask( const Task *t, TaskId& id_ptr ) = 0;

    /*!
      \brief ������� ������ � �������� ���������������.

      Scheduler ������� ������ �� ������ ����� �� ����������.  �����,
      ��������� ���������� ������, ������������� �� ���������� ������
      ������ ���� ��� ������������ ������ ERR_NO_MORE_TASKS.

      \param id [in] ������������� ��������� ������.
      \return ��� ������

    */

        virtual Errors DelTask( const TaskId id ) = 0;

	/*!
      \brief ���������������� ������ ��������� ������.

      Scheduler �� ����� ������� ������ ����� �� ���������� ���� ��� ��� �� ����� �������
	  ������� ResumeTask.

      \param id [in] ������������� ������.
      \return ��� ������ ( ERR_TASK_ID, ERR_TASK_STATE, ERR_NONE )

    */

        virtual Errors SuspendTask( const TaskId id ) = 0;

	/*!
      \brief ������������ ������ ���������������� ������ ��������� ������.

      \param id [in] ������������� ������.
      \return ��� ������ ( ERR_TASK_ID, ERR_TASK_STATE, ERR_NONE )

    */

        virtual Errors ResumeTask( const TaskId id ) = 0;

	/*!
      \brief ���������� ��������� ����� ������� ������.

      \param id [in] ������������� ������.
	  \param sec [out] ��������������� ����� ���������� ������ � ������� time_t.
      \param msec [out] ��������������� ����� ���������� ������ � msec. ��������
                             ���������� sec � msec ������������.
      \return ��� ������ ( ERR_TASK_ID, ERR_NONE, ERR_SCHEDULE )
    */

        virtual Errors GetTaskNextExecutionTime( const TaskId id, time_t& sec, int& msec ) = 0;

    /*!
      \brief ������� �������� ��� ��������� ������ �����.

      ������� �������� ��� ��������� ������ ����� � ���������� ���
      �������.  ������ ����� �������� ����� ����� ��� ���������.
      �� ��������� ��������������� ��� ������.

      \param it [out] �������� ��� ��������� ������ �����.
      \param cid [in] ����� ����� ��� ��������� ����������.
      \return ��� ������

    */


        virtual Errors CreateTasksIterator(  
            TasksIterator *it, 
            TaskClassId cid = 0 ) = 0;


    /*!
      \brief ������� �������� ��� ��������� ������ "���������" �����.

      ������� �������� ��� ��������� ������ "���������" ����� (�.�. �����,
      ������� �� ��������� ���������� � ������� ����������� ��� ����� �������)
      � ���������� ��� �������. ������ ����� �������� ����� ����� ��� ���������.
      �� ��������� ��������������� ��� ������.

      \param it [out] �������� ��� ��������� ������ "���������" �����.
      \param cid [in] ����� ����� ��� ��������� ����������.
      \return ��� ������

    */


        virtual Errors CreateHangingTasksIterator( 
            TasksIterator *it, 
            TaskClassId cid = 0 ) = 0;


    /*!
      \brief ���������� ����� �����, ��������� ���������� ������ Scheduler.

      \param num [out] ����� �����, ������������ ������ Scheduler.
      \param cid [in] ����� ����� ��� ��������� ����� �����.  �� ���������
                      ������������ ������ ����� �����.
      \return ��� ������

    */


        virtual Errors GetTasksNumber( int& num, TaskClassId cid = 0) const = 0;

	/*!
	  \brief ��������� scheduler � ����� �������������.

      ��� ������ � ������ ������ ������� WaitTaskExecution ���������� ERR_SUSPEND_MODE.
	  ��� ������, ������������ � ������ ������ ������� � WaitTaskExecution ���� �������� ��
	  ������� � ����� �������� ERR_SUSPEND_MODE.
      
      \return ��� ������

    */	

		virtual Errors Suspend( ) = 0;

	/*!
	  \brief �������� ����������� �� ������ ������������� � ����������.
            
      \return ��� ������

    */	

		virtual Errors Resume( ) = 0;

    /*!
      \brief ������������� ������������ ����� �������� ������ �� ������ 
             ���������� ������ (msec).

      ����� ������������� ������������ ����� �������� ������ �� ������ 
      ���������� ������ ��������� ������ � �������������.  � ������, ���� 
      ����� �� ������ ���������� ������ ����� �������������� � ������ ������,
      ����� ����������� � ������ WaitTaskExecution.  � ��������� ������
      ����� WaitTaskExecution ���������� ���������� ���������� � �������
      ERR_NO_MORE_TASKS.  �� ��������� ����� �������� ��������������� ��� �����
      ���� �������.

      \param waitTime [in] ����� ����������� ��� �������� ������� ������� 
                           ���������� ������.
      \param cid [in] ����� ����� ��� ������������ ������� ��������.
      \return ��� ������

    */

        virtual Errors SetWaitTime( int waitTime = 10000, TaskClassId cid = 0 ) = 0;


    /*!
      \brief ���������� ������������ ����� �������� ������ �� ������ 
             ���������� ������ (msec).

      \param waitTime [out] ����� ����������� ��� �������� ������� ������� 
                           ���������� ������.
      \param cid [in] ����� ����� ��� ��������� ������� ��������.
      \return ��� ������

    */

        virtual Errors GetWaitTime( int& waitTime, TaskClassId cid = 0 ) = 0;


    /*!
      \brief ��������� ����� ������� �� ������� ���������� ������.

      ����� ��������� ����� ������� �� ������� ���������� ������. ������������
      ��� ������ callback ���������� � ���� ������ � ���������� ����������
      ������������ �������. ����� ����� ������ �������� �� ���������� ����������
      ������ � ������ ������� �� ����� ��������� ������ � ����.
      ������ ����� ����������, ���������� ����� ������
      ������ �� ������� ������ ������� ������.  �� ��������� ��������� ����������
      ������ ������ ������.  ���� ����� �� ���������� ��������� ������ ����� 
      ���������, ������������ ������ ERR_NO_MORE_TASKS.

      \param res [out] ��������� ���������� ������.  ������ ������ �������
                       ���������� ���������� ������ ����� ��������� ������
                       � ����.
	  \param threadContex [in] �������� ����������� ������. ������ �������� ������������� 
							   ����� ��������� ������� �������. ������ �������� ����� ��������
							   � �������� ������ ( ����� Task ) �� ����� �� ���������. ����� ����
							   ����������� ��� ������ � �������� ��������.
      \param waitTime [in] ����� ����������� ��� �������� ������� ������� 
                           ���������� ������.  �� ��������� ������������
                           �����, ������������ � SetWaitTime.
      \param cid [in] ����� ����� ��� �������. �� ��������� ����������� ������
                      ������ ������.
	  \param waitFlag [in] ������� ������������� �������� ������ ������� ���� � ������ ���� ���
					  ������� �� ��������� �����. �� ��������� ������������
                      �����, ������������ � SetWaitTime.
      \return ��� ������

    */

        virtual Errors WaitTaskExecution(   TaskResults** res,
									void *threadContex,
                                    int waitTime = 0, 
                                    TaskClassId cid = 0,
									bool waitFlag = true ) = 0;


	/*!
      \brief ������������� ��������� ��� ��������� ������

      \param id [in] ������������� 
	  \param par [in] ������ �� ��������� ��� ������� ������.
      \return ��� ������

    */

        virtual Errors SetPramsForTask( const TaskId id, TaskParams * par ) = 0;

    };

} // namespace KLSCH

/*
	\brief ����� ��� �������� ������� Scheduler
*/
KLCSC_DECL KLSCH::Scheduler *KLSCH_CreateScheduler( int waitTime = KLSCH::c_Infinite );

#endif // KLSCH_H
