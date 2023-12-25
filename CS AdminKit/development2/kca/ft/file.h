/*!
 * (C) 2004 "Kaspersky Lab"
 *
 * \file File.h
 * \author ����� �����������
 * \date 2004
 * \brief ��������� �������� �����
 * 
 */

#ifndef KLFT_FILE_H
#define KLFT_FILE_H

#include <map>

#include <std/base/klbase.h>
#include <std/io/klio.h>

#include <kca/ft/updateagentinfo.h>
#include <kca/ft/filetransfer.h>
#include <kca/ft/filesender.h>
#include <kca/ft/foldersync.h>

namespace KLFT {

	const wchar_t c_InfoFileExt[] = L".info";
	
	const int c_defaultUploadingChunkDelay	= 60;	// 1 min

	class File : public KLSTD::KLBaseImpl<KLSTD::KLBase>
	{			
	public:

		struct UploadingClientDesc
		{
			std::wstring	clientName;
			time_t			lastAccessTime;
			bool			uploadingNow;
		};

		enum UpdateAgentFileStatus
		{
			UAFS_None = 0x0,
			UAFS_DownloadingFromServer = 0x1,
			UAFS_Downloaded = 0x2,
			UAFS_UseOnlyForUpdateAgentFlag = 0x4
		};

		File();

		virtual ~File();
		
		/*!
			\brief ������� �������� ����� ��� ������� ��������
		*/
		void CreateServerFile( const std::wstring &filePath, 
			const std::wstring &description, 			
			const std::wstring &workingFolder, 
			const KLTRAP::Transport::LocationExList &locsList,
			unsigned long broadcastDelay,
			std::wstring &fileId,
			int maxNumberUploadingClients );

		/*
			\brief ��������� ������������� ���-�� �������� ��� ������� 
		 */
		void SetMaxNumberUploadingClients( int maxNumberUploadingClients );

		/*!
			\brief ������� �������� ����� ��� �������� � �������
		*/
		void CreateClientFile( const std::wstring &fileName, const std::wstring &fileId,
			const std::wstring &description, bool isDir, unsigned long fullFileSize,
			KLFT::FileType fileType,
			const bool useConnectionNames,
			const KLTRAP::Transport::ConnectionFullName &connFullName, 
			unsigned long uploadDelay, unsigned long chunkTimeout,
			bool forUpdateAgentFlag,
			const UpdateAgentLocationList &updateAgentsLocs,
			const std::wstring &workingFolder );

		/*!
			\brief ��������� �������� ����� ��� �������� � �������
		*/
		void UpdateClientFile( const std::wstring &fileName, const std::wstring &fileId,
			const std::wstring &description, bool isDir, unsigned long fullFileSize,
			KLFT::FileType fileType,
			const bool useConnectionNames,
			const KLTRAP::Transport::ConnectionFullName &connFullName, 
			unsigned long uploadDelay, unsigned long chunkTimeout,
			bool forUpdateAgentFlag,
			const UpdateAgentLocationList &updateAgentsLocs,
			const std::wstring &workingFolder );
		
		/*!
			\brief ����������� ���������� ���� � ��������� ������ 
					( ��� ����������� ��������������� UpdateAgent'�� )
		*/
		void ConvertToServerFile( KLPAR::Params *pFullFileInfo );

		/*!
			\brief ������� �������� ����� ��� �������� 
		*/
		void CreateServerUploadedClientFile( const std::wstring &fileId,
			bool isDir, unsigned long fullFileSize,
			const std::wstring &remoteClientName, 			
			const std::wstring &workingFolder );

		/*!
			\brief ������� �������� ����� �� ����� updater ��� ������� � �������
		*/
		void CreateUpdaterFolderFile( const std::wstring &filePath, 
			int maxUploadClients = c_defaultUploadingClients );

		/*!
			\brief ������� �������� ����� ��� ������� �� ������
		*/
		void CreateSendToFile( KLFT::FileSender::FileInfo *filesArray, int filesArraySize, 
			std::wstring &fileId );

		/*!
			\brief ������� �������� package ��� ��������� � �������
		*/
		void CreatePackageFile( const std::wstring &fileName, const std::wstring &fileId,
			const std::wstring &description, 
			KLFT::FileType fileType,
			bool isDir,
			const bool useConnectionNames,
			const KLTRAP::Transport::ConnectionFullName &connFullName, 
			unsigned long uploadDelay, unsigned long chunkTimeout,
			const std::wstring &workingFolder );

		/*!
			\brief ������� �������� ����� ��� �������� � UA
		*/
		void CreateEndPointFile( const std::wstring &fileId,
			const std::wstring &description,
			const std::wstring &workingFolder );

		/*!
			\brief ��������� �������� ���� ( ���������� ������� ������������� ������������� )
		*/
		void UpdatePackageFile( KLFT::FileType &newFileType );


