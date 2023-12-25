#ifndef _NAMECACHE_H
#define _NAMECACHE_H

/*!
*		
*		
*		(C) 2001-3 Kaspersky Lab 
*		
*		\file	NameCache.h
*		\brief	��� ��������, ��������� �������� ��������� ������
*		
*		\author Sergey Belov, Andrew Sobko
*		\date	12.09.2003 11:35:34
*		
*		
*		
*		
*/		

#include "osspec.h"
#include "debug.h"

//+ ------------------------------------------------------------------------------------------
//+ ������ � ������� 
#define HASH_FUNC(_object)  (((ULONG)(_object) >> 8) & (HASH_SIZE - 1))
#define HASH4FOBJ(_fobject)  ((ULONG)(_fobject))

//+ ������ �������
#ifdef _HOOK_VXD_ 
	#define HASH_SIZE  128        // MUST be a power of 2
#else
	#define HASH_SIZE  256        // MUST be a power of 2
#endif

//+ ������� �������� � ����
typedef struct _NAMECACHE {
	ULONG	Key;
	struct _NAMECACHE *Next;
	ULONG	RefCount;
	VOID	*Owner;
	DWORD ObjectNameLen;
	CHAR	Name[];
} NAMECACHE,*PNAMECACHE;

//+ ��������� ����
typedef struct _KLG_NAME_CACHE
{
	PNAMECACHE	m_NameCache[HASH_SIZE];
	ERESOURCE	m_CacheResource;
#ifdef __DBG__
	ULONG			m_NameCacheLen[HASH_SIZE];
	ULONG			m_NCLen;
#endif
} KLG_NAME_CACHE, *PKLG_NAME_CACHE;

//+ ------------------------------------------------------------------------------------------
//+ ����� ����
extern PKLG_NAME_CACHE g_pCommon_NameCache;
extern PKLG_NAME_CACHE g_pNameCache_DriveLetter;
extern PKLG_NAME_CACHE g_pCommon_NameCache_Context;

//! \fn				: GlobalCacheInit
//! \brief			: ������������� ����� ����� � 'AIMem'
//! \return			: 
void
GlobalCacheInit();

//! \fn				: GlobalCacheDone
//! \brief			: �������� ���� ��������� ������
//! \return			: 
void
GlobalCacheDone();

//! \fn				: NameCacheInit
//! \brief			: ������������� ��������� ����
//! \return			: TRUE - ������� / FALSE - ���� ��� �������������
//! \param          : PKLG_NAME_CACHE* ppNameCache - ��������� �� ��������� (����� �������� ������ ��� ������ �������)
BOOLEAN
NameCacheInit(PKLG_NAME_CACHE* ppNameCache);

//! \fn				: NameCacheDone
//! \brief			: �������� ����
//! \return			: 
//! \param          : PKLG_NAME_CACHE* ppNameCache - ��������� �� ��������� (����� ����������� ������)
void
NameCacheDone(PKLG_NAME_CACHE* ppNameCache);

//! \fn				: NameCacheCleanupByProc
//! \brief			: ������� ����� � ������ Owner-� (������������ ��� ���������� ��������)
//! \return			: 
//! \param          : VOID *ProcHandle - ������������� ��������-���������
VOID
NameCacheCleanupByProc(VOID *ProcHandle);

//! \fn				: NameCacheGet
//! \brief			: �������� ������ �� ����
//! \return			: ��������� �� ������ (�� ������������ ��� �������������)
//! \param          : PKLG_NAME_CACHE pNameCache - ���
//! \param          : ULONG key - ���� ��� ������
//! \param          : PVOID name - �������� �� �����, � ������� ����� ����������� ������� ����������� ��������� � ������ ������
//! \param          : ULONG uNameSize - ������ ������
//! \param          : BOOLEAN* pbOverBuf - ������� ������������ ������
PVOID
NameCacheGet(PKLG_NAME_CACHE pNameCache, ULONG key, PVOID name, ULONG uNameSize, BOOLEAN* pbOverBuf);

//! \fn				: NameCacheStore
//! \brief			: ��������� ������ � ���� (���� ������ �� ����� ���� ������� - ������������� �������)
//! \return			: 
//! \param          : PKLG_NAME_CACHE pNameCache - ���
//! \param          : ULONG key - ����
//! \param          : PVOID name - ������
//! \param          : DWORD NameLen - ����� ������ (� ������)
//! \param          : BOOLEAN bAllowIncreaseRef - ���������� �� ������������� �������� ������ (��� ������� ��������� 
//						���� ����� �������)
//! \param          : DWORD Tag - ���, ������������ ��� ��������� ������ ��� ���������� � ����
VOID
NameCacheStore(PKLG_NAME_CACHE pNameCache, ULONG key, PVOID name, DWORD NameLen, BOOLEAN bAllowIncreaseRef, DWORD Tag);

//! \fn				: NameCacheClean
//! \brief			: �������� ���
//! \return			: 
//! \param          : PKLG_NAME_CACHE pNameCache - ���
VOID
NameCacheClean(PKLG_NAME_CACHE pNameCache);

//! \fn				: NameCacheFree
//! \brief			: ������� ������ �� ���� (� ������ ��������)
//! \return			: TRUE - ������ ����� / FALSE - ������ �� ������
//! \param          : PKLG_NAME_CACHE pNameCache - ���
//! \param          : ULONG key - ����
BOOLEAN
NameCacheFree(PKLG_NAME_CACHE pNameCache, ULONG key);

//! \fn				: NameCacheGetBinary
//! \brief			: �������� ��������������� � ������ ������ ��� �������� ����
//! \return			: ��������� �� ������������ ���� (�� ������������ ��� �������������)
//! \param          : PKLG_NAME_CACHE pNameCache - ���
//! \param          : ULONG key - ����
//! \param          : PVOID name - ��������� �� �����
//! \param          : ULONG uNameSize - ����� ������
//! \param          : BOOLEAN* pbOverBuf - ������� ����������� ������
PVOID
NameCacheGetBinary(PKLG_NAME_CACHE pNameCache, ULONG key, PVOID name, ULONG uNameSize, BOOLEAN* pbOverBuf, PULONG pRefCount);

//! \fn				: NameCacheGetReplaceBinary
//! \brief			: �������� ������������ ������ � ���� �� �����
//! \return			: 
//! \param          : PKLG_NAME_CACHE pNameCache -���
//! \param          : ULONG key - ����
//! \param          : PVOID Value - ��������� �� ����� ������
//! \param          : DWORD ValueLen - ����� ����� ������
VOID
NameCacheGetReplaceBinary(PKLG_NAME_CACHE pNameCache, ULONG key, PVOID Value, DWORD ValueLen);

//+ ------------------------------------------------------------------------------------------

typedef struct _tAIMemBlock
{
	BYTE		m_AIMem_BlockType;	// 0 - private, 1 - extrenal
	BYTE		m_Idx;
	int		m_Tag;
}AIMemBlock, *PAIMemBlock;

typedef struct _tAIMemObject
{
#ifdef __DBG__
	DWORD			m_dwMaxItems;
	DWORD			m_dwCurItems;
#endif
	ERESOURCE	m_CacheResource;
	ULONG			m_Hint;
	ULONG			m_BlockSize;
	PAIMemBlock	m_Blocks[32];
}AIMemObject, *PAIMemObject;

//+ ------------------------------------------------------------------------------------------

#ifdef _AI_MEM_USE
extern PAIMemObject g_pAiMem;
extern PAIMemObject g_pAiMemObjectName;
#endif
//+ ------------------------------------------------------------------------------------------

void*
_AIMem_Alloc(PAIMemObject pAIMem, ULONG size, int tag);

void
_AIMem_Free(PAIMemObject pAIMem, void* p);

#endif // _NAMECACHE_H