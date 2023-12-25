#ifndef __AVP_H
#define __AVP_H

#define FL_LOAD_INI   0x01
#define FL_LOAD_KEY   0x02
#define FL_LOAD_PRF   0x04
#define FL_LOAD_HLP   0x08   // 1 - out help screen
#define FL_LOAD_BASE  0x10
#define FL_UNSIGN_EXE 0x20
extern ULONG fl_load;

#define YEAR(t)   (((t & 0xFE00) >> 9) + 1980)
#define MONTH(t)  ((t & 0x01E0) >> 5)
#define DAY(t)    (t & 0x001F)
#define HOUR(t)   ((t & 0xF800) >> 11)
#define MINUTE(t) ((t & 0x07E0) >> 5)
#define SECOND(t) ((t & 0x001F) << 1)

extern char  nameExe[CCHMAXPATH];
char *GNAM(char *_ttop);

// errorlevel
#define ERR_LEVEL_NO_VIRUS         0 // ����ᮢ �� �����㦥��
#define ERR_LEVEL_NOT_COMPLETED    1 // ᪠��஢���� �� �����祭�
#define ERR_LEVEL_WARNINGS         3 // ������� ������⥫�� ��ꥪ��
#define ERR_LEVEL_VIRUS            4 // �����㦥� �����
#define ERR_LEVEL_ALL_DISINFECTED  5 // �� �����㦥��� ������ 㤠����
#define ERR_LEVEL_AVP_DAMAGE       7 // 䠩� AVP.EXE ���०���
#define ERR_LEVEL_AVP_CRASH       10 // ����७��� �訡�� �ணࠬ�� AVP.EXE

struct _cmdline
 {
  BYTE start_minumize,
       skip_mbr,
       skip_boot,
       skip_dlg,
       one_floppy,
       quit_after,
       remote,
       abort_disable,
       KillList;
  char ListFile[CCHMAXPATH];
 };
extern struct  _cmdline cmdline;

//extern unsigned char scanner_name[9];
//extern unsigned char ctrl_break_state;
//extern unsigned char LngID;
extern unsigned char f_help;           // 1 - out help screen
//extern unsigned char f_daily;          // 1 - daily
//extern unsigned char f_csdl;           // 1 - can't set def. lng.

extern BOOL flScanAll;
extern unsigned char prg_error;

//extern unsigned char f_damage;
extern unsigned char f_was_expir;      // =1 - �뢥�� �।�०�����, �� ��業���
extern unsigned char f_will_expir;     // =1 - �뢥�� �।�०�����, �����
//extern unsigned char f_i_every_launch; // =1 - �뢥�� "Copy Info" �� ����᪥
extern char *startPath;//[CCHMAXPATH];   // ����� ����, ��㤠 �� ����饭 AVP

extern char prgPath[CCHMAXPATH];         // ����� ����, ��� ��室���� AVP

extern char file_name[CCHMAXPATH];       // ����

// ��ࠡ��稪 ��室� �� �ணࠬ��
//void exit_();

#endif