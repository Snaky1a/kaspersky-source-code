#ifndef __APPRUL_H
#define __APPRUL_H

/*!
*		
*		
*		(C) 2007 Kaspersky Lab 
*		
*		\file	apprul.h
*		\brief	�������� ������ ��� ����������
*		
*		\author 
*		\date	24.07.2007 00:00:00
*		
*		
*		
*		
*/		

#include "pch.h"
#include "../kldefs.h"
#include "../hook/avpgcom.h"

#define FILE_OP_WRITE	0x1
#define FILE_OP_READ	0x2
#define FILE_OP_ENUM	0x4
#define FILE_OP_DELETE  0x8

//������������ � ������ �������� � ������ PID
typedef struct _RUL_INFO 
{
	ULONG			mask;
	ULONG			blockID;
	UNICODE_STRING	usDeviceName; // ���� � �����/��������(��������), ���� � ����� �������  
	UNICODE_STRING	usValueName;  // ��� ��������� ������� (���� �����)
}RUL_INFO, *PRUL_INFO;

//������������ � ������ ��������
typedef struct 
{
	UNICODE_STRING	usPath;
	md5_byte_t		digest[16];
} APPL_INFO, *PAPPL_INFO;

//����� �������� ������ �������
typedef struct 
{
	RUL_INFO	rul_info;
	APPL_INFO	appl_info;
}APPL_RUL, *PAPPL_RUL;

//������� ������ �������
typedef struct 
{
	LIST_ENTRY	ListEntry;
	ULONG		clientID;
	LONGLONG	RulID;
	APPL_RUL	app_rul;
} APP_RUL_ENTRY, *PAPP_RUL_ENTRY;


//������� ������ ��� ������ PID  
typedef struct 
{
	LIST_ENTRY	ListEntry;
	ULONG		clientID;
	LONGLONG	RulID;
	RUL_INFO	rul_info;
} RUL_ENTRY, *PRUL_ENTRY;


//������� ��������� ������ PID,��� ����������� �� pProcessInfo (sysio.c)
typedef struct 
{
	LIST_ENTRY		ListEntry;
	HANDLE			pid;
	UNICODE_STRING	usNativePath;
	md5_byte_t		digest[16];
} PID_LIST_ENTRY, *PPID_LIST_ENTRY;




/////////////////////////////////////////////////////////////////////////////
////////////�������


//�������(����) ������
typedef struct 
{
	HANDLE		pid;
	PLIST_ENTRY	pRulHead;
	LONG		readers_cnt;
} PID_TREE_ENTRY, *PPID_TREE_ENTRY;

//������
typedef struct 
{
	RTL_GENERIC_TABLE  PidTree;
	LONG				readers_cnt;
} PID_TREE, *PPID_TREE;

NTSTATUS
InsertAppRuleToList( 
	__in ULONG clientID,
	__in UNICODE_STRING usNativeAppPath,
	__in UNICODE_STRING usNativeFilePath,
	__in UNICODE_STRING usValueName,
	__in PVOID	pHash,
	__in ULONG	HashSize,
	__in ULONG AccessMask,
	__inout PLONGLONG pRulID,
	__in ULONG blockID
	);

NTSTATUS
ResetClientRulesFromList(
	__in ULONG clientID
	);


NTSTATUS
RebuildPidTree();

tefVerdict 
IsAllowAccessFile(
	__in PFLT_CALLBACK_DATA Data,
	__in HANDLE pid,
	__in PFLT_FILE_NAME_INFORMATION pFileNameInfo,
	__in ULONG	desiredOp
	);

tefVerdict
IsAllowAccessReg(
	__in_opt PSID psid,
	__in HANDLE pid,
	__in UNICODE_STRING Path,
	__in_opt PUNICODE_STRING pValueName,
	__in ULONG	desiredOp
	);


//������ ����������� ��� ������������� ��������
void InitAppRul();

// ������ ��� �������� ��������
void DoneAppRul();


#endif