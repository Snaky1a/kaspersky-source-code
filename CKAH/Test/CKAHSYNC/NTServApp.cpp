// NTService.cpp
// 
// This is the main program file containing the entry point.

#include "NTServApp.h"
#include "myservice.h"

#define RUN_AS_APP

bool g_bIsNT = true;

int main(int argc, char* argv[])
{
    // Create the service object
    CMyService MyService;

#ifdef RUN_AS_APP
	MyService.OnInit ();
	MyService.PerformBasesMerge ();
	MyService.OnStop ();
#else
    // Parse for standard arguments (install, uninstall, version etc.)
    if (!MyService.ParseStandardArgs(argc, argv)) {

        // Didn't find any standard args so start the service
        // Uncomment the DebugBreak line below to enter the debugger
        // when the service is started.
        //DebugBreak();
        MyService.StartService();
    }
#endif

    // When we get here, the service has been stopped
    return MyService.m_Status.dwWin32ExitCode;
}
