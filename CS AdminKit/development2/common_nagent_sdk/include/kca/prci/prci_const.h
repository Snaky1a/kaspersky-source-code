/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	prci_const.h
 * \author	Andrew Kazachkov
 * \date	21.04.2003 11:42:52
 * \brief	��������� ������ prci
 * 
 */


#ifndef __KLPRCI_CONST_H__
#define __KLPRCI_CONST_H__

#define KLPRCI_ASYNCID          L"KLPRCI_EVP_ASYNCID"
#define KLPRCI_PRODUCT_NAME     L"KLPRCI_EVP_PRODUCT_NAME"
#define KLPRCI_PRODUCT_VERSION  L"KLPRCI_EVP_PRODUCT_VERSION"
#define KLPRCI_COMPONENT_NAME   L"KLPRCI_EVP_COMPONENT_NAME"
#define KLPRCI_INSTANCE_ID      L"KLPRCI_EVP_INSTANCE_ID"
#define KLPRCI_SECTION_NAME     L"KLPRCI_EVP_SECTION_NAME"


namespace KLPRCI
{   
    
    const wchar_t c_szAddrLocal[]=L"";
    const wchar_t c_szAddrAny[]=L"*";
    const wchar_t c_szAddrAnySSL[]=L"*SSL";
    /*
        ��������� �������� ����������� � ��������� ���������� ���������� ����������
    */
	const wchar_t c_ComponentAsyncId[]=KLPRCI_ASYNCID;              // STRING_T
	const wchar_t c_WasStartedByAgent[]=L"KLPRCI_STARTED_BY_AGENT"; // BOOL_T
	const wchar_t c_AutoStopAllowed[]=L"KLPRCI_AUTOSTOP_ALLOWED";	// BOOL_T
	const wchar_t c_TimeoutStopAllowed[]=L"KLPRCI_TIMEOUT_STOP";	//INT_T

	/*!
		��������� �������� ����������� � ��������� ���������� ������.
	*/	
	const wchar_t c_szwTaskAsyncId[]=KLPRCI_ASYNCID;                //STRING_T
	const wchar_t c_szwTaskIsInvisible[]=L"KLPRCI_TASK_INVISIBLE";  //BOOL_T
    

    /*! This parameter can be queried via ComponentProxy::GetTaskParams 
        call and contains params specified in SetTaskState. 
    */
    const wchar_t c_szwTaskStateExtra[]=L"KLPRCI_TASK_STATE_EXTRA";  //PARAMS_T

    /*! ������ ������� c_EventInstanceState  ����������� ��� ���������
        ��������� ����������
		��������� ������:
            c_evpInstanceNewState,	INT_T  - ������ ���������.
            c_evpInstanceOldState,	INT_T - ����� ���������.
    */
	const wchar_t c_EventInstanceState[]=L"KLPRCI_EV_INSTANCE_STATE";
    const wchar_t c_evpInstanceNewState[]=L"KLPRCI_newState";
    const wchar_t c_evpInstanceOldState[]=L"KLPRCI_oldState";

    /*!
        ������� �� ��������� � ��������� ��������
        ��������� ������:
            c_evpProductName
            c_evpVersion
            c_evpSection
            c_evpSsType ��� ���������
            c_evpParameterName   -   �������������� ��������            
            c_evpOldValue   -   �������������� ��������
            c_evpNewValue   -   �������������� ��������
            c_evpUserName
    */
	const wchar_t c_EventSettingsChange[]=L"KLPRCI_EV_SS_CHANGE";        
		const wchar_t c_evpProductName[]=KLPRCI_PRODUCT_NAME;
		const wchar_t c_evpVersion[]=KLPRCI_PRODUCT_VERSION;
		const wchar_t c_evpSection[]=KLPRCI_SECTION_NAME;
        const wchar_t c_evpSsType[]=L"KLPRCI_SS_TYPE";//STRING_T
        const wchar_t c_evpIs_SETTINGS[]=L"KLPRCI_IS_SETTINGS";// BOOL_T
        const wchar_t c_evpChangeType[]=L"KLPRCI_CHANGE_TYPE";//INT_T PRSS::DataChangeType
		const wchar_t c_evpParameterName[]=L"KLPRCI_EVP_PARAMETER";//�������������� ��������
		const wchar_t c_evpOldValue[]=L"KLPRCI_EVP_OLDVALUE";//�������������� ��������
		const wchar_t c_evpNewValue[]=L"KLPRCI_EVP_NEWVALUE";//�������������� ��������
        const wchar_t c_evpUserName[]=L"KLPRCI_EVP_USERNAME"; //sid ����� ��� ������ ������.

    //! KLPRCI::HSUBSCRIBE - ���������� ��������
    KLSTD_DECLARE_HANDLE(HSUBSCRIBE); // KLPRCI::HSUBSCRIBE   


	/*!
        ������� c_EventTaskState ����������� ��� ��������� ��������� ������
        ���������:
            c_evpTaskId,        INT_T - ������������� ������.
            c_evpTaskOldState,  INT_T - ������ ��������� ������.
            c_evpTaskNewState,  INT_T - ����� ��������� ������.
		    c_evpTaskResults,   PARAMS_T - �������������� �������� - ���������.
		    c_evpTaskAsyncID,   STRING_T - 
            c_evpTaskTsId,      STRING_T - ������������� ������ � TasksStorage.
                                ���� ������ �� �� TasksStorage, �������
                                ����������� ��� ����� ������ ������.
    */
	const wchar_t c_EventTaskState[]=L"KLPRCI_TaskState";

    /*!
        ������� c_EventTaskCompletion ����������� ����� ���������� �������
        ���������� ������.
            c_evpTaskId,        INT_T - ������������� ������.
            c_evpTaskPercent,   INT_T  - ������� ���������� ������.
		    c_evpTaskAsyncID,   STRING_T
            c_evpTaskTsId,      STRING_T - ������������� ������ � TasksStorage.
                                ���� ������ �� �� TasksStorage, �������
                                ����������� ��� ����� ������ ������.
    */
	const wchar_t c_EventTaskCompletion[]=L"KLPRCI_TaskCompletion";

    /*!
        ������� c_EventTaskStarted ����������� ��� ������� ������
		    c_evpTaskId, STRING_T
		    c_evpTaskAsyncID, INT_T - ������������� ������.        
    */
	const wchar_t c_EventTaskStarted[]=L"KLPRCI_TaskStarted";

		/*!
			������������� ������
		*/
		const wchar_t c_evpTaskId[]=L"KLPRCI_taskId"; //INT_T

		/*!
			������ ��������� (��. enum TaskState)
		*/
		const wchar_t c_evpTaskOldState[]=L"KLPRCI_oldState"; //INT_T

		/*!
			����� ��������� (��. enum TaskState)
		*/
		const wchar_t c_evpTaskNewState[]=L"KLPRCI_newState"; //INT_T

		/*!
			��������� (�������� � ������ ProductTasksControl::SetState).
		*/
		const wchar_t c_evpTaskResults[]=L"KLPRCI_TASK_RESULTS"; //PARAMS_T

		/*!
			AsyncID ������ (������� � ������ RunTask).
		*/
		const wchar_t c_evpTaskAsyncID[]=L"KLPRCI_TASKASYNCID";//STRING_T

		/*!
			�������� ���������� (������� � ������ SetCompletion).
		*/
		const wchar_t c_evpTaskPercent[]=L"KLPRCI_COMPLETION"; //INT_T

		/*!
			������������� ������ � TasksStorage. ���� ������ �� ��
			TasksStorage, ������� ����������� ��� ����� ������ ������.
		*/
		const wchar_t c_evpTaskTsId[]=L"KLPRCI_TASK_TS_ID"; //STRING_T

		/*!
			������������� ������ ������ KCA. ������������ ��� �����������
			������ �����, ��������� ��� ������ ������ �� ������ KCA.
		*/
	    const wchar_t c_evp_kca_locid[]=L"KLPRCI_kca_loc_id"; // INT_T, �� EKCALocId

		/*!
			��� ���� ������
		*/
		const wchar_t c_evpTaskType[]=L"KLPRCI_taskType";	//STRING_T
		
		enum EKCALocId{
			KLPRCI_LOC_ERR_TASK_ALREADY_RUNNING = 0x00800001
		};
		
		/*!
			
		*/
        const wchar_t c_evpTaskInvisible[]=L"KLPRCI_IS_TASK_INVISIBLE";  //BOOL_T
        
        const wchar_t c_szwTskConnectionInfo[] = L"KLPRCI_TSK_CONN_INFO";

#define KLPRCI_DEFAULT_PING_TIMEOUT  (1000*60*2) // 2 minues
#define KLPRCI_DEFAULT_SS_TIMEOUT    KLSTD_INFINITE

} // namespace KLPRCI

#endif //__KLPRCI_CONST_H__

// Local Variables:
// mode: C++
// End:
