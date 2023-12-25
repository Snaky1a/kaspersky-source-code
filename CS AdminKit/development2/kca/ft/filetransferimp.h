/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file FileTransferImp.h
 * \author ����� �����������
 * \date 2004
 * \brief ��������� ������ �������� ������ ( ���������� )
 * 
 */

#ifndef KLFT_FILETRANSFERIMP_H
#define KLFT_FILETRANSFERIMP_H

#include <map>

#include <std/base/klbase.h>
#include <std/conv/klconv.h>

#include <kca/prci/componentid.h>
#include <kca/contie/connectiontiedobjectshelper.h>

#include <transport/tr/transport.h>
#include <transport/tr/notifier.h>
#include <std/tp/threadspool.h>
#include <transport/tr/transportproxy.h>
#include <transport/wat/authserver.h>

#include <kca/ft/updateagentinfo.h>

#include "kca/ft/filetransfer.h"
#include "filereceiver.h"
#include "file.h"
#include "multicastsender.h"

namespace KLFT {

	const int c_defaultNumberOfUploadThreads	= 10;

	const wchar_t c_filesIdsListIdField[]		= L"ftp_FilesListFileId";

	class FileTransferImpBase : public FileTransfer, public KLTR::NotificationMulticastPacket,
		public KLFT::MulticastSender::FileProvider, public KLTP::ThreadsPool::Worker, public KLWAT::CustomCredentialsConverter
	{
	};

	class FileTransferImp : public KLSTD::KLBaseImpl<FileTransferImpBase> 
	{	
	public:
		KLSTD_INTERAFCE_MAP_BEGIN(FileTransferImp)
            KLSTD_INTERAFCE_MAP_ENTRY(KLTR::NotificationMulticastPacket)
        KLSTD_INTERAFCE_MAP_END()

		// ����� ��� Broadcast'��
		class FileTransferBroadcaster : public KLSTD::KLBaseImpl<KLTRAP::Transport::Broadcast> 
		{
		public:

			FileTransferBroadcaster( FileTransferImp *fileTransfer, const std::wstring &fileId,
				const KLTRAP::Transport::LocationExList &locsList );

			~FileTransferBroadcaster();
			
			int BroadcastCallback( KLTRAP::Transport::BroadcastId broadcastId, 
				KLTRAP::Transport::BroadcastState state, 
				const wchar_t *localComponentName, 
				const wchar_t *remoteComponentName,
				void *userData );

		public:

			KLTRAP::Transport::BroadcastId broadcastId;
			std::wstring		m_workingFileId;
			FileTransferImp		*m_fileTransfer;
			KLTRAP::Transport::LocationExList m_locsList;
		};

		// �������� async ������ ��� ������������� broadcast �������
		class CBroadcastCallInfo : public KLSTD::KLBaseImpl<KLSTD::KLBase>
		{
		public:
			std::list<std::wstring> m_filesIdsForBroadcasting;
		};

		class FileTransferDisconnectSink : public KLSTD::KLBaseImpl<CONTIE::DisconnectSink>
		{
		public:
			FileTransferDisconnectSink() {}

			void Init( FileTransferImp *pFT )
			{
				m_pFT = pFT;
			}

			virtual void OnDisconnectObjectID(
                            const std::wstring& wstrObject)
			{
				m_pFT->OnDisconnectObjectID( wstrObject );
			}

		private:
			FileTransferImp *m_pFT;
		};


		friend class FileTransferDisconnectSink;

	public:

		FileTransferImp();
		~FileTransferImp();


		//!\brief ������������� ���������� ��� ������ � �������� �������
		void InitServer( const std::wstring &workingFolder,
			const std::wstring &serverConnName );

		//!\brief ������������� ���������� ��� ������ � �������� �������
		void InitClient( const std::wstring &workingFolder,			
			const std::wstring &serverRemoteConnName,
			const std::wstring &localConnName,			
			const std::wstring &hostId,
			KLPAR::BinaryValue *pSer,
			TransferConnectionInvoker *connectionInvoker );

		//!\brief ��������� ���������� ���������� ��� ������������ �������������		 	
		void SetClientInfo( KLPAR::BinaryValue *pSer, std::wstring &hostId );

