unit zCHMUnpacker;

interface
uses Windows, Classes, SysUtils;
type
 QWORD = ULARGE_INTEGER;

 // ��������� CHM �����, ���� � ������ �����, ������ 38h
 TCHM_MAIN_HEADER = packed record
  Sign      : packed array[1..4] of char;   // ��������� 'ITSF'
  Version   : DWORD;                 // ����� ������ (3)
  HdrSize   : DWORD;                 // ������ ������ ���������
  Unc1      : DWORD;                 // ??, ����� 1
  TimeStamp : DWORD;                 // TimeStamp
  LangID    : DWORD;                 // ��� ����� ($0409 = LANG_ENGLISH/SUBLANG_ENGLISH_US
                                     //            $0407 = LANG_GERMAN/SUBLANG_GERMAN
                                     //            $0419 = ������� ?
  GUID1      : TGUID;                // {7C01FD10-7BAA-11D0-9E0C-00A0-C922-E6EC}
  GUID2      : TGUID;                // {7C01FD11-7BAA-11D0-9E0C-00A0-C922-E6EC}
 end;

 // ��������� ������
 TCHM_SECTION_HEADER = packed record
  Offset    : QWORD;                 // �������� ������ �� ������ �����
  Length    : QWORD;                 // ������ ������
 end;

 // ��������� ������ 1
 TCHM_SECTION1_HEADER = packed record
  SIGN      : DWORD;                 // ��������� ?? 01FE
  Unc1      : DWORD;                 // ??, 0
  FileSize  : QWORD;                 // ������ ����� (����� �����, � ������)
  Unc2      : DWORD;                 // ??, 0
  Unc3      : DWORD;                 // ??, 0
 end;

  // ��������� ������ 2
 TCHM_DIR_HEADER = packed record
  SIGN       : packed array[1..4] of char;   // ��������� 'ITSP';
  Version    : DWORD;                 // ������, 1
  HdrSize    : DWORD;                 // ������ ��������
  Unc1       : DWORD;                 // ??, 0A
  ChunkSize  : DWORD;                 // ������ "������" ��������, ������ 4096 ����
  QuickRefD  : DWORD;                 // "Density" of quickref section, ������ 2
  IndexDepth : DWORD;                 // ������� ���������� ������ (1-��� �������)
  ChunksInRoot  : DWORD;              //
  ChunksInFirstPMGL  : DWORD;         //
  ChunksInLastPMGL   : DWORD;         //
  Unc2               : DWORD;         // ??, -1
  DirChunksCount     : DWORD;         // ����� ������ � �������� (�����)
  LangID             : DWORD;         // ��� ����� ($0409 = LANG_ENGLISH/SUBLANG_ENGLISH_US
                                      //            $0407 = LANG_GERMAN/SUBLANG_GERMAN
                                      //            $0419 = ������� ?
  GUID1      : TGUID;                 // {7C01FD10-7BAA-11D0-9E0C-00A0-C922-E6EC}
  Size1      : DWORD;                 // ������ ���������
  Unc3       : DWORD;                 // ??, -1
  Unc4       : DWORD;                 // ??, -1
  Unc5       : DWORD;                 // ??, -1
 end;

 // ��������� "�����" ��������
 TCHM_DIR_CHUNK_HEADER = packed record
  SIGN       : packed array[1..4] of char;   // ��������� 'PMGL'
  SizeAtEnd  : DWORD;                        // ������ � ������ �����, ������� �������� ������ ��� ������
  Unc1       : DWORD;                        // ??, 0
  PrevChunk  : DWORD;                        // ��� ����������� �����, -1 - ��� ������  (FFFFFFFF)
  NextChunk  : DWORD;                        // ��� ������������ �����, -1 - ��� ��������� (FFFFFFFF)
                                             // !! ��� ������ CHM ��� ����� ���� PrevChunk = NextChunk = -1
 end;

 // ��������� "�����" NameList
 TCHMNameListHeader = packed record
  FileSize   : WORD;                         // ������ NameList ����� � ������
  NumEntries : WORD;                         // ���-�� ���������
  // ����� ���� ��������� ����
  //  WORD - ����� ������ (� �������� !!)
  //  (����� * 2) ���� - Unicode ������
  //  WORD = 0 - ����������� 0 Unicode ������
 end;


 // ������� ��������
 TCHMDirItem = record
  Name      : string; // ���
  Section   : DWORD;  // ������
  Offset    : DWORD;  // ��������
  Length    : DWORD;  // �����
 end;

 TCHMBuffer = packed array of byte;
 // ������
 TCHMSection = record
  Name       : string;  // ��� ������
  Offset     : DWORD;   // �������� �� ������ ����� �� ������
  Length     : DWORD;   // ����� ������
  Compressed : boolean; // ������� ������
  CmpType    : string;  // ��� ����������
  WindowSize : integer; // ������ ����
  UcLength,             // ������������� ������
  CLength    : DWORD;   // ������ ������
  Cache      : TCHMBuffer; // ���-�����
 end;

 TLZXInit       = function (WindowSize : Longint) : LongInt; stdcall;
 TLZXdecompress = function (in_buf : pointer; out_buf : pointer; in_len : DWORD; out_len : DWORD) : LongInt; stdcall;
 TCHMUnpacker = class
  private
    FFileName: string;
    procedure SetFileName(const Value: string);
    function LoadSectionList : boolean;
 public
    FS : TFileStream;
    // ������� ���������
    CHM_MAIN_HEADER     : TCHM_MAIN_HEADER;
    // ��������� ������
    CHM_SECTION_HEADERS : array [1..2] of TCHM_SECTION_HEADER;
    CHM_SECTION1_HEADER : TCHM_SECTION1_HEADER;
    CHM_DIR_HEADER      : TCHM_DIR_HEADER;
    // �����
    DirItems            : array of TCHMDirItem;
    // ������
    Sections            : array of TCHMSection;
    Section0Offest      : DWORD;
    // �������� CHM, ������ ��� ��������
    function OpenCHM : boolean;
    // ����� ����� �� ��������� - ���������� ������ ��� -1, ���� ��� �� �������
    function SearchDirItem(AItemName : string) : integer;
    // ���������� � �����
    function ExtractToStream(Stream : TStream; Item : TCHMDirItem) : boolean;
    destructor Destroy; override;
 published
  property FileName : string read FFileName write SetFileName;
 end;

implementation
{$L lzx.obj}
 function _LZXInit(WindowSize : Longint) : LongInt;  cdecl; external;
 function _LZXdecompress(in_buf : pointer; out_buf : pointer; in_len : DWORD; out_len : DWORD) : LongInt;  cdecl; external;

{ TCHMUnpacker }

function _malloc(Size: dword): Pointer; cdecl;
begin
  Result := AllocMem(Size);
end;

procedure _free(Block: Pointer); cdecl;
begin
  FreeMem(Block);
end;

procedure _memcpy(dest, source: Pointer; count: Integer); cdecl;
begin
  Move(source^, dest^, count);
end;

// ������ Integer � ���������� �������
Function Read_ENCINT(var FS : TFileStream) : dword;
var
 b : byte;
 r : dword;
begin
 try
  r := 0;
  FS.ReadBuffer(b,1);
  while ((b and $80) > 0) do  begin
    r := (r shl 7) + (b and $7f);
    FS.ReadBuffer(b, 1);
  end;
   Result := (r shl 7) + b;
 except
   Result := 0;
 end;
end;

destructor TCHMUnpacker.Destroy;
var
 i : integer;
begin
 FS.Free;
 FS := nil;
 for i := 0 to Length(Sections) - 1 do
  Sections[i].Cache := nil;
 inherited Destroy;
end;

function TCHMUnpacker.ExtractToStream(Stream: TStream;
  Item: TCHMDirItem): boolean;
var
 PackedStream : TMemoryStream;
 Buf          : TCHMBuffer;
 h            : thandle;
 LZXInit      : TLZXInit;
 LZXdecompress : TLZXdecompress;
 p1, p2 : pointer;
begin
 Result := false;
 // ������ �� �����
 if not(Sections[Item.Section].Compressed) then begin
  FS.Seek(Item.Offset + Sections[Item.Section].Offset, 0);
  Stream.CopyFrom(FS, Item.Length);
  Result := true;
  exit;
 end;
 // ������ �� �����
 if Sections[Item.Section].Compressed and (Sections[Item.Section].CmpType='LZXC') then begin
  if Sections[Item.Section].WindowSize < 0 then exit;
  if Sections[Item.Section].UcLength   = 0 then exit;
  if Sections[Item.Section].cLength    = 0 then exit;
  // ������ ��� ����������� � ���
  if Sections[Item.Section].Cache <> nil then begin
   Stream.Write(Sections[Item.Section].Cache[Item.Offset],  Item.Length);
   Result := true;
   exit;
  end else begin
   // ������ ���������� � ��� �� ��������������� � ���
   SetLength(Sections[Item.Section].Cache, Sections[Item.Section].UcLength + 10000);
   SetLength(Buf, Sections[Item.Section].cLength + 10000);
   FS.Seek(Sections[Item.Section].Offset, 0);
   FS.Read(Buf[0], Sections[Item.Section].cLength);
   p1 := @Buf[0];
   p2 := @(Sections[Item.Section].Cache[0]);
//   h := LoadLibrary('E:\Delphi5\Delphi7\Projects\SysInfo\avz\unpack\CHM\LZXDecomp1.dll');
//   @LZXInit       := GetProcAddress(h, 'LZXinit');
//   @LZXdecompress := GetProcAddress(h, 'LZXdecompress');

//   LZXInit(Sections[Item.Section].WindowSize);
//   LZXdecompress(p1, p2, Sections[Item.Section].CLength, Sections[Item.Section].UcLength);
   _LZXInit(Sections[Item.Section].WindowSize);
   _LZXdecompress(p1, p2, Sections[Item.Section].CLength, Sections[Item.Section].UcLength);

   Stream.Write(Sections[Item.Section].Cache[Item.Offset], Item.Length);
   Buf := nil;
  end;
 end;
end;

function TCHMUnpacker.LoadSectionList: boolean;
var
 CHMNameListHeader : TCHMNameListHeader;
 UnicodeS, S : string;
 i, NameListItem,ControlItem : integer;
 w : word;
 CmpCode : dword;
 MS : TMemoryStream;
begin
 Result := false;
 Sections := nil;
 // ���������� ������ � ������ �������, ��� ������ ������ �� ����� NameList
 NameListItem := SearchDirItem('::DataSpace/NameList');
 // ���� ::DataSpace/NameList �� ������ ? ����� �����
 if NameListItem < 0 then exit;
 // ������ ��������� �����
 FS.Seek(Section0Offest + DirItems[NameListItem].Offset, 0);
 FS.Read(CHMNameListHeader, SizeOf(CHMNameListHeader));
 // ���������� ��������
 if CHMNameListHeader.NumEntries > 100 then exit;
 // ���� ������ ������
 for i := 1 to CHMNameListHeader.NumEntries do begin
  // ������ ����� ����� (� ������)
  FS.Read(w, 2);
  Setlength(UnicodeS, w*2+2);
  // �������� �����
  FS.Read(UnicodeS[1], w*2+2);
  // ��������������� ����� � UTF8
  Setlength(S, w+1);
  UnicodeToUtf8(@S[1], Length(S), @UnicodeS[1], w);
  // ���������� ������
  SetLength(Sections, Length(Sections)+1);
  Sections[Length(Sections)-1].Name   := Trim(S);
  Sections[Length(Sections)-1].Cache  := nil;
  Sections[Length(Sections)-1].WindowSize := 0;
  Sections[Length(Sections)-1].UcLength := 0;
  Sections[Length(Sections)-1].cLength  := 0;
  // ����� ������ ������ � �����
  if i = 1 then begin
   Sections[Length(Sections)-1].Offset     := Section0Offest;
   Sections[Length(Sections)-1].Compressed := false;
   Sections[Length(Sections)-1].CmpType    := 'Not compressed';
   Sections[Length(Sections)-1].WindowSize := 0;
  end else begin
   NameListItem :=  SearchDirItem('::DataSpace/Storage/'+Sections[Length(Sections)-1].Name+'/Content');
   Sections[Length(Sections)-1].Compressed := true;
   Sections[Length(Sections)-1].CmpType := '?';
   if NameListItem >= 0 then
    Sections[Length(Sections)-1].Offset := DirItems[NameListItem].Offset + Section0Offest
     else Sections[Length(Sections)-1].Offset := 0;
   // ��������� ���� ����������
   ControlItem := SearchDirItem('::DataSpace/Storage/'+Sections[Length(Sections)-1].Name+'/ControlData');
   if ControlItem >= 0 then begin
    MS := TMemoryStream.Create;
    if ExtractToStream(MS, DirItems[ControlItem]) then begin
     MS.Seek($4, 0);
     SetLength(Sections[Length(Sections)-1].CmpType, 4);
     MS.Read(Sections[Length(Sections)-1].CmpType[1], 4);
     MS.Seek($10, 0);
     MS.Read(CmpCode, 4);
     case CmpCode of
      1 : Sections[Length(Sections)-1].WindowSize := 15;
      2 : Sections[Length(Sections)-1].WindowSize := 16;
      4 : Sections[Length(Sections)-1].WindowSize := 17;
      8 : Sections[Length(Sections)-1].WindowSize := 18;
      $10 : Sections[Length(Sections)-1].WindowSize := 19;
      $20 : Sections[Length(Sections)-1].WindowSize := 20;
      $40 : Sections[Length(Sections)-1].WindowSize := 21;
     else
      Sections[Length(Sections)-1].WindowSize := -1;
     end;
    end;
    MS.Free;
   end;
   // ��������� �������� ����� ������ (������� � ���������)
   ControlItem := SearchDirItem('::DataSpace/Storage/'+Sections[Length(Sections)-1].Name+'/Transform/{7FC28940-9D31-11D0-9B27-00A0C91E9C7C}/InstanceData/ResetTable');
   if ControlItem >= 0 then begin
    MS := TMemoryStream.Create;
    if ExtractToStream(MS, DirItems[ControlItem]) then begin
      MS.Seek($10, 0); MS.Read(Sections[Length(Sections)-1].UcLength, 4);
      MS.Seek($18, 0); MS.Read(Sections[Length(Sections)-1].cLength, 4);
    end;
    MS.Free;
   end;
  end;
 end;
 Result := true;
end;

function TCHMUnpacker.OpenCHM: boolean;
var
 CHM_DIR_CHUNK_HEADER : TCHM_DIR_CHUNK_HEADER;
 i, EndPoz, NewChunkPoz : integer;
 Tmp : TCHMDirItem;
 NameSize : integer;
begin
 Result := false;
 DirItems := nil;
 Sections := nil;
 FS := TFileStream.Create(FFileName, fmOpenRead or fmShareDenyNone);
 FS.Seek(0,0);
 // �������� �������� ���������
 FS.Read(CHM_MAIN_HEADER, SizeOf(CHM_MAIN_HEADER));
 // �������� ���������
 if CHM_MAIN_HEADER.Sign <> 'ITSF' then exit;
 // �������� ���������� ������
 FS.Read(CHM_SECTION_HEADERS[1], SizeOf(TCHM_SECTION_HEADER));
 FS.Read(CHM_SECTION_HEADERS[2], SizeOf(TCHM_SECTION_HEADER));
 // ��������
 if (CHM_SECTION_HEADERS[1].Offset.QuadPart <  CHM_MAIN_HEADER.HdrSize) or
    (CHM_SECTION_HEADERS[2].Offset.QuadPart <  CHM_MAIN_HEADER.HdrSize) then exit;
 if (CHM_SECTION_HEADERS[1].Offset.QuadPart >  FS.Size) or
    (CHM_SECTION_HEADERS[2].Offset.QuadPart >  FS.Size) then exit;
 // �������� ������ 1
 FS.Seek(CHM_SECTION_HEADERS[1].Offset.QuadPart, 0);
 FS.Read(CHM_SECTION1_HEADER, SizeOf(CHM_SECTION1_HEADER));
 // �������� ������ 2
 FS.Seek(CHM_SECTION_HEADERS[2].Offset.QuadPart, 0);
 FS.Read(CHM_DIR_HEADER, SizeOf(CHM_DIR_HEADER));
 // ������� ����������
 if CHM_DIR_HEADER.SIGN <> 'ITSP' then exit;
 // ��������� "��������" ��������
 for i := 1 to CHM_DIR_HEADER.DirChunksCount do begin
  NewChunkPoz  := FS.Position + CHM_DIR_HEADER.ChunkSize;
  FS.Read(CHM_DIR_CHUNK_HEADER, SizeOf(CHM_DIR_CHUNK_HEADER));
  // ������� ������, �������� �� �������� �� ���������
  if CHM_DIR_CHUNK_HEADER.SIGN <> 'PMGL' then begin
   FS.Seek(NewChunkPoz, 0);
   Continue;
  end;
  EndPoz       := FS.Position - SizeOf(CHM_DIR_HEADER) + CHM_DIR_HEADER.ChunkSize - CHM_DIR_CHUNK_HEADER.SizeAtEnd;
  // ������ �������� ����������
  while FS.Position < EndPoz do begin
   NameSize := Read_ENCINT(FS);
   if (NameSize = 0) or (NameSize > 1000) then Break;
   SetLength(Tmp.Name, NameSize);
   FS.Read(Tmp.Name[1], NameSize);
   Tmp.Section := Read_ENCINT(FS);
   namesize := FS.position;
   Tmp.Offset  := Read_ENCINT(FS);
   Tmp.Length  := Read_ENCINT(FS);
   SetLength(DirItems, Length(DirItems) + 1);
   DirItems[Length(DirItems) - 1] := Tmp;
  end;
  FS.Seek(NewChunkPoz, 0);
 end;
 // ���������� ������ � ������ 0
 FS.Seek($058, 0);
 FS.Read(Section0Offest, 4);
 //Section0Offest := FS.Position;
 if not(LoadSectionList) then exit;
 Result := true;
end;

function TCHMUnpacker.SearchDirItem(AItemName: string): integer;
var
 i : integer;
begin
 Result := -1;
 AItemName := Trim(UpperCase(AItemName));
 for i := 0 to Length(DirItems) - 1 do
  if Trim(UpperCase(DirItems[i].Name)) = AItemName then begin
   Result := i;
   exit;
  end;
end;

procedure TCHMUnpacker.SetFileName(const Value: string);
begin
  FFileName := Value;
end;

end.












