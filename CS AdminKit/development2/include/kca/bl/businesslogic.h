/*KLCSAK_PUBLIC_HEADER*/

#ifndef KLBL_BUSINESSLOGIC_H
#define KLBL_BUSINESSLOGIC_H

/*KLCSAK_BEGIN_PRIVATE*/
#include <vector>
#include <string>


#include <std/base/klbase.h>
#include <std/par/params.h>

#include <kca/prss/settingsstorage.h>

#include <kca/prci/componentid.h>
#include <kca/prcp/componentproxy.h>
/*KLCSAK_END_PRIVATE*/

namespace KLBL
{
/*KLCSAK_BEGIN_PRIVATE*/

    /*! ������� ������� ���������, �������������� � 1, � ������
        KLPRSS_COMPONENT_PRODUCT ��������� SS_PRODINFO ��������, ���
        ������� ����� ����� �������������� ���������� ����������.
        ���� ������� ����� �� ������ �������������� ���������� ����������,
        ������ �������� ���� �� ������� ��������� ���� � ���� �������
        ���������� 0.
    */
    const wchar_t c_szwAutoStartControl[] = L"AutoStartControl";//INT_T

    /*! � ������ ��������� �������� ������ �����������, ������� �������
        ��������� �������������. �������� ������ ��������� ������ �����������
        Params, ������ �� ������� �������� ������������ �������� 
        c_szwAutoStartComponentName � �������������� �������� 
        c_szwAutoStartRegValName (��. �����) - �� �������� ������� ��
        ������ ���������, ����������� � �����������.
    */
    const wchar_t c_szwAutoStartComponents[] = L"AutoStartComponents";//ARRAY_T|PARAMS_T

    /*!
        ��� ����������, ������������ � �����������. �������� 
        KLPRSS_COMPONENT_PRODUCT (��. ���� PRSS/SettingsStorage.h) 
        �������� ������� � �����.
    */
    const wchar_t c_szwAutoStartComponentName[] = L"ComponentName";//STRING_T


    /*!
        ������ �������� ������������ ������, ���� ��������� ����� ���
        ������� MTF_EXE � ���������� ������������ ����� ������ �������
        HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
        �������� ��������� ������������ ����� ��� ����������, �����������
        � ���������� ������ �������.
    */
    const wchar_t c_szwAutoStartRegValName[] = L"RegValName";//STRING_T
    /*!
        ������ ������ ��������� � SS_SETTINGS. ���� ���������� 
        c_szwAutoStartControl (��. ����) ����������� � 1, ������� �����
        ����������� ��������� ������ ������ � �������� ���������
        ����������� ����������. ������ �������� ���������� 
        c_szwAutoStartStates (��. ����).
    */
    #define KLBL_GLOBAL_AUTOSTART_SECTION   L"KLBL_GLOBAL_AUTOSTART"

    /*!
        �������� ���������� <��� ����������> ���� BOOL. ���� ���������� 
        � ������ X ����� �������� true, �� ��������� � ������ X ������
        ����������� �������������; �������� false ��������, ��� 
        �������������� ����� ��� ���������� � ������ X ��������.
       
        ���� ��������� c ������ <��� ����������> ����� ��� ������� MTF_EXE,
        �� ������� ����� ��� ����������� ���������� <��� ����������> �
        true, �������  � ������� ������� 
        HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
        ���������� � ������, ������������ � ����������
        c_szwAutoStartRegValName � ���������� � ��� ��������� ������
        ����������,  ������� ����� �� ���������� 
        <��� ����������>\KLPRSS_VAL_CUSTOMNAME.
        ��� ����������� ���������� c ������ <��� ����������> � false,
        �������  ����� ������� ���������� ���������� �������.

        ���� ��������� ����� ��� ������� MTF_NTSERVICE, ������� �����
        ������ ��� ������ ������ (��� ������ ������� ����� �� 
        <��� ����������>\KLPRSS_VAL_CUSTOMNAME).

        "��� ����������" ����� ��������� KLPRSS_COMPONENT_PRODUCT  
        (��. ���� PRSS/SettingsStorage.h).
    */

    const wchar_t c_szwAutoStartStates[] = L"AutoStartStates";//PARAMS_T

    //!OBSOLETE
    const wchar_t c_szwAutoStartEnabled[] = L"EnableAutoStart"; //BOOL_T

/*KLCSAK_END_PRIVATE*/
    
    /*! ������ ������� ������� ����������� ��� ���������� �������
        ������������ ����������. ������� �� ����� ����������.
    */
    const wchar_t c_szwFulscanCompletedEvent[]=L"KLBL_EV_FSCAN_COMPLETED";

    typedef enum
    {
        RtpState_Unknown = 0,
        RtpState_Stopped,
        RtpState_Suspended,
        RtpState_Starting,
        RtpState_Running,        
        RtpState_Running_MaxProtection,
        RtpState_Running_MaxSpeed,
        RtpState_Running_Recomended,
        RtpState_Running_Custom,
        RtpState_Failure
    }
    GlobalRptState;

/*KLCSAK_BEGIN_PRIVATE*/
    #define KLBL_GLOBAL_STATE_PRODUCT  KLPRSS_PRODUCT_CORE
    #define KLBL_GLOBAL_STATE_VERSION  KLPRSS_VERSION_INDEPENDENT
    #define KLBL_GLOBAL_STATE_SECTION  L"KLBL_GLOBAL_STATE_SECTION"

