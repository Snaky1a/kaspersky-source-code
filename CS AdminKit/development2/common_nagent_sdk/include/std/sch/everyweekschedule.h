/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file EveryWeekSchedule.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ������ ���������� ������ 
 *        ��� ������� �������-������������� �����������.
 *
 */

#ifndef KLSCH_EVERYWEEKSCHEDULE_H
#define KLSCH_EVERYWEEKSCHEDULE_H

#include "std/sch/errors.h"
#include "schedule.h"

#include "std/base/klbase.h"

namespace KLSCH {


   
    /*!
    * \brief ���������� ������ ��� ������� �� �������-�������������
    *        �����������.
    *
    */ 


    class EveryWeekSchedule : public Schedule
	{

    public:

		/*!
			\brief ����������� ����������.
		*/
		virtual ~EveryWeekSchedule() {}

		/*!
			\brief ���������� ��� ����������
		*/
		virtual ScheduleType GetType() const = 0;

		/*!
            \brief ������������� ����� ��� ������������� ���������� ������.

            \param day [in] ���� ��� ������� ������ (0-6). ����������� - 0.
            \param hours [in] ��� ��� ������� ������ (0-23).
            \param min [in] ������ ��� ������� ������ (0-59).
            \param sec [in] ������� ��� ������� ������ (0-59).
            \return ��� ������
				\retval <ERR_TIME_INTERVAL>

        */
        virtual Errors SetExecutionTime( int day = 0,
                                 int hours = 0, 
                                 int min = 0,
                                 int sec = 0) = 0;


        /*!
            \brief ���������� ����� ��� ����������� ���������� ������.

            \param day [out] ���� ��� ������� ������ (0-6). ����������� - 0.
            \param hours [out] ��� ��� ������� ������ (0-23).
            \param min [out] ������ ��� ������� ������ (0-59).
            \param sec [out] ������� ��� ������� ������ (0-59).
            \return ��� ������
				\retval <ERR_SCHEDULE> ���������� �������� ������ �� ����������������

        */
        virtual Errors GetExecutionTime( int& day, int& hours, int& min, int& sec) const = 0;
		
		/*!
            \brief ������������� ������ ���������� ������ � �������
				( �� ��������� ������ ����� 1 ������ )

            \param weeks [in] ������ ���������� ������ � �������
            \return ��� ������

        */
        virtual Errors SetPeriod( int weeks = 1 ) = 0;

        /*!
            \brief ���������� ������ ���������� ������ � �������

            \param weeks [out] ������ ���������� ������ � �������
            \return ��� ������

        */
        virtual Errors GetPeriod( int& weeks ) const = 0;
    };

}

/*
	\brief ����� ��� �������� ������� MillisecondsSchedule
*/
KLCSC_DECL KLSCH::EveryWeekSchedule *KLSCH_CreateEveryWeekSchedule();

#endif // KLSCH_EVERYWEEKSCHEDULE_H
