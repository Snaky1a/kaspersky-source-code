/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file EveryMonthScheduleImp.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ������ ���������� ������ 
 *        ��� ������� �������-������������� ����������.
 *
 */


#ifndef KLSCH_EVERYMONTHSCHEDULEIMP_H
#define KLSCH_EVERYMONTHSCHEDULEIMP_H

#include "std/sch/errors.h"
#include "std/sch/schedule.h"

#include "std/sch/everymonthschedule.h"

namespace KLSCH {


   
    /*!
    * \brief ���������� ������ ��� ������� �� �������-�������������
    *        ����������.
    *
    */ 


    class EveryMonthScheduleImp : public EveryMonthSchedule
	{

    public:

		/*!
            \brief �����������.
		*/
		EveryMonthScheduleImp();

		/*!
            \brief ���������� �����������.
		*/
		EveryMonthScheduleImp( const EveryMonthScheduleImp &schedule );

		/*!
			\brief ���������� ��� ����������
		*/
		virtual ScheduleType GetType() const { return SCH_TYPE_EVERYMONTH; }

        /*!
            \brief ������������� ����� ��� ������������ ���������� ������.

            \param day [in] ���� ������ ��� ������� ������ (1-31).
            \param hours [in] ��� ��� ������� ������ (0-23).
            \param min [in] ������ ��� ������� ������ (0-59).
            \param sec [in] ������� ��� ������� ������ (0-59).
            \return ��� ������

        */
        Errors SetExecutionTime( int day = 0,
                                 int hours = 0, 
                                 int min = 0,
                                 int sec = 0);


        /*!
            \brief ���������� ����� ��� ������������ ���������� ������.

            \param day [out] ���� ������ ��� ������� ������ (1-31).
            \param hours [out] ��� ��� ������� ������ (0-23).
            \param min [out] ������ ��� ������� ������ (0-59).
            \param sec [out] ������� ��� ������� ������ (0-59).
            \return ��� ������

        */
        Errors GetExecutionTime( int& day, int& hours, int& min, int& sec) const;
		
		/*!
            \brief ������������� ������ ���������� ������ � �������
				( �� ��������� ������ ����� 1 ����� )

            \param months [in] ������ ���������� ������ � �������
            \return ��� ������

        */
        Errors SetPeriod( int months = 1 );

        /*!
            \brief ���������� ������ ���������� ������ � �������

            \param months [out] ������ ���������� ������ � �������
            \return ��� ������

        */
        Errors GetPeriod( int& months ) const;

		/*!
            \brief ������ ����� �������.

            \param newCopy [out] ��������� �� ������������� ������.
            \return ��� ������

        */
		virtual Errors Clone( Schedule **newCopy );

	private:
		/** ���������� ���������� */

		int		  day;		//!< ���� ������ ������� ������ ( 1 - 31 )
		int		hours;		//!< ��� ������� ������ ( 0 - 23 )
		int		  min;		//!< ������ ������� ������ ( 0 - 59 )
		int		  sec;		//!< ������� ������� ������ ( 0 - 59 )

		int		monthsPeriod;	//!< ������ ���������� � �������

	protected:
		/** class helper functions */

		/*!
            \brief ������ ������� ������� ��������� �������. 
		*/
		virtual Errors CalculateNextExecutionTime( time_t &nextTime, int &msec, time_t currTime,
			time_t lastExeSec, int lastExeMsec, int startDelta = 0 );
		
		int GetDaysInMonth( struct tm &monthTm );
    };

}

#endif // KLSCH_EVERYMONTHSCHEDULEIMP_H
