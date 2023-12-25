/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	kllicinfo.h
 * \author	Andrew Kazachkov
 * \date	04.06.2003 11:13:00
 * \brief	
 * 
 */

#ifndef __KL_LICINFO_H__
#define __KL_LICINFO_H__

namespace KLLIC
{
    //Errors
	enum{
		KLLIC_KEY_CHECK_FAILED=KLLICERRSTART,
        KLLIC_KEY_INSTALL_FAILED,
        KLLIC_BAD_VERSION,
        KLLIC_CANT_LOAD_MODULE,        
        KLLIC_PRODUCT_NOT_FOUND,
        KLLIC_CANT_GET_PRODUCT_FOLDER,
        KLLIC_PRODUCT_INFO_ABSENT,
        KLLIC_KEY_SIGN_MISTMACH,
        KLLIC_APP_INFO_SIGN_MISMATCH,
        KLLIC_APPINFO_CANT_RESTORE,
        KLLIC_KAVSETXML_DATE_CANT_GET,
        KLLIC_KAVSETXML_SIGN_MISMATCH,
        KLLIC_KEYINFO_CANT_RESTORE,
        KLLIC_BLACKLIST_NOT_FOUND,
        KLLIC_KEY_SERIAL_NOT_FOUND
	};

	const KLERR::ErrorDescription c_errorDescriptions[]={
		{KLLIC_KEY_CHECK_FAILED,		L"Checking key validity failed"},
        {KLLIC_KEY_INSTALL_FAILED,		L"Key installation failed"},
        {KLLIC_BAD_VERSION,             L"Module '%ls' has bad version"},
        {KLLIC_CANT_LOAD_MODULE,        L"Cannot load module '%ls' ('%ls')"},
        {KLLIC_PRODUCT_NOT_FOUND,       L"Cannot install key because product '%u' is not installed"},        
        {KLLIC_CANT_GET_PRODUCT_FOLDER, L"Cannot obtain folder for product '%ls'"},
        {KLLIC_PRODUCT_INFO_ABSENT,     L"Cannot install key because product info file is absent"},
        {KLLIC_KEY_SIGN_MISTMACH,       L"Key signature mistmach"},
        {KLLIC_APP_INFO_SIGN_MISMATCH,  L"Appinfo signature mistmach"},
        {KLLIC_APPINFO_CANT_RESTORE,    L"Cannot obtain application info"},
        {KLLIC_KAVSETXML_DATE_CANT_GET, L"Cannot obtain kavset date"},
        {KLLIC_KAVSETXML_SIGN_MISMATCH, L"Kavset signature mistmach"},
        {KLLIC_KEYINFO_CANT_RESTORE,    L"Cannot obtain key info"},
        {KLLIC_BLACKLIST_NOT_FOUND,     L"Cannot found black list"},
        {KLLIC_KEY_SERIAL_NOT_FOUND,    L"Cannot obtain key serial number"}

	};

    const wchar_t c_szwTaskInstallKey[]=L"InstallKey";

    const wchar_t c_szwKeyContents[]=L"KLLIC_KEY_CONTENTS"; //BINARY_T
    const wchar_t c_szwKeyFileName[]=L"KLLIC_KEY_FNAME";
    const wchar_t c_szwIsCurrentKey[]=L"KLLIC_IS_CURRENT_KEY";

	// ��� ������� ������������ � SettingsStorage.h, �� ��� ������ 0.12b ��� ����������� �����:
	//! ���������� � ������������ ������ � Product Info Settings Storage
	#define KLPRSS_SECTION_LIC_INFO			L"LicensingInfo"
	//! ���������� �� �������� ������������ �����
	#define KLPRSS_VAL_LIC_KEY_CURRENT		L"CurrentKey"
	//! ���������� � ��������� ������������ �����
	#define KLPRSS_VAL_LIC_KEY_NEXT			L"NextKey"


