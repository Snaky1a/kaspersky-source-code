////////////////////////////////////////////////////////////////////
//
//  XFlags.h
//  IO flags definitions
//  Generic purpose IO stuff
//  Victor Matiouchenkov [victor@avp.ru], Kaspersky Labs. 1999
//  Copyright (c) Kaspersky Labs
//
////////////////////////////////////////////////////////////////////
#ifndef __XFLAGS_H__
#define __XFLAGS_H__

//--
typedef enum {
  FIOSO_START   = 0,
  FIOSO_CURRENT = 1,
  FIOSO_END     = 2
} IOS_SEEK_ORIGIN;

//---
#define FIOAM_READ       0x00000008l        // ��������� ���� ������ �� ������
#define FIOAM_WRITE      0x00000004l        // ��������� ���� �� ������ � ������

#define FIOAM_TEMPORARY  0x00008000l        // ��������� ��������� ���� (������������ ����� ������)

#define FIOAM_RANDOM     0x00000100l        // ��������� ������ � ����������
#define FIOAM_SEQUENTIAL 0x00000000l        // ���������������� ������ � ����������

#define FIOCD_CREATE_NEW    		0x00010000l	// ��������� ����� ����. ��������� ������, ���� ���� ��� ����������.
#define FIOCD_CREATE_ALWAYS			0x00020000l	// ��������� ����� ����. ������ ���� ������������
#define FIOCD_OPEN_EXISTING			0x00030000l	// ��������� ����. ��������� ������, ���� ����� ���
#define FIOCD_OPEN_ALWAYS	  		0x00040000l	// ��������� ����. ���� ����� ���, �� �� ���������
#define FIOCD_TRUNCATE_EXISTING	0x00050000l	// ��������� ����. ����� �������� ���� ���������� �� ������� �����.  ����� ������ ����������� � ��������� FIOAM_WRITE. ��������� ������, ���� ����� ���.

#define FIOSM_SHARE_NONE        0x01000000l // ��������� ������ � �����
#define FIOSM_SHARE_READ        0x02000000l // ��������� ������ �� ������
#define FIOSM_SHARE_WRITE       0x04000000l // ��������� ������ �� ������


void IOFlagsToWin32Flags( DWORD dwIOFlags, 
												  DWORD *pdwDesiredAccess, 
													DWORD *pdwShareMode, 
													DWORD *pdwCreationDisposition, 
													DWORD *pdwFlagsAndAttributes );

void IOSeekCodeToWin32SeekCode( IOS_SEEK_ORIGIN dwIOSeek, DWORD *pdwWin32Seek );

#endif