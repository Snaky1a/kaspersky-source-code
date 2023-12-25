/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file TasksIteratorImp.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ������-��������� ���
 *        ��������� ������ �����. 
 *
 */


#ifndef KLSCH_TASKSITERATORIMP_H
#define KLSCH_TASKSITERATORIMP_H

#include "std/sch/errors.h"
#include "std/sch/tasksiterator.h"

namespace KLSCH {

   
    /*!
    * \brief ����� - �������� ��� ��������� ������ �����.
    *
    */ 

	class TasksIteratorImp : public TasksIterator
	{

        friend class SchedulerImp;

    public:

		/*!
            \brief �����������.
        */
		TasksIteratorImp();

		/*!
            \brief ����������.
        */
		~TasksIteratorImp();

        /*!
            \brief ������������� �������� �� ������ ������.

        */
        Errors Reset();

        /*!
            \brief ���������� ����������� ��������� �� ��������� ������ � ������.

            \param t [out] ��������� �� ������ � ������.
            \param hasMoreTasks [out] ������, ���� � ������ ������� ��� ������.
            \return ��� ������

        */
        Errors Next( const Task ** t, bool& hasMoreTasks );

	protected:

		/* ���������� ��������� ������ */
		SchedulerImp *scheduler;	//!< ��������� �� scheduler
		TaskList	  *taskList;	//!< ��������� �� ������ �����
		TaskId		 currentTid;	//!< ������������� ������� ������

		TaskClassId filterCid;	//!< ����� ����� ��� �������
		bool	  onlyHanging;	//!< �������� ������ ������� ������

		/* helper class functions */

		/** ������� ������������� ���������  */
		void Init( SchedulerImp *sch, TaskList *lst, TaskClassId fCid,
			bool hanging );
    };

}

#endif // KLSCH_TASKSITERATORIMP_H
