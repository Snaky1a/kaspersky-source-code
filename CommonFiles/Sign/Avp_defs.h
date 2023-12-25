#ifndef __avp_defs_h
#define __avp_defs_h

#include <Sign/ct_funcs.h>

#define AVP_VERSION_NOW         0x1

#if defined( N_PLAT_NLM )
  extern char	szKaspUser[];              //"Kaspersky Lab"
  extern char	szKaspUserSN[];            //"Kaspersky Lab SK 000"
#else
  #define szKaspUser              "Kaspersky Lab"
  #define szKaspUserSN            "Kaspersky Lab SK 000"
#endif

#define sizeofKaspUserSN        21
//#define szDistUserSN            "Kaspersky Lab SK 001"

#define szPubFileExt            "pub"
#define szOrderFileExt          "ord"
#define szKeyFileExt            "key"
#define szWalletFileExt         "wal"
#define szAVPTitle              "AVP"

#if defined( _DEBUG )
  #define szAVPKeyAddress       "dbkeys1@avp.ru"
#else
  #define szAVPKeyAddress       "dbkeys@avp.ru"
#endif

#define szAVPPublicKeySubject   "AVP public key file"
#define szAVPRequestSubject     "AVP key request"
#define szAVPTestRequest        "This key must be used for testing purpose only"
#define szDBFDriver             "Microsoft Access Driver (*.mdb)"
//#define szDBFDriver             "Microsoft dBase Driver (*.dbf)"

#define ENCRYPT_KEY             0x4321
#define MAX_NUM_OF_COPIES       10000

#define TCP_PORT_NUM            7770
#define TCP_PORT_NUM_STR        "7770"

// ---
#define WALLET_MAGIC  'fWlK'
#define WALLET_XOR    ((unsigned char)0x19)

enum { khe_empty, khe_ready, khe_created, khe_restricted };

typedef struct t_KHeadEntry {
  unsigned ok      : 4;    // ���� ������ � �� �����������
  unsigned offset  : 28;   // �������� �� ������ �����
} KHeadEntry;


#ifndef GUID_DEFINED
#define GUID_DEFINED

typedef struct _GUID {          // size is 16
    unsigned long   Data1;
    unsigned short  Data2;
    unsigned short  Data3;
    unsigned char   Data4[8];
} GUID;

#endif // !GUID_DEFINED


// ---
typedef struct t_WalletHeader {
  unsigned long magic;          // signature
  unsigned long version;        // version
  unsigned long head_len;       // ����� ���������
  unsigned long cont_len;       // ����� ����� ��� �������
  unsigned long pack_len;       // ����� ����� ��� �������
  unsigned long distr_num;      // ���������� ����� �����������
  GUID          order_id;       // id ������
  unsigned long order_num;      // ���������� ����� ������
  unsigned long key_num;        // ������ �������� ����� �����
  unsigned long key_len;        // ����� ����� ��� �������
  short order_count;    // ���-�� ������ � ������
  short real_count;     // ���-�� ������ � �����
  KHeadEntry keys[1];   // ��������� ��� ������
} WalletHeader;

#endif