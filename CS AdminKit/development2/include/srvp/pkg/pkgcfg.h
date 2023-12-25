/*!
 * (C) 2006 "Kaspersky Lab"
 *
 * \file srvp/pkg/pkgcfg.h
 * \author ������ ��������
 * \date 14:57 27.04.2006
 * \brief ��������� ��� ������/������ ������ �������� ��������������� �������.
 *
 */

#ifndef _KLPKG_PKGCFG_H__
#define _KLPKG_PKGCFG_H__

namespace KLPKG {

    class KLSTD_NOVTABLE PackageConfigurator : public KLSTD::KLBaseQI {
    public:
			/*!
		  \brief �������� �������� ����� ����. ����� �������� ������.
       
			\param wszFileRelativePath [in]	-	������������� ���� � �����; NULL ��� �����, ���������� � .kpd
			\param ppData [out] ���������	-	�������� ����� ����� ��������.
		*/
		virtual void ReadPkgCfgFile(
			wchar_t* wszFileRelativePath,
			KLSTD::MemoryChunk** ppChunk) = 0;

		/*!
		  \brief �������� �������� ����� ����. ����� �������� ������.
       
			\param wszFileRelativePath [in]	-	������������� ���� � �����; NULL ��� �����, ���������� � .kpd
			\param pData [in] ���������		-	�������� ����� ����� ��������.
		*/
		virtual void WritePkgCfgFile(
			wchar_t* wszFileRelativePath,
			KLSTD::MemoryChunk* pChunk) = 0;

	};

	class KLSTD_NOVTABLE PackageConfigurator2 : public PackageConfigurator {
    public:
		/*!
		  \brief �������� ���������� � ������������ ����� � ������ 
			\param wstrKeyFileName [out] - ��� ����� �����
			\param ppMemoryChunk [out] - ���� �����
		*/
		virtual void GetLicenseKey(
			std::wstring& wstrKeyFileName,
			KLSTD::MemoryChunk** ppMemoryChunk) = 0;

		/*!
		  \brief �������� ������������ ���� � �����
			\param wstrKeyFileName [in] - ��� ����� �����
			\param ppMemoryChunk [in] - ���� �����
		*/
		virtual void SetLicenseKey(
			const std::wstring& wstrKeyFileName,
			KLSTD::MemoryChunk* pMemoryChunk,
			bool bRemoveExisting) = 0;

	};
}

#endif // _KLPKG_PKGCFG_H__
