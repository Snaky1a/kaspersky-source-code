#ifndef __AVPAGENT_EXE_PATCHINFO_H
#define __AVPAGENT_EXE_PATCHINFO_H

#pragma once

#include <string>
#include <vector>
#include "../../../cciface/BaseMarshal.h"
#include "../../Common/Pid.h"

//! �������� ApplicationId ��� ������ ���������.
#define APPLICATION_ID_PERSONAL _T("Personal")
#define APPLICATION_ID_PERSONAL_PRO _T("Personal Pro")
#define APPLICATION_ID_WORKSTATION _T("Workstation")
#define APPLICATION_ID_ONSITESCANNER _T("OnSiteScanner")

//! ���������� �� ��������� �����.
struct CPatchInfo
{
	CPatchInfo()
		: m_bAskUser(true), m_bUrgent(false)
	{
	}

	//! ���������� ���� � �����.
	std::string m_sPath;
	//! ������ �������� ��� ������� �������� ����.
	std::vector<std::string> m_FromAppVersion;
	//! ������ �������� ����� ���������� �����.
	std::string m_sToAppVersion;
	//! ����������� � �����.
	std::string m_sComment;
	//! ����, ���������� �� ������������ ����� ����������.
	bool m_bAskUser;
	//! ����, ������� ����.
	bool m_bUrgent;

	PoliType& MarshalImpl(PoliType& pt)
	{
		const int nThisVersion = 2;
		int nVersion = nThisVersion;
		pt << nVersion;
		switch (nVersion)
		{
		case 2: pt << m_sComment << m_bAskUser << m_bUrgent;
		case 1: pt << m_sPath << m_FromAppVersion << m_sToAppVersion;
			break;
		default: pt.set_error_(PoliType::eDataMoreRecent);
			break;
		}
		return pt;
	}
};

IMPLEMENT_MARSHAL(CPatchInfo);

//! ������ ������.
struct CPatchList: public CCBaseMarshal<PID_PATCH_LIST>
{
	CPatchList()
	{
	}

	typedef std::vector<CPatchInfo> CPatches;
	CPatches m_Patches;
	CSysTimeSer m_tmLastRebootPatchInstallTime; //!< ����� ��������� ���������� �����, �������������� ����������.

	PoliType& MarshalImpl(PoliType& pt)
	{
		const int nThisVersion = 2;
		int nVersion = nThisVersion;
		pt << nVersion;
		switch(nVersion)
		{
		case 2: pt << m_tmLastRebootPatchInstallTime;
		case 1: pt << m_Patches;
			break;
		default: pt.set_error_(PoliType::eDataMoreRecent); break;
		}
		return pt;
	}
};

IMPLEMENT_MARSHAL(CPatchList);

#endif