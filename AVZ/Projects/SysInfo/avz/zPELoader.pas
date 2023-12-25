unit zPELoader;

interface
uses Windows, classes, sysutils;
const
 // �������� ������
 // ������� �������������� ��������
 IMAGE_DIRECTORY_ENTRY_EXPORT  =  0;
 // ������� ������������� ��������
 IMAGE_DIRECTORY_ENTRY_IMPORT  =  1;
 // ������� ��������
 IMAGE_DIRECTORY_ENTRY_RESOURCE =  2;
 // ������� ����������
 IMAGE_DIRECTORY_ENTRY_EXCEPTION = 3;
 // ������� ������������
 IMAGE_DIRECTORY_ENTRY_SECURITY = 4;
 // ������� �������������
 IMAGE_DIRECTORY_ENTRY_BASERELOC = 5;
 // ���������� �������
 IMAGE_DIRECTORY_ENTRY_DEBUG = 6;
 // ������ ��������
 IMAGE_DIRECTORY_ENTRY_COPYRIGHT = 7;
 // �������� �������� (MIPS GP)
 IMAGE_DIRECTORY_ENTRY_GLOBALPTR = 8;
 // ������� TLS ( Thread local storage - ��������� ������ ������� )
 IMAGE_DIRECTORY_ENTRY_TLS = 9;
 // ������� ������������ ��������
 IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG  = 10;

