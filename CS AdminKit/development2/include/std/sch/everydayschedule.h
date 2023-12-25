/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file EverydaySchedule.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ������ ���������� ������ 
 *        ��� ������� �������-������������� ���������.
 *
 */
/*KLCSAK_PUBLIC_HEADER*/

#ifndef KLSCH_EVERYDAYSCHEDULE_H
#define KLSCH_EVERYDAYSCHEDULE_H

#include "std/sch/errors.h"
#include "schedule.h"

#include "std/base/klbase.h"

namespace KLSCH {


   
    /*!
    * \brief ���������� ������ ��� ������� �� �������-�������������
    *        ���������.
    *
    */ 


    class EverydaySchedule : public Schedule
	{

    public:

		/*!
			\brief ����������� ����������.
		*/
		virtual ~EverydaySchedule() {}

		/*!
			\brief ���������� ��� ����������
		*/
		virtual ScheduleType GetType() const = 0;

        /*!
            \brief ������������� ����� ��� ����������� ���������� ������.

            \param hours [in] ��� ��� ������� ������ (0-23).
            \param min [in] ������ ��� ������� ������ (0-59).
            \param sec [in] ������� ��� ������� ������ (0-59).
            \return ��� ������

        */
        virtual Errors SetExecutionTime( int hours = 0, 
                                 int min = 0,
                                 int sec = 0) = 0;


        /*!
            \brief ���������� ����� ��� ����������� ���������� ������.

            \param hours [out] ��� ��� ������� ������ (0-23).
            \param min [out] ������ ��� ������� ������ (0-59).
            \param sec [out] ������� ��� ������� ������ (0-59).
            \return ��� ������

        */
        virtual Errors GetExecutionTime( int& hours, int& min, int& sec) const = 0;
		

		/*!
            \brief ������������� ������ ���������� ������ � ����
				( �� ��������� ������ ����� 1 ���� )

            \param days [in] ������ ���������� ������ � ����
            \return ��� ������

        */
        virtual Errors SetPeriod( int days = 1 ) = 0;

        /*!
            \brief ���������� ������ ���������� ������ � ����

            \param days [out] ������ ���������� ������ � ����.
            \return ��� ������

        */
        virtual Errors GetPeriod( int& days ) const = 0;		
    };
}

/*
	\brief ����� ��� �������� ������� MillisecondsSchedule
*/
KLCSC_DECL KLSCH::EverydaySchedule *KLSCH_CreateEverydaySchedule();

#endif // KLSCH_EVERYDAYSCHEDULE_H
