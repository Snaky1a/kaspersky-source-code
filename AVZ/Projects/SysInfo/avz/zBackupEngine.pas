unit zBackupEngine;
// ������� �������� ��������� �����
interface
uses windows, registry, Classes,
  zCRC32,
  AbArcTyp,
  AbZipTyp,
  AbUnzPrc,
  AbDfBase,
  AbDfEnc,
  AbDfDec;
const
 // ���� ������ ��� ������
 brtCreateKey                = 1; // ������� ����
 brtDeleteParam              = 2; // ������� ��������
 brtSetParamValREG_DWORD     = 3; // ������� �������� � ������ ��� ��������. ��� ��������� REG_DWORD
 brtSetParamValREG_SZ        = 4; // ������� �������� � ������ ��� ��������. ��� ��������� REG_SZ
 brtSetParamValREG_EXPAND_SZ = 5; // ������� �������� � ������ ��� ��������. ��� ��������� REG_EXPAND_SZ
 brtSetParamValREG_MULTI_SZ  = 6; // ������� �������� � ������ ��� ��������. ��� ��������� REG_MULTY_SZ
 brtSetParamValREG_BINARY    = 7; // ������� �������� � ������ ��� ��������. ��� ��������� REG_BINARY
 // ������ ������ ���������� ����
 CodeArray      : array [0..1, 0..$0F] of byte = ((0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
                                                 (115,25,67,51,134,92,210,111,6,35,197,241,19,125,230,72));
type
 // ������ � ���� ������
 TBackupRec = class
  RecType  : word;   // ��� ���� ��������
  X1, X2, X3, X4 : string; // ������. ������������� X* ������� �� RecType
 end;
 // ��������� ���� ������
 TBackupFileHeader = packed record
  Sign           : packed array [1..6] of char; // ��������� BACKUP
  DateTime       : TDateTime;                   // ���� � ����� �������� ����
  MinAvzVersion  : Real48;                      // ��� ������ ���� (��� �������������)
  RecCount       : Longint;                     // ���������� ������� � ���� ������ ���� 1
  CRC            : DWORD;                       // ����������� ����� ����� �����
  code_num       : byte;                        // ���� ��� ���. �����������
 end;
 // �����, �������������� ��������� ������
 TZBackupEngine = class
  private
    FBackupId: string;
    procedure SetBackupId(const Value: string);
  public
   // ����� ��� ������ � ��������
   Reg : TRegistry;
   // ���� ������
   BackupDB : TStringList;
   // ��������/���������� ������
   constructor Create;
   destructor Destroy; override;
   // ������� ����
   function ClearDB : boolean;
   // �������� ���� ������
   function LoadBackupDB(AStream : TMemoryStream) : boolean;
   // ���������� ���� ������
   function SaveBackupDB(AStream : TMemoryStream) : boolean;
   // ���������� ������ (ADeleteItems - �������� ��������� �� ���� ������ ����� ����������)
   function UndoChanges(ABackupId : string; ADeleteItems : boolean = true) : boolean;
   // ��������, ���������� �� ����� ��� ������� ID
   function BackUpExists(ABackupId : string) : boolean;
   // �������� ������� ���� �� ��������� � �������� ID �� ����
   function DeleteChanges(ABackupId : string) : boolean;
   // �������� ��������
   function DeleteItem(AIndx : integer) : boolean;
   // ���������� �������� (������ �������� ����������� �������)
   function AddItem(ARecType : word; ABackupId, AX1, AX2, AX3, AX4 : string) : boolean;
   // ���������� �������� (������ ����������� �� ������)
   function AddItemFromStream(AStream : TStream) : boolean;
   // ���������� �������� � �����
   function SaveItemToStream(AStream : TStream; ABackupId : string; AItem : TBackupRec) : boolean;
   // ���������� ������ � �����
   function SaveStringToStream(AStream : TStream; S : string) : boolean;
   // �������� ������ �� ������
   function LoadStringFromStream(AStream : TStream; var S : string) : boolean;
   // ****** ���������� ������� � ���� ******
   function AddBackupDeleteKey(ARoot, AKey : string) : boolean;
   function AddBackupDeleteParam(ARoot, AKey, AParamName : string) : boolean;
   function AddBackupChangeParam(ARoot, AKey, AParamName : string) : boolean;
   // ��������� ����� ����� � ���� ������
   function BackupRegKey(ARoot, AKey : string) : boolean;
   // ************ ��������������� ������� ***********
   // ��������� RootKey ������ ������ � �������� �� �����
   function SetRootKeyByName(Reg : TRegistry; AName : string) : boolean;
 published
   property BackupId : string read FBackupId write SetBackupId;
 end;
implementation
uses Math, SysUtils, zutil, zSharedFunctions;

// ������������ �������� ������ (���������� � ������������)
Function DecodeBinData(MS : TMemoryStream) : boolean;
var
 i, ResSize : integer;
 w : word;
 b : byte;
 VirusBaseHeader : TBackupFileHeader;
 CRC, HeaderCRC : DWORD;
 AbDeflateHelper : TAbDeflateHelper;
 PackedStream, UnpackedStream : TMemoryStream;
begin
 Result := false;
 {$R-}
 // ������ ���������
 MS.Seek(0,0);
 MS.Read(VirusBaseHeader, sizeof(VirusBaseHeader));
 // ������ ��������� � CRC = 0
 MS.Seek(0,0);
 HeaderCRC := VirusBaseHeader.CRC;
 VirusBaseHeader.CRC := 0;
 MS.Write(VirusBaseHeader, sizeof(VirusBaseHeader));
 MS.Seek(0,0);
 CRC := 0;
 // ���� ������������� ������
 for i := sizeof(TBackupFileHeader) to MS.Size - 1 do begin
  w := word(i + i*5 + i*i div 3 + VirusBaseHeader.code_num * 8 + 219);
  b := byte( Pointer(Longint(MS.Memory) + i)^ );
  CRC := DWORD(CRC + b * i);
  b := byte(not(b xor w));
  b := b xor CodeArray[1, i mod $0F];
  asm rol b, 3 end;
  ResSize := 1;
  Move(b, Pointer(Longint(MS.Memory) + i)^, ResSize);
 end;
 // ���� ������� CRC ���������
 for i := 0 to sizeof(TBackupFileHeader) - 1 do begin
  b := byte( Pointer(Longint(MS.Memory) + i)^ );
  CRC := CRC + b * i;
 end;
 Result := CRC = HeaderCRC;
 if Result then begin
  PackedStream := nil; UnPackedStream := nil; AbDeflateHelper := nil;
  try
    try
     // �������� �������� � �������
     PackedStream    := TMemoryStream.Create;
     UnPackedStream  := TMemoryStream.Create;
     AbDeflateHelper := TAbDeflateHelper.Create;
     // ����������� ������ � �����
     MS.Seek(SizeOf(VirusBaseHeader), 0);
     PackedStream.CopyFrom(MS, MS.Size - SizeOf(VirusBaseHeader));
     // ����������
     PackedStream.Seek(0,0); UnPackedStream.Seek(0,0);
     Inflate(PackedStream, UnPackedStream, AbDeflateHelper);
     MS.SetSize(SizeOf(VirusBaseHeader));
     UnPackedStream.Seek(0,0);
     MS.CopyFrom(UnPackedStream, UnPackedStream.Size);
    finally
     AbDeflateHelper.Free;
     UnPackedStream.Free;
     PackedStream.Free;
    end;
  except
   Result := false;
  end;
 end;
 {$R+}
end;

// ���������� (�������� + ���������)
function CodeBinData(MS: TMemoryStream) : boolean;
var
 i, ResSize : integer;
 w : word;
 b : byte;
 VirusBaseHeader : TBackupFileHeader;
 AbDeflateHelper : TAbDeflateHelper;
 PackedStream, UnpackedStream : TMemoryStream;
begin
 Result := false;
 {$R-}
 // �������� ������ � �����
 MS.Seek(0,0);
 MS.Read(VirusBaseHeader, SizeOf(VirusBaseHeader));
 // �������� �������� � �������
 PackedStream    := TMemoryStream.Create;
 UnPackedStream  := TMemoryStream.Create;
 AbDeflateHelper := TAbDeflateHelper.Create;
 AbDeflateHelper.PKZipOption := 'x';
 // ����������� ������ � �����
 UnPackedStream.CopyFrom(MS, MS.Size - SizeOf(VirusBaseHeader));
 // ������
 UnpackedStream.Seek(0,0); PackedStream.Seek(0,0);
 Deflate(UnpackedStream, PackedStream, AbDeflateHelper);
 PackedStream.Seek(0,0);
 MS.SetSize(0);
 VirusBaseHeader.CRC := 0;
 MS.Write(VirusBaseHeader,  SizeOf(VirusBaseHeader));
 PackedStream.Seek(0,0);
 MS.CopyFrom(PackedStream, PackedStream.Size);
 // ���������� ������� � ����������� ������
 PackedStream.Free;
 UnPackedStream.Free;
 AbDeflateHelper.Free;
 // ���� ����������� ������
 for i := sizeof(TBackupFileHeader) to MS.Size - 1 do begin
  b := byte( Pointer(Longint(MS.Memory) + i)^ );
  asm ror b, 3 end;
  w := i + i*5 + i*i div 3 + VirusBaseHeader.code_num * 8 + 219;
  b := b xor CodeArray[1, i mod $0F];
  b := (not b) xor w;
  ResSize := 1;
  Move(b, Pointer(Longint(MS.Memory) + i)^, ResSize);
 end;
 VirusBaseHeader.CRC := 0;
 for i := 0 to MS.Size - 1 do
  VirusBaseHeader.CRC := DWORD(VirusBaseHeader.CRC + byte( Pointer(Longint(MS.Memory) + i)^ ) * i);
 MS.Seek(0,0);
 MS.Write(VirusBaseHeader, SizeOf(VirusBaseHeader));
 MS.Seek(0,0);
 Result := true;
 {$R+}
end;

{ TZBackupEngine }

function TZBackupEngine.AddBackupChangeParam(ARoot, AKey,
  AParamName: string): boolean;
var
 j     : integer;
 ST    : string;
 DataType, DataSize: Integer;
begin
 Result := false;
 if not SetRootKeyByName(Reg, ARoot) then exit;
 if AKey = '' then exit;
 try
   // ������� ������� ����
   if Reg.OpenKey(AKey, false) then begin
    // �������� ����������
    if Reg.ValueExists(AParamName) then begin
     case Reg.GetDataType(AParamName) of
      rdString       : AddItem(brtSetParamValREG_SZ, BackupId, ARoot, AKey, AParamName, Reg.ReadString(AParamName));
      rdExpandString : AddItem(brtSetParamValREG_EXPAND_SZ, BackupId, ARoot, AKey, AParamName, Reg.ReadString(AParamName));
      rdInteger      : AddItem(brtSetParamValREG_DWORD, BackupId, ARoot, AKey, AParamName, Reg.ReadString(AParamName));
      rdBinary,
      rdUnknown      : begin
                       DataSize := Reg.GetDataSize(AParamName);
                       SetLength(ST, DataSize);
                       if DataSize > 0 then begin
                        j := Reg.ReadBinaryData(AParamName, ST[1], Length(ST));
                        SetLength(ST, j);
                       end;
                        if (RegQueryValueEx(Reg.CurrentKey, PChar(AParamName), nil, @DataType, nil,
                           @DataSize) = ERROR_SUCCESS) and (DataType = REG_MULTI_SZ) then
                            AddItem(brtSetParamValREG_MULTI_SZ, BackupId, ARoot, AKey, AParamName, ST)
                             else AddItem(brtSetParamValREG_BINARY, BackupId, ARoot, AKey, AParamName, ST);
                       end;
     end;
    end else
     AddItem(brtDeleteParam, BackupId, ARoot, AKey, AParamName, ST); // ����� �������� �� ����������� - ������ ��� ��� ������
    Reg.CloseKey;
   end;
 except
  Result := false;
 end;
end;

function TZBackupEngine.AddBackupDeleteKey(ARoot, AKey: string): boolean;
begin
 Result := false;
 // �������������� root ����� - ��� �������� ����� � ����
 ARoot := StringReplace(ARoot, 'HKEY_LOCAL_MACHINE',  'HKLM', [rfIgnoreCase]);
 ARoot := StringReplace(ARoot, 'HKEY_CLASSES_ROOT',   'HKCR', [rfIgnoreCase]);
 ARoot := StringReplace(ARoot, 'HKEY_CURRENT_USER',   'HKCU', [rfIgnoreCase]);
 ARoot := StringReplace(ARoot, 'HKEY_CURRENT_CONFIG', 'HKCC', [rfIgnoreCase]);
 // ���� ���� ���������� - �������� ��� BackUp
 if SetRootKeyByName(Reg, ARoot) then
  if Reg.KeyExists(AKey) then begin
   BackupRegKey(ARoot, AKey);
  end;
end;

function TZBackupEngine.AddBackupDeleteParam(ARoot, AKey,
  AParamName: string): boolean;
var
 j     : integer;
 ST    : string;
 DataType, DataSize: Integer;
begin
 Result := false;
 if not SetRootKeyByName(Reg, ARoot) then exit;
 if AKey = '' then exit;
 try
   // ������� ������� ����
   if Reg.OpenKey(AKey, false) then begin
    // �������� ����������
    if Reg.ValueExists(AParamName) then begin
     case Reg.GetDataType(AParamName) of
      rdString       : AddItem(brtSetParamValREG_SZ, BackupId, ARoot, AKey, AParamName, Reg.ReadString(AParamName));
      rdExpandString : AddItem(brtSetParamValREG_EXPAND_SZ, BackupId, ARoot, AKey, AParamName, Reg.ReadString(AParamName));
      rdInteger      : AddItem(brtSetParamValREG_DWORD, BackupId, ARoot, AKey, AParamName, Reg.ReadString(AParamName));
      rdBinary,
      rdUnknown      : begin
                       DataSize := Reg.GetDataSize(AParamName);
                       SetLength(ST, DataSize);
                       if DataSize > 0 then begin
                        j := Reg.ReadBinaryData(AParamName, ST[1], Length(ST));
                        SetLength(ST, j);
                       end;
                        if (RegQueryValueEx(Reg.CurrentKey, PChar(AParamName), nil, @DataType, nil,
                           @DataSize) = ERROR_SUCCESS) and (DataType = REG_MULTI_SZ) then
                            AddItem(brtSetParamValREG_MULTI_SZ, BackupId, ARoot, AKey, AParamName, ST)
                             else AddItem(brtSetParamValREG_BINARY, BackupId, ARoot, AKey, AParamName, ST);
                       end;
     end;
    end;
    Reg.CloseKey;
   end;
 except
  Result := false;
 end;
end;

// ���������� �������� (������ �������� ����������� �������)
function TZBackupEngine.AddItem(ARecType: word; ABackupId, AX1, AX2, AX3,
  AX4: string): boolean;
var
 Tmp : TBackupRec;
begin
 Result := false;
 // ���������� �������������� (������� �������, ������� � ������ � ����� �� ���������)
 ABackupId := Trim(UpperCase(ABackupId));
 // �������� ������-��������� �������
 Tmp := TBackupRec.Create;
 // ���������� �����
 with Tmp do begin
  RecType  := ARecType;
  X1       := AX1;
  X2       := AX2;
  X3       := AX3;
  X4       := AX4;
 end;
 // ���������� �������� � ����
 BackupDB.AddObject(ABackupId, Tmp);
 Result := true;
end;

// ���������� �������� (������ ����������� �� ������)
function TZBackupEngine.AddItemFromStream(AStream: TStream): boolean;
var
 W   : word;
 Tmp : TBackupRec;
 S   : string;
begin
 Result := false;
 W := 0;
 // ������ ���� ���� ������
 if AStream.Read(W, 2) <> 2 then exit;
 // ������ �������������
 if not(LoadStringFromStream(AStream, S)) then exit;
 Tmp := TBackupRec.Create;
 Tmp.RecType  := W;
 // �������� ������
 LoadStringFromStream(AStream, Tmp.X1);
 LoadStringFromStream(AStream, Tmp.X2);
 LoadStringFromStream(AStream, Tmp.X3);
 LoadStringFromStream(AStream, Tmp.X4);
 // ���������� ������� � ����
 BackupDB.AddObject(S, Tmp);
end;

// ��������, ���������� �� ����� ��� ������� ID
function TZBackupEngine.BackUpExists(ABackupId: string): boolean;
var
 i : integer;
begin
 Result := false;
 ABackupId := Trim(UpperCase(ABackupId));
 if ABackupId = '' then exit;
 for i := 0 to BackupDB.Count - 1 do
  if BackupDB[i] = ABackupId then begin
   Result := true;
   exit;
  end;
end;

// ��������� ����� ����� � ���� ������
function TZBackupEngine.BackupRegKey(ARoot, AKey: string): boolean;
var
 Lines : TStringList;
 i,j   : integer;
 ST    : string;
 DataType, DataSize: Integer;
 Reg   : TRegistry;
begin
 Result := false;
 if AKey = '' then exit;
 Lines := TStringList.Create;
 Reg   := TRegistry.Create;
 try
  if not SetRootKeyByName(Reg, ARoot) then exit;
  // �������� ������� ��� �����
  if Reg.OpenKey(AKey, false) then begin
   // �������� ������ ������ ������ �����
   AddItem(brtCreateKey, BackupId, ARoot, AKey, '', '');
   // ************ BackUp ���������� *************
   // �������� ������ ����������
   Lines.Clear;
   Reg.GetValueNames(Lines);
   for i := 0 to Lines.Count - 1 do begin
    case Reg.GetDataType(Lines[i]) of
     rdString       : AddItem(brtSetParamValREG_SZ, BackupId, ARoot, AKey, Lines[i], Reg.ReadString(Lines[i]));
     rdExpandString : AddItem(brtSetParamValREG_EXPAND_SZ, BackupId, ARoot, AKey, Lines[i], Reg.ReadString(Lines[i]));
     rdInteger      : AddItem(brtSetParamValREG_DWORD, BackupId, ARoot, AKey, Lines[i], Inttostr(Reg.ReadInteger(Lines[i])));
     rdBinary,
     rdUnknown      : begin
                       DataSize := Reg.GetDataSize(Lines[i]);
                       SetLength(ST, DataSize);
                       if DataSize > 0 then begin
                        j := Reg.ReadBinaryData(Lines[i], ST[1], Length(ST));
                        SetLength(ST, j);
                       end;
                       if (RegQueryValueEx(Reg.CurrentKey, PChar(Lines[i]), nil, @DataType, nil,
                          @DataSize) = ERROR_SUCCESS) and (DataType = REG_MULTI_SZ) then
                           AddItem(brtSetParamValREG_MULTI_SZ, BackupId, ARoot, AKey, Lines[i], ST)
                            else AddItem(brtSetParamValREG_BINARY, BackupId, ARoot, AKey, Lines[i], ST);
                      end;
    end;
   end;
   // ************* BackUp ��������� ������ ******
   // �������� ������ ��������� ������
   Lines.Clear;
   Reg.GetKeyNames(Lines);
   if not(AKey[length(AKey)] in ['\', '/']) then
    AKey := AKey + '\';
   for i := 0 to Lines.Count - 1 do
    BackupRegKey(ARoot, AKey + Lines[i]);
   Reg.CloseKey;
  end;
 finally
  Lines.Free;
  Reg.Free;
 end;
 Result := true;
end;

// ������� ����
function TZBackupEngine.ClearDB: boolean;
var
 i : integer;
begin
 Result := false;
 // ������� �������, �������� ������ ������
 for i := 0 to BackupDB.Count - 1 do
  if BackupDB.Objects[i] <> nil then begin
   if BackupDB.Objects[i] is TBackupRec then
    (BackupDB.Objects[i] as TBackupRec).Free;
   BackupDB.Objects[i] := nil;
  end;
 // ������� ������ �������
 BackupDB.Clear;
 Result := true;
end;

constructor TZBackupEngine.Create;
begin
 BackupDB := TStringList.Create;
 Reg      := TRegistry.Create;
end;

function TZBackupEngine.DeleteChanges(ABackupId: string): boolean;
var
 i : integer;
begin
 Result := false;
 i := 0;
 ABackupId := Trim(UpperCase(ABackupId));
 // ���� �������� ��������� � �������� ID
 while i < BackupDB.Count do begin
  if BackupDB[i] = ABackupId then
   DeleteItem(i)
    else inc(i);
 end;
 Result := true;
end;

function TZBackupEngine.DeleteItem(AIndx: integer): boolean;
begin
 Result := false;
 // �������� �������
 if AIndx < 0 then exit;
 if AIndx >= BackupDB.Count then exit;
 // ������������ ������, ������� ���������
 if BackupDB.Objects[AIndx] is TBackupRec then
  (BackupDB.Objects[AIndx] as TBackupRec).Free;
 BackupDB.Objects[AIndx] := nil;
 // �������� ��������
 BackupDB.Delete(AIndx);
 Result := true;
end;

destructor TZBackupEngine.Destroy;
begin
 // ����������� ������
 ClearDB;
 try Reg.CloseKey; except end;
 Reg.Free;
 BackupDB.Free;
 inherited;
end;

function TZBackupEngine.LoadBackupDB(AStream: TMemoryStream): boolean;
var
 BackupFileHeader : TBackupFileHeader;
 i : integer;
begin
 Result := false;
 // ������� ���� ����� ���������
 ClearDB;
 AStream.Seek(0,0);
 // �������� CRC, �����������, ������������
 if not(DecodeBinData(AStream)) then exit;
 AStream.Seek(0,0);
 // �������� ���������
 AStream.Read(BackupFileHeader, SizeOf(BackupFileHeader));
 // �������� ������
 for i := 0 to BackupFileHeader.RecCount - 1 do begin
  AddItemFromStream(AStream);
 end;
 Result := true;
end;

// �������� ������ �� ������
function TZBackupEngine.LoadStringFromStream(AStream: TStream;
  var S: string): boolean;
var
 W : Word;
begin
 Result := false;
 S := '';
 // �������� ������ ������
 if AStream.Read(W, 2) <> 2 then exit;
 Result := true;
 // ������ ������ ������ 0 ? ���� ��, �� �������� ����� � ��������� ������
 if W > 0 then begin
  SetLength(S, W);
  Result := AStream.Read(S[1], W) = W;
 end;
end;

function TZBackupEngine.SaveBackupDB(AStream: TMemoryStream): boolean;
var
 BackupFileHeader : TBackupFileHeader;
 i   : integer;
begin
 // ������� ������
 AStream.Seek(0,0);
 AStream.Clear;
 AStream.Size := 0;
 AStream.Seek(0,0);
 // ���������� ���������
 BackupFileHeader.Sign := 'BACKUP';
 BackupFileHeader.DateTime := Now;
 BackupFileHeader.MinAvzVersion := 4.18;
 BackupFileHeader.RecCount := BackupDB.Count;
 BackupFileHeader.CRC := 0;
 BackupFileHeader.code_num := Random(255);
 // ������ ���������
 AStream.Write(BackupFileHeader, SizeOf(BackupFileHeader));
 // ������ ������
 for i := 0 to BackupDB.Count - 1 do
  SaveItemToStream(AStream, BackupDB[i], (BackupDB.Objects[i] as TBackupRec));
 // ����������, ���������, ������ CRC
 Result := CodeBinData(AStream);
end;

// ���������� �������� � �����
function TZBackupEngine.SaveItemToStream(AStream: TStream;
  ABackupId : string; AItem: TBackupRec): boolean;
begin
 // ������ ���� ����
 AStream.Write(AItem.RecType, 2);
 // ������ ID
 SaveStringToStream(AStream, ABackupId);
 // ������ ��������� ����� � �������
 SaveStringToStream(AStream, AItem.X1);
 SaveStringToStream(AStream, AItem.X2);
 SaveStringToStream(AStream, AItem.X3);
 SaveStringToStream(AStream, AItem.X4);
end;

// ���������� ������ � �����
function TZBackupEngine.SaveStringToStream(AStream: TStream;
  S: string): boolean;
var
 W  : word;
begin
 Result := false;
 W := length(S);
 // ������ ������ ������
 AStream.Write(W, 2);
 // ������ ����� ������
 if W > 0 then
  AStream.Write(S[1], W);
 Result := true;
end;

procedure TZBackupEngine.SetBackupId(const Value: string);
begin
  FBackupId := Trim(UpperCase(Value));
end;

function TZBackupEngine.SetRootKeyByName(Reg : TRegistry; AName: string): boolean;
begin
 Result := false;
 if StrToRootKey(AName) > 0 then begin
  Reg.RootKey := StrToRootKey(AName);
  Result := true;
 end;
end;

// ���������� ������ (ADeleteItems - �������� ��������� �� ���� ������ ����� ����������)
function TZBackupEngine.UndoChanges(ABackupId: string;
  ADeleteItems: boolean): boolean;
var
 i, ErrCount, OpCount : integer;
 Tmp : TBackupRec;
 S : string;
begin
 Result := false;
 ABackupId := Trim(UpperCase(ABackupId));
 OpCount := 0; ErrCount := 0;
 // ���� �������������� - ����������� � �������� �������
 i := BackupDB.Count - 1;
 while (i >= 0) and (i < BackupDB.Count) do begin
  // ��� ������� ��������� ������ ? ���� ��, �� �������� ���
  if BackupDB[i] = ABackupId then begin
   // �������� �������� ��������
   Tmp := (BackupDB.Objects[i] as TBackupRec);
   // ��������� �����
   case Tmp.RecType of
    // �������� ����� �������
    brtCreateKey : begin
                    try
                     if SetRootKeyByName(Reg, Tmp.X1) then
                      Reg.CreateKey(Tmp.X2)
                       else inc(ErrCount);
                    except
                     inc(ErrCount);
                    end;
                   end;
    // �������� ��������� �������
    brtDeleteParam : begin
                    try
                     if SetRootKeyByName(Reg, Tmp.X1) then
                      if Reg.OpenKey(Tmp.X2, false) then begin
                       if Reg.ValueExists(Tmp.X3) then
                        Reg.DeleteValue(Tmp.X3);
                       Reg.CloseKey;
                      end;
                    except
                     inc(ErrCount);
                    end;
                   end;
    // �������� ��� ��������� �������� ��������� REG_DWORD, REG_SZ
    brtSetParamValREG_DWORD,
    brtSetParamValREG_SZ,
    brtSetParamValREG_EXPAND_SZ : begin
                    try
                     if SetRootKeyByName(Reg, Tmp.X1) then
                      if Reg.OpenKey(Tmp.X2, true) then begin
                       // �������� �������� ���������
                       if Reg.ValueExists(Tmp.X3) then
                        Reg.DeleteValue(Tmp.X3);
                       // �������� ������ ��������� � ���������� ����� � ���������
                       // REG_DWORD
                       if Tmp.RecType = brtSetParamValREG_DWORD then
                        Reg.WriteInteger(Tmp.X3, StrToInt(Tmp.X4));
                       // REG_SZ
                       if Tmp.RecType = brtSetParamValREG_SZ then
                        Reg.WriteString(Tmp.X3, Tmp.X4);
                       // REG_EXPAND_SZ
                       if Tmp.RecType = brtSetParamValREG_EXPAND_SZ then
                        Reg.WriteExpandString(Tmp.X3, Tmp.X4);
                       Reg.CloseKey;
                      end;
                    except
                     inc(ErrCount);
                    end;
                   end;
    // �������� ��� ��������� �������� ��������� REG_DWORD, REG_SZ
    brtSetParamValREG_MULTI_SZ,
    brtSetParamValREG_BINARY : begin
                    try
                     if SetRootKeyByName(Reg, Tmp.X1) then
                      if Reg.OpenKey(Tmp.X2, true) then begin
                       // �������� �������� ���������
                       if Reg.ValueExists(Tmp.X3) then
                        Reg.DeleteValue(Tmp.X3);
                       // �������� ������ ��������� � ���������� ����� � ���������
                       S := Tmp.X4;
                       if Length(S) > 0 then begin
                        // REG_BINARY
                        if Tmp.RecType = brtSetParamValREG_BINARY then
                         RegSetValueEx(Reg.CurrentKey, PChar(Tmp.X3), 0,
                                       REG_BINARY, @S[1], Length(S));
                        // REG_MULTI_SZ
                        if Tmp.RecType = brtSetParamValREG_MULTI_SZ then
                         RegSetValueEx(Reg.CurrentKey, PChar(Tmp.X3), 0,
                                       REG_MULTI_SZ, @S[1], Length(S));
                       end else begin
                        // REG_BINARY
                        if Tmp.RecType = brtSetParamValREG_BINARY then
                         RegSetValueEx(Reg.CurrentKey, PChar(Tmp.X3), 0,
                                       REG_BINARY, nil, 0);
                        // REG_MULTI_SZ
                        if Tmp.RecType = brtSetParamValREG_MULTI_SZ then
                         RegSetValueEx(Reg.CurrentKey, PChar(Tmp.X3), 0,
                                       REG_MULTI_SZ, nil, 0);
                       end;
                       Reg.CloseKey;
                      end;
                    except
                     inc(ErrCount);
                    end;
                   end;
   end;
  end;
  dec(i);
 end;
 // ������ ����
 if ADeleteItems then
  DeleteChanges(ABackupId);
 Result := true;
end;

end.

(*
// ��� ��� ������������ �������
var
 BackupEngine : TZBackupEngine;
 MS : TMemoryStream;
begin
 BackupEngine := TZBackupEngine.Create;
 MS           := TMemoryStream.Create;
 {
 BackupEngine.BackupId := 'X5';
 BackupEngine.AddBackupDeleteKey('HKEY_LOCAL_MACHINE', 'SOFTWARE\Microsoft\Windows\CurrentVersion');
 BackupEngine.SaveBackupDB(MS);
 MS.seek(0,0);
 MS.SaveToFile('c:\text.zbk');
 }
 MS.LoadFromFile('c:\text.zbk');
 BackupEngine.LoadBackupDB(MS);
 MS.Free;
 BackupEngine.Free;
end;

*)
