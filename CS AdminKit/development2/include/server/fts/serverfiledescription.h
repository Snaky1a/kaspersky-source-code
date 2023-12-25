/*!
 * (C) 2004 "Kaspersky Lab"
 *
 * \file ServerFileDescription.h
 * \author ����� �����������
 * \date 2004
 * \brief �������� �������� �����
 * 
 */

#ifndef KLFT_SERVERFILEDESCRIPTION_H
#define KLFT_SERVERFILEDESCRIPTION_H

#include <std/base/klbase.h>
#include <kca/prci/componentid.h>
#include <transport/tr/transport.h>

namespace KLFTS {

	struct HostDesc
	{
		HostDesc()
		{
			nHostId = (-1);
		}
		
		std::wstring	strHostName;
		std::wstring	strHostConnectionName;
		std::wstring	strHostDisplayName;		
		int				nHostId;
		
		bool operator == (const std::wstring &hostName ) const
        {
			return (strHostName==hostName);
        };
		
		bool operator == (const int &hostId ) const
        {
			return (nHostId==hostId);
        };
	};

	typedef std::vector<HostDesc> HostDescList;

	typedef std::list<int>						HostsIdsList;

	class ServerFileDescription
	{
	public:
		

		ServerFileDescription()
		{
			m_fileName = L"";
			m_fileId = L"";
			m_description = L"";
			m_currentUploadPos = 0;
			m_operationTime = 0;
			m_fileSize = 0;
			m_isDirectory = false;
			m_maxNumberUploadingClients = 0;
		}

		ServerFileDescription( const ServerFileDescription &fd )
		{
			m_status			= fd.m_status;
			m_fileName			= fd.m_fileName;
			m_fileId			= fd.m_fileId;
			m_description		= fd.m_description;		
			m_operationTime		= fd.m_operationTime;		
			m_fileSize			= fd.m_fileSize;		
			m_currentUploadPos	= fd.m_currentUploadPos;		
			m_sentHostsList		= fd.m_sentHostsList;
			m_notSendHostsList	= fd.m_notSendHostsList;
			m_uploadHostsList	= fd.m_uploadHostsList;
			m_isDirectory		= fd.m_isDirectory;
			m_maxNumberUploadingClients = fd.m_maxNumberUploadingClients;
			m_notSendUAList		= fd.m_notSendUAList;
			m_pParContext		= fd.m_pParContext;
		}

		
		enum FileStatus{ Uploaded, Uploading, Sent, Sending, Delivered, NotStartUploading };
		
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
		
		HostDescList	m_sentHostsList;	//! ������ ������, ������� ���� ��������� ������� �� �������� ������� �����
		HostDescList	m_notSendHostsList;	//! ������ ������, ��� ������� ��� �� �������� ������� �� ��������
		
		HostDescList	m_uploadHostsList;	//! ������ ������, ������� ��� ������� ������ ����

		HostDescList	m_notSendUAList;	//! ������ ������ UA, ��� ������� ��� �� �������� ������� �� ��������

		KLSTD::CAutoPtr<KLPAR::Params>	m_pParContext;	//! ���������������� �������� �����
	};

} // end namespace KLFTS

#endif // !defined(KLFT_SERVERFILEDESCRIPTION_H)

