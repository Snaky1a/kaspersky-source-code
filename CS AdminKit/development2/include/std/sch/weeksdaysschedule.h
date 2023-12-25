/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file weeksdaysschedule.h
 * \author ����� �����������
 * \date 2007
 * \brief ���� � ������������ ������ ���������� ������ 
 *        ��� ������� �������-������������� � ������������ ��� ������.
 *
 */
/*KLCSAK_PUBLIC_HEADER*/

#ifndef KLSCH_WEEKSDAYSSCHEDULE_H
#define KLSCH_WEEKSDAYSSCHEDULE_H

#include "std/sch/errors.h"
#include "schedule.h"

#include "std/base/klbase.h"

namespace KLSCH {


   
    /*!
    * \brief ���������� ������ ��� ������� �� �������-�������������
    *        � ������������ ��� ������.
    *
    */ 


    class WeeksDaysSchedule : public Schedule
	{

    public:

		/*!
			\brief ����������� ����������.
		*/
		virtual ~WeeksDaysSchedule() {}

		/*!
			\brief ���������� ��� ����������
		*/
		virtual ScheduleType GetType() const = 0;

		/*!
            \brief ������������� �����.

            \param hours [in] ��� ��� ������� ������ (0-23).
            \param min [in] ������ ��� ������� ������ (0-59).
            \param sec [in] ������� ��� ������� ������ (0-59).
			\param daysBitMask [in] ������� ����� ������ ���� ������ (���� 1-7). ����������� - ��� 1.
            \return ��� ������
				\retval <ERR_TIME_INTERVAL>

        */
        virtual Errors SetExecutionTime( 
								int hours = 0, 
                                int min = 0,
                                int sec = 0,
								int daysBitMask = 0 ) = 0;


        /*!
            \brief ���������� ����� ��� ����������� ���������� ������.

            \param hours [out] ��� ��� ������� ������ (0-23).
            \param min [out] ������ ��� ������� ������ (0-59).
            \param sec [out] ������� ��� ������� ������ (0-59).
			\param daysBitMask [out] ������ ���� ������ (���� 1-7). ����������� - ��� 1.
            \return ��� ������
				\retval <ERR_SCHEDULE> ���������� �������� ������ �� ����������������

        */
        virtual Errors GetExecutionTime( int& hours, int& min, int& sec,
			int &daysBitMask ) const = 0;
		
    };

}

/*
	\brief ����� ��� �������� ������� WeeksDaysSchedule
*/
KLCSC_DECL KLSCH::WeeksDaysSchedule *KLSCH_CreateWeeksDaysSchedule();

#endif // KLSCH_WEEKSDAYSSCHEDULE_H
