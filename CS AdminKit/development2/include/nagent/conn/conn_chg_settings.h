/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	conn_chg_settings.h
 * \author	Andrew Kazachkov
 * \date	13.08.2007 15:47:34
 * \brief	���������, ���������� �� ����������� � ������� �������� 
 *        �������� � ��������� ����� ����������
 */

#ifndef __KLCONN_CHG_SETTINGS_H__
#define __KLCONN_CHG_SETTINGS_H__
/*KLCSAK_PUBLIC_HEADER*/

#include "./conn_types.h"

#include "./settings_synchronizer_base.h"

namespace KLCONN
{
    /*!
     \brief ���������, ���������� �� ����������� � ������� �������� 
        �������� � ��������� ����� ����������

        ��������� ����������� ����������� ����������.
        ��������� ������������ �������� �����������������.

        ������ ������� ���������� ����� ������������ �� ������ �����, �� ���
        ���� ������������� ���������� ��������.

        ������ ��������� ������������ �������� ����������������� ������ � ������, 
        ���� ��� ��������� ���������� ��� ��������� ���� CIF_PRIVATE_POLICY_FORMAT.
        � ��������� ������ ������� ����� ��������, ��� ������ �������� ��������� 
        ������������� ������� �������� � ������������ ��������� ��������������. 
    */

    class KLSTD_NOVTABLE SettingsModifier
        :   public KLSTD::KLBaseQI
    {
    public:

        /*!
          \brief	��������� ������ �������������� ��������� � ��������� 
                    ������, ������� ������������ ������ �������� � ������ szwName. 
                    ���� �������������� �� ������� (��������, ������� 
                    ������ �������������), ������� ������ ����������. 
                    ����� ModifyLocalTasksAndSettingsWithPolicySection ����� 
                    ������ ������. 

          \param	szwName IN ��� ������ � ��������
        */
        virtual void ModifyLocalTasksAndSettingsWithPolicySection(
                        const wchar_t* szwName) = 0;
    };
};

#endif //__KLCONN_CHG_SETTINGS_H__
