/*!
* (C) 2007 "Kaspersky Lab"
*
* \file securitypolicyserver.h
* \author ����������� �����
* \date 2007
* \brief ��������� ���������� �������� ���� ������� �� ������ �� ������� �����������������
*
*/

#ifndef SPLS_SECURITYPOLICYSERVER_H
#define SPLS_SECURITYPOLICYSERVER_H

#include <std/base/klbase.h>
#include <std/err/klerrors.h>

#include <transport/wat/common.h>

#include <server/db/dbconnection.h>
#include <server/srvinst/srvinstdata.h>

namespace KLSPLS {

	class KLSTD_NOVTABLE SecurityPolicyServer : public KLSTD::KLBase 
	{
	public:

		/*!
			\brief ������������� ���������� 
		*/
		virtual void Init( KLSRV::SrvData* pSrvData ) = 0;

		/*!
			\brief ���������� ������ ����������
		*/
		virtual void Shutdown() = 0;

		/*!
			\brief ������� ����������� �� ��������� �������� ����� �����������������
		*/
		virtual void NotifyGroupHierarchyChanged() = 0;

		/*!
			\breif ������� ���������� ������� ���� ������� ��� �������� ������������

			\param pClientContext [in,out] - �������� �������. �� ������ ��������� ������� ����� 
				��������� ������� ���� ������� � ��������� � �������� ������������� ������������ � ��
				� ��� ��������� GUID
		*/
		virtual void PrepareClientContext( int transportConnId, 
			KLSTD::CAutoPtr<KLWAT::ClientContext> pClientContext ) = 0;

		/*!
			\breif ������� ���������� � �������� ���������� �� ������������
		*/
		virtual void NotifyClientContextDestroy( KLSTD::CAutoPtr<KLWAT::ClientContext> pClientContext ) = 0;


	};

} // end namespace KLSPLS

/*
	\brief ������� ������������/���������������
*/
DECLARE_MODULE_INIT_DEINIT2( KLCSSRV_DECL, KLSPLS );

/*\brief ���������� ��������� �� ���������� ������ ������ SecurityPolicyServer */
KLCSSRV_DECL KLSPLS::SecurityPolicyServer *KLSPLS_GetSecurityPolicyServer();

#endif // SPLS_SECURITYPOLICYSERVER_H