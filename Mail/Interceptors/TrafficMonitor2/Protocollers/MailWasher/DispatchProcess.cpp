#include "dispatchprocess.h"

#define	SOCKETBUFSIZE 0x2000

void ClearCallback( CSimpleBufferWindow* _this, tDWORD context, tVOID* data )
{
	// �������� ������ �� ��������������
	tBYTE* pData = _this->View();
	tDWORD dwDataSize = _this->GetSize();
	if ( dwDataSize )
	{
		//TODO: �� ������ ���� ���������� �� ������� ������, � ���������� (������ �� ������������ ���������)!
		detect_t hDetectParams;
		hDetectParams.assign(*((session_t*)data), false);
		hDetectParams.dsDataSource = ((ClearCallbackData*)data)->dsDataSource;
		hDetectParams.pLastReceivedData = pData;
		hDetectParams.ulLastReceivedData = dwDataSize;
		hDetectParams.pdcDetectCode = ((ClearCallbackData*)data)->pdcDetectCode;
		hDetectParams.phDetectorHandle = ((ClearCallbackData*)data)->phDetectorHandle;
		cERROR err = errOK;
		if ( !hDetectParams.phDetectorHandle || !*hDetectParams.phDetectorHandle )
			err = errOBJECT_BAD_PTR;
		if ( PR_SUCC(err) )
			err = (*hDetectParams.phDetectorHandle)->sysSendMsg( pmcTRAFFIC_PROTOCOLLER, pmDETECT, 0, &hDetectParams, SER_SENDMSG_PSIZE );
		if ( PR_FAIL(err) ) 
			*((ClearCallbackData*)data)->pdcDetectCode = dcNeedMoreInfo;
	}
}

void CreateReportLetter(IN tBOOL bFullMessage, IN cStringObj* szOriginalLetter, OUT cStringObj& szReportLetter)
{
	szOriginalLetter->replace_all("\r\n.\r\n", 0, "\r\n..\r\n");
	szReportLetter += "From: Kaspersky MailDispatcher\r\n";
	szReportLetter += "Subject: [!! SPAM] The message has been deleted\r\n";
	szReportLetter += CLocalTime::getRfc822Date().c_str();
	szReportLetter += "\r\n";
	szReportLetter += "Content-Type: multipart/mixed;\r\n";
	szReportLetter +=		"\tboundary=Kaspersky-MailDispatcher\r\n";
	szReportLetter += "MIME-Version: 1.0\r\n";
	
//	szReportLetter += "\r\n--Kaspersky-MailDispatcher\r\n";
//	szReportLetter += "Content-type: text/plain; \r\n";
//	szReportLetter +=	"\tcharset=us-ascii\r\n";
//	szReportLetter += "\r\n";
	szReportLetter += "The message has been deleted\r\n";
	
	szReportLetter += "\r\n--Kaspersky-MailDispatcher\r\n";
	szReportLetter += bFullMessage ? "Content-type: message/rfc822\r\n" :"Content-type: text/plain\r\n" ;
	szReportLetter += "Content-Transfer-Encoding: 8bit\r\n";
	szReportLetter += "\r\n";
	szReportLetter += (char*)szOriginalLetter->c_str(cCP_ANSI);
	szReportLetter += "\r\n";

	szReportLetter += "\r\n--Kaspersky-MailDispatcher--\r\n";
	szReportLetter += "\r\n";
	szReportLetter += ".";
	szReportLetter += "\r\n";
}

CDispatchProcess::CDispatchProcess(
	CMailWasher* pMailWasher,
	hOBJECT&   hParent,
	session_t& hSessionCtx,
	recv_t&    p_recv,
	send_t&    p_send,
	detect_code_t& dcPOP3DetectCode,
	hOBJECT&   hPOP3Protocoller
	):
	m_pMailWasher(pMailWasher),
	m_hParent(hParent),
	m_recv(p_recv),
	m_send(p_send),
	m_dcPOP3DetectCode(dcPOP3DetectCode),
	m_hPOP3Protocoller(hPOP3Protocoller),
	m_dsDataSource(dsUnknown),
	m_bWaitServerDeleResponse(false)
{
	m_ccdClient.assign(hSessionCtx, false);
	m_ccdClient.dsDataSource = dsClient; 
	m_ccdClient.pdcDetectCode = &m_dcPOP3DetectCode; 
	m_ccdClient.phDetectorHandle = &m_hPOP3Protocoller;
	m_ccdServer.assign(hSessionCtx, false);
	m_ccdServer.dsDataSource = dsServer; 
	m_ccdServer.pdcDetectCode = &m_dcPOP3DetectCode; 
	m_ccdServer.phDetectorHandle = &m_hPOP3Protocoller;
	m_pBuf_Client = new CSimpleBufferWindow(SOCKETBUFSIZE * 2, ClearCallback, (tDWORD)this, &m_ccdClient);
	m_pBuf_Server = new CSimpleBufferWindow(SOCKETBUFSIZE * 2, ClearCallback, (tDWORD)this, &m_ccdServer);
}

CDispatchProcess::~CDispatchProcess()
{
	if ( m_pBuf_Client )
	{
		delete m_pBuf_Client;
		m_pBuf_Client = NULL;
	}
	if ( m_pBuf_Server )
	{
		delete m_pBuf_Server;
		m_pBuf_Server = NULL;
	}
}

