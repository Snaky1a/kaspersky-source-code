/*!
* (C) 2005 "Kaspersky Lab"
*
* \file filetransferbridge.h
* \author ����������� �����
* \date 2005
* \brief ��������� ������ ��� �������������� ��������� � FileTransfer'�� �������� ������
		������ ��������� ��������� ���������� ����� ���������� � ������� �����������������.

		����� ������: FileTransferBridge ����������� � ������� �������, ������� ���������� ��� 
		������� � ������� ����������������
*/

#ifndef KLFT_FILETRANSFERBRIDGE_H
#define KLFT_FILETRANSFERBRIDGE_H

#include <wchar.h>

namespace KLFT {

	/*!
		\brief ��������� ������ ������� Connect
	*/
	enum ConnectResult
	{
		CR_Ok,						//!< ���������� ������������ �������
		CR_WrongReceiverId,			//!< �������� ������������� ( ���� ������, ���� ��� ������� receiver'� ��� ��� ������ connect )
		CR_ServerBusy,				//!< ������ �� ������ ������ ����� � �� ����� ������������ ������� �� �������
		CR_ConnectionError,			//!< ������ ����������� ����������� � �������
		CR_ConnectionNagentError,	//!< ������ ����������� ����������� � �������� ������
		CR_ConnectionServerError	//!< ������ ����������� ����������� � �������� �������
	};
	
	/*!
		\brief ��������� ������� ������ � �������
	*/
	enum FileOpeartionResult
	{
		FR_Ok,					//!< ������ ����� ������� ��������
		FR_WrongReceiverId,		//!< �������� ������������� ( ���� ������, ���� ��� ������� receiver'� ��� ��� ������ connect )
		FR_OkDownloaded,		//!< ������ ����� ������� �������� � ��� ���� ��������� ������ ������� �����
		FR_WrongArguments,		//!< �������� �������� �������
		FR_FileNotFound,		//!< ���� � ������ ������ �� ������
		FR_Timeout,				//!< timeout
		FR_ErrorInOperation		//!< ������ ��� ������� ��������� ������ �����			
	};
	
	class FileTransferBridge
	{
	public:

		/*!
			\brief ��������� �������� �����
		*/
		struct FileInfo
		{			
			bool			m_isDirectory;
			bool			m_readPermissionOk;
			time_t			m_createTime;
			long			m_fileSize;
		};

		/*!
			\brief ������� ���������� ����������� � ������� �����������������
		*/
		virtual ConnectResult Connect() = 0;

		/*!
			\brief ������� ���������� ����������� �� ������������ ������� � ��������
				������� �����������������
		*/
		virtual ConnectResult ConnectToMasterServer() = 0;

		/*!
			\brief ���������� ���������� � �����

			\return false - ���� � ������ ������ �� ������
		*/
		virtual FileOpeartionResult GetFileInfo( const wchar_t *fileName,
			FileInfo &fileInfo ) = 0;

		/*!
			\brief ���������� � ������� ������ �����

			\param fileName [in] ��� �����
			\param startPos [in] ������� ����� � ������� ���������� ��������� ������			
			\param chunkBuff [in,out] ����� ��� ������ ����� 
			\param chunkBuffSize [in] P����� ���������� ������
			\param receivedChunkSize [out] ������ ���������� ������

			\return FileChunkResult - ��������� ������ �������
		*/
		virtual FileOpeartionResult GetFileChunk( const wchar_t *fileName,
			long startPos, void *chunkBuff, int chunkBuffSize,  int &receivedChunkSize ) = 0;

		/*!
			\brief ��������� ���������� � ��������
		*/
		virtual void Disconnect() = 0;

	};

} // end namespace KLFT


/*!
	\brief ������� ������� ��������� ������ FileTransferBridge, ������� ����� �������������
	���������� ���������� �������� KLFT_ReleaseFileTransferBridge
*/
void KLFT_CreateFileTransferBridge( KLFT::FileTransferBridge **ppBridge );

/*!
	\brief ������� ����������� ��������� ������ FileTransferBridge
*/
void KLFT_ReleaseFileTransferBridge( KLFT::FileTransferBridge **ppBridge );

#endif // KLFT_FILETRANSFERBRIDGE_H
