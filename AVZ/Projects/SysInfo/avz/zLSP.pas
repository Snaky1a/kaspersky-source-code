unit zLSP;

interface
uses Windows, SysUtils, winsock, registry, Variants, Classes, zSharedFunctions,
  RxVerInf, zutil, zHTMLTemplate;
 const
  LSP_Reg_Key = 'SYSTEM\CurrentControlSet\Services\WinSock2\Parameters';
 type
  // ���������� � ����������� ����
  TNameSpaceInfo = record
   Found           : boolean; // ������� ����, ��� �����. CLSID ������
   IsCorrect       : boolean; // ������� ������������
   NSProviderId    : TGUID;   // CLSID ����������
   dwNameSpace     : DWord;
   fActive         : Boolean; // ������� ����������
   dwVersion       : DWord;   // ������
   lpszIdentifier  : String;  // ��������� �������������
   BinFileName     : string;  // ��� ������������ �����
   BinFileExists   : boolean; // ������� ������������� ����� �� �����
   BinFileInfo     : string;  // ���������� � ����������� �����
   RegKey          : string;  // ���� �������
   CheckResults    : integer; // ���������� ��������
  end;
  // ���������� � ���������
  TProtocolInfo = record
   Found           : boolean;
   IsCorrect       : boolean;
   lpszIdentifier  : String;
   BinFileName     : string;
   BinFileExists   : boolean;
   BinFileInfo     : string;
   RegKey          : string;
   CheckResults    : integer; // ���������� ��������
  end;
  // ��������� �������
  TWSAEnumNameSpaceProviders = function (lpdwBufferLength : LPDWORD; lpNameSpaceBuffer : pointer) : LongInt; stdcall;
  TWSCUnInstallNameSpace     = function(NSProviderId     : PGUID) : LongInt; stdcall;
  TWSCEnableNSProvider       = function(NSProviderId     : PGUID; Enabled : bool) : LongInt; stdcall;
  TWSAEnumProtocols          = function (lpiProtocols: PInt; lpProtocolBuffer: pointer; lpdwBufferLength: PDWORD): longint; stdcall;
  TWSARemoveServiceClass     = function(NSProviderId     : PGUID) : LongInt; stdcall;
  TWSCDeinstallProvider      = function(NSProviderId     : pointer; ErrorCode : PLongInt) : LongInt; stdcall;

  // ����� ��� ������ � LSP
  TLSPManager = class
   private
    FCurrent_NameSpace_Catalog: string;
    FCurrent_Protocol_Catalog: string;
   protected
    hLib : THandle;
    WSAEnumNameSpaceProviders : TWSAEnumNameSpaceProviders;
    WSARemoveServiceClass     : TWSARemoveServiceClass;
    WSCDeinstallProvider      : TWSCDeinstallProvider;
    WSAEnumProtocols          : TWSAEnumProtocols;
    WSCUnInstallNameSpace     : TWSCUnInstallNameSpace;
    WSCEnableNSProvider       : TWSCEnableNSProvider;
    function RefreshCatalogNames  : boolean;
    function RefreshNameSpaceListReg : boolean;
    function RefreshNameSpaceListWS  : boolean;
    function RefreshProtocolInfo     : boolean;
    // ����� ����� ����� �� �������
    function SearchLSPFileByRegistry(ANameSpaceCatalog: string;
      AGUID: TGUID): string;
    public
    // ������ ����������� ����
    NameSpaceListReg  : array of  TNameSpaceInfo; // �� ������ �������
    NameSpaceListWS   : array of  TNameSpaceInfo; // �� ������ WinSock
    // ������ ����������
    ProtocolListReg   : array of  TProtocolInfo;  // �� ������ �������
    constructor Create;
    // ���������� �������
    function Refresh : boolean;
    function SetNameSpaceActive(ID : integer; NewStatus : boolean) : boolean;
    // **** �������� ������������ ���� ****
    // �� GUID
    function DeleteNameSpaceByGUID(AGUID : TGUID) : boolean;
    // �� �����
    function DeleteNameSpaceByName(AName : string) : boolean;
    // �� ����� DLL �����
    function DeleteNameSpaceByBinaryName(AName : string; ANameCompare : boolean) : boolean;
    // ���������� �� ����� �����
    function SortNameSpaceRegList : boolean;
    // ������������� ������, ���������� ��������� � ���������, ���������� ���-�� �����������
    function RenumberNameSpace : boolean;
    // �������������� ��������������
    function AutoRepairNameSpace : boolean;
    // **** �������� ��������� ****
    // �� GUID
    function DeleteProtocolByID(ID : integer) : boolean;
    // �� �����
    function DeleteProtocolByName(AName : string) : boolean;
    // �� ����� DLL �����
    function DeleteProtocolByBinaryName(AName : string; ANameCompare : boolean) : boolean;
    // ���������� �� ����� �����
    function SortProtocolRegList : boolean;
    // ������������� ������, ���������� ��������� � ���������, ���������� ���-�� �����������
    function RenumberProtocol : boolean;
    // �������������� ��������������
    function AutoRepairProtocol : boolean;
    // **** ����������� � ������ ������������������ ****
    // ����� ������
    function SearchErrors(AList : TStrings) : integer;
    // �������� HTML ������
    function CreateHTMLReport(ALines : TStrings; HideGoodFiles: boolean) : integer;
    function FullAutoRepair(ABackUpPath : string) : boolean;
    destructor Destroy; override;
    property Current_NameSpace_Catalog : string read FCurrent_NameSpace_Catalog;
    property Current_Protocol_Catalog  : string read FCurrent_Protocol_Catalog;
  end;
