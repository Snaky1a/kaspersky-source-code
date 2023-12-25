#include <stdio.h>
#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*������������������������������������������������R34_10_2001_clear_secret_key*/
int CrypC_LR34_10_2001_clear_secret_key(struct LR34_10_2001 *Context)
/*����������������������������������������������������������������������������*/
/*                  ���⪠ ᥪ�⭮�� ���� � ���⥪��                      */
/*                  ��ࠡ�⪨/�஢�ન ��஢�� ������                       */
/*                            ���� �3410-2001                                 */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* ��室:                                                                     */
/* - ��饭�� ���� ᥪ�⭮�� ���� � ���⥪��.                            */
/* ���� ������:                                                             */
/* - RET_OK                - ��ଠ�쭮� �����襭��.                           */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_CONTEXTNOTREADY   - ���⥪�� �� ���樠����஢��.                     */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
  int i,Ret;

if(!Context)
  Ret = RET_INVALIDPARAMETER;
else
if((Context->Mark     & GOST_XXXXX_Marker_Mask ==
    R34_10_2001_Marker & GOST_XXXXX_Marker_Mask   ) &&
   (Context->Mark                                  !=
    R34_10_2001_Marker                            )   )
  Ret = RET_INCORRECTCONTEXT;
else if(!(Context->IsReady & R34_10_2001_CONTEXT))
  Ret = RET_CONTEXTNOTREADY;
else
  {
  for(i=0;i<Context->Q_Size;i++) ((char *)Context->SecretKey)[i] = 0x00;
  Context->IsReady &= ~R34_10_2001_SECRETKEY;
  Ret = RET_OK;
  }
return(Ret);
}
/*������������������������������������������������R34_10_2001_clear_secret_key*/
/*�������������������������������������������������������������������������EOF*/
