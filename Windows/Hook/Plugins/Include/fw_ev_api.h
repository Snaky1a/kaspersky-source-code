// Firewall plugin API
#ifndef FIREWALL_PLUGIN_API
#define FIREWALL_PLUGIN_API

#include "../../klsdk/kl_ipaddr.h"

#define FIREWALL_PLUGIN_NAME        "Firewall Plugin"
#define NDIS_FIREWALL_PLUGIN_NAME   "NDIS Firewall Plugin"

// ID ������� (m_FunctionMj ��� FILTER_TRANSMIT)

// m_FltCtl == FLTTYPE_KLIN
#define FW_EVENT_CONNECT		0x1
#define FW_EVENT_DISCONNECT		0x2
#define FW_EVENT_RECEIVE		0x3
#define FW_EVENT_SEND			0x4
#define FW_EVENT_OPEN_PORT		0x5
#define FW_EVENT_CLOSE_PORT		0x6
#define FW_EVENT_LISTEN			0x7
#define	FW_EVENT_UDP_SEND		0x8
#define FW_EVENT_UDP_RECEIVE	0x9

// m_FltCtl == FLTTYPE_KLICK
#define FW_NDIS_PACKET_IN       0xa
#define FW_NDIS_PACKET_OUT      0xb

// ID ������������ ����������
#define FW_ID_FULL_APP_PATH		0x04000001

#define FW_ID_REMOTE_IP			0x04000002
#define FW_ID_REMOTE_PORT		0x04000003
#define FW_ID_LOCAL_PORT		0x04000004

#define FW_CONNECT_OUTGOING		0
#define FW_CONNECT_INCOMING		1
#define FW_ID_INITIATOR			0x04000005

#define FW_ID_LOCAL_IP			0x04000006

#define FW_ID_FILE_CHECKSUM		0x04000007

#define FW_ID_IMAGE_NAME	   	0x04000008


#define FW_ID_PROTOCOL          0x04000009

#define FW_ID_ICMP_TYPE         0x0400000a

//#define FW_MJ_PACKET_OUT		0x1
//#define FW_MJ_PACKET_IN			0x2

// __int64 time
#define FW_ID_EVENT_TIME        0x0400000b

#define FW_ID_ICMP_CODE         0x0400000c


#define FW_STREAM_UNDEFINED     0x0
#define FW_STREAM_IN            0x1
#define FW_STREAM_OUT           0x2
// ULONG
#define FW_ID_STREAM_DIRECTION  0x0400000d


/*
    FW_ID_TIME_SECOND - ������� ������� ( 0..59 )
    FW_ID_TIME_MINUTE - ������� ������  ( 0..59 )
    FW_ID_TIME_HOUR   - ������� ���     ( 0..23 )
    FW_ID_TIME_DAY    - ���� ������     ( 1..31 )
    FW_ID_TIME_WEEK_DAY - ���� ������   ( 0..6  ) (Sunday .. Saturday)

    FW_ID_TIME_MONTH  -  ������� �����  ( 1=������ .. 12=������� )
    FW_ID_TIME_YEAR   - ��� �� �.�.     ( 0..65535.   P.S. ������ 2005 ... )
    FW_ID_TIME_DAY_SECOND - ����� �������� ���, ������� � 00.00 ( 0 .. 86399 )
*/
#define FW_ID_TIME_SECOND       0x0400000e  // uchar
#define FW_ID_TIME_MINUTE       0x0400000f  // uchar
#define FW_ID_TIME_HOUR         0x04000010  // uchar
#define FW_ID_TIME_DAY          0x04000011  // uchar
#define FW_ID_TIME_WEEK_DAY     0x04000012  // uchar
#define FW_ID_TIME_MONTH        0x04000013  // uchar
#define FW_ID_TIME_YEAR         0x04000014  // ushort
#define FW_ID_TIME_DAY_SECOND   0x04000015  // ulong


#define FW_ID_COMMAND_LINE      0x04000016  // binary


// ����������� ����� ���������, �������������� � 1 �������� 
// ��� ������� �� ����� ����������.
// ���������� ��� ������������� � 0 -> ����� ����������� � ������ ����.
#define FW_ID_NO_LOG_PLEASE     0x04000017  // uchar

