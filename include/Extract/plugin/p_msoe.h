// AVP Prague stamp begin( Interface header,  )
// -------- ANSI C Code Generator 2.0 --------
// -------- Monday,  22 November 2004,  14:43 --------
// -------------------------------------------
// Copyright � Kaspersky Labs 1996-2004.
// -------------------------------------------
// Project     -- msoe
// Sub project -- msoe
// Purpose     -- ������ ��� ������ � Outlook Express
// Author      -- Mezhuev
// File Name   -- plugin_msoe.c
// Additional info
//    ������ ������ ������������ ��� ������ �� ���������� ��������� Outlook Express:
//    - �������� ������� (���������������� �� Identity, ���� �� ������, �� ������������ �������)
//    - ���� ��������� � ������� dbx.
//    - ��������� � ������� RFC822 (eml ����)
//    - ���� � ���������� ��������� (message part)
//
//    ���������� ������� ������� �� ������������ ������������� �������� �� ������!!!
// -------------------------------------------
// AVP Prague stamp end

// AVP Prague stamp begin( Header ifndef,  )
#if !defined( __public_plugin_msoe )
#define __public_plugin_msoe
// AVP Prague stamp end

// AVP Prague stamp begin( Header includes,  )
#include <Prague/prague.h>
#include <Prague/iface/i_objptr.h>
#include <Prague/iface/i_io.h>
#include <Prague/iface/i_os.h>
// AVP Prague stamp end

// AVP Prague stamp begin( Plugin identifier,  )
#define PID_MSOE  ((tPID)(49003))
// AVP Prague stamp end

// AVP Prague stamp begin( Vendor identifier,  )
#define VID_MEZHUEV  ((tVID)(79))
// AVP Prague stamp end

// AVP Prague stamp begin( Plugin public definitions, OS )
// OS interface implementation
// Short comments -- object system interface

// errors
#define warnNOTHING_TO_COMMIT                    PR_MAKE_IMP_WARN(PID_MSOE, 0x003) // 0x1bf6b003,469151747 (3) --
#define warnPARENT_NOT_COMMITED                  PR_MAKE_IMP_WARN(PID_MSOE, 0x004) // 0x1bf6b004,469151748 (4) --
#define warnPROPERTY_NOT_COMMITED                PR_MAKE_IMP_WARN(PID_MSOE, 0x005) // 0x1bf6b005,469151749 (5) --

// message class
//! #define pmc_OS_VOLUME 0x75eb704a // ��������� � �����
// AVP Prague stamp end

// AVP Prague stamp begin( Plugin public definitions, ObjPtr )
// ObjPtr interface implementation
// Short comments -- pointer to the object
// AVP Prague stamp end

// AVP Prague stamp begin( Plugin public definitions, IO )
// IO interface implementation
// Short comments -- input/output interface

// message class
//    �������� "send_point" � ����� �� ���� ��������� ����� ���� ������ �� ���� �����: OS, ObjPtr ��� IO
//! #define pmc_IO 0x52e986b3 // ����� ��������� ��������� � ������������� �������� OS, ObjPtr � IO
// AVP Prague stamp end

// AVP Prague stamp begin( Header endif,  )
#endif // __public_plugin_msoe
// AVP Prague stamp end

