#include <windows.h>
#include <tchar.h>
#include <stuffio/ioutil.h>


// �������� �������� ��� ����� 
//
DWORD IOSGetShortPathName( const TCHAR *lpszLongPath, TCHAR *lpszShortPath, DWORD cchBuffer ) {
	return ::GetShortPathName( lpszLongPath, lpszShortPath, cchBuffer );
}

