#include <windows.h>
#include <stuffio/ioutil.h>


// ��������� ��� ����������
//
UINT IOSGetDriveType( const TCHAR *pszDriveName ) {
	return ::GetDriveType( pszDriveName );
}

