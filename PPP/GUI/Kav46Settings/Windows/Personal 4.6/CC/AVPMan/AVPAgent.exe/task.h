#ifndef _TASK_H__INCLUDED_
#define _TASK_H__INCLUDED_

#include "../../../cciface/BaseMarshal.h"
#include "../../../cciface/UserSettings.h"
#include "../../../cciface/UserTasks.h"
#include "../../../cciface/ScheduleHelper.h"

#ifndef _DATAONLY_
#	include "../../Common/UserTasksIface.h"
#	include "netdetect.h"
#endif

struct CUserTask;
class CSettings;

//////////////////////////////////////////////////////////////////////////

struct CTaskStartSettings_v1 : CCBaseMarshal<8365>
{
	// ���������, ���������� ��� ������ ������ �� GUI
	std::vector<BYTE> m_Param;
	std::vector<BYTE> m_AcceptableEvents;

	virtual PoliType &MarshalImpl (PoliType &pt)
	{
		return BaseMarshal::MarshalImpl (pt) << m_Param << m_AcceptableEvents;
	}
};

typedef DeclareExternalName<CTaskStartSettings_v1> CTaskStartSettings;

//////////////////////////////////////////////////////////////////////////

// ���������� ��� CUserTaskSettings
class CTaskUserTaskSettings : public CUserTaskSettings
{
public:
	// ���������� ��������� � ����������� ���������
	CUserSettingsODS GetMergedUserSettingsODS() const;
	// ������������� ��������� � ������ ��������
	void SetMergedUserSettingsODS(const CUserSettingsODS &settings);
	// ���������� ���������� � ����������� ���������
	CScheduleSettings GetMergedScheduleSettings() const;
	// ������������� ���������� � ������ ��������
	void SetMergedScheduleSettings(const CScheduleSettings &schedule);
	// ������������� m_UserTaskSettings.m_ODSSettings.m_blOkInfoEventsOff, m_eUseIChecker, m_eUseIStreams
	void SetWriteAllEventsInUserSettingsODS(bool bWriteAllEvents);
	void SetICheckerUsageInUserSettingsODS(EICheckerType type);
	void SetIStreamsUsageInUserSettingsODS(EICheckerType type);
};

class CTaskUpdaterTaskSettings : public CUpdaterTaskSettings
{
public:
	// ���������� ��������� � ����������� ���������
	CUserSettingsUpdater GetMergedUserSettingsUpdater() const;
	// ������������� ��������� � ������ ��������
	void SetMergedUserSettingsUpdater(const CUserSettingsUpdater &settings);
	// ������������� m_UserTaskSettings.m_ODSSettings.m_blOkInfoEventsOff
	void SetWriteAllEventsInUserSettingsUpdater(bool bWriteAllEvents);
};

class CTaskBase : public CBase
{
public:
	CTaskBase (LPCTSTR szName, DWORD dwType);

	// ���� ���������� ������ (���������� � RunningTask � �������� '�� ������� �� ������ ��� ����������')
	BOOL m_bPermanent;
	
	// logon-��������� �������
	CLogonCredentials m_LogonCredentials;

	// ��������� �� ������� ������������ �� UI (���� �� ����)
	// � ������ ���� ������� ��������� ����������������� �� ������� (user+pass ��� thread token)
	bool m_bImplicitImpersonationDeprecated;

	// ��������� ������
	CTaskStartSettings m_StartSettings;

	// ��������� ��� ODS User task
	enum ETaskType
	{
		eTask = 0,
		eUserTask = 1,
		eUpdaterTask = 2,
		eInstallKeyTask = 3,
		eRollbackTask = 4
	};
	ETaskType m_eTaskType;
	// ��������� ODS ������
	CTaskUserTaskSettings m_UserTaskSettings;
	CTaskUpdaterTaskSettings m_UpdaterTaskSettings;
	CInstallKeyTaskSettings m_InstallKeyTaskSettings;
	CRollbackTaskSettings m_RollbackTaskSettings;

	virtual int Store(LPPOLICY* ppPolicy) const;
	virtual int Load(LPPOLICY pPolicy);

protected:
	// ��������� �� �������� ������������� ������
	bool m_bDeferredSchedule;
	unsigned m_nMaxRunningTimeMs;
	// ��������� ������� �� ����������
	std::vector<CSchedulePoint> m_vecSchedule;
	__int64 m_tLastChecked;
	__int64 m_tLastTaskExecTimeBySchedule;

	// ���������� ������������ ����� ��������
	bool m_bAskUser;
	
	// ��������� �� ��� ������
	bool m_bRunOnStartup;
	// �������� ��� ������ (���������� �� 9x)
	DWORD m_nStartDelay;
	//! ���� �������� ������
	KLUTIL::CSysTime m_dtCreationDate;
	//! ����� ���������� ��������� ���������� ������
	KLUTIL::CSysTime m_dtLastSuccessfulFinish;

	// ����� ���������� ����������� �������
	__int64 m_tDeferred;
	
	// ��������������� ����� TASK_INFO_PARAMS\KLPRSS_EVPNotifications ��� WKS
	std::vector<BYTE> m_TaskNotificationDescriptionBlob;
};

#ifndef _DATAONLY_

class CTask : public CTaskBase
{
public:
	CTask ();
	CTask (LPCTSTR szName, DWORD dwType);
	// ��� ������ ��� ����������� CTask ���� �������� ResetLastCheck(). (��� ������� ������ �������� �� ���������� ������������ ������, ��� ������� ������������ ������� ����������).
	void ResetLastCheck ();

	std::string GetExeName() const;

	// Checks happenning of the event
	bool IsTimeForTask();
	bool IsWaitingInternet() const { return m_bWaitingInternet; }

	bool IsNeedAskUser() const;

	bool IsStartupTask() const;
	DWORD GetStartupDelay() const;
	void SetStartup(bool bStartup);

	void SetDeferredTime(const KLUTIL::CSysTime& dtDeferred);
	void ClearDeferredTime();

	void TaskExecutedByScheduler();
	void SetBaseSchedule(const CScheduleSettings& ScheduleSettings);
	__int64 GetLastTaskExecTimeBySchedule() const { return m_tLastTaskExecTimeBySchedule; }
	__int64 GetBaseTimeForNextStart() const;
	KLUTIL::CSysTime GetNextTaskStart() const;
	__int64 GetNextTaskStartI64() const;

	unsigned GetMaxRunningTimeMs() const { return m_nMaxRunningTimeMs; }
	
	//! ���������������� ����� ������ �� scheduler.
	void PauseScheduleStart();
	//! ������������ ����������� ������ ������ �� scheduler.
	void UnpauseScheduleStart();

	CUserTask GetUserTask(bool bMerged) const;
	void SetUserTask(const CUserTask& usertask, bool bMerged, CSettings& settings);
	bool IsAdminTask() const;

	//! ����������� ������ �Ө��� ���, ���� ��� �� ������. 
	void CheckUserName();

	//! ���������� �Ө��� ��� �� ���������.
	std::string GetDefaultUserName() const;

	//! ���������� �������� ������ �Ө��� ���.
	std::string GetUserName() const;

	//! ���������� ��������� ���������� ������.
	void OnSuccessfulyFinished();

private:
	// ���������� ����� ���������� ������� � ������ ���������� ������
	__int64 GetNextStartI64(__int64 ftLastExecute, const std::vector<CSchedulePoint> &Schedule, bool& bNeedInternet) const;

	//! ��������� �� ��������� ��������� ����������� � ���������.
	Notifier::CMethodSubscriberT<ENetDetectEvent, CTask> m_InetDetectSubscriber;
	//! ������� "��������� ����", "��������� ����������� � ���������" (��� WKS)
	Notifier::CEvent m_NetStateEvent, m_InternetStateEvent;
	//! Callback ��� NetDetect.
	void OnInternetStateChanged(const ENetDetectEvent& ev);
	//! ��������� ��������� �������� NetDetect.
	bool m_bInternetIsOnline;
	//! ���� �������� ���������. true - ��� ������� ������ ����� ��������.
	bool m_bWaitingInternet;

	// ��������� �� ����������
	bool m_bPauseSchedule;
};

#endif // _DATAONLY_

#endif // _TASK_H__INCLUDED_