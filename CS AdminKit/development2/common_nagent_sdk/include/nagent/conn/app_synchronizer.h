#ifndef __KL_APP_SYNCHRONIZER_H__
#define __KL_APP_SYNCHRONIZER_H__

#include "./conn_types.h"
#include <kca/prss/settingsstorage.h>
#include <common/kllicinfo.h>

#define KLCONN_UPDATE_INFO_1            L"KLCONN_UPDATE_INFO_1"
#define KLCONN_LIC_INFO_1               L"KLCONN_LIC_INFO_1"
#define KLCONN_COMPONENTS_INFO_1        L"KLCONN_COMPONENTS_INFO_1"
#define KLCONN_CRITICAL_FIXES_INFO_1    L"KLCONN_CRITICAL_FIXES_INFO_1"
#define KLCONN_VAL_FIXES                L"KLCONN_VAL_FIXES"


namespace KLCONN
{
	/*!
      \brief ��������� ����������
    */    
    typedef enum
    {
        APP_STATE_INACTIVE,
        APP_STATE_RUNNING
    }AppState;

	/*!
      \brief �������, ���������� ���������� �������� �����������������.
    */    
    typedef enum
    {
        APP_ACTION_START,
        APP_ACTION_STOP
    }AppAction;


	/*!
      \brief �������, ���������� ���������� �������� �����������������.
    */    
    typedef enum
    {
        APP_RTP_STATE_UNKNOWN = 0,
        APP_RTP_STATE_STOPPED,
        APP_RTP_STATE_SUSPENDED,
        APP_RTP_STATE_STARTING,
        APP_RTP_STATE_RUNNING,
        APP_RTP_STATE_RUNNING_MAX_PROTECTION,
        APP_RTP_STATE_RUNNING_MAX_SPEED,
        APP_RTP_STATE_RUNNING_RECOMMENDED,
        APP_RTP_STATE_RUNNING_CUSTOM,
        APP_RTP_STATE_FAILURE
    }AppRtpState;

    /*!
    \brief ���������, ���������� �� ������������� ��������� ����������
	    � ���������� � ������� �����������������.

        ��������� ����������� ����������� ����������
        ��������� ������������ �������� �����������������.

        ������ ������� ���������� ����� ������������ �� ������ �����, �� ���
        ���� ������������� ���������� ��������.

    */

    class KLSTD_NOVTABLE AppSynchronizer : public KLSTD::KLBaseQI
    {
    public:

        /*!
          \brief	���������� ������ ����������
            � ������ ������ ������������� ���������� ���� KLERR::Error*

            \param	nState      [out] - ��������� ����������
            \param ppResult     [out]   �������������� ���������.
            \param tmRiseTime   [out]   ����� ���������� ������� � UTC.
        */
        virtual void GetAppStatus(
                                KLCONN::AppState&   nState,
                                KLPAR::Params**     ppResult,
                                raise_time_t&       tmRiseTime) = 0;

        /*!
          \brief	���������� ���������� ����������.
            � ������ ������ ������������� ���������� ���� KLERR::Error*

          \param	pFilter - ������; ������������ �������� �����, ��������� � �������.
          \param	ppStatistics - ������������ ���������� ����������
        */
        virtual void GetAppStatistics(
                                KLPAR::Params*  pFilter,
                                KLPAR::Params** ppStatistics) = 0;


        /*!
          \brief	�������� ���������� �������.
            � ������ ������ ������������� ���������� ���� KLERR::Error*

          \param	nAction - �������
          \param	pData - ������

          \exception STDE_NOTPERM - ������ ������� �� ��������������
        */
        virtual void SendAppAction(
                                KLCONN::AppAction   nAction,
                                KLPAR::Params*      pData) = 0;

        /*!
          \brief	���������� �������� ����������.

          \param	KLPAR::Params** ppData -- ��������� �� ����������
                        ����������. ��������� ����� ��������� ���������:
                    KLCONN_UPDATE_INFO_1
	                    KLPRSS_PRODVAL_INSTALLTIME      -- ����/����� ����������� ����������, DATE_TIME_T
	                    KLPRSS_PRODVAL_LASTUPDATETIME   -- ����/����� ���������� ����������, DATE_TIME_T
                        KLPRSS_PRODVAL_DISPLAYNAME      -- ������������ ��� �������� ��� ������ ���������, STRING_T
                        KLPRSS_PRODVAL_VERSION          -- ������ ������ ��������,  STRING_T
	                    KLPRSS_PRODVAL_BASEDATE         -- ����/����� ������������ ���, DATE_TIME_T
	                    KLPRSS_PRODVAL_BASEINSTALLDATE  -- ����/����� ��������� ������������ ���, DATE_TIME_T
	                    KLPRSS_PRODVAL_BASERECORDS      -- ���������� ������� � ������������ �����, INT_T

                    KLCONN_LIC_INFO_1
	                    KLPRSS_VAL_LIC_KEY_CURRENT          -- ���������� � ������� �����
		                    KLLIC::c_szwKeyType             -- ��� �����, INT_T
		                    KLLIC::c_szwKeyProdSuiteID      -- ������������� ��������, INT_T
		                    KLLIC::c_szwKeyAppID            -- ������������� ����������, INT_T
		                    KLLIC::c_szwKeyInstallDate      -- ����/����� ����������� �����, DATE_TIME_T
		                    KLLIC::c_szwKeyExpirationDate   -- ����/����� ��������� ����� �����, DATE_TIME_T
		                    KLLIC::c_szwKeyLicPeriod        -- ����� ����� �����, INT_T
		                    KLLIC::c_szwKeyLicCount         -- ���������� ��������, INT_T
		                    KLLIC::c_szwKeySerial           -- �������� �����, STRING_T
		                    KLLIC::c_szwKeyMajVer           -- ������ ��������, STRING_T
		                    KLLIC::c_szwKeyProdName		    -- ��� ��������, STRING_T
	                    KLPRSS_VAL_LIC_KEY_NEXT
		                    KLLIC::c_szwKeyType
		                    KLLIC::c_szwKeyProdSuiteID
		                    KLLIC::c_szwKeyAppID
		                    KLLIC::c_szwKeyInstallDate
		                    KLLIC::c_szwKeyExpirationDate
		                    KLLIC::c_szwKeyLicPeriod
		                    KLLIC::c_szwKeyLicCount
		                    KLLIC::c_szwKeySerial
		                    KLLIC::c_szwKeyMajVer
		                    KLLIC::c_szwKeyProdName
                    KLCONN_COMPONENTS_INFO_1
                        KLPRSS_VAL_PRODCOMPS                -- ������ �����������, ������� ����, ����������� � ����������, ARRAY_T|PARAMS_T
                            KLPRSS_VAL_NAME                 -- ��� ����������, STRING_T
                            KLPRSS_VAL_VERSION              -- ������ ����������, STRING_T
                    KLCONN_CRITICAL_FIXES_INFO_1
                        KLCONN_VAL_FIXES             -- ������ ����������� ���������� � ������� �� ���������, ARRAY_T|PARAMS_T
                            KLPRSS_PRODVAL_DISPLAYNAME      -- �������������� ������������ ��� ������������ ���������� -- ������ ������������ �������� Unicode ������ �� ����� 256 ��������, STRING_T
                            KLPRSS_VAL_NAME                 -- ����������� �� ����������� ������������� ������������ ���������� -- ������ �������� ������ �������� ������� ������� ������ �� ����� 64 �������, STRING_T

        */
        virtual void GetApplicationProperties(
                                KLPAR::Params** ppData) = 0;


        /*!
          \brief	���������� ��������� ������ ��������� �������. ����� 
                    ���������� ��� ����������, ������� ����� ������ 
                    ������������ (� ������� ��������� ���� 
                    CIF_PROVIDES_RTP � ���������� ConnectorFlags � ������ 
                    ����������� ����������).

          \param	nRtpState  OUT ��������� ������ ��������� �������
          \param	nErrorCode OUT ��� ������ ( ��� ��������� of APP_RTP_STATE_FAILURE)
        */
        virtual void GetRtpState(
                        AppRtpState&    nRtpState,
                        int&            nErrorCode) = 0;
    };
}
#endif //__KL_APP_SYNCHRONIZER_H__
