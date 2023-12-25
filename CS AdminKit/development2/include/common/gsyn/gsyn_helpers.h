/*!
 * (C) 2002 Kaspersky Lab 
 * 
 * \file	gsyn_helpers.h
 * \author	Andrew Kazachkov
 * \date	06.12.2002 19:35:11
 * \brief	���������������� ������� ��������� �������������
 * 
 */


#include <list>
#include <map>
#include <nagent/sync/ssync.h>
#include <srvp/gsyn/groupsync.h>

namespace KLGSYN
{

	//const wchar_t c_szwStoreVersion[]=L"gsyn_nStoreVersion";	//LONG_T
    const wchar_t c_szwStoreId[]=L"gsyn_nStoreId";	//STRING_T

	// ������������� �������������
	const std::wstring c_wstrGsynId=L"gsyn_idSync";
	// ��� ��������� ������������� (GSYN_DIRECTION)
	const std::wstring c_wstrGsynType=L"gsyn_nType";
	// ����-��� ��������� �������������
	const std::wstring c_wstrGsynTimeout=L"gsyn_lTimeout";
	// ������� �� �������������� ��������� �� ����� ������
	const std::wstring c_wstrGsynReplaceChanged=L"gsyn_bReplaceChanged";
	// ������������� ���� � ���������
	const std::wstring c_wstrLocation=L"gsyn_wstrLocation";
	// ����-��� ��������� �������������
	const std::wstring c_wstrGsynStoreTimeout=L"gsyn_lStoreTimeout";
	// �� ������� ������ ���������
	const wchar_t c_szwGsynSectionsToRead[]=L"gsyn-nSectionsToRead";

	// ��������� ������� KLEVP::c_szwGroupSyn
		const wchar_t ep_szwGroupSynType[]=L"nType"; // INT_T
		const wchar_t ep_szwGroupSynEvent[]=L"wstrEvent"; // STRING_T
			const wchar_t epv_szwEvent_Finished[]=L"finished";
			const wchar_t epv_szwEvent_FirstPassFinished[]=L"firstPassFinished";
		const wchar_t ep_szwGroupSynId[]=L"idSync"; // INT_T
		//const wchar_t ep_qwGroupSynVersion[]=L"qwVersion"; // LONG_T
		const wchar_t ep_szwGroupSyn_ServerTime[]=L"tmServerTime"; // DATETIME_T
	
	//
	typedef enum{
		sc_read_sections_changed=CSYNC::sc_last+1
	}gsync_command_t;

	//KLCSNAGT_DECL std::wstring MakeServerStoreLocation(const std::wstring& wstrRelative);
	//KLCSNAGT_DECL std::wstring MakeAgentStoreLocation(const std::wstring& wstrRelative);

    std::wstring GetClientStoreLocation(const std::wstring& wstrType);
/*
	KLCSNAGT_DECL AVP_qword RetrieveStoreVersion(KLPRSS::Storage* pStorage);
	KLCSNAGT_DECL void WriteStoreVersion(
				KLPRSS::Storage*		pStorage,
				AVP_qword				qwVersion);
*/	
};
