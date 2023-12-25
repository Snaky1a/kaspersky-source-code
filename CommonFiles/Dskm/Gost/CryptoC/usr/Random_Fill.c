#include "CrC_User.h"

/*���������������������������������������������������������������������DEFINES*/
/*�����������������������������������������������������������������Random_Fill*/
int     CrypC_Random_Fill( struct RND_State *State, void  *Field, int Bytes )
/*����������������������������������������������������������������������������*/
/*                 ���������� ���� �ᥢ����砩�묨 ����묨.                */
/* �室�� ��ࠬ����:                                                         */
/* - ���� ���� ����� Field.                                               */
/* - ������ ���� � ����� Bytes.                                            */
/* ��室:                                                                     */
/* - ���� �������� �ᥢ����砩��� ��᫥����⥫쭮���� ���� ����� Bytes.     */
/* ���� ������:                                                             */
/* - RET_OK                - ��ଠ�쭮� �����襭��.                           */
/* - RET_INVALIDPARAMETER  - �㫥��� 㪠��⥫� �� ��易⥫�� ��ࠬ���.      */
/*����������������������������������������������������������������������������*/
{
  int    i,Ret,Words,Rest;
  DWORD  TMP;

if(!Field)
  Ret = RET_INVALIDPARAMETER;
else
  {
  Words = Bytes / 4;
  Rest  = Bytes % 4;

  CrypC_FillByRandom_(State,Field,Bytes-Rest);
  CrypC_HostToNet(Field,Words);
  if(Rest)
    {
    CrypC_FillByRandom_(State,&TMP,4);
    CrypC_HostToNet(&TMP,1);
    memcpy(((BYTE *)Field)+Bytes-Rest,&TMP,Rest);
    }

  Ret = RET_OK;
  }
return(Ret);
}
/*�����������������������������������������������������������������Random_Fill*/
/*�������������������������������������������������������������������������EOF*/
