/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file TSK/GroupTaskControl.h
 * \author ������ ��������
 * \date 2002
 * \brief ��������� ��� ������ � ���������� ��������. ���������� TaskStorage.
 *
 */

#ifndef __TSK_GROUPTASKCONTROL_H__
#define __TSK_GROUPTASKCONTROL_H__

#include <kca/prts/tasksstorage.h>
#include <kca/prci/producttaskscontrol.h>
#include "./grouptaskstatus.h"
#include <srvp/evp/eventproperties.h>
#include <server/tsk/common.h>

namespace KLTSK
{
	const wchar_t c_need_reboot_cnt[] = L"KLTSK_NEED_RBT_CNT"; // INT_T - c�. GroupTaskControl::GetTaskStatistics
	const wchar_t c_error_reasons_cnt[] = L"KLTSK_ERR_REASONS_CNT"; // PARAMS_T - ��. GroupTaskControl::GetTaskStatistics
	const wchar_t c_virtual_progress_active[] = L"KLTSK_VIRT_PRGS"; // BOOL_T - ��. GroupTaskControl::GetTaskStatistics

    /*!
    * \brief ��������� ��� ������ � ���������� ��������.
    */
    class GroupTaskControl : public KLSTD::KLBaseQI
    {
    public:
        /*!
          \brief ���������� TasksStorage ��� ��������� ����� (�.�. �������������� � �������).
                    ID ������ ������ ��� ������ TasksStorage, ������������� ���� ��������, 
                    ��������� ����� ���� ��������� �����, �.�. ��� ����� �� ���� TaskStorage, 
                    ���������� ���� �������� � �������� GetCommonTasks.

          \param nGroupId   ID ������

          \return ��������� TasksStorage
        */
        virtual KLSTD::CAutoPtr<KLPRTS::TasksStorage> GetGroupTasks( int nGroupId ) = 0;

        virtual void ForbidTaskForGroup( int nGroupId, const std::wstring& wstrTaskId ) = 0;

        /*!
          \brief ���������� TasksStorage ��� ��������� �����, �������������� � �������, �� �������
                    ���������. � ������������ ������. ID ������ ������ ��� ������ TasksStorage,
                    ������������� ���� ��������, ��������� ����� ���� ��������� �����.

          \return ��������� TasksStorage
        */
        virtual KLSTD::CAutoPtr<KLPRTS::TasksStorage> GetCommonTasks() = 0;

        /*!
          \brief ���������� TasksStorage ��� ��������� �����, �.�. �������������� � 
                    ��������� ������. ID ������ ������ ��� TasksStorage, 
                    ������������� ���� ��������, ��������� ������ ����� ����� ���� 
                    ��������� ������.
          \param domain   ��� ������, � ������� ��������� ����.
          \param name     ��� �����

          \return ��������� TasksStorage
        */
        virtual KLSTD::CAutoPtr<KLPRTS::TasksStorage>
        GetHostTasks( const std::wstring & domain, const std::wstring & name ) = 0;

        /*
          \brief ���������� GroupTaskStatus ��� ��������� �����, �.�. �����, �������������� � 
                    �������.

          \param wstrTaskId [in]  ID ������, ���������� �� TaskStorage, �������������
            ���� GetCommonTasks(), ���� GetGroupTasks()
        */
        virtual KLSTD::CAutoPtr<GroupTaskStatus> GetGroupTaskStatus( const std::wstring& wstrTaskId ) = 0;

        /*
          \brief ���������� GroupTaskHistory ��� ��������� �����, �.�. �����, �������������� � 
                    �������.

          \param wstrTaskId [in]  ID ������, ���������� �� TaskStorage, �������������
            ���� GetCommonTasks(), ���� GetGroupTasks()
        */
        virtual KLSTD::CAutoPtr<KLEVP::EventProperties> GetGroupTaskHistory(
            const std::wstring& wstrTaskId,
	        const std::vector<std::wstring>& vect_fields,
	        const std::vector<KLCSP::field_order_t>& vect_fields_to_order,
            long  lifetime,
            const std::wstring& wstrDomainName = L"" ,
            const std::wstring& wstrHostName = L"",
			const KLPAR::Params* pParamsIteratorDescr = NULL /*! ��������� ���������� �������*/) = 0;

