/*!
 * (C) 2007 Kaspersky Lab
 * 
 * \file	Inventory.h
 * \author	Eugene Rogozhnikov
 * \date	02.07.2007 15:14:31
 * \brief	
 * 
 */

#ifndef __INVENTORY_H__
#define __INVENTORY_H__
					   
#include <string>

namespace KLINV {

	/*
	 *	
		���������, �������� �������� ��� Add/Remove Programms
		������ ��������� ������������� � ������� ��� ������:
		HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\
	 */ 
	struct CARPInfo
	{
		CARPInfo();

		std::wstring wstrRegKey; // ����, ��� ������������� �������� ��������
		std::wstring wstrDisplayName;
		std::wstring wstrDisplayVersion;
		std::wstring wstrPublisher;
		unsigned short uLangId;
		std::wstring wstrInstallDate;
		std::wstring wstrInstallDir;
		std::wstring wstrParentDisplayName;
		std::wstring wstrComments;
		std::wstring wstrHelpLink;
		std::wstring wstrHelpTelephone;
	};

	inline CARPInfo::CARPInfo() : uLangId(0)
	{
	}

	/*
	 *	
		���������, ����������� �������� ��������, �������������� ���������� MSI.
		������ ������� ������������� � MsiEnumProducts
	 */
	struct CMSIInfo
	{
		CMSIInfo();

		std::wstring wstrCode;
		std::wstring wstrPackageCode;
		std::wstring wstrName;
		std::wstring wstrVersionString;
		std::wstring wstrPublisher;
		unsigned short uLangId;
		std::wstring wstrInstallDate;
		std::wstring wstrInstallDir;
		std::wstring wstrHelpLink;
		std::wstring wstrHelpTelephone;
	};

	inline CMSIInfo::CMSIInfo() : uLangId(0)
	{
	}

	struct CMSIPatchInfo
	{
		std::wstring wstrCode;
		std::wstring wstrProductCode;
		std::wstring wstrName;
		std::wstring wstrPublisher;
		std::wstring wstrClassification;
		std::wstring wstrMoreInfoURL;

	};

	struct CInvProductInfo
	{
		CInvProductInfo();

		// ���������� ������������� �������� � ����� ������� Inventory
		// ��� msi-�������� ��������� � wstrCode, � ��� ARP - ��� �� wstrDisplayName
		std::wstring wstrProductID;

		bool bIsMsi;
		std::wstring wstrPackageCode;
		std::wstring wstrDisplayName;
		std::wstring wstrDisplayVersion;
		std::wstring wstrPublisher;
		unsigned short uLangId;
		std::wstring wstrInstallDate;
		std::wstring wstrInstallDir;
		std::wstring wstrComments;
		std::wstring wstrHelpLink;
		std::wstring wstrHelpTelephone;
		std::wstring wstrARPRegKey;
		std::wstring wstrCleanerProductName;
	};

	inline CInvProductInfo::CInvProductInfo() : bIsMsi(false), uLangId(0)
	{
	}

	struct CInvPatchInfo
	{
		// ���������� ������������� ����� � ����� ������� Inventory
		// ��� msi-�������� ��������� � PatchCode, � ��� ARP - ��� �� wstrDisplayName
		std::wstring wstrPatchID;

		bool bIsMsi;
		std::wstring wstrParentID; // �� ������ ���� ������.
		std::wstring wstrDisplayName;
		std::wstring wstrDisplayVersion;
		std::wstring wstrPublisher;
		std::wstring wstrInstallDate;
		std::wstring wstrComments;
		std::wstring wstrHelpLink;
		std::wstring wstrHelpTelephone;
		std::wstring wstrClassification;
		std::wstring wstrMoreInfoURL;
	};

}; // namespace KLINV

#endif //__INVENTORY_H__