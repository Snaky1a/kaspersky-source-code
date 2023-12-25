#include <stdio.h>
#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*��������������������������������������������������R34_10_2001_get_public_key*/
int CrypC_LR34_10_2001_get_public_key(struct LR34_10_2001 *Context, struct LPoint *PublicKey, int *KeySize)
/*����������������������������������������������������������������������������*/
/*       �⥭�� ����⮣� ���� �� ���⥪�� ��ࠡ�⪨ ��஢�� ������       */
/*                            ���� �3410-2001                                 */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* - �����⥫� �� ���� �������� ����⮣� ����: *PublicKey.                */
/* - �����⥫� �� ���� ࠧ��� ��������� ����: *KeySize.                    */
/* ��室:                                                                     */
/* - ������ ���� � ���� PublicKey, ࠧ��� ��������� ���� � ����� -      */
/*   � ���� KeySize.                                                        */
/*   �᫨ PublicKey == 0, � �����頥��� ⮫쪮 ����� ����.                 */
/* ���� ������:                                                             */
/* - RET_OK                - ��ଠ�쭮� �����襭��.                           */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_CONTEXTNOREADY    - �� ���樠����஢��� ��ࠬ���� ������.           */
/* - RET_KEYNOTPRESENT     - �� ��⠭����� ������ ����.                     */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
         int  Ret;

     if(! Context || !KeySize)
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
  {
  *KeySize = Context->P_Size;                 /* ������ ���न���� ���� � �����. */
  Ret = RET_KEYNOTPRESENT;
  }
else  
  {
  *KeySize = Context->P_Size;                 /* ������ ���न���� ���� � �����. */
  if(PublicKey)
    {
    memcpy(          PublicKey,
           &Context->PublicKey,
                     LPTSIZE  );              /* ������ ���� ������.       */
    CrypC_LProjToAffi(Context, PublicKey);
    CrypC_LMontToInt (Context, PublicKey);
                                              /* Host to Net Byteorder.       */
    CrypC_HostToNet(PublicKey->X, (Context->P_Size/4));
    CrypC_HostToNet(PublicKey->Y, (Context->P_Size/4));
    }

  Ret = RET_OK;
  }
return(Ret);
}
/*��������������������������������������������������R34_10_2001_get_public_key*/
/*�������������������������������������������������������������������������EOF*/
