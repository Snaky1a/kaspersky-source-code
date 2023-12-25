/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file Thread.h
 * \author ����� �����������
 * \date 2002
 * \brief ����������� ��������� ������ ��������� �������
 * 
 */


#ifndef KLSTD_THREAD_H
#define KLSTD_THREAD_H

#include "std/base/klbase.h"
#ifdef __unix__
 #ifndef _stdcall
  #define _stdcall
 #endif
#endif

namespace KLSTD {

#ifndef N_PLAT_NLM 		// Novell Netware
	#define KLSTD_THREADDECL	_stdcall
#else
	#define KLSTD_THREADDECL
#endif

	typedef unsigned long ( KLSTD_THREADDECL *ThreadFunctionPtr)(void *arpg);

	class Thread
	{
	public:
		
		/*!\enum ���������� ������� */
		enum ThreadPriority
		{
			PriorityLow,
			PriorityNormal,
			PriorityHigh
		};

		virtual ~Thread() {}
	/*!
      \brief ������� �������� � ������� ������.

      \param name [in] ��� ������.
	  \param func [in] ������� ������.
      \exception TRERR_INVALID_PARAMETER 
    */
        virtual void Start( const wchar_t *name, ThreadFunctionPtr func, 
			void *argp = NULL ) = 0;

	/*!
      \brief ������� �������� ���������� ������.

      \param timeOut [in] ����� �������� � ������������� <0 - �������� ���� ����� �� �����������  
	  \return ��������� ��������. true - ����� �������� ���� ������
    */
        virtual bool Join( int timeOut = (-1) ) = 0;

	};

} // namespace KLSTD

//!\brief ������� �������� ������� ���� Thread
KLCSC_DECL bool KLSTD_CreateThread(KLSTD::Thread** pThread);

//!\brief Function returns id of current thread
KLCSC_DECL int KLSTD_GetCurrentThreadId();

//!\brief ������������ ������� ����� � ��������
void RegisterThreadInDriver();

//!\brief �������������� ������� ����� � ��������
void UnregisterThreadInDriver();

//!\brief Function returns pid of current process

KLCSC_DECL int KLSTD_GetCurrentProcessId();

#endif // KLSTD_THREAD_H
