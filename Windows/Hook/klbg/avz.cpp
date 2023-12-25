#ifndef _WIN64
//--------------------------------------------------------------------------------------------------------

// ������� ��� ������������ ������� AVZ
// (�) ������ ����, 2005
#include <fltkernel.h>
#include "avz.h"


DWORD SysCallPTR = 0;

extern "C" {
	// ��������� �� SDT
	extern PSERVICE_DESCRIPTOR_TABLE    KeServiceDescriptorTable;

	// ����� ������ NT - ��� �������
	extern  PWORD						NtBuildNumber;
}

// PID ��������, ������� ����� ��������� ���������
DWORD TrustedPID = 0xFFFFFFFF;

NTSTATUS DumpKernelMemory(PVOID DstAddr, PVOID SrcAddr, ULONG Size)
{
    PMDL  pSrcMdl, pDstMdl;
    PUCHAR pAddress, pDstAddress;
    NTSTATUS st = STATUS_UNSUCCESSFUL;
    ULONG r;

	// ������� MDL ��� ������-���������
    pSrcMdl = IoAllocateMdl(SrcAddr, Size, FALSE, FALSE, NULL);

	if (pSrcMdl)
	{
		// ���������� MDL
		MmBuildMdlForNonPagedPool(pSrcMdl);
		// ��������� ������ �� MDL
		pAddress = (PUCHAR)MmGetSystemAddressForMdlSafe(pSrcMdl, NormalPagePriority);
		zDbgPrint("pAddress = %x", pAddress);
		if (pAddress != NULL)
		{
			pDstMdl = IoAllocateMdl(DstAddr, Size, FALSE, FALSE, NULL);
			zDbgPrint("pDstMdl = %x", pDstMdl);
			if (pDstMdl != NULL)
			{
				__try
				{
					MmProbeAndLockPages(pDstMdl, KernelMode, IoWriteAccess);
					pDstAddress = (PUCHAR)MmGetSystemAddressForMdlSafe(pDstMdl, NormalPagePriority);
					zDbgPrint("pDstAddress = %x", pDstAddress);
					if (pDstAddress != NULL)
					{
						memset(pDstAddress, 0, Size);
						zDbgPrint("Copy block");
						for (r = 1; r < Size; r++)
						{
							if (MmIsAddressValid(pAddress)) 
								*pDstAddress = *pAddress;
							else
								*pDstAddress = 0;
							pAddress++;
							pDstAddress++;
						}

						st = STATUS_SUCCESS;
					}

					MmUnlockPages(pDstMdl);
				}
				__except(EXCEPTION_EXECUTE_HANDLER)
				{    
					zDbgPrint("Copy block exception");
				}
				IoFreeMdl(pDstMdl);
			}
		}            
		IoFreeMdl(pSrcMdl);
	}
	return st;
}
// ***** ���������� ������� IO Control *****
extern "C"
NTSTATUS AvzDispatchControl ( __in PIRP pIrp )
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

	// ��������� PID ��������, ������� ����� ��������� ���������
	if (IoControlCode == IOCTL_Z_SETTRUSTEDPID) {
		//�������� ������� �������� ������
		if (OutputBufferLength >= 16) 
		{
			DWORD TmpPID = 0xFFFFFFFF, X, X1, X2;
			memcpy(&TmpPID, InputBuffer, 4);
			memcpy(&X, (PVOID)((DWORD)InputBuffer+4), 4);
			memcpy(&X1, (PVOID)((DWORD)InputBuffer+8), 4);
			memcpy(&X2, (PVOID)((DWORD)InputBuffer+12), 4);
			DWORD Y = (X1*3+X2*2+155)*(X2-3) + TmpPID; 
			zDbgPrint("Control codes - Y=%d, X=%d, X1=%d, X2=%d", TmpPID, Y, X, X1, X2);
			if (X == Y && Y > 1500) {
				zDbgPrint("Trusted Process = %d", TmpPID);
				TrustedPID = TmpPID; 
				dInfo = 0;
				ns = STATUS_SUCCESS;         
			}
		}
	}
	if ((DWORD)PsGetCurrentProcessId() == TrustedPID) {
		// **** IOCTL_Z_GET_KESDT_PTR - ������ ������ SDT *****
		if (IoControlCode == IOCTL_Z_GET_KESDT_PTR) {
			//�������� ������� �������� ������
			if (OutputBufferLength >= 4) 
			{
				__try {
					DWORD Tmp = (DWORD)KeServiceDescriptorTable;
					zDbgPrint("KeServiceDescriptorTable Address = %x\n", Tmp);	
					memcpy(OutputBuffer, &Tmp, 4);
					dInfo = 4;
					ns = STATUS_SUCCESS;         
				} __except(EXCEPTION_EXECUTE_HANDLER) {
					dInfo = 0; 
					ns = STATUS_DATA_ERROR;
				}

			}
			else ns = STATUS_BUFFER_TOO_SMALL; // ������� ������		   
		}

		// **** IOCTL_Z_GET_SDT_PTR - ������ ������ SDT *****
		if (IoControlCode == IOCTL_Z_GET_SDT_PTR) {
			//�������� ������� �������� ������
			if (OutputBufferLength >= 4) 
			{
				__try {
					DWORD Tmp = (DWORD)(KeServiceDescriptorTable->ntoskrnl.ServiceTable);
					zDbgPrint("ntoskrnl table Address = %x\n", Tmp);	
					memcpy(OutputBuffer, &Tmp, 4);
					dInfo = 4;
					ns = STATUS_SUCCESS;         
				} __except(EXCEPTION_EXECUTE_HANDLER) {
					dInfo = 0; 
					ns = STATUS_DATA_ERROR;
				}
			}
			else ns = STATUS_BUFFER_TOO_SMALL; // ������� ������		   
		}

		// **** IOCTL_Z_GET_SDT_SIZE - ������ ���-�� ��������� SDT *****
		if (IoControlCode == IOCTL_Z_GET_SDT_SIZE) {
			//�������� ������� �������� ������
			if (OutputBufferLength >= 4) 
			{
				__try {
					DWORD Tmp = KeServiceDescriptorTable->ntoskrnl.ServiceLimit;
					zDbgPrint("SDT ServiceLimit = %x\n", Tmp);	
					memcpy(OutputBuffer, &Tmp, 4);
					dInfo = 4;
					ns = STATUS_SUCCESS;         
				} __except(EXCEPTION_EXECUTE_HANDLER) {
					dInfo = 0; 
					ns = STATUS_DATA_ERROR;
				}
			}
			else ns = STATUS_BUFFER_TOO_SMALL; // ������� ������		   
		}

		// ������ ������ ������� � �������� �������
		if (IoControlCode == IOCTL_Z_GET_SDT_ENTRY) {
			// �������� ������� ��������/��������� ������
			if (OutputBufferLength >= 4 && InputBufferLength >= 4) {
				// ������ ���� ������� �� ������ 4� ���� �� �������� ������ 
				DWORD ServiceID = 0;
				// ����������� 
				memcpy(&ServiceID, InputBuffer, 4);
				zDbgPrint("ServiceID = @%x\n", ServiceID);
				// �������� ������ ������� (��� ������ ���� � ��������� 0..ntoskrnl.ServiceLimit-1)
				if (((LONG)ServiceID >= 0) && (ServiceID < KeServiceDescriptorTable->ntoskrnl.ServiceLimit)) {
					__try {
						DWORD Tmp = (DWORD)KeServiceDescriptorTable->ntoskrnl.ServiceTable[ServiceID];
						memcpy(OutputBuffer, &Tmp, 4);
						dInfo = 4;
						ns = STATUS_SUCCESS;         
					} __except(EXCEPTION_EXECUTE_HANDLER) {
						dInfo = 0; 
						ns = STATUS_DATA_ERROR;
					}
				}
				else
					ns = STATUS_DATA_ERROR; // ������� ������			
			}
			else
				ns = STATUS_BUFFER_TOO_SMALL; // ������� ������
		}

		// ��������� ������ ������� � �������� �������
		if (IoControlCode == IOCTL_Z_SET_SDT_ENTRY) {
			// �������� ������� ��������/��������� ������
			if (OutputBufferLength >= 4 && InputBufferLength >= 8) {
				// ������ ���� ������� �� ������ 4� ���� �� �������� ������ 
				DWORD ServiceID = 0, NewPtr = 0;
				// ����������� 
				memcpy(&ServiceID, InputBuffer, 4);
				memcpy(&NewPtr,    (PVOID)((DWORD)InputBuffer+4), 4);
				zDbgPrint("ServiceID = %x\n", ServiceID);
				zDbgPrint("NewPtr = @%x\n", NewPtr);
				// �������� ������ ������� (��� ������ ���� � ��������� 0..ntoskrnl.ServiceLimit-1)
				if (((LONG)ServiceID >= 0) && (ServiceID < KeServiceDescriptorTable->ntoskrnl.ServiceLimit)) {
					__try {
						// ��������� ����������
						KIRQL OldIRQL = KeRaiseIrqlToDpcLevel();			 
						_asm cli
							DWORD OldCR0;	
						_asm {
							mov eax,CR0
								mov OldCR0,eax
								and eax,0xFFFEFFFF
								mov cr0, eax
						}
						// �������������� �������
						__try {
							KeServiceDescriptorTable->ntoskrnl.ServiceTable[ServiceID] = (NTPROC)NewPtr;
						} __except(EXCEPTION_EXECUTE_HANDLER) { // � ������ ������ ��������� ���������� 
						}
						_asm sti				   
							// �������������� WP ����
							_asm {
								mov eax,OldCR0
									mov cr0,eax
							}
							KeLowerIrql(OldIRQL);
					} __except(EXCEPTION_EXECUTE_HANDLER) { // � ������ ������ ��������� ���������� 
						_asm sti
					}
					dInfo = 4;
					ns = STATUS_SUCCESS;         
				}
				else
					ns = STATUS_DATA_ERROR; // ������� ������			
			}
			else
				ns = STATUS_BUFFER_TOO_SMALL; // ������� ������
		}

		// ***** ������ N ���� �� ��������� ������ *****
		if (IoControlCode == IOCTL_Z_READ_MEMORY) {
			zDbgPrint("Read Memory \n");
			__try {
				// �������� ������� ������ - ��� ������ ���� ��� DWORD - ����� � ������ ������
				if (InputBufferLength >= 8) {
					DWORD MemPtr, MemSize = 0;
					// ����������� 
					memcpy(&MemPtr, InputBuffer, 4);
					memcpy(&MemSize,    (PVOID)((DWORD)InputBuffer+4), 4);
					// ����� ���������� ����������
					zDbgPrint("MemPtr  = %x\n", MemPtr);
					zDbgPrint("MemSize = @%x\n", MemSize);
					// �������� ������� ������
					if (MemSize > 0 && MemSize <= OutputBufferLength) {
						// �������� ������������ ������� ������ � ���� ������ - ������ � ����� �������
						__try {
							// ������ ������ �� ��������� ������	
							memcpy(OutputBuffer, (PVOID)MemPtr, MemSize);
							// ������� ������� � ���� ��������� ����������
							dInfo = MemSize;
							ns = STATUS_SUCCESS;   
						} __except(EXCEPTION_EXECUTE_HANDLER) { 
							ns = STATUS_DATA_ERROR; 
						}					
					} 
					else 
						ns = STATUS_BUFFER_TOO_SMALL; // ������� ������
				} 
				else
					ns = STATUS_DATA_ERROR; // ������� ������			
			} __except(EXCEPTION_EXECUTE_HANDLER) {
				dInfo = 0; 
				ns = STATUS_DATA_ERROR;
			}
		}
		// ***** ������ N ���� �� ��������� ������ *****
		if (IoControlCode == IOCTL_Z_DUMP_MEMORY) {
			zDbgPrint("IOCTL_Z_DUMP_MEMORY \n");
			__try {
				// �������� ������� ������ - ��� ������ ���� ��� DWORD - ����� � ������ ������
				if (InputBufferLength >= 8) {
					DWORD MemPtr, MemSize = 0;
					// ����������� 
					memcpy(&MemPtr, InputBuffer, 4);
					memcpy(&MemSize,    (PVOID)((DWORD)InputBuffer+4), 4);
					// ����� ���������� ����������
					zDbgPrint("MemPtr  = %x\n", MemPtr);
					zDbgPrint("MemSize = @%x\n", MemSize);
					// �������� ������� ������
					if (MemSize > 0 && MemSize <= OutputBufferLength) {
						ns = DumpKernelMemory((PVOID)OutputBuffer, (PVOID)MemPtr, MemSize);							
						if (ns == STATUS_SUCCESS)
							dInfo = MemSize;
					} 
					else 
						ns = STATUS_BUFFER_TOO_SMALL; // ������� ������
				} 
				else
					ns = STATUS_DATA_ERROR; // ������� ������			
			} __except(EXCEPTION_EXECUTE_HANDLER) {
				dInfo = 0; 
				ns = STATUS_DATA_ERROR;
			}
		}
		// ***** ������ N ���� �� ��������� ������ *****
		if (IoControlCode == IOCTL_Z_WRITE_MEMORY) {
			zDbgPrint("Write Memory \n");
			__try {
				// �������� ������� ������ - ��� ������ ���� ��� DWORD - ����� � ������ ������
				if (InputBufferLength > 8) {
					DWORD MemPtr, MemSize = 0;
					// ����������� 
					memcpy(&MemPtr, InputBuffer, 4);
					memcpy(&MemSize,    (PVOID)((DWORD)InputBuffer+4), 4);
					// ����� ���������� ����������
					zDbgPrint("MemPtr  = %x\n", MemPtr);
					zDbgPrint("MemSize = @%x\n", MemSize);
					// �������� ������� ������
					if (MemSize > 0 && MemSize <= InputBufferLength-8) {
						// �������� ������������ ������� ������ � ���� ������ - ������ � ����� �������
						__try {
							// ��������� ����������
							KIRQL OldIRQL = KeRaiseIrqlToDpcLevel();			 
							_asm cli
								DWORD OldCR0;	
							_asm {
								mov eax,CR0
									mov OldCR0,eax
									and eax,0xFFFEFFFF
									mov cr0, eax
							}
							// ������ ������ �� ��������� ������	
							memcpy((PVOID)MemPtr, (PVOID)((DWORD)InputBuffer+8),  MemSize);
							_asm sti				   
								// �������������� WP ����
								_asm {
									mov eax,OldCR0
										mov cr0,eax
								}

								KeLowerIrql(OldIRQL);
								// ������� ������� � ���� ��������� ����������
								dInfo = 0;
								ns = STATUS_SUCCESS;   
						} __except(EXCEPTION_EXECUTE_HANDLER) { 
							_asm sti
								ns = STATUS_DATA_ERROR; 
						}					
					} 
					else 
						ns = STATUS_BUFFER_TOO_SMALL; // ������� ������
				} 
				else
					ns = STATUS_DATA_ERROR; // ������� ������			
			} __except(EXCEPTION_EXECUTE_HANDLER) {
				dInfo = 0; 
				ns = STATUS_DATA_ERROR;
			}
		}
		// ***** ��������� �������� 176h ���������� *****
		if (IoControlCode == IOCTL_Z_GET_CPU_176REG) {
			zDbgPrint("CPU_176REG \n");			
			if (OutputBufferLength >= 4) {
				__try {
					__asm {
						pushad
							mov ecx, 0x176
							rdmsr
							mov SysCallPTR, eax		
							popad
					}
					// ������� ���������� ������	
					memcpy(OutputBuffer, &SysCallPTR, 4);
					dInfo = 4;
					ns = STATUS_SUCCESS;   
				} __except(EXCEPTION_EXECUTE_HANDLER) {
					dInfo = 0; 
					ns = STATUS_DATA_ERROR;
				}
			} 
			else 
				ns = STATUS_BUFFER_TOO_SMALL; // ������� ������

		}
		// ***** ��������� �������� 176h ���������� *****
		if (IoControlCode == IOCTL_Z_SET_CPU_176REG) {
			zDbgPrint("SET CPU_176REG \n");
			if (InputBufferLength >= 4) {
				DWORD SyscallPTR;
				memcpy(&SyscallPTR, InputBuffer, 4);
				zDbgPrint("SyscallPTR = %x \n", SyscallPTR);
				__asm {
					pushad
						mov ecx, 0x176
						mov eax, SyscallPTR
						xor edx, edx
						cli
						wrmsr
						sti
						popad
				}
				ns = STATUS_SUCCESS;   
			} 
			else 
				ns = STATUS_BUFFER_TOO_SMALL; // ������� ������

		}
		// ***** ��������� IDT *****
		if (IoControlCode == IOCTL_Z_GET_IDT) {
			zDbgPrint("GET IDT \n");
			if (OutputBufferLength >= sizeof(IDT)) {
				IDT Idt;
				__asm {
						pushad
						sidt [Idt]
						popad
				}
				// ������� ��������� IDT
				memcpy(OutputBuffer, &Idt, sizeof(IDT));
				dInfo = sizeof(IDT);
				ns = STATUS_SUCCESS;   
			} 
			else 
				ns = STATUS_BUFFER_TOO_SMALL; // ������� ������

		}
	}
	// ���������� IRP �������
	pIrp->IoStatus.Status      = ns;
	pIrp->IoStatus.Information = dInfo;

	return ns;  
}
//--------------------------------------------------------------------------------------------------------
#endif
