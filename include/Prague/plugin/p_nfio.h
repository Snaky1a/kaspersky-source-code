// --------------------------------------------------------------------------------
// AVP Prague stamp begin( Interface header,  )
// -------- ANSI C Code Generator 2.0 --------
// -------- Friday,  18 March 2005,  14:18 --------
// -------------------------------------------
// Copyright � Kaspersky Labs 1996-2004.
// -------------------------------------------
// Project     -- Not defined
// Sub project -- Not defined
// Purpose     -- Unix native file IO
// Author      -- petrovitch
// File Name   -- plugin_nfio.c
// Additional info
//    File input/output for Unix
// -------------------------------------------
// AVP Prague stamp end



// --------------------------------------------------------------------------------
// AVP Prague stamp begin( Header ifndef,  )
#if !defined( __public_plugin_unix_nfio )
#define __public_plugin_unix_nfio
// AVP Prague stamp end



// --------------------------------------------------------------------------------
// AVP Prague stamp begin( Header includes,  )
#include <Prague/prague.h>
#include <Prague/iface/i_os.h>
#include <Prague/iface/i_objptr.h>
#include <Prague/iface/i_io.h>
// AVP Prague stamp end



// --------------------------------------------------------------------------------
// AVP Prague stamp begin( Plugin identifier,  )
#define PID_NFIO  ((tPID)(3))
// AVP Prague stamp end



// --------------------------------------------------------------------------------
// AVP Prague stamp begin( Vendor identifier,  )
#define VID_PETROVITCH  ((tVID)(100))
// AVP Prague stamp end



#define fOMODE_OPEN_IF_EXECUTABLE      ((tDWORD)(0x01000000L))


// --------------------------------------------------------------------------------
// AVP Prague stamp begin( Plugin public definitions, OS )
// OS interface implementation
// Short comments -- object system interface

// message class
//! #define pmc_OS_VOLUME 0x75eb704a // ��������� � �����
// AVP Prague stamp end



// --------------------------------------------------------------------------------
// AVP Prague stamp begin( Plugin public definitions, ObjPtr )
// ObjPtr interface implementation
// Short comments -- Object Enumerator (Pointer to Object)

// properties
#define plMASK_CP                 mPROPERTY_MAKE_LOCAL( pTYPE_CODEPAGE, 0x00002001 )
#define plMASK_APPLIED_TO_FOLDERS mPROPERTY_MAKE_LOCAL( pTYPE_BOOL    , 0x00002002 )
// AVP Prague stamp end



// --------------------------------------------------------------------------------
// AVP Prague stamp begin( Plugin public definitions, IO )
// IO interface implementation
// Short comments -- input/output interface

// constants

// ----------  PrCopy/PrMoveFileEx constants  ----------
#define fPR_FILE_REPLACE_EXISTING           ((tDWORD)(0x00000001L)) // applied for PrMoveFileEx & PrCopy functions
#define fPR_FILE_DELAY_UNTIL_REBOOT         ((tDWORD)(0x00000004L)) // applied for PrMoveFileEx & PrCopy functions
#define fPR_FILE_MOVE_COPY_ALLOWED          ((tDWORD)(0x00000002L)) // applied for PrMoveFileEx function
#define fPR_FILE_MOVE_WRITE_THROUGH         ((tDWORD)(0x00000008L)) // applied for PrMoveFileEx function
#define fPR_FILE_NAME_PREPARSING            ((tDWORD)(0x00000010L)) // applied for PrCopy function

// ----------  PrGetErrorMode/PrSetErrorMode constants  ----------
#define fPR_SEM_FAILCRITICALERRORS     ((tDWORD)(0x00000001L)) //  --
#define fPR_SEM_NOGPFAULTERRORBOX      ((tDWORD)(0x00000002L)) //  --
#define fPR_SEM_NOALIGNMENTFAULTEXCEPT ((tDWORD)(0x00000004L)) //  --
#define fPR_SEM_NOOPENFILEERRORBOX     ((tDWORD)(0x80000000L)) //  --

// ----------  PrExecute flags  ----------
#define fPR_EXECUTE_WAIT               ((tDWORD)(0x00000001L)) //  --

// properties
#define plNATIVE_HANDLE            mPROPERTY_MAKE_LOCAL( pTYPE_DWORD   , 0x00002001 )
#define plEXCLUSIVE_ACCESS         mPROPERTY_MAKE_LOCAL( pTYPE_BOOL    , 0x00002002 )
#define plRESTORE_ATTRIBUTES       mPROPERTY_MAKE_LOCAL( pTYPE_BOOL    , 0x00002003 )
#define plIGNORE_RO_ATTRIBUTE      mPROPERTY_MAKE_LOCAL( pTYPE_BOOL    , 0x00002004 )
#define plCONTROL_SIZE_ON_READ     mPROPERTY_MAKE_LOCAL( pTYPE_BOOL    , 0x00002005 )
#define plEXTENDED_NAME_PROCESSING mPROPERTY_MAKE_LOCAL( pTYPE_BOOL    , 0x00002006 )
#define plIS_REMOTE                mPROPERTY_MAKE_LOCAL( pTYPE_DWORD   , 0x00002007 )
#define plNATIVE_PATH              mPROPERTY_MAKE_LOCAL( pTYPE_STRING  , 0x00002008 )
#define plPREPARSE_NAME            mPROPERTY_MAKE_LOCAL( pTYPE_BOOL    , 0x00002009 )
#define plSAVE_FILE_TIME           mPROPERTY_MAKE_LOCAL( pTYPE_BOOL    , 0x0000200a )

// message class
//    �������� "send_point" � ����� �� ���� ��������� ����� ���� ������ �� ���� �����: OS, ObjPtr ��� IO
//! #define pmc_IO 0x52e986b3 // ����� ��������� ��������� � ������������� �������� OS, ObjPtr � IO
// AVP Prague stamp end



// --------------------------------------------------------------------------------
// AVP Prague stamp begin( Interface comment,  )

// OS interface implementation
// Short comments -- object system interface
//    Interface defines behavior of an object system. It responds for
//      - enumerate IO and Folder objects by creating Folder objects.
//      - create and delete IO and Folder objects
//    There are two possible ways to create or open IO object on OS. First is three steps protocol:
//      -- call ObjectCreate system method and get new IO (Folder) object
//      -- dictate properties of new object
//      -- call ObjectCreateDone system method and have working object
//    Second is using FolderCreate and IOCreate methods which must have the same behivior i.e. FolderCreate and IOCreate are wrappers for convenience.
//    Advise: when caller invokes ObjectCreateDone method OS object receives ChildDone notification and can do all necessary job to process it.
//


// ObjPtr interface implementation
// Short comments -- pointer to the object


// IO interface implementation
// Short comments -- input/output interface
//    Defines behavior of input/output of an object
//    Important -- It is supposed several clients can use single IO object simultaneously. It has no internal current position.
// AVP Prague stamp end



// --------------------------------------------------------------------------------
// AVP Prague stamp begin( ,  )

// OS declarations

// ObjPtr declarations

// IO declarations
#define fACCESS_NONE                   ((tDWORD)(0x01000000L)) // object has to be closed
#define fOMODE_DONT_CACHE_POS          ((tDWORD)(0x01000000L)) // do not cache file position

// OS declarations

// ObjPtr declarations

// IO declarations

// OS declarations

// ObjPtr declarations

// IO declarations
#define plNATIVE_HANDLE    mPROPERTY_MAKE_LOCAL( pTYPE_DWORD   , 0x00002001 )
#define plEXCLUSIVE_ACCESS mPROPERTY_MAKE_LOCAL( pTYPE_BOOL    , 0x00002002 )
// AVP Prague stamp end



// --------------------------------------------------------------------------------
// AVP Prague stamp begin( Header endif,  )
#endif // __public_plugin_unix_nfio
// AVP Prague stamp end



// --------------------------------------------------------------------------------
// AVP Prague stamp begin( Plugin export methods,  )
#ifdef IMPEX_TABLE_CONTENT
{ (tDATA)&PrCopy, PID_NFIO, 0xf292d15bl },
{ (tDATA)&PrMoveFileEx, PID_NFIO, 0x19baae35l },
{ (tDATA)&PrSetErrorMode, PID_NFIO, 0xd457c4ffl },
{ (tDATA)&PrGetTempFileName, PID_NFIO, 0x31725308l },
{ (tDATA)&PrCreateDir, PID_NFIO, 0x8fc48b23l },
{ (tDATA)&PrExecute, PID_NFIO, 0xd79c3509l },
{ (tDATA)&PrGetTempDir, PID_NFIO, 0x5bf195c6l },
{ (tDATA)&PrPeparseFileName, PID_NFIO, 0xf97328fdl },

#elif defined(IMPEX_EXPORT_LIB) || defined(IMPEX_IMPORT_LIB)
#include <Prague/iface/impexhlp.h>

IMPEX_DECL tERROR IMPEX_FUNC(PrCopy)( hOBJECT p_src, hOBJECT p_dst, tDWORD p_flags )IMPEX_INIT;
IMPEX_DECL tERROR IMPEX_FUNC(PrMoveFileEx)( hOBJECT p_src_name, hOBJECT p_dst_name, tDWORD p_flags )IMPEX_INIT;
IMPEX_DECL tDWORD IMPEX_FUNC(PrSetErrorMode)( tDWORD p_errMode )IMPEX_INIT;
IMPEX_DECL tERROR IMPEX_FUNC(PrGetTempFileName)( hOBJECT p_path, const tVOID* p_prefix, tCODEPAGE p_cp )IMPEX_INIT;
IMPEX_DECL tERROR IMPEX_FUNC(PrCreateDir)( hOBJECT p_path )IMPEX_INIT;
IMPEX_DECL tERROR IMPEX_FUNC(PrExecute)( hOBJECT p_executable, hSTRING p_cmd_line, hSTRING p_start_dir, tDWORD* p_result, tDWORD p_flags )IMPEX_INIT;
IMPEX_DECL tERROR IMPEX_FUNC(PrGetTempDir)( hOBJECT p_result_path, const tVOID* p_sub_dir, tCODEPAGE p_cp )IMPEX_INIT;
IMPEX_DECL tERROR IMPEX_FUNC(PrPeparseFileName)( hSTRING p_file_name )IMPEX_INIT;
#endif
// AVP Prague stamp end



