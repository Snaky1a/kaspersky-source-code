/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	policies.h
 * \author	Mikhail Karmazine
 * \date	09.04.2003 19:02:43
 * \brief	��������� ��� �������������� Policy
 * 
 */


#ifndef __KLPOL_POLICIES_H__
#define __KLPOL_POLICIES_H__

#pragma warning  (disable : 4786 )
#include <vector>

#include <std/base/klbase.h>
#include <std/trc/trace.h>
#include <kca/prssp/prsspclient.h>

namespace KLPOL
{
    /*! 
        \brief PolicyId - ���, �������������� � �������� 
        ����������� �������������� ��� policy */
    typedef long PolicyId;

    /*!
        \brief PolicyCommonData - ����� ������ ��� policy. */
    struct PolicyCommonData
    {
        std::wstring wstrDisplayName;
        std::wstring wstrProductName;
        std::wstring wstrProductVersion;
        time_t tCreated;
        time_t tModified;
        bool bInherited;
        long nGroupSyncId; //< id ��������� �������������
    };

    typedef std::pair<PolicyId, PolicyCommonData> PolicyIdAndCommonData;
    typedef std::vector<PolicyIdAndCommonData> PoliciesVector;

    class AddSuperPolicyCallback
    {
    public:
        virtual void OnPolicySsCreating(const wchar_t* szwPath) = 0;
    };

    /*!
        \brief Policies - ��������� ��� �������������� Policies */
    class Policies : public KLSTD::KLBaseQI
    {
    public:

        /*!
          \brief	GetPolicyCommonData - ������ ����� ������ ���� ������� 

          \param	 long nGroupId [in] - ID ������
          \param	 PoliciesVector & vectPolicies [out] - ������ ��������� � ���� ����� 
                        ������ ��� ���� policy ������ ������. ID policy ��������� �����
                        ���� policy ���� �����.
        */
        virtual void GetPolicyCommonData( long nGroupId, PoliciesVector & vectPolicies ) = 0;

        /*!
          \brief	GetPolicyCommonData - ������ ����� ������ ����� ������� 

          \param	 long nGroupId [in] - ID ������
          \param	 PolicyCommonData & policyCommonData [out] - ����� ������ ��� policy � ������� ID.
        */
        virtual void GetSinglePolicyCommonData(
            const PolicyId & policyId,
            PolicyCommonData & policyCommonData ) = 0;


        /*!
          \brief	AddPolicy - ���������� policy.

          \param    long nGroupId [in] - ID ������, � ������� ���� ��������� policy.
          \param	PolicyCommonData & policyCommonData [in/out] - ����� ������ ��� ����� policy.
          \return	PolicyId - ID ����� policy.
        */
        virtual PolicyId AddPolicy( long nGroupId, PolicyCommonData & policyCommonData ) = 0;

        /*!
          \brief	UpdatePolicyCommonData - ��������� ����� ������ �������� 

          \param    policyId [in] - id ��������, ����� ������ ������� ���� ��������.
          \param	PolicyCommonData & policyCommonData [in/out] - ����� ������ ��� ����� policy.
                �� ��������� PolicyCommonData ����� �������� ������ ���������:
                    wstrDisplayName [in]
                    tModified [out] !!! ���� ������ ����� ���� !!!
        */
        virtual void UpdatePolicyCommonData(
            const KLPOL::PolicyId & policyId,
            PolicyCommonData & policyCommonData ) = 0;

        /*!
          \brief	CopyPolicy - ����������� policy.

          \param    policyId [in] - id ��������, ������� ���� �����������.
          \param    long nNewGroupId [in] - ID ��� ������, � ������� ���� ����������� policy.
          \return	PolicyId - ID ����� policy.
        */
        virtual KLPOL::PolicyId CopyPolicy( const KLPOL::PolicyId & policyId, long nNewGroupId ) = 0;

        /*!
          \brief	MovePolicy - ����������� policy.

          \param    policyId [in] - id ��������, ������� ���� �����������.
          \param    long nNewGroupId [in] - ID ��� ������, � ������� ���� ����������� policy.
          \return	PolicyId - ID ����� policy (������� �������� ������ � ��������� ����� ��������)
        */
        virtual KLPOL::PolicyId MovePolicy( const KLPOL::PolicyId & policyId, long nNewGroupId ) = 0;

        /*!
          \brief    DeletePolicy - �������� policy.

          \param	const PolicyId & policyId [in] - ID ��������� policy.
          \return	void 
        */
        virtual void DeletePolicy( const PolicyId & policyId ) = 0;


        /*!
          \brief    GetPolicySettings - ��������� �������� policy.

          \param	const PolicyId & policyId [in] - ID policy.
          \param	nTimeout - ����� � ����, � ������� �������� �� ������� ����� 
                        ���� SettingsStorage.
          \return	CAutoPtr<KLPRSS::SettingsStorage> - ��������� ��� ������ � ����������� policy.
  
        */
        virtual KLSTD::CAutoPtr<KLPRSSP::SettingsStorageWithApply>
            GetPolicySettings( const PolicyId & policyId, long nTimeout ) = 0;


        /*!
          \brief	GetSSId - ������� ��� ����������� �������������.

          \param	const PolicyId & policyId
          \param	long nTimeout
          \param	std::wstring wstrId
        */
        virtual void GetSSId(
            const PolicyId & policyId,
            long nTimeout,
            std::wstring & wstrId ) = 0;


        /*!
          \brief	GetSSRelease - ������� ��� ����������� �������������.

          \param	const std::wstring & wstrId
        */
        //virtual void SSRelease( const std::wstring & wstrId ) = 0;

        virtual PolicyId RecreateSuperPolicy(
                                long nSuperGroupId,
                                const std::wstring& wstrProduct,
                                const std::wstring& wstrVersion,
                                AddSuperPolicyCallback* pCallback) = 0;

        virtual void DeleteSuperPolicy(
                                long nSuperGroupId,
                                const std::wstring& wstrProduct,
                                const std::wstring& wstrVersion) = 0;
    };
};

#endif //__KLPOL_POLICIES_H__
