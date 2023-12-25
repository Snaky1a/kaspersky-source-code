/*!
* (C) 2005 "Kaspersky Lab"
*
* \file filetransferserver.h
* \author ����������� �����
* \date 2005
* \brief ��������� ������ �������� ������
*
*/

#ifndef FTS_FILETRANSFERSERVER_H
#define FTS_FILETRANSFERSERVER_H

#include <std/base/klbase.h>
#include <std/err/klerrors.h>

#include <server/fts/serverfiledescription.h>
#include <kca/ft/filetransferconst.h>

#include <kca/ft/errors.h>

#include <server/db/dbconnection.h>
#include <server/srvinst/srvinstdata.h>

namespace KLFT
{
	struct UpdateAgentInfo;
}

namespace KLFTS {

	const wchar_t c_DefaultMulticastId[] = L"http://225.6.7.8:15001";

	class KLSTD_NOVTABLE FileTransferServer : public KLSTD::KLBase 
	{
	public:

		struct FileTransferServerOptions
		{
			FileTransferServerOptions()
			{
				bSendUnicast = true;
			}

			bool bSendUnicast;
		};

		struct GetFileChunkParams
		{
			GetFileChunkParams()
			{
				bUseUpdaterFolder = bForUpdateAgent = false;
			}
			
			GetFileChunkParams( const GetFileChunkParams &p )
			{
				bUseUpdaterFolder = p.bUseUpdaterFolder;
				bForUpdateAgent = p.bForUpdateAgent;
				wstrNagentHostId = p.wstrNagentHostId;
			}
			
			bool			bUseUpdaterFolder;
			bool			bForUpdateAgent;
			std::wstring	wstrNagentHostId;
		};	
	

		/*!
			\brief ������������� ���������� ��� ������ � �������� �������

			������ ������� ��������� ���������� �� ������� �����. ���� ���������� ������������� ���������
			������� ( ������� �������� �������� ), �� ������������� �������� ��������� �� ����������

			\param workingFolder			[in]  ���� � ����� �� �����, � ������� FileTransfer ����� ������� ���������� ������
			\param maxNumberOfUploadThreads [in]  ����������� ��������� ���-�� �������� ��� ���������� ����� � �������
			\param serverConnName			[in]  ��� ���������� 
		*/
		virtual void InitServer( KLSRV::SrvData* pSrvData,
			const std::wstring &workingFolder,
			const std::wstring &serverConnName,
			FileTransferServerOptions &options = FileTransferServerOptions() ) = 0;

		/*!
			\brief ��������� ����� ��� ������ Updater'�	
		*/
		virtual void SetUpdaterFolder( const std::wstring &updaterFolderName,
			int maxNumberUploadingClients = KLFT::c_defaultUploadingClients ) = 0;

		/*!
			\brief ���������� ������ ����������
		*/
		virtual void Shutdown() = 0;

		/*!
			\brief ������������ ������ ������ ����������

			\param nAgentHostId		[in] ������������� �����, ������� ����� ������������� � �������� ������ ���������� ( UA )
			\param nGroupId			[in] ������������� ������, ����� �� ������� ������ UA ����� ����������� 
						( ���� nGroupId < 0 �� ����� ������������ ������ ������� ��������� UA )
			\param strAddress		[in] TCP/IP ������ UA ( ���� ������� ������ ������, �� ����� 
						����������� ����� �������� � �������� ������� ����� + ���� 13000 )
			\param strMulticastIP	[in] Multicast ����� �������� ( ���� �������� ������ ������,
						�� ������ ����� �������� ������������� )
			\param pCertificate		[in] ����������, ������� ����� ������������ ��� ������� 
						������� �������� � ��� �������� ����������� 
						( ���� ������� NULL �� ���������� ����� ������������ ������ ������� )			
		*/
		virtual void RegisterUpdateAgent( KLFT::UpdateAgentInfo &updateAgentInfo, 
			bool checkExisting = true ) = 0;


