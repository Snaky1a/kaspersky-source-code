#pragma pack (push, pack_records)
#pragma pack (1)

#define far 

struct	DB_EMPTY_RECORD		{
	WORD	Type;

				};

struct	DB_FILE_RECORD		{			// FILE Data Base definition

	WORD	Type;				//
	BYTE	Name[SIZE_VIRUS_NAME];	// ��� �����

	BYTE	Page_1;				// ��࠭�� ��� ������뢠���� ��ࢠ� �㬬�
	WORD	Off_1;				// � ������ ���� 1
	BYTE	Len_1;				// ᪮�쪮 ���� 1
	DWORD	Sum_1;				// ����஫쭠� �㬬� 1
	BYTE	Page_2;				// ��� ����� �஢��塞� ���� 2
	WORD	Off_2;				// � ������ ᬥ饭�� 2
	BYTE	Len_2;				// ᪮�쪮 ���� 2
	DWORD	Sum_2;				// ����஫쭠� �㬬� 2

	DWORD		Check;		// program CHECK,
	DWORD		Cure;		// program CURE

	BYTE	Cure_Method;		// ��⮤ ��祭��
	BYTE	Cure_Page;			// ��࠭�� ��㤠 ���� ����� ��� ��祭��
										// �᫨ DUMM, � �� �窨 �室�
	WORD	Cure_Data_1;			// ����� ��� ��祭��
	WORD	Cure_Data_2;			// ����� ��� ��祭��
	WORD	Cure_Data_3;			// ����� ��� ��祭��
	WORD	Cure_Data_4;			// ����� ��� ��祭��

	WORD	Cure_Cut;			// �� ᪮�쪮 㪮�稢���
	WORD	Tail;				// ����� "墮��"

							};

struct	DB_SECTOR_RECORD	{			// SECTOR Data Base definition
	WORD	Type;				//
	BYTE	Name[SIZE_VIRUS_NAME];	// ��� �����

	WORD	Off_1;				// � ������ ���� (1)
	BYTE	Len_1;				// ᪮�쪮 ���� (1)
	DWORD	Sum_1;				// ����஫쭠� �㬬� (1)
	WORD	Off_2;				// � ������ ᬥ饭��
	BYTE	Len_2;				// ᪮�쪮 ����
	DWORD	Sum_2;				// ����஫쭠� �㬬�
	BYTE	Page_2;				// ��� ����� �஢��塞� ����

	DWORD		Check;		// program CHECK,
	DWORD		Cure;		// program CURE

	BYTE	Cure_Method;		// ��⮤ ��祭��, �᫨ SPC -> �믮������ �ணࠬ��
	BYTE	Cure_Page;			// ��࠭�� ��㤠

	WORD	Cure_Addr_A;		// Addr1  - ���. ��� offs ��� ����� ���.
	WORD	Cure_Addr_B;		// Addr2  - DH
	WORD	Cure_Offset;		// �������� � ����� (CX)

				};

struct	DB_JMP_RECORD		{			// JMP Data Base definition

	WORD	Type;				//
	BYTE	Name[SIZE_VIRUS_NAME];	//

	BYTE	Len_1;				// ᪮�쪮 ���� (1)
	DWORD	Sum_1;				// ����஫쭠� �㬬� (1)
	WORD	Off_2;				// � ������ ���� (2)
	BYTE	Len_2;				// ᪮�쪮 ���� (2)
	DWORD	Sum_2;				// ����஫쭠� �㬬� (2)

	DWORD		Jmp;		// spec. program JMP

	BYTE	Jmp_Method;			// ��� ������ JMP
	WORD	Jmp_Data;			// ����� ��� JMP

							};

struct	DB_TSR_RECORD		{			// TSR Data Base definition
	WORD	Type;				//
	BYTE	Name[SIZE_VIRUS_NAME];	// ��� �����

	DWORD		Find;               // program ���᪠ in memory

	BYTE	Find_Method;		// ��⮤ ���᪠ in memory
	WORD	Segment;			// ᥣ���� ��� ADDR

	WORD	Off_1;				// �����
	BYTE	Len_1;				// ᪮�쪮 ����
	DWORD	Sum_1;				// ����஫쭠� �㬬�
	BYTE	Control_Byte;		// ����஫�� ����

	WORD	Off_2;				// ����� ��� ��祭��
	BYTE	Len_2;				// ᪮�쪮 ���� �������� (�� ����� 5) byte
	BYTE	Replace_Bytes[5];	// ����� ��� ������


				};

#pragma pack (pop, pack_records)
