#include <windows.h>
#include <tchar.h>
#include <stuffio/ioutil.h>


// �������� ������� ��������� ������ 
// 
DWORD IOSGetTempPath( DWORD cchBuffer, TCHAR *pchBuffer ) {
	return ::GetTempPath( cchBuffer, pchBuffer ); 
}


// �������� ���� �� ��������� ����
UINT IOSGetTempFileName( const TCHAR *lpPathName, const TCHAR *lpPrefixString, UINT uUnique, TCHAR *lpTempFileName ) {
	return ::GetTempFileName( lpPathName, lpPrefixString, uUnique, lpTempFileName );
}
