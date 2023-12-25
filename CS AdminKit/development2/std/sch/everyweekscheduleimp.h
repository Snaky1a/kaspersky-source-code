/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file EveryWeekScheduleImp.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ������ ���������� ������ 
 *        ��� ������� �������-������������� �����������.
 *
 */


#ifndef KLSCH_EVERYWEEKSCHEDULEIMP_H
#define KLSCH_EVERYWEEKSCHEDULEIMP_H

#include "std/sch/errors.h"
#include "std/sch/schedule.h"
#include "std/sch/everyweekschedule.h"

namespace KLSCH {


   
    /*!
    * \brief ���������� ������ ��� ������� �� �������-�������������
    *        �����������.
    *
    */ 


    class EveryWeekScheduleImp : public EveryWeekSchedule
	{

    public:

		/*!
            \brief �����������.
		*/
		EveryWeekScheduleImp();			

		/*!
            \brief ���������� �����������.
		*/
		EveryWeekScheduleImp( const EveryWeekScheduleImp &schedule );

		/*!
			\brief ���������� ��� ����������
		*/
		virtual ScheduleType GetType() const { return SCH_TYPE_EVERYWEEK; }
			
        /*!
            \brief ������������� ����� ��� ������������� ���������� ������.

            \param day [in] ���� ��� ������� ������ (0-6). ����������� - 0.
            \param hours [in] ��� ��� ������� ������ (0-23).
            \param min [in] ������ ��� ������� ������ (0-59).
            \param sec [in] ������� ��� ������� ������ (0-59).
            \return ��� ������
				\retval <ERR_TIME_INTERVAL>

        */
        Errors SetExecutionTime( int day = 0,
                                 int hours = 0, 
                                 int min = 0,
                                 int sec = 0);


        /*!
            \brief ���������� ����� ��� ����������� ���������� ������.

            \param day [out] ���� ��� ������� ������ (0-6). ����������� - 0.
            \param hours [out] ��� ��� ������� ������ (0-23).
            \param min [out] ������ ��� ������� ������ (0-59).
            \param sec [out] ������� ��� ������� ������ (0-59).
            \return ��� ������
				\retval <ERR_SCHEDULE> ���������� �������� ������ �� ����������������

        */
        Errors GetExecutionTime( int& day, int& hours, int& min, int& sec) const;
		
		/*!
            \brief ������������� ������ ���������� ������ � �������
				( �� ��������� ������ ����� 1 ������ )

            \param weeks [in] ������ ���������� ������ � �������
            \return ��� ������

        */
        Errors SetPeriod( int weeks = 1 );

        /*!
            \brief ���������� ������ ���������� ������ � �������

            \param weeks [out] ������ ���������� ������ � �������
            \return ��� ������

        */
        Errors GetPeriod( int& weeks ) const;

		/*!
            \brief ������ ����� �������.

            \param newCopy [out] ��������� �� ������������� ������.
            \return ��� ������

        */
		virtual Errors Clone( Schedule **newCopy );

	private:
		/** ���������� ���������� */

		int		  day;		//!< ���� ������ ������� ������ ( 0 - 7 )
		int		hours;		//!< ��� ������� ������ ( 0 - 23 )
		int		  min;		//!< ������ ������� ������ ( 0 - 59 )
		int		  sec;		//!< ������� ������� ������ ( 0 - 59 )

		int		weeksPeriod;	//!< ������ �������

	protected:
		/** class helper functions */

		/*!
            \brief ������ ������� ������� ��������� �������. 
		*/
		virtual Errors CalculateNextExecutionTime( time_t &nextTime, int &msec, time_t currTime,
			time_t lastExeSec, int lastExeMsec, int startDelta = 0 );

    };

}

#endif // KLSCH_EVERYWEEKSCHEDULEIMP_H
