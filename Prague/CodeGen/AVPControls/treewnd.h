#if !defined(AFX_TREEWND_H__788BF3C5_94F2_11D2_96B0_00104B5B66AA__INCLUDED_)
#define AFX_TREEWND_H__788BF3C5_94F2_11D2_96B0_00104B5B66AA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxcmn.h>
#include <Stuff\PArray.h>
#include <Stuff\PSynArr.h>
#include <Stuff\SArray.h>
#include <Stuff\StdDefs.h>

#if (_WIN32_IE < 0x0500)
#define COMCTL32_VERSION  5
#define CCM_SETVERSION          (CCM_FIRST + 0x7)
#define CCM_GETVERSION          (CCM_FIRST + 0x8)
#define CCM_SETNOTIFYWINDOW     (CCM_FIRST + 0x9) // wParam == hwndParent.
#endif // (_WIN32_IE < 0x0500)  

// TreeWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreeWnd window

class CTreeWnd;

typedef void (*TvActionFunc)( CTreeWnd &owner, HTREEITEM cur, int ind, void *par );
typedef bool (*TvCondFunc)( CTreeWnd &owner, HTREEITEM cur, int ind, void *par );

// ---
struct CTreeItemInfo : public TV_INSERTSTRUCT {
	int level;
	CTreeItemInfo( LPCTSTR lpszItem, int nLevel ) :
		level( nLevel ) {

		item.mask = TVIF_TEXT;
		item.pszText = (LPTSTR)lpszItem;
	}
};

// ---
class CTreeWnd : public CTreeCtrl {
  HTREEITEM lastAddNode;
	int       notRedrawCount;
  int       lastAddLevel;
	uint8     m_bDeleteCollapsedSubTree : 1;
	uint8			m_bPossibleRedraw : 1;

// Construction
public:
	CTreeWnd();

// Attributes
public:

// Operations
public:

	void      SetDeleteCollapsed( bool set = true ) { m_bDeleteCollapsedSubTree = set; }
	bool      IsDeleteCollapsed()										{ return m_bDeleteCollapsedSubTree; }

	void      SetPossibleRedraw( bool set = true )  { m_bPossibleRedraw = set; }
	bool      IsPossibleRedraw()										{ return m_bPossibleRedraw; }

	HTREEITEM AddNode( CTreeItemInfo &newNode, HTREEITEM addAfter = NULL ); // �������� ���� (������������� ����������� �� �������� ������)
	HTREEITEM InsertNode( CTreeItemInfo &newNode, HTREEITEM addAfter );
  void      DeleteSubTree( HTREEITEM node, bool bRootIncluded = false );	// ������� ��������� ������� ����
	void 			ExpandNode( int ind );                   // �������� ���� �� �������
	void			CollapseNode( int ind );    						 // ������� ���� �� �������    
	void 			SelectNode( int ind );									 // ������������� ���� �� �������
	int  			GetSelectedIndex();											 // ������ ������ ���������������� ����
	bool 			IsExpanded( int ind );                   // ������� �� ���� � �������� ��������
	bool 			IsExpanded( HTREEITEM node );            // ������� �� ����
  bool 			IsNodeVisible( int ind );                // ����� �� ���� � �������� ��������
	void 			SetNodeData( uint32 data, int ind );     // ���������� ������ ����
	uint32 		GetNodeData( int ind );                  // ������ ������ ����
  bool    	IsLeaf( int ind );                                  // �������� �� ���� ��������
  bool    	IsLeaf( HTREEITEM node );                           // �������� �� ���� ��������
  HTREEITEM ItemFromMousePos();                                 // ������ ���� ��� �������� ����

  void      ForEach( TvActionFunc action, void *param = NULL, HTREEITEM fromNode = NULL ); // �������� "�� ����"
  HTREEITEM FirstThat( TvCondFunc action, void *param = NULL, HTREEITEM fromNode = NULL ); // �������� "�� ������� ���"

	void      NewLoadSession() { lastAddNode = NULL; lastAddLevel = 0; }

	virtual int				IndexNode( HTREEITEM node );                        // ������ ������ ������� ����
	virtual HTREEITEM NodeByIndex( int ind );                             // ������ ���� �� ��������� �������

	void      SetRedraw( BOOL bRedraw );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeWnd();

	// Generated message map functions
protected:
					int 			GetNodeLevel( int ind );                            // ������ ������� ���� �� �������
					int 			GetNodeLevel( HTREEITEM node );                     // ������ ������� ����
					bool			HasStyle( uint32 mask );
					HTREEITEM AddItemChild( HTREEITEM node, CTreeItemInfo &newNode ); // �������� item � ������
					HTREEITEM InsertItemChild( HTREEITEM hParentNode, HTREEITEM hAfterNode, CTreeItemInfo &newNode );

	//{{AFX_MSG(CTreeWnd)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	HTREEITEM RecourseEnumeration ( HTREEITEM node, int &index );
	bool			RecourseEnumeration ( HTREEITEM node, HTREEITEM find, int &index );
	bool			RecourseEnumeration ( HTREEITEM node, int findInd, int &index, int &level );
	HTREEITEM ForEachEnumeration  ( HTREEITEM node, TvActionFunc action, void *param, int &index );
	HTREEITEM FirstThatEnumeration( HTREEITEM node, TvCondFunc action, void *param, int &index, bool &result );
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CCheckTree window

#define CTIS_BOLD      (0x00000001)
#define CTIS_ITALIC    (0x00000002)
#define CTIS_UNDERLINE (0x00000004)
#define CTIS_STRIKEOUT (0x00000008)

// ---
struct CCTFontCacheItem {
	HFONT  m_hFont;
	DWORD  m_dwStyle;
	CCTFontCacheItem( HFONT hFont, DWORD dwStyle ) :
		m_hFont( hFont ),
		m_dwStyle( dwStyle ) {}
};


// ---
class CCTFontCache : public CSArray<CCTFontCacheItem> {
public :
	CCTFontCache() : CSArray<CCTFontCacheItem> (0, 1) {}
	HFONT Find( DWORD dwStyle );
	void  Flush();
};

class CCheckTree;

// ���������� ���� �����
// ---
class CCheckTreeItem {
protected :
  CString   m_Text;									// ����� ����
	HTREEITEM m_TreeItem;							// ���� ������
	HFONT     m_Font;                 // ����� ����������� ����
  int       m_Level;								// ������� ����
  int       m_NumItems;							// ���������� ������������ � ����
  int       m_NumItemsChecked;			// ���������� ���������� ������������ � ����
  int       m_NumItemsSomeChecked;  // ���������� ������� ���������� ������������ � ����
	int       m_ImageIndex;						// ������ � Image-�����
	int       m_CurrImageIndex;				// ������� ������ � Image-�����
	void		 *m_Data;									// ������ ����
  uint8     fChecked					: 2;	// �������/��������/������� �������
	uint8			fEnabled					: 1;	// ��������
  uint8     fNode							: 1;	// �������� �����
  uint8     fExpanded					: 1;	// �������
  uint8     fSelected					: 1;	// ������������
  uint8     fFirstVisible			: 1;	// ������ �������
	uint8     fMarkable					: 1;	// ����� ����������/�����������
	uint8			fOwnsData					: 1;  // ������� ������� (��� �������)
	uint8     fStrictlyDisabled : 1;	// ������ ��������

public:
    typedef enum {
      ie_Unchecked = 0,
      ie_Checked,
      ie_SomeChecked
    } CieChecked;

    typedef enum {
			ii_LeafUnchecked = 0,		// 0
			ii_LeafChecked,					// 1
			ii_NodeUnchecked,				// 2
			ii_NodeChecked,					// 3
			ii_NodeSomeChecked,			// 4
			ii_LastIndex,						// 5
		} CieImageIndex;

		CCheckTreeItem();
    virtual ~CCheckTreeItem();

		virtual bool operator == ( const CCheckTreeItem &rItem );
		virtual bool operator != ( const CCheckTreeItem &rItem ) { return !operator == ( rItem ); }

		virtual CCheckTreeItem *operator = ( const CCheckTreeItem &rItem ) { Assign( rItem ); return this; }
		virtual void Assign( const CCheckTreeItem &rItem );

		virtual CCheckTreeItem *Duplicate();

		void       SetFont( HFONT hFont )										 { m_Font = hFont; }
		HFONT      GetFont()																 { return m_Font; }

    CieChecked GetChecked() const 										   { return CieChecked(fChecked); }
    bool       IsChecked() const 										     { return !!fChecked; }
    void 			 Toggle()         				  						   { fChecked = !fChecked; }
    void 			 SetCheck( CieChecked check = ie_Checked ) { fChecked = uint8(check); }
    void 			 Check( bool check = true ) 							 { fChecked = uint8(check ? ie_Checked : ie_Unchecked); }

    void 			 SetLevel( int lvl )        							 { m_Level   = lvl; }
    int  			 GetLevel() const           							 { return m_Level; }

    void 			 SetText( const CString &setText );
    CString	  &GetText();

    void 			 SetTreeItem( HTREEITEM hItem )    				 { m_TreeItem   = hItem; }
    HTREEITEM  GetTreeItem() const           						 { return m_TreeItem; }

		void       SetEnabled( bool set = true )						 { fEnabled = set; }
    bool       IsEnabled()															 { return !!fEnabled; } 

    void       SetNode( bool set = true )								 { fNode = set; if ( IsMarkable() ) SetImageIndex( set ? ii_NodeUnchecked : ii_LeafUnchecked ); }
    bool       IsNode()																	 { return !!fNode; } 

    void       SetExpanded( bool set = true )						 { fExpanded = set; }
    bool       IsExpanded()															 { return !!fExpanded; } 

    void       SetSelected( bool set = true )						 { fSelected = set; }
    bool       IsSelected()															 { return !!fSelected; } 

    void       SetFirstVisible( bool set = true )				 { fFirstVisible = set; }
    bool       IsFirstVisible()													 { return !!fFirstVisible; } 

    void       SetMarkable( bool set = true )						 { fMarkable = set; }
    bool       IsMarkable()															 { return !!fMarkable; } 

    int        GetNumItems()														 { return m_NumItems; }
    void       SetNumItems( int _numItems )							 { m_NumItems = _numItems; }

    int        GetNumItemsChecked()											 { return m_NumItemsChecked; }
    void       SetNumItemsChecked( int _numItems )			 { m_NumItemsChecked = _numItems; }

    int        GetNumItemsSomeChecked()									 { return m_NumItemsSomeChecked; }
    void       SetNumItemsSomeChecked( int _numItems )	 { m_NumItemsSomeChecked = _numItems; }

		virtual int		GetImageIndex();
		void			 SetImageIndex( int iImageIndex )					 { m_ImageIndex = iImageIndex; }

		void			 SetCurrImageIndex( int iCurrImageIndex )		{ m_CurrImageIndex = iCurrImageIndex; }
		int 			 GetCurrImageIndex()                       	{ return m_CurrImageIndex; }

		void       SetData( void *pData, bool bOwnsData )		 { m_Data = pData; SetOwnsData( bOwnsData ); }
		void      *GetData()																 { return m_Data; }	

		void       SetOwnsData( bool set = true )						 { fOwnsData = set; }
		bool       IsOwnsData()															 { return !!fOwnsData; } 

		void       SetStrictlyDisabled( bool set = true )		 { fStrictlyDisabled = set; }
		bool       IsStrictlyDisabled()											 { return !!fStrictlyDisabled; } 

		virtual bool CanChangeChecked()												{ return true; } 

    friend class CCheckTree; 
};


// ---
class CCTItemsArray : public CPSyncArray<CCheckTreeItem> {
public :
	CCTItemsArray( bool owns = true );
	~CCTItemsArray();

	void SetOwns( bool owns = true ) { OwnsElem(owns); }
	bool GetOwns() const { return OwnsElem(); }

	void RemoveAt( int nIndex );
	int  FindIt( CCheckTreeItem *item );

	void InsertAt( int nIndex, CCTItemsArray *pNewArray );
	void InsertAt( int nIndex, CCheckTreeItem *pNewItem );

	int  GetSize() const { return Count(); }
	int  GetUpperBound() const { return MaxIndex(); }

	bool operator == ( const CCTItemsArray &rItems );
	bool operator != ( const CCTItemsArray &rItems ) { return !operator == ( rItems ); }
	void operator = ( const CCTItemsArray &rItems );
};


// ---
class CCheckTree : public CTreeWnd {
protected :
	CWnd					 *m_MsgReceiver;
	HACCEL					m_hAccelTable;
	bool            m_bAccelTableShouldBeDestroyed;
	bool            m_bInterfaceLocked;
	int             m_nInterfaceLockCount;
	CCTItemsArray  *m_Items;
  CImageList			m_ImageList;
	int							m_nFirstVisibleInd;
	CCTFontCache		m_FontCache;
	HFONT           m_hOldFont;

	uint8           fSpreadMark							: 1; // �������������� ���������� ���� � �����
	uint8						fStateImageType					: 1; // Image ���� State
	uint8           fOwnsItemsArray					: 1; // ������� (��� ����������) ������ ���������
	uint8           fSetupImagesAtLoad			: 1; // ������������� ����� ��� ��������
	uint8						fEnableOpOnDisabled			: 1; // ��������� �������� �� ����������� ����
	uint8						fEnableChangeItemsState	: 1; // ��������� ��������� ��������� ���������
	uint8						fUseCheckSemantic				: 1; // ������������ ��������� CheckTree
	uint8						fEnablePostLoadProcessing : 1; // ��������� ��������� ����� ��������

// Construction
public:
	CCheckTree();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckTree)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual COLORREF SetBkColor( COLORREF crColor );
	protected:
	virtual void PreSubclassWindow();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCheckTree();

	void SetSpreadMark( bool set = true )        { fSpreadMark = set; }
  bool IsSpreadMark()                          { return !!fSpreadMark; } 

	void SetOwnsItemsArray( bool set = true )    { fOwnsItemsArray = set; }
  bool IsOwnsItemsArray()                      { return !!fOwnsItemsArray; } 

	void SetStateImageType( bool set = true )    { fStateImageType = set; }
  bool IsStateImageType()                      { return !!fStateImageType; } 

	void SetSetupImagesAtLoad( bool set = true )   { fSetupImagesAtLoad = set; }
  bool IsSetupImagesAtLoad()                     { return !!fSetupImagesAtLoad; } 

	void SetEnableOpOnDisabled( bool set = true ) { fEnableOpOnDisabled = set; }
	bool IsEnableOpOnDisabled()								    { return !!fEnableOpOnDisabled; } 

	void SetEnableChangeItemsState( bool set = true ) { fEnableChangeItemsState = set; }
	bool IsEnableChangeItemsState()								    { return !!fEnableChangeItemsState; } 

	void SetUseCheckSemantic( bool set = true ) { fUseCheckSemantic = set; }
	bool IsUseCheckSemantic()								    { return !!fUseCheckSemantic; } 

	void SetEnablePostLoadProcessing( bool set = true );
	bool IsEnablePostLoadProcessing();

	void	SetItemsArray( CCTItemsArray *itemsArray );									// ���������� ����� ������ ������������
	// ���������� ����� ������ ������������, ������� � ��������� �������
	void	UpdateItemsArray( int fromIndex, CCTItemsArray &itemsArray, bool bRootInserted = false );
	void	UpdateItemsArrayByRange( int fromIndex, int toIndex, CCTItemsArray &itemsArray );
	
	// ��������� ��������� �������������
	void  StartupInitiation();

	// �������� ������ ���������
	CCTItemsArray *GetItemsArray() { return m_Items; }

	// ������� ������ ������������� ��������
	int  GetParentIndex( int nItemIndex );

	// ������� ������ �������� ��������
	int  GetFirstVisibleIndex();

	// ������� ������ ������� ��������� ��������
	int  GetFirstChildIndex( int nItemIndex );

	// ������� ������ ���������� ��������� ��������
	int  GetNextSiblingIndex( int nItemIndex );

	virtual int				IndexNode( HTREEITEM node );                     // ������ ������ ������� ����
	        int				IndexNode( CCheckTreeItem *item );                        // ������ ������ ������� ����
	virtual HTREEITEM NodeByIndex( int ind );                          // ������ ���� �� ��������� �������

	// ���������� ������� Checked �� �������
  void SetItemChecked( int iItemIndex, CCheckTreeItem::CieChecked fHowToChecked, bool bSpreadAutomatically = false ); 
	virtual void InternalSetItemChecked( CCheckTreeItem *item, CCheckTreeItem::CieChecked fHowToChecked );
	
	// �������� ����� ������� �� �����������, ������� � ��������� ������� ����
	int AddItemToParent( CCheckTreeItem *pNewItem, int parentIndex = -1 );

	// �������� ����� ������� �� �����������, ������� � ��������� ������� ���� ����� �������� ��������
	int InsertItemToParent( CCheckTreeItem *pNewItem, int parentIndex, int indexBefore );

	// ������� ������� �� ���� ����������, ������� � ��������� ������� 
	void DeleteItemWithSubtree( int nFromIndex );

	// ���������� ����� �� �������
	void SetTreeItemText( int nItemIndex, const CString &rcText );

	// ������������/�����
  void      ForEach( TvActionFunc action, void *param = NULL, int indFromNode = -1 ); // �������� "�� ����"
  int       FirstThat( TvCondFunc action, void *param = NULL, int indFromNode = -1 ); // �������� "�� ������� ���"

	CWnd *GetMessageReceiver();
	void  SetMessageReceiver( CWnd *pReceiver ) { m_MsgReceiver = pReceiver; }

	void   SetAccelTable( HACCEL	hAccelTable, bool bShouldBeDestroyed = false );

// ������ ��� ����������� �������������
	// �������� ���� ��������� ������� ����
	virtual void CheckParents( HTREEITEM node );	
	// �������� ���� ����� ������� ����
	virtual void CheckChildren( HTREEITEM node, int ind, CCheckTreeItem::CieChecked fHowToChecked, bool bSetCheck = true );
	// ���������� Images ����
	virtual void SetNodeImage( CCheckTreeItem *item, HTREEITEM hNode );

	       	void SetupImages( HTREEITEM fromNode = NULL );

					void SetNodeFont( CCheckTreeItem *item, HFONT hFont ) { item->SetFont(hFont); }
					void SetNodeStyle( CCheckTreeItem *item, DWORD dwStyle );

					void LockInterface( bool bLock );

private :
	// ��������� ������ ����� ��������� ����
	void LoadTreeWindow(  HTREEITEM loadAfter = NULL, bool bRootInserted = false ); 
	void LoadTreeWindow( int fromIndex, int toIndex, HTREEITEM hParent, HTREEITEM addAfter );

protected :
	virtual void			CreateImageList();        // ������� ImageList
	virtual HTREEITEM AddItem( CCheckTreeItem *item, HTREEITEM addAfter ); // �������� ���� (������������� ����������� �� �������� ������)
	virtual HTREEITEM InsertItem( CCheckTreeItem *item, HTREEITEM addAfter );
	virtual void			PostLoadProcessing();		 // �������������� ��������� ����� �������� ������
	virtual void			CheckNode( HTREEITEM node );										 // �������� ����
	virtual int				ItemCheckingAnalize( CCheckTreeItem *item );
	
	       	void SetupNodes( HTREEITEM fromNode = NULL );
					void SetupInternalInfo();


	// Generated message map functions
protected:
	//{{AFX_MSG(CCheckTree)
	afx_msg void		OnNcLButtonDown( UINT nFlags, CPoint point );
	afx_msg void		OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void		OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void		OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void		OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void		OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void		OnItemExpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void		OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void		OnDestroy();
	afx_msg LRESULT OnAfterLoadExpanding( WPARAM wParam, LPARAM lParam );
	afx_msg void		OnSelChanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void		OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int			OnMouseActivate( CWnd* pDesktopWnd, UINT nHitTest, UINT message );
	afx_msg LRESULT OnSetRedraw( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEWND_H__788BF3C5_94F2_11D2_96B0_00104B5B66AA__INCLUDED_)