#define FW_ID_LOCAL_IPV6        0x04000018  // USHORT[8]
#define FW_ID_REMOTE_IPV6       0x04000019  // USHORT[8]

#define FW_ID_LOCAL_IPV6_ZONE   0x0400001A  // ULONG
#define FW_ID_REMOTE_IPV6_ZONE   0x0400001B  // ULONG

#define FW_ID_ETH_FRAME_TYPE    0x0400001C  // USHORT


#define FW_PROCNAMELEN              16
#define FW_USERAPPNAMELEN	        1100
#define FW_COMMANDLINELEN           1100
#define FW_HASH_SIZE	            16

// ID ���������, ���������� � ������
#pragma pack( push, 1 )
typedef struct _FW_PORT_LIST_ITEM {    
    unsigned long	Protocol;                       // TCP, UDP, IP .... ??
    unsigned long	LocalIp;
    unsigned short	LocalPort;	
    unsigned long	PID;                            // PID ��������    
    wchar_t	        UserAppName[FW_USERAPPNAMELEN]; // ����������� ������
} FW_PORT_LIST_ITEM, *PFW_PORT_LIST_ITEM;
#define MSG_GET_PORT_LIST   0x1


typedef struct _FW_CONN_LIST_ITEM {    
    unsigned long	Protocol;                       // TCP, UDP, IP ....
    unsigned long	LocalIp;
    unsigned short	LocalPort;	
    unsigned long	RemoteIp;
	unsigned short	RemotePort;	
    unsigned long	PID;                            // PID ��������    
    unsigned char	isIncoming;	
    wchar_t	        UserAppName[FW_USERAPPNAMELEN]; // ����������� ������    
} FW_CONN_LIST_ITEM, *PFW_CONN_LIST_ITEM;
#define MSG_GET_CONN_LIST   0x2


typedef struct _FW_BREAK_CONN_ITEM	{
	unsigned char	Protocol;
	unsigned long	LocalIp;
	unsigned short	LocalPort;
	unsigned long	RemoteIp;
	unsigned short	RemotePort;	
} FW_BREAK_CONN_ITEM, *PFW_BREAK_CONN_ITEM;

// inBuffer = FW_BREAK_CONN_ITEM
#define MSG_BREAK_CONN      0x3



// ID ���������, ���������� � ������
typedef struct _FW_PORT_LIST_ITEM2 {    
    unsigned long	Protocol;                       // TCP, UDP, IP .... ??
    unsigned long	LocalIp;
    unsigned short	LocalPort;	
    unsigned long	PID;                            // PID ��������        
    unsigned long   ActiveTime;                     // ����� ���������� ����� ( � �������� )
    __int64         inBytes;                        // ���������� ���������� ����
    __int64         outBytes;                       // ���������� ������������ ����
    wchar_t	        UserAppName[FW_USERAPPNAMELEN]; // ����������� ������
} FW_PORT_LIST_ITEM2, *PFW_PORT_LIST_ITEM2;
#define MSG_GET_PORT_LIST2   0x4


typedef struct _FW_CONN_LIST_ITEM2 {    
    unsigned long	Protocol;                       // TCP, UDP, IP ....
    unsigned long	LocalIp;
    unsigned short	LocalPort;	
    unsigned long	RemoteIp;
	unsigned short	RemotePort;	
    unsigned long	PID;                            // PID ��������    
    unsigned char	isIncoming;	
    unsigned long   ActiveTime;                     // ����� ���������� ���������� ( � �������� )
    __int64         inBytes;                        // ���������� ���������� ����
    __int64         outBytes;                       // ���������� ������������ ����
    wchar_t	        UserAppName[FW_USERAPPNAMELEN]; // ����������� ������    
} FW_CONN_LIST_ITEM2, *PFW_CONN_LIST_ITEM2;
#define MSG_GET_CONN_LIST2   0x5

// inBuffer = HostStatTable
#define MSG_GET_HOST_STAT    0x6

typedef struct _FW_PORT_LIST_ITEM3 {    
    unsigned long	Protocol;                       // TCP, UDP, IP .... ??
    unsigned long	LocalIp;
    unsigned short	LocalPort;	
    unsigned long	PID;                            // PID ��������        
    unsigned long   ActiveTime;                     // ����� ���������� ����� ( � �������� )
    __int64         inBytes;                        // ���������� ���������� ����
    __int64         outBytes;                       // ���������� ������������ ����
    wchar_t	        UserAppName[FW_USERAPPNAMELEN]; // ����������� ������
    wchar_t	        CommandLine[FW_COMMANDLINELEN]; // command line
} FW_PORT_LIST_ITEM3, *PFW_PORT_LIST_ITEM3;
#define MSG_GET_PORT_LIST3   0x7


typedef struct _FW_CONN_LIST_ITEM3 {    
    unsigned long	Protocol;                       // TCP, UDP, IP ....
    unsigned long	LocalIp;
    unsigned short	LocalPort;	
    unsigned long	RemoteIp;
	unsigned short	RemotePort;	
    unsigned long	PID;                            // PID ��������    
    unsigned char	isIncoming;	
    unsigned long   ActiveTime;                     // ����� ���������� ���������� ( � �������� )
    __int64         inBytes;                        // ���������� ���������� ����
    __int64         outBytes;                       // ���������� ������������ ����
    wchar_t	        UserAppName[FW_USERAPPNAMELEN]; // ����������� ������    
    wchar_t	        CommandLine[FW_COMMANDLINELEN]; // command line
} FW_CONN_LIST_ITEM3, *PFW_CONN_LIST_ITEM3;
#define MSG_GET_CONN_LIST3   0x8


// InBuffer = DWORD
#define MSG_FIX_PID		0x9


// InBuffer = DWORD   ( 1, 0 )
#define MSG_CHECK_TDI_AT_NDIS_LEVEL 0xA

typedef struct _FW_PORT_LIST_ITEM4 {
    unsigned long	Protocol;                       // TCP, UDP, IP .... ??
    ip_addr_t       LocalIp;
    unsigned short	LocalPort;	
    unsigned long	PID;                            // PID ��������        
    unsigned long   ActiveTime;                     // ����� ���������� ����� ( � �������� )
    __int64         inBytes;                        // ���������� ���������� ����
    __int64         outBytes;                       // ���������� ������������ ����
    wchar_t	        UserAppName[FW_USERAPPNAMELEN]; // ����������� ������
    wchar_t	        CommandLine[FW_COMMANDLINELEN]; // command line
} FW_PORT_LIST_ITEM4, *PFW_PORT_LIST_ITEM4;
#define MSG_GET_PORT_LIST4   0xB


typedef struct _FW_CONN_LIST_ITEM4 {        
    unsigned long	Protocol;                       // TCP, UDP, IP ....

    ip_addr_t       LocalIp;
    ip_addr_t       RemoteIp;

    unsigned short	LocalPort;
    unsigned short	RemotePort;	
    unsigned long	PID;                            // PID ��������    
    unsigned char	isIncoming;	
    unsigned long   ActiveTime;                     // ����� ���������� ���������� ( � �������� )
    __int64         inBytes;                        // ���������� ���������� ����
    __int64         outBytes;                       // ���������� ������������ ����
    wchar_t	        UserAppName[FW_USERAPPNAMELEN]; // ����������� ������    
    wchar_t	        CommandLine[FW_COMMANDLINELEN]; // command line
} FW_CONN_LIST_ITEM4, *PFW_CONN_LIST_ITEM4;
#define MSG_GET_CONN_LIST4   0xC

typedef struct _FW_BREAK_CONN_ITEM2	{
    unsigned char	Protocol;
    ip_addr_t         LocalIp;
    unsigned short	LocalPort;
    ip_addr_t	        RemoteIp;
    unsigned short	RemotePort;	
} FW_BREAK_CONN_ITEM2, *PFW_BREAK_CONN_ITEM2;

// inBuffer = FW_BREAK_CONN_ITEM
#define MSG_BREAK_CONN2      0xD


#define MSG_GET_HOST_STAT2    0xE

#pragma pack( pop )

#endif // FIREWALL_PLUGIN_API