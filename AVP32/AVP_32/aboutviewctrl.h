#if !defined(AFX_ABOUTVIEWCTRL_H__106D4842_1145_11D4_A4CF_0000E8E1E96D__INCLUDED_)
#define AFX_ABOUTVIEWCTRL_H__106D4842_1145_11D4_A4CF_0000E8E1E96D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CAboutViewCtrl wrapper class

class CAboutViewCtrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CAboutViewCtrl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x8c397fa8, 0x6ce7, 0x11d3, { 0x96, 0xb0, 0x0, 0x10, 0x4b, 0x5b, 0x66, 0xaa } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	short GetAppearance();
	void SetAppearance(short);
	short GetBorderStyle();
	void SetBorderStyle(short);
	BOOL GetFullRowSelect();
	void SetFullRowSelect(BOOL);
	BOOL GetShowGridLines();
	void SetShowGridLines(BOOL);

// Operations
public:
	SCODE SetApplicationID(long nApplicationID);
	SCODE SetKeyFilesFolder(LPCTSTR pFolderName);
	SCODE SetApplicationName(LPCTSTR pApplicationName);
	SCODE SetApplicationVersion(LPCTSTR pApplicationVersion);
	SCODE SetRegisteredName(LPCTSTR pName);
	SCODE SetRegisteredOrganization(LPCTSTR pOrganization);
	SCODE SetLastUpdate(LPCTSTR pLastUpdate);
	SCODE SetCopyRight1(LPCTSTR pCopyRight);
	SCODE SetCopyRight2(LPCTSTR pCopyRight);
	SCODE ClearKeyList();
	SCODE GetMinSize(long* pnMinXSize, long* pnMinYSize);
	SCODE ChangeLocalization();
	SCODE SetInformationDataH(long hInfoData);
	SCODE SetInformationDataS(short* pDataBuffer, long dwDataBufferSize);
	SCODE SetNumberOfViruses(long dwVirNumber);
	SCODE SetApplicationVersionEx(LPCTSTR pApplicationVersion);
	SCODE SetLastUpdateEx(long* pLastUpdateDate);
	SCODE SetAVPBitmap(long hBitmap);
	SCODE SetAVPHyperLink(LPCTSTR pHyperLink);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTVIEWCTRL_H__106D4842_1145_11D4_A4CF_0000E8E1E96D__INCLUDED_)
