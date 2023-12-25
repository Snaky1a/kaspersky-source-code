/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file EverydayScheduleImp.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ ������ ���������� ������ 
 *        ��� ������� �������-������������� ���������.
 *
 */


#ifndef KLSCH_EVERYDAYSCHEDULEIMP_H
#define KLSCH_EVERYDAYSCHEDULEIMP_H

#include "std/sch/errors.h"
#include "std/sch/schedule.h"

#include "std/sch/everydayschedule.h"

namespace KLSCH {


   
    /*!
    * \brief ���������� ������ ��� ������� �� �������-�������������
    *        ���������.
    *
    */ 


    class EverydayScheduleImp : public EverydaySchedule
	{

    public:

		/*!
            \brief �����������.
		*/
		EverydayScheduleImp();

		/*!
            \brief ���������� �����������.
		*/
		EverydayScheduleImp( const EverydayScheduleImp &schedule );

		/*!
			\brief ���������� ��� ����������
		*/
		virtual ScheduleType GetType() const { return SCH_TYPE_EVERYDAY; }

        /*!
            \brief ������������� ����� ��� ����������� ���������� ������.

            \param hours [in] ��� ��� ������� ������ (0-23).
            \param min [in] ������ ��� ������� ������ (0-59).
            \param sec [in] ������� ��� ������� ������ (0-59).
            \return ��� ������

        */
        Errors SetExecutionTime( int hours = 0, 
                                 int min = 0,
                                 int sec = 0);


        /*!
            \brief ���������� ����� ��� ����������� ���������� ������.

            \param hours [out] ��� ��� ������� ������ (0-23).
            \param min [out] ������ ��� ������� ������ (0-59).
            \param sec [out] ������� ��� ������� ������ (0-59).
            \return ��� ������

        */
        Errors GetExecutionTime( int& hours, int& min, int& sec) const;
		
		/*!
            \brief ������������� ������ ���������� ������ � ����
				( �� ��������� ������ ����� 1 ���� )

            \param days [in] ������ ���������� ������ � ����
            \return ��� ������

        */
        Errors SetPeriod( int days = 1 );

        /*!
            \brief ���������� ������ ���������� ������ � ����

            \param days [out] ������ ���������� ������ � ����.
            \return ��� ������

        */
        Errors GetPeriod( int& days ) const;

		/*!
            \brief ������ ����� �������.

            \param newCopy [out] ��������� �� ������������� ������.
            \return ��� ������

        */
		virtual Errors Clone( Schedule **newCopy );

	private:
		/** ���������� ���������� */

		int		hours;		//!< ��� ������� ������ ( 0 - 23 )
		int		  min;		//!< ������ ������� ������ ( 0 - 59 )
		int		  sec;		//!< ������� ������� ������ ( 0 - 59 )

		int		daysPeriod;	//!< ������ ���������� � ����

	protected:
		/** class helper functions */

		/*!
            \brief ������ ������� ������� ��������� �������. 
		*/
		virtual Errors CalculateNextExecutionTime( time_t &nextTime, int &msec, time_t currTime,
			time_t lastExeSec, int lastExeMsec, int startDelta = 0 );

    };

}

#endif // KLSCH_EVERYDAYSCHEDULEIMP_H
