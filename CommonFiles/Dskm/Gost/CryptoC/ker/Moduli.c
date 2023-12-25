#include <stdio.h>
#include "CrC_User.h"

#define P_      (Context->P_)
#define Q_      (Context->Q_)
#define PG_     (Context->PG_)
#define QP_     (Context->QP_)
#define OQ_     (Context->OQ_)
#define OQP_    (Context->OQP_)
#define P_Bytes (Context->P_Size)
#define P_Words (P_Bytes/4)
#define Q_Bytes (Context->Q_Size)
#define Q_Words (Q_Bytes/4)
/*���������������������������������������������������������������������DEFINES*/
/*������������������������������������������������������������������CUMODULOPQ*/
void CrypC_LCuModuloPQ(DWORD *Dividend, struct LR34_10_2001 *Context)
/* �ਢ������ �� ����� Q �᫠ P-����� (Curve-���⥪��).                     */
{
if(CrypC_Lcmp_LC(P_Words,Dividend,QP_) < 0)      // if Dividend < Q
  return;

CrypC_LmultC(Dividend, OQP_, QP_, P_Words);      /* *[1]Q ࠧ��� P. */
while(CrypC_Lcmp_LC(Q_Words                 ,
                    Dividend+P_Words-Q_Words,
                    Q_)           >= 0)          // While Rest >= q :
      CrypC_Lsub_LC(Q_Words                 ,
                    Dividend+P_Words-Q_Words,
	            Q_                      );   // Rest -= q.
}
/*������������������������������������������������������������������CUMODULOPQ*/
/*������������������������������������������������������������������CUMODULOQQ*/
void CrypC_LCuModuloQQ(DWORD *Dividend, struct LR34_10_2001 *Context)
/* �ਢ������ �� ����� Q �᫠ Q-����� (Curve-���⥪��).                     */
{
if(CrypC_Lcmp_LC(Q_Words,Dividend,Q_) < 0)       // if Dividend < Module
  return;

CrypC_LmultC(Dividend, OQ_, Q_, Q_Words);        /* *[1]Q ࠧ��� Q. */
while(CrypC_Lcmp_LC(Q_Words,Dividend,Q_) >= 0)   // While Rest >= q :
      CrypC_Lsub_LC(Q_Words,Dividend,Q_);        // Rest -= q.
}
/*������������������������������������������������������������������CUMODULOQQ*/
/*�������������������������������������������������������������������������EOF*/