implementation
uses zTranslate;
 const
  MAX_PROTOCOL_CHAIN = 7;
  WSAPROTOCOL_LEN    = 255;
 type
  LPINT = ^longint;
  // �������� LPS
  TWSANameSpaceInfo = packed record
   NSProviderId   : TGUID;
   dwNameSpace    : DWord;
   fActive        : bool;
   dwVersion      : DWord;
   lpszIdentifier : LPSTR;
  end;
  TWSAProtocolChain = record
    ChainLen: Integer;  // the length of the chain,
    // length = 0 means layered protocol,
    // length = 1 means base protocol,
    // length > 1 means protocol chain
    ChainEntries: Array[0..MAX_PROTOCOL_CHAIN-1] of LongInt; // a list of dwCatalogEntryIds
  end;

  TWSAProtocol_InfoA = record
    dwServiceFlags1: LongInt;
    dwServiceFlags2: LongInt;
    dwServiceFlags3: LongInt;
    dwServiceFlags4: LongInt;
    dwProviderFlags: LongInt;
    ProviderId: TGUID;
    dwCatalogEntryId: LongInt;
    ProtocolChain: TWSAProtocolChain;
    iVersion: Integer;
    iAddressFamily: Integer;
    iMaxSockAddr: Integer;
    iMinSockAddr: Integer;
    iSocketType: Integer;
    iProtocol: Integer;
    iProtocolMaxOffset: Integer;
    iNetworkByteOrder: Integer;
    iSecurityScheme: Integer;
    dwMessageSize: LongInt;
    dwProviderReserved: LongInt;
    szProtocol: Array[0..WSAPROTOCOL_LEN+1-1] of Char;
  end;

  TProtocolPackedCatalogItem = packed record
   BinFileName  : array[0..$FF] of char;
   Unc1         : array[0..$77] of char;
   ProtocolName : array[0..$FF] of char;
   Unc2         : array[0..2000] of char;
  end;
{ TLSPManager }

constructor TLSPManager.Create;
var
 WSAData : TWSAData;
begin
 // ������� ������
 NameSpaceListWS  := nil;
 NameSpaceListReg := nil;
 ProtocolListReg  := nil;
 WSAEnumNameSpaceProviders := nil;
 // ������� �������� ����������
 hLib := LoadLibrary('ws2_32.dll');
 // ������������� Winsock
 WSAStartup($0202, WSAData);
 // ����� ����������� �������
 if hLib <> NULL then begin
  WSAEnumNameSpaceProviders := GetProcAddress(hLib, 'WSAEnumNameSpaceProvidersA');
  WSARemoveServiceClass     := GetProcAddress(hLib, 'WSARemoveServiceClass');
  WSCDeinstallProvider      := GetProcAddress(hLib, 'WSCDeinstallProvider');
  WSCUnInstallNameSpace     := GetProcAddress(hLib, 'WSCUnInstallNameSpace');
  WSAEnumProtocols          := GetProcAddress(hLib, 'WSAEnumProtocolsA');
  WSCEnableNSProvider       := GetProcAddress(hLib, 'WSCEnableNSProvider');
 end;
 // ����������� ������� ��������� � �������
 RefreshCatalogNames;
end;


destructor TLSPManager.Destroy;
begin
 NameSpaceListWS  := nil;
 NameSpaceListReg := nil;
 ProtocolListReg  := nil;
 inherited;
end;

function TLSPManager.SearchLSPFileByRegistry(ANameSpaceCatalog : string; AGUID: TGUID): string;
var
 Reg     : TRegistry;
 Lines   : TStringList;
 TmpGUID : TGUID;
 i       : integer;
begin
 Result := '';
 Lines := TStringList.Create;
 // ����� ����� ��������� �����
 Reg  := TRegistry.Create;
 try
  try
   Reg.RootKey := HKEY_LOCAL_MACHINE;
    if Reg.OpenKey(LSP_Reg_Key+'\'+ANameSpaceCatalog+'\Catalog_Entries', false) then begin
     Reg.GetKeyNames(Lines);
     Reg.CloseKey;
     for i := 0 to Lines.Count - 1 do
      if Reg.OpenKey(LSP_Reg_Key+'\'+ANameSpaceCatalog+'\Catalog_Entries\'+Lines[i], false) then begin
       if Reg.ReadBinaryData('ProviderId', TmpGUID, SizeOf(TmpGUID)) = SizeOf(TmpGUID) then
        if GUIDToString(TmpGUID) = GUIDToString(AGUID) then begin
         Result := NTFileNameToNormalName(Reg.ReadString('LibraryPath'));
         Reg.CloseKey;
         Break;
        end;
       Reg.CloseKey;
      end;
    end;
   finally
    Reg.Free;
   end;
 except // �������� ��� ������
 end;
 Lines.Free;
end;

function TLSPManager.RefreshNameSpaceListWS: boolean;
var
 buf : array[0..200] of TWSANameSpaceInfo;
 BufSize : DWORD;
 i, Res : integer;
 Current_NameSpace_Catalog : string;
 VersionInfo : TVersionInfo;
begin
 Result := false;
 // ������� �������
 NameSpaceListWS := nil;
 if @WSAEnumNameSpaceProviders = nil then exit;
 if Current_NameSpace_Catalog = '' then exit;
 // ���������� ������ LSP �����������
 BufSize := sizeof(Buf);
 ZeroMemory(@buf, BufSize);
 Res := WSAEnumNameSpaceProviders(@BufSize, @Buf[0]);
 SetLength(NameSpaceListWS, Res);
 // ���������� ������
 for i := 0 to Res-1 do begin
  NameSpaceListWS[i].NSProviderId   := Buf[i].NSProviderId;
  NameSpaceListWS[i].dwNameSpace    := Buf[i].dwNameSpace;
  NameSpaceListWS[i].fActive        := Buf[i].fActive;
  NameSpaceListWS[i].dwVersion      := Buf[i].dwVersion;
  NameSpaceListWS[i].lpszIdentifier := Trim(Buf[i].lpszIdentifier);
  NameSpaceListWS[i].BinFileName    := SearchLSPFileByRegistry(Current_NameSpace_Catalog, NameSpaceListWS[i].NSProviderId);
  NameSpaceListWS[i].BinFileExists  := FileExists(NameSpaceListWS[i].BinFileName);
  // ����������� ������ �����
  try
   VersionInfo := TVersionInfo.Create(NameSpaceListWS[i].BinFileName);
   NameSpaceListWS[i].BinFileInfo := VersionInfo.LegalCopyright + '('+VersionInfo.FileVersion+')';
   VersionInfo.Free;
  except end;
 end;
 Result := true;
end;

function TLSPManager.Refresh: boolean;
begin
 // ���������� ������ � ���������
 RefreshCatalogNames;
 // ��������� ������ � LSP ����� WinSock
 RefreshNameSpaceListWS;
 // ��������� ������ � LSP ����� ������
 RefreshNameSpaceListReg;
 // ��������� ������ � ���������� ����� ������
 RefreshProtocolInfo;
end;


function TLSPManager.RefreshNameSpaceListReg: boolean;
var
 Reg     : TRegistry;
 Lines   : TStringList;
 i       : integer;
 VersionInfo : TVersionInfo;
begin
 Result := false;
 NameSpaceListReg := nil;
 // ���� ������� ������� �� ���������, �� �����
 if Current_NameSpace_Catalog = '' then exit;
 Lines := TStringList.Create;
 // ����� ����� ��������� �����
 Reg  := TRegistry.Create;
 try
  Reg.RootKey := HKEY_LOCAL_MACHINE;
  if Reg.OpenKey(LSP_Reg_Key+'\'+Current_NameSpace_Catalog+'\Catalog_Entries', false) then begin
   // ��������� ������ ��������� ������
   Reg.GetKeyNames(Lines);
   Reg.CloseKey;
   SetLength(NameSpaceListReg, Lines.Count);
   // ����� ��������� "������" � "��������"
   for i := 0 to Lines.Count - 1 do begin
    NameSpaceListReg[i].Found     := false;
    NameSpaceListReg[i].IsCorrect := false;
   end;
   // ���������� �������
   for i := 0 to Lines.Count - 1 do
    // ��������� ���� ������� ������� ??
    if Reg.OpenKey(LSP_Reg_Key+'\'+Current_NameSpace_Catalog+'\Catalog_Entries\'+Lines[i], false) then begin
     // ������ GUID
     Reg.ReadBinaryData('ProviderId', NameSpaceListReg[i].NSProviderId, SizeOf(TGUID));
     NameSpaceListReg[i].Found := true;
     NameSpaceListReg[i].dwNameSpace    := Reg.ReadInteger('SupportedNameSpace');
     NameSpaceListReg[i].fActive        := Reg.ReadBool('Enabled');
     NameSpaceListReg[i].dwVersion      := Reg.ReadInteger('Version');
     NameSpaceListReg[i].lpszIdentifier := Trim(Reg.ReadString('DisplayString'));
     NameSpaceListReg[i].BinFileName    := NTFileNameToNormalName(Reg.ReadString('LibraryPath'));
     // ?? ��������, �� �������� �� ���� �������������
     if pos(':', NameSpaceListReg[i].BinFileName) = 0 then begin
      if FileExists(NormalDir(GetSystemDirectoryPath) + NameSpaceListReg[i].BinFileName) then
       NameSpaceListReg[i].BinFileName := NormalDir(GetSystemDirectoryPath) + NameSpaceListReg[i].BinFileName;
     end;
     NameSpaceListReg[i].BinFileExists  := FileExists(NameSpaceListReg[i].BinFileName);
     NameSpaceListReg[i].IsCorrect      := (NameSpaceListReg[i].BinFileName <> '') and
                                           (NameSpaceListReg[i].lpszIdentifier <> '')   ;
     NameSpaceListReg[i].RegKey         := Lines[i];
     NameSpaceListReg[i].CheckResults   := -1;
     // ����������� ������ �����
     try
      VersionInfo := TVersionInfo.Create(NameSpaceListReg[i].BinFileName);
      NameSpaceListReg[i].BinFileInfo := VersionInfo.LegalCopyright + '('+VersionInfo.FileVersion+')';
      VersionInfo.Free;
     except end;
     Reg.CloseKey;
    end;
   end;
 except
 end;
 // ���������� �������
 Reg.Free;
 Lines.Free;
 Result := true;
end;

function TLSPManager.RefreshCatalogNames: boolean;
begin
 // ����������� ������� ��������� � �������
 FCurrent_NameSpace_Catalog := Trim(RegKeyReadString(HKEY_LOCAL_MACHINE, LSP_Reg_Key, 'Current_NameSpace_Catalog'));
 FCurrent_Protocol_Catalog  := Trim(RegKeyReadString(HKEY_LOCAL_MACHINE, LSP_Reg_Key, 'Current_Protocol_Catalog'));
end;

function TLSPManager.RefreshProtocolInfo: boolean;
var
 Reg     : TRegistry;
 Tmp     : TProtocolPackedCatalogItem;
 Lines   : TStringList;
 i, Res  : integer;
 S : string;
 VersionInfo : TVersionInfo;
begin
 Result := false;
 ProtocolListReg := nil;
 // ���� ������� ������� �� ���������, �� �����
 if Current_NameSpace_Catalog = '' then exit;
 Lines := TStringList.Create;
 // ����� ����� ��������� �����
 Reg  := TRegistry.Create;
 try
  Reg.RootKey := HKEY_LOCAL_MACHINE;
  if Reg.OpenKey(LSP_Reg_Key+'\'+Current_Protocol_Catalog+'\Catalog_Entries', false) then begin
   // ��������� ������ ��������� ������
   Reg.GetKeyNames(Lines);
   Reg.CloseKey;
   SetLength(ProtocolListReg, Lines.Count);
   // ����� ��������� "������" � "��������"
   for i := 0 to Lines.Count - 1 do begin
    ProtocolListReg[i].Found   := false;
    ProtocolListReg[i].IsCorrect := false;
   end;
   // ���������� �������
   for i := 0 to Lines.Count - 1 do
    // ��������� ���� ������� ������� ??
    if Reg.OpenKey(LSP_Reg_Key+'\'+Current_Protocol_Catalog+'\Catalog_Entries\'+Lines[i], false) then begin
     Reg.ReadBinaryData('PackedCatalogItem', Tmp, SizeOf(Tmp));
     ProtocolListReg[i].Found := true;
     ProtocolListReg[i].BinFileName   := NTFileNameToNormalName(Trim(Tmp.BinFileName));
     // ?? ��������, �� �������� �� ���� �������������
     if pos(':', ProtocolListReg[i].BinFileName) = 0 then begin
      if FileExists(NormalDir(GetSystemDirectoryPath) + ProtocolListReg[i].BinFileName) then
       ProtocolListReg[i].BinFileName := NormalDir(GetSystemDirectoryPath) + ProtocolListReg[i].BinFileName;
     end;
     SetLength(S, 255);
     Res := UnicodeToUtf8(@S[1], @Tmp.ProtocolName[0], length(S));
     ProtocolListReg[i].lpszIdentifier := Trim(copy(S, 1, Res));
     ProtocolListReg[i].IsCorrect        := (ProtocolListReg[i].BinFileName <> '') and
                                            (ProtocolListReg[i].lpszIdentifier <> '')   ;
     // ?? ��������, �� �������� �� ���� �������������
     if pos(':', ProtocolListReg[i].BinFileName) = 0 then begin
      if FileExists(NormalDir(GetSystemDirectoryPath) + ProtocolListReg[i].BinFileName) then
       ProtocolListReg[i].BinFileName := NormalDir(GetSystemDirectoryPath) + ProtocolListReg[i].BinFileName;
     end;
     ProtocolListReg[i].BinFileExists  := FileExists(ProtocolListReg[i].BinFileName);
     ProtocolListReg[i].RegKey         := Lines[i];
     ProtocolListReg[i].CheckResults   := -1;
     // ����������� ������ �����
     try
      VersionInfo := TVersionInfo.Create( ProtocolListReg[i].BinFileName );
      ProtocolListReg[i].BinFileInfo := VersionInfo.LegalCopyright + '('+VersionInfo.FileVersion+')';
      VersionInfo.Free;
     except end;
     Reg.CloseKey;
    end;
   end;
 except
 end;
 // ���������� �������
 Reg.Free;
 Lines.Free;
 Result := true;
end;

function TLSPManager.DeleteNameSpaceByGUID(AGUID: TGUID): boolean;
var
 i, Res : integer;
 Reg : TRegistry;
begin
 Result := false;
 // ���������� ������
 RefreshNameSpaceListReg;
 Res := -1;
 // ����� ������������ ����
 for i := 0 to Length(NameSpaceListReg)-1 do
  if GUIDToString(NameSpaceListReg[i].NSProviderId) = GUIDToString(AGUID) then begin
   Res := i;
   Break;
  end;
 // ������ ������� ?
 if Res = -1 then exit;
 Reg := TRegistry.Create;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 // �������� ����� �������
 Reg.DeleteKey(LSP_Reg_Key+'\'+Current_NameSpace_Catalog+'\Catalog_Entries\'+NameSpaceListReg[Res].RegKey);
 Reg.CloseKey;
 Reg.Free;
 RenumberNameSpace;
 Result := true;
end;

function TLSPManager.DeleteNameSpaceByBinaryName(AName: string;
  ANameCompare: boolean): boolean;
var
 i : integer;
begin
 // ���������� ������
 RefreshNameSpaceListReg;
 // ����� ������������ ����
 for i := 0 to Length(NameSpaceListReg)-1 do
  if (not(ANameCompare) and (AnsiUpperCase(NameSpaceListReg[i].BinFileName) = AnsiUpperCase(AName))) or
     (ANameCompare and (ExtractFileName(AnsiUpperCase(NameSpaceListReg[i].BinFileName)) = ExtractFileName(AnsiUpperCase(AName)))) then begin
   Result := DeleteNameSpaceByGUID(NameSpaceListReg[i].NSProviderId);
   Break;
  end;
end;

function TLSPManager.DeleteNameSpaceByName(AName: string): boolean;
var
 i : integer;
begin
 // ���������� ������
 RefreshNameSpaceListReg;
 // ����� ������������ ����
 for i := 0 to Length(NameSpaceListReg)-1 do
  if AnsiUpperCase(NameSpaceListReg[i].lpszIdentifier) = AnsiUpperCase(AName) then begin
   Result := DeleteNameSpaceByGUID(NameSpaceListReg[i].NSProviderId);
   Break;
  end;
end;


function TLSPManager.SortNameSpaceRegList: boolean;
var
 i, j : integer;
 Tmp : TNameSpaceInfo;
begin
 for i := 0 to Length(NameSpaceListReg) - 2 do
  for j := i+1 to Length(NameSpaceListReg) - 1 do
   if NameSpaceListReg[i].RegKey > NameSpaceListReg[j].RegKey then begin
    Tmp := NameSpaceListReg[i];
    NameSpaceListReg[i] := NameSpaceListReg[j];
    NameSpaceListReg[j] := Tmp;
   end;
end;

function TLSPManager.RenumberNameSpace: boolean;
var
 i, KeyNameDigits, LastKeyNum : integer;
 KeyNameMask           : string;
 Reg : TRegistry;
begin
 Result := false;
 // ���������� ������ ������
 RefreshNameSpaceListReg;
 // ���������� ���������� �� ����� �����
 SortNameSpaceRegList;
 // ����� ������������ ������ ����� (������ ��� ������ � �������� ������)
 KeyNameDigits := 1;
 for i := 0 to Length(NameSpaceListReg)-1 do
  if StrToIntDef(NameSpaceListReg[i].RegKey, -1) >= 0 then
   if Length(NameSpaceListReg[i].RegKey) > KeyNameDigits then
    KeyNameDigits := Length(NameSpaceListReg[i].RegKey);
 // ������������ ������ ����� �������, ���������� ��������
 if (KeyNameDigits < 4) or (KeyNameDigits > 14) then
  KeyNameDigits := 12;
 // �������� ��������� �����
 KeyNameMask := '';
 for i := 1 to KeyNameDigits do
  KeyNameMask := KeyNameMask + '0';
 LastKeyNum := 0;
 // ���� ������������� ������ ��� ������������������� �������
 Reg := TRegistry.Create;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 for i := 0 to Length(NameSpaceListReg)-1 do begin
  if StrToIntDef(NameSpaceListReg[i].RegKey, 0) <> (LastKeyNum + 1) then
   Reg.MoveKey(LSP_Reg_Key+'\'+Current_NameSpace_Catalog+'\Catalog_Entries\'+NameSpaceListReg[i].RegKey,
               LSP_Reg_Key+'\'+Current_NameSpace_Catalog+'\Catalog_Entries\'+FormatFloat(KeyNameMask,LastKeyNum + 1),
               true);
  inc(LastKeyNum);
 end;
 // ������ ��������� ���������� ������ � Num_Catalog_Entries
 if Reg.OpenKey(LSP_Reg_Key+'\'+Current_NameSpace_Catalog, false) then begin
  Reg.WriteInteger('Num_Catalog_Entries', Length(NameSpaceListReg));
  Reg.CloseKey;
 end;
 Reg.Free;
 Result := true;
end;

function TLSPManager.AutoRepairNameSpace: boolean;
var
 i : integer;
begin
 RefreshNameSpaceListReg;
 // �������� �������, ��� ������� ��� �����
 i := 0;
 while i <= Length(NameSpaceListReg) - 1 do
  if not(NameSpaceListReg[i].BinFileExists) then
   DeleteNameSpaceByGUID(NameSpaceListReg[i].NSProviderId)
    else inc(i);
 // �������������
 RenumberNameSpace;
end;

function TLSPManager.AutoRepairProtocol: boolean;
var
 i : integer;
begin
 RefreshProtocolInfo;
 i := 0;
 while i <= Length(ProtocolListReg) - 1 do
  if not(ProtocolListReg[i].BinFileExists) then
   DeleteProtocolByID(i) else inc(i);
end;

function TLSPManager.DeleteProtocolByID(ID: integer): boolean;
var
 Reg : TRegistry;
begin
 Result := false;
 // ������ ������� ?
 if not((ID >= 0) and (ID < Length(ProtocolListReg))) then exit;
 Reg := TRegistry.Create;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 // �������� ����� �������
 Reg.DeleteKey(LSP_Reg_Key+'\'+Current_Protocol_Catalog+'\Catalog_Entries\'+ProtocolListReg[ID].RegKey);
 Reg.CloseKey;
 Reg.Free;
 RenumberProtocol;
 Result := true;
end;

function TLSPManager.DeleteProtocolByBinaryName(AName: string;
  ANameCompare: boolean): boolean;
var
 i : integer;
begin
 for i := 0 to Length(ProtocolListReg)-1 do
  if (not(ANameCompare) and (AnsiUpperCase(ProtocolListReg[i].lpszIdentifier) = AnsiUpperCase(AName))) or
     (ANameCompare and (ExtractFileName(AnsiUpperCase(ProtocolListReg[i].lpszIdentifier)) = ExtractFileName(AnsiUpperCase(AName)))) then
       DeleteProtocolByID(i);
end;

function TLSPManager.DeleteProtocolByName(AName: string): boolean;
var
 i : integer;
begin
 for i := 0 to Length(ProtocolListReg)-1 do
  if AnsiUpperCase(ProtocolListReg[i].lpszIdentifier) = AnsiUpperCase(AName) then
   DeleteProtocolByID(i);
end;

function TLSPManager.RenumberProtocol: boolean;
var
 i, KeyNameDigits, LastKeyNum : integer;
 KeyNameMask           : string;
 Reg : TRegistry;
begin
 Result := false;
 // ���������� ������ ������
 RefreshProtocolInfo;
 // ���������� ���������� �� ����� �����
 SortProtocolRegList;
 // ����� ������������ ������ ����� (������ ��� ������ � �������� ������)
 KeyNameDigits := 1;
 for i := 0 to Length(ProtocolListReg)-1 do
  if StrToIntDef(ProtocolListReg[i].RegKey, -1) >= 0 then
   if Length(ProtocolListReg[i].RegKey) > KeyNameDigits then
    KeyNameDigits := Length(ProtocolListReg[i].RegKey);
 // ������������ ������ ����� �������, ���������� ��������
 if (KeyNameDigits < 4) or (KeyNameDigits > 14) then
  KeyNameDigits := 12;
 // �������� ��������� �����
 KeyNameMask := '';
 for i := 1 to KeyNameDigits do
  KeyNameMask := KeyNameMask + '0';
 LastKeyNum := 0;
 // ���� ������������� ������ ��� �������� ����������� �������
 Reg := TRegistry.Create;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 for i := 0 to Length(ProtocolListReg)-1 do begin
  if StrToIntDef(ProtocolListReg[i].RegKey, 0) <> (LastKeyNum + 1) then
   Reg.MoveKey(LSP_Reg_Key+'\'+Current_Protocol_Catalog+'\Catalog_Entries\'+ProtocolListReg[i].RegKey,
               LSP_Reg_Key+'\'+Current_Protocol_Catalog+'\Catalog_Entries\'+FormatFloat(KeyNameMask,LastKeyNum + 1),
               true);
  inc(LastKeyNum);
 end;
 // ������ ��������� ���������� ������ � Num_Catalog_Entries
 if Reg.OpenKey(LSP_Reg_Key+'\'+Current_Protocol_Catalog, false) then begin
  Reg.WriteInteger('Num_Catalog_Entries', Length(ProtocolListReg));
  Reg.CloseKey;
 end;
 Reg.Free;
 Result := true;
end;

function TLSPManager.SortProtocolRegList: boolean;
var
 i, j : integer;
 Tmp : TProtocolInfo;
begin
 for i := 0 to Length(ProtocolListReg) - 2 do
  for j := i+1 to Length(ProtocolListReg) - 1 do
   if ProtocolListReg[i].RegKey > ProtocolListReg[j].RegKey then begin
    Tmp := ProtocolListReg[i];
    ProtocolListReg[i] := ProtocolListReg[j];
    ProtocolListReg[j] := Tmp;
   end;
end;

function TLSPManager.SearchErrors(AList: TStrings): integer;
var
 i, Num_Catalog_Entries : integer;
 Reg : TRegistry;
begin
 Refresh;
 Result := 0;
 Reg := TRegistry.Create;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 if Reg.OpenKey(LSP_Reg_Key+'\'+Current_NameSpace_Catalog, false) then begin
  Num_Catalog_Entries := -1;
  try Num_Catalog_Entries := Reg.ReadInteger('Num_Catalog_Entries'); except end;
  if Num_Catalog_Entries = -1 then begin
   AList.Add(TranslateStr('$AVZ0638'));
   inc(Result);
  end else
   if Length(NameSpaceListReg) <> Num_Catalog_Entries then begin
    AList.Add(TranslateStr('$AVZ0639 '+IntToStr(Num_Catalog_Entries)+' $AVZ0487 '+IntToStr(Length(NameSpaceListReg))));
    inc(Result);
   end;
  Reg.CloseKey;
 end;
 // ������������ ����
 for i := 0 to Length(NameSpaceListReg) - 1 do begin
  if not(NameSpaceListReg[i].BinFileExists) then begin
   AList.Add(TranslateStr('$AVZ0637: "'+NameSpaceListReg[i].lpszIdentifier+'" --> $AVZ0623 ')+NameSpaceListReg[i].BinFileName);
   inc(Result);
  end;
  if StrToIntDef(NameSpaceListReg[i].RegKey, -1) = -1 then begin
   AList.Add(TranslateStr('$AVZ0637: "'+NameSpaceListReg[i].lpszIdentifier+'" --> $AVZ0509 ')+NameSpaceListReg[i].RegKey);
   inc(Result);
  end else begin
   if (i=0) and (StrToIntDef(NameSpaceListReg[i].RegKey, -1) <> 1) then begin
    AList.Add(TranslateStr('$AVZ0637: "'+NameSpaceListReg[i].lpszIdentifier+'" --> $AVZ0528 (')+NameSpaceListReg[i].RegKey+')');
    inc(Result);
   end;
   if (i>0) and (StrToIntDef(NameSpaceListReg[i].RegKey, -1) - StrToIntDef(NameSpaceListReg[i-1].RegKey, -1) <> 1) then begin
    AList.Add(TranslateStr('$AVZ0637: "'+NameSpaceListReg[i].lpszIdentifier+'" --> $AVZ0939'));
    inc(Result);
   end;
  end;
 end;
 // ***** ��������� *****
 if Reg.OpenKey(LSP_Reg_Key+'\'+Current_Protocol_Catalog, false) then begin
  Num_Catalog_Entries := -1;
  try Num_Catalog_Entries := Reg.ReadInteger('Num_Catalog_Entries'); except end;
  if Num_Catalog_Entries = -1 then begin
   AList.Add(TranslateStr('$AVZ0640: $AVZ0092'));
   inc(Result);
  end else
   if Length(ProtocolListReg) <> Num_Catalog_Entries then begin
    AList.Add(TranslateStr('$AVZ0640: $AVZ0349 '+IntToStr(Num_Catalog_Entries)+' $AVZ0487 ')+IntToStr(Length(ProtocolListReg)));
    inc(Result);
   end;
  Reg.CloseKey;
 end;
 for i := 0 to Length(ProtocolListReg) - 1 do begin
  if not(ProtocolListReg[i].BinFileExists) then begin
   AList.Add(TranslateStr('$AVZ0640 = "'+ProtocolListReg[i].lpszIdentifier+'" --> $AVZ0623 ')+ProtocolListReg[i].BinFileName);
   inc(Result);
  end;
  if StrToIntDef(ProtocolListReg[i].RegKey, -1) = -1 then begin
   AList.Add(TranslateStr('$AVZ0640 = "'+ProtocolListReg[i].lpszIdentifier+'" --> $AVZ0509 ')+ProtocolListReg[i].RegKey);
   inc(Result);
  end else begin
   if (i=0) and (StrToIntDef(ProtocolListReg[i].RegKey, -1) <> 1) then begin
    AList.Add(TranslateStr('$AVZ0640: "'+ProtocolListReg[i].lpszIdentifier+'" --> $AVZ0528 ('+ProtocolListReg[i].RegKey+')'));
    inc(Result);
   end;
   if (i>0) and (StrToIntDef(ProtocolListReg[i].RegKey, -1) - StrToIntDef(ProtocolListReg[i-1].RegKey, -1) <> 1) then begin
    AList.Add(TranslateStr('$AVZ0640: "'+ProtocolListReg[i].lpszIdentifier+'" --> $AVZ0939'));
    inc(Result);
   end;
  end;
 end;
 Reg.Free;
end;

function TLSPManager.FullAutoRepair(ABackUpPath : string): boolean;
var
 Lines : TStrings;
begin
 Result := false;
 ABackUpPath := Trim(ABackUpPath);
 if ABackUpPath <> '' then begin
  NormalDir(ABackUpPath);
  zForceDirectories(ABackUpPath);
  Lines := TStringList.Create;
  Lines.Add('REGEDIT4');
  Lines.Add('');
  Lines.Add('[-'+LSP_Reg_Key+']');
  ExpRegKey(HKEY_LOCAL_MACHINE, LSP_Reg_Key, Lines);
  try
   Lines.SaveToFile(ABackUpPath+'SPI_'+FormatDateTime('YYYYMMDD_HHNNSS', Now)+'.reg');
  except
  end;
  Lines.Free;
 end;
 // �������������� ��������������
 AutoRepairNameSpace;
 AutoRepairProtocol;
 Result := true;
end;

function TLSPManager.SetNameSpaceActive(ID: integer;
  NewStatus: boolean): boolean;
var
 Reg : TRegistry;
begin
 Result := false;
 // ������ ������� ?
 if not((ID >= 0) and (ID < Length(NameSpaceListReg))) then exit;
 Reg := TRegistry.Create;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 // �������� ����� �������
 if Reg.OpenKey(LSP_Reg_Key+'\'+Current_NameSpace_Catalog+'\Catalog_Entries\'+NameSpaceListReg[ID].RegKey, false) then begin;
  Reg.WriteBool('Enabled', NewStatus);
  Reg.CloseKey;
 end;
 Reg.Free;
 RenumberProtocol;
 Result := true;
end;

function TLSPManager.CreateHTMLReport(ALines: TStrings; HideGoodFiles: boolean): integer;
var
 i, Res,  GoodFiles : integer;
 S, ST, FileInfoStr : string;
begin
 ALines.Add('<TABLE '+HTML_TableFormat1+'>');
 ALines.Add(TranslateStr('<B>$AVZ0788'));
 ALines.Add('<TR '+HTMP_TableHeader+'>'+HTML_TableHeaderTD+'$AVZ0787'+HTML_TableHeaderTD+'$AVZ1051'+HTML_TableHeaderTD+'$AVZ0317'+HTML_TableHeaderTD+'$AVZ0581'+HTML_TableHeaderTD+'GUID');
 GoodFiles := 0;
 for i := 0 to Length(NameSpaceListReg)-1 do begin
  if NameSpaceListReg[i].CheckResults = 0  then begin
   S := 'bgColor='+HTMP_BgColorTrusted;
   inc(GoodFiles);
  end else S :=  'bgColor='+HTMP_BgColor2;
  if not(HideGoodFiles and (NameSpaceListReg[i].CheckResults = 0)) then begin
   FileInfoStr := FormatFileInfo(NameSpaceListReg[i].BinFileName, ', ');
   ALines.Add('<TR '+S+'>'+
                 '<TD>'+HTMLNVL(NameSpaceListReg[i].lpszIdentifier)+
                 '<TD>'+ST+
                 '<TD>'+'<a href="" title="'+FileInfoStr+'">'+HTMLNVL(NameSpaceListReg[i].BinFileName)+'</a>'+GenScriptTxt(NameSpaceListReg[i].BinFileName)+
                 '<TD>'+HTMLNVL(NameSpaceListReg[i].BinFileInfo)+
                 '<TD>'+HTMLNVL(GUIDToString(NameSpaceListReg[i].NSProviderId))
                 );
  end;
 end;
 ALines.Add('<TR bgColor='+HTMP_BgColorFt+'><TD colspan=7>$AVZ0538 - '+IntToStr(Length(NameSpaceListReg))+', $AVZ0586 - '+IntToStr(GoodFiles));
 ALines.Add('</TABLE>');
 //
 ALines.Add('<B>$AVZ0789');
 ALines.Add('<TABLE '+HTML_TableFormat1+'>');
 ALines.Add('<TR '+HTMP_TableHeader+'>'+HTML_TableHeaderTD+'$AVZ0787'+HTML_TableHeaderTD+'$AVZ0317'+HTML_TableHeaderTD+'$AVZ0581');
 GoodFiles := 0;
 for i := 0 to Length(ProtocolListReg)-1 do begin
  if ProtocolListReg[i].CheckResults = 0 then begin
   S := 'bgColor='+HTMP_BgColorTrusted;
   inc(GoodFiles);
  end else S :=  'bgColor='+HTMP_BgColor2;
  if not(HideGoodFiles and (ProtocolListReg[i].CheckResults = 0)) then begin
   FileInfoStr := FormatFileInfo(ProtocolListReg[i].BinFileName, ', ');
   ALines.Add('<TR '+S+'>'+
                 '<TD>'+HTMLNVL(ProtocolListReg[i].lpszIdentifier)+
                 '<TD>'+'<a href="" title="'+FileInfoStr+'">'+HTMLNVL(ProtocolListReg[i].BinFileName)+'</a>'+GenScriptTxt(ProtocolListReg[i].BinFileName)+
                 '<TD>'+HTMLNVL(ProtocolListReg[i].BinFileInfo)
                 );
  end;
 end;
 ALines.Add('<TR bgColor='+HTMP_BgColorFt+'><TD colspan=7>$AVZ0538 - '+IntToStr(Length(ProtocolListReg))+', $AVZ0586 - '+IntToStr(GoodFiles));
 ALines.Add('</TABLE>');
 ALines.Add('<B>$AVZ0930');
 ALines.Add('<TABLE '+HTML_TableFormat1+'><pre>');
 Res := SearchErrors(ALines);
 if Res > 0 then begin
  ALines.Add('$AVZ0117 - '+IntToStr(Res));
  ALines.Add('$AVZ0132');
 end else begin
  ALines.Add(TranslateStr('$AVZ0463'));
 end;
 ALines.Add('</pre></TABLE>');
 // ������� ���������
 TranslateLines(ALines);
end;

end.
