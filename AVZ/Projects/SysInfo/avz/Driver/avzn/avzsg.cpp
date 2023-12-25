// ������� ��� ������������ ������� AVZ
// (�) ������ ����, 2005
#include "StdAfx.h"
#include <ntddk.h>
#include <ntdef.h>
#include <avzsg.h>
#include <ntddndis.h>
#include <pfhook.h>

// ���������� ��� ������������� � NT4, ������� �� ������������ *WithTag ...
#undef ExFreePool
#undef ExAllocatePool

// ��� ���������� (� ������� UnicodeString, ����������� ��������)
PRESET_UNICODE_STRING (usDeviceName,       CSTRING (\\Device\\AvzSGKernelDevice));
// ��� ���������� ����� (� ������� UnicodeString, ����������� ��������)
PRESET_UNICODE_STRING (usSymbolicLinkName, CSTRING (\\??\\AvzSGKernelDeviceLink));

// ���������� ���������� - ��������� �� ������� "����������" � "�������� ����������"
PDEVICE_OBJECT  gpDeviceObject  = NULL;
PDEVICE_CONTEXT gpDeviceContext = NULL;

DWORD TrustedPID1 = 0xFFFFFFFF; // �������� ���������� �������
// ������� ���������� ���������
#define MaxTrustedPIDCnt 20
DWORD TrustedPID[MaxTrustedPIDCnt];

// ��������� ��������� ProcessNotifyRoutine 
NTSTATUS ProcessNotifyRoutineRes = STATUS_UNSUCCESSFUL;
// �������� ��������� � EPROCESS
DWORD EPROCESS_ALPRel = 0, EPROCESS_NAMERel = 0, EPROCESS_PIDRel = 0;

DRIVER_OBJECT OldTCPDriverObject;
extern "C" {
	// ��������� �� SDT
	extern PSERVICE_DESCRIPTOR_TABLE    KeServiceDescriptorTable;
	// ����� ������ NT - ��� �������
	extern  PWORD						NtBuildNumber;
NTKERNELAPI
NTSTATUS
ObReferenceObjectByName (
    IN PUNICODE_STRING  ObjectName,
    IN ULONG            Attributes,
    IN PACCESS_STATE    PassedAccessState OPTIONAL,
    IN ACCESS_MASK      DesiredAccess OPTIONAL,
    IN POBJECT_TYPE     ObjectType,
    IN KPROCESSOR_MODE  AccessMode,
    IN OUT PVOID        ParseContext OPTIONAL,
    OUT PVOID           *Object
);
extern POBJECT_TYPE                 *IoDriverObjectType;
}


BOOL  TCPIPHooksInstalled = false;

  // ������ ��� ��������� ZwCreateFile
  int ZwCreateFileCode = -1;
  PZwCreateFile OldZwCreateFile = NULL;
  // ������ ��� ��������� ZwCreateKey
  int ZwCreateKeyCode = -1;
  PZwCreateKey OldZwCreateKey = NULL;
  // ������ ��� ��������� ZwOpenKey
  int ZwOpenKeyCode = -1;
  PZwOpenKey OldZwOpenKey = NULL;
  // ZwSetValueKey
  int ZwSetValueKeyCode = -1;
  PZwSetValueKey OldZwSetValueKey = NULL;
  // ZwDeleteValueKey
  int ZwDeleteValueKeyCode = -1;
  PZwDeleteValueKey OldZwDeleteValueKey = NULL;
  // �������� ��������
  int ZwOpenProcessCode = -1;
  PZwOpenProcess OldZwOpenProcess = NULL;
  // �������� ��������
  int ZwCreateProcessCode = -1;
  PZwCreateProcess OldZwCreateProcess = NULL;
  int ZwCreateProcessExCode = -1;
  PZwCreateProcessEx OldZwCreateProcessEx = NULL;
  // ZwOpenSection
  int ZwOpenSectionCode = -1;
  PZwOpenSection OldZwOpenSection = NULL;
  // ZwOpenFile
  int ZwOpenFileCode = -1;
  PZwOpenFile OldZwOpenFile = NULL;
  // ZwOpenThread
  int ZwOpenThreadCode = -1;
  PZwOpenThread OldZwOpenThread = NULL;
  // ZwWriteVirtualMemory
  int ZwWriteVirtualMemoryCode = -1;
  PZwWriteVirtualMemory OldZwWriteVirtualMemory = NULL;
  // ZwTerminateJobObject
  int ZwTerminateJobObjectCode = -1;
  PZwTerminateJobObject OldZwTerminateJobObject = NULL;

  int ZwCreateJobObjectCode = -1;
  PZwCreateJobObject OldZwCreateJobObject = NULL;

  // ������� ������ � ������������ ������ - � ��� ���� ���������� ��������� ������ � ������ ����� ��������� � ��������� ��
  BOOL RestricredMode = false;

  // ��������� �������� ����, �������� �� ������� ����������
  BOOL TrustedProcessByPID(DWORD APID) {
	  // ��� �������, ������������ ������� ?
	  if (APID == TrustedPID1)
		  return true;
	  else
		  // ��� ���� �� ���������� ���������
		  for (int i = 0; i < MaxTrustedPIDCnt; i++)
			  if (TrustedPID[i] != 0xFFFFFFFF && TrustedPID[i] == APID) 
				  return true;
	  return false;
  }

  // ��������, ��� ������� �������� ����������
  BOOL TrustedProcess() {
	  // ����������� PID �������� ��������
	  return TrustedProcessByPID((DWORD)PsGetCurrentProcessId());
  }

  // ������� ������� ���������� PID
  VOID ClearTrustedPIDTable() {
   for (int i = 0; i < MaxTrustedPIDCnt; i++) 
	   TrustedPID[i] = 0xFFFFFFFF;
  }

  // �������� PID �� ���� ����������
  VOID DeleteTrustedPID(DWORD APID) {
   for (int i = 0; i < MaxTrustedPIDCnt; i++) 
	   if (TrustedPID[i] == APID)
		   TrustedPID[i] = 0xFFFFFFFF;
  }

  // ���������� ����������� PID � ���� 
  NTSTATUS AddTrustedPID(DWORD APID) 
  {
   // ���� ����� PID ���� � ����, �� �� ��������� ���
   for (int i = 0; i < MaxTrustedPIDCnt; i++) 
	   if (TrustedPID[i] == APID) return STATUS_UNSUCCESSFUL;
   // ��������� 
   for (int i = 0; i < MaxTrustedPIDCnt; i++) 
	   if (TrustedPID[i] == 0xFFFFFFFF) {
		   TrustedPID[i] = APID;
		   return STATUS_SUCCESS;
	   };
   return STATUS_UNSUCCESSFUL;
  }