type
  //(C++: IMAGE_FILE_HEADER, )
  _IMAGE_FILE_HEADER = packed record
    PE_Segnature         : DWord; // 4550h ('PE', 00h, 00h)
    Machine              : Word;  // CPU ����������, ��� 32-bit Intel ��� 014� (hex)
    NumberOfSections     : Word;  // ����� PE-������
    TimeDateStamp        : DWORD; // ���� � ����� (����� ������ � ������� 16:00 31.12.1969) �������� �����
    PointerToSymbolTable : DWORD; // ��� OBJ-������ ���� ��������� �� ������� ��������, ��� DLL - �� ������� � ���������� �����������
    NumberOfSymbols      : DWORD; // ���-�� �������� ��� OBJ
    SizeOfOptionalHeader : Word;  // ������ �������������� ����� PE-���������
    Characteristics      : Word;  // ��������� �������������� �����
  end;
  TImageFileHeader = _IMAGE_FILE_HEADER;

  //(C++: IMAGE_OPTIONAL_HEADER, �� ���� � Windows.pas - ����� ���������� � �������������)
  _IMAGE_OPTIONAL_HEADER = packed record
    Magic                   : Word;     // ���, ����������� ���������� ���������
    MajorLinkerVersion      : Byte;     // ������ ������� (HI)
    MinorLinkerVersion      : Byte;     // ������ ������� (LO)
    SizeOfCode              : DWORD;    // ��������� ����������� ������ ���� ������, ���������� ��� (������������ ��� ��������� ������)
    SizeOfInitializedData   : DWORD;    // �� �� ��� ������������������ ������ (�� ���. � Win 95 ?)
    SizeOfUninitializedData : DWORD;    // � ��� ��������������������
    AddressOfEntryPoint     : DWORD;    // RVA ����� ����� � PE-���� (��� DLL - DllMain)
    BaseOfCode              : DWORD;    // RVA ������ � �����
    BaseOfData              : DWORD;    // RVA ������ ������
    ImageBase               : DWORD;    // ���������������� ������� ����� ��������
    SectionAlignment        : DWORD;    // ������������ - ��� ����������� ������ ������ ������ ����� �����
    FileAlignment           : DWORD;    // ������������ � �����
    MajorOperatingSystemVersion : Word; // ��������� ������ �� ��� ������� ���������
    MinorOperatingSystemVersion : Word;
    MajorImageVersion        : Word;    // ���������������� ����� ������, �������� �������
    MinorImageVersion        : Word;
    MajorSubsystemVersion    : Word;    // ����� ������ ���������� (?)
    MinorSubsystemVersion    : Word;
    Win32VersionValue        : DWORD;   // ���������������
    SizeOfImage              : DWORD;   // ������ ������� ������, ����������� ��� ���������� ������ PE-�����
    SizeOfHeaders            : DWORD;   // ������ ������� ����������.
    CheckSum                 : DWORD;   // ����������� ����� �����, ������ ����� 0 (�� ������������ ��� SYS ������ !!)
    Subsystem                : Word;    // ��� ���������� ������ � ��������� ��� ������ ����������
    DllCharacteristics       : Word;    // �������� DLL. �������� 1,2,4 � 8 ���������������; 2000h - WDM-�������
    SizeOfStackReserve       : DWORD;   // ������ ��� ����� (�����)
    SizeOfStackCommit        : DWORD;   // ������ ��� ����� (��������� ����� ��� ��������)
    SizeOfHeapReserve        : DWORD;   // ����������� ��������� ������ Heap
    SizeOfHeapCommit         : DWORD;   // �������� ��� �������� Heap
    LoaderFlags              : DWORD;   // ����� ����������, ���������� (����� �� ������������)
    NumberOfRvaAndSizes      : DWORD;   // ���������� ��������� � �������� DataDirectory
    //����� ������� ������ �� NumberOfRvaAndSizes ���������, ����������� �� ������ ��������� ������,
    DataDirectory: packed array[0..IMAGE_NUMBEROF_DIRECTORY_ENTRIES-1] of TImageDataDirectory;
  end;
  TImageOptionalHeader = _IMAGE_OPTIONAL_HEADER;

  // ������ ������� �������� PE �����
  TImageSectionHeader = packed record
   ObjName         : packed array [0..7] of char; // ��� �������
   VirtSize        : DWord;
   VirtRVA         : DWord;
   PhSize          : DWord;
   PhOffset        : DWord;
   Reserved        : packed array[1..3] of DWORD;
   Characteristics : ULONG;
  end;

  // ��������� ����� ������� Relocation Table
  TImageBaseRelocation=packed record
    VirtualAddress  : cardinal; // ������� RVA
    SizeOfBlock     : cardinal; // ������ �����
  end;

  _IMAGE_EXPORT_DIRECTORY = packed record  //(C++: IMAGE_EXPORT_DIRECTORY)
      Characteristics : DWord;       //�� ������������
      TimeDateStamp   : DWord;       //������� ������� �������� �������; �� ������ �������� ������ ��������!
      MajorVersion    : Word;        //�� ������������
      MinorVersion    : Word;        //�� ������������
      Name            : DWord;       //����������� ����� ASCIIZ-������ � ������ ������ DLL
      Base            : DWord;       //��������� ordinal (������ � ����������� �� ���������� ������� ����
                                     // �������������� ��������)
      NumberOfFunctions: DWord;      //����� ����� �������������� ��������
      NumberOfNames: DWord;          //���������� ��������, ���������������� �� ������
      AddressOfFunctions: DWORD;     //����������� ����� ������� ������� �������
      AddressOfNames: DWORD;         //�� �� ��� ������� ����������� ������� ���� �������
      AddressOfNameOrdinals: DWord;   //�� �� ��� �������, ��������� ������������ ���������� ������� ������
      ForAligmentBuf : array[1..16] of byte;
  end;

  TImageExportDirectory = _IMAGE_EXPORT_DIRECTORY;
  TImageImportDescriptor=packed record  //(C++: IMAGE_IMPORT_DESCRIPTOR)
    OriginalFirstThunk : DWORD; // ����� ��� ���� ���������� Characteristics; � ����� ����������
    TimeDateStamp      : DWORD; // 0, ���� �������������� �������������� ��� �������� (binding - ��. �����)
                                // ��� �������������� � ��������� �������� ������� ������� �����, �� ��������
    ForwarderChain     : DWORD; //
    Name               : DWORD; // ����������� ����� ASCIIZ-������ � ������ �����, �� �������� �����������
    FirstThunk         : DWORD; // ����������� ����� ���������� ������������� ��������
  end;
  PImageImportDescriptor=^TImageImportDescriptor;

  _IMAGE_TLS_DIRECTORY32 = packed record
    StartAddressOfRawData : DWORD;
    EndAddressOfRawData   : DWORD;
    AddressOfIndex        : DWORD;    // PDWORD
    AddressOfCallBacks    : DWORD;    // PIMAGE_TLS_CALLBACK *
    SizeOfZeroFill        : DWORD;
    Characteristics       : DWORD;
  end;
  TImageTSLDirectory = _IMAGE_TLS_DIRECTORY32;
  PImageTSLDirectory = ^TImageTSLDirectory;

 // ����� ��� ������ � PE ������
 TPEImageLoader = class
 protected
  // �������� ������� �������� ������ �����
  function LoadSectionTable : boolean;
 public
  FS : TMemoryStream;    // ����� PE ����� � ������
  PE_Header_Rel         : DWORD;                        // �������� �� PE ���������
  ImageFileHeader       : TImageFileHeader;             // ��������� �����
  ImageOptionalHeader   : TImageOptionalHeader;         // ����������� ��������� �����
  ImageSections         : array of TImageSectionHeader; // ������ ������
  PELoaded              : boolean;
  constructor Create;
  destructor Destroy; override;
  // �������� PE ����� � ������
  function LoadPEFile(APEFileName : string) : boolean;
  function LoadMemImage(ABuf: pointer; Size: dword): boolean;
  // �������� PE ����� �� ������
  function UnLoadPEFile : boolean;
  // ��������� ������ ��������
  function SetupPageProtect : boolean;
  // ���������� ��������� �� ������� �����������
  function ExecuteReallocation(AImageBase : DWORD) : boolean;
  // ����� ������ �� RVA (-1 - ������ �� �������)
  function GetSectionByRVA(RVA : DWORD) : integer;
  // ����� ������ �� ����� (-1 - ������ �� �������)
  function GetSectionByName(AName : string) : integer;
  // �������� ������� ������ �������
  function GetImportTable(AList : TStrings) : boolean;
  // �������� ������� ������ �������
  function GetExportTable(AList : TStrings) : boolean;
  // ������� ������ ��� ������� �������
  function FreeImportTable(AList : TStrings) : boolean;
  // ����� ������� �� �� �����
  function ImportFunctionExists(AList : TStrings; ADLLName, AFunctionName : string) : boolean;
  // ���������� ������ �� RVA � ���� ������
  function GetPhAddByRVA(RVA : DWORD; ASectionId : DWORD) : DWORD; overload;
  function GetPhAddByRVA(RVA : DWORD) : DWORD; overload;
  function DWordIsReallocated(Addr : dword) : boolean;
  function CreateCodeImageFS(AFS : TMemoryStream) : boolean;
 end;

 TImageDirectoryEntryToData = function (Base: Pointer; MappedAsImage: ByteBool;
  DirectoryEntry: Word; var Size: DWORD): Pointer; stdcall;

