/*!
* (C) 2005 "Kaspersky Lab"
*
* \file filetransferconst.h
* \author ����������� �����
* \date 2005
* \brief ��������� ���������� �������� ������
*
*/

#ifndef KLFT_FILETRANSFERCONST_H
#define KLFT_FILETRANSFERCONST_H

#include <std/base/klbase.h>
#include <std/err/klerrors.h>

namespace KLFT {
	
	const int c_UploadDelay					= 6000;		// 6 secs 
	const int c_NextChunkTimeout			= 1000;		// 1 secs	
	const int c_NextChunkTimeoutAddDelta	= 3000;		// 3 secs	
	const int c_MaxChunkTimeout				= 30000;	// 60 secs
	
	const int c_MulticastStartUploadingDelay	=  20;	// 20 secs
	const int c_UpdateAgentStartUploadingDelay	=  10;	// 10 secs

	const int c_UploadAfterMulticastTimeout	= 30;	// 30 secs

	const int c_DefaultChunkSize	= 98304;		// 32*3~100 Kb

	const int c_defaultUploadingClients	= 10;

	const wchar_t c_FileTransferTempDir[]	= L"/temp";
	
	/*!
			\brief ��������� �������� �����
	*/
	struct FileInfo
	{
		std::wstring	m_fileName;
		bool			m_isDirectory;
		bool			m_readPermissionOk;
		time_t			m_createTime;
		long			m_fileSize;
	};

	enum FileType
	{
		FT_None = 0,
		FT_Simple,
		FT_Custom,
		FT_Updater,
		FT_Package,
		FT_SyncArchive,
		FT_Folder,		
		FT_FolderEndPoint,
		FT_CustomServerUploaded
	};
	
	enum UploadingType
	{
		UT_None = 0,
		UT_ForUpdateAgentOnly = 1,
		UT_ForHostUploadingOnly = 2,
		UT_ForUpdateAgentAndHost = 3
	};
	
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

	const wchar_t EVENT_TYPE_START_HOST_FILE_UPLOAD[]	= L"KLFT_StartHostFileUpload";		// ���� ����� ������� ����� � �������
	const wchar_t EVENT_TYPE_HOST_FILE_UPLOADED[]		= L"KLFT_HostFileUploaded";			// ���� �������� ������� ����� � �������
	const wchar_t EVENT_TYPE_HOST_FILE_PROGRESS[]		= L"KLFT_HostFileProgress";			// ������� � ������� ��������� ������ ����� ������

	// ������� �� ��������� ������ ������ ������������ ��� ������ ������ ����������
	// ��������� �� ���������� � ������ c_FileTransferComponentName + ������ � ������� �������� �������� ������
	const wchar_t EVENT_TYPE_USING_LISTENERS_PORTS_LIST_CHANGED[]	= L"KLFT_UsingPortsChanged";
	
	/*!
    * \brief ���� �������
    */

	const wchar_t EVENT_BODY_FILE_ID[]					= L"KLFT_FileId";					// ������������� ����� 
	const wchar_t EVENT_BODY_REMOTE_HOST_NAME[]			= L"KLFT_RemoteHostName";			// ��� �����	
	const wchar_t EVENT_BODY_UPLOAD_PERCENT[]			= L"KLFT_UploadPercent";			// ������� �������� �����
	const wchar_t EVENT_BODY_UPLOAD_DELAY[]				= L"KLFT_UploadDelay";				// (�����������) ������������ ����� �������� �������� ����� ( � ��� )

	/*!
	* \brief ��������� ��������������
	*/
	const wchar_t UPDATE_AGENT_HOST_ID[]				= L"KLFT_UAHostId";
	const wchar_t UPDATE_AGENT_CONN_NAME[]				= L"KLFT_UAConnName";
	const wchar_t UPDATE_AGENT_NON_SSL_ADDR[]			= L"KLFT_UANonSSLAddr";
	const wchar_t UPDATE_AGENT_GROUP_ID[]				= L"KLFT_UAGroupId";
	const wchar_t UPDATE_AGENT_CERTIFICATE[]			= L"KLFT_UACert";
	const wchar_t UPDATE_AGENT_CERTIFICATE_PSWD[]		= L"KLFT_UACertPswd";

	const wchar_t SER_FILE_ID[]							= L"FileId";
	const wchar_t SER_MAX_CLIENT[]						= L"MaxClients";
	const wchar_t SER_CREATE_TIME[]						= L"CreateTime";
	const wchar_t SER_HOSTS_DESCS[]						= L"Hosts";
	const wchar_t SER_HOST_NAME[]						= L"HostName";
	const wchar_t SER_HOST_ID[]							= L"HostId";
	const wchar_t SER_HOST_STR_ID[]						= L"HostStrId";
	const wchar_t SER_HOST_CONN_NAME[]					= L"ConnName";
	const wchar_t SER_HOST_DISPLAY_NAME[]				= L"DisplayName";

	const wchar_t SER_UA_CERT_PSWD[]					= L"B20670EF-FFC2-4f66-AAC5-1690BA56624C-FT";
	
	/*!
	* \brief ��������� multicast ��������
	*/
	const wchar_t SER_MC_FILE_ID[]						= L"MCFileId";
	const wchar_t SER_MC_FILE_NAME[]					= L"MCFileName";
	const wchar_t SER_MC_FOLDER_NAME[]					= L"MCFolderName";
	const wchar_t SER_MC_FULL_SIZE[]					= L"MCFileFullSize";
	const wchar_t SER_MC_CHUNK_POS[]					= L"MCChunkPos";
	const wchar_t SER_MC_CHUNK_SIZE[]					= L"MCChunkSize";
	const wchar_t SER_MC_CHUNK_CRC[]					= L"MCChunkCRC";
	const wchar_t SER_MC_CHUNK_DATA[]					= L"MCChunkData";

	/*!
	* \brief ��������� ��� ����� �������������
	*/
	const wchar_t SYNC_FOLDER_NAME_UPDATE[]				= L"ft-updater-sync-folder";
	
} // end namespace KLFT

#endif // KLFT_FILETRANSFERCONST_H