NTSTATUS MyZwCreateFile(
    OUT PHANDLE  FileHandle,
    IN ACCESS_MASK  DesiredAccess,
    IN POBJECT_ATTRIBUTES  ObjectAttributes,
    OUT PIO_STATUS_BLOCK  IoStatusBlock,
    IN PLARGE_INTEGER  AllocationSize  OPTIONAL,
    IN ULONG  FileAttributes,
    IN ULONG  ShareAccess,
    IN ULONG  CreateDisposition,
    IN ULONG  CreateOptions,
    IN PVOID  EaBuffer  OPTIONAL,
    IN ULONG  EaLength
    )
{
 BOOL LockOperation = false;
 zDbgPrint("CreateFile PID=%d, File=%ws \n", PsGetCurrentProcessId(), ObjectAttributes->ObjectName->Buffer);
 // ������� ������������ � � ������� ���� ��� ?
 if (!TrustedProcess() && ObjectAttributes->ObjectName->Buffer != NULL) {
	 PWCHAR	TmpStr = (PWCHAR)ExAllocatePool(PagedPool, ObjectAttributes->ObjectName->Length+4);
	 if (TmpStr != NULL) {
		 RtlZeroMemory(TmpStr, ObjectAttributes->ObjectName->Length+4);
		 memcpy(TmpStr, ObjectAttributes->ObjectName->Buffer, ObjectAttributes->ObjectName->Length); 
		 _wcslwr(TmpStr);
		 if (wcsstr(TmpStr, L".exe") != NULL ||
			 wcsstr(TmpStr, L".scr") != NULL ||
			 wcsstr(TmpStr, L".dll") != NULL ||
			 wcsstr(TmpStr, L".sys") != NULL ||
			 wcsstr(TmpStr, L".ocx") != NULL ||
			 wcsstr(TmpStr, L".pif") != NULL ||
			 wcsstr(TmpStr, L".cmd") != NULL ||
			 wcsstr(TmpStr, L".cpl") != NULL ||
			 wcsstr(TmpStr, L".bat") != NULL ||
			 wcsstr(TmpStr, L".nls") != NULL)			 
		 {
			 zDbgPrint("Lock file access !!!!\n");
			 CreateDisposition = FILE_OPEN;
		 }		 
		 // ���������� ������� � ����������� 
		 if (wcsstr(TmpStr, L"\\device\\rawip") != NULL ||
			 wcsstr(TmpStr, L"\\device\\udp") != NULL ||
			 wcsstr(TmpStr, L"\\device\\tcp") != NULL ||
			 wcsstr(TmpStr, L"\\device\\ip") != NULL)			 
		 {
			 zDbgPrint("Lock network access !!!!\n");
			 LockOperation = true;
		 }
      /*
		 // ���������� ������� � ���������� ������ �� ������� AVZ
		 if (wcsstr(TmpStr, L"avzsgkerneldevicelink") != NULL)  {
			 zDbgPrint("Lock AVZ driver link access !!!!\n");
			 LockOperation = true;
		 }
      */ 
 		 ExFreePool(TmpStr);
	 }	  
 }
 if (LockOperation)
	 return STATUS_ACCESS_DENIED;
 // ����� �������� �������
 return OldZwCreateFile(FileHandle, DesiredAccess, ObjectAttributes, 
	  IoStatusBlock, AllocationSize, FileAttributes, ShareAccess,
	  CreateDisposition, CreateOptions, EaBuffer, EaLength);
}


NTSTATUS MyZwCreateKey (
    OUT PHANDLE  KeyHandle,
    IN ACCESS_MASK  DesiredAccess,
    IN POBJECT_ATTRIBUTES  ObjectAttributes,
    IN ULONG  TitleIndex,
    IN PUNICODE_STRING  Class  OPTIONAL,
    IN ULONG  CreateOptions,
    OUT PULONG  Disposition  OPTIONAL
    )
{
 zDbgPrint("CreateKey PID=%d, %ws \n", PsGetCurrentProcessId(), ObjectAttributes->ObjectName->Buffer);
 // ���� ������� �� �������� ����������, �� ������ ���������
 /*
 if (!TrustedProcess()) {
	 zDbgPrint("CreateKey - access changed !!");
	 DesiredAccess = DesiredAccess & ~(KEY_CREATE_SUB_KEY | KEY_SET_VALUE);
 }
 */
 // ����� �������� �������
 return OldZwCreateKey(KeyHandle, DesiredAccess, ObjectAttributes, TitleIndex, Class, CreateOptions, Disposition);
}

NTSTATUS MyZwOpenKey(
    OUT PHANDLE  KeyHandle,
    IN ACCESS_MASK  DesiredAccess,
    IN POBJECT_ATTRIBUTES  ObjectAttributes
    )
{
 zDbgPrint("OpenKey PID=%d, %ws \n", PsGetCurrentProcessId(), ObjectAttributes->ObjectName->Buffer);
 /*
 if (!TrustedProcess()) {
	 zDbgPrint("OpenKey - access changed !!");
	 DesiredAccess = DesiredAccess & ~(KEY_CREATE_SUB_KEY | KEY_SET_VALUE);
 }
 */
 // ����� �������� �������
 return OldZwOpenKey(KeyHandle, DesiredAccess, ObjectAttributes);
}


