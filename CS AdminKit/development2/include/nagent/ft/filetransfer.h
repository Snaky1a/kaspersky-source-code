/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file FileTransfer.h
 * \author ����� �����������
 * \date 2004
 * \brief ������� ��������� ������ �������� ������
 * 
 */

#ifndef KLFT_FILETRANSFER_H
#define KLFT_FILETRANSFER_H

#include <std/base/klbase.h>
#include <kca/prci/componentid.h>

#include "filedescription.h"

namespace KLFT {

	const int c_UploadDelay			= 6000;		// 6 secs 
	const int c_NextChunkTimeout	= 1000;		// 1 secs	

	const int c_DefaultChunkSize	= 32768;		// 32 Kb

	const int c_defaultUploadingClients	= 10;
	
	/*!
		��� ���������� FileTransfer
	*/
	const wchar_t c_FileTransferComponentName[] = L"FileTransfer";

	/*!
    * \brief ������������ ������� ( publisher ������ ������� �������� ���������� � 
		�������� ������������� ��������� ��� )
    */
	
	const wchar_t EVENT_TYPE_START_UPLOAD[]			= L"KLFT_StartUpload";			// ����� �������� �������� �� �������
	const wchar_t EVENT_TYPE_UPLOADED[]				= L"KLFT_Uploaded";				// ��������� �������� �������� �� �������	
	const wchar_t EVENT_TYPE_UPLOADING_CANCELED[]	= L"KLFT_UploadingCanceled";	// ������ ������� �������� �������� ������� �����

	
	/*!
    * \brief ���� �������
    */

	const wchar_t EVENT_BODY_FILE_ID[]			= L"KLFT_FileId";		// ������������� ����� 

	/*!
    * \brief ������� ��������� ������ File Transfer (FT).
    *  
    */

	class KLSTD_NOVTABLE FileTransfer : public KLSTD::KLBase 
	{	
	public:
		
		class TransferConnectionInvoker : public KLSTD::KLBase
		{
		public:
			virtual void CreateConnection( const std::wstring &localComponentName,
				const std::wstring &remoteComponentName ) = 0;
		};

	public:

		/*!
			\brief ������������� ���������� ��� ������ � �������� �������

			������ ������� ��������� ���������� �� ������� �����. ���� ���������� ������������� ���������
			������� ( ������� �������� �������� ), �� ������������� �������� ��������� �� ����������

			\param workingFolder			[in]  ���� � ����� �� �����, � ������� FileTransfer ����� ������� ���������� ������
			\param maxNumberOfUploadThreads [in]  ����������� ��������� ���-�� �������� ��� ���������� ����� � �������
			\param serverComponentId		[in]  ������������� ������� ( ������ ����� ����������� � ������� �������� ��������� ������ ComponentId )
		*/
		virtual void InitServer( const std::wstring &workingFolder,
			const std::wstring &serverConnName ) = 0;

		/*!
			\brief ������������� ���������� ��� ������ � �������� �������
			
			������ ������� ��������� ���������� �� ������� �����. 
			���������� ������� "��������������" ������
		*/
		virtual void InitClient( const std::wstring &workingFolder,			
			const std::wstring &serverRemoteConnName,
			const std::wstring &localConnName,
			TransferConnectionInvoker *connectionInvoker ) = 0;

		/*!
			\brief ��������� ����� ��� ������ Updater'�	
		*/
		virtual void SetUpdaterFolder( const std::wstring &updaterFolderName,
			int maxNumberUploadingClients = c_defaultUploadingClients ) = 0;

		/*!
			\brief ���������� ������ ����������
		*/
		virtual void Shutdown() = 0;
		
