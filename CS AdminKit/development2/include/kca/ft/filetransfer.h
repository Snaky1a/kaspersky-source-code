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
#include "filetransferconst.h"
#include "updateagentinfo.h"

namespace KLFT {


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
			const std::wstring &hostId,
			KLPAR::BinaryValue *pSer,
			TransferConnectionInvoker *connectionInvoker ) = 0;
		
		/*!
			\brief ��������� ���������� ���������� ��� ������������ �������������		 	
		*/
		virtual void SetClientInfo( KLPAR::BinaryValue *pSer, std::wstring &hostId ) = 0;

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
			\brief �������������� ������ �������� ��� ���������� �����
			
			\param fileId		[in]  ������������� �����
			\param locsList		[in]  ������ ��������, ������� ���������� �������� ������ ����
		*/
		virtual void ReplaceClientsList( const std::wstring &fileId, 
			const KLTRAP::Transport::LocationExList &locsList ) = 0;		
		
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
			const std::wstring &copyFolderPath,
			bool overwrite = false ) = 0;

		/*!
			\brief ���������� ��������� ������������ ��� FileTransfer'�
		*/
		virtual void GetLocalConnectionName( std::wstring &localName ) = 0;

		/*!
			\brief ���������� ������� ���������� FileTransfer'�
		*/
		virtual void GetWorkingFolder( std::wstring &workingFolder ) = 0;
		
		/*!
			\brief ���������� ���� �� ��� ������� ���������� ����� ��� ��������
		*/
		virtual bool HasNotSentFiles( const std::wstring &remoteName ) = 0;

		/*!
			\brief ������� ������� ���������� ��� ������� ���������� ����� ����������
			 � �������������� ������� �����
		*/
		virtual void InitiateRemoteConnectionAndSendSignal( const std::wstring &localConnName, 
				const std::wstring &remoteConnName, 
				const std::wstring &remoteName ) = 0;
		
		/*!
			\brief ���������� ������ �� ��������� ���� ������� �������� �����

			\exception ERR_WRONG_FILE_ID
		*/
		virtual bool IsFileUploadingByHost( const std::wstring &fileId, const std::wstring &remoteName ) = 0;
		
		/*!
			\brief ���������� ����������� ������ ������ ����������

			\param	uaStat	[out] ����������	
			\return false -	������ ���� �� �������� ������� ����������
		*/
		virtual bool GetUpdateAgentStatistics( UpdateAgentStatistics &uaStat ) = 0;

		/*
			\brief ���������� ������ listener ������ ������������ UpdateAgent'��
		 */
		virtual void GetUsingListenersPostsList( std::vector<int> &vecTCPPortsList,
			std::vector<int> &vecUDPPortsList ) = 0;
		
		/*
			\brief ������� �������� ������� ������ ���������� �� �������
		*/
		virtual void CheckUpdateAgentStatus( const KLTRAP::Transport::ConnectionFullName &serverConnName ) = 0;
		
		/*
			\brief ������� ��������� ������ FT �� ��������� ��������� ���������� �� �������
		*/
		virtual void SwitchToReserveUpdaterFolder( const std::wstring &wstrNagentHostId ) = 0;

		/*
			\brief ���������� ��������� ������ � ��������� ���������� ����������
		*/
		virtual void IsReserveUpdaterFolderActivated( bool &bUseReserveUpdate, 
			std::wstring &wstrNagentHostId ) = 0;
	};		

	KLCSKCA_DECL void ConnectToServer( const std::wstring &localName, std::wstring &serverRemoteName );

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

/*
	\brief ������� ������������/��������������� ����������
*/
DECLARE_MODULE_INIT_DEINIT2( KLCSKCA_DECL, KLFTBRIDGE );

/*\brief ���������� ��������� �� ���������� ������ ������ FileTransfer */
KLCSKCA_DECL KLFT::FileTransfer *KLFT_GetFileTransfer();


#endif // !defined(KLFT_FILETRANSFER_H)