		/*!
			\brief ������� �������� ����� �� ����� �������� ( ��������� ������������� )
		*/
		void CreateFromInfoFile( const std::wstring &infoFilePath );

		/*!
			\brief ���������� ������������� �����
		*/
		std::wstring GetFileId();

		/*!
			\brief ���������� ������������� �������, �������� ��������
		*/
		std::wstring GetClientName();

		/*!
			\brief ���������� ��������� ��� ����������, ������� ���� ������������ ��� ������� ������� �����
		*/
		std::wstring GetLocalName();

		/*!
			\brief ��������� ���������� � �����
		*/
		FileDescription GetFileDescription();

		/*!
			\brief ������ �������� �����
		*/
		void SetStatus( FileDescription::FileStatus newStatus );

		/*!
			\brief ������ �������� �����
		*/
		FileDescription::FileStatus GetStatus();

		/*!
			\brief ���������� ����� "������" �����

			\return false - ���� ��� ��� ��������� chunk
		*/
		bool AddChunk( void *buff, unsigned long buffSize, unsigned long CRC, 
			unsigned long startPosInFile, unsigned long fullFileSize,
			bool fromMulticast = false );

		/*!
			\brief ��������� ��������� "������" �����

			\return ���-�� ����������� ����
		*/
		int GetChunk( const std::wstring &remoteClientName,
			unsigned long startPosInFile,			
			void *buff, unsigned long buffSize, bool &endOfFile );

		/*!
			\brief ���������� ������� � ������ ������������
		*/
		bool AddSentLocation( const std::wstring &remoteName );

		/*!
			\brief ���������� ������� � ������ ������������
		*/
		bool AddUploadedLocation( const std::wstring &remoteName );

		/*!
			\brief ��������� ������ �������� ��� ��������
		*/
		void AddClientsForSend( const KLTRAP::Transport::LocationExList &locsList );

		/*!
			\brief ������� �� ������ �������� ��� ��������
		*/
		void DeleteClients( const std::list<std::wstring> &compsList );

		/*!
			\brief ��������� ������ �������� ��� ���������� �����
		*/
		void UpdateClientsList( const KLTRAP::Transport::LocationExList &locsList );

		/*!
			\brief �������������� ������ �������� ��� ���������� �����
		*/
		void ResetClientsList( const KLTRAP::Transport::LocationExList &locsList );

		/*!
			\brief ��������� ������ ��������
		*/
		bool CheckUploadingClient( const std::wstring &remoteClientName, 
			bool &uploadingClientsExceeded );

		/*!
			\brief �������� ������� ���� �� ���������� ����
		*/
		void SaveFileAs( const std::wstring &filePath, bool overwrite );

		/*!
			\brief ������� ��� ���������� � ������ �����
		*/
		void DeleteWorkingFiles();

		/*!
			\brief ������� ���������� ������� � �����
		*/
		void Lock();
		void UnLock();

		/*!
			\brief ����������� ���������� �� ��������� �������
		*/
		bool IsNeedToUpload();

		/*!
			\brief ����������� ���������� �� ��������� �������� ������� � ��������
		*/
		bool IsNeedToBroadcast( bool checkInBroadcastFlag = true );

		/*!
			\brief ��������� ������� ����� ��� ����� ��������� �������� � ������
		*/
		void InBroadcastFlag( bool inBroadcast = false );

		/*!
			\brief ���������� ���-�� ������������� Broadcast'�� ��� ������� �����
		*/
		int GetBroadcastCount();

		/*!
			\brief ���������� ���-�� ������������� Broadcast'�� ��� ������� �����
		*/
		void ResetBroadcastCount( int count = 0 );

		/*!
			\brief ����������� ����� �������� ������ ������� ������� �����
		*/
		void IncreaseStartUploadingTimeout( int addDelay );

		/*!
			\brief �������� timeout ����� �������� ��������� ������ �����
		*/
		void ChangeUploadDelayTimeout( bool increase = true, bool usingUAConnection = false );
		
		/*!
			\brief ���������� ����� ���������� ������ ��� ������� �����.
		*/
		long GetUploadChunkFailedCount();

		/*!
			\brief ������� ������ � broadcastId
		*/
		KLTRAP::Transport::BroadcastId GetBroadcastId();
		void SetBroadcastId( KLTRAP::Transport::BroadcastId broadcastId );

		/*!
			\brief ���� �� ����� Updater
		*/
		bool IsCustomModeFile();

		/*!
			\brief ���� ������� Update Agent ��� ���������� ���������������
		*/
		bool IsForUpdateAgentFile();

		/*!
			\brief ���������� ������ ����� ������ ����������
		*/
		UpdateAgentFileStatus GetUpdateAgentFileStatus();

		/*!
			\brief ������� ������������� ���������� ������� ��� ������� ������� ����� �� ����� ����������
		*/
		void ResetUseOnlyForUpdateAgentFlag();
		bool GetUseOnlyForUpdateAgentFlag();
		
		/*
			\brief ��������� ������� ������ �����
		 */
		void ReadFileSize();

		/*
			\brief ���������� ��������� ����� �������� �������� ����� ��������
		 */
		int GetCalculateDelayTimeout();

		/*
			\brief ���������� ������ ������� ����������
		 */
		UpdateAgentLocationList GetUpdateAgentList();

		/*
			\brief ������� �������� ������������ ����� ( �� multicast �������� )
		 */
		bool PartlySavedFile();
		void PartlySavedFile( bool newVal );

		/*
			\brief ��������� ������ � ������� ���������� ������������ �����
		 */
		bool GetNextNeededChunk( unsigned long &pos, unsigned long &size, 
			unsigned long buffsize );

		/*!
			\brief ��� �����
		*/
		KLFT::FileType Type();

		/*!
			\brief ���������� ���������� �� ������ ����� �������������
		*/
		void GetFullSyncInfo( KLFT::FolderSync::FolderFilesInfo &folderFileInfo );

		/*!
			\brief ��������� �� ����� ����� ������������� � ������� ( ������ ������������� ������� )
		*/
		void ApplyPackageSyncArchive( const std::wstring& syncArchiveFileId );

		/*!
			\brief ���������� ��������� �� ��������� FolderSync
		*/
		void GetFolderSync( KLSTD::CAutoPtr<KLFT::FolderSync> &pFolderSync );
		
		/*!
			\brief ���������� ������� ������� �������������� � ��������� �������������� ������
		*/
		bool IfExistsUnprocessedLastSyncChangedFiles();

		/*!
			\brief ���������� ������� ������� �������������� � ��������� �������������� ������
		*/
		bool GetUnprocessedLastSyncChangedFiles( std::vector<std::wstring>& folderFiles );

		/*!
			\brief ���������� ���� ��������� ��� ���������� �����
		*/
		void ProcessedLastSyncChangedFiles( const std::wstring& folderFilePath );

		/*!
			\brief ������� ��� ������ �� ������� �������� ��� �������������
		*/
		KLFT::FolderSync::SubfoldersList GetSubfoldersListForFolderSync();
		bool AddSubfoldersForFolderSync( const std::wstring &requestedFilePath );
		bool AppendSubfoldersForFolderSync( const KLFT::FolderSync::SubfoldersList &subfoldersList );

		//!\brief ���������� ������� �������� �������������
		int GetArchivatePercent();

		//!\brief ��������� info ����
		void SaveInfoFile();
		

	private:
		
		enum CloseChunkType{ CCT_None, CCT_Left, CCT_Right, CCT_Equal };

		class RecievedChunk
		{
		public:

			RecievedChunk()
			{
				pos = size = 0;
			}

			RecievedChunk( unsigned long _pos, unsigned long _size )
			{
				Init( _pos, _size );
			}

			RecievedChunk( const RecievedChunk &rc )
			{
				pos = rc.pos;
				size = rc.size;
			}

			void Init( unsigned long _pos, unsigned long _size )
			{
				pos = _pos, size = _size;
			}

			unsigned long pos;
			unsigned long size;
		};

		typedef std::list<RecievedChunk> RecievedChunkList;

		typedef std::map<std::wstring,UploadingClientDesc> UploadingClientsList;
		
		
		// ������ ������
		KLSTD::CAutoPtr<KLSTD::CriticalSection>		m_pCricSec;

		FileDescription::FileStatus					m_currentStatus;

		std::wstring								m_fileName;
		std::wstring								m_copyFileName;
		std::wstring								m_fileId;
		std::wstring								m_infoFilePath;
		std::wstring								m_description;
		std::wstring								m_clientName;
		std::wstring								m_localName;
		bool										m_isDirectory;
		unsigned long								m_fullFileSize;
		unsigned long								m_multicastRecvSize;
		unsigned long								m_currentUploadPos;
		time_t										m_createTime;
		bool										m_customFileMode;
		KLFT::FileType								m_fileType;

		long										m_updateAgentFileStatus;

		UpdateAgentLocationList						m_updateAgentsLocs;


		KLTRAP::Transport::BroadcastId				m_broadcastId;

		bool										m_inBroadcastFlag; 
		int											m_BroadcastCount; 
		time_t										m_lastOperationTime;
		long										m_delay;
		long										m_uploadChunkTimeout;
		long										m_uploadChunkFailedCount;

