unit zVBAMacros;

interface
uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Spin;

type
 // ��������� ������� VBA
 TVBAProjectHeader = packed record
   Sign     : word;                        // ��������� (������ ���� CC 61)
   Version  : packed array [1..4] of byte; // ������
   Sign1    : word;                        // ��������� (������ ���� 00 FF)
   LidA     : DWORD;
   LidB     : DWORD;
   CodePage : word;                        // ������� ��������
   LenA     : word;
   UnknownB : DWORD;
   UnknownC : DWORD;
   LenB     : word;
   LenC     : word;
   LenD     : word;
 end;

 TMacroDescr = record
  Name : string;     // ��� �������
  Rel  : integer;    // �������� ������ ������� �� ������ ������
 end;

 // ����� ��� ������ � ����������
 TOfficeMacros = class
  public
   // ������� ��������
   MacrosList : array of TMacroDescr;
   procedure AddDebug(s : string);
   // ������������ ������� �� ��������� ������, ������� � ��������� ��������
   function DecompressVBA(FS : TStream; rel: word): string;
   // ������� � ������ ���������
   function ParseVBAProjectHeader(FS: TStream): boolean;
   // �����������
   constructor Create;
 end;

implementation

const VBA_COMPRESSION_WINDOW = 4096;

function vba_endian_convert_16(value : word; is_mac : boolean) : word;
begin
 // return ((value >> 8) + (value << 8));
 Result := Swap(value);
 Result := value shr 8 + value shl 8;
 Result := value;
end;

procedure TOfficeMacros.AddDebug(s: string);
begin
 ;
end;

constructor TOfficeMacros.Create;
begin
 MacrosList := nil;
end;

function TOfficeMacros.DecompressVBA(FS : TStream; rel : word) : string;
var
 i, poz, shift, win_pos, mask, distance : word;
 clean : boolean;
 flag : byte;
 token, len : word;
 buffer : array [0..VBA_COMPRESSION_WINDOW] of char;
 srcpos : integer;
 c : char;
begin
 poz := 0;
 clean := true;
 Result := '';
 // ������� ������
 ZeroMemory(@buffer, VBA_COMPRESSION_WINDOW);
 FS.Seek(rel, soFromCurrent);
 FS.Seek(+3, soFromCurrent);
 while true do begin
  // ������ ������
  if FS.Read(flag, 1) <> 1 then Break;
  // ����
  mask := 1;
  while mask < $100 do begin
   if (flag and mask) > 0 then begin
    // ������ ������ � �����, ���� ������
    if FS.Read(token, 2) <> 2 then exit;
    token := vba_endian_convert_16(token, false);
    win_pos := poz mod VBA_COMPRESSION_WINDOW;
    if win_pos <= $80 then begin
      if win_pos <= $20 then begin
       if win_pos <= $10 then shift := 12 else shift := 11;
      end else
       if win_pos <= $40 then shift := 10 else shift := 9;
    end else begin
      if win_pos <= $200 then begin
       if win_pos <= $100 then shift := 8 else shift := 7;
      end else
      if win_pos <= $800 then begin
       if win_pos <= $400 then shift := 6 else shift := 5;
      end else
       shift := 4;
    end;
    len        := (token and ((1 shl shift)-1)) + 3;
    distance   := (token shr shift);
    clean := true;
    for i := 0 to len - 1 do begin
     srcpos := (poz - distance - 1) mod VBA_COMPRESSION_WINDOW;
     c := buffer[srcpos];
     buffer[poz mod VBA_COMPRESSION_WINDOW] := c;
     inc(poz);
    end;
   end else begin
    if (poz <> 0) and (poz mod VBA_COMPRESSION_WINDOW = 0) and clean then begin
     if FS.Read(token, 2) <> 2 then exit;
     clean := false;
     // ���������� �������  � ����������
     Result := Result + copy(buffer,1, VBA_COMPRESSION_WINDOW);
     break;
    end;
    if FS.Read(buffer[poz mod VBA_COMPRESSION_WINDOW], 1) = 1 then
     inc(poz);
    clean := true;
   end;
   // ����� �� 1 ��� �����
   mask := (mask shl 1);
  end;
 end;
 Result := Result + copy(buffer,1, VBA_COMPRESSION_WINDOW);
end;