		//!\brief ��������� ����� ��� ������ Updater'�
		void SetUpdaterFolder( const std::wstring &updaterFolderName,
			int maxNumberUploadingClients = c_defaultUploadingClients );

		//!\brief ���������� ������ ����������
		void Shutdown();
		
		//!\brief ����������� �������� ������� �� ������� � ������������� ������� ���������� �����
		void SendFile( const std::wstring &filePath, 
			const KLTRAP::Transport::LocationExList &locsList,
			const std::wstring &fileDescription, std::wstring &fileId,
			int maxNumberUploadingClients = c_defaultUploadingClients );
		
		//\brief ��������� ������������� ���-�� �������� ��� ������� ��� ���������� �����
		void SetMaxNumberUploadingClients( const std::wstring &fileId, 
			int maxNumberUploadingClients );

		//!\brief ��������� ����� ��������� �������� � ������ �������� ��� ���������� �����
		void AddClientsToFile( const std::wstring &fileId, 
			const KLTRAP::Transport::LocationExList &locsList );

		//!\brief ������� ����� ��������� �������� �� ������ �������� ��� ���������� �����
		void DeleteClientsFromFile( const std::wstring &fileId, 
			const std::list<std::wstring> &compsList );

		//!\brief �������������� ������ �������� ��� ���������� �����
		void ReplaceClientsList( const std::wstring &fileId, 
			const KLTRAP::Transport::LocationExList &locsList );

		//!\brief ��������� ������ �������� ��� ���������� �����
		void UpdateClientsList( const std::wstring &fileId, 
			const KLTRAP::Transport::LocationExList &locsList );

		//!\brief ���������� ������ ��������������� ������� ������
		void GetFilesList( std::vector<std::wstring> &filesIdsList );

		//!\brief ���������� ������ ���������� �� �����
		FileDescription GetFileInfo( const std::wstring &fileId ) ;

		//!\brief ������� �������� ������� ����� � ���������� ��� ������������� ��������
		void DeleteFile( const std::wstring &fileId );

		//!\brief �������� ���������� ���� �� ���������� ����			
		void SaveFileAs( const std::wstring &fileId,
			const std::wstring &copyFolderPath,
			bool overwrite = false );

		//!\brief ���������� ��������� ������������ ��� FileTransfer'�
		void GetLocalConnectionName( std::wstring &localName );

		//!\brief ���������� ������� ���������� FileTransfer'�
		void GetWorkingFolder( std::wstring &workingFolder );
		
		//!\brief ���������� ���� �� ��� ������� ���������� ����� ��� ��������
		bool HasNotSentFiles( const std::wstring &remoteName );

		/*!\brief ������� ������� ���������� ��� ������� ���������� ����� ����������
			 � �������������� ������� �����
		*/
		void InitiateRemoteConnectionAndSendSignal( const std::wstring &localConnName, 
				const std::wstring &remoteConnName, 
				const std::wstring &remoteName );

		//!\brief ���������� ������ �� ��������� ���� ������� �������� �����
		bool IsFileUploadingByHost( const std::wstring &fileId, const std::wstring &remoteName );
		
		//!\brief ���������� ����������� ������ ������ ����������
		bool GetUpdateAgentStatistics( UpdateAgentStatistics &uaStat );

		//\brief ���������� ������ listener ������ ������������ UpdateAgent'��
		void GetUsingListenersPostsList( std::vector<int> &vecTCPPortsList,
			std::vector<int> &vecUDPPortsList );

		//!\brief �������� ������ �������
		void SendUploadSignal( const std::wstring &fileId, 
			const std::wstring &localName, const std::wstring &remoteName );

		//!\brief ���������� ��������� ������ �����
		int GetNextFileChunk( 
			const std::wstring &remoteClientName,
			const std::wstring &fileName, const std::wstring &fileId,
			unsigned long pos, unsigned long neededSize,
			unsigned long &fullFileSize,
			bool useUpdaterFolder, unsigned long multicastRecived,
			char **ppBuff, int &buffSize );

		//!\brief ���������� ��������� ������ � ���� ������� ��������
		void PutNextFileChunk( const std::wstring &fileId,			
			unsigned long pos, 
			unsigned long fullFileSize,
			unsigned long CRC,
			void *ppBuff, int buffSize );