		/*!
			\brief ������� ����� ������������������ ����� ����������

			\param nAgentHostId		[in] ������������� �����, ������� ����� ������������� � �������� ������ ���������� ( UA )
		*/
		virtual void DeleteUpdateAgent( const std::wstring &nAgentHostId ) = 0;

		
		/*!
			\brief ����������� �������� ������� �� ������� � ������������� ������� ���������� �����

			������ ������� ��������� ������ ( ����������� � ������ ���������� ������ )
			������� ��������� ����. ������������������ ��������:
				1. �������� ���� � ������� ����������� FileTrabsfer'�
				2. ������ ������� ����� ���������� ������������
				3. ������� ���������� � ������ �� �������� � ��������� � ������������� ������� ����� �� ����������� ��������������

			\param filePath		[in]  ���� � ����� 
			\param hostsList	[in]  ������ ��������������� ������, ������� ���������� �������� ������ ����
			\param fileId		[out] ���������� �������������, ��������������� ����������, ��������� � ���������� ������
		*/
		virtual void SendFile( KLDB::DbConnectionPtr pDbConn,
			const std::wstring &filePath, 
			const HostsIdsList &hostsList,
			const std::wstring &fileDescription,
			std::wstring &fileId, 
			KLPAR::Params *pParContext = NULL,
			int maxNumberUploadingClients = KLFT::c_defaultUploadingClients ) = 0;
		
		/*!
			\brief ����������� �������� ������� �� ������� � ������������� ������� ���������� ������

			� ������ ������ ������� ����� ����������� � ���� �������� ����������. ��� ������� 
			���������� ������� ������������ ������������� ���������� �� ������� � ����� ���������� 
			���������� �� �������.
			
			\param fileDirPath		[in]  ���� � ����������
			\param locsList		[in]  ������ ��������, ������� ���������� �������� ������ ����
			\param fileId		[out] ���������� �������������, ��������������� ����������, ��������� � ���������� ������
		*/
		virtual void SendPackage( KLDB::DbConnectionPtr pDbConn,
			const std::wstring &filePath, 
			const HostDescList &hostsList,			
			const std::wstring &fileDescription,
			std::wstring &fileId, 
			KLPAR::Params *pParContext = NULL,
			int maxNumberUploadingClients = KLFT::c_defaultUploadingClients ) = 0;
		
		/*!
			\brief �������������� ���������������� ����� ��� ����������� �������� ��������

			��� ������� ���������� ������� ������������ ������������� ���������� �� ������� � ����� ���������� 
			���������� �� �������.
						
			\param fileId		[out] ���������� ������������� ����� ���������� ����� ( package )
		*/
		virtual void SyncPackage( KLDB::DbConnectionPtr pDbConn,			
			std::wstring &fileId ) = 0;
		
		/*!
			\brief ������� ����� ������������� ��� ������� ����������
			
			����� �������� �������� � �� ������������� ������������� ����������� ��������� ����������������
			 ����� � ���������� ������. ��������� ������� ���������� ���������� � ������������� ��������
			 ������ ������������� �����.
			
			\param fileDirPath		[in]  ���� � ����������
			\param groupIds		[in]  ������ ��������������� �����, ��� ������� ���������� �������������� ������ �����
										���� ������ ������, ����� ����� ���������������� �� ��� ������ ���������� 
										������� ������� �����������������.
			\param fileId		[out] ���������� �������������, ��������������� ����������, ��������� � ���������� ������
		*/
		virtual void CreateFolderSync( const std::wstring &filePath, 			
			const std::wstring &syncFolderName,
			std::wstring &fileId, 
			KLPAR::Params *pParContext = NULL,
			int maxNumberUploadingClients = KLFT::c_defaultUploadingClients ) = 0;

		/*!
			\brief ���������� ������������� �����
			
			������ ������� ���������� ����� ��������� ����� ������������� � �� � � ������
			�������� ������ ������������ ������������ ���������������� ����� � ������ ����� � ������� FT.
			���������� �������� ������� �������� ���������� � ������������� ��������� ������� �������������.
			
			\param syncFolderName	[in]  ��� ����� �������������
		*/
		virtual void InitiateFolderSync( KLDB::DbConnectionPtr pDbConn, const std::wstring &syncFolderName ) = 0;

		/*
			\brief ��������� ������������� ���-�� �������� ��� ������� ��� ����������
					�����
			\param fileId		[in]  ������������� �����
		 */
		virtual void SetMaxNumberUploadingClients( KLDB::DbConnectionPtr pDbConn,
			const std::wstring &fileId, 
			int maxNumberUploadingClients ) = 0;

