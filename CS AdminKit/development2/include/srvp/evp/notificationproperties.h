/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file evp/notificationproperties.h
 * \author ������ ��������
 * \date 14:21 22.11.2002
 * \brief ��������� ��� ��������� � �������������� ���������� ����������� � ��������,
 *		����������� � �������. ������ ���������� ���� ��������� ��� ����������� 
 *		����������������� (��������, ��� snap-in'�).
 *
 */

/*!
* \brief ��������� ��������� ���������������� �� ��������� � �������������� �������� 
*		����������� � ��������, ������������������ �� �������.
*
*		����������� ���������������:
*			�) ����� e-mail (�.�. ���������� ������� SMTP ������ � ���������� e-mail)
*			
*			�) � ������� net send, ��� ����� ����� ������� ���������, �� ������� ��������
*					���������.
*			
*			�) � ������� ���������� ��������� ������������� ������� (��� exe-�����)
*		
*		��������� ����� ���� ��� ����� ��� ����, ��� � ����������������� ��� ��������� �������� -
*		��������, ��� ������� "Virus detected", ���������� �� �������� "Kaspersky Antivirus".
*		��� ���� ������������������ ��������� ����������� ��������� �����. ����� ����, ��������
*		��������� ������������� �������� - ��������, ��� ���� �������, ���������� ��
*		�������� "Kaspersky Antivirus". ��� ��������, ��� ������� "Virus detected", �����������
*		�� ������ ��������. 
*		
*		��� ����:
*		1. ���������� ��� ���� �������, ����������� ������� ����� ���������������� ���������. 
*			��� ������, ������� � ��� �������.
*			
*		2. ��� ����������� ����, ����� ��������� ��������� ���� ������������, �������� 
*			��������� �������: ����� �������� ������������� ����������� ����� ��������.
*			
*		3. ��� ����������� ������������� ������������� ������������ merge ��������.
*			����� �������� ����� ��������. ��������, ���� �� �����:
*
*			3.1 � ������� ������� ���� ���������, � �� ���� ����������, ����� ������ ��������� ������������.
*			
*			3.2 ��������� ������������� - ���� � ������� "Virus detected" �� ���� ���������
*			��������� ����������� �� e-mail ��� "user1@bbb.com", � � 
*			�������� "Kaspersky Antivirus" ��� ���� ������� ����� "user2@bbb.com", ��
*			����������� ���������� ����� �������������.
*			
*			3.3 ��������� ��������������� - ��������, ��� "Store information about event 
*			in the database for NNN days" NNN ����� ������� ������������.
*			
*			...
*			
*			3.N ��������� �������� ��� �����-�� ����������� ��������.
*			
*/


#ifndef _KLNOTIFICATPROPS_H__011D27B2_EFF7_48fe_BBF5_3FCFCBB876AC__
#define _KLNOTIFICATPROPS_H__011D27B2_EFF7_48fe_BBF5_3FCFCBB876AC__

#include <std/par/params.h>

// String params:
#define KLEVP_NPAR_SEVERITY_STRING     L"SEVERITY"
#define KLEVP_NPAR_SOURCE_HOST         L"COMPUTER"
#define KLEVP_NPAR_SOURCE_DOMAIN       L"DOMAIN"
#define KLEVP_NPAR_TYPE                L"EVENT"
#define KLEVP_NPAR_DESCR               L"DESCR"
#define KLEVP_NPAR_RISE_TIME           L"RISE_TIME"
#define KLEVP_NPAR_TSK_DISPLAY_NAME    L"KLCSAK_EVENT_TASK_DISPLAY_NAME"
#define KLEVP_NPAR_PRODUCT             L"KL_PRODUCT"
#define KLEVP_NPAR_VERSION             L"KL_VERSION"
#define KLEVP_NPAR_SEVERITY_NUM        L"KLCSAK_EVENT_SEVERITY_NUM"
#define KLEVP_NPAR_SOURCE_HOST_IP      L"HOST_IP"
#define KLEVP_NPAR_SOURCE_HOST_CONN_IP L"HOST_CONN_IP"

#define KLEVP_MSG_TEMPL_BOUNDARY       L"%" // will work if it is one symbol. Otherwise change EventsProcessorImpl::GetMessageText() function.
#define _BOUND_STRING(S) L"%"##S##L"%"
#define _MSG_TEMPL(S)  _BOUND_STRING(S)

#define KLEVP_MSG_TEMPL_SEVERITY_STRING     _MSG_TEMPL(KLEVP_NPAR_SEVERITY_STRING)
#define KLEVP_MSG_TEMPL_SEVERITY_NUM        _MSG_TEMPL(KLEVP_NPAR_SEVERITY_NUM)
#define KLEVP_MSG_TEMPL_SOURCE_HOST         _MSG_TEMPL(KLEVP_NPAR_SOURCE_HOST)
#define KLEVP_MSG_TEMPL_SOURCE_DOMAIN       _MSG_TEMPL(KLEVP_NPAR_SOURCE_DOMAIN)
#define KLEVP_MSG_TEMPL_TYPE                _MSG_TEMPL(KLEVP_NPAR_TYPE)
#define KLEVP_MSG_TEMPL_DESCR               _MSG_TEMPL(KLEVP_NPAR_DESCR)
#define KLEVP_MSG_TEMPL_RISE_TIME           _MSG_TEMPL(KLEVP_NPAR_RISE_TIME)
#define KLEVP_MSG_TEMPL_TSK_DISPLAY_NAME    _MSG_TEMPL(KLEVP_NPAR_TSK_DISPLAY_NAME)
#define KLEVP_MSG_TEMPL_PRODUCT				_MSG_TEMPL(KLEVP_NPAR_PRODUCT) 
#define KLEVP_MSG_TEMPL_VERSION				_MSG_TEMPL(KLEVP_NPAR_VERSION) 
#define KLEVP_MSG_TEMPL_SOURCE_HOST_IP		_MSG_TEMPL(KLEVP_NPAR_SOURCE_HOST_IP)
#define KLEVP_MSG_TEMPL_SOURCE_HOST_CONN_IP	_MSG_TEMPL(KLEVP_NPAR_SOURCE_HOST_CONN_IP)
// Obsolete:
#define KLEVP_MSG_TEMPL_TIME                _MSG_TEMPL(L"TIME") 

#define KLEVP_ENV_VAR_SEVERITY_STRING		KLEVP_NPAR_SEVERITY_STRING
#define KLEVP_ENV_VAR_SEVERITY_NUM			KLEVP_NPAR_SEVERITY_NUM
#define KLEVP_ENV_VAR_SOURCE_HOST			KLEVP_NPAR_SOURCE_HOST
#define KLEVP_ENV_VAR_SOURCE_DOMAIN			KLEVP_NPAR_SOURCE_DOMAIN
#define KLEVP_ENV_VAR_TYPE					KLEVP_NPAR_TYPE
#define KLEVP_ENV_VAR_DESCR					KLEVP_NPAR_DESCR
#define KLEVP_ENV_VAR_RISE_TIME				KLEVP_NPAR_RISE_TIME
#define KLEVP_ENV_VAR_TSK_DISPLAY_NAMEE		KLEVP_NPAR_TSK_DISPLAY_NAME
#define KLEVP_ENV_VAR_PRODUCT				KLEVP_NPAR_PRODUCT
#define KLEVP_ENV_VAR_VERSION				KLEVP_NPAR_VERSION
#define KLEVP_ENV_VAR_SOURCE_HOST_IP		KLEVP_NPAR_SOURCE_HOST_IP
#define KLEVP_ENV_VAR_SOURCE_HOST_CONN_IP	KLEVP_NPAR_SOURCE_HOST_CONN_IP

#define	KLTSK_VIRTUAL_DAYS_TO_STORE_EVENTS	-1
#define KLTSK_DEFAULT_DAYS_TO_STORE_EVENTS	7

namespace KLEVP {

	/*!
    * \brief notification_descr_t - ������� � ������ �����������.
	*
	*/
    /*
     *	���������� ���������
     */
	struct notification_descr_t
	{
		std::wstring	wstrProduct;
        std::wstring	wstrVersion;
		std::wstring	wstrEventType;
        long            nSeverity;

        std::wstring	wstrSMTPServer;
        long            nSMTPPort;
		std::wstring	wstrEMail;
        bool            bUseEmail;

		std::wstring	wstrNetSendParameter;
        bool            bUseNetSend;

		std::wstring	wstrScript;
        bool            bUseScript;

		long			lDaysToStoreEvent;
        std::wstring	wstrMessageTemplate;
        bool            bStoreAtSeverEventLog;
        bool            bStoreAtClientEventLog;
        bool            bStoreAtClientPRES;
        
        KLSTD::CAutoPtr<KLPAR::Params> pBodyFilter;

        notification_descr_t()
        {
            nSMTPPort = 0;
		    lDaysToStoreEvent = 0;
            nSeverity = 0;
            bStoreAtSeverEventLog = false;
			bUseNetSend = false;
			bUseScript = false;
			bUseEmail = false;
        }
	};
    
	struct notification_descr_t2: public notification_descr_t{
		std::wstring	wstrEMailSubj;
		std::wstring	wstrEMailFrom;
		std::wstring	wstrEMailESMTPUserName;
		std::wstring	wstrEMailESMTPUserPassword;
	};

    struct MessageArguments
    {
        std::wstring wstrDomain;
        std::wstring wsrtHost;
        std::wstring wstrEventType;
        std::wstring wstrEventTypeDispl;
        time_t tEventTime;
        int nEventSeverity;
        std::wstring wstrDescripton;
        std::wstring wstrTaskDislpayName;
		// Added by Andrey Bryksin 4/3/2005
		std::wstring wstrAttachment;
		// Added by Andrey Lashchenkov 07/09/2005
		std::wstring wstrProductId;
		std::wstring wstrProductDisplayName;
		std::wstring wstrDisplayVersion;
		unsigned long ulHostIP;
		unsigned long ulHostConnectIP;
		// Added by Andrey Lashchenkov 27/10/2005
		//std::wstring wsrtWinHostName;
		std::wstring wsrtHostDisplayName;

		// Added by Andrey Bryksin 4/3/2005
        std::wstring GetMessageSeverity() const;
    };

    // ��� ���������� STRING_T, ���������� �������������, ������������ �� �������:
    const wchar_t c_NotificationDescrId[]    = L"KLEVP_NOTIFICATION_DESCR_ID";

    // ��� ���������� STRING_T, ���������� �������������, ������������ �� �������:
    const wchar_t c_NotificationDescrChecksum[]    = L"KLEVP_NOTIFICATION_CHECKSUM";

    // old stuff
    const wchar_t c_NotificationDescrArray[]    = L"KLEVP_NOTIFICATION_DESCR_ARRAY";

    // ��� ���������� ARRAY_T, ������� �� Params, �������������� notification_descr_t
    // ��������� notification_descr_t:
    const int c_nNFDescrSize = 3;

    // ����� ����� c_NF*Descr ������ ���� c_nNFDescrSize:
    const wchar_t c_NFInfoDescr[]      = L"INF";  // ��� ������� � severity = info
    const wchar_t c_NFWarningDescr[]   = L"WRN"; // ��� ������� � severity = warning
    const wchar_t c_NFErrorDescr[]     = L"ERR"; // ��� ������� � severity = error
    const wchar_t c_NFCriticalDescr[]  = L"CRT"; // ��� ������� � severity = critical

    
    // ����� ���������� � ���������� c_NDFld_Product: 
    const wchar_t c_NDFld_Product[]             = L"KLEVP_ND_PRODUCT";				// STRING_T
    const wchar_t c_NDFld_Version[]             = L"KLEVP_ND_VERSION";				// STRING_T

    const wchar_t c_NDFld_EventType[]           = L"KLEVP_ND_EVETN_TYPE";			// STRING_T
    const wchar_t c_NDFld_SMTPServer[]          = L"KLEVP_ND_SMTP_SERVER";			// STRING_T
    const wchar_t c_NDFld_SMTPPort[]            = L"KLEVP_ND_SMTP_PORT";			// STRING_T
    const wchar_t c_NDFld_EMail[]               = L"KLEVP_ND_EMAIL";				// INT_T
    const wchar_t c_NDFld_UseEmail[]            = L"KLEVP_ND_USE_EMAIL";			// BOOL_T
    const wchar_t c_NDFld_NetSend[]             = L"KLEVP_ND_NET_SEND";				// STRING_T
    const wchar_t c_NDFld_UseNetSend[]          = L"KLEVP_ND_USE_NET_SEND";			// BOOL_T
    const wchar_t c_NDFld_Script[]              = L"KLEVP_ND_SCRIPT";				// STRING_T
    const wchar_t c_NDFld_UseScript[]           = L"KLEVP_ND_USE_SCRIPT";			// BOOL_T
    const wchar_t c_NDFld_DaysToStoreEvent[]    = L"KLEVP_ND_DAYS_TO_STORE_EVENT";	// INT_T
    const wchar_t c_NDFld_MessageTemplate[]     = L"KLEVP_ND_MESSAGE_TEMPLATE";		// STRING_T
    const wchar_t c_NDFld_EmailFrom[]			= L"KLEVP_ND_EMAIL_FROM";			// STRING_T
    const wchar_t c_NDFld_EmailSubject[]		= L"KLEVP_ND_EMAIL_SUBJECT";		// STRING_T
    const wchar_t c_NDFld_EmailESMTPUserName[]	= L"KLEVP_ND_EMAIL_ESMTP_USER";		// STRING_T
    const wchar_t c_NDFld_EmailESMTPUserPassword[] = L"KLEVP_ND_EMAIL_ESMTP_PASSWORD";	// STRING_T
    const wchar_t c_NDFld_StoreAtServerLog[]    = L"KLEVP_ND_STORE_AT_SERVER_LOG";	// BOOL_T
    const wchar_t c_NDFld_StoreAtClientLog[]    = L"KLEVP_ND_STORE_AT_CLIENT_LOG";	// BOOL_T
    const wchar_t c_NDFld_StoreAtClientPRES[]   = L"KLEVP_ND_STORE_AT_CLIENT_PRES"; // BOOL_T
    const wchar_t c_NDFld_BodyFilter[]          = L"KLEVP_ND_BODY_FILTER";			// BOOL_T
    const wchar_t c_NDFld_DenyDefaults[]		= L"KLEVP_ND_DENY_DEFAULTS";		// BOOL_T

    // internal stuff
    const wchar_t c_NLMaxEventsToSendPerPeriod[]= L"KLEVP_MAX_EVENTS_TO_SEND_PER_PERIOD";	// INT_T
    const wchar_t c_NLTestPeriodToSendEvent[]   = L"KLEVP_TEST_PERIOD_TO_SEND_EVENTS";		// INT_T
    const wchar_t c_NLMaxVirusEventsForOutbreakFiles[]= L"KLEVP_MAX_VIRUS_EVENTS_FOR_OUTBREAK";	// INT_T
    const wchar_t c_NLMaxVirusEventsForOutbreakEmail[]= L"KLEVP_MAX_VIRUS_EVENTS_FOR_OUTBREAK_E";	// INT_T
    const wchar_t c_NLMaxVirusEventsForOutbreakPerim[]= L"KLEVP_MAX_VIRUS_EVENTS_FOR_OUTBREAK_P";	// INT_T
    const wchar_t c_NLTestPeriodToOutbreakFiles[]	= L"KLEVP_TEST_PERIOD_TO_OUTBREAK";			// INT_T
    const wchar_t c_NLTestPeriodToOutbreakEmail[]	= L"KLEVP_TEST_PERIOD_TO_OUTBREAK_E";			// INT_T
    const wchar_t c_NLTestPeriodToOutbreakPerim[]	= L"KLEVP_TEST_PERIOD_TO_OUTBREAK_P";			// INT_T

	enum EVirusOutbreakType{
		VOT_FILESYSTEM	= 1,
		VOT_EMAIL		= 2,
		VOT_PERIMETER	= 4
	};

	const size_t VOT_COUNT = 3;
    
    const AVP_dword VOT_MASK = ~(unsigned(-1) << VOT_COUNT);

	class VirusOutbreakSource{
	public:
		EVirusOutbreakType m_eType;
        int m_nMaxVirusEventsForOutbreak;
        int m_nTestPeriodToOutbreak;
        VirusOutbreakSource(EVirusOutbreakType eType = VOT_FILESYSTEM) 
		:
			m_eType(eType),
            m_nMaxVirusEventsForOutbreak(0),
            m_nTestPeriodToOutbreak(0)
		{
		}

        bool CheckVirusOutbreak() const
        {
            return ( m_nMaxVirusEventsForOutbreak > 0 ) && ( m_nTestPeriodToOutbreak > 0 );
        };

		bool GetParamsNames(std::wstring& wstrMaxVirusEvents, std::wstring& wstrTestPeriod) const
		{
			return GetParamsNames(m_eType, wstrMaxVirusEvents, wstrTestPeriod);
		}

		static bool GetParamsNames(EVirusOutbreakType eType, std::wstring& wstrMaxVirusEvents, std::wstring& wstrTestPeriod)
		{
			switch( eType ) 
			{
				case VOT_FILESYSTEM:
					wstrMaxVirusEvents = c_NLMaxVirusEventsForOutbreakFiles;
					wstrTestPeriod = c_NLTestPeriodToOutbreakFiles;
					break;
				case VOT_EMAIL:
					wstrMaxVirusEvents = c_NLMaxVirusEventsForOutbreakEmail;
					wstrTestPeriod = c_NLTestPeriodToOutbreakEmail;
					break;
				case VOT_PERIMETER:
					wstrMaxVirusEvents = c_NLMaxVirusEventsForOutbreakPerim;
					wstrTestPeriod = c_NLTestPeriodToOutbreakPerim;
					break;
				default:
					return false;
			}
			return true;
		}
	};

    struct NotificationLimits
    {
        int nMaxEventsToSendPerPeriod;
        int nTestPeriodToSendEvents;

		std::vector<VirusOutbreakSource> m_vecVirusOutbreakSources;

        bool UseLimits() const
        {
            return ( nMaxEventsToSendPerPeriod > 0 ) && ( nTestPeriodToSendEvents > 0 );
        };

        NotificationLimits() :
            nMaxEventsToSendPerPeriod(0),
            nTestPeriodToSendEvents(0){};

		VirusOutbreakSource& GetVirusOutbreakSettings(EVirusOutbreakType eType)
		{
			for( size_t i = 0; i < m_vecVirusOutbreakSources.size(); ++i )
			{
				if( m_vecVirusOutbreakSources[i].m_eType == eType )
				{
					return m_vecVirusOutbreakSources[i];
				}
			}
			VirusOutbreakSource vo(eType);
			m_vecVirusOutbreakSources.push_back(vo);
			return m_vecVirusOutbreakSources[m_vecVirusOutbreakSources.size()-1];
		}

		void SetVirusOutbreakSettings(
			EVirusOutbreakType eType, int nMaxVirusEventsForOutbreak, int nTestPeriodToOutbreak)
		{
			/*
			for( size_t i = 0; i < m_vecVirusOutbreakSources.size(); ++i )
			{
				if( m_vecVirusOutbreakSources[i].m_eType == eType )
				{
					m_vecVirusOutbreakSources[i].m_nMaxVirusEventsForOutbreak = nMaxVirusEventsForOutbreak;
					m_vecVirusOutbreakSources[i].m_nTestPeriodToOutbreak = nTestPeriodToOutbreak;
					return;
				}
			}
			VirusOutbreakSource vo(eType);
			vo.m_nMaxVirusEventsForOutbreak = nMaxVirusEventsForOutbreak;
			vo.m_nTestPeriodToOutbreak = nTestPeriodToOutbreak;
			m_vecVirusOutbreakSources.push_back(vo);
			*/
			VirusOutbreakSource& vo = GetVirusOutbreakSettings(eType);
			vo.m_nMaxVirusEventsForOutbreak = nMaxVirusEventsForOutbreak;
			vo.m_nTestPeriodToOutbreak = nTestPeriodToOutbreak;
		}

		bool IsVirusOutbreakActive()
		{
			for( size_t i = 0; i < m_vecVirusOutbreakSources.size(); ++i )
			{
				if( m_vecVirusOutbreakSources[i].m_nMaxVirusEventsForOutbreak > 0 &&  
					m_vecVirusOutbreakSources[i].m_nTestPeriodToOutbreak > 0 )
				{
					return true;
				}
			}
			return false;
		}
    };
    
	/* brief �������� ��.����.
	*
	   ���������� ���������
	*/
    class KLSTD_NOVTABLE NotificationProperties : public KLSTD::KLBaseQI {
    public:
		virtual void GetDefaultSettings(
            std::wstring & wstrSMTPServer,
            long & nSMTPPort,
		    std::wstring & wstrEMail,
            bool & bUseEmail,
		    std::wstring & wstrNetSendParameter,
            bool & bUseNetSend,
		    std::wstring& wstrScript,
            bool & bUseScript,
            std::wstring & wstrMessageTemplate ) = 0;

		virtual void SetDefaultSettings(
            const std::wstring & wstrSMTPServer,
            long nSMTPPort,
		    const std::wstring & wstrEMail,
            bool bUseEmail,
		    const std::wstring & wstrNetSendParameter,
            bool bUseNetSend,
		    const std::wstring & wstrScript,
            bool bUseScript,
            const std::wstring & wstrMessageTemplate ) = 0;
        
		virtual void TestEmail(
            const std::wstring & wstrSMTPServer,
            long nSMTPPort,
		    const std::wstring & wstrEMail,
            const std::wstring & wstrMessageTemplate ) = 0;

		virtual void TestNetSend(
            const std::wstring & wstrNetSendParameter,
            const std::wstring & wstrMessageTemplate ) = 0;

		virtual void TestScript(
            const std::wstring & wstrScript,
            const std::wstring & wstrMessageTemplate ) = 0;

        virtual KLEVP::NotificationLimits GetNotificationLimits() = 0;

        virtual void SetNotificationLimits( const NotificationLimits & nl ) = 0;

		/*! 
		  \brief ����� ������ ��������� �����������, �� ������������������ �� �������, 
					��, ��������, ������������������ �� ����� ������� � �� ����������.
			\param vectNotificationDescr [out] - ���������. ���� � �������� �������
			notification_descr_t::notificationCondition   �������� wstrProduct � wstrEventType - 
			��� ������ ������, �� ��� ����� ����� ���������. ���� ������ ���� �� ���� ��������� - ������ ������,
			�� ���� ������� ������� �������� �������������. ���� ��� �������� �������� �����-�� �������� - ��
			���� ������� ��������� ������ ������������� ��� ����� �������� (������������� ��������� 
			���������������� ��������). 
			vectNotificationDescr ������ �������� ��� �������� ���� ������� � ������ �����������.

		*/
        /* ���������� ����� */
		virtual void GetCommonProperties(
			std::vector<notification_descr_t>& vectNotificationDescr ) = 0;


		/*! 
		  \brief ����� ������ ��������� ����������� ��� ���������� ������.
			\param nGroupID - ID ������.
			\param vectNotificationDescr [out] - ���������. ��� �� �� �����, ��� � ������ GetCommonProperties,
					�� ������������� � ���������� ������. ����� ����, vectNotificationDescr ����� �� ���������
					�� ������ �������� - � ����� ������ ������������� ����� ���������, ������������ �������
					GetCommonProperties().
		*/
        /* ���������� ����� */
		virtual void GetGroupProperties(
			long nGroupID,
			std::vector<notification_descr_t>& vectNotificationDescr ) = 0;

		/*! 
		  \brief ����� ������ ��������� ����������� ��� ������.
			\param wstrTaskId - ID ������.
			\param vectNotificationDescr [out] - ���������. ��� �� �� �����, ��� � ������ GetCommonProperties,
					�� ������������� � ������.
		*/
        /* ���������� ����� */
		virtual void GetTaskProperties(
			const std::wstring& wstrTaskId,
			std::vector<notification_descr_t>& vectNotificationDescr ) = 0;


		/*! 
		  \brief ����� ��������� ����� ��������� �����������.
			\param vectNotificationDescr - ��. �������� ������ GetCommonProperties().
				vectNotificationDescr ������ ��������� ��� �������� ���� ������� � ������ �����������.
		*/
        /* ���������� ����� */
		virtual void SetCommonProperties(
			const std::vector<notification_descr_t>& vectNotificationDescr
		) = 0;

		/*! 
		  \brief ����� ��������� ��������� ����������� ��� ������.
			\param vectNotificationDescr - ��. �������� ������ GetCommonProperties().
				vectNotificationDescr ����� �� ��������� �� ������ ��������, � ����� ������ ������������� 
				����� ���������.

		*/
        /* ���������� ����� */
		virtual void SetGroupProperties(
			long nGroupID,
			const std::vector<notification_descr_t>& vectNotificationDescr
		) = 0;


		/*! 
		  \brief ����� ��������� ��������� ����������� ��� ������.
            \param wstrTaskId - ID ������.
			\param vectNotificationDescr - ��. �������� ������ GetCommonProperties().
		*/
        /* ���������� ����� */
		virtual void SetTaskProperties(
			const std::wstring& wstrTaskId,
			const std::vector<notification_descr_t>& vectNotificationDescr
		) = 0;
	};
	
    class KLSTD_NOVTABLE NotificationProperties2 : public KLSTD::KLBaseQI {
    public:
		virtual void GetDefaultSettings(
            std::wstring & wstrSMTPServer,
            long & nSMTPPort,
		    std::wstring & wstrEMail,
            bool & bUseEmail,
		    std::wstring & wstrNetSendParameter,
            bool & bUseNetSend,
		    std::wstring& wstrScript,
            bool & bUseScript,
            std::wstring & wstrMessageTemplate,
			std::wstring & wstrEmailSubject,
			std::wstring & wstrEmailFrom) = 0;

		virtual void SetDefaultSettings(
            const std::wstring & wstrSMTPServer,
            long nSMTPPort,
		    const std::wstring & wstrEMail,
            bool bUseEmail,
		    const std::wstring & wstrNetSendParameter,
            bool bUseNetSend,
		    const std::wstring & wstrScript,
            bool bUseScript,
            const std::wstring & wstrMessageTemplate,
			const std::wstring & wstrEmailSubject,
			const std::wstring & wstrEmailFrom) = 0;

		virtual void TestEmail(
            const std::wstring & wstrSMTPServer,
            long nSMTPPort,
		    const std::wstring & wstrEMail,
            const std::wstring & wstrMessageTemplate,
			const std::wstring & wstrEmailSubject,
			const std::wstring & wstrEmailFrom,
			bool bDenyDefaults = false) = 0;

		virtual void TestNetSend(
            const std::wstring & wstrNetSendParameter,
            const std::wstring & wstrMessageTemplate,
			bool bDenyDefaults = false) = 0;

		virtual void TestScript(
            const std::wstring & wstrScript,
            const std::wstring & wstrMessageTemplate,
			bool bDenyDefaults = false) = 0;

        virtual KLEVP::NotificationLimits GetNotificationLimits() = 0;

        virtual void SetNotificationLimits( const NotificationLimits & nl ) = 0;
	};

    class KLSTD_NOVTABLE NotificationProperties3 : public NotificationProperties2 {
    public:
		virtual void GetDefaultSettings(notification_descr_t2& nd) = 0;

		virtual void SetDefaultSettings(const notification_descr_t2& nd) = 0;

		virtual void TestEmail2(
            const std::wstring & wstrSMTPServer,
            long nSMTPPort,
		    const std::wstring & wstrEMail,
            const std::wstring & wstrMessageTemplate,
			const std::wstring & wstrEmailSubject,
			const std::wstring & wstrEmailFrom,
			const std::wstring & wstrEmailESMTPUserName,
			const std::wstring & wstrEmailESMTPUserPassword,
			bool bDenyDefaults = false) = 0;
	};
}

/*!
  \brief ������� proxy-������ ������ KLEVP::NotificationProperties

    \param wstrURL      [in] ����� soap-�������
    \param ppEventProperties   [out] ��������� �� ������ ������ KLEVP::NotificationProperties
*/
KLCSSRVP_DECL void KLEVP_CreateNotificationPropertiesProxy(
                        const wchar_t*  szwAddress,
                        KLEVP::NotificationProperties**           pp,
                        const unsigned short* pPorts = NULL,
                        bool            bUseSsl = true);

/*!
  \brief ������� proxy-������ ������ KLEVP::NotificationProperties2

    \param wstrURL      [in] ����� soap-�������
    \param ppEventProperties   [out] ��������� �� ������ ������ KLEVP::NotificationProperties2
*/
KLCSSRVP_DECL void KLEVP_CreateNotificationProperties2Proxy(
                        const wchar_t*  szwAddress,
                        KLEVP::NotificationProperties2**           pp,
                        const unsigned short* pPorts = NULL,
                        bool            bUseSsl = true);

#endif // _KLNOTIFICATPROPS_H__011D27B2_EFF7_48fe_BBF5_3FCFCBB876AC__

// Local Variables:
// mode: C++
// End:
