#ifndef _AVZAPI_H_
#define _AVZAPI_H_

#ifndef WINAPI
#	define WINAPI __stdcall
#endif
#ifndef IN
#	define IN 
#endif
#ifndef OUT
#	define OUT 
#endif
#if !defined(__IStream_INTERFACE_DEFINED__)
	struct IStream;
#endif

#ifndef PRAGUE_OLD_DEFINES
#include <Prague/pr_compl.h>
#include <Prague/pr_types.h>
#else
#include <pr_compl.h>
#include <pr_types.h>
#endif

// calling convention for AVZ functions
#define AVZCALL

// ���� ������ AVZ
enum AVZERROR
{
	AVZ_OK                   = 0x00000000, // ������ ���
	AVZ_Error                = 0xC0000000, // ������ (�������� �����, ��� ���������)
	AVZ_InvalidKernelHandle  = 0xC0000001, // ������������ ����� ����
	AVZ_InvalidDBPath        = 0xC0000002, // ������������ ���� � �����
	AVZ_LoadDBError          = 0xC0000003, // ������ �������� ���
	AVZ_Cancel               = 0xC0000004, // ��������� ����
	AVZ_InvalidStream        = 0xC0000005, // ������������ ����� - ��������� �������� ��������� �� �����, � ��� ���
	AVZ_StreamReadError      = 0xC0000006, // ������ ������ ������ �� ������
	AVZ_XMLParseError        = 0xC0000007, // ������ �������� XML
	AVZ_XMLTokenNotFound     = 0xC0000008, // XML ��� �� ������
	AVZ_InvalidFormatMask    = 0xC0000009, // ������������ �����, �������� ������ ��������������
	AVZ_InvalidCallbackID    = 0xC000000A, // ������������ ��� �������
	AVZ_InvalidScriptID      = 0xC000000B, // ������������ ID �������
	AVZ_InvalidScriptMode    = 0xC000000C, // ������������ ID ������ ������� �������
	AVZ_InvalidScriptDBHandle= 0xC000000D, // ������������ ����� ����
	AVZ_InvalidScript        = 0xC000000E, // ������ � �������
};
#define AVZ_SUCC(e) (e) == AVZ_OK
#define AVZ_FAIL(e) (e) != AVZ_OK

struct CAVZScanKernel;

// ���� ������� AVZ, ���������� � ScriptCallback
enum AVZMSG
{
	logNormal = 0,
	logInfo   = 1,
	logAlert  = 2,
	logVirus  = 3,
	logGood   = 4,
	logError  = 10,
	logDebug  = 11,
};


//////////////////////////////////////////////////////////////////////////
//
//	��������
//	�� ���� ��������� ������ ���������� ������ ���� �������� ������
//
	enum AVZCallback_t
	{
		avzcb_ScriptCallback = 0,	// ������������� tScriptCallback
		avzcb_GetLocalizedStr,		// ������������� tGetLocalizedStr
		avzcb_FreeLocalizedStr,		// ������������� tFreeLocalizedStr
		avzcb_CheckFileCallback,	// ������ �������� �����
		avzcb_LAST,
	};
	// ����������� �������� ���������� �������:
	// pTaskContext - �������� ����������� ������� (��� �������� ����� �������� � ��������, ��������� AVZ_GetSomeInfo)
	// ��������� ��������� - �������� ������� (��� �����������, ��������, ��������-����)
	// ���� ������� ���������� AVZ_Cancel, �� ���������� ���������� ������� ������������ � AVZ_GetSomeInfo ���� ���������� AVZ_Cancel.
	// ������������� ������ ��� szMsg AVZ, ������� ����� ����� �������� ���������� �� ��������. � ���� ������ ���������� ��� ������ ��� ����� ���� � ��������.
	typedef  AVZERROR (  WINAPI *tScriptCallback ) ( 
		IN void* pTaskContext,
		IN tDWORD dwProgressCur,   // ����� �������� �������
		IN tDWORD dwProgressMax,   // ����� ���������� ������� (�.�. ��������������� � � ��� ������������� ��� ��������-����)
		IN wchar_t* szMsg,        // �������� ������� (���� ���������, ��� ��� ��������������)
		IN tDWORD    dwMsgSize,    // ������ ������ �������� �������
		IN AVZMSG   dwMsgType     // ��� �������
		);
	//////////////////////////////////////////////////////////////////////////
	//
	// �������� ����� ��-��� avzkrnl ������� ����������� (����������� �� ������� ������� CheckFile)
	//
		enum AVZCheckResult_t
		{
			avzcr_Error = 0xC0000000,      // - ������ (���� �� ������ ��� � ���� ��� �������)
			avzcr_Clean = 0,               // - ���� �� �������� � ���� ���������� � �� ������� ��� �����������
			avzcr_VirusFound = 1,          // - ���� ������� ��� ����������� ������
			avzcr_Suspicious = 2,          // - ���� �� �������� � ���� ���������� � ������������� ��� ����������� ������
			avzcr_CleanBase = 3,           // - ���� ������� �� ���� ������ �������� �������� ����������		
		};
		typedef  AVZERROR ( WINAPI *tCheckFile ) ( 
			IN void* pTaskContext,				// �������� ������
			IN wchar_t* szFileName,				// ��� ����� ��� ��������
			OUT AVZCheckResult_t* pCheckResult	// ��������� ��������
		);
	//
	// �������� ����� ��-��� avzkrnl ������� �����������
	//
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//
	// �������� �����������
	//
		// ��������� ������ �� ��������������
		typedef  AVZERROR ( WINAPI *tGetLocalizedStr ) ( 
			IN void* pTaskContext,    // �������� ������
			IN  char* szID,           // ������������� ������������ ������
			OUT wchar_t** pszResult   // �������������� ������
			);
		// ������������ ������
		typedef  AVZERROR ( WINAPI *tFreeLocalizedStr ) ( 
			IN void* pTaskContext,    // �������� ������
			IN wchar_t* szResult      // ��������� �� ����� � �������������� ������� ��� ������������ ������
			);
	//
	// �������� �����������
	//
	//////////////////////////////////////////////////////////////////////////
