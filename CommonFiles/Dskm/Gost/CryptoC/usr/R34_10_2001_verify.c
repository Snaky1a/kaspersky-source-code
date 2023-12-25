#include "CrC_User.h"
#include <stdio.h>

/*���������������������������������������������������������������������DEFINES*/
/*����������������������������������������������������������R34_10_2001_verify*/
int CrypC_LR34_10_2001_verify(struct LR34_10_2001 *Context, void *_Digest, void *_Signature)
/*����������������������������������������������������������������������������*/
/*            �஢�ઠ ��஢�� ������ ��������� ���-�����                 */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* - �����⥫� �� ���� ���-�����: Digest (NQ*2 ����).                      */
/* - �����⥫� �� ���� ��஢�� ������: Signature (4*NQ ����).              */
/* ��室:                                                                     */
/* - ��� ������.                                                            */
/* ���� ������:                                                             */
/* - RET_OK             - ������� �஢�७�, १���� �஢�ન ������⥫��.*/
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_INCORRECTSIGN  - ������� �஢�७�, १���� �஢�ન ����⥫��.*/
/* - RET_ZERO_R         - �㫥��� ���祭�� ��������� ��� r'.                 */
/* - RET_ZERO_S         - �㫥��� ���祭�� ��������� ��� s .                 */
/* - RET_BAD_R          - �����४⭮� ���祭�� ��������� ��� r'.            */
/* - RET_BAD_S          - �����४⭮� ���祭�� ��������� ��� s .            */
/* - RET_CONTEXTNOTREADY   - �� ���樠����஢��� ��ࠬ���� ������.           */
/* - RET_KEYNOTPRESENT     - �� ��⠭����� ������ ����.                     */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
#define Digest    ((BYTE *)_Digest)
#define Signature ((DWORD *)_Signature)
DWORD SignBuff[LNQ+LNQ+LNQ];
int   Ret;

     if(! Context || !Digest || !Signature)
  Ret = RET_INVALIDPARAMETER;
else
if((Context->Mark     & GOST_XXXXX_Marker_Mask ==
    R34_10_2001_Marker & GOST_XXXXX_Marker_Mask   ) &&
   (Context->Mark                                  !=
    R34_10_2001_Marker                            )   )
  Ret = RET_INCORRECTCONTEXT;
else if(!(Context->IsReady & R34_10_2001_CONTEXT))
  Ret = RET_CONTEXTNOTREADY;
else if(!(Context->IsReady & R34_10_2001_PUBLICKEY))
  Ret = RET_KEYNOTPRESENT;
else
  {
  memcpy( SignBuff                  , Digest   , Context->Q_Size   );
  memcpy( SignBuff+Context->Q_Size/4, Signature, Context->Q_Size*2 );
  CrypC_NetToHost(SignBuff,((Context->Q_Size*3)/4));
  Ret = CrypC_LCuCheck(Context, SignBuff);
  }
return (Ret);
}
/*����������������������������������������������������������R34_10_2001_verify*/
/*�������������������������������������������������������������������������EOF*/
