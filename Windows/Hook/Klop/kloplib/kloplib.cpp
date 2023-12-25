// kloplib.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "kloplib.h"
#include "klop_util.h"

HANDLE	g_DrvHandle = NULL;
std::list<ADAPTER_INFO>	AdapterList;

KLOPUMMETHOD
KLOPUM::KlopInit( const char* pKey, unsigned long KeySize)
{
	BOOL	Result;
	ULONG	Version = 0;
	ULONG	dwRet;
	KLOPUM::OpResult res;

	if ( g_DrvHandle )
		return KLOPUM::srInitializedAlready;
	
	// ��������� ������� ����� Symbolic Link
	g_DrvHandle = CreateFile(
							"\\\\.\\"KLOP_DRV_NAME,
							GENERIC_READ | GENERIC_WRITE,
							0,
							NULL,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							NULL
							);
	
	if ( g_DrvHandle == INVALID_HANDLE_VALUE )
	{
		// ������ ����� ������ �� �������� �������.
		g_DrvHandle = NULL;
		return KLOPUM::srDriverNotLoaded;
	}
	
	do {
		Result = DeviceIoControl( 
							g_DrvHandle,
							KLOP_GET_VERSION,
							NULL,
							0,
							&Version,
							sizeof ( Version ),
							&dwRet,
							NULL);
		if ( Result )
		{	
			if ( Version != KLOP_API_VERSION )
			{
				// ����������� ������ �����������.
				res = KLOPUM::srNotOk;
				break;
			}

			if ( !KLOP_Init( pKey, KeySize ) )
			{
				// �� ������ ������������� ��������.
				// ���� �� ������ - ������ �������� ������.
				res = KLOPUM::srNotOk;
				break;
			}

			// ������ ����� ����� ��������, �������� �� � �������
			// ����� ������� �������� ��������� ����������������� IP �����.

			// 1. �������� ������ ���� ���������.
			AdapterList = KLOP_GetAdapterList();

			std::list<ADAPTER_INFO>::iterator ii;

			// 2. �������� ����� � �������. ������� ������� ������ �� ��������� �� �����.
			//	  �� ���� ��� ������ �� �����������.
			for ( ii = AdapterList.begin(); ii != AdapterList.end(); ii++ )
			{		
				KLOP_AddAdapter( &(ADAPTER_INFO)*ii );		
			}
			
			// 3. �������� ������ < IP > - < MAC >
			//	  � �������� ��� � �������
			//    ������ ������ �����������
			KLOP_SetBroadcastAddr();
			
			return KLOPUM::srOK;
		}
		else
		{
			// �� ������ IOCTL KLOP_GET_VERSION �� �����-�� �������.
		}
		
	} while( FALSE );

	// ���-�� ������ �� ��� ...
	// ������� ������� � ������ ���������

	CloseHandle( g_DrvHandle );
	g_DrvHandle = NULL;

	return res;
}

KLOPUMMETHOD
KLOPUM::KlopActivate(unsigned long TimeToWait)
{
	if ( g_DrvHandle )
	{
		BOOL	Result;
		DWORD	lpReturned;
		
		// ���������� ����. 
		// ������� � ����� ������� � � ������� TimeToWait ����� ���������� ���������� � ������ � ����.
		Result = DeviceIoControl( g_DrvHandle,
			KLOP_CP_ACTIVATE,
			&TimeToWait,
			sizeof ( TimeToWait ),
			NULL,
			0,
			&lpReturned,
			NULL);
		
		return Result ? KLOPUM::srOK : KLOPUM::srNotOk;
	}
	
	return KLOPUM::srNotOk;
}

KLOPUMMETHOD
KLOPUM::KlopGetCount( ULONG* pKeyCount )
{
	if ( pKeyCount == NULL )
		return KLOPUM::srNotOk;

	*pKeyCount = 0;

	if ( g_DrvHandle )
	{
		BOOL	Result;
		DWORD	lpReturned;
		
		// ���������� ����. 
		// ������� � ����� ������� � � ������� TimeToWait ����� ���������� ���������� � ������ � ����.
		Result = DeviceIoControl( g_DrvHandle,
			KLOP_CP_CHECK,
			NULL,
			0,
			pKeyCount,
			sizeof ( ULONG ),
			&lpReturned,
			NULL);

		if ( lpReturned < sizeof ( ULONG ) )
			return KLOPUM::srNotOk;
		
		return Result ? KLOPUM::srOK : KLOPUM::srNotOk;
	}

	return KLOPUM::srNotOk;
}

KLOPUMMETHOD
KLOPUM::KlopDone()
{	
	if ( g_DrvHandle )
	{
		BOOL	Result;
		DWORD	lpReturned;

		// ��������� ������� �������� � ��������� ��� �������.
		Result = DeviceIoControl( g_DrvHandle,
			KLOP_CP_DONE,
			NULL,
			0,
			NULL,
			0,
			&lpReturned,
			NULL);

		CloseHandle( g_DrvHandle );
		g_DrvHandle = NULL;

		return KLOPUM::srOK;
	}
	
	return KLOPUM::srNotOk;
}

#ifdef KLOPUM_EXPORTS

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:		
		DisableThreadLibraryCalls ((HMODULE)hModule);
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

#endif