		/*!
			\brief ��������� ����� ��������� �������� � ������ ��������
				��� ���������� �����
			
			\param fileId		[in]  ������������� �����
			\param locsList		[in]  ������ ��������, ������� ���������� �������� ������ ����
		*/
		virtual void AddClientsToFile( KLDB::DbConnectionPtr pDbConn,
			const std::wstring &fileId, 
			const HostsIdsList &hostsList ) = 0;

		/*!
			\brief ������� ����� ��������� �������� �� ������ ��������
				��� ���������� �����
			
			\param fileId		[in]  ������������� �����
			\param compsList	[in]  ������ ��������
		*/
		virtual void DeleteClientsFromFile( KLDB::DbConnectionPtr pDbConn,
			const std::wstring &fileId, 
			const HostsIdsList &hostsList ) = 0;

		/*!
			\brief �������������� ������ �������� ��� ���������� �����
			
			\param fileId		[in]  ������������� �����
			\param locsList		[in]  ������ ��������, ������� ���������� �������� ������ ����
		*/
		virtual void ReplaceClientsList( KLDB::DbConnectionPtr pDbConn,
			const std::wstring &fileId, 
			const HostsIdsList &hostsList ) = 0;		
		
		/*!
			\brief ��������� ������ �������� ��� ���������� �����
			
			\param fileId		[in]  ������������� �����
			\param hostsList	[in]  ������ ��������, ������� ���������� �������� ������ ����
			\param bDeleteAbsent [in]	true - ������� �� ����� �������� ������� ��� � ���������� 
											������. ��� ������� �������� ��� ��������� �������� 
											������������.
										false - ������ ����� ������� �� ������ ����� ��������� � 
											������ �������� �����. ���� ������� ������� ���� ��� 
											��������� �� ��������� ������� �� ����� bResendExisting
			\param bResendExisting [in] true - �������� �� ����������� ������ ����� ��������� ������ 
											���� ���� � ������ ���� �������� ������� ����� ������� ���
											�������������
										false - ���� ������� ������� ���� ��� �����������, �� ��������� 
											������ ������������				
		*/
		virtual void UpdateClientsList( KLDB::DbConnectionPtr pDbConn,
			const std::wstring &fileId, 
			const HostsIdsList &hostsList,
			bool  bDeleteAbsent = false,
			bool  bResendExisting = false ) = 0;
		
		/*!
			\brief ��������� ����� ��������� �������� � ������ ��������
				��� ���������� �����
			
			\param fileId		[in]  ������������� �����
			\param hostsList	[in]  ������ ��������, ������� ���������� �������� ������ ����
		*/
		virtual void AddClientsToFile( KLDB::DbConnectionPtr pDbConn,
			const std::wstring &fileId, 
			const HostDescList &hostsList ) = 0;
		
		/*!
			\brief ��������� ������ �������� ��� ���������� �����
			
			\param fileId		[in]  ������������� �����
			\param hostsList	[in]  ������ ��������, ������� ���������� �������� ������ ����
			\param bDeleteAbsent [in]	true - ������� �� ����� �������� ������� ��� � ���������� 
											������. ��� ������� �������� ��� ��������� �������� 
											������������.
										false - ������ ����� ������� �� ������ ����� ��������� � 
											������ �������� �����. ���� ������� ������� ���� ��� 
											��������� �� ��������� ������� �� ����� bResendExisting
			\param bResendExisting [in] true - �������� �� ����������� ������ ����� ��������� ������ 
											���� ���� � ������ ���� �������� ������� ����� ������� ���
											�������������
										false - ���� ������� ������� ���� ��� �����������, �� ��������� 
											������ ������������				
		*/
		virtual void UpdateClientsList( KLDB::DbConnectionPtr pDbConn,
			const std::wstring &fileId, 
			const HostDescList &hostsList,
			bool  bDeleteAbsent = false,
			bool  bResendExisting = false ) = 0;


		/*!
			\brief ������������� ���������������� �������� ��� �����

			\param fileId		[in]  ������������� �����
			\param pParContext	[in]  ���������������� ��������
		*/
		virtual void SetFileUserContext( KLDB::DbConnectionPtr pDbConn,
			const std::wstring &fileId, 
			KLPAR::Params *pParContext ) = 0;

