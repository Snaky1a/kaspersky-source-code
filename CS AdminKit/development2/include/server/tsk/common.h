/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	tsk/common.h
 * \author	Mikhail Karmazine
 * \date	24.06.2003 13:13:29
 * \brief	����� ���������� ��� ��������� � ���������� ������,
            � �.�. ��� ������, ���������� �� ������
 * 
 */


#ifndef __TSK_COMMON_H__
#define __TSK_COMMON_H__

namespace KLTSK
{
    /* � ������ ������������� ���������, ����������, ��� ������������� ���������
        ��������� ������ � �� �������� TaskInfo ����������� ��������� ������ (�
        ����������� ��������������): */

    enum GroupTaskAction { gtaRun, gtaStop, gtaPause, gtaResume, gtaNone };

    // PARAMS_T, �������� � ���� ������ ��� �������� (��.���������
    // ��������� c_szwGroupTaskAction*).
    // ����������� � TaskInfo:
    // +---<c_szwGroupTaskActionId>
    // |        c_szwGroupTaskActionType
    // |        c_szwGroupTaskActionDate
    const wchar_t c_szwGroupTaskActionData[] = L"KLTSK_GROUP_TASK_ACTION_DATA";

    // STRING_T, �������� � ���� ID, ���������� ��� ������ ������������� - � ���,
    // ����� ��������� ��� � ������ ��������� �������������.
    const wchar_t c_szwGroupTaskActionId[] = L"KLTSK_GROUP_TASK_ACTION_ID";

    // INT_T, �������� � ���� ���. � ���, ��� ����� ������. ����� ���� ����� �� 
    // �������� enum GroupTaskAction.
    const wchar_t c_szwGroupTaskActionType[] = L"KLTSK_GROUP_TASK_ACTION_TYPE";

    // DATE_TIME_T, �������� � ���� ���. � ���� ������� �������
    const wchar_t c_szwGroupTaskActionDate[] = L"KLTSK_GROUP_TASK_ACTION_DATE";

    // BOOL_T, �������� � �������, ����� �� �������� �������������� �� ��������.
    const wchar_t c_szwGroupTaskActionSkipOnSlaves[] = L"KLTSK_GROUP_TASK_ACTION_SKIP_SLV";
	const bool c_bGroupTaskActionSkipOnSlavesDflt = false;
}

#endif //__TSK_COMMON_H__

// Local Variables:
// mode: C++
// End:
