#ifndef __CCTASKS_H__
#define __CCTASKS_H__

#include "UserSettingsScanners.h"
#include "../../../CommonFiles/KLUtil/guid.h"
#include "../../../CommonFiles/CfgPages/CfgPagesRegisteredWindowMessages.h"
#include "../../../CommonFiles/CCClient/taskstat.h"
#include "PredefinedTaskNames.h"

//! ��� ������
enum EReportType
{
	eRT_Default = 0,	//!< � ������������ � ���������� ����������.
	eRT_Skip = 1,		//!< �� ������ �����.
	eRT_Important = 2,	//!< ���������� ������ ������ ���������.
	eRT_Full = 3,		//!< ���������� ��� ���������.
};

// ��� ������� ������
enum EStartType
{
	eNotStarted,
	eOnStartup,
	eByScheduler,
	eFromGUI,
	eByService
};

// ���� ��� ���� � ��������� m_dwParam CRunningTask
// ��� ��������� ������ TS_ERREXEC ��� TS_FAILED (��� ���� � ��������� m_dwParam2 ����� ���� ��� �� GetLastError())
// ���������� ���������� ������ ���������� � ��������� ������������� �����
// � ������ ���������� � m_dwParam ���� ��� ������ Updater, �
// � ������ ��������� ������������� ����� ���� HRESULT �� ���������� ��������������
enum ETaskExecErrCode
{
    eTaskSkipped = 1,
    eLicenceInvalid,
    eModuleSignatureInvalid,
    eComponentLoadingFailed,
    eIpcConnectionFailed,
    eSendingSettingsFailed,
	eBatteryPowerBelowPermitted,
	eImpersonationFailed, // state2: GetLastError
	eConnectionLost,
	eSecondUpdaterRejected,
	eGroupTaskInterrupted, // ��������� ������ �������� (��-�� ������ �� ����������, ������������ � �.�.)

	// ��� ���������� ���� ����� ��������, �� ���� ������������ � �������
	// TaskErrExecError::MakeDescription � AK\Plugin\OldWKS\Common\general_events\general_events.cpp
		
	// ��� ������ �� ����� ���������� ������ InstallKey
	// ������ ����� ���� ������������ HRESULT �� Licensing\include\err_defs.h
	// ��� ���������� � ���� enum ����� ��������, ��� �� ������ ������������
	// � ������ ������ ���������� ��������������.
};

enum CCTaskManagementCommand
{
	tcStart = CMD_START_TASK,
	tcStop = CMD_STOP_TASK,
	tcPause = CMD_PAUSE_TASK,
	tcResume = CMD_RESUME_TASK
};

__inline std::string MakeODSUniqueTaskName (LPCSTR lpszPrefix = CC_TASK_UID_PREFIX)
{
	return std::string (lpszPrefix) + KLUTIL::MakeGuidString();
}

// general task interface
struct CCIFACEEXPORT CInterfaceTask
{
	CInterfaceTask() : m_ReportType(eRT_Default), m_bBindCustomCommandIface(false)
	{
	}
	
	virtual ~CInterfaceTask()
	{
	}
	
	virtual const char *Name() const = 0;
	virtual LPVOID CreateParamBuffer(DWORD &dwParamBufferSize)
	{
		return NULL;
	}
	virtual LPPOLICY CreateForceSettingsBuffer(DWORD &dwForceSettingsPolicySize)
	{
		dwForceSettingsPolicySize = 0;
		return NULL;
	}
	virtual EReportType GetReportType() const
	{
		return m_ReportType;
	}
	LPPOLICY CreateTaskStartCommandPolicy(
		CCTaskManagementCommand Command,		
		LPCTSTR szReportName,
		LPCTSTR szExternalStateSemaphoreName);
	void SetReportType(EReportType reportType)
	{
		m_ReportType = reportType;
	}
	void SetAcceptableEvents (LPVOID lpEventBuffer, DWORD dwBuferSize)
	{
		if (lpEventBuffer && dwBuferSize)
			m_AcceptableEvents.assign((LPBYTE)lpEventBuffer, (LPBYTE)lpEventBuffer + dwBuferSize);
		else
			m_AcceptableEvents.clear();
	}
	void BindCustomCommandIface(bool bBind)
	{
		m_bBindCustomCommandIface = bBind;
	}
private:
	EReportType m_ReportType;
	std::vector<BYTE> m_AcceptableEvents;
	bool m_bBindCustomCommandIface;
};

// ��� ������
class CCIFACEEXPORT CInterfaceUserTask : public CInterfaceTask
{
public:
	CInterfaceUserTask(const char *pszTaskName) :
		m_sTaskName(pszTaskName)
	{
	}
	virtual const char *Name() const
	{
		return m_sTaskName.c_str();
	}
private:
	std::string m_sTaskName;
};

// user objects scan
class CCIFACEEXPORT CInterfaceScanObjectsTask : public CInterfaceUserTask
{
public:
    CCODSScanObjects m_Objects;

	CInterfaceScanObjectsTask()
		: CInterfaceUserTask(MakeODSUniqueTaskName(CC_TASK_UID_USER_OBJECT_SCAN).c_str())
	{
	}
	CInterfaceScanObjectsTask(const CCODSScanObjects &Objects)
		: CInterfaceUserTask(MakeODSUniqueTaskName(CC_TASK_UID_USER_OBJECT_SCAN).c_str()), m_Objects (Objects)
	{
	}
	CInterfaceScanObjectsTask(const char *pszTaskName)
		: CInterfaceUserTask(pszTaskName)
	{
	}
	CInterfaceScanObjectsTask(const char *pszTaskName, const CCODSScanObjects &Objects)
		: CInterfaceUserTask(pszTaskName), m_Objects(Objects)
	{
	}

	virtual LPVOID CreateParamBuffer(DWORD &dwParamBufferSize)
	{
		LPPOLICY pPolicy = NULL;
		dwParamBufferSize = m_Objects.Store(&pPolicy);
		return pPolicy;
	}
};
 
inline const TCHAR * GetTaskStateStr (ETaskState dwTaskState)
{
	switch (dwTaskState)
	{
	case TS_UNKNOWN:
		return _T("TS_UNKNOWN");
	case TS_RUNNING:
		return _T("TS_RUNNING");
	case TS_DONE:
		return _T("TS_DONE");
	case TS_FAILED:
		return _T("TS_FAILED");
	case TS_ABORTED:
		return _T("TS_ABORTED");
	case TS_PAUSED:
		return _T("TS_PAUSED");
	case TS_STARTING:
		return _T("TS_STARTING");
	case TS_STOPING:
		return _T("TS_STOPING");
	case TS_ERREXEC:
		return _T("TS_ERREXEC");
	case TS_RESTARTING:
		return _T("TS_RESTARTING");
	}
	
	return _T("TS_UNEXPECTED");
}

#endif