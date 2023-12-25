unit zProtocols;

interface
uses Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, RxVerInf,
     Registry, zSharedFunctions, zAVKernel, zAVZKernel;
type
 // ���������� � ����������
 TProtocolInfo = record
  RegKey          : string;  // ���� �������
  RegSuffix       : string;  // �������
  RegKeyName      : string;
  CLSID           : string;  // CLSID
  BinFile         : string;  // �������� ����
  Descr           : string;  // ��������
  LegalCopyright  : string;  // ���������
  Prim            : string;  // ����������
  CheckResult     : integer; // ��������� �������� �� ���� ���������� ��������
  ProtocolType    : integer; // 1 - ������, 2 - ����������, 3 - NamespaceHandler
 end;
 TProtocolInfoArray = array of TProtocolInfo;

 // �������� ����������
 TProtocolList = class
   ProtocolInfoArray : TProtocolInfoArray;
   constructor Create;
   destructor Destroy; override;
   function RefresList : boolean;
   function ScanProtocolKeys(APrefix : string) : boolean;
   function GetItemEnabledStatus(ProtocolInfo : TProtocolInfo) : integer;
   function DeleteItem(ProtocolInfo : TProtocolInfo) : boolean;
   function SetItemEnabledStatus(var ProtocolInfo : TProtocolInfo; NewStatus : boolean) : boolean;
   function AddProtocol(ProtocolInfo : TProtocolInfo; AType : integer) : boolean;
 end;

implementation
uses  zScriptingKernel;
{ TProtocolList }

function TProtocolList.AddProtocol(ProtocolInfo: TProtocolInfo;
  AType: integer): boolean;
var
 VersionInfo : TVersionInfo;
begin
 ProtocolInfo.BinFile := Trim(NTFileNameToNormalName(ProtocolInfo.BinFile));
 ProtocolInfo.CheckResult  := FileSignCheck.CheckFile(ProtocolInfo.BinFile);
 ProtocolInfo.ProtocolType := AType;
 try
  VersionInfo := TVersionInfo.Create(ProtocolInfo.BinFile);
  ProtocolInfo.Descr := VersionInfo.FileDescription;
  ProtocolInfo.LegalCopyright := VersionInfo.LegalCopyright;
  VersionInfo.Free;
 except end;
 SetLength(ProtocolInfoArray, Length(ProtocolInfoArray)+1);
 ProtocolInfoArray[Length(ProtocolInfoArray)-1] := ProtocolInfo;
end;

constructor TProtocolList.Create;
begin
 ProtocolInfoArray := nil;
end;

function TProtocolList.DeleteItem(ProtocolInfo: TProtocolInfo): boolean;
var
 Reg : TRegistry;
begin
 Result := false;
 Reg := TRegistry.Create;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 Reg.DeleteKey(ProtocolInfo.RegKey+'\'+ProtocolInfo.RegSuffix);
 Result := true;
 Reg.Free;
end;

destructor TProtocolList.Destroy;
begin
 ProtocolInfoArray := nil;
 inherited;
end;

function TProtocolList.GetItemEnabledStatus(
  ProtocolInfo: TProtocolInfo): integer;
begin
 Result := 1;
 if copy(ProtocolInfo.RegKey, length(ProtocolInfo.RegKey), 1) = '-' then
  Result := 0;
end;

function TProtocolList.RefresList: boolean;
begin
 ProtocolInfoArray := nil;
 ScanProtocolKeys('');
 ScanProtocolKeys('-');
end;

function TProtocolList.ScanProtocolKeys(APrefix: string): boolean;
var
 Reg  : TRegistry;
 List : TStrings;
 Tmp  : TProtocolInfo;
 i    : integer;
 BaseKey, S    : string;
begin
 Reg  := TRegistry.Create;
 List := TStringList.Create;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 // ����� ��������
 BaseKey := 'SOFTWARE\Classes\PROTOCOLS'+APrefix;
 if Reg.OpenKey(BaseKey+'\Filter', false) then begin
  Reg.GetKeyNames(List);
  Reg.CloseKey;
  for i := 0 to List.Count - 1 do begin
   Tmp.RegKey     := BaseKey;
   Tmp.RegSuffix  := 'Filter\'+List[i];
   Tmp.RegKeyName := List[i];
   if Reg.OpenKey(Tmp.RegKey + '\' + Tmp.RegSuffix, false) then begin
    Tmp.CLSID   := Trim(Reg.ReadString('CLSID'));
    Tmp.Prim    := Trim(Reg.ReadString(''));
    Reg.CloseKey;
    S := copy(Tmp.CLSID, 2, length(Tmp.CLSID)-2);
    Tmp.BinFile := CLSIDFileName(S);
    if Tmp.BinFile <> '' then
     AddProtocol(Tmp, 1);
   end;
  end;
 end;
 // ����� ��������
 BaseKey := 'SOFTWARE\Classes\PROTOCOLS'+APrefix;
 if Reg.OpenKey(BaseKey+'\Handler', false) then begin
  Reg.GetKeyNames(List);
  Reg.CloseKey;
  for i := 0 to List.Count - 1 do begin
   Tmp.RegKey     := BaseKey;
   Tmp.RegSuffix  := 'Handler\'+List[i];
   Tmp.RegKeyName := List[i];
   if Reg.OpenKey(Tmp.RegKey + '\' + Tmp.RegSuffix, false) then begin
    Tmp.CLSID   := Trim(Reg.ReadString('CLSID'));
    Tmp.Prim    := Trim(Reg.ReadString(''));
    Reg.CloseKey;
    S := copy(Tmp.CLSID, 2, length(Tmp.CLSID)-2);
    Tmp.BinFile := CLSIDFileName(S);
    if Tmp.BinFile <> '' then
     AddProtocol(Tmp, 2);
   end;
  end;
 end;
 List.Free;
 Reg.Free;
end;

function TProtocolList.SetItemEnabledStatus(
  var ProtocolInfo: TProtocolInfo; NewStatus: boolean): boolean;
var
 Reg : TRegistry;
begin
 Result := false;
 // ���. ������ - ������������ ��������� ��������� � ���������� �����������
 if NewStatus      and  (GetItemEnabledStatus(ProtocolInfo) <> 0) then exit;
 if not(NewStatus) and  (GetItemEnabledStatus(ProtocolInfo) <> 1) then exit;
 // ����������
 if not(NewStatus) then begin
  Reg := TRegistry.Create;
  Reg.RootKey := HKEY_LOCAL_MACHINE;
  Reg.MoveKey(ProtocolInfo.RegKey+'\'+ProtocolInfo.RegSuffix, ProtocolInfo.RegKey+'-\'+ProtocolInfo.RegSuffix, true);
  ProtocolInfo.RegKey := ProtocolInfo.RegKey + '-';
  Result := true;
 end;
 // �������������
 if NewStatus then begin
  Reg := TRegistry.Create;
  Reg.RootKey := HKEY_LOCAL_MACHINE;
  Reg.MoveKey(ProtocolInfo.RegKey+'\'+ProtocolInfo.RegSuffix, copy(ProtocolInfo.RegKey, 1, length(ProtocolInfo.RegKey)-1)+'\'+ProtocolInfo.RegSuffix, true);
  ProtocolInfo.RegKey := copy(ProtocolInfo.RegKey, 1, length(ProtocolInfo.RegKey)-1);
  Result := true;
 end;
end;

end.