//
//	��������
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
//  ������������� AVZ. 
//
	AVZERROR AVZ_InitializeExA( 
			 OUT CAVZScanKernel** ppAVZAScanKernel, // �������� ���� AVZ
			 IN const char* szBasesPath,            // ���� � ����� AVZ
			 IN const char* szProductType           // ��� ��������
			 );	
	AVZERROR AVZ_InitializeExW( 
			 OUT CAVZScanKernel** ppAVZAScanKernel, // �������� ���� AVZ
			 IN const wchar_t* szPath,              // ���� � ����� AVZ
			 IN const wchar_t* szProductType        // ��� ��������
			 );
	AVZERROR AVZ_SetCallbackCtx(
			IN CAVZScanKernel* pAVZAScanKernel,     // �������� ���� AVZ
			IN void* pTaskContext                   // �������� ������. ����� �������� ������ ���������� � ������ ��������
			);
	AVZERROR AVZ_SetCallbackProc(
			IN CAVZScanKernel* pAVZAScanKernel,     // �������� ���� AVZ
			IN AVZCallback_t dwCallBackID,			// ������������� ��������
			IN void* pCallBackProc					// ��������� �� �������
			);
	// ��������� ������ � AVZ
	AVZERROR AVZ_Done( 
			 IN CAVZScanKernel* pAVZAScanKernel     // �������� ���� AVZ
			 );
//
//  ������������� AVZ. 
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
//	������ � ������
//
	enum AVZ_DBStatus_t
	{
		AVZ_DBStatus_MainBase		= 1, // - ������� ���� -
		AVZ_DBStatus_Macros			= 2, // - ���� ����������� �������� Office (���� �� �����������) -
		AVZ_DBStatus_Clean			= 4, // - ���� ������ +
		AVZ_DBStatus_ScriptsHeur	= 8, // - ���� �������� ������������� �������� ������� +
		AVZ_DBStatus_ScriptsVul		= 16, // - ���� �������� ������������� �������� �������, ���������� ��� (�������� �����������) +
		AVZ_DBStatus_ScriptsRecovery= 32, // - ���� �������� �������������� ������� +
		AVZ_DBStatus_Scripts		= 64, // - ���� ����������� �������� +
		AVZ_DBStatus_Memory			= 128, // - ���� ������� ������ -
		AVZ_DBStatus_MemoryHeur		= 256, // - ���� ���������� ������� ��� ������� ������ -
		AVZ_DBStatus_Drivers		= 512, // - ���� ������� ���������� +/- (����� � ������� �� ������� AVP, �� -)
	};
	// ��������� ������� �������� ��� AVZ (���������� ������� ����� �� DBStatus_t)
	tDWORD    AVZ_GetDBStatus( 
			 IN CAVZScanKernel* pAVZAScanKernel     // �������� ���� AVZ
			 );

	// ���������� ��� AVZ (����� �������)
	AVZERROR AVZ_ReloadBase( 
			 IN CAVZScanKernel* pAVZAScanKernel     // �������� ���� AVZ
			 );		
//
//	������ � ������
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
//	������ � AVZ
//
	// �������� ����� ������������ ����� AVZ (�������������� �������)
	AVZERROR AVZ_CheckFile( 
			 IN CAVZScanKernel* pAVZAScanKernel,    // �������� ���� AVZ
			 IN char* szFileName,                   // ��� �����
			 IN OUT char* szVerdict                 // ��������� ��������
			 );

	// ���������� ������������� ������� AVZ � ��������� ����������
	AVZERROR AVZ_GetSomeInfo( 
			 IN CAVZScanKernel* pAVZAScanKernel,    // �������� ���� AVZ
			 IN wchar_t* szScript,                  // ����� �������
			 IN void* pScriptContext,               // �������� ������� (this)
			 IN OUT IStream* pXMLStream             // ����� ��� ��������� ��������� ������ �������
			 );

	// ���������� ���������� �������
	// { return AVZ_GetSomeInfo(pAVZAScanKernel, szScript, NULL, NULL, NULL); };
	AVZERROR AVZ_RunScript( 
			 IN CAVZScanKernel* pAVZAScanKernel,    // �������� ���� AVZ
			 IN wchar_t* szScript                   // ����� �������
			 );

	// ��������� �� XML ������� ��������� (��� ���������� ������ ���������� ��������)
	// ������ �������� ��������� (szBufFormat):
	//		����: 
	//			ftByte (1 ���� ��� �����),
	//			ftWord (2 ����� ��� �����), 
	//			ftDWORD (4 ����� ��� �����), 
	//			ftInteger (4 ����� �� ������),  
	//			ftPChar - ��������� �� Ascii ������ c ����������� �����,
	//			ftPWChar - ��������� �� Unicode ������ c ����������� �����. 
	//		�����������:
	//			������� - ����������� ����� ����� � ��������� ���������
	//			����� � ������� - ����������� �������� �����
	//		��������� ��������:
	//			����� � ���������� ������� (��� �������� �����) 
	//			������ (��� �������, ������� ",", ";" � "=" � ������ �� ���������)
	//		������ �� �������� ������������
	//		���������� �������� �� ������������ ��������
	// ������ szBufFormat:
	//		L"PID=ftDWORD,0; File=ftPWChar,; CheckResult=ftInteger,-1; Descr=ftPWChar,; LegalCopyright=ftPWChar,; CmdLine=ftPWChar,; Size=ftDWORD,0; Attr=ftPWChar,; CreateDate=ftPWChar,; ChageDate=ftPWChar,; MD5=ftPWChar,"
	//		��� ������ ������� ��������� ������ ���������� ������� (� ����������� ������� � ���������� ��������� ��������, ��������� � szBufFormat):
	// 		struct record_t
	// 		{
	// 			record_t* m_pNextItem; // ��� ���� ��������� �� ��������� ������� ���������� ������. ��� ���������� ����� = NULL
	// 			tDWORD     m_dwPID;
	// 			wchar_t*  m_szFile; 
	// 			int       m_iCheckResult; 
	// 			wchar_t*  m_szDescr; 
	// 			wchar_t*  m_szLegalCopyright; 
	// 			wchar_t*  m_szCmdLine; 
	// 			tDWORD     m_szSize; 
	// 			wchar_t*  m_szAttr; 
	// 			wchar_t*  m_szCreateDate; 
	// 			wchar_t*  m_szChageDate; 
	// 			wchar_t*  m_szMD5;
	// 		}
	// ������� ����� ����������� ����������� ���� ������:
	// AVZ_InvalidStream - ������� ������� ��������� �� ������ ISTREAM = NULL
	// AVZ_StreamReadError - ������ ������ ������ �� ������
	// AVZ_XMLParseError - ������ � ���� �������� XML
	// AVZ_XMLTokenNotFound - ��������� ��� �� ������
	// AVZ_InvalidFormatMask - ������ � �������� ������� ���������
	AVZERROR AVZ_DeserializeXML( 
			 IN CAVZScanKernel* pAVZAScanKernel,    // �������� ���� AVZ
			 IN IStream* pXMLStream,                // ����� � XML
			 IN wchar_t* szTagName,                 // ��� ���� ������� ������, ��� ���������� ����� ������������� � ���������
			 IN wchar_t* szBufFormat,               // �������� ���������
			 OUT void** ppAVZBuffer,                // ��������� �� ������ ������� ���������� ������ ��������
			 OUT tDWORD* pdwAVZBufSize              // ������ pAVZBuffer (����� ������ ��� �������)
			 );

	// ������������ ������, ����������� � ���� AVZ.
	// ������������ ����� ������� AVZ_DeserializeXML
	AVZERROR AVZ_Free( 
			 IN CAVZScanKernel* pAVZAScanKernel,    // �������� ���� AVZ
			 IN void* pAVZBuffer                    // ����� ��� ������������
			 );

	//////////////////////////////////////////////////////////////////////////
	//
	// ���������� �������, ����������� � ���� AVZ
	//	����� ������ ������� ���, ��� Check/Fix ����� �������� ����������� ��� ������ ��� �������. 
	//	Check/Fix �����������, �.�. � ������ ����� ����� Fix ����� ��� ��� ������� Check � 
	//	���� �� ������ 0, �� ��� ������ ��� ��� � ���, ��� �������� ������������� ���� ���������� ...
	AVZERROR AVZ_LoadCustomScriptDB(
			 IN CAVZScanKernel* pAVZAScanKernel,    // �������� ���� AVZ
			 wchar_t* szDBFilename,					// ��� ���������� ����
			 OUT void** ppDBHandle					// �������� ���������� ����
			 );
	AVZERROR AVZ_FreeCustomScriptDB(
			 IN CAVZScanKernel* pAVZAScanKernel,    // �������� ���� AVZ
			 IN void* pDBHandle						// �������� ���������� ����
			 );
	AVZERROR AVZ_GetCustomScriptCount(
			 IN CAVZScanKernel* pAVZAScanKernel,    // �������� ���� AVZ
			 IN void* pDBHandle,					// �������� ���������� ����
			 OUT tDWORD* pdwCount					// ���������� ��������
			 );
	enum CustomScriptRunMode_t 
	{
		csmode_Check = 1, 
		csmode_Fix = 2,
		csmode_SuperFix = 3,
		csmode_CheckUndo = 4,
		csmode_Undo = 5,
	};
	enum csCheckResult_t
	{
		csres_Check_Unknown = -1,
		csres_Check_Clean = 0,		// �������� �� ������� ���� ��� ���������
		csres_Check_FoundLow = 1,	// ������� �������������� ��������, ������� ������ ����� �� ������ ��������� ������� �� ������������ � ����������������� �������
		csres_Check_FoundMedium = 2,// ������� �������� ������� �������
		csres_Check_FoundHigh = 3,	// ������� ������� ��������, ������� ������������ ������������� ���������� ���������
	};
	enum csFixResult_t
	{
		csres_Fix_OK = 0,			// �������� ��������� 
		csres_Fix_Fail = 1,			// �������� �� �������
		csres_Fix_NeedReboot = 2,	// �������� ���������, ��������� ������������ ����������
	};
	enum csCheckUndoResult_t
	{
		csres_CheckUndo_NotFound = 0,	// ����� ����������
		csres_CheckUndo_OK = 1,			// ����� ��������
	};
	enum csUndoResult_t
	{
		csres_Undo_OK = 0,			// ����� ��������
		csres_Undo_Fail = 1,		// ����� �� ������
		csres_Undo_NeedReboot = 2,	// ����� ��������, ��������� ������������ ����������
	};
	AVZERROR AVZ_RunCustomScript(
			 IN CAVZScanKernel* pAVZAScanKernel,    // �������� ���� AVZ
			 IN void* pDBHandle,					// �������� ���������� ����
			 IN tDWORD dwScriptID,					// ������������� ������� (������ �� 0 �� N-1). ���� ������ ��� ���������, �� ���������� � ������� AVZ_InvalidScriptID  = C000000B
			 IN tDWORD dwScriptMode,				// ����� ������� ������� (csmode_Check/csmode_Fix/...). ���� ��� �� 1 ��� 2, �� ���������� � ������� AVZ_InvalidScriptMode = C000000C
			 OUT tDWORD* pdwResult					// ��� csmode_Check:csCheckResult_t, ��� csmode_Fix � csmode_SuperFix:csFixResult_t, ��� csmode_CheckUndo:csCheckUndoResult_t, ��� csmode_Undo:csUndoResult_t
			 );
	//
	// ���������� �������, ����������� � ���� AVZ
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//
	//	������ AVZ � ����������
	//
		// ������ ��������� �����
		AVZERROR AVZ_SR_Init(
			IN CAVZScanKernel* pAVZAScanKernel,     // �������� ���� AVZ
			IN const wchar_t* szFileName,			// ��� ��������������� �����
			OUT tDWORD* pdwSessionID				// ������������� ������ 
			);
		// ��������� ��������� �����
		AVZERROR AVZ_SR_Done(
			IN tDWORD dwSessionID
			);
		// ���� ������� ��� AVZ_SR_AddEvent
		enum AVZ_SR_Event_t {
			AVZ_SR_EVENT_API_STR = 0,				// ����� �������� ��������� ������������� ��������� API-�������
		};
		// ���������� �������. ���������� ���������� ����������� ��� �������� ��������� ������� � ��������� ���������� �����
		AVZERROR AVZ_SR_AddEvent(
			IN tDWORD dwSessionID, 					// ������������� ������ 
			IN tDWORD dwEventType,					// ��� ���� �������
			IN const void* pEventData,				// ��������� �� ����� � �������, ������������ �������
			IN tDWORD dwEventDataSize				// ������ ������
			);
		// �������� ����� ������ ��� �������. ���������� ���������� �����������
		AVZERROR AVZ_SR_Memory(
			IN tDWORD dwSessionID, 					// ������������� ������ 
			IN tDWORD dwProcessID,					// ������������� ��������
			IN tDWORD qwBaseAddr,					// ������� �����
			IN const void* pMemory,					// ��������� �� ����� ������
			IN tDWORD dwDataSize					// ������ ������
			);
		// ���� ��������� ��� AVZ_SR_GetSecurityRating
		enum AVZ_SR_SecurityRating_t {
			AVZ_SR_RATING_SEVERITY = 0,				// ����� ������� ���������/������������ �� N-�������� �����
		};
		// ������ SecurityRating. ARatingType - ��� ���� ��������
		AVZERROR AVZ_SR_GetSecurityRating(
			IN tDWORD dwSessionID, 					// ������������� ������ 
			IN tDWORD ARatingType,					// ��� ���� ��������
			OUT tDWORD* pRes						// �������
			);
	//
	//	������ AVZ � ����������
	//
	//////////////////////////////////////////////////////////////////////////
