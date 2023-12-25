/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file Task.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ������������ ���������� ������ ��� ������� �������-�������������.
 *
 */
/*KLCSAK_PUBLIC_HEADER*/


#ifndef KLSCH_TASK_H
#define KLSCH_TASK_H

#include <ctime>

#include "std/base/klbase.h"

#include "std/sch/common.h"
#include "std/sch/errors.h"

namespace KLSCH {


    class Schedule;
    class TaskResults;
    class TaskParams;

	struct TaskOptions
	{	
		TaskOptions()
		{
			PreparativeStart = false;
		}

		TaskOptions( bool prepStart, unsigned long prepTimeout )
		{
			PreparativeStart = prepStart;
			PreparativeTimeout = prepTimeout;
		}		

		bool			PreparativeStart;
		unsigned long	PreparativeTimeout;
	};
    
    /*!
		\brief Callback - ������� ��� ������ ������

		\param tParams [in]  ��������� ������
		\param tResult [out] ��������� ����������� ������. Callback ������� ������ ������� 
							 ������ TaskResults � �������� ��� ������� ����� ���� ��������
	*/
    typedef Errors (*TaskCallback)(const TaskParams* tParams, TaskResults **tResult );

	/*!
		\brief Callback - ������� ��� ������ ������

		\param tParams [in]  ��������� ������
		\param tOptions [in] ��������� ������
		\param tResult [out] ��������� ����������� ������. Callback ������� ������ ������� 
							 ������ TaskResults � �������� ��� ������� ����� ���� ��������
							  \param tParams [in]  ��������� ������		
	*/
    typedef Errors (*TaskCallback2)(const TaskParams* tParams, 
		const TaskOptions *tOptions, TaskResults **tResult );

   /*!
    * \brief ������ ��� ������� �������-�������������.
    *
    */ 


	class Task
	{
    public:

		//! \enum - ��������� ������
		enum State {
			Created,			///< ������ ������ ��� ������� � ��� �� ������ � Scheduler
			Scheduled,			///< ������ ���������� � ��������� �������� ������
			WaitForRunning,		///< ������ ������ ������� �������
			Running,			///< ������ �����������
			Suspended,			///< ������ ������� �������������� ( ��. Scheduler::SuspendTask )
			Completed,			///< ������ ��� ����������� � ������ ����������� �� ����� ( �� ������ �� ���������� )
			Deleted				///< ������ ������� ( ��������� �� ������ ����� ������� ����� )
		};

		//! \enum - ��������� ������ ������
		enum TaskThreadPriority {
			TP_Low,
			TP_Normal,
			TP_Hight
		};

		/*!
			\brief ����������� ����������.
		*/
		virtual ~Task() {}

		/*!
            \brief ������������� ������������� ������.

            \param id [in] ������������� ������.
            \return ��� ������

        */
        virtual Errors SetTaskId( TaskId id ) = 0;


        /*!
            \brief ���������� ������������� ������.

            \param id [out] ������������� ������.
            \return ��� ������

        */
        virtual Errors GetTaskId( TaskId& id ) const = 0;


        /*!
            \brief ������������� ������������� ������ ������.

            \param id [in] ������������� ������ ������.
            \return ��� ������

        */
        virtual Errors SetClassId( TaskClassId cid ) = 0;


        /*!
            \brief ���������� ������������� ������ ������.

            \param id [out] ������������� ������ ������.
            \return ��� ������

        */
        virtual Errors GetClassId( TaskClassId& cid ) const = 0;


		/*!
            \brief ���������� ������� ��������� ������.

            \param s [out] ������� ��������� ������.
            \return ��� ������

        */

        virtual Errors GetCurrentState( State &s ) const = 0;

        /*!
            \brief ������������� ���������� ��� ������� ������.

            \param s [in] ���������� ��� ������� ������.
            \return ��� ������

        */


        virtual Errors SetSchedule( Schedule* s ) = 0;

        /*!
            \brief ���������� ��������� �� ���������� ��� ������� ������.

            \param s [out] ���������� ��� ������� ������. 0 ���� ���������� ��
                            ����������.
            \return ��� ������

        */

        virtual Errors GetSchedule( const Schedule ** s) const = 0;

        /*!
            \brief ������������� callback ��� ������� ������.

            \param cb [in] ��������� �� ������� ��� ������� ������.
            \return ��� ������

        */
        virtual Errors SetCallback( TaskCallback cb) = 0;

		/*!
            \brief ������������� ����������� callback ��� ������� ������.

            \param cb [in] ��������� �� ������� ��� ������� ������.
            \return ��� ������

        */
        virtual Errors SetCallback2( TaskCallback2 cb) = 0;
		

        /*!
            \brief ���������� ������������� callback ��� ������� ������.

            \param cb [out] ��������� �� ������� ��� ������� ������.  0 ���� callback
                            �� ���������.
            \return ��� ������

        */
        virtual Errors GetCallback( TaskCallback& cb ) const = 0;

        /*!
            \brief ������������� ��������� ��� ������� ������.

            \param par [in] ������ �� ��������� ��� ������� ������.
            \return ��� ������

        */
        virtual Errors SetTaskParams( TaskParams * par ) = 0;

        /*!
            \brief ���������� ����� ���������� ��� ������� ������.

            \param par [in] ��������� �� ��������� ��� ������� ������.
            \return ��� ������

        */
        virtual Errors GetTaskParams( const TaskParams** par ) const = 0;

