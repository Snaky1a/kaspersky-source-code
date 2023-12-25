/*!
 * (C) 2004 "Kaspersky Lab"
 *
 * \file srvhrch/srvhrch.h
 * \author Andrew Lashenkov
 * \date	24.12.2004 18:54:00
 * \brief ����� ���������� ������ �������� ��������.
 *
 */

#include <std/base/klbase.h>

#ifndef KLSRVH_SRVHRCH_H
#define KLSRVH_SRVHRCH_H

namespace KLSRVH {

    //! ������������ ��������� ��������� ������������ �������.
    enum ChildServerStatus {
        CSS_VISIBLE =				0x00000001	//! ������ ������� � ������������ � ����.
    };

    //! �������� ������� ��������� ������������ �������.
	struct child_server_info_t {
		//! ������������� ������������ ������� (������������ ������������ ��������).
        long nId;	

		//! ������������ ��� �������.
        std::wstring wstrDisplName;	

		//! ������� ����� �������.
		std::wstring wstrNetAddress;	

		//! ������������� ������, � ������� ������� ������ ������.
        long nGroupId;	

		//! ����� ������ ������������ ������� 
        std::wstring wstrVersion;	

		//! InstanceID ������������ ������� 
        std::wstring wstrInstanceId;	

		//! ���������� ������ �� ChildServerStatus.
		int nStatus;		
	};


	//! ����� ��������� ����� � ���������� Params � ����������� � ����������� �������.

    //! INT_T, ������������� ������������ �������.
    const wchar_t c_srv_id[] = L"KLSRVH_SRV_ID";

    //! STRING_T, ������������ ��� �������
    const wchar_t c_srv_display_name[]	= L"KLSRVH_SRV_DN";

    //! INT_T, ������������� ������, � ������� ������� ������ ������.
    const wchar_t c_srv_group_id[] = L"KLSRVH_SRV_GROUPID";

    //! STRING_T, ������� ����� ������� (��� ��� IP-�����).
    const wchar_t c_srv_address[] = L"KLSRVH_SRV_ADDR";

	//! STRING_T, ������ ������������ �������.
    const wchar_t c_srv_version[] = L"KLSRVH_SRV_VERSION";

	//! STRING_T, ������������� ���������� ������������ �������.
    const wchar_t c_srv_instance_id[] = L"KLSRVH_SRV_INST_ID";

    //! BINARY_T, ���������� �������.
    const wchar_t c_srv_certificate[] = L"KLSRVH_SRV_CERTIFICATE";
	
    //! STRING_T, MD5-hash ���������� ����� �������.
    const wchar_t c_srv_public_key_hash[] = L"KLSRVH_SRV_PUBLIC_KEY_HASH";
	
    //! INT_T, ������� ��������� ������� �� ������������ ChildServerStatus.
    const wchar_t c_srv_status[] = L"KLSRVH_SRV_STATUS";

    //! PARAMS_T, �������������� ��������� �������.
    const wchar_t c_srv_params[] = L"KLSRVH_SRV_PARAMS";

    //! STRING_T, ������������� ����� ������������ �������.
    const wchar_t c_srv_host_guid[] = L"KLSRVH_SRV_HOST_GUID";
	
    //! INT_T, ������������� ����� ������������ �������.
    const wchar_t c_srv_host_id[] = L"KLSRVH_SRV_HOST_ID";

    //! INT_T, �������� ������ �������.
    const wchar_t c_srv_build_id[] = L"KLSRVH_SRV_BUILD_ID";
	
	/*
    //! TIME_T, ����� ������ ��������� ��� ��� �������� � ����.
    const wchar_t c_srv_last_visible[] = L"KLSRVH_SRV_LAST_VISIBLE";

    //! TIME_T, ��������� ����� ���������� ���������� � �������.
    const wchar_t c_srv_last_info_update[] = L"KLSRVH_SRV_LAST_INFOUDATE";
	*/
} // namespace KLSRVH

#define KLSRVH_SLAVE_REC_DEPTH L"KLSRVH_SLAVE_REC_DEPTH"

#endif // KLSRVH_SRVHRCH_H
