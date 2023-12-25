/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file PRCI/ProductTasks.h
 * \author ������ ��������
 * \date 2002
 * \brief ��������� ��� ���������� ����������� �������� ���������������� �����.
 *
 */

#ifndef KLPRCI_PRODUCTTASKSCONTROL_H
#define KLPRCI_PRODUCTTASKSCONTROL_H

#include <string>

#include "prci_const.h"
#include "std/err/error.h"
#include "std/par/params.h"

namespace KLPRCI {


    /*!
		\brief Callback - ������� ��� ���������� ����������� ���������������� �����.  
                ���������� ���� ������� ������ ���� ����������������.

        ��������� ������ ������� �� ���������� ������ ���� taskName � ����������� params
        � ��������������� taskId ��� ����� ���������� ������.

        ������ ���������� ������ - �����������.  ��������� ��������� ������ �� ����������
        � ����� ����� ������������ � ������� ���������� ������ ��� ������ �������.
        ��������� ������� ���������� ����:
            c_EventTaskState
            c_EventTaskCompletion
            c_EventTaskStarted
         
        \param taskName       [in]  ��� ����������� ������.
        \param params         [in]  ��������� ��� ���������� ������.
								� ���������� ���������� ������ ����������
								��������� ���������� � ������, ��������
								����������  c_szwTaskAsyncId, ���� STRING_T,
								���������� �������� ��������� asyncId ������
								ComponentProxy::RunTask.
        \param taskId         [in]  ������������� ���������� ������.
        \param timeout        [in]  ������������ ����� ���������� ������ (msec).

        \return  ������������� ���������� ������. �������� ��� ���� �����, 
                 ����������� �����������.

	*/
    typedef void  (*RunTasksCallback)(
					void*					context,
					const std::wstring&		taskName,
							KLPAR::Params*	params,
					long					taskId,
					long					timeout) ;

        //! ��������� ��������� ������. 
    enum TaskState {
        TASK_CREATED,   ///< ������ ������ ��� �������.
        TASK_RUNNING,   ///< ������ �����������.
        TASK_SUSPENDED, ///< ������ ������������� ������.
        TASK_FAILURE,   ///< ��������� ������ ��� ���������� ������.
        TASK_COMPLETED, ///< ������ ��������� ���� ������.
        TASK_TIMEOUT,   ///< ������ ����������� ������, ��� ��������.
        TASK_RELOADING,
        TASK_INACTIVE
    };


        //! ��������� �������� ��� ����������� �������. 
    enum TaskAction {
        ACTION_STOP,      ///< ���������� ���������� ������.
        ACTION_SUSPEND,   ///< ������������� ���������� ������.
        ACTION_RESUME,    ///< ����������� ���������� ������.
        ACTION_STATUS,    ///< ������� ������� ������ ������.
        /*! ������������ �������� ������. ���� ������ �� ������������
            ������������ ������������ ��������, ��� ������ ������ ����������.
            ����� ��������� ����� �������� � �������� ������� ������ ������
            ����� ��������� ������ �� �������.
            ������ ������� ��� ��������� ����� �������� ������� ��������
            ����� GetTaskParams.
        */
        ACTION_RELOAD,   ///< ������������� ���������
        ACTION_START
    };


    /*!
		\brief Callback - ������� ��� �������� ��� ������������ ����������� 
               ����������������� ��������.���������� ���� ������� ������ ���� 
               ����������������.

        \param taskId       [in]  ������������� ���������� ������.
        \param action       [in]  ��� ��������, ������� ��������� ��������� ��� �������.
	*/
    typedef void (*TasksControlCallback)(
					void*		context,
					long		taskId,
					TaskAction	action);

    /*!
    * \brief ��������� ��� ���������� ����������� �������� ���������������� �����.
    */


    class KLSTD_NOVTABLE ProductTasksControl: public KLSTD::KLBaseQI
    {
    public:

    /*!
      \brief ������������� ������� ��������� ������.

      \param taskId       [in] ������������� ���������� ������.
      \param state        [in] ������� ��������� ������.
	  \param results      [in] �������������� ���������, ������������ � ��������� 
                               KLPRCI::c_evpTaskResults ������������� ������� 
							   � ��������� ������ (KLPRCI::c_EventTaskState).
                               ������ ������ �������������� ����������, ����� ��������� 
							   ����������� ��������� �������, ������� ����������� ����� 
							   ������������ ��� ��������� ���������������� ������� 
							   KLPRCI::c_EventTaskState:

                               - KLEVP::c_er_descr � �������������� ��������� �������� 
                               ���������� ���������� ������ (���� ��� ���������� � 
                               ��������, � ������ ������������� ������ � �������� ������ 
                               � ��������� KLPRCI::TASK_FAILURE);

                               - KLEVP::c_er_locid � ������������� �����������, ������������ 
                               ��� ����������� ������� � ������� �����������������.

                               - KLEVP::c_er_par1, ...  KLEVP::c_er_par6 � �������������� 
                               ���������, ������������ ��� �����������; �� ���������� 
							   ������������� ������� �� �������������� �����������.

                               - KLEVP::c_er_completedPercent � ������������ �������������� 
                               ��������, ������������ ��� ����������� �������� ���������� 
                               ������, � ������, ���� �� ���������� ����� ������� �� 
                               ��������� ������, � ������ �� ������ ������������ 
                               ����������� ���������������� ������� KLPRCI::TASK_RUNNING.
    */

        virtual void SetState(long taskId, TaskState state, const KLPAR::Params * results = 0)  = 0;


    /*!
      \brief ������������� ������� ���������� ������.

      \param taskId       [in]  ������������� ���������� ������.
      \param percent      [in]  ������� ���������� ������ (0-100).
 
    */

        virtual void SetTaskCompletion(long taskId, int percent)  = 0;


    /*!
		\brief ������������� callback-������� ��� ������� �����, ����������� �����������.

        \param callback        [in]  Callback - ������� ��� ������� �����.
	*/

       virtual void SetRunTasksCallback( 
						void*				context,
                        RunTasksCallback	callback )  = 0;

    /*!
		\brief ������������� callback-������� ��� �������� �����, ����������� �����������.

        \param callback        [in]  Callback - ������� ��� �������� �����.
	*/

       virtual void SetTasksControlCallback(
						void*					context,
                        TasksControlCallback	callback )  = 0;

	   virtual long CallRunTasksCallback(
						const std::wstring & taskName,
						const KLPAR::Params * params,
						const std::wstring& asyncId=L"",
						long timeout=0) = 0;

	   virtual void* SetTaskData(long taskId, void* pData) = 0;

       virtual void GetTaskParams(long idTask, KLPAR::Params** pParams) = 0;
      };
}

#endif // KLPRCI_PRODUCTTASKSCONTROL_H

// Local Variables:
// mode: C++
// End:
