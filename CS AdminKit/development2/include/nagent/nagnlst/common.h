/*!
 * (C) 2005 "Kaspersky Lab"
 *
 * \file nagent/nlst/common.h
 * \author ����� �����������
 * \date 2005
 * \brief ����� ������������ ������ NLST
 */

#if !defined(NAGENT_COMMON)
#define NAGENT_COMMON

#include <string>

#include <std/time/kltime.h>
#include <std/par/params.h>

namespace KLNLST {
	
	class NetworkListItem
	{
	public:
		NetworkListItem() 
		{
			bDeletedFlag = false;
		}

		NetworkListItem( const NetworkListItem &li )
		{
			wstrItemId = li.wstrItemId;		
			tTime = li.tTime;
			pItemParams = li.pItemParams;
			bDeletedFlag = li.bDeletedFlag;
		}

		std::wstring					wstrItemId;		
		
		KLSTD::precise_time_t			tTime;
		KLSTD::CAutoPtr<KLPAR::Params>	pItemParams;

		bool							bDeletedFlag;
	};

	typedef std::vector<NetworkListItem> NetworkListItemsList;

	/*
		!\brief ������������� ��������
	*/
	const wchar_t LIST_CHANGED_SUBS_ID[]			=	L"SUBS";
	
	/*
		!\brief ������� �� ��������� ������

		������ ������� ������������ �� �������� �����, � � ������ �������������, ������������ �� ������
		��� ������ EVP
	*/
	const wchar_t LIST_CHANGED_EVENT[]			=	L"list_changed";


	//!\brief ����������� ���� ���� �������

	/* \!brief ��� ������������� ��������
	*/
	const wchar_t LIST_ITEM_CHANGED_TYPE[]		=	L"li_change_type"; 

	const wchar_t LIST_ITEM_CHANGED_ADDED[]		=	L"item_added";
	const wchar_t LIST_ITEM_CHANGED_DELETED[]	=	L"item_deleted";
	const wchar_t LIST_ITEM_CHANGED_MODIFIED[]	=	L"item_modified";

	/* \!\brief ������������� �������� ������. 
		
		��������� ������ ������������� ������������� ��� �������� ��� ������ ��������� ������ �� 
		�������� �����.
	 */
	const wchar_t LIST_ITEM_ID[]					=	L"list_item_id"; 
	
	/* \!\brief ������ ������������� ��������� ������. 
		
	 */
	const wchar_t LIST_ITEM_IDS[]					=	L"list_item_ids"; 

	/* \!\brief ��� ������������������� �� ������� ������.		
	 */
	const wchar_t LIST_NAME[]					=	L"list_name";


	/* \!\brief ��� ���������� ������		
	 */
	const wchar_t LIST_COMPONENT_NAME[]			=	L"list_comp_name";

	/* \!\brief ��������� �������� ������. 
		
		������ ��������� ����� ��������� ������ � ������������ ������ �� ������ �����. ����������
		� ��� ���������� �������� ��� ��������� ������ �� �������� �����
	 */
	const wchar_t LIST_ITEM_PARAMS[]				=	L"list_item_params";
	
	
} // namespace KLNLST

#endif // !defined(NAGENT_COMMON)
