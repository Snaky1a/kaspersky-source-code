/*!
 * (C) 2005 "Kaspersky Lab"
 *
 * \file srvhrch/srvhrch_master.h
 * \author Andrew Lashenkov
 * \date	20.01.2005 10:16:00
 * \brief ��������� ������-������� �������� ��������.
 *
 */

#ifndef KLSRVH_SRVHRCH_MASTER_H
#define KLSRVH_SRVHRCH_MASTER_H

#include <srvp/srvhrch/srvhrch.h>
#include <std/par/params.h>
#include <server/srvinst/connstore.h>

namespace KLSRVH {

	class SrvHierarchyMaster : public KLSTD::KLBaseQI {
	public:
		virtual ~SrvHierarchyMaster(){}
	/*!
	  \brief ������������� ��� ������������ ������� ��� InstanceId �� ���������� ���������.

		\param pParams	[in] � c_srv_instance_id �������� InstanceId ������������ �������.
	*/
		virtual void InitialPingMaster(						
			KLSTD::CAutoPtr<KLPAR::Params> pInParams,
			KLSTD::CAutoPtr<KLPAR::Params>& pOutParams) = 0;

	/*!
	  \brief Ping.

		\param pParams	[in] ������������ ��������� �����.
	*/
		virtual void PingMaster(						
			KLSTD::CAutoPtr<KLPAR::Params> pInParams,
			KLSTD::CAutoPtr<KLPAR::Params>& pOutParams) = 0;

	/*!
	  \brief �������� ����������� ������ � ������������ �������.

		\param wstrRequestId			[in] - ������������� �������;
		\param nRecipientDeliverLevel	[in] - ����� �������, �� ������� ����� �������� ������;
		\param nSenderDeliverLevel		[in] - ������� ����������� �������;
		\param wstrSenderInstanceId		[in] - ������������� �������;
		\param parDeliveryParams		[in] - �������������� ��������� ��������;
		\param parReportResult			[in] - ������ ������
	*/
		virtual void DeliverReport(						
			std::wstring wstrRequestId,
			int nRecipientDeliverLevel,
			int nSenderDeliverLevel,
			std::wstring wstrSenderInstanceId,
			KLSTD::CAutoPtr<KLPAR::Params> parDeliveryParams,
			KLSTD::CAutoPtr<KLPAR::Params> parReportResult) = 0;

	/*!
	  \brief �������� ����������� ���������� ������ �������.

		\param wstrTaskFileId			[in] - ������������� �������� ������;
		\param parResultTaskStateEvent	[in] - ������� ���������� ���������
	*/
		virtual void ReportRemoteInstallationResult(
			std::wstring wstrTaskTsId,
			KLSTD::CAutoPtr<KLPAR::Params> parResultTaskStateEvent) = 0;

	/*!
	  \brief ������ � ���������� ��������� ������.

		\param wstrRequestId			[in] - ������������� �������;
		\param lResultCode				[in] - ��� ����������;
		\param parParams				[in] - �������������� ��������� 
	*/
		virtual void NotifyOnReportResult(
			std::wstring wstrRequestId,
			long lResultCode,
			KLSTD::CAutoPtr<KLPAR::Params> parParams) = 0;
	};

} // namespace KLSRVH

KLCSSRV_DECL void KLSRVH_CreateSrvHierarchyMasterProxy(
	KLSTD::CAutoPtr<KLSRV::ConnectionInfo> pConnectionInfo, 
	KLSRVH::SrvHierarchyMaster** ppSrvHierarchyMasterProxy);

#endif // KLSRVH_SRVHRCH_MASTER_H

