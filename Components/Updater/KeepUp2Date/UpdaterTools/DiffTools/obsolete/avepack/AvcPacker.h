#ifndef _AVC_PACKER_H_
#define _AVC_PACKER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define ERR_SUCCESS         0
#define ERR_INVALID_PARAMS  1
#define ERR_BAD_FORMAT      2
#define ERR_OUTOFMEMORY     3
#define ERR_FILE_IO_ERROR   4
#define ERR_FILE_CORRUPTED  5
#define ERR_AVP_BLOCKHEADER_CORRUPTED  20
#define ERR_GENERAL_ERROR   100

/*
������� UnpackAvc ������������� avc-���� � �������� ������ ave2
������������ ���������:
    pszAvcFileName - ������ ���� � avc-����� ����������� ����������.
    ppAveBuffer -   �����, �� �������� ����� ��������� ��������� �� �����,
                    ���������� ������������� ������.
                    ����� ���������� ������ ������ ������� � ����� �������������
                    ��� ���������� ���������� � ������� FreeBuffer.
    pdwAveBufferSize - �����, �� �������� ����� ��������� ������ ������,
                       ����������� ������������� ������.
������������ ��������:
    � ������ ������ - 0.
    � ������ ������ - ��� ������
        1 - invalid parameters
        2 - not avc file
        3 - out of memory
        4 - file i/o error
        5 - file corrupted
        20 - ���������� �������� LINK16, ������� �����. � ������ ������� �� ��������!!!
*/
int UnpackAvc(const char * pszAvcFileName, void ** ppAveBuffer, unsigned long * pdwAveBufferSize);

/*
������� PackInAvc ����������� ������ � �������� ������� ave2(only!!!) � ������ avc.
������������ ���������:
    pAveBuffer - ��������� �� �����, ���������� ������������� ������.
    dwAveBufferSize - ������ ������, ����������� ������������� ������.
    pszAvcFileName - ������ ���� � �����, � ������� ������� ��������
                     ����������� ������.
������������ ��������:
    � ������ ������ - 0.
    � ������ ������ - ��� ������
        1 - invalid parameters
        2 - unknown format (not ave2)
        3 - out of memory
        4 - file i/o error
*/
int PackInAvc( void * pAveBuffer, unsigned long dwAveBufferSize, const char * pszAvcFileName );

/*
������� PackInAvc ����������� ������ � �������� ������� ave(only!!!) � ������ avc.
*/
int PackAveInAvc( void *pAveBuffer, unsigned long dwAveBufferSize, const char *pszAvcFileName );

/*
������� FreeBuffer ����������� ������, ���������� � ������� UnpackAvc.
������������ ��������:
    pBuffer - ��������� �� �����, ������� ���������� ����������.
������������ ��������:
    � ������ ������ - 0.
    � ������ ������ - ��� ������
        1 - ������� ���������
        2 - ��������� �� �����, ������� �� ��� ������� �������� UnpackAvc
*/
int FreeBuffer( void * pBuffer );

#ifdef __cplusplus
}
#endif

#endif /*AVC_PACKER_H_*/
