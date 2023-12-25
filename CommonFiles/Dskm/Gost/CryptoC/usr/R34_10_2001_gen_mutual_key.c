#include <stdio.h>
#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*��������������������������������������������������R34_10_2001_gen_mutual_key*/
int CrypC_LR34_10_2001_gen_mutual_key(struct LR34_10_2001 *Context,
                                       struct LPoint *PublicKey,
				       struct LPoint *MutualKey)
/*����������������������������������������������������������������������������*/
/*               ���᫥��� ᮢ���⭮�� ���� ���� ������⮢                  */
/*      � �ᯮ�짮������ ᪠��୮�� 㬭������ �� �����᪮� �ਢ��,        */
/*            ���ᠭ��� � ���⥪�� ��ࠡ�⪨ ��஢�� ������                */
/*                            ���� �3410-2001                                 */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* - �����⥫� �� ���� ����⮣� ���� PublicKey 㤠�񭭮�� �������.        */
/* - �����⥫� �� ���� ᮢ���⭮�� ���� MutualKey.                          */
/* ��室:                                                                     */
/* - �������� ���� � ஫� MutualKey.                                        */
/* ���� ������:                                                             */
/* - RET_OK                - ��ଠ�쭮� �����襭��.                           */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_CONTEXTNOREADY    - �� ���樠����஢��� ��ࠬ���� ������.           */
/* - RET_KEYNOTPRESENT     - �� ��⠭����� ᥪ��� ����.                    */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
#define P_      (Context->P_)
#define SK_     (Context->SecretKey)
#define P_Bytes (Context->P_Size)
#define P_Words (Context->P_Size/4)
#define Q_Bytes (Context->Q_Size)
#define Q_Words (Context->Q_Size/4)
{
         int  i,Ret;
struct LPoint PK;

     if(! Context)
  Ret = RET_INVALIDPARAMETER;
else
if((Context->Mark      & GOST_XXXXX_Marker_Mask ==
    R34_10_2001_Marker & GOST_XXXXX_Marker_Mask   ) &&
   (Context->Mark                                  !=
    R34_10_2001_Marker                            )   )
  Ret = RET_INCORRECTCONTEXT;
else if(!(Context->IsReady & R34_10_2001_CONTEXT))
  Ret = RET_CONTEXTNOTREADY;
else if(!(Context->IsReady & R34_10_2001_SECRETKEY))
  Ret = RET_KEYNOTPRESENT;
else  
  {
  /* �����᪨஢���� ᥪ�⭮�� ����.*/
  for(i=0;i<Q_Words;i++)
     ((DWORD *)SK_)[i        ] +=
     ((DWORD *)SK_)[i+Q_Words]  ;

  memcpy(&PK,PublicKey,LPTSIZE  );            /* ������ ���� ������.       */
  CrypC_NetToHost(PK.X,P_Words);              /* Net to Host Byteorder.       */
  CrypC_NetToHost(PK.Y,P_Words);              /* Net to Host Byteorder.       */
  CrypC_LAffiToProj(Context, &PK);
  CrypC_LIntToMont (Context, &PK);

  /* ���᫥��� ᮢ���⭮�� ����. */
  CrypC_LCuPower(&PK, SK_, MutualKey, Context);             /* MK_ = (PK)*SK_ */

  /* ��᪨஢���� ����. */
  CrypC_Mask_SecretKey_(Context->RS, SK_);

  CrypC_LProjToAffi(Context, MutualKey);
  CrypC_LMontToInt (Context, MutualKey);
                                              /* Host to Net Byteorder.       */
  CrypC_HostToNet(MutualKey->X, P_Words);
  CrypC_HostToNet(MutualKey->Y, P_Words);
    
  Ret = RET_OK;
  }
return(Ret);
}
/*��������������������������������������������������R34_10_2001_gen_mutual_key*/
/*�������������������������������������������������������������������������EOF*/
