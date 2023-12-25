#ifndef KLCONN_NOTIFIER_H
#define KLCONN_NOTIFIER_H

#include "./conn_types.h"
#include "./app_synchronizer.h"
#include "./tasks_synchronizer.h"
/*KLCSAK_PUBLIC_HEADER*/

namespace KLCONN
{
    /*!
     \brief ���������, ���������� �� ����������� ������� �����������������
        � ���������� � ��������� ����������.

        ��������� ����������� �������� �����������������.
        ��������� ������������ ����������� ����������.

        ������ ������� ���������� ����� ������������ �� ������ �����.
    */


    class KLSTD_NOVTABLE  Notifier : public KLSTD::KLBaseQI
    {
    public:
    /*!
      \brief	���������� �� ���������� � ���������� ����������. ������
                ����� ������� �������� ��� ��������/��������/���������
                �������� ��������.

      \param	pSectionNames [in] ������ ���������� �� ����� ������.
      \param	nSectionNames [in] ����� ������� pSectionNames.

     */
        virtual void SettingsChange(
                    const wchar_t** pSectionNames,
                    size_t          nSectionNames) = 0;

    /*!
      \brief ���������� �� ���������� � ���������� ����� ����������. ������
                ����� ������� �������� ��� ��������/�������� ����� ��� 
                ��������� �� ��������.

      \param	pTaskIds [in] ������ ���������� �� �������������� �����.
      \param	nTaskIds [in] ����� ������� pTaskIds.

    */
        virtual void TasksSettingsChange(
                    const wchar_t** pTaskIds,
                    size_t          nTaskIds) = 0;


	/*!
      \brief ���������� �� ���������� � ��������� ������.

      \param	szwTaskId       [in] ������������� ������.
      \param	nNewState       [in] ����� ��������� ������.
      \param	pTaskResults    [in] �������������� ���������.
      \param    tmRiseTime      [in] ����� ��������� ������� � UTC.

      \remarks  ������� ����������� ������ � ������� � ����� ��������� 
                ������ ������ �������� (��������, � ������ �������� � 
                ��������� TSK_STATE_FAILED ����� ����� �������� �������� 
                ��������). ��� ����� ���������� ��������� � pTaskResults 
                ��������� ��������.
                KLEVP::c_er_locid (INT_T)- ������������� ��������� ������ -- 
                        ��� ����������� �������� 
                KLEVP::c_er_par1...c_er_par9 (STRING_T) - ��������� ��������� 
                        ������ c_er_locid (������)
                KLEVP::c_er_descr (STRING_T) - �������� ������� (�� ���� 
                        ��������� ������ � �������������� c_er_par1...
                        c_er_par9) ��� ���������� ����������� ������� 
                        ��� ������ � EventLog ��� �������� �� �����. 

                ��� ��������� TSK_STATE_RUNNING ����� ����� ����� 
                ���������� �������� �������� �������� (��. ����) �/��� 
                �������� ���������� ������ � ������� �������� 
                c_er_completedPercent.
                KLEVP::c_er_completedPercent (INT_T) - ������� ����������.

                ����� ����, ����� ������ �������� �� �������� �� ���������
                �������� ��������, ��� ����� ������� ��������� � pTaskResults 
                ������� c_er_severity. �� ���������, ��������� TSK_STATE_FAILED
                ����� �������� KLEVP_EVENT_SEVERITY_ERROR, ������ ���������
                ����� �������� KLEVP_EVENT_SEVERITY_INFO.
                KLEVP::c_er_severity (INT_T) - ��������, ���� �� 
                        �������� KLEVP_EVENT_SEVERITY_*:
                            KLEVP_EVENT_SEVERITY_INFO, 
                            KLEVP_EVENT_SEVERITY_WARNING, 
                            KLEVP_EVENT_SEVERITY_ERROR, 
                            KLEVP_EVENT_SEVERITY_CRITICAL. 
    */
        virtual void TaskStateChange(
                    const wchar_t*      szwTaskId,
                    KLCONN::TskState    nNewState,
                    KLPAR::Params*      pTaskResults,
                    const raise_time_t& tmRiseTime = raise_time_t::Now()) = 0;


	/*!
      \brief ���������� �� ���������� � ��������� ������.

      \param	szwTaskId       [in] ������������� ������.
      \param	nCompletion     [in] ����� �������� �������� ����������.
      \param    tmRiseTime   [in] ����� ��������� ������� � UTC.

    */
        virtual void TaskCompletionChange(
                    const wchar_t*      szwTaskId,
                    int                 nCompletion,
                    const raise_time_t& tmRiseTime = raise_time_t::Now()) = 0;


    /*!
      \brief ���������� � ���������� � ��������� ����������

      \param	nNewState [in] ����� ��������� ����������.
      \param	pData     [in] �������������� ���������.
      \param    tmRiseTime   [in] ����� ��������� ������� � UTC.

    */
        virtual void ApplicationStateChange(
                    KLCONN::AppState    nNewState,
                    KLPAR::Params*      pData,
                    const raise_time_t& tmRiseTime = raise_time_t::Now()) = 0;


    /*!
      \brief	���������� � ������� � ������ ����������.

      \param	szwEventType [in] ��� (���) �������
      \param	pEventBody   [in] ���� �������.
      \param    tmRiseTime   [in] ����� ��������� ������� � UTC.

      \remarks  ��� ����������� ���������� ��������� � ����������� 
                � ���� ������� ������� ��������� ��������� ��������:
                KLEVP::c_er_locid (INT_T)- ������������� ��������� ������ -- 
                        ��� ����������� �������� 
                KLEVP::c_er_par1...c_er_par9 (STRING_T) - ��������� ��������� 
                        ������ c_er_locid (������)
                KLEVP::c_er_severity (INT_T) - ��������, ���� �� 
                        �������� KLEVP_EVENT_SEVERITY_*:
                            KLEVP_EVENT_SEVERITY_INFO, 
                            KLEVP_EVENT_SEVERITY_WARNING, 
                            KLEVP_EVENT_SEVERITY_ERROR, 
                            KLEVP_EVENT_SEVERITY_CRITICAL. 

                KLEVP::c_er_task_display_name (STRING_T) - 
                        ������������ ��� ������, � ���������� ������ 
                        ������� ���� ������������ �������. 

                ����� ����, ��������� ���� ���������� ��� ���������� 
                ����������� ������� ��� ������ � EventLog ��� �������� ��
                �����. 
                KLEVP::c_er_descr (STRING_T) - �������� ������� (�� ���� 
                        ��������� ������ � �������������� c_er_par1...c_er_par9). 
                KLEVP::c_er_event_type_display_name (STRING_T) 
                        ������������� ��� ���� �������.

    */
        virtual void Event(
                        const wchar_t*      szwEventType,
                        KLPAR::Params*      pEventBody,
                        const raise_time_t& tmRiseTime = raise_time_t::Now()) = 0;

        /*!
          \brief	���������� �� ��������� ������� ����������.
                    ��. AppSynchronizer::GetApplicationProperties

          \param    tmRiseTime   [in] ����� ��������� ������� � UTC.

        */
        virtual void ApplicationPropertiesChange(
                    const raise_time_t& tmRiseTime = raise_time_t::Now()) = 0;

        /*!
          \brief	���������� �� ��������� ��������� ������ ��������� 
                    �������. ��. AppSynchronizer::GetRtpState

          \param    nRtpState   [in] ��������� ������ ��������� �������
          \param    nErrorCode  [in] ��� ������ ( ��� ��������� of APP_RTP_STATE_FAILURE)

        */
        virtual void RtpStateChanges(
                        AppRtpState    nRtpState,
                        int            nErrorCode) = 0;
    };    
}

#endif // KLCONN_NOTIFIER_H