NTSTATUS  MyZwSetValueKey(
    IN HANDLE  KeyHandle,
    IN PUNICODE_STRING  ValueName,
    IN ULONG  TitleIndex  OPTIONAL,
    IN ULONG  Type,
    IN PVOID  Data,
    IN ULONG  DataSize
    )
{
 zDbgPrint("ZwSetValueKey PID=%d, %ws \n", PsGetCurrentProcessId(), ValueName->Buffer);
 if (!TrustedProcess()) {
	 zDbgPrint("ZwSetValueKey - access denied !!");
	 return STATUS_SUCCESS;
 }
 return OldZwSetValueKey(KeyHandle, ValueName, TitleIndex, Type, Data, DataSize);
}


NTSTATUS NTAPI MyZwDeleteValueKey(
    IN HANDLE KeyHandle,
    IN PUNICODE_STRING ValueName
    )

{
 zDbgPrint("ZwDeleteValueKey PID=%d, %ws \n", PsGetCurrentProcessId(), ValueName->Buffer);
 if (!TrustedProcess()) {
	 zDbgPrint("ZwDeleteValueKey - access denied !!");
	 return STATUS_SUCCESS;
 }
 return OldZwDeleteValueKey(KeyHandle, ValueName);
}

NTSTATUS MyZwOpenProcess( 
    OUT PHANDLE ProcessHandle,
    IN ACCESS_MASK DesiredAccess,
    IN POBJECT_ATTRIBUTES ObjectAttributes,
    IN PCLIENT_ID ClientId OPTIONAL)
{
   zDbgPrint("ZwOpenProcess  PID=%d \n", PsGetCurrentProcessId());
   if (ClientId != NULL)
	   zDbgPrint("ZwOpenProcess  ClientID=%d \n", ClientId->UniqueProcess);
   if (!TrustedProcess() || RestricredMode) {	   
	   DesiredAccess = DesiredAccess & ~(PROCESS_TERMINATE | PROCESS_VM_WRITE | 0x0200);
	   /*if ((ClientId != NULL) && ClientId->UniqueProcess != PsGetCurrentProcessId()) 
		   return STATUS_ACCESS_DENIED; */
   }   
   return OldZwOpenProcess(ProcessHandle, DesiredAccess, ObjectAttributes, ClientId);
}

NTSTATUS MyZwCreateProcess(
   OUT PHANDLE ProcessHandle,
   IN ACCESS_MASK DesiredAccess,
   IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
   IN HANDLE ParentProcess,
   IN BOOLEAN InheritObjectTable,
   IN HANDLE SectionHandle OPTIONAL,
   IN HANDLE DebugPort OPTIONAL,
   IN HANDLE ExceptionPort OPTIONAL
)
{
 zDbgPrint("ZwCreateProcess  PID=%d, %ws \n", PsGetCurrentProcessId(), ObjectAttributes->ObjectName->Buffer);
 if (!TrustedProcess()) {	   
     zDbgPrint("CreateProcess  locked");
	 return STATUS_ACCESS_DENIED;
   }
 return OldZwCreateProcess(ProcessHandle, DesiredAccess, ObjectAttributes,
                           ParentProcess,InheritObjectTable, SectionHandle, DebugPort,
                           ExceptionPort);
}


NTSTATUS MyZwCreateProcessEx(
    OUT PHANDLE ProcessHandle,
    IN ACCESS_MASK DesiredAccess,
    IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
    IN HANDLE ParentProcess,
    IN BOOLEAN InheritObjectTable,
    IN HANDLE SectionHandle OPTIONAL,
    IN HANDLE DebugPort OPTIONAL,
    IN HANDLE ExceptionPort OPTIONAL,
    IN HANDLE Unknown OPTIONAL)

{ 
 zDbgPrint("ZwCreateProcessEx  PID=%d  \n", PsGetCurrentProcessId());
 if (!TrustedProcess()) {	   
   //  zDbgPrint("CreateProcessEx  locked");
	 return STATUS_ACCESS_DENIED;
   }
 return OldZwCreateProcessEx(ProcessHandle, DesiredAccess, ObjectAttributes,
                           ParentProcess,InheritObjectTable, SectionHandle, DebugPort,
                           ExceptionPort, Unknown);
}

// ����������� ZwOpenSection
NTSTATUS  MyZwOpenSection(
    OUT PHANDLE  SectionHandle,
    IN ACCESS_MASK  DesiredAccess,
    IN POBJECT_ATTRIBUTES  ObjectAttributes
    )
{
 BOOL LockOperation = false;
 zDbgPrint("ZwOpenSection  PID=%d, %ws \n", PsGetCurrentProcessId(), ObjectAttributes->ObjectName->Buffer);
 // ������� ������������ � � ������� ���� ��� ?
 if (!TrustedProcess() && ObjectAttributes->ObjectName->Buffer != NULL) {
	 PWCHAR	TmpStr = (PWCHAR)ExAllocatePool(PagedPool, ObjectAttributes->ObjectName->Length+4);
	 if (TmpStr != NULL) {
		 RtlZeroMemory(TmpStr, ObjectAttributes->ObjectName->Length+4);
		 memcpy(TmpStr, ObjectAttributes->ObjectName->Buffer, ObjectAttributes->ObjectName->Length); 
		 _wcslwr(TmpStr);
		 if (wcsstr(TmpStr, L"device\\physicalmemory") != NULL) {
			 LockOperation = true;
			 zDbgPrint("Lock physical memory operations !!!!\n");
		 }
		 ExFreePool (TmpStr);
	 }	  
 }
 if (LockOperation)
	 return STATUS_ACCESS_DENIED;
 return OldZwOpenSection(SectionHandle, DesiredAccess, ObjectAttributes);
}


NTSTATUS MyZwOpenFile(
    OUT PHANDLE  FileHandle,
    IN ACCESS_MASK  DesiredAccess,
    IN POBJECT_ATTRIBUTES  ObjectAttributes,
    OUT PIO_STATUS_BLOCK  IoStatusBlock,
    IN ULONG  ShareAccess,
    IN ULONG  OpenOptions
    )
{
 zDbgPrint("ZwOpenFile  PID=%d, %ws \n", PsGetCurrentProcessId(), ObjectAttributes->ObjectName->Buffer);
 BOOL LockOperation = false;
 // ������� ������������ � � ������� ���� ��� ?
 if (!TrustedProcess() && ObjectAttributes->ObjectName->Buffer != NULL) {
	 PWCHAR	TmpStr = (PWCHAR)ExAllocatePool(PagedPool, ObjectAttributes->ObjectName->Length+4);
	 if (TmpStr != NULL) {
		 RtlZeroMemory(TmpStr, ObjectAttributes->ObjectName->Length+4);
		 memcpy(TmpStr, ObjectAttributes->ObjectName->Buffer, ObjectAttributes->ObjectName->Length); 
		 _wcslwr(TmpStr);
		 if (wcsstr(TmpStr, L"\\device\\rawip") != NULL ||
			 wcsstr(TmpStr, L"\\device\\udp") != NULL ||
			 wcsstr(TmpStr, L"\\device\\tcp") != NULL ||
			 wcsstr(TmpStr, L"\\device\\ip") != NULL)			 
		 {
			 zDbgPrint("Lock network access !!!!\n");
			 LockOperation = true;
		 }
		 // ���������� ������� � ���������� ������ �� ������� AVZ
		 if (wcsstr(TmpStr, L"avzsgkerneldevicelink") != NULL)  {
			 zDbgPrint("Lock AVZ driver link access !!!!\n");
			 LockOperation = true;
		 }
		 ExFreePool(TmpStr);
	 }	  
 }
 if (LockOperation)
	 return STATUS_ACCESS_DENIED;
 return OldZwOpenFile(FileHandle, DesiredAccess, ObjectAttributes, 
	        IoStatusBlock, ShareAccess, OpenOptions);
}

NTSTATUS MyZwOpenThread(
     OUT PHANDLE ThreadHandle,
	 IN ACCESS_MASK DesiredAccess,
	 OUT POBJECT_ATTRIBUTES ObjectAttributes,
	 IN PCLIENT_ID ClientId)
{

	zDbgPrint("ZwOpenThread  PID=%d, ClientId.Pid=%d \n", PsGetCurrentProcessId(), ClientId->UniqueProcess);
	if (!TrustedProcess() && (ClientId->UniqueProcess != PsGetCurrentProcessId())) {
		zDbgPrint("ZwOpenThread - access denied! \n");
		return STATUS_ACCESS_DENIED;
	}
	return OldZwOpenThread(ThreadHandle, DesiredAccess, ObjectAttributes, ClientId); 
}

 NTSTATUS MyZwWriteVirtualMemory(
     IN HANDLE ProcessHandle,
	 IN PVOID BaseAddress,
	 IN PVOID Buffer,
	 IN ULONG BufferLength,
	 OUT PULONG ReturnLength OPTIONAL)
{
	zDbgPrint("ZwWriteVirtualMemory  PID=%d \n", PsGetCurrentProcessId());
	/*
	if (!TrustedProcess() || RestricredMode) {
		zDbgPrint("ZwWriteVirtualMemory - access denied! \n");
		return STATUS_SUCCESS;
	}
	*/
	return OldZwWriteVirtualMemory(ProcessHandle, BaseAddress, Buffer, BufferLength, ReturnLength);
}

NTSTATUS MyZwTerminateJobObject(  
	IN HANDLE  JobHandle,
	IN NTSTATUS  ExitStatus 
 )
{
	zDbgPrint("ZwTerminateJobObject  PID=%d \n", PsGetCurrentProcessId());
	if (!TrustedProcess()) {
		zDbgPrint("ZwTerminateJobObject - access denied! \n");
		return STATUS_SUCCESS;
	}
	return OldZwTerminateJobObject(JobHandle, ExitStatus);
}
// ********** ��������� Hook �� c�������/���������� ��������� **********
VOID MyCreateProcessNotifyRoutine(IN HANDLE  ParentId,
    IN HANDLE  ProcessId,
    IN BOOLEAN  Create)
{
	zDbgPrint("CreateProcessNotifyRoutine: Call params ParentId = %d, ProcessId = %d, Create = %d \n",
			ParentId, ProcessId, Create);
	// ������������ ����������
	if (Create && TrustedProcess() && TrustedProcessByPID((DWORD)ParentId)) {
		AddTrustedPID((DWORD)ProcessId);
		zDbgPrint("CreateProcessNotifyRoutine:  Add trusted PID =%d \n", (DWORD)ProcessId);
	}
	// �������� �������� �� ������ ���������� � ������ ��� ����������
	if (!Create) {
		DeleteTrustedPID((DWORD)ProcessId);
		if ((DWORD)ProcessId == TrustedPID1)
			TrustedPID1 = 0xFFFFFFFF;
		zDbgPrint("CreateProcessNotifyRoutine: Delete trusted.  ParentId = %d, ProcessId = %d \n",
			ParentId, ProcessId);
	}
}


PF_FORWARD_ACTION IPFirewallHookProc(
        unsigned char *PacketHeader,
        unsigned char *Packet,
        unsigned int PacketLength,
        unsigned int RecvInterfaceIndex,
        unsigned int SendInterfaceIndex,
        IPAddr RecvLinkNextHop,
        IPAddr SendLinkNextHop)
{
    zDbgPrint("[ipfilter] PID=%d \n", PsGetCurrentProcessId());
	if (!TrustedProcess()) {
	 return PF_DROP;
	}
    if (RecvInterfaceIndex != INVALID_PF_IF_INDEX) {
        
        zDbgPrint("[ipfilter] hook_proc: receive packet on interface #%u (len: %u)\n",
                        RecvInterfaceIndex,
                        PacketLength);        
    }
    
    if (SendInterfaceIndex != INVALID_PF_IF_INDEX) {
        
        zDbgPrint("[ipfilter] hook_proc: send packet on interface #%u (len: %u)\n",
                        SendInterfaceIndex,
                        PacketLength);        
    }
    
    return PF_FORWARD;
}