tERROR CDispatchProcess::DispatchProcess(process_t* pProcessParams)
{
	PR_TRACE((m_hParent, prtIMPORTANT, "mc\tCMailWasher: Dispatching data (ds is %s)...", GetDataSourceStr(pProcessParams->dsDataSource)));

	cERROR err = errOK;
	detect_code_t& dcDetectCode = m_dcPOP3DetectCode;
	hOBJECT& hProtocoller = m_hPOP3Protocoller;
	
	*(pProcessParams->psStatus) = psKeepAlive;

	//////////////////////////////////////////////////////////////////////////
	//
	//	1. ���� ���� ������ RETR �� ��������� ���� ������ - �� ���������� ���! �������� �������������� "+OK\r\n"
	//	2. ���� ���� ������ DELE �� ��������� ���� ������ - �� ���������� ���! �������� �������������� 
	//	3. ���� ���� ������ LIST �� ��������� ���� ������ - �� ���������� ���! �������� �������������� 
	//	4. ���� ���� ������ TOP �� ��������� ���� ������ - �� ���������� ���! �������� ��������������
	//	5. ����� ������ ������� ����� ����������
	//
	tBOOL bRecvIsDELE	= cFALSE;
	tBOOL bRecvIsRETR	= cFALSE;
	tBOOL bRecvIsList	= cFALSE;
	tBOOL bRecvIsTop	= cFALSE;
	tBOOL bRecvQuit		= cFALSE;
	tBOOL bFullClientCmd = cFALSE;

	{
		tBOOL bCommandHasBeenDeleted = cFALSE;
		data_source_t dsDataSource = pProcessParams->dsDataSource;
		if ( 
			dsDataSource == dsClient && 
			!m_recv.NeedMore("\r\n", 2) 
			)
		{
			bFullClientCmd = cTRUE;

			tDWORD dwDeleNumber = 0;
			tDWORD dwRetrNumber = 0;
			tDWORD dwListNumber = 0;
			tDWORD dwTopNumber = 0;

			bRecvIsDELE = m_recv.IsDELE(dwDeleNumber);
			bRecvIsRETR = m_recv.IsRETR(dwRetrNumber);
			bRecvIsList = m_recv.IsLIST(dwListNumber);
			bRecvIsTop	= m_recv.IsTOP(dwTopNumber);
			bRecvQuit	= m_recv.IsQUIT();

			cStringObj szReplacedData;
			cPOP3Message* pOperatedMessage = NULL;
			bCommandHasBeenDeleted = 
				(bRecvIsDELE && m_pMailWasher->HasBeenDeleted(dwDeleNumber, &pOperatedMessage)) ||
				(bRecvIsRETR && m_pMailWasher->HasBeenDeleted(dwRetrNumber, &pOperatedMessage)) ||
				(bRecvIsList && m_pMailWasher->HasBeenDeleted(dwListNumber, &pOperatedMessage)) ||
				(bRecvIsTop  && m_pMailWasher->HasBeenDeleted(dwTopNumber,  &pOperatedMessage))
				;
			tBOOL bCommandHasBeenDownloaded = 
				(bRecvIsRETR && m_pMailWasher->HasBeenDownloaded(dwRetrNumber, &pOperatedMessage))
				;
			if ( bRecvIsDELE && bCommandHasBeenDeleted)
			{
				// ������� ������ ����� ������, � �� �� "quit" ����� � ������ �� ������� "list" ���� ���������
				szReplacedData.format(cCP_ANSI, "DELE %d\r\n", dwDeleNumber);
				m_pMailWasher->Send(dsServer, szReplacedData.c_str(cCP_ANSI), szReplacedData.length());
				//pOperatedMessage->m_bDeleted = cFALSE;
				m_recv.Clear();
				m_pBuf_Client->Clear(cFALSE);
				return errOK_DECIDED;
			}
			else if ( bRecvIsList && bCommandHasBeenDeleted)
			{
				// � ������ �������� "+OK N M\r\n" (��� N - ����� ���������, M - ��� ������), ����� ������ �� ������ �����
				szReplacedData.format(cCP_ANSI, "+OK %d %d\r\n", dwListNumber, pOperatedMessage->m_dwSize);
				m_pMailWasher->Send(dsClient, szReplacedData.c_str(cCP_ANSI), szReplacedData.length());
				m_recv.Clear();
				m_pBuf_Client->Clear(cFALSE);
				return errOK_DECIDED;
			}
			else if ( bRecvIsTop && bCommandHasBeenDeleted)
			{
				// � ������ ��������, ����� ������ �� ������ �����
				szReplacedData = "+OK\r\n";
				CreateReportLetter(bCommandHasBeenDownloaded, &pOperatedMessage->m_szData, szReplacedData);
				m_pMailWasher->Send(dsClient, szReplacedData.c_str(cCP_ANSI), szReplacedData.length());
				m_recv.Clear();
				m_pBuf_Client->Clear(cFALSE);
				return errOK_DECIDED;
			}
			else if ( bRecvIsRETR && bCommandHasBeenDeleted )
			{
				// ���� ������� ��� ������, ������� ���� ���������� � ������, ���� ��� ������� "-ERR". ��� Outlook2003 ((
				// �������� ���� �������� "+OK\r\n"
				szReplacedData = "+OK\r\n";
				CreateReportLetter(bCommandHasBeenDownloaded, &pOperatedMessage->m_szData, szReplacedData);
				m_pMailWasher->Send(dsClient, szReplacedData.c_str(cCP_ANSI), szReplacedData.length());
				m_recv.Clear();
				m_pBuf_Client->Clear(cFALSE);
				return errOK_DECIDED;
			}
			else if ( bRecvIsRETR && bCommandHasBeenDownloaded )
			{
				// ��������� ��� ��������� ������
				szReplacedData = "+OK\r\n";
				pOperatedMessage->m_szData.replace_all("\r\n.\r\n", 0, "\r\n..\r\n");
				szReplacedData += pOperatedMessage->m_szData;
				szReplacedData += "\r\n";
				szReplacedData += ".";
				szReplacedData += "\r\n";
				m_pMailWasher->Send(dsClient, szReplacedData.c_str(cCP_ANSI), szReplacedData.length());
				m_recv.Clear();
				m_pBuf_Client->Clear(cFALSE);
				return errOK_DECIDED;
			}
			else if (bRecvQuit)
			{
				// ������������ ������� (������� ��� ��������� �� �������� ������ � ���������� quit �������)

				// ����������� ������ ����� ��� ��������
				CollectMarkedLetters();

				// �������� ���������� ������� ��������� ������ � � ����� �������� QUIT
				m_bWaitServerDeleResponse = RemoveNextLetter();

				// ������ ���� �� ������� ������ �� ���� ��������
				
				m_recv.Clear();
				m_pBuf_Client->Clear(cFALSE);
				return errOK_DECIDED;
			}
		}

		if (dsDataSource == dsServer && m_bWaitServerDeleResponse)
		{
			// �������� ����� �� ������� �� �������� �����
			if (!m_recv.NeedMore("\r\n", 2))
			{
				// ����� ������, ����� ������� ��������� ������ ���� �����
				m_bWaitServerDeleResponse = RemoveNextLetter();
				m_recv.Clear();
				m_pBuf_Server->Clear(cFALSE);
			}

			return errOK_DECIDED;
		}
	}
	//
	//	1. ���� ���� ������ RETR �� ��������� ���� ������ - �� ���������� ���! �������� �������������� "+OK\r\n"
	//	2. ���� ���� ������ DELE �� ��������� ���� ������ - �� ���������� ���! �������� �������������� "+OK\r\n"
	//	3. ����� ������ ������� ����� ����������
	//
	//////////////////////////////////////////////////////////////////////////

	// ��������� ��������� ReadWriteSocket
	{
		if ( pProcessParams->dsDataSource == dsClient )
		{
			m_pBuf_Client->Insert((tBYTE*)pProcessParams->pData, pProcessParams->ulDataSize, cFALSE);
			if ( m_dsDataSource != pProcessParams->dsDataSource )
			{
				// ������������� ���������� ���� �������, � �������� ���
				m_dsDataSource = pProcessParams->dsDataSource;
				m_pBuf_Server->Clear();
			}
		}
		else if (  pProcessParams->dsDataSource == dsServer )
		{
			m_pBuf_Server->Insert((tBYTE*)pProcessParams->pData, pProcessParams->ulDataSize, cFALSE);
			if ( m_dsDataSource != pProcessParams->dsDataSource )
			{
				// ������������� ���������� ���� �������, � �������� ���
				m_dsDataSource = pProcessParams->dsDataSource;
				m_pBuf_Client->Clear();
			}
		}

		if ( dcDetectCode != dcDataDetected )
		{
			// ������ ������� (������� �������) ����� �������� ������ ���� ��� ������
			if ((dsClient == pProcessParams->dsDataSource) && bFullClientCmd)
			{
				// �������� ������� �� ������
				// ���-������ � ����� �� ������� ������ ������, ���������� ����� ����� �� ��������������
				// � �������� ����������� dcDataDetected
				m_pMailWasher->Translate(dsServer, auto_io_t(m_recv).io(), cFALSE);
			}
			else if (dsServer == pProcessParams->dsDataSource)
			{
				m_pMailWasher->Translate(dsClient, auto_io_t(m_recv).io(), cFALSE);
			}
		}
		else
		{
			// ������������� ������
			// �������� ������ ������������
			m_pBuf_Server->Clear(cFALSE);
			m_pBuf_Client->Clear(cFALSE);
			process_t hProcessParams;
			hProcessParams.assign(*pProcessParams, false);
			hProcessParams.phDetectorHandle = &hProtocoller;
			err = hProtocoller->sysSendMsg( pmcTRAFFIC_PROTOCOLLER, pmPROCESS, 0, &hProcessParams, SER_SENDMSG_PSIZE );
			if ( *(hProcessParams.psStatus) == psProcessFailed ) 
				dcDetectCode = dcNeedMoreInfo;
			else if(dcDetectCode == dcNeedMoreInfo && bRecvIsRETR)
				dcDetectCode = dcDataDetected;
		}

		if (!m_recv.NeedMore("\r\n", 2) || dsServer == pProcessParams->dsDataSource)
		{
			// ������ ����� �������
			m_recv.Clear();
		}
	}
	

	*(pProcessParams->psStatus) = psKeepAlive;

	PR_TRACE((m_hParent, prtIMPORTANT, "mc\tCMailWasher: Dispatching data done"));

	return errOK_DECIDED;
}

