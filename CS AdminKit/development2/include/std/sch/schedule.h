/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file Schedule.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ������������ �������� ������ ���������� ������ 
 *        ��� ������� �������-�������������.
 *
 */
/*KLCSAK_PUBLIC_HEADER*/


#ifndef KLSCH_SCHEDULE_H
#define KLSCH_SCHEDULE_H

#include <ctime>
#include "std/base/klbase.h"

#include "std/sch/errors.h"

namespace KLSCH {

    //! ������������ ��������� ����� ���������� �����
    enum ScheduleType {
        SCH_TYPE_NONE,			///< ��� ���������� �� ���������.
        SCH_TYPE_MILLISECONS,	///< ���������� � ��������, ���������� ������ msec.
        SCH_TYPE_EVERYDAY,		///< ������ ����������� ������ ����.
        SCH_TYPE_EVERYWEEK,		///< ������ ����������� ������ ������.
        SCH_TYPE_EVERYMONTH,	///< ������ ����������� ������ �����.
		SCH_TYPE_SECONDS,		///< ���������� � ��������, ���������� ������ ������.
		SCH_TYPE_WEEKSDAYS		///< ���������� � �������� � ������������ ��� ������
    };  


   
    /*!
    * \brief ���������� ������ ��� ������� �������-�������������.
    *
    */ 


	class Schedule
	{

		friend class TaskImp;

    public:

		
		Schedule();
		virtual ~Schedule();


        virtual ScheduleType GetType() const { return SCH_TYPE_NONE; }


        /*!
            \brief ������������� ���� ������� ����������� �����.

            \param runMissed [in] ���� true, �� ����������� ������ ����� ���������.
            \return ��� ������

        */
        virtual Errors SetRunMissedFlag( bool runMissed = false );

        /*!
            \brief ���������� ���� ������� ����������� �����.

            \param runMissed [out] ���� true, �� ����������� ������ ����� ���������.
            \return ��� ������

        */
        virtual Errors GetRunMissedFlag( bool& runMissed ) const;

        /*!
            \brief ������������� ������ ������������ ����������. ������ �
                   ������������ �������� ������������ �� ����� ���������.

            \param lifetime [in] ������ ������� � ������� time_t, �� ��������
                                 ������ �������� ����������.
            \return ��� ������

        */
        virtual Errors SetLifetime( time_t lifetime );


        /*!
            \brief ���������� ������ ������������ ����������. ������ �
                   ������������ �������� ������������ �� ����� ���������.

            \param lifetime [out] ������ ������� � ������� time_t, �� ��������
                                 ������ �������� ����������.
            \return ��� ������

        */
        virtual Errors GetLifetime( time_t& lifetime ) const;


        /*!
            \brief ������������� ����� ��� ���������� ������ ������ ���.

            \param sec [in] ����� ���������� ������ � ������� time_t.
            \param msec [in] ����� ���������� ������ � msec. ��������
                             ���������� sec � msec ������������.
            \return ��� ������

        */
        virtual Errors SetFirstExecutionTime( time_t sec = 0, int msec = 0 );

        /*!
            \brief ���������� ����� ��� ���������� ������ ������ ���.

            \param sec [out] ����� ���������� ������ � ������� time_t.
            \param msec [out] ����� ���������� ������ � msec. ��������
                             ���������� sec � msec ������������.
            \return ��� ������

        */
        virtual Errors GetFirstExecutionTime( time_t& sec, int& msec) const;

		/*!
            \brief ������ ����� �������.

            \param newCopy [out] ��������� �� ������������� ������.
            \return ��� ������

        */
		virtual Errors Clone( Schedule **newCopy ) = 0;
		
		/*!
            \brief ������������� ������ ���������� ������.

            \param period [in] ������ ���������� ������ � �������������� ���������� ��������
            \return ��� ������

        */
        virtual Errors SetPeriod( int period = 0 ) = 0;

        /*!
            \brief ���������� ������ ���������� ������.

            param period [in] ������ ���������� ������ � �������������� ���������� ��������
            \return ��� ������
        */
        virtual Errors GetPeriod( int& period ) const = 0;		

		/*!
			\brief �������� �����������	
		*/
		void CopyFrom( const Schedule *from );

	protected: // protected ��� ������� � ��������� �� ����������� �������
		/** ���������� ���������� */

		bool  runMissed;		//!< ���� ������� ����������� �����
		time_t lifeTime;		//!< ����� ������������ ������
		
		time_t firstExeTime;	//!< ������ ����� ���������� ������
		time_t firstExemsec;

	protected:
		/** class helper functions */

		/*!
            \brief ������ ������� ������� ��������� �������. 
		*/
		virtual Errors CalculateNextExecutionTime( time_t &nextTime, int &msec, time_t currTime,
			time_t lastExeSec, int lastExeMsec, int startDelta = 0 ) = 0;

    };

}

/*
	\brief ����� ��� �������� ������� EmptySchedule
*/
KLCSC_DECL KLSCH::Schedule *KLSCH_CreateEmptySchedule();

#endif // KLSCH_SCHEDULE_H
