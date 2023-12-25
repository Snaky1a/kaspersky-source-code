#include <windows.h>
#include <tchar.h>
#include <stuff/pathstr.h>
#include <stuffio/ioutil.h>

TCHAR* DuplicateFileName( const TCHAR* s );
TCHAR* DuplicateString( const TCHAR* s );

//---
IOS_ERROR_CODE IOSCreateDirectory( const TCHAR * pszDirName ) {
  if ( pszDirName ) {
    ::IOSSetLastError( IOS_ERR_OK );

    bool ret = true;
  
  // ��������� ������� ����/�������
    CAPointer<TCHAR> currDir = new TCHAR[_MAX_PATH];
    ::IOSGetCurrentDirectory( currDir, _MAX_PATH );

    CAPointer<TCHAR> pszoemDirName = ::DuplicateFileName( pszDirName );
  
  /*  
    if ( !::CreateDirectory(pszDirName, NULL) ) 
      ::Win32ErrToIOSErr( ::GetLastError() );
  */
    if ( !::SetCurrentDirectory(pszoemDirName) ) {
  // ���� ������� �� ����������� - ��� ����� ���������
  // �������� ���������� �������� ���������� ����
      CAPointer<TCHAR> path = ::DuplicateString( pszoemDirName );
      TCHAR *p;
      do {
        p = _tcsrchr( path, L'\\' );
        if ( p ) 
          *p = L'\0';
      } while( p && _tcsnextc(path) != L'\0' && !::SetCurrentDirectory(path) ); // ���� �� ���������������

  // ������� ������� ���������
      while ( _tcsclen(path) != _tcsclen(pszoemDirName) ) {
        *_tcsninc(((TCHAR *)path), _tcsclen(path)) = L'\\';
        
        if ( !::CreateDirectory(path, NULL) ) {
          ret = false;
          break;
        }
      }
    }

    if ( !ret )
      ::Win32ErrToIOSErr( ::GetLastError() );

  // ������������ ������� ����/�������
    ::IOSSetCurrentDirectory( currDir );

    return ::IOSGetLastError();
  }
  return IOS_ERR_INVALID_FILE_NAME;
}


