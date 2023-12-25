#ifndef _PLUG_API_H
#define _PLUG_API_H

#include "kldef.h"
#include "baseapi.h"

#pragma warning( disable : 4200 )

typedef struct _PLUGIN_INIT_INFO PLUGIN_INIT_INFO,  *PPLUGIN_INIT_INFO;
typedef struct _BASEDRV_INFO     BASEDRV_INFO,      *PBASEDRV_INFO;

// ����� ������ ���������� ��������
#define PRIORITY_MINIMUM    (UCHAR)0

#define PRIORITY_LOW        (UCHAR)0x40
#define PRIORITY_NORMAL     (UCHAR)0x80
#define PRIORITY_HIGH       (UCHAR)0xC0

#define PRIORITY_MAXIMUM    (UCHAR)0xFF

typedef enum _KL_PLUGIN_TYPE
{
    KlPluginCommon,
    KlPluginIds,
    KlPluginTdi
} KL_PLUGIN_TYPE;

#define PLUGIN_EVENT(_type_, _class_, _event_) ( ULONG ) ( ( (_type_) << 24 ) | ( (_class_) << 16 ) | ( ( _event_ ) & 0x00FFFFFF ) )

typedef
KLSTATUS
(KL_CALLBACK *biDebugHandler)       ( char* message, ...);

typedef
KLSTATUS
(KL_CALLBACK *biIoctlHandler)       ( ULONG nIoctl, PVOID pInBuffer, ULONG InBufferSize, PVOID pOutBuffer, ULONG OutBufferSize, ULONG* nReturned);

typedef
KLSTATUS
(KL_CALLBACK *biEventHandler)       ( unsigned long dwEventID, unsigned long dwDataSize, void*    pData);

typedef
PVOID
(KL_CALLBACK *biAllocHander)        ( unsigned long dwSize );

typedef
void
(KL_CALLBACK *biFreeHandler)        ( void* Memory);

typedef struct _BASEDRV_INFO {
    ULONG             BaseDrvID;          // ID �������� ��������.
    biIoctlHandler    IOCTL_Handler;      // ���������� 
    biDebugHandler    DbgOut;             // ���������� ���������� ������
    biEventHandler    BaseEventHandler;   // ���������� ����������� ������� ��������
    biAllocHander     MemAlloc;           // ��������� ������ � ������� �������� ��������
    biFreeHandler     MemFree;            // ������������ ������

    KL_EVENT          DeinitEvent;        // ����� event �������, �� ������� ������� ������ �� ������ ������� ������� � �������

    void*       	  IsNeedFilterEvent;  // Sobko's Notificators
    void*   	      FilterEvent;        // 

    PVOID             pExportTable;       // ������� �������, ������� �������������� ������� ���������
} BASEDRV_INFO, *PBASEDRV_INFO;

typedef
KLSTATUS
(KL_CALLBACK *piIoctlHandler)       ( void* plContext, ULONG nIoctl, PVOID pInBuffer, ULONG InBufferSize, PVOID pOutBuffer, ULONG OutBufferSize, ULONG* nReturned);

typedef
KLSTATUS
(KL_CALLBACK *EventProcessHandler)( void* plContext, unsigned long dwDataSize, void*    pData);

typedef
KLSTATUS
(KL_CALLBACK *NewPluginHandler)   ( void* plContext, void*    plNewContext);

typedef
KLSTATUS
(KL_CALLBACK *PluginInitEntry)    ( PPLUGIN_INIT_INFO    pInfo, PBASEDRV_INFO pBaseDrv, void*   Context );

typedef struct _PLUGIN_CALLBACK {
    ULONG   EventType;      // ��� �������
    PVOID   pCallback;      // ��� callback
    ULONG   Priority;       // ��������� callback-�
} PLUGIN_CALLBACK, *PPLUGIN_CALLBACK;

// ������������ �������
enum CB_TYPE 
{   
    CB_PACKET_RECEIVE = 1,          // ����� ������
    CB_PACKET_SEND,                 // �������� ������
    CB_PACKET_RECEIVE_ON_PASSIVE,   // ����� ������ �� PASSIVE_LEVEL
    CB_PACKET_SEND_ON_PASSIVE,      // �������� ������ �� PASSIVE_LEVEL
    CB_REGISTER_PLUGIN,             // ����������� � ������� ������ �������
    CB_REVEAL_PLUGIN,

    CB_OPEN_ADDR,    
    CB_CLOSE_ADDR,

    CB_OPEN_CONN,
    CB_CLOSE_CONN,

    CB_SET_EVENT,

    CB_CONNECT,
    CB_POST_CONNECT,
    CB_POST_CONNECT_PASSIVE,
    CB_DISCONNECT,
    CB_EVENT_DISCONNECT,

    CB_ACCEPT,
    CB_LISTEN,    
    
    CB_SEND_DG,
    CB_DELAYED_SEND_DG,
    CB_RECEIVE_DG,
    CB_DELAYED_RECEIVE_DG,
    CB_SEND,
    CB_RECEIVE,
    
    CB_PRE_CONNECT_PASSIVE,
    
    CB_KLICK_LOW_RESOURCES,