NTSTATUS SetIPFirewallHookProc(PacketFilterExtensionPtr HookPtr)
{
	UNICODE_STRING ipfilter_name;
	NTSTATUS status;
	PFILE_OBJECT fileobj = NULL;
	PDEVICE_OBJECT devobj;
	PF_SET_EXTENSION_HOOK_INFO hook_nfo;
	PIRP IRP = NULL;
	IO_STATUS_BLOCK isb;

	// ���������� ������ � ������ IPFILTERDRIVER
	RtlInitUnicodeString(&ipfilter_name, DD_IPFLTRDRVR_DEVICE_NAME);
	// ��������� ��������� �� IPFILTERDRIVER
	status = IoGetDeviceObjectPointer(
		&ipfilter_name,
		STANDARD_RIGHTS_ALL,
		&fileobj,
		&devobj);
	if (status == STATUS_SUCCESS) {
		hook_nfo.ExtensionPointer = HookPtr;
		// ������������ IRP � IOCTL_PF_SET_EXTENSION_POINTER
		IRP = IoBuildDeviceIoControlRequest(IOCTL_PF_SET_EXTENSION_POINTER,
			devobj, &hook_nfo, sizeof(hook_nfo),
			NULL, 0, FALSE, NULL, &isb);
		// �������� IRP
		if (IRP != NULL) {
			status = IoCallDriver(devobj, IRP);
			IRP = NULL;
		}
		else 
			status = STATUS_UNSUCCESSFUL;
	}
	if (fileobj != NULL)
		ObDereferenceObject(fileobj);
	return status;
}

VOID SetIPFirewall(BOOL NewStatus)
{
 if (NewStatus == TCPIPHooksInstalled) 
	 return;
 if (NewStatus)
	 TCPIPHooksInstalled = (SetIPFirewallHookProc(IPFirewallHookProc) == STATUS_SUCCESS);
  else 
	 TCPIPHooksInstalled = (SetIPFirewallHookProc(NULL) == STATUS_SUCCESS);
}

VOID SetKiSTHook()
{
 DWORD OldCR0;	
  
 // ��������� ����������
 KIRQL OldIRQL = KeRaiseIrqlToDpcLevel();			 
 
 // ����� WP ����
_asm {
    mov eax,CR0 
    mov OldCR0,eax
    and eax,0xFFFEFFFF			
    mov cr0, eax
 }
 // 1. �������� ZwCreateFile
if (ZwCreateFileCode >= 0) {
 OldZwCreateFile = (PZwCreateFile)*KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwCreateFileCode];
 KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwCreateFileCode]   = (NTPROC)*MyZwCreateFile;
}

  // 2. �������� ZwCreateKey
if (ZwCreateKeyCode >= 0) {
 OldZwCreateKey = (PZwCreateKey)*KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwCreateKeyCode];
 KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwCreateKeyCode]   = (NTPROC)*MyZwCreateKey;
}
 // 3. �������� ZwOpenKey
 if (ZwOpenKeyCode >= 0) {
  OldZwOpenKey = (PZwOpenKey)*KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenKeyCode];
  KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenKeyCode]   = (NTPROC)*MyZwOpenKey;
 }

 // 4. �������� ZwSetValueKey
 if (ZwSetValueKeyCode >= 0) {
  OldZwSetValueKey = (PZwSetValueKey)*KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwSetValueKeyCode];
  KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwSetValueKeyCode]   = (NTPROC)*MyZwSetValueKey;
 }
 // 5. �������� ZwDeleteValueKey
 if (ZwDeleteValueKeyCode >= 0) {
  OldZwDeleteValueKey = (PZwDeleteValueKey)*KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwDeleteValueKeyCode];
  KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwDeleteValueKeyCode]   = (NTPROC)*MyZwDeleteValueKey;
 }
 
 // 6. �������� ZwOpenProcess (!!!!!)
 if (ZwOpenProcessCode >= 0) {
  OldZwOpenProcess = (PZwOpenProcess)*KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenProcessCode];
  KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenProcessCode]   = (NTPROC)*MyZwOpenProcess;
 }
 
 // 7. �������� ZwCreateProcess
 if (ZwCreateProcessCode >= 0) {
  OldZwCreateProcess = (PZwCreateProcess)*KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwCreateProcessCode];
  KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwCreateProcessCode]   = (NTPROC)*MyZwCreateProcess;
 }

  // 8. �������� ZwCreateProcessEx
 if (ZwCreateProcessExCode >= 0) {
  OldZwCreateProcessEx = (PZwCreateProcessEx)*KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwCreateProcessExCode];
  KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwCreateProcessExCode]   = (NTPROC)*MyZwCreateProcessEx;
 }

 // 9. �������� ZwOpenSectionCode
 if (ZwOpenSectionCode >= 0) {
  OldZwOpenSection = (PZwOpenSection)*KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenSectionCode];
  KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenSectionCode]   = (NTPROC)*MyZwOpenSection;
 }

 // 10. �������� ZwOpenFile
 if (ZwOpenFileCode >= 0) {
  OldZwOpenFile = (PZwOpenFile)*KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenFileCode];
  KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenFileCode]   = (NTPROC)*MyZwOpenFile;
 }

 // 11. �������� ZwOpenThread
 if (ZwOpenThreadCode >= 0) {
  OldZwOpenThread = (PZwOpenThread)*KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenThreadCode];
  KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenThreadCode]   = (NTPROC)*MyZwOpenThread;
 } 

  // 12. �������� ZwOpenThread 
 if (ZwWriteVirtualMemoryCode >= 0) {
  OldZwWriteVirtualMemory = (PZwWriteVirtualMemory)*KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwWriteVirtualMemoryCode];
  KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwWriteVirtualMemoryCode]   = (NTPROC)*MyZwWriteVirtualMemory;
 } 

  // 13. �������� ZwTerminateJobObject 
 if (ZwTerminateJobObjectCode >= 0) {
  OldZwTerminateJobObject = (PZwTerminateJobObject)*KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwTerminateJobObjectCode];
  KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwTerminateJobObjectCode]   = (NTPROC)*MyZwTerminateJobObject;
 } 

 // ��� ���������
 if (ZwTerminateJobObjectCode >= 0) {
	 OldZwCreateJobObject = (PZwCreateJobObject)*KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwCreateJobObjectCode];
 }
 
 
 // �������������� WP ����
 _asm {
	 mov eax,OldCR0		
     mov cr0,eax
 }
 // �������������� ����������
 KeLowerIrql(OldIRQL);
}


