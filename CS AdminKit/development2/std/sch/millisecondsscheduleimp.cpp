/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file MillisecondsScheduleImp.cpp
 * \author ����� �����������
 * \date 2002
 * \brief ���� � ����������� ������ ���������� MillisecondsScheduleImp ��� ������ 
 *
 */

#include "std/trc/trace.h"

#include "std/sch/common.h"
#include "std/sch/errors.h"
#include "millisecondsscheduleimp.h"

namespace KLSCH {

	const long c_day96Time = 345600000; // 96  �����  1000*60*60*96

	//!\brief ����������.
	MillisecondsScheduleImp::MillisecondsScheduleImp()
	{
		period = 0;
		periodCounter = c_Undefined;
	}

	//!\brief ���������� �����������.	
	MillisecondsScheduleImp::MillisecondsScheduleImp( const MillisecondsScheduleImp &schedule )
	{
		firstStart		= schedule.firstStart;
		period			= schedule.period;
		periodCounter	= schedule.periodCounter;
	}
	
	//!\brief ������������� ������ ���������� ������.
	Errors MillisecondsScheduleImp::SetPeriod( int msec /* = 0 */ )
	{
		period = msec;
		return ERR_NONE;
	}
	
	//!\brief ���������� ������ ���������� ������.
	Errors MillisecondsScheduleImp::GetPeriod( int& msec ) const		
	{
		msec = period;
		return ERR_NONE;
	}

	//!\brief ������ ����� �������.
	Errors MillisecondsScheduleImp::Clone( Schedule **newCopy )
	{
		*newCopy = new MillisecondsScheduleImp( *this );
		(*newCopy)->CopyFrom( this ); // ����������� �������� ������
		return ERR_NONE;
	}
	
	//!\brief ������ ������� ������� ��������� �������.		
	Errors MillisecondsScheduleImp::CalculateNextExecutionTime( time_t &nextTime, int &msec, time_t currTime,
		time_t lastExeSec, int lastExeMsec, int startDelta )
	{
		if ( period<0 ) return ERR_SCHEDULE;

		//nextTime = currTime;		
		//msec = period;
		if ( periodCounter==c_Undefined || lastExeSec==c_Undefined )
		{	
			time_t executionTimeBeforeCurrentSec; int beforeMsec; 
			time_t executionTimeAfterCurrentSec; int AfterMsec;

			GetExecutionTimes( currTime, executionTimeBeforeCurrentSec, beforeMsec,
				executionTimeAfterCurrentSec, AfterMsec, lastExeSec, lastExeMsec );

			if ( lastExeSec!=c_Undefined && lastExeSec<currTime && runMissed &&
				CompareTimes( executionTimeBeforeCurrentSec,  beforeMsec, lastExeSec, lastExeMsec ) > 0 ) // ������ ����������� ������
			{
				firstStart = executionTimeBeforeCurrentSec;	// ��������� ���� ���������� ������				
				periodCounter = beforeMsec;
			}
			else
			{
				firstStart = executionTimeAfterCurrentSec;
				periodCounter = AfterMsec;
			}
		}
		else
			periodCounter += period;

		if ( startDelta>0 && period!=0 ) {
			if ( startDelta>period ) startDelta = startDelta % period;			
		}
		
		msec		= periodCounter + startDelta; 
		nextTime	= firstStart;		
		
		if ( periodCounter>c_day96Time ) // ������� �����
		{
			// ���������� periodCounter ������ ������� �����
			firstStart += periodCounter / c_MillisecondsInSecond;
			periodCounter = periodCounter % c_MillisecondsInSecond;
		}
		
		int compareDelta = 30000;	// 30 secs
		if ( period > compareDelta ) compareDelta = period;

		if ( ( CompareTimes( currTime, 0, nextTime, ( msec + compareDelta ) ) > 0  // ��������� ����� ������ �������
			 || ( lastExeSec!=c_Undefined && lastExeSec > currTime ) ) // ����� ������ ���� �����
			 && period!=0 )
		{
			periodCounter = c_Undefined;
			if ( lastExeSec > currTime ) lastExeSec = lastExeMsec = c_Undefined;

			return CalculateNextExecutionTime( nextTime, msec, currTime,
				lastExeSec, lastExeMsec, startDelta );
		}

		if ( nextTime>=0 )
		{
			// trace info
			struct tm infoT;
			KL_LOCALTIME( nextTime, infoT );
			char timeStr[128];
			strftime( timeStr, sizeof(timeStr), "%a %b %d %H:%M:%S %Y", &infoT );

			KLTRACE3( L"SCH", L"MillisecondsScheduleImp::CalculateNextExecutionTime nextTime - %hs nextTime - %d period - %d period counter - %d\n", 
					timeStr, nextTime, period, periodCounter );
		}

		return ERR_NONE;
	}

	void MillisecondsScheduleImp::GetExecutionTimes( time_t currTime, time_t &executionTimeBeforeCurrentSec,
			int &beforeMsec, 
			time_t &executionTimeAfterCurrentSec,
			int &AfterMsec, 
			time_t lastExeSec, int lastExeMsec )
	{
		periodCounter = 0;

		// ���������� ������ ���������� ������� ������� ������������� ������ �� �������� � �����
		// ��� ������� ���������� ������������� ����� ������� ������� ������
		if ( ( firstExeTime!=c_Undefined && firstExemsec!=c_Undefined && firstExeTime!=0 ) || 
			 ( lastExeSec!=c_Undefined && lastExeSec!=0 ) )
		{
			if ( lastExeSec!=c_Undefined && lastExeSec!=0  )
			{
				executionTimeBeforeCurrentSec = lastExeSec;
				beforeMsec = lastExeMsec;

				executionTimeAfterCurrentSec = lastExeSec;
				AfterMsec = lastExeMsec;				
			}
			else
			{
				executionTimeBeforeCurrentSec = firstExeTime;
				beforeMsec = firstExemsec;

				executionTimeAfterCurrentSec = firstExeTime;
				AfterMsec = firstExemsec;				
			}

			periodCounter = period;

			if ( (firstExeTime!=c_Undefined && firstExeTime>currTime) || period==0 ) return;

			int currnetDeltaMsec = AfterMsec;
			while( CompareTimes( executionTimeAfterCurrentSec,  AfterMsec, currTime, currnetDeltaMsec ) <= 0 )
			{
				executionTimeBeforeCurrentSec = executionTimeAfterCurrentSec;
				beforeMsec = AfterMsec;

				periodCounter += period;
				AfterMsec = periodCounter;

				if ( periodCounter>c_day96Time ) // ������� �����
				{
					// ���������� periodCounter ������ ������� �����
					executionTimeAfterCurrentSec += periodCounter / c_MillisecondsInSecond;
					executionTimeBeforeCurrentSec += beforeMsec / c_MillisecondsInSecond;
					periodCounter = periodCounter % c_MillisecondsInSecond;
					AfterMsec = periodCounter;
					beforeMsec = beforeMsec % c_MillisecondsInSecond;
				}
			}

			periodCounter = 0;
		}
		else
		{
			executionTimeBeforeCurrentSec = currTime;
			beforeMsec = 0;

			executionTimeAfterCurrentSec = currTime;
			AfterMsec = period;

			periodCounter = period;

			return;
		}	
	}
	
}	// end namespace KLSCH

/*
	\brief ����� ��� �������� ������� MillisecondsSchedule
*/
KLSCH::MillisecondsSchedule *KLSCH_CreateMillisecondsSchedule()
{
	return new KLSCH::MillisecondsScheduleImp;
}