function TOfficeMacros.ParseVBAProjectHeader(FS : TStream): boolean;
var
 i : integer;
 VBAProjectHeader : TVBAProjectHeader;
 len, ooff, RecordCount : word;
 buf, name : array[0..6000] of char;
 CodeRel : dword;
 BlocksCount : byte;

 // ����� "����������" ������������������ ������� 20 ����, ������� ����� �������������� ����� ��������
 // (� ������������ - ������ ����� ����� ������, �� � ���� ���������� � �� �� �������� ������)
 function vba56_test_middle : boolean;
 var
  buf : packed array[0..20] of byte;
 const
  // ��������� ��� MS Office
  SIGN_MSOffice : packed array[0..19] of byte = ($00, $00, $e1, $2e, $45, $0d, $8f, $e0, $1a, $10,
                                                  $85, $2e, $02, $60, $8c, $4d, $0b, $b4, $00, $00);
  // ��������� ��� Mac Office
  SIGN_MacOffice : packed array[0..19] of byte = ($00, $01, $0d, $45, $2e, $e1, $e0, $8f, $10, $1a,
                                                  $85, $2e, $02, $60, $8c, $4d, $0b, $b4, $00, $00);
 begin
   FS.Read(buf, 20);
   // ��������� ������ � ����������� - ���� �������, �� ����������
   if not(CompareMem(@buf, @SIGN_MSOffice, 20)) and not(CompareMem(@buf, @SIGN_MacOffice, 20)) then begin
    FS.Seek(-20, soFromCurrent);
   end else
    AddDebug('������� ����� 20 ���� - "���������� ����"');
   Result := true;
 end;
 function ReadProhectStrings : boolean;
 var
  len : word;
  buf, name : array[0..6000] of char;
 begin
  AddDebug('������ ������ �����');
  while true do begin
   // ������ ������
   FS.Read(len, 2);
   if len < 6 then begin
    FS.Seek(-2, soFromCurrent);
    break;
   end;
   // ������ ������
   FS.Read(buf, len);
   UnicodeToUtf8(name, 6000, @buf, len);
   AddDebug('-->������� ��� '+copy(name, 1, len div 2));
   // �������� ���� ������
   if (copy(name, 1, 3) = '*\G') or (copy(name, 1, 3) = '*\H') or
      (copy(name, 1, 3) = '*\C') or (copy(name, 1, 3) = '*\D') then begin
        FS.Read(len, 2);
        if (len <> 0) and not(len > 2000) then begin
         FS.Seek(-2, soFromCurrent);
         continue;
        end;
        FS.Read(buf, 10);
    end else begin
     // ����������� ��� ������ (����������� �������)
     FS.Seek(-(len+2), soFromCurrent);
     break;
    end;
    vba56_test_middle;
  end;
 end;
begin
 Result     := false;
 MacrosList := nil;
 // ����������� ���������
 FS.Read(VBAProjectHeader, sizeof(TVBAProjectHeader));
 AddDebug('��������� 1 = '+IntToHex(VBAProjectHeader.Sign, 2));
 AddDebug('��������� 2 = '+IntToHex(VBAProjectHeader.Sign1, 2));
 AddDebug('������� �������� = '+IntToStr(VBAProjectHeader.CodePage));
 // ������ ���� ��������� �����
 ReadProhectStrings;
 // ����� �������� ���������� ���� ��������� �����
 i := 0;
 repeat
  FS.Read(ooff, 2);
  inc(i);
 until (ooff = $FFFF) or (i > 1024);
 // ������� ������� ������� ���� - �����
 if i > 1024 then exit;
 // �������� ������������
 FS.Seek(-3, soFromCurrent);
 FS.Read(ooff, 2);
 // ��� ������������ - ��������� �� ���� ������
 if ooff <> $FFFF then
  FS.Seek(1, soFromCurrent);
 // ������ 2 �����
 FS.Read(ooff, 2);
 if ooff <> $FFFF then
  FS.Seek(ooff, soFromCurrent);
 FS.Read(ooff, 2);
 if ooff <> $FFFF then
  FS.Seek(ooff, soFromCurrent);
 FS.Seek(100, soFromCurrent);
 FS.Read(RecordCount, 2);
 AddDebug('���������� ������� � VBA ������� = '+IntToStr(RecordCount));
 if RecordCount <= 0 then exit;
 // ���� ������� �������
 for i := 0 to RecordCount-1 do begin
  SetLength(MacrosList, Length(MacrosList)+1);
  FS.Read(len, 2);
  FS.Read(buf, len);
  UnicodeToUtf8(name, 6000, @buf, len);
  AddDebug('-->������� ��� '+copy(name, 1, len div 2));
  MacrosList[Length(MacrosList)-1].Name := copy(name, 1, len div 2);
  // ��� ������
  FS.Read(len, 2);
  FS.Seek(len, soFromCurrent);
  // ���-��
  FS.Read(ooff, 2);
  if ooff = $FFFF then begin
   FS.Read(ooff, 2);
   FS.Read(ooff, 2);
   FS.Seek(ooff, soFromCurrent);
  end else
   FS.Seek(2+ooff, soFromCurrent);
  // ����� ����� 8 ����
  FS.Seek(8, soFromCurrent);
  // ���-�� ������ �� 8 ����
  FS.Read(BlocksCount, 1);
  FS.Seek(8*BlocksCount, soFromCurrent);
  // ����� ����� 6 ����
  FS.Seek(6, soFromCurrent);
  FS.Read(CodeRel, 4);
  AddDebug('   �������� = '+IntToStr(CodeRel));
  FS.Seek(2, soFromCurrent);
  MacrosList[Length(MacrosList)-1].Rel  := CodeRel;
 end;
end;

end.