VOID DeleteKiSTHook()
{
 DWORD OldCR0;	
  
 // ��������� ����������
 KIRQL OldIRQL = KeRaiseIrqlToDpcLevel();			 
 
 // ����� WP ����
_asm 
{
	mov eax,CR0
	mov OldCR0,eax
	and eax,0xFFFEFFFF
	mov cr0, eax
}
  if (ZwCreateFileCode >= 0 && OldZwCreateFile != NULL) 
   KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwCreateFileCode]   = (NTPROC)*OldZwCreateFile;	 
  if (ZwCreateKeyCode >= 0 && OldZwCreateKey != NULL) 
   KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwCreateKeyCode]    = (NTPROC)*OldZwCreateKey;	 
  if (ZwOpenKeyCode >= 0 && OldZwOpenKey != NULL) 
   KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenKeyCode]      = (NTPROC)*OldZwOpenKey;	 
  if (ZwSetValueKeyCode >= 0 && OldZwSetValueKey != NULL) 
   KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwSetValueKeyCode]  = (NTPROC)*OldZwSetValueKey;	 
  if (ZwDeleteValueKeyCode >= 0 && OldZwDeleteValueKey != NULL) 
   KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwDeleteValueKeyCode]  = (NTPROC)*OldZwDeleteValueKey;	 
  if (ZwOpenProcessCode >= 0 && OldZwOpenProcess != NULL) 
   KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenProcessCode]  = (NTPROC)*OldZwOpenProcess;	 
  if (ZwCreateProcessCode >= 0 && OldZwCreateProcess != NULL) 
   KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwCreateProcessCode]  = (NTPROC)*OldZwCreateProcess;	 
  if (ZwCreateProcessExCode >= 0 && OldZwCreateProcessEx != NULL) 
   KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwCreateProcessExCode]  = (NTPROC)*OldZwCreateProcessEx;	 
  if (ZwOpenSectionCode >= 0 && OldZwOpenSection != NULL) 
   KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenSectionCode]  = (NTPROC)*OldZwOpenSection;	 
  if (ZwOpenFileCode >= 0 && OldZwOpenFile != NULL) 
   KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenFileCode]  = (NTPROC)*OldZwOpenFile;	 
  if (ZwOpenThreadCode >= 0 && OldZwOpenThread != NULL) 
   KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwOpenThreadCode]  = (NTPROC)*OldZwOpenThread;	 
  if (ZwWriteVirtualMemoryCode >= 0 && OldZwWriteVirtualMemory != NULL) 
   KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwWriteVirtualMemoryCode]  = (NTPROC)*OldZwWriteVirtualMemory;	 
  if (ZwTerminateJobObjectCode >= 0 && OldZwTerminateJobObject != NULL) 
   KeServiceDescriptorTable->ntoskrnl.ServiceTable[ZwTerminateJobObjectCode]  = (NTPROC)*OldZwTerminateJobObject;	 
 // �������������� WP ����
 _asm {
	 mov eax,OldCR0		
     mov cr0,eax
 }
 // �������������� ����������
 KeLowerIrql(OldIRQL);
}


// ***** �������� �������� *****
void DriverUnload (PDRIVER_OBJECT pDriverObject)
{
  // �������� ����������
 DeleteKiSTHook();
 // ���������� Firewall
 //SetIPFirewall(false);
 // �������� HOOK �� �������� � ���������� ���������
 if (ProcessNotifyRoutineRes == STATUS_SUCCESS)
	 NTSTATUS Res = PsSetCreateProcessNotifyRoutine(*MyCreateProcessNotifyRoutine, true);
 // �������� ���������� ������
 IoDeleteSymbolicLink (&usSymbolicLinkName);
 // �������� ����������
 IoDeleteDevice       (gpDeviceObject);
 return;
}

// ***** ������������� �������� *****
NTSTATUS DriverInitialize (PDRIVER_OBJECT  pDriverObject,
                           PUNICODE_STRING pusRegistryPath)
{
 PDEVICE_OBJECT pDeviceObject = NULL;
 NTSTATUS       ns            = STATUS_DEVICE_CONFIGURATION_ERROR; // ��� ��������
 // �������� ����������
 if ((ns = IoCreateDevice (pDriverObject, DEVICE_CONTEXT_,
                              &usDeviceName, FILE_DEVICE_UNKNOWN,
                              0, FALSE, &pDeviceObject))
        == STATUS_SUCCESS)
        {
		// ���������� ������� - ������� ���������� ������
        if ((ns = IoCreateSymbolicLink (&usSymbolicLinkName,
                                        &usDeviceName))
            == STATUS_SUCCESS)
            { 
		    // ������ (� ����������� ���������� !) ������� - ���������� ������
            gpDeviceObject  = pDeviceObject;
            gpDeviceContext = (PDEVICE_CONTEXT)pDeviceObject->DeviceExtension;

            gpDeviceContext->pDriverObject = pDriverObject;
            gpDeviceContext->pDeviceObject = pDeviceObject;
            }
        else
            {
			// ���������� �������, � ������ - ���. ����� ������ ����������
            IoDeleteDevice (pDeviceObject);
            }
        }
 return ns; 
}


// ***** ���������� ������� ��������/��������/������� *****
NTSTATUS DispatchCreateCloseControl (PDEVICE_OBJECT pDeviceObject,
                           PIRP           pIrp)
{
	PIO_STACK_LOCATION pisl;
	DWORD              dInfo = 0;
	NTSTATUS           ns    = STATUS_NOT_IMPLEMENTED; // ��� ��������
	// ��� ��� ���������� ??
	// �������� ���������� IRP �����
	pisl = IoGetCurrentIrpStackLocation (pIrp);
	zDbgPrint("Device Open !");	
	// ��������� ��� �������������� �������
	switch (pisl->MajorFunction)
	{
	case IRP_MJ_CREATE:
	case IRP_MJ_CLEANUP:
	case IRP_MJ_CLOSE:
		{
			ns = STATUS_SUCCESS;
			break;
		}
	}

	// ��������� IRP ������
	pIrp->IoStatus.Status      = ns;
	pIrp->IoStatus.Information = dInfo;
	IoCompleteRequest (pIrp, IO_NO_INCREMENT);
	return ns;
}

