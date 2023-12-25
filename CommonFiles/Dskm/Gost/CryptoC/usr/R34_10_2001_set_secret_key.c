#include <stdio.h>
#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*��������������������������������������������������R34_10_2001_set_secret_key*/
int CrypC_LR34_10_2001_set_secret_key(struct LR34_10_2001 *Context, void *SecretKey)
/*����������������������������������������������������������������������������*/
/*      ��⠭���� ᥪ�⭮�� ���� � ���⥪�� ��ࠡ�⪨ ��஢�� ������      */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* - �����⥫� �� ���� ����᪨஢������ ᥪ�⭮�� ����: *SecretKey.        */
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

     if(!Context || !SecretKey)
  Ret = RET_INVALIDPARAMETER;
else
if((Context->Mark     & GOST_XXXXX_Marker_Mask ==
    R34_10_2001_Marker & GOST_XXXXX_Marker_Mask   ) &&
   (Context->Mark                                  !=
    R34_10_2001_Marker                            )   )
  Ret = RET_INCORRECTCONTEXT;
else if(!(Context->IsReady & R34_10_2001_CONTEXT))
  Ret = RET_CONTEXTNOTREADY;
else if( (Context->IsReady & R34_10_2001_SECRETKEY))
  Ret = RET_KEYALREADYPRESENT;
else  
  {
  memcpy(Context->SecretKey,
                  SecretKey,
         Context->Q_Size   );                 /* ������ ���� ������.      */
  CrypC_NetToHost(Context->SecretKey,
                 (Context->Q_Size/4));        /* Net to Host Byteorder.       */

  /* ��᪨஢���� ����. */
  CrypC_Mask_SecretKey_(Context->RS, Context->SecretKey);
    
  Context->IsReady |= R34_10_2001_SECRETKEY;
  Ret = RET_OK;
  }
return(Ret);
}
/*��������������������������������������������������R34_10_2001_set_secret_key*/
/*�������������������������������������������������������������������������EOF*/
