/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file TasksIterator.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ������������ ������-��������� ���
 *        ��������� ������ �����. 
 *
 */
/*KLCSAK_PUBLIC_HEADER*/

#ifndef KLSCH_TASKSITERATOR_H
#define KLSCH_TASKSITERATOR_H

#include "std/base/klbase.h"

#include "std/sch/errors.h"

namespace KLSCH {


   
    /*!
    * \brief ����� - �������� ��� ��������� ������ �����.
    *
    */ 
	class Scheduler;


	class TasksIterator
	{

        friend class SchedulerImp;

    public:
		
		/*!
			\brief ����������� ����������.
		*/
		virtual ~TasksIterator() {}
        /*!
            \brief ������������� �������� �� ������ ������.

        */
        virtual Errors Reset() = 0;

        /*!
            \brief ���������� ����������� ��������� �� ��������� ������ � ������.

            \param t [out] ��������� �� ������ � ������.
            \param hasMoreTasks [out] ������, ���� � ������ ������� ��� ������.
            \return ��� ������

        */
        virtual Errors Next( const Task ** t, bool& hasMoreTasks ) = 0;
    };

}

/*
	\brief ����� ��� �������� ������� Scheduler
*/
KLCSC_DECL KLSCH::TasksIterator *KLSCH_CreateTasksIterator();

#endif // KLSCH_TASKSITERATOR_H
