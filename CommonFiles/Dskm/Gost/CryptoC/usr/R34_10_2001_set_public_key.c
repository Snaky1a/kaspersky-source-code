#include <stdio.h>
#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*��������������������������������������������������R34_10_2001_set_public_key*/
int CrypC_LR34_10_2001_set_public_key(struct LR34_10_2001 *Context, void *PublicKey)
/*����������������������������������������������������������������������������*/
/*      ��⠭���� ����⮣� ���� � ���⥪�� ��ࠡ�⪨ ��஢�� ������       */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* - �����⥫� �� ���� ����⮣� ����: *PublicKey.                          */
/* ��室:                                                                     */
/* - ���⥪��, ��⮢� � �஢�થ ��஢�� ������.                           */
/* ���� ������:                                                             */
/* - RET_OK                - ��ଠ�쭮� �����襭��.                           */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_CONTEXTNOREADY    - �� ���樠����஢��� ��ࠬ���� ������.           */
/* - RET_KEYALREADYPRESENT - 㦥 ��⠭����� ������ ����.                    */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
         int  Ret;

     if(!Context || !PublicKey)
  Ret = RET_INVALIDPARAMETER;
else
if((Context->Mark     & GOST_XXXXX_Marker_Mask ==
    R34_10_2001_Marker & GOST_XXXXX_Marker_Mask   ) &&
   (Context->Mark                                  !=
    R34_10_2001_Marker                            )   )
  Ret = RET_INCORRECTCONTEXT;
else if(!(Context->IsReady & R34_10_2001_CONTEXT))
  Ret = RET_CONTEXTNOTREADY;
else if( (Context->IsReady & R34_10_2001_PUBLICKEY))
  Ret = RET_KEYALREADYPRESENT;
else  
  {
  memcpy(&Context->PublicKey,
                   PublicKey,
                   LPTSIZE  );                /* ������ ���� ������.       */
//{int I;for(I=0;I<Context->P_Size/2;I++)printf("%04X",((struct Point *)PublicKey)->X[I]);printf("=Y.X In\n");}
//{int I;for(I=0;I<Context->P_Size/2;I++)printf("%04X",Context->PublicKey.X[I]);printf("=Y.X Net\n");}
  CrypC_NetToHost(Context->PublicKey.X,
                 (Context->P_Size/4));        /* Net to Host Byteorder.       */
  CrypC_NetToHost(Context->PublicKey.Y,
                 (Context->P_Size/4));        /* Net to Host Byteorder.       */
//{int I;for(I=0;I<Context->P_Size/2;I++)printf("%04X",Context->PublicKey.X[I]);printf("=Y.X Host\n");}
  CrypC_LAffiToProj(Context, &Context->PublicKey);
//{int I;for(I=0;I<Context->P_Size/2;I++)printf("%04X",Context->PublicKey.X[I]);printf("=Y.X Proj\n");}
  CrypC_LIntToMont (Context, &Context->PublicKey);
//{int I;for(I=0;I<Context->P_Size/2;I++)printf("%04X",Context->PublicKey.X[I]);printf("=Y.X Mont\n");}

  Context->IsReady |= R34_10_2001_PUBLICKEY;
  Ret = RET_OK;
  }
return(Ret);
}
/*��������������������������������������������������R34_10_2001_set_public_key*/
/*�������������������������������������������������������������������������EOF*/
