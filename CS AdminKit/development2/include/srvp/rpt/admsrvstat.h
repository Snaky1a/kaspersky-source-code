/*!
 * (C) 2005 Kaspersky Lab 
 * 
 * \file	srvp/rpt/admsrvstat.h
 * \author	Andrew Lashchenkov
 * \date	22.08.2005 12:00:00
 * \brief	��������� ��� ��������� ���������� � ���������� �������
 * 
 */

#ifndef __KLPRT_ADMSRVSTAT_H__
#define __KLPRT_ADMSRVSTAT_H__

#pragma warning  (disable : 4786 )
#include <vector>

#include <std/base/klstd.h>
#include <srvp/rpt/reports.h>

namespace KLRPT
{
    /*!
        \brief AdmSrvStatistics - ��������� ��������� ���������� � ���������� ������� */
    class AdmSrvStatistics : public KLSTD::KLBaseQI{
    public:
	    /*!
        \brief ������ ���������� 
			\param pRequestParams - Params � ������������� ������������� ����������;
									������ ������� ����� ��� Params � ����������� �������� ��������� �������;
			\param wstrRequestId - ���������� ������������� �������;
		*/
        virtual void RequestStatisticsData(
			const KLSTD::CAutoPtr<KLPAR::Params> pRequestParams,
            const std::wstring& wstrRequestId,
			KLEV::AdviseEvSink* pSink,
            KLEV::HSINKID& hSink) = 0;

	    /*!
        \brief ������ ���������� 
			\param pRequestParams - ������ �������;
			\param wstrRequestId - ������������� �������;
		*/
        virtual void CancelStatisticsRequest(
            const std::wstring & wstrRequestId) = 0;

	    /*!
        \brief ������ ��������� ���������� �������;
			\param wstrRequestId - ������������� �������;
			\param ppParamsData - ���������� ������.
		*/
        virtual void GetStatisticsData(
            const std::wstring& wstrRequestId,
			KLPAR::Params** ppParamsData) = 0;
	};

	class AdmSrvStatistics2 : public AdmSrvStatistics{
	public:
	    /*!
        \brief �������������� ����� ������ ����������, ��������, ����� ������� "�������� �����" ��� 
			"������ ���������� ������ ������� �����������������" ����� ������������ � ��������� �����������. 
			\param pRequestParams - Params � ������������� ��������, ������� ���� "��������";
		*/
        virtual void ResetStatisticsData(
			const KLSTD::CAutoPtr<KLPAR::Params> pRequestParams) = 0;
	};

	// Counters parameters:
	const wchar_t c_rptStatPeriodInSec[]=L"KLPPT_StatPeriodInSec"; // INT_T
	
	const wchar_t c_rptStatTimeGridSec[]=L"KLPPT_StatTimeGridSec"; // ARRAY_T

	const wchar_t c_rptReturnDataAsSeries[]=L"KLPPT_ReturnDataAsSeries"; // BOOL_T

	const wchar_t c_rptMaxSubitemsCount[]=L"KLPPT_MaxSubitemsCount"; // INT_T

	const wchar_t c_rptStatFinishTime[]=L"KLPPT_StatFinishTime"; // DATETIME_T

	// Counters:
	const wchar_t c_rptUnassignedHostsCount[]=L"KLPPT_UnassignedHostsCount"; // INT_T

	const wchar_t c_rptNetScanPercent[]=L"KLPPT_NetScanPercent"; // INT_T

	const wchar_t c_rptNewHostsCount[]=L"KLPPT_NewHostsCount"; // INT_T
		// c_rptStatPeriodInSec

	const wchar_t c_rptLastNetScanTime[]=L"KLPPT_LastNetScanTime"; // DATE_TIME_T
	
	const wchar_t c_rptDomainBeingScanned[]=L"KLRPT_DomainBeingScanned"; //STRING_T

	const wchar_t c_rptGroupsHostsCount[]=L"KLPPT_GroupsHostsCount"; // INT_T

	const wchar_t c_rptCrtHostsCount[]=L"KLPPT_CrtHostsCount"; // INT_T

	const wchar_t c_rptWrnHostsCount[]=L"KLPPT_WrnHostsCount"; // INT_T

