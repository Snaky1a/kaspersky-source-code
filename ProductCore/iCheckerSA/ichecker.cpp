// AVP Prague stamp begin( Interface header,  )
// -------- ANSI C++ Code Generator 1.0 --------
// -------- Tuesday,  25 January 2005,  19:01 --------
// -------------------------------------------
// Copyright � Kaspersky Labs 1996-2004.
// -------------------------------------------
// Project     -- Kaspersky Anti-Virus
// Sub project -- KAV6
// Purpose     -- Not defined
// Author      -- Pavlushchik
// File Name   -- ichecker.cpp
// -------------------------------------------
// AVP Prague stamp end



// AVP Prague stamp begin( Interface version,  )
#define IChecker_VERSION ((tVERSION)1)
// AVP Prague stamp end


// AVP Prague stamp begin( Header includes,  )
#include <Prague/prague.h>
#include <Prague/iface/i_io.h>
#include <Prague/iface/i_root.h>
#include <Prague/plugin/p_hash_md5.h>
#include <Prague/plugin/p_win32_nfio.h>

#include <ProductCore/plugin/p_icheckersa.h>
// AVP Prague stamp end

#include <windows.h>

//#include "../../prague/MKavIO/plugin_mkavio.h"
#define PID_MKAVIO  ((tPID)(61015))
#define plMKAV_FIDBOX		mPROPERTY_MAKE_LOCAL( pTYPE_BINARY    , 0x00002009 )

#include "../../Windows/hook/Hook/FSDrvLib.h"
#include "../../Windows/hook/Hook/IDriver.h"

#include <pshpack1.h>
typedef struct tag_FIDBOX_DATA {
	DWORD		m_DataFormatId;				// must be 0
	BYTE		m_VolumeID[16];
	BYTE		m_FileID[16];
	tQWORD qwHash;
	tBYTE  bData[20];
} tFIDBOX_DATA;
#include <poppack.h>

#define STATUS_NOT_FOUND				((DWORD)0xC0000225L)
#define _mkav_io_handle					((HANDLE) 0xF0000001)

tFIDBOX_DATA g_fiddata_empty;

// AVP Prague stamp begin( C++ class declaration,  )
struct pr_novtable iCheckerSA : public cIChecker {
private:
// Internal function declarations
	tERROR pr_call ObjectInit();
	tERROR pr_call ObjectInitDone();
	tERROR pr_call ObjectPreClose();

// Property function declarations

public:
// External function declarations
	tERROR pr_call GetStatus( tDWORD* result, hIO p_io, tBYTE* p_pData, tDWORD p_dwDataSize, tDWORD* p_pStatusBuffer, tDWORD p_dwStatusBufferSize );
	tERROR pr_call UpdateStatus( hIO p_io, tDWORD* p_pStatusBuffer, tDWORD p_dwStatusBufferSize );
	tERROR pr_call DeleteStatus( hIO p_io );
	tERROR pr_call FlushStatusDB();
	tERROR pr_call ClearStatusDB();

// Data declaration
// AVP Prague stamp end

private:
	tERROR iCheckerSA::iGetHandleFromObj(hOBJECT hObject, HANDLE* phNativeHandle, hIO* pIo);

// AVP Prague stamp begin( C++ class declaration end,  )
public:
	mDECLARE_INITIALIZATION(iCheckerSA)
};
// AVP Prague stamp end

#define cFIDBOX_PROP_DATA                 ((tSTRING)("FIDBOX_PROP_DATA"))
static tPROPID propFIDBOX_DATA = 0;


tERROR GetFIDBOXDataWithDriver(HANDLE hNativeHandle, tFIDBOX_DATA* pFIDBOX_data)
{
	// to do
	ULONG DataSize = sizeof(tFIDBOX_DATA);
	if (IDriver_FidBox_Get(FSDrvGetDeviceHandle(), FSDrvGetAppID(), hNativeHandle, pFIDBOX_data, &DataSize))
	{
		if (0 != memcmp(pFIDBOX_data, &g_fiddata_empty, sizeof(tFIDBOX_DATA)))
		{
			PR_TRACE(( g_root, prtNOTIFY, "ichsa\tGetFIDBOXDataWithDriver successed - data valid"));
			return errOK;
		}

		PR_TRACE(( g_root, prtNOTIFY, "ichsa\tGetFIDBOXDataWithDriver successed, but data not valid (returning errNOT_FOUND)"));
		return errNOT_FOUND;
	}

	DWORD err = GetLastError();
	if (err == 0xc0000225)
	{
		PR_TRACE(( g_root, prtNOTIFY, "ichsa\tGetFIDBOXDataWithDriver failed - not found (err 0x%x)", err));
	}
	else
	{
		PR_TRACE(( g_root, prtERROR, "ichsa\tGetFIDBOXDataWithDriver failed (err 0x%x)", err));
	}

	if (err == STATUS_NOT_FOUND)
		return errNOT_FOUND;

	return errNOT_SUPPORTED;
}

