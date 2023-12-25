/*!
* (C) 2002 "Kaspersky Lab"
*
* \file ThreadsPoolManager.h
* \author ����������� �����
* \date 2002
* \brief ��������� ��������� ������� ������� ����������
*
*/

#ifndef KLTP_THREADSPOOLMANAGER_H
#define KLTP_THREADSPOOLMANAGER_H

#include "std/thr/sync.h"
#include "std/base/klbase.h"

namespace KLTP {

	const int c_DefualtMaxNumberOfThreads = 5;

	class WorkingThread;
 
	class ThreadsPoolManager : public KLSTD::KLBase {
	public:

		/* 
			\brief �������������� ��������� �������

			\params maxThreads [in] ������������ ���������� ������� �������
		*/
		virtual void Init( int maxThrds, KLTP::ThreadsPool *threadPool ) = 0;

		/*
			\brief ��������� ������ �� ����������

			������ ������� ��������� �����

			\param params [in] ��������� ��� ���������� ������������ ������
			\param useTaskQueue [in] ���� ������������� ���������� ������� �����. ������� 
						������������ � ������ ��������� �� ������ ������ ���������� 
						�������� ������
		*/
		virtual void AddThread( void *params, bool useTaskQueue = false ) = 0;

		/*
			\brief ������� ���� ����� �� ���� �������
		*/
		virtual void DeleteNonusedThread() = 0;

		/*
			\brief ������� ������������ �������� ������

			������ ������� ���������� ����� ������� ������� ����� ���������� ������

		*/
		virtual void FreeTask( WorkingThread *thr ) = 0;
	};

} // end namespace KLTP

/*
	\breif ������� ������� ������ ������ ThreadsPoolManager
*/
void KLTP_CreateThreadsPoolManager( KLTP::ThreadsPoolManager **threadManager, int maxThrds,
									 KLTP::ThreadsPool *threadPool );

#endif // KLTP_THREADSPOOLMANAGER_H
