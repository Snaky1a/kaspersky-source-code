unit zSharedFunctions;

interface
uses windows, Messages, registry, SysUtils, ShellAPI, Classes, orautil, ntdll, Forms,
     zBase64, md5, zxml;
const
 REG_NONE                       = 0;
 REG_SZ                         = 1;
 REG_EXPAND_SZ                  = 2;

 REG_BINARY                     = 3;
 REG_DWORD                      = 4;
 REG_DWORD_LITTLE_ENDIAN        = 4;
 REG_DWORD_BIG_ENDIAN           = 5;
 REG_LINK                       = 6;
 REG_MULTI_SZ                   = 7;
 REG_RESOURCE_LIST              = 8;
 REG_FULL_RESOURCE_DESCRIPTOR   = 9;
 REG_RESOURCE_REQUIREMENTS_LIST = 10;

 // ��������� ����� ������������� ����� �� ��� GUID
 Function GetBinFileByGUID(AGUID : TGUID) : string; overload;
 // ��������� ����� ������������� ����� �� ��� GUID
 Function GetBinFileByGUID(AGUID : string) : string;overload;
 // ������ ����� �������
 Function RegKeyReadString(ARootKey : HKey; AKeyName, AParamName : string) : string;
 Function RegKeyReadInt(ARootKey : HKey; AKeyName, AParamName : string) : integer;
 // �������������� NT ����� ���� � ����������
 Function NTFileNameToNormalName(AFileName : string) : string;
 // ���������� ����� �����
 Function ExpandFileNameEx(AFileName : string) : string;
 // ���������/����������� ���������� NT
 Function AdjustPrivileges(APrivStr : string; NewState : boolean) : boolean;
 // ��������������� ����-������� ����� � ����������� ����-�����
 function FileTimeToDateTime(MyFileTime: TFileTime): TDateTime;
 // ���������� ������ ��� HTML ������ (������ ������ ���������� &nbsp;)
 function HTMLNVL(S : string) : string;
 // �������� CRLF
 function DelCRLF(S : string) : string;
 // �������������� ������ ��� XML
 function XMLStr(S : string) : string;
 // ������������ ����� ����� (� ���������� ���������� � �.�.)
 function NormalProgramFileName(AFileName : string; DefExt : string) : string;
 // ����� � ���� (����� ������� �� ���������)
 function WebSearchInYandex(AKeyWord : string) : boolean;
 function WebSearchInGoogle(AKeyWord : string) : boolean;
 function WebSearchInRambler(AKeyWord : string) : boolean;
 function WebOpenURLinBrowser(AURL : string) : boolean;
 // ���� ���������� � ����� � �� ��������������
 function FormatFileInfo(AFileName : string; DelimStr : string = ',<br>') : string;
 function FormatXMLFileInfo(AFileName : string; AGoodDBCheck : boolean = false) : string;
 // ��������� ������ ������� kernel32.dll �� �����
 function GetProcAddrFromKernelDLL(aProcName: String): Pointer;
 // �������� ��������� ���������� �� ��������� ��������
 function RemoteFreeLibrary(PID:Cardinal; HModule : Cardinal) : boolean;
 // ��������� ���-�� ���� ��������� ��������
 function GetWindowsCountByPid(APID:Cardinal; AVisibleOnly : boolean) : integer;
 // ��������� ���������� � �����
 function GetFileInfo(AFileName : string; var SR : TSearchRec) : boolean;
 // ����������� ������ API ������� (������ JMP)
 function ModifyProgrammAPICall(AFunctionStubPtr,
  ANewAPIAddr: pointer): boolean;
 // ��������� PID �������� �� ����
 function GetPIDByWindowHandle(AHandle : dword) : dword;
 // ��������� ����� ���. ����� �������� �� ��� �����
 function GetProcessByPID(APID : dword) : string;
 // ��������� ��������� ������ ��������
 function GetProcessCmdLineByPID(APID : dword) : string;   // ����� 1
 function GetProcessCmdLineByPID1(APID : dword) : string;  // ����� 2
 // ��������� ����� ����� ������� �� ��� Handle
 function GetRegKeyNameByHandle(AHandle : dword) : string;
 // ��������� ��������� ���� �� ��� Handle
 Function GetWindowTextByHandle(AHandle : dword) : string;
 // ��������� ����� ����� �� ��� Handle
 Function GetFileNameByHandle(AHandle : dword) : string;
 // ��������� ����� �������� �� ��� Handle
 function GetProcessImageNameByHandle(hProcess : dword) : string;
 // ��������� ����� �������� �� ��� PID
 function GetProcessImageNameByPID(APID : dword) : string;
 // ��������� PID �������� �� Handle
 function GetProcessIDByHandle(hProcess : dword) : dword;

 // ����������� �������� ����� ������ �������
 function InstallDriver(ADriverFile, AKeyName, ADisplayName : string; AStartType : byte = 3) : dword;
 // ������������� �������� (�������� ����� �������)
 function UnInstallDriver(AKeyName : string) : dword;
 // �������� ��������
 function LoadDriver(AKeyName : string) : dword;
 // �������� ��������
 function UnLoadDriver(AKeyName : string) : dword;
 // ��������� ���������������� ����� ��� ��������
 function GenerateRandomName(ALength, ACode : integer) : string;
 // �������� ������� ���� �������������� � ������� ������
 function UserIsNTAdmin: Boolean;
 // ����� ����� �� ��������� �����
 function SearchSysPath(FileName : string; DefExt : string = '') : string;
 // �������������� ����� ����� � �������, ��������� � KernelMode
 function RegKeyToSystemRegKey(AKey : string) : string;
 // ����������� ����� ����� Hosts
 function GetHostsFileName : string;
 // ����� ���� � ����� ProgramFiles
 Function GetProgramFilesDirectoryPath : string;   // Program Files

 // ������ RegEdit � �������� � ��� ��������� �����
 Function RegEditCtl(ARun : boolean; AKey, AParam : string) : boolean;
 // ������� ���������� ����� �������
 Function ExpRegKey(ARoot : HKEY; AKey : string; Lines : TStrings) : boolean;

 // ���������� MD5 ����� �� ��� �����
 Function CalkFileMD5(AFileName : string) : string;

implementation
uses
 zutil, SystemMonitor, zAVKernel;
var
 CU_KEY : String;

function GetFileInfo(AFileName : string; var SR : TSearchRec) : boolean;
begin
 Result := false;
 Result := FindFirst(AFileName, faAnyFile, SR) = 0;
 FindClose(SR);
end;

 // ��������������� ����-������� ����� � ����������� ����-�����
function FileTimeToDateTime(MyFileTime: TFileTime): TDateTime;
var
  LTime: TFileTime;
  SystemTime : TSystemTime;
begin
  FileTimeToLocalFileTime(MyFileTime, LTime);
  FileTimeToSystemTime(LTime, SystemTime);
  Result := SystemTimeToDateTime(SystemTime);
end;

// ��������� ����� ������������� ����� �� ��� GUID
Function GetBinFileByGUID(AGUID : string) : string;
var
 Reg : TRegistry;
 KeyName : string;
begin
 Result := '';
 AGUID := Trim(AGUID);
 // �������� ������ (��� ��� ����
 if copy(AGUID, 1, 1) = '{' then delete(AGUID, 1, 1);
 if copy(AGUID, length(AGUID), 1) = '}' then delete(AGUID, length(AGUID), 1);
 AGUID := Trim(AGUID);
 if AGUID = '' then exit;
 Reg := TRegistry.Create;
 try
  Reg.RootKey := HKEY_CLASSES_ROOT;
  KeyName := 'CLSID\{'+AGUID+'}';
  // ����� ���� ���������� ?
  if Reg.OpenKey(KeyName, false) then begin
   Reg.CloseKey;
   // ����� ����� InprocServer32
   Result := Trim(RegKeyReadString(HKEY_CLASSES_ROOT, KeyName+'\InprocServer32', '')); //#DNL
   if Result <> '' then exit;
   // ����� ����� LocalServer32
   Result := Trim(RegKeyReadString(HKEY_CLASSES_ROOT, KeyName+'\LocalServer32', ''));  //#DNL
   if Result <> '' then exit;
   // ����� ����� InprocServer
   Result := Trim(RegKeyReadString(HKEY_CLASSES_ROOT, KeyName+'\InprocServer', ''));  //#DNL
   if Result <> '' then exit;
  end;
 finally
  Reg.Free;
 end;
end;

// ��������� ����� ������������� ����� �� ��� GUID
Function GetBinFileByGUID(AGUID : TGUID) : string;
begin
 Result := GetBinFileByGUID(GUIDToString(AGUID));
end;

// ������ ����� �������
Function RegKeyReadString(ARootKey : HKey; AKeyName, AParamName : string) : string;
var
 Reg : TRegistry;
begin
 Result := '';
 Reg := TRegistry.Create;
 try
  Reg.RootKey := ARootKey;
  // �������� ����� � ������ ������
  if Reg.OpenKey(AKeyName, false) then begin
   if Reg.ValueExists(AParamName) then
    Result := Reg.ReadString(AParamName);
   Reg.CloseKey;
  end;
 finally
  Reg.Free;
 end;
end;

// ������ ����� �������
Function RegKeyReadInt(ARootKey : HKey; AKeyName, AParamName : string) : integer;
var
 Reg : TRegistry;
begin
 Result := -1;
 Reg := TRegistry.Create;
 try
  try
    Reg.RootKey := ARootKey;
    // �������� ����� � ������ ������
    if Reg.OpenKey(AKeyName, false) then begin
     if Reg.ValueExists(AParamName) then
      Result := Reg.ReadInteger(AParamName);
     Reg.CloseKey;
    end;
  except
   Result := -1;
  end;
 finally
  Reg.Free;
 end;
end;

// �������������� NT ����� ���� � ����������
Function NTFileNameToNormalName(AFileName : string) : string;
begin
 Result := Trim(AFileName);
 // �������� ��������
 if pos('file://', LowerCase(Result)) = 1 then
    Result := copy(Result, 7, 500);
 if pos('file:\\', LowerCase(Result)) = 1 then
    Result := copy(Result, 7, 500);
 if pos('\??\', Result) = 1 then
    Result := copy(Result, 5, 500);
 if pos('\?\\', Result) = 1 then
    Result := copy(Result, 5, 500);
 if pos('\\.\', Result) = 1 then
    Result := copy(Result, 5, 500);
 if pos('\SYSTEMROOT', UpperCase(Result)) = 1 then //#DNL
   Result := GetWindowsDirectoryPath + copy(Result, 13, 500);
 if pos('/SYSTEMROOT', UpperCase(Result)) = 1 then //#DNL
   Result := GetWindowsDirectoryPath + copy(Result, 13, 500);
 if pos('SYSTEM32', UpperCase(Result)) = 1 then //#DNL
   Result := GetSystemDirectoryPath + copy(Result, 10, 500);
 if pos('\SYSTEM32', UpperCase(Result)) = 1 then //#DNL
   Result := GetSystemDirectoryPath + copy(Result, 11, 500);
 if pos('/SYSTEM32', UpperCase(Result)) = 1 then //#DNL
   Result := GetSystemDirectoryPath + copy(Result, 11, 500);
 if pos('\WINDOWS', UpperCase(Result)) = 1 then //#DNL
   Result := GetWindowsDirectoryPath + copy(Result, 10, 500);
 if pos('/WINDOWS', UpperCase(Result)) = 1 then //#DNL
   Result := GetWindowsDirectoryPath + copy(Result, 10, 500);
 if pos('\WINNT', UpperCase(Result)) = 1 then //#DNL
   Result := GetWindowsDirectoryPath + copy(Result, 8, 500);
 if pos('/WINNT', UpperCase(Result)) = 1 then //#DNL
   Result := GetWindowsDirectoryPath + copy(Result, 8, 500);
 if pos('\WINXP', UpperCase(Result)) = 1 then //#DNL
   Result := GetWindowsDirectoryPath + copy(Result, 8, 500);
 if pos('/WINXP', UpperCase(Result)) = 1 then //#DNL
   Result := GetWindowsDirectoryPath + copy(Result, 8, 500);
 if pos('\WIN_XP', UpperCase(Result)) = 1 then //#DNL
   Result := GetWindowsDirectoryPath + copy(Result, 9, 500);
 if pos('/WIN_XP', UpperCase(Result)) = 1 then //#DNL
   Result := GetWindowsDirectoryPath + copy(Result, 9, 500);
 // ������ ������� �� �������� ����
 Result := StringReplace(Result, '%SystemRoot%', NormalNameDir(GetWindowsDirectoryPath), [rfReplaceAll, rfIgnoreCase]); //#DNL
 // ������ ������� �� �������� ����
 Result := StringReplace(Result, '%System32%', NormalNameDir(GetSystemDirectoryPath), [rfReplaceAll, rfIgnoreCase]); //#DNL
 // ������ ������� �� �������� ����
 Result := StringReplace(Result, '%WinDir%', NormalNameDir(GetWindowsDirectoryPath), [rfReplaceAll, rfIgnoreCase]); //#DNL
 // ������ ������� �� �������� ����
 Result := StringReplace(Result, '%SysDisk%', copy(GetSystemDirectoryPath, 1, 2), [rfReplaceAll, rfIgnoreCase]); //#DNL
 // ������ ������� �� �������� ����
 Result := StringReplace(Result, '%ProgramFiles%', NormalDir(GetProgramFilesDirectoryPath), [rfReplaceAll, rfIgnoreCase]); //#DNL
end;

// ���������� ����� �����
Function ExpandFileNameEx(AFileName : string) : string;
begin
 Result := Trim(AFileName);
 Result := StringReplace(Result, '"', '', [rfReplaceAll, rfIgnoreCase]);
 if FileExists(AFileName) then exit;
 // ��� ����� �������, ; � ? �������
 if pos(',', Result) > 0 then  delete(Result, pos(',', Result), 800);
 if pos(';', Result) > 0 then  delete(Result, pos(';', Result), 800);
 if pos('?', Result) > 0 then  delete(Result, pos('?', Result), 800);
 if pos(' /', Result) > 0 then  delete(Result, pos(' /', Result), 800);
 // �������� ���������
 if (Length(Result) > 12) and (pos(' ', Result) > 0 ) then begin
  if pos('RUNDLL32.EXE', UpperCase(Result)) = 1 then begin delete(Result, 1, 12); Result := Trim(Result); end;
  if pos('RUNDLL32', UpperCase(Result)) = 1 then begin delete(Result, 1, 8); Result := Trim(Result); end;
  if pos('RUNDLL', UpperCase(Result)) = 1 then begin delete(Result, 1, 6); Result := Trim(Result); end;
  if pos('CMD.EXE', UpperCase(Result)) = 1 then begin delete(Result, 1, 7);  Result := Trim(Result); end;
  if pos('EXPLORER.EXE', UpperCase(Result)) = 1 then begin delete(Result, 1, 12); Result := Trim(Result); end;
  if pos('EXPLORER', UpperCase(Result)) = 1 then begin delete(Result, 1, 8);Result := Trim(Result); end;
 end;
 // ����������� ����������
 if pos('.EXE ', UpperCase(Result)) > 0 then begin delete(Result, pos('.EXE ', UpperCase(Result))+4, 800); Result := Trim(Result); end; //#DNL
 if pos('.DLL ', UpperCase(Result)) > 0 then begin delete(Result, pos('.DLL ', UpperCase(Result))+4, 800); Result := Trim(Result); end; //#DNL
 if pos('.SYS ', UpperCase(Result)) > 0 then begin delete(Result, pos('.SYS ', UpperCase(Result))+4, 800); Result := Trim(Result); end; //#DNL
 // ���������� ����������� �����
 if (pos(':', Result) <> 2) and Not(FileExists(Result)) then
  if FileExists(SearchSysPath(Result)) then
    Result := SearchSysPath(Result);
end;

// ���������/����������� ���������� NT
Function AdjustPrivileges(APrivStr : string; NewState : boolean) : boolean;
var
 hToken   : THandle;
 tkp      : TTokenPrivileges;
 tkpo     : TTokenPrivileges;
 zero     : DWORD;
begin
 Result := false;
 zero := 0;
 // �������� ������ �������� ���������� SeDebugPrivilege
 if OpenProcessToken(GetCurrentProcess,	TOKEN_ADJUST_PRIVILEGES or TOKEN_QUERY,	hToken) then begin
  if LookupPrivilegeValue( nil, PChar(APrivStr), tkp.Privileges[0].Luid ) then  begin
   tkp.PrivilegeCount := 1;
   if NewState then
    tkp.Privileges[0].Attributes := SE_PRIVILEGE_ENABLED
     else tkp.Privileges[0].Attributes := 4; //4 = SE_PRIVILEGE_REMOVED;
   //Result := AdjustTokenPrivileges(hToken, False, tkp, SizeOf( TTokenPrivileges ), tkpo, zero);
   Result := AdjustTokenPrivileges(hToken, False, tkp, 0, nil, zero);
  end;
  CloseHandle(hToken);
 end;
end;

//
function HTMLNVL(S : string) : string;
begin
 Result := S;
 if Trim(S) = '' then
  Result := '&nbsp;';
end;

function DelCRLF(S : string) : string;
begin
 Result := S;
 Result := StringReplace(Result, #$0D, '', [rfReplaceAll]);
 Result := StringReplace(Result, #$0A, '', [rfReplaceAll]);
end;

function XMLStr(S : string) : string;
var
 i : integer;
begin
 Result := S;
 for i := 1 to 5 do
  Result := StringReplace(Result, HTMLCodes[i, 1], HTMLCodes[i, 2], [rfReplaceAll]);
end;

// ������������ ��������
Function DecodeWEBParam(AParam : string) : String;
var
 i : integer;
begin
 Result := '';
 if AParam = '' then exit;
 i := 1;
 while i <= Length(AParam) do
  case AParam[i] of
   '+' : begin
          Result := Result + ' ';
          inc(i);
         end;
   '%' : begin
          try
           Result := Result + Chr(StrToInt('$'+Copy(AParam,i+1,2)));
          except end;
          inc(i, 3); // ���� % + ��� ����� ���� �������
         end;
   else begin
          Result := Result + AParam[i];
          inc(i);
         end;
  end;
end;

// ������������ ��������
Function EncodeWEBParam(AParam : string) : String;
var
 i : integer;
begin
 Result := '';
 if AParam = '' then exit;
 for i := 1 to Length(AParam) do
  case AParam[i] of
   'a'..'z',
   'A'..'Z','_','-','.',
   '0', '1'..'9'         : Result := Result + AParam[i];
   ' '                   : Result := Result + '+';
   else Result := Result + '%'+IntToHex(byte(AParam[i]),2);
  end;
end;

function WebSearchInYandex(AKeyWord : string) : boolean;
begin
 ShellExecute(0, nil,PChar('http://www.yandex.ru/yandsearch?stype=&nl=0&text='+ //#DNL
              EncodeWEBParam(Trim(AKeyWord))),nil,nil,1);
end;

function WebSearchInGoogle(AKeyWord : string) : boolean;
begin
 ShellExecute(0, nil,PChar('http://www.google.ru/search?hl=ru&q='+ //#DNL
              EncodeWEBParam(Trim(AKeyWord))),nil,nil,1);
end;

function WebSearchInRambler(AKeyWord : string) : boolean;
begin
 ShellExecute(0, nil,PChar('http://search.rambler.ru/srch?words='+ //#DNL
              EncodeWEBParam(Trim(AKeyWord)+'&where=1')),nil,nil,1);
end;

function WebOpenURLinBrowser(AURL : string) : boolean;
begin
 ShellExecute(0, nil,PChar(AURL),nil,nil,1);
end;

function NormalProgramFileName(AFileName : string; DefExt : string) : string;
var
 S, ST : string;
 i : integer;
begin
 Result := Trim(AFileName);
 if AFileName = '' then exit;
 // �������� '"'
 Result := StringReplace(Result, '"', '', [rfReplaceAll]);
 // ������������ NT ����� �����
 Result := NTFileNameToNormalName(Result);
 Result := ExpandFileNameEx(Result);
 S := Result;
 // ����� ��������� �����
 I := LastDelimiter('.' + PathDelim + DriveDelim + ' ', S);
 // ����� ��� ������ - ������, ���������� �� �������
 if i = 0 then begin
  Result := S + DefExt;
 end else begin
  while i > 0 do begin
   I := LastDelimiter('.' + PathDelim + DriveDelim + ' ', S);
   ST := copy(S, I, MaxInt);
   Delete(S, I, MaxInt);
   if Pos(' ', ST) > 0 then
    Delete(ST, Pos(' ', ST), MaxInt);
   if ST = '' then ST := DefExt;
   // ����� ���� ����
   if FileExists(S + ST) then begin
    Result := S + ST;
    exit;
   end;
   // ����� ���� ���� � ��������� ����� ��� �� ����� ������ ?
   if FileExists(SearchSysPath(S + ST)) then begin
    Result := SearchSysPath(S + ST);
    exit;
   end;
   // ����� ���� ���� � ��������� �����
   if FileExists(GetSystemDirectoryPath + 'Drivers\' + S + ST) then begin
    Result := GetSystemDirectoryPath + 'Drivers\' + S + ST;
    exit;
   end;
  end;
 end;
 Result := Trim(Result);
 if not(FileExists(Result)) then begin
   // ����� ���� ���� � ��������� �����
   if FileExists(GetSystemDirectoryPath + Result) then begin
    Result := GetSystemDirectoryPath + Result;
    exit;
   end;
   // ����� ���� ���� � ��������� �����
   if FileExists(GetWindowsDirectoryPath + Result) then begin
    Result := GetWindowsDirectoryPath + Result;
    exit;
   end;
   // ����� ���� ���� � ��������� �����
   if FileExists(GetSystemDirectoryPath + 'Drivers\' + Result) then begin
    Result := GetSystemDirectoryPath + 'Drivers\' + Result;
    exit;
   end;
 end;
end;

function FormatFileInfo(AFileName : string; DelimStr : string = ',<br>') : string;
var
 SR  : TSearchRec;
 Res : integer;
 AttrStr : string;
begin
 Result := '';
 try
  // ����� �����
  Res := FindFirst(AFileName, faAnyFile, SR);
  FindClose(SR);
  if Res = 0 then begin
   AddToList(Result, FormatFloat('0.00', SR.Size/1024)+' $AVZ1191', DelimStr);
   if SR.Attr and faReadOnly  > 0 then AttrStr := AttrStr + 'R' else AttrStr := AttrStr + 'r';
   if SR.Attr and faSysFile   > 0 then AttrStr := AttrStr + 'S' else AttrStr := AttrStr + 's';
   if SR.Attr and faArchive   > 0 then AttrStr := AttrStr + 'A' else AttrStr := AttrStr + 'a';
   if SR.Attr and faHidden    > 0 then AttrStr := AttrStr + 'H' else AttrStr := AttrStr + 'h';
   AddToList(Result, AttrStr, ', ');
   AddToList(Result, '$AVZ1015: '+DateTimeToStr(FileTimeToDateTime(SR.FindData.ftCreationTime)), DelimStr);
   AddToList(Result, '$AVZ0295: '+DateTimeToStr(FileTimeToDateTime(SR.FindData.ftLastWriteTime)), DelimStr);
  end else
   Result := '$AVZ0676';
  // ����� ������������ ��������
  if (LowerCase(AFileName) <> AnsiLowerCase(AFileName)) or (UpperCase(AFileName) <> AnsiUpperCase(AFileName)) then
   AddToList(Result, '$AVZ0306', DelimStr);
  FindClose(SR);
 except
 end;
end;

function FormatXMLFileInfo(AFileName : string; AGoodDBCheck : boolean = false) : string;
var
 SR  : TSearchRec;
 Res : integer;
 AttrStr : string;
begin
 Result := '';
 AFileName := Trim(AFileName);
 if AFileName = '' then exit;
 try
  // ����� �����
  Res := FindFirst(AFileName, faAnyFile, SR);
  FindClose(SR);
  if Res = 0 then begin
   if AGoodDBCheck then
    AddToList(Result, 'CheckResult="'+IntToStr(FileSignCheck.CheckFile(AFileName))+'"', ' ');;
   AddToList(Result, 'Size="'+ IntToStr(SR.Size)+'"', ' ');
   if SR.Attr and faReadOnly  > 0 then AttrStr := AttrStr + 'R' else AttrStr := AttrStr + 'r';
   if SR.Attr and faSysFile   > 0 then AttrStr := AttrStr + 'S' else AttrStr := AttrStr + 's';
   if SR.Attr and faArchive   > 0 then AttrStr := AttrStr + 'A' else AttrStr := AttrStr + 'a';
   if SR.Attr and faHidden    > 0 then AttrStr := AttrStr + 'H' else AttrStr := AttrStr + 'h';
   AddToList(Result, 'Attr="'+AttrStr+'"', ' ');
   AddToList(Result, 'CreateDate="'+DateTimeToStr(FileTimeToDateTime(SR.FindData.ftCreationTime))+'"', ' ');
   AddToList(Result, 'ChageDate="'+DateTimeToStr(FileTimeToDateTime(SR.FindData.ftLastWriteTime))+'"', ' ');
   AddToList(Result, 'MD5="'+CalkFileMD5(AFileName)+'"', ' ');
  end else
   Result := '';
  // ����� ������������ ��������
  if (LowerCase(AFileName) <> AnsiLowerCase(AFileName)) or (UpperCase(AFileName) <> AnsiUpperCase(AFileName)) then
   AddToList(Result, 'NationalName="Y"', ' ');
  FindClose(SR);
 except
 end;
end;

Function GetProcAddrFromKernelDLL(aProcName: String): Pointer;
var
 hKernel: THandle;
begin
 Result := 0;
 hKernel   := GetModuleHandle(Kernel32);
 if hKernel <> INVALID_HANDLE_VALUE then
  Result := GetProcAddress(hKernel, PChar(aProcName));
end;

function RemoteFreeLibrary(PID:Cardinal; HModule : Cardinal) : boolean;
type
 TInjectCode = packed record
  PushOp    : Byte;   // 00000 PUSH const
  PushValue : DWord;  // 00001  <const DWORD>
  CallOp    : Byte;   // 00004 Call FreeLibrary
  CallValue : DWord;  // 00005  <rel to FreeLibrary>
  IsZeroOp  : Word;   // 0000A
  JmpZeroOp : Word;   // 0000C JZ -0Ch
  RetOp     : Byte;   // 0000D RET
end;
var
 InjectedCode    : TInjectCode;
 InjectedCodePTR : Pointer;
 hProcess, hRemoteThread:DWord;
 dwTmp : DWord;
begin
 hProcess := INVALID_HANDLE_VALUE;
 InjectedCodePTR := nil;
 try
   InjectedCode.CallValue := Cardinal(GetProcAddrFromKernelDLL('FreeLibrary'));
   if InjectedCode.CallValue = 0 then exit;
   // �������� ��������
   hProcess := OpenProcess(PROCESS_ALL_ACCESS , False, PID);
   if hProcess = 0 then exit;
   // �������� � �������� ����� ������ � ��������� PAGE_EXECUTE_READWRITE ��� ������ ����
   InjectedCodePTR := VirtualAllocEx(hProcess, nil, SizeOf(InjectedCode), MEM_RESERVE or MEM_COMMIT, PAGE_EXECUTE_READWRITE);
   if InjectedCodePTR = nil then exit;
   // ���������� ��������� ����
   InjectedCode.PushOp    := $068;
   InjectedCode.CallOp    := $0E8;
   InjectedCode.IsZeroOp  := $0C021;
   InjectedCode.JmpZeroOp := $0F275;
   InjectedCode.RetOp     := $0C3;
   // ������������ ����� - ������ Handle DLL
   InjectedCode.PushValue := DWord(HModule);
   // ������������ ����� - ������ ������ FreeLibrary (��� JMP, ������� ����� �������������)
   InjectedCode.CallValue := InjectedCode.CallValue - DWord(InjectedCodePTR) - 10;
   // ������ ���� � �������������� �����
   if (WriteProcessMemory(hProcess, InjectedCodePTR, @InjectedCode, SizeOf(InjectedCode), dwTmp) and (dwTmp=SizeOf(InjectedCode))) then begin
    // �������� ���������� ������
    hRemoteThread := CreateRemoteThread(hProcess,nil,0,InjectedCodePTR, nil, 0, dwTmp);
    // ����� ������ - �������� ��� ����������
    if hRemoteThread <> 0 then begin
     // ��������
     if WaitForSingleObject(hRemoteThread, 5000) <> WAIT_TIMEOUT then ; //���� �� �������� ���� �������.
     // �������� Handle ������
     CloseHandle(hRemoteThread);
    end;
   end;
 finally
  // ����������� ������
  if InjectedCodePTR <> nil then
   VirtualFreeEx(hProcess, InjectedCodePTR, 0, MEM_RELEASE);
  CloseHandle(hProcess);
 end;
end;

function GetWindowsCountByPid(APID:Cardinal; AVisibleOnly : boolean) : integer;
var
 WinHandle   : HWnd;
 PID : dword;
begin
 Result := 0;
 WinHandle := GetWindow(Application.Handle, gw_HWndFirst);
 while WinHandle <> 0 do begin
  GetWindowThreadProcessId(WinHandle, PID);
  if PID = APID then
   if not(AVisibleOnly) or (AVisibleOnly and IsWindowVisible(WinHandle)) then inc(Result);
  // ����� ���������� ����
  WinHandle := GetWindow(WinHandle, gw_hWndNext);
 end;
end;

function ModifyProgrammAPICall(AFunctionStubPtr,
  ANewAPIAddr: pointer): boolean;
var
 Buf1     : packed array [0..10] of byte;
 BytesReaded       : dword;
 dw : dword;
begin
 // ���������� ������ "EB xx xx xx xx 90"
 Buf1[0] := $E9;
 Buf1[5] := $90;
 // ���������� �������� ��� JMP � ��� ������ � ����� 2-5 ������
 dw := dword(ANewAPIAddr)  - (dword(AFunctionStubPtr) + 5);
 CopyMemory(@Buf1[1], @dw, 4);
 // ������ ���� JMP <���������� �����>; NOP ������ �����������, ������������� Delphi ��� ������������ �������
 Result := WriteProcessMemory(GetCurrentProcess, AFunctionStubPtr, @Buf1[0], 6, BytesReaded);
end;

function GetPIDByWindowHandle(AHandle : dword) : dword;
begin
 Result := 0;
 GetWindowThreadProcessId(AHandle, @Result);
end;

function GetProcessByPID(APID : dword) : string;
var
 SysProcessInfo : TSysProcessInfo;
 ModulesList  : TStrings;
begin
 // �������� ������ "���������� � ���������" � ����������� �� ���� ��
 if ISNT then
  SysProcessInfo := TPSAPIProcessInfo.Create
   else SysProcessInfo := TToolHelpProcessInfo.Create;
 ModulesList  := TStringList.Create;
 SysProcessInfo.CreateModuleList(ModulesList, APID);
 if ModulesList.Count > 0 then
  Result := (ModulesList.Objects[0] as TModuleInfo).ModuleName
   else Result := '';
 SysProcessInfo.Free;
end;

function GetProcessImageNameByHandle(hProcess : dword) : string;
var
 dwTmp    : DWord;
 PBI      : TProcessBasicInformation;
 Res, Tmp      : DWORD;
 PProcessParameters : pointer;
 RUP : _RTL_USER_PROCESS_PARAMETERS;
 TmpWS : WideString;
begin
 Result := '?';
 // �������� �������
 if @zNtQueryInformationProcess = nil then LoadNTDllAPI;
 // �������� �������� - ����� �����
 if @zNtQueryInformationProcess = nil then exit;
 Res := zNtQueryInformationProcess(hProcess,
                              ProcessBasicInformation,
                              @PBI, SizeOf(PBI),
                              @Tmp);
 if Res <> STATUS_SUCCESS then exit;
 PProcessParameters := nil;
 // ������ ������ ���������� �� PEB
 if not(ReadProcessMemory(hProcess,
                     pointer(dword(PBI.PebBaseAddress) + $10),
                     @PProcessParameters, 4, dwTmp)) then exit;
   if not(ReadProcessMemory(hProcess,
                     PProcessParameters,
                     @RUP, sizeof(RUP), dwTmp)) then exit;
   if (RUP.ImagePathName.Length = 0) or (RUP.ImagePathName.Length > 10000) then exit;
   SetLength(TmpWS, RUP.ImagePathName.Length);
   if not(ReadProcessMemory(hProcess,
                     RUP.ImagePathName.Buffer,
                     @TmpWS[1], RUP.ImagePathName.Length, dwTmp)) then exit;
   Result := copy(TmpWS, 1, RUP.ImagePathName.Length div 2);
end;

function GetProcessImageNameByPID(APID : dword) : string;
var
 dwTmp    : DWord;
 PBI      : TProcessBasicInformation;
 Res, Tmp      : DWORD;
 hProcess : THandle;
 PProcessParameters : pointer;
 RUP : _RTL_USER_PROCESS_PARAMETERS;
 TmpWS : WideString;
begin
 Result := '?';
 // �������� �������
 if @zNtQueryInformationProcess = nil then LoadNTDllAPI;
 // �������� �������� - ����� �����
 if @zNtQueryInformationProcess = nil then exit;
 // �������� ��������
 hProcess := OpenProcess(PROCESS_QUERY_INFORMATION or PROCESS_VM_READ, False, APID);
 if hProcess = 0 then exit;
 try
  Res := zNtQueryInformationProcess(hProcess,
                              ProcessBasicInformation,
                              @PBI, SizeOf(PBI),
                              @Tmp);
  if Res <> STATUS_SUCCESS then exit;
  PProcessParameters := nil;
  // ������ ������ ���������� �� PEB
  if not(ReadProcessMemory(hProcess,
                     pointer(dword(PBI.PebBaseAddress) + $10),
                     @PProcessParameters, 4, dwTmp)) then exit;
   if not(ReadProcessMemory(hProcess,
                     PProcessParameters,
                     @RUP, sizeof(RUP), dwTmp)) then exit;
   if (RUP.ImagePathName.Length = 0) or (RUP.ImagePathName.Length > 10000) then exit;
   SetLength(TmpWS, RUP.ImagePathName.Length);
   if not(ReadProcessMemory(hProcess,
                     RUP.ImagePathName.Buffer,
                     @TmpWS[1], RUP.ImagePathName.Length, dwTmp)) then exit;
   Result := copy(TmpWS, 1, RUP.ImagePathName.Length div 2);
  finally
   CloseHandle(hProcess);
  end;
end;

function GetProcessIDByHandle(hProcess : dword) : dword;
var
 PBI      : TProcessBasicInformation;
 Res, Tmp      : DWORD;
begin
 Result := 0;
 // �������� �������
 if @zNtQueryInformationProcess = nil then LoadNTDllAPI;
 // �������� �������� - ����� �����
 if @zNtQueryInformationProcess = nil then exit;
 Res := zNtQueryInformationProcess(hProcess,
                              ProcessBasicInformation,
                              @PBI, SizeOf(PBI),
                              @Tmp);
 if Res <> STATUS_SUCCESS then exit;
 Result := PBI.UnicueProcessID;
end;

Function GetWindowTextByHandle(AHandle : dword) : string;
var
 Res : integer;
begin
 SetLength(Result, 255);
 Res := GetWindowText(AHandle, @Result[1], Length(Result));
 SetLength(Result, Res);
end;

Function GetFileNameByHandle(AHandle : dword) : string;
var
 Res : dword;
 FileName : TFileNameInformation;
 IO_STATUS_BLOCK : TIO_STATUS_BLOCK;
begin
 Result := '';
 if (@zNtQueryInformationFile = nil) then exit;
 try
  // ������ ������
  Res := zNtQueryInformationFile(AHandle, @IO_STATUS_BLOCK,
                                   @FileName,
                                   SizeOf(FileName),
                                   FileNameInformation);
  if Res = STATUS_SUCCESS then begin
   Result := copy(String(FileName.Filename), 1, FileName.FileNameLength div 2);
  end;
 except end;
end;

// ��������� ��������� ������ ��������
function GetProcessCmdLineByPID1(APID : dword) : string;
var
 InjectedCodePTR : pointer;
 hProcess, hRemoteThread:DWord;
 dwTmp : DWord;
begin
 Result := '';
 hProcess := INVALID_HANDLE_VALUE;
 try
   InjectedCodePTR := GetProcAddrFromKernelDLL('GetCommandLineA'); //#DNL
   if InjectedCodePTR = nil then exit;
   // �������� ��������
   hProcess := OpenProcess(PROCESS_ALL_ACCESS , False, APID);
   if hProcess = 0 then exit;
   // �������� ���������� ������
   hRemoteThread := CreateRemoteThread(hProcess,nil,0,InjectedCodePTR, nil, 0, dwTmp);
    // ����� ������ - �������� ��� ����������
    if hRemoteThread <> 0 then begin
     // ��������
     if WaitForSingleObject(hRemoteThread, 500) <> WAIT_TIMEOUT then ; //���� �� �������� 500 ms
     GetExitCodeThread(hRemoteThread, dwTmp);
     if dwTmp <> 0 then begin
      SetLength(Result, 500);
      ReadProcessMemory(hProcess, pointer(dwTmp), @Result[1], length(Result), dwTmp);
      Result := Trim(Result);
      if pos(#0, Result)>0 then
       Delete(Result, pos(#0, Result), maxint);
     end;
     // �������� Handle ������
     CloseHandle(hRemoteThread);
    end;
 finally
  CloseHandle(hProcess);
 end;
end;

// ��������� ��������� ������ ��������
function GetProcessCmdLineByPID(APID : dword) : string;
var
 hProcess : DWord;
 dwTmp    : DWord;
 PBI      : TProcessBasicInformation;
 Res, Tmp      : DWORD;
 PProcessParameters   : Pointer;
 RUP : _RTL_USER_PROCESS_PARAMETERS;
 TmpWS : WideString;
begin
 Result := '';
 hProcess := INVALID_HANDLE_VALUE;
 LoadNTDllAPI;
 try
   // �������� ��������
   hProcess := OpenProcess(PROCESS_ALL_ACCESS , False, APID);
   if hProcess = 0 then exit;
   if ISNT then begin
    // �������� �������
    if @zNtQueryInformationProcess = nil then LoadNTDllAPI;
    // �������� �������� - ����� �����
    if @zNtQueryInformationProcess = nil then exit;
    Res := zNtQueryInformationProcess(hProcess,
                               ProcessBasicInformation,
                               @PBI, SizeOf(PBI),
                               @Tmp);
    if PBI.UnicueProcessID <> APID then exit;
   end else
    exit;
   PProcessParameters := nil;
   // ������ ������ ���������� �� PEB
   if not(ReadProcessMemory(hProcess,
                     pointer(dword(PBI.PebBaseAddress) + $10),
                     @PProcessParameters, 4, dwTmp)) then exit;
   if not(ReadProcessMemory(hProcess,
                     PProcessParameters,
                     @RUP, sizeof(RUP), dwTmp)) then exit;
   if (RUP.CommandLine.Length = 0) or (RUP.CommandLine.Length > 10000) then exit;
   SetLength(TmpWS, RUP.CommandLine.Length);
   if not(ReadProcessMemory(hProcess,
                     RUP.CommandLine.Buffer,
                     @TmpWS[1], RUP.CommandLine.Length, dwTmp)) then exit;
   Result := copy(TmpWS, 1, RUP.CommandLine.Length div 2);
 finally
  CloseHandle(hProcess);
 end;
end;

function GetRegKeyNameByHandle(AHandle : dword) : string;
var
 KI : KEY_NAME_INFORMATION;
 Res : ULONG;
 ResultLength : ULONG;
begin
 Result := '';
 if @zZwQueryKey = nil then exit;
 ZeroMemory(@KI, SizeOf(KI));
 Res := zZwQueryKey(AHandle, KeyNameInformation, @KI, SizeOf(KI), @ResultLength);
 if Res = STATUS_SUCCESS then begin
  Result := Trim(KI.Name);
  Result := StringReplace(Result,CU_KEY, 'HKCU\', [rfIgnoreCase]);
  Result := StringReplace(Result,'\REGISTRY\MACHINE\SOFTWARE\Classes\', 'HKCR\', [rfIgnoreCase]);
  Result := StringReplace(Result,'\REGISTRY\MACHINE\', 'HKLM\', [rfIgnoreCase]);
 end;
end;

function InstallDriver(ADriverFile, AKeyName, ADisplayName : string; AStartType : byte = 3) : dword;
var
 Reg       : TRegistry;
 KeyName   : String;
begin
 Result := 1;
 KeyName := 'SYSTEM\CurrentControlSet\Services\'+AKeyName; //#DNL
 // ��� 1. ����������� � �������
 Reg := TRegistry.Create;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 if Reg.OpenKey(KeyName, true) then begin
  Reg.WriteString('DisplayName', ADisplayName); //#DNL
  Reg.WriteInteger('ErrorControl', 1); //#DNL
  Reg.WriteString('ImagePath', '\??\'+ADriverFile); //#DNL
  Reg.WriteInteger('Start', AStartType); //#DNL
  Reg.WriteInteger('Type', 1); //#DNL
  Reg.WriteInteger('ErrorControl', 0); //#DNL
  Result := 0;
  Reg.Free;
 end else begin
  exit;
  Reg.Free;
 end;
end;

function UnInstallDriver(AKeyName : string) : dword;
var
 Reg     : TRegistry;
 KeyName : String;
begin
 Result := 1;
 KeyName := 'SYSTEM\CurrentControlSet\Services\'+AKeyName; //#DNL
 // ��� 1. ����������� � �������
 Reg := TRegistry.Create;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 Reg.DeleteKey(KeyName);
 Reg.Free;
 Result := 0;
end;

function LoadDriver(AKeyName : string) : dword;
var
 US  : UNICODE_STRING;
 KeyName : WideString;
begin
 // �������� ��������
 KeyName := '\Registry\Machine\System\CurrentControlSet\Services\'+AKeyName; //#DNL
 US.Length := Length(KeyName)*2;
 US.MaximumLength := US.Length;
 US.Buffer := @KeyName[1];
 Result := CallZwLoadDriver(@US);
end;

function UnLoadDriver(AKeyName : string) : dword;
var
 US  : UNICODE_STRING;
 KeyName : WideString;
begin
 Result := 1;
 // ��� 1. �������� ��������
 KeyName := '\Registry\Machine\System\CurrentControlSet\Services\'+AKeyName; //#DNL
 US.Length := Length(KeyName)*2;
 US.MaximumLength := US.Length;
 US.Buffer := @KeyName[1];
 Result := CallZwUnLoadDriver(@US);
end;

// ��������� ���������������� ����� ��� ��������
function GenerateRandomName(ALength, ACode : integer) : string;
var
 dw, i : dword;
 S  : string;
 StrSize : dword;
begin
 {$R-}
 S := copy(GetSystemDirectoryPath, 1, 1)+'C'; //#DNL
 dw := DiskSize(byte(S[1])-$40) xor 6410*ACode div ACode*107;
 SetLength(S, 200);
 StrSize := length(s);
 GetComputerName(PChar(S), StrSize);
 S := copy(S, 1, StrSize);
 for i := 1 to Length(S) do
  dw := dw + byte(S[i]);
 S := char(ACode+$50) + copy(IntToStr(dw), 1, 2) + IntToStr(dw mod 1000000);
 Result := LowerCase(copy(CodeStringBase64(S), 1, ALength));
 {$R+}
end;

const
  SECURITY_NT_AUTHORITY: TSIDIdentifierAuthority =
    (Value: (0, 0, 0, 0, 0, 5));
  SECURITY_BUILTIN_DOMAIN_RID = $00000020;
  DOMAIN_ALIAS_RID_ADMINS = $00000220;

// �������� ������� ���� ��������������
function UserIsNTAdmin: Boolean;
var
  hAccessToken: THandle;
  ptgGroups: PTokenGroups;
  dwInfoBufferSize: DWORD;
  psidAdministrators: PSID;
  x: Integer;
  bSuccess: BOOL;
begin
  Result   := False;
  if not(ISNT) then exit;
  // �������� ������ ������
  bSuccess := OpenThreadToken(GetCurrentThread, TOKEN_QUERY, True,
    hAccessToken);
  if not bSuccess then
  begin
    if GetLastError = ERROR_NO_TOKEN then
      bSuccess := OpenProcessToken(GetCurrentProcess, TOKEN_QUERY,
        hAccessToken);
  end;
  // ������� �������
  if bSuccess then begin
    GetMem(ptgGroups, 1024*8);
    // ��������� ������ �����
    bSuccess := GetTokenInformation(hAccessToken, TokenGroups,
                                    ptgGroups, 1024*8, dwInfoBufferSize);
    CloseHandle(hAccessToken);
    // ��������� ������ ����� ������� - ������
    if bSuccess then  begin
      // ��������� psid ������ "��������������"
      AllocateAndInitializeSid(SECURITY_NT_AUTHORITY, 2,
        SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0, psidAdministrators);
      {$R-}
      // ��������� PSID ������ "��������������" � ����� ������������
      for x := 0 to ptgGroups.GroupCount - 1 do
        if EqualSid(psidAdministrators, ptgGroups.Groups[x].Sid) then
        begin
          Result := True;
          Break;
        end;
      {$R+}
      FreeSid(psidAdministrators);
    end;
    FreeMem(ptgGroups);
  end;
end;

function SearchSysPath(FileName : string; DefExt : string = '') : string;
var
 S : string;
 Res : integer;
 lpFilePart: PChar;
begin
 SetLength(S, 500);
 if DefExt = '' then
  Res := SearchPath(nil, PChar(FileName), nil, length(S), @S[1], lpFilePart)
 else
  Res := SearchPath(nil, PChar(FileName), PChar(DefExt), length(S), @S[1], lpFilePart);
 if Res > 0 then
  Result := copy(S, 1, Res)
   else Result := FileName;
end;

function RegKeyToSystemRegKey(AKey : string) : string;
var
 S : string;
begin
 Result := AKey;
 S := UpperCase(Trim(copy(Result, 1, pos('\', Result)-1)));
 if S = '' then exit;
 delete(Result, 1, pos('\', Result));
 if (S = 'HKLM') or (S = 'HKEY_LOCAL_MACHINE') then
  Result := '\Registry\Machine\' + Result;
 if (S = 'HKCU') or (S = 'HKEY_CURRENT_USER') then
  Result := '\Registry\User\' + Result;
end;

// ����������� ����� ����� Hosts
function GetHostsFileName : string;
var
 Reg : TRegistry;
 S : string;
begin
 Result := '';
 if ISNT then begin
  Result := GetSystemDirectoryPath + 'Drivers\Etc\hosts';
  Reg := TRegistry.Create;
  Reg.RootKey := HKEY_LOCAL_MACHINE;
  if Reg.OpenKey('SYSTEM\CurrentControlSet\Services\Tcpip\Parameters', false) then
   if Reg.ValueExists('DataBasePath') then begin
     S := Reg.ReadString('DataBasePath');
    if DirectoryExists(NTFileNameToNormalName(S)) then
     Result := NormalDir(NTFileNameToNormalName(S)) + 'hosts';
   end;
  Reg.Free;
  end
   else Result := GetWindowsDirectoryPath + 'hosts';
end;

Function GetProgramFilesDirectoryPath : string;   // Program Files
begin
 Result := RegKeyReadString(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows\CurrentVersion', 'ProgramFilesDir');
end;

// ������ RegEdit � �������� ��������� �����
Function RegEditCtl(ARun : boolean; AKey, AParam : string) : boolean;
var
 Regedit, Tree, List : HWND;
 i       : integer;
begin
 Result := false;
 // ����� ���� RegEdit
 Regedit := FindWindow('RegEdit_RegEdit', 0);
 if not(ARun) and (Regedit = 0) then exit;
 // ������ ��������� �������
 if Regedit = 0 then begin
  ExecuteFile('regedit.exe', '', '', SW_NORMAL);
  Regedit := FindWindow('RegEdit_RegEdit', 0);
  if (Regedit = 0) then exit;
 end;
 // ����� Regedit �� �������� ����
 AKey := trim(AKey);
 if AKey <> '' then begin
  SetForegroundWindow(Regedit);
  Sleep(80);
  Tree := FindWindowEx(Regedit, 0, 'SysTreeView32', 0);
  SendMessage(Tree, WM_KEYDOWN, VK_HOME, 0);
  Sleep(80);
  SendMessage(Tree, WM_KEYUP, VK_HOME, 0);
  Sleep(80);
  for i := 1 to Length(AKey) do begin
   Application.ProcessMessages;
   if AKey[i] = '\' then
    SendMessage(Tree,WM_KEYDOWN,VK_RIGHT,0)
     else SendMessage(Tree, WM_CHAR, integer(AKey[i]), 0);
   Sleep(25);
  end;
  if AParam <> '' then begin
   SetForegroundWindow(Regedit);
   Tree := FindWindowEx(Regedit, 0, 'SysListView32', 0);
   SetForegroundWindow(List);
   SetFocus(List);
   Sleep(80);
   SendMessage(List,WM_KEYDOWN, VK_HOME,0);
   SendMessage(List,WM_KEYUP, VK_HOME,0);
   for i := 1 to Length(AParam) do begin
    SendMessage(Tree, WM_CHAR, integer(AParam[i]), 0);
    Application.ProcessMessages;
    Sleep(80);
   end;
  end
 end;
end;

// ������� ���������� ����� �������
Function ExpRegKey(ARoot : HKEY; AKey : string; Lines : TStrings) : boolean;
var
 Reg       : TRegistry;
 TmpLines  : TStringList;
 S, ST : string;
 i, j : integer;
 DataType, DataSize: Integer;
begin
 AKey := Trim(AKey);
 if Copy(AKey, Length(AKey), 1) <> '\' then
  if Copy(AKey, Length(AKey), 1) <> '/' then
   AKey := AKey + '\';
 Reg       := TRegistry.Create;
 TmpLines  := TStringList.Create;
 try
  Reg.RootKey := ARoot;
  if Reg.OpenKeyReadOnly(AKey) then begin
   if Lines.Count > 0 then
    Lines.Add('');
   Lines.Add('['+RootKeyToStr(ARoot)+'\'+AKey+']');
   // ���������
   Reg.GetValueNames(TmpLines);
   for i := 0 to TmpLines.Count - 1 do
    case Reg.GetDataType(TmpLines[i]) of
     rdString, rdExpandString : begin
                 S := Reg.ReadString(TmpLines[i]);
                 S := StringReplace(S, '\', '\\', [rfReplaceAll]);
                 S := StringReplace(S, '''', '\''', [rfReplaceAll]);
                 S := StringReplace(S, '"', '\"', [rfReplaceAll]);
                 if TmpLines[i] = '' then
                  TmpLines[i] := '@';
                 Lines.Add('"'+TmpLines[i]+'"="'+S+'"');
                end;
     rdInteger : begin
                  S := 'dword:'+IntToHex(Reg.ReadInteger(TmpLines[i]), 8);
                  Lines.Add('"'+TmpLines[i]+'"='+S);
                 end;
     rdBinary, rdUnknown : begin
                  SetLength(ST, Reg.GetDataSize(TmpLines[i]) + 16);
                  try
                   j := Reg.ReadBinaryData(TmpLines[i], ST[1], Length(ST));
                   SetLength(ST, j);
                   S := '';
                   for j := 1 to Length(ST) do begin
                    AddToList(S, IntToHex(byte(ST[j]), 2));
                    if j mod 20 = 0 then S := S + '\'#$0D#$0A;
                   end;
                   if (RegQueryValueEx(Reg.CurrentKey, PChar(TmpLines[i]), nil, @DataType, nil,
                          @DataSize) = ERROR_SUCCESS) and (DataType = REG_MULTI_SZ) then
                           Lines.Add('"'+TmpLines[i]+'"=hex(7):'+S)
                            else Lines.Add('"'+TmpLines[i]+'"=hex:'+S);
                  except
                  end;
                 end;
    end;
   // ��������� �����
   Reg.GetKeyNames(TmpLines);
   for i := 0 to TmpLines.Count - 1 do
    ExpRegKey(ARoot, AKey + TmpLines[i], Lines);
  end;
 finally
  Reg.Free;
  TmpLines.Free;
 end;
end;

// ���������� MD5 ����� �� ��� �����
Function CalkFileMD5(AFileName : string) : string;
var
 MD5Digest   : TMD5Digest;
begin
 Result := '';
 try
  MD5Digest := MD5File(AFileName);
  Result    := MD5DigestToStr(MD5Digest);
 except end;
end;

var
 H : HKEY;
begin
 RegOpenKey(HKEY_CURRENT_USER, 'Software', H); //#DNL
 CU_KEY := GetRegKeyNameByHandle(H);
 CU_KEY := copy(CU_KEY, 1, length(CU_KEY) - 8);
 RegCloseKey(H);
end.

{ ��������� ������ �������� �������������� �������
Function OpenProcessEx(dwProcessId: DWORD): THandle;
var
 HandlesInfo: PSYSTEM_HANDLE_INFORMATION_EX;
 ProcessInfo: _PROCESS_BASIC_INFORMATION;
 idCSRSS: dword;
 hCSRSS : dword;
 tHandle: dword;
 r      : dword;
begin
 Result := 0;
 //��������� ������� csrss.exe
 idCSRSS := GetProcessId('csrss.exe');
 hCSRSS  := OpenProcess(PROCESS_DUP_HANDLE, false, idCSRSS);
 if hCSRSS = 0 then Exit;
 HandlesInfo := GetInfoTable(SystemHandleInformation);
 if HandlesInfo <> nil then
 for r := 0 to HandlesInfo^.NumberOfHandles do
   if (HandlesInfo^.Information[r].ObjectTypeNumber = $5) and  //��� ������ - �������
      (HandlesInfo^.Information[r].ProcessId = idCSRSS) then   //�������� - CSRSS
        begin
          //�������� ����� ����
          if DuplicateHandle(hCSRSS, HandlesInfo^.Information[r].Handle,
                             INVALID_HANDLE_VALUE, @tHandle, 0, false,
                             DUPLICATE_SAME_ACCESS) then

             begin
               ZwQueryInformationProcess(tHandle, ProcessBasicInformation,
                                         @ProcessInfo,
                                         SizeOf(_PROCESS_BASIC_INFORMATION), nil);
               if ProcessInfo.UniqueProcessId = dwProcessId then
                  begin
                    VirtualFree(HandlesInfo, 0, MEM_RELEASE);
                    CloseHandle(hCSRSS);
                    Result := tHandle;
                    Exit;
                  end else CloseHandle(tHandle);
             end;
        end;
 VirtualFree(HandlesInfo, 0, MEM_RELEASE);
 CloseHandle(hCSRSS);
end;
}




{
 if Length(FolderName) = 0 then FolderName := DefaultProgramFilesDir;
  dwStrSize := ExpandEnvironmentStrings( PChar(FolderName), nil, 0 );
  SetLength( Result, dwStrSize );
  ExpandEnvironmentStrings( PChar(FolderName), PChar(Result), dwStrSize );
 }


(*

DEVMODE dm;
EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&dm);
if(dm.dmBitsPerPel>8)Sleep(750);
char *ch=KeyEdit->Text.c_str();
for(; *ch; ++ch)
  {
  if(*ch=='\\')
    {
    SendMessage(Tree,WM_KEYDOWN,VK_RIGHT,0);
    if(dm.dmBitsPerPel>8)Sleep(750);
    }
  else
    SendMessage(Tree,WM_CHAR,toupper(*ch),0);
  }

if(ValueCB->Checked)
  {
  List=FindWindowEx(Regedit,NULL,"SysListView32",NULL);
  SetForegroundWindow(List);
  ::SetFocus(List);
  Sleep(1000);
  SendMessage(List,WM_KEYDOWN,VK_HOME,0);
  ch=ValueEdit->Text.c_str();
  for(; *ch; ++ch)
    SendMessage(List,WM_CHAR,toupper(*ch),0);
  }

 }
 *)

