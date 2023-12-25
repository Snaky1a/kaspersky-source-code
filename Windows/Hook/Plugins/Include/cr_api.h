#ifndef _CR_API_H_
#define _CR_API_H_

#include "../../klsdk/kl_ipaddr.h"

#pragma warning (disable : 4200)

/*  
 *	    Connection redirector plugin API 
 *  
 *      �����       : ����� �.�.
 *      Updated     : 16/02/2005
 *
 *      
 *
 *      ������ ��������������� ���������� ������������� ����� ������������� "������ �������" ( �������� ���������� ),
 *      ���� ������������ ��������� ���������� � ������������ ������.
 *
 *      ���� ������ ������ "�����" �������� � ������������ ������ � ������������ ������, �� ���������� ������������������
 *      � �������� ����������� � ������� ������� PLUGIN_MESSAGE � �������� MSG_CR_INITIALIZE. � ����� ������ ��������
 *      ����� ��������, � � ������� �������� � ���� �������. ������ ����� ������� ������ ��� ������ ������ � �� ����� ����
 *      ����������� ��� ������ ������, ��� �� ��� �� ����������. ��� ���� ����� ����� ������������ �� ������ �������.
 *
 *      ��� ���������� ��������� ������ �� ������������� ����� ���������� ������� PLUGIN_MESSAGE � �������� 
 *      MSG_CR_ADD_PORT. ���� ���� ��� ������������ ��� ���������, �� �������� ������.
 *      ��� ���������� ����� �� ��������� ���������� ������� PLUGIN_MESSAGE � �������� MSG_CR_REMOVE_PORT
 *
 *      ��� ���������� ������, ������ ������ ������ ������� PLUGIN_MESSAGE � �������� MSG_CR_DONE, ��� ����, ����
 *      ����������� �������� ���� ������, ������� ����������� ������ ������.
 * 
 *      ����� ���������� ��������������� �� ������ ������, ������� ������ ������ ������ �������� � 500 ���� � ���� :
 *      sprintf( HelloBuffer, "KAVSEND <%s> <%d> <%d> <%d>\r\n\0", Ip, htons ( rPort ), PID, htons ( rMaskedPort ) );
 *
 *      �������� ����� ����������� � ������ �������� �������-����������� ��� � ������ 
 *      �������� ������� � ����� PAUSE.
 */

#define REDIRECTOR_PLUGIN_NAME        "Connection redirector Plugin"

// ID ���������, ���������� � ������

#pragma pack(1)

typedef struct _CrInitInfo {
    unsigned short  m_ListenPort;   // �������������� ����    
    unsigned long   m_ProxyPID;     // PID ������
} CrInitInfo;

typedef struct _CrInitInfo2 {
    unsigned short  m_ListenPort;   // �������������� ����    
    unsigned short  m_ServPort;     // ��������������� ����.
    unsigned long   m_ProxyPID;     // PID ������
} CrInitInfo2;

typedef struct _CrAskConnection {    
    unsigned long   m_Ver;          // ��� ���������
    unsigned long   m_Size;         // ������ ���������

    _ip_addr_t      m_rIp;
    unsigned short  m_rPort;
    unsigned long   m_PID;
    __int64         m_ID;           // ID ����������. ����������� ���������.
} CrAskConnection ;

typedef struct _CrReplyConnection {
    KLSTATUS        m_Status;       // ������ ���������� � ��������.
    __int64         m_ID;           // ID ����������.
} CrReplyConnection;

typedef struct _CrInitInfoRet {
    unsigned long   m_Status;       // 0 � ������ ������.
    unsigned long   m_Handle;       // �����, �������������� � ������ ������. ��� DWORD ���� �� 64-������ ������.
} CrInitInfoRet;

typedef struct _CrPortInfo {
    unsigned long  m_Handle;        // ����� ������
    unsigned short m_PortValue;     // �������� ����� ��� ���������������
} CrPortInfo;

typedef struct _CrPortListInfo {
    unsigned long   m_TotalPortCount;
    unsigned long   m_PortCount;
    unsigned short  m_Port[0];
} CrPortListInfo;

typedef struct _CrExcludeInfo {    
    unsigned long   m_Host;
    unsigned short  m_Port;    
    unsigned char   m_Hash[16];
} CrExcludeInfo;

typedef struct _CrExcludeInfo2 {    
    ip_addr_t       m_Host;
    unsigned short  m_Port;    
    unsigned char   m_Hash[16];
} CrExcludeInfo2;


#define CR_ANY_APP  L"*"

// InBuffer = PPLUGIN_MESSAGE(CrInitInfo); OutBuffer = CrInitInfoRet
#define MSG_CR_INITIALIZE       0x1

// *InBuffer = PPLUGIN_MESSAGE(m_Handle)
#define MSG_CR_DONE             0x2

// InBuffer = PPLUGIN_MESSAGE(CrPortInfo);
#define MSG_CR_ADD_PORT         0x3

// InBuffer = PPLUGIN_MESSAGE(CrPortInfo);
#define MSG_CR_REMOVE_PORT      0x4

// *InBuffer = PPLUGIN_MESSAGE(m_Handle); OutBuffer = CrPortListInfo
#define MSG_CR_GET_PORTS        0x5

// *InBuffer = PPLUGIN_MESSAGE(CrExcludeInfo); *OutBuffer = Handle (ULONG)
#define MSG_ADD_EXCLUDE         0x6

// *inBuffer = ExcludeHandle
#define MSG_REMOVE_EXCLUDE      0x7

typedef struct _CrAssociateStruct {
    ULONG   lIp1;
    ULONG   rIp1;
    USHORT  lPort1;
    USHORT  rPort1; 

    ULONG   lIp2;
    ULONG   rIp2;
    USHORT  lPort2;
    USHORT  rPort2; 
} CrAssociateStruct;

// *InBuffer = CrAssociateStruct
#define MSG_CR_ASSOCIATE_CONN      0x8

// *InBuffer = PPLUGIN_MESSAGE(CrExcludeInfo2); *OutBuffer = Handle (ULONG)
#define MSG_ADD_EXCLUDE2         0x9

typedef struct _CrAssociateStruct2 {
    ip_addr_t   lIp1;
    ip_addr_t   rIp1;
    USHORT  lPort1;
    USHORT  rPort1; 

    ip_addr_t   lIp2;
    ip_addr_t   rIp2;
    USHORT  lPort2;
    USHORT  rPort2; 
} CrAssociateStruct2;

// *InBuffer = CrAssociateStruct
#define MSG_CR_ASSOCIATE_CONN2      0xA

// InBuffer = PPLUGIN_MESSAGE(CrInitInfo2); OutBuffer = CrInitInfoRet
#define MSG_CR_INITIALIZE2          0xB

// �������� ���-�� ����������, ������� � ������ � �� ����������� �������
// OutBuffer = ULONG
#define MSG_CR_GET_CONNCOUNT        0xC

// OutBuffer = DWORD
#define MSG_CR_FLAGS               0xD

    #define CR_FLAG_INITIALIZED         0x1     // ������ �������������
    #define CR_FLAG_CLOSING             0x2     // �������� ����������
    #define CR_FLAG_CLOSING_DONE        0x4     // ����� �����������
    #define CR_HAS_CONNECTIONS          0x8     // ���� ������� ����������
    #define CR_QUIT_SET                 0x10    // QuitEvent - ��������������

// ���� ������� ��������, ��� �� �������. ( SetEvent ( QuitEvent ) )
#define MSG_PREPARE_EXIT               0xE

// �������� ��� ������, ������� ���������� �� ������� �������,
// ������� ����� �����������
// InBuffer = PPLUGIN_MESSAGE( DWORD )
#define MSG_ASSIGN_EVENT              0xF

// �������� ��������� �������� � �����������, ���� ���������� ��������������
// InBuffer = PPLUGIN_MESSAGE()
// OutBuffer = CrAskConnection
#define MSG_GET_CONTEXT               0x10

// ����� ���������� ���������� ��������� ������� ( ����������/�����������/�� ����������� )
// InBuffer = PPLUGIN_MESSAGE ( CrReplyConnection )
#define MSG_SET_CONTEXT_VERDICT       0x11

#pragma pack()

#endif