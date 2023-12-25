/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	updsrv.h
 * \author	Andrew Kazachkov
 * \date	28.05.2003 13:12:36
 * \brief	
 * 
 */

#ifndef __KL_UPDSRV_H__96D3468A_D243_4f26_8112_0D29586BA03E
#define __KL_UPDSRV_H__96D3468A_D243_4f26_8112_0D29586BA03E

#include <std/base/klbase.h>
#include <std/par/params.h>
//#include <srvp/updsrv/updatercompconstants.h>

namespace KLUPDSRV
{
    struct BundleOptions
    {
        std::wstring wstrBundleId;  //< id ������
        //bool bOrderToLoad;             //< ���� true, �� ��� ��������� �������� ����� ����� ��������, ���� false, �� �� ����� ��������.
        bool bAutoInstall;          //< ���� true, �� ����� ����� ������������ ������������� �� ���� �������. ����� ������� ����� ���� ��� �� �������� � ����� ������������.
    };

    struct GeneralOptions
    {
        bool bAutoInstallAVDB;
        bool bAutoInstallAllPatches;
        bool bAutoInstallAllUrgentUpdates;

        GeneralOptions() :
            bAutoInstallAVDB( false ),
            bAutoInstallAllPatches( false ),
            bAutoInstallAllUrgentUpdates( false ) {};
    };

    class KLSTD_NOVTABLE Updates : public KLSTD::KLBase
    {
    public:
        /*!
          \brief	GetUpdatesInfo - ���������� ������ ������������

          \param	pFilter ���� NULL, �� ����� ���������� ��� ���������� ��
                    ���� ���������. ����� ��������� ������ ID �������, ���
                    ������� ���� ���������� ������:
                        c_spUpdate_Bundles //ARRAY_T
                            c_spUpdate_BundleId //STRING_T

          \param	bIncludeDependantsInfo - ���� true, �� � ��������� ����� ��������
                        �������� c_spUpdate_BundleDependencies
                    
          \param	ppData - ���������
                        c_spUpdate_Bundles //ARRAY_T
                            c_spUpdate_BundleId //STRING_T
                            c_spUpdate_BundleName //STRING_T
                            c_spUpdate_BundleApp //STRING_T
                            c_spUpdate_BundleComponentList //ARRAY_T
                            c_spUpdate_BundleComponent //STRING_T
                            c_spUpdate_BundleToVersion //STRING_T
                            c_spUpdate_BundleComment //STRING_T
                            c_spUpdate_BundleStatus //STRING_T
                            c_spUpdate_BundleSize //LONG_T!!!!!!!!!!!!!!!!!!!!!!!
							c_spUpdate_BundleRecordsCount // LONG_T - ������ ��� ComponentidAVS
                            c_spUpdate_BundleType //STRING_T
                            c_spUpdate_BundleDate //DATE_TIME_T
                            c_spUpdate_BundleDownloadDate //DATE_TIME_T
                            c_spUpdate_BundlePostponedToLoad //BOOL_T
                            c_spUpdate_BundleFromVersions //PARAMS_T - �������� ���� version / fake bool value
                                <Version> // BOOL_T
                                <Version> // BOOL_T
                                <Version> // BOOL_T
                            [c_spUpdate_BundleDependencies] //ARRAY_T - ������������ ������ ���� bIncludeDependantsInfo = true, 
                                        // �������� Params ����� �� ���������, � ������� �������� ������ c_spUpdate_Bundles,
                                        // �� ��� �������� c_spUpdate_BundleDependencies (���� �� ������� ������).
                                        // �.�. ������������ �������� c_spUpdate_BundleId, c_spUpdate_BundleName, � �.�.
                                        // ������� �����, ������ ���� �����, ��������������� ����� �������� 
                                        // ������ ��������� ������ �����.
                                        // �����!!!! ������� c_spUpdate_BundleDependencies ����� �������������, ����
                                        // �����-���� �� ��� ���������� ����� ���� NULL!!!!

            ���� �������� c_spUpdate_BundleComponent ����� ComponentidAVS � �������� c_spUpdate_BundleType ����� SS_KEY_Desc,
                �� ���� ����� ��������� ������������ ����. ����� ����� ������ ������������ � ������������
                ����������.

            ���� � ������ c_spUpdate_BundleStatus==SS_KEY_PostponedAvailable, ��� ��������, ��� ���� ����� ���
                �� �������� � ������� ��. � ����� ������ ��� ����� ������ ����� ����� �����
                ������� SetBundleOptions() - ����� �������, ��� ��� ��������� ������� Updater'� ������ �����
                ����� ������� � ������� ��. ���� ��� ������ ��� �� ������� ����� ����� ������� ��������. ����
                �� � ������ �����-�� ������ ������, �� ����� ���� ������� ������ �� �����.
        */
        virtual void GetUpdatesInfo(
            KLPAR::Params* pFilter, bool bIncludeDependantsInfo, KLPAR::Params** ppData ) = 0;
        
