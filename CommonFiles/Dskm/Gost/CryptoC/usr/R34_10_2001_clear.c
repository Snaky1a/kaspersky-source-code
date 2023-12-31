#include <stdio.h>
#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*�����������������������������������������������������������R34_10_2001_clear*/
int CrypC_LR34_10_2001_clear(struct LR34_10_2001 *Context)
/*����������������������������������������������������������������������������*/
/*                           ���⪠ ���⥪��                                */
/*                  ��ࠡ�⪨/�஢�ન ��஢�� ������                       */
/*                            ���� �3410-2001                                 */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* ��室:                                                                     */
/* - ��饭�� ���� ���⥪��.                                               */
/* ���� ������:                                                             */
/* - RET_OK                - ��ଠ�쭮� �����襭��.                           */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
  int i, Ret;

if(!Context)
  Ret = RET_INVALIDPARAMETER;
else
if((Context->Mark     & GOST_XXXXX_Marker_Mask ==
    R34_10_2001_Marker & GOST_XXXXX_Marker_Mask   ) &&
   (Context->Mark                              !=
    R34_10_2001_Marker                            )   )
  Ret = RET_INCORRECTCONTEXT;
else
  {
  for(i=0;i<sizeof(struct LR34_10_2001);i++)
     ((char *)Context)[i] = 0x00;
  Context->Mark = R34_10_2001_Marker;
  Ret = RET_OK;
  }
return(Ret);
}
/*�����������������������������������������������������������R34_10_2001_clear*/
/*�������������������������������������������������������������������������EOF*/