		 /*!
            \brief ������������� ��������� � ������� ����� ���������� ����� ������� ������ (msec).

			��� ������� ������� ������� ������ �� ��������� �� 0 �� startDeltaTimeout ����������
			��������� �����, ������� ������������ � ������� �������. ������������ ���
			����������� �������� ��� ����� � ���������� �������� �������.

            \param startDeltaTimeout [in] ������ (msec).
            \return ��� ������
        */
        virtual Errors SetStartDeltaTimeout( int startDeltaTimeout ) = 0;

        /*!
            \brief ���������� ��������� � ������� ����� ���������� ����� ������� ������ (msec).

            \param startDeltaTimeout [out] ������������ ����� ���������� ������ (msec).
            \return ��� ������
        */
        virtual Errors GetStartDeltaTimeout(int& startDeltaTimeout) const = 0;
		
		/*!
            \brief ������������� timeout ��� ����������������� �������

			���� ������ timeout ����������, �� ������ ������� ����� ��������� � 
			���������������� ������, � ����� � ������ ����� ���������� �����������
			� ����������.

			\param timeout [in] Timeout (msec).            
            \return ��� ������

        */
        virtual Errors SetPreparativeStartTimeout( int timeout ) = 0;

		/*!
			\brief ���������� timeout ��� ����������������� �������
            
            \param timeout [out] Timeout (msec).
            \return ��� ������

        */
        virtual Errors GetPreparativeStartTimeout( int &timeout ) const = 0;

        /*!
            \brief ������������� ������������ ����� ���������� ������ (msec).

            \param maxTime [in] ������������ ����� ���������� ������ (msec).
             \return ��� ������

        */
        virtual Errors SetMaxExecutionTime( int maxTime = 10000 ) = 0;

        /*!
            \brief ���������� ������������ ����� ���������� ������ (msec).

            \param maxTime [out] ������������ ����� ���������� ������ (msec).
            \return ��� ������ ( ERR_TASK_STATE, ERR_NONE )

        */
        virtual Errors GetMaxExecutionTime(int& maxTime) const = 0;

		/*!
            \brief ���������� ����� ����������� ������� ������.
            
            \param msec [in] ����� ���������� ������ � msec. 
            \return ��� ������

        */
        virtual Errors GetRunningTime( int &msec ) = 0;	

        /*!
            \brief ������������� ��������� ����� ���������� ������.

            \param sec [in] ��������� ����� ���������� ������ � ������� time_t.
            \param msec [in] ��������� ����� ���������� ������ � msec. ��������
                             ���������� sec � msec ������������.
            \return ��� ������

        */
        virtual Errors SetLastExecutionTime( time_t sec = 0,  int msec = 0 ) = 0;

        /*!
            \brief ���������� ��������� ����� ���������� ������.

            \param sec [out] ��������� ����� ���������� ������ � ������� time_t.
            \param msec [out] ��������� ����� ���������� ������ � msec. ��������
                             ���������� sec � msec ������������.
            \return ��� ������

        */
        virtual Errors GetLastExecutionTime( time_t& sec, int& msec ) const = 0;

        /*!
            \brief ���������� ��������� ��������������� ����� ���������� ������.

            \param sec [out] ��������������� ����� ���������� ������ � ������� time_t.
            \param msec [out] ��������������� ����� ���������� ������ � msec. ��������
                             ���������� sec � msec ������������.
            \return ��� ������

        */
        virtual Errors GetNextExecutionTime( time_t& sec, int& msec ) = 0;

		/*!
            \brief ������������� ���� �������� ������ ����� ����� �� ����������.

            \param delAfterRun [in] ���� true, �� ������ ��������� ����� ����������.
            \return ��� ������

        */
        virtual Errors SetDelAfterRunFlag( bool delAfterRun ) = 0;

		/*!
            \brief ���������� ���� �������� ������ ����� ����� �� ����������.

            \param delAfterRun [out] ���� true, �� ������ ��������� ����� ����������.
            \return ��� ������

        */
        virtual Errors GetDelAfterRunFlag( bool &delAfterRun ) const = 0;

		/*!
			\brief ������������� ��������� ������ � ������� ������ ����������� ������.
					�� ��������� ����� TP_Normal.
			
			\param ttPriority [in] ����� ��������� ���������� ������
		*/
		virtual Errors SetTaskThreadPriority( TaskThreadPriority ttPriority ) = 0;

		/*!
			\brief ���������� ��������� ������ � ������� ������ ����������� ������.
								
			\param ttPriority [out] ��������� ���������� ������
		*/
		virtual Errors GetTaskThreadPriority( TaskThreadPriority &ttPriority ) const = 0;

		/*!
            \brief ���������� �������� ������, � ������� ������������� ���������� ������.

            \param threadCntx [out] �������� ������ ( �� ����� NULL ������ ����� ������ 
									���������� � ��������� Running.            
            \return ��� ������

        */
        virtual Errors GetThreadContext( void **threadCntx ) const = 0;

		/*!
			\brief ������� �������� ����� �������

			\return ��������� �� ��������� ����� ������
		*/
		virtual void Clone( Task **ppTask ) const = 0;
		
		/*!
            \brief ���������� ��������� �� ���������� ��� ������� ������ ���
			 ���������� �����������.

            \param s [out] ���������� ��� ������� ������. 0 ���� ���������� ��
                            ����������.
            \return ��� ������

        */
        virtual Errors GetWritableSchedule( Schedule ** s) = 0;
    };

}	// end namespace KLSCH

/*
	\brief ����� ��� �������� ������� Task
*/
KLCSC_DECL KLSCH::Task *KLSCH_CreateTask();

#endif // KLSCH_TASK_H
