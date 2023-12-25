 /*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file Common.h
 * \author ����� �����������
 * \date 2002
 * \brief �������� ����� ����������� ��� ������ Scheduler.
 *
 */
/*KLCSAK_PUBLIC_HEADER*/

#ifndef KLSCH_COMMON_H
#define KLSCH_COMMON_H

#include <ctime>

namespace KLSCH {


    //! ������������� ������. 
    typedef int TaskId;

    //! ������������� ������ ������.
    typedef int TaskClassId;

	//! ��������� ��� ����������� ������������ timeout
	const int c_Infinite = (-1);

	//! �������������� ��������
	const int c_Undefined = (-1);

	//! ���������� ������������ ���������� � ������
	const int c_MillisecondsInSecond = 1000;
	
	/*!
      \brief ������� ��� �������� time_t + msec.
      \return 0 - �����, < 0 - ������, > 0 - ������
    */
	int CompareTimes( time_t t1sec, int t1msec, time_t t2sec, int t2msec );

	/*!
      \brief ������� ��� ������� ������� �������� ( � ������������ ) �� ���������� �������.
      \return 0 - �����, < 0 - ������, > 0 - ������
    */
	unsigned long CalculateWaitingTime( time_t tsec, int tmsec, time_t currTime,
		int currTimeMSec );

} // nasmesapce KLSCH

#endif // KLSCH_COMMON_H
