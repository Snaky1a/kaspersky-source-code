
/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
    KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
    PURPOSE.

Module Name:

    filter.c

Abstract:

    This module shows how to a write a generic filter driver.

Environment:

    Kernel mode

Revision History:

    Fixed bugs - March 15, 2001

    Added Ioctl interface - Aug 16, 2001
    
    Updated to use IoCreateDeviceSecure function - Sep 17, 2002

    Updated to use RemLocks - Oct 29, 2002
    
--*/

#include "filter.h"
#include "devrul.h"
#include "struct.h"
#include "ioctl.h"
#include "const.h"
#include "tags.h"
#include "debug.h"

#include "filter.tmh"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, FilterAddDevice)
#pragma alloc_text (PAGE, FilterDispatchPnp)
#pragma alloc_text (PAGE, FilterUnload)
#endif

//
// Define IOCTL_INTERFACE in your sources file if  you want your
// app to have private interaction with the filter driver. Read KB Q262305
// for more information.
//

#ifdef IOCTL_INTERFACE

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, FilterCreateControlObject)
#pragma alloc_text (PAGE, FilterDeleteControlObject)
#pragma alloc_text (PAGE, FilterDispatchIo)
#endif
FAST_MUTEX ControlMutex;
ULONG InstanceCount = 0;
//PDEVICE_OBJECT Globals.m_FilterControlDeviceObject;

#endif

//#pragma intrinsic( memcmp )

GLOBAL_DATA_KLFLTDEV KLFltDev_Globals;
NTSTATUS
DriverEntry(
    __in PDRIVER_OBJECT  DriverObject,
    __in PUNICODE_STRING RegistryPath
    )
/*++

Routine Description:

    Installable driver initialization entry point.
    This entry point is called directly by the I/O system.

Arguments:

    DriverObject - pointer to the driver object

    RegistryPath - pointer to a unicode string representing the path,
                   to driver-specific key in the registry.

Return Value:

    STATUS_SUCCESS if successful,
    STATUS_UNSUCCESSFUL otherwise.

--*/
{
    NTSTATUS            status = STATUS_SUCCESS;
    ULONG               ulIndex;
    PDRIVER_DISPATCH  * dispatch;

    UNREFERENCED_PARAMETER (RegistryPath);

    DebugPrint (("Entered the Driver Entry\n"));


    //
    // Create dispatch points
    //
	
	for (ulIndex = 0, dispatch = DriverObject->MajorFunction;
         ulIndex <= IRP_MJ_MAXIMUM_FUNCTION;
         ulIndex++, dispatch++) {

        *dispatch = FilterPass;
    }

    DriverObject->MajorFunction[IRP_MJ_PNP]            = FilterDispatchPnp;
    DriverObject->MajorFunction[IRP_MJ_POWER]          = FilterDispatchPower;
    DriverObject->DriverExtension->AddDevice           = FilterAddDevice;
    DriverObject->DriverUnload                         = FilterUnload;

#ifdef IOCTL_INTERFACE
    //
    // Set the following dispatch points as we will be doing
    // something useful to these requests instead of just
    // passing them down. 
    // 
    
    DriverObject->MajorFunction[IRP_MJ_CREATE]     = 
    DriverObject->MajorFunction[IRP_MJ_CLOSE]      = 
    DriverObject->MajorFunction[IRP_MJ_CLEANUP]    = 
    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = 
                                                        FilterDispatchIo;
    //
    // Mutex is to synchronize multiple threads creating & deleting 
    // control deviceobjects. 
    //
    ExInitializeFastMutex(&ControlMutex);
	
	InitDevRul();
	GlobalInitDeviceList();
	FilterCreateControlObject( RegistryPath, DriverObject );
	
	RebuildDevRulListFromReg( RegistryPath );

    
#endif
	
#ifndef WIN2K
	WPP_INIT_TRACING( DriverObject, RegistryPath );
#endif // WIN2K

	//status = InitDevRul();

    return status;
}

NTSTATUS
GetClassGuidName(PDEVICE_OBJECT PhysicalDeviceObject, PWCHAR *pwcGuidName)
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	ULONG retSize = 0;
	*pwcGuidName = NULL;
	
	status = IoGetDeviceProperty(
		PhysicalDeviceObject, 
		DevicePropertyClassGuid, 
		0,
		*pwcGuidName,
		&retSize
		);

	if ( status != STATUS_BUFFER_TOO_SMALL )
		return status;

	*pwcGuidName = ExAllocatePoolWithTag( PagedPool, retSize, tag_filter5 );


	status = IoGetDeviceProperty(
		PhysicalDeviceObject, 
		DevicePropertyClassGuid, 
		retSize,
		*pwcGuidName,
		&retSize
		);

	if ( !NT_SUCCESS( status ) )
	{
		ExFreePool( *pwcGuidName );
		*pwcGuidName = NULL;
	}

	return status;
}

int
TypeCompare ( PWCHAR wcGuidType, PWCHAR wcDevType )
{
	ULONG wcGuidTypeLen;
	ULONG wcDevTypeLen;

	wcGuidTypeLen = (ULONG)wcslen(wcGuidType);
	wcDevTypeLen = (ULONG)wcslen(wcDevType);

	if ( wcDevTypeLen > wcGuidTypeLen )
		return 1;

	return _wcsnicmp( wcGuidType, wcDevType, wcDevTypeLen );
}

