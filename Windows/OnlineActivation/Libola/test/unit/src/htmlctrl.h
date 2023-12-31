#ifndef _AG_HTMLCTRL_H_
#define _AG_HTMLCTRL_H_

// Microsoft Systems Journal -- January 2000
 // If this code works, it was written by Paul DiLascia.
 // If not, I don't know who wrote it.
 // Compiles with Visual C++ 6.0, runs on Windows 98 and probably Windows NT too.
 //

class COlaTestDlg;

class CHtmlCtrl : public CHtmlView 
{
public:
	CHtmlCtrl(COlaTestDlg* pDialog);
	~CHtmlCtrl() { }

	BOOL CreateFromStatic(UINT nID, CWnd* pParent);

	// Normally, CHtmlView destroys itself in PostNcDestroy,
	// but we don't want to do that for a control since a control
	// is usually implemented as a stack object in a dialog.
	//
	virtual void PostNcDestroy() {  }

	// overrides to bypass MFC doc/view frame dependencies
	afx_msg void OnDestroy();
	afx_msg int  OnMouseActivate(CWnd* pDesktopWnd,UINT nHitTest,UINT message);

	virtual void OnBeforeNavigate2
	(
		LPCTSTR lpszURL,
		DWORD nFlags,
		LPCTSTR lpszTargetFrameName,
		CByteArray& baPostedData,
		LPCTSTR lpszHeaders,
		BOOL* pbCancel
	);

	void LoadFromBuffer(const char* szData, size_t nSize);

	bool Submit();

	DECLARE_MESSAGE_MAP();
	DECLARE_DYNAMIC(CHtmlCtrl)
		
private:
	COlaTestDlg* m_pDialog;

};

#endif //_AG_HTMLCTRL_H_
