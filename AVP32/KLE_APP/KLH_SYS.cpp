// KLH_SYS.cpp

#define VDW_MAIN
#include <vdw.h>

extern "C"{
NTSYSAPI
NTSTATUS
NTAPI
ZwLoadDriver(
			 IN PUNICODE_STRING DriverServiceName
			 );
NTSYSAPI
NTSTATUS
NTAPI
ZwUnloadDriver(
			   IN PUNICODE_STRING DriverServiceName
			   );
}


#include "function.h"
#include "KLH_SYS.h"
#include "KLH_SYSDev.h"
#include "SendDIOC.h"

typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;
typedef int                 BOOL;
#include "../KLE/KLEAPI.H"
KLE_FUNCTION_TABLE* KLE_FT=0;


// Generated by Driver::Wizard version 1.20

// Defaults and globals used for tracing
	ULONG		defTraceDevice=0;				// Default trace device
	TRACE_LEVEL defTraceOutputLevel;		// Default trace output level
	BREAK_LEVEL defTraceBreakLevel;			// Default trace break level
	KTrace		Tracer("KLH_SYS");// Global driver trace object
//	KTrace		*Tracer;	// Global driver trace object


//	Unload is responsible for releasing any system objects that
//	the driver has allocated. 
//
//	In general, this function must comprehensively ensure that
//	the driver is not unloaded while holding system objects,
//	including memory, or while there are pending events that
//	would cause the system to call the driver. This is best done
//	by deconstructing top level objects, which in turn release
//	objects for which they are responsible.
//
//	This function is called at PASSIVE_LEVEL.
//
#pragma code_seg("INIT")

DECLARE_DRIVER_CLASS(KLH_SYS, NULL)

// Driver Entry routine
//		This routine is called when the driver is loaded.
//		Usually, this is where any devices associated with
//		the driver are created.
//
//		The driver often reads the registry at DriverEntry in
//		order to setup various configurable parameters.
//		
//		Driver::Works makes it easy to use the registry to also
//		control what devices are present and should be created.
//
KUstring sRegistryPath(0x200,NonPagedPool);


NTSTATUS KLH_SYS::DriverEntry(PUNICODE_STRING RegistryPath)
{
	NTSTATUS status=STATUS_INSUFFICIENT_RESOURCES;
//return status;
	// Status of device creation
//	DbgPrint("KLH_SYS: DriverEntry\n");
	SetPoolTag(' wen');			// Set default pool tag for all 'new' allocations
								// Under checked build, use POOLMON to view tags

	// Automatically load following variables from registry values
	// The default value is preloaded.  If the appropriate registry
	// value is not found, the default will be left unchanged.

	// Open the driver "Parameters" key
//	pKLH_SYSDriver=this;
	sRegistryPath.Assign(L"");
	sRegistryPath.Append(RegistryPath->Buffer);
	KRegistryKey Params(sRegistryPath, L"Parameters");
	if (!NT_SUCCESS(Params.LastError()))
	{
		// Error, could not open registry key
		return STATUS_INSUFFICIENT_RESOURCES;
	}

//#if DBG
	// Setup default trace parameters.
	// If not spec'd in registry, trace to both Monitor and Debugger devices.
	defTraceDevice = TRACE_MONITOR | TRACE_DEBUGGER;
	// If not spec'd in registry, output all trace messages.
	defTraceOutputLevel = TraceAlways;
	// If not spec'd in registry, never break on trace messages.
	defTraceBreakLevel = BreakNever;

	Params.QueryValue(L"TraceDevice", (PULONG) &defTraceDevice);
	Params.QueryValue(L"TraceOutputLevel", (PULONG) &defTraceOutputLevel);
	Params.QueryValue(L"TraceBreakLevel", (PULONG) &defTraceBreakLevel);

	// Create a global trace object.  We also create trace objects
	// for each device.

/*	Tracer = new (NonPagedPool) KTrace("KLH_SYS",
									   defTraceDevice,
									   defTraceOutputLevel,
									   defTraceBreakLevel);
*/

	Tracer.SetTarget(defTraceDevice);
	Tracer.SetOutputLevel(defTraceOutputLevel);
	Tracer.SetBreakLevel(defTraceBreakLevel);

//#endif


// Create KLH_SYSDevice

	KLH_SYSDevice* pKLH_SYSDevice;
	pKLH_SYSDevice = new (NonPagedPool) KLH_SYSDevice();
	if (pKLH_SYSDevice == NULL)
	{
		_DebugTrace(TraceError, "Error constructing device KLH_SYSDevice\n");
		return STATUS_INSUFFICIENT_RESOURCES;
	}
	status = pKLH_SYSDevice->ConstructorStatus();
	if (!NT_SUCCESS(status))
	{
		// Error returned from a constructor
		_DebugTrace(TraceError, "Error creating device KLH_SYSDevice, status %x\n", status);
		delete pKLH_SYSDevice;
		return status;
	}

	KUstring uDevName=KLE_DEVICE_NAME_NT_L;
	
	status=SendDIOC(uDevName,KLE_IOCTL_GET_FUNCTION_TABLE,0,0,&KLE_FT,4);
	
	if(!NT_SUCCESS(status) || !KLE_FT)
    {
		status=STATUS_DEVICE_CONFIGURATION_ERROR;
		_DebugTrace(TraceError, "Failed to INIT");
		delete pKLH_SYSDevice;
    }
	return status;
}


#pragma code_seg()

VOID KLH_SYS::Unload(VOID)
{

   // If you don't need to perform any functions
   // except to call the base class KDriver::Unload(),
   // then this entire routine may be safely deleted.

    // Call base class to delete all devices.
	_DebugTrace(TraceInfo, "Unload called\n");

	KDriver::Unload();
//	delete Tracer;
}