tERROR SetFIDBOXDataWithDriver(HANDLE hNativeHandle, tFIDBOX_DATA* pFIDBOX_data)
{
	if (IDriver_FidBox_Set(FSDrvGetDeviceHandle(), FSDrvGetAppID(), hNativeHandle, pFIDBOX_data, sizeof(tFIDBOX_DATA)))
		return errOK;

	DWORD err = GetLastError();
	PR_TRACE(( g_root, prtERROR, "ichsa\tSetFIDBOXDataWithDriver failed (err 0x%x)", err));

	if (err == STATUS_NOT_FOUND)
		return errNOT_FOUND;

	return errUNEXPECTED;
}

// AVP Prague stamp begin( Global property variable declaration,  )
// Interface "IChecker". Static(shared) property table variables
// AVP Prague stamp end



// AVP Prague stamp begin( Internal (kernel called) interface method implementation, ObjectInit )
// Extended method comment
//    Kernel notifies an object about successful creating of object
// Behaviour comment
//    Initializes internal object data
// Result comment
//    Returns value differ from errOK if object cannot be initialized
// Parameters are:
tERROR iCheckerSA::ObjectInit() {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "IChecker::ObjectInit method" );

	// Place your code here
	if (!FSDrvInterceptorInit())
		error = errNOT_SUPPORTED;

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( Internal (kernel called) interface method implementation, ObjectInitDone )
// Extended method comment
//    Notification that all necessary properties have been set and object must go to operation state
// Result comment
//    Returns value differ from errOK if object cannot function properly
// Parameters are:
tERROR iCheckerSA::ObjectInitDone() {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "IChecker::ObjectInitDone method" );

	memset(&g_fiddata_empty, 0, sizeof(g_fiddata_empty));

	if (propFIDBOX_DATA == 0)
		error = sysGetRoot()->RegisterCustomPropId(&propFIDBOX_DATA, cFIDBOX_PROP_DATA, pTYPE_BINARY);

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( Internal (kernel called) interface method implementation, ObjectPreClose )
// Extended method comment
//    Kernel warns object it is going to close all children
// Behaviour comment
//    Object takes all necessary "before preclosing" actions
// Parameters are:
tERROR iCheckerSA::ObjectPreClose() {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "IChecker::ObjectPreClose method" );

	// Place your code here
	FSDrvInterceptorDone();

	return error;
}
// AVP Prague stamp end


tERROR iCheckerSA::iGetHandleFromObj(hOBJECT hObject, HANDLE* phNativeHandle, hIO* pIo)
{
	tERROR error;
	hIO hIo;

	if (!pIo || !phNativeHandle)
		return errPARAMETER_INVALID;

	*pIo = NULL;
	*phNativeHandle = NULL;

	if (PR_SUCC(error = sysCheckObject(hObject, IID_IO, PID_NATIVE_FIO)))
	{
		error = hObject->propGet(NULL, plNATIVE_HANDLE, phNativeHandle, sizeof(HANDLE));
		return error;
	}

	if (PR_SUCC(error = sysCheckObject(hObject, IID_IO, PID_MKAVIO)))
	{
		*phNativeHandle = _mkav_io_handle;
		return errOK;
	}

	if (PR_SUCC(error = sysCheckObject(hObject, IID_STRING)))
	{
		hSTRING hStr = (hSTRING)hObject;
		if (PR_SUCC(error = hObject->sysCreateObject((hOBJECT*)&hIo, IID_IO, PID_NATIVE_FIO)))
		{
			error = hIo->set_pgOBJECT_OPEN_MODE(fOMODE_OPEN_IF_EXIST);
			if (PR_SUCC(error))
				error = hIo->set_pgOBJECT_ACCESS_MODE(0);
			if (PR_SUCC(error))
				error = hStr->ExportToProp(NULL, cSTRING_WHOLE, (hOBJECT) hIo, pgOBJECT_FULL_NAME);
			if (PR_SUCC(error))
				error = hIo->sysCreateObjectDone();	
			if (PR_SUCC(error))
				error = hIo->propGet(NULL, plNATIVE_HANDLE, phNativeHandle, sizeof(HANDLE));
			if (PR_SUCC(error))
				*pIo = hIo;
			if (PR_FAIL(error))
				hIo->sysCloseObject();
		}
		if (PR_FAIL(error))
		{
			PR_TRACE((this, prtERROR, "icsa\tGetHandleFromObj: cannot create IO from string '%tstr'", hObject));
		}
		return error;
	}

	return errOBJECT_INCOMPATIBLE;
}


