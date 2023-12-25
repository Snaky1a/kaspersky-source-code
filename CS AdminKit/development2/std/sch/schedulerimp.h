/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file SchedulerImp.h
 * \author ����� �����������
 * \date 2002
 * \brief ������� ��������� ������-������������
 *
 *  ������ ���� �������� �������� ���������� ������-������������ Scheduler.
 *  ������-����������� ��������� ���������� ������ � �������� ������ �� ����������
 *  � ������������ ������ �������.  ������ �������� ������ ������ ������ Scheduler
 *  ���������� � ����� CS AdminKit\DESIGN\Modules\Scheduler.doc
 *
 */


#ifndef KLSCHIMP_H
#define KLSCHIMP_H

#ifdef _MSC_VER
	#pragma warning (disable : 4786)
#endif

#include <list>

#include "std/sch/common.h"
#include "std/sch/errors.h"
#include "private.h"

#include "std/sch/scheduler.h"

#include "std/sch/task.h"
#include "tasklist.h"
#include "taskclasseslist.h"
#include "tasksiteratorimp.h"

namespace KLSCH {

/*!
 * \brief ������� ��������� ������ Scheduler.  �������� ���������������� ������
 *		  ���� �������� � ����� ����������.
 */ 

    class Task;
    class TasksIterator;
    class TaskResults;
// class SchedulerImp;
//    class SchedulerImp::WaitingThreadContext;
// typedef std::list<KLSCH::SchedulerImp::WaitingThreadContext *> container_type;

    // _WaitingThreadContext defined here to workarounv VC6 bug
    // with incomplete class/inner class definition, like
    // BaseClass::InnerClass, in the context like
    // list<BaseClass::InnerClass *>.

    /*! \struct WaitingThreadContext
      \brief ������������ ��� �������� ���������� ���������� ������ ������
    */
    struct _WaitingThreadContext {
        /*\enum ��� �������� */
        enum WaitingType {
          NO_WAITING,			//!< ������� ���������� ���������
          TASK_WAITING,		//!< ����� ������� ������������ ������
          NO_TASK_WAITING,	//!< ������ ��� ������ ���, �� ������ ���� ����������� timeout
          LEAVE_WAITING,		//!< ������ ������ ������������� ������� ������� ( ������� ���� ��� ����� ������� �� �������� )
          TASK_RUNNING		//!< �������� ��������� ������
        };

        _WaitingThreadContext() : sem(0)
          {
            wType				= NO_WAITING;
            tId					= c_Undefined;
            tcId				= c_Undefined;
            clientThreadCntx	= NULL;
          }		

        KLSCH::Semaphore 	 sem;	//!< ������� ��� �������� ��������

        WaitingType		   wType;	//!< ��� ��������
        TaskId			     tId;	//!< ������������� ������, ������� ����
        time_t		     timeSec;	//!< ����� ������� ������
        int				timeMSec;
        TaskClassId			tcId;	//!< ����� ������
        
        void  *clientThreadCntx;	//!< �������� ����������� ������ ( ����������� � ������� WaitTaskExecution )
    };

	class SchedulerImp : public Scheduler
	{
		friend class TasksIteratorImp;

    public:

	/*!
      \brief �����������.
	  \param waitTime [in] ����� ����������� ��� �������� ������� ������� 
                           ���������� ������.
	 */
		SchedulerImp( int waitTime = c_Infinite );

	/*!
		\brief ����������.
	*/
		~SchedulerImp( );

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
      
        Errors AddTask( const Task *t, TaskId& id_ptr );

    /*!
      \brief ������� ������ � �������� ���������������.

      Scheduler ������� ������ �� ������ ����� �� ����������.  �����,
      ��������� ���������� ������, ������������� �� ���������� ������
      ������ ���� ��� ������������ ������ ERR_NO_MORE_TASKS.

      \param id [in] ������������� ��������� ������.
      \return ��� ������

    */

        Errors DelTask( const TaskId id );


	/*!
      \brief ������������� ��������� ��� ��������� ������

      \param id [in] ������������� 
	  \param par [in] ������ �� ��������� ��� ������� ������.
      \return ��� ������

    */

        Errors SetPramsForTask( const TaskId id, TaskParams * par );


	/*!
      \brief ���������������� ������ ��������� ������.

      Scheduler �� ����� ������� ������ ����� �� ���������� ���� ��� ��� �� ����� �������
	  ������� ResumeTask.

      \param id [in] ������������� ������.
      \return ��� ������ ( ERR_TASK_ID, ERR_TASK_STATE, ERR_NONE )

    */

        Errors SuspendTask( const TaskId id );

	/*!
      \brief ������������ ������ ���������������� ������ ��������� ������.

      \param id [in] ������������� ������.
      \return ��� ������ ( ERR_TASK_ID, ERR_TASK_STATE, ERR_NONE )

    */

        Errors ResumeTask( const TaskId id );