// ***** ���������� ������� IO Control *****
NTSTATUS DispatchControl (PDEVICE_OBJECT pDeviceObject,
                           PIRP           pIrp)
{
   PIO_STACK_LOCATION pisl;
   DWORD              dInfo = 0;
   NTSTATUS           ns    = STATUS_NOT_IMPLEMENTED; // ��� ��������
   // ��������� ������������ IRP �����
   pisl = IoGetCurrentIrpStackLocation (pIrp);
   
   // ������� ����� � ��� ������
   PVOID  InputBuffer         = pIrp->AssociatedIrp.SystemBuffer;
   ULONG  InputBufferLength   = pisl->Parameters.DeviceIoControl.InputBufferLength;
   // �������� ����� � ��� ������
   PVOID  OutputBuffer        = pIrp->AssociatedIrp.SystemBuffer;
   ULONG  OutputBufferLength  = pisl->Parameters.DeviceIoControl.OutputBufferLength;
   // ��� ���������� 
   ULONG  IoControlCode		  = pisl->Parameters.DeviceIoControl.IoControlCode;
   // ����� ������ ��� �������
   zDbgPrint("IoControlCode = %x\n", IoControlCode);	
   zDbgPrint("InputBufferLength  = %x\n", InputBufferLength);	
   zDbgPrint("OutputBufferLength = %x\n", OutputBufferLength);	
   // ��������� ���� ��������
   HANDLE  CurrentProcess = PsGetCurrentProcess();

   // **** IOCTL_Z_SET_TRUSTEDPROCESS - ��������� ��������� ����������� �������� *****
   if (IoControlCode == IOCTL_Z_SET_TRUSTEDPROCESS) 
	   // �������� ������� �������� ������
       if (InputBufferLength >= 4 && TrustedPID1 == 0xFFFFFFFF) 
	   {
		   memcpy(&TrustedPID1, InputBuffer, 4);
		   zDbgPrint("IOCTL_Z_SET_TRUSTEDPROCESS PID=%d \n", TrustedPID1);
		   ns = STATUS_SUCCESS;
	   }
   // ��� ��������� ������� ��������� ������ �� ����������� ��������
   if ((DWORD)PsGetCurrentProcessId() == TrustedPID1) {
	   if (IoControlCode == IOCTL_Z_ADD_ALTTRUSTEDPROCESS)
		   if (InputBufferLength >= 4) 
		   {
			   DWORD TmpTrustedPID;
			   memcpy(&TmpTrustedPID, InputBuffer, 4);
			   zDbgPrint("IOCTL_Z_ADD_TRUSTEDPROCESS1 PID=%d \n", TmpTrustedPID);
			   ns = AddTrustedPID(TmpTrustedPID);
	   }
	   if (IoControlCode == IOCTL_Z_DEL_ALTTRUSTEDPROCESS)
		   if (InputBufferLength >= 4) 
		   {
			   DWORD TmpTrustedPID;
			   memcpy(&TmpTrustedPID, InputBuffer, 4);
			   zDbgPrint("IOCTL_Z_DEL_TRUSTEDPROCESS1 PID=%d \n", TmpTrustedPID);
			   DeleteTrustedPID(TmpTrustedPID);
			   ns = STATUS_SUCCESS;
	   }
	   if (IoControlCode == IOCTL_Z_CLR_ALTTRUSTEDPROCESS) 
		   {
			   zDbgPrint("IOCTL_Z_CLR_TRUSTEDPROCESS \n");
			    ClearTrustedPIDTable();
			   ns = STATUS_SUCCESS;
	   }
	   if (IoControlCode == IOCTL_Z_ENABLEULNOAD) 
		   if (InputBufferLength >= 4) 
		   {
			   DWORD Tmp;
			   memcpy(&Tmp, InputBuffer, 4);
			   zDbgPrint("IOCTL_Z_ENABLEULNOAD NewState=%d \n", Tmp);
		       // ����������� ����������� �������� ��������
			   if (Tmp != 0) {
				   zDbgPrint("DriverUnload proc inserted \n");
				   gpDeviceContext->pDriverObject->DriverUnload  = DriverUnload;
			   }
			   else {
				   zDbgPrint("DriverUnload proc removed \n");
				   gpDeviceContext->pDriverObject->DriverUnload  = NULL;
			   }
			   ns = STATUS_SUCCESS;
	   }
	   if (IoControlCode == IOCTL_Z_RESTRICTEDMODE) 
		   if (InputBufferLength >= 4) 
		   {
			   DWORD Tmp;
			   memcpy(&Tmp, InputBuffer, 4);
			   zDbgPrint("IOCTL_Z_RESTRICTEDMODE NewState=%d \n", Tmp);
		       // ����������� ����������� �������� ��������
			   if (Tmp != 0) {
				   zDbgPrint("RestrictedMode: on \n");
				   RestricredMode = true;
			   }
			   else {
				   zDbgPrint("RestrictedMode: off \n");
				   RestricredMode = false;
			   }
			   ns = STATUS_SUCCESS;
	   }
   }
   // ���������� IRP �������
   pIrp->IoStatus.Status      = ns;
   pIrp->IoStatus.Information = dInfo;
   IoCompleteRequest (pIrp, IO_NO_INCREMENT);
   return ns;
}

// ***** ����� ����� � ������� *****
NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject, IN PUNICODE_STRING pusRegistryPath)
{
	NTSTATUS          InitRes = STATUS_SUCCESS;	
	// ������� ������� ���������� ��������
	ClearTrustedPIDTable();
	// ��������� ��������� ������ ��
    switch ((*NtBuildNumber) & 0x00ffffff) {
	 case  1381:  // Win NT
      ZwCreateFileCode = 23;	 
	  ZwCreateKeyCode  = 25;
	  ZwOpenKeyCode    = 81;
	  ZwSetValueKeyCode = 179;
	  ZwOpenProcessCode = 84;
	  ZwCreateProcessCode = 31;
	  ZwOpenSectionCode = 86;
	  ZwOpenFileCode = 79;
	  ZwDeleteValueKeyCode = 44;
	  ZwWriteVirtualMemoryCode = 203;
	  break;
     case  2195:  // Win 2k
      ZwCreateFileCode = 32;	 
	  ZwCreateKeyCode  = 35;
	  ZwOpenKeyCode    = 103;
	  ZwSetValueKeyCode = 215;
	  ZwOpenProcessCode = 106;
  	  ZwCreateProcessCode = 41;
	  ZwOpenSectionCode = 108;
	  ZwOpenFileCode = 100;
	  ZwDeleteValueKeyCode = 55;
	  ZwWriteVirtualMemoryCode = 240;
	  ZwTerminateJobObjectCode = 223;
	  ZwCreateJobObjectCode = 34;
	  EPROCESS_ALPRel = 0xA0; EPROCESS_NAMERel = 0x1FC; EPROCESS_PIDRel = 0x9C;
	  break;
     case 2600:   // Win XP
      ZwCreateFileCode = 37;	 
	  ZwCreateKeyCode  = 41;
	  ZwOpenKeyCode    = 119;
	  ZwSetValueKeyCode = 247;
	  ZwOpenProcessCode = 122;
  	  ZwCreateProcessCode = 47;
 	  ZwCreateProcessExCode = 48;
	  ZwOpenSectionCode = 125;
	  ZwOpenFileCode = 116;
	  ZwDeleteValueKeyCode = 65;
	  ZwWriteVirtualMemoryCode = 277;
	  ZwTerminateJobObjectCode = 256;
	  ZwCreateJobObjectCode = 39;
	  EPROCESS_ALPRel = 0x88; EPROCESS_NAMERel = 0x174; EPROCESS_PIDRel = 0x84;
	  break;
     case 3790:  // W2K3
      ZwCreateFileCode = 39;	 
	  ZwCreateKeyCode  = 43;
	  ZwOpenKeyCode    = 125;	  
	  ZwSetValueKeyCode = 256;
	  ZwOpenProcessCode = 128;
  	  ZwCreateProcessCode = 49;
 	  ZwCreateProcessExCode = 50;
	  ZwOpenSectionCode = 131;
	  ZwOpenFileCode = 122;
	  ZwDeleteValueKeyCode = 68;
	  ZwWriteVirtualMemoryCode = 287;	  
  	  ZwTerminateJobObjectCode = 265;
	  ZwCreateJobObjectCode = 41;
	  EPROCESS_ALPRel = 0x98; EPROCESS_NAMERel = 0x164; EPROCESS_PIDRel = 0x94;
	  break;
     case 5112:  // Vista Beta 1
      ZwCreateFileCode = 59;	 
	  ZwCreateKeyCode  = 63;
	  ZwOpenKeyCode    = 182;	  
	  ZwSetValueKeyCode = 318;
	  ZwOpenProcessCode = 185;
  	  ZwCreateProcessCode = 69;
 	  ZwCreateProcessExCode = 70;
	  ZwOpenSectionCode = 188;
	  ZwOpenFileCode = 179;
	  ZwDeleteValueKeyCode = 123;
	  ZwWriteVirtualMemoryCode = 350;
  	  ZwTerminateJobObjectCode = 327;
	  ZwCreateJobObjectCode = 61;
	  break;
     case 5308:  // Vista Beta 2
      ZwCreateFileCode = 59;	 
	  ZwCreateKeyCode  = 63;
	  ZwOpenKeyCode    = 188;	  
	  ZwSetValueKeyCode = 326;        //+
	  ZwOpenProcessCode = 192;        //+
  	  ZwCreateProcessCode = 70;       //+
 	  ZwCreateProcessExCode = 71;     //+
	  ZwOpenSectionCode = 195;        //+
	  ZwOpenFileCode = 185;           //+
	  ZwDeleteValueKeyCode = 126;     //+
	  ZwWriteVirtualMemoryCode = 360; //+
  	  ZwTerminateJobObjectCode = 335; //+
	  ZwCreateJobObjectCode = 61;     //+
	  break;
     case 6000:  // Vista Release 2006-11-28
      ZwCreateFileCode = 60;	 
	  ZwCreateKeyCode  = 64;
	  ZwOpenKeyCode    = 189;	  
	  ZwSetValueKeyCode = 328; 
	  ZwOpenProcessCode = 194;
  	  ZwCreateProcessCode = 72;  
 	  ZwCreateProcessExCode = 73;
	  ZwOpenSectionCode = 197;
	  ZwOpenFileCode = 186;
	  ZwDeleteValueKeyCode = 126;
	  ZwWriteVirtualMemoryCode = 362;
  	  ZwTerminateJobObjectCode = 337;
	  ZwCreateJobObjectCode = 62; 
	  break;
	 default: 
	  return STATUS_UNSUCCESSFUL;
     }	
//	SetIPFirewall(true);
    // ��������� ������������ ������� "�������� ���������"
	ProcessNotifyRoutineRes = PsSetCreateProcessNotifyRoutine(*MyCreateProcessNotifyRoutine, false);
	zDbgPrint("ProcessNotifyRoutineRes =  %d",  ProcessNotifyRoutineRes);
	// ��������� ���������� KiST
	SetKiSTHook();   
	// �������� ������� "����������"
	if (DriverInitialize(pDriverObject, pusRegistryPath) == STATUS_SUCCESS)
	{
		// ����������� ����������� DEVICE_CONTROL	 
		pDriverObject->MajorFunction [IRP_MJ_DEVICE_CONTROL] = DispatchControl;
		// ����������� ������������ CREATE/CLOSE/CLEANUP
		pDriverObject->MajorFunction [IRP_MJ_CLEANUP] =
		pDriverObject->MajorFunction [IRP_MJ_CREATE] = 
		pDriverObject->MajorFunction [IRP_MJ_CLOSE] =  DispatchCreateCloseControl;

	};
	// ������� ���������� �������������
    return InitRes;	
}