		/*!
			\brief ����������� �������� ������� �� ������� � ������������� ������� ���������� �����

			������ ������� ��������� ������ ( ����������� � ������ ���������� ������ )
			������� ��������� ����. ������������������ ��������:
				1. �������� ���� � ������� ����������� FileTrabsfer'�
				2. ������ ������� ����� ���������� ������������
				3. ������� ���������� � ������ �� �������� � ��������� � ������������� ������� ����� �� ����������� ��������������

			\param filePath		[in]  ���� � ����� 
			\param locsList		[in]  ������ ��������, ������� ���������� �������� ������ ����
			\param fileId		[out] ���������� �������������, ��������������� ����������, ��������� � ���������� ������
		*/
		virtual void SendFile( const std::wstring &filePath, 
			const KLTRAP::Transport::LocationExList &locsList,
			const std::wstring &fileDescription,
			std::wstring &fileId, 
			int maxNumberUploadingClients = c_defaultUploadingClients ) = 0;

		/*
			\brief ��������� ������������� ���-�� �������� ��� ������� ��� ����������
					�����
			\param fileId		[in]  ������������� �����
		 */
		virtual void SetMaxNumberUploadingClients( const std::wstring &fileId, 
			int maxNumberUploadingClients ) = 0;

		/*!
			\brief ��������� ����� ��������� �������� � ������ ��������
				��� ���������� �����
			
			\param fileId		[in]  ������������� �����
			\param locsList		[in]  ������ ��������, ������� ���������� �������� ������ ����
		*/
		virtual void AddClientsToFile( const std::wstring &fileId, 
			const KLTRAP::Transport::LocationExList &locsList ) = 0;

		/*!
			\brief ������� ����� ��������� �������� �� ������ ��������
				��� ���������� �����
			
			\param fileId		[in]  ������������� �����
			\param compsList	[in]  ������ ��������
		*/
		virtual void DeleteClientsFromFile( const std::wstring &fileId, 
			const std::list<std::wstring> &compsList ) = 0;
		
		/*!
			\brief ��������� ������ �������� ��� ���������� �����
			
			\param fileId		[in]  ������������� �����
			\param locsList		[in]  ������ ��������, ������� ���������� �������� ������ ����
		*/
		virtual void UpdateClientsList( const std::wstring &fileId, 
			const KLTRAP::Transport::LocationExList &locsList ) = 0;

		/*!
			\brief ���������� ������ ��������������� ������� ������
		*/
		virtual void GetFilesList( std::vector<std::wstring> &filesIdsList ) = 0;

		/*!
			\brief ���������� ������ ���������� �� �����

			\param fleId		[in] ������������� �����
		*/
		virtual FileDescription GetFileInfo( const std::wstring &fileId ) = 0;

		/*!
			\brief ������� �������� ������� ����� � ���������� ��� ������������� ��������

			\param fileId		[in] ������������� �����
		*/
		virtual void DeleteFile( const std::wstring &fileId ) = 0;

		/*!
			\brief �������� ���������� ���� �� ���������� ����			

			\param fileId		[in] ������������� �����
		*/
		virtual void SaveFileAs( const std::wstring &fileId,
			const std::wstring &copyFolderPath ) = 0;

		/*!
			\brief ���������� ��������� ������������ ��� FileTransfer'�
		*/
		virtual void GetLocalConnectionName( std::wstring &localName ) = 0;
		
	};		

} // end namespace KLFT


//!\brief ������� ��� ��������� �����
KLCSKCA_DECL bool KLFT_ArchiveFolder( const std::wstring &folderPathFrom, 
									 const std::wstring &archiveFileName );

//!\brief ������� ��� ���������� ������ �� ������
KLCSKCA_DECL bool KLFT_ExtractArchiveFile( const std::wstring &folderPathTo, 
										  const std::wstring &archiveFileName );

/*
	\brief ������� ������������/��������������� ���������� �������� ������
*/
DECLARE_MODULE_INIT_DEINIT2( KLCSKCA_DECL, KLFT );

/*\brief ���������� ��������� �� ���������� ������ ������ FileTransfer */
KLCSKCA_DECL KLFT::FileTransfer *KLFT_GetFileTransfer();


#endif // !defined(KLFT_FILETRANSFER_H)
