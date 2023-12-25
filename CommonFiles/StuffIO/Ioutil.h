#ifndef __IOUTIL_H
#define __IOUTIL_H

#include <windows.h>
#include <tchar.h>
#include "../stuff/stddefs.h"
#include "xerrors.h"


// �������� ��� ������� IOSGetFileInfo
//--
typedef struct {
  uint uiSecond;
  uint uiMinute;
  uint uiHour;
  uint uiDay;
  uint uiDayOfWeek;
  uint uiMonth;
  uint uiYear;
} IOSTIME, *PIOSTIME;

//--
typedef struct {
  uint32 dwcbSize;
  IOSTIME fioTime;
} IOSFILEINFO, *PIOSFILEINFO; 

// �������� ���������� � �����
// pszFileName - ������ ��� �����
// pfi         - ��������� �� �������������� ���������
IOS_ERROR_CODE IOSGetFileInfo(const TCHAR * pszFileName, PIOSFILEINFO pfi);
IOS_ERROR_CODE IOSGetFileInfoW(const WCHAR * pszFileName, PIOSFILEINFO pfi);


// ���������� ����
// pszSrc        - ������ ��� ��������� �����
// pszDst        - ������ ��� ��������� �����
// fFailIfExists - true - ���� ������ ��������� ����������� �� ������������ ����
IOS_ERROR_CODE IOSCopyFile( const TCHAR * pszSrc, const TCHAR * pszDst, bool fFailIfExists = false );
IOS_ERROR_CODE IOSCopyFileW( const WCHAR * pszSrc, const WCHAR * pszDst, bool fFailIfExists = false );


// ������� ����
// pszFileName - ������ ��� �����
IOS_ERROR_CODE IOSDeleteFile( const TCHAR * pszFileName );
IOS_ERROR_CODE IOSDeleteFileW( const WCHAR * pszFileName );


// ������������� ����
// pszOldFileName  - ������ ��� ��������� �����
// pszNewFileName  - ������ ��� ��������� �����
IOS_ERROR_CODE IOSRenameFile( const TCHAR * pszOldFileName, const TCHAR * pszNewFileName );


// ������� �������
// pszDirName - ������ ��� ��������
IOS_ERROR_CODE IOSCreateDirectory( const TCHAR * pszDirName );
IOS_ERROR_CODE IOSCreateDirectoryW( const WCHAR * pszDirName );


// ������� �������
// pszDirName - ������ ��� ��������
IOS_ERROR_CODE IOSDeleteDirectory( const TCHAR * pszDirName );


// �������� ������� ������� ������
// pszDirBuf    - ����� ��� ����� ��������
// uicchBufSize - ������ ������
IOS_ERROR_CODE IOSGetCurrentDirectory( TCHAR * pszDirBuf, uint uicchBufSize, ulong *puicchBuffSizeNeeded = NULL );
IOS_ERROR_CODE IOSGetCurrentDirectoryW( wchar_t * pszDirBuf, uint uicchBufSize, ulong *puicchBuffSizeNeeded = NULL );


// ���������� ������� ������� ������
// pszDirName - ��� ��������
IOS_ERROR_CODE IOSSetCurrentDirectory( const TCHAR * pszDirName );
IOS_ERROR_CODE IOSSetCurrentDirectoryW( const wchar_t * pszDirName );


// ��������� ����������� ������ � ��������� ����
// pszFileName     - ������ ��� �����
// fCheckDirectory - true - ���� ����� ��������� ����������� ������ � �������
//                          ���������� �����           
IOS_ERROR_CODE IOSCheckWritableFile( const TCHAR * pszFileName, bool fCheckDirectory = true );


// ��������� ����������� ������ � ��������� �������
// pszDirName - ��� ��������
IOS_ERROR_CODE IOSCheckWritableDir( const TCHAR * pszDirName );
IOS_ERROR_CODE IOSCheckWritableDirW( const WCHAR * pszDirName );


// ��������� - �������� �� ������ ��� ������ ��������
// pszFileName - ����������� ���
IOS_ERROR_CODE IOSGetIsDirectory( const TCHAR * pszFileName );
IOS_ERROR_CODE IOSGetIsDirectoryW( const WCHAR * pszFileName );


// ������ ������ ����� � ������
// pszFileName      - ��� �����
// pdwcbyFileLength - �������� �������� - ������ �����
IOS_ERROR_CODE IOSFileLengthName( const TCHAR * pszFileName, uint32 * pdwcbyFileLength );
IOS_ERROR_CODE IOSFileLengthNameW( const WCHAR * pszFileName, uint32 * pdwcbyFileLength );


// �������� ������� ����� � �������� ������
// pszFileName - ������ ��� �����
IOS_ERROR_CODE IOSFileExists( const TCHAR * pszFileName );
IOS_ERROR_CODE IOSFileExistsW( const WCHAR * pszFileName );


// ��������� ������ ��� �����
// pszRelativePath - ������������� ��� �����
// pszBuffer       - ����� ��� ������ ���
// uicchBufferLen  - ������ ������
IOS_ERROR_CODE IOSMakeFullPath( const TCHAR * pszRelativePath, TCHAR * pszBuffer, uint uicchBufferLen );
IOS_ERROR_CODE IOSMakeFullPathW( const WCHAR * pszRelativePath, WCHAR * pszBuffer, uint uicchBufferLen );


// ������� ���� �� ������� ����� �����
// pszFileName    - ������ ��� �����
// pszDirName     - ����� ��� �������� ��� ��������
// uicchBufferLen - ������ ������
IOS_ERROR_CODE IOSDirExtract( const TCHAR * pszFileName, TCHAR * pszDirName, uint uicchBufferLen );
IOS_ERROR_CODE IOSDirExtractW( const WCHAR * pszFileName, WCHAR * pszDirName, uint uicchBufferLen );


// ������� ��� ��������� �������� �� ������� ����� �����
// pszFileName    - ������ ��� �����
// pszDirName     - ����� ��� �������� ��� ��������
// uicchBufferLen - ������ ������
IOS_ERROR_CODE IOSRootDirExtract( const TCHAR * pszFileName, TCHAR * pszDirName, uint uicchBufferLen );
IOS_ERROR_CODE IOSRootDirExtractW( const WCHAR * pszFileName, WCHAR * pszDirName, uint uicchBufferLen );


// ������� ��� ����� � ����������� �� ������� ����� �����
// pszFullFileName  - ������ ��� �����
// pszFileName      - ����� ��� ��� �����
// uicchBufferLen   - ������ ������
IOS_ERROR_CODE IOSFileExtract( const TCHAR * pszFullFileName, TCHAR * pszFileName, uint uicchBufferLen );
IOS_ERROR_CODE IOSFileExtractW( const WCHAR * pszFullFileName, WCHAR * pszFileName, uint uicchBufferLen );


// ������� ��� ����� ��� ���������� �� ������� ����� �����
// pszFullFileName  - ������ ��� �����
// pszFileName      - ����� ��� ��� �����
// uicchBufferLen   - ������ ������
IOS_ERROR_CODE IOSPureFileExtract( const TCHAR * pszFullFileName, TCHAR * pszFileName, uint uicchBufferLen );


// ����� ������� ���������� � ����� �����
// pszFileName - ��� �����
// realExt     - true - ���� ����� ������ ������� �������� ������� � ����������
//                      ����� �������� ������� '.'
TCHAR 				 * IOSFindFileExtention( const TCHAR *pszFileName, bool realExt = false );
WCHAR 				 * IOSFindFileExtentionW( const WCHAR *pszFileName, bool realExt = false );


// ��������� ������������� ��� ����� ������������ ��������� �����
// pszMainFileName  - ��� ��������� �����
// pszRelFileName   - ��� ��������������� �����
// pszBuffer        - ����� ��� �������� ���
// uicchBufferLen   - ������ ������
IOS_ERROR_CODE IOSRelativePathFromFullPath( const TCHAR * pszMainFileName, const TCHAR * pszRelFileName, TCHAR * pszBuffer, uint uicchBufferLen );



// ��������� ������ ��� ����� �� ��������������
// pszMainFileName  - ��� ��������� �����
// pszRelFileName   - ��� ��������������� �����
// pszBuffer        - ����� ��� �������� ���
// uicchBufferLen   - ������ ������
IOS_ERROR_CODE IOSFullPathFromRelativePath( const TCHAR * pszMainFileName, const TCHAR * pszRelFileName, TCHAR * pszBuffer, uint uicchBufferLen );
IOS_ERROR_CODE IOSFullPathFromRelativePathW( const WCHAR * pszMainFileName, const WCHAR * pszRelFileName, WCHAR * pszBuffer, uint uicchBufferLen );


