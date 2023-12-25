#ifndef __CKAHUM_H__
#define __CKAHUM_H__

#include "ckahdefs.h"
#include "ckahumdefs.h"

#pragma warning(disable : 4200) // non-standard MS extension

#define CKAHUMMETHOD_ CKAHUMEXPORT
#define CKAHUMMETHOD CKAHUMMETHOD_ CKAHUM::OpResult 

// ����� ������� ������ � CKAH
namespace CKAHUM
{
	// �������� �������-�������������
	typedef void (CALLBACK *EXTERNALLOGGERPROC) (LogLevel Level, LPCSTR szString);

	// ������������� persistent ��������� � CCKAHRegStorageImpl �� defalt ����,
	// � ����� ������� �������-������������
	CKAHUMMETHOD Initialize (EXTERNALLOGGERPROC logger = NULL);

	// ������������� persistent ��������� � CCKAHRegStorageImpl � ��������� ����� � �������),
	// � ����� ������� �������-������������
	CKAHUMMETHOD Initialize (HKEY hKey, LPCWSTR szSubKey, EXTERNALLOGGERPROC logger = NULL);

    // ��������������� ������� �������-������������
	CKAHUMMETHOD Deinitialize (EXTERNALLOGGERPROC logger = NULL);

	// ��������� persistent ��������� � ������������� ���������� �������
	CKAHUMMETHOD Reload (LPCWSTR szManifestFilePath);

    // ��������������� � ������� ������������������� �������� (��� ������ �� ��������������)
    CKAHUMMETHOD Uninstall ();
	
	// �������� ���������� �������� ���������� (��� ������ ���������� ��������)
	// ����� �������� � �� ������ ��������
	CKAHUMMETHOD Pause ();

	// ��������� ���������� �������� ���������� (��� ������ ���������� ��������)
	// ����� �������� � �� ������ ��������
	CKAHUMMETHOD Resume ();
	
	// ��������������� ������� ��������
	CKAHUMMETHOD UnregisterBaseDrivers ();

	// ��������� / ��������� ������� ��������
	CKAHUMMETHOD EnableBaseDrivers (bool bEnable);
	
	// ����������, ��������� �� ������� ��������
	CKAHUMMETHOD IsBaseDriversEnabled (bool *pbEnabled);

	// ����������, �������� �� ������� ��������
	CKAHUMMETHOD IsBaseDriversRunning (bool *pbRunning);

	// ������������� ��� ���������� �������
	CKAHUMMETHOD StopAll ();

}; //namespace CKAHUM

// C stubs
extern "C" CKAHUMMETHOD CKAHUM_Reload (LPCWSTR szManifestFilePath);
extern "C" CKAHUMMETHOD CKAHUM_Uninstall ();
extern "C" CKAHUMMETHOD CKAHUM_Initialize (HKEY hKey, LPCWSTR szSubKey, CKAHUM::EXTERNALLOGGERPROC logger = NULL);
extern "C" CKAHUMMETHOD CKAHUM_Deinitialize (CKAHUM::EXTERNALLOGGERPROC logger = NULL);

#include "ckahids.h"
#include "ckahstm.h"
#include "ckahfw.h"
#include "ckahcr.h"

#pragma warning(default : 4200)

#include "ckahrules.h"

#endif