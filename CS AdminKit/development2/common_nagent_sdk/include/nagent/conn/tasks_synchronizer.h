/*!
 * (C) 2004 "Kaspersky Lab"
 *
 * \file conn/tasks_synchronizer.h
 * \author ������ ��������
 * \date 2004
 * \brief ���������, ���������� �� ������������� ��������� ����� ����������
 *        � ���������� ����� � ������� �����������������. 
 *
 */

#ifndef KLCONN_TASKS_SYNCHRONIZER_H
#define KLCONN_TASKS_SYNCHRONIZER_H

#include "./conn_types.h"

namespace KLCONN
{
    typedef enum
    {
        TSK_ACTION_START    =   5, //KLPRCI::ACTION_START,
        TSK_ACTION_STOP     =   0, //KLPRCI::ACTION_STOP,
        TSK_ACTION_SUSPEND  =   1, //KLPRCI::ACTION_SUSPEND,
        TSK_ACTION_RESUME   =   2  //KLPRCI::ACTION_RESUME
    }TskAction;

    typedef enum
    {
        TSK_STATE_INACTIVE  = 7, //KLPRCI::TASK_INACTIVE,
        TSK_STATE_RUNNING   = 1, //KLPRCI::TASK_RUNNING,
        TSK_STATE_SUSPENDED = 2, //KLPRCI::TASK_SUSPENDED,
        TSK_STATE_COMPLETED = 4, //KLPRCI::TASK_COMPLETED,
        TSK_STATE_FAILED    = 3  //KLPRCI::TASK_FAILURE
    }TskState;

    /*!
     \brief ���������, ���������� �� ������������� ��������� ����� ����������
	        � ���������� ����� � ������� �����������������.

        ��������� ����������� ����������� ����������.
        ��������� ������������ �������� �����������������.

        ������ ������� ���������� ����� ������������ �� ������ �����, �� ���
        ���� ������������� ���������� ��������.
    */

    class KLSTD_NOVTABLE TasksSynchronizer : public KLSTD::KLBaseQI
    {
    public:
    /*!
      \brief ���������� ������� ������ ������.

        \param szwTaskId    [in]	������������� ������ ��� ��������� �������.
        \param nState	    [out]	������� ������ ������.
        \param ppResult     [out]   �������������� ���������.
        \param tmRiseTime   [out]   ����� ���������� ������� � UTC.

        \exception KLSTD::STDE_NOTFOUND - ������ � ���������
            ��������������� �� �������
    */
        virtual void GetTaskStatus(
                        const wchar_t*          szwTaskId, 
                        KLCONN::TskState&       nState, 
                        KLPAR::Params**         ppResult,
                        KLCONN::raise_time_t&   tmRiseTime) = 0;
    /*!
      \brief ���������� ������� ���������� ������.

        \param szwTaskId    [in]	������������� ������ ��� ��������� �������.
        \param nPercent	    [out]	������� ������� ���������� ������.
        \param tmRiseTime   [out]   ����� ���������� ������� � UTC.

        \exception KLSTD::STDE_NOTFOUND - ������ � ���������
            ��������������� �� �������
        \exception KLSTD::STDE_NOFUNC - ������ �� ����� �������� ����������
    */
        virtual void GetTaskCompletion(
                        const wchar_t*          szwTaskId,
                        int&                    nPercent,
                        KLCONN::raise_time_t&   tmRiseTime) = 0;

    /*!
      \brief �������� ������ �������.

		\param wstrId   [in]    ������������� ������
		\param nAction  [in]    ��������, ������� ��������� ��������� ��� ������.
        \param pData    [in]    �������������� ���������.

		\exception KLSTD::STDE_NOTFOUND - ������ � ���������
            ��������������� �� �������
        \exception KLSTD::STDE_NOFUNC - ������ �� ������������ ���������
            ��������
    */
        virtual void SendTaskAction(
                        const wchar_t*      szwTaskId, 
                        KLCONN::TskAction   nAction)  = 0;

    };
}


#endif // KLCONN_TASKS_SYNCHRONIZER_H


