// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "reportviewctrl.h"

/////////////////////////////////////////////////////////////////////////////
// CReportViewCtrl

IMPLEMENT_DYNCREATE(CReportViewCtrl, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CReportViewCtrl properties

short CReportViewCtrl::GetAppearance()
{
	short result;
	GetProperty(DISPID_APPEARANCE, VT_I2, (void*)&result);
	return result;
}

void CReportViewCtrl::SetAppearance(short propVal)
{
	SetProperty(DISPID_APPEARANCE, VT_I2, propVal);
}

short CReportViewCtrl::GetBorderStyle()
{
	short result;
	GetProperty(DISPID_BORDERSTYLE, VT_I2, (void*)&result);
	return result;
}

void CReportViewCtrl::SetBorderStyle(short propVal)
{
	SetProperty(DISPID_BORDERSTYLE, VT_I2, propVal);
}

BOOL CReportViewCtrl::GetAutoTracking()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetAutoTracking(BOOL propVal)
{
	SetProperty(0x1, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetUseCheckSemantic()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetUseCheckSemantic(BOOL propVal)
{
	SetProperty(0x2, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetUseCortegeImages()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetUseCortegeImages(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetLargeDataProcessing()
{
	BOOL result;
	GetProperty(0x4, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetLargeDataProcessing(BOOL propVal)
{
	SetProperty(0x4, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetSortByColumns()
{
	BOOL result;
	GetProperty(0x5, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetSortByColumns(BOOL propVal)
{
	SetProperty(0x5, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetExternalParseCortege()
{
	BOOL result;
	GetProperty(0x6, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetExternalParseCortege(BOOL propVal)
{
	SetProperty(0x6, VT_BOOL, propVal);
}

long CReportViewCtrl::GetItemsViewLimit()
{
	long result;
	GetProperty(0x7, VT_I4, (void*)&result);
	return result;
}

void CReportViewCtrl::SetItemsViewLimit(long propVal)
{
	SetProperty(0x7, VT_I4, propVal);
}

BOOL CReportViewCtrl::GetFullRowSelect()
{
	BOOL result;
	GetProperty(0x8, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetFullRowSelect(BOOL propVal)
{
	SetProperty(0x8, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetEnableChangeItemsState()
{
	BOOL result;
	GetProperty(0x9, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetEnableChangeItemsState(BOOL propVal)
{
	SetProperty(0x9, VT_BOOL, propVal);
}

long CReportViewCtrl::GetRefreshingTimeout()
{
	long result;
	GetProperty(0xa, VT_I4, (void*)&result);
	return result;
}

void CReportViewCtrl::SetRefreshingTimeout(long propVal)
{
	SetProperty(0xa, VT_I4, propVal);
}

BOOL CReportViewCtrl::GetViewLastSession()
{
	BOOL result;
	GetProperty(0xb, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetViewLastSession(BOOL propVal)
{
	SetProperty(0xb, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetShowGridLines()
{
	BOOL result;
	GetProperty(0xc, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetShowGridLines(BOOL propVal)
{
	SetProperty(0xc, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetShowSelectionAlways()
{
	BOOL result;
	GetProperty(0xd, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetShowSelectionAlways(BOOL propVal)
{
	SetProperty(0xd, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetProportionalHeaderResize()
{
	BOOL result;
	GetProperty(0xe, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetProportionalHeaderResize(BOOL propVal)
{
	SetProperty(0xe, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetShowHeaderOnEmptyList()
{
	BOOL result;
	GetProperty(0xf, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetShowHeaderOnEmptyList(BOOL propVal)
{
	SetProperty(0xf, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetExternalReadingReport()
{
	BOOL result;
	GetProperty(0x1d, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetExternalReadingReport(BOOL propVal)
{
	SetProperty(0x1d, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetSmartRefreshingTimeout()
{
	BOOL result;
	GetProperty(0x1e, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetSmartRefreshingTimeout(BOOL propVal)
{
	SetProperty(0x1e, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetProgressNotify()
{
	BOOL result;
	GetProperty(0x1f, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetProgressNotify(BOOL propVal)
{
	SetProperty(0x1f, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetAddToListImmediatelly()
{
	BOOL result;
	GetProperty(0x20, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetAddToListImmediatelly(BOOL propVal)
{
	SetProperty(0x20, VT_BOOL, propVal);
}

BOOL CReportViewCtrl::GetExternalSortingComparison()
{
	BOOL result;
	GetProperty(0x21, VT_BOOL, (void*)&result);
	return result;
}

void CReportViewCtrl::SetExternalSortingComparison(BOOL propVal)
{
	SetProperty(0x21, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CReportViewCtrl operations

SCODE CReportViewCtrl::ClearReportView()
{
	SCODE result;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_ERROR, (void*)&result, NULL);
	return result;
}

SCODE CReportViewCtrl::SetReportCortege(LPCTSTR pCortegeStr)
{
	SCODE result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_ERROR, (void*)&result, parms,
		pCortegeStr);
	return result;
}

SCODE CReportViewCtrl::AcceptReportFile(LPCTSTR pFileName)
{
	SCODE result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_ERROR, (void*)&result, parms,
		pFileName);
	return result;
}

SCODE CReportViewCtrl::SetReportItem(long hItemData)
{
	SCODE result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_ERROR, (void*)&result, parms,
		hItemData);
	return result;
}

SCODE CReportViewCtrl::GetSelectedIndex(long* pnSelectedInd)
{
	SCODE result;
	static BYTE parms[] =
		VTS_PI4;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_ERROR, (void*)&result, parms,
		pnSelectedInd);
	return result;
}

SCODE CReportViewCtrl::UpdateHeaderText()
{
	SCODE result;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_ERROR, (void*)&result, NULL);
	return result;
}

SCODE CReportViewCtrl::GetSessionHeadlines(long* phHeadlinesData, LPCTSTR pFileName)
{
	SCODE result;
	static BYTE parms[] =
		VTS_PI4 VTS_BSTR;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_ERROR, (void*)&result, parms,
		phHeadlinesData, pFileName);
	return result;
}

SCODE CReportViewCtrl::SetViewedSessionNumber(long dwNumber)
{
	SCODE result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_ERROR, (void*)&result, parms,
		dwNumber);
	return result;
}

SCODE CReportViewCtrl::FindFirstItem(LPCTSTR pszFindContext, long dwFlags)
{
	SCODE result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_ERROR, (void*)&result, parms,
		pszFindContext, dwFlags);
	return result;
}

SCODE CReportViewCtrl::FindNextItem()
{
	SCODE result;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_ERROR, (void*)&result, NULL);
	return result;
}

SCODE CReportViewCtrl::GetHeaderColumnWidths(long* phWidthsData)
{
	SCODE result;
	static BYTE parms[] =
		VTS_PI4;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_ERROR, (void*)&result, parms,
		phWidthsData);
	return result;
}

SCODE CReportViewCtrl::Activate()
{
	SCODE result;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_ERROR, (void*)&result, NULL);
	return result;
}

SCODE CReportViewCtrl::GetLastFindResult(BOOL* pbResult)
{
	SCODE result;
	static BYTE parms[] =
		VTS_PBOOL;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_ERROR, (void*)&result, parms,
		pbResult);
	return result;
}

SCODE CReportViewCtrl::GetCortege(long nCortegeIndex, long* phCortegeData)
{
	SCODE result;
	static BYTE parms[] =
		VTS_I4 VTS_PI4;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_ERROR, (void*)&result, parms,
		nCortegeIndex, phCortegeData);
	return result;
}

SCODE CReportViewCtrl::GetHeaderCortege(long* phCortegeData)
{
	SCODE result;
	static BYTE parms[] =
		VTS_PI4;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_ERROR, (void*)&result, parms,
		phCortegeData);
	return result;
}