    /*! ������ (KLBL_GLOBAL_STATE_PRODUCT,
        KLBL_GLOBAL_STATE_VERSION, KLBL_GLOBAL_STATE_SECTION) ��������� �
        ��������� SS_PRODINFO.
        ��� ����������� ����������, �������������� RTP-������ ������
        �������� � ��� ������ ��������� ����������:
        c_swzValComponentRtpState
        c_swzValPathRtpState

    */

    /*!
        ���������, ������������ � ���������� ��������� Rtp � �����������
        ������� c_szwRptStateChengedEvent � ��� ���������. ������:
        <�������>/<������>/<���������>[/<���������>].
        ���� <���������> �����������, �������������� ����� ���������
        ���������.
    */
    const wchar_t c_swzValComponentRtpState[]=L"KLBL_GSVAL_COMPONENT_RTPSTATE";

    /*! ���� � ���������� ����������, ���������� � ������� ����������
        c_swzValComponentRtpState, � ���������� c_swzValRptState �
        c_swzValRptStateErrorCode
    */
    const wchar_t c_swzValPathRtpState[] = L"KLBL_GSVAL_VALPATH_RTPSTATE";
    
    //! ��������� rpt-������
    const wchar_t c_swzValRptState[]=L"KLBL_GSVAL_RPTSTATE";    //INT_T

    //! ��� ������ (��� ��������� RtpState_Failure)
    const wchar_t c_swzValRptStateErrorCode[]=L"KLBL_GSVAL_RPTSTATE_ECODE"; //INT_T

    /*! ������� c_szwRptStateChengedEvent ������� ����������� 
        ��� ��������� ��������� rpt-������.
        ��������� �������
            c_swzValRptState
            c_swzValRptStateErrorCode
    */
    const wchar_t c_szwRptStateChengedEvent[]=L"KLBL_EV_RPTSTATE_CHANGED";

    /*!
        ������ �������� �������������.
        ������ <product>/<version>/KLBL_UNINSTALL_OPTIONS �������������
        � SS_SETTINGS. 
        ������ �������� ��������� ����������
            szwUninstallPswdHash
    */
    #define KLBL_UNINSTALL_OPTIONS   L"KLBL_UNINSTALL_OPTIONS"

    /*!
		���������� �������� ��� MD5 ������ �������������. ��� ��������� 
        ��� ��������� ������ ������ (��� �������� ������� �� �����).
	*/
    const wchar_t szwUninstallPswdHash[] = L"KLBL_UNINST_PSWD_HASH";//BINARY_T

    /*!
		�������, ������� ������������, ����� ��������� ����������� � BL �����
		�� ������ ��������� ��������.
	*/
    const wchar_t c_szwActionAskedEvent[] = L"KLBL_EV_ACTION_ASKED";

    /*!
		�������, ������� ������������, ����� BL �������� ���������� �� ������
		� ������ ��������.
	*/
    const wchar_t c_szwActionResponsed[] = L"KLBL_EV_ACTION_RESPONSED";

    /*!
		\brief �������� ��������� � ��������� �������, �� ������� �������������
		�������� ������������.
    */

    struct EventToAsk{
		///< ������������� ����������, � ������� ��������� �������.
		KLPRCI::ComponentId id; 
		///< ��� �������, ������� ���������.
		std::wstring eventType;
		///< ���� �������.
		KLSTD::CAutoPtr<KLPAR::Params> eventBody;
		///< ������������� ������, ��� ������� ��������� �������. 
        long taskId;
		///< ��������� �������� ��� ������� �������.
		KLSTD::CAutoPtr<KLPAR::Params> actions;
	};

	typedef std::vector<KLSTD::KLAdapt<KLSTD::CAutoPtr<KLPRCP::ComponentProxy> > > proxies_t;

    /*!
		\brief	��������� ��������� ���������������� ������ ������-������ ���
				�����������-��������.
		������ ��������� ��������� �����������-�������� �������� ���������
		����������������:
		1)	��������� proxy �� ���������, ��������� ����������-�������. ���
			���� ������ BL �������� ��������� ��������������, ���� ���
			�����������.
		2)	������ ��������� �������� ��� ������������� ��� ��� ���� �������.
    */
    
    class BusinessLogicProxy : public KLSTD::KLBase
	{
    public:

    /*!
		\brief	����� ���������� ����������-������� proxy �� ���������
				���������.
		������ ����� ��������� "����� �� ����������". ���� ��������� ���������
		��� �������, ���� ����� ���������� proxy �� ���������� ���������, �
		���� ��������� �� �������, ��������� ��� � ��������� ��������. � �����
		������ �������� ����� ������� ���������, ������������ ������-�������
		����������.

        \param idServer [in] ������������� ���������� ����������-�������.
        \param idClient [in] ������������� ����������-�������, ������� �����
							������������ ���������-������.
        \param vecProxies [out] ������ proxy �� ��������� ����������-�������,
							������� ����� ������������ ���������-������.
		\param lTimeout [in] ����-���

		\exception	STDE_TIMEOUT ���� ����-���
       
    */
        virtual void GetComponentProxies (
						KLPRCI::ComponentId&	idServer,
						KLPRCI::ComponentId&	idClient,
						proxies_t&				vecProxies,
						long					lTimeout) = 0;

    /*!
		\brief	����� ���������� ����������-������� proxy �� ���������
				���������.
		������ ����� ��������� "����� �� ����������". ���� ��������� ���������
		��� �������, ���� ����� ���������� proxy �� ���������� ���������, �
		���� ��������� �� �������, ��������� ��� � ��������� ��������. � �����
		������ �������� ����� ������� ���������, ������������ ������-�������
		����������.

        \param idServer [in] ������������� ���������� ����������-�������.
        \param idClient [in] ������������� ����������-�������, ������� �����
							������������ ���������-������.
        \param vecIDs [out] ������ ComponentId ��������� �����������-��������,
							������� ����� ������������ ���������-������.
		\param lTimeout [in] ����-���

		\exception	STDE_TIMEOUT ���� ����-���
       
    */
        virtual void GetComponentIDs (
						KLPRCI::ComponentId&				idServer,
						KLPRCI::ComponentId&				idClient,
						std::vector<KLPRCI::ComponentId>&	vecIDs,
						long								lTimeout) = 0;

		/*!
		  \brief	���������� ���������� � ���������� ���������� ����������.
		  ������ ����, ������������ �������������� ��������:
			   KLSTD::CAutoPtr<KLPAR::Params> pInfo;
			   pBL->GetRuntimeInfo(id, KLSTD_INFINITE, &pInfo);
			   long nPid=KLPAR::GetIntValue(pInfo, KLPRSS_VAL_PID);

		  \param	id			[in] ������������� ���������� ����������
		  \param	lTimeout	[in] ����-��� ������� � ���������.
		  \param	ppInfo		[out] ��������� Params. �������� ���������
					����������: KLPRSS_VAL_INSTANCEPORT, KLPRSS_VAL_LASTSTART,
					KLPRSS_VAL_PID (��. ���� prss/settingsstorage.h)
										
		  \return	pid	��������
		*/
		virtual void GetRuntimeInfo(
					KLPRCI::ComponentId&	id,
					long					lTimeout,
					KLPAR::Params**			ppInfo) = 0;


    /*!
		\brief	����� ���������� ����������-������� ����� �� �������,
				����������� � ����������.
		���������-������ �������� ���� �����, ����� ��� ��������� ��������
		���������� � ���������� ������� �� ��������� �������. ��������
		������������� ������� ���������� � ��������� event. ��������� BL
		��������� ������� � ���, ��� ����������� �� ��� ������� (��������,
		���������� �� ���� ������������) � ���������� ���������� � ��������
		������� � ��������� action. ��� ���� ��������� BL ����� ������������
		���� ������� ACTION_ASKED, ACTION_RESPONSED.

        \param Event    [in] �������� �������, �� �������� ������������� ��������.
		\param lTimeout [in] ����-���
        \param ppAction   [out] ��������, ������� ���������� ��� ������� �������.

		\exception	STDE_TIMEOUT ���� ����-���
		\exception	STDE_UNAVAIL �� �������� ������ GUI
       
    */

        virtual void AskAction(
						EventToAsk&		Event,
						long			lTimeout,
						KLPAR::Params**	ppAction) = 0;


    /*!
		\brief	����� ���������� ������ ������ ���� (� ������) �����������
				������� (������ EXE), ������� �������� � ������ �������
				��������.

		\param vecNames [out] ������ ���� ����������� �������.
       
    */
		virtual void GetProcessNames(std::vector<std::wstring>& vecNames, long lTimeout) = 0;

    };

/*KLCSAK_END_PRIVATE*/
};

/*KLCSAK_BEGIN_PRIVATE*/
/*!
  \brief ������� ������ ������ BusinessLogicProxy.

  \param idComponent	[in] ������������� ����������, ������� ����� ������������ BusinessLogicProxy.
  \param ppBL			[out] ��������� ������ ������ BusinessLogicProxy.

*/



namespace KLBL
{
    typedef void (*pCreateBusinessLogicProxyProc_t)(
									KLPRCI::ComponentId&		idComponent,
									KLBL::BusinessLogicProxy**	ppBL);

    #define KLBL_BUSINESSLOGIC_PROXY_PROC   KLBL_CreateBusinessLogicProxyProc

    /*
    void KLBL_BUSINESSLOGIC_PROXY_PROC(
									    KLPRCI::ComponentId&		idComponent,
									    KLBL::BusinessLogicProxy**	ppBL);
    */

};

KLCSC_DECL void KLBL_CreateBusinessLogicProxy(
									KLPRCI::ComponentId&		idComponent,
									KLBL::BusinessLogicProxy**	ppBL);
/*KLCSAK_END_PRIVATE*/
#endif // KLBL_BUSINESSLOGIC_H
