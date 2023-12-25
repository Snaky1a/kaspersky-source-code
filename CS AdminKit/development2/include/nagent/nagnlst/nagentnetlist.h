/*!
 * (C) 2005 "Kaspersky Lab"
 *
 * \file nagentnetlist.h
 * \author ����� �����������
 * \date 2005
 * \brief ��������� ������ ��� ������ � ����������� ( �������� ) �������� �� ������� �������� ������
 */

#if !defined(KLNAGNLST_NAGENTNETKLIST)
#define KLNAGNLST_NAGENTNETKLIST

#include <string>
#include <list>

#include <avp/klids.h>
#include <std/base/kldefs.h>
#include <std/base/klbase.h>
#include <std/tmstg/timeoutstore.h>

#include <kca/basecomp/cmpbase.h>
#include <kca/contie/connectiontiedobjectshelper.h>

#include <nagent/naginst/naginst.h>
#include <nagent/nagnlst/producteventconvertor.h>
#include <nagent/evp/eventstoserver.h>
#include <nagent/conn/networklist.h>

namespace KLNAGNLST {

	//!\brief ��� ������ �������� �������� ������ 
	const wchar_t KLNLST_SEND_QB_LIST[] = KLCS_COMPONENT_NAGENT;

		//!\brief ��� ���� � ������ KLNLST_SEND_QB_LIST 
		const wchar_t KLNLST_SEND_QB_LIST_FLAG[] = L"SEND_QB_LIST_FLAG"; // BOOL_T
		
		//!\brief ��� ���� � ������ KLNLST_SEND_QB_LIST 
		const wchar_t KLNLST_SEND_BACKUP_LIST_FLAG[] = L"SEND_BACKUP_LIST_FLAG"; // BOOL_T


	//!\brief ��� ������ �������� ������� ��� �������� ���������� ������� �������
	const wchar_t KLNLST_PRODUCT_NETWORKLIST_SECTION[] = L".NETWORKLISTS";
	
		//!\brief ��� ���� � ������ KLNLST_PRODUCT_NETWORKLIST_SECTION
		const wchar_t KLNLST_PRODUCT_Q_LIST_FLAG[] = L"Q_LIST_FLAG"; // BOOL_T
		
		//!\brief ��� ���� � ������ KLNLST_PRODUCT_NETWORKLIST_SECTION
		const wchar_t KLNLST_PRODUCT_B_LIST_FLAG[] = L"B_LIST_FLAG"; // BOOL_T

		//!\brief ��� ���� � ������ KLNLST_PRODUCT_NETWORKLIST_SECTION
		const wchar_t KLNLST_PRODUCT_TIF_LIST_FLAG[] = L"TIF_LIST_FLAG"; // BOOL_T

	class NagentNetList : public KLTP::ThreadsPool::Worker
	{
	public:

		/*
			\brief ������� �������������
		*/
		virtual void Initialize( const KLPRCI::ComponentId&  idMySelf,
					const KLPRCI::ComponentId	&idServer,
                    KLNAG::NagentProperties*    pNagentProperties,
					KLBASECOMP::ComponentBase*		pNagentInstance,
					CONTIE::ConnectionTiedObjectsHelper *pTieStorage ) = 0;		

		/*
			\brief ������� �������������
		*/
		virtual void InitializeHook( KLEVP::PRESServersForRead*	pPresForRead ) = 0;

		/*
			\brief ������� �������������
		*/
		virtual void PostInitialize( KLEVP::PRESServersForRead* pPresForRead ) = 0;		

		/*
			\brief ������� ���������� �� ��������� ������� connector
		 */
		virtual void OnConnectorLoading(
                            const wchar_t*      szwProduct,
                            const wchar_t*      szwVersion,
                            AVP_dword           dwFlags) = 0;

		virtual void OnConnectorUnLoaded(
                            const wchar_t*      szwProduct,
                            const wchar_t*      szwVersion,
                            AVP_dword           dwFlags) = 0;
		
		/*
			\brief ������� ���������������
		*/
		virtual void DeInitialize() = 0;

		/*
			\brief ������� ���������� ���������� ������� ��������
		*/
		virtual void AddConvertor( const std::wstring &listName, ProductEventConvertor* pConvertor ) = 0;

		/*
			\brief ������� ���������� hook ��� EVP
		*/
		virtual KLEVP::EvProcessorHook* GetHook() = 0;
		
		/*
			\brief ������������ ���������������� ������ ��� ����������� ��������� ���������� �� ������

			\param	listName - ��� ������ ( ��� ������ ������ ������ ����� �������� �� ������ )
			
		*/
		virtual void RegisterCustomList( std::wstring customListName, KLCONN::NetworkList *pNetworkList ) = 0;

		/*
			\brief ��������������� ���������������� ������

			\param	listName - ��� ������ 
			
		*/
		virtual void UnregisterCustomList( std::wstring customListName ) = 0;

	};

} // end namespace KLNAGNLST


KLNAGNLST::NagentNetList *KLNAGNLST_GetNagentNetList();

/*
	\brief ������� ������������/��������������� ����������
*/
DECLARE_MODULE_INIT_DEINIT2( KLCSNAGT_DECL, KLNAGNLST );

#endif // !defined(KLNAGNLST_NAGENTNETKLIST)
