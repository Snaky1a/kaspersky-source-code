#include <stdio.h>
#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*��������������������������������������������������R34_10_2001_get_secret_key*/
int CrypC_LR34_10_2001_get_secret_key(struct LR34_10_2001 *Context, void *SecretKey, int *KeySize)
/*����������������������������������������������������������������������������*/
/*       �⥭�� ᥪ�⭮�� ���� �� ���⥪�� ��ࠡ�⪨ ��஢�� ������      */
/*                            ���� �3410-2001                                 */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* - �����⥫� �� ���� ����᪨஢������ ᥪ�⭮�� ����: *SecretKey.        */
/* - �����⥫� �� ���� ࠧ��� ����: *KeySize.                              */
/* ��室:                                                                     */
/* - ����᪨஢���� ������ ���� � ���� SecretKey, ࠧ��� ���� � ����� */
/*   - � ���� KeySize.                                                      */
/*   �᫨ SecretKey == 0, � �����頥��� ⮫쪮 ����� ����.                 */
/* ���� ������:                                                             */
/* - RET_OK                - ��ଠ�쭮� �����襭��.                           */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_CONTEXTNOREADY    - �� ���樠����஢��� ��ࠬ���� ������.           */
/* - RET_KEYNOTPRESENT     - �� ��⠭����� ᥪ��� ����.                    */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
         int  i,Ret;

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
else if(!(Context->IsReady & R34_10_2001_SECRETKEY))
  {
  *KeySize = Context->Q_Size;             /* ������ ���� � �����.           */
  Ret = RET_KEYNOTPRESENT;
  }
else  
  {
  *KeySize = Context->Q_Size;             /* ������ ���� � �����.           */
                                          /* �����᪨஢���� ᥪ�⭮�� ���� */
                                          /*             � ���� SecretKey.   */
  if(SecretKey)
    {
    for(i=0;i<Context->Q_Size/4;i++)
       ((DWORD *)         SecretKey)[i                  ] =
       ((DWORD *)Context->SecretKey)[i                  ] +
       ((DWORD *)Context->SecretKey)[i+Context->Q_Size/4] ;
     
    CrypC_NetToHost(           SecretKey,
                     (Context->Q_Size/4));/* Net to Host Byteorder.           */
                                          /* ��६�᪨஢���� ����.          */
    CrypC_ReMask_SecretKey_(Context->RS, Context->SecretKey);
    }
  Ret = RET_OK;
  }
return(Ret);
}
/*��������������������������������������������������R34_10_2001_get_secret_key*/
/*�������������������������������������������������������������������������EOF*/