PWCHAR
GetDevType(PWCHAR wcGuidType)
{
	
	if ( TypeCompare(wcGuidType, DEV_TYPE_USB_CLASS_RESERVED) == 0 )
	  return DEV_TYPE_USB_CLASS_RESERVED;

	if ( TypeCompare(wcGuidType, DEV_TYPE_USB_CLASS_AUDIO) == 0 )
		return DEV_TYPE_USB_CLASS_AUDIO;
 
	if ( TypeCompare(wcGuidType, DEV_TYPE_USB_CLASS_COMMUNICATIONS) == 0 )
		return DEV_TYPE_USB_CLASS_COMMUNICATIONS;
	
	if ( TypeCompare(wcGuidType, DEV_TYPE_USB_CLASS_HUMAN_INTERFACE) == 0 )
		return DEV_TYPE_USB_CLASS_HUMAN_INTERFACE;
	
	if ( TypeCompare(wcGuidType, DEV_TYPE_USB_CLASS_MONITOR) == 0 )		
		return DEV_TYPE_USB_CLASS_MONITOR;
	
	if ( TypeCompare(wcGuidType, DEV_TYPE_USB_CLASS_PHYSICAL_INTERFACE) == 0 )
		return DEV_TYPE_USB_CLASS_PHYSICAL_INTERFACE;
 
	if ( TypeCompare(wcGuidType, DEV_TYPE_USB_CLASS_POWER) == 0 )
		return DEV_TYPE_USB_CLASS_POWER;
	
	if ( TypeCompare(wcGuidType, DEV_TYPE_USB_CLASS_PRINTER) == 0 )
		return DEV_TYPE_USB_CLASS_PRINTER;

	if ( TypeCompare(wcGuidType, DEV_TYPE_USB_CLASS_STORAGE) == 0 )
		return DEV_TYPE_USB_CLASS_STORAGE;

	if ( TypeCompare(wcGuidType, DEV_TYPE_USB_CLASS_HUB) == 0 )
		return DEV_TYPE_USB_CLASS_HUB;
 
	if ( TypeCompare(wcGuidType, DEV_TYPE_USB_CLASS_VENDOR_SPECIFIC) == 0 )	
		return DEV_TYPE_USB_CLASS_VENDOR_SPECIFIC;
	

	return DEV_TYPE_OTHER;

}

NTSTATUS
GetClassGuidType( PDEVICE_OBJECT PhysicalDeviceObject, PWCHAR *pwcGuidType )
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	ULONG retSize = 0;
	PWCHAR buf = NULL;
		
	PWCHAR wcdevType;
	
	status = IoGetDeviceProperty(
		PhysicalDeviceObject, 
		DevicePropertyCompatibleIDs, 
		0,
		buf,
		&retSize
		);

	if ( status != STATUS_BUFFER_TOO_SMALL )
	{	
		*pwcGuidType =NULL;
		return status;
	}

	buf = ExAllocatePoolWithTag( PagedPool, retSize, tag_filter5 );
	if (!buf)
	{
		*pwcGuidType =NULL;
		return STATUS_NO_MEMORY;
	}


	status = IoGetDeviceProperty(
		PhysicalDeviceObject, 
		DevicePropertyCompatibleIDs, 
		retSize,
		buf,
		&retSize
		);

	if ( !NT_SUCCESS( status ) )
	{
		ExFreePool( buf );
		buf = NULL;
		return status;
	}
	
	wcdevType = GetDevType(buf);
	ExFreePool( buf );
	buf = NULL;
	
	retSize = (ULONG)( (wcslen(wcdevType)+1)*sizeof(WCHAR) );
	*pwcGuidType = ExAllocatePoolWithTag(PagedPool, retSize, tag_filter6 );
	if ( !(*pwcGuidType) )
	{
		return STATUS_NO_MEMORY;
	}
	
	memset(*pwcGuidType, 0, retSize );

	memcpy( *pwcGuidType, wcdevType, retSize );

	return STATUS_SUCCESS;
}


NTSTATUS
FilterAddDevice(
    __in PDRIVER_OBJECT DriverObject,
    __in PDEVICE_OBJECT PhysicalDeviceObject
    )
/*++

Routine Description:

    The Plug & Play subsystem is handing us a brand new PDO, for which we
    (by means of INF registration) have been asked to provide a driver.

    We need to determine if we need to be in the driver stack for the device.
    Create a function device object to attach to the stack
    Initialize that device object
    Return status success.

    Remember: We can NOT actually send ANY non pnp IRPS to the given driver
    stack, UNTIL we have received an IRP_MN_START_DEVICE.

Arguments:

    DeviceObject - pointer to a device object.

    PhysicalDeviceObject -  pointer to a device object created by the
                            underlying bus driver.

Return Value:

    NT status code.

--*/
{
    NTSTATUS                status = STATUS_SUCCESS;
    PDEVICE_OBJECT          deviceObject = NULL;
    PDEVICE_EXTENSION       deviceExtension;
    ULONG                   deviceType = FILE_DEVICE_UNKNOWN;

    PAGED_CODE ();


    //
    // IoIsWdmVersionAvailable(1, 0x20) returns TRUE on os after Windows 2000.
    //
    
	//return STATUS_SUCCESS;
	if (!IoIsWdmVersionAvailable(1, 0x20)) {
        //
        // Win2K system bugchecks if the filter attached to a storage device
        // doesn't specify the same DeviceType as the device it's attaching
        // to. This bugcheck happens in the filesystem when you disable
        // the devicestack whose top level deviceobject doesn't have a VPB.
        // To workaround we will get the toplevel object's DeviceType and
        // specify that in IoCreateDevice.
        //
        deviceObject = IoGetAttachedDeviceReference(PhysicalDeviceObject);
        deviceType = deviceObject->DeviceType;
        ObDereferenceObject(deviceObject);
    }

    //
    // Create a filter device object.
    //

    status = IoCreateDevice (DriverObject,
                             sizeof (DEVICE_EXTENSION),
                             NULL,  // No Name
                             deviceType,
                             FILE_DEVICE_SECURE_OPEN,
                             FALSE,
                             &deviceObject);


    if (!NT_SUCCESS (status)) {
        //
        // Returning failure here prevents the entire stack from functioning,
        // but most likely the rest of the stack will not be able to create
        // device objects either, so it is still OK.
        //
        return status;
    }

    DebugPrint (("AddDevice PDO (0x%p) FDO (0x%p)\n",
                    PhysicalDeviceObject, deviceObject));

    

	deviceExtension = (PDEVICE_EXTENSION) deviceObject->DeviceExtension;

    deviceExtension->Type = DEVICE_TYPE_FIDO;
	
	{
		PWCHAR wcStr;
		
		memset ( &deviceExtension->DevName, 0, sizeof(DEVICE_NAME) );
		status = GetClassGuidName( PhysicalDeviceObject, &wcStr );
		if (!NT_SUCCESS (status)) 
		{
			if (wcStr)
				ExFreePool(wcStr);
			
			IoDeleteDevice(deviceObject);
			
			//���� �� ����� �������� guid, �� �� ��������� ����������, � ������� ������ ���������� ��������
			return STATUS_SUCCESS;
		}
		
		RtlInitUnicodeString(&deviceExtension->DevName.usGuid, wcStr);
		
		status = GetClassGuidType( PhysicalDeviceObject, &wcStr );
		if (!NT_SUCCESS (status)) 
		{
			
			ULONG wcStrSize;
			wcStrSize = (ULONG)( wcslen(DEV_TYPE_OTHER)*sizeof(WCHAR)+sizeof(WCHAR) );
			
			if (wcStr)
				ExFreePool(wcStr);
			
			wcStr = ExAllocatePoolWithTag ( PagedPool, wcStrSize, tag_filter9 );
			if (!wcStr)
			{
				if ( deviceExtension->DevName.usGuid.Buffer )
					ExFreePool( deviceExtension->DevName.usGuid.Buffer );
			
				IoDeleteDevice(deviceObject);
				return STATUS_SUCCESS;
			}
			
			memset( wcStr, 0, wcStrSize  );
			RtlCopyMemory( wcStr, DEV_TYPE_OTHER, wcStrSize );
		}
		
		RtlInitUnicodeString(&deviceExtension->DevName.usDeviceType, wcStr);

		status = InsertDeviceList( &deviceExtension->DevName );
		if (!NT_SUCCESS (status)) 
		{
			if ( deviceExtension->DevName.usGuid.Buffer )
				ExFreePool( deviceExtension->DevName.usGuid.Buffer );
			
			if ( deviceExtension->DevName.usGuid.Buffer )
				ExFreePool( deviceExtension->DevName.usDeviceType.Buffer );
			
			IoDeleteDevice(deviceObject);
			
			//���� �� ����� �������� �������, �� �� ��������� ����������, � ������� ������ ���������� ��������
			return STATUS_SUCCESS;
		}

	}
    deviceExtension->NextLowerDriver = IoAttachDeviceToDeviceStack (
                                       deviceObject,
                                       PhysicalDeviceObject);
    //
    // Failure for attachment is an indication of a broken plug & play system.
    //

    if (NULL == deviceExtension->NextLowerDriver) {

        IoDeleteDevice(deviceObject);
        return STATUS_UNSUCCESSFUL;
    }

    deviceObject->Flags |= deviceExtension->NextLowerDriver->Flags &
                            (DO_BUFFERED_IO | DO_DIRECT_IO |
                            DO_POWER_PAGABLE );


    deviceObject->DeviceType = deviceExtension->NextLowerDriver->DeviceType;

    deviceObject->Characteristics =
                          deviceExtension->NextLowerDriver->Characteristics;

    deviceExtension->Self = deviceObject;

    //
    // Let us use remove lock to keep count of IRPs so that we don't 
    // deteach and delete our deviceobject until all pending I/Os in our
    // devstack are completed. Remlock is required to protect us from
    // various race conditions where our driver can get unloaded while we
    // are still running dispatch or completion code.
    //
    
    IoInitializeRemoveLock (&deviceExtension->RemoveLock , 
                            POOL_TAG,
                            1, // MaxLockedMinutes 
                            100); // HighWatermark, this parameter is 
                                // used only on checked build. Specifies 
                                // the maximum number of outstanding 
                                // acquisitions allowed on the lock
                                

    //
    // Set the initial state of the Filter DO
    //

    INITIALIZE_PNP_STATE(deviceExtension);

    DebugPrint(("AddDevice: %p to %p->%p \n", deviceObject,
                       deviceExtension->NextLowerDriver,
                       PhysicalDeviceObject));

	deviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

    return STATUS_SUCCESS;

}


NTSTATUS
FilterPass (
    __in PDEVICE_OBJECT DeviceObject,
    __in PIRP Irp
    )
/*++

Routine Description:

    The default dispatch routine.  If this driver does not recognize the
    IRP, then it should send it down, unmodified.
    If the device holds iris, this IRP must be queued in the device extension
    No completion routine is required.

    For demonstrative purposes only, we will pass all the (non-PnP) Irps down
    on the stack (as we are a filter driver). A real driver might choose to
    service some of these Irps.

    As we have NO idea which function we are happily passing on, we can make
    NO assumptions about whether or not it will be called at raised IRQL.
    For this reason, this function must be in put into non-paged pool
    (aka the default location).

Arguments:

   DeviceObject - pointer to a device object.

   Irp - pointer to an I/O Request Packet.

Return Value:

      NT status code

--*/
{
    PDEVICE_EXTENSION           deviceExtension;
    NTSTATUS    status;
    
    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
    status = IoAcquireRemoveLock (&deviceExtension->RemoveLock, Irp);
    if (!NT_SUCCESS (status)) {
        Irp->IoStatus.Status = status;
        IoCompleteRequest (Irp, IO_NO_INCREMENT);
        return status;
    }

   IoSkipCurrentIrpStackLocation (Irp);
   status = IoCallDriver (deviceExtension->NextLowerDriver, Irp);
   IoReleaseRemoveLock(&deviceExtension->RemoveLock, Irp); 
   return status;
}


NTSTATUS
FilterDispatchPnp (
    __in PDEVICE_OBJECT DeviceObject,
    __in PIRP Irp
    )
/*++

Routine Description:

    The plug and play dispatch routines.

    Most of these the driver will completely ignore.
    In all cases it must pass on the IRP to the lower driver.

Arguments:

   DeviceObject - pointer to a device object.

   Irp - pointer to an I/O Request Packet.

Return Value:

      NT status code

--*/
{
    PDEVICE_EXTENSION           deviceExtension;
    PIO_STACK_LOCATION         irpStack;
    NTSTATUS                            status;
    KEVENT                               event;

    PAGED_CODE();

    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
    irpStack = IoGetCurrentIrpStackLocation(Irp);

    DebugPrint(("FilterDO %s IRP:0x%p \n",
                PnPMinorFunctionString(irpStack->MinorFunction), Irp));

   status = IoAcquireRemoveLock (&deviceExtension->RemoveLock, Irp);
    if (!NT_SUCCESS (status)) {
        Irp->IoStatus.Status = status;
        IoCompleteRequest (Irp, IO_NO_INCREMENT);
        return status;
    }
    

    switch (irpStack->MinorFunction) {
    case IRP_MN_START_DEVICE:

        //
        // The device is starting.
        // We cannot touch the device (send it any non pnp irps) until a
        // start device has been passed down to the lower drivers.
        //
        KeInitializeEvent(&event, NotificationEvent, FALSE);
        IoCopyCurrentIrpStackLocationToNext(Irp);
        IoSetCompletionRoutine(Irp,
                               (PIO_COMPLETION_ROUTINE) FilterStartCompletionRoutine,
                               &event,
                               TRUE,
                               TRUE,
                               TRUE);

        status = IoCallDriver(deviceExtension->NextLowerDriver, Irp);
        
        //
        // Wait for lower drivers to be done with the Irp. Important thing to
        // note here is when you allocate memory for an event in the stack  
        // you must do a KernelMode wait instead of UserMode to prevent 
        // the stack from getting paged out.
        //
        if (status == STATUS_PENDING) {

           KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);          
           status = Irp->IoStatus.Status;
        }
		
		if ( !IsAllowAccess( deviceExtension->DevName.usGuid, deviceExtension->DevName.usDeviceType ) )
			status = STATUS_ACCESS_DENIED;
		        
		if (NT_SUCCESS (status)) {

            //
            // As we are successfully now back, we will
            // first set our state to Started.
            //

            SET_NEW_PNP_STATE(deviceExtension, Started);

            //
            // On the way up inherit FILE_REMOVABLE_MEDIA during Start.
            // This characteristic is available only after the driver stack is started!.
            //
            if (deviceExtension->NextLowerDriver->Characteristics & FILE_REMOVABLE_MEDIA) {

                DeviceObject->Characteristics |= FILE_REMOVABLE_MEDIA;
            }
			
		}
        
        Irp->IoStatus.Status = status;
        IoCompleteRequest (Irp, IO_NO_INCREMENT);
        IoReleaseRemoveLock(&deviceExtension->RemoveLock, Irp); 
        return status;

    case IRP_MN_REMOVE_DEVICE:

        //
        // Wait for all outstanding requests to complete
        //
        DebugPrint(("Waiting for outstanding requests\n"));
        
		IoReleaseRemoveLockAndWait(&deviceExtension->RemoveLock, Irp);

        IoSkipCurrentIrpStackLocation(Irp);

        status = IoCallDriver(deviceExtension->NextLowerDriver, Irp);

        SET_NEW_PNP_STATE(deviceExtension, Deleted);
        
		RemItemFromDeviceList ( &deviceExtension->DevName );
		ExFreePool (deviceExtension->DevName.usDeviceType.Buffer);
		ExFreePool (deviceExtension->DevName.usGuid.Buffer);

        IoDetachDevice(deviceExtension->NextLowerDriver);
        IoDeleteDevice(DeviceObject);
        return status;


    case IRP_MN_QUERY_STOP_DEVICE:
        SET_NEW_PNP_STATE(deviceExtension, StopPending);
        status = STATUS_SUCCESS;
        break;

    case IRP_MN_CANCEL_STOP_DEVICE:

        //
        // Check to see whether you have received cancel-stop
        // without first receiving a query-stop. This could happen if someone
        // above us fails a query-stop and passes down the subsequent
        // cancel-stop.
        //

        if (StopPending == deviceExtension->DevicePnPState)
        {
            //
            // We did receive a query-stop, so restore.
            //
            RESTORE_PREVIOUS_PNP_STATE(deviceExtension);
        }
        status = STATUS_SUCCESS; // We must not fail this IRP.
        break;

    case IRP_MN_STOP_DEVICE:
        SET_NEW_PNP_STATE(deviceExtension, Stopped);
        status = STATUS_SUCCESS;
        break;

    case IRP_MN_QUERY_REMOVE_DEVICE:

        SET_NEW_PNP_STATE(deviceExtension, RemovePending);
        status = STATUS_SUCCESS;
        break;

    case IRP_MN_SURPRISE_REMOVAL:

        SET_NEW_PNP_STATE(deviceExtension, SurpriseRemovePending);
        status = STATUS_SUCCESS;
        break;

    case IRP_MN_CANCEL_REMOVE_DEVICE:

        //
        // Check to see whether you have received cancel-remove
        // without first receiving a query-remove. This could happen if
        // someone above us fails a query-remove and passes down the
        // subsequent cancel-remove.
        //

        if (RemovePending == deviceExtension->DevicePnPState)
        {
            //
            // We did receive a query-remove, so restore.
            //
            RESTORE_PREVIOUS_PNP_STATE(deviceExtension);
        }

        status = STATUS_SUCCESS; // We must not fail this IRP.
        break;

    case IRP_MN_DEVICE_USAGE_NOTIFICATION:

        //
        // On the way down, pagable might become set. Mimic the driver
        // above us. If no one is above us, just set pagable.
        //
        if ((DeviceObject->AttachedDevice == NULL) ||
            (DeviceObject->AttachedDevice->Flags & DO_POWER_PAGABLE)) {

            DeviceObject->Flags |= DO_POWER_PAGABLE;
        }

        IoCopyCurrentIrpStackLocationToNext(Irp);

        IoSetCompletionRoutine(
            Irp,
            FilterDeviceUsageNotificationCompletionRoutine,
            NULL,
            TRUE,
            TRUE,
            TRUE
            );

        return IoCallDriver(deviceExtension->NextLowerDriver, Irp);

    default:
        //
        // If you don't handle any IRP you must leave the
        // status as is.
        //
        status = Irp->IoStatus.Status;

        break;
    }

    //
    // Pass the IRP down and forget it.
    //
    Irp->IoStatus.Status = status;
    IoSkipCurrentIrpStackLocation (Irp);
    status = IoCallDriver (deviceExtension->NextLowerDriver, Irp);
    IoReleaseRemoveLock(&deviceExtension->RemoveLock, Irp); 
    return status;
}

NTSTATUS
FilterStartCompletionRoutine(
    __in PDEVICE_OBJECT   DeviceObject,
    __in PIRP             Irp,
    __in PVOID            Context
    )
/*++
Routine Description:
    A completion routine for use when calling the lower device objects to
    which our filter deviceobject is attached.

Arguments:

    DeviceObject - Pointer to deviceobject
    Irp          - Pointer to a PnP Irp.
    Context      - NULL
Return Value:

    NT Status is returned.

--*/

{
    PKEVENT             event = (PKEVENT)Context;

    UNREFERENCED_PARAMETER (DeviceObject);

    //
    // If the lower driver didn't return STATUS_PENDING, we don't need to 
    // set the event because we won't be waiting on it. 
    // This optimization avoids grabbing the dispatcher lock, and improves perf.
    //
    if (Irp->PendingReturned == TRUE) {
        KeSetEvent (event, IO_NO_INCREMENT, FALSE);
    }

    //
    // The dispatch routine will have to call IoCompleteRequest
    //

    return STATUS_MORE_PROCESSING_REQUIRED;

}

NTSTATUS
FilterDeviceUsageNotificationCompletionRoutine(
    __in PDEVICE_OBJECT   DeviceObject,
    __in PIRP             Irp,
    __in PVOID            Context
    )
/*++
Routine Description:
    A completion routine for use when calling the lower device objects to
    which our filter deviceobject is attached.

Arguments:

    DeviceObject - Pointer to deviceobject
    Irp          - Pointer to a PnP Irp.
    Context      - NULL
Return Value:

    NT Status is returned.

--*/

{
    PDEVICE_EXTENSION       deviceExtension;

    UNREFERENCED_PARAMETER(Context);

    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;


    if (Irp->PendingReturned) {

        IoMarkIrpPending(Irp);
    }

    //
    // On the way up, pagable might become clear. Mimic the driver below us.
    //
    if (!(deviceExtension->NextLowerDriver->Flags & DO_POWER_PAGABLE)) {

        DeviceObject->Flags &= ~DO_POWER_PAGABLE;
    }

    IoReleaseRemoveLock(&deviceExtension->RemoveLock, Irp); 

    return STATUS_CONTINUE_COMPLETION;

}

NTSTATUS
FilterDispatchPower(
    __in PDEVICE_OBJECT    DeviceObject,
    __in PIRP              Irp
    )
/*++

Routine Description:

    This routine is the dispatch routine for power irps.

Arguments:

    DeviceObject - Pointer to the device object.

    Irp - Pointer to the request packet.

Return Value:

    NT Status code
--*/
{
    PDEVICE_EXTENSION   deviceExtension;
    NTSTATUS    status;
    
    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
    status = IoAcquireRemoveLock (&deviceExtension->RemoveLock, Irp);
    if (!NT_SUCCESS (status)) { // may be device is being removed.
        Irp->IoStatus.Status = status;
        PoStartNextPowerIrp(Irp);
        IoCompleteRequest (Irp, IO_NO_INCREMENT);
        return status;
    }

    PoStartNextPowerIrp(Irp);
    IoSkipCurrentIrpStackLocation(Irp);
    status = PoCallDriver(deviceExtension->NextLowerDriver, Irp);
    IoReleaseRemoveLock(&deviceExtension->RemoveLock, Irp); 
    return status;
}



VOID
FilterUnload(
    __in PDRIVER_OBJECT DriverObject
    )
/*++

Routine Description:

    Free all the allocated resources in DriverEntry, etc.

Arguments:

    DriverObject - pointer to a driver object.

Return Value:

    VOID.

--*/
{
    PAGED_CODE ();

    //
    // The device object(s) should be NULL now
    // (since we unload, all the devices objects associated with this
    // driver must be deleted.
    //
    ASSERT(DriverObject->DeviceObject == NULL);

    //
    // We should not be unloaded until all the devices we control
    // have been removed from our queue.
    //
	GlobalDoneDeviceList();
	DoneDevRul();
	
#ifdef IOCTL_INTERFACE
	FilterDeleteControlObject();
#endif

    DebugPrint (("unload\n"));

#ifndef WIN2K
	WPP_CLEANUP(KLFltDev_Globals.m_FilterControlDeviceObject->DriverObject);
#endif

    return;
}

#ifdef IOCTL_INTERFACE
NTSTATUS
FilterCreateControlObject(
    //__in PDEVICE_OBJECT    DeviceObject
	__in PUNICODE_STRING RegistryPath,
	__in PDRIVER_OBJECT  DriverObject
)
{
    UNICODE_STRING      ntDeviceName;
    UNICODE_STRING      symbolicLinkName;
    PCONTROL_DEVICE_EXTENSION   deviceExtension;
    NTSTATUS status = STATUS_UNSUCCESSFUL;
    UNICODE_STRING  sddlString;    

    PAGED_CODE();    

    //
    // Using unsafe function so that the IRQL remains at PASSIVE_LEVEL.
    // IoCreateDeviceSecure & IoCreateSymbolicLink must be called at
    // PASSIVE_LEVEL.
    //
    ExAcquireFastMutexUnsafe(&ControlMutex);

    //
    // If this is a first instance of the device, then create a controlobject
    // and register dispatch points to handle ioctls.
    //
    if (1 == ++InstanceCount)
    {

        //
        // Initialize the unicode strings
        //
        RtlInitUnicodeString(&ntDeviceName, NTDEVICE_NAME_STRING);
        RtlInitUnicodeString(&symbolicLinkName, SYMBOLIC_NAME_STRING);

        //
        // Initialize a security descriptor string. Refer to SDDL docs in the SDK
        // for more info.
        //
        RtlInitUnicodeString( &sddlString, L"D:P(A;;GA;;;SY)(A;;GA;;;BA)");

        //
        // Create a named deviceobject so that applications or drivers
        // can directly talk to us without going throuhg the entire stack.
        // This call could fail if there are not enough resources or
        // another deviceobject of same name exists (name collision).
        // Let us use the new IoCreateDeviceSecure and specify a security
        // descriptor (SD) that allows only System and Admin groups to access the 
        // control device. Let us also specify a unique guid to allow administrators 
        // to change the SD if he desires to do so without changing the driver. 
        // The SD will be stored in 
        // HKLM\SYSTEM\CCSet\Control\Class\<GUID>\Properties\Security.
        // An admin can override the SD specified in the below call by modifying
        // the registry.
        //
        
        /*status = IoCreateDeviceSecure(DriverObject,
                                sizeof(CONTROL_DEVICE_EXTENSION),
                                &ntDeviceName,
                                FILE_DEVICE_UNKNOWN,
                                FILE_DEVICE_SECURE_OPEN,
                                FALSE, 
                                &sddlString,
                                (LPCGUID)&GUID_SD_FILTER_CONTROL_OBJECT,
                                &ControlDeviceObject);
		*/

		status = IoCreateDevice(
			DriverObject,
			sizeof(CONTROL_DEVICE_EXTENSION),
			&ntDeviceName,
			FILE_DEVICE_UNKNOWN,
			0,
			FALSE,
			&KLFltDev_Globals.m_FilterControlDeviceObject
			);


        if ( NT_SUCCESS( status ) ) {

            KLFltDev_Globals.m_FilterControlDeviceObject->Flags |= DO_BUFFERED_IO;

            status = IoCreateSymbolicLink( &symbolicLinkName, &ntDeviceName );

            if ( !NT_SUCCESS( status )) {
                IoDeleteDevice(KLFltDev_Globals.m_FilterControlDeviceObject);
                DebugPrint(("IoCreateSymbolicLink failed %x\n", status));
                goto End;
            }

            deviceExtension = KLFltDev_Globals.m_FilterControlDeviceObject->DeviceExtension;
            deviceExtension->Type = DEVICE_TYPE_CDO;
            deviceExtension->ControlData = NULL;
            deviceExtension->Deleted = FALSE;
            
			memset( &deviceExtension->usRegistryPath, 0, sizeof(UNICODE_STRING) );
			deviceExtension->usRegistryPath.Buffer = ExAllocatePoolWithTag( PagedPool, RegistryPath->Length, tag_filter4 );
			if ( deviceExtension->usRegistryPath.Buffer )
			{
				deviceExtension->usRegistryPath.Length = 0;
				deviceExtension->usRegistryPath.MaximumLength = RegistryPath->MaximumLength;
				RtlCopyUnicodeString( &deviceExtension->usRegistryPath,  RegistryPath );
			}

            KLFltDev_Globals.m_FilterControlDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;
            
        }else {
            DebugPrint(("IoCreateDevice failed %x\n", status));
        }
    }

End:
    
    ExReleaseFastMutexUnsafe(&ControlMutex); 
    return status;
    
}

VOID
FilterDeleteControlObject(
)
{
    UNICODE_STRING      symbolicLinkName;
    PCONTROL_DEVICE_EXTENSION   deviceExtension;

    PAGED_CODE();    

    ExAcquireFastMutexUnsafe (&ControlMutex);

    //
    // If this is the last instance of the device then delete the controlobject
    // and symbolic link to enable the pnp manager to unload the driver.
    //
    
    if (!(--InstanceCount) && KLFltDev_Globals.m_FilterControlDeviceObject)
    {
        RtlInitUnicodeString(&symbolicLinkName, SYMBOLIC_NAME_STRING);
        deviceExtension = KLFltDev_Globals.m_FilterControlDeviceObject->DeviceExtension;
        deviceExtension->Deleted = TRUE;

		ExFreePool( deviceExtension->usRegistryPath.Buffer );
        
		IoDeleteSymbolicLink(&symbolicLinkName);
        IoDeleteDevice(KLFltDev_Globals.m_FilterControlDeviceObject);
        KLFltDev_Globals.m_FilterControlDeviceObject = NULL;
    }

    ExReleaseFastMutexUnsafe (&ControlMutex); 

}


#define IS_ALIGNED(_pointer, _alignment)                        \
	((((ULONG_PTR) (_pointer)) & ((_alignment) - 1)) == 0)

NTSTATUS
Comm_CheckOutputBuffer (
						__in PVOID OutputBuffer,
						__in ULONG OutputBufferSize,
						__in ULONG MinSize
						)
{
	if (!OutputBuffer)
		return STATUS_INVALID_PARAMETER;

#if defined(_WIN64)
	if (IoIs32bitProcess( NULL ))
	{
		if (!IS_ALIGNED(OutputBuffer, sizeof(ULONG)))
		{
			//_dbg_break_;
			//return STATUS_DATATYPE_MISALIGNMENT;
			//DoTraceEx( TRACE_LEVEL_ERROR, DC_COMM, "OutputBuffer not aligned %p",  OutputBuffer );
		}
	}
	else
	{
#endif
		if (!IS_ALIGNED(OutputBuffer, sizeof(PVOID)))
		{
			//_dbg_break_;
			//return STATUS_DATATYPE_MISALIGNMENT;
			//DoTraceEx( TRACE_LEVEL_ERROR, DC_COMM, "OutputBuffer not aligned %p",  OutputBuffer );
		}
#if defined(_WIN64)
	}
#endif

	if (OutputBufferSize < MinSize)
		return STATUS_BUFFER_TOO_SMALL;

	return STATUS_SUCCESS;
}

NTSTATUS
Comm_CopyDataToUserBuffer (
						   __in PVOID OutputBuffer,
						   __in ULONG OutputBufferSize,
						   __in PVOID pSource,
						   __in ULONG SourceLen,
						   __inout PULONG ReturnOutputBufferLength
						   )
{
	NTSTATUS status = STATUS_BUFFER_TOO_SMALL;

	*ReturnOutputBufferLength = 0;
	if (!OutputBuffer)
	{
		return STATUS_INVALID_PARAMETER;
	}

	if (OutputBufferSize < SourceLen)
		return STATUS_BUFFER_TOO_SMALL;

	__try {
		memcpy( OutputBuffer, pSource, SourceLen );
		*ReturnOutputBufferLength = SourceLen;
		status = STATUS_SUCCESS;
	} 
	__except( EXCEPTION_EXECUTE_HANDLER ) {
		status = GetExceptionCode();
	}

	return status;
}

NTSTATUS
Comm_CopyUserBufferToInternal (
							   __in PVOID pInternalPtr,
							   __in PVOID pUserBuffer,
							   __in ULONG Size
							   )
{
	NTSTATUS status = STATUS_SUCCESS;

	__try {
		memcpy( pInternalPtr, pUserBuffer, Size );
	} 
	__except( EXCEPTION_EXECUTE_HANDLER ) {
		status = GetExceptionCode();
		_dbg_break_;
	}
	return status;
}

NTSTATUS
Comm_GetIncomeString (
	__in PVOID pStartPtr,
	__in USHORT StrLen,
	__out PWCHAR* ppwchStr
)
{
	NTSTATUS status = STATUS_NO_MEMORY;
	*ppwchStr = NULL;

	*ppwchStr = ExAllocatePoolWithTag( PagedPool, StrLen, tag_filter1 );
	if (*ppwchStr)
	{
		status = Comm_CopyUserBufferToInternal( *ppwchStr, pStartPtr, StrLen );
		if (!NT_SUCCESS( status ))
		{
			ExFreePool( *ppwchStr );
			*ppwchStr=NULL;
		}
	}

	return status;
}


NTSTATUS
FilterDispatchIo(
    __in PDEVICE_OBJECT    DeviceObject,
    __in PIRP              Irp
    )
/*++

Routine Description:

    This routine is the dispatch routine for non passthru irps.
    We will check the input device object to see if the request
    is meant for the control device object. If it is, we will
    handle and complete the IRP, if not, we will pass it down to 
    the lower driver.
    
Arguments:

    DeviceObject - Pointer to the device object.

    Irp - Pointer to the request packet.

Return Value:

    NT Status code
--*/
{
    PIO_STACK_LOCATION  irpStack;
    NTSTATUS            status;
    PCONTROL_DEVICE_EXTENSION   deviceExtension;
    PCOMMON_DEVICE_DATA commonData;
	
	PVOID               InputBuffer;
	PVOID               OutputBuffer;
	ULONG               InputBufferSize;
	ULONG               OutputBufferSize;
	PIO_STATUS_BLOCK	IoStatus;

    PAGED_CODE();

   commonData = (PCOMMON_DEVICE_DATA)DeviceObject->DeviceExtension;
   

   IoStatus=&Irp->IoStatus;

   
   irpStack = IoGetCurrentIrpStackLocation(Irp);

   InputBuffer      = Irp->AssociatedIrp.SystemBuffer;
   InputBufferSize  = irpStack->Parameters.DeviceIoControl.InputBufferLength;
   OutputBuffer     = Irp->AssociatedIrp.SystemBuffer;
   OutputBufferSize = irpStack->Parameters.DeviceIoControl.OutputBufferLength;

    //
    // Please note that this is a common dispatch point for controlobject and
    // filter deviceobject attached to the pnp stack. 
    //
    if ( commonData->Type == DEVICE_TYPE_FIDO ) {
        //
        // We will just  the request down as we are not interested in handling
        // requests that come on the PnP stack.
        //
        return FilterPass(DeviceObject, Irp);    
    }
 
    ASSERT(commonData->Type == DEVICE_TYPE_CDO);

    deviceExtension = (PCONTROL_DEVICE_EXTENSION)DeviceObject->DeviceExtension;
    
    //
    // Else this is targeted at our control deviceobject so let's handle it.
    // Here we will handle the IOCTl requests that come from the app.
    // We don't have to worry about acquiring remlocks for I/Os that come 
    // on our control object because the I/O manager takes reference on our 
    // deviceobject when it initiates a request to our device and that keeps
    // our driver from unloading when we have pending I/Os. But we still
    // have to watch out for a scenario where another driver can send 
    // requests to our deviceobject directly without opening an handle.
    //
    if (!deviceExtension->Deleted) 
	{ //if not deleted
        status = STATUS_SUCCESS;
        Irp->IoStatus.Information = 0;
        irpStack = IoGetCurrentIrpStackLocation (Irp);

        switch (irpStack->MajorFunction) {
            case IRP_MJ_CREATE:
                DebugPrint(("Create \n"));
                break;
                
            case IRP_MJ_CLOSE:
                DebugPrint(("Close \n"));
                break;
                
            case IRP_MJ_CLEANUP:
                DebugPrint(("Cleanup \n"));
                break;
                
             case  IRP_MJ_DEVICE_CONTROL:
			 case  IRP_MJ_INTERNAL_DEVICE_CONTROL:
                DebugPrint(("DeviceIoControl\n"));
                switch (irpStack->Parameters.DeviceIoControl.IoControlCode) {
                    //
                    //case IOCTL_CUSTOM_CODE: 
                    //
					case IOCTL_KLFLTDEV_ADDRULE:
						if ( InputBufferSize < ( sizeof(KLFLTDEV_RULE) + sizeof(ULONG) + sizeof(WCHAR)+ sizeof(ULONG) + sizeof(WCHAR) ) )
							status = STATUS_INVALID_PARAMETER;
						else
							status = STATUS_SUCCESS;

						if (NT_SUCCESS( status ))
						{
							if ( OutputBufferSize < sizeof(REPLUG_STATUS) )
								 status = STATUS_BUFFER_TOO_SMALL;
						}

						if (NT_SUCCESS( status ))
						{
							PKLFLTDEV_RULE pklfltdev_add_rule;
							ULONG	klflt_dev_rule_size;

							klflt_dev_rule_size = InputBufferSize;
							pklfltdev_add_rule = ExAllocatePoolWithTag( PagedPool, klflt_dev_rule_size, tag_filter2 );

							if (!pklfltdev_add_rule)
								status = STATUS_NO_MEMORY;

							if (NT_SUCCESS( status ))
								status = Comm_CopyUserBufferToInternal (
								pklfltdev_add_rule,
								InputBuffer,
								klflt_dev_rule_size
								);

							if (NT_SUCCESS( status ))
							{
								LONGLONG RulID = 0;
								UNICODE_STRING usGuid;
								UNICODE_STRING usDeviceType;
								PULONG	pStrSize;
								ULONG retSize = 0;
								PWCHAR	pStr;
								REPLUG_STATUS replug_status = Need_Noting;

								RtlInitEmptyUnicodeString ( &usGuid, NULL, 0 );
								RtlInitEmptyUnicodeString ( &usDeviceType, NULL, 0 );
								
								pStrSize=(ULONG*)( (char*)pklfltdev_add_rule + sizeof(KLFLTDEV_RULE) );
								pStr=(PWCHAR)(pStrSize + 1);

								if (*pStrSize && (((char*)pStr + (*pStrSize)) <= (char*)pklfltdev_add_rule + klflt_dev_rule_size))
								{
									RtlInitEmptyUnicodeString( &usGuid, pStr, (USHORT) *pStrSize );
									usGuid.Length =(USHORT) *pStrSize;
								}

								pStrSize = (ULONG*) ((char*) pStr + *pStrSize);
								pStr = (PWCHAR) (pStrSize + 1);
								if (*pStrSize && (((char*)pStr + (*pStrSize)) <= (char*)pklfltdev_add_rule + klflt_dev_rule_size))
								{
									RtlInitEmptyUnicodeString( &usDeviceType, pStr, (USHORT)*pStrSize );
									usDeviceType.Length = (USHORT)*pStrSize;
								}

								status = SaveDevRuleToReg(
									&deviceExtension->usRegistryPath,
									usGuid,
									usDeviceType,
									pklfltdev_add_rule->m_mask
									);

								if ( IsAttachedDevice ( &usGuid, &usDeviceType ) )
								{
									replug_status = Need_Replug;
								}
								else
									replug_status = Need_Noting;

								if (NT_SUCCESS( status ))
								{
									status = Comm_CopyDataToUserBuffer (
										OutputBuffer,
										OutputBufferSize,
										&replug_status,
										sizeof(REPLUG_STATUS),
										&retSize
										);
									
									if ( NT_SUCCESS (status) )
									{
										Irp->IoStatus.Information = sizeof(REPLUG_STATUS);
									}
								}
							}

							if (pklfltdev_add_rule)
								ExFreePool( pklfltdev_add_rule );
						}
					break;
					
					case IOCTL_KLFLTDEV_APPLYRULES:
						status = RebuildDevRulListFromReg( &deviceExtension->usRegistryPath );
					break;
					
					case IOCTL_KLFLTDEV_GETRULES_SIZE:
						if ( OutputBufferSize < sizeof( KLFLTDEV_RULES_SIZE ) )
							status = STATUS_BUFFER_TOO_SMALL;
						else
							status = STATUS_SUCCESS;

						if (NT_SUCCESS( status ))
						{
							ULONG rul_size;
							KLFLTDEV_RULES_SIZE klfltdev_rul_size;
							ULONG retSize = 0;

							memset ( &klfltdev_rul_size, 0, sizeof(KLFLTDEV_RULES_SIZE) );

							status = GetDevRulSize ( &rul_size );
							 if ( NT_SUCCESS ( status ) )
							 {
								 klfltdev_rul_size.m_size = rul_size;
								 status = Comm_CopyDataToUserBuffer (
											OutputBuffer,
											OutputBufferSize,
											&klfltdev_rul_size,
											sizeof(KLFLTDEV_RULES_SIZE),
											&retSize
											);
								
								if ( NT_SUCCESS (status) )
								{
									Irp->IoStatus.Information = sizeof(KLFLTDEV_RULES_SIZE);
								}
							 }
						}
					break;

					case IOCTL_KLFLTDEV_GETRULES:
					{
						ULONG max_size;
						
						
						if ( OutputBufferSize < sizeof( KLFLTDEV_RULES ) )
							status = STATUS_BUFFER_TOO_SMALL;
						else
							status = STATUS_SUCCESS;
						
						max_size = OutputBufferSize;
												
						if (NT_SUCCESS( status ))
						{
							PKLFLTDEV_RULES pklfltdev_rules;
							ULONG retSize = 0;

							pklfltdev_rules = ExAllocatePoolWithTag( PagedPool, max_size, tag_filter7 );
							if ( !pklfltdev_rules )
								status = STATUS_NO_MEMORY;

							if ( NT_SUCCESS ( status ) )
							{
								memset ( pklfltdev_rules, 0, sizeof(KLFLTDEV_RULES) );

								status = GetDevRules ( max_size, pklfltdev_rules );

								if ( NT_SUCCESS ( status ) )
								{
									status = Comm_CopyDataToUserBuffer (
												OutputBuffer,
												OutputBufferSize,
												pklfltdev_rules,
												max_size,
												&retSize
												);
									
									if ( NT_SUCCESS (status) )
									{
										Irp->IoStatus.Information = max_size;
									}
								}
								
								ExFreePool( pklfltdev_rules );
							}
						}
					}
					break;
                    
					default:
                        status = STATUS_INVALID_PARAMETER;
                        break;
                }
            default:
                break;
        }
    } else {
        ASSERTMSG(FALSE, "Requests being sent to a dead device\n");
        status = STATUS_DEVICE_REMOVED;
    }
    Irp->IoStatus.Status = status;
    IoCompleteRequest (Irp, IO_NO_INCREMENT);
    return status;
}

#endif 

#if DBG

PCHAR
PnPMinorFunctionString (
    UCHAR MinorFunction
)
{
    switch (MinorFunction)
    {
        case IRP_MN_START_DEVICE:
            return "IRP_MN_START_DEVICE";
        case IRP_MN_QUERY_REMOVE_DEVICE:
            return "IRP_MN_QUERY_REMOVE_DEVICE";
        case IRP_MN_REMOVE_DEVICE:
            return "IRP_MN_REMOVE_DEVICE";
        case IRP_MN_CANCEL_REMOVE_DEVICE:
            return "IRP_MN_CANCEL_REMOVE_DEVICE";
        case IRP_MN_STOP_DEVICE:
            return "IRP_MN_STOP_DEVICE";
        case IRP_MN_QUERY_STOP_DEVICE:
            return "IRP_MN_QUERY_STOP_DEVICE";
        case IRP_MN_CANCEL_STOP_DEVICE:
            return "IRP_MN_CANCEL_STOP_DEVICE";
        case IRP_MN_QUERY_DEVICE_RELATIONS:
            return "IRP_MN_QUERY_DEVICE_RELATIONS";
        case IRP_MN_QUERY_INTERFACE:
            return "IRP_MN_QUERY_INTERFACE";
        case IRP_MN_QUERY_CAPABILITIES:
            return "IRP_MN_QUERY_CAPABILITIES";
        case IRP_MN_QUERY_RESOURCES:
            return "IRP_MN_QUERY_RESOURCES";
        case IRP_MN_QUERY_RESOURCE_REQUIREMENTS:
            return "IRP_MN_QUERY_RESOURCE_REQUIREMENTS";
        case IRP_MN_QUERY_DEVICE_TEXT:
            return "IRP_MN_QUERY_DEVICE_TEXT";
        case IRP_MN_FILTER_RESOURCE_REQUIREMENTS:
            return "IRP_MN_FILTER_RESOURCE_REQUIREMENTS";
        case IRP_MN_READ_CONFIG:
            return "IRP_MN_READ_CONFIG";
        case IRP_MN_WRITE_CONFIG:
            return "IRP_MN_WRITE_CONFIG";
        case IRP_MN_EJECT:
            return "IRP_MN_EJECT";
        case IRP_MN_SET_LOCK:
            return "IRP_MN_SET_LOCK";
        case IRP_MN_QUERY_ID:
            return "IRP_MN_QUERY_ID";
        case IRP_MN_QUERY_PNP_DEVICE_STATE:
            return "IRP_MN_QUERY_PNP_DEVICE_STATE";
        case IRP_MN_QUERY_BUS_INFORMATION:
            return "IRP_MN_QUERY_BUS_INFORMATION";
        case IRP_MN_DEVICE_USAGE_NOTIFICATION:
            return "IRP_MN_DEVICE_USAGE_NOTIFICATION";
        case IRP_MN_SURPRISE_REMOVAL:
            return "IRP_MN_SURPRISE_REMOVAL";

        default:
            return "unknown_pnp_irp";
    }
}

#endif


