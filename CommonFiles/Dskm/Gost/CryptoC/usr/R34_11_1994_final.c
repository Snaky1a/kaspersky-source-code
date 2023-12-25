#include "CrC_User.h"
#include <stdio.h>

void HTON(void *, int);
/*���������������������������������������������������������������������DEFINES*/
/*�����������������������������������������������������������R34_11_1994_final*/
int CrypC_R34_11_1994_final(struct R34_11_1994 *Context, void *Digest)
/*����������������������������������������������������������������������������*/
/*           �����襭�� ��ࠡ�⪨ ���⮢���� ᮮ�饭�� � �뤠� ���         */
/*                           ��뢠�饩 �ணࠬ��                             */
/* �室�� ��ࠬ����:                                                         */
/* - �����⥫� �� ���� ���⥪��: *Context (�������).                      */
/* - �����⥫� �� ���� ��� ��।�� ���-������ *Digest.                     */
/* ��室:                                                                     */
/* - ���� ��।�� ���-����� ᮤ�ন� ���-����� ᮮ�饭��.                */
/* ���� ������:                                                             */
/* - RET_OK                                                                   */
/* - RET_INCORRECTCONTEXT  - ��।�� ���樠����஢���� ���⥪�� ��. ०���.  */
/* - RET_CONTEXTNOTREADY                                                      */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
   int          Ret;
  DWORD         TotalLength;
   BYTE         A[LNQ*4],SUMVEC[LNQ*4];

if(!Context || !Digest)
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
  memcpy(Digest,Context->Digest,LNQ*4);       /* �뢥�� ���⮢���� � ����. */
  memcpy(SUMVEC,Context->SumVec,LNQ*4);       /* ������ �㬬� ������.        */
  TotalLength = Context->MsgLength;           /* ������ ����� ᮮ�饭��.     */

  if(Context->BlockOffs)                      /* ���� ���������� �����?     */
    {
    if(Context->BlockOffs < LNQ*4)            /* ��������� �����  �����?     */
      memset(Context->Feed+Context->BlockOffs,0,(LNQ*4)-(Context->BlockOffs));
                                              /* ���஢���� ��������� �����: */
//printf("Hash Partial:\n");
    CrypC__Hash(Context->PE->K_, Digest, Context->Feed); /* (� ��室��� ����).*/
    CrypC__add_LbC(LNQ*4,SUMVEC,Context->Feed);
    TotalLength += Context->BlockOffs;        /* ����� � ������� ������.     */
    }
  else                                        /* ��� ����������� ������.      */
    if(!TotalLength)                          /* ����� �� �뫮 ������.       */
      {                                       /* ���஢���� �㫥���� �����:  */
                                              /* SUMVEC �筮 = 0.            */
      HTON(SUMVEC, LNQ);                      /* Net to Host Byteorder.       */
      CrypC__Hash(Context->PE->K_, Digest, SUMVEC); /* (� ��室��� ����).   */
      }

  TotalLength <<= 3;                          /* ����� ᮮ�饭�� � ����.     */
  memset(A,0,LNQ*4);
  memcpy(A,&TotalLength,4);                   /* ����, ᮤ�ঠ騩 �����.      */
  HTON(A, LNQ);                               /* Net to Host Byteorder.       */
//printf("Hash Length:\n");
  CrypC__Hash(Context->PE->K_, Digest, A);    /* ���஢���� ����� ᮮ�饭��. */
  HTON(SUMVEC, LNQ);                          /* Net to Host Byteorder.       */
//printf("Hash Sum:\n");
  CrypC__Hash(Context->PE->K_, Digest, SUMVEC);/* ���஢���� �㬬� ������.   */
    
  HTON(Digest, LNQ);                           /* Host to Net Byteorder.      */
//CrypC_HostToNet(Digest, LNQ);                /* Host to Net Byteorder.      */
  Ret = RET_OK;
  }
return(Ret);
}
/*�����������������������������������������������������������R34_11_1994_final*/
/*�������������������������������������������������������������������������EOF*/
