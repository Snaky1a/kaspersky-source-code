#ifndef __KLUTIL_THREAD_H__INCLUDE__
#define __KLUTIL_THREAD_H__INCLUDE__

#pragma once

#include "defs.h"
#include "inl/smart_ptr.hpp"

#pragma warning (push)
#pragma warning (disable : 4251) // 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'

namespace KLUTIL
{
	//! ������������� ��� ������ � ���� Threads ��������� MSVC6 � �����.
	KLUTIL_API void SetDebuggerThreadName(
		DWORD dwThreadID,	//!< [in] ������������� ������ ��� -1 ��� �������� ������.
		LPCSTR szThreadName	//!< [in] ��� ������.
		);
	
	class KLUTIL_API CThread
	{
	public:
		typedef boost::shared_ptr<CThread> CThreadPtr;

		bool CreateThread(
			DWORD dwCreateFlags = 0,
			UINT nStackSize = 0,
			LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

		virtual ~CThread();

		//! ���������� shared ��������� �� ���� ������ (������ ���, ���� �� ��� ����������� SetThisSharedPtr)
		CThreadPtr GetThisSharedPtr();
		
		//! ������������� shared ��������� �� ���� ������, ���� �� ���������� �� ����� new.
		void SetThisSharedPtr(CThreadPtr p);

		unsigned m_nThreadId;
		HANDLE m_hThread;

	protected:
		CThread();
		virtual unsigned Run() = 0;

	private:
		static unsigned __stdcall RunFunc(void* pThis);

		CThreadPtr m_pThis;
	};

	typedef CThread::CThreadPtr CThreadPtr;

	class KLUTIL_API CGuiThread
	{
	public:
		virtual unsigned Run();
		virtual BOOL InitInstance();
		virtual unsigned ExitInstance();
	};
}

#pragma warning (pop)

#endif