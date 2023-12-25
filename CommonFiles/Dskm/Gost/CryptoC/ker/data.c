#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*����������������������������������������������������VARIABLES�FOR�GOST�28147*/
struct COM_State PERMDefault =
       {
/* ���ᨢ �� 8 ����⠭���� ������⢠ {0,...,15} �ਯ��奬� ���� 28147-89     */
       {0X1,0XF,0XD,0X0,0X5,0X7,0XA,0X4,0X9,0X2,0X3,0XE,0X6,0XB,0X8,0XC,
        0XD,0XB,0X4,0X1,0X3,0XF,0X5,0X9,0X0,0XA,0XE,0X7,0X6,0X8,0X2,0XC,
        0X4,0XB,0XA,0X0,0X7,0X2,0X1,0XD,0X3,0X6,0X8,0X5,0X9,0XC,0XF,0XE,
        0X6,0XC,0X7,0X1,0X5,0XF,0XD,0X8,0X4,0XA,0X9,0XE,0X0,0X3,0XB,0X2,
        0X7,0XD,0XA,0X1,0X0,0X8,0X9,0XF,0XE,0X4,0X6,0XC,0XB,0X2,0X5,0X3,
        0X5,0X8,0X1,0XD,0XA,0X3,0X4,0X2,0XE,0XF,0XC,0X7,0X6,0X0,0X9,0XB,
        0XE,0XB,0X4,0XC,0X6,0XD,0XF,0XA,0X2,0X3,0X8,0X1,0X0,0X7,0X5,0X9,
        0X4,0XA,0X9,0X2,0XD,0X8,0X0,0XE,0X6,0XB,0X1,0XC,0X7,0XF,0X5,0X3},
/* ���ᨢ �� 4 (��६��������) ����⠭���� ������⢠ {0,...,255} � ᤢ�����  */
/* ��ࠧ�� �� ������ ���� �ம�ࠧ� ����� �������� ᫮��.                  */
       {0,0}
       };
/*���������������������������������������������������VARIABLES�FOR�GOST�28147 */
/*���������������������������������������������������������������DATA�FOR�SIGN*/
struct RND_State RandomDefault={0};               /* ����ﭨ� ��� -          */
                                                  /* - ��� ���������� ����� � */
						  /* 㬮��⥫��� ���⥪��� */
						  /* ����権.                */

struct LR34_10_2001 _LC3410_Default0256 =
       {
//     DWORD  Mark             ;  		  /* Context Marker.          */
       0x9ABCDEF7,
//      WORD  SecretKey[CuNQ*2];                  /* ����. ���. ���� ������.*/
       {
       0x00000000,0x00000000,0x00000000,0x00000000,
       0x00000000,0x00000000,0x00000000,0x00000000,
       0x00000000,0x00000000,0x00000000,0x00000000,
       0x00000000,0x00000000,0x00000000,0x00000000
       },
//struct Point  PublicKey      ;                  /* ���.       ���� ������.*/
       {
       0x00000000,0x00000000,0x00000000,0x00000000,
       0x00000000,0x00000000,0x00000000,0x00000000,
       0x00000000,0x00000000,0x00000000,0x00000000,
       0x00000000,0x00000000,0x00000000,0x00000000,
       0x00000000,0x00000000,0x00000000,0x00000000,
       0x00000000,0x00000000,0x00000000,0x00000000,
       0x00000000
       },
//      WORD  a_       [CuNP  ];                  /* ��ࠬ��� a �ਢ��. (HBO) */
       {
       0x7FFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
       0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFC983
       },
//      WORD  b_       [CuNP  ];                  /* ��ࠬ��� b �ਢ��. (HBO) */
       {
       0x58DF983A,0x171CD5AE,0x20391ABE,0x272C66AD,
       0x004469B4,0x541A2542,0x807BBFA3,0x23A3952A
       },
//      WORD  P_       [CuNP+2];                  /* ���⮥      P.    (HBO) */
       {
       0x80000000,0x00000000,0x00000000,0x00000000,
       0x00000000,0x00000000,0x00000000,0x00000431,
       0x883B2B2F
       },
//      WORD  PG_      [CuNP  ];                  /* 2^(2nP)(mod P).    (HBO) */
       {
       0x00000000,0x00000000,0x00000000,0x00000000,
       0x00000000,0x00000000,0x00000000,0x00464584
       },
//      WORD  Q_       [CuNQ+2];                  /* ���⮥      Q.    (HBO) */
       {
       0x80000000,0x00000000,0x00000000,0x00000001,
       0x50FE8A18,0x92976154,0xC59CFC19,0x3ACCF5B3,
       0x34713E85
       },
//      WORD  QG_      [CuNQ  ];                  /* 2^(2nQ)(mod Q).    (HBO) */
       {
       0x6E749E5B,0x503B112A,0xC0DB8B05,0xC83AD16A,
       0x4AF1F8AC,0x73C6C555,0xECAED446,0x77F7F28D
       },
//      WORD  QP_      [CuNP+2];                  /* ���⮥ Q ����� CuNP.    */
       {
       0x80000000,0x00000000,0x00000000,0x00000001,
       0x50FE8A18,0x92976154,0xC59CFC19,0x3ACCF5B3,
       0x34713E85
       },
//      WORD  OQ_      [CuNQ  ];                  /* [1]Q ����� CuNQ.   (HBO) */
       {
       0x7FFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFE,
       0xAF0175E7,0x6D689EAB,0x3A6303E6,0xC5330A4D
       },
//      WORD  OP_      [CuNP  ];                  /* [1]P ����� CuNP.   (HBO) */
       {
       0x7FFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
       0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFBCF
       },
//      WORD  OQP_     [CuNP  ];                  /* [1]Q ����� CuNP.   (HBO) */
       {
       0x7FFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFE,
       0xAF0175E7,0x6D689EAB,0x3A6303E6,0xC5330A4D
       },
//struct Point  A_             ;                  /* ��窠 A �ਢ��.    (HBO) */
       {
       0x00000000,0x00000000,0x00000000,0x00000000,
       0x00000000,0x00000000,0x00000000,0x00000200,
       0xE208A0A8,0x51E6D447,0x63BD0316,0x160E9CD1,
       0xC9850A7F,0xA29C1267,0x962BBCAB,0x7EEAC88F,
       0x00000000,0x00000000,0x00000000,0x00000000,
       0x00000000,0x00000000,0x00000000,0x00000100,
       0x00000000
       },
//struct Point  AP_            ;                  /* �ਢ��񭭠� [A_]P. (HBO) */
       {
       0x7FFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
       0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFF36D,
       0x03F66B35,0x4AA3DAA4,0x67617A63,0xE4B6DDE6,
       0x7CE5090A,0xF69BF9AE,0x9AF45A5A,0x471125F5,
       0x7FFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
       0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFBCF,
       0x00000081
       },
//      WORD  Half     [CuNP  ];                  /* [1/2]P.            (HBO) */
       {
       0x80000000,0x00000000,0x00000000,0x00000000,
       0x00000000,0x00000000,0x00000000,0x00000000
       },
//       int  P_Size           ;                  /* ����� ���⮣� P (����). */
       0x00000020,
//       int  Q_Size           ;                  /* ����� ���⮣� Q (����). */
       0x00000020,
//       int  IsReady          ;                  /* ����� ���樠����樨.     */
       0x0001,
//     struct RND_State *RS  ;                    /* ����ﭨ� ���.           */
       &RandomDefault
       };

DWORD LO_[LNP]=
      {
      0     ,0     ,0     ,0     ,0     ,0     ,0     ,0     , /* 1. */
      0     ,0     ,0     ,0     ,0     ,0     ,0     ,0     ,
      0     ,0     ,0     ,0     ,0     ,0     ,0     ,0     ,
      0     ,0     ,0     ,0     ,0     ,0     ,0     ,0     ,
      0     ,0     ,0     ,0     ,0     ,0     ,0     ,0     ,
      0     ,0     ,0     ,0     ,0     ,0     ,0     ,0     ,
      0     ,0     ,0     ,0     ,0     ,0     ,0     ,0     ,
      0     ,0     ,0     ,0     ,0     ,0     ,0     ,1
      };

/*���������������������������������������������������������������DATA�FOR�SIGN*/
/*�������������������������������������������������������������������������EOF*/
