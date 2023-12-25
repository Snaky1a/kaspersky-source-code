/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file MillisecondsScheduleImp.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ������ ���������� ������ 
 *        ��� ������� ������ �������-������������� ������ N �����������
 *
 */


#ifndef KLSCH_MILLISECONDSSCHEDULEIMP_H
#define KLSCH_MILLISECONDSSCHEDULEIMP_H

#include "std/sch/errors.h"
#include "std/sch/schedule.h"
#include "std/sch/millisecondsschedule.h"

namespace KLSCH {
   
    /*!
    * \brief ���������� ������ ��� ������� �� �������-������������� ������
    *        N �����������
    *
    */ 

    class MillisecondsScheduleImp : public MillisecondsSchedule
	{

    public:
	
		/*!
            \brief ����������.
		*/
		MillisecondsScheduleImp();

		/*!
			\brief ���������� ��� ����������
		*/
		virtual ScheduleType GetType() const { return SCH_TYPE_MILLISECONS; }

		/*!
            \brief ���������� �����������.
		*/
		MillisecondsScheduleImp( const MillisecondsScheduleImp &schedule );

        /*!
            \brief ������������� ������ ���������� ������.

            \param msec [in] ������ ���������� ������ � msec.
            \return ��� ������

        */
        Errors SetPeriod( int msec = 0 );

        /*!
            \brief ���������� ������ ���������� ������.

            \param msec [out] ������ ���������� ������ � msec.
            \return ��� ������

        */

        Errors GetPeriod( int& msec ) const;

		/*!
            \brief ������ ����� �������.

            \param newCopy [out] ��������� �� ������������� ������.
            \return ��� ������

        */
		virtual Errors Clone( Schedule **newCopy );

	private:
		/** ���������� ���������� */

		int		period;			//!< ������ ������� ( � ������������ )		
		time_t	firstStart;		//!< ����� ������� �������
		int     periodCounter;	//!< ������� ������� ������� ( ������������ ���� period<1000 )		

	protected:
		/** class helper functions */

		/*!
            \brief ������ ������� ������� ��������� �������. 
		*/
		virtual Errors CalculateNextExecutionTime( time_t &nextTime, int &msec, time_t currTime,
			time_t lastExeSec, int lastExeMsec, int startDelta = 0 );

		void GetExecutionTimes( time_t currTime, time_t &executionTimeBeforeCurrentSec,
			int &beforeMsec, 
			time_t &executionTimeAfterCurrentSec,
			int &AfterMsec,
			time_t lastExeSec, int lastExeMsec );
    };

}

#endif // KLSCH_MILLISECONDSSCHEDULEIMP_H