		//!\brief ��������� �������� ����� �� �������
		void InitiateFileUpload( const std::wstring &fileName, const std::wstring &fileId,
			const std::wstring &description,
			const bool dirFlag,
			unsigned long fullFileSize,			
			const bool useConnectionNames,
			const KLTRAP::Transport::ConnectionFullName &connFullName,
			KLFT::FileType fileType,
			KLFT::UploadingType updateAgentUploadingFlag,
			UpdateAgentLocationList &updateAgentsLocs,
			unsigned long uploadDelay, unsigned long nextChunkDelay );

		//!\brief ��������� �������� package �� �������
		void InitiatePackageUpload( const std::wstring &fileName, const std::wstring &fileId,
			const std::wstring &description,
			const bool dirFlag,	
			const bool useConnectionNames,
			const KLTRAP::Transport::ConnectionFullName &connFullName, 
			KLFT::FileType fileType,			
			unsigned long uploadDelay, unsigned long nextChunkDelay );

		//!\brief ��������� �������� ����� �� �������
		void InitiateServerFileUpload( const std::wstring &fileId,
			const bool dirFlag,
			unsigned long fullFileSize,
			unsigned long lifeTime,
			const std::wstring &localConnName, 
			const std::wstring &remoteConnName );

		//!\brief ���������� ������ ��������������� ������, ��������������� ��� ������� �������
		void GetFilesIdsList( const std::wstring &clientName, 
			KLSTD::CAutoPtr<KLPAR::Params> &pList );
		
		//!\brief ������� ������������ ������ ����������
		void RegisterUpdateAgent( int nAgentHostId, 
			const std::wstring &strConnName, 
			const std::wstring &strAddress, const std::wstring &strNoSSLAddress, 
			const std::wstring &strMulticastIp,
			int nGroupId, KLPAR::BinaryValue *pCert, const std::wstring &certPswd );

		//!\brief ������� �������� ������� ������ ���������� �� �������
		void CheckUpdateAgentStatus( const KLTRAP::Transport::ConnectionFullName &serverConnName );
		
		//\brief ������� ��������� ������ FT �� ��������� ��������� ���������� �� �������
		void SwitchToReserveUpdaterFolder( const std::wstring &wstrNagentHostId );

		//\brief ���������� ��������� ������ � ��������� ���������� ����������
		void IsReserveUpdaterFolderActivated( bool &bUseReserveUpdate, 
			std::wstring &wstrNagentHostId );

		//!\brief ������� �������� ������
		virtual int RunWorker( KLTP::ThreadsPool::WorkerId wId );

		//!\brief ��������� info ����� � ������� ����������
		void LoadInfoFiles();
		
		//!\brief ������������� ���������� � �������� ��������� ���������� � ������ �� ������� � ������� ���������� �� �������
		void DoCheckServerFilesList();

		//!\brief ��������� ���������� � ������ �� ������� � ������� ���������� �� �������
		void LoadServerFileInfo( KLTRAP::TransportProxy &trProxy );
		
		//!\brief ���������� ���������� � ������ � ����� Updater
		void GetUpdaterFolderFileInfo( const std::wstring &fileName, 
			FileInfo &r );

		void DeleteAlreadyUploadedClient( const std::wstring &fileId, const std::wstring &remoteComponentName );
		
		void DeleteUpdaterFile( const std::wstring &fileId );

		virtual void MulticastPacketArrived( const std::wstring &mcGroupName,
			const KLPAR::BinaryValue *pTransportPacket );

		// KLFT::MulticastSender::FileProvider
		virtual int GetFileInfo( const std::wstring &fileId, 
				const std::wstring &fileName,
				unsigned long &fullSize,
				std::wstring &folderName );

		virtual int GetFileChunk( const std::wstring &fileId, 
				const std::wstring &fileName,
				unsigned long pos,
				void *buff, unsigned long buffSize, 
				bool &endOfFile );

		virtual int OnFileSent( const std::wstring &fileId,
				const std::wstring &fileName, 
				const unsigned long sentSize );
		
		/////////////////////////////////////////////

		bool GetSyncFolderDiff( const std::wstring &fileDescription, 
				const KLFT::FolderSync::FileInfoMap &clientFolderInfo,
				std::wstring &syncFolderFileId,
				KLFT::FolderSync::FolderFilesInfo &diffFolderFilesInfo,
				const FolderSync::SubfoldersList &subfoldersList,
				KLFT::FolderSync::SubfoldersHashList &subfoldersHashList );

		void GetSyncFolderFileInfo( 
				const std::wstring &remoteClientName,
				const std::wstring &syncFolderFileId, 
				const std::wstring &folderFileName,
				KLFT::FileInfo &fi );

		int GetSyncFolderFileChunk( 
				const std::wstring &remoteClientName,
				const std::wstring &syncFolderFileId, 
				const std::wstring &folderFileName,
				unsigned long pos, unsigned long neededSize,
				unsigned long &fullFileSize,
				void **buff, unsigned long &buffSize, 
				bool &endOfFile );

		bool TryToGetUpdateAgentInfoFromServer(
				const std::wstring &localName, std::wstring &serverRemoteName,
				bool &useUpdateAgent );

		bool CanUseUpdateAgent();

		bool ConnectToUpdateAgent( std::wstring &localName, std::wstring &remoteName,
			UpdateAgentLocationList	*locsList = NULL );

		bool ConnectToFolderSyncUpdateAgent(
				const std::wstring &folderSyncName,
				KLSTD::CAutoPtr<KLFT::FolderSync> &pOutFolderSync,
				std::wstring &localName, std::wstring &remoteName );
		
		bool AddSubfoldersForFolderSync( 
				const std::wstring &folderSyncName,
				const std::wstring &requestedFilePath );

		//KLWAT::CustomCredentialsConverter
        void ConvertCustomCredentials(
            const KLPAR::Params*        pCustomCredetials,
            KLWAT::CustomAccessToken&   customAccessToken,
			std::wstring&               wstrUserName,
			std::wstring&               wstrUserDomain,
			std::wstring&               wstrUserPassword );

        void AdjustSSLCredentials(
			void* pPublicKey,
			size_t nPublicKeySize,
            KLWAT::CustomAccessToken& customAccessToken);

	public:
		enum UsedConnectionType
		{
			NO_ConnType,
			UA_ConnType,
			SRV_ConnType
		};

	private:
		
		

		struct UsedConnectionInfo
		{
			UsedConnectionInfo()
			{
				m_connType = NO_ConnType;
				m_bNeedToClose = false;
			}

			void Init(std::wstring localConnName, std::wstring serverConnName)
			{
				KLTRACE4( L"KLFT", L"FileTransferImp::UsedConnectionInfo::Init(). localConnName - '%ls' serverConnName - '%ls'.\n", 
								localConnName.c_str(), serverConnName.c_str() );

				CloseConn();				
				m_connLocalName = localConnName;
				m_connRemoteName = serverConnName;
			}

			void CloseConn()
			{
				if ( m_bNeedToClose )
				{
					KLTRACE4( L"KLFT", L"FileTransferImp::UsedConnectionInfo::CloseConn(). localConnName - '%ls' serverConnName - '%ls'.\n", 
								m_connLocalName.c_str(), m_connRemoteName.c_str() );

					KLTR_GetTransport()->CloseClientConnection(				
						m_connLocalName.c_str(),
						m_connRemoteName.c_str() );
					
					m_connType = NO_ConnType;
					m_bNeedToClose = false;
				}
			}

			~UsedConnectionInfo()
			{
				CloseConn();
			}

			UsedConnectionInfo( const UsedConnectionInfo &ci )
			{
				m_connType = ci.m_connType;

				m_connLocalName = ci.m_connLocalName;
				m_connRemoteName = ci.m_connRemoteName;

				m_bNeedToClose = ci.m_bNeedToClose;
			}

			UsedConnectionType	m_connType;

			std::wstring		m_connLocalName, m_connRemoteName;
			bool				m_bNeedToClose;
			
		};

		typedef KLSTD::CAutoPtr<File> FileAutoPtr;
		typedef std::map<std::wstring, KLSTD::KLAdapt<FileAutoPtr> > FileMapType;
		
		KLSTD::CAutoPtr<KLSTD::CriticalSection> m_pCricSec;

		std::wstring							m_workingFolder;

		std::wstring							m_updaterFolder;
		int										m_maxNumberUploadingClientsForUpdaterFolder;

		std::wstring							m_localConnName, m_serverConnName;
		std::wstring							m_strHostId;
		std::wstring							m_strLocalHostConnName;

		int										m_uploadDelay, m_nextChunkTimeout;

		KLTP::ThreadsPool::WorkerId				m_transferWorkerId;
		bool									m_workerAdded;

		KLTP::ThreadsPool::WorkerId				m_checkFilesListWorkerId;
		bool									m_checkFilesListWorkerAdded;
		bool									m_checkFilesListWorkerFirstStart;

		FileMapType								m_filesList;

		KLSTD::CAutoPtr<TransferConnectionInvoker>	m_connectionInvoker;
		time_t									m_lastLoadFilesInfo;
		
		bool									m_shutdownFlag;

		KLSTD::CAutoPtr<CONTIE::ConnectionTiedObjectsHelper>	m_pContie;
		FileTransferDisconnectSink								m_DisconnectSink;

		KLFT::UpdateAgentInfo					m_updateAgentInfo;
		KLFT::UpdateAgentInfo					m_saveUpdateAgentInfo;

		KLSTD::CAutoPtr<KLPAR::BinaryValue>		m_pSer;

		KLSTD::CAutoPtr<MulticastSender>		m_pMulticastSender;

		UpdateAgentLocationList					m_updateAgentLocsList;

		UpdateAgentStatistics					m_updateAgentStat;

		// ��������� ��� ������ �������� ����������
		std::wstring							m_wstrNagentHostId;

	protected:

		//!\brief ���������� �������� ������
		void AddFileTransferWorker();
		
		//!\brief ���������� �������
		void PublishEvent( const std::wstring &eventTypeName, 
			const std::wstring &fileId, KLPAR::Params *pEventBody = NULL );

		//!\brief ������������� info �����
		void LoadInfoFile( const std::wstring &infoFilePath );

		void DoBroadcastCall( 
			KLSTD::CAutoPtr<CBroadcastCallInfo> pInfo);

		//!\brief ������� ��������� ����� ��� ����� �� ����� updater
		File *CreateUpdaterFolderFileDescription( const std::wstring &fileName );
		
		void OnDisconnectObjectID( const std::wstring& wstrObject );

		//!\brief ������� ���� �� UpdateAgent ��� ����������� ���������������
		void CreateUpdateAgentServerFile( const std::wstring &fileId );

		//!\brief ��������� ���������� ������ ����������
		void SaveUpdateAgentInfo();

		//!\brief ����������� ������ �������� ������ ����������
		void ReadUpdateAgentInfo();
		
		//!\brief ������� ���������� � ������ ����������
		void DeleteUpdateAgentInfo();

		//!\brief ��������� ���������� �� ������� ����������
		void SaveUpdateAgentLocsList();

		//!\brief ����������� ������ ���������� �� ������� ����������
		void ReadUpdateAgentLocsList();

		//!\brief ��������� ���������� ������ ����������
		void SaveUpdateAgentStatistics();

		//!\brief �������������� ���������� ������ ����������
		void ReadUpdateAgentStatistics();

		//!\brief ���������� ������ ������ ����������
		void ActivateUpdateAgent();

		//!\brief ������������� ������ ������ ����������
		void StopUpdateAgent();

		//!\brief ���������� �������� ������ � ���������� ������ ��������
		bool JoinUpdateAgentMulticastGroup();

		//!\brief ���������� FolderSync ��� ����� ��������������
		void GetFileFolderSync( const std::wstring &remoteClientName,
				const std::wstring &syncFolderFileId, FileAutoUnlock &fileUnlocker, 
				KLSTD::CAutoPtr<KLFT::FolderSync> &pFolderSync);

		//!\brief ���������� ����� ����� �������� �������������
		void ProcessSyncFolderFile( const std::wstring &folderFileId );

		//!\brief ���������� ���������� ����� ������������� ������/�����
		void ApplyPackageSyncArchive( const std::wstring &fileId );
	};		
	

	KLCSKCA_DECL void ConnectToMasterServer( const std::wstring &localName, std::wstring &serverRemoteName );

} // end namespace KLFT

#endif // !defined(KLFT_FILETRANSFERIMP_H)