    #define KLLIC_KEY_TYPE                      L"KLLIC_KEY_TYPE"
    #define KLLIC_PROD_SUITE_ID                 L"KLLIC_PROD_SUITE_ID"
    #define KLLIC_APP_ID                        L"KLLIC_APP_ID"
    #define KLLIC_INSTALL_DATE                  L"KLLIC_INSTALL_DATE"
    #define KLLIC_CREATION_DATE                 L"KLLIC_CREATION_DATE"
    #define KLLIC_LIMIT_DATE                    L"KLLIC_LIMIT_DATE"
	#define KLLIC_EXPIRATION_DATE               L"KLLIC_EXPIRATION_DATE"
    #define KLLIC_LICENSE_PERIOD                L"KLLIC_LICENSE_PERIOD"
    #define KLLIC_LIC_COUNT                     L"KLLIC_LIC_COUNT"
    #define KLLIC_EFFECTIVE_LICENSE_PERIOD      L"KLLIC_EFFECTIVE_LICENSE_PERIOD"
    #define KLLIC_EFFECTIVE_LIC_COUNT           L"KLLIC_EFFECTIVE_LIC_COUNT"
    #define KLLIC_SERIAL                        L"KLLIC_SERIAL"
    #define KLLIC_MAJ_VER                       L"KLLIC_MAJ_VER"
    #define KLLIC_PROD_NAME                     L"KLLIC_PROD_NAME"


	//! ��� ����� (Commercial, Beta, Trial, Test, OEM)
    const wchar_t c_szwKeyType[] = KLLIC_KEY_TYPE;	// INT_T
    
	//! ������������� ��������, ����������� � ������������ �����
    const wchar_t c_szwKeyProdSuiteID[]=KLLIC_PROD_SUITE_ID;	// INT_T

	//! ������������� ����������, ����������� � ������������ �����
    const wchar_t c_szwKeyAppID[]=KLLIC_APP_ID;	// INT_T

	//! ���� � ����� ����������� �����
    const wchar_t c_szwKeyInstallDate[]=KLLIC_INSTALL_DATE; // DATE_TIME_T

	//! ���� � ����� �������� �����
    const wchar_t c_szwKeyCreationDate[]=KLLIC_CREATION_DATE; // DATE_TIME_T

	//! ���� � ����� ����������� �����
    const wchar_t c_szwKeyLimitDate[]=KLLIC_LIMIT_DATE; // DATE_TIME_T

	//! ���� ��������� �������� �������� �� ������ ����������
	const wchar_t c_szwKeyExpirationDate[]=KLLIC_EXPIRATION_DATE;	// DATE_TIME_T

	//! ���� �������� ��������
    const wchar_t c_szwKeyLicPeriod[]=KLLIC_LICENSE_PERIOD;    	// INT_T

	//! ����������� �� ���������� ��������
    const wchar_t c_szwKeyLicCount[]=KLLIC_LIC_COUNT;	// INT_T

	//! ���� �������� ��������
    const wchar_t c_szwKeyLicEffectivePeriod[]=KLLIC_EFFECTIVE_LICENSE_PERIOD;    	// INT_T

	//! ����������� �� ���������� ��������
    const wchar_t c_szwKeyLicEffectiveCount[]=KLLIC_EFFECTIVE_LIC_COUNT;	// INT_T

	//! �������� ����� �����
    const wchar_t c_szwKeySerial[]=KLLIC_SERIAL;	// STRING_T

	//! ������� ������ ��������, ����������� � ������������ �����
    const wchar_t c_szwKeyMajVer[]=KLLIC_MAJ_VER;	// INT_T

	//! ��� ����������, ����������� � ������������ �����
    const wchar_t c_szwKeyProdName[]=KLLIC_PROD_NAME;	// STRING_T

    //! Events
    #define KLLIC_EVENT_CODES_BASE  1024L

};

#endif //__KL_LICINFO_H__