// AVP Prague stamp begin( External (user called) interface method implementation, GetStatus )
// Extended method comment
//    ��� ��������� ��������������� ������, ����� ������� ���������� ��� ��� �����. ��� ��������� �� ���������� ������ �� ����� (� ����������� �� ��������� �����), � ����� ������ ��������� � ��������� pData. �����, ������� � ���� ������ ��������, ��������������� � ���� ����� � ���������� ��. ������ ��������������� ������ ��������� �����  DWORD'���.
// Behaviour comment
//    ���������� errMODULE_UNKNOWN_FORMAT � ������, ����� ���������� ��������� ��� ��� ������� �����.
// Parameters are:
//   "dwDataSize"         : ����������� � ������
tERROR iCheckerSA::GetStatus( tDWORD* result, hIO p_io, tBYTE* p_pData, tDWORD p_dwDataSize, tDWORD* p_pStatusBuffer, tDWORD p_dwStatusBufferSize ) {
	tERROR error = errOK;
	tDWORD ret_val = 0;
	tQWORD qwHash;
	hOBJECT hObj = NULL;
	hHASH hHashMD5;
	tDWORD bHashMD5[4];
//	tDWORD dwLength;
//	WCHAR wcszFileName[MAX_PATH];
//	WCHAR* pwcszFileName = wcszFileName;
//	WCHAR  wcszPrefix[] = L"\\\\?\\";
	HANDLE hNativeHandle = NULL;
	hIO hNewIO = NULL; 
	tFIDBOX_DATA FIDBOX_data;

//#define PREFIX_LEN 4
//#define PREFIX_LEN_W (PREFIX_LEN*sizeof(wcszPrefix[0]))

	PR_TRACE_FUNC_FRAME( "IChecker::GetStatus method" );

	if (result)
		*result = 0;

	if (p_dwDataSize > 0)
		return errNOT_SUPPORTED;

	if (p_dwStatusBufferSize > sizeof(FIDBOX_data.bData))
	{
		PR_TRACE(( this, prtERROR, "ichsa\tGetStatus\tInvalid size %d", p_dwStatusBufferSize));
		return errBAD_SIZE;
	}

	// actually we can receive any object, not only IO
	hObj = (hOBJECT)p_io;

	if (PR_FAIL(error = hObj->sysCreateObjectQuick((hOBJECT*)&hHashMD5, IID_HASH, PID_HASH_MD5)))
	{
		PR_TRACE(( this, prtERROR, "ichsa\tiCheckerSA::GetStatus can't create hash object with %terr", error));
		return error;
	}

	error = iGetHandleFromObj((hOBJECT)p_io, &hNativeHandle, &hNewIO);

	if (PR_FAIL(error))
	{
		if ( error == errOBJECT_INCOMPATIBLE )
			PR_TRACE(( this, prtWARNING, "ichsa\tFailed to get native handle for object (incompatible object)"));
		else
			PR_TRACE(( this, prtERROR, "ichsa\tFailed to get native handle for object (%terr)", error));
		return error;
	}


	// retrieve file name 

//	error = hObj->propGetStr(&dwLength, pgOBJECT_FULL_NAME, 0, 0, cCP_UNICODE);
//	if (PR_SUCC(error))
//	{
//		if (dwLength + PREFIX_LEN_W > sizeof(wcszFileName))
//			error = hObj->heapAlloc((tPTR*)&pwcszFileName, dwLength + PREFIX_LEN_W);
//		else
//			pwcszFileName = wcszFileName; // use local buffer
//	}
//	
//	if (PR_SUCC(error))
//	{
//		memcpy(pwcszFileName, wcszPrefix, PREFIX_LEN * sizeof(wcszPrefix[0]));
//		error = hObj->propGetStr(&dwLength, pgOBJECT_FULL_NAME, pwcszFileName + PREFIX_LEN, dwLength, cCP_UNICODE);
//	}

	// calculate hash from file name and attributes
	if (PR_SUCC(error))
	{
		hIO io = hNewIO;
		if (PR_SUCC(sysCheckObject((hOBJECT)p_io, IID_IO)))
			io = p_io;
		if (io)
		{
			tDWORD dwAttributes;
			tQWORD qwSize;
			tDATETIME dt;
			
			if (PR_SUCC(error))
				error = io->GetSize(&qwSize, IO_SIZE_TYPE_EXPLICIT);
			if (PR_SUCC(error))
				error = hHashMD5->Update((tBYTE*)&qwSize, sizeof(qwSize));
			if (PR_SUCC(error))
				error = io->get_pgOBJECT_CREATION_TIME(&dt);
			if (PR_SUCC(error))
				error = hHashMD5->Update((tBYTE*)&dt, sizeof(dt));
			if (PR_SUCC(error))
				error = io->get_pgOBJECT_LAST_WRITE_TIME(&dt);
			if (PR_SUCC(error))
				error = hHashMD5->Update((tBYTE*)&dt, sizeof(dt));
			if (PR_SUCC(error))
			{
				dwAttributes = io->get_pgOBJECT_ATTRIBUTES();
				dwAttributes &= ~(FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_NORMAL); // ignore ARCHIVE & NORMAL attribute (Backup agents may change archive attribute)
				error = hHashMD5->Update((tBYTE*)&dwAttributes, sizeof(dwAttributes));
			}
		}


//		WIN32_FILE_ATTRIBUTE_DATA sFAData;
//		if (!GetFileAttributesExW(pwcszFileName, GetFileExInfoStandard, &sFAData))
//		{
//			tDWORD dwW32Err = GetLastError();
//			error = errUNEXPECTED;
//		}
//		else
//		{
//			tDWORD i;
//			sFAData.ftLastAccessTime.dwHighDateTime = 0;
//			sFAData.ftLastAccessTime.dwLowDateTime  = 0;
//			sFAData.dwFileAttributes &= ~(FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_NORMAL); // ignore ARCHIVE & NORMAL attribute (Backup agents may change archive attribute)
//			error = hHashMD5->Update((tBYTE*)&sFAData, sizeof(sFAData));
//
//
//			// extract file name from path
//			dwLength += PREFIX_LEN_W;
//			for (i=dwLength/2-2; i>0; i--)
//			{
//				if (pwcszFileName[i] == '\\' || pwcszFileName[i] == '/')
//					break;
//			}
//			if (PR_SUCC(error))
//				error = hHashMD5->Update((tBYTE*)(pwcszFileName+i+1), dwLength-(i+2)*2);
//		}
	}

//	if (pwcszFileName && pwcszFileName != wcszFileName)
//		hObj->heapFree(pwcszFileName);
	
	if (PR_SUCC(error) && p_dwDataSize != 0)
		error = hHashMD5->Update(p_pData, p_dwDataSize);
	if (PR_SUCC(error))
		error = hHashMD5->GetHash((tBYTE*)&bHashMD5[0], sizeof(bHashMD5));
	if (PR_SUCC(error))
	{
		// build qword hash from MD5 (128 bit -> 64 bit)
		tDWORD* pShortHash = (tDWORD*)&qwHash;
		pShortHash[0] = bHashMD5[0] ^ bHashMD5[2] ^ IChecker_VERSION;
		pShortHash[1] = bHashMD5[1] ^ bHashMD5[3];
	}
	hHashMD5->sysCloseObject();

	// get data from driver
	if (PR_SUCC(error))
	{
		if (_mkav_io_handle == hNativeHandle)
		{
			tDWORD outsize;
			error = CALL_SYS_PropertyGet(p_io, &outsize, plMKAV_FIDBOX, &FIDBOX_data, sizeof(FIDBOX_data));
		}
		else
			error = GetFIDBOXDataWithDriver(hNativeHandle, &FIDBOX_data);
	}

	if (PR_SUCC(error) && FIDBOX_data.qwHash != qwHash)
	{
		error = warnDEFAULT;
		FIDBOX_data.qwHash = qwHash;
		memset(&FIDBOX_data.bData, 0, sizeof(FIDBOX_data.bData));
	}

	if (PR_SUCC(error))
		hObj->propSet(NULL, propFIDBOX_DATA, &FIDBOX_data, sizeof(FIDBOX_data));
	
	if (PR_FAIL(error))
		memset(p_pStatusBuffer, 0, p_dwStatusBufferSize);
	else
		memcpy(p_pStatusBuffer, &FIDBOX_data.bData, p_dwStatusBufferSize);
	if (result)
		*result = p_dwStatusBufferSize;
	
	if (hNewIO)
		hNewIO->sysCloseObject();

	if (PR_FAIL(error))
	{
		PR_TRACE(( this, prtERROR, "ichsa\tiCheckerSA::GetStatus failed with %terr", error));
		return error;
	}

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( External (user called) interface method implementation, UpdateStatus )
// Parameters are:
tERROR iCheckerSA::UpdateStatus( hIO p_io, tDWORD* p_pStatusBuffer, tDWORD p_dwStatusBufferSize ) {
	tERROR error = errOK;
	HANDLE hNativeHandle = NULL;
	hIO hNewIO = NULL; 
	tFIDBOX_DATA FIDBOX_data;
	
	PR_TRACE_FUNC_FRAME( "IChecker::UpdateStatus method" );
	
	if (p_dwStatusBufferSize > sizeof(FIDBOX_data.bData))
		return errBAD_SIZE;
	
	if (PR_FAIL(error = p_io->propGet(NULL, propFIDBOX_DATA, &FIDBOX_data, sizeof(FIDBOX_data))))
		return errOBJECT_DATA_CORRUPTED;
	
	if (PR_FAIL(error = iGetHandleFromObj((hOBJECT)p_io, &hNativeHandle, &hNewIO)))
		return error;

	// push data to driver
	FIDBOX_data.m_DataFormatId = 0;
	memset(&FIDBOX_data.bData, 0, sizeof(FIDBOX_data.bData));
	memcpy(&FIDBOX_data.bData, p_pStatusBuffer, p_dwStatusBufferSize);

	if (_mkav_io_handle == hNativeHandle)
	{
		tDWORD outsize;
		error = CALL_SYS_PropertySet(p_io, &outsize, plMKAV_FIDBOX, &FIDBOX_data, sizeof(FIDBOX_data));
	}
	else
		error = SetFIDBOXDataWithDriver(hNativeHandle, &FIDBOX_data);

	if (hNewIO)
		hNewIO->sysCloseObject();

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( External (user called) interface method implementation, DeleteStatus )
// Parameters are:
tERROR iCheckerSA::DeleteStatus( hIO p_io ) {
	tERROR error = errOK;
	HANDLE hNativeHandle = NULL;
	hIO hNewIO = NULL; 
	tFIDBOX_DATA FIDBOX_data;
	
	PR_TRACE_FUNC_FRAME( "IChecker::DeleteStatus method" );

//	if (PR_FAIL(error = p_io->propGet(NULL, propFIDBOX_DATA, &FIDBOX_data, sizeof(FIDBOX_data))))
//		return errOBJECT_DATA_CORRUPTED;
	
	if (PR_FAIL(error = iGetHandleFromObj((hOBJECT)p_io, &hNativeHandle, &hNewIO)))
		return error;

	// push data to driver
	if (_mkav_io_handle == hNativeHandle)
	{
		tDWORD outsize;

		FIDBOX_data.m_DataFormatId = 0;
		FIDBOX_data.qwHash = 0;
		memset(&FIDBOX_data.bData, 0, sizeof(FIDBOX_data.bData));

		error = CALL_SYS_PropertySet(p_io, &outsize, plMKAV_FIDBOX, &FIDBOX_data, sizeof(FIDBOX_data));
	}
	else
	{
		error = GetFIDBOXDataWithDriver( hNativeHandle, &FIDBOX_data );

		if (PR_SUCC(error))
		{
			FIDBOX_data.m_DataFormatId = 0;
			FIDBOX_data.qwHash = 0;
			memset(&FIDBOX_data.bData, 0, sizeof(FIDBOX_data.bData));

			error = SetFIDBOXDataWithDriver(hNativeHandle, &FIDBOX_data);
		}
	}

	if (hNewIO)
		hNewIO->sysCloseObject();

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( External (user called) interface method implementation, FlushStatusDB )
// Extended method comment
//    ����� ������������ ��� �������������� ������ ����������� � ������� ���������� ������ ������ � ���������� �������� ������� �������� (��������, ����������� ���������� �������).
// Parameters are:
tERROR iCheckerSA::FlushStatusDB() {
	tERROR error = errOK;
	PR_TRACE_FUNC_FRAME( "IChecker::FlushStatusDB method" );

	// Nothing to do here

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( External (user called) interface method implementation, ClearStatusDB )
// Parameters are:
tERROR iCheckerSA::ClearStatusDB() {
	tERROR error = errNOT_IMPLEMENTED;
	PR_TRACE_FUNC_FRAME( "IChecker::ClearStatusDB method" );

	// Place your code here

	return error;
}
// AVP Prague stamp end



// AVP Prague stamp begin( C++ class regitration,  )
// Interface "IChecker". Register function
tERROR iCheckerSA::Register( hROOT root ) {
	tERROR error;
// AVP Prague stamp end



// AVP Prague stamp begin( Property table,  )
mpPROPERTY_TABLE(IChecker_PropTable)
	mSHARED_PROPERTY( pgINTERFACE_VERSION, IChecker_VERSION )
	mSHARED_PROPERTY_PTR( pgINTERFACE_COMMENT, "", 1 )
mpPROPERTY_TABLE_END(IChecker_PropTable)
// AVP Prague stamp end



// AVP Prague stamp begin( Internal method table,  )
mINTERNAL_TABLE_BEGIN(IChecker)
	mINTERNAL_METHOD(ObjectInit)
	mINTERNAL_METHOD(ObjectInitDone)
	mINTERNAL_METHOD(ObjectPreClose)
mINTERNAL_TABLE_END(IChecker)
// AVP Prague stamp end



// AVP Prague stamp begin( External method table,  )
mEXTERNAL_TABLE_BEGIN(IChecker)
	mEXTERNAL_METHOD(IChecker, GetStatus)
	mEXTERNAL_METHOD(IChecker, UpdateStatus)
	mEXTERNAL_METHOD(IChecker, DeleteStatus)
	mEXTERNAL_METHOD(IChecker, FlushStatusDB)
	mEXTERNAL_METHOD(IChecker, ClearStatusDB)
mEXTERNAL_TABLE_END(IChecker)
// AVP Prague stamp end



// AVP Prague stamp begin( Registration call,  )

	PR_TRACE_FUNC_FRAME_( *root, "IChecker::Register method", &error );

	error = CALL_Root_RegisterIFace(
		root,                                   // root object
		IID_ICHECKER2,                          // interface identifier
		PID_ICHECKERSA,                         // plugin identifier
		0x00000000,                             // subtype identifier
		IChecker_VERSION,                       // interface version
		VID_MIKE,                               // interface developer
		&i_IChecker_vtbl,                       // internal(kernel called) function table
		(sizeof(i_IChecker_vtbl)/sizeof(tPTR)), // internal function table size
		&e_IChecker_vtbl,                       // external function table
		(sizeof(e_IChecker_vtbl)/sizeof(tPTR)), // external function table size
		IChecker_PropTable,                     // property table
		mPROPERTY_TABLE_SIZE(IChecker_PropTable),// property table size
		sizeof(iCheckerSA)-sizeof(cObjImpl),    // memory size
		0                                       // interface flags
	);

	#ifdef _PRAGUE_TRACE_
		if ( PR_FAIL(error) )
			PR_TRACE( (root,prtDANGER,"IChecker(IID_ICHECKER2) registered [%terr]",error) );
	#endif // _PRAGUE_TRACE_
// AVP Prague stamp end



// AVP Prague stamp begin( C++ class regitration end,  )
	return error;
}

tERROR pr_call IChecker_Register( hROOT root ) { return iCheckerSA::Register(root); }
// AVP Prague stamp end
