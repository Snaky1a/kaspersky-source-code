/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file EveryMonthSchedule.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ������ ���������� ������ 
 *        ��� ������� �������-������������� ����������.
 *
 */
/*KLCSAK_PUBLIC_HEADER*/

#ifndef KLSCH_EVERYMONTHSCHEDULE_H
#define KLSCH_EVERYMONTHSCHEDULE_H

#include "std/sch/errors.h"
#include "schedule.h"

#include "std/base/klbase.h"

namespace KLSCH {


   
    /*!
    * \brief ���������� ������ ��� ������� �� �������-�������������
    *        ����������.
    *
    */ 


    class EveryMonthSchedule : public Schedule
	{

    public:
		
		/*!
			\brief ����������� ����������.
		*/
		virtual ~EveryMonthSchedule() {}

		/*!
			\brief ���������� ��� ����������
		*/
		virtual ScheduleType GetType() const = 0;

        /*!
            \brief ������������� ����� ��� ������������ ���������� ������.

            \param day [in] ���� ������ ��� ������� ������ (1-31).
            \param hours [in] ��� ��� ������� ������ (0-23).
            \param min [in] ������ ��� ������� ������ (0-59).
            \param sec [in] ������� ��� ������� ������ (0-59).
            \return ��� ������

        */
        virtual Errors SetExecutionTime( int day = 0,
                                 int hours = 0, 
                                 int min = 0,
                                 int sec = 0) = 0;


        /*!
            \brief ���������� ����� ��� ������������ ���������� ������.

            \param day [out] ���� ������ ��� ������� ������ (1-31).
            \param hours [out] ��� ��� ������� ������ (0-23).
            \param min [out] ������ ��� ������� ������ (0-59).
            \param sec [out] ������� ��� ������� ������ (0-59).
            \return ��� ������

        */
        virtual Errors GetExecutionTime( int& day, int& hours, int& min, int& sec) const = 0;
		
		/*!
            \brief ������������� ������ ���������� ������ � �������
				( �� ��������� ������ ����� 1 ����� )

            \param months [in] ������ ���������� ������ � �������
            \return ��� ������

        */
        virtual Errors SetPeriod( int months = 1 ) = 0;

        /*!
            \brief ���������� ������ ���������� ������ � �������

            \param months [out] ������ ���������� ������ � �������
            \return ��� ������

        */
        virtual Errors GetPeriod( int& months ) const = 0;
    };
}

/*
	\brief ����� ��� �������� ������� MillisecondsSchedule
*/
KLCSC_DECL KLSCH::EveryMonthSchedule *KLSCH_CreateEveryMonthSchedule();

#endif // KLSCH_EVERYMONTHSCHEDULE_H
