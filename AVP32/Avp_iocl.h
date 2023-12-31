#ifndef AVP_IOCL_H
#define AVP_IOCL_H

#define AVP_LLIO_DRIVER AVP_IO

#define IOCTL_AVPIO_GET_VERSION     CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
//OutBuf: DWORD Version; OutBufSize 4;
#define IOCTL_AVPIO_MEMORY_READ				CTL_CODE(FILE_DEVICE_UNKNOWN, 0x841, METHOD_BUFFERED, FILE_ANY_ACCESS)
//InBuf: DWORD offset; DWORD count;
#define IOCTL_AVPIO_MEMORY_WRITE			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x842, METHOD_BUFFERED, FILE_ANY_ACCESS)
//InBuf: DWORD offset; DWORD count; BYTE buf[]
#define IOCTL_AVPIO_MEMORY_GET_DOS_MEM_SIZE     CTL_CODE(FILE_DEVICE_UNKNOWN, 0x843, METHOD_BUFFERED, FILE_ANY_ACCESS)
//OutBuf: DWORD DosMemSize
#define IOCTL_AVPIO_MEMORY_GET_FIRST_MCB_SEG    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x844, METHOD_BUFFERED, FILE_ANY_ACCESS)
//OutBuf: DWORD FirstMcbSeg
#define IOCTL_AVPIO_MEMORY_GET_IFSAPI_HOOK_TABLE  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x845, METHOD_BUFFERED, FILE_ANY_ACCESS)
//OutBuf: DWORD IfsApiHookAddresses
#define IOCTL_AVPIO_MEMORY_GET_DOS_TRACE_TABLE  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x846, METHOD_BUFFERED, FILE_ANY_ACCESS)
//OutBuf: DWORD TraceAddresses
#define IOCTL_AVPIO_PHYSICAL_DISK_GET_PARAM   CTL_CODE(FILE_DEVICE_UNKNOWN, 0x850, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_AVPIO_PHYSICAL_DISK_READ      CTL_CODE(FILE_DEVICE_UNKNOWN, 0x851, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_AVPIO_PHYSICAL_DISK_WRITE      CTL_CODE(FILE_DEVICE_UNKNOWN, 0x852, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_AVPIO_LOGICAL_DRIVE_READ      CTL_CODE(FILE_DEVICE_UNKNOWN, 0x853, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_AVPIO_LOGICAL_DRIVE_WRITE     CTL_CODE(FILE_DEVICE_UNKNOWN, 0x854, METHOD_BUFFERED, FILE_ANY_ACCESS)

#pragma pack(push, pack_vxdio)
#pragma pack(1)

#pragma warning(disable:4200)

typedef struct FlatIoCb_{
        DWORD offset;
        DWORD size;
        BYTE  buffer[];
}FlatIoCb;

typedef struct DiskIoCb_{
        DWORD disk;
		DWORD sector;
        DWORD head;
        DWORD numSectors;
        DWORD sectorSize;
        BYTE  buffer[];
}DiskIoCb;

#pragma warning(default:4200)

#pragma pack(pop, pack_vxdio)


#endif
