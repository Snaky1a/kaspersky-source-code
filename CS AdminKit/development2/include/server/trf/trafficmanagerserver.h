/*!
* (C) 2007 "Kaspersky Lab"
*
* \file trafficmanagerserver.h
* \author ����������� �����
* \date 2007
* \brief ��������� ������ ��� ����������� ��������
*
*/

#ifndef FTS_TRAFFICMANAGERSERVER_H
#define FTS_TRAFFICMANAGERSERVER_H

#include <std/base/klbase.h>
#include <std/err/klerrors.h>

#include <transport/tr/trafficmanager.h>

#include <kca/contie/connectiontiedobjectshelper.h>

#include <server/db/dbconnection.h>
#include <server/srvinst/srvinstdata.h>

namespace KLTRFS {

	class KLSTD_NOVTABLE TrafficManagerServer : public KLSTD::KLBase 
	{
	public:

		/*!
			\brief ������������� ���������� 
		*/
		virtual void InitServer( KLSRV::SrvData* pSrvData ) = 0;

		/*!
			\brief ���������� ������ ����������
		*/
		virtual void Shutdown() = 0;

		/*!
		  \brief ��������� ����������� �������� ��� ���������� ��������� IP �������
		*/
		virtual long ReplaceRestriction( const KLTR::TrafficManager::Restriction &restriction ) = 0;

		/*!
		  \brief ������� ���������� �����������
		*/
		virtual void DeleteRestriction( long nRestrictionId ) = 0;

		/*!
		  \brief ���������� ��� ����������� �������� 
		*/
		virtual void GetRestrictions( KLTR::TrafficManager::RestrictionsMap &restrictList ) = 0;
	};

} // end namespace KLTRFS

/*
	\brief ������� ������������/��������������� ���������� �������� ������
*/
DECLARE_MODULE_INIT_DEINIT2( KLCSSRV_DECL, KLTRFS );


/*\brief ���������� ��������� �� ���������� ������ ������ TrafficManagerServer */
KLCSSRV_DECL KLTRFS::TrafficManagerServer *KLTRFS_GetTrafficManagerServer();

#endif // FTS_TRAFFICMANAGERSERVER_H