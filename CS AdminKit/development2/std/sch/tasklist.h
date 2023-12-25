/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file TaskList.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ���������� ������ ����� ( ������������ ��� ��������������� ����� ).
 *
 */


#ifndef KL_TASK_LIST_H
#define KL_TASK_LIST_H

#include <ctime>

#include "std/sch/common.h"
#include "std/sch/errors.h"

#include "taskimp.h"

namespace KLSCH {

   /*!
    * \brief ������ ����� ������������.
    *
    */ 

	class TaskList
	{
    public:
		/*! \struct ListUnit
			\brief ������������ ��� ������������ ������ �����
		*/
		struct ListUnit {
			ListUnit( const TaskImp &t )
			{				
				task = t;				
				next = NULL;				
			}
			~ListUnit( )
			{				
			}
			TaskImp				task;		//!< ������		

			struct ListUnit *next;		//!< ���� ��� ����������� ������
		};
		
		/*!
            \brief �����������.
        */
		TaskList( );

		/*!
            \brief ����������. 
				   ����������� ������ �����.				   
        */
        ~TaskList( );

        /*!
            \brief ������������� ������������� ������.

            \param t [in] ������ ��� ����������.
            \return ��������� �� ����������� ���������

        */
		ListUnit *AddTask( const Task *t );	      


        /*!
            \brief ����������� ����� ������ � ������.

			\param taskUnit [out] ��������� �� ��������� ������� ������
            \param tId [in] ������������� ������.
            \return ��������� ������

        */
        bool FindTask( ListUnit **taskUnit, const TaskId tId );


        /*!
            \brief ������� ������ �� ������.

            \param tId [in] ������������� ������.
            \return ��������� ��������

        */
        bool DeleteTask( const TaskId tId ); 

		/*!
            \brief ���������� �������� ������ ��� �����������.

            \param �tId [in] ������������� ������ ������.
            \return ��������� �� ��������� ���������

        */
        ListUnit *FindNextTask( const TaskClassId ctId ); 


        /*!
            \brief �������� ������ �� �����������.

			\param tId [in] ������������� ������.
			\param threadContext [in] �������� ����������� ������.
            \param res [out] ��������� ������ ������.
            
        */
		bool CallTaskById( const TaskId tId, void *threadContext, TaskResults** res );

		/*!
            \brief ������� ������������� ��� �������� ���������� �����.

			\param tId [in] ������������� ��������� ������ � ������ ��� (c_Undefined)
				��� ��������� ���������� ������ ������.			
			\param tCid [in] ��������� ����� ����� ��� ������
            \return ��������� �� ��������� ��������� ��� NULL
            
        */
		ListUnit *GetNextUnit( const TaskId prevtId, TaskClassId tCid );

		/*!
            \brief ������� ��� ������, � ������� ������� ������ Deleted, �� ������.			
            \return 
            
        */
		void EraseAllDeletedTasks();
        
	private:
		/** ���������� ���������� */

		ListUnit *first;			//!< ��������� �� ������ ������������� ������

	protected:
		/** class helper functions */

    };

}	// end namespace KLSCH

#endif // KL_TASK_LIST_H
