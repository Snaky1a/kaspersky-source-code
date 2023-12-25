// AVP Prague stamp begin( Interface header,  )
// -------- ANSI C++ Code Generator 1.0 --------
// -------- Thursday,  05 July 2007,  18:32 --------
// -------------------------------------------
// Copyright � Kaspersky Lab 1996-2006.
// -------------------------------------------
// Project     -- Not defined
// Sub project -- Not defined
// Purpose     -- Not defined
// Author      -- Denisov
// File Name   -- task.cpp
// -------------------------------------------
// AVP Prague stamp end



// AVP Prague stamp begin( Interface version,  )
#define Task_VERSION ((tVERSION)1)
// AVP Prague stamp end



// AVP Prague stamp begin( Header includes,  )
#include <Prague/prague.h>
#include <Prague/pr_remote.h>
#include <Prague/pr_vtbl.h>
#include <Prague/iface/i_os.h>
#include <Prague/iface/i_reg.h>
#include <Prague/iface/i_root.h>
#include <Prague/iface/i_threadpool.h>

#include <Extract/plugin/p_msoe.h>

#include <Mail/plugin/p_smtpprotocoller.h>
#include <Mail/structs/s_mc.h>
// AVP Prague stamp end



#include "../../ThreadImp.h"
#include "../../StateManager.h"
#include "../../TrafficProtocoller.h"
#include "SMTPSessionAnalyzer.h"

tPROPID g_propMessageIsIncoming;
tPROPID g_propMailMessageOS_PID;
tPROPID g_propMailerPID;
tPROPID g_propMessageCheckOnly;


// AVP Prague stamp begin( C++ class declaration,  )
struct pr_novtable CSMTPProtocoller : public cTask {
private:
// Internal function declarations
	tERROR pr_call ObjectInitDone();
	tERROR pr_call ObjectPreClose();
	tERROR pr_call MsgReceive( tDWORD p_msg_cls_id, tDWORD p_msg_id, hOBJECT p_send_point, hOBJECT p_ctx, hOBJECT p_receive_point, tVOID* p_par_buf, tDWORD* p_par_buf_len );

// Property function declarations

public:
// External function declarations
	tERROR pr_call SetSettings( const cSerializable* p_settings );
	tERROR pr_call GetSettings( cSerializable* p_settings );
	tERROR pr_call AskAction( tActionId p_actionId, cSerializable* p_actionInfo );
	tERROR pr_call SetState( tTaskRequestState p_state );
	tERROR pr_call GetStatistics( cSerializable* p_statistics );

// Data declaration
	tDWORD       m_state; // --
	hTASKMANAGER m_tm;    // --
// AVP Prague stamp end



private:
	tERROR DETECT(
		IN session_t* pSession,          // �������� ������
		IN data_source_t dsDataSource,   // �������� ������
		IN tVOID* pLastReceivedData,     // ����� � ������� ��� ������
		IN tULONG ulLastReceivedData,    // ������ ������
		OUT detect_code_t* pdcDetectCode,// ��������� �������������� ���������
		OUT hOBJECT* phDetectorHandle    // ����� ������������
		);
	tERROR PROCESS(
		IN session_t* pSession,          // �������� ������
		IN data_source_t dsDataSource,   // �������� ������
		IN tVOID* pData,                 // ���� ������
		IN tULONG ulDataSize             // ������ ����� ������
		);
	
private:
	hOBJECT m_traffic_monitor;
	tDWORD m_dwSessionCount;
	hCRITICAL_SECTION m_hSessionCS;

// AVP Prague stamp begin( C++ class declaration end,  )
public:
	mDECLARE_INITIALIZATION(CSMTPProtocoller)
};
// AVP Prague stamp end



// AVP Prague stamp begin( Global property variable declaration,  )
// Interface "Task". Static(shared) property table variables
// AVP Prague stamp end



// AVP Prague stamp begin( Internal (kernel called) interface method implementation, ObjectInitDone )
// Extended method comment
//    Notification that all necessary properties have been set and object must go to operation state
// Result comment
//    Returns value differ from errOK if object cannot function properly
// Parameters are:
tERROR CSMTPProtocoller::ObjectInitDone() {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "Task::ObjectInitDone method" );

	// Place your code here
	if ( PR_SUCC(error) )
		error = PrepareObject<CSMTPProtocoller>(this, m_dwSessionCount, &m_hSessionCS, m_traffic_monitor, m_tm);

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( Internal (kernel called) interface method implementation, ObjectPreClose )
// Extended method comment
//    Kernel warns object it is going to close all children
// Behaviour comment
//    Object takes all necessary "before preclosing" actions
// Parameters are:
tERROR CSMTPProtocoller::ObjectPreClose() {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "Task::ObjectPreClose method" );

	// Place your code here
	error = ReleaseObject<CSMTPProtocoller>(this, &m_hSessionCS, m_traffic_monitor, m_tm);

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( Internal (kernel called) interface method implementation, MsgReceive )
// Extended method comment
//    Receives message sent to the object or to the one of the object parents as broadcast
// Parameters are:
//   "msg_cls_id"    : Message class identifier
//   "msg_id"        : Message identifier
//   "send_point"    : Object where the message was send initially
//   "ctx"           : Context of the object processing
//   "receive_point" : Point of distributing message (tree top for RegisterMsgHandler call
//   "par_buf"       : Buffer of the parameters
//   "par_buf_len"   : Lenght of the buffer of the parameters
tERROR CSMTPProtocoller::MsgReceive( tDWORD p_msg_cls_id, tDWORD p_msg_id, hOBJECT p_send_point, hOBJECT p_ctx, hOBJECT p_receive_point, tVOID* p_par_buf, tDWORD* p_par_buf_len ) {
	tERROR err = errOK;

	// Place your code here
	if ( p_msg_cls_id == pmcTRAFFIC_PROTOCOLLER )
	{
		if (
			p_msg_id == pmSESSION_START &&
			((cSerializable*)p_par_buf)->isBasedOn(session_t::eIID) &&
			((session_t*)p_par_buf)->dwInterfaceVersion == TRAFFIC_PROTOCOLLER_INTERFACE_VERSION &&
			((session_t*)p_par_buf)->dwSessionCtxCount >= po_SMTP
			)
		{
			//////////////////////////////////////////////////////////////////////////
			//
			// SESSION_START
			//
			if ( m_state == TASK_STATE_RUNNING )
			{
				CSMTPSessionAnalyzer* pSessionData = new CSMTPSessionAnalyzer();
				if ( pSessionData )
				{
					CMailSessionProcessor::InitParams_t hInitParams;
					hInitParams.hParent = *this;
					hInitParams.pSession = (session_t*)p_par_buf;
					hInitParams.hTrafficMonitor = p_send_point;
					if ( PR_SUCC( err = pSessionData->Init(&hInitParams) ))
					{
						((session_t*)p_par_buf)->pdwSessionCtx[po_SMTP] = (tVOID *)pSessionData;
						InterlockedIncrement((PLONG)&m_dwSessionCount); //m_dwSessionCount++;
						PR_TRACE((this, prtIMPORTANT, "smtp\tSession created (session count is %d)", m_dwSessionCount));
					}
					else
					{
						delete pSessionData;
						pSessionData = NULL;
					}
				}
			}
			//
			// SESSION_START
			//
			//////////////////////////////////////////////////////////////////////////
		}
		else if (
			p_msg_id == pmSESSION_STOP &&
			((cSerializable*)p_par_buf)->isBasedOn(session_t::eIID) &&
			((session_t*)p_par_buf)->dwInterfaceVersion == TRAFFIC_PROTOCOLLER_INTERFACE_VERSION &&
			((session_t*)p_par_buf)->dwSessionCtxCount >= po_SMTP
			)
		{
			//////////////////////////////////////////////////////////////////////////
			//
			// SESSION_STOP
			//
			cAutoCS _cs_(m_hSessionCS, true);
			CSMTPSessionAnalyzer* pSessionData = (CSMTPSessionAnalyzer*)((session_t*)p_par_buf)->pdwSessionCtx[po_SMTP];
			if ( pSessionData )
			{
				pSessionData->Stop();
				delete pSessionData;
				pSessionData = NULL;
				InterlockedDecrement((PLONG)&m_dwSessionCount); //m_dwSessionCount--;
				PR_TRACE((this, prtIMPORTANT, "smtp\tSession stopped (session count is %d)", m_dwSessionCount));
			}
			else
			{
				PR_TRACE((this, prtIMPORTANT, "smtp\tSession stopped (no processor)"));
			}
			((session_t*)p_par_buf)->pdwSessionCtx[po_SMTP] = NULL;
			//
			// SESSION_STOP
			//
			//////////////////////////////////////////////////////////////////////////
		}
		else if (
			p_msg_id == pmSESSION_PSEUDO_STOP &&
			((cSerializable*)p_par_buf)->isBasedOn(pseudo_stop_t::eIID) &&
			((pseudo_stop_t*)p_par_buf)->dwInterfaceVersion == TRAFFIC_PROTOCOLLER_INTERFACE_VERSION &&
			((pseudo_stop_t*)p_par_buf)->dwSessionCtxCount >= po_SMTP &&
			((pseudo_stop_t*)p_par_buf)->phProtocollerHandle &&
			*(((pseudo_stop_t*)p_par_buf)->phProtocollerHandle) == (hOBJECT)this
			)
		{
			//////////////////////////////////////////////////////////////////////////
			//
			// SESSION_PSEUDO_STOP
			//
			cAutoCS _cs_(m_hSessionCS, true);
			CSMTPSessionAnalyzer* pSessionData = (CSMTPSessionAnalyzer*)((session_t*)p_par_buf)->pdwSessionCtx[po_SMTP];
			if ( pSessionData )
			{
				pSessionData->Stop();
				delete pSessionData;
				pSessionData = NULL;
				InterlockedDecrement((PLONG)&m_dwSessionCount); //m_dwSessionCount--;
				PR_TRACE((this, prtIMPORTANT, "smtp\tSession pseudo stopped (session count is %d)", m_dwSessionCount));
			}
			else
			{
				PR_TRACE((this, prtIMPORTANT, "smtp\tSession pseudo stopped (no processor)"));
			}
			((session_t*)p_par_buf)->pdwSessionCtx[po_SMTP] = NULL;
			//
			// SESSION_PSEUDO_STOP
			//
			//////////////////////////////////////////////////////////////////////////
		}
		else if (
			p_msg_id == pmDETECT &&
			((cSerializable*)p_par_buf)->isBasedOn(detect_t::eIID) &&
			((detect_t*)p_par_buf)->dwInterfaceVersion == TRAFFIC_PROTOCOLLER_INTERFACE_VERSION &&
			((detect_t*)p_par_buf)->dwSessionCtxCount >= po_SMTP
			)
		{
			//////////////////////////////////////////////////////////////////////////
			//
			// DETECT
			//
			cAutoCS _cs_(m_hSessionCS, false);
			detect_t* detect_data = (detect_t*)p_par_buf;
			err = DETECT(
				(session_t*)detect_data,
				detect_data->dsDataSource,
				detect_data->pLastReceivedData,
				detect_data->ulLastReceivedData,
				detect_data->pdcDetectCode,
				detect_data->phDetectorHandle
				);
			if (
				PR_SUCC(err) &&
				detect_data->pdcDetectCode &&
				(
					*(detect_data->pdcDetectCode) == dcDataDetected ||
					*(detect_data->pdcDetectCode) == dcProtocolDetected
				))
				return errOK_DECIDED;
			else
				return errOK;
			//
			// DETECT
			//
			//////////////////////////////////////////////////////////////////////////
		}
		else if (
			p_msg_id == pmPROCESS &&
			((cSerializable*)p_par_buf)->isBasedOn(process_t::eIID) &&
			((process_t*)p_par_buf)->dwInterfaceVersion == TRAFFIC_PROTOCOLLER_INTERFACE_VERSION &&
			((process_t*)p_par_buf)->dwSessionCtxCount >= po_SMTP
			)
		{
			//////////////////////////////////////////////////////////////////////////
			//
			// PROCESS
			//
			cAutoCS _cs_(m_hSessionCS, false);
			process_t* process_data = (process_t*)p_par_buf;
			if (
				process_data->phDetectorHandle &&
				*(process_data->phDetectorHandle) == (hOBJECT)this
				)
			{
				err = PROCESS(
					(session_t*)process_data,
					process_data->dsDataSource,
					process_data->pData,
					process_data->ulDataSize
					);
				if ( PR_FAIL(err) && process_data->psStatus  )
					*(process_data->psStatus) = psProcessFailed;
				else
				{
					*(process_data->psStatus) = psKeepAlive;
					return errOK_DECIDED;
				}
			}
			else
			if ( process_data->psStatus )
				*(process_data->psStatus) = psProcessFailed;
			return errOK;
			//
			// PROCESS
			//
			//////////////////////////////////////////////////////////////////////////
		}
	}
	if (
		p_msg_cls_id == pmc_TASK_STATE_CHANGED &&
		/*m_state == TASK_STATE_RUNNING &&*/
		m_traffic_monitor &&
		p_send_point->propGetPID() == PID_TRAFFICMONITOR
		)
	{
		m_state = p_msg_id;
		sysSendMsg(pmc_TASK_STATE_CHANGED, m_state, NULL, NULL, NULL);
	}

	return err;
}
// AVP Prague stamp end



tERROR CSMTPProtocoller::DETECT(
	IN session_t* pSession,          // �������� ������
	IN data_source_t dsDataSource,   // �������� ������
	IN tVOID* pLastReceivedData,     // ����� � ������� ��� ������
	IN tULONG ulLastReceivedData,    // ������ ������
	OUT detect_code_t* pdcDetectCode,// ��������� �������������� ���������
	OUT hOBJECT* phDetectorHandle    // ����� ������������
	)
{
	if ( !pSession )
		return errOBJECT_NOT_FOUND;

	cERROR err = errOK;
	CSMTPSessionAnalyzer* pSessionData = ((CSMTPSessionAnalyzer*)pSession->pdwSessionCtx[po_SMTP]);
	if ( pSessionData )
	{
		*pdcDetectCode = pSessionData->Detect( 
			dsDataSource, 
			(tBYTE*)pLastReceivedData, 
			ulLastReceivedData 
			);
		*phDetectorHandle = (hOBJECT)this;
	}
	else
		return errOBJECT_NOT_FOUND;
	return err;
}

tERROR CSMTPProtocoller::PROCESS(
	IN session_t* pSession,          // �������� ������
	IN data_source_t dsDataSource,   // �������� ������
	IN tVOID* pData,                 // ���� ������
	IN tULONG ulDataSize             // ������ ����� ������
	)
{
	if ( !pSession )
		return errOBJECT_NOT_FOUND;

	cERROR err = errOK;
	CSMTPSessionAnalyzer* pSessionData = ((CSMTPSessionAnalyzer*)pSession->pdwSessionCtx[po_SMTP]);
	if ( pSessionData )
		err = pSessionData->Process( dsDataSource, (tBYTE*)pData, ulDataSize );
	return err;
}


// AVP Prague stamp begin( External (user called) interface method implementation, SetSettings )
// Parameters are:
tERROR CSMTPProtocoller::SetSettings( const cSerializable* p_settings ) {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "Task::SetSettings method" );

	// Place your code here

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( External (user called) interface method implementation, GetSettings )
// Parameters are:
tERROR CSMTPProtocoller::GetSettings( cSerializable* p_settings ) {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "Task::GetSettings method" );

	// Place your code here

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( External (user called) interface method implementation, AskAction )
// Parameters are:
tERROR CSMTPProtocoller::AskAction( tActionId p_actionId, cSerializable* p_actionInfo ) {
	tERROR error = errNOT_IMPLEMENTED;
	PR_TRACE_FUNC_FRAME( "Task::AskAction method" );

	// Place your code here

	return error;
}
// AVP Prague stamp end

// AVP Prague stamp begin( External (user called) interface method implementation, SetState )
// Parameters are:
tERROR CSMTPProtocoller::SetState( tTaskRequestState p_state ) {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "Task::SetState method" );

	m_state = TASK_STATE_FAILED;

	switch ( p_state )
	{
	case TASK_REQUEST_RUN:
		if (m_traffic_monitor || PR_SUCC(error = m_tm->GetService( TASKID_TM_ITSELF, *this, AVP_SERVICE_TRAFFICMONITOR, &m_traffic_monitor, cREQUEST_SYNCHRONOUS )))
		{
			sysRegisterMsgHandler(pmc_TASK_STATE_CHANGED, rmhLISTENER, m_tm, IID_ANY, PID_TRAFFICMONITOR, IID_ANY, PID_ANY);
			m_state = TASK_STATE_RUNNING;
		}
		break;
	case TASK_REQUEST_PAUSE:
		m_state = TASK_STATE_PAUSED;
		break;
	case TASK_REQUEST_STOP:
		// ����������� ���������� �������� �������
		PR_TRACE((this, prtIMPORTANT, "smtp\tProcessing stop request..."));
		m_state = TASK_STATE_COMPLETED;
		PR_TRACE((this, prtIMPORTANT, "smtp\tReleasing trafmon"));
		if ( m_traffic_monitor && PR_SUCC(this->sysCheckObject((hOBJECT)m_traffic_monitor)) )	
		{	
			sysUnregisterMsgHandler(pmc_TASK_STATE_CHANGED, m_tm);
			m_tm->ReleaseService(TASKID_TM_ITSELF, (hOBJECT)m_traffic_monitor);	
			m_traffic_monitor = NULL;	
		}	
		PR_TRACE((this, prtIMPORTANT, "smtp\tSending pseudo stop"));
		if ( errOK_DECIDED == sysSendMsg(pmcTRAFFIC_PROTOCOLLER, pmSESSION_PSEUDO_STOP_REQUEST, 0,0,0))
		{
			// ���������, ���� ��� ������� ������ ����������� 
			// (�� ��������� � ��������� ������ m_pStateManager, ������� ��� ���������)
			PR_TRACE((this, prtIMPORTANT, "smtp\tWaiting sessions (if any)"));
			time_t last_trace = 0, t;
			while ( cTRUE ) 
			{
				tDWORD sess_count;
				{
					if (!(sess_count = m_dwSessionCount))
						break;
				}
				if(last_trace != (t = time(0)))
				{
					PR_TRACE((this, prtIMPORTANT, "smtp\tStill %d sessions to wait...", sess_count));
					last_trace = t;
				}
				Sleep(100);
			}
		}
		PR_TRACE((this, prtIMPORTANT, "smtp\tStop request processed"));
		break;
	default:
		m_state = TASK_STATE_COMPLETED;
		break;
	}
	sysSendMsg(pmc_TASK_STATE_CHANGED, m_state, NULL, NULL, NULL);
	return error;
}
// AVP Prague stamp end

