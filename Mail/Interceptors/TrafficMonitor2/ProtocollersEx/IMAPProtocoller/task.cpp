// AVP Prague stamp begin( Interface header,  )
// -------- ANSI C++ Code Generator 1.0 --------
// -------- Thursday,  05 July 2007,  18:50 --------
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



#define PR_IMPEX_DEF

// AVP Prague stamp begin( Interface version,  )
#define Task_VERSION ((tVERSION)1)
// AVP Prague stamp end



#pragma warning(disable:4786)

// AVP Prague stamp begin( Header includes,  )
#include <Prague/prague.h>
#include <Prague/pr_vtbl.h>
#include <Prague/iface/i_reg.h>
#include <Prague/iface/i_root.h>
#include <Prague/iface/i_threadpool.h>

#include <Mail/plugin/p_imapprotocoller.h>
// AVP Prague stamp end



#include "../../ThreadImp.h"
#include "../../StateManager.h"
#include "../../TrafficProtocoller.h"
#include "../common/protocolprocessor.h"
#include "../imap/ImapProtocolAnalyzer.h"


tPROPID g_propMessageIsIncoming;
tPROPID g_propMailMessageOS_PID;
tPROPID g_propMailerPID;


// AVP Prague stamp begin( C++ class declaration,  )
struct pr_novtable CIMAPProtocoller : public cTask {
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
	hOBJECT m_traffic_monitor;
	tDWORD m_dwSessionCount;
	hCRITICAL_SECTION m_hSessionCS;

// AVP Prague stamp begin( C++ class declaration end,  )
public:
	mDECLARE_INITIALIZATION(CIMAPProtocoller)
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
tERROR CIMAPProtocoller::ObjectInitDone() {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "Task::ObjectInitDone method" );

	// Place your code here
	if ( PR_SUCC(error) )
		error = PrepareObject<CIMAPProtocoller>(this, m_dwSessionCount, &m_hSessionCS, m_traffic_monitor, m_tm);

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( Internal (kernel called) interface method implementation, ObjectPreClose )
// Extended method comment
//    Kernel warns object it is going to close all children
// Behaviour comment
//    Object takes all necessary "before preclosing" actions
// Parameters are:
tERROR CIMAPProtocoller::ObjectPreClose() {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "Task::ObjectPreClose method" );

	// Place your code here
	error = ReleaseObject<CIMAPProtocoller>(this, &m_hSessionCS, m_traffic_monitor, m_tm);

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
tERROR CIMAPProtocoller::MsgReceive( tDWORD p_msg_cls_id, tDWORD p_msg_id, hOBJECT p_send_point, hOBJECT p_ctx, hOBJECT p_receive_point, tVOID* p_par_buf, tDWORD* p_par_buf_len ) {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "Task::MsgReceive method" );

	// Place your code here
	if (
		p_msg_cls_id == pmc_TASK_STATE_CHANGED &&
		/*m_state == TASK_STATE_RUNNING &&*/
		m_traffic_monitor &&
		p_send_point->propGetPID() == PID_TRAFFICMONITOR
		)
	{
		m_state = p_msg_id;
		sysSendMsg(pmc_TASK_STATE_CHANGED, m_state, NULL, NULL, NULL);
		return error;
	}
	return ProtocollerMsgReceive<ImapProtocolAnalyzer>("imap", *this, po_IMAP4, p_msg_cls_id, p_msg_id, p_send_point, p_ctx, p_receive_point, p_par_buf, p_par_buf_len, m_dwSessionCount, m_hSessionCS, (tTaskState)m_state);
}
// AVP Prague stamp end



// AVP Prague stamp begin( External (user called) interface method implementation, SetSettings )
// Parameters are:
tERROR CIMAPProtocoller::SetSettings( const cSerializable* p_settings ) {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "Task::SetSettings method" );

	// Place your code here

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( External (user called) interface method implementation, GetSettings )
// Parameters are:
tERROR CIMAPProtocoller::GetSettings( cSerializable* p_settings ) {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "Task::GetSettings method" );

	// Place your code here

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( External (user called) interface method implementation, AskAction )
// Parameters are:
tERROR CIMAPProtocoller::AskAction( tActionId p_actionId, cSerializable* p_actionInfo ) {
	tERROR error = errNOT_IMPLEMENTED;
	PR_TRACE_FUNC_FRAME( "Task::AskAction method" );

	// Place your code here

	return error;
}
// AVP Prague stamp end

// AVP Prague stamp begin( External (user called) interface method implementation, SetState )
// Parameters are:
tERROR CIMAPProtocoller::SetState( tTaskRequestState p_state ) {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "Task::SetState method" );

	{
		cAutoCS _cs_(m_hSessionCS, true);
		m_state = TASK_STATE_FAILED;
	}

	switch ( p_state )
	{
	case TASK_REQUEST_RUN:
		if (m_traffic_monitor || PR_SUCC(error = m_tm->GetService( TASKID_TM_ITSELF, *this, AVP_SERVICE_TRAFFICMONITOR, &m_traffic_monitor, cREQUEST_SYNCHRONOUS )))
		{
			sysRegisterMsgHandler(pmc_TASK_STATE_CHANGED, rmhLISTENER, m_tm, IID_ANY, PID_TRAFFICMONITOR, IID_ANY, PID_ANY);
			cAutoCS _cs_(m_hSessionCS, true);
			m_state = TASK_STATE_RUNNING;
		}
		break;
	case TASK_REQUEST_PAUSE:
		{
			cAutoCS _cs_(m_hSessionCS, true);
			m_state = TASK_STATE_PAUSED;
		}
		break;
	case TASK_REQUEST_STOP:
		// ����������� ���������� �������� �������
		PR_TRACE((this, prtIMPORTANT, "imap\tProcessing stop request..."));
		{
			cAutoCS _cs_(m_hSessionCS, true);
			m_state = TASK_STATE_COMPLETED;
		}
		PR_TRACE((this, prtIMPORTANT, "imap\tReleasing trafmon"));
		if ( m_traffic_monitor && PR_SUCC(this->sysCheckObject((hOBJECT)m_traffic_monitor)) )	
		{	
			sysUnregisterMsgHandler(pmc_TASK_STATE_CHANGED, m_tm);
			m_tm->ReleaseService(TASKID_TM_ITSELF, (hOBJECT)m_traffic_monitor);	
			m_traffic_monitor = NULL;	
		}	
		PR_TRACE((this, prtIMPORTANT, "imap\tSending pseudo stop"));
		if ( errOK_DECIDED == sysSendMsg(pmcTRAFFIC_PROTOCOLLER, pmSESSION_PSEUDO_STOP_REQUEST, 0,0,0))
		{
			// ���������, ���� ��� ������� ������ ����������� 
			// (�� ��������� � ��������� ������ m_pStateManager, ������� ��� ���������)
			PR_TRACE((this, prtIMPORTANT, "imap\tWaiting sessions (if any)"));
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
					PR_TRACE((this, prtIMPORTANT, "imap\tStill %d sessions to wait...", sess_count));
					last_trace = t;
				}
				Sleep(100);
			}
		}
		PR_TRACE((this, prtIMPORTANT, "imap\tStop request processed"));
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
tERROR CIMAPProtocoller::GetStatistics( cSerializable* p_statistics ) {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "Task::GetStatistics method" );

	// Place your code here

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( C++ class regitration,  )
// Interface "Task". Register function
tERROR CIMAPProtocoller::Register( hROOT root ) {
	tERROR error;
// AVP Prague stamp end



// AVP Prague stamp begin( Property table,  )
mpPROPERTY_TABLE(Task_PropTable)
	mSHARED_PROPERTY( pgINTERFACE_VERSION, Task_VERSION )
	mSHARED_PROPERTY_PTR( pgINTERFACE_COMMENT, "0", 2 )
	mpLOCAL_PROPERTY_BUF( pgTASK_TM, CIMAPProtocoller, m_tm, cPROP_BUFFER_READ_WRITE | cPROP_WRITABLE_ON_INIT | cPROP_REQUIRED )
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
		PID_IMAPPROTOCOLLER,                    // plugin identifier
		0x00000000,                             // subtype identifier
		Task_VERSION,                         // interface version
		VID_DENISOV,                            // interface developer
		&i_Task_vtbl,                         // internal(kernel called) function table
		(sizeof(i_Task_vtbl)/sizeof(tPTR)),   // internal function table size
		&e_Task_vtbl,                         // external function table
		(sizeof(e_Task_vtbl)/sizeof(tPTR)),   // external function table size
		Task_PropTable,                       // property table
		mPROPERTY_TABLE_SIZE(Task_PropTable), // property table size
		sizeof(CIMAPProtocoller)-sizeof(cObjImpl),// memory size
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


// AVP Prague stamp begin( C++ class regitration end,  )
	return error;
}

tERROR pr_call Task_Register( hROOT root ) { return CIMAPProtocoller::Register(root); }
// AVP Prague stamp end



// AVP Prague stamp begin( Caution !!!,  )
// You have to implement propetry: pgTASK_STATE
// You have to implement propetry: pgTASK_SESSION_ID
// You have to implement propetry: pgTASK_ID
// You have to implement propetry: pgTASK_PERSISTENT_STORAGE
// You have to implement propetry: pgTASK_PARENT_ID
// AVP Prague stamp end



