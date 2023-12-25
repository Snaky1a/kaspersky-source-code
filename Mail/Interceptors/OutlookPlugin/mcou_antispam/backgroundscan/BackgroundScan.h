/*!
*		
*		
*		(C) 2002 Kaspersky Lab 
*		
*		\file	BackgroundScan.h
*		\brief	
*		
*		\author Vitaly DVi Denisov
*		\date	30.07.2004 11:02:13
*		
*		Example:	
*		
*		
*		
*/		


#ifndef _BACGROUNDSCAN_H_
#define _BACGROUNDSCAN_H_

#include <stuff\thread.h>
#include "../../mapiedk/mapiedk.h"

class CBackgroundScan: public CThread
{
public:
	CBackgroundScan(void* pAntispamOUSupport);
	virtual ~CBackgroundScan();

	///////////////////////////////////////////////////////////////////////////
	//! \fn				: Run
	//! \brief			:	�������� ������� ������. 
	//! \return			: virtual int 
	virtual int Run();

	///////////////////////////////////////////////////////////////////////////
	//! \fn				: Terminate
	//! \brief			:	��������� ������
	//! \return			: virtual void 
	virtual void Terminate();

	///////////////////////////////////////////////////////////////////////////
	//! \fn				: ScanNow
	//! \brief			:	������ ������ �� ����������������, �.�. ������ ����� �����
	//! \return			: bool 
	bool ScanNow();

	///////////////////////////////////////////////////////////////////////////
	//! \fn				: 
	//! \brief			:	������������ ���� ������������ 
	//!						����� � ������ ������ lpMAPISession
	//! \return			: HRESULT Scan 
	//! \param          : CMCThread* pMCThread
	//! \param          : LPMAPISESSION lpMAPISession
	//! \param          : HRESULT* phrActionResult = 0
	HRESULT Scan(LPMAPISESSION lpMAPISession, HRESULT* phrActionResult = 0);

	///////////////////////////////////////////////////////////////////////////
	//! \fn				: Scan
	//! \brief			:	������������ ���� ������������ � ��������� lpMDB
	//! \return			: HRESULT 
	//! \param          : LPMDB lpMDB
	//! \param          : HRESULT* phrActionResult = 0
	HRESULT Scan(LPMAPISESSION lpMAPISession, LPMDB lpMDB, HRESULT* phrActionResult = 0);

	///////////////////////////////////////////////////////////////////////////
	//! \fn				: Scan
	//! \brief			:	������������ ���� ������������ 
	//!						����� � ��������� ����� lpFolder ��������� lpMDB
	//! \return			: HRESULT 
	//! \param          : CMCThread* pMCThread
	//! \param          : LPMDB lpMDB
	//! \param          : LPMAPIFOLDER lpFolder
	//! \param          : bool bUnreadOnly
	//! \param          : bool bUncheckedOnly
	//! \param          : HRESULT* phrActionResult = 0
	HRESULT Scan(
		LPMAPISESSION lpMAPISession, 
		LPMDB lpMDB, 
		LPMAPIFOLDER lpFolder, 
		bool bUnreadOnly = true, 
		bool bUncheckedOnly = true, 
		HRESULT* phrActionResult = 0
		);

private:
	HANDLE m_hEventScanNow;
	HANDLE m_hEventStop;
	HANDLE m_hEvents[2];
	void* m_pAntispamOUSupport;
};



#endif//_BACGROUNDSCAN_H_