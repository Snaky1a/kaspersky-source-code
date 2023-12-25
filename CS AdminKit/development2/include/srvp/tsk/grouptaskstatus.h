/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file tsk/grouptaskstatus.h
 * \author ������ ��������
 * \date 2003
 * \brief ��������� ��� ��������� ���������� ������� ����� ��������� ������, 
 *        ������������� �� ������ �������.
 */

#ifndef __TSK_GROUP_TASK_STATUS_H__
#define __TSK_GROUP_TASK_STATUS_H__

#include <srvp/csp/klcsp.h>
#include <srvp/tsk/grouptaskbase.h>

namespace KLTSK
{
    /*!
    * \brief ��������� ��� ��������� ���������� ������� ����� ��������� ������, 
        ������������� �� ������ �������.
    */
    class GroupTaskStatus : public KLSTD::KLBase
    {
    public:

		/*
			\brief ������������� �� ������ �������� ��������� ������ ������.

			\param fields [in] ������ �����, ������� ���� ��������.
            \size [in] ������ ������
            \param hsHostStateMask [in] ����� � ����� �������� ����� ��������. �������� �������
                ����� ������������� ��������.
			\param lifetime [in] ����� ����� ������� �� ������� (���).
		*/
		virtual void ResetHostIterator(
			const wchar_t**		fields,
			int					size,
            HostState   hsHostStateMask,
			long        nLifetime = 20)  = 0;

		/*
			\brief �������� ���������� � ��������� ���������� � ������.

			\param nCount	[in, out] in - ���������� �������, ������� ���������� �������,
                    out - ���-�� ������� ��������� �������.
			\param ppParHostStatus     [out] ��������� - �������� �������� c ������ c_host_state_array,
                ����� ARRAY_T. ������ �������� nCount[out] ���������, ������ ������� � ������� -
                 ��������� Params c ���������� � ������, ���������� ���� (��������� c_hs*).
			\return	false, ���� ��������� ����� ������ �����������. ���� false, �� ����� 
                � nCount ������������� 0.

		*/
        virtual bool GetNext( long& nCount, KLPAR::Params** ppParHostStatus ) = 0;

		/*
			\brief ������������� �� ������ �������� ��������� ������ ������.

			\param vectFields [in] ������ �����, ������� ���� ��������.
			\param vect_fields_to_order [in] ������ �����, �� ������� ���� ������������ ����������
            \param hsHostStateMask [in] ����� � ����� �������� ����� ��������. �������� �������
                ����� ������������� ��������.
			\param lifetime [in] ����� ����� ������� �� ������� (���).
		*/
		virtual void ResetHostIteratorEx(
			const std::vector<std::wstring> vectFields,
			const std::vector<KLCSP::field_order_t>& vect_fields_to_order,
            HostState   hsHostStateMask,
			long        nLifetime = 20)  = 0;

        /*!
          \brief	GetRecordCount

          \return	long ���������� ���������� ������� � ������
        */
        virtual long GetRecordCount() = 0;
		
		/*
			\brief ���������� �������� �������� �������.

            \param	long nStart [in] - ���������� ����� ��������� ������
            \param	long nEnd [in] - ���������� ����� �������� ������
			\param ppParHostStatus [out] - ��������� - �������� �������� c ������ c_host_state_array,
                ����� ARRAY_T. ������ �������� (nEnd - nStart + 1) ���������, ������ ������� � ������� -
                 ��������� Params c ���������� � ������, ���������� ���� (��������� c_hs*).
			\return	int - �������� ����� ������� ������������ �������.

		*/
        virtual int GetRecordRange(long nStart, long nEnd, KLPAR::Params** ppParHostStatus ) = 0;
    };
}

#endif // __TSK_GROUP_TASK_STATUS_H__

