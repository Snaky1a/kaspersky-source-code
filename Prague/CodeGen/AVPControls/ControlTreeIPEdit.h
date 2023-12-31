#ifndef _IPADDR_H							// Only include this file once
#define	_IPADDR_H

//#pragma title("IP Address Custom Control Definitions")

// Created by Joseph A. Dziedzic, September 1997
// Revised April 1998
// Thanks to Dan Anderson, Kenny Goers, Kevin Lussier, and Doug Miller for their suggestions
// and code enhancements.
// Mail comments to dziedzic@ma.ultranet.com


// The structure we use to pass addresses around
typedef struct tagIPA_ADDR {
	unsigned char	nAddr1;	// The four bytes of the IP address
	unsigned char	nAddr2;
	unsigned char	nAddr3;
	unsigned char	nAddr4;
	UINT	nInError;		// Address byte with erroroneous/missing data (1..4)
} IPA_ADDR;

// IP Address control style bits

#define	IPAS_NOVALIDATE	0x0001	// Don't validate fields as they are input

// Messages to/from the IP Address control
enum IPAM {
	IPAM_GETADDRESS = WM_USER,
	IPAM_SETADDRESS,
	IPAM_SETREADONLY
};

// Resource IDs for our edit controls
enum RID {
	IDC_ADDR1 = 1,
	IDC_ADDR2,
	IDC_ADDR3,
	IDC_ADDR4
};

class CControlTreeIPCtl;


/////////////////////////////////////////////////////////////////////////////
// CControlTreeIPEdit window

class CControlTreeIPEdit : public CEdit
{
// Construction
public:
	CControlTreeIPEdit();

// Attributes
public:
	friend class CControlTreeIPCtl;

	// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlTreeIPEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CControlTreeIPEdit();

	// Generated message map functions
protected:
	CControlTreeIPCtl* m_pParent;
	void SetParent(CControlTreeIPCtl* pParent);
	//{{AFX_MSG(CControlTreeIPEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus( CWnd* pNewWnd );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CControlTreeIPCtl window

class CControlTreeIPCtl : public CWnd {
	bool									 m_bESC;
	HTREEITEM							 m_hItem;
// Construction
public:
	static BOOL Register();

	CControlTreeIPCtl( HTREEITEM hItem, CWnd *pLocWnd );

// Attributes
public:
	friend class CControlTreeIPEdit;

	void GetEncloseRect( CRect &rcEncloseRect );
	void EndWorkingProcessing();

// Operations
public:
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, DWORD dwExStyle=0);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlTreeIPCtl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CControlTreeIPCtl();
	BOOL GetAddress(BOOL bPrintErrors, IPA_ADDR* lpIPAddr)
		{ return (BOOL) ::SendMessage(m_hWnd, IPAM_GETADDRESS, (WPARAM) bPrintErrors, (LPARAM) lpIPAddr); };
	BOOL SetAddress(IPA_ADDR* lpIPAddr)
		{ return (BOOL) ::SendMessage(m_hWnd, IPAM_SETADDRESS, 0, (LPARAM) lpIPAddr); };
	BOOL SetReadOnly(BOOL bReadOnly = TRUE)
		{ return (BOOL) ::SendMessage(m_hWnd, IPAM_SETREADONLY, (WPARAM) bReadOnly, 0); };
	CControlTreeIPEdit* GetEditControl(int nIndex);

	// Generated message map functions
protected:
	virtual void OnChildChar(UINT nChar, UINT nRepCnt, UINT nFlags, CControlTreeIPEdit& child);
	//{{AFX_MSG(CControlTreeIPCtl)
	afx_msg LRESULT OnEditKillFocus( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnGetEncloseRect( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnGetIPAddress( WPARAM wParam, LPARAM lParam );
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnPaint();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg LONG OnSetFont(UINT wParam, LONG lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LONG OnGetAddress(UINT wParam, LONG lParam);
	afx_msg LONG OnSetAddress(UINT wParam, LONG lParam);
	afx_msg LONG OnSetReadOnly(UINT wParam, LONG lParam);
	afx_msg LONG OnChildInvalid(UINT wParam, LONG lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	CControlTreeIPEdit m_Addr[4];
	CRect							 m_rcAddr[4];
	CRect							 m_rcDot[3];
	CWnd              *m_pLocWnd;

	BOOL ParseAddressPart(CEdit& edit, int& n);

	BOOL m_bEnabled;
	BOOL m_bReadOnly;
	BOOL m_bNoValidate;
};

/////////////////////////////////////////////////////////////////////////////

#endif	// _IPADDR_H
