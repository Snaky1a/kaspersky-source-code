/*!
 * (C) 2004 "Kaspersky Lab"
 *
 * \file FileDescription.h
 * \author ����� �����������
 * \date 2004
 * \brief �������� �������� �����
 * 
 */

#ifndef KLFT_FILEDESCRIPTION_H
#define KLFT_FILEDESCRIPTION_H

#include <std/base/klbase.h>
#include <kca/prci/componentid.h>
#include <transport/tr/transport.h>

namespace KLFT {

	class FileDescription
	{
	public:		

		FileDescription()
		{
			m_fileName.clear();// = L"";
			m_fileId.clear();// = L"";
			m_description.clear();// = L"";
			m_currentUploadPos = 0;
			m_operationTime = 0;
			m_fileSize = 0;
			m_isDirectory = false;
			m_maxNumberUploadingClients = 0;
		}

		FileDescription( const FileDescription &fd )
		{
			m_status			= fd.m_status;
			m_fileName			= fd.m_fileName;
			m_fileId			= fd.m_fileId;
			m_description		= fd.m_description;		
			m_operationTime		= fd.m_operationTime;		
			m_fileSize			= fd.m_fileSize;		
			m_currentUploadPos	= fd.m_currentUploadPos;		
			m_sentLocsList		= fd.m_sentLocsList;
			m_notSendLocsList	= fd.m_notSendLocsList;
			m_uploadLocsList	= fd.m_uploadLocsList;
			m_isDirectory		= fd.m_isDirectory;
			m_maxNumberUploadingClients = fd.m_maxNumberUploadingClients;
		}

		
		enum FileStatus{ Uploaded, Uploading, Sent, Sending, Delivered };
		
		/*!\brief ������ �������� ��������� ���������:
		
			��� �������:
			Uploading - ������ ������� ������ �  ������������� ������� ����� � ���������� ��� ��������
			Uploaded - ������ ��������� ������ ���� � ������ ������� ������ �� ��������� ������
		  
			��� �������:
			Sending	- ������ ���������� � �������� ������� �������� �������� ( ��� �� ��� ������� �������� ������� )
			Sent - ������ �������� ������� ���� ��������
			Delivered - ������ ���� ��� ������ ����� ��������� 
		*/
		FileStatus		m_status;			//! ������� ������ �����
		
		std::wstring	m_fileName;			//!	��� �����
		std::wstring	m_fileId;			//! ������������� �����, ��������������� �������� FT

		std::wstring	m_description;		//! �������� �����

		bool			m_isDirectory;		//! ������� �����������
		
		time_t			m_operationTime;	//! ����� �������� ������ �� �������� � ������ ������
		
		time_t			m_createFileTime;	//! ����� �������� �����
		
		unsigned long	m_fileSize;			//! ������ �����
		
		unsigned long	m_currentUploadPos;	//! ������� ������� �������� ������� ����� ( ��������� ��� ������� Uploading )
		
		int				m_maxNumberUploadingClients;	//! ������������ ���-�� �������� ��� ������������� �������
		
		KLTRAP::Transport::LocationExList	m_sentLocsList;			//! ������ ��������, ������� ���� ��������� ������� �� �������� ������� �����
		KLTRAP::Transport::LocationExList	m_notSendLocsList;		//! ������ ��������, ��� ������� ��� �� �������� ������� �� ��������
		
		KLTRAP::Transport::LocationExList	m_uploadLocsList;		//! ������ ��������, ������� ��� ������� ������ ����
	};

} // end namespace KLFT

#endif // !defined(KLFT_FILEDESCRIPTION_H)