	/*!
      \brief ���������� ��������� ����� ������� ������.

      \param id [in] ������������� ������.
	  \param sec [out] ��������������� ����� ���������� ������ � ������� time_t.
      \param msec [out] ��������������� ����� ���������� ������ � msec. ��������
                             ���������� sec � msec ������������.
      \return ��� ������ ( ERR_TASK_ID, ERR_NONE )
    */

        Errors GetTaskNextExecutionTime( const TaskId id, time_t& sec, int& msec );

    /*!
      \brief ������� �������� ��� ��������� ������ �����.

      ������� �������� ��� ��������� ������ ����� � ���������� ���
      �������.  ������ ����� �������� ����� ����� ��� ���������.
      �� ��������� ��������������� ��� ������.

      \param it [out] �������� ��� ��������� ������ �����.
      \param cid [in] ����� ����� ��� ��������� ����������.
      \return ��� ������

    */


        Errors CreateTasksIterator( 
            TasksIterator *it, 
            TaskClassId cid = 0 );


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


        Errors CreateHangingTasksIterator( 
            TasksIterator *it, 
            TaskClassId cid = 0 );


    /*!
      \brief ���������� ����� �����, ��������� ���������� ������ Scheduler.

      \param num [out] ����� �����, ������������ ������ Scheduler.
      \param cid [in] ����� ����� ��� ��������� ����� �����.  �� ���������
                      ������������ ������ ����� �����.
      \return ��� ������

    */


        Errors GetTasksNumber( int& num, TaskClassId cid = 0) const;

	/*!
	  \brief ��������� scheduler � ����� �������������.

      ��� ������ � ������ ������ ������� WaitTaskExecution ���������� ERR_SUSPEND_MODE.
	  ��� ������, ������������ � ������ ������ ������� � WaitTaskExecution ���� �������� ��
	  ������� � ����� �������� ERR_SUSPEND_MODE.
      
      \return ��� ������

    */	

		Errors Suspend( );

	/*!
	  \brief �������� ����������� �� ������ ������������� � ����������.
            
      \return ��� ������

    */	

		Errors Resume( );

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

        Errors SetWaitTime( int waitTime = 10000, TaskClassId cid = 0 );


    /*!
      \brief ���������� ������������ ����� �������� ������ �� ������ 
             ���������� ������ (msec).

      \param waitTime [out] ����� ����������� ��� �������� ������� ������� 
                           ���������� ������.
      \param cid [in] ����� ����� ��� ��������� ������� ��������.
      \return ��� ������

    */

        Errors GetWaitTime( int& waitTime, TaskClassId cid = 0 );


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

        Errors WaitTaskExecution(   TaskResults** res,
									void *threadContex,
                                    int waitTime = 0, 
                                    TaskClassId cid = 0,
									bool waitFlag = true );

	private:
		/** ���������� ��������� � ������ */

        typedef _WaitingThreadContext WaitingThreadContext;
        typedef std::list<KLSCH::_WaitingThreadContext *> container_type;
        typedef container_type::iterator iterator;
        typedef container_type::const_iterator const_iterator;


		/** ���������� ���������� */

		int			internalTaskIdCounter;	//!< ������������ ��� ��������� taskId

		TaskList				 taskList;	//!< ������ �����
		
		TaskClassesList	  taskClassesList;	//!< ������ �������� ������� �����		
        container_type wtc_list;  //!< ������������ ������ WTC

		LightMutex					mutex;	//!< Mutex ��� ������������ ������� �� ���������� ���������� �������

		bool				  suspendMode;	//!< ���� ����������������� ������ ������������

		int		      createdIteratorsNum;	//!< ������� ��������� ���������� ( ������������ � ������� �������� ������ )

		bool			  needFreeDelTask;	//!< ���� ������������� ��������� ������� ������ �� ������ ����� ����������� ���������� ���������

	protected:
		/** @name class helper functions */
		//@{

		/** @name ������� ��� ������ � �������� ���������� ���������� ������*/		
		//@{		
		/** ���������� ��������� ������ � ������� */
		WaitingThreadContext *GetFreeWTCUnit( );	
		/** ���������� ������ ��������� �������� ������� ������ ����� */
		WaitingThreadContext *GetWaitingWTCByClassTaskId( const TaskClassId ctId );	
		/** ����������� wtc */
		void FreeWTCUnit( WaitingThreadContext *wtc );
		//@}

		/** ��������� ����� ������� ������ ������. ����������� ���������� WTC */
		void WriteTaskNextExecutionTime( TaskList::ListUnit *taskDesc );

		/** �������� ������ ������ �� ������� ����������� �������� */
		void RemoveTaskFromWork( TaskId tId, TaskList::ListUnit *taskUnit, bool findInWTC );

		/** ���������� ������ �� ���������� mutex. ���������� ��� TasksIterator */
		LightMutex &GetInternalMutex();

		/** ������� ����������� � ����������� ������� ��������. ���������� �� ������ TasksIterator */
		void NotifyIteratorDestroy( TasksIteratorImp *tIter );

		
		//@}
    };

} // namespace KLSCH

#endif // KLSCHIMP_H

// Local Variables:
// mode: C++
// End:
