#include <stdio.h>
#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*��������������������������������������������������R34_10_2001_gen_public_key*/
int CrypC_LR34_10_2001_gen_public_key(struct LR34_10_2001 *Context)
/*����������������������������������������������������������������������������*/
/*                  ���᫥��� � ��⠭���� ����⮣� ����                    */
/*                  � ���⥪�� ��ࠡ�⪨ ��஢�� ������                     */
/*                    � ��⠭������� ᥪ��� ���箬                        */
/*                            ���� �3410-2001                                 */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* ��室:                                                                     */
/* - ���⥪��, ��⮢� � ���᫥��� � �஢�થ ��஢�� ������.              */
/* ���� ������:                                                             */
/* - RET_OK                - ��ଠ�쭮� �����襭��.                           */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_CONTEXTNOREADY    - �� ���樠����஢��� ��ࠬ���� ������.           */
/* - RET_KEYALREADYPRESENT - 㦥 ��⠭����� ������ ����.                    */
/* - RET_KEYNOTPRESENT     - �� ��⠭����� ᥪ��� ����.                    */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
#define P_      (Context->P_)
#define Q_      (Context->Q_)
#define QG_     (Context->QG_)
#define AP_     (Context->AP_)
#define SK_     (Context->SecretKey)
#define PK_     (Context->PublicKey)
#define P_Bytes (Context->P_Size)
#define P_Words (Context->P_Size/4)
#define Q_Bytes (Context->Q_Size)
#define Q_Words (Context->Q_Size/4)
{
         int  i,Ret;

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
else if( (Context->IsReady & R34_10_2001_PUBLICKEY))
  Ret = RET_KEYALREADYPRESENT;
else if(!(Context->IsReady & R34_10_2001_SECRETKEY))
  Ret = RET_KEYNOTPRESENT;
else  
  {
  /* �����᪨஢���� ᥪ�⭮�� ����.*/
  for(i=0;i<Q_Words;i++)
     ((DWORD *)SK_)[i        ] +=
     ((DWORD *)SK_)[i+Q_Words]  ;

  /* ���᫥��� ����⮣� ����. */
  CrypC_LCuPower(&AP_, SK_, &PK_, Context);                      /* PK_ = (AP_)*SK_ */

  /* ��᪨஢���� ����. */
  CrypC_Mask_SecretKey_(Context->RS, SK_);
    
  Context->IsReady |= R34_10_2001_PUBLICKEY;
  Ret = RET_OK;
  }
return(Ret);
}
/*��������������������������������������������������R34_10_2001_gen_public_key*/
/*�������������������������������������������������������������������������EOF*/