//
//	������ � AVZ
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
//  Typedefs for explicit import
//
	typedef AVZERROR (AVZCALL * tAVZ_InitializeExW)( 
		OUT CAVZScanKernel** ppAVZAScanKernel, // �������� ���� AVZ
		IN const wchar_t* szPath,              // ���� � ����� AVZ
		IN const wchar_t* szProductType        // ��� ��������
		);
	typedef AVZERROR (AVZCALL * tAVZ_Done)( 
		IN CAVZScanKernel* pAVZAScanKernel     // �������� ���� AVZ
		);
	typedef AVZERROR (AVZCALL * tAVZ_SR_Init)(
		IN CAVZScanKernel* pAVZAScanKernel,     // �������� ���� AVZ
		IN const wchar_t* szFileName,			// ��� ��������������� �����
		OUT tDWORD* pdwSessionID				// ������������� ������ 
		);
	typedef AVZERROR (AVZCALL * tAVZ_SR_Done)(
		IN tDWORD dwSessionID
		);
	typedef AVZERROR (AVZCALL * tAVZ_SR_AddEvent)(
		IN tDWORD dwSessionID, 					// ������������� ������ 
		IN tDWORD dwEventType,					// ��� ���� �������
		IN const void* pEventData,				// ��������� �� ����� � �������, ������������ �������
		IN tDWORD dwEventDataSize				// ������ ������
		);
	typedef AVZERROR (AVZCALL * tAVZ_SR_Memory)(
		IN tDWORD dwSessionID, 					// ������������� ������ 
		IN tDWORD dwProcessID,					// ������������� ��������
		IN tDWORD qwBaseAddr,					// ������� �����
		IN const void* pMemory,					// ��������� �� ����� ������
		IN tDWORD dwDataSize					// ������ ������
		);
	typedef AVZERROR (AVZCALL * tAVZ_SR_GetSecurityRating)(
		IN tDWORD dwSessionID, 					// ������������� ������ 
		IN tDWORD ARatingType,					// ��� ���� ��������
		OUT tDWORD* pRes						// �������
		);
//
//	Typedefs for explicit import
//
//////////////////////////////////////////////////////////////////////////



#endif//_AVZAPI_H_
