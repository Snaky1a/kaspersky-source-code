#include "CrC_User.h"
#include <stdio.h>

/*���������������������������������������������������������������������DEFINES*/
/*����������������������������������������������������������R34_11_1994_update*/
int CrypC_R34_11_1994_update(struct R34_11_1994 *Context, void *Buff, LINT LenBuff)
/*����������������������������������������������������������������������������*/
/*           ����䨪��� ���-����� ᮮ�饭�� �ࠣ���⮬ ᮮ�饭��           */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* - �����⥫� �� ���� ⥪�� ��� ���஢���� *Buff.                         */
/* - ����� ������ � ���� *Buf � ����� LenBuff.                             */
/* ��室:                                                                     */
/* - ������஢����� ���ﭨ� ���⥪��.                                    */
/* ���� ������:                                                             */
/* - RET_OK                                                                   */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_CONTEXTNOTREADY                                                      */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
    int         Ret;
   LINT         i;

if(!Context || !Buff)
  Ret = RET_INVALIDPARAMETER;
else
if((Context->Mark     & GOST_XXXXX_Marker_Mask ==
    R34_11_1994_Marker & GOST_XXXXX_Marker_Mask   ) &&
   (Context->Mark                                  !=
    R34_11_1994_Marker                            )   )
  Ret = RET_INCORRECTCONTEXT;
else if(Context->IsReady != 1)
  Ret = RET_CONTEXTNOTREADY;
else
  {  
  for(i=0;i<LenBuff;i++)
     {
     if(Context->BlockOffs == LNQ*4)         /* ��⮢ ���� ��� ���஢����?   */
       {
//     CrypC_NetToHost(Context->Feed,LNQ);
       CrypC__Hash(Context->PE->K_, Context->Digest, Context->Feed);
//     CrypC_HostToNet(Context->Feed,LNQ);
       CrypC__add_LbC(LNQ*4,Context->SumVec,Context->Feed);
       Context->MsgLength += LNQ*4;
       Context->BlockOffs  =     0;          /* ���. ᤢ�� � �����.           */
       }
                                             /* ���������� ⥪��:            */
     Context->Feed[Context->BlockOffs++] = ((BYTE *)Buff)[i];
     }
    
  Ret = RET_OK;
  }
return(Ret);
}
/*����������������������������������������������������������R34_11_1994_update*/
/*�������������������������������������������������������������������������EOF*/