		/*!
			\brief ���������� ������ ��������������� ������� ������
		*/
		virtual void GetFilesList( std::vector<std::wstring> &filesIdsList ) = 0;

		/*!
			\brief ���������� ������ ���������� �� �����
			
			\param fleId		[in] ������������� �����
		*/
		virtual ServerFileDescription GetFileInfo( const std::wstring &fileId ) = 0;

		/*!
			\brief ������� �������� ������� ����� � ���������� ��� ������������� ��������

			\param fileId		[in] ������������� �����
		*/
		virtual void DeleteFile( KLDB::DbConnectionPtr pDbConn,
			const std::wstring &fileId ) = 0;

		/*!
			\brief �������� ���������� ���� �� ���������� ����			

			\param fileId		[in] ������������� �����
		*/
		virtual void SaveFileAs( const std::wstring &fileId,
			const std::wstring &copyFolderPath ) = 0;
		
		/*!
			\brief ���������� ���� �� ��� ������� ���������� ����� ��� ��������
		*/
		virtual bool HasNotSentFiles( int nHostId ) = 0;

		/*!
			\brief ������� ������� ���������� ��� ������� ���������� ����� ����������
			 � �������������� ������� �����
		*/
		virtual void InitiateRemoteConnectionAndSendSignal( const std::wstring &localConnName, 
				const std::wstring &remoteConnName, KLDB::DbConnectionPtr pCon,
				int nHostId, bool inPingHostMode = true ) = 0;
		
		/*!
			\brief ���������� ������ �� ��������� ���� ������� �������� �����

			\exception ERR_WRONG_FILE_ID
		*/
		virtual bool IsFileUploadingByHost( const std::wstring &fileId, const std::wstring &hostName ) = 0;

		/*!
			\brief ���������� ������ �������� ����� ��� ����������� ������ ����������

			\exception ERR_WRONG_FILE_ID
		*/
		virtual void GetFullFileInfo( const std::wstring &fileId, 
			const KLTRAP::Transport::ConnectionFullName &connFullName,
			KLPAR::Params **ppFileInfo ) = 0;
		
		/*
			\brief ������� �������� ������� ����� �� ������� ������ ����������. ������� ���������� �� ����
		*/
		virtual void CheckHostUpdateAgentStatus( KLDB::DbConnectionPtr pCon,
			const KLTRAP::Transport::ConnectionFullName &hostConnName,
			const int nHostId ) = 0;

		/*
			\brief ���������� ��������� ������ �����
		*/
		virtual int GetNextFileChunk( 
			const std::wstring &remoteClientName,
			const std::wstring &fileName, const std::wstring &fileId,
			unsigned long pos, unsigned long neededSize,
			unsigned long &fullFileSize,
			GetFileChunkParams &params,
			char **ppBuff, int &buffSize ) = 0;

		/*
			\brief ���������� ���������� � ������ � ����� Updater
		*/
		virtual void GetUpdaterFolderFileInfo( const std::wstring &fileName, 
			KLFT::FileInfo &r, const std::wstring &wstrNagentHostId ) = 0;

		/*!
			\brief ���������� ������ ������� ���������� ������� ������������� ��� ���������������
			 ���������� �����
			
			\param fileId		[in]  ������������� �����
			\param uaHostsList	[out]  ������ ������ ������� ����������
		*/
		virtual void GetFileUAList( const std::wstring &fileId, 
			HostsIdsList &uaHostsList ) = 0;

		/*!
			\brief ������������� ��������� ������� �������� ����������

			\param nCheckTaskId	[in]  ������������� ������ �������� ����������
			\param wstrReserveUpdatesFolder	[in]  ����� � ���������� ��������� ����������
		*/
		virtual void SetCheckUpdatesParams( long nCheckTaskId, 
			const std::wstring &wstrReserveUpdatesFolder ) = 0;

		

	};

} // end namespace FTS

/*
	\brief ������� ������������/��������������� ���������� �������� ������
*/
DECLARE_MODULE_INIT_DEINIT2( KLCSSRV_DECL, KLFTS );


/*\brief ���������� ��������� �� ���������� ������ ������ FileTransfer */
KLCSSRV_DECL KLFTS::FileTransferServer *KLFTS_GetFileTransferServer();


#endif // FTS_FILETRANSFERSERVER_H