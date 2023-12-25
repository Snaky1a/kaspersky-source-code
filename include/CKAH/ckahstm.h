#ifndef __CKAHSTM_H__
#define __CKAHSTM_H__

// Stealth Mode
namespace CKAHSTM
{
	typedef LPVOID HSTMNETLIST;

	struct StmNet {
        CKAHUM::IP Net;
		CKAHUM::IP Mask;
	};

	// ��������� Stealth Mode
	CKAHUMMETHOD Start ();

	// ������������� Stealth Mode
	CKAHUMMETHOD Stop ();

	// ���������������� Stealth Mode (��� ������� ������ �������������)
	CKAHUMMETHOD Pause ();

	// ������������ ������ Stealth Mode (��� ������� ������ �������������)
	CKAHUMMETHOD Resume ();

	// ��������� ��������� � ��������� Mac-������� � ����� Stealth.
	// Mode : true - Stealthed, false - Unstealthed
	// ��-��������� stealth-mode ��������� �� ��� ����������.
	CKAHUMMETHOD SetStealth(char MacAddr[6], bool Mode);

	// �������� unstealthed ����
	CKAHUMMETHOD AddNet( StmNet* pNet );

	// ������� unstealthed ����
	CKAHUMMETHOD RemoveNet( StmNet* pNet );

	// �������� ������ unstealthed ��������
	CKAHUMMETHOD GetNetList( HSTMNETLIST* phList );

	// �������� ������ ������
	CKAHUMMETHOD NetList_GetSize( HSTMNETLIST hList, int* psize);

	// �������� ������� ������.
	CKAHUMMETHOD NetList_GetItem( HSTMNETLIST hList, int n, StmNet* pNet );

	// ������� ������ � ���������� �������
	CKAHUMMETHOD NetList_Delete(  HSTMNETLIST hList );
	
	// ���������� ��������� ��������� ��� �����
	// ���� true, �� Stm ����� ����������� ������ � ����������� ��������.
	// ���� false, �� Stm ����� ����������� �����, ����� ����������� �����.
	// �� ���������, �.�. ���� ������ �� ����������, �� ��������� �������� false.
	CKAHUMMETHOD SetNetDefaultReaction( bool NetUsesStm );
};


#endif