        /*!
          \brief ������ ������ "����� ������"

            \param wstrTaskId  ID ��������� ������, ���������� �� TaskStorage,
                ������������� ���� GetGroupTasks, ���� GetCommonTasks.
            \wstrHostName ��� �����, �� ������� ��������� ������. ����� ���� ������ ������� - �����
                    ����������� �� ���� ������, �� ������� ������ �������� ��� ������.
                    ���� �� ������ ������, �� ��������� ���� ������ ������� � ������ ����� ������.
            \bEvenIfAlreadySucceeded ���� true, �� ������������ ��� ������� �����, ���� ���� �� 
                    ���� �����, ������ ��� ������� ����������. ���� false, �� ���������� ���� �� ������,
                    ��� ������ ������� �� �����������. �������� ����� ����� � � ������, ����� ������ 
                    ���� ����.
        */
        virtual void RunTaskNow(
            const std::wstring& wstrTaskId,
            const std::wstring& wstrDomainName = L"",
            const std::wstring& wstrHostName = L"",
            bool bEvenIfAlreadySucceeded = false
        ) = 0;

        /*!
          \brief ������������ ������

            \param wstrTaskId  ID ������ �� TaskStorage, ������������� �������� GetServerInitiatedTasks
            \param domain   ��� ������, � ������� ��������� ����. ���� ������ ������, 
                                �� TaskId - ��� ID ��������� ������, ����� 
                                ��� ID ��������� ������ �� �����.
            \param name     ��� �����
        */
        virtual void SuspendTask( const std::wstring& wstrTaskId,
                                  const std::wstring & domain,
                                  const std::wstring & name ) = 0;


        /*!
          \brief ������� ������ ����� �������� SuspendTask

            \param wstrTaskId  ID ������ �� TaskStorage, ������������� �������� GetServerInitiatedTasks
            \param domain   ��� ������, � ������� ��������� ����. ���� ������ ������, 
                                �� TaskId - ��� ID ��������� ������, ����� 
                                ��� ID ��������� ������ �� �����.
            \param name     ��� �����
        */
        virtual void ResumeTask( const std::wstring& wstrTaskId,
                                 const std::wstring & domain,
                                 const std::wstring & name ) = 0;


        /*!
          \brief ������ ������

            \param wstrTaskId  ID ������ �� TaskStorage, ������������� �������� GetServerInitiatedTasks
            \param domain   ��� ������, � ������� ��������� ����. ���� ������ ������, 
                                �� TaskId - ��� ID ��������� ������, ����� 
                                ��� ID ��������� ������ �� �����.
            \param name     ��� �����
        */
        virtual void CancelTask( const std::wstring& wstrTaskId,
                                 const std::wstring & domain,
                                 const std::wstring & name ) = 0;



        /*!
          \brief GetAllTasksOfHost - ��������� ���� ��������� � ���������� ����� ������� �����

            \param wstrDomainName - �����
            \param wstrHostName   - ��� �����
            \param vectTaskIds [out] - ������ �� TsID �����
        */
        virtual void GetAllTasksOfHost(
            const std::wstring & wstrDomainName,
            const std::wstring & wstrHostName,
            std::vector<std::wstring> & vectTaskIds ) = 0;

        /*!
          \brief GetTaskByID - ���������� �������� ������ � �������� ID.
            ID ����� ��������� ����� ���� TaskStorage'��, ������������
            �������� ����� ����������.

            \param taskId			[in]  ������������� ������ � Task Storage.
            \param componentId      [out]  ������������� ����������.
            \param taskName         [out]  ��� ������, ��������������� ��� ����������.
            \param task             [out]  �������� ��������������� � ���������� ������.
		    \param params			[out]  ��������� ������
		    \param paramsTaskInfo	[out]  �������������� ��������� ������
		    \param startOnEvent     [out]  ����������� �� ������ ��� ������������� � ������� ������������� �������.
        */
        virtual void GetTaskByID ( 
						const std::wstring &taskId,
                        KLPRCI::ComponentId & id,
                        std::wstring & taskName,
						bool& bStartOnEvent,
                        KLSCH::Task ** task,
						KLPAR::Params** params,
						KLPAR::Params** paramsTaskInfo ) = 0;

        /*!
          \brief GetTaskStatistics - ���������� ��������� ���-�� ������, ����������� �
            ��������� ����������.
            \param wstrTaskId		[in]  ������������� ������ � Task Storage.
            \param wstrTaskId       [out] Params �� �����������. �������� � ���� �������� IntValue �
                    �������, ������� ���������� �������������� � ����n����� �����
                    �������� ���� HostState. �.�. ����� �������������� ���� hsNone=0x01, ��
                    ������� � ������ "1" ����� ��������� � ���� ���-�� ������ ��� ������
                    ������ �� �������� hsNone.
                    � ppStatistics ����� ������������� �� ��� ���� ��������, ��� � ���� �����
                    ���� ������.
					����� ����� �������������� ���������:
					 - KLEVP::c_er_completedPercent - ����� % ���������� ������;
					 - KLTSK::c_need_reboot_cnt - ����� �����������, ��������� ������������ ��� ���������� ������;
					 - KLTSK::c_error_reasons_cnt - Params, ��� - ������� ������ (KLTSK::RIFailReason), 
						�������� - ����� �����������, �� ������� ������ ����������� � ����� �������.
					 - KLTSK::c_virtual_progress_active - Bool, true, ���� ����� % ���������� ����� �������� 
						��� ������� �� ��������� % ���������� ������ �� ������������ �����.
        */
        virtual void GetTaskStatistics(
			const std::wstring & wstrTaskId,
			KLPAR::Params** ppStatistics ) = 0;
        
        /*!
          \brief ������������� �� ������ �������� ��� ��������� ������� ���������� 
                    �����.
 
          \param nSecondsToLive - ����� ����� ��������� � ��������.
        */
        // virtual void ResetIteratorForTaskHistory( long nSecondsToLive = 20 ) = 0;


        /*!
          \brief ���������� ��������� ���� �� TaskHistory (��.������� ResetIteratorForTaskHistory)

            \param nRecCount            [in]  in - ������������ ���������� �������
            \param vectTaskHistoryItem  [out] ������ �� TaskHistory

            \return     ���� EOF
        */
        // virtual bool GetNextTaskHistoryBlock( long& nRecCount,
         //   std::vector<TaskHistoryItem>& vectTaskHistoryItem ) = 0;
    };
	
    class GroupTaskControl2 : public GroupTaskControl
    {
    public:
        /*!
          \brief ���������� TasksStorage ��� ��������� ����� (�.�. �������������� � �������),
					������� ��������� ����� � ������������ �����.
                    ID ������ ������ ��� ������ TasksStorage, ������������� ���� ��������, 
                    ��������� ����� ���� ��������� �����, �.�. ��� ����� �� ���� TaskStorage, 
                    ���������� ���� �������� � �������� GetCommonTasks.

          \param nGroupId   ID ������

          \return ��������� TasksStorage
        */
        virtual KLSTD::CAutoPtr<KLPRTS::TasksStorage> GetGroupTasks2( int nGroupId, bool bIncludeSupergroups ) = 0;

        /*!
          \brief ���������� ������������� ������ ��� ��������� ������.

          \param wstrTaskId   ID ������

          \return ID ������
        */
        virtual int GetTaskGroup( const std::wstring& wstrTaskId ) = 0;
	};

}

#endif // __TSK_GROUPTASKCONTROL_H__