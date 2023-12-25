unit MonFunct;

interface
uses Types, Windows;

const
 // ����������������� ���� (���������� ������������)
 CriptKey1 : array[0..16] of byte = ($53, $7F, $22, $FE, $0D, $79, $31, $24, $04, $9B, $15, $83, $D2, $6F, $1D, $B0, $4A);
 (* ****** ��������� �������� ������ ***
  0     Z \
  1     M  > ��������� ��� ��������� �������
  2     A /
  3     ����� ������ (������ ����)
  4     ����� ������ (������ ����)
  5     ����������� �����
  6     ����������� �����
  7     ����������� �����
  8     ����������� �����
  9     ������� �����, ��������� ���������� ���������� (����������� ���. ��������)
  A     ������
  B     ������
  C     ���. ���� (4 �����, ������������ ���������� �������� ��� ��������� ��������� � �������)
  D     ���. ����
  E     ���. ����
  F     ���. ����
  10 ... ������
  ------------
  ������� �����:
   0    ���-�� ���, �� ������� ������� ��������� ���� ����� (0-��� ��������)
   1    ���-�� ���, �� ������� ������� ��������� ���� ����� (0-��� ��������)
   2    ���-�� ���, �� ������� ������� ��������� ���� ����� (0-��� ��������)
   3    ���-�� ���, �� ������� ������� ��������� ���� ����� (0-��� ��������)
   4
   5
   6
   7    �������� �����
 *)
type
 TMonitoringNETBuffer = packed array of char;
 // ������������ �����
 Function DecodeBuffer(var Buf  : TMonitoringNETBuffer) : boolean;
 // ���������� �����
 Function EncodeBuffer(var Buf  : TMonitoringNETBuffer) : boolean;
 // ����������� ������ ��� ��������
 Function PrepareBufferToSend(S : String; var Buf  : TMonitoringNETBuffer) : boolean;
implementation

// ������������ �����
Function DecodeBuffer(var Buf  : TMonitoringNETBuffer) : boolean;
var
 i : integer;
 CurByte : byte;
 RollKey : byte;
begin
 for i := $10 to Length(Buf)-1 do begin
  CurByte := ord(Buf[i]);
  // �������� XOR � ������
  CurByte := CurByte xor byte(buf[12 + i mod 4]);
  // �������� ��������
  if byte(Buf[9]) and $80 > 0 then
   CurByte := not CurByte;
  // �������� �������� �����
  RollKey := byte(Buf[9]) and $07;
  if RollKey > 0 then
   asm
    mov cl, RollKey
    rol CurByte, cl;
   end;
  // ���������� ������� ����
  CurByte := CurByte xor CriptKey1[i mod $0F];
  // ����������� ����������
  Buf[i]  := Chr(CurByte);
 end;
end;

// ���������� �����
Function EncodeBuffer(var Buf  : TMonitoringNETBuffer) : boolean;
var
 i : integer;
 CurByte : byte;
 RollKey : byte;
begin
 for i := $10 to Length(Buf)-1 do begin
  CurByte := ord(Buf[i]);
  // ���������� ������� ����
  CurByte := CurByte xor CriptKey1[i mod $0F];
  // �������� �������� �����
  RollKey := byte(Buf[9]) and $07;
  if RollKey > 0 then
   asm
    mov cl, RollKey
    ror CurByte, cl;
   end;
  // �������� ��������
  if byte(Buf[9]) and $80 > 0 then
   CurByte := not CurByte;
  // �������� XOR � ������
  CurByte := CurByte xor byte(buf[12 + i mod 4]);
  // ����������� ����������
  Buf[i]  := Chr(CurByte);
 end;
end;

// ����������� ������ ��� ��������
Function PrepareBufferToSend(S : String; var Buf  : TMonitoringNETBuffer) : boolean;
var
 i : integer;
 CRC : DWORD;
 CRC_bytes : packed array[1..4] of byte absolute CRC;
 DataSize, ResLength : word;
 DataSize_bytes : packed array[1..2] of byte absolute DataSize;
begin
 // ��������� ������ ��� �����
 SetLength(Buf, Length(S) + $10);
 // ������� ������
 ZeroMemory(@Buf[0], Length(Buf));
 // ������ ���������
 Buf[0] := 'Z'; Buf[1] := 'M'; Buf[2] := 'A';
 // ������ ������
 for i := 1 to length(s) do
  buf[i+$0F] := s[i];
 // ������ ������
 DataSize   := length(s);
 ResLength  := DataSize+$10;
 Buf[3] := chr(DataSize_Bytes[1]);
 Buf[4] := chr(DataSize_Bytes[2]);
 // �������� ���� ���������� (��� ������� �� ����� � ���. ���������� �����)
 Randomize;
 Buf[9] := chr(byte(random(255)));
 Buf[9] := char(3);
 Buf[12] := chr(byte(random(255)));
 Buf[13] := chr(byte(random(255)));
 Buf[14] := chr(byte(random(255)));
 Buf[15] := chr(byte(random(255)));
 // ����������
 MonFunct.EncodeBuffer(Buf);
 // ������ CRC
 CRC := 0;
 for i := 0 to ResLength-1 do
  CRC := CRC + i*ord(buf[i]);
 // ������ CRC
 for i := 1 to 4 do
  buf[i+4] := chr(CRC_bytes[i]);
 Result := true;
end;

end.
