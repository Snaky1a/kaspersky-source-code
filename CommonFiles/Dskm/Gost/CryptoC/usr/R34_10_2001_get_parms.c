#include <stdio.h>
#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*�������������������������������������������������������R34_10_2001_get_parms*/
int CrypC_LR34_10_2001_get_parms(struct   LR34_10_2001 *Context,
                                 void   *_R34_10_2001_P, int *P_Size,
                                 void   *_R34_10_2001_Q, int *Q_Size,
                                 void   *_R34_10_2001_a,
                                 void   *_R34_10_2001_b,
                          struct LPoint *_R34_10_2001_A
                                )
/*����������������������������������������������������������������������������*/
/*                  �⥭�� ��ࠬ��஢ ��஢�� ������                        */
/*    �� ���樠����஢������ ���⥪�� ��ࠡ�⪨/�஢�ન ��஢�� ������    */
/*                            ���� �3410-2001                                 */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* - �����⥫� �� ���� ����� *P_Size  ���⮣� ���浪� P: *R34_10_2001_P.    */
/* - �����⥫� �� ���� ����� *Q_Size  ���⮣� ���浪� Q: *R34_10_2001_Q.    */
/* - �����⥫� �� ���� ����� *P_Size  ��ࠬ��� a �ਢ��: *R34_10_2001_a.    */
/* - �����⥫� �� ���� ����� *P_Size  ��ࠬ��� b �ਢ��: *R34_10_2001_b.    */
/* - �����⥫� �� ���� ��������          �窨 A �ਢ��: *R34_10_2001_A.    */
/* ��室:                                                                     */
/* - ���� R34_10_2001_P, R34_10_2001_Q, R34_10_2001_a, R34_10_2001_b,         */
/*   R34_10_2001_A ᮤ�ঠ� ��ࠬ���� P, Q, a, b � A, ᮮ⢥��⢥���.         */
/*   ���� *P_Size, *Q_Size ����������� ������� P � Q � �����.                */
/* - �᫨ R34_10_2001_P == 0, ��ࠬ��� P �� ���������.                       */
/* - �᫨ R34_10_2001_Q == 0, ��ࠬ��� Q �� ���������.                       */
/* - �᫨ R34_10_2001_a == 0, ��ࠬ��� a �� ���������.                       */
/* - �᫨ R34_10_2001_b == 0, ��ࠬ��� b �� ���������.                       */
/* - �᫨ R34_10_2001_A == 0, ��ࠬ��� A �� ���������.                       */
/* ���� ������:                                                             */
/* - RET_OK                - ��ଠ�쭮� �����襭��.                           */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_CONTEXTNOTREADY   - ���⥪�� �� ���樠����஢��.                     */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
#define R34_10_2001_P ((DWORD *)_R34_10_2001_P)
#define R34_10_2001_Q ((DWORD *)_R34_10_2001_Q)
#define R34_10_2001_a ((DWORD *)_R34_10_2001_a)
#define R34_10_2001_b ((DWORD *)_R34_10_2001_b)
#define R34_10_2001_A ((struct LPoint *)_R34_10_2001_A)
         int  Ret;

if(! Context || !P_Size || !Q_Size)
  Ret = RET_INVALIDPARAMETER;
else
if((Context->Mark      & GOST_XXXXX_Marker_Mask ==
    R34_10_2001_Marker & GOST_XXXXX_Marker_Mask   ) &&
   (Context->Mark                                  !=
    R34_10_2001_Marker                            )   )
  Ret = RET_INCORRECTCONTEXT;
else if(!(Context->IsReady & R34_10_2001_CONTEXT))
  Ret = RET_CONTEXTNOTREADY;
else
  {
                                              /* �������.                     */
  *P_Size =                                    Context->P_Size    ;
  *Q_Size =                                    Context->Q_Size    ;
                                              /* ���⮥ P.                   */
  if(R34_10_2001_P)
    {
    memcpy         (R34_10_2001_P,Context->P_, Context->P_Size   );
    CrypC_HostToNet(R34_10_2001_P,            (Context->P_Size/4));
    }
                                              /* ���⮥ Q � ࠧ���.          */
  if(R34_10_2001_Q)
    {
    memcpy         (R34_10_2001_Q,Context->Q_, Context->Q_Size   );
    CrypC_HostToNet(R34_10_2001_Q,            (Context->Q_Size/4));
    }
                                              /* ��ࠬ.  a.                   */
  if(R34_10_2001_a)
    {
    memcpy         (R34_10_2001_a,Context->a_, Context->P_Size   );
    CrypC_LmultC((DWORD *)R34_10_2001_a,      /* a *= 1.                      */
                 (DWORD *)LO_+LNP-(Context->P_Size/4),
                 (DWORD *)Context->P_                ,
                          Context->P_Size/4          );
    CrypC_HostToNet(R34_10_2001_a,            (Context->P_Size/4));
    }
                                              /* ��ࠬ.  b.                   */
  if(R34_10_2001_b)
    {
    memcpy         (R34_10_2001_b,Context->b_, Context->P_Size   );
    CrypC_LmultC((DWORD *)R34_10_2001_b,      /* a *= 1.                      */
                 (DWORD *)LO_+LNP-(Context->P_Size/4),
                 (DWORD *)Context->P_                ,
                          Context->P_Size/4          );
    CrypC_HostToNet(R34_10_2001_b,            (Context->P_Size/4));
    }
                                              /* ��窠 A.                     */
  if(_R34_10_2001_A)
    {
    memcpy         (R34_10_2001_A,&Context->A_,LPTSIZE           );
    CrypC_LProjToAffi(Context, R34_10_2001_A);
    CrypC_LMontToInt (Context, R34_10_2001_A);
    CrypC_HostToNet(R34_10_2001_A->X,         (Context->P_Size/4));
    CrypC_HostToNet(R34_10_2001_A->Y,         (Context->P_Size/4));
    }

  Ret = RET_OK;
  }
return(Ret);
}
/*�������������������������������������������������������R34_10_2001_get_parms*/
/*�������������������������������������������������������������������������EOF*/
