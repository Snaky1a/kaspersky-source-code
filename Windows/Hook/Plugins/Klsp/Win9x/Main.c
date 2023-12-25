#define   DEVICE_MAIN
#include  "precomp.h"
#undef    DEVICE_MAIN

Declare_Virtual_Device(KLSP)

DefineControlHandler(DEVICE_INIT,			OnDeviceInit);
DefineControlHandler(W32_DEVICEIOCONTROL,	OnW32Deviceiocontrol);
DefineControlHandler(SYS_DYNAMIC_DEVICE_INIT, OnSysDynamicDeviceInit);
DefineControlHandler(SYS_DYNAMIC_DEVICE_EXIT, OnSysDynamicDeviceExit);


BOOL __cdecl ControlDispatcher(
							   DWORD dwControlMessage,
							   DWORD EBX,
							   DWORD EDX,
							   DWORD ESI,
							   DWORD EDI,
							   DWORD ECX)
{
	START_CONTROL_DISPATCH	
	
	ON_W32_DEVICEIOCONTROL(OnW32Deviceiocontrol);
	ON_DEVICE_INIT(OnDeviceInit);	
    ON_SYS_DYNAMIC_DEVICE_INIT(OnSysDynamicDeviceInit);
    ON_SYS_DYNAMIC_DEVICE_EXIT(OnSysDynamicDeviceExit);
	
    END_CONTROL_DISPATCH
        
        return TRUE;
}

BOOL OnSysDynamicDeviceInit()
{    
    if ( Klick_Device = KlFindBaseDriver( KLICK_BASE_DRV ) )
    {        
        REGISTER_KLICK_PLUGIN( Klick_Device, PluginInit );
    }

    if ( Klin_Device = KlFindBaseDriver( KLIN_BASE_DRV ) )
    {        
        REGISTER_KLIN_PLUGIN( Klin_Device, PluginInit );
    }
	return TRUE;
}

BOOL OnSysDynamicDeviceExit()
{
    if ( Klick_Device )
    {
        DEREGISTER_KLICK_PLUGIN( Klick_Device, KlickPluginID );
    }

    if ( Klin_Device )
    {
        DEREGISTER_KLIN_PLUGIN( Klin_Device, KlinPluginID );
    }

	return TRUE;
}

BOOL OnDeviceInit(VMHANDLE hVM, PCHAR CommandTail)
{	
	ULONG			Status = 0;

	return TRUE;
}

DWORD OnW32Deviceiocontrol(PIOCTLPARAMS pDIOCParams)
{
    DWORD   ret                 = 0;
    *pDIOCParams->dioc_bytesret = 0;

    switch( pDIOCParams->dioc_IOCtlCode ) 
    {
    case DIOC_OPEN:
    	break;
    case DIOC_CLOSEHANDLE:
        break;
    
    default:
        {
            switch ( MyIoctlHandler( 
                            pDIOCParams->dioc_IOCtlCode,
                            pDIOCParams->dioc_InBuf,
                            pDIOCParams->dioc_cbInBuf,
                            pDIOCParams->dioc_OutBuf,
                            pDIOCParams->dioc_cbOutBuf,
                            pDIOCParams->dioc_bytesret ) )
            {
            case KL_SUCCESS :
                ret = 0;
                break;
            default:
                ret = 0;
                break;
            }

        }
        break;
    }
	return ret;
}
