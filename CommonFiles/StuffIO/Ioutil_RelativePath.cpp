#include <windows.h>
#include <tchar.h>
#include <stuff/pathstr.h>
#include <stuffio/ioutil.h>

IOS_ERROR_CODE IOSFinishCopying( const TCHAR * pszFileName, TCHAR * pszBuffer, uint uicchBufferLen );

//---
IOS_ERROR_CODE IOSRelativePathFromFullPath( const TCHAR * pszMainFileName, const TCHAR * pszRelFileName, TCHAR * pszBuffer, uint uicchBufferLen ) {
  if ( pszMainFileName && pszRelFileName && pszBuffer ) {
    // ��������� � ������ ����
    CAPointer<TCHAR> mainFullPath = new TCHAR[_MAX_PATH];
    IOS_ERROR_CODE result = ::IOSMakeFullPath( pszMainFileName, mainFullPath, _MAX_PATH );
    if ( result == IOS_ERR_OK ) {
      CAPointer<TCHAR> relFullPath = new TCHAR[_MAX_PATH];
      _tcscpy( relFullPath, pszRelFileName );
			int n0 = _tcsnextc(_tcsninc(relFullPath, 0));
			int n1 = _tcsnextc(_tcsninc(relFullPath, 1));
      if ( n1 == L':' || (n0 == L'\\' && n1 == L'\\' ) ) { // ���� ��� �������� ������ ����
      
        // ������� �������� �������
        CAPointer<TCHAR> mainRootDir = new TCHAR[_MAX_PATH];
        result = ::IOSRootDirExtract( mainFullPath, mainRootDir, _MAX_PATH );
        if (  result == IOS_ERR_OK ) {
          // ������� �������� �������
          CAPointer<TCHAR> relRootDir = new TCHAR[_MAX_PATH];
          result = ::IOSRootDirExtract( relFullPath, relRootDir, _MAX_PATH );
          if (  result == IOS_ERR_OK ) {
            // �������� ���������� �������� ���������
            if ( !_tcsicmp(mainRootDir, relRootDir) ) {
              // ������� ������ ����
              result = ::IOSDirExtract( mainFullPath, mainFullPath, _MAX_PATH );
              if ( result == IOS_ERR_OK ) {
                // ������� ������ ����
                result = ::IOSDirExtract( relFullPath, relFullPath, _MAX_PATH );
                if ( result == IOS_ERR_OK ) {
                  // �������� ������ ����� �����
                  int mainCharCount = (int)_tcsclen( mainFullPath );
                  int relCharCount  = (int)_tcsclen( relFullPath );

                  // �������� ���� �� ������������
                  TCHAR *mainSubDir = _tcstok( mainFullPath, _T("\\") );
                  while ( mainSubDir )
                    mainSubDir = _tcstok( NULL, _T("\\") );

                  TCHAR *relSubDir  = _tcstok( relFullPath, _T("\\") );
                  while ( relSubDir )
                    relSubDir = _tcstok( NULL, _T("\\") );

                  // ���� ������ ������������ �����  
                  mainSubDir = mainFullPath;
                  relSubDir  = relFullPath;
                  int mainCount = 0;
                  int relCount  = 0;
                  while ( mainCount < mainCharCount && 
                          relCount  < relCharCount  &&
                          !_tcsicmp(mainSubDir, relSubDir ) ) {
                    int curLen = (int)_tcsclen( mainSubDir );
                    mainCount  += curLen + 1;
                    mainSubDir = _tcsninc( mainSubDir, curLen ) + 1;
                    curLen = (int)_tcsclen( relSubDir );
                    relCount  += curLen + 1;
                    relSubDir = _tcsninc(relSubDir, curLen) + 1;
                  }        

                  // ������� ����� ����� � ��������� ��� ��������� �������
                  // �� ���������� ��������� �������� ����
                  CPathStr pszFinishPath( _MAX_PATH );
                  while ( mainCount < mainCharCount ) {
                    _tcscat( pszFinishPath, _T("..\\") );
                    int curLen = (int)_tcsclen( mainSubDir );
                    mainCount  += curLen + 1;
                    mainSubDir = _tcsninc( mainSubDir, curLen ) + 1;
                  }        
                  // ��������� ����� ����������� ���������� �� ���������
                  // ��������������� ����
                  while ( relCount < relCharCount ) {
                    _tcscat( pszFinishPath, relSubDir );
                    _tcscat( pszFinishPath, _T("\\") );
                    int curLen = (int)_tcsclen( relSubDir );
                    relCount  += curLen + 1;
                    relSubDir = _tcsninc(relSubDir, curLen) + 1;
                  }        

                  // ������� ��� ����� � ��������� �� �������������� ����
                  _tcscpy( relFullPath, pszRelFileName );
                  ::IOSFileExtract( relFullPath, relFullPath, _MAX_PATH );
                  _tcscat( pszFinishPath, relFullPath );

                  // ����������� ����������� � ��������� ������� ������
                  return ::IOSFinishCopying( pszFinishPath, pszBuffer, uicchBufferLen );
                }
              }
            }
            else
              // ���� �������� �������� �� ��������� - ������ �������� � ��������
              // �����
              return ::IOSFinishCopying( relFullPath, pszBuffer, uicchBufferLen );
          }
        }
      }
    }
    return result;
  }
  return IOS_ERR_INVALID_FILE_NAME;
}

//---
IOS_ERROR_CODE IOSFullPathFromRelativePath( const TCHAR * pszMainFileName, const TCHAR * pszRelFileName, TCHAR * pszBuffer, uint uicchBufferLen ) {
  if ( pszRelFileName && pszBuffer ) {
    // ��������� � ������ ����
    CAPointer<TCHAR> mainFullPath = new TCHAR[_MAX_PATH];
    IOS_ERROR_CODE result = ::IOSMakeFullPath( pszMainFileName, mainFullPath, _MAX_PATH );
    if ( result == IOS_ERR_OK ) {
      // ������� ������ ����
      result = ::IOSDirExtract( mainFullPath, mainFullPath, _MAX_PATH );
      if ( result == IOS_ERR_OK ) {
      // ������� ������ ����
        CAPointer<TCHAR> relPath = new TCHAR[_MAX_PATH];
        result = ::IOSDirExtract( pszRelFileName, relPath, _MAX_PATH );
        if ( result == IOS_ERR_OK ) {
					int n0 = _tcsnextc(_tcsninc(relPath, 0));
					int n1 = _tcsnextc(_tcsninc(relPath, 1));
          if ( !(n1 == L':' || (n0 == L'\\' && n1 == L'\\' ) ) ) { // ���� ��� �� �������� ������ ����
            if ( n0 != L'\\' ) {
              // ���� ������������ ���� ������������� �������������
              // �������� ������ ����� �����
              int mainCharCount = (int)_tcsclen( mainFullPath );
              int relCharCount  = (int)_tcsclen( relPath );

              // �������� ���� �� ������������
              TCHAR *mainSubDir = _tcstok( mainFullPath, _T("\\") );
              while ( mainSubDir )
                mainSubDir = _tcstok( NULL, _T("\\") );

              TCHAR *relSubDir  = _tcstok( relPath, _T("\\") );
              while ( relSubDir )
                relSubDir = _tcstok( NULL, _T("\\") );

              // ��������� �� ����� �������� ���� ������� ���������,
              // ������� �������� ����� � �����������
              mainSubDir = _tcsninc(mainFullPath, mainCharCount);
              relSubDir  = relPath;
              int mainCount = 0;
              int relCount  = 0;
              while ( mainCount < mainCharCount && 
                      relCount  < relCharCount  &&
                      !_tcsicmp(relSubDir, _T("..") ) ) {
                mainSubDir = _tcsdec(mainFullPath, mainSubDir);
                while ( mainSubDir && _tcsnextc(mainSubDir) != L'\0' )
                  mainSubDir = _tcsdec(mainFullPath, mainSubDir);
								if ( !mainSubDir )
									mainSubDir = mainFullPath;
                int curLen = (int)_tcsclen( mainSubDir + 1 );
                mainCount  += curLen + 1;
                curLen = (int)_tcsclen( relSubDir );
                relCount  += curLen + 1;
								relSubDir = _tcsninc( relSubDir, curLen ) + 1;
              }        

              // ������� ����� ����� � ��������� ��� ���������� ������
              // �������� ����
              CAPointer<TCHAR> pszFinishPath = new TCHAR[_MAX_PATH];
              *pszFinishPath = L'\0';
              mainSubDir = mainFullPath;
              mainCharCount -= mainCount;
              mainCount     = 0;
              while ( mainCount < mainCharCount ) {
                _tcscat( pszFinishPath, mainSubDir );
                _tcscat( pszFinishPath, _T("\\") );
                int curLen = (int)_tcsclen( mainSubDir );
                mainCount  += curLen + 1;
                mainSubDir = _tcsninc(mainSubDir, curLen) + 1;
              }        
              // ��������� � ����� ���������� ����� ������������
              while ( relCount < relCharCount ) {
                _tcscat( pszFinishPath, relSubDir );
                _tcscat( pszFinishPath, _T("\\") );
                int curLen = (int)_tcsclen( relSubDir );
                relCount  += curLen + 1;
                relSubDir = _tcsninc(relSubDir, curLen - 1) + 1;
              }        

              // �������� ��� � ��������� �� �������������� ����
              _tcscpy( relPath, pszRelFileName );
              ::IOSFileExtract( relPath, relPath, _MAX_PATH );
              _tcscat( pszFinishPath, relPath );

              // ����������� ����������� � ��������� ������� ������
              return ::IOSFinishCopying( pszFinishPath, pszBuffer, uicchBufferLen );
            }
            else {
              // ��� �������� ������� �������� ����
              CPathStr pszFinishPath( _MAX_PATH );
              result = ::IOSRootDirExtract( mainFullPath, pszFinishPath, _MAX_PATH );
              if (  result == IOS_ERR_OK ) {
                pszFinishPath = _tcsninc(relPath, 1);
                // �������� ��� � ��������� �� �������������� ����
                _tcscpy( relPath, pszRelFileName );
                ::IOSFileExtract( relPath, relPath, _MAX_PATH );
                pszFinishPath ^= relPath;

                // ����������� ����������� � ��������� ������� ������
                return ::IOSFinishCopying( pszFinishPath, pszBuffer, uicchBufferLen );
              }
            } 
          }
          else {
            // ���� ����������� ���� �� ������������� - ������ �������� � �������� �����
            result = ::IOSMakeFullPath( pszRelFileName, relPath, _MAX_PATH );
            if ( result == IOS_ERR_OK ) 
              return ::IOSFinishCopying( relPath, pszBuffer, uicchBufferLen );
          }  
        }
      }
    }
    return result;
  }
  return IOS_ERR_INVALID_FILE_NAME;
}
