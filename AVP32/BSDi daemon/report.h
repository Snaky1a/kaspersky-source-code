#ifndef __REPORT_H
#define __REPORT_H

#pragma pack (1)

extern char szExtRep[0x400];
// ���樠����஢��� ࠯��� 䠩�
void reportInit(ULONG flag);
void reportReinit(void);
// ������� ��ப� � ࠯��� 䠩�
void reportPutS(char *str);
void reportForEach(char* szCurName);
// �������� ࠡ��� � ࠯��� 䠩���
void reportDone(ULONG flag);

#endif