	const wchar_t c_rptSrvConnectionsCount[]=L"KLPPT_SrvConnectionsCount"; // INT_T

	const wchar_t c_rptLastSrvConnTimeHistogram[]=L"KLPPT_LastSrvConnTimeHistogram"; // PARAMS_T
		// c_rptStatTimeGridSec
		// c_rptReturnDataAsSeries

	const wchar_t c_rptInfectedObjectsCount[]=L"KLPPT_InfectedObjectsCount"; // INT_T
		// c_rptStatPeriodInSec

	const wchar_t c_rptLastUpdateTime[]=L"KLPPT_LastUpdateTime"; // DATE_TIME_T

	const wchar_t c_rptUpdTskState[]=L"KLPPT_UpdTskState"; // INT_T

	const wchar_t c_rptUpdTskStateDescr[]=L"KLPPT_UpdTskStateDescr"; // STRING_T

	const wchar_t c_rptAVSBasesAgeHistogram[]=L"KLPPT_AVSBasesAgeHistogram"; // PARAMS_T

	const wchar_t c_rptRTPStateHistogram[]=L"KLPPT_RTPStateHistogram"; // PARAMS_T

	const wchar_t c_rptFullScanTimeHistogram[]=L"KLPPT_FullScanTimeHistogram"; // PARAMS_T

	const wchar_t c_rptVirusesHistogram[]=L"KLPPT_VirusesHistogram"; // PARAMS_T

	const wchar_t c_rptStatViractPeriodInSec[]=L"KLPPT_StatViractPeriodInSec"; // INT_T

	// ������� �������: // �� ��������� c_rptStatViractPeriodInSec ������

	const wchar_t c_rptVirWKSFound[]=L"KLPPT_VirWKSFound"; // INT_T

	const wchar_t c_rptVirWKSCured[]=L"KLPPT_VirWKSCured"; // INT_T

	const wchar_t c_rptVirWKSDeleted[]=L"KLPPT_VirWKSDeleted"; // INT_T

	const wchar_t c_rptVirWKSNotCured[]=L"KLPPT_VirWKSNotCured"; // INT_T

	const wchar_t c_rptVirWKSNetAttacks[]=L"KLPPT_VirWKSNetAttacks"; // INT_T

	// �������� �������: // �� ��������� c_rptStatViractPeriodInSec ������

	const wchar_t c_rptVirFSFound[]=L"KLPPT_VirFSFound"; // INT_T

	const wchar_t c_rptVirFSCured[]=L"KLPPT_VirFSCured"; // INT_T

	const wchar_t c_rptVirFSDeleted[]=L"KLPPT_VirFSDeleted"; // INT_T

	const wchar_t c_rptVirFSNotCured[]=L"KLPPT_VirFSNotCured"; // INT_T

	const wchar_t c_rptVirFSNetAttacks[]=L"KLPPT_VirFSNetAttacks"; // INT_T

	// �������� �������: // �� ��������� c_rptStatViractPeriodInSec ������

	const wchar_t c_rptVirEMLFound[]=L"KLPPT_VirEMLFound"; // INT_T

	const wchar_t c_rptVirEMLCured[]=L"KLPPT_VirEMLCured"; // INT_T

	const wchar_t c_rptVirEMLDeleted[]=L"KLPPT_VirEMLDeleted"; // INT_T

	const wchar_t c_rptVirEMLNotCured[]=L"KLPPT_VirEMLNotCured"; // INT_T

	const wchar_t c_rptVirEMLNetAttacks[]=L"KLPPT_VirEMLNetAttacks"; // INT_T

	// ������ ���������: // �� ��������� c_rptStatViractPeriodInSec ������

	const wchar_t c_rptVirPHFound[]=L"KLPPT_VirPHFound"; // INT_T

	const wchar_t c_rptVirPHCured[]=L"KLPPT_VirPHCured"; // INT_T

	const wchar_t c_rptVirPHDeleted[]=L"KLPPT_VirPHDeleted"; // INT_T

	const wchar_t c_rptVirPHNotCured[]=L"KLPPT_VirPHNotCured"; // INT_T

