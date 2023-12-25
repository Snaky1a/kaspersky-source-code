/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file MillisecondsSchedule.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ������ ���������� ������ 
 *        ��� ������� ������ �������-������������� ������ N �����������
 *
 */
/*KLCSAK_PUBLIC_HEADER*/


#ifndef KLSCH_MILLISECONDSSCHEDULE_H
#define KLSCH_MILLISECONDSSCHEDULE_H

#include "std/sch/errors.h"
#include "schedule.h"

#include "std/base/klbase.h"

namespace KLSCH {


   
    /*!
    * \brief ���������� ������ ��� ������� �� �������-������������� ������
    *        N �����������
    *
    */ 


    class MillisecondsSchedule : public Schedule
	{

    public:
		
		/*!
			\brief ����������� ����������.
		*/
		virtual ~MillisecondsSchedule() {}

		/*!
			\brief ���������� ��� ����������
		*/
		virtual ScheduleType GetType() const = 0;

        /*!
            \brief ������������� ������ ���������� ������.

            \param msec [in] ������ ���������� ������ � msec.
            \return ��� ������

        */
        virtual Errors SetPeriod( int msec = 0 ) = 0;

        /*!
            \brief ���������� ������ ���������� ������.

            \param msec [out] ������ ���������� ������ � msec.
            \return ��� ������

        */
        virtual Errors GetPeriod( int& msec ) const = 0;		
    };

}

/*
	\brief ����� ��� �������� ������� MillisecondsSchedule
*/
KLCSC_DECL KLSCH::MillisecondsSchedule *KLSCH_CreateMillisecondsSchedule();

#endif // KLSCH_MILLISECONDSSCHEDULE_H
