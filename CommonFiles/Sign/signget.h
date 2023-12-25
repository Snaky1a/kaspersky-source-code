#ifndef _SIGNGET_H_
#define _SIGNGET_H_

#include <ctype.h>
#include "sign.h"

#define DEF_SIGN_BUFFER 58
typedef unsigned char TSignBuffer[DEF_SIGN_BUFFER + 1];

// 1. ��������� ������� � szFileName ����������� ������ sign_check_file
// 2. � ������ ������ 1. ���������� ������� vSign �� ����� szFileName
// ������������ ��������
//     SIGN_OK - �������� ����������
//     SIGN_BAD_FILE - ������ 
int SIGNAPI sign_get_file( const char* szFileName, 
                           TSignBuffer& vSign );

// 1. ��������� ������� � wszFileName ����������� ������ sign_check_fileW
// 2. � ������ ������ 1. ���������� ������� vSign �� ����� wszFileName
// ������������ ��������
//     SIGN_OK - �������� ����������
//     SIGN_BAD_FILE - ������ 
int SIGNAPI sign_get_file( const wchar_t* wszFileName, 
                           TSignBuffer& vSign );

#endif