		KLTRAP::Transport::LocationExList			m_sentLocsList;			//! ������ ��������, ������� ���� ��������� ������� �� �������� ������� �����
		KLTRAP::Transport::LocationExList			m_notSendLocsList;		//! ������ ��������, ��� ������� ��� �� �������� ������� �� ��������
		
		KLTRAP::Transport::LocationExList			m_uploadLocsList;		//! ������ ��������, ������� ��� ������� ������ ����

		KLSTD::CAutoPtr<KLSTD::File>				m_file;
		
		time_t										m_createFileTime;

		UploadingClientsList						m_uploadingClients;		//! ������ �������� ������� ���������� �������� ������� �����
		int											m_maxNumberUploadingClients;
		int											m_calculatedUploadDelayTimeout;	//! ��������� ����� �������� ������� �� �������

		RecievedChunkList							m_recievedChunks;
		bool										m_partlySavedFile;		

		KLSTD::CAutoPtr<KLFT::FolderSync>			m_pFolderSync;

		KLFT::FolderSync::FolderFilesInfo			m_lastSyncFilesInfo;
		unsigned long								m_lastSyncTickCount;

		KLFT::FolderSync::SubfoldersList			m_vecFoldersForSync;

		long										m_totalFilesInArchive, m_archivedFilesCount; //! ��� �������� �������� ���������

	protected:
		
		//!\brief ������������� ���������� ������
		void Init( const std::wstring &fileId,
			const std::wstring &filePath, const std::wstring &description,
			const std::wstring &workingFolder, bool copyFile, bool createFile,
			bool updaterFile = false );

		void Init( const std::wstring &fileId, const std::wstring &copyFileName,
			KLFT::FileSender::FileInfo *filesArray, int filesArraySize );

		//!\brief ��������������� ������� ��� ������������ 
		void AddLocationListExInParams( KLPAR::Params *parSerFile, 
			const wchar_t *fieldName, KLTRAP::Transport::LocationExList &locsList );
		void AddLocationExInParams( KLPAR::Params *parSerFile, 
			const wchar_t *fieldName, KLTRAP::Transport::LocationEx &loc );
		void AddUAListInParams( KLPAR::Params *parSerFile );		
		void AddChunksListInParams( KLPAR::Params *parSerFile );
		void AddSubfoldersListInParams( KLPAR::Params *parSerFile );

		//!\brief �������������� ������ �� info �����
		void RestoreFromInfoFile();

		//!\brief ��������������� ������� ��� ��������������
		void GetLocationListExFromParams( KLPAR::Params *parSerFile, 
			const wchar_t *fieldName, KLTRAP::Transport::LocationExList &locsList );
		void GetLocationListExFromParams( KLPAR::Params *parSerFile, 
			const wchar_t *fieldName, KLTRAP::Transport::LocationEx &loc );
		void GetUAListFromParams( KLPAR::Params *parSerFile );
		void GetChunkListFromParams( KLPAR::Params *parSerFile );
		void GetSubfoldersListInParams( KLPAR::Params *parSerFile );

		//!\brief ��������� ��� ��� ������� ������� ����
		bool CheckDeliveredStatus();

		//!\brief ������� ����������� ����� �������� ����� �������� ����� �� �������
		void CalculateDelayTimeout();

		//!\brief ���������� ��������� ����� ������������ ����� ��� ������������
		RecievedChunkList::iterator GetCloseChunksListItem( 
			unsigned long pos, unsigned long size, CloseChunkType &chunkType );

		//!\brief ��������� ����� ������������� chunk'�
		void ClueRecievedChunksList();

	};

	class FileAutoUnlock
	{
	public:
		
		FileAutoUnlock() { m_file = NULL; }
		~FileAutoUnlock() 
		{			
			if ( m_file ) m_file->UnLock();
		}
		
		void Init( File *file )
		{
			m_file = file;
			if ( m_file ) m_file->Lock();
		}

		File *Get()
		{
			return m_file;
		}
		
		void Free()
		{
			if ( m_file ) m_file->UnLock();
			m_file = NULL;
		}
		
		
	private:
		File *m_file;
	};

	bool CreateArchiveFile( KLFT::FileSender::FileInfo *filesArray, int filesArraySize,
		const std::wstring &copyFileName, const std::wstring &fileId,
		long &totalFilesCount, long &archivedFilesCount );
	
	bool CreateArchiveFile2( KLFT::FileSender::FileInfo *filesArray, int filesArraySize,
		const std::wstring &copyFileName, const std::wstring &fileId );

	bool CreateArchiveFile( const std::wstring &folderPath, const std::wstring &workingFolder,
		const std::wstring &fileId );

	bool ExtractArchiveFile( const std::wstring &folderPath, const std::wstring &workingFolder,
		const std::wstring &archiveFile, const std::wstring &fileId );
	
} // end namespace KLFT

#endif // !defined(KLFT_FILE_H)
