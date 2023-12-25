/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file SecondsScheduleImp.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ������ ���������� ������ 
 *        ��� ������� ������ �������-������������� ������ N ������
 *
 */


#ifndef KLSCH_SECONDSSCHEDULEIMP_H
#define KLSCH_SECONDSSCHEDULEIMP_H

#include "std/sch/errors.h"
#include "std/sch/schedule.h"
#include "std/sch/secondsschedule.h"

namespace KLSCH {
   
    /*!
    * \brief ���������� ������ ��� ������� �� �������-������������� ������
    *        N �����������
    *
    */ 

    class SecondsScheduleImp : public SecondsSchedule
	{

    public:
	
		/*!
            \brief ����������.
		*/
		SecondsScheduleImp();

		/*!
			\brief ���������� ��� ����������
		*/
		virtual ScheduleType GetType() const { return SCH_TYPE_SECONDS; }

		/*!
            \brief ���������� �����������.
		*/
		SecondsScheduleImp( const SecondsScheduleImp &schedule );

        /*!
            \brief ������������� ������ ���������� ������.

            \param sec [in] ������ ���������� ������ � sec.
            \return ��� ������

        */
        Errors SetPeriod( int sec = 0 );

        /*!
            \brief ���������� ������ ���������� ������.

            \param sec [out] ������ ���������� ������ � sec.
            \return ��� ������

        */

        Errors GetPeriod( int& sec ) const;

		/*!
            \brief ������ ����� �������.

            \param newCopy [out] ��������� �� ������������� ������.
            \return ��� ������

        */
		virtual Errors Clone( Schedule **newCopy );

	private:
		/** ���������� ���������� */

		int		period;			//!< ������ ������� ( � �e������ )		
		time_t	firstStart;		//!< ����� ������� �������
		int     periodCounter;	//!< ������� ������� �������

	protected:
		/** class helper functions */

		/*!
            \brief ������ ������� ������� ��������� �������. 
		*/
		virtual Errors CalculateNextExecutionTime( time_t &nextTime, int &msec, time_t currTime,
			time_t lastExeSec, int lastExeMsec, int startDelta = 0 );

		void GetExecutionTimes( time_t currTime, time_t &executionTimeBeforeCurrentSec,			
			time_t &executionTimeAfterCurrentSec, time_t lastExeSec, int lastExeMsec );
    };

}

#endif // KLSCH_SECONDSSCHEDULEIMP_H