	const wchar_t c_rptVirPHNetAttacks[]=L"KLPPT_VirPHNetAttacks"; // INT_T

	// ����� ����������� � �������� ������ ������������� �����
	const wchar_t c_rptLicExpiredCnt[]=L"KLPPT_LicExpiredCnt"; // INT_T

	// ����� ����������� ��� ������������ ������
	const wchar_t c_rptNoAvpCnt[]=L"KLPPT_NoAvpCnt"; // INT_T

	// ����� �����������, ���������� �������� ��������
	const wchar_t c_rptControlLostCnt[]=L"KLPPT_ControlLostCnt"; // INT_T
};

namespace KLSTS
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ������� ������� ����������������� /////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ������� ����, ��� ��������� ��� ��������, � �� ������ ������������ ������� ������:
	const wchar_t c_sts_NeedAllCounters[]=L"KLSTS_NeedAllCounters"; // BOOL_T
	const bool c_sts_bNeedAllCountersDflt = false;

	// ������� ����, ��� ��������� ��� �������, ������������ ������� ������:
	const wchar_t c_sts_NeedAllReasons[]=L"KLSTS_NeedAllReasons"; // BOOL_T
	const bool c_sts_bNeedAllReasonsDflt = true;
	
	enum EStatus{
		STATUS_OK  = 0,
		STATUS_INFO = 1,
		STATUS_WARNING = 2,
		STATUS_CRITICAL = 3
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ����� ��������� ��������:

		// ������ (��. enum EStatus):
		const wchar_t c_sts_Par_Status[]=L"KLSTS_Par_Status"; // INT_T

		// ������� ������� (������� �����):
		const wchar_t c_sts_Par_StatusReasonMask[]=L"KLSTS_Par_StatusReasonMask"; // INT_T

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// C������:
	// (� ���� �������� ��� ������� 2 ������������ ��������� - c_sts_Par_Status � c_sts_Par_StatusReasonMask)

	// ������ "��������� ����������":
	const wchar_t c_sts_Deployment[]=L"KLSTS_Deployment"; // PARAMS_T
		// ���������:
		const wchar_t c_sts_Par_Dpl_HostsInGroups[]=L"KLSTS_Par_Dpl_HostsInGroups"; // INT_T
		const wchar_t c_sts_Par_Dpl_HostsWithAVP[]=L"KLSTS_Par_Dpl_HostsWithAVP"; // INT_T
		const wchar_t c_sts_Par_Dpl_RITaskStrId[]=L"KLSTS_Par_Dpl_RITaskStrId"; // STRING_T
		const wchar_t c_sts_Par_Dpl_RITaskName[]=L"KLSTS_Par_Dpl_RITaskName"; // STRING_T
		const wchar_t c_sts_Par_Dpl_RITaskPercent[]=L"KLSTS_Par_Dpl_RITaskPercent"; // INT_T
		const wchar_t c_sts_Par_Dpl_RITaskOkCnt[]=L"KLSTS_Par_Dpl_RITaskOkCnt"; // INT_T
		const wchar_t c_sts_Par_Dpl_RITaskFailedCnt[]=L"KLSTS_Par_Dpl_RITaskFailedCnt"; // INT_T
		const wchar_t c_sts_Par_Dpl_RITaskNeedRbtCnt[]=L"KLSTS_Par_Dpl_RITaskNeedRbtCnt"; // INT_T
		const wchar_t c_sts_Par_Dpl_LicExparingSerial[]=L"KLSTS_Par_Dpl_LicExparingSerial"; // STRING_T
		const wchar_t c_sts_Par_Dpl_LicExparingDays[]=L"KLSTS_Par_Dpl_LicExparingDays"; // INT_T
		const wchar_t c_sts_Par_Dpl_LicExparingCnt[]=L"KLSTS_Par_Dpl_LicExparingCnt"; // INT_T
		const wchar_t c_sts_Par_Dpl_LicExparedCnt[]=L"KLSTS_Par_Dpl_LicExparedCnt"; // INT_T
		
		// ������������ �������� c_sts_Par_StatusReasonMask:
		enum{
			// �� ��� ���������� � ������� ����������������� ����������� ������������ ������
			STAT_DPL__OK = 0x0000,

			// ����������� � ������� �����������������: N, �� ��� � ������������� �����������: M (N > M)
			// N - c_sts_Par_Dpl_HostsInGroups
			// M - c_sts_Par_Dpl_HostsWithAVP
			STAT_DPL__NO_AV = 0x0001,

			// �������� ������ ��������� ���������� NNN, ������� ����������: N
			// NNN - c_sts_Par_Dpl_RITaskName
			// N - c_sts_Par_Dpl_RITaskPercent
			// {Id ������} - c_sts_Par_Dpl_RITaskStrId
			STAT_DPL__RI_RUNNING = 0x0002,

			// ������ ��������� ���������� NNN ����������� ������� �� N �����������, ��������� �� M �����������
			// NNN - c_sts_Par_Dpl_RITaskName
			// N - c_sts_Par_Dpl_RITaskOkCnt
			// M - c_sts_Par_Dpl_RITaskFailedCnt
			// {Id ������} - c_sts_Par_Dpl_RITaskStrId
			STAT_DPL__RI_FAILED = 0x0004,

			// ������ ��������� ���������� NNN ����������� ������� �� N �����������, ��������� ������������ �� M �����������
			// NNN - c_sts_Par_Dpl_RITaskName
			// N - c_sts_Par_Dpl_RITaskOkCnt
			// M - c_sts_Par_Dpl_RITaskNeedRbtCnt
			// {Id ������} - c_sts_Par_Dpl_RITaskStrId
			STAT_DPL__RI_NEED_REBOOT = 0x0008,

			// �� ��������� ����� �������� �������� NNN �� N ����������� �������� M ����. 
			// NNN - c_sts_Par_Dpl_LicExparingSerial
			// N - c_sts_Par_Dpl_LicExparingCnt
			// M - c_sts_Par_Dpl_LicExparingDays
			STAT_DPL__LIC_EXPARING = 0x0010,

			// �������� �������� �������� �� N �����������
			// N - c_sts_Par_Dpl_LicExparedCnt
			STAT_DPL__LIC_EXPARED = 0x0020
		};

	// ������ "����������":
	const wchar_t c_sts_Updates[]=L"KLSTS_Updates"; // PARAMS_T
		// ���������:
		const wchar_t c_sts_Par_Upd_LastSrvUpdateTime[]=L"KLSTS_Par_Upd_LastSrvUpdateTime"; // DATETIME_T
		const wchar_t c_sts_Par_Upd_NotUpdatesCnt[]=L"KLSTS_Par_Upd_NotUpdatesCnt"; // INT_T
		const wchar_t c_sts_Par_Upd_SrvCompletedPercent[]=L"KLSTS_Par_Upd_SrvCompletedPercent"; // INT_T
		// ������������ �������� c_sts_Par_StatusReasonMask:
		enum{
			// ��������� ���������� ������� �����������������: N ����� �����
			// N - c_sts_Par_Upd_LastSrvUpdateTime
			STAT_UPD__OK = 0x0000,

			// ������ ����������������� ����� �� ����������
			STAT_UPD__SRV_NOT_UPDATED = 0x0001,

			// N ����������� � ������� ����������������� ����� �� �����������
			// N - c_sts_Par_Upd_NotUpdatesCnt
			STAT_UPD__HOSTS_NOT_UPDATED = 0x0002,

			// �������� ������ ���������� ������� �����������������, ������� ����������: N
			// N - c_sts_Par_Upd_SrvCompletedPercent
			STAT_UPD__SRV_UPDATE_IN_PROGRESS = 0x0004
		};

	// ������ "������":
	const wchar_t c_sts_Protection[]=L"KLSTS_Protection"; // PARAMS_T
		// ���������:
		const wchar_t c_sts_Par_Prt_AvpNotRunningCnt[]=L"KLSTS_Par_Prt_AvpNotRunningCnt"; // INT_T
		const wchar_t c_sts_Par_Prt_RtpNotRunningCnt[]=L"KLSTS_Par_Prt_RtpNotRunningCnt"; // INT_T
		const wchar_t c_sts_Par_Prt_RtpLevelChangedCnt[]=L"KLSTS_Par_Prt_RtpLevelChangedCnt"; // INT_T
		const wchar_t c_sts_Par_Prt_NoncuresHstCnt[]=L"KLSTS_Par_Prt_NoncuresHstCnt"; // INT_T
		const wchar_t c_sts_Par_Prt_TooManyThreadsCnt[]=L"KLSTS_Par_Prt_TooManyThreadsCnt"; // INT_T
		// ������������ �������� c_sts_Par_StatusReasonMask:
		enum{
			// ������������ ������ �������� �� ���� ����������� �����������
			STAT_PRT__OK = 0x0000,
				
			// �� �������� ������������ ���������� �� N �����������
			// N - c_sts_Par_Prt_AvpNotRunningCnt
			STAT_PRT__AV_NOT_RUNNING = 0x0001,
			
			// �� �������� ���������� ������ �� N �����������
			// N - c_sts_Par_Prt_RtpNotRunningCnt
			STAT_PRT__RTP_NOT_RUNNING = 0x0002,
			
			// ������� ���������� ������ ���������� �� �������������� ��������������� �� N �����������
			// N - c_sts_Par_Prt_RtpLevelChangedCnt
			STAT_PRT__RPT_LEVEL_CHANGED = 0x0004,
			
			// �� N ����������� ������� ������������ �������
			// N - c_sts_Par_Prt_NoncuresHstCnt
			STAT_PRT__NONCURED_FOUND = 0x0008,

			// �� N ����������� ������� ������� ����� �������
			// N - c_sts_Par_Prt_TooManyThreadsCnt
			STAT_PRT__TOO_MANY_THREATS = 0x0010,
			
			// �������� �����
			STAT_PRT__VIRUS_OUTBREAK = 0x0020
		};

	// ������ "��������":
	const wchar_t c_sts_FullScan[]=L"KLSTS_FullScan"; // PARAMS_T
		// ���������:
		const wchar_t c_sts_Par_Scn_NotScannedLatelyCnt[]=L"KLSTS_Par_Scn_NotScannedLatelyCnt"; // INT_T
		const wchar_t c_sts_Par_Scn_NeverScannedCnt[]=L"KLSTS_Par_Scn_NeverScannedCnt"; // INT_T
		// ������������ �������� c_sts_Par_StatusReasonMask:
		enum{
			// ������ ������������ �������� ����������� �� ���� ����������� 
			STAT_SCN__OK = 0x0000,

			// ������ ������������ �������� ����� �� ����������� �� N �����������
			// N - c_sts_Par_Scn_NotScannedLatelyCnt
			STAT_SCN__NOT_SCANNED_LATELY = 0x0001,
				
			// ������ ������������ �������� �� ���� �� ����������� �� N �����������
			// N - c_sts_Par_Scn_NeverScannedCnt
			STAT_SCN__NEVER_SCANNED = 0x0002
		};

	// ������ "����������� ���������� ����":
	const wchar_t c_sts_Administration[]=L"KLSTS_Administration"; // PARAMS_T
		// ���������:
		const wchar_t c_sts_Par_Adm_FoundHstCnt[]=L"KLSTS_Par_Adm_FoundHstCnt"; // INT_T
		const wchar_t c_sts_Par_Adm_GrpCnt[]=L"KLSTS_Par_Adm_GrpCnt"; // INT_T
		const wchar_t c_sts_Par_Adm_GrpHstCnt[]=L"KLSTS_Par_Adm_GrpHstCnt"; // INT_T
		const wchar_t c_sts_Par_Adm_NotConnectedLongTimeCnt[]=L"KLSTS_Par_Adm_NotConnectedLongTimeCnt"; // INT_T
		const wchar_t c_sts_Par_Adm_ControlLostCnt[]=L"KLSTS_Par_Adm_ControlLostCnt"; // INT_T
		// ������������ �������� c_sts_Par_StatusReasonMask:
		enum{
			// ���������� N �����������, � M ������� ����������������� ��������� K �����������
			// N - c_sts_Par_Adm_FoundHstCnt
			// M - c_sts_Par_Adm_GrpCnt
			// K - c_sts_Par_Adm_GrpHstCnt
			STAT_ADM__OK = 0x0000,

			// N ����������� ����� �� ����������� � �������� �����������������
			// N - c_sts_Par_Adm_NotConnectedLongTimeCnt
			STAT_ADM__NOT_CONNECTED_LONG_TIME = 0x0001,

			// �������� ���������� ������������
			// N - c_sts_Par_Adm_ControlLostCnt
			STAT_ADM__CONTROL_LOST = 0x0002,
		
			// �������� NETBIOS-���� ���������� �����������
			STAT_ADM__NAME_CONFLICT = 0x0004
		};

	// ������ "������ � �����������":
	const wchar_t c_sts_Events[]=L"KLSTS_Events"; // PARAMS_T
		// ���������:
		const wchar_t c_sts_Par_Ev_CriticalSrvEventsCnt[]=L"KLSTS_Par_Ev_CriticalSrvEventsCnt"; // INT_T
		const wchar_t c_sts_Par_Ev_FailedSrvTskName[]=L"KLSTS_Par_Ev_FailedSrvTskName"; // STRING_T
		const wchar_t c_sts_Par_Ev_FailedSrvTskStrId[]=L"KLSTS_Par_Ev_FailedSrvTskStrId"; // STRING_T
		// ������������ �������� c_sts_Par_StatusReasonMask:
		enum{
			// ����� ����������� ������� �� �����������
			STAT_EV__OK = 0,

			// �� ������� ����������������� ���������������� N ����������� �������
			// N - c_sts_Par_Ev_CriticalSrvEventsCnt
			STAT_EV__EVENTS_OCCURED = 0x0001,

			// ������ NNN ������� ����������������� ����������� � �������
			// NNN - c_sts_Par_Ev_FailedSrvTskName
			// {ID ������} - c_sts_Par_Ev_FailedSrvTskStrId
			STAT_EV__TASK_FAILED = 0x0002
		};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

namespace KLDSH
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Dashboard data
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	const wchar_t c_dshDashboard[]=L"KLPPT_DASHBOARD"; // ARRAY_T // of PARAMS_T
	// |- KLRPT::c_dshEntryId; // STRING_T; ������������� ����������.
	//		|- KLDSH::c_dshType; // INT_T; EDashboardType
	//		|- KLRPT::c_rptStatFinishTime; // DATETIME_T
	//		|- KLRPT::c_rptStatPeriodInSec; // INT_T
	//		|- ���. ���������, ����������� ��� ������� ����������.

	enum EDashboardType{
		DSHT_UNKNOWN = 0,
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		// �����������:
		DSHT_HIST_EV_BY_COND = 1, // ������������� �������, ��������������� �������� ��������
		// In - ��������� (���.):
			// - KLEVP::c_er_product_name // ��� �������� (����� ������������� ��� �.�. ������ ������);
			// - KLEVP::c_er_product_version // �����. ������ �������� (����� ������������� ��� �.�. ������ ������);
			// - KLEVP::c_er_event_type // ��� ������� (����� ������������� ��� �.�. ������ ������);
			// - KLEVP::c_er_severity // ��������� ������� (����� ������������� ��� �.�. < 0 - ��� ����);
		// Out - ���������: 
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Finish; // ����� ���������� ���������;
			//		|- c_dshPar_Start; // ������ ���������� ���������;
			//		|- c_dshPar_Count; // �������;
		DSHT_HIST_VIRACT = 2,  // ������������� �������� ����������
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Finish; // ����� ���������� ���������;
			//		|- c_dshPar_Start; // ������ ���������� ���������;
			//		|- c_dshPar_Count; // �������;
		DSHT_HIST_VIRACT_PRD = 3, // ������������� �������� ���������� �� ����� ���������
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Finish; // ����� ���������� ���������;
			//		|- c_dshPar_Start; // ������ ���������� ���������;
			//		|- c_dshPar_Count; // �������;
			//		|- c_dshPar_AvpPrdType; // ��� �������� (KLRPT::EAVProdType);
		DSHT_HIST_NET_ATTACK = 4, // ������������� ������� ����
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Finish; // ����� ���������� ���������;
			//		|- c_dshPar_Start; // ������ ���������� ���������;
			//		|- c_dshPar_Count; // �������;
		DSHT_HIST_NEW_HST_FND = 5, // ������������� ����������� ����� ������
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Finish; // ����� ���������� ���������;
			//		|- c_dshPar_Start; // ������ ���������� ���������;
			//		|- c_dshPar_Count; // �������;
		DSHT_HIST_GRP_TSK = 6, // ������������� ��������� ��������� ������
		// In - ��������� (���.):
			// - KLTSK::c_evpGrpTaskId;
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Finish; // ����� ���������� ���������;
			//		|- c_dshPar_Start; // ������ ���������� ���������;
			//		|- KLEVP::c_er_task_new_state; // ��������� ������ �� �����;
			//		|- c_dshPar_Count; // �������;
		DSHT_HIST_AV_REC = 7, // ������������� ����� ������� � ������������ ����� �������
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Finish; // ����� ���������� ���������;
			//		|- c_dshPar_Start; // ������ ���������� ���������;
			//		|- c_dshPar_Count; // �������;
		DSHT_HIST_AVP = 8, // ������������� ��������� ������������ ������.
		// Out - ���������:
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Finish; // ����� ���������� ���������;
			//		|- c_dshPar_Start; // ������ ���������� ���������;
			//		|- c_dshPar_CountCrt; // ����� ������ �� �������� CRT;
			//		|- c_dshPar_CountWrn; // ����� ������ �� �������� WRN;
			//		|- c_dshPar_CountOk; // ����� ������ �� �������� OK;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ���������:
		DSHT_VIRACT_ACT_BY_VIR = 9, // ��������� �� ����� ������� � ����������� �������.
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_VirType; // INT_T - EDetectionType;
			//		|- c_dshPar_Result; // INT_T - EViractResult;
			//		|- c_dshPar_Count; // INT_T;
		DSHT_VIRACT_VIR_BY_AVP = 10,// ��������� �� ����� �������, ����������� ���������� ������ ���������.
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_AvpPrdType; // INT_T - ��� �������� (KLRPT::EAVProdType);
			//		|- c_dshPar_VirType; // INT_T - EDetectionType;
			//		|- c_dshPar_Count; // �������;
		DSHT_VIRACT_ACT_BY_AVP = 11, // ��������� ����������� ������� �������, ����������� ���������� ������ ���������.
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_AvpPrdType; // INT_T - ��� �������� (KLRPT::EAVProdType);
			//		|- c_dshPar_Result; // INT_T - EViractResult;
			//		|- c_dshPar_Count; // INT_T;
		DSHT_VIRACT_MI_HOSTS = 12, // ��������� �������� ���������� �����������.
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Name; // ��� ����������;
			//		|- c_dshPar_Count; // �������;
		DSHT_VIRACT_MI_USERS = 13, // ��������� �������� ���������� �������������.
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Name; // ������� ������������;
			//		|- c_dshPar_Count; // �������;
		DSHT_AVP_STATE = 14, // ������� ��������� ������������ ������.
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshPar_CountCrt; // ����� ������ �� �������� CRT;
			// - c_dshPar_CountWrn; // ����� ������ �� �������� WRN;
			// - c_dshPar_CountOk; // ����� ������ �� �������� OK;
		DSHT_PROD_VER = 15, // ���������, ������������ ������������� ��������� �� �������.
		// In - ��������� (���.):
			// - KLEVP::c_er_product_name // ��� �������� (����� ������������� ��� �.�. ������ ������);
			// - KLEVP::c_er_product_version // �����. ������ �������� (����� ������������� ��� �.�. ������ ������);
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Name; // ������;
			//		|- c_dshPar_Count; // �������;
		DSHT_AVDB_VER = 16, // ���������, ������������ ������������� �� ������� ������������ ���.
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshPar_CountActual; // �������;
			// - c_dshPar_CountDay; // �������;
			// - c_dshPar_Count3Days; // �������;
			// - c_dshPar_Count7Days; // �������;
			// - c_dshPar_CountOld; // �������;
		DSHT_ERR = 17, // ��������� �� ����� ������.
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Name; // ������;
			//		|- c_dshPar_Count; // �������;
		DSHT_RTP_STATE = 18, // ��������� �� �������� ��������� RTP ������.
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Type; // ���������; KLCONN::AppRtpState
			//		|- c_dshPar_Count; // �������;
		DSHT_NET_ATTACKS = 19, // ��������� �� ����� ������� ����.
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Name; // ��� �����
			//		|- c_dshPar_Count; // �������;
		DSHT_LIC = 20, // ��������� ������������� ��������.
		// Out - ���������:
			// - ��� In - ���������;
			// - c_dshData; // ARRAY_T of PARAMS_T
			//		|- c_dshPar_Name; // ��������
			//		|- c_dshPar_Count; // ������������;
			//		|- c_dshPar_Limit; // �����;
		DSHT_SRV_UPD = 21, // ������� ������ ������ ��������� ���������� �������� �����������������.
		// Out - ���������:
			// - ��� In - ���������;
			// - KLEVP::c_er_task_new_state; // ��������� ������ �� �����;
			// - KLEVP::c_er_rise_time; // �����;
			// - KLEVP::c_er_descr; // ��������;
			// - KLEVP::c_er_completedPercent; // ������� ����������;
		DSHT_SRV_BKP = 22, // ������� ������ ������ ���������� ����������� ������� �����������������.
		// Out - ���������:
			// - ��� In - ���������;
			// - KLEVP::c_er_task_new_state; // ��������� ��������� ������;
			// - KLEVP::c_er_rise_time; // �����;
			// - KLEVP::c_er_descr; // ��������;
		DSHT_TYPE_END
	};

	enum EViractResult{
		VR_NA  = 0,
		VR_CURED = 1,
		VR_DELETED = 2,
		VR_NOTCURED = 3
	};

	const wchar_t c_dshType[] = L"KLRPT_DSH_TYPE"; // INT_T; ��� ���������� (EDashboardType).
	const wchar_t c_dshEntryId[] = L"KLRPT_DSH_ENTRY_ID"; // STRING_T; ������������� ����������.
	const wchar_t c_dshData[]=L"DSHT_DATA"; // ARRAY_T
	const wchar_t c_dshPar_Finish[] = L"tmFinish"; // DATETIME_T - ����� ���������� ���������;
	const wchar_t c_dshPar_Start[] = L"tmStart"; // DATETIME_T - ������ ���������� ���������;
	const wchar_t c_dshPar_Count[] = L"nCount"; // INT_T - �������;
	const wchar_t c_dshPar_Count64[] = L"nCount64"; // LONG_T - 64-������ �������;
	const wchar_t c_dshPar_CountCrt[] = L"nCrtCount"; // INT_T - ������� �������� �� �������� CRT;
	const wchar_t c_dshPar_CountWrn[] = L"nWrnCount"; // INT_T - ������� �������� �� �������� WRN;
	const wchar_t c_dshPar_CountOk[] = L"nOkCount"; // INT_T - ������� �������� �� �������� OK;
	const wchar_t c_dshPar_AvpPrdType[] = L"nAvpPrdType"; // INT_T - ��� �������� (KLRPT::EAVProdType);
	const wchar_t c_dshPar_VirType[] = L"nVirType"; // INT_T - EDetectionType;
	const wchar_t c_dshPar_Result[] = L"nVirRslt"; // INT_T - EViractResult;
	const wchar_t c_dshPar_Name[] = L"wstrName"; // STRING_T - ��� (����������, ��������, etc.);
	const wchar_t c_dshPar_Type[] = L"nType"; // INT_T - ���������, ��� (RTP, ��� ������� �����, etc.);
	const wchar_t c_dshPar_Limit[] = L"nLimit"; // INT_T - �����;
	const wchar_t c_dshPar_CountActual[] = L"nCountActual"; // �������;
	const wchar_t c_dshPar_CountDay[] = L"nCountDay"; // �������;
	const wchar_t c_dshPar_Count3Days[] = L"nCount3Days"; // �������;
	const wchar_t c_dshPar_Count7Days[] = L"nCount7Days"; // �������;
	const wchar_t c_dshPar_CountOld[] = L"nCountOld"; // �������;
}

#endif //__KLPRT_ADMSRVSTAT_H__
