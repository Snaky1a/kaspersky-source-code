/*!
 * (C) 2005 "Kaspersky Lab"
 *
 * \file networklist.h
 * \author ����� �����������
 * \date 2005
 * \brief ��������� ������ ��� ������ � ����������� ( �������� ) ��������
 */


#if !defined(KLNLST_NETWORKLIST)
#define KLNLST_NETWORKLIST

#include <string>
#include <list>

#include <std/base/kldefs.h>
#include <std/base/klbase.h>
#include <std/tmstg/timeoutstore.h>

#include <kca/prci/componentid.h>
#include <kca/contie/connectiontiedobjectshelper.h>
#include <kca/prss/settingsstorage.h>

#include <server/nlst/common.h>

#include <srvp/evp/transeventstypes.h>
#include <server/evp/transeventsource.h>

#include <server/db/dbconnection.h>
#include <server/srvinst/srvinstdata.h>

#include <server/nlst/listitemiterator.h>

namespace KLNLST {
	
	/*!
     \brief ��������� ��� ������ � ����������������� ��������
    */

	class CustomNetworkList : public KLSTD::KLBaseQI
	{
	public:
		/*!
			\brief ���������� ��� ���������\���������� �������� ������ 

			\param szwListName		[in]	��� �������� ������.
			\param nHostId			[in]	������������� ����� � �������� ������ ������ �������
			\param szwListItemId	[in]	������������� �������� ������ 
			\param pItemParams		[in]	��������� ��������
		*/
		virtual void UpdateListItem( KLDB::DbConnectionPtr pDbConn,
			const std::wstring &szwListName,
			const long nHostId,
			const std::wstring &szwListItemId, 			
			KLPAR::Params *pItemParams ) = 0;

		/*!
			\brief ���������� ��� �������� �������� ������

			\param szwListName		[in]	��� �������� ������.
			\param nHostId			[in]	������������� ����� � �������� ������ ������ �������
			\param szwListItemId	[in]	������������� �������� ������ 
		*/
		virtual void DeleteListItem( KLDB::DbConnectionPtr pDbConn,
			const std::wstring &szwListName,
			const long nHostId,
			const std::wstring &szwListItemId ) = 0;

		/*!
			\brief ������� ��� �������� �� ������
		*/
		virtual void DeleteAllListItems( KLDB::DbConnectionPtr pDbConn,
			const std::wstring &szwListName,
			const long nHostId ) = 0;
	};

	class NetworkList : public KLSTD::KLBaseQI
	{
	public:
		
		/*
			\brief ������� �������������
		*/
		virtual void Initialize( KLSRV::SrvData* pSrvData, 
			KLSTD::CAutoPtr<KLEVP::TransEventSource> pTransEventSource ) = 0;

		virtual void Deinitialize() = 0;

		/*
			\brief ������� ����������� ������ ������

			\param listName [in] ��� ��������������� ������
			\param listComponentId [in] ������������� ����������, �������������� ������
			\param listControlComponentTaskName [in] ��� ������ �� ��������� ����������, 
					������� ������������� ��� ��������� ���������� �� ��������� 
					������ �� �������� �����

			\exception NLSTERR_WRONG_LIST_NAME
		*/
		virtual void RegisterList( const std::wstring& listName, 
			const KLPRCI::ComponentId &listComponentId,
			const std::wstring &listControlComponentTaskName ) = 0;

		/*
			\brief ������� ���������� �������� ��������� ������
		*/
		virtual void GetListItemsIterator( KLNLST::ListItemIterator **ppIterator ) = 0;

		/*
			\brief ������� ��������� ������ ������ ��������� �����

			\exception NLSTERR_WRONG_LIST_NAME, NLSTERR_WRONG_ARGS
		*/
		virtual void UpdateHostNetworkList( const std::wstring &listName,
			const std::wstring &listComponentName,
			const std::wstring &remoteConnName,
			const NetworkListItemsList &itemsList ) = 0;

		/*
			\brief ������� ��������� ������ ��� �������� ������

			\exception NLSTERR_WRONG_LIST_NAME, NLSTERR_WRONG_ARGS
		*/
		virtual void AddListItemTask( int itemId, const std::wstring &taskName,
			KLPAR::Params *pParams ) = 0;


		/*
			\brief ������� ��������� ������ ��� ��������� ������

			\exception NLSTERR_WRONG_LIST_NAME, NLSTERR_WRONG_ARGS
		*/
		virtual void AddListItemsTask( std::vector<long> itemsIds, const std::wstring &taskName,
			KLPAR::Params *pParams ) = 0;
		

		/*
			\brief ������� ���������� �� ���������� �������� �� ������� �����������������			
		*/
		virtual void PolicyChangedNotify( 
			const KLPRSS::product_version_t&	productVersion,
			const std::wstring&					sectionName,
			const KLPAR::Params*				sectionParams,
			KLDB::DbConnectionPtr				pDbConn,
			const int							groupSyncId ) = 0;
		
		/*
			\brief ������� ���������� �� ���������\������������ ��������
		*/
		virtual void PolicyActivatedNotify( 
			const KLPRSS::product_version_t&	productVersion,
			bool								activatedFlag,
			const std::wstring&					settingsStoragePath,
			KLDB::DbConnectionPtr				pDbConn,
			const int							groupSyncId ) = 0;


		/*!
			\brief ������������ ���������������� ������
		 */
		virtual void RegisterCustomNetworkList( const std::wstring &listName,  
			CustomNetworkList *pCustomList ) = 0;

		/*!
			\brief ��������������� ���������������� ������
		 */
		virtual void UnregisterCustomNetworkList( const std::wstring &listName ) = 0;
		
		/*
			\brief ������� ���������� ���������� �� �������� ������

			\exception NLSTERR_WRONG_ARGS
		*/
		virtual void GetItemInfo( int itemId, std::wstring &hostName,
			std::wstring &listName, std::wstring &itemIdName ) = 0;
	};

} // end namespace KLNLST

KLNLST::NetworkList *KLNLST_GetNetworkList();

void KLNLST_GetNetworkList( KLNLST::NetworkList **ppNetworkList );

void KLNLST_CreateNetworkList( KLNLST::NetworkList **ppNetList );

/*
	\brief ������� ������������/��������������� ����������
*/
DECLARE_MODULE_INIT_DEINIT2( KLCSSRV_DECL, KLNLST );

#endif // !defined(KLNLST_NETWORKLIST)