    CB_ON_SEND_PACKET,
    CB_ON_RECEIVE_PACKET,    
    CB_ON_DROP_SEND_PACKET,
    CB_ON_DROP_RECEIVE_PACKET,

    CB_ON_DROP_CONNECTION,
    CB_SET_ETH_FILTER
};

// ���������� � �������
typedef struct _PLUGIN_INIT_INFO {
    int                 PluginID;           // ID �������.  ����������� Base-���������.
    KL_PLUGIN_TYPE      PluginType;         // ��� �������. ����������� ��������.
    char*               PluginDescription[PLUGIN_DESCRIPTION_SIZE]; // ����������� ��������
    
    piIoctlHandler      IOCTL_Handler;      // ������� ������� ��� ������ ��������� IOCTL
    PluginInitEntry     m_pInitEntry;       // ����� ����� �������.    

    ULONG               CallbackCount;      // ��� ���������� � �����������
    PLUGIN_CALLBACK     *plCallback;        // ��������

    ULONG*              pResourceCount;     // ��������� �� ���������� �������� �������, 
                                            // ������� ������������ ������� ���������.
                                            // ������������� �������� ��������
    ULONG*              pPaused;
} PLUGIN_INIT_INFO, *PPLUGIN_INIT_INFO;

//  ---------------------------------------------------------
//  ---------    ������� API ��� ������ plugin-a - ----------
//  ---------------------------------------------------------
#define PLUG_FILE_DEVICE_SECTION    0x00008005

#define PLUG_IOCTL_INDEX            0x841

// �������� ������ API !! �������� !! ( ���������� ������ )
// outBuffer = DWORD*
#define PLUG_GET_MOD_VERSION	CTL_CODE(BASE_FILE_DEVICE_SECTION,				\
								BASE_IOCTL_INDEX,								\
								METHOD_BUFFERED,								\
								FILE_ANY_ACCESS)
// �������� ������ ������� 
// InBuffer  = PLUGIN_MESSAGE*
// OutBuffer = DWORD*
#define PLUG_GET_VERSION		CTL_CODE(BASE_FILE_DEVICE_SECTION,				\
								BASE_IOCTL_INDEX + 1,							\
								METHOD_BUFFERED,								\
								FILE_ANY_ACCESS)
// �������� ��������� �������
// InBuffer = PLUGIN_MESSAGE*
// ������������� ����������� �������, �� �����.
#define PLUG_IOCTL   		    CTL_CODE(BASE_FILE_DEVICE_SECTION,				\
								BASE_IOCTL_INDEX + 2,							\
								METHOD_BUFFERED,								\
								FILE_ANY_ACCESS)

// ������������� ������� ������.
// InBuffer = PLUGIN_MESSAGE*
#define PLUG_INITIALIZE		    CTL_CODE(BASE_FILE_DEVICE_SECTION,				\
								BASE_IOCTL_INDEX + 3,							\
								METHOD_BUFFERED,								\
								FILE_ANY_ACCESS)

// ����������� �������� � ������� ��������
// InBuffer = PLUGIN_MESSAGE* + char[PLUGIN_DESCRIPTION_SIZE]
#define PLUG_REGISTER	        CTL_CODE(BASE_FILE_DEVICE_SECTION,				\
								BASE_IOCTL_INDEX + 4,							\
								METHOD_BUFFERED,								\
								FILE_ANY_ACCESS)

// ������������� �������� 
// InBuffer = PLUGIN_MESSAGE*
#define PLUG_DEREGISTER	        CTL_CODE(BASE_FILE_DEVICE_SECTION,				\
								BASE_IOCTL_INDEX + 5,	    					\
								METHOD_BUFFERED,								\
								FILE_ANY_ACCESS)

// ��� ������� � ��������� ������ �����������������
#define PLUG_MOD_PAUSE	        CTL_CODE(BASE_FILE_DEVICE_SECTION,				\
								BASE_IOCTL_INDEX + 6,	    					\
								METHOD_BUFFERED,								\
								FILE_ANY_ACCESS)

// ��� ������� � ��������� ������ �������������� ����� 
#define PLUG_MOD_RESUME	        CTL_CODE(BASE_FILE_DEVICE_SECTION,				\
								BASE_IOCTL_INDEX + 7,	    					\
								METHOD_BUFFERED,								\
								FILE_ANY_ACCESS)


// in = TimeOut ( ULONG, seconds ) out = TRUE
#define MSG_PLUG_SET_WD_TIMEOUT 0x1

// InBuffer = PLUGIN_MESSAGE*
#define PLUG_COMMON_IOCTL       CTL_CODE(BASE_FILE_DEVICE_SECTION,				\
								BASE_IOCTL_INDEX + 8,	    					\
								METHOD_BUFFERED,								\
								FILE_ANY_ACCESS)

// InBuffer = PLUGIN_MESSAGE*, OutBuffer = KLSTATUS + OLD OutBuffer
#define PLUG_IOCTL2				CTL_CODE(BASE_FILE_DEVICE_SECTION,				\
								BASE_IOCTL_INDEX + 9,	    					\
								METHOD_BUFFERED,								\
								FILE_ANY_ACCESS)

#endif // _PLUG_API_H