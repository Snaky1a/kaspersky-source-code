#include "stdafx.h"
#include <CKAH/ckahrulesdefs.h>

CProgramExecutionLog log;

CKAHRULESEXPORT void CkahRules_SetExternalLogger (CProgramExecutionLog::EXTERNALLOGGERPROC logger)
{
	log.Initialize (logger);
}


BOOL APIENTRY DllMain (HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}

    return TRUE;
}
