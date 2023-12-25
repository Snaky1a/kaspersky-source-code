#include <stdio.h>
#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*��������������������������������������������������R34_10_2001_gen_secret_key*/
int CrypC_LR34_10_2001_gen_secret_key(struct LR34_10_2001 *Context)
/*����������������������������������������������������������������������������*/
/*            ��ࠡ�⪠ � ��⠭���� ��砩���� ᥪ�⭮�� ����               */
/*                  � ���⥪�� ��ࠡ�⪨ ��஢�� ������                     */
/*                            ���� �3410-2001                                 */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* ��室:                                                                     */
/* - ���⥪��, ��⮢� � ���᫥��� ��஢�� ������.                         */
/* ���� ������:                                                             */
/* - RET_OK                - ��ଠ�쭮� �����襭��.                           */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_CONTEXTNOREADY    - �� ���樠����஢��� ��ࠬ���� ������.           */
/* - RET_KEYALREADYPRESENT - 㦥 ��⠭����� ᥪ��� ����.                   */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
         int  i,Ret;

     if(! Context)
  Ret = RET_INVALIDPARAMETER;
else
if((Context->Mark     & GOST_XXXXX_Marker_Mask ==
    R34_10_2001_Marker & GOST_XXXXX_Marker_Mask   ) &&
   (Context->Mark                                  !=
    R34_10_2001_Marker                            )   )
  Ret = RET_INCORRECTCONTEXT;
else if(!(Context->IsReady &  R34_10_2001_CONTEXT                         ))
  Ret = RET_CONTEXTNOTREADY;
else if(  Context->IsReady & (R34_10_2001_SECRETKEY ^ R34_10_2001_PUBLICKEY))
  Ret = RET_KEYALREADYPRESENT;
else  
  {
  /* ������� ��砩���� ����. */
  CrypC_Gen_SecretKey_(Context->RS, Context->SecretKey, 1);
  /* Network to Host Byteorder. */
  CrypC_NetToHost(Context->SecretKey,(Context->Q_Size/4));

  /* ��᪨஢���� ����. */
  CrypC_Mask_SecretKey_(Context->RS, Context->SecretKey);
    
  Context->IsReady |= R34_10_2001_SECRETKEY;
  Ret = RET_OK;
  }
return(Ret);
}
/*��������������������������������������������������R34_10_2001_gen_secret_key*/
/*�������������������������������������������������������������������������EOF*/
