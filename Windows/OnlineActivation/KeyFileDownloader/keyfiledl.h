/*!
	(�) 2003 "Kaspersky Lab"

	\file keyfiledl.h
	\author Guzhov Andrey
	\date 26.05.2003
	\brief ������������ ������� ���������� ���������� ������ �������������� �� Internet.
*/

#ifndef KFD_KEYFILEDL_H
#define KFD_KEYFILEDL_H

#include <windows.h>

#ifdef KEYFILEDOWNLOADER_EXPORTS
	#define KFD_DLL_API __declspec(dllexport)
#else
	#define KFD_DLL_API __declspec(dllimport)
#endif

// ���� �������� ������������ �������.

const int ERR_SUCCESS			= 0;	//!< �������� ����������
const int ERR_BAD_HWND			= 1;	//!< ������������ ���������� �������
const int ERR_BAD_RID			= 2;	//!< ������������ ������������� �������
const int ERR_BAD_KEY			= 3;	//!< �������� ������ � ���� "����"
const int ERR_BAD_URL			= 4;	//!< ������������ URL
const int ERR_BAD_FOLDER		= 5;	//!< ������������ ������� �������
const int ERR_MEM_ALLOC			= 6;	//!< ������ ��������� ������
const int ERR_CONV_ANSI			= 7;	//!< ������ ����������� ���������� � ansi ������ (url, folder, agent)
const int ERR_THR_CREATE		= 8;	//!< ������ �������� �������� ������
const int ERR_THR_STARTED		= 9;	//!< ������� ����� ��� �������
const int ERR_THR_STOPPED		= 10;	//!< ������� ����� �� �������


// ��������� �� ������ ����������

// ��������� "�������� ����������"
const int MSG_INITING			= 101;	// ������������� ����������
const int MSG_POSTING_DATA		= 102;	// ����� ������ �� ������
const int MSG_SAVING_TMP		= 103;	// ���������� �������� �� ��������� ��������
const int MSG_VERIFYING			= 104;	// �������� ��������
const int MSG_RETRYING			= 105;	// ��������� ������� ��������� ��������
const int MSG_SAVING_DST		= 106;	// ���������� �������� � ������� ��������
const int MSG_POSTING_STAT		= 107;	// ������� ������� ���������� �������� �� ������
const int MSG_COMPLETED			= 108;	// ������ ������� ���������

// ��������� "�������� http ����������"
const int MSG_CONNECTING		= 701;	// ���������� � ��������
const int MSG_RESOLVING			= 702;	// ���������� IP ������
const int MSG_SENDING			= 703;	// ����� ���������
const int MSG_SENT				= 704;	// ��������� ������� 
const int MSG_RECEIVING			= 705;	// ��������� ������ �������
const int MSG_RECEIVED			= 706;	// ������ ������� �������
const int MSG_REDIRECTING		= 707;	// ���������������

// ��������� �� �������

// ��������� "������ ����������"
const int MSGERR_CANCELLED		= 600;	// ������ ��������
const int MSGERR_INITING		= 601;	// ������ �������������
const int MSGERR_FILLDATA		= 602;	// ������ ���������� ����� �������
const int MSGERR_SENDING		= 603;	// ������ ������ http-�������
const int MSGERR_BADCONTENT		= 604;	// � ������� �������� �������� ������
const int MSGERR_GETSTATUS		= 605;	// ���������� �������� ������ ������
const int MSGERR_SAVETEMP		= 606;	// ������ ��� ���������� ���������� �����
const int MSGERR_SAVEDST		= 607;	// ������ ��� ���������� �������� �����
const int MSGERR_BADLICENSE		= 608;	// �������� �� �������������
const int MSGERR_CORRUPTLIC		= 609;	// �������� �� ����������� �������� �� �������


// http ������ ������ 4��
const int MSGERR_CLNT_SYNTHAX	= 400;	// ������ ���������� � �������
const int MSGERR_CLNT_UNAUTH	= 401;	// ���������� �����������
const int MSGERR_CLNT_FORBID	= 403;	// ������ � ������� ��������
const int MSGERR_CLNT_NOTFND	= 404;	// ������ �� ������
const int MSGERR_CLNT_BADMETH	= 405;	// ����� ��������
const int MSGERR_CLNT_NONACPT	= 406;	// �� ������� ���������� ���������� �������
const int MSGERR_CLNT_PRXAUTHRQ	= 407;	// ��������� ������-�����������
const int MSGERR_CLNT_TIMOUT	= 408;	// ������� �������� �������
const int MSGERR_CLNT_STCONFL	= 409;	// �������� - ���������� ���. ����������
const int MSGERR_CLNT_GONE		= 410;	// ������ ������ � ������� ��������
const int MSGERR_CLNT_LENREQ	= 411;	// ��������� ����� �����������
const int MSGERR_CLNT_PREFAIL	= 412;	// ���������� ����������� ���� ����
const int MSGERR_CLNT_TOOLARGE	= 413;	// ������ ������� �����
const int MSGERR_CLNT_URILONG	= 414;	// URI ������� �������
const int MSGERR_CLNT_UNSMEDIA	= 415;	// �� �������������� ������ ������
const int MSGERR_CLNT_OTHER		= 499;	// ��������. ������ �� ������� �������

// http ������ ������� 5��
const int MSGERR_SERV_INT		= 500;	// ���������� ������ �������
const int MSGERR_SERV_NSUP		= 501;	// ���������������� �� ��������������
const int MSGERR_SERV_BADGATE	= 502;	// ������������ ����� �� �����
const int MSGERR_SERV_UNVL		= 503;	// ������ �������� ����������
const int MSGERR_SERV_GATIMO	= 504;	// ������� �������� ������ �� �����
const int MSGERR_SERV_PROT		= 505;	// �������� �� �������������� ��������
const int MSGERR_SERV_OTHER		= 599;	// ��������. ������ �� ������� �������

const int MSGERR_HTTP_OTHER		= 799;	// ��������. ������ http


// ������� ���������� �������� ��������� ��������
const wchar_t MSG_LIC_OK[]		= L"SUCCESSFUL. PID=%d, VER=%s";
const wchar_t MSG_LIC_BAD[]		= L"WRONG. PID=%d, VER=%s";
const wchar_t MSG_LIC_CORRUPT[]	= L"CORRUPTED. PID=%d, VER=%s";

#pragma pack(1)

//! ��������� ������ ������������
/*!
	���������� ��� �������� ������, �������� ������������� � �����������. 
	#pragma pack(1) ���������� ��� ������������ ������ ��������� �� �������
	�����, �.�. ���������� ��-������� �� ��������.
*/
struct CUserData
{
	int		nProdId;		//!< ������������� ���������������� ��������
	LPWSTR	lpszProdVer;	//!< ������ ���������������� ��������
	LPWSTR	lpszAgent;		//!< ������������� ������ HTTP (User-Agent)
	LPWSTR	lpszUrl;		//!< URL ������� ��������� � ������� http://server/path
	LPWSTR	lpszDstFolder;	//!< ������� ������� ��� ���������� �����
	LPWSTR	lpszKeyNum;		//!< ���� � ������� XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
	LPWSTR	lpszCompany;	//!< �������� �������� ������������
	LPWSTR	lpszName;		//!< ��� ������������
	LPWSTR	lpszCountry;	//!< �������� ������ ������������
	LPWSTR	lpszCity;		//!< �������� ������ ������������
	LPWSTR	lpszAddress;	//!< ����� ������������
	LPWSTR	lpszTelephone;	//!< ������� ������������
	LPWSTR	lpszFax;		//!< ���� ������������
	LPWSTR	lpszEmail;		//!< �-���� ������������
	LPWSTR	lpszWww;		//!< URL ������������

};

#pragma pack()

//! ������� ��������� ����� �������������.
/*!
	��������� ������� ����� � ���������� ����������. � ������ ����������� 
	���������� ����� �� Internet �� ��������� HTTP/1.0. � �������� ������ 
	������������ �������� lpszUrl. ���� ����������� �� ������������  ����� 
	��������� �������������� ��������, ������������� � ����� � ����������� 
	� ��������� CUserData.nProdId. ���� �� ������ ���� ���������, OEM, 
	����������, ��������. ���� ��� ������� �����������, �� ���� ����������� 
	� ������� �������� CUserData.lpszDstFolder.

	������ ���������� ������ ���������� ����������� �������� ��������� �������� 
	nDlgItem ������� hDialog. �������� ��������� ��������� � ����� cmndefs.h.
	��������� ���������� �������� Win32 API SendMessage().

	\param hDialog			[in]	���������� �������
	\param nDlgItem			[in]	������������� �������� �������
	\param pUserData		[in]	��������� �� ��������� ������ ������������

	\return ERR_SUCCESS ������� ����� ������� ������
	\return ERR_BAD_HWND ������� ������������ ���������� �������
	\return ERR_BAD_RID ������� ������������ ������������� �������� �������
	\return ERR_BAD_KEY �������� ������ � ���� ����
	\return ERR_BAD_URL ������� �������� URL
	\return ERR_BAD_FOLDER ������� �������� ������� �������
	\return ERR_MEM_ALLOC ������ ��������� ������
	\return ERR_CONV_ANSI ������ ����������� ���������� � ANSI
	\return ERR_THR_CREATE ������ �������� �������� ������
	\return ERR_THR_STARTED ������� ����� ��� ������� (��� ������� ���������� �������)
*/
KFD_DLL_API int WINAPI StartDownloadKeyFile(
						HWND			hDialog,
						int				nDlgItem,
						const CUserData	*pUserData
);

//! �������-������� ���������� � ��������� ��������� �����.
/*!
	��������� ������� ����� � ���������� ����������. � ������ ����������� 
	���������� ����� �� Internet �� ��������� HTTP/1.0. � �������� ������ 
*/

typedef void (WINAPI* KFD_NOTIFICATION_CALLBACK)(void* pContext, unsigned int nStatusCode);

//! ������� ��������� ����� � �������������� ��������
/*!
	�������� ���������� ������� StartDownloadKeyFile
*/
KFD_DLL_API int WINAPI StartDownloadKeyFileCallback(
						KFD_NOTIFICATION_CALLBACK fCallback,
						void* pContext,
						const CUserData	*pUserData
);

//! ������� ����������� ��������� ����� � �������������� ��������
/*!
	�������� ���������� ������� StartDownloadKeyFile
*/
KFD_DLL_API int WINAPI StartDownloadKeyFileSyncCallback(
						KFD_NOTIFICATION_CALLBACK fCallback,
						void* pContext,
						const CUserData	*pUserData
);


//! ������� ������ ��������� �����.
/*!
	���������� ���� ���������� ������ � ���������� ����������. ���������
	���������� ����� ��������� � ���������� ������ ���������� MSGERR_CANCELLED.

	\return ERR_SUCCESS ���� �������� ������� ���������
	\return ERR_THR_STOPPED ������� ����� �� ��� �������
*/
KFD_DLL_API int WINAPI StopDownloadKeyFile();

//! ������� ��������� ����� ����� �����
/*!
	������ ���������� ����� ��������� ��������� MSG_COMPLETED.

	\param szName	[out] ����� ��� ���������� ����� �����
	\param pLength	[in, out] ������ ������

	\return ������ ����� ����� � TCHAR ��� ������������ ����
	\return 0 � ������ ������, pLength �������� ��������� ������ ������
*/
KFD_DLL_API int WINAPI GetKeyFileName(TCHAR* szName, int* pLength);

//! ������� ��������� ����� � ������ ������������ ��� ����������� �� ������-�������. 
/*!
	������ ���������� �� �������� ��� ��������� ��������� MSGERR_CLNT_PRXAUTHRQ.

	\param szUserName	[in] ��� ������������
	\param szPassword	[in] ������ ������������

	\return ERR_SUCCESS �������� ������� ���������, � ��������� ������ GetLastError()
*/
KFD_DLL_API int WINAPI SetCredentialProxy(TCHAR* szUserName, TCHAR* szPassword);

//! ������� ��������� ����� � ������ ������������ ��� ����������� �� http-�������. 
/*!
	������ ���������� �� �������� ��� ��������� ��������� MSGERR_CLNT_UNAUTH.

	\param szUserName	[in] ��� ������������
	\param szPassword	[in] ������ ������������

	\return ERR_SUCCESS �������� ������� ���������, � ��������� ������ GetLastError()
*/
KFD_DLL_API int WINAPI SetCredentialServer(TCHAR* szUserName, TCHAR* szPassword);

//! ������� ������������� ����������. 
/*!
	������ ���������� �� ������ ��������� ������������ �������.

	\return ERR_SUCCESS ������������� ������� ���������
*/
KFD_DLL_API int WINAPI InitLibrary();

//! ������� ��������������� ����������
/*!
	������ ���������� ����� ��������� ����������. ���������� ����
	���������� �������� ������ � ������� ��� ����������.
	
	\warning ������ �������� ������ ������� � ����������� ��������� 
	�� ����������, �.�. ��� �������� � DeadLock.

	\return ERR_SUCCESS ��������������� ������� ���������
*/
KFD_DLL_API int WINAPI DeinitLibrary();

#endif // KFD_KEYFILEDL_H