// Make Attack Plugin API

#define MAD_PLUGINNAME  "Make Attack Plugin"

// ioctl message ids
#define MAD_MSGID_ATTACK          0x00000001

typedef struct _MAD_ATTACK {
	ULONG	AttackID;			// ������������� �����
	USHORT	Proto;				// ��������
	ULONG	AttackerIP;			// IP-����� ����������
	USHORT	LocalPort;			// ����
} MAD_ATTACK, *PMAD_ATTACK;
