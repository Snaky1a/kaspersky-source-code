#ifndef __REPORT_H
#define __REPORT_H

//#define report_buf_size 1024            // ࠧ��� ���� ࠯��� 䠩��

//extern unsigned char *report_buf;       // 㪠��⥫� �� ���� ࠯��� 䠩��
//extern int            report_hnd;       // handle ࠯��� 䠩��

extern char szExtRep[0x200];
// ���樠����஢��� ࠯��� 䠩�
void reportInit(void);
// ������� ��ப� � ࠯��� 䠩�
void reportPutS(char *str);
void reportForEach(char* szCurName);
// �������� ࠡ��� � ࠯��� 䠩���
void reportDone(void);

#endif