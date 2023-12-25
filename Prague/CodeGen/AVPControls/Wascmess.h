#ifndef __WASCMESS_H
#define __WASCMESS_H

#include <windows.h>


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
struct CTTMessageInfo {
	UINT   m_nWindowID;					// ������������� ����
	int		 m_nItemIndex;				// ������ ����
	BOOL   m_bRepeate;				  // ��������� �������
	union {
		TCHAR  *m_pItemText;			// ����� ����� ��������������
	  VOID   *m_pStringList;		// ��������� �� ��������� CStringList, ���������� ����������
		UINT    m_nScrollGroup;		// ������� � ������ �������������� 
															// LOWORD - ��������� ������ � ������, HIWORD - �������� ������ � ������     
		HMENU   m_hMenu;					// Handle Context-����
		DWORD   m_ToolBarStuff[2];// Context-���� toolbar ID[0]/Handle[1]
		DWORD   m_iCommandId;			// ������������� ������� Context-����
		BOOL    m_bSetRemove;			// ���� - "����������/�����"
		DWORD   m_aUpDownStuff[3];// ��������� UpDown [0]-MinValue; [1]-MaxValue; [2]-Step
		TCHAR  *m_pDateFormat;		// ������ ������ ����
		TCHAR  *m_pTimeFormat;		// ������ ������ �������
		TCHAR  *m_pDateTimeFormat;// ������ ������ ����-�������
		WORD    m_aDateValue[4];	// �������� ���� - ������ 4 ����� SYSTEMTIME
		WORD    m_aTimeValue[4];	// �������� ������� - ������ 4 ����� SYSTEMTIME
		WORD    m_aDateTimeValue[8];	// �������� ����-������� - SYSTEMTIME
		BYTE    m_aIPValue[4];	  // �������� IP ������
		WORD    m_aPIDValue[4];	  // �������� PID
	} m_Value;
};

// ��������� �� ��������� ���������� Checked
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������ Checked ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� CTTMessageInfo
//						m_Value.m_bSetRemove - TRUE - ����������, FALSE - �����
// LRESULT	- �� ������������
UINT const CTTM_CHECKEDCHANGING     = (0xC000 - 1);

// ��������� �� ��������� ���������
// WPARAM		- LPBOOL - ��������� �� ��������� - �� ������������
// LPARAM		- ��������� �� ��������� ��������� CTTMessageInfo
// LRESULT	- �� ������������
UINT const CTTM_STATECHANGED        = (0xC000 - 2);

// ������ � Parent �� ���������� �������� �������������� ������ ��������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� �������������� ���������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//            m_Value.m_pItemText - ����� ������ ����
//						m_bRepeate					- ���� ���������� �������, ��-���������	= FALSE;
// LRESULT	- �� ������������
UINT const CTTM_DOEXTERNALEDITING   = (0xC000 - 3);

// ������ �� ���������������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� "��������������" ���������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//            m_Value.m_ScrollGroup - ������ ��������������
// LRESULT	- �� ������������
UINT const CTTM_VSCROLLUP			  	  = (0xC000 - 4);
UINT const CTTM_VSCROLLDOWN			    = (0xC000 - 5);

// ��������� � ������ �������������� ������ ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� �������������� ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//            m_Value.m_pItemText - ����� ������ ����
// LRESULT	- �� ������������
UINT const CTTM_BEGINLABELEDIT			= (0xC000 - 6);

// ��������� � ���������� �������������� ������ ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������ ������ ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//            m_Value.m_pItemText - ����� ������������������ ������
// LRESULT	- �� ������������
UINT const CTTM_ENDLABELEDIT			  = (0xC000 - 7);

// ��������� �� ������ �� �������������� ������ ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������ ������ ���������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//            m_Value.m_pItemText - NULL
// LRESULT	- �� ������������
UINT const CTTM_CANCELLABELEDIT			= (0xC000 - 8);

// ��������� � ����������� ���������� PostEdit ��������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ��������� ���������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//            m_Value.m_pItemText - ����� ������ ����
// LRESULT	- �� ������������
UINT const CTTM_POSTLABELEDIT				= (0xC000 - 9);

// ������ �� ���������� ������� ComboBox 
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� �������� ���������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� CTTMessageInfo
//            m_Value.m_StringList - ��������� �� ��������� CStringList, ���������� ����������
// LRESULT	- �� ������������
UINT const CTTM_LOADCOMBOCONTENTS		= (0xC000 - 10);

// ������ �� ��������� ���������� UpDown Edit 
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ��������� ���������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� CTTMessageInfo
// 		        m_Value.m_UpDownStuff - ��������� UpDown [0]-MinValue; [1]-MaxValue; [2]-Step
// LRESULT	- �� ������������
UINT const CTTM_LOADUPDOWNCONTEXT		= (0xC000 - 11);

// ������ �� �������� �������� 
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� �������� ���������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//            m_Value.m_pItemText - ����� ������ ����
// LRESULT	- �� ������������
UINT const CTTM_REMOVEITEM          = (0xC000 - 12);

// ������ �� ��������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ��������� ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//            m_Value.m_hMenu - Handle Context-����
// LRESULT	- �� ������������
UINT const CTTM_PREPROCESSCONTEXTMENU = (0xC000 - 13);

// ������ �� ���������� ������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������� ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//            m_Value.m_Command - ������������� ������� ����
// LRESULT	- �� ������������
UINT const CTTM_DOCONTEXTMENUCOMMAND = (0xC000 - 14);

// ��������� � ����� �������������� �������
// WPARAM		- �� ������������ ( =0 )
// LPARAM		- ��������� �� ��������� ��������� CTTMessageInfo
//						m_Value.m_bSetRemove - TRUE - ���������, FALSE - ������
// LRESULT	- �� ������������
UINT const CTTM_ITEMSELCHANGING      = (0xC000 - 15);

// ��������� �� ����������� ����
// WPARAM		- 0
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
// LRESULT	- �� ������������
UINT const CTTM_WINDOWSHUTDOWN       = (0xC000 - 16);

// ��������� � ������� ������� ������ ���� ��� ��������������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ����� ���
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� CTTMessageInfo
//						m_Value.m_pDateFormat - ������ ������ ����
UINT const CTTM_QUERYDATEFORMAT      = (0xC000 - 17);

// ��������� � ������� ��������� ������������� ���� ��� ��������������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ���� ����
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� CTTMessageInfo
//						m_Value.m_aDateValue[4] - �������� ���� - ������ 4 ����� SYSTEMTIME
UINT const CTTM_QUERYDATE						 = (0xC000 - 18);

// ��������� � ���������� �������������� ������ ���� ���� "Date"
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������ ������ ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//						m_Value.m_aDateValue[4] - �������� ���� - ������ 4 ����� SYSTEMTIME
// LRESULT	- �� ������������
UINT const CTTM_ENDDATELABELEDIT		 = (0xC000 - 19);

// ��������� � ��������� ����
// WPARAM		- �� ������������ ( =0 )
// LPARAM		- ��������� �� ��������� ��������� CTTMessageInfo
//						m_Value.m_bSetRemove - TRUE - ��������, FALSE - ��������
// LRESULT	- �� ������������
UINT const CTTM_ITEMEXPANDING        = (0xC000 - 20);

// ��������� � ����� ������� �������� ��������
// WPARAM		- �� ������������ ( =0 )
// LPARAM		- ��������� �� ��������� ��������� CTTMessageInfo
//						m_Value.m_bSetRemove - TRUE - ���������, FALSE - ������
// LRESULT	- �� ������������
UINT const CTTM_FIRSTVISIBLECHANGING  = (0xC000 - 21);

// ������ �� �������� IP ������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� �������� ���������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� CTTMessageInfo
// 		        m_Value.m_aIPValue[4] - �������� ����� IP ������
// LRESULT	- �� ������������
UINT const CTTM_LOADIPADDRESS					= (0xC000 - 22);

// ��������� � ���������� �������������� ������ ���� ���� "IP Address"
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������ ������ ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//						m_Value.m_aIPValue[4] - �������� ����� IP ������
// LRESULT	- �� ������������
UINT const CTTM_ENDADDRESSLABELEDIT		= (0xC000 - 23);

// ��������� � ������� ������� ������ ������� ��� ��������������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ����� ���
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� CTTMessageInfo
//						m_Value.m_pTimeFormat - ������ ������ ����
UINT const CTTM_QUERYTIMEFORMAT      = (0xC000 - 24);

// ��������� � ������� ��������� ������������� ������� ��� ��������������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ���� ����
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� CTTMessageInfo
//						m_Value.m_aTimeValue[4] - �������� ���� - ������ 4 ����� SYSTEMTIME
UINT const CTTM_QUERYTIME						 = (0xC000 - 25);

// ��������� � ���������� �������������� ������ ���� ���� "Time"
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������ ������ ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//						m_Value.m_aTimeValue[4] - �������� ���� - ������ 4 ����� SYSTEMTIME
// LRESULT	- �� ������������
UINT const CTTM_ENDTIMELABELEDIT		 = (0xC000 - 26);

// ��������� � ������� toolbar ID ��� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ID �����
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//            m_Value.m_ToolBarStuff	- �������� toolbar ID[0] and Handle[1]
// LRESULT	- �� ������������
UINT const CTTM_GETMENUTOOLBAR		   = (0xC000 - 27);

// ��������� � ���������/������ ������ �����
// WPARAM		- HWND ���������/�������� ������
// LPARAM		- ��������� �� ��������� ��������� CTTMessageInfo
//						m_Value.m_bSetRemove - TRUE - ���������, FALSE - ������
// LRESULT	- �� ������������
UINT const CTTM_FOCUSCHANGING        = (0xC000 - 28);

// ��������� � ������� ������� ������ ����-������� ��� ��������������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ����� ���
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� CTTMessageInfo
//						m_Value.m_pDateTimeFormat - ������ ������ ����-�������
UINT const CTTM_QUERYDATETIMEFORMAT      = (0xC000 - 29);

// ��������� � ������� ��������� ������������� ����-������� ��� ��������������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ���� ����
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� CTTMessageInfo
//						m_Value.m_aDateTimeValue[8] - �������� ����-������� - SYSTEMTIME
UINT const CTTM_QUERYDATETIME						 = (0xC000 - 30);

// ��������� � ���������� �������������� ������ ���� ���� "DateTime"
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������ ������ ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//						m_Value.m_aDateTimeValue[4] - �������� ����-������� - SYSTEMTIME
// LRESULT	- �� ������������
UINT const CTTM_ENDDATETIMELABELEDIT		 = (0xC000 - 31);

// ������ �� �������� PID
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� �������� ���������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� CTTMessageInfo
// 		        m_Value.m_aPIDValue[4] - �������� ����� PID
// LRESULT	- �� ������������
UINT const CTTM_LOADPIDVALUE					= (0xC000 - 32);

// ��������� � ���������� �������������� ������ ���� ���� "PID Value"
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������ ������ ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� CTTMessageInfo 
//						m_Value.m_aPIDValue[4] - �������� ����� PID
// LRESULT	- �� ������������
UINT const CTTM_ENDPIDLABELEDIT		= (0xC000 - 33);

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
struct NSTMessageInfo {
	int	m_nItemIndex;				// ������ ����
	union {
		HMENU   m_hMenu;							// Handle ContextMenu
		DWORD   m_ToolBarStuff[2];	// Context-���� toolbar ID[0]/Handle[1]
		DWORD   m_iCommandId;				// ������������� ������� Context-����
		BOOL    m_bSetRemove;				// ���� - "����������/�����"
	} m_Value;
};

// ������ �� ���������� ��������� 
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ���������� ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� NSTMessageInfo
// LRESULT	- �� ������������
UINT const NSTM_LOADSUBTREE      		= (0xC000 - 40);

// ������ �� ��������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ����� ���� ��������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� NSTMessageInfo
//						m_Value.m_hMenu - Handle ���� (HMENU)
// LRESULT	- �� ������������
UINT const NSTM_PREPROCESSCONTEXTMENU = (0xC000 - 41);

// ������ �� ���������� ������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������� ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� NSTMessageInfo
//						m_Value.m_iCommandId - ������������� ������� ����
// LRESULT	- �� ������������
UINT const NSTM_DOCONTEXTMENUCOMMAND = (0xC000 - 42);

// ��������� � ������ ��������� Checked
// WPARAM		- LPBOOL - ��������� �� ��������� - FALSE - ��������� �������������� ����������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� NSTMessageInfo
//						m_Value.m_bSetRemove - TRUE - ����������, FALSE - �����
// LRESULT	- �� ������������
UINT const NSTM_MANUALLYSETREMOVECHECKED   = (0xC000 - 43);

// ��������� �� �������������� ��������� Checked
// WPARAM		- LPBOOL - ��������� �� ��������� - FALSE - ��������� �������������� ����������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� NSTMessageInfo
//						m_Value.m_bSetRemove - TRUE - ����������, FALSE - �����
// LRESULT	- �� ������������
UINT const NSTM_SETREMOVECHECKED		= (0xC000 - 44);

// ��������� � ������ ��������� Strict
// WPARAM		- LPBOOL - ��������� �� ��������� - FALSE - ��������� �������������� ����������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� NSTMessageInfo
//						m_Value.m_bSetRemove - TRUE - ����������, FALSE - �����
// LRESULT	- �� ������������
UINT const NSTM_MANUALLYSETREMOVESTRICT = (0xC000 - 45);

// ��������� � ����� �������������� �������
// WPARAM		- �� ������������ ( =0 )
// LPARAM		- ��������� �� ��������� ��������� NSTMessageInfo
//						m_Value.m_bSetRemove - TRUE - ���������, FALSE - ������
// LRESULT	- �� ������������
UINT const NSTM_ITEMSELCHANGING      = (0xC000 - 46);

// ��������� �� ����������� ����
// WPARAM		- 0
// LPARAM		- 0
// LRESULT	- �� ������������
UINT const NSTM_WINDOWSHUTDOWN       = (0xC000 - 47);

// ��������� � ���������/������ ������ �����
// WPARAM		- HWND ���������/�������� ������
// LPARAM		- ��������� �� ��������� ��������� NSTMessageInfo
//						m_Value.m_bSetRemove - TRUE - ���������, FALSE - ������
// LRESULT	- �� ������������
UINT const NSTM_FOCUSCHANGING        = (0xC000 - 48);

// ��������� �� ��������� ���������
// WPARAM		- �� ������������
// LPARAM		- ��������� �� ��������� ��������� NSTMessageInfo
// LRESULT	- �� ������������
UINT const NSTM_STATECHANGED					= (0xC000 - 49);

// ��������� � ������� toolbar ID ��� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ID �����
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� NSTMessageInfo 
//            m_Value.m_ToolBarStuff[2]	- �������� toolbar ID[0] and Handle[1]
// LRESULT	- �� ������������
UINT const NSTM_GETMENUTOOLBAR		   = (0xC000 - 50);

// ��������� � ��������� ����
// WPARAM		- �� ������������ ( =0 )
// LPARAM		- ��������� �� ��������� ��������� NSTMessageInfo
//						m_Value.m_bSetRemove - TRUE - ��������, FALSE - ��������
// LRESULT	- �� ������������
UINT const NSTM_ITEMEXPANDING        = (0xC000 - 51);

// ��������� � ������/��������� �������� ������� �������� ����
// WPARAM		- �� ������������ ( =0 )
// LPARAM		- ��������� �� ��������� ��������� NSTMessageInfo
//						m_Value.m_bSetRemove - TRUE - ������ ��������, FALSE - ��������� �������
// LRESULT	- �� ������������
UINT const NSTM_FULLEXPANDING       = (0xC000 - 52);

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
struct NSLMessageInfo {
	int	m_nItemIndex;				// ������ ����
	union {
		HMENU  m_hMenu;				    // Handle ContextMenu
		DWORD  m_ToolBarStuff[2];	// Context-���� toolbar ID[0]/Handle[1]
		DWORD  m_iCommandId;			// ������������� ������� Context-����
		BOOL   m_bSetRemove;      // ���� - "����������/�����"
	} m_Value;
};

// ������ �� ��������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ����� ���� ��������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� NSLMessageInfo
//						m_Value.m_nItemIndex	- ����� ���� -1, ���� ��� ���������������� ��������
//						m_Value.m_hMenu - Handle ���� (HMENU)
// LRESULT	- �� ������������
UINT const NSLM_PREPROCESSCONTEXTMENU = (0xC000 - 60);

// ������ �� ���������� ������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������� ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� NSLMessageInfo
//						m_Value.m_iCommandId - ������������� ������� ����
// LRESULT	- �� ������������
UINT const NSLM_DOCONTEXTMENUCOMMAND  = (0xC000 - 61);

// ������ �� ��������� Checked
// WPARAM		- LPBOOL - ��������� �� ��������� - FALSE - ��������� �������������� ����������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� NSLMessageInfo
//						m_Value.m_bSetRemove - TRUE - ����������, FALSE - �����
// LRESULT	- �� ������������
UINT const NSLM_MANUALLYSETREMOVECHECKED = (0xC000 - 62);

// ������ �� ��������� Strict
// WPARAM		- LPBOOL - ��������� �� ��������� - FALSE - ��������� �������������� ����������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� NSLMessageInfo
//						m_Value.m_bSetRemove - TRUE - ����������, FALSE - �����
// LRESULT	- �� ������������
UINT const NSLM_MANUALLYSETREMOVESTRICT  = (0xC000 - 63);

// ��������� � ����� �������������� �������
// WPARAM		- �� ������������ ( =0 )
// LPARAM		- ��������� �� ��������� ��������� NSLMessageInfo
//						m_Value.m_bSetRemove - TRUE - ���������, FALSE - ������
// LRESULT	- �� ������������
UINT const NSLM_ITEMSELCHANGING				= (0xC000 - 64);

// ��������� �� ����������� ����
// WPARAM		- 0
// LPARAM		- 0
// LRESULT	- �� ������������
UINT const NSLM_WINDOWSHUTDOWN				= (0xC000 - 65);

// ��������� � ���������/������ ������ �����
// WPARAM		- HWND ���������/�������� ������
// LPARAM		- ��������� �� ��������� ��������� NSLMessageInfo
//						m_Value.m_bSetRemove - TRUE - ���������, FALSE - ������
// LRESULT	- �� ������������
UINT const NSLM_FOCUSCHANGING         = (0xC000 - 66);

// ��������� �� ��������� ���������
// WPARAM		- �� ������������
// LPARAM		- ��������� �� ��������� ��������� NSLMessageInfo
// LRESULT	- �� ������������
UINT const NSLM_STATECHANGED					= (0xC000 - 67);

// ��������� � ������� toolbar ID ��� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ID �����
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� NSLMessageInfo 
//            m_Value.m_ToolBarStuff[2]	- �������� toolbar ID[0] and Handle[1]
// LRESULT	- �� ������������
UINT const NSLM_GETMENUTOOLBAR		   = (0xC000 - 68);
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
struct RPVMessageInfo {
	int	m_nItemIndex;				// ������ item'�
	int	m_nSubItemIndex;		// ������ subitem'�
	union {
		HMENU    m_hMenu;					 // Handle ContextMenu
		DWORD    m_ToolBarStuff[2];// Context-���� toolbar ID[0]/Handle[1]
		DWORD    m_iCommandId;		 // ������������� ������� Context-����
		BOOL     m_bSetRemove;     // ���� - "����������/�����"
		BOOL     m_bSortAscending; // ���� - "���������� �� �����������/��������"
		TCHAR   *m_pContext;			 // �������� ������
		DWORD    m_MenuItemStuff[2];// Context-���� item ID[0]/BitmapHandle[1]
	} m_Value;
};

// ������ �� ���������� ��������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������� ��������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� RPVMessageInfo
// LRESULT	- �� ������������
UINT const RPVM_DOFILLITEM						= (0xC000 - 70);

// ��������� �� ����������� ����
// WPARAM		- 0
// LPARAM		- 0
// LRESULT	- �� ������������
UINT const RPVM_WINDOWSHUTDOWN				= (0xC000 - 71);

// ������ �� ���������� �� ��������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ���������� ���������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� RPVMessageInfo
//            m_nItemIndex - ������ �������� ���������
// LRESULT	- �� ������������
UINT const RPVM_DOSORTITEMS					  = (0xC000 - 72);

// ������ �� ��������� Checked
// WPARAM		- LPBOOL - ��������� �� ��������� - FALSE - ��������� �������������� ����������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� RPVMessageInfo
//						m_Value.m_bSetRemove - TRUE - ����������, FALSE - �����
// LRESULT	- �� ������������
UINT const RPVM_MANUALLYSETREMOVECHECKED = (0xC000 - 73);

// ������ �� ��������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ����� ���� ��������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� RPVMessageInfo
//						m_Value.m_nItemIndex	- ����� ���� -1, ���� ��� ���������������� ��������
//						m_Value.m_hMenu - Handle ���� (HMENU)
// LRESULT	- �� ������������
UINT const RPVM_PREPROCESSCONTEXTMENU = (0xC000 - 74);

// ������ �� ���������� ������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������� ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� RPVMessageInfo
//						m_Value.m_iCommandId - ������������� ������� ����
// LRESULT	- �� ������������
UINT const RPVM_DOCONTEXTMENUCOMMAND  = (0xC000 - 75);

// ������ �� �������� ������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� �������� �����
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� RPVMessageInfo
//						m_Value.m_pContext - ��������� �� �������� ������
// LRESULT	- �� ������������
UINT const RPVM_GETFINDITEMCONTEXT    = (0xC000 - 76);

// ������ �� �������� �������� ��� ������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������� ������������� ������� ������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� RPVMessageInfo
//						m_Value.m_pContext - ��������� �� �������� ������
// LRESULT	- �� ������������
UINT const RPVM_CHECKITEMFORFIND      = (0xC000 - 77);

// ������ �� �������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ���� ���� �������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� RPVMessageInfo
//						m_Value.m_nItemIndex	- ����� ���� -1, ���� ��� ���������������� ��������
//						m_Value.m_hMenu - Handle ���� (HMENU)
// LRESULT	- �� ������������
UINT const RPVM_CREATECONTEXTMENU			= (0xC000 - 78);

// ��������� � ������� toolbar ID ��� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ID �����
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� RPVMessageInfo 
//            m_Value.m_ToolBarStuff[2]	- �������� toolbar ID[0] and Handle[1]
// LRESULT	- �� ������������
UINT const RPVM_GETMENUTOOLBAR		   = (0xC000 - 79);

// ��������� � ���������/������ ������ �����
// WPARAM		- HWND ���������/�������� ������
// LPARAM		- ��������� �� ��������� ��������� RPVMessageInfo
//						m_Value.m_bSetRemove - TRUE - ���������, FALSE - ������
// LRESULT	- �� ������������
UINT const RPVM_FOCUSCHANGING		   = (0xC000 - 80);

// ��������� � ������� BITMAP ��� �������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� BITMAP �����
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� RPVMessageInfo 
//            m_Value.m_hBitmap	- ��������� �� HBITMAP
// LRESULT	- �� ������������
UINT const RPVM_GETMENUITEMBITMAP   = (0xC000 - 81);

// ��������� � ����� �������������� �������
// WPARAM		- �� ������������ ( =0 )
// LPARAM		- ��������� �� ��������� ��������� RPVMessageInfo
//						m_Value.m_bSetRemove - TRUE - ���������, FALSE - ������
// LRESULT	- �� ������������
UINT const RPVM_ITEMSELCHANGING			= (0xC000 - 82);
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
struct STVMessageInfo {
	int	m_nItemIndex;				// ������ ����
	union {
		HMENU   m_hMenu;					// Handle ContextMenu
		DWORD   m_ToolBarStuff[2];// Context-���� toolbar ID[0]/Handle[1]
		DWORD   m_iCommandId;			// ������������� ������� Context-����
		TCHAR  *m_pContext;			  // �������� ������
		BOOL    m_bSetRemove;     // ���� - "����������/�����"
	} m_Value;
};

// ��������� �� ����������� ����
// WPARAM		- 0
// LPARAM		- 0
// LRESULT	- �� ������������
UINT const STVM_WINDOWSHUTDOWN				= (0xC000 - 90);

// ������ �� ��������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ����� ���� ��������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� STVMessageInfo
//						m_Value.m_nItemIndex	- ����� ���� -1, ���� ��� ���������������� ��������
//						m_Value.m_hMenu - Handle ���� (HMENU)
// LRESULT	- �� ������������
UINT const STVM_PREPROCESSCONTEXTMENU = (0xC000 - 91);

// ������ �� ���������� ������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������� ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� STVMessageInfo
//						m_Value.m_iCommandId - ������������� ������� ����
// LRESULT	- �� ������������
UINT const STVM_DOCONTEXTMENUCOMMAND  = (0xC000 - 92);

// ������ �� �������� ������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� �������� �����
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� STVMessageInfo
//						m_Value.m_pContext - ��������� �� �������� ������
// LRESULT	- �� ������������
UINT const STVM_GETFINDITEMCONTEXT    = (0xC000 - 93);

// ������ �� �������� �������� ��� ������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������� ������������� ������� ������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� STVMessageInfo
//						m_Value.m_pContext - ��������� �� �������� ������
// LRESULT	- �� ������������
UINT const STVM_CHECKITEMFORFIND      = (0xC000 - 94);

// ������ �� �������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ���� ���� �������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� STVMessageInfo
//						m_Value.m_nItemIndex	- ����� ���� -1, ���� ��� ���������������� ��������
//						m_Value.m_hMenu - Handle ���� (HMENU)
// LRESULT	- �� ������������
UINT const STVM_CREATECONTEXTMENU			= (0xC000 - 95);

// ��������� � ������� toolbar ID ��� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ID �����
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� STVMessageInfo 
//            m_Value.m_ToolBarStuff[2]	- �������� toolbar ID[0] and Handle[1]
// LRESULT	- �� ������������
UINT const STVM_GETMENUTOOLBAR		   = (0xC000 - 96);

// ��������� � ���������/������ ������ �����
// WPARAM		- HWND ���������/�������� ������
// LPARAM		- ��������� �� ��������� ��������� STVMessageInfo
//						m_Value.m_bSetRemove - TRUE - ���������, FALSE - ������
// LRESULT	- �� ������������
UINT const STVM_FOCUSCHANGING		   = (0xC000 - 97);

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
struct ABTMessageInfo {
	int	m_nItemIndex;				// ������ ����
	union {
		HMENU   m_hMenu;					// Handle ContextMenu
		DWORD   m_ToolBarStuff[2];// Context-���� toolbar ID[0]/Handle[1]
		DWORD   m_iCommandId;			// ������������� ������� Context-����
		TCHAR  *m_pContext;			  // �������� ������
		BOOL   m_bSetRemove;      // ���� - "����������/�����"
	} m_Value;
};

// ��������� �� ����������� ����
// WPARAM		- 0
// LPARAM		- 0
// LRESULT	- �� ������������
UINT const ABTM_WINDOWSHUTDOWN				= (0xC000 - 100);

// ������ �� ��������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ����� ���� ��������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� ABTMessageInfo
//						m_Value.m_nItemIndex	- ����� ���� -1, ���� ��� ���������������� ��������
//						m_Value.m_hMenu - Handle ���� (HMENU)
// LRESULT	- �� ������������
UINT const ABTM_PREPROCESSCONTEXTMENU = (0xC000 - 101);

// ������ �� ���������� ������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������� ���������
//            ��-��������� - TRUE
// LPARAM		- ��������� �� ��������� ��������� ABTMessageInfo
//						m_Value.m_iCommandId - ������������� ������� ����
// LRESULT	- �� ������������
UINT const ABTM_DOCONTEXTMENUCOMMAND  = (0xC000 - 102);

// ������ �� �������� ������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� �������� �����
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� ABTMessageInfo
//						m_Value.m_pContext - ��������� �� �������� ������
// LRESULT	- �� ������������
UINT const ABTM_GETFINDITEMCONTEXT    = (0xC000 - 103);

// ������ �� �������� �������� ��� ������
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ������� ������������� ������� ������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� ABTMessageInfo
//						m_Value.m_pContext - ��������� �� �������� ������
// LRESULT	- �� ������������
UINT const ABTM_CHECKITEMFORFIND      = (0xC000 - 104);

// ������ �� �������� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ���� ���� �������
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ��������� ABTMessageInfo
//						m_Value.m_nItemIndex	- ����� ���� -1, ���� ��� ���������������� ��������
//						m_Value.m_hMenu - Handle ���� (HMENU)
// LRESULT	- �� ������������
UINT const ABTM_CREATECONTEXTMENU			= (0xC000 - 105);

// ��������� � ������� toolbar ID ��� ����
// WPARAM		- LPBOOL - ��������� �� ��������� - TRUE - ���� ID �����
//            ��-��������� - FALSE
// LPARAM		- ��������� �� ��������� ABTMessageInfo 
//            m_Value.m_ToolBarStuff[2]	- �������� toolbar ID[0] and Handle[1]
// LRESULT	- �� ������������
UINT const ABTM_GETMENUTOOLBAR		   = (0xC000 - 106);

// ��������� � ����� �������������� �������
// WPARAM		- �� ������������ ( =0 )
// LPARAM		- ��������� �� ��������� ��������� ABTMessageInfo
//						m_Value.m_bSetRemove - TRUE - ���������, FALSE - ������
// LRESULT	- �� ������������
UINT const ABTM_ITEMSELCHANGING			 = (0xC000 - 107);

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// ������ �� ���������� ������� ���� ��� ������������ �� CCheckList
// WPARAM		- ������������� �������
// LPARAM		- �� ������������
// LRESULT	- �� ������������
UINT const CLWM_DOCOMMAND							= (0xC000 - 200);

// ������ �� ���������� ������� ���� ��� ������������ �� CCheckTree
// WPARAM		- ������������� �������
// LPARAM		- �� ������������
// LRESULT	- �� ������������
UINT const CTWM_DOCOMMAND							= (0xC000 - 201);

#endif