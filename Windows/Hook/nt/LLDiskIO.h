#ifndef _LLDISK_IO_H
#define _LLDISK_IO_H

/*!
*		
*		
*		(C) 2002-3 Kaspersky Lab 
*		
*		\file	LLDiskIO.h
*		\brief	�������������� �������� � ������������ (�����, ������, cd, etc..) - ������������, ������, ������, etc...
*		
*		\author Andrew Sobko
*		\date	12.09.2003 11:33:06
*		
*		
*		
*/		

#include "../osspec.h"

//! \fn				: DoDiskRequest
//! \brief			: ������ � ������
//! \return			: 
//! \param          : PEXTERNAL_DRV_REQUEST pInRequest - ������ �������
//! \param          : PVOID pOutRequest - �������� ������
//! \param          : ULONG OutRequestSize - ������ ��������� ������ ��� ������
//! \param          : ULONG *pRetSize - ������ ���������� ��� ��������� ������� ������
NTSTATUS
DoDiskRequest(PEXTERNAL_DRV_REQUEST pInRequest, PVOID pOutRequest, ULONG OutRequestSize, ULONG *pRetSize);

#endif