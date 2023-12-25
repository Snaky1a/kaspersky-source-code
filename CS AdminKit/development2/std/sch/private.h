 /*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file Private.h
 * \author ����� �����������
 * \date 2002
 * \brief �������� ���������� ������� ��� ������ Scheduler.
 *
 */


#ifndef KLSCH_PRIVATE_H
#define KLSCH_PRIVATE_H

#include "std/base/klbase.h"
#include "std/thr/sync.h"


namespace KLSCH {

	/*!
    * \brief ����� LightMutex.
    *
    */ 

    class LightMutex
	{
	public:
		//!\ ����� �������������� ������������ mutex
		class AutoUnlock 
		{
		public:
			AutoUnlock( LightMutex *mtx );
			~AutoUnlock();

		private:
			LightMutex *mtx;
		};

	public:
		LightMutex();
		~LightMutex();

		//!\brief �������� ���������� mutex
		void Lock();

		//!\brief �������� ������������� mutex
		void Unlock();

	private:

		KLSTD::CAutoPtr<KLSTD::CriticalSection> criticalSection;
	};

	/*!
    * \brief ����� Semaphore.
    *
    */ 

    class Semaphore
	{
	public:
		Semaphore( int initCount = 1 );
		~Semaphore();

		/*!
            \brief ��������� �������� ��������.

            \param msec [in] ����� �������� � ������������. ��� ������������ �������� c_Infinite.
            \return true  - �������� �������� ���� ������� ���������
					false - ������� ����� ��������

        */
		bool Wait( int msec );

		/*!
            \brief ����������� �������� ��������.
		*/
		void Post();

	private:
		KLSTD::CAutoPtr<KLSTD::Semaphore> semHandle;
	};

	void Trace( int traceLevel, const char* format , ...);    

} // namespace KLSCH

#endif // KLSCH_PRIVATE_H

// Local Variables:
// mode: C++
// End:
