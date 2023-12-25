/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file weeksdaysscheduleimp.h
 * \author ����� �����������
 * \date 2007
 * \brief ���� � ������������ ������ ���������� ������ 
 *        ��� ������� �������-������������� � ������������ ��� ������.
 *
 */

#ifndef KLSCH_WEEKSDAYSSCHEDULEIMP_H
#define KLSCH_WEEKSDAYSSCHEDULEIMP_H

#include "std/sch/errors.h"
#include "std/sch/weeksdaysschedule.h"

#include "std/base/klbase.h"

namespace KLSCH {


   
    /*!
    * \brief ���������� ������ ��� ������� �� �������-�������������
    *        � ������������ ��� ������.
    *
    */ 


    class WeeksDaysScheduleImp : public WeeksDaysSchedule
	{

    public:

		/*!
            \brief �����������.
		*/
		WeeksDaysScheduleImp();			

		/*!
            \brief ���������� �����������.
		*/
		WeeksDaysScheduleImp( const WeeksDaysScheduleImp &schedule );

		/*!
			\brief ���������� ��� ����������
		*/
		virtual ScheduleType GetType() const { return SCH_TYPE_WEEKSDAYS; }

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
								 int daysBitMask = 0 );



        /*!
            \brief ���������� ����� ��� ����������� ���������� ������.

            \param day [out] ���� ��� ������� ������ (0-6). ����������� - 0.
            \param hours [out] ��� ��� ������� ������ (0-23).
            \param min [out] ������ ��� ������� ������ (0-59).
            \param sec [out] ������� ��� ������� ������ (0-59).
			\param daysBitMask [out] ������ ���� ������ (���� 1-7). ����������� - ��� 1.
            \return ��� ������
				\retval <ERR_SCHEDULE> ���������� �������� ������ �� ����������������

        */
        virtual Errors GetExecutionTime( int& hours, int& min, int& sec,
			int &daysBitMask ) const;

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

		std::vector<int>	days;		//!< ��� ������ ������� ������ ( 0 - 7 )
		int					daysBitMask;
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

#endif // KLSCH_WEEKSDAYSSCHEDULEIMP_H
