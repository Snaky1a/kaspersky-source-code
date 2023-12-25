/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file SecondsSchedule.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ������ ���������� ������ 
 *        ��� ������� ������ �������-������������� ������ N ������
 *
 */


#ifndef KLSCH_SECONDSSCHEDULE_H
#define KLSCH_SECONDSSCHEDULE_H

#include "std/sch/errors.h"
#include "schedule.h"

#include "std/base/klbase.h"

namespace KLSCH {


   
    /*!
    * \brief ���������� ������ ��� ������� �� �������-������������� ������
    *        N �����������
    *
    */ 


    class SecondsSchedule : public Schedule
	{

    public:
		
		/*!
			\brief ����������� ����������.
		*/
		virtual ~SecondsSchedule() {}

		/*!
			\brief ���������� ��� ����������
		*/
		virtual ScheduleType GetType() const = 0;

        /*!
            \brief ������������� ������ ���������� ������.

            \param sec [in] ������ ���������� ������ � sec.
            \return ��� ������

        */
        virtual Errors SetPeriod( int sec = 0 ) = 0;

        /*!
            \brief ���������� ������ ���������� ������.

            \param sec [out] ������ ���������� ������ � sec.
            \return ��� ������

        */

        virtual Errors GetPeriod( int& sec ) const = 0;		
    };

}

/*
	\brief ����� ��� �������� ������� SecondsSchedule
*/
KLCSC_DECL KLSCH::SecondsSchedule *KLSCH_CreateSecondsSchedule();

#endif // KLSCH_SECONDSSCHEDULE_H