// AVP Prague stamp begin( External (user called) interface method implementation, GetStatistics )
// Parameters are:
tERROR CSMTPProtocoller::GetStatistics( cSerializable* p_statistics ) {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "Task::GetStatistics method" );

	// Place your code here

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( C++ class regitration,  )
// Interface "Task". Register function
tERROR CSMTPProtocoller::Register( hROOT root ) {
	tERROR error;
// AVP Prague stamp end



// AVP Prague stamp begin( Property table,  )
mpPROPERTY_TABLE(Task_PropTable)
	mSHARED_PROPERTY( pgINTERFACE_VERSION, Task_VERSION )
	mSHARED_PROPERTY_PTR( pgINTERFACE_COMMENT, "1", 2 )
	mpLOCAL_PROPERTY_BUF( pgTASK_TM, CSMTPProtocoller, m_tm, cPROP_BUFFER_READ_WRITE | cPROP_WRITABLE_ON_INIT | cPROP_REQUIRED )
mpPROPERTY_TABLE_END(Task_PropTable)
// AVP Prague stamp end



// AVP Prague stamp begin( Internal method table,  )
mINTERNAL_TABLE_BEGIN(Task)
	mINTERNAL_METHOD(ObjectInitDone)
	mINTERNAL_METHOD(ObjectPreClose)
	mINTERNAL_METHOD(MsgReceive)
mINTERNAL_TABLE_END(Task)
// AVP Prague stamp end



// AVP Prague stamp begin( External method table,  )
mEXTERNAL_TABLE_BEGIN(Task)
	mEXTERNAL_METHOD(Task, SetSettings)
	mEXTERNAL_METHOD(Task, GetSettings)
	mEXTERNAL_METHOD(Task, AskAction)
	mEXTERNAL_METHOD(Task, SetState)
	mEXTERNAL_METHOD(Task, GetStatistics)
mEXTERNAL_TABLE_END(Task)
// AVP Prague stamp end



// AVP Prague stamp begin( Registration call,  )

	PR_TRACE_FUNC_FRAME_( *root, "Task::Register method", &error );

	error = CALL_Root_RegisterIFace(
		root,                                   // root object
		IID_TASK,                             // interface identifier
		PID_SMTPPROTOCOLLER,                    // plugin identifier
		0x00000000,                             // subtype identifier
		Task_VERSION,                         // interface version
		VID_DENISOV,                            // interface developer
		&i_Task_vtbl,                         // internal(kernel called) function table
		(sizeof(i_Task_vtbl)/sizeof(tPTR)),   // internal function table size
		&e_Task_vtbl,                         // external function table
		(sizeof(e_Task_vtbl)/sizeof(tPTR)),   // external function table size
		Task_PropTable,                       // property table
		mPROPERTY_TABLE_SIZE(Task_PropTable), // property table size
		sizeof(CSMTPProtocoller)-sizeof(cObjImpl),// memory size
		0                                       // interface flags
	);

	#ifdef _PRAGUE_TRACE_
		if ( PR_FAIL(error) )
			PR_TRACE( (root,prtDANGER,"Task(IID_TASK) registered [%terr]",error) );
	#endif // _PRAGUE_TRACE_
// AVP Prague stamp end



	if( PR_SUCC(error) )
		error = root->RegisterCustomPropId(
			&g_propMessageIsIncoming,
			npMESSAGE_IS_INCOMING,
			pTYPE_BOOL | pCUSTOM_HERITABLE
			);
	if( PR_SUCC(error) )
		error = root->RegisterCustomPropId(
			&g_propMailMessageOS_PID, 
			npMAILMESSAGE_OS_PID, 
			pTYPE_DWORD | pCUSTOM_HERITABLE
			);
	if( PR_SUCC(error) )
		error = root->RegisterCustomPropId(
			&g_propMailerPID, 
			npMAILER_PID, 
			pTYPE_DWORD | pCUSTOM_HERITABLE
			);
	if( PR_SUCC(error) )
		error = root->RegisterCustomPropId(
			&g_propMessageCheckOnly, 
			npMESSAGE_CHECK_ONLY, 
			pTYPE_DWORD | pCUSTOM_HERITABLE
			);


// AVP Prague stamp begin( C++ class regitration end,  )
	return error;
}

tERROR pr_call Task_Register( hROOT root ) { return CSMTPProtocoller::Register(root); }
// AVP Prague stamp end



// AVP Prague stamp begin( Caution !!!,  )
// You have to implement propetry: pgTASK_STATE
// You have to implement propetry: pgTASK_SESSION_ID
// You have to implement propetry: pgTASK_ID
// You have to implement propetry: pgTASK_PERSISTENT_STORAGE
// You have to implement propetry: pgTASK_PARENT_ID
// AVP Prague stamp end



