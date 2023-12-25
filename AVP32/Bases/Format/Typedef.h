////////////////////////////////////////////////////////////////////
//
//  TYPEDEF.H
//  definition of common types for different plathforms
//  AVP 3.0 Engine
//  Alexey de Mont de Rique [graf@avp.ru], Kaspersky Labs. 1996
//  Copyright (c) Kaspersky Labs.
//
////////////////////////////////////////////////////////////////////

#ifndef __TYPEDEF_H
#define __TYPEDEF_H

#define FALSE 0
#define TRUE 1

        //typedef int                 BOOL;
        //typedef char CHAR;
#define BYTE unsigned char
        //typedef int                 INT;
        //typedef long LONG;
        //typedef LONG LPARAM;
        //#define FAR                 far
        //#define NEAR                near
typedef LONG *PLONG;
typedef LONG LRESULT;
typedef unsigned long ULONG;
typedef unsigned short USHORT;
typedef unsigned char UCHAR;
#define VOID void

#define pascal __stdcall
//#define pascal

//#define CALLBACK    __stdcall
#define WINAPI      __stdcall           //????????
//#define WINAPIV     __cdecl
//#define APIENTRY    WINAPI
//#define APIPRIVATE  __stdcall
//#define PASCAL      __stdcall

//#define CALLBACK
//#define WINAPI
//#define WINAPIV
//#define APIENTRY    WINAPI
//#define APIPRIVATE
//#define PASCAL      pascal

#define CONST               const

typedef unsigned long       DWORD;
typedef unsigned short      WORD;
        //typedef BYTE far            *LPBYTE;
typedef WORD far            *LPWORD;
typedef DWORD far           *LPDWORD;
typedef void far            *LPVOID;
typedef CONST void far      *LPCVOID;

typedef unsigned int        UINT;
typedef UINT WPARAM;

typedef struct  _SYSTEMTIME
    {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
    }   SYSTEMTIME;

typedef void *HANDLE;
//typedef PVOID HANDLE;

#define __RPC_FAR

        //typedef char CHAR;
typedef /* [string] */ const CHAR __RPC_FAR *LPCSTR;
typedef LPCSTR LPCTSTR;
typedef CHAR *LPSTR;
typedef LPSTR LPTSTR;

//typedef unsigned short wchar_t;
//typedef wchar_t WCHAR;
//typedef /* [string] */ const WCHAR __RPC_FAR *LPCWSTR;
//typedef LPCWSTR LPCTSTR;
//typedef WCHAR *LPSTR;
//typedef LPWSTR LPTSTR;

typedef struct _OVERLAPPED
 {
    DWORD Internal;
    DWORD InternalHigh;
    DWORD Offset;
    DWORD OffsetHigh;
    HANDLE  hEvent;
 } OVERLAPPED;

#ifndef _SECURITY_ATTRIBUTES_
#define _SECURITY_ATTRIBUTES_
typedef struct _SECURITY_ATTRIBUTES
 {
    DWORD  hLength;
    LPWORD lpSecurityAttributes;
    BOOL   hInheritHandle;
 } SECURITY_ATTRIBUTES;
#endif

#define INVALID_HANDLE_VALUE (HANDLE)-1
#define INVALID_FILE_SIZE (DWORD)0xFFFFFFFF

        //#define FILE_BEGIN           0
        //#define FILE_CURRENT         1
        //#define FILE_END             2

#define GENERIC_READ                     (0x80000000L)
#define GENERIC_WRITE                    (0x40000000L)
#define GENERIC_EXECUTE                  (0x20000000L)
#define GENERIC_ALL                      (0x10000000L)

#define FILE_SHARE_READ                 0x00000001
#define FILE_SHARE_WRITE                0x00000002
#define FILE_SHARE_DELETE               0x00000004
#define FILE_ATTRIBUTE_READONLY         0x00000001
#define FILE_ATTRIBUTE_HIDDEN           0x00000002
#define FILE_ATTRIBUTE_SYSTEM           0x00000004
#define FILE_ATTRIBUTE_DIRECTORY        0x00000010
#define FILE_ATTRIBUTE_ARCHIVE          0x00000020
#define FILE_ATTRIBUTE_NORMAL           0x00000080
#define FILE_ATTRIBUTE_TEMPORARY        0x00000100
#define FILE_ATTRIBUTE_COMPRESSED       0x00000800
#define FILE_ATTRIBUTE_OFFLINE          0x00001000
#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001
#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002
#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004
#define FILE_NOTIFY_CHANGE_SIZE         0x00000008
#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010
#define FILE_NOTIFY_CHANGE_LAST_ACCESS  0x00000020
#define FILE_NOTIFY_CHANGE_CREATION     0x00000040
#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100
#define FILE_ACTION_ADDED               0x00000001
#define FILE_ACTION_REMOVED             0x00000002
#define FILE_ACTION_MODIFIED            0x00000003
#define FILE_ACTION_RENAMED_OLD_NAME    0x00000004
#define FILE_ACTION_RENAMED_NEW_NAME    0x00000005
#define MAILSLOT_NO_MESSAGE             ((DWORD)-1)
#define MAILSLOT_WAIT_FOREVER           ((DWORD)-1)
#define FILE_CASE_SENSITIVE_SEARCH      0x00000001
#define FILE_CASE_PRESERVED_NAMES       0x00000002
#define FILE_UNICODE_ON_DISK            0x00000004
#define FILE_PERSISTENT_ACLS            0x00000008
#define FILE_FILE_COMPRESSION           0x00000010
#define FILE_VOLUME_IS_COMPRESSED       0x00008000

#define CREATE_NEW          1
#define CREATE_ALWAYS       2
#define OPEN_EXISTING       3
#define OPEN_ALWAYS         4
#define TRUNCATE_EXISTING   5

//
// dwPlatformId defines:
//

#define VER_PLATFORM_WIN32s             0
#define VER_PLATFORM_WIN32_WINDOWS      1
#define VER_PLATFORM_WIN32_NT           2

#endif
