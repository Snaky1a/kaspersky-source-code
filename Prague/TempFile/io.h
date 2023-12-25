// AVP Prague stamp begin( Interface header,  )
// -------- Tuesday,  22 April 2003,  16:35 --------
// -------------------------------------------
// Copyright (c) Kaspersky Labs. 1996-2002.
// -------------------------------------------
// Project     -- Not defined
// Sub project -- Not defined
// Purpose     -- ������ ������ � ���������� �������
// Author      -- Andy Nikishin
// File Name   -- io.h
// Additional info
//    ���� ������ ������ ��� ������ � ���������� �������. ��� ���� ����� ������������� ��������� � ������. ���� ������ ����� ��������� ����� ��������� �������� (� ������� ���������� 16 ��������), ���������� �������� ����� �� �����, � � ����������� ���� ������ � ������ ����� ����� ������.
// -------------------------------------------
// AVP Prague stamp end



// AVP Prague stamp begin( Header ifndef,  )
#if !defined( __io_h__7b1b6411_62dd_4c90_8429_8f0318e104d3 )
#define __io_h__7b1b6411_62dd_4c90_8429_8f0318e104d3
// AVP Prague stamp end



// AVP Prague stamp begin( Plugin identifier,  )
// AVP Prague stamp end



// AVP Prague stamp begin( Vendor identifier,  )
// AVP Prague stamp end



// AVP Prague stamp begin( Header includes,  )
#include <IFace/i_root.h>
#include <IFace/i_io.h>
#include "plugin_temporaryio.h"
#include <IFace/i_string.h>
#include <IFace/windows.h.h>
#include <IFace/i_seqio.h>
// AVP Prague stamp end



// AVP Prague stamp begin( Interface constants,  )
#define MAX_PATH                       ((tDWORD)(260)) //
#define PID_TEMPIO                     ((tDWORD)(TEMPIO_ID)) //  --
// AVP Prague stamp end



// AVP Prague stamp begin( Interface defined messages,  )

// message class
#define pmc_TEMPFILE 0xe64494e4 // (3863254244) --

	#define pm_TEMPFILE_GETPATH 0x00000001 // (1) --
	// context comment
	//    hSTRING, Receiver can fill it with TempPath with terminating

	#define pm_TEMPFILE_GETNAME 0x00000002 // (2) --
	// context comment
	//    hSTRING, contains TempPath with terminating
// AVP Prague stamp end



// AVP Prague stamp begin( Interface comment,  )
// IO interface implementation
// Short comments -- input/output interface
// AVP Prague stamp end



// AVP Prague stamp begin( Registration call prototype,  )
	tERROR pr_call IO_Register( hROOT root );
// AVP Prague stamp end



// AVP Prague stamp begin( Data structure,  )
// Interface IO. Inner data structure

typedef struct tag_sLocals 
{
	hIO      real_io;                   // Handle to NativeIO if created
	tDWORD   m_dwfAccessMode;           // --
	tDWORD   m_dwfOpenMode;             // --
	tQWORD   FileSize;                  // --
	tCHAR    m_szFileName[cMAX_PATH];   // ��� ���������� �����, ���� ������� ��� ������
	tCHAR    m_szPath[cMAX_PATH];       // ���� � ���������� �����, ���� ������� ��� ������
	tORIG_ID m_ObjectOrigin;            // --
	tBYTE    byFillChar;                // --
	tBOOL    bDeleteOnClose;            // --
	hOBJECT  hBasedOn;                  // --
	hSTRING  hStr;                      // --
	tCHAR    m_szObjectName[cMAX_PATH]; // ��� ������� (����� �� ��������� � ������ �����)
	tCHAR    m_szObjectPath[cMAX_PATH]; // ���� � ������� (����� �� ��������� � ����� � �����)
	tERROR   WriteBackError;            // --
	tQWORD   m_qwCurPos;                // IO current position
	tQWORD   SwapSize;                  // --
} sLocals;


// to get pointer to the structure sLocals from the hOBJECT obj
#define CUST_TO_sLocals(object)  ((sLocals*)( (((tPTR*)object)[2]) ))
// AVP Prague stamp end



// AVP Prague stamp begin( Object declaration,  )
// AVP Prague stamp end



// AVP Prague stamp begin( Property table,  )
// AVP Prague stamp end



// AVP Prague stamp begin( Header endif,  )
#endif // io_h
// AVP Prague stamp end



