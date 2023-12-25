#include <stdio.h>
#include "CrC_User.h"

DWORD CrypC_LEPSCount(DWORD C);

/*���������������������������������������������������������������������DEFINES*/
/*�������������������������������������������������������R34_10_2001_set_parms*/
int CrypC_LR34_10_2001_set_parms(struct   LR34_10_2001 *Context,
                                 struct   RND_State  *State,
                                 void   *_R34_10_2001_P, int P_Size,
                                 void   *_R34_10_2001_Q, int Q_Size,
                                 void   *_R34_10_2001_a,
                                 void   *_R34_10_2001_b,
                          struct LPoint * R34_10_2001_A
                                )
/*����������������������������������������������������������������������������*/
/*                 ��⠭���� ��ࠬ��஢ ��஢�� ������                      */
/*             � ���⥪�� ��ࠡ�⪨/�஢�ન ��஢�� ������                 */
/*                     ("���樠������" ���⥪��)                            */
/*                            ���� �3410-2001                                 */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* - �����⥫� �� ���� ����� P_Size   ���⮣� ���浪� P: *GOST_C3411_P.     */
/* - �����⥫� �� ���� ����� Q_Size   ���⮣� ���浪� Q: *R34_10_2001_Q.    */
/* - �����⥫� �� ���� ����� *P_Size  ��ࠬ��� a �ਢ��: *R34_10_2001_a.    */
/* - �����⥫� �� ���� ����� *P_Size  ��ࠬ��� b �ਢ��: *R34_10_2001_b.    */
/* - �����⥫� �� ���� ��������          �窨 A �ਢ��: *R34_10_2001_A.    */
/*   �᫨ �����-���� 㪠��⥫� ࠢ�� 0, � ������� ��ࠬ���� �� 㬮�砭��    */
/*   ��� ����� P_Size � ���⠢����� 䫠� ��⮢���� ���⥪��. ��⠫��     */
/*   ��ࠬ���� �����������.                                                  */
/* ��室:                                                                     */
/* - ���⥪��, ��⮢� � ��⠭���� ᥪ�⭮�� �/��� ����⮣� ���� ������.  */
/* ���� ������:                                                             */
/* - RET_OK                - ��ଠ�쭮� �����襭��.                           */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_CONTEXTNOTCLEAR   - ���⥪�� ���樠����஢�� ࠭��.                  */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
#define R34_10_2001_P ((DWORD *)_R34_10_2001_P)
#define R34_10_2001_Q ((DWORD *)_R34_10_2001_Q)
#define R34_10_2001_a ((DWORD *)_R34_10_2001_a)
#define R34_10_2001_b ((DWORD *)_R34_10_2001_b)
#define P_      (Context->P_)
#define Q_      (Context->Q_)
#define A_      (Context->A_)
#define AP_     (Context->AP_)
#define a_      (Context->a_)
#define b_      (Context->b_)
#define QP_     (Context->QP_)
#define OP_     (Context->OP_)
#define OQ_     (Context->OQ_)
#define OQP_    (Context->OQP_)
#define PG_     (Context->PG_)
#define QG_     (Context->QG_)
#define Half    (Context->Half)
#define P_Bytes (Context->P_Size)
#define P_Words (Context->P_Size/4)
#define Q_Bytes (Context->Q_Size)
#define Q_Words (Context->Q_Size/4)
         int  Ret;
       DWORD  w[LCuNP];
      extern  struct COM_State PERMDefault;

/* �맮� ��楤��� �ନ஢����  ������஢������ ���ᨢ� ����⠭����       */
/* ��� �ਯ��奬� ���� 28147-89:                                             */
CrypC__InitGost( (BYTE *)PERMDefault.Perms, PERMDefault.K_ );

if(!Context || !State)
  Ret = RET_INVALIDPARAMETER;
else
if(Q_Size != 32)
  Ret = RET_INCORRECTSIZE;
else
if((Context->Mark     & GOST_XXXXX_Marker_Mask ==
    R34_10_2001_Marker & GOST_XXXXX_Marker_Mask   ) &&
   (Context->Mark                                  !=
    R34_10_2001_Marker                            )   )
  Ret = RET_INCORRECTCONTEXT;
else if(Context->IsReady & R34_10_2001_CONTEXT)
  Ret = RET_CONTEXTNOTCLEAR;
else
  {
  if(Context->Mark != R34_10_2001_Marker)
    CrypC_LR34_10_2001_clear(Context);

  Context->RS = State;                        /* �����⥫� �� ���⥪�� ���.   */

  if(R34_10_2001_P && R34_10_2001_Q && R34_10_2001_a && R34_10_2001_b && R34_10_2001_A)
    {
                                              /* ���⮥ P.                   */
                                 P_Bytes =
                                 P_Size;
    memcpy     (P_,R34_10_2001_P,P_Bytes );
    CrypC_NetToHost(P_,         (P_Words));
                                              /* ���⮥ Q.                   */
                                 Q_Bytes =
                                 Q_Size;
    memcpy       (Q_,R34_10_2001_Q,Q_Bytes );
    CrypC_NetToHost(Q_,         (Q_Words));
                                              /* Eps(P).                      */
        *((DWORD *)(P_+P_Words)) =
    CrypC_LEPSCount(P_[P_Words-1]);
                                              /* Eps(Q).                      */
        *((DWORD *)(Q_+Q_Words)) =
    CrypC_LEPSCount(Q_[Q_Words-1]);
                                              /* ��ࠬ��� a �ਢ��.           */
    memcpy     (a_,R34_10_2001_a,P_Bytes );
    CrypC_NetToHost(a_,         (P_Words));
                                              /* ��ࠬ��� b �ਢ��.           */
    memcpy     (b_,R34_10_2001_b,P_Bytes );
    CrypC_NetToHost(b_,         (P_Words));

    memset(PG_,0,P_Bytes); PG_[P_Words-1] = 1;	  /* 1 ��� PG.          (HBO) */
    CrypC_LroundC(PG_,PG_,P_,P_Words);		  /* 1*2^n(mod P).            */
    CrypC_LroundC(PG_,PG_,P_,P_Words);		  /* 1*2^(2n)(mod P).         */
    memset(QG_,0,Q_Bytes); QG_[Q_Words-1] = 1;	  /* 1 ��� QG.          (HBO) */
    CrypC_LroundC(QG_,QG_,Q_,Q_Words);		  /* 1*2^n(mod P).            */
    CrypC_LroundC(QG_,QG_,Q_,Q_Words);		  /* 1*2^(2n)(mod P).         */
    
    CrypC_LmultC(a_, PG_, P_, P_Words);		  /* a � M-Domain.            */
    CrypC_LmultC(b_, PG_, P_, P_Words);		  /* b � M-Domain.            */
                                              /* ��窠 A �ਢ��.              */
    memcpy    (&A_,R34_10_2001_A, LPTSIZE );
                                              /* ��窠 A �ਢ��: Proj & Mont. */
    memcpy   (&AP_,R34_10_2001_A, LPTSIZE );
    CrypC_NetToHost(AP_.X,      (P_Words));
    CrypC_NetToHost(AP_.Y,      (P_Words));
    CrypC_NetToHost(AP_.Z,      (P_Words));
/* To***() �ᯮ����� � ���⥪�� ⮫쪮 PG_, P_ � P_Size:                    */
    CrypC_LAffiToProj (Context, &AP_);
    CrypC_LIntToMont  (Context, &AP_);

    memset(QP_,0,P_Bytes-Q_Bytes);	 	  /* ���⮥ QP + Eps(Q).     */
    memcpy(QP_+P_Words-Q_Words,Q_,Q_Bytes+4);
    memset(w,0,P_Bytes); w[P_Words-1]=1;
    CrypC_LroundC(OP_ ,w,P_ ,P_Words);            /* �ਢ������� [1]P.      */
    CrypC_LroundC(OQ_ ,w+P_Words-Q_Words,
                         Q_ ,Q_Words);            /* �ਢ������� [1]Q.      */
    CrypC_LroundC(OQP_,w,QP_,P_Words);            /* �ਢ������� [1]QP.     */

    memset(Half,0,P_Bytes);
    Half[P_Words-1] = 2;			  /*    2.                    */
    memcpy(w,P_,P_Size);                          /* Q.                       */
    CrypC_Lsub_LC(P_Words,w,Half);                /* Q-2.                     */
    CrypC_LmultC(Half,PG_,P_,P_Words);		  /*   [2]P.                  */
    CrypC_LpowerC  ((DWORD *)Half   ,
                    (DWORD *)w      ,
                    (DWORD *)Half   ,
                             0      ,
                    (DWORD *)P_     ,
                             P_Words);             /* Half  = (2**(-1)) mod P */
    }
  else                                    /* ���⥪�� �� 㬮�砭��:           */
    {
    if(Q_Size == 32)memcpy(Context,&_LC3410_Default0256,sizeof(struct LR34_10_2001));
    }

  Context->IsReady |= R34_10_2001_CONTEXT;
  Ret = RET_OK;
  }
return(Ret);
}
/*�������������������������������������������������������R34_10_2001_set_parms*/
/*�������������������������������������������������������������������������EOF*/
