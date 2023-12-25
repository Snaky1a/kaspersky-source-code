#ifndef __KLOPLIB_H__
#define __KLOPLIB_H__

#include "winioctl.h"
#include "..\..\hook\klop_api.h"

#pragma warning(disable : 4200) // non-standard MS extension

#define KLOP_DRV_NAME	"Klop"

#if defined (KLOPUM_EXPORTS)
	#define KLOPUMEXPORT __declspec (dllexport)
#else
#if defined (KLOPUM_INPLACE)
	#define KLOPUMEXPORT 
#else 
	#define KLOPUMEXPORT __declspec (dllimport)
#endif
#endif

#define KLOPUMMETHOD_ KLOPUMEXPORT
#define KLOPUMMETHOD KLOPUMMETHOD_ KLOPUM::OpResult 

namespace KLOPUM
{
	enum OpResult 
	{
		srOK,
		srNotOk,
		srDriverNotLoaded,
		srInitializedAlready
	};

	// ������������� ������ ��������������.
	// pKey		  - �����, ���������� ������������ ����
	// KeySize	  - ������ ������	
	KLOPUMMETHOD	KlopInit( const char* pKey, unsigned long KeySize);

	// ����������� �����.
	// TimeToWait - ���-�� �����������, � ������� ������� ������� ���� ������ �� ����,
	//				����� ���� ����������� ����� ������� �� ����.
	KLOPUMMETHOD	KlopActivate(unsigned long TimeToWait);


	// �������� ���������� ����� �� ��������, ���������� � ������� �������
	KLOPUMMETHOD	KlopGetCount( ULONG* pKeyCount );

	// ������ ��������������� ������ ��������������. ����� ������ ������� ������ ��������� ������������ � �����������.
	KLOPUMMETHOD	KlopDone();
}

extern HANDLE	g_DrvHandle;

#endif