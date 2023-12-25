#ifndef _THREAD_POOL__INCLUDE_
#define _THREAD_POOL__INCLUDE_

#include "defs.h"
#include <queue>
#include <vector>
#include <windows.h>
#include "inl/synchro.h"

namespace KLUTIL
{

//! �����, � ������� ����������� ������ ������ ������.
class KLUTIL_API IThreadJob
{
protected:
	virtual ~IThreadJob() {}
public:
	//! ����������� ������ ������.
	//! ����� ��������� ������ Process() ���������� Free().
	virtual void Free() { delete this; }
	//! � ���� ������� ����������� ������ ������ ������.
	virtual void Process(
		HANDLE evStop	//!< [in] �������, ��� ������������ �������� ����� ������ �������� �����. ���� �������� ����� ���� NULL.
		) throw() = 0;
};

template <class T, typename Param = void*>
class CMemberFuncThreadJobT: public IThreadJob
{
	T* m_pObj;
	Param m_param;
	typedef void (T::*ThreadFunc)(Param param, HANDLE evStop) throw();
	ThreadFunc m_pfnFunc;
public:
	CMemberFuncThreadJobT(T* pObj, ThreadFunc pfnFunc)
		: m_pObj(pObj), m_pfnFunc(pfnFunc) {}
	CMemberFuncThreadJobT(T* pObj, ThreadFunc pfnFunc, Param param)
		: m_pObj(pObj), m_pfnFunc(pfnFunc), m_param(param) {}
	void Process(HANDLE evStop) throw()
	{
		(m_pObj->*m_pfnFunc)(m_param, evStop);
	}
};

#pragma warning (push)
#pragma warning (disable : 4251) // 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'

//! ��� �������.
class KLUTIL_API CThreadPool
{
public:
	//! �����������
	CThreadPool(
		unsigned nThreadCount = MAXIMUM_WAIT_OBJECTS	//!< [in] ������������ ����������� �������, ����������� �����. �� ������ ��������� ����� MAXIMUM_WAIT_OBJECTS.
		) throw();
	~CThreadPool() throw();
	//! ������������� ��� ������.
	void StopAllThreads() throw();
	//! ������������� ���������� �������.
	//!  \attention ���������� ������� ����� ������ ���������.
	void SetThreadCount(
		unsigned nThreadCount	//!< [in] ������������ ����������� �������, ����������� �����. �� ������ ��������� ����� MAXIMUM_WAIT_OBJECTS.
		) throw();
	//! ��������� ������� �� ���������.
	void Process(
		IThreadJob* pJob	//!< [in] ������� �� ���������. ����� ��������� ������ Process() ���������� Free().
		) throw();
	typedef void (*ThreadFunc)(void* pParam, HANDLE evStop);
	void Process(ThreadFunc pfnThreadFunc, void* pParam) throw();

private:
	static unsigned __stdcall WorkThread(void*);
	std::vector<HANDLE> m_hThreads;
	HANDLE m_evStop;
	typedef std::queue<IThreadJob*> CJobQueue;
	CJobQueue m_JobQueue;
	CCritSec m_cs;
	HANDLE m_hJobCount;
#if defined(_MSC_VER) && _MSC_VER>1300 // �������� �� �������� volatile
	LONG volatile m_nBusyThreadCount;
#else
	LONG          m_nBusyThreadCount;
#endif
	unsigned m_nMaxThreadCount;
};

#pragma warning (pop)


} // namespace KLUTIL

#endif