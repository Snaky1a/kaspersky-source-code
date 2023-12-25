/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file EventProperties.h
 * \author ������ ��������
 * \date 16:56 22.11.2002
 * \brief ���������� ��� ��������� � �������� �������� �������. 
 *			��� ��������� ������� �������� � ���� ������������� �������, 
 *			����������� � ������� ( "Virus found" � �.�.), � human-readbale form.
 *			������  ������������� ��� ���������� ��� ����������� ����������������� 
 *			(��������, ��� snap-in'�), ����� ��� ��� ����������� �����. ���������������� � 
 *			���������������� ����������.
 */



#ifndef _KLEVENTROPS_H__5745B60A_831F_4678_816D_9265D1AD094D__
#define _KLEVENTROPS_H__5745B60A_831F_4678_816D_9265D1AD094D__

#include <std/base/klstd.h>
#include <std/par/params.h>
#include <transport/ev/ev_general.h>

namespace KLEVP{
    
	typedef void (*RangeCalcProgressCallback)(
        int nProgress, ///< �� 0 �� 100
        bool & bStop, ///< ��������� � true ���� ���� ���������� ����������
		void* pParam );///< ��������, ���������� ��� �������� �������.

    const wchar_t c_szwIteratorId[]                     = L"EVP_ITERATOR_ID"; // STRING_T
    const wchar_t c_szwDeletionResult[]                 = L"EVP_DELETION_RESULT"; // INT_T, ��. enum DeletionResult
    const wchar_t c_szwDeletionProgress[]               = L"EVP_DELETION_PROGRESS"; // INT_T
    const wchar_t c_szwDeletionErrId[]                  = L"EVP_DELETION_ERR_ID"; // INT_T

    const wchar_t c_szwMaxSelectedRecNumber[]   = L"EVP_MAX_SELECTED_REC_NUMBER"; // INT_T
    const wchar_t c_szwBlocks[]                 = L"EVP_EVENT_BLOCKS"; // ARRAY_T
    const wchar_t c_szwBlockBegin[]             = L"EVP_EVENT_BLOCK_BEGIN"; // INT_T
    const wchar_t c_szwBlockEnd[]               = L"EVP_EVENT_BLOCK_END"; // INT_T

    const wchar_t c_szwIncludeGnrlEvents[]		= L"EVP_INCL_GNRL_EVENTS"; // BOOL_T
    const wchar_t c_szwLastEventsOnly[]			= L"EVP_LAST_EVENTS_ONLY"; // BOOL_T

	const wchar_t c_szwIncludeTaskStates[]		= L"EVP_INCL_TASK_STATES"; // BOOL_T

    const wchar_t c_szwMaxEventsCount[]			= L"EVP_MAX_EVENTS_COUNT"; // INT_T
	
    const wchar_t c_er_registration_time[]      = L"registration_time";	// DATE_TIME_T
	
    enum DeletionResult {
        DELETION_SUCCEED, ///< �������� ������� ���������.
        DELETION_FAILED,   ///< �� ������� ��������� ��������.
        DELETION_ABORTED,  ///< �������� ���������� �������� (������������ ��� ��� ����)
        SHALL_REFRESH_BEFORE  ///<  ���� ������������� (������, �����) ������� 
                        /// ��������, �������������� ������� ������ (�.�. ������ ������ ��������),
                        /// �.�. �� ������, ������� �� �����, ���� �������� ������� � ������� ��������� ��������,
                        /// ���-�� ���.
    };

    /*!
        ������� c_DeletionFinished ����������� �������� ��� ��������� ��������
                        ��������� �������� (�������������� �������� InitiateDelete)
        ���������:
            c_szwIteratorId        STRING_T - ������������� �������� ��������, ������������ �-� InitiateDelete
            c_szwDeletionResult    INT_T, ��. enum DeletionResult
            c_er_descr             STRING_T � ������, ����� c_szwDeletionResult == DELETION_FAILED, �������� ��������� �������� ������
            c_szwDeletionErrId     INT_T � ������, ����� c_szwDeletionResult == DELETION_FAILED, �������� ��� ������.

    */
	const wchar_t c_DeletionFinished[]=L"KLEVP_DeletionFinished";

    /*!
        ������� c_DeletionProgress ����������� �������� � �������� ��������
                        ��������� �������� (�������������� �������� InitiateDelete)
        ���������:
            c_szwIteratorId             STRING_T - ������������� �������� ��������, ������������ �-� InitiateDelete
            c_szwDeletionProgress       INT_T - ����� �� 0 �� 100
    */
	const wchar_t c_DeletionProgress[]=L"KLEVP_DeletionProgress";

	// events virtual parameters (not published by product, but selected from db):
	const wchar_t c_EventHostStatus[] = L"KLEVP_EVENT_HOST_STATUS";		//  INT_T    
	const wchar_t c_EventHostStatusEx[] = L"KLEVP_EVENT_HOST_STATUS_EX";	//  INT_T    
	const wchar_t c_EventTaskName[] = L"KLEVP_EVENT_TASK_NAME";	//  STRING_T    
	const wchar_t c_IsRemoteInstall[] = L"KLEVP_EVENT_IS_RI";	//  INT_T    
	const wchar_t c_NeedReboot[] = L"KLEVP_EVENT_NEED_REBOOT";	//  INT_T    

    enum EventPropertiesType { eptAll, eptGroupTask, eptHost };

    /*!
    * \brief ��������� ��������� ���������������� �� ��������� � �������� �������� �������.
	*		
    */
    class KLSTD_NOVTABLE EventProperties : public KLSTD::KLBase {
    public:
        /*!
          \brief	GetRecordCount

          \param	long ���������� ���������� ������� � ������
        */
        virtual long GetRecordCount() = 0;

		/*
			\brief ���������� �������� �������� �������.

            \param	long nStart [in] - ���������� ����� ��������� ������
            \param	long nEnd [in] - ���������� ����� �������� ������
            \param paramProperties [out] - ���������, �������� ���������� c ������ c_grp_array_hosts ���� ARRAY_T.
		*/
        virtual void GetRecordRange(
            long nStart,
            long nEnd,
            KLPAR::Params** pParamsEvents,
            RangeCalcProgressCallback fnProgress = NULL,
            void * pCallbackParam = NULL)  = 0;

        /*!
          \brief	FindRecordByFirstChars - ���� ������, � ������� �������� ����
                ���������� � �������� ��������.

          \param	wstrFieldToSearch [in] - ����, �� �������� ������������ �����.
          \param	wstrFirstChars [in] - �������, ������� ������.
          \return	long - ���������� ����� ������ ������, � �������
            ���� wstrFieldToSearch ���������� � wstrFirstChars. ���� ������ ��
            �������, �� ����������� �������� < 0.
        */
        virtual long FindRecordByFirstChars( const std::wstring & wstrFieldToSearch, 
                                             const std::wstring & wstrFirstChars )  = 0;

		/*! 
		  \brief ������� �������, ID ������� ������� � ���������� ���������.
			\param vectIDs [in] - ID ��� �������, ������� ���� �������.
		*/
		virtual void DeleteProperties( const std::vector<long>& vectIDs  ) = 0;
		/*! 
		  \brief ���������� �������� �������� �������
			\param pSettings [in]
                c_szwMaxSelectedRecNumber // INT_T
                c_szwBlocks // ARRAY_T
                    +---<array element> // PARAMS_T
                        +---c_szwBlockBegin // INT_T, id ������ � ������� �����
                        +---c_szwBlockEnd // INT_T
                    +---<array element> // PARAMS_T
                        ...
                    ...
                    
            \return std::wstring - luid, ������� ������ ����� � ���� �������, �����������
                � �������� �������� �������. ����� ������ ��� ����, ����� �������� "����" �������
		*/
        virtual std::wstring InitiateDelete( KLSTD::CAutoPtr<KLPAR::Params> pSettings ) = 0;

        virtual void CancelDelete( KLSTD::CAutoPtr<KLPAR::Params> pSettings ) = 0;

		/*! 
		  \brief ���������� ������������� ���������, ������������� ��� �������� �������, 
		  (��. ����������� � ������� InitiateDelete). � ����� ������ ������� ������ ����� ������ InitiateDelete.
		*/
        virtual std::wstring GetIteratorId( KLSTD::CAutoPtr<KLPAR::Params> pSettings ) = 0;
    };
}

/* ! KLEVP_NF_TASK_ID - ��� ���������� � EventInfo::body,
������� ����������� � ������� �� ��������� ������. ���������� ������ ���� 
���� STRING_T � ��������� ID ������. ���� �������� 
�����������, �� ��� ������� �������. */
#define KLEVP_EVENT_GROUP_TASK_ID                    L"KLEVP_EVENT_GROUP_TASK_ID"

/* ! KLEVP_EVENT_SEVERITY - ��� ������������ ���������� � EventInfo::body,
���������� ������ ��������� �������� KLEVP_EVENT_SEVERITY_* - "�����������" ������� */
#define KLEVP_EVENT_SEVERITY         KLEVP::c_er_severity  // INT_T

// ! brief ��� ���������� � EventInfo::body, ������� ����������� � ������� �� 
// ��������� ������ � � ������� ����������� �������� �������
#define KLEVP_EVENT_DESCR           KLEVP::c_er_descr  // STRING_T

// ! brief ��� ���������� � EventInfo::body, ������� ����������� � ������� �� 
// ��������� ������ � � ������� ����������� ��� ������
#define KLEVP_EVENT_TASK_DISPLAY_NAME    KLPRTS::TASK_DISPLAY_NAME //L"KLEVP_EVENT_TASK_DISPLAY_NAME" // STRING_T

// ! brief ��� ���������� � EventInfo::body, ������� �������� user-friendly ��� ���� �������.
// ��������, ����� ��� ������� 'klevp-task-on-host-finished', �� ��� ���� �����
// ��������� '������ ���������'
#define KLEVP_EVENT_TYPE_DISPLAY_NAME       L"KLEVP_EVENT_TYPE_DISPLAY_NAME" // STRING_T

#define KLEVP_EVENT_HOST            L"KLEVP_EVENT_HOST"     // STRING_T
#define KLEVP_EVENT_DOMAIN          L"KLEVP_EVENT_DOMAIN"   // STRING_T
#define KLEVP_EVENT_PRODUCT         L"KLEVP_EVENT_PRODUCT"     // STRING_T
#define KLEVP_EVENT_VERSION         L"KLEVP_EVENT_VERSION"   // STRING_T
#define KLEVP_EVENT_HOST_DISPNAME   L"KLEVP_EVENT_HOST_DISPNAME"	// STRING_T
#define KLEVP_EVENT_TASK_NAME       L"KLEVP_EVENT_TASK_NAME"   // STRING_T
#define KLEVP_EVENT_HOST_NETBIOSNAME	L"KLEVP_EVENT_HOST_NETBIOSNAME"	// STRING_T

#define	KLEVP_EVENT_TYPE				L"KLEVP_EVENT_TYPE"					// STRING_T
#define	KLEVP_EVENT_GNRL_TYPE			L"KLEVP_EVENT_GNRL_TYPE"			// STRING_T
#define	KLEVP_EVENT_GNRL_TYPES_ARRAY	L"KLEVP_EVENT_GNRL_TYPES_ARRAY"		// ARRAY_T (STRING_T)
#define	KLEVP_EVENT_TSK_STATE_TYPE		L"KLEVP_EVENT_TSK_STATE_TYPE"		// STRING_T
#define KLEVP_EVENT_RISE_TIME_LEAST		L"KLEVP_EVENT_RISE_TIME_LEAST"		// DATE_TIME_T
#define KLEVP_EVENT_RISE_TIME_GREATEST	L"KLEVP_EVENT_RISE_TIME_GREATEST"	// DATE_TIME_T
#define KLEVP_EVENT_RISE_TIME_LAST_DAYS	L"KLEVP_EVENT_RISE_TIME_LAST_DAYS"	// INT_T
#define KLEVP_EVENT_HOST_GROUP			L"KLEVP_EVENT_HOST_GROUP"			// STRING_T
#define	KLEVP_EVENT_TASK_STATE			KLEVP::c_er_task_new_state			// INT_T

#define KLEVP_EVENT_HOST_IP_FROM		L"KLEVP_EVENT_HOST_IP_FROM"	// INT_T if 0 - ignore
#define KLEVP_EVENT_HOST_IP_TO			L"KLEVP_EVENT_HOST_TO"		// INT_T if 0 - ignore

#define KLEVP_EVENT_RI_NEED_REBOOT   L"KLEVP_EVENT_RI_NEED_REBOOT"	// BOOL_T
#define KLEVP_EVENT_RI_ERR_REASONS   L"KLEVP_EVENT_RI_ERR_REASONS"	// ARRAY_T (INT_T)

#endif // _KLEVENTROPS_H__5745B60A_831F_4678_816D_9265D1AD094D__

// Local Variables:
// mode: C++
// End:
