// NameSpaceList.cpp : implementation file
//

#include "stdafx.h"
#include <tchar.h>
#include "WASCRes.rh"
#include <Stuff\PathStr.h>
#include <StuffIO\Utils.h>
#include <Wascmess.h>
#include "NameSpaceTree.h"
#include <ODMenu.h>        // CODMenu class declaration

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT mAfterChangeState  = ::RegisterWindowMessage( _T("AfterChangeState") ); 



/////////////////////////////////////////////////////////////////////////////
// CNameSpaceTreeItem

// --- 
CNameSpaceTreeItem::CNameSpaceTreeItem() :
	m_NormalIcon( NULL ), 
	m_SelectedIcon( NULL ),
	m_NormalIconIndex( -1 ),
	m_SelectedIconIndex( -1 ),
	m_AdditionData( NULL ),
	fStrict( ie_NonStrict ),
	fEnabled( true ),
	fOwnsAdditionData( false ),
	fDummy( false ),
	fHasCheckedDescendants( false ),				// ����� ���������� ��������
	fHasStrictDescendants( false ),			    // ����� Strict ��������
	fHasStrictCheckedDescendants( false ),  // ����� ������ ���������� ��������
	fManuallyChecked( false ),					  	// ������� �������
	fManuallyStrict( false ), 						  // Strict �������
	fHasNoCheckButton( false ),							// �� ����� check button
	fOwnsIcons( false )
{
}

// --- 
CNameSpaceTreeItem::~CNameSpaceTreeItem() {
	if ( IsOwnsAdditionData() )
		delete m_AdditionData;
}


// --- 
bool CNameSpaceTreeItem::operator == ( const CCheckTreeItem &rItem ) {
	CNameSpaceTreeItem &nsItem = (CNameSpaceTreeItem &)rItem;

	return CCheckTreeItem::operator == ( rItem ) &&
					m_NormalIcon									== nsItem.m_NormalIcon								&& 
					m_SelectedIcon								== nsItem.m_SelectedIcon							&&
					m_NormalIconIndex							== nsItem.m_NormalIconIndex						&&
					m_SelectedIconIndex						== nsItem.m_SelectedIconIndex					&&
					m_Data												== nsItem.m_Data											&&
					m_AdditionData								== nsItem.m_AdditionData							&&
					fStrict												== nsItem.fStrict											&&
					fEnabled											== nsItem.fEnabled										&&
					fOwnsAdditionData							== nsItem.fOwnsAdditionData						&&
					fOwnsData											== nsItem.fOwnsData										&&
					fDummy												== nsItem.fDummy											&&
					fHasCheckedDescendants				== nsItem.fHasCheckedDescendants			&&	// ����� ���������� ��������
					fHasStrictDescendants					== nsItem.fHasStrictDescendants				&&	// ����� Strict ��������
					fHasStrictCheckedDescendants	== nsItem.fHasStrictCheckedDescendants && // ����� ������ ���������� ��������
					fManuallyChecked							== nsItem.fManuallyChecked						&&	// ������� �������
					fManuallyStrict								== nsItem.fManuallyStrict; 						  	// Strict �������
}


// --- 
void CNameSpaceTreeItem::Assign( const CCheckTreeItem &rItem ) {
	CNameSpaceTreeItem &nsItem = (CNameSpaceTreeItem &)rItem;

	CCheckTreeItem::Assign( rItem );

	m_NormalIcon									= nsItem.m_NormalIcon								; 
	m_SelectedIcon								= nsItem.m_SelectedIcon							;
	m_NormalIconIndex							= nsItem.m_NormalIconIndex					;
	m_SelectedIconIndex						= nsItem.m_SelectedIconIndex				;
	m_Data												= nsItem.m_Data											;
	m_AdditionData								= nsItem.m_AdditionData							;
	fStrict												= nsItem.fStrict										;
	fEnabled											= nsItem.fEnabled										;
	fOwnsData											= nsItem.fOwnsData									;
	fOwnsAdditionData							= nsItem.fOwnsAdditionData					;
	fDummy												= nsItem.fDummy											;
	fHasCheckedDescendants				= nsItem.fHasCheckedDescendants			;	// ����� ���������� ��������
	fHasStrictDescendants					= nsItem.fHasStrictDescendants			;	// ����� Strict ��������
	fHasStrictCheckedDescendants	= nsItem.fHasStrictCheckedDescendants ; // ����� ������ ���������� ��������
	fManuallyChecked							= nsItem.fManuallyChecked						;	// ������� �������
	fManuallyStrict								= nsItem.fManuallyStrict						; // Strict �������
}


// ---
CCheckTreeItem *CNameSpaceTreeItem::Duplicate() {
	CNameSpaceTreeItem *newItem = new CNameSpaceTreeItem;
	*newItem = *this;
	return newItem;
}


// --- 
int	CNameSpaceTreeItem::GetImageIndex() {
	int nIndexShift = 0;

	if ( IsHasCheckedDescendants() )
		nIndexShift = iti_LastIndex;

	if ( IsHasStrictCheckedDescendants() )
		nIndexShift = iti_LastIndex << 1;

/* �� ������������
	if( IsHasNoCheckButton() )
		nIndexShift = iti_LastIndex * 3 + !!IsExpanded();
*/

/* Image �������
	if ( IsEnabled() ) {
		return int(( GetChecked() == ie_Checked
								?	iti_Checked
								: iti_Unchecked
							 ) + nIndexShift) + ((iti_LastIndex * 3 + 2) * (int)IsStrict());
	}
	else {
		return int(( GetChecked() == ie_Checked
								?	iti_Checked
								: iti_Unchecked
							 ) + nIndexShift) + ((iti_LastIndex * 3 + 2) * 2) + ((iti_LastIndex * 3 + 2) * (int)IsStrict());
	}
*/
	if ( IsEnabled() ) {
		return int(( GetChecked() == ie_Checked
								?	iti_Checked
								: iti_Unchecked
							 ) + nIndexShift) + 
							     ((iti_LastIndex * 3) * (int)IsStrict());
	}
	else {
		nIndexShift /= 2;
		return int(( GetChecked() == ie_Checked
								?	iti_Checked
								: iti_Unchecked
							 ) + nIndexShift) + 
							     ((iti_LastIndex * 3) * 2);
	}

/* Image �������
	return int(( GetChecked() == ie_Checked
							?	iti_Checked
							: iti_Unchecked
						 ) + nIndexShift) + ((iti_LastIndex * 3 + 2) * (int)IsStrict());
*/
}

// ---
bool CNameSpaceTreeItem::CanChangeChecked() {
	return GetStrict() != ie_Strict;
}

/////////////////////////////////////////////////////////////////////////////
// CNameSpaceTree

CNameSpaceTree::CNameSpaceTree() :
	fShowSelectionAlways( false ),
	m_nImageSize(16,16)//( ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON) )
{
	// ImageList � ������ CCheckTree ����� ���� State
	SetStateImageType( true );	
}

CNameSpaceTree::~CNameSpaceTree() {
}


// ---
void CNameSpaceTree::PreSubclassWindow() {
	CCheckTree::PreSubclassWindow();

	if ( ::IsDlgClassName(*GetParent()) ) 
		SetShowSelectionAlways( fShowSelectionAlways );
}


// ---
COLORREF CNameSpaceTree::SetBkColor( COLORREF crColor ) {
	if ( m_NameImageList.GetSafeHandle() )
		m_NameImageList.SetBkColor( crColor );

	return CCheckTree::SetBkColor( crColor );
}


// ---
void CNameSpaceTree::SetShowSelectionAlways( bool bShowAlways ) {
	fShowSelectionAlways = bShowAlways;

	if ( m_hWnd )
		if ( ModifyStyle(!fShowSelectionAlways ? TVS_SHOWSELALWAYS : 0, 
											fShowSelectionAlways ? TVS_SHOWSELALWAYS : 0) ) {
			HTREEITEM hSelectedItem = GetSelectedItem();
			CRect itemRect;
			GetItemRect( hSelectedItem, &itemRect, TRUE );
			InvalidateRect( itemRect );
			UpdateWindow();
		}
}


// ---
void CNameSpaceTree::SetImageListSize( SIZE nSize ) {
	m_nImageSize = nSize;

	if ( m_NameImageList.GetSafeHandle() ) {
		SetImageList( NULL, TVSIL_NORMAL );

		m_NameImageList.DeleteImageList();

		CreateStandartImageList();
	}
}

// ������� ImageList
// ---
void CNameSpaceTree::CreateImageList() {
	m_ImageList.Create( IDB_WAS_NAMETREEIMAGE, 25, 1, RGB(255, 255, 255) );
	//m_DisabledImageList.Create( IDB_WAS_NAMETREEIMAGE, 25, 1, RGB(255, 255, 255) );

	SetImageList( &m_ImageList, TVSIL_STATE );

	CreateStandartImageList();
}

// ---
void CNameSpaceTree::CreateStandartImageList() {
	m_NameImageList.Create( m_nImageSize.cx, m_nImageSize.cy, ILC_COLOR24 | ILC_MASK, 25, 1);

	m_NameImageList.SetBkColor( GetBkColor() );

	HDC hDC = ::GetDC( *this  );
	HBITMAP hbm = ::CreateCompatibleBitmap( hDC, m_nImageSize.cx, m_nImageSize.cy );

	if ( hbm != NULL ) {
		HDC hDCMem = ::CreateCompatibleDC( hDC );
		HBITMAP hbmOld = (HBITMAP)::SelectObject(hDCMem, hbm);

		::SetBkColor( hDCMem, ::GetSysColor(COLOR_WINDOW) );
		CRect rect(0, 0, m_nImageSize.cx, m_nImageSize.cy);
		::ExtTextOut( hDCMem, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL );

		::SelectObject( hDCMem, hbmOld );
		::DeleteDC( hDCMem );

		ImageList_AddMasked( m_NameImageList, hbm, ::GetSysColor(COLOR_WINDOW) );
	}
	::ReleaseDC( *this, hDC );

	int nImage = m_NameImageList.Add( AfxGetApp()->LoadIcon(IDI_WAS_NAMETREEOVERLAYIMAGE) );
	m_NameImageList.SetOverlayImage( nImage, 1 );

	SetImageList( &m_NameImageList, TVSIL_NORMAL );

	TreeView_SetItemHeight( *this, m_nImageSize.cy );
}


// ---
void CNameSpaceTree::SetNodeImage( CCheckTreeItem *item, HTREEITEM hNode ) {

	if ( !hNode )
		hNode = NodeByIndex( IndexNode(item) );
/*
	static BOOL bLastEnabledList = TRUE;
	if ( item->IsEnabled() ) {
		if ( !bLastEnabledList ) {
			SetRedraw( FALSE );
			SetImageList( &m_ImageList, TVSIL_STATE );
			bLastEnabledList = TRUE;
			SetRedraw( TRUE );
		}
	}
	else {
		if ( bLastEnabledList ) {
			SetRedraw( FALSE );
			SetImageList( &m_DisabledImageList, TVSIL_STATE );
			bLastEnabledList = FALSE;
			SetRedraw( TRUE );
		}
	}
*/

	CCheckTree::SetNodeImage( item, hNode );
/*
	CNameSpaceTreeItem *nsItem = (CNameSpaceTreeItem *)item;

	int nOverLayInd = ( nsItem->GetStrict() == CNameSpaceTreeItem::ie_Strict ) ? 1 : 0;
	SetItemState( hNode, INDEXTOOVERLAYMASK(nOverLayInd), TVIS_OVERLAYMASK );
*/
}


// ---
void CNameSpaceTree::FlushItemImages() {
	for ( int i=0,c=m_NameImageList.GetImageCount(); i<c; i++ ) 
		m_NameImageList.Remove( i );
	m_IconCache.Flush();
}


