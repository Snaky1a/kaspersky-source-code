/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file EverydayScheduleImp.h
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ���������� ������ ���������� ������ 
 *        ��� ������� �������-������������� �����������.
 *
 */

#include "std/trc/trace.h"

#include "std/sch/common.h"
#include "std/sch/errors.h"
#include "private.h"

#include "everydayscheduleimp.h"

namespace KLSCH {

	//!\brief ����������.
	EverydayScheduleImp::EverydayScheduleImp()
	{		
		hours	= c_Undefined;
		min     = c_Undefined;
		sec     = c_Undefined;
		daysPeriod = 1;
	}

	//!\brief ���������� �����������.	
	EverydayScheduleImp::EverydayScheduleImp( const EverydayScheduleImp &schedule )
	{		
		hours	= schedule.hours;
		min		= schedule.min;
		sec		= schedule.sec;
		daysPeriod = schedule.daysPeriod;
	}
	
	//!\brief ������������� ������ ���������� ������.
	Errors EverydayScheduleImp::SetExecutionTime( int h, int m, int s )
	{
		if ( h<0 || h>23 )	return ERR_TIME_INTERVAL;
		if ( m<0 || m>59 )	return ERR_TIME_INTERVAL;
		if ( s<0 || s>59 )	return ERR_TIME_INTERVAL;
		
		hours   = h;
		min     = m;
		sec     = s;

		return ERR_NONE;
	}
	
	//!\brief ���������� ������ ���������� ������.
	Errors EverydayScheduleImp::GetExecutionTime( int& h, int& m, int& s ) const
	{
		if ( hours==c_Undefined ) return ERR_SCHEDULE;
				
		h		= hours;
		m		= min;
		s		= sec;

		return ERR_NONE;
	}

	//!\brief ������������� ������ ���������� ������ � ����
	Errors EverydayScheduleImp::SetPeriod( int days )
	{
		if ( days<=0 ) return ERR_SCHEDULE;

		daysPeriod = days;

		return ERR_NONE;
	}

    //!\brief ���������� ������ ���������� ������ � ����
	Errors EverydayScheduleImp::GetPeriod( int& days ) const
	{
		days = daysPeriod;

		return ERR_NONE;
	}

	//!\brief ������ ����� �������.
	Errors EverydayScheduleImp::Clone( Schedule **newCopy )
	{
		*newCopy = new EverydayScheduleImp( *this );
		(*newCopy)->CopyFrom( this ); // ����������� �������� ������
		return ERR_NONE;
	}
	
	//!\brief ������ ������� ������� ��������� �������.		
	Errors EverydayScheduleImp::CalculateNextExecutionTime( time_t &nextTime, int &msec, time_t currTime,
		time_t lastExeSec, int lastExeMsec, int startDelta )
	{
		const long c_day24Time = 86400000; // 24 ���� 1000*60*60*24

		if ( hours==c_Undefined ) 
		{
			return ERR_SCHEDULE;
		}

		struct tm startTm;
		
		if ( lastExeSec != c_Undefined && lastExeSec != 0 && runMissed )
		{
			// ���������� ���������� ����� �������
			KL_LOCALTIME( lastExeSec, startTm );
		} else {
			// ���������� ������� ����� ��� �������
			KL_LOCALTIME( currTime, startTm );
        }

		if ( startDelta>0 ) {
			if ( startDelta>c_day24Time ) startDelta = startDelta % c_day24Time;
		}

		bool find = false;
		time_t saveNextTime = nextTime;		
		while ( !find )
		{		
			// �������� ��������� �� ���/��� �����
			mktime( &startTm );

			startTm.tm_hour = hours;
			startTm.tm_min  = min;
			startTm.tm_sec  = sec;
			
			nextTime = mktime( &startTm );


			if ( nextTime==(-1) ) return ERR_SCHEDULE;

			msec = startDelta;			

			if ( !find )
			{

				if ( nextTime>=currTime && ( lastExeSec==c_Undefined || nextTime>lastExeSec ) ) 
				{
					if ( lastExeSec != c_Undefined && lastExeSec != 0 && runMissed &&
						lastExeSec >= firstExeTime )
					{
						if ( saveNextTime>lastExeSec && saveNextTime<=currTime ) { 
							nextTime = saveNextTime;
						}
					}
					
					find = true;
				}
				// ��������� �������� ������� ������� ������� ������
				if ( firstExeTime != c_Undefined && nextTime<firstExeTime && nextTime!=(-1) )
					find = false;

				if ( !find )
					startTm.tm_mday += daysPeriod; // �������� ��� �� ������ ������
			}

			saveNextTime = nextTime;
		}

		if ( lifeTime!=c_Undefined && nextTime > lifeTime ) 
		{
			return ERR_SCHEDULE_EXPIRED;
		}

		{
			// trace info
			struct tm infoT;
			KL_LOCALTIME( nextTime, infoT );
			char timeStr[128];
			strftime( timeStr, sizeof(timeStr), "%a %b %d %H:%M:%S %Y", &infoT );
			KLTRACE3( L"SCH", 
				L"EveryDaySchedule::CalculateNextExecutionTime nextTime - %hs msec - %d\n", timeStr, msec );
		}

		return ERR_NONE;
	}
	

}	// end namespace KLSCH

/*
	\brief ����� ��� �������� ������� MillisecondsSchedule
*/
KLSCH::EverydaySchedule *KLSCH_CreateEverydaySchedule()
{
	return new KLSCH::EverydayScheduleImp;
}
