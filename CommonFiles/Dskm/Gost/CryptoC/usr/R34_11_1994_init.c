#include <stdio.h>
#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*������������������������������������������������������������R34_11_1994_init*/
int CrypC_R34_11_1994_init(struct R34_11_1994 *Context, struct COM_State *PE, struct RND_State *State, void *Sync)
/*����������������������������������������������������������������������������*/
/*                        ���樠������ ���⥪��                             */
/*                         ��ࠡ�⪨ ���-�����                              */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* - �����⥫� �� ���� ��砫쭮�� ���祭�� ���-����� *Sync (NQ*2 ����).   */
/*             �᫨ 㪠��⥫� ࠢ�� 0, � �ਭ������� �㫥��� ����������.     */
/* ��室:                                                                     */
/* - ���⥪��, ��⮢� � ��ࠡ�⪥ ���-�����.                               */
/* ���� ������:                                                             */
/* - RET_OK                                                                   */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_CONTEXTNOTCLEAR                                                      */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
	 int  i, Ret;

/* �맮� ��楤��� �ନ஢����  ������஢������ ���ᨢ� ����⠭����       */
/* ��� �ਯ��奬� ���� 28147-89:                                             */
CrypC__InitGost( (BYTE *)PE->Perms, PE->K_ );

if(!Context || !State)
  Ret = RET_INVALIDPARAMETER;
else
if((Context->Mark     & GOST_XXXXX_Marker_Mask ==
    R34_11_1994_Marker & GOST_XXXXX_Marker_Mask   ) &&
   (Context->Mark                                  !=
    R34_11_1994_Marker                            )   )
  Ret = RET_INCORRECTCONTEXT;
else if(Context->IsReady)
  Ret = RET_CONTEXTNOTCLEAR;
else
  {
  if(Context->Mark != R34_11_1994_Marker)
    CrypC_R34_11_1994_clear(Context);

  Context->RS = State;                   /* �����⥫� �� ���⥪�� ���.        */
  Context->PE = PE;                      /* �����⥫� �� ���⥪�� ����⠭����.*/

  if(Sync)
    memcpy        (Context->Digest,Sync,LNQ*4);/* ��砫쭮� ���. ���-�����.*/
  else
    memset        (Context->Digest,   0,LNQ*4);/* ����ய��뫪� �� 㬮�砭��. */
  CrypC_NetToHost (Context->Digest     ,    8);/* Net to Host Byteorder.      */
  memset          (Context->SumVec,   0,LNQ*4);/* ��砫쭮� ���. Sum-�����.*/
    
  Context->MsgLength = 0;                   /* ���稪 �㬬�୮� �����.       */
  Context->BlockOffs = 0;                   /* ���-�. � ���� �����-� �����. */

  Context->IsReady = 1;
  Ret = RET_OK;
  }
return(Ret);
}
/*������������������������������������������������������������R34_11_1994_init*/
/*�������������������������������������������������������������������������EOF*/
