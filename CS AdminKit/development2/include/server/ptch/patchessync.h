/*!
 * (C) 2007 Kaspersky Lab
 * 
 * \file	patchessync.h
 * \author	Eugene Rogozhnikov
 * \date	28.04.2007 16:41:12
 * \brief	��������� ��� ������������� ���������� � ������ ��� AdminKit
 *			� ����� ������
 * 
 */

#ifndef __PATCHESSYNC_H__
#define __PATCHESSYNC_H__

#include <std/base/klbase.h>
#include <server/db/dbconnection.h>

namespace KLPTCH
{
	class KLSTD_NOVTABLE PatchesSyncSrv
        :   public KLSTD::KLBaseQI
    {
    public:
		virtual ~PatchesSyncSrv(){}

		/*
		 *	
			�������� ���������� � ���� ������ �� ������ ��������� ������ ��� AdminKit.
			bServerAutoUpdates - ���� true, �� AK-������ ����� ������������� ��������, ���� ����� ���������� ����
			bNagentAutoUpdates - ���� true, �� ����� �������� ������ ���������� ��������, ��� ������� ����
									����� ����� ����� ��� ������� ( �� ���� �� �� ���� � ���� �� ������
									������ ����� ������), ���� bForceRunNagentUpdate == true
		 */
        virtual void Sync( 
			KLDB::DbConnectionPtr pDbConn = NULL,
			bool bServerAutoUpdates = false,
			bool bNagentAutoUpdates = false,
			bool bForceRunNagentUpdate = false ) = 0;
	};

}; // namespace KLPTCH

#endif //__PATCHESSYNC_H__