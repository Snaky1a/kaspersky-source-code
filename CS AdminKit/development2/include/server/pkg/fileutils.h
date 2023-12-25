/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file PCK/Packages.h
 * \author ������ ��������
 * \date 2002
 * \brief ���������� � ������� ��� ������ � ������� � ������������ (����������� � �.�.)
 *
 */

#ifndef _FILEUTILS_H__0852EE00_43FA_46E7_AC7F_82A22ECFCF7B_
#define _FILEUTILS_H__0852EE00_43FA_46E7_AC7F_82A22ECFCF7B_

#include <std/base/klbase.h>
#include <kca/prci/componentinstance.h>

namespace KLFU {
	/*! ������������ � ��������� ������ callback-������� ��� ����������� �������:
		Progress - ��������� � �������� �����������.	
		CopyingFinished - ����������� ���������.
		CopyFailed - ����������� ��������� ��������
	 */
	enum ECopyCallbackReason { Progress, Counting, CopyFinished, CopyStopped, CopyFailed };


	/*!
		\brief ����������� callback-�������, ���������� ��� ����������� �������:
		
		\param dwTotalPercent - ������� �������������� ������
		\param eCopyCallbackReason - ������� ������ callback'� (��.�������� 
				��� ECopyCallbackReason)
		\param pcszFileName - ������ ���� � ���������������� � ������ ������� �����.
					�� NULL � ������ Counting � Progress.
		\param pcszFailReason - ������ � ��������� ������, ��-NULL ������ � ������
				eCopyCallbackReason == CopyFailed
	 */
	typedef void (*PCopyProgressRoutine)
		(
			AVP_dword dwTotalPercent,
			ECopyCallbackReason eCopyCallbackReason,
			const wchar_t* pcszFileName,
			const wchar_t* pcszFailReason,
			void* pParam
		);

	class KLSTD_NOVTABLE FolderAim : public KLSTD::KLBase {
    public:
	    /*!
			\brief ����������� ����������� ����������� �����. ���������� ������������ �� 
					������� �� ���������� �����������. ���� ����������� ���������� �
					��������� ������, ��� ���� ������������ �� ���� �� ������ ����������
					callback-������� � ����������� � ��������� ����������. �������� �����
					����������� �������� ����� callback'� � ���������� eCopyCallbackReason,
					������ ���� CopyFinished, ���� CopyStopped, ���� CopyFailed.
					� ������ CopyFailed ���������� ����� ������� ������.

					����� ����, � �������� ����������� ������������ ����������� ��������
					bool-���������� bStopFlag (���������� �� ������). ���� bStopFlag
					����������� ������ true, to ������� ����������� ������������, � ����������
					callback-������� � eCopyCallbackReason == CopyStopped.

                    ����� ����������� ���������� �� ������ ��� ����� ����������� ��������
                    �����, �� ��������� ��������� �����������.

                    ���������� ������� ������� ���������� ��������� ���� ���������� � ��� 
                    ������� ����������� ��������� ����������� (������� ����� ������� ���,
                    ����� ����������� ���������, � ����� �������� �����).

			\param wstrFromPath - �����-��������
			\param wstrToPath - �����, � ������� ����� ����������.
			\param bStopFlag - ���������� �� ������ ���������, �������� ������� ������������
					� �������� �����������.
			\param pCopyProgressRoutine - callback-������� (��.���� ��������).
					�� ����� ���� NULL, ��� ��� �� ��������� ����� � �������������� ���������
					��������� eCopyCallbackReason �������� � ����� ��������.
		*/
		virtual void CopyFolderAsynch(
				const std::wstring& wstrFromPath,
				const std::wstring& wstrToPath,
				int& bStopFlag,
				PCopyProgressRoutine pCopyProgressRoutine,
				void* pParam ) = 0;


		/*!
			\brief �� �� �����, ��� � ����. �������, �� ����������� ����, ��� ��������� �
					��������� � ����� �������� ����������� ����� ����� Publish ����������,
					���������� ����� �������� pComponentInstance.
			
			\param wstrFromPath - �����-��������
			\param wstrToPath - �����, � ������� ����� ����������.
			\param bStopFlag - ���������� �� ������ ���������, �������� ������� ������������
					� �������� �����������.
			\param pComponentInstance - ���������, � �������� ���������� ����� Publish ���
					��������� � ��������� � ����� ��������. �� ����� ���� NULL, �� ��� ��
					��������, ��� � callback ��� ����.�������.
	    */
		virtual void CopyFolderAsynch(
				const std::wstring& wstrFromPath,
				const std::wstring& wstrToPath,
				int& bStopFlag,
				KLPRCI::ComponentInstance* pComponentInstance,
				void* pParam ) = 0;
        
		/*!
			\brief �� �� �����, ��� � CopyFolderAsynch, �� �������� ��������� 
                �  ���������� ���������� � ������ ������.
        */
		virtual void CopyFolder(
				const std::wstring& wstrFromPath,
				const std::wstring& wstrToPath,
				int& bStopFlag,
				PCopyProgressRoutine pCopyProgressRoutine,
				void* pParam ) = 0;

		/*!
			\brief �� �� �����, ��� � CopyFolderAsynch, �� �������� ��������� 
                �  ���������� ���������� � ������ ������.
        */
		virtual void CopyFolder(
				const std::wstring& wstrFromPath,
				const std::wstring& wstrToPath,
				int& bStopFlag,
				KLPRCI::ComponentInstance* pComponentInstance,
				void* pParam ) = 0;
        
		/*!
			\brief ���������� ������ �����. � ������ ������ ����������� ����������. */
        virtual AVP_longlong GetFolderSize( const std::wstring& wstrFolderPath ) = 0;

        virtual void DeleteFolderWithContent( const std::wstring& wstrFolder ) = 0;
		
        virtual void ClearReadOnlyAttributeForFilesInFolder( const std::wstring& wstrFolder ) = 0;
	};
}

KLCSSRV_DECL void KLFU_CreateFolderAim( KLFU::FolderAim** ppCopyFolder );

#endif _FILEUTILS_H__0852EE00_43FA_46E7_AC7F_82A22ECFCF7B_
