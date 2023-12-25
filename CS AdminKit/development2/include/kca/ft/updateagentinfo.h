/*!
* (C) 2005 "Kaspersky Lab"
*
* \file updateagentinfo.h
* \author ����������� �����
* \date 2005
* \brief ��������� 
*
*/

#ifndef KLFT_UPDATEAGENTINFO_H
#define KLFT_UPDATEAGENTINFO_H

#include <std/base/klbase.h>
#include <std/err/klerrors.h>

namespace KLFT {

	struct UpdateAgentInfo
	{		
		UpdateAgentInfo()
		{
			nAgentHostId = (-1);
		}

		UpdateAgentInfo( const UpdateAgentInfo &uai )
		{
			nAgentHostId = uai.nAgentHostId;
			strAgentHostId = uai.strAgentHostId;
			strAgentHostDisplayName = uai.strAgentHostDisplayName;
			nGroupId = uai.nGroupId;
			strConnName = uai.strConnName;
			strAddress = uai.strAddress;
			strNonSSLAddress = uai.strNonSSLAddress;
			strMulticastAddr = uai.strMulticastAddr;
			pCertificate = uai.pCertificate;
			strCertPswd = uai.strCertPswd;
		}


		int nAgentHostId;	// ������������� �����, ������� ����� ������������� � �������� ������ ���������� ( UA )
		std::wstring strAgentHostId;	// ��������� ������������� �����
		std::wstring strAgentHostDisplayName;// ������ ��� ����������� �������� �����

		int nGroupId;		// ������������� ������, ����� �� ������� ������ UA ����� ����������� 
							// ( ���� � ������� ����������� UA ������� nGroupId < 0 �� ����� ������������ ������ ������� ��������� UA )
		std::wstring strConnName;	// ������������ ���
		std::wstring strAddress;	// TCP/IP ������ UA ( ���� � ������� ����������� UA �������� ������ ������, 
					// �� ����� ����������� ����� �������� � �������� ������� ����� + ���� 13000 )
		std::wstring strNonSSLAddress;	// TCP/IP ������ UA ( ���� � ������� ����������� UA �������� ������ ������, 
					// �� ����� ����������� ����� �������� � �������� ������� ����� + ���� 13000 )
		std::wstring strMulticastAddr; // Multicast ����� �������� ( ���� �������� ������ ������,
					// �� ������ ����� �������� ������������� )
		KLSTD::CAutoPtr<KLSTD::MemoryChunk> pCertificate;		// [in] ����������, ������� ����� ������������ ��� ������� 
					// ������� �������� � ��� �������� ����������� 
					// ( ���� � ������� ����������� UA ������� NULL �� ���������� ����� ������������ ������ ������� ����������� UA )
		std::wstring strCertPswd;	// ������ �����������
	};

	struct UpdateAgentLocation
	{
		std::wstring strConnectionName;
		std::wstring strLocation;
		std::wstring strSSLLocation;
		std::wstring strMulticastAddr;
	};

	typedef std::vector<UpdateAgentLocation> UpdateAgentLocationList;

	typedef std::vector<UpdateAgentInfo> UpdateAgentInfoList;
	

	struct UpdateAgentStatistics
	{
		UpdateAgentStatistics()
		{			
			time(&tCreateTime);

			nNumberOfFiles = 0; 
			nSizeOfFiles = 0;
		
			nSuccededUploads = 0;
			nSuccededUploadsSize = 0;

			nTCPUploadedSize = nMulticastUploadedSize = 0;

			nMulticastSentSize = 0;

			tFolderSyncLastServerSyncTime = 0;
			nFolderSyncServerSyncCount = 0;

			nFolderSyncMulticastSentCount = 0;
			nFolderSyncMulticastSentSize = 0;

			nFolderSyncTCPUploadedSize = 0;
			nFolderSyncTCPUploadedCount = 0;
		}
		
		time_t			tCreateTime;					// ����� �������� ������ ����������

		//////////////// ��������� ���������� ////////////////
		long			nNumberOfFiles;					// ����� ����� ������, ����������� ��� ��������������� ����� ������ ����������
		AVP_longlong	nSizeOfFiles;					// ����� ������ ������
		
		long			nSuccededUploads;				// ����� ����� �������� ������� � ������� ������ ����������
		AVP_longlong	nSuccededUploadsSize;			// �������� ������ �������� �������

		AVP_longlong	nTCPUploadedSize;				// ������ ���������� ���������� �� TCP/IP
		AVP_longlong	nMulticastUploadedSize;			// ������ ���������� ���������� �� ��������� Multicast

		AVP_longlong	nMulticastSentSize;				// ������ ���������� �� multicast ����������

		long			nPercentUsageMulticast;			// ���� ���������� ���������� �������� �� ��������� multicast
		//////////////// 

		//////////////// ������������ ���� //////////////// 
		time_t			tFolderSyncLastServerSyncTime;	// ����� ��������� ������������� � ��������
		long			nFolderSyncServerSyncCount;		// ���-�� ������������� ����� � ��������

		long			nFolderSyncMulticastSentCount;	// ����� ���-�� multicast ��������
		AVP_longlong	nFolderSyncMulticastSentSize;	// ������ multicast �������� ��� ������������� ����� ( ���������� )		

		AVP_longlong	nFolderSyncTCPUploadedSize;		// ������ TCP ������� ��� ������������� ����� ( ���������� )
		long			nFolderSyncTCPUploadedCount;	// ���-�� ������������� � �������� 
		long			nFolderSyncPercentUsageMulticast;	// ���� ���������� ���������� �������� �� ��������� multicast ��� ������������� ������������ ���
		//////////////// 
		
	};

} // end namespace KLFT

#endif // KLFT_UPDATEAGENTINFO_H
