/*!
* (C) 2002 "Kaspersky Lab"
*
* \file WorkingThread.h
* \author ����������� �����
* \date 2002
* \brief ��������� �������� ������ ���������� ( ������������ ��� ������ � I/O completion port )
*
*/

#ifndef KLTP_WORKINGTHREAD_H
#define KLTP_WORKINGTHREAD_H

#include "std/thr/sync.h"
#include "std/base/klbase.h"

#include "std/tp/threadspool.h"

namespace KLTP {

	/*!
	* \brief ������� ����� ���������� 
	*/	

	class ThreadsPoolManager;

	class WorkingThread : public KLSTD::KLBase {
	public:

		enum ActionState {	//!< ��������� ������
			Free, 
			Working,
			ThreadNotStarted
		};

		/*
			\brief ������� ���������� ������ ������
		*/
		virtual void StartThread( ThreadsPoolManager *manager ) = 0;

		/*
			\brief ������� ���������� ������� ������ ( ��� �������� ��������� ������ ������ )
		*/
		virtual void StopThread() = 0;

		/*
			\brief ������� ���������� ����������� �� ������� �����
		*/
		virtual bool IsStopped() = 0;
		
		/*
			\brief ��������� ������� ����� �� ���������� ������

			\params params [in] ��������� ������
		*/
		virtual void NewTask( void *params ) = 0;

		/*
			\brief ���������� ������� ��������� ������
		*/
		virtual ActionState GetCurrentState() = 0;

		/*
			\brief ������ ����� ��� ������� ������ ( �� ��������� ����� (-1) )
		*/
		virtual void SetWorkingThreadNumber( int wNum ) = 0;

		/*
			\brief ���������� ��������� ������
		*/
		virtual void *GetParams() = 0;

		/*
			\brief ��������� �������� �� ������� �����, ������� WorkingThread
		*/
		virtual bool IsCurrentThread() = 0;

	};

} // end namespace KLTP

/*
	\breif ������� ������� ������ ������ WorkingThread
*/
void KLTP_CreateWorkingThread( KLTP::WorkingThread **workingThread, int threadNum,
								KLTP::ThreadsPool *threadPool );

#endif // KLTP_WORKINGTHREAD_H