tERROR CDispatchProcess::DispatchProtocollerMessage(process_msg_t* ppmCommand)
{
	cERROR err = errOK;
	detect_code_t& dcDetectCode = m_dcPOP3DetectCode;
	PR_TRACE(( m_hParent, prtNOTIFY, "mc\tCMailWasher::DispatchProtocollerMessage => " ));
	if ( 
		ppmCommand->psStatus == psProcessFinished ||
		ppmCommand->psStatus == psProcessFailed ||
		ppmCommand->psStatus == psCloseConnection
		)
	{
		PR_TRACE(( m_hParent, prtNOTIFY, "mc\tCMailWasher::DispatchProtocollerMessage => psProcessFinished" ));
		dcDetectCode = dcNeedMoreInfo;
	}
	err = m_pMailWasher->Translate(ppmCommand->dsDataTarget, ppmCommand->hData, (ppmCommand->psStatus == psCloseConnection));

	return err;
}

tERROR CMailWasher::DispatchProcess(process_t* pProcessParams)
{
	if ( !m_pDispatchProcess )
		m_pDispatchProcess = new CDispatchProcess(
			this,
			m_InitParams.hParent,
			m_hSessionCtx,
			m_recv,
			m_send,
			m_dcPOP3DetectCode,
			m_InitParams.hPOP3Protocoller
			);
	if ( m_pDispatchProcess )
		return m_pDispatchProcess->DispatchProcess(pProcessParams);
	return errOBJECT_NOT_CREATED;
}

tERROR CMailWasher::DispatchProtocollerMessage(process_msg_t* ppmCommand)
{
	if ( !m_pDispatchProcess )
		m_pDispatchProcess = new CDispatchProcess(
			this,
			m_InitParams.hParent,
			m_hSessionCtx,
			m_recv,
			m_send,
			m_dcPOP3DetectCode,
			m_InitParams.hPOP3Protocoller
			);
	if ( m_pDispatchProcess )
		return m_pDispatchProcess->DispatchProtocollerMessage(ppmCommand);
	return errOBJECT_NOT_CREATED;
}

tDWORD CDispatchProcess::CollectMarkedLetters()
{
	m_lettersIdToDelete.clear();
	return  m_pMailWasher->CollectMarkedLetters(m_lettersIdToDelete);
}

bool CDispatchProcess::RemoveNextLetter()
{
	bool bSuccessSend = false;
	while (!m_lettersIdToDelete.empty() && !bSuccessSend)
	{
		cStringObj request;
		request.format(cCP_ANSI, "DELE %d\r\n", m_lettersIdToDelete.back());

		if (PR_SUCC(m_pMailWasher->Send(dsServer, request.c_str(cCP_ANSI), request.length())))
		{
			bSuccessSend = true;
			m_bWaitServerDeleResponse = true;
		}
		
		m_lettersIdToDelete.erase(m_lettersIdToDelete.end() - 1);
	}

	if (!bSuccessSend)
	{
		// ���� �� ���������� ��������� �� ����� �������
		// ��� ��� ��������� ������ ��� ������� ������ �������� QUIT
		cStringObj request;
		request.format(cCP_ANSI, "QUIT\r\n");
		m_pMailWasher->Send(dsServer, request.c_str(cCP_ANSI), request.length());
	}

	// ������ ���� �� ������� ������ �� ���� ��������

	return bSuccessSend;
}