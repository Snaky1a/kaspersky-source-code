#ifndef __DISK_H
#define __DISK_H

typedef unsigned long       DWORD;
typedef struct _SELECT_SEGM
 {
  USHORT  segment;
  union
   {
    char far* str;
    struct
     {
      ULONG  offset;
      USHORT selector;
     };
   };
 } SelectSegm;

extern SelectSegm  SS;
#define SIZEALLOC 0x8000 //0xffff

typedef struct rminfo
 {
    long EDI;
    long ESI;
    long EBP;
    long reservedBySystem;
    long EBX;
    long EDX;
    long ECX;
    long EAX;
    short flags;
    short ES,DS,FS,GS,IP,CS,SP,SS;
 } RMI;

#ifdef __cplusplus
   extern "C" {
#endif
BOOL SimulateRMInt(UCHAR Int,RMI far* rmi);
BOOL pmAllocMem(USHORT Size,USHORT *selector,USHORT *segment);
BOOL pmResizeMem(USHORT NewSize,USHORT selector);
#ifdef __cplusplus
   }
#endif
BOOL pmFreeMem(short selector);
#pragma aux pmFreeMem=  \
  "mov   ax,0101h"      \
  "int   031h"          \
  "jc    FM_Err  "      \
  "mov   eax,1   "      \
  "jmp   short FM_Done" \
"FM_Err:         "      \
  "mov   eax,0   "      \
"FM_Done:        "      \
  parm   [edx]          ;
//  modify [eax]         ;

BOOL SetCursorOff(BOOL fl);
void GetCurrentDir(CHAR* szPath);

#define OPEN_AVP  0x0008  /* ---- ---- ---- 1--- */
int copyfile(char *oldFile,char *newFile);

BOOL ExistDisk(char device);
// �����頥� ⨯ ���ன�⢠:
//  00h - no such drive
//  01h - floppy without change-line support
//  02h - floppy with change-line support
//  03h - hard disk
LONG DiskType(CHAR *dst);

// �����頥�: 1 - disk is remote, 0 - disk is not remote
//unsigned char CheckForRemote(unsigned char num);

//��᫮ ��᪮��� ������⥫��
//���� 6-7 � ���� ����� - ������⢮ ����(�᫨ ��� 1 = 1)
UCHAR GetNumberFloppyDisks(void);
#pragma aux GetNumberFloppyDisks= \
  "int  11h        "      \
  "test al,0       "      \
  "jne  No_Drives  "      \
  "and  al,1100000b"      \
  "mov  cl,5       "      \
  "shr  al,cl      "      \
  "inc  al         "      \
  "jmp  GNF_Done   "      \
"No_Drives:        "      \
  "mov  ax,0       "      \
"GNF_Done:         "      \
  modify [cl]             ;
//  value  [ax];

#define DISK_FDD_WITHOUT   1              // floppy without change-line support
#define DISK_FDD_WITH      2              // floppy with change-line support
#define DISK_HDD           8              // hard disk
#define DISK_REMOTE       16              // remote disk
#define DISK_SELECTED    128              // disk selected by user

//extern unsigned char CountHDD,            // ������⢮ 䨧��᪨� HDD � ��⥬�
//                     CountDisk,           // ������⢮ ॠ���� �����᪨� ��᪮�
//                     CountNetWork,        // ������⢮ �⥢�� �����᪨� ��᪮�
//                     Disk[26],            // Disk... (�࠭�� ���ଠ�� � ��᪠�)
//                     VolumeLabel[26][12]; // ��⪨ ⮬�� �� floppy ��᪮�
                                          // VolumeLabel[2]  - label c:
                                          // VolumeLabel[3]  - label d:
                                          // ...
                                          // VolumeLabel[25] - label z:

// ������� ���ଠ�� � ��� ��������� � ��⥬� �����᪨� ��᪠�:
//  - ������⢮ 䨧��᪨� HDD � ��⥬�
//  - ������⢮ ��� ��᪮�
//  - ������⢮ �⥢�� �����᪨� ��᪮�
//  - �� �� ᥡ� �।�⠢��� ����� ��� � �⤥�쭮��
//  - ��⪨ ��᪮�
//void  InitDisks(void);

// ������� ⥪�騩 �����᪨� ��� (00h='A:',01h='B:',02h='�:',etc)
// �����頥�: ����� ⥪�饣� �����᪮�� ��᪠
//unsigned char GetCurrentDisk();

// ��⠭����� ⥪�騩 �����᪨� ��� (00h='A:',01h='B:',02h='�:',etc)
// �����頥�: ����� ��⥭樠�쭮 ���������� �����᪮�� ��᪠
//unsigned char SetCurrentDisk(unsigned char num);

// ������ ॠ��� ����� ��᪠ �� ������ � ᯨ᪥
//unsigned char GetRealDiskNum(unsigned char num);

// ����p頥�: 1 - �뤥���� �� ������� HDD, ���� 0
//unsigned char IsSelectAllLocHDD();

// ����p�頥�: 1 - �뤥���� �� �⥢� ��᪨, ���� 0
//unsigned char IsSelectAllNetWork();

// �����頥�: 1 - �뤥��� ��� �� ���� ���, ���� 0
//unsigned char IsDiskSelect();

#endif