// ThreadImp.h: interface for the CThreadImp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADIMP_H__BA5BF2C3_A42B_4B0A_94D9_304DFDA42C69__INCLUDED_)
#define AFX_THREADIMP_H__BA5BF2C3_A42B_4B0A_94D9_304DFDA42C69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Prague/prague.h>
#include <Prague/pr_serializable.h>

#include <windows.h>

class CThreadImp
{
public:
	CThreadImp();
	virtual ~CThreadImp();

	virtual tERROR Start(LPCSTR szThreadName = NULL);
	virtual tERROR Stop();
	virtual tERROR _Run() = 0;

protected:
	static DWORD WINAPI RunThreadFunc(LPVOID param);

protected:
    HANDLE          m_hStopEvent;	// ���� hStopEvent - ����� ��� ����� ������ ��������� ��� ������
    HANDLE			m_hThread;
};

#endif // !defined(AFX_THREADIMP_H__BA5BF2C3_A42B_4B0A_94D9_304DFDA42C69__INCLUDED_)
