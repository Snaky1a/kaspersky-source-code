#ifndef _SIGN_STRUCTURES_H__
#define _SIGN_STRUCTURES_H__

/*
      �������� ������� "�����" �������

      ������� ����������� � ����� ����� �������� ���������� ��������� :
      
      1. ����������� SIGN_HEADER_SIGNATURE
      2. ����������� ����� ������ �����, ���� ���������.
      3. ��������� ��������������� ��������� SIGN_STRUCT ( �� ����� ���� ��������� )
      4. �������� ����� ������ �����, ���� ���������. ( �� �� �����, ��� � � �.2 )
      5. SIGN_FOOTER_SIGNATURE
*/

#define SIGN_HEADER_SIGNATURE 'oRuR'
#define SIGN_FOOTER_SIGNATURE 'RuRo'

#pragma pack ( push, 1 )


typedef struct _SIGN_HEADER {
    unsigned long  Tag;
    unsigned long  TotalSize;

} SIGN_HEADER, *PSIGN_HEADER;

typedef struct _SIGN_FOOTER {
    unsigned long  TotalSize;
    unsigned long  Tag;
} SIGN_FOOTER, *PSIGN_FOOTER;

#define ALG_UNDEFINED   0x0
#define ALG_CRYPTOC     'gcpc'  // CryPtoC Gost

typedef struct _SIGN_STRUCT {
    unsigned long AlgID;		// ID ������������� ���������
    unsigned long Size;			// ������ ���������

    char  Sign[0];		// �������
} SIGN_STRUCT, *PSIGN_STRUCT;

// ����� �������� + ������ ��������� == Size ( ��. ����������� SIGN_STRUCT ) 
typedef struct _CRYPTOC_SIGN {
    unsigned long Key1Size;    // ������� � ������ ����� Key1
    unsigned long Key2Size;    // ����� � ������ ����� Key2
    unsigned long RegSize;     // ����� � ������ ����� ������.

    char  Buffer[0];   // ������, � ������� ��������������� ����� ��� ����� � ������.
} CRYPTOC_SIGN, *PCRYPTOC_SIGN;

#pragma pack ( pop )

#endif