#include <windows.h>
#include "common\custview.h"


static const tName WindowsMessages[] = {
	{ 0x0, "WM_NULL" },
	{ 0x1, "WM_CREATE" },
	{ 0x2, "WM_DESTROY" },
	{ 0x3, "WM_MOVE" },
	{ 0x5, "WM_SIZE" },
	{ 0x6, "WM_ACTIVATE" },
	{ 0x7, "WM_SETFOCUS" },
	{ 0x8, "WM_KILLFOCUS" },
	{ 0x0A, "WM_ENABLE" },
	{ 0x0B, "WM_SETREDRAW" },
	{ 0x0C, "WM_SETTEXT" },
	{ 0x0D, "WM_GETTEXT" },
	{ 0x0E, "WM_GETTEXTLENGTH" },
	{ 0x0F, "WM_PAINT" },
	{ 0x10, "WM_CLOSE" },
	{ 0x11, "WM_QUERYENDSESSION" },
	{ 0x12, "WM_QUIT" },
	{ 0x13, "WM_QUERYOPEN" },
	{ 0x14, "WM_ERASEBKGND" },
	{ 0x15, "WM_SYSCOLORCHANGE" },
	{ 0x16, "WM_ENDSESSION" },
	{ 0x18, "WM_SHOWWINDOW" },
	{ 0x1A, "WM_SETTINGCHANGE" },
	{ 0x1B, "WM_DEVMODECHANGE" },
	{ 0x1C, "WM_ACTIVATEAPP" },
	{ 0x1D, "WM_FONTCHANGE" },
	{ 0x1E, "WM_TIMECHANGE" },
	{ 0x1F, "WM_CANCELMODE" },
	{ 0x20, "WM_SETCURSOR" },
	{ 0x21, "WM_MOUSEACTIVATE" },
	{ 0x22, "WM_CHILDACTIVATE" },
	{ 0x23, "WM_QUEUESYNC" },
	{ 0x24, "WM_GETMINMAXINFO" },
	{ 0x26, "WM_PAINTICON" },
	{ 0x27, "WM_ICONERASEBKGND" },
	{ 0x28, "WM_NEXTDLGCTL" },
	{ 0x2A, "WM_SPOOLERSTATUS" },
	{ 0x2B, "WM_DRAWITEM" },
	{ 0x2C, "WM_MEASUREITEM" },
	{ 0x2D, "WM_DELETEITEM" },
	{ 0x2E, "WM_VKEYTOITEM" },
	{ 0x2F, "WM_CHARTOITEM" },
	{ 0x30, "WM_SETFONT" },
	{ 0x31, "WM_GETFONT" },
	{ 0x32, "WM_SETHOTKEY" },
	{ 0x33, "WM_GETHOTKEY" },
	{ 0x37, "WM_QUERYDRAGICON" },
	{ 0x39, "WM_COMPAREITEM" },
	{ 0x41, "WM_COMPACTING" },
	{ 0x46, "WM_WINDOWPOSCHANGING" },
	{ 0x47, "WM_WINDOWPOSCHANGED" },
	{ 0x48, "WM_POWER" },
	{ 0x4A, "WM_COPYDATA" },
	{ 0x4B, "WM_CANCELJOURNAL" },
	{ 0x4E, "WM_NOTIFY" },
	{ 0x50, "WM_INPUTLANGCHANGEREQUEST" },
	{ 0x51, "WM_INPUTLANGCHANGE" },
	{ 0x52, "WM_TCARD" },
	{ 0x53, "WM_HELP" },
	{ 0x54, "WM_USERCHANGED" },
	{ 0x55, "WM_NOTIFYFORMAT" },
	{ 0x7B, "WM_CONTEXTMENU" },
	{ 0x7C, "WM_STYLECHANGING" },
	{ 0x7D, "WM_STYLECHANGED" },
	{ 0x7E, "WM_DISPLAYCHANGE" },
	{ 0x7F, "WM_GETICON" },
	{ 0x80, "WM_SETICON" },
	{ 0x81, "WM_NCCREATE" },
	{ 0x82, "WM_NCDESTROY" },
	{ 0x83, "WM_NCCALCSIZE" },
	{ 0x84, "WM_NCHITTEST" },
	{ 0x85, "WM_NCPAINT" },
	{ 0x86, "WM_NCACTIVATE" },
	{ 0x87, "WM_GETDLGCODE" },
	{ 0x0A0, "WM_NCMOUSEMOVE" },
	{ 0x0A1, "WM_NCLBUTTONDOWN" },
	{ 0x0A2, "WM_NCLBUTTONUP" },
	{ 0x0A3, "WM_NCLBUTTONDBLCLK" },
	{ 0x0A4, "WM_NCRBUTTONDOWN" },
	{ 0x0A5, "WM_NCRBUTTONUP" },
	{ 0x0A6, "WM_NCRBUTTONDBLCLK" },
	{ 0x0A7, "WM_NCMBUTTONDOWN" },
	{ 0x0A8, "WM_NCMBUTTONUP" },
	{ 0x0A9, "WM_NCMBUTTONDBLCLK" },
	{ 0x100, "WM_KEYFIRST" },
	{ 0x100, "WM_KEYDOWN" },
	{ 0x101, "WM_KEYUP" },
	{ 0x102, "WM_CHAR" },
	{ 0x103, "WM_DEADCHAR" },
	{ 0x104, "WM_SYSKEYDOWN" },
	{ 0x105, "WM_SYSKEYUP" },
	{ 0x106, "WM_SYSCHAR" },
	{ 0x107, "WM_SYSDEADCHAR" },
	{ 0x108, "WM_KEYLAST" },
	{ 0x10D, "WM_IME_STARTCOMPOSITION" },
	{ 0x10E, "WM_IME_ENDCOMPOSITION" },
	{ 0x10F, "WM_IME_COMPOSITION" },
	{ 0x10F, "WM_IME_KEYLAST" },
	{ 0x110, "WM_INITDIALOG" },
	{ 0x111, "WM_COMMAND" },
	{ 0x112, "WM_SYSCOMMAND" },
	{ 0x113, "WM_TIMER" },
	{ 0x114, "WM_HSCROLL" },
	{ 0x115, "WM_VSCROLL" },
	{ 0x116, "WM_INITMENU" },
	{ 0x117, "WM_INITMENUPOPUP" },
	{ 0x11F, "WM_MENUSELECT" },
	{ 0x120, "WM_MENUCHAR" },
	{ 0x121, "WM_ENTERIDLE" },
	{ 0x132, "WM_CTLCOLORMSGBOX" },
	{ 0x133, "WM_CTLCOLOREDIT" },
	{ 0x134, "WM_CTLCOLORLISTBOX" },
	{ 0x135, "WM_CTLCOLORBTN" },
	{ 0x136, "WM_CTLCOLORDLG" },
	{ 0x137, "WM_CTLCOLORSCROLLBAR" },
	{ 0x138, "WM_CTLCOLORSTATIC" },
	{ 0x200, "WM_MOUSEFIRST" },
	{ 0x200, "WM_MOUSEMOVE" },
	{ 0x201, "WM_LBUTTONDOWN" },
	{ 0x202, "WM_LBUTTONUP" },
	{ 0x203, "WM_LBUTTONDBLCLK" },
	{ 0x204, "WM_RBUTTONDOWN" },
	{ 0x205, "WM_RBUTTONUP" },
	{ 0x206, "WM_RBUTTONDBLCLK" },
	{ 0x207, "WM_MBUTTONDOWN" },
	{ 0x208, "WM_MBUTTONUP" },
	{ 0x209, "WM_MBUTTONDBLCLK" },
	{ 0x20A, "WM_MOUSEWHEEL" },
	{ 0x20A, "WM_MOUSELAST" },
	{ 0x20A, "WM_MOUSELAST" },
	{ 0x210, "WM_PARENTNOTIFY" },
	{ 0x211, "WM_ENTERMENULOOP" },
	{ 0x212, "WM_EXITMENULOOP" },
	{ 0x213, "WM_NEXTMENU" },
	{ 0x214, "WM_SIZING" },
	{ 0x215, "WM_CAPTURECHANGED" },
	{ 0x216, "WM_MOVING" },
	{ 0x218, "WM_POWERBROADCAST" },
	{ 0x219, "WM_DEVICECHANGE" },
	{ 0x281, "WM_IME_SETCONTEXT" },
	{ 0x282, "WM_IME_NOTIFY" },
	{ 0x283, "WM_IME_CONTROL" },
	{ 0x284, "WM_IME_COMPOSITIONFULL" },
	{ 0x285, "WM_IME_SELECT" },
	{ 0x286, "WM_IME_CHAR" },
	{ 0x290, "WM_IME_KEYDOWN" },
	{ 0x291, "WM_IME_KEYUP" },
	{ 0x220, "WM_MDICREATE" },
	{ 0x221, "WM_MDIDESTROY" },
	{ 0x222, "WM_MDIACTIVATE" },
	{ 0x223, "WM_MDIRESTORE" },
	{ 0x224, "WM_MDINEXT" },
	{ 0x225, "WM_MDIMAXIMIZE" },
	{ 0x226, "WM_MDITILE" },
	{ 0x227, "WM_MDICASCADE" },
	{ 0x228, "WM_MDIICONARRANGE" },
	{ 0x229, "WM_MDIGETACTIVE" },
	{ 0x230, "WM_MDISETMENU" },
	{ 0x231, "WM_ENTERSIZEMOVE" },
	{ 0x232, "WM_EXITSIZEMOVE" },
	{ 0x233, "WM_DROPFILES" },
	{ 0x234, "WM_MDIREFRESHMENU" },
	{ 0x2A1, "WM_MOUSEHOVER" },
	{ 0x2A3, "WM_MOUSELEAVE" },
	{ 0x300, "WM_CUT" },
	{ 0x301, "WM_COPY" },
	{ 0x302, "WM_PASTE" },
	{ 0x303, "WM_CLEAR" },
	{ 0x304, "WM_UNDO" },
	{ 0x305, "WM_RENDERFORMAT" },
	{ 0x306, "WM_RENDERALLFORMATS" },
	{ 0x307, "WM_DESTROYCLIPBOARD" },
	{ 0x308, "WM_DRAWCLIPBOARD" },
	{ 0x309, "WM_PAINTCLIPBOARD" },
	{ 0x30A, "WM_VSCROLLCLIPBOARD" },
	{ 0x30B, "WM_SIZECLIPBOARD" },
	{ 0x30C, "WM_ASKCBFORMATNAME" },
	{ 0x30D, "WM_CHANGECBCHAIN" },
	{ 0x30E, "WM_HSCROLLCLIPBOARD" },
	{ 0x30F, "WM_QUERYNEWPALETTE" },
	{ 0x310, "WM_PALETTEISCHANGING" },
	{ 0x311, "WM_PALETTECHANGED" },
	{ 0x312, "WM_HOTKEY" },
	{ 0x317, "WM_PRINT" },
	{ 0x318, "WM_PRINTCLIENT" },
	{ 0x358, "WM_HANDHELDFIRST" },
	{ 0x35F, "WM_HANDHELDLAST" },
	{ 0x360, "WM_AFXFIRST" },
	{ 0x37F, "WM_AFXLAST" },
	{ 0x380, "WM_PENWINFIRST" },
	{ 0x38F, "WM_PENWINLAST" },
	{ 0x8000, "WM_APP" },
	{ 0x400, "WM_USER" },
};

// this function formats value (passed in dwValue and pEvalInfo parameters) into readable string
HRESULT WINAPI format_value( 
							DWORD dwValue,        // low 32-bits of address or value
							DEBUGHELPER *pHelper, // callback pointer to access helper functions
							int nBase,            // decimal or hex
							BOOL bIgnore,         // not used
							char *pResult,        // where the result needs to go
							size_t max,           // how large the above buffer is
							EVAL_INFO* pEvalInfo  // internal debugger data
							) 
{
	// todo: write yor formatting code here
	DWORD i;
	CHAR  str[0x100];
		
	if (dwValue >= WM_APP)
	{
		wsprintf(str, "WM_APP+%d", dwValue-WM_APP);
		lstrcpyn(pResult, str, max);
		return S_OK;
	}

	if (dwValue >= WM_USER)
	{
		wsprintf(str, "WM_USER+%d", dwValue-WM_USER);
		lstrcpyn(pResult, str, max);
		return S_OK;
	}

		
	for (i=0; i<sizeof(WindowsMessages)/sizeof(WindowsMessages[0]);i++)
	{
		if (dwValue == WindowsMessages[i].id)
		{
			lstrcpyn(pResult, WindowsMessages[i].name, max);
			return S_OK;
		}
	}

	lstrcpyn(pResult, "<unknown>", max);	
	return S_OK;
}

