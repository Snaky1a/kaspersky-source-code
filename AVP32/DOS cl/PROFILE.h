#ifndef __PROFILE_H
#define __PROFILE_H

// errors
#define PERR_MEM 0x01  // malloc() failed
#define PERR_OPN 0x02  // Load - open failed
#define PERR_DSK 0x03  // reading/writting/creating failed
#define PERR_COR 0x04  // Load - undet. value

extern char  DefProfile[0x50],LocFile[0x50],KeyFile[0x50],
      KeysPath[CCHMAXPATH],SetFile[0x50],BasePath[CCHMAXPATH];
extern char sInfectedFolder[CCHMAXPATH],sSuspiciousFolder[CCHMAXPATH];

typedef struct _profile_data
 {
  char *List,Path,SubDirectories;
  char Memory,Sectors,Files,Packed,Archives,MailBases,MailPlain,UserMask[81];
  char ExcludeFiles,ExcludeMask[81],*ExcludeDir,ScanRemovable;
//  char ScanAllSector;
  char FileMask,InfectedAction,InfectedCopy,SuspiciousCopy;
  char InfectedFolder[CCHMAXPATH],SuspiciousFolder[CCHMAXPATH];
  char Warnings,CodeAnalyser,RedundantScan,ShowOK,ShowPack,Sound;
  char Report,Append,ExtReport,ReportFileLimit,ReportFileName[CCHMAXPATH],ReportFileSize[8];
  char RepForEachDisk,LongStrings;
  char OtherMessages;
  char Color;
  ULONG OpenHandles;
 } profile_data;

extern unsigned char prf_global_state; // ��⠭���������� �� �訡��

// o_location[2] - ��� ��樨 � �������� "Location"
// o_location[?]=1  - ���� ��⠭������
// o_location[?]=0 - ���� �� ��⠭������
//extern unsigned char o_location[2]; // [0] - "Local hard hisks",
//                                    // [1] - "Network drivers"

extern profile_data prf_data;

// ��⠭���� ��権 �� 㬮�砭��
void setDefaultOptions();

// ���࠭���� PRF 䠩�� (return 0 - ok)
char save_profile_(char *name);

// ����㧪� PRF 䠩�� (return 0 - ok)
char loadProfile(char *name,char *szRep);

ULONG load_ini(char *name);
ULONG SearchFile(char* sFileName,char* sDestName,char* sExt);
#endif