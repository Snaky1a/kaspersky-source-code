unit ZUUE;
// ***************************************************************************
// ******** ���������� ������� ��� ������ � MIME UUE ������������ ********
// ********************** (C) ������ �.�.,2002 �. ****************************
// ***************************************************************************
interface
uses  classes, Sysutils, messages, dialogs, types;

 type
  // ���������� ��� ������ ����������� � �������������
  EUUEError = class(Exception)
  end;

  // 3-� � 4-� ������� ��������� ��� �������� �����������
  TByte3 = packed array[0..2] of byte;
  PByte3 = ^TByte3;
  TByte4 = packed array[0..3] of byte;
  PByte4 = ^TByte4;

  // �������������� 3 ����� --> 4 ������� �� ��������� Base64
  Procedure InternalCodeUUE(AByte3 : TByte3; var AByte4 : TByte4);
  // �������������� 4 ������� Base64 --> 3 ���������� �����
  Procedure InternalDeCodeUUE(AByte4 : TByte4; var AByte3 : TByte3);

  // ***** ������������� ������ *****
  // ����������� ������������� - ��������� ��� ��������� �������������� � �����������
  Function DeCodeStringUUEEx(AInBuffer : AnsiString) : AnsiString;

  // ***** ���������� �������� ������� *****
  // ������ ��������������� ������ (��� ������������ ������, �������� ����� ���� ������ ��-�� "=" � ������, ��������� ������ � �.�.)
  function UUEDecodedSize(const InputSize: Cardinal): Cardinal;
  // ������ ��������������� ������ (��������� ��������� ������ � ������ ����������� ��� ������� ��������� ������)
  function UUEEncodedSize(const InputSize: Cardinal): Cardinal;
implementation

function UUEEncodedSize(const InputSize: Cardinal): Cardinal;
begin
  Result := (InputSize + 2) div 3 * 4;
end;

function UUEDecodedSize(const InputSize: Cardinal): Cardinal;
begin
  Result := (InputSize + 3) div 4 * 3 + (InputSize + 3) div 40;
end;

// �������������� 3 ����� --> 4 ������� �� ��������� Base64
Procedure InternalCodeUUE(AByte3 : TByte3; var AByte4 : TByte4);
begin
end;

Function DeCodeByteUUE(AIn : byte) : byte;
begin
 if AIn  =$60 then Result :=0 else
  Result := AIn - $20;
end;

// �������������� 4 ������� Base64 --> 3 ���������� �����
Procedure InternalDeCodeUUE(AByte4 : TByte4; var AByte3 : TByte3);
begin
 {$R-}
 AByte3[2] := DeCodeByteUUE(AByte4[3]) + (DeCodeByteUUE(AByte4[2]) and $3) shl 6;
 AByte3[1] := DeCodeByteUUE(AByte4[2]) shr 2 + (DeCodeByteUUE(AByte4[1]) and $0F) shl 4;
 AByte3[0] := DeCodeByteUUE(AByte4[1]) shr 4 + (DeCodeByteUUE(AByte4[0]) shl 2);
 {$R+}
end;


// �������������� �������
Function CodeStringBase64(const AInBuffer : AnsiString; CRLFfl : boolean = false) : AnsiString;
begin
 // ����������� ������ ������
 if AInBuffer = '' then begin
  Result := '';
  exit;
 end;
 // ��������� ������ ������
 SetLength(Result, UUEEncodedSize(length(AInBuffer)));
 // �����������
// CodeBufferBase64(AInBuffer[1], length(AInBuffer), Result[1]);
end;

//
Function DeCodeStringUUEEx(AInBuffer : AnsiString) : AnsiString;
var
 Poz,  EndPoz, Size,
 OutPoz, LineOutPoz       : Cardinal;
 Byte4        : TByte4;
 Byte4dword   : dword absolute Byte4;
 Byte4Poz     : byte;
 LineLen      : integer;
 LineEnd      : integer;
 i            : integer;
begin
 {$R-}{$I-}
 Result := '';
 Poz := pos('begin', AInBuffer);
 if Poz = 0 then exit;
 // ������ ������� ������� ������
 SetLength(Result, UUEDecodedSize(length(AInBuffer)));
 // ���������� ������� � ����������
 poz    := Cardinal(@AInBuffer[1]) + poz + 5;
 OutPoz := Cardinal(@Result[1]);
 Size   := Length(AInBuffer);
 EndPoz := Poz + Size;
 Byte4Poz := 0;
 // ���� �������������
 while Poz < EndPoz do begin
  // ������� ���� �������� ����� �������� ������
  if pbyte(pointer(Poz))^ <> $0D then begin inc(Poz); Continue; end;
  inc(Poz); // ������� ������� 0D
  if pbyte(pointer(Poz))^ =  $0A then begin
   inc(Poz); // ������� ������� 0A
   if Poz < EndPoz then begin
    // ��� "End" ??
    if (pbyte(pointer(Poz))^ in [byte('e'), byte('E')]) and (pbyte(pointer(Poz+1))^ = byte('n')) then  break;
    // ������ ������ ���� - ��� ������ ������
    LineLen := DeCodeByteUUE(pbyte(pointer(Poz))^);
    inc(Poz);
    if LineLen = 0 then  continue;
    LineEnd :=  LineLen  div 3 * 4 + Poz;
    Byte4Poz := 0;
    LineOutPoz := 0;
    while LineOutPoz < LineLen do begin
     Byte4[Byte4Poz] := pbyte(pointer(Poz))^;
     inc(Poz);
     inc(Byte4Poz);
     if Byte4Poz = 4 then begin
      InternalDeCodeUUE(Byte4, PByte3(pointer(OutPoz))^);
      inc(OutPoz, 3);
      inc(LineOutPoz, 3);
      Byte4Poz := 0;
     end;
    end;
    if LineOutPoz > LineLen then
     OutPoz := OutPoz - (LineOutPoz - LineLen);
    if (Byte4Poz > 0) and (Byte4Poz <> 4) then begin
     for i := Byte4Poz to 3 do
      Byte4[i] := 0;
     InternalDeCodeUUE(Byte4, PByte3(pointer(OutPoz))^);
     inc(OutPoz, LineLen mod 3);
     Byte4Poz := 0;
    end;
   end;
  end;
 end;
 SetLength(Result, OutPoz - Cardinal(@Result[1]));
 {$R+}{$I+}
end;

end.


