/*!
 * (C) 2004 "Kaspersky Lab"
 *
 * \file srvhrch/srvhrch_lst.h
 * \author Andrew Lashenkov
 * \date	24.12.2004 18:54:00
 * \brief ��������� ������ ����������� ��������.
 *
 */

#ifndef KLSRVH_SRVHRCH_LST_H
#define KLSRVH_SRVHRCH_LST_H

#include <srvp/srvhrch/srvhrch.h>
#include <std/base/klbase.h>
#include <std/par/params.h>

namespace KLSRVH {

	class KLSTD_NOVTABLE ChildServers : public KLSTD::KLBaseQI {
	public:
	/*!
	  \brief ���������� ������ ����������� ��������.

		\param nGroupId			[in] ������, ��� ������� ������������� ������ ����������� ��������; 
									GROUPID_INVALID_ID ��� ������ �� ���� �������.
		\param servers			[out] ������ ����������� ��������.
	*/
		virtual void GetChildServers(
			long nGroupId,
			std::vector<child_server_info_t>& vecServers) = 0;

	/*!
	  \brief ���������� ���������� � ����������� ������� �� ��� ��������������.

		\param nId		[in] ������������� �������.
		\param fields	[in] ������ �����, ������� ��������� ��������.
		\param size		[in] ����� ����� � ������ fields.
		\param info		[out] ���������� � �������.
		
		  \exception STDE_NOTFOUND ��������� ������ �� ������
   
	*/
		virtual void GetServerInfo(
			long nId,
			const wchar_t**	fields,
			int size,
			KLPAR::Params** info) = 0;

	/*!
	  \brief ���������� ���������� � ����������� ������� �� wstrInstanceId.

		\param wstrInstanceId	[in] wstrInstanceId.
		\param fields			[in] ������ �����, ������� ��������� ��������.
		\param size				[in] ����� ����� � ������ fields.
		\param info				[out] ���������� � ����������.
		
		  \exception STDE_NOTFOUND ��������� ������ �� ������
   
	*/
		virtual void GetServerInfoByInstanceId(						
			const std::wstring& wstrInstanceId,
			const wchar_t**		fields,
			int					size,
			KLPAR::Params**     info) = 0;

	/*!
	  \brief ���������� ���������� � ����������� ������� �� MD5-hash �����������.

		\param wstrPublicKeyHash	[in] MD5-hash ���������� ����� �����������.
		\param fields				[in] ������ �����, ������� ��������� ��������.
		\param size					[in] ����� ����� � ������ fields.
		\param info					[out] ���������� � ����������.
		
		  \exception STDE_NOTFOUND ��������� ������ �� ������
   
	*/
		virtual void GetServerInfoByPublicKeyHash(			
			const std::wstring& wstrPublicKeyHash,
			const wchar_t**		fields,
			int					size,
			KLPAR::Params**     info) = 0;

	/*!
	  \brief ������������ ����� ����������� ������ ��� �������� ������.

		\param wstrDisplName	[in] ������������ ��� �������.
		\param wstrNetAddress	[in] ������� ����� �������.
		\param nGroupId			[in] ������������� ������, � ������� ������� ������ ������.
		\param pAdditionalInfo	[in] ���. ���������� � ����������� �������.

		  \return ������������� ������������ �����

		  \exception STDE_OBJ_EXISTS - ����������� ������ � ����� ������ ��� ���������������.
	*/
		virtual long RegisterServer(
			const std::wstring& wstrDisplName,
			long nGroupId,
			void* pCertificate,
			long nCertificateLen,
			const std::wstring& wstrNetAddress,
			KLSTD::CAutoPtr<KLPAR::Params> pAdditionalInfo) = 0;
		
	/*!
	  \brief ������� ����������� ������.

		\param nId [in] ������������� �������.
   
	*/
		virtual void DelServer(long nId) = 0;

	/*!
	  \brief ��������� ���������� � ����������� �������.

		\param nId		[in] ������������� �������.
		\param pInfo	[in] ���������� � ����������.
			
		  \exception STDE_NOTFOUND - ������ �� ������.
		  \exception STDE_OBJ_EXISTS - ����������� ������ � ����� ������ ��� ���������������.
   
	*/
		virtual void UpdateServer(
			long nId,
			KLSTD::CAutoPtr<KLPAR::Params> pInfo ) = 0;


//		/*!
//		  \brief    ��������� ������������� ���������� � ��������� wstrSSType
//					���������. ����� ����������, �.�. ����� �� ����������
//					���������� �� ��� ���, ���� �� ���������� ����� ��
//					��������� �������: ������������� �� ������ ��
//					����� ��� ��� �� ��������� ������.
//
//		  \param    nId [in] - ������������� ������������ �������.
//		  \param    wstrSSType [in] - ������������� ��������� (������ ������
//						��������, ��� ��������� �������� ������������� ��� ����
//						��������)
//		  \param    lWaitTimeout [in] - ������������ ����� �������� � �� - �����
//						������� ����
//		  \param    bCancelWait [in] - ������ � ����������, �� ������� ���������
//						������ ���������, �������� true �������� � ����������
//						�������� ���������� � ������������ ����������
//						STDE_CANCELED.
//
//		    \exception    KLSTD::STDE_CANCELED - �������� ���� ��������
//		    \exception    KLSTD::STDE_TIMEOUT - ���� ������� lWaitTimeout
//		    \exception    KLSRV::KLSRV_ERR_NO_HOST_ADDRESS - ������� ���������� ����� �����.
//		    \exception    KLSRV::KLSRV_ERR_HOST_NOT_RESPONDING - ���� �� ��������
//		*/
//		virtual void ForceSynchronizationSync(
//						long					nId,
//						const std::wstring&     wstrSSType,
//						long                    lWaitTimeout,
//						volatile bool*          bCancelWait=NULL) = 0;
	};
};

namespace KLSRV{
	class ConnectionInfo;
};

KLCSSRVP_DECL void KLSRVH_CreateChildServersProxy(
	KLSTD::CAutoPtr<KLSRV::ConnectionInfo> pConnectionInfo, 
	KLSRVH::ChildServers** ppChildServersProxy);

#endif // KLSRVH_SRVHRCH_LST_H