        /*!
          \brief	SetBundleOptions - ������������� ����� ��� ������� ����������.

          \param	vectOrders - ������ � ���������� ��� ��������� �������. �������� bOrderToLoad 
                ����� �������� ������ ��� �������, � ������� ������ c_spUpdate_BundleStatus == SS_KEY_PostponedAvailable 
                (�.�. �������� � ��������, �� ��� �� ��������). ���� ������ ������, �� �������� bOrderToLoad ��� ������ ���� �������
                ��� ��������������� ������ ������������.
        */
        virtual void SetBundleOptions( const std::vector<BundleOptions> & vectOptions ) = 0;

        virtual void SetGeneralOptions( const GeneralOptions & generalOptions ) = 0;
        virtual GeneralOptions GetGeneralOptions() = 0;

    };

	/*
	enum EGetUpdatesTypesInfoParams{
		AvailableUpdateComps = 1,
		AvailableUpdateApps = 2, 
		InstalledComps = 4,
		InstalledApps = 8
	};
	*/

    class KLSTD_NOVTABLE Updates2 : public KLSTD::KLBaseQI{
    public:
		virtual void GetUpdates(Updates** ppUpdates) = 0;

		virtual void GetAvailableUpdatesInfo(
			const wchar_t* wszLocalization,
			KLPAR::Params** ppAvailableUpdateComps,
			KLPAR::Params** ppAvailableUpdateApps) = 0;

		virtual void GetRequiedUpdatesInfo(
			KLPAR::Params** ppInstalledComps,
			KLPAR::Params** ppInstalledApps) = 0;
	};
	
	enum AntiSpamProductType{
		AS_UNQNOWN,
		AS_AntiSpamPersonal_1_0,
		AS_AntiSpamPersonal_1_1,
		AS_SecuritySMTPGateway_5_5,
		AS_SecurityForExchange2003,
		AS_KasperskyAntiSpam_3_0
	};

};

KLCSSRVP_DECL void KLUPDSRV_CreateUpdatesProxy(
							const std::wstring&		wstrLocalComponentName,
							const std::wstring&		wstrConnName,
                            KLUPDSRV::Updates**     ppUpdates,
                            KLSTD::KLBase*          pParent=NULL);

KLCSSRVP_DECL KLUPDSRV::AntiSpamProductType KLUPDSRV_GetAntiSpamProductFromAppId(const std::wstring& wstrAppId);

KLCSSRVP_DECL void KLUPDSRV_GetAppIdsForAntiSpamProductType(KLUPDSRV::AntiSpamProductType type, std::vector<std::wstring>& appIds);

KLCSSRVP_DECL void KLUPDSRV_GetAllAntiSpamProducts(std::vector<KLUPDSRV::AntiSpamProductType>& vectAntiSpamPrds);

#endif //__KL_UPDSRV_H__96D3468A_D243_4f26_8112_0D29586BA03E

// Local Variables:
// mode: C++
// End:
