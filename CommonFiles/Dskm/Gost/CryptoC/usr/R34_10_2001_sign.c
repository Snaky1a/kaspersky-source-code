#include <stdio.h>
#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*������������������������������������������������������������R34_10_2001_sign*/
int CrypC_LR34_10_2001_sign(struct LR34_10_2001 *Context, void *_Digest, void *_Signature)
/*����������������������������������������������������������������������������*/
/*           ��ࠡ�⪠ ��஢�� ������ ��������� ���-�����                 */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* - �����⥫� �� ���� ���-�����: Digest (NQ*2 ����).                      */
/* - �����⥫� �� ���� ��� ��஢�� ������: Signature (4*NQ ����).          */
/* ��室:                                                                     */
/* - ���� ������ ᮤ�ন� ��� ��।������ ���-�����.                      */
/* ���� ������:                                                             */
/* - RET_OK                - ��ଠ�쭮� �����襭��.                           */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_CONTEXTNOREADY    - �� ���樠����஢��� ��ࠬ���� ������.           */
/* - RET_KEYNOTPRESENT     - �� ��⠭����� ᥪ��� ����.                    */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
#define Digest    ((BYTE *)_Digest)
#define Signature ((DWORD *)_Signature)
       DWORD SignBuff[LNQ+LNQ+LNQ];
         int Ret;

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
else if(!(Context->IsReady & R34_10_2001_SECRETKEY))
  Ret = RET_KEYNOTPRESENT;
else
  {
  memcpy(SignBuff, Digest, Context->Q_Size);
  CrypC_NetToHost(SignBuff,(Context->Q_Size/4));  /* Net to Host Byteorder.   */
  CrypC_LCuSign( Context, SignBuff );
  memcpy( Signature, SignBuff+Context->Q_Size/4, Context->Q_Size*2 );
  CrypC_HostToNet(Signature,(Context->Q_Size/2)); /* Host to Net Byteorder.   */
  
                                /* ��६�᪨஢���� ᥪ�⭮�� ���� ������: */
  CrypC_ReMask_SecretKey_(Context->RS, (BYTE *)Context->SecretKey);
    
  Ret = RET_OK;
  }
return(Ret);
}
/*������������������������������������������������������������R34_10_2001_sign*/
/*�������������������������������������������������������������������������EOF*/
