/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	taskdata_merge.h
 * \author	Andrew Kazachkov
 * \date	17.10.2003 13:24:25
 * \brief	
 * 
 */

#ifndef __KLTASKDATA_MERGE_H__
#define __KLTASKDATA_MERGE_H__

namespace KLHST
{
    class CTaskDataMerger
    {
    public:
        /*!
          \brief	�������������

          \param	pTasksDataSS - ���������� ������ KLPRSS_TASKS_POLICY
                        ��������� SS_SETTINGS, ���� ������ �����������, ��
                        NULL
          \param	pTasksDataPolicy - ���������� ������
                        KLPRSS_TASKS_POLICY ��������, ���� ������
                        �����������, �� NULL
        */

        void Load(
                KLPAR::Params*      pTasksDataSS,
                KLPAR::Params*      pTasksDataPolicy);

        bool Merge(
                const std::wstring& wstrTaskType,
                KLPAR::Params*      pTaskInitial,
                KLPAR::Params**     ppTaskMerged);
    protected:
        KLSTD::CAutoPtr<KLPAR::Params>  m_pMandatory;
        KLSTD::CAutoPtr<KLPAR::Params>  m_pDefault;
        KLSTD::CAutoPtr<KLPAR::Params>  m_pSettings;
    };
};
#endif //__KLTASKDATA_MERGE_H__