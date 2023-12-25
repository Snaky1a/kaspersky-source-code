/*!
 * (C) 2004 "Kaspersky Lab"
 *
 * \file conn/task_settings_synchronizer.h
 * \author ������ ��������
 * \date 2004
 * \brief ���������, ���������� �� ������������� �������� �����
 *        ���������� � ����������� ����� ���������� ��� �������
 *        �����������������.
 *
 */

#ifndef KLCONN_TASK_SETTINGS_SYNCHRONIZER_H
#define KLCONN_TASK_SETTINGS_SYNCHRONIZER_H

#include "./conn_types.h"
#include "./settings_synchronizer_base.h"
#include <std/sch/task.h>


namespace KLCONN
{
    //! Application must save this parametr
    const wchar_t c_szwPar_GroupTaskFlag[] = L"PRTS_TASK_GROUPID";	// INT_T

    /*!
     \brief ���������, ���������� �� ������������� �������� �����
            ���������� � ����������� ����� ���������� ��� �������
            �����������������.

        ��������� ����������� ����������� ����������.
        ��������� ������������ �������� �����������������.

        ������ ������� ���������� ����� ������������ �� ������ �����, �� ���
        ���� ������������� ���������� ��������.
    */

    /*
        Some special variables:

        Login/Password for task start.
            Use function KLCSPWD::UnprotectData to decrypt password.
            Use function KLCSPWD::ProtectDataLocally to encrypt
            password for local tasks.
            These variables are put into the pParams container.

            KLPRTS::c_szwTaskAccountUser        login (STRING_T)
	        KLPRTS::c_szwTaskAccountPassword    encrypted password (BINARY_T)

    */

    class KLSTD_NOVTABLE TaskSettingsSynchronizer : public SettingsSynchronizerBase
    {
    public:

    /*!
      \brief ���������� ������ ��������������� ����� ����������.
            � ������ ������ ������������� ���������� ���� KLERR::Error*

	  \param vecTasks [out]  ������ ��������� � ���������� ��������������� �����.
                             ������������ ������ ����������� ���������� �������.

    */
        virtual void GetTasksList (KLSTD::AKWSTRARR& vecTasks)  = 0;


    /*!
      \brief ���������� �������� ������ � �������� ID �� ������
        ��������������� � ���������� ������������ ��������� �����.
             � ������ ������ ������������� ���������� ���� KLERR::Error*

        \param szwTaskId        [in]	������������� ������.
        \param wstrTaskType     [out]	��� ������.
        \param ppTaskSch        [out]	���������� ������.
		\param ppParams         [out]	��������� ������
		\param ppParamsTaskInfo [out]	�������������� ��������� ������

		���� ������ � ��������� ID �� ������� �� ����� ��������� ���������� KLSTD::STDE_NOTFOUND
    */
        virtual void GetTask(
						const wchar_t*  szwTaskId,
                        KLSTD::AKWSTR&  wstrTaskType,
                        KLSCH::Task**   ppTaskSch,
						KLPAR::Params** ppParams,
						KLPAR::Params** ppParamsTaskInfo) = 0;



    /*!
      \brief ��������� ����� ������ ��� ����������. ���� ������ ���
            ����������, �� �� ��������� ���������� �� ���������.
            � ������ ������ ������������� ���������� ���� KLERR::Error*
            ��� ����, ����� ��������� ������ ����� ���� ������� �����
            ������������� �������� ������, �������� c_szwPar_GroupTaskFlag
            �� pParamsTaskInfo ������ ����������� �� ������� ����������.


		\param szwTaskId        [in]  ������������� ������ ��� ����������.
        \param szwTaskType      [in]  ��� ������.
        \param pTaskSch         [in]  ����� ���������� ��������������� � ���������� ������.
		\param pParams          [in]  ��������� ������
		\param pParamsTaskInfo  [in]  �������������� ��������� ������
        \param ppParamsUnsuported [out] ���������������� ����������, �.�.
                ����������� ���������� ���������� �� pParams, ������� ��
                ����� ���� �� ����������� ���������.

        \param ppTaskInfoUnsuported [out] ���������������� ����������, �.�.
                ����������� ���������� ���������� �� pParamsUnsuported,
                ������� �� ����� ���� �� ����������� ���������.
    */
        virtual void PutTask (
			const wchar_t*          szwTaskId,
            const wchar_t*          szwTaskType,
            const KLSCH::Task*      pTaskSch,
		    const KLPAR::Params*    pParams,
		    const KLPAR::Params*    pParamsTaskInfo,
                  KLPAR::Params**   ppParamsUnsuported,
                  KLPAR::Params**   ppTaskInfoUnsuported) = 0;

    /*!
      \brief ������� ������ � �������� ���������������.
        � ������ ������ ������������� ���������� ���� KLERR::Error*

		\param taskId		[in]	������������� ������ ��� ��������.

		\return false - ���� ������ � �������� ��������������� ��
            ����������
        \return true - ������ ���� ������� �������

    */
        virtual bool DeleteTask (
			const wchar_t*  szwTaskId )  = 0;

    /*!
      \brief ������� ����� ������������� ��� ������. ������������ ������
            ����������� ���������� �������.

    */
        virtual KLSTD::AKWSTR CreateNewTaskId() = 0;
    };

    //!Container in pParamsTaskInfo that contains information about task start event, PARAMS_T
    const wchar_t  c_szwTaskStartEvent[] = L"KLCONN_TASK_START_EVENT";
}


#endif // KLCONN_TASK_SETTINGS_SYNCHRONIZER_H


