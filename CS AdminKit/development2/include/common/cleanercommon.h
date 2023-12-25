/*!
 * (C) 2006 Kaspersky Lab
 * 
 * \file	cleanercommon.h
 * \author	Eugene Rogozhnikov
 * \date	06.06.2006 16:27:34
 * \brief	����� ���������, ������������ ����������� cleaner.	
 * 
 */

#ifndef __CLEANERCOMMON_H__
#define __CLEANERCOMMON_H__	  

#ifdef _WIN32

#define KLCLEANER_DLL_FILE_NAME				L"cleanapi.dll"

// ������������� ���� � ini-������ ��� ���������� cleaner
#define KLCLEANER_INI_PATH					L"Cleaner"

// ��� ������ main � ini-����� ��� cleaner
#define KLCLEANER_INI_MAIN_SECTION			L"main"

// ��� ����� � ini-����� ��� cleaner, ��� �������� ��� ��������
#define KLCLEANER_INI_PRODUCT_NAME			L"name"

// ��� ����� � ini-����� ��� cleaner, ��� �������� ��� ini-�����
#define KLCLEANER_INI_TYPE			L"type"

// ��� ����� � ini-����� ��� cleaner, ��� �������� ���� � ������� ��� ����������� ��������� ��������
#define KLCLEANER_DETECT_REGISTRY			L"detect-registry"

// ��� ����� � ini-����� ��� cleaner, ��� �������� ��� �������� ProductCode ��������, ����������� � ������� msi
#define KLCLEANER_DETECT_MSI			L"detect-msi"

namespace KLCLEANER {

	// ���� ini-������
	const wchar_t INI_TYPE_UNINSTALL[] = L"uninstall";
	const wchar_t INI_TYPE_DETECTONLY[] = L"detect-only";

	struct CIniFileInfo
	{
		std::wstring wstrProductName;
		std::wstring wstrType;
		std::wstring wstrFileName;
		std::wstring wstrDetectRegistry;
		std::wstring wstrDetectMsi;
	};

}; // namespace KLCLEAN

#endif

#endif //__CLEANERCOMMON_H__