/*!
* (C) 2005 "Kaspersky Lab"
*
* \file foldersync.h
* \author ����������� �����
* \date 2006
* \brief ��������� ������� ������������� ����������� �����������
*
*/

#ifndef KLFT_FOLDERSYNC_H
#define KLFT_FOLDERSYNC_H

#include <map>

#include <std/base/klbase.h>
#include <std/err/klerrors.h>

#include "../kca/ft/filereceiver.h"

namespace KLFT {

	const int FileFlags_ChangeFromLastSync	= 0x1;
	const int FileFlags_DeletedFile			= 0x2;
	
	class FolderSync : public KLSTD::KLBase 
	{
	public:
  
		/*!
			\brief �������� �������� �����
		*/
		struct FolderFileInfo
		{
			FolderFileInfo() { CRC = 0; MaskFileFlags = 0; }
			FolderFileInfo( unsigned long _CRC, const std::string &fNameHash ) 
			{ 
				CRC = _CRC; 
				FileNameHash = fNameHash;
				MaskFileFlags = 0;
			}

			FolderFileInfo( unsigned long _CRC,
				const std::wstring &fName,
				const std::string &fNameHash ) 
			{ 
				CRC = _CRC; 
				FullFileName = fName;
				FileNameHash = fNameHash;
				MaskFileFlags = 0;
			}

			FolderFileInfo( const FolderFileInfo &fi )
			{
				CRC = fi.CRC;
				FullFileName = fi.FullFileName;
				FileNameHash = fi.FileNameHash;
				FilePathIndex = fi.FilePathIndex;
				MaskFileFlags = fi.MaskFileFlags;
			}

			unsigned long	CRC;
			std::wstring	FullFileName;
			std::string		FileNameHash;
			int				FilePathIndex;
			unsigned short	MaskFileFlags;
		};

		typedef std::vector<FolderFileInfo> FileInfoList;
		typedef std::map<std::string,FolderFileInfo> FileInfoMap;

		typedef std::vector<std::wstring> SubfoldersList;
		typedef std::vector<std::string> SubfoldersHashList;

		class FolderFilesInfo
		{
		public:
			FolderFilesInfo()
			{
				bFileNameHashed = false;
			}

			FolderFilesInfo( FolderFilesInfo &ffi )
			{
				FilesList = ffi.FilesList;
				bFileNameHashed = ffi.bFileNameHashed;

			}

		public:

			bool			bFileNameHashed;
			FileInfoList	FilesList;

		};
		/*!
			\brief ��������������� ��������� ����� ������������

			\param fileId		[in] ������������� �����
			\param workingFolder[in] ������� ���������� FT
			\param dirFilePath	[in] ���������� ��������� ����������
		*/
		virtual void InitServer( const std::wstring &fileId,
			const std::wstring &workingFolder, 
			const std::wstring &dirFilePath ) = 0;

		/*!
			\brief ��������������� ���������� ����� ������������

			\param fileId		[in] ������������� �����
			\param workingFolder[in] ������� ���������� FT
		*/
		virtual void InitClient( const std::wstring &fileId,
			const std::wstring &workingFolder ) = 0;

		/*!
			\brief ��������������� ���������� ����� ������������ ���������� � �������� ������� ������.
			������������ ����� ���������� ������ � �������� ����������� ����� �� ��������� � ������ �� 
			������ ����������

			\param fileId		[in] ������������� �����
			\param workingFolder[in] ������� ���������� FT
		*/
		virtual void InitEndPoint( const std::wstring &fileId,
			const std::wstring &workingFolder ) = 0;

		/*!
			\brief ���������� ������������� ����� ����� �������������
		*/
		virtual std::wstring GetFileId() = 0;

		/*!
			\brief ���������� ���������� ��� ���� ������ � ����������. ������ 
			���������� ������������ ��� ������������� � ��������� ��������

			\param folderFilesInfo	[out] ���������� ��� ���� ������ ����������		
		*/
		virtual void GetFullSyncInfo( FolderFilesInfo &folderFilesInfo ) = 0;	

		/*!
			\brief ��������� ���������� ����� �� ������ ������ ����������� � �������. 
			���� ���������� false �� ���������� �����

			\param clientFolderFilesInfo[in] ���������� ��� ���� ������ ���������� �������
		*/
		virtual bool CheckFullSyncContent( const FolderFilesInfo &clientFolderFilesInfo,			
			const KLFT::FolderSync::SubfoldersList &subfoldersList ) = 0;

		/*!
			\brief ��������� ���������� ����� �� ������ ������ ����������� � �������. ���������
			����� ������ ������������� ��� �������� �� �������.
			���� ���������� false �� ���������� ����� � ���� �� �����������

			\param clientFolderFilesInfo[in] ���������� ��� ���� ������ ���������� �������
			\param archiveFileId		[out] ��� ����� ������, � ������� ���������� FT
		*/
		virtual bool MakeFullSyncContent( const FolderFilesInfo &clientFolderFilesInfo,
			const std::wstring &archiveFileId,
			const KLFT::FolderSync::SubfoldersList &subfoldersList ) = 0;

		/*!
			\brief ��������� ���������� ����� �� ������ ������ ����������� � �������. ���������
			������ �� ������ ������.
			���� ���������� false �� ���������� �����

			\param clientFolderFilesInfo[in] ���������� ��� ���� ������ ���������� �������
			\param diffFolderFilesInfo	[out] ������ ��������� ��� ������������� ������
			\param serverSubfoldersHashList [out] ������ ����� � �������� UA �������� �������������
		*/
		virtual bool GetFullSyncInfo( const FileInfoMap &clientFolderFilesInfo,
			FolderFilesInfo &diffFolderFilesInfo,
			const FolderSync::SubfoldersList &subfoldersList,
			SubfoldersHashList &serverSubfoldersHashList ) = 0;

		/*!
			\brief �������������� ����� � ������� FT � ��������� � �������� ������������ ������ 
			������ �������� �������� ������ �� ��������� �������
		*/
		virtual void SyncServerFolder() = 0;

		/*!
			\brief ������������� ����� ������� � ��������������� ���������� �� ������� 
			������� ���������

			\param contentFileId	[in] ������������� ����� ���������
		*/
		virtual void Sync( const std::wstring &contentFileId ) = 0;

		/*!
			\brief ������������� ������ ������, ������� ������� ����������

			\param badFolderFilesInfo	[in] ������ ������
			\param serverSubfoldersHashList [in] ������ ����� � �������� UA �������� �������������
		*/
		virtual void SetNeedToUpdateFilesInfo( const FolderFilesInfo &badFolderFilesInfo,
			SubfoldersHashList &serverSubfoldersHashList ) = 0;

		/*!
			\brief ���������� ������������� ������� ����� ������ ���������� ����� � ������ ����������

			\param syncFolderFileName	[in] ���� � ����� � ����� �������������
		*/
		virtual bool IsNeedToUpdateFile( const std::wstring& syncFolderFileName, bool &notExists ) = 0;

		/*!
			\brief ���������� ������������ ��� ����� � ����. ����� ��� ������� � ������ ����������

			\param id	[in] ������������� ��������
		*/
		virtual std::wstring GetUploadingTemporyFileName( const std::wstring& id ) = 0;


		/*!
			\brief �������� ��� ��������� ���� � ����� �������������

			\param destFileName			[in] ���� � ��������� ����� 
			\param syncFolderFileName	[in] ��� ����� � ����� �������������
		*/
		virtual void UpdateFile( const std::wstring &destFileName, 
			const std::wstring &syncFolderFileName ) = 0;

				
		/*!
			\brief ���������� ���-�� ������, ��������� � ���������� ��������������.
				(-1) ������������� �� �����������
		*/
		virtual long GetLastFullSyncTimeout() = 0;

		/*!
			\brief ��������� ����� FT �� ���������� ������������� ����

			\param copyFolderName	[in] ���� ��� ����������
			\param overwite			[in] ������� ����������, � ������ ���� ���� ��� ����������
		*/
		virtual void SaveFolderAs( const std::wstring &copyFolderName, 
			bool overwrite = false ) = 0;

		/*!
			\brief ���������� ���������� � ����� ����� �������������

			\param folderFilePath	[in] ���� � ����� � ������ ���������� �������������
			\param fi				[out] ���������� � �����
		*/
		virtual void GetFolderFileInfo( const std::wstring &folderFilePath, 
			KLFT::FileInfo &fi ) = 0;

		/*!
			\brief ���������� ����� ����� ����� �������������

			\param folderFilePath	[in] ���� � ����� � ������ ���������� �������������
			\param ...
		*/
		virtual unsigned long GetFolderFileChunk( const std::wstring& folderFilePath,
			unsigned long startPosInFile, unsigned long neededSize,
			unsigned long &fullFileSize,
			void **ppBuff, unsigned long buffSize, bool &endOfFile ) = 0;

		/*!
			\brief ���������� ����� ����� ����������� �� multicast �������� 
			   ���������� ���������� � ��������� �����, � ����� ������ ����� �����
				�� ���������� � �������� �����
		*/
		virtual unsigned long  WriteFolderFileChunk( const std::wstring& folderFilePath,
			unsigned long startPosInFile, unsigned long fullFileSize,
			void *ppBuff, unsigned long buffSize, bool &endOfFile ) = 0;
		
		/*!
			\brief ���������� ������� ������� �������������� � ��������� �������������� ������
		*/
		virtual bool IfExistsUnprocessedLastSyncChangedFiles() = 0;

		/*!
			\brief ���������� ������� ������� �������������� � ��������� �������������� ������
		*/
		virtual void GetUnprocessedLastSyncChangedFiles( FolderFilesInfo &folderFilesInfo, 
			unsigned long &syncTickCount ) = 0;

		/*!
			\brief ���������� ���� ��������� ��� ���������� �����
		*/
		virtual void ProcessedLastSyncChangedFiles( const std::string &fileNameHash,
			unsigned long syncTickCount ) = 0;

		/*!
			\brief ������� ��� ������� �����
		*/
		virtual void DeleteWorkingFiles() = 0;

		/*!
			\brief ���������� ������� ����� � syncfolder
		*/
		virtual bool IsFileExists( const std::wstring& syncFolderFileName, bool &bCanBeUploaded ) = 0;

		/*!
			\brief ���������� ������ ������ ������� ���� ������� 

			\param clientFolderFilesInfo[in] ���������� ��� ���� ������ ���������� �������
		*/
		virtual void GetDeletedFilesList( const FolderFilesInfo &clientFolderFilesInfo,			
			const KLFT::FolderSync::SubfoldersList &subfoldersList, FileInfoList &deletedFolderFiles  ) = 0;

		/*!
			\brief ������� ����� ������� ����� �������� � ����� ��������� 
		*/
		virtual void SyncDeletedFiles( const FileInfoList &deletedFolderFiles  ) = 0;



	};

} // end namespace KLFT

KLCSKCA_DECL void KLFT_CreateFolderSync( KLFT::FolderSync **ppFolderSync );

#endif // KLFT_FOLDERSYNC_H