// ������������� (���� ��������) ��������� ��� � ��� � ������� UNC
// pszLocalPath - �������� ��������� ���
// pszUNCPath   - ����� ��� �������� ��� � ������� UNC
// uicchUNCLen  - ������ ������
IOS_ERROR_CODE IOSLocalPathToUNC( const TCHAR *pszLocalPath, TCHAR *pszUNCPath, uint uicchUNCLen );
IOS_ERROR_CODE IOSLocalPathToUNCW( const WCHAR *pszLocalPath, WCHAR *pszUNCPath, uint uicchUNCLen );


// ������������� �������� ��� � �������
// pszFileName    - ��� �����
// pszBuffer      - �������� �����
// uicchBufferLen - ������ ������
IOS_ERROR_CODE IOSGetLongPathName( const TCHAR *pszFileName, TCHAR *szBuffer, uint uicchBufferLen );


// ������������� ��� ����� � ������������ �������
// pszSourcePath  - �������� ��� �����
// pszBasePath    - ������� ����
// pszAlias       - ������� ��� ������ ����
// pszBuffer      - �������� �����
// uicchBufferLen - ������ ������
// ������ :
// pszSourcePath  - "�:\myfiles\myprojects\firstproject\shelf.cdw"
// pszBasePath    - "�:\myfiles\myprojects"
// pszAlias       - "allprojects"
// pszBuffer      - "<allprojects>\firstproject\shelf.cdw"
IOS_ERROR_CODE IOSFullPathToBased( const TCHAR *pszSourcePath, const TCHAR *pszBasePath, const TCHAR *pszAlias, TCHAR *pszBuffer, uint uicchBufferLen );



// ������������� ������������ ������� � ������ ��� �����
// pszSourcePath  - �������� ��� �����
// pszBasePath    - ������� ����
// pszAlias       - ������� ��� ������ ����
// pszBuffer      - �������� �����
// uicchBufferLen - ������ ������
// ������ :
// pszSourcePath  - "<allprojects>\firstproject\shelf.cdw"
// pszBasePath    - "�:\myfiles\myprojects"
// pszAlias       - "allprojects"
// pszBuffer      - "�:\myfiles\myprojects\firstproject\shelf.cdw"
IOS_ERROR_CODE IOSBasedPathToFull( const TCHAR *pszSourcePath, const TCHAR *pszBasePath, const TCHAR *pszAlias, TCHAR *pszBuffer, uint uicchBufferLen );


// ������ ���� �� �������� ����� ������
// pszFileName    - ��� �����
// szBuffer       - ����� ��� �������� ���
// uicchBufferLen - ������ ������
// pszFindPattern - ������ ����� ������

// ����� ������
// 1 - ������� ������� ������
// 2 - ������� �������
// 3 - ������� Windows
// 4 - ������� Windows\System ��� WindowsNT/System32
// 5 - ������� WindowsNT\System16
// 6 - �������� Path 

IOS_ERROR_CODE IOSFindFile( const TCHAR *pszFileName, TCHAR *szBuffer, uint uicchBufferLen, const TCHAR *pszFindPattern = _T("21346"));

// ������������� ��� ����� � ������������ ���
// pszFileName    - ��� �����
// szBuffer       - ����� ��� �������� ���
// uicchBufferLen - ������ ������
IOS_ERROR_CODE IOSGetFileTitle( const TCHAR *pszFileName, TCHAR *szBuffer, uint uicchBufferLen );

// ��������� ����������� ��������/������ � ���� � �������� ������
// pszFileName    - ��� �����
IOS_ERROR_CODE IOSCheckCreatableFile( const TCHAR *pszFileName );

// ��������� ��� ����������
UINT IOSGetDriveType( const TCHAR *pszDriveName );
UINT IOSGetDriveTypeW( const WCHAR *pszDriveName );

// ��������� �������� �����
DWORD IOSGetFileAttributes( const TCHAR *pszFileName );
DWORD IOSGetFileAttributesW( const WCHAR *pszFileName );