// ---
void CNameSpaceTree::SetItemIcons( CNameSpaceTreeItem *nsItem, HTREEITEM hItem ) {
	// ����� Image �������� ����� ��� ���������
	int iNormal = nsItem->GetNormalIconIndex();
	int iSelected = nsItem->GetSelectedIconIndex();
	int iCacheIndex;
	bool bImageListChanged = false;

	if ( nsItem->GetNormalIcon() ) {
		if ( (iCacheIndex = m_IconCache.FindIt(nsItem->GetNormalIcon())) != -1 ) {
			iNormal = iCacheIndex;
/*
			TCHAR pBuffer[100];
			wsprintf( pBuffer, "%s -> Normal cache hit %d\n", LPCTSTR(nsItem->GetText()), iNormal );
			::OutputDebugString( pBuffer );
*/		
			/*
			if ( nsItem->IsOwnsIcons() )
				m_IconCache.Condemn( nsItem->GetNormalIcon() );
			*/
		}
		else {
			iNormal = m_NameImageList.Add( nsItem->GetNormalIcon() );
			bImageListChanged = true;

			int iNewIndex = m_IconCache.Add( nsItem->GetNormalIcon() );
			m_IconCache.SetItemIndex( iNewIndex, iNormal );
/*
			TCHAR pBuffer[100];
			wsprintf( pBuffer, "%s -> Normal added to %d = %d\n", LPCTSTR(nsItem->GetText()), iNewIndex, iNormal );
			::OutputDebugString( pBuffer );
*/
		}
	}

	if ( nsItem->GetSelectedIcon() ) {
		if ( (iCacheIndex = m_IconCache.FindIt(nsItem->GetSelectedIcon())) != -1 ) {
			iSelected = iCacheIndex;
/*
			TCHAR pBuffer[100];
			wsprintf( pBuffer, "%s -> Selected cache hit %d\n", LPCTSTR(nsItem->GetText()), iSelected );
			::OutputDebugString( pBuffer );
*/			
			/*
			if ( nsItem->IsOwnsIcons() )
				m_IconCache.Condemn( nsItem->GetSelectedIcon() );
			*/
		}
		else {
			iSelected = m_NameImageList.Add( nsItem->GetSelectedIcon() );
			bImageListChanged = true;

			int iNewIndex = m_IconCache.Add( nsItem->GetSelectedIcon() );
			m_IconCache.SetItemIndex( iNewIndex, iSelected );
/*
			TCHAR pBuffer[100];
			wsprintf( pBuffer, "%s -> Selected added to %d = %d\n", LPCTSTR(nsItem->GetText()), iNewIndex, iSelected );
			::OutputDebugString( pBuffer );
*/
		}
	}

//		if ( bImageListChanged )
//			SetImageList( &m_NameImageList, LVSIL_NORMAL );
/*
	TCHAR pBuffer[100];
	wsprintf( pBuffer, "%s -> %d %d\n", LPCTSTR(nsItem->GetText()), iNormal, iSelected );
	::OutputDebugString( pBuffer );
*/	
	nsItem->SetIconIndexes( iNormal, iSelected );

	if ( !hItem )
		hItem = NodeByIndex( IndexNode(nsItem) );

	SetItemImage( hItem, (iNormal < 0 ? 0 : iNormal), (iSelected < 0 ? 0 : iSelected) );

	nsItem->SetIcons( NULL, NULL );
}


// �������� ���� (������������� ����������� �� �������� ������)
// ---
HTREEITEM CNameSpaceTree::AddItem( CCheckTreeItem *item, HTREEITEM addAfter ) {
	HTREEITEM hAddedItem = CCheckTree::AddItem( item, addAfter );

	SetItemIcons( (CNameSpaceTreeItem *)item, hAddedItem );

	return hAddedItem;
}


// ���������� ������� Strict �� �������
// ---
void CNameSpaceTree::SetItemStrict( int iItemIndex, 
																		CNameSpaceTreeItem::CieStrict fHowToStrict, 
																		bool bSpreadAutomatically ) {

	if ( iItemIndex >=0 && iItemIndex <= m_Items->MaxIndex() ) {
		CNameSpaceTreeItem *item = (CNameSpaceTreeItem *)(*m_Items)[iItemIndex];

		HTREEITEM hNode = NodeByIndex( iItemIndex );

		if ( !item->IsNode() ) {
			// ���� ��� �� ����
			// ����������� ��� ��������
			item->SetStrict( fHowToStrict );

			// ���������� ��������
			SetNodeImage( item, hNode );
		}
		else {
			item->SetStrict( fHowToStrict );

			// ���������� �������� ����
			SetNodeImage( item, hNode );

			if ( bSpreadAutomatically )
				// ���������� ��������� ���� �����
				CheckChildrenStrict( hNode, iItemIndex, fHowToStrict, false );
		}

		if ( bSpreadAutomatically )
			// ���������� ��������� ���� ���������
			CheckParentsStrict( hNode );
	}
}


// ---
void CNameSpaceTree::ScanChildrenAndSetChecked( HTREEITEM hParentNode, 
																								CNameSpaceTreeItem *prItem, 
																								int parentIndex, 
																								bool bCheckChildren,
																								CNameSpaceTreeItem::CieChecked fHowToChecked ) {
	int firstChildLevel  = prItem->GetLevel() + 1;

	int numItemsChecked       = 0;
	int numItemsStrict        = 0;
	int numItemsStrictChecked = 0;

	for ( int i=parentIndex+1,c=m_Items->GetSize(); i<c; i++ ) {
		CNameSpaceTreeItem *crItem = (CNameSpaceTreeItem *)(*m_Items)[i];
		if ( crItem->GetLevel() == firstChildLevel ) {

			if ( bCheckChildren )
				CheckChildren( NodeByIndex(i), i, fHowToChecked );

			bool bStrict = crItem->GetStrict() == CNameSpaceTreeItem::ie_Strict;

			bool bChecked = (/*crItem->GetChecked() == CNameSpaceTreeItem::ie_Checked &&
											 */crItem->IsManuallyChecked()) || 
											crItem->IsHasCheckedDescendants();
			numItemsChecked += !bStrict && bChecked;

			numItemsStrict  += bStrict || crItem->IsHasStrictDescendants();

			numItemsStrictChecked += (bStrict && bChecked) || crItem->IsHasStrictCheckedDescendants();
		}
		else  
			if ( crItem->GetLevel() < firstChildLevel )
				break;
	}

	prItem->SetHasCheckedDescendants( !!numItemsChecked );
	prItem->SetHasStrictDescendants( !!numItemsStrict );
	prItem->SetHasStrictCheckedDescendants( !!numItemsStrictChecked );
/*
	fHowToChecked = CNameSpaceTreeItem::CieChecked( ItemCheckingAnalize(prItem) );
 	InternalSetItemChecked( prItem, fHowToChecked );
*/
	// ���������� ��������
	SetNodeImage( prItem, hParentNode );
}


// ---
void CNameSpaceTree::ScanChildrenAndSetStrict( HTREEITEM hParentNode, 
																							 CNameSpaceTreeItem *prItem, 
																							 int parentIndex, 
																							 bool bCheckChildren,
																							 CNameSpaceTreeItem::CieStrict fHowToStrict ) {
	int firstChildLevel  = prItem->GetLevel() + 1;

	int numItemsChecked     = 0;
	int numItemsStrict        = 0;
	int numItemsStrictChecked = 0;

	for ( int i=parentIndex+1,c=m_Items->GetSize(); i<c; i++ ) {
		CNameSpaceTreeItem *crItem = (CNameSpaceTreeItem *)(*m_Items)[i];
		if ( crItem->GetLevel() == firstChildLevel ) {
			
			if ( bCheckChildren )
				CheckChildrenStrict( NodeByIndex(i), i, fHowToStrict );

			bool bStrict = crItem->GetStrict() == CNameSpaceTreeItem::ie_Strict;

			bool bChecked = (/*crItem->GetChecked() == CNameSpaceTreeItem::ie_Checked &&
											 */crItem->IsManuallyChecked()) || 
											crItem->IsHasCheckedDescendants();
			numItemsChecked += !bStrict && bChecked;

			numItemsStrict  += bStrict || crItem->IsHasStrictDescendants();

			numItemsStrictChecked += (bStrict && bChecked) || crItem->IsHasStrictCheckedDescendants();
		}
		else  
			if ( crItem->GetLevel() < firstChildLevel )
				break;
	}

	prItem->SetHasCheckedDescendants( !!numItemsChecked );
	prItem->SetHasStrictDescendants( !!numItemsStrict );
	prItem->SetHasStrictCheckedDescendants( !!numItemsStrictChecked );
/*
	fHowToStrict = CNameSpaceTreeItem::CieStrict( ItemStrictAnalize(prItem) );
	prItem->SetStrict( fHowToStrict );
*/
	// ���������� ��������
	SetNodeImage( prItem, hParentNode );
}



// ���������� ��������� ����� ����
// ---
void CNameSpaceTree::CheckChildren( HTREEITEM hNode, int ind, CNameSpaceTreeItem::CieChecked fHowToChecked, bool bSetCheck ) {
#if 0	// Try avoid this logique
	CNameSpaceTreeItem *prItem = (CNameSpaceTreeItem *)(*m_Items)[ind];

	if ( bSetCheck ) {
		if ( prItem->CanChangeChecked() ) {
		  
			if ( fHowToChecked == CCheckTreeItem::ie_Unchecked ) {
				prItem->SetManuallyChecked( false );
				if ( !prItem->IsManuallyChecked() )
					InternalSetItemChecked( prItem, fHowToChecked );
			}
			else
				InternalSetItemChecked( prItem, fHowToChecked );
		}

		// ���������� �������� ����
		SetNodeImage( prItem, hNode );
	}
 
	if ( prItem->GetNumItems() ) {
		// ���� � ���� ���� ���� - ������ �� ���� ��� ������ �����
		ScanChildrenAndSetChecked( hNode, prItem, ind, true, fHowToChecked );
	}
#endif
}


// ���������� ��������� ������� ����
// ---
void CNameSpaceTree::CheckParents( HTREEITEM hNode ) {
#if 0	// Try avoid this logique
	HTREEITEM parentNode = GetParentItem( hNode );
	if ( parentNode ) {
		// ���� � ���� ���� ����

		int parentIndex = IndexNode( parentNode );
		CNameSpaceTreeItem *prItem = (CNameSpaceTreeItem *)(*m_Items)[parentIndex];

	// ���������� ���������� ���������� ������ ����� ����
		ScanChildrenAndSetChecked( parentNode, prItem, parentIndex );
		
		// ���������� ���������� ��������� �������� ����
		CheckParents( parentNode );
	}
#endif
}


// ���������� ��������� ����� ����
// ---
void CNameSpaceTree::CheckChildrenStrict( HTREEITEM hNode, int ind, CNameSpaceTreeItem::CieStrict fHowToStrict, bool bStrict ) {
#if 0	// Try avoid this logique
	CNameSpaceTreeItem *prItem = (CNameSpaceTreeItem *)(*m_Items)[ind];

	if ( bStrict ) {
		if ( fHowToStrict == CNameSpaceTreeItem::ie_NonStrict ) {
			prItem->SetManuallyStrict( false );
			if ( !prItem->IsManuallyStrict() )
				prItem->SetStrict( fHowToStrict );
		}
		else
			prItem->SetStrict( fHowToStrict );

		// ���������� �������� ����
		SetNodeImage( prItem, hNode );
	}
 
	if ( IsSpreadMark() &&
				// �� ������������� ���� Strict
			 fHowToStrict != CNameSpaceTreeItem::ie_Strict ) {
		if ( prItem->GetNumItems() ) {
			// ���� � ���� ���� ���� - ������ �� ���� ��� ������ �����
			ScanChildrenAndSetStrict( hNode, prItem, ind, true, fHowToStrict );
		}
	}
#endif
}


// ���������� ��������� ������� ����
// ---
void CNameSpaceTree::CheckParentsStrict( HTREEITEM hNode ) {
#if 0	// Try avoid this logique
	HTREEITEM parentNode = GetParentItem( hNode );
	if ( parentNode ) {
		// ���� � ���� ���� ����

		int parentIndex = IndexNode( parentNode );
		CNameSpaceTreeItem *prItem = (CNameSpaceTreeItem *)(*m_Items)[parentIndex];

	// ���������� ���������� ���������� ������ ����� ����
		ScanChildrenAndSetStrict( parentNode, prItem, parentIndex );

	// ���������� ���������� ��������� �������� ����
		CheckParentsStrict( parentNode );
	}
#endif
}


// ---
int CNameSpaceTree::HowShouldItemBeChecked( CNameSpaceTreeItem *nsItem ) {
	return nsItem->GetChecked() == CCheckTreeItem::ie_Checked/* ||
				 nsItem->IsHasCheckedDescendants()*/
				 //clItem->GetChecked() == CCheckTreeItem::ie_SomeChecked		
				 ? CCheckTreeItem::ie_Unchecked
				 : CCheckTreeItem::ie_Checked;
}


// ---
int CNameSpaceTree::HowShouldItemBeStricted( CNameSpaceTreeItem *nsItem ) {
	return nsItem->GetStrict() == CNameSpaceTreeItem::ie_Strict/* ||
				 nsItem->IsHasStrictDescendants()*/
				 //clItem->GetStrict() == CCheckTreeItem::ie_SomeStrict		
				 ? CNameSpaceTreeItem::ie_NonStrict
				 : CNameSpaceTreeItem::ie_Strict;
}


// ---
void CNameSpaceTree::ScanChildrenForManuallyChecked( CNameSpaceTreeItem *prItem, int parentIndex ) {
	int firstChildLevel  = prItem->GetLevel() + 1;

	for ( int i=parentIndex+1,c=m_Items->GetSize(); i<c; i++ ) {
		CNameSpaceTreeItem *crItem = (CNameSpaceTreeItem *)(*m_Items)[i];
		if ( crItem->GetLevel() == firstChildLevel ) {

			crItem->SetManuallyChecked( false );
			ScanChildrenForManuallyChecked( crItem, i );
		}
		else  
			if ( crItem->GetLevel() < firstChildLevel )
				break;
	}
}


// ��������/��������� ����
// ---
void CNameSpaceTree::CheckNode( HTREEITEM hNode ) {
  int ind = IndexNode( hNode );
	CNameSpaceTreeItem *nsItem = (CNameSpaceTreeItem *)(*m_Items)[ind];

	nsItem->SetManuallyChecked( true );

	CCheckTreeItem::CieChecked fHowToCheck = CCheckTreeItem::CieChecked( HowShouldItemBeChecked(nsItem) );

	NSTMessageInfo info;

	info.m_nItemIndex = ind;
	info.m_Value.m_bSetRemove = !!fHowToCheck;//nsItem->IsChecked();

	BOOL bResult = TRUE;

	GetMessageReceiver()->SendMessage( NSTM_MANUALLYSETREMOVECHECKED, WPARAM(&bResult), LPARAM(&info) );

	if ( bResult ) {
		if ( fHowToCheck == CCheckTreeItem::ie_Unchecked && !nsItem->IsChecked() )
			ScanChildrenForManuallyChecked( nsItem, ind );

		SetItemChecked( ind, fHowToCheck, true );
	}
	else {
		// ������ - ��������� �������
		nsItem->SetManuallyChecked( false );
		nsItem->SetManuallyChecked( false );
	}

	PostMessage( mAfterChangeState, ind, LPARAM(0) );
}

// ---
void CNameSpaceTree::InternalSetItemChecked( CCheckTreeItem *item, 
																						 CCheckTreeItem::CieChecked fHowToChecked ) {
	if ( item->GetChecked() != fHowToChecked ) {
		NSTMessageInfo info;

		info.m_nItemIndex = IndexNode( item );
		info.m_Value.m_bSetRemove = !!fHowToChecked;

		BOOL bResult = TRUE;

		GetMessageReceiver()->SendMessage( NSTM_SETREMOVECHECKED, WPARAM(&bResult), LPARAM(&info) );

		if ( bResult ) 
			item->SetCheck( fHowToChecked );
	}
}


// ---
void CNameSpaceTree::ScanChildrenForManuallyStrict( CNameSpaceTreeItem *prItem, 
																										 int parentIndex ) {
	int firstChildLevel  = prItem->GetLevel() + 1;

	for ( int i=parentIndex+1,c=m_Items->GetSize(); i<c; i++ ) {
		CNameSpaceTreeItem *crItem = (CNameSpaceTreeItem *)(*m_Items)[i];
		if ( crItem->GetLevel() == firstChildLevel ) {

			crItem->SetManuallyStrict( false );
			ScanChildrenForManuallyStrict( crItem, i );
		}
		else  
			if ( crItem->GetLevel() < firstChildLevel )
				break;
	}
}


// ���������� Strict
// ---
void CNameSpaceTree::StrictNode( int iNodeIndex ) {
	CNameSpaceTreeItem *nsItem = (CNameSpaceTreeItem *)(*m_Items)[iNodeIndex];

	nsItem->SetManuallyStrict( true );

	CNameSpaceTreeItem::CieStrict fHowToStrict = CNameSpaceTreeItem::CieStrict( HowShouldItemBeStricted(nsItem) );

	NSTMessageInfo info;

	info.m_nItemIndex = iNodeIndex;
	info.m_Value.m_bSetRemove = !!fHowToStrict;

	BOOL bResult = TRUE;

	GetMessageReceiver()->SendMessage( NSTM_MANUALLYSETREMOVESTRICT, WPARAM(&bResult), LPARAM(&info) );

	if ( bResult ) {

		if ( fHowToStrict == CNameSpaceTreeItem::ie_NonStrict && !nsItem->IsStrict() )
			ScanChildrenForManuallyStrict( nsItem, iNodeIndex );

		SetItemStrict( iNodeIndex, fHowToStrict, true );
	}
	else {
		// ������ - ��������� �������
		nsItem->SetManuallyStrict( false );
		nsItem->SetManuallyStrict( false );
	}

	PostMessage( mAfterChangeState, iNodeIndex, LPARAM(0) );
}

// ---
int CNameSpaceTree::ItemCheckingAnalize( CCheckTreeItem *prItem ) {

/*
	if ( prItem->GetNumItemsChecked() || prItem->GetNumItemsSomeChecked() ) {
		// ���� ���������� ����
		if ( prItem->GetNumItems() == prItem->GetNumItemsChecked() ) 
			// ���� ��������� � ����������� ����� - �� ��������� �������
     	return CCheckTreeItem::ie_Checked;
		else 
			// ����� - �� ������� ����-����
     	return CCheckTreeItem::ie_SomeChecked;
	}
	else 
		// ����� �� �� �������
   	return CCheckTreeItem::ie_Unchecked;
*/
/*
	if ( prItem->GetNumItemsChecked() || prItem->GetNumItemsSomeChecked() ) 
		// ���� ���������� ����
   	return CCheckTreeItem::ie_SomeChecked;
	else 
		// ����� �� �� �������
   	return CCheckTreeItem::ie_Unchecked;
*/
/*
	CNameSpaceTreeItem *nsItem = (CNameSpaceTreeItem *)prItem;
	if ( nsItem->IsHasCheckedDescendants() )
   	return CCheckTreeItem::ie_SomeChecked;
	else
		return nsItem->GetChecked();
*/
   	return CCheckTreeItem::ie_Unchecked;
}

// ---
int CNameSpaceTree::ItemStrictAnalize( CNameSpaceTreeItem *prItem ) {
/*
#if 0 // ���������� ����������� Checked
	if ( numItemsStrict ) {
		// ���� ���������� ����
		if ( prItem->GetNumItems() == numItemsStrict ) 
			// ���� ��������� � ����������� ����� - �� ��������� �������
     	return CNameSpaceTreeItem::ie_Strict;
		else 
			// ����� - �� ������� ����-����
     	return CNameSpaceTreeItem::ie_SomeStrict;
	}
	else 
		// ����� �� �� �������
   	return CNameSpaceTreeItem::ie_NonStrict;
#else
	if ( numItemsStrict ) 
		// ���� ���������� ���� - �� ������� ����-����
    return CNameSpaceTreeItem::ie_SomeStrict;
	else 
		// ����� �� �� �������
   	return CNameSpaceTreeItem::ie_NonStrict;
#endif
*/
/*
	if ( prItem->GetNumItemsStrict() || prItem->GetNumItemsSomeStrict() ) {
		// ���� ���������� ����
		if ( prItem->GetNumItems() == prItem->GetNumItemsStrict() ) 
			// ���� ��������� � ����������� ����� - �� ��������� �������
     	return CNameSpaceTreeItem::ie_Strict;
		else 
			// ����� - �� ������� ����-����
     	return CNameSpaceTreeItem::ie_SomeStrict;
	}
	else 
		// ����� �� �� �������
   	return CNameSpaceTreeItem::ie_NonStrict;
*/

/*
	if ( prItem->GetNumItemsStrict() || prItem->GetNumItemsSomeStrict() ) 
		// ���� ���������� ����
   	return CNameSpaceTreeItem::ie_SomeStrict;
	else 
		// ����� �� �� �������
   	return CNameSpaceTreeItem::ie_NonStrict;
*/
   	return CNameSpaceTreeItem::ie_NonStrict;
}


#define CTreeCtrl CCheckTree
BEGIN_MESSAGE_MAP(CNameSpaceTree, CTreeCtrl)
#undef CTreeCtrl
	//{{AFX_MSG_MAP(CNameSpaceTree)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemExpanding)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
	ON_WM_RBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(TVN_SELCHANGING, OnSelChanging)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelChanged)
	ON_WM_DESTROY()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_REGISTERED_MESSAGE(mAfterChangeState,  OnAfterChangeState)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNameSpaceTree message handlers
// ---
int CNameSpaceTree::OnCreate( LPCREATESTRUCT lpCreateStruct ) {
	if (CCheckTree::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if ( !::IsDlgClassName(*GetParent()) ) 
		SetShowSelectionAlways( fShowSelectionAlways );

	SendMessage( CCM_SETVERSION, COMCTL32_VERSION, 0 );

	return 0;
}

// ---
void CNameSpaceTree::OnItemExpanding( NMHDR* pNMHDR, LRESULT* pResult ) {
	SetRedraw( FALSE );

	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	HTREEITEM hNode = pNMTreeView->itemNew.hItem;
	ASSERT( hNode != NULL);
	
	CNameSpaceTreeItem *nsItem = (CNameSpaceTreeItem *)GetItemData( hNode );

	nsItem->SetExpanded( pNMTreeView->action == TVE_EXPAND );
	
	*pResult = 0;

	if ( pNMTreeView->action == TVE_EXPAND ) {
		HTREEITEM hChildNode = GetChildItem( hNode );

		if ( hChildNode ) {
			CNameSpaceTreeItem *nsChildItem = (CNameSpaceTreeItem *)GetItemData( hChildNode );
			if ( nsChildItem->IsDummy() ) {
				m_Items->RemoveAt( IndexNode(hChildNode) );
				DeleteItem( hChildNode );
				hChildNode = NULL;
			}
		}

		if ( !hChildNode ) {

			NSTMessageInfo info;

			info.m_nItemIndex = IndexNode( hNode );

			BOOL bResult = TRUE;

			SetCursor( LoadCursor(NULL, IDC_WAIT) );

			GetMessageReceiver()->SendMessage( NSTM_LOADSUBTREE, WPARAM(&bResult), LPARAM(&info) );
/*
			if ( IsLeaf(hNode) )
				// � ���������� ��������� � �������� ����� �� ��������� �����
				SetItemImage( hNode, nsItem->GetNormalIconIndex(), nsItem->GetNormalIconIndex() );
			else
				SetItemImage( hNode, nsItem->GetSelectedIconIndex(), nsItem->GetSelectedIconIndex() );
*/
			// CCheckTree ��������� State images
			SetNodeImage( nsItem, hNode );

			if ( !nsItem->IsExpanded() )
				*pResult = 1;
		}
	}
/*
	if ( pNMTreeView->action == TVE_COLLAPSE ) 
    SetItemImage( hNode, nsItem->GetNormalIconIndex(), nsItem->GetNormalIconIndex() );
*/	
}


// ---
void CNameSpaceTree::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags ) {
	if ( nChar == VK_MULTIPLY/*'*'*/ ) {
		NSTMessageInfo info;
		info.m_nItemIndex = GetSelectedIndex();
		info.m_Value.m_bSetRemove = TRUE;
		GetMessageReceiver()->SendMessage( NSTM_FULLEXPANDING, WPARAM(NULL), LPARAM(&info) );
	}
	
	CCheckTree::OnKeyDown(nChar, nRepCnt, nFlags);
	
	if ( nChar == VK_MULTIPLY/*'*'*/ ) {
		NSTMessageInfo info;
		info.m_nItemIndex = GetSelectedIndex();
		info.m_Value.m_bSetRemove = FALSE;
		GetMessageReceiver()->SendMessage( NSTM_FULLEXPANDING, WPARAM(NULL), LPARAM(&info) );
	}
}


// ---
void CNameSpaceTree::OnItemExpanded( NMHDR* pNMHDR, LRESULT* pResult ) {
	CCheckTree::OnItemExpanded( pNMHDR, pResult );

	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	SetCursor( NULL );

	HTREEITEM hNode = pNMTreeView->itemNew.hItem;
	ASSERT( hNode != NULL);
	
	NSTMessageInfo info;

	info.m_nItemIndex = IndexNode( hNode );
	info.m_Value.m_bSetRemove = pNMTreeView->action == TVE_EXPAND;
	
	GetMessageReceiver()->SendMessage( NSTM_ITEMEXPANDING, WPARAM(0), LPARAM(&info) );

	SetRedraw( TRUE );

	*pResult = 0;
}


// ---
void CNameSpaceTree::OnLButtonDown( UINT nFlags, CPoint point ) {
	// TODO: Add your message handler code here and/or call default
	
	// ����� ����� ��� ������
	SetFocus();
  
	CCheckTree::OnLButtonDown(nFlags, point);
}


// ---
void CNameSpaceTree::OnRButtonDown( UINT nFlags, CPoint point ) {
	// TODO: Add your message handler code here and/or call default

	SetFocus();
  
	HTREEITEM selection = HitTest( point );

  if ( selection ) 
    SelectItem( selection );
    
   // but don't call default.... otherwise WM_CONTEXTMENU is NOT sent
   // CTreeCtrl::OnRButtonDown( nFlags, point );
}

// ---
void CNameSpaceTree::OnContextMenu( CWnd* pWnd, CPoint point ) {
	CRect rcClient;
	GetClientRect( &rcClient );
	CPoint rcRPoint( point );
	ScreenToClient( &rcRPoint );
	if ( rcClient.PtInRect(rcRPoint) )
		CreateAndTrackPopupMenu( point );
	else
		CCheckTree::OnContextMenu( pWnd, point );
}


// ---
void CNameSpaceTree::InsideImageClickImitate( HTREEITEM hItemOnWhich ) {
	CImageList *pImgNormal = GetImageList( TVSIL_NORMAL );		
	ASSERT( pImgNormal );

	IMAGEINFO imageInfoNormal;
	pImgNormal->GetImageInfo( 0, &imageInfoNormal );		

	CImageList *pImgState = GetImageList( TVSIL_STATE );		
	ASSERT( pImgState );

	IMAGEINFO imageInfoState;
	pImgState->GetImageInfo( 0, &imageInfoState );		

	CRect rect;
	GetItemRect( hItemOnWhich, &rect, TRUE );
	rect.right = (rect.left - 2) - (imageInfoNormal.rcImage.right - 2);		
	rect.left -= (imageInfoState.rcImage.right + 2) + (imageInfoNormal.rcImage.right + 2);					

	CPoint point = rect.TopLeft(); 
	point.Offset( rect.Width() >> 1, rect.Height() >> 1 );    

	PostMessage( WM_LBUTTONDOWN, 0, MAKELPARAM(point.x, point.y) );
	PostMessage( WM_LBUTTONUP  , 0, MAKELPARAM(point.x, point.y) );
}


// ---
void CNameSpaceTree::CreateAndTrackPopupMenu( CPoint& point ) {
  HTREEITEM hSelectedItem = GetSelectedItem();
	if ( hSelectedItem ) {
		CNameSpaceTreeItem *nsItem = (CNameSpaceTreeItem *)GetItemData( hSelectedItem );
		int ind = IndexNode( hSelectedItem );

		if (point.x == -1 && point.y == -1) {
		 //keystroke invocation      
			CRect itemRect;
			GetItemRect( hSelectedItem, &itemRect, TRUE );
			ClientToScreen( itemRect );
    
			point = itemRect.TopLeft(); 
			point.Offset( itemRect.Width() >> 1, itemRect.Height() >> 1 );    
		} 

		CODMenu menu(this);
		menu.CreatePopupMenu();

		CString menuItemName;
		if ( nsItem->GetNumItems() ) {
			if ( IsExpanded(hSelectedItem) ) {
				menuItemName.LoadString( IDS_WAS_COLLAPSENODE );
				menu.AppendMenu( MF_STRING, IDS_WAS_COLLAPSENODE, menuItemName );
			}
			else {
				menuItemName.LoadString( IDS_WAS_EXPANDNODE );
				menu.AppendMenu( MF_STRING, IDS_WAS_EXPANDNODE, menuItemName );
			}
		}

		CCheckTreeItem::CieChecked fHowToCheck = CCheckTreeItem::CieChecked( HowShouldItemBeChecked(nsItem) );

		switch ( fHowToCheck ) {
			case CCheckTreeItem::ie_Checked :
				menuItemName.LoadString( IDS_WAS_CHECKNODE );
				menu.AppendMenu( MF_STRING | (!IsEnableChangeItemsState() ? (MF_DISABLED|MF_GRAYED) : 0), IDS_WAS_CHECKNODE, menuItemName );
				break;
			case CCheckTreeItem::ie_Unchecked :
				menuItemName.LoadString( IDS_WAS_UNCHECKNODE );
				menu.AppendMenu( MF_STRING | (!IsEnableChangeItemsState() ? (MF_DISABLED|MF_GRAYED) : 0), IDS_WAS_UNCHECKNODE, menuItemName );
				break;
		}

		CNameSpaceTreeItem::CieStrict fHowToStrict = CNameSpaceTreeItem::CieStrict( HowShouldItemBeStricted(nsItem) );

		switch ( fHowToStrict ) {
			case CNameSpaceTreeItem::ie_Strict :
				menuItemName.LoadString( IDS_WAS_SETSTRICT );
				menu.AppendMenu( MF_STRING | (!IsEnableChangeItemsState() ? (MF_DISABLED|MF_GRAYED) : 0), IDS_WAS_SETSTRICT, menuItemName );
				break;
			case CNameSpaceTreeItem::ie_NonStrict :
				menuItemName.LoadString( IDS_WAS_REMOVESTRICT );
				menu.AppendMenu( MF_STRING | (!IsEnableChangeItemsState() ? (MF_DISABLED|MF_GRAYED) : 0), IDS_WAS_REMOVESTRICT, menuItemName );
				break;
		}


		NSTMessageInfo info;

		info.m_nItemIndex = ind;
		info.m_Value.m_hMenu = (HMENU)menu;

		BOOL bResult = TRUE;

		GetMessageReceiver()->SendMessage( NSTM_PREPROCESSCONTEXTMENU, WPARAM(&bResult), LPARAM(&info) );

		if ( bResult && menu.GetMenuItemCount() ) {
			menu.SynchronizeMenu();

			menu.LoadToolbar( IDR_WAS_TOOLBAR );

			bResult = FALSE;
			info.m_Value.m_ToolBarStuff[0] = 0;
			info.m_Value.m_ToolBarStuff[1] = 0;

			GetMessageReceiver()->SendMessage( NSTM_GETMENUTOOLBAR, WPARAM(&bResult), LPARAM(&info) );
			if ( bResult && info.m_Value.m_ToolBarStuff[0] ) {
				HINSTANCE hOldResModule = ::AfxGetResourceHandle();
				if ( info.m_Value.m_ToolBarStuff[1] )
					::AfxSetResourceHandle( HINSTANCE(info.m_Value.m_ToolBarStuff[1]) ); 

				menu.LoadToolbar( info.m_Value.m_ToolBarStuff[0] );

				::AfxSetResourceHandle( hOldResModule ); 
			}

//			GetMessageReceiver()->SendMessage( WM_INITMENUPOPUP, (WPARAM)(HMENU)menu, 0 );

			UINT nSelected = menu.TrackPopupMenu( TPM_RETURNCMD|TPM_NONOTIFY|TPM_LEFTALIGN|TPM_RIGHTBUTTON,
																								point.x, point.y, this ); 
			menu.DestroyMenu();

			switch ( nSelected ) 	{
				case IDS_WAS_EXPANDNODE :
					  SendMessage( WM_KEYDOWN, VK_ADD );
						break;
				case IDS_WAS_COLLAPSENODE :
					  SendMessage( WM_KEYDOWN, VK_SUBTRACT );
						//Expand( hSelectedItem, TVE_TOGGLE );
						break;
				case IDS_WAS_CHECKNODE   :
				case IDS_WAS_UNCHECKNODE : 
						InsideImageClickImitate( hSelectedItem );
						break;
				case IDS_WAS_SETSTRICT    :
				case IDS_WAS_REMOVESTRICT : 
						StrictNode( ind );
						break;
				case 0:
						//user selected nothing
						break;
				default: {
						NSTMessageInfo info;

						info.m_nItemIndex = ind;
						info.m_Value.m_iCommandId = nSelected;

						BOOL bResult = TRUE;

						GetMessageReceiver()->SendMessage( NSTM_DOCONTEXTMENUCOMMAND, WPARAM(&bResult), LPARAM(&info) );

						PostMessage( mAfterChangeState, info.m_nItemIndex, LPARAM(0) );
				}
						break;
			}
		}
		else
			menu.DestroyMenu();
	}
}


// ---
void CNameSpaceTree::OnSelChanging( NMHDR* pNMHDR, LRESULT* pResult ) {
	CCheckTree::OnSelChanging( pNMHDR, pResult );
	if ( !*pResult ) {
		NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

		if ( m_Items && m_Items->GetSize() && IsPossibleRedraw() ) {
			BeginWaitCursor(); 
			//SetCursor( LoadCursor(NULL, IDC_WAIT) );

			NSTMessageInfo info;

			info.m_nItemIndex = IndexNode( pNMTreeView->itemOld.hItem );
			info.m_Value.m_bSetRemove = FALSE;

			GetMessageReceiver()->SendMessage( NSTM_ITEMSELCHANGING, WPARAM(0), LPARAM(&info) );
		}			
		*pResult = 0;
	}
}


// ---
void CNameSpaceTree::OnSelChanged( NMHDR* pNMHDR, LRESULT* pResult ) {
	CCheckTree::OnSelChanged( pNMHDR, pResult );
	if ( !*pResult ) {
		NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
		
		if ( m_Items && m_Items->GetSize() && IsPossibleRedraw() ) {
			NSTMessageInfo info;

			info.m_nItemIndex = IndexNode( pNMTreeView->itemNew.hItem );
			info.m_Value.m_bSetRemove = TRUE;

			GetMessageReceiver()->SendMessage( NSTM_ITEMSELCHANGING, WPARAM(0), LPARAM(&info) );

			if ( info.m_nItemIndex >= 0 )
				SetNodeImage( (*m_Items)[info.m_nItemIndex], pNMTreeView->itemNew.hItem );
			
			EndWaitCursor(); 
			//SetCursor( 0 );
		}			
		*pResult = 0;
	}
}


// ---
void CNameSpaceTree::OnDestroy() {
	GetMessageReceiver()->SendMessage( NSTM_WINDOWSHUTDOWN, WPARAM(0), LPARAM(0) );

	CCheckTree::OnDestroy();
}

// ---
void CNameSpaceTree::OnKillFocus( CWnd* pNewWnd ) {
	CCheckTree::OnKillFocus(pNewWnd);	

	NSTMessageInfo info;

	info.m_nItemIndex = GetSelectedIndex();
	info.m_Value.m_bSetRemove = FALSE;

	GetMessageReceiver()->SendMessage( NSTM_FOCUSCHANGING, WPARAM(HWND(*pNewWnd)), LPARAM(&info) );
}

// ---
void CNameSpaceTree::OnSetFocus( CWnd* pOldWnd ) {
	CCheckTree::OnSetFocus(pOldWnd);

	NSTMessageInfo info;

	info.m_nItemIndex = GetSelectedIndex();
	info.m_Value.m_bSetRemove = TRUE;

	GetMessageReceiver()->SendMessage( NSTM_FOCUSCHANGING, WPARAM(HWND(*pOldWnd)), LPARAM(&info) );
}


// ---
LRESULT CNameSpaceTree::OnAfterChangeState( WPARAM wParam, LPARAM lParam ) {
	NSTMessageInfo info;

	info.m_nItemIndex = int(wParam);

	BOOL bResult = TRUE;

	GetMessageReceiver()->SendMessage( NSTM_STATECHANGED, WPARAM(&bResult), LPARAM(&info) );

	return 0;
}

// ---
void CNameSpaceTree::OnCustomDraw( NMHDR* pNMHDR, LRESULT* pResult ) {
	*pResult = 0;
	LPNMTVCUSTOMDRAW lpNMCustomDraw = (LPNMTVCUSTOMDRAW)pNMHDR;
	switch ( lpNMCustomDraw->nmcd.dwDrawStage ) {
		case CDDS_PREPAINT :
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;
		case CDDS_ITEMPREPAINT : {
			*pResult = CDRF_DODEFAULT;
			HTREEITEM hNode = (HTREEITEM)lpNMCustomDraw->nmcd.dwItemSpec;
			if ( hNode ) {
				CNameSpaceTreeItem *nsItem = (CNameSpaceTreeItem *)GetItemData( hNode );
				if ( nsItem ) {
					if ( !nsItem->IsEnabled() )
						lpNMCustomDraw->clrText = ::GetSysColor( COLOR_GRAYTEXT );
					HFONT hFont = nsItem->GetFont();
					if ( hFont ) {
						HFONT hOldFont = (HFONT)::SelectObject( lpNMCustomDraw->nmcd.hdc, hFont );
						if ( !m_hOldFont )
							m_hOldFont = hOldFont;
						*pResult = CDRF_NEWFONT;
					}
				}
			}
			break;
		}
	}
}



