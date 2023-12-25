#include "CrC_User.h"
#include <string.h>
#include <stdio.h>
/*���������������������������������������������������������������������DEFINES*/
/*����������������������������������������������������������������������GENSEC*/
int     CrypC_Gen_SecretKey_(struct RND_State *State, void  *Sec, int Keys)
/*���������������������������������������������������������������������������*/
/*       ������� Keys �ᥢ����砩��� ������� ���祩 ����� NK*4 ����     */
/* �室�� ��ࠬ����:                                                        */
/* - ���� ���� *Sec (Keys*NK*4 ����).                                      */
/* ��室:                                                                    */
/* - Keys �ᥢ����砩��� ������� ���祩 � ���� *Sec.                       */
/*���������������������������������������������������������������������������*/
{
  DWORD *M1, TMPKey[LNK];
  int    i;
extern   struct COM_State PERMDefault;

/* �맮� ��楤��� �ନ஢����  ������஢������ ���ᨢ� ����⠭����       */
/* ��� �ਯ��奬� ���� 28147-89:                                             */
CrypC__InitGost( (BYTE *)PERMDefault.Perms, PERMDefault.K_ );
CrypC_FillByRandom_(State, TMPKey,     LNK*4);/* ���砩�� ����.              */ 
CrypC_FillByRandom_(State, Sec   ,Keys*LNK*4);/* ��砫쭮� ����������.        */ 
for(i=0;i<Keys*LNK/2;i++)                /* �����஢���� �� ��砩��� ����.*/
   {
   M1=(DWORD *)((char *)Sec+(i*8));
   CrypC__GOSTE_(PERMDefault.K_,TMPKey,M1,M1);
   }
CrypC_HostToNet(Sec,(Keys*LNK));         /* Host to Network Byteorder.        */
return(0);
}
/*����������������������������������������������������������������������GENSEC*/
/*�������������������������������������������������������������������������EOF*/