IOS_ERROR_CODE IOSGetFileAttributesEx( const TCHAR *pszFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation );
IOS_ERROR_CODE IOSGetFileAttributesExW( const WCHAR *pszFileName, GET_FILEEX_INFO_LEVELS fInfoLevelId, LPVOID lpFileInformation );


// ���������� �������� �����
BOOL IOSSetFileAttributes( const TCHAR *pszFileName, DWORD dwFileAttributes );
BOOL IOSSetFileAttributesW( const WCHAR *pszFileName, DWORD dwFileAttributes );

// �������� �������� ��� ����� 
DWORD IOSGetShortPathName( const TCHAR *lpszLongPath, TCHAR *lpszShortPath, DWORD cchBuffer );
DWORD IOSGetShortPathNameW( const WCHAR *lpszLongPath, WCHAR *lpszShortPath, DWORD cchBuffer );

// �������� ������� ��������� ������ 
DWORD IOSGetTempPath( DWORD cchBuffer, TCHAR *pchBuffer );
DWORD IOSGetTempPathW( DWORD cchBuffer, WCHAR *pchBuffer );

// �������� ���� �� ��������� ����
UINT IOSGetTempFileName( const TCHAR *lpPathName, const TCHAR *lpPrefixString, UINT uUnique, TCHAR *lpTempFileName );
UINT IOSGetTempFileNameW( const WCHAR *lpPathName, const WCHAR *lpPrefixString, UINT uUnique, WCHAR *lpTempFileName );

// �������� ���������� �� ����������
//  LPCTSTR lpRootPathName,           // root directory
//  LPTSTR	lpVolumeNameBuffer,        // volume name buffer
//  DWORD		nVolumeNameSize,            // length of name buffer
//  LPDWORD lpVolumeSerialNumber,     // volume serial number
//  LPDWORD lpMaximumComponentLength, // maximum file name length
//  LPDWORD lpFileSystemFlags,        // file system options
//  LPTSTR	lpFileSystemNameBuffer,    // file system name buffer
//  DWORD		nFileSystemNameSize         // length of file system name buffer
BOOL IOSGetVolumeInformation( LPCTSTR lpRootPathName, LPTSTR lpVolumeNameBuffer, DWORD nVolumeNameSize, LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength, LPDWORD lpFileSystemFlags, LPTSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize );
BOOL IOSGetVolumeInformationW( LPCWSTR lpRootPathName, LPWSTR lpVolumeNameBuffer, DWORD nVolumeNameSize, LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength, LPDWORD lpFileSystemFlags, LPWSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize );


// ����������/������� ���� �� ������������
// pszSrcName - source file full name
// pszDestName - destignation file fule name (might be NUL - means file should be deleted on reboot)
IOS_ERROR_CODE IOSMoveFileOnReboot( LPCTSTR pszSrcName, LPCTSTR pszDestName );
IOS_ERROR_CODE IOSMoveFileOnRebootW( LPCWSTR pszSrcName, LPCWSTR pszDestName );
IOS_ERROR_CODE IOSMoveFileOnReboot9x( LPCTSTR pszSrcName, LPCTSTR pszDestName );


// ��������� - �� �������� �� ���������� subst-drive
IOS_ERROR_CODE IOSIsSubstDrive( TCHAR caDrive );
IOS_ERROR_CODE IOSIsSubstDriveW( WCHAR cDrive );

// �������� ��� DOS Device
// lpDeviceName - MS-DOS device name string
// lpTargetPath - query results buffer
// ucchMax      - maximum size of buffer
DWORD IOSQueryDosDevice( LPCTSTR lpDeviceName, LPTSTR lpTargetPath, DWORD ucchMax );
DWORD IOSQueryDosDeviceW( LPCWSTR lpDeviceName, LPWSTR lpTargetPath, DWORD ucchMax );

// �������� ������ ��������� � �������
// nBufferLength  - size of buffer
// lpBuffer       - drive strings buffer
DWORD IOSGetLogicalDriveStrings( DWORD nBufferLength,  LPTSTR lpBuffer );
DWORD IOSGetLogicalDriveStringsW( DWORD nBufferLength,  LPWSTR lpBuffer );


#endif 
