#include "CrC_User.h"
#include <stdio.h>

#define P_      (Context->P_)
#define PG_     (Context->PG_)
#define P_Bytes (Context->P_Size)
#define P_Words (P_Bytes/4)
/*���������������������������������������������������������������������DEFINES*/
/*����������������������������������������������������������������TOPROJECTIVE*/
CrypC_LAffiToProj(struct LR34_10_2001 *Context, struct LPoint *B)
/* �८�ࠧ������ �窨 �ਢ�� �  ��䨭��� �ଥ � �஥�⨢�� ���न����.    */
/* ��窠 B - �� ���न���� �� mod P:                                         */
/*         �� �室�  - (Xv,Yv,Undefined),                                     */
/*         �� ��室� - (Xp,Yp,Zp) = (Xv,Yv,1).                                */
{
memset(B->Z,0,P_Bytes);                         /* ���न���  Z = 0.         */
B->Z[P_Words-1] = 1;                            /* ���न���  Z = 1.         */
if(B->Type & MONT)                              /* �뫮 � M-Domain?           */
  {
  CrypC_LmultC(B->Z, PG_, P_, P_Words);         /* [B->Z]P.                   */
  B->Type = Proj ^ MONT;
  }
else
  B->Type = Proj;
return(0);
}
/*����������������������������������������������������������������TOPROJECTIVE*/
/*���������������������IEEE�P1363�VERSION�����������������������FROMPROJECTIVE*/
CrypC_LProjToAffi(struct LR34_10_2001 *Context, struct LPoint *B)
/* �८�ࠧ������ �窨 �ਢ�� � ��䨭��� ��� �� �஥�⨢��� ���न���.     */
/* ��窠 B - �� ���न���� �� mod P:                                         */
/*         �� �室�  - (Xp,Yp,Zp),                                            */
/*         �� ��室� - (Xv,Yv,Zv=Undefined),                                  */
/*                     (Xv,Yv) = (Xp/(Zp^2),Yp/(Zp^3)),                       */
/* ���� Zv �� ����, � �� ������� 1/Zp.                                    */
{
DWORD A[LCuNP],D[LCuNP];

memcpy(A,P_,P_Bytes);                             /* A = P.                   */
memset(D,0,P_Bytes);
D[P_Words-1] = 2;                                 /* 2.                       */
CrypC_Lsub_LC(P_Words,A,D);                       /* A = P-2.                 */

if(B->Type & MONT)                                /* �뫮 � M-Domain?         */
  {
  CrypC_LpowerC(B->Z, A, B->Z, 0, P_, P_Words);   /*      [ 1/Zp  ]P.         */
  memcpy(A,B->Z,P_Bytes);
  CrypC_Lpower2C(A   ,       P_, P_Words);        /*      [ 1/Zp^2]P.         */
  CrypC_LmultC  (B->X, A   , P_, P_Words);        /* Xv = [Xp/Zp^2]P.         */
  CrypC_LmultC  (B->Y, A   , P_, P_Words);        /* Yv = [Yp/Zp^2]P.         */
  CrypC_LmultC  (B->Y, B->Z, P_, P_Words);        /* Yv = [Yp/Zp^3]P.         */
  B->Type = Affi ^ MONT;
  }
else
  {
  CrypC_LIntToMont  (Context,B);
  CrypC_LpowerC(B->Z, A, B->Z, 0, P_, P_Words);   /*      [ 1/Zp  ]P.         */
  memcpy(A,B->Z,P_Bytes);
  CrypC_Lpower2C(A   ,       P_, P_Words);        /*      [ 1/Zp^2]P.         */
  CrypC_LmultC  (B->X, A   , P_, P_Words);        /* Xv = [Xp/Zp^2]P.         */
  CrypC_LmultC  (B->Y, A   , P_, P_Words);        /* Yv = [Yp/Zp^2]P.         */
  CrypC_LmultC  (B->Y, B->Z, P_, P_Words);        /* Yv = [Yp/Zp^3]P.         */
  CrypC_LMontToInt(Context,B);
  B->Type = Affi;
  }
return(0);
}
/*���������������������IEEE�P1363�VERSION�����������������������FROMPROJECTIVE*/
/*����������������������������������������������������������������TOMONTGOMERY*/
CrypC_LIntToMont(struct LR34_10_2001 *Context, struct LPoint *B)
/* �⮡ࠦ���� ���न��� �窨 �ਢ�� � Montgomery Domain.                    */
{
CrypC_LmultC(B->X, PG_, P_, P_Words);             /* [B->X]P. */
CrypC_LmultC(B->Y, PG_, P_, P_Words);             /* [B->Y]P. */
CrypC_LmultC(B->Z, PG_, P_, P_Words);             /* [B->Z]P. */
B->Type |= MONT;
}
/*����������������������������������������������������������������TOMONTGOMERY*/
/*��������������������������������������������������������������FROMMONTGOMERY*/
CrypC_LMontToInt(struct LR34_10_2001 *Context, struct LPoint *B)
/* �⮡ࠦ���� ���न��� �窨 �ਢ�� �� Montgomery Domain � Z.               */
{
DWORD w[LCuNP];

memset(w,0,P_Bytes);                            /* ����� ������.  */
w[P_Words-1] = 1;
CrypC_LmultC(B->X, w, P_, P_Words);             /* [B->X] - � Z/P. */
CrypC_LmultC(B->Y, w, P_, P_Words);             /* [B->Y] - � Z/P. */
CrypC_LmultC(B->Z, w, P_, P_Words);             /* [B->Z] - � Z/P. */
B->Type &= ~MONT;
}
/*��������������������������������������������������������������FROMMONTGOMERY*/
/*�������������������������������������������������������������������������EOF*/
