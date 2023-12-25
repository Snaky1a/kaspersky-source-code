/*!
 * (C) 2002 Kaspersky Lab 
 * 
 * \file	evp/transeventstypes.h
 * \author	Andrew Kazachkov
 * \date	10.12.2002 17:39:12
 * \brief	
 * 
 */

#ifndef __TRANSEVENTSTYPES_H__pekIqsSzPIaemCLoTrIpt1
#define __TRANSEVENTSTYPES_H__pekIqsSzPIaemCLoTrIpt1

#include "evperrors.h"
#include <common/serverinfo.h>
#include <kca/prci/prci_const.h>

namespace KLEVP
{
    // ! brief ��� ��������� � ����.Params, � ������� ����������� ������
    //     �� ��������� �������/��� �������, �����. ��� �������� � ������

    // ����� ���������� � ������� Params, ������� ������ ���� �������� � Policy ��� ����,
    // ����� ����� �����, �� ����� ������� ��� ������� ��� ���������

    //#define KLEVP_NF_DELETE_FLAG                L"KLEVP_NF_DELETE_FLAG"

    /*! brief KLEVP_NF_SECTION - ������ � policy, � ������ ��������� ���. � ���������. */
    #define KLEVP_NF_SECTION                    L"KLEVP_NF_SECTION"

    /*! brief ��������� Params, ���������� � ������ KLEVP_NF_SECTION (�������� ���������� ��. ����)
            KLEVP_NF_LIST_ID // STRING_T
            KLEVP_NF_PRSS_MAXIMUM_SIZE// INT_T
            KLEVP_NF_EVENT_LIST     // ARRAY_T, ���������� ������� ��.����:
                {
                    ...
                    {
                        KLEVP_NF_EVENT_TYPE             // STRING_T
                        KLEVP_NF_STORE_AT_EVENT_LOG     // BOOL_T
                        KLEVP_NF_STORE_AT_PRES          // BOOL_T
                    }
                    ...
                }
    */

    /* KLEVP_NF_LIST_ID - STRING_T ������������� ��������, ����������� �� ������� */
    #define KLEVP_NF_LIST_ID                    L"KLEVP_NF_LIST_ID"
    
    /*! brief KLEVP_NF_PRSS_MAXIMUM_SIZE - INT_T, ��������� ������������ ������ ��� �������� 
            EventStorage. ���� 0, �� ������� �� ��������� �� ������� ������. ��� ������� 
            ����������� ������� �������, ����������� ��� � EventStorage ��� ��������� �� ���� 
            �������� �� ������ */
    #define KLEVP_NF_PRSS_MAXIMUM_SIZE          L"KLEVP_NF_PRSS_MAXIMUM_SIZE"   

	/*	! brief KLEVP_NF_EVENTS_TO_SERVER_PERIOD - INT_T, ������ �������� ������� �� 
				������ �����������������, �����
	*/
	#define KLEVP_NF_EVENTS_TO_SERVER_PERIOD	L"KLEVP_NF_EVENTS_TO_SERVER_PERIOD"

    /* */
    #define KLEVP_NF_EVENT_LIST                 L"KLEVP_NF_EVENT_LIST"

    /*!brief KLEVP_NF_EVENT_TYPE - STRING_T, ��� ������� */
    #define KLEVP_NF_EVENT_TYPE                 L"KLEVP_NF_EVENT_TYPE"   

    /*!brief KLEVP_NF_STORE_AT_EVENT_LOG - BOOL_T, ���� true, �� ���� ��������� � EventLog'e ��������� ������. */
    #define KLEVP_NF_STORE_AT_EVENT_LOG         L"KLEVP_NF_STORE_AT_EVENT_LOG"  

    /*!brief KLEVP_NF_STORE_AT_PRES - BOOL_T, ���� true, �� ���� ��������� � PRES'e ��������� ������. */
    #define KLEVP_NF_STORE_AT_PRES              L"KLEVP_NF_STORE_AT_PRES"
    

    /*
    const wchar_t c_szw_E2S_EventList[]=L"EventList";

    const wchar_t c_szw_E2S_DeleteFlag[]=L"DeleteFlag";

    const wchar_t c_szw_E2S_Id[]=L"ListId";
    
    
    const wchar_t c_szw_E2S_ProductName[]=L"ProductName";
    const wchar_t c_szw_E2S_ProductVersion[]=L"ProductVersion";
    const wchar_t c_szw_E2S_EventType[]=L"EventType";

    const wchar_t c_szw_E2S_SectionName[] = KLPRSS_PRODUCT_NAME;
    const wchar_t c_szw_E2S_SectionVersion[] = KLPRSS_VERSION_CURRENT;
    const wchar_t c_szw_E2S_SectionSection[] = KLPRSS_SECTION_SERVER_LOCATION; */

// ���� ���������� ���� �������, �� ������� ����� ������������� ��������.
	
	const wchar_t c_szwGroupSyn[]=L"klevp-groupSyn";
    const wchar_t c_szwLocalTaskNFInfo[]=L"klevp-c_szwLocalTaskNFInfo";
    const wchar_t c_szwNFSSDirectChange[]=L"klevp-c_szwNFSSDirectChange";

    /* static const wchar_t* c_arrDefaultEventTypes [] = {
        c_szwAgentStart,
        KLPRCI::c_EventTaskState
    }; */
};
#endif //__TRANSEVENTSTYPES_H__pekIqsSzPIaemCLoTrIpt1

// Local Variables:
// mode: C++
// End:
