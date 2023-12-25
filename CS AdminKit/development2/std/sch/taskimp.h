/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file TaskImp.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ���������� ������ ��� ������� �������-�������������.
 *
 */


#ifndef KLSCH_TASKIMP_H
#define KLSCH_TASKIMP_H

#include <ctime>

#include "std/sch/common.h"
#include "std/sch/errors.h"
#include "std/sch/task.h"

namespace KLSCH {

   
        
   /*!
    * \brief ������ ��� ������� �������-�������������.
    *
    */ 


	class TaskImp : public Task
	{

        friend class TaskList;
		friend class TasksIteratorImp;
		friend class SchedulerImp;

    public:
		
		/*!
            \brief ������������.

            \param id [in]  ������������� ������.
			\param cId [in] ������������� ������ ������.
        */
		TaskImp( );
		TaskImp( TaskId id, TaskClassId cId );
		/*!
			\brief �������� �������������.
		*/
		const TaskImp &operator = ( const TaskImp &t );

		/*!
            \brief ����������. 
				   ������� ������ Schedule.
				   ������� TaskParams.
        */
        ~TaskImp( );

        /*!
            \brief ������������� ������������� ������.

            \param id [in] ������������� ������.
            \return ��� ������

        */
        Errors SetTaskId( TaskId id );


        /*!
            \brief ���������� ������������� ������.

            \param id [out] ������������� ������.
            \return ��� ������

        */
        Errors GetTaskId( TaskId& id ) const;


        /*!
            \brief ������������� ������������� ������ ������.

            \param id [in] ������������� ������ ������.
            \return ��� ������

        */
        Errors SetClassId( TaskClassId cid );


        /*!
            \brief ���������� ������������� ������ ������.

            \param id [out] ������������� ������ ������.
            \return ��� ������

        */
        Errors GetClassId( TaskClassId& cid ) const;


		/*!
            \brief ���������� ������� ��������� ������.

            \param s [out] ������� ��������� ������.
            \return ��� ������

        */

        Errors GetCurrentState( State &s ) const;

        /*!
            \brief ������������� ���������� ��� ������� ������.

            \param s [in] ���������� ��� ������� ������.
            \return ��� ������

        */


        Errors SetSchedule( Schedule* s );

        /*!
            \brief ���������� ��������� �� ���������� ��� ������� ������.

            \param s [out] ���������� ��� ������� ������. 0 ���� ���������� ��
                            ����������.
            \return ��� ������

        */

        Errors GetSchedule( const Schedule ** s) const;

        /*!
            \brief ������������� callback ��� ������� ������.

            \param cb [in] ��������� �� ������� ��� ������� ������.
            \return ��� ������

        */
        Errors SetCallback( TaskCallback cb);

		/*!
            \brief ������������� ����������� callback ��� ������� ������.

            \param cb [in] ��������� �� ������� ��� ������� ������.
            \return ��� ������

        */
        Errors SetCallback2( TaskCallback2 cb);

        /*!
            \brief ���������� ������������� callback ��� ������� ������.

            \param cb [out] ��������� �� ������� ��� ������� ������.  0 ���� callback
                            �� ���������.
            \return ��� ������

        */
        Errors GetCallback( TaskCallback& cb ) const;

        /*!
            \brief ������������� ��������� ��� ������� ������.

            \param par [in] ������ �� ��������� ��� ������� ������.
            \return ��� ������

        */
        Errors SetTaskParams( TaskParams * par );

        /*!
            \brief ���������� ����� ���������� ��� ������� ������.

            \param par [in] ��������� �� ��������� ��� ������� ������.
            \return ��� ������

        */
        Errors GetTaskParams( const TaskParams** par ) const;

		/*!
            \brief ������������� ��������� � ������� ����� ���������� ����� ������� ������ (msec).

			��� ������� ������� ������� ������ �� ��������� �� 0 �� startDeltaTimeout ����������
			��������� �����, ������� ������������ � ������� �������. ������������ ���
			����������� �������� ��� ����� � ���������� �������� �������.

            \param startDeltaTimeout [in] ������ (msec).
            \return ��� ������
        */
        Errors SetStartDeltaTimeout( int startDeltaTimeout );

        /*!
            \brief ���������� ��������� � ������� ����� ���������� ����� ������� ������ (msec).

            \param startDeltaTimeout [out] ������������ ����� ���������� ������ (msec).
            \return ��� ������
        */
        Errors GetStartDeltaTimeout(int& startDeltaTimeout) const;

		/*!
            \brief ������������� timeout ��� ����������������� �������

			���� ������ timeout ����������, �� ������ ������� ����� ��������� � 
			���������������� ������, � ����� � ������ ����� ���������� �����������
			� ����������.

			\param timeout [in] Timeout (msec).            
            \return ��� ������

        */
        Errors SetPreparativeStartTimeout( int timeout );

		/*!
			\brief ���������� timeout ��� ����������������� �������
            
            \param timeout [out] Timeout (msec).
            \return ��� ������

        */
        Errors GetPreparativeStartTimeout( int &timeout ) const;

        /*!
            \brief ������������� ������������ ����� ���������� ������ (msec).

            \param maxTime [in] ������������ ����� ���������� ������ (msec).
             \return ��� ������

        */
        Errors SetMaxExecutionTime( int maxTime = 10000 );

        /*!
            \brief ���������� ������������ ����� ���������� ������ (msec).

            \param maxTime [out] ������������ ����� ���������� ������ (msec).
            \return ��� ������ ( ERR_TASK_STATE, ERR_NONE )

        */
        Errors GetMaxExecutionTime(int& maxTime) const;

		/*!
            \brief ���������� ����� ����������� ������� ������.
            
            \param msec [in] ����� ���������� ������ � msec. 
            \return ��� ������

        */
        Errors GetRunningTime( int &msec );	

        /*!
            \brief ������������� ��������� ����� ���������� ������.

            \param sec [in] ��������� ����� ���������� ������ � ������� time_t.
            \param msec [in] ��������� ����� ���������� ������ � msec. ��������
                             ���������� sec � msec ������������.
            \return ��� ������

        */
        Errors SetLastExecutionTime( time_t sec = 0,  int msec = 0 );

        /*!
            \brief ���������� ��������� ����� ���������� ������.

            \param sec [out] ��������� ����� ���������� ������ � ������� time_t.
            \param msec [out] ��������� ����� ���������� ������ � msec. ��������
                             ���������� sec � msec ������������.
            \return ��� ������

        */
        Errors GetLastExecutionTime( time_t& sec, int& msec ) const;

        /*!
            \brief ���������� ��������� ��������������� ����� ���������� ������.

            \param sec [out] ��������������� ����� ���������� ������ � ������� time_t.
            \param msec [out] ��������������� ����� ���������� ������ � msec. ��������
                             ���������� sec � msec ������������.
            \return ��� ������

        */
        Errors GetNextExecutionTime( time_t& sec, int& msec );

		/*!
            \brief ������������� ���� �������� ������ ����� ����� �� ����������.

            \param delAfterRun [in] ���� true, �� ������ ��������� ����� ����������.
            \return ��� ������

        */
        Errors SetDelAfterRunFlag( bool delAfterRun );

		/*!
            \brief ���������� ���� �������� ������ ����� ����� �� ����������.

            \param delAfterRun [out] ���� true, �� ������ ��������� ����� ����������.
            \return ��� ������

        */
        Errors GetDelAfterRunFlag( bool &delAfterRun ) const;
		

		/*!
			\brief ������������� ��������� ������ � ������� ������ ����������� ������.
					�� ��������� ����� TP_Normal.
			
			\param ttPriority [in] ����� ��������� ���������� ������
		*/
		Errors SetTaskThreadPriority( TaskThreadPriority ttPriority );

		/*!
			\brief ���������� ��������� ������ � ������� ������ ����������� ������.
								
			\param ttPriority [out] ��������� ���������� ������
		*/
		Errors GetTaskThreadPriority( TaskThreadPriority &ttPriority ) const;

		/*!
            \brief ���������� �������� ������, � ������� ������������� ���������� ������.

            \param threadCntx [out] �������� ������ ( �� ����� NULL ������ ����� ������ 
									���������� � ��������� Running.            
            \return ��� ������

        */
        Errors GetThreadContext( void **threadCntx ) const;

		/*!
			\brief ������� �������� ����� �������

			\return ��������� �� ��������� ����� ������
		*/
		virtual void Clone( Task **ppTask ) const; 

		/*!
            \brief ���������� ��������� �� ���������� ��� ������� ������ ���
			 ���������� �����������.

            \param s [out] ���������� ��� ������� ������. 0 ���� ���������� ��
                            ����������.
            \return ��� ������

        */
        virtual Errors GetWritableSchedule( Schedule ** s);

	private:
		/** ���������� ���������� */

		TaskId		tId;		//!< ������������� ������
		TaskClassId cId;		//!< ������������� ������ ������

		State		state;		//!< ������� ��������� ������

		TaskCallback	func;	//!< ����� callback ������� ������
		TaskCallback2	func2;	//!< ����� ����������� callback ������� ������
		TaskParams  *params;	//!< ��������� ������

		int	 maxExecuteTime;	//!< ����������� ��������� ����� ����������� ������ ( � ������������ )

		void	*threadCntx;	/*!< �������� ������ � ������� ������������� ��������� callback 
									�������. �������� ������ �� ������ ���������. */

		Schedule *schedule;		//!< ���������� ������

		Schedule *accessorySchedule;	//!< ��������������� ���������� ������ ( ������������ ��� ���������������� ������� ������ )

		time_t lastExeTime;			//!< ��������� ����� ���������� ������
		int    lastExemsec;

		time_t nextExeTime;			//!< ��������������� ����� ���������� ������
		int    nextExemsec;

		int  startSysTick;		//!< ����� ������� ������ � ������������ ( � ����� )

		int  startDeltaTimeout;

		int  preparativeTimeout;
		bool preparativeStart;	//!< ������� ����������������� �������

		TaskThreadPriority taskThreadPriority;	//!< ��������� ������ ������

		bool delAfterRun;		//!< ���� �������� ������ ����� ����� �� ������� ����������

	protected:
		/** class helper functions */

		void InitializeVars();					//!< �������������� ���������� ����������

		void SetCurrState( State newState );	//!< ������������� ������� ��������� ������

		/** ����������� ��������� ����� ������� */
		void CalculateNextExecutionTime( time_t currTime = 0 ); 

		/** ����������� ��������� ����� ������� ����� Suspend ��������� */
		void CalculateNextTimeAfterSuspend( );

		void SetThreadContext( void	*tCntx );	//!< ������������� �������� ������ ��� ������

		void Call( TaskResults** result, bool &delTask );	//!< �������� callback ������

		bool IsTaskHanging() const;				//!< ���������� �������� �� ������ ������ �������

    };

}	// end namespace KLSCH

#endif // KLSCH_TASKIMP_H
