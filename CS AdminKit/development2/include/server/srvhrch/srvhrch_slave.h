/*!
 * (C) 2005 "Kaspersky Lab"
 *
 * \file srvhrch/srvhrch_slave.h
 * \author Andrew Lashenkov
 * \date	20.01.2005 10:32:00
 * \brief ��������� ������������ ������� � �������� ��������.
 *
 */

#ifndef KLSRVH_SRVHRCH_SLAVE_H
#define KLSRVH_SRVHRCH_SLAVE_H

#include <srvp/srvhrch/srvhrch.h>
#include <std/par/params.h>
#include <server/srvinst/connstore.h>

namespace KLSRVH {

	class SrvHierarchySlave : public KLSTD::KLBaseQI {
	public:
		virtual ~SrvHierarchySlave(){}
	/*!
	  \brief Ping.

		\param pParams	[in] ������������ ��������� �����.
	*/
		virtual void PingSlave(						
			KLSTD::CAutoPtr<KLPAR::Params> pParams,
			KLSTD::CAutoPtr<KLPAR::Params>& pOutParams) = 0;
		
	/*!
	  \brief ForceRetranslateUpdates.

		\param pParams	[in] ������������ �������������� ��������� ������������.
	*/
		virtual bool ForceRetranslateUpdates(						
			KLSTD::CAutoPtr<KLPAR::Params> pParams) = 0;
	/*!
	  \brief ����������� ������ ��������� ���������, ����������� �� FT.

		\param wstrPackageGUID [in] - GUID ������
		\param wstrNewPackageName [in] - �������������� ��� ������
		\param wstrFileId [in] - ������������� ����� � FT
		\param wstrProductName [in] - ��� �������� � ������������
		\param wstrProductVersion [in] - ������ �������� � ������������
		\param wstrProductDisplName [in] - ���������� ��� �������� � ������������
		\param wstrProductDisplVersion [in] - ���������� ������ �������� � ������������
	*/
		virtual bool RecreateInstallationPackage(						
			const std::wstring& wstrPackageGUID,
			const std::wstring& wstrNewPackageName,
			const std::wstring& wstrFileId,
			const std::wstring& wstrProductName,
			const std::wstring& wstrProductVersion,
			const std::wstring& wstrProductDisplName,
			const std::wstring& wstrProductDisplVersion,
			bool bReplaceExisting,
			std::wstring& wstrCreatedPackageName) = 0;

	/*!
	  \brief ������ ������ �� ����������� �������.

		\param wstrTaskTsId [in] - ������������� ������
		\param wstrTaskTypeName [in] - ��� ������
		\param parParams [in] - ������������ ���������
		\param parOutParams [out] - ������������ ���������
	*/
		virtual void StartTask(						
			const std::wstring& wstrTaskTsId,
			const std::wstring& wstrTaskTypeName,
			KLSTD::CAutoPtr<KLPAR::Params> parParams,
			KLSTD::CAutoPtr<KLPAR::Params>& parOutParams) = 0;
		
	/*!
	  \brief ������ ������ ��������� ���������.

		\param parTaskInfo [in] - parTaskInfo �������� ������
		\param parTaskParams [in] - parTaskParams �������� ������
		\return ��������� ��������. false - ����� ����������� �� ������ �������
	*/
		virtual bool StartRemoteInstallation(
			KLSTD::CAutoPtr<KLPAR::Params> parTaskInfo,
			KLSTD::CAutoPtr<KLPAR::Params> parTaskParams,
			bool& bAlreadyInstalledSkipped) = 0;
	};
	
} // namespace KLSRVH

KLCSSRV_DECL void KLSRVH_CreateSrvHierarchySlaveProxy(
	KLSTD::CAutoPtr<KLSRV::ConnectionInfo> pConnectionInfo, 
	KLSRVH::SrvHierarchySlave** ppSrvHierarchySlaveProxy);

#endif // KLSRVH_SRVHRCH_SLAVE_H

