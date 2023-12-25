#ifndef __KL_SETTINGS_SYNCHRONIZER_BASE_H__
#define __KL_SETTINGS_SYNCHRONIZER_BASE_H__
/*KLCSAK_PUBLIC_HEADER*/

#include "./conn_types.h"

namespace KLCONN
{
    typedef enum
    {
        SSC_SUPPORT_LIST_LOCK   = 0x1,  //! ��������� ������������ "���������� ������"
        SSC_SUPPORT_ITEM_LOCK   = 0x2   //! ��������� ������������ ���������� ���������
    }SS_CAPABILITIES;

    /*!
     \brief ������������ ��������� ��� �����������, ���������� ��
            ������������� ��������.

        ������ ������� ���������� ����� ������������ �� ������ �����, �� ���
        ���� ������������� ���������� ��������.
    */

    class KLSTD_NOVTABLE SettingsSynchronizerBase : public KLSTD::KLBaseQI
    {
    public:
        /*!
        \brief ��������� ��������� - ������������� ��������/����������
            ��������� ��������� ������� ��������, �� ��������� ���������
            ��������� ���������. ������� ��������� ������ LockList
            ������������� ����� UnlockList.
            ���� ���������� ��������� ��������������, �� ��������,
            ������������ ������� GetCapabilities, ������ ��������� ����
            SSC_SUPPORT_LIST_LOCK. 
            � ������ ������ ������������� ���������� ���� KLERR::Error*

        \param lMaxWaitTime - ������������ ����� �������� ����������, ��

        \exception STDE_NOFUNC - ���������� �� ��������������
        \exception STDE_TIMEOUT - �� ������� ������������� ��������� ��
                ����� lMaxWaitTime.
        */

        virtual void LockList(long lMaxWaitTime) = 0;

        /*!
          \brief	������� ����������, ������������� ������� LockList.
            � ������ ������ ������������� ���������� ���� KLERR::Error*

          \exception STDE_NOFUNC - ���������� �� ��������������
        */
        virtual void UnlockList() = 0;

        /*!
        \brief ��������� ��������� ������� ��������� - �������������
            ��� ��������� ������� ��������. � ��������� �������� ����
            ��������� ������ ������, � ��������� �������� ����� - ������.
            ������� ��������� ������ LockItem ������������� �����
            UnlockItem. ���� ���������� ��������� ���������
            ��������������, �� ��������, ������������ �������
            GetCapabilities, ������ ��������� ����
            SSC_SUPPORT_ITEM_LOCK. 
            � ������ ������ ������������� ���������� ���� KLERR::Error*

        \param lMaxWaitTime - ������������ ����� �������� ����������, ��

        \exception STDE_NOFUNC - ���������� �� ��������������
        \exception STDE_TIMEOUT - �� ������� ������������� ������� ��
                ����� lMaxWaitTime.
        \exception STDE_NOTFOUND - ������� � ��������� ������ �� ������
        */

        virtual void LockItem(
                        const wchar_t*  szwName,
                        long            lMaxWaitTime) = 0;

        /*!
          \brief	������� ����������, ������������� ������� LockItem.
            � ������ ������ ������������� ���������� ���� KLERR::Error*

          \exception STDE_NOFUNC - ���������� �� ��������������
          \exception STDE_NOTFOUND - ������� � ��������� ������ �� ������
        */
        virtual void UnlockItem(const wchar_t* szwName) = 0;

        /*!
          \brief ���������� ����� ������, ����������� �����������
            ���������

          \return ����� SSC_SUPPORT_* ������������ � ������� '|'
        */
        virtual unsigned long   GetCapabilities() = 0;
    };
};

#endif //__KL_SETTINGS_SYNCHRONIZER_BASE_H__
