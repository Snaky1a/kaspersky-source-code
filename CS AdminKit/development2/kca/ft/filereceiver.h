/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file FileReceiver.h
 * \author ����� �����������
 * \date 2004
 * \brief ������� ��������� ��� ������� ������
 * 
 */

#ifndef KLFT_FILERECEIVER_H
#define KLFT_FILERECEIVER_H

#include <time.h>

#include <std/base/klbase.h>
#include <kca/ft/filetransferconst.h>

namespace KLFT {

	/*!
		\brief ������������ ������ ������ ��� �������
	*/
	const int c_MaxChunkSize = 32768;	// 32 Kb

	class KLSTD_NOVTABLE FileReceiver : public KLSTD::KLBase 
	{	
	public:
		
		/*!
			\brief ��������� ������ ������� Connect
		*/
		enum ConnectResult
		{
			CR_Ok,					//!< ���������� ������������ �������
			CR_ServerBusy,			//!< ������ �� ������ ������ ����� � �� ����� ������������ ������� �� �������
			CR_ConnectionError		//!< ������ ����������� ����������� � �������
		};

		/*!
			\brief ��������� ������ ������� GetFileChunk
		*/
		enum FileChunkResult
		{
			FC_Ok,					//!< ������ ����� ������� ��������
			FC_OkDownloaded,		//!< ������ ����� ������� �������� � ��� ���� ��������� ������ ������� �����
			FC_WrongArguments,		//!< �������� �������� �������
			FC_FileNotFound,		//!< ���� � ������ ������ �� ������
			FC_Timeout,				//!< timeout
			FC_ErrorInOperation		//!< ������ ��� ������� ��������� ������ �����			
		};

	public:

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
			\brief ������� ��������� ���������� ��� �������������
		*/
		virtual void SetConnectParam( const std::wstring &localConnName,
			const std::wstring &remoteConnName ) = 0;

		/*!
			\brief ���������� ���������� � �����

			\return false - ���� � ������ ������ �� ������
		*/
		virtual bool GetFileInfo( const std::wstring &fileName,
			FileInfo &fileInfo ) = 0;

		/*!
			\brief ���������� � ������� ������ �����

			\param fileName [in] ��� �����
			\param startPos [in] ������� ����� � ������� ���������� ��������� ������			
			\param chunkBuff [in,out] ����� ��� ������ ����� 
			\param chunkBuffSize [in] P����� ���������� ������
			\param receivedChunkSize [out] ������ ���������� ������

			\return FileChunkResult - ��������� ������ �������
				FC_WrongArguments - ������������ � ��������� �������:
						chunkBuff == NULL
						chunkBuffSize = 0
						startPos < 0 ��� startPos ������� �� ������� �����
		*/
		virtual FileChunkResult GetFileChunk( const std::wstring &fileName,
			long startPos, void *chunkBuff, int chunkBuffSize,  int &receivedChunkSize ) = 0;

		/*!
			\brief �������� �������� �� ������� �������������� �����
		*/
		virtual bool StartFileReceiving( const std::wstring &fileName ) = 0;

		/*!
			\brief ���������� � ������� ������ �������� ����� ( ������� ���� ��������������� 
				�������� StartFileReceiving )
			\params ��. ������� GetFileChunk
		*/
		virtual FileChunkResult GetCurrentFileChunk( void *chunkBuff, int chunkBuffSize,  
			int &receivedChunkSize ) = 0;

		/*!
			\brief ��������� ���������� � ��������
		*/
		virtual void Disconnect() = 0;
	};	

} // end namespace KLFT

/*\brief ������� ������ ������ FileReceiver */
KLCSNAGT_DECL void KLFT_CreateFileReceiver( KLFT::FileReceiver **ppFileReceiver );

#endif // !defined(KLFT_FILERECEIVER_H)
