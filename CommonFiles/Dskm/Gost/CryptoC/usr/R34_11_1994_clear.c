#include <stdio.h>
#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*�����������������������������������������������������������R34_11_1994_clear*/
int CrypC_R34_11_1994_clear(struct R34_11_1994 *Context)
/*����������������������������������������������������������������������������*/
/*                           ���⪠ ���⥪��                                */
/*                         ��ࠡ�⪨ ���-�����                              */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* ��室:                                                                     */
/* - ��饭�� ���� ���⥪��.                                               */
/* ���� ������:                                                             */
/* - RET_OK                                                                   */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
  int i, Ret;

if(!Context)
  Ret = RET_INVALIDPARAMETER;
else
if((Context->Mark     & GOST_XXXXX_Marker_Mask ==
    R34_11_1994_Marker & GOST_XXXXX_Marker_Mask   ) &&
   (Context->Mark                              !=
    R34_11_1994_Marker                            )   )
  Ret = RET_INCORRECTCONTEXT;
else
  {
  for(i=0;i<sizeof(struct R34_11_1994);i++)
     ((char *)Context)[i] = 0x00;
  Context->Mark = R34_11_1994_Marker;
  Ret = RET_OK;
  }
return(Ret);
}
/*�����������������������������������������������������������R34_11_1994_clear*/
/*�������������������������������������������������������������������������EOF*/
