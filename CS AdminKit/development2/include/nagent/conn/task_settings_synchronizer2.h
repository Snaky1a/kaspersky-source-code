/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	task_settings_synchronizer2.h
 * \author	Andrew Kazachkov
 * \date	12.09.2005 10:31:20
 * \brief ���������, ���������� �� ������������� �������� �����
 *        ���������� � ����������� ����� ���������� ��� �������
 *        �����������������. 
 */
/*KLCSAK_PUBLIC_HEADER*/

#ifndef __KL_TASK_SETTINGS_SYNCHRONIZER2_H__
#define __KL_TASK_SETTINGS_SYNCHRONIZER2_H__

#include "./task_settings_synchronizer.h"
#include <std/sch/task.h>


namespace KLCONN
{
    /*!
     \brief ���������, ���������� �� ������������� �������� �����
            ���������� � ����������� ����� ���������� ��� �������
            �����������������.

        ��������� ����������� ����������� ����������.
        ��������� ������������ �������� �����������������.

        ������ ������� ���������� ����� ������������ �� ������ �����, �� ���
        ���� ������������� ���������� ��������.
    */

    class KLSTD_NOVTABLE TaskSettingsSynchronizer2 : public TaskSettingsSynchronizer
    {
    public:
    /*!
      \brief ������� ����� ������������� ��� ������. ������������ ������ 
            ����������� ���������� �������.

        \param szwTaskType      [in]  ��� ������.
    */
        virtual KLSTD::AKWSTR CreateNewTaskId2(
                                const wchar_t* szwTaskType) = 0;
    };
}

#endif //__KL_TASK_SETTINGS_SYNCHRONIZER2_H__