implementation

uses Math;

{ TPEImageLoader }

function TPEImageLoader.GetPhAddByRVA(RVA, ASectionId: DWORD): DWORD;
begin
 Result := RVA - ImageSections[ASectionId].VirtRVA +
           ImageSections[ASectionId].PhOffset;
end;

constructor TPEImageLoader.Create;
begin
 FS := TMemoryStream.Create;
 ImageSections := nil;
 PELoaded := false;
end;

destructor TPEImageLoader.Destroy;
begin
 PELoaded := false;
 ImageSections := nil;
 FS.Clear;
 FS.Free;
 inherited;
end;


function TPEImageLoader.ExecuteReallocation(AImageBase: DWORD): boolean;
var
 ImageBaseRelocation : TImageBaseRelocation;
 RelocSize, ImageBaseDelta : DWORD;
 P         : PWORD;
 RelocSectionId, CorrectSectionId : integer;
 CorrectSectionPhAddr : DWORD;
 StartTablePtr, EndTablePtr, TekTablePtr : pointer;
 ModCount : cardinal;
 i : integer;
begin
 Result := false;
 // ��������, ���� �� ������� ������
 if ImageSections = nil then exit;
 // ��������, ���� �� ������� ����������� (���� ���, �� �����)
 if ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size = 0 then exit;
 if ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress = 0 then exit;
 // ����� ������, � ������� ��������� ������� �����������
 RelocSectionId := GetSectionByRVA(ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
 if RelocSectionId < 0 then exit;
 // ���������� �����������
 RelocSize := ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size;
 // ���������� ��������� �� ������ �������
 StartTablePtr := pointer(dword(FS.Memory) +
                          ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress -
                          ImageSections[RelocSectionId].VirtRVA +
                          ImageSections[RelocSectionId].PhOffset);
 // ���������� ��������� �� ����� �������
 EndTablePtr := pointer(dword(StartTablePtr) + RelocSize);
 TekTablePtr := StartTablePtr;
 // ���������� ������������ ������������ ImageBaseDelta (������� ����� ������� � ��������� � �������� ������� ��������)
 ImageBaseDelta := AImageBase - ImageOptionalHeader.ImageBase;
 if ImageBaseDelta = 0 then exit;
 // ���� �� ������ ������� �����������
 while dword(TekTablePtr) < dword(EndTablePtr) do begin
  // ������ ���������
  Move(TekTablePtr^, ImageBaseRelocation, SizeOf(ImageBaseRelocation));
  // ���������� ��������� �� ������ WORD � ������� �����
  P := pointer(dword(TekTablePtr) + SizeOf(ImageBaseRelocation));
  // ���������� ����������� �������� � �����
  CorrectSectionId := GetSectionByRVA(ImageBaseRelocation.VirtualAddress);
  if CorrectSectionId >= 0 then
   CorrectSectionPhAddr := dword(FS.Memory) +
                          ImageBaseRelocation.VirtualAddress -
                          ImageSections[CorrectSectionId].VirtRVA +
                          ImageSections[CorrectSectionId].PhOffset
  else
   CorrectSectionPhAddr := 0;
  // ���������� ���������� ��������� � �����
  ModCount := (ImageBaseRelocation.SizeOfBlock - SizeOf(ImageBaseRelocation)) div 2;
  for i := 0 to ModCount - 1 do begin
   if (CorrectSectionPhAddr <> 0) and ((P^ and $F000) <> 0) then // ��� ������ - �� IMAGE_REL_BASED_ABSOLUTE(=0)
    Inc(pdword(CorrectSectionPhAddr + (P^ and $0fff))^, ImageBaseDelta);
   inc(P);
  end;
  TekTablePtr := P; // ������� ��������� := ��������� ������� + 1 (�.�. ��������� �� ��������� ���������)
 end;
end;

function TPEImageLoader.GetSectionByRVA(RVA: DWORD): integer;
var
 i : integer;
begin
 Result := -1;
 if not(PELoaded) then exit;
 // ����� ������
 for i := 0 to Length(ImageSections) - 1 do
  if (RVA >= ImageSections[i].VirtRVA) and (RVA < ImageSections[i].VirtRVA + ImageSections[i].VirtSize) then begin
   Result := i;
   Break;
  end;
end;

// ����� ������ �� ����� (-1 - ������ �� �������)
function TPEImageLoader.GetSectionByName(AName: string): integer;
var
 i : integer;
begin
 Result := -1;
 AName := Trim(UpperCase(AName));
 if not(PELoaded) then exit;
 // ����� ������
 for i := 0 to Length(ImageSections) - 1 do
  if (AName = UpperCase(Trim(ImageSections[i].ObjName))) then begin
   Result := i;
   Break;
  end;
end;

function TPEImageLoader.LoadMemImage(ABuf : pointer; Size : dword): boolean;
var
 Buf            : packed array [0..90000] of byte;
begin
 if Size < 100 then exit;
 Result := false;
 PELoaded := false;
 // �������� ����������� ������
 UnLoadPEFile;
 FS.SetSize(Size);
 CopyMemory(FS.Memory, ABuf, Size);
 // ����������� �� ������ ����� � �������� ��������� � �����
 FS.Seek(0,0);
 FS.Read(Buf, SizeOf(Buf));
 if FS.Size < ($3C+4) then begin
  UnLoadPEFile;
  exit;
 end;
 // ����� �������� �� ���������
 Move(pointer(dword(FS.Memory)+$3C)^, PE_Header_Rel, 4);
 // ������ ��������� ���������
 if FS.Size < (PE_Header_Rel + sizeof(ImageFileHeader)) then begin
  UnLoadPEFile;
  exit;
 end;
 Move(pointer(dword(FS.Memory)+PE_Header_Rel)^, ImageFileHeader, sizeof(ImageFileHeader));
 if ImageFileHeader.PE_Segnature <> 17744 then begin
  UnLoadPEFile;
  exit;
 end;
 // ������ ������������ ���������
 Move(pointer(dword(FS.Memory)+PE_Header_Rel+$18)^, ImageOptionalHeader, sizeof(ImageOptionalHeader));
 // ������ �������� ������ �����
 LoadSectionTable;
 // ��������� ������ 
 SetupPageProtect;
 PELoaded := true;
 Result := true;
end;

function TPEImageLoader.LoadPEFile(APEFileName: string): boolean;
var
 FS_DLL   : TFileStream;
 Buf            : packed array [0..90000] of byte;
begin
 Result := false;
 PELoaded := false;
 // �������� ����������� ������
 UnLoadPEFile;
 // �������� ������, ���������� � ������ (������ ������ � fmShareDenyNone - ����� �� ������� ����������� DLL)
 try
  FS_DLL  := TFileStream.Create(APEFileName, fmOpenRead  or fmShareDenyNone);
 except
  exit;
 end;
 try
  try
   FS.LoadFromStream(FS_DLL);
  except
   exit;
  end;
 finally
  FS_DLL.Free;
  FS_DLL := nil;
 end;
 // ����������� �� ������ ����� � �������� ��������� � �����
 FS.Seek(0,0);
 FS.Read(Buf, SizeOf(Buf));
 if FS.Size < ($3C+4) then begin
  UnLoadPEFile;
  exit;
 end;
 // ����� �������� �� ���������
 Move(pointer(dword(FS.Memory)+$3C)^, PE_Header_Rel, 4);
 // ������ ��������� ���������
 if FS.Size < (PE_Header_Rel + sizeof(ImageFileHeader)) then begin
  UnLoadPEFile;
  exit;
 end;
 Move(pointer(dword(FS.Memory)+PE_Header_Rel)^, ImageFileHeader, sizeof(ImageFileHeader));
 if ImageFileHeader.PE_Segnature <> 17744 then begin
  UnLoadPEFile;
  exit;
 end;
 // ������ ������������ ���������
 Move(pointer(dword(FS.Memory)+PE_Header_Rel+$18)^, ImageOptionalHeader, sizeof(ImageOptionalHeader));
 // ������ �������� ������ �����
 LoadSectionTable;
 // ��������� ������
 SetupPageProtect;
 PELoaded := true;
 Result := true;
end;

function TPEImageLoader.LoadSectionTable: boolean;
begin
 ImageSections := nil;
 // ��������� ������� ������� �� ����� ������
 SetLength(ImageSections, ImageFileHeader.NumberOfSections);
 // �������� ������� ������
 Move(pointer(dword(FS.Memory)+PE_Header_Rel + $18 + ImageFileHeader.SizeOfOptionalHeader)^,
      ImageSections[0],
      ImageFileHeader.NumberOfSections * sizeof(TImageSectionHeader));
end;

function TPEImageLoader.UnLoadPEFile: boolean;
begin
 Result := true;
 // ������� ������
 FS.SetSize(0);
 ImageSections := nil;
end;

function TPEImageLoader.GetPhAddByRVA(RVA: DWORD): DWORD;
var
 SectionID : integer;
begin
 Result := 0;
 SectionID := GetSectionByRVA(RVA);
 if SectionID < 0 then exit;
 Result := GetPhAddByRVA(RVA, SectionID);
end;

function TPEImageLoader.FreeImportTable(AList: TStrings): boolean;
var
 i : integer;
begin
 For i := 0 to AList.Count-1 do
  if (AList.Objects[i] is TStrings) then begin
   (AList.Objects[i] as TStrings).Free;
   AList.Objects[i] := nil;
  end;
 AList.Clear;
end;

function TPEImageLoader.GetImportTable(AList: TStrings): boolean;
var
 ImportTableSection : integer;
 ImportTableRVA, ImportTableEntryPoint : DWord;
 PImport     : PImageImportDescriptor;
 PRVA_Import : LPDWORD;
 PLibName, PImportedName    : PChar;
 dw : dword;
 Tmp : TStrings;
begin
 FreeImportTable(AList);
 Result := false;
 // 1. ��������, ���� �� ������� �������
 if ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress = 0 then exit;
 // 2. ����� ������ �������� �������
 ImportTableSection := GetSectionByRVA(ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
 // ���� ������ �� �������, �� �����
 if ImportTableSection < 0 then exit;
 // �������� ������� � ������
 if ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size > 100000 then exit;
 ImportTableRVA        := ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
 ImportTableEntryPoint := GetPhAddByRVA(ImportTableRVA);
 FS.Seek(ImportTableEntryPoint, 0);
 PImport := pointer(ImportTableEntryPoint + dword(FS.Memory));
 while PImport.Name <> 0 do begin
  PLibName := pchar(DWord(GetPhAddByRVA(PImport.Name)));
  dw := DWord(GetPhAddByRVA(PImport.Name));
  Tmp := TStringList.Create;
  AList.AddObject(pchar(dw+dword(FS.Memory)), Tmp);
  // �������� ���� ?
  if PImport.TimeDateStamp=0  then PRVA_Import := LPDWORD(GetPhAddByRVA(pImport.FirstThunk) + dword(FS.Memory))
   else PRVA_Import:=LPDWORD(GetPhAddByRVA(pImport.OriginalFirstThunk) + dword(FS.Memory));
  while PRVA_Import^<>0 do begin
   if (dword(PRVA_Import^) and $80000000) = 0 then begin
    PImportedName := pchar(GetPhAddByRVA(PRVA_Import^) + 2 + dword(FS.Memory));
    Tmp.Add(PImportedName);
   end;
   Inc(PRVA_Import);
  end;
  inc(PImport);
 end;
 Result := true;
end;

function TPEImageLoader.ImportFunctionExists(AList: TStrings; ADLLName,
  AFunctionName: string): boolean;
var
 Poz : integer;
 Tmp : TStrings;
begin
 Result := false;
 ADLLName      := Trim(LowerCase(ADLLName));
 AFunctionName := Trim(LowerCase(AFunctionName));
 Poz := AList.IndexOf(ADLLName);
 if Poz < 0 then exit;
 Tmp := (AList.Objects[Poz] as TStrings);
 if Tmp = nil then exit;
 Result := Tmp.IndexOf(AFunctionName) >= 0;
 Tmp := nil;
end;

function TPEImageLoader.GetExportTable(AList: TStrings): boolean;
var
 ExportTableSection : integer;
 ExportTableRVA,
 ExportTableEntryPoint,
 ExportTableSize,
 ExportTableItemsCount,
 ExportTableFunctionsRel,
 ExportTableNameRel, ExportTableOrdinalRel : DWORD;
 dw      : dword;
 i       : integer;
 Buf            : packed array of byte;
 ImageExportDirectory : TImageExportDirectory;
 FunctionName    : string;
 FunctionOrdinal : word;
 FunctionRVA     : dword;
begin
 AList.Clear;
 // ������ ��� ������� �������� ����������� ? ���� ��, �� �����
 if (ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size = 0) or
    (ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress = 0) then
     exit;
 // ���������� ����� ������
 ExportTableSection := GetSectionByRVA(ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
 if (ExportTableSection <  0) then
   exit;
 // ����������� RVA, ������� � ����������� ��������� ������� ��������
 ExportTableRVA        := ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
 ExportTableEntryPoint := GetPhAddByRVA(ExportTableRVA);
 ExportTableSize       := ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
 // ������ ������ �� ������� �������� � �����
 SetLength(Buf, ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size);
 FS.Seek(ExportTableEntryPoint, 0);
 FS.Read(Buf[0], ImageOptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size);
 move(Buf[0], ImageExportDirectory, sizeof(ImageExportDirectory));
 // ������ ���������� ��������� ������� ��������
 ExportTableItemsCount   := ImageExportDirectory.NumberOfFunctions;
 ExportTableFunctionsRel := ImageExportDirectory.AddressOfFunctions - ExportTableRVA;
 // ������ ��������� �� �� ������� ����
 ExportTableNameRel    := ImageExportDirectory.AddressOfNames - ExportTableRVA;
 ExportTableOrdinalRel := ImageExportDirectory.AddressOfNameOrdinals - ExportTableRVA;
 // ���� �� ������� ����
 for i := 0 to  ImageExportDirectory.NumberOfNames - 1 do begin
  // ��� �������
  move(Buf[ExportTableNameRel+i*4], dw, 4);
  if (dw - ExportTableRVA) > ExportTableSize then continue;
  FunctionName := Pchar(@Buf[dw - ExportTableRVA]);
  // �������
  move(Buf[ExportTableOrdinalRel+i*2], FunctionOrdinal, 2);
  // �����
  move(Buf[ExportTableFunctionsRel+FunctionOrdinal*4], dw, 4);
  FunctionRVA := dw;
  AList.AddObject(FunctionName, pointer(FunctionRVA));
 end;
end;


function TPEImageLoader.DWordIsReallocated(Addr: dword): boolean;
begin
 result := true;
end;

function TPEImageLoader.SetupPageProtect: boolean;
var
 NewProtect, OldProtect : cardinal;
begin
 NewProtect := PAGE_EXECUTE_READWRITE;
 VirtualProtect(FS.Memory, FS.Size, NewProtect, OldProtect);
end;

function TPEImageLoader.CreateCodeImageFS(AFS: TMemoryStream): boolean;
var
 i : integer;
begin
 if not(PELoaded) then exit;
 AFS.SetSize(ImageOptionalHeader.SizeOfImage);
 ZeroMemory(AFS.Memory, AFS.Size);
 // ����������� ����������
 CopyMemory(AFS.Memory, FS.Memory, ImageOptionalHeader.SizeOfHeaders);
 // ����������� ������
 for i := 0 to length(ImageSections)-1 do
  CopyMemory(pointer(dword(AFS.Memory) + ImageSections[i].VirtRVA),
             pointer(dword(FS.Memory)  + ImageSections[i].PhOffset),
             ImageSections[i].PhSize);
end;

end.
