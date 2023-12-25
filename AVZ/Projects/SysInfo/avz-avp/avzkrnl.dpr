library avzkrnl;
// ���� ������������ ������� AVZ
// ������ �� 29.12.2007
// ���� ����������������� ��� ���������� ��� ������������� DEBUG ������� ���������, �� ��������� ���������� ������ � �����������������
//{$DEFINE DEBUG}
// ���� ����������������� ��� ���������� ��� �������� DEBUG, �� ����� ���������� ����� �� �����������
//{$DEFINE LOC_DEBUG}
uses
  SysUtils,
  Windows,
  Forms,
  Messages,
  Dialogs,
  Classes,
  ActiveX,
  // ����� zAntivirus �������� ������ � ������ AVZ � ������� ��������
  zAntivirus,
  zAVZArcKernel,
  zutil,
  orautil,
  str_serialize,
  zAVZKernel,
  zAVKernel,
  // ��������� � ���������
  zAVZDriver,  zAVZDriverN,  zAVZDriverRK, zAVZDriverBC,
  WIZARDNN,
  zESScripting,
  zVirFileList,
  zUserScripting,
  zScriptingKernel,
  zStringCompressor,
  zLogSystem,
  zSharedFunctions,
  zHTMLTemplate,
  zXML,
  uProcessView,
  uKernelObjectsView,
  uServiceView,
  uAutoruns,
  uFileSearch,
  uBHOManager, uExplorerExtManager,
  uPrintExtManager, uTaskScheduler,
  uSPIView, uDPFManager,
  uCPLManager, uActiveSetup, uHostsManager,
  zBackupEngine,
  zXmlLogger;

{$R *.res}

{uses , , zutil, ntdll,
   uOpenPorts,
    uProtocolManager,
    zAVKernel, zAVZkernel, zTranslate;}
const
  AVZ_ScanError        =  3; // ������ ���������� �� �������
  AVZ_Suspicious       =  2; // ��������������
  AVZ_VirusFound       =  1; // �����
  AVZ_OK               =  0; // �������� ����������

  // ���� ����� ��������
  AVZCB_ScriptCallback    = 0; // ������������� ScriptCallback
  AVZCB_GetLocalizedStr   = 1; // ������������� GetLocalizedStr
  AVZCB_FreeLocalizedStr  = 2; // ������������� FreeLocalizedStr
  AVZCB_CheckFileCallback = 3; // ������������� ExternalCheckFile

  // ���� ������ ������� �������
  smCheck     = 1; // ����� CHECK
  smFix       = 2; // ����� FIX
  smSuperFix  = 3; // ����� SUPERFIX
  smCheckUndo = 4; // ���������, ���� �� ������ ������
  smUndo      = 5; // ��������� �����

  // ���� ������
  AVZ_Error                 = $C0000000; // ������ (�������� �����, ��� ���������)
  AVZ_InvalidKernelHandle   = $C0000001; // ������������ ����� ����
  AVZ_InvalidDBPath         = $C0000002; // ������������ ���� � �����
  AVZ_LoadDBError           = $C0000003; // ������ �������� ���
  AVZ_Cancel                = $C0000004; // ��������� ����
  AVZ_InvalidStream         = $C0000005; // ������������ ����� - ��������� �������� ��������� �� �����, � ��� ���
  AVZ_StreamReadError       = $C0000006; // ������ ������ ������ �� ������
  AVZ_XMLParseError         = $C0000007; // ������ �������� XML
  AVZ_XMLTokenNotFound      = $C0000008; // XML ��� �� ������
  AVZ_InvalidFormatMask     = $C0000009; // ������������ �����, �������� ������ ��������������
  AVZ_InvalidCallbackID     = $C000000A; // ������������ ��� �������
  AVZ_InvalidScriptID       = $C000000B; // ������������ ID �������
  AVZ_InvalidScriptMode     = $C000000C; // ������������ ID ������ ������� �������
  AVZ_InvalidScriptDBHandle = $C000000D; // ������������ ����� ����
  AVZ_InvalidScript         = $C000000E; // ������������ ������ - �� �� ������������� ���������
  AVZ_SR_NotInitialized     = $C1000001; // ���������� SR - �� ��������������� ������ �������
  AVZ_SR_InvalidSession     = $C1000002; // ���������� SR - ������������ ������
  AVZ_SR_InvalidEvent       = $C1000003; // ���������� SR - �������� ������������ �������

  // ���� ������� �������� ����������
  AVZCR_Error = AVZ_Error; // ������
  AVZCR_Clean = 0;       // ����, �� � ���� ���������� �� ������
  AVZCR_VirusFound  = 1; // �������
  AVZCR_Suspicious  = 2; // �������������
  AVZCR_CleanBase   = 3; // ������ � ���� ������
type
 // CallBack �������.
 // ���������� ���������� �������. pTaskContext - �������� �������, dwProgressCurr, dwProgressMax - ��������-���������; szMsg, dwMsgSize - ��������� ��� ����; AVZMSG - ��� ���� ���������
 TAVZCallBackProc = function (pTaskContext : pointer; dwProgressCurr, dwProgressMax : DWORD; szMsg: PWChar; dwMsgSize : dword; AVZMSG : DWORD) : DWORD; stdcall;
 PAVZCallBackProc = ^TAVZCallBackProc;
 // ������� ������. ������ ���������� ��������
 TGetLocalizedStr = function (pTaskContext : pointer;szID: PChar; var pszResult : PWChar) : DWORD; stdcall;
 PGetLocalizedStr = ^TGetLocalizedStr;
 // ������������ ������ ������������ ������
 TFreeLocalizedStr = function (pTaskContext : pointer;pszResult : PWChar) : DWORD; stdcall;
 PFreeLocalizedStr = ^TFreeLocalizedStr;
 // �������� ����� �� ������� ����
 TExternalCheckFile = function (pTaskContext : pointer; szFileName : PWChar; var Res : DWORD) : DWORD; stdcall;
 PExternalCheckFile = ^TExternalCheckFile;

 TAVZScanKernel = class
 private
  Loaded     : Boolean;
  // ����� ��������� �������
  VirusName       : string;
  // ��������� ������������
  FullResult      : integer;
  function OnAVZFileExtracted(AVZArcInfo : TAVZArcInfoArray): boolean;
  function OnTranslateEvent(AStr : string) : string;
 public
  // ��������� ��������-����������
  FMax, FCurr : integer;
  // ������� ��������� ������ ��� ��������� � ��������-���������
  AVZCallBackProc     : PAVZCallBackProc;
  // ������� ��������� ������ ��� ��������
  AVZGetLocalizedStr  : PGetLocalizedStr;
  AVZFreeLocalizedStr : PFreeLocalizedStr;
  // ������� ��������� ������ ��� ������� ���� ����������
  AVZExternalCheckFile : PExternalCheckFile;
  // �������� �������
  pTaskContext  : pointer;
  // ��������
  LogText : TStrings;
  // �������� - ���������� ���������� ������
  constructor Create;
  destructor  Destroy; override;
  // ������� ����������������
  procedure AddToLogEvent(AMsg : string; InfoType : integer);
  procedure AddToDebugLogEvent(AMsg : string);
  // ������ ���������� ������ ���������
  procedure GetLog(ALog : TStrings);
  // ��������-���������
  procedure Progress(AMax, ACurr : integer);
  // �����������  ������
  function  LocalizeStr(S : string) : string;
  // �������� ����� �� ������� ���� ���������� � ������� �������
  function  DoCheckFile(AFileName : string) : dword;
  // ������������ ����� �� ������
  function VirusScan(AFileName: string; ArcInfo : TAVZArcInfoArray): integer;
  // ���������� ������� "�������� ����� �� ���� ������"
  procedure OnFileSignCheck(AFileName : string; var AStatus : integer);
 end;

 // ����� ���� "����". ��������� �� ���� ���������� � �������� "������" �� ��� �������
 TAVZKernel = class
   // ���������� ��� ������������� �������� (KIS, AVPTool ...)
   ProductType : string;
   AVZScanKernel : TAVZScanKernel; // ���� �������
   // ���������
   MainAntivirus   : TAntivirus;
   // ������� �������� ��������
   FileSignCheck   : TFileSignCheck;
   // ������� ���������
   WizardNeuralNetwork : TWizardNeuralNetwork;
   // �������� ��������������
   KeyloggerBase : TKeyloggerBase;
   // ���������� �����������
   RootkitBase   : TRootkitBase;
   // ����������� � ���������� Office
   OfficeMacroBase : TOfficeMacroBase;
   // ��������� �������� �������
   SystemCheck   : TSystemCheck;
   // ��������� �������� ������� - �������� ���. �����������
   SystemIPU     : TSystemIPU;
   // ��������� �������������� �������
   SystemRepair : TSystemRepair;
   // ����������� �������
   StdScripts   : TStdScripts;
   // ���� ���� kernel-mode
   KMBase       : TKMBase;
   // ��������
   AVZDriver     : TAVZDriver;
   AVZDriverBC   : TAVZDriverBC;
   AVZDriverRK   : TAVZDriverRK;
   // ����������� �������
   AVZDecompress : TAVZDecompress;
   // ������ �����������
   TranslateSys  : TTranslate;
   // ������������� ���������� ������
   ESSystem    : TESSystem;
   ESUserScript : TESUserScript;
   // ���� ������� ������
   MemScanBase : TMemScanBase;
   // ������ �������� ������ ��� �������������� ���������
   VirFileList : TVirFileList;
   // ������-������
   AvzUserScript : TAvzUserScript;
   // ����������������
   ZLoggerClass : TLogger;
   ZProgressClass : TzProgress;
   // XML ������
   XMLLogger  : TXMLLogger;
   // �����
   BackupEngine : TZBackupEngine;
   // ������ �������� DB
   DBLoadStatus : dword;
 end;

var
 CopyUnpackedFiles : boolean = false;    // ������� ����������� ������������� ������ � UNPACKED
 UnpackedPath : string;                  // ���� � Unpacked �����
 KrnlList     : TList;                   // ������ ��������������������� ����
 DBList       : TList;                   // ������ ��������������������� ���
 SRSessions   : TList;                   // ������ ������� ��������
 SRSystem     : TSRSystem = nil;         // ����� ������ �������� ��������� - ����� ��� ���� �������

// ��������� ������
function AVZAllocateMemory(ASize : DWORD) : pointer;
begin
 if ASize = 0 then Result := nil
  else Result := GetMemory(ASize);
end;

// ������������ ������
procedure AVZFreeMemory(APtr : pointer);
begin
 FreeMemory(APtr);
end;

// �������� Wide String
function MakeWStr(var ABuf: PWChar; const S: String): DWORD;
begin
 Result := Length(S) * 2 + 1;
 ABuf := AVZAllocateMemory(Result);
 if (ABuf = nil) then begin
  Result := 0;
  exit;
 end;
 StringToWideChar(S, ABuf, Result);
end;

{$IFDEF DEBUG}
// �������� ������ � ����������� �����
Function DebugOutput(s:string):boolean;
var
 f     : TextFile;
 FName : String;
begin
 Result := false;
 FName := 'c:\avzkrnl.dbg';
 AssignFile(f, FName);
 try
  // ���� ���� ���������� - ��������, �� ���������� - ��������
  if FileExists(FName) then Append(f)
   else Rewrite(f);
 except
  exit; // ��� ������� ����������� �����, ���� �� ���������� ��������� ���������
 end;
 try
  Writeln(f, DateTimetoStr(Now)+' : '+s);
 finally
  CloseFile(f); // � ����� ����������� ������� ����
 end;
end;
{$ENDIF}

// ��������� �����
procedure SetupPath(AVZKernel : TAVZKernel);
var
 S : string;
begin
 {$IFDEF DEBUG} DebugOutput('SetupPath"');{$ENDIF}
 S := AVZKernel.AVZScanKernel.LocalizeStr('%DataRoot%');
 if S = '' then exit;
 if S = '%DataRoot%' then exit;
 QuarantineBaseFolder := NormalDir(S);
 {$IFDEF DEBUG} DebugOutput('SetupPath QuarantineBaseFolder = "'+QuarantineBaseFolder+'"');{$ENDIF}
end;

// �������� "������", �������� �� �� ���������� ������� �� ����
function CheckKernelPtr(ppAVZAScanKernel : pointer) : boolean;
begin
 {$IFDEF DEBUG} DebugOutput('CheckKernelPtr ppAVZAScanKernel='+IntToHex(integer(ppAVZAScanKernel), 6));{$ENDIF}
 Result := false;
 // ��������� � ������
 if ppAVZAScanKernel  = nil then exit;
 // ���� ��� � ������ ��������������������
 if KrnlList.IndexOf(ppAVZAScanKernel) < 0 then exit;
 // ���� � ������ ����, �� ��������� �� ���������� �� �������� TAVZKernel
 if not(TObject(ppAVZAScanKernel) is TAVZKernel) then exit;
 {$IFDEF DEBUG} DebugOutput('CheckKernelPtr ppAVZAScanKernel=OK');{$ENDIF}
 Result := true;
end;

// �������� "������", �������� �� �� ���������� ������� �� ����
function CheckDBPtr(ppDBHandle : pointer) : boolean;
begin
 {$IFDEF DEBUG} DebugOutput('CheckDBPtr ppDBHandle='+IntToHex(integer(ppDBHandle), 6));{$ENDIF}
 Result := false;
 // ��������� � ������
 if ppDBHandle  = nil then exit;
 // ���� ��� � ������ ��������������������
 if DBList.IndexOf(ppDBHandle) < 0 then exit;
 // ���� � ������ ����, �� ��������� �� ���������� �� �������� TAVZKernel
 if not(TObject(ppDBHandle) is TCustomScripts) then exit;
 {$IFDEF DEBUG} DebugOutput('CheckDBPtr ppDBHandle=OK');{$ENDIF}
 Result := true;
end;

// ��������� ���� ��� ������
function SetKernel(ppAVZAScanKernel : pointer) : boolean;
var
 Tmp : TAVZKernel;
begin
 Result := false;
 Tmp := (TObject(ppAVZAScanKernel) as TAVZKernel);
 {$IFDEF DEBUG} DebugOutput('SetKernel ppAVZAScanKernel='+Inttohex(dword(ppAVZAScanKernel), 6));{$ENDIF}
 // ��������� ���������� �� "handle" � ���������� ������
 ZLoggerClass   := Tmp.ZLoggerClass;
 ZProgressClass := Tmp.ZProgressClass;
 MainAntivirus  := Tmp.MainAntivirus;
 FileSignCheck  := Tmp.FileSignCheck;
 WizardNeuralNetwork := Tmp.WizardNeuralNetwork;
 KeyloggerBase       := Tmp.KeyloggerBase;
 RootkitBase         := Tmp.RootkitBase;
 OfficeMacroBase     := Tmp.OfficeMacroBase;
 SystemCheck         := Tmp.SystemCheck;
 SystemIPU           := Tmp.SystemIPU;
 SystemRepair        := Tmp.SystemRepair;
 StdScripts          := Tmp.StdScripts;
 KMBase              := Tmp.KMBase;
 AVZDriver           := Tmp.AVZDriver;
 AVZDriverBC         := Tmp.AVZDriverBC;
 AVZDriverRK         := Tmp.AVZDriverRK;
 AVZDecompress       := Tmp.AVZDecompress;
 TranslateSys        := Tmp.TranslateSys;
 ESSystem            := Tmp.ESSystem;
 ESUserScript        := Tmp.ESUserScript;
 MemScanBase         := Tmp.MemScanBase;
 VirFileList         := Tmp.VirFileList;
 XMLLogger           := Tmp.XMLLogger;
 // ������������� ����������� ������
 AvzUserScript       := Tmp.AvzUserScript;
 {$IFDEF DEBUG} DebugOutput('SetKernel OK');{$ENDIF}
 Result := true;
end;

// �������� ���
Function LoadAVBase : dword;
var
 Step : integer;
begin
 Result := 0;
 {$IFDEF DEBUG} DebugOutput('LoadAVBase 0');{$ENDIF}
 Step := 1;
 // �������� ������� AV ����
 try if MainAntivirus.LoadBinDatabase then Result := Result or 1; except end;
 {$IFDEF DEBUG} DebugOutput('LoadAVBase 1');{$ENDIF}
 try
  Step := 2;
  // �������� ���� ������������
  try if OfficeMacroBase.LoadBinDatabase then Result := Result or 2; except end;
  Step := 3;
  // �������� ������� �������� ������
  if FileSignCheck.LoadBinDatabase  then Result := Result or 4;
  Step := 4;
  if SystemCheck.LoadBinDatabase  then Result := Result or 8;
  Step := 5;
  // �������� ������ �������� ������� - ���
  if SystemIPU.LoadBinDatabase  then Result := Result or 16;
  Step := 6;
  // �������� ���� �������������� �������
  if SystemRepair.LoadBinDatabase  then Result := Result or 32;
  Step := 7;
  // �������� ���� ����������� ��������
  if StdScripts.LoadBinDatabase  then Result := Result or 64;
  Step := 8;
  // �������� ���� ������������ ������
  if MemScanBase.LoadBinDatabase  then Result := Result or 128;
  Step := 9;
  // �������� ������ ���������� �������
  if ESSystem.LoadBinDatabase then Result := Result or 256;
  Step := 10;
  // ���� ���������
  if KMBase <> nil then
   if KMBase.LoadBinDatabase  then Result := Result or 512;
  // ���� ���������� ������ ��������
  if SRSystem.LoadBinDatabase then Result := Result or 1024;
  {$IFDEF DEBUG} DebugOutput('LoadAVBase complete. Status = '+inttostr(Result));{$ENDIF}
 except
 {$IFDEF DEBUG}
  on e : Exception do
   DebugOutput('LoadAVBase Step='+IntToStr(Step)+',ERROR = '+e.Message);
 {$ENDIF}
 end;
end;

// �������������. ADbPath - ���� � �����
function AVZ_InitializeExA(var ppAVZAScanKernel : pointer; ADbPath : PChar; AProductType : PChar): DWORD; stdcall;
var
 Tmp : TAVZKernel;
begin
 Result := AVZ_Error;
  {$IFDEF DEBUG} DebugOutput('AVZ_InitializeExA');{$ENDIF}
 KAVQuarantineMode := true;
 // �� ������� ���� � ���� - ������
 if ADbPath = nil then exit;
 {$IFDEF DEBUG} DebugOutput('AVZ_InitializeExA ADbPath = "'+ADbPath+'"');{$ENDIF}
 ppAVZAScanKernel := nil;
 Tmp := TAVZKernel.Create;
 Tmp.AVZScanKernel := TAVZScanKernel.Create;
 Tmp.ProductType := Trim(UpperCase(AProductType));
 // ��������� ����
 ppAVZAScanKernel := Tmp;
 AVPath := Trim(String(ADbPath));
 {$IFDEF DEBUG} DebugOutput('AVZ_InitializeExA AVPath = "'+AVPath+'"');{$ENDIF}
 // �������������� ������� ����������������
 InitLogger;
 {$IFDEF DEBUG} DebugOutput('AVZ_InitializeExA InitLogger OK');{$ENDIF}
 // ��������� ���������� �� ��� ��������� � ��� "handle"
 Tmp.ZLoggerClass  := ZLoggerClass;
 ZLoggerClass.OnAddToDebugLog := Tmp.AVZScanKernel.AddToDebugLogEvent;
 ZLoggerClass.OnAddToLog      := Tmp.AVZScanKernel.AddToLogEvent;
 ZLoggerClass.OnGetLog        := Tmp.AVZScanKernel.GetLog;
 Tmp.ZProgressClass           := ZProgressClass;
 ZProgressClass.OnProgress    := Tmp.AVZScanKernel.Progress;
 ZProgressClass.Max           := 0;
 {$IFDEF DEBUG} DebugOutput('AVZ_InitializeExA Logger+Progress init OK');{$ENDIF}
 // **** ������������� AV ���� (��������� ���������� �������) ***
 // ������������� �������� - AVPTool ��������� �������� AVZ, KAV/KIS - ���� �������
 {$IFDEF DEBUG} DebugOutput('AVZ_InitializeExA ProductType='+Tmp.ProductType);{$ENDIF}
 {$IFDEF DEBUG} DebugOutput('AVZ_InitializeExA InitMode='+Tmp.ProductType);{$ENDIF}
 if Tmp.ProductType = 'KAT' then begin
  InitAVKernel('--');
 end else
  InitAVKernel('--', 1);
 {$IFDEF DEBUG} DebugOutput('AVZ_InitializeExA InitAVKernel OK');{$ENDIF}
 Tmp.MainAntivirus := MainAntivirus;
 Tmp.FileSignCheck := FileSignCheck;
 // ����������� ����������� ������� "�������� ����� �� ���� ������"
 Tmp.FileSignCheck.OnFileSignCheck := Tmp.AVZScanKernel.OnFileSignCheck;
 Tmp.WizardNeuralNetwork := WizardNeuralNetwork;
 Tmp.KeyloggerBase   := KeyloggerBase;
 Tmp.RootkitBase     := RootkitBase;
 Tmp.OfficeMacroBase := OfficeMacroBase;
 Tmp.SystemCheck     := SystemCheck;
 Tmp.SystemIPU       := SystemIPU;
 Tmp.SystemRepair    := SystemRepair;
 Tmp.StdScripts      := StdScripts;
 Tmp.KMBase          := KMBase;
 Tmp.AVZDriver       := AVZDriver;
 Tmp.AVZDriverBC     := AVZDriverBC;
 Tmp.AVZDriverRK     := AVZDriverRK;
 Tmp.AVZDecompress   := AVZDecompress;
 Tmp.TranslateSys    := TranslateSys;
 Tmp.TranslateSys.OnTranslate := Tmp.AVZScanKernel.OnTranslateEvent;
 Tmp.ESSystem        := ESSystem;
 Tmp.ESUserScript    := ESUserScript;
 Tmp.MemScanBase     := MemScanBase;
 Tmp.VirFileList     := VirFileList;
 Tmp.XMLLogger       := XMLLogger;
 // ������������� ����������� ������
 InitScriptingKernel;
 // ������������� ������� ������
 Tmp.BackupEngine    := TZBackupEngine.Create;
 // ������������� ������ ����������� �������� (���������������� ������ �������, ��� ��� ���������)
 if SRSystem = nil then
  SRSystem := TSRSystem.Create(AVPath);
 {$IFDEF DEBUG} DebugOutput('AVZ_InitializeExA InitScriptingKernel OK');{$ENDIF}
 Tmp.AvzUserScript := AvzUserScript;
 Tmp.AvzUserScript.BackupEngine := Tmp.BackupEngine;
 // ���������� ���� � ������
 KrnlList.Add(ppAVZAScanKernel);
 // �������� ����
 Tmp.DBLoadStatus := LoadAVBase;
 if (Tmp.DBLoadStatus and 120 = 120) then
  Result := AVZ_OK
   else begin
    Result := AVZ_LoadDBError;
   end;
 // ���������� ���������� "�������"
 AdjustPrivileges('SeDebugPrivilege', true);       //#DNL
 {$IFDEF DEBUG} DebugOutput('AVZ_InitializeExA. SeDebugPrivilege GetLastError='+IntToStr(GetLastError));{$ENDIF}
 AdjustPrivileges('SeLoadDriverPrivilege', true);  //#DNL
 {$IFDEF DEBUG} DebugOutput('AVZ_InitializeExA. SeLoadDriverPrivilege GetLastError='+IntToStr(GetLastError));{$ENDIF}
 AdjustPrivileges('SeBackupPrivilege', true);      //#DNL
 {$IFDEF DEBUG} DebugOutput('AVZ_InitializeExA. SeBackupPrivilege GetLastError='+IntToStr(GetLastError));{$ENDIF}
 AdjustPrivileges('SeRestorePrivilege', true);     //#DNL
 {$IFDEF DEBUG} DebugOutput('AVZ_InitializeExA. SeRestorePrivilege GetLastError='+IntToStr(GetLastError));{$ENDIF}
 AdjustPrivileges('SeShutdownPrivilege', true);     //#DNL
 {$IFDEF DEBUG} DebugOutput('AVZ_InitializeExA. SeShutdownPrivilege GetLastError='+IntToStr(GetLastError));{$ENDIF}
end;

// �������������. ADbPath - ���� � ����� (Wide String)
function AVZ_InitializeExW(var ppAVZAScanKernel : pointer; ADbPath : PWChar; AProductType : PWChar): DWORD; stdcall;
var
 S, S1 : string;
begin
 Result := AVZ_Error;
 if ADbPath = nil then
  exit;
 if AProductType = nil then
  exit;
 S  := Trim(String(ADbPath));
 S1 := Trim(String(AProductType));
 Result := AVZ_InitializeExA(ppAVZAScanKernel, PChar(S), PChar(S1));
end;

// ���������� ���������� ���� � ����������� ������
function AVZ_Done(ppAVZAScanKernel : pointer): DWORD; stdcall;
begin
 {$IFDEF DEBUG} DebugOutput('AVZ_Done');{$ENDIF}
 // �������� ������������ ������ ����
 Result := AVZ_InvalidKernelHandle;
 if not(CheckKernelPtr(ppAVZAScanKernel)) then exit;
 {$IFDEF DEBUG} DebugOutput('AVZ_Done 1');{$ENDIF}
 // ���������� ��������
 with TAVZKernel(ppAVZAScanKernel) do begin
  AVZScanKernel.Free;
  AVZScanKernel := nil;
  ZLoggerClass.Free;
  MainAntivirus.Free;
  FileSignCheck.Free;
  WizardNeuralNetwork.Free;
  KeyloggerBase.Free;
  RootkitBase.Free;
  OfficeMacroBase.Free;
  SystemCheck.Free;
  SystemIPU.Free;
  SystemRepair.Free;
  StdScripts.Free;
  KMBase.Free;
  AVZDriver.Free;
  AVZDriverBC.Free;
  AVZDriverRK.Free;
  AVZDecompress.Free;
  TranslateSys.Free;
  ESSystem.Free;
  ESUserScript.Free;
  MemScanBase.Free;
  VirFileList.Free;
  AvzUserScript.Free;
  BackupEngine.Free;
  DBLoadStatus := 0;
  Free;
 end;
 Result := AVZ_OK;
 {$IFDEF DEBUG} DebugOutput('AVZ_Done OK');{$ENDIF}
 // �������� ���� �� ������ ���������������������
 try
  KrnlList.Delete(KrnlList.IndexOf(ppAVZAScanKernel));
 except
 end;
 // ���� ������ ��������������������� ���� ����, �� ��������� ���������� �������
 if KrnlList.Count = 0 then begin
  // ���������� ������ ������� ������ ��������
  SRSystem.Free;
  SRSystem := nil;
 end;
end;

// ������������ ���
function AVZ_ReloadBase(ppAVZAScanKernel : pointer): DWORD; stdcall;
begin
 {$IFDEF DEBUG} DebugOutput('AVZ_ReloadBase');{$ENDIF}
 // �������� ������������ ������ ����
 Result := AVZ_InvalidKernelHandle;
 // �������� ��������� �� ����
 if not(CheckKernelPtr(ppAVZAScanKernel)) then exit;
 // ��������� ����
 SetKernel(ppAVZAScanKernel);
 {$IFDEF DEBUG} DebugOutput('AVZ_ReloadBase SetKernel OK');{$ENDIF}
 // �������� ����
 (TObject(ppAVZAScanKernel) as TAVZKernel).DBLoadStatus := LoadAVBase;
 if ((TObject(ppAVZAScanKernel) as TAVZKernel).DBLoadStatus and 1020 = 1020) then
  Result := AVZ_OK
 else begin
  Result := AVZ_LoadDBError;
 end;
end;

// ������ ������� ���
function AVZ_GetDBStatus(ppAVZAScanKernel : pointer): dword; stdcall;
begin
 {$IFDEF DEBUG} DebugOutput('AVZ_GetDBStatus');{$ENDIF}
 // �������� ������������ ������ ����
 Result := 0;
 // �������� ��������� �� ����
 if not(CheckKernelPtr(ppAVZAScanKernel)) then exit;
 // ������� ����������
 Result := (TObject(ppAVZAScanKernel) as TAVZKernel).DBLoadStatus;
end;

// �������� ����� �� ���� ���������
function AVZ_CheckFile(ppAVZAScanKernel : pointer; szFileName : PWChar; var szVerdict : PWChar): Integer; stdcall;
var
 FileName : string;
 CriticalSection: TRTLCriticalSection;
 Krnl : TAVZKernel;
begin
 {$IFDEF DEBUG} DebugOutput('AVZ_CheckFile');{$ENDIF}
 // �������� ������������ ������ ����
 Result := AVZ_InvalidKernelHandle;
 // �������� ��������� �� ����
 if not(CheckKernelPtr(ppAVZAScanKernel)) then exit;
 // ��������� ����
 SetKernel(ppAVZAScanKernel);
 {$IFDEF DEBUG} DebugOutput('AVZ_CheckFile SetKernel OK');{$ENDIF}

 Krnl := ppAVZAScanKernel;

 FileName := Trim(szFileName);
 Result := AVZ_OK;
 Krnl.AVZScanKernel.VirusName := '';
 Krnl.AVZScanKernel.FullResult := 0;
 try
  Krnl.AVZScanKernel.VirusScan(FileName, nil);
 except
  on e: exception do
   Krnl.AVZScanKernel.FullResult := 3;
 end;
 // �������� �����
 case Krnl.AVZScanKernel.FullResult of
  // ������
  0 : Result := AVZ_OK;
  // ������� (szVerdict = ���)
  1 : begin
       Result := AVZ_VirusFound;
       MakeWStr(szVerdict, Krnl.AVZScanKernel.VirusName);
      end;
  // ���������� (szVerdict = ��� + ���������)
  2 : begin
       Result := AVZ_Suspicious;
       MakeWStr(szVerdict, Krnl.AVZScanKernel.VirusName);
      end;
  // ������
  3 : begin
       Result := AVZ_ScanError;
      end;
 end;
end;

// ��������� ��������
function AVZ_SetCallbackProc(ppAVZAScanKernel : pointer; dwCallBackID : dword; AVZCallBackProc : pointer) : DWORD; stdcall;
begin
 Result := AVZ_Error;
 {$IFDEF DEBUG} DebugOutput('AVZ_GetSomeInfo');{$ENDIF}
 // �������� ������������ ������ ����
 Result := AVZ_InvalidKernelHandle;
 // �������� ��������� �� ����
 if not(CheckKernelPtr(ppAVZAScanKernel)) then exit;
 // ��������� �������
 Result := AVZ_OK;
 case dwCallBackID of
  // ������ ����������� ��������� � ���� �������
  AVZCB_ScriptCallback    : TAVZKernel(ppAVZAScanKernel).AVZScanKernel.AVZCallBackProc      := AVZCallBackProc;
  // ����������� - ������ ��������
  AVZCB_GetLocalizedStr   : TAVZKernel(ppAVZAScanKernel).AVZScanKernel.AVZGetLocalizedStr   := AVZCallBackProc;
  // ����������� - ������������ ������
  AVZCB_FreeLocalizedStr  : TAVZKernel(ppAVZAScanKernel).AVZScanKernel.AVZFreeLocalizedStr  := AVZCallBackProc;
  // �������� ����� ������� AV �������
  AVZCB_CheckFileCallback : TAVZKernel(ppAVZAScanKernel).AVZScanKernel.AVZExternalCheckFile := AVZCallBackProc;
  else
   Result := AVZ_InvalidCallbackID;
 end;
end;

// ��������� ��������� ������
function AVZ_SetCallbackCtx(ppAVZAScanKernel : pointer; pTaskContext : pointer) : DWORD; stdcall;
begin
 Result := AVZ_Error;
 {$IFDEF DEBUG} DebugOutput('AVZ_GetSomeInfo');{$ENDIF}
 // �������� ������������ ������ ����
 Result := AVZ_InvalidKernelHandle;
 // �������� ��������� �� ����
 if not(CheckKernelPtr(ppAVZAScanKernel)) then exit;
 // ��������� ���������
 TAVZKernel(ppAVZAScanKernel).AVZScanKernel.pTaskContext    := pTaskContext;
 Result := AVZ_OK;
end;

// ������������ ���������� � XML ������� �� ��������� ����-������
function AVZ_GetXMLInfo(AInfoClass : string; ALines : TStrings) : DWORD;
var
 HideGoodFiles : boolean;
begin
 Result := AVZ_Error;
 HideGoodFiles := false;
 AInfoClass := Trim(UpperCase(AInfoClass));
 ZProgressClass.AddProgressMax(100);
 // ����� ������ � ���������
 if (AInfoClass = 'PROCESS') or (AInfoClass = 'DLL') then  begin
  try
   ProcessView := nil;
   ProcessView := TProcessView.Create(nil);
   ProcessView.CreateProcessList;
   ProcessView.CreateXMLProcessLog(ALines, HideGoodFiles);
   ZProgressClass.ProgressStep(100);
   Result := AVZ_OK;
  finally
   ProcessView.Free;
   ProcessView := nil;
  end;
 end;
 // ����� ������ � ������� ����
 if (AInfoClass = 'KERNELOBJ') then  begin
  try
   KernelObjectsView := nil;
   KernelObjectsView := TKernelObjectsView.Create(nil);
   KernelObjectsView.RefreshModuleList;
   KernelObjectsView.CreateXMLReport(ALines, HideGoodFiles);
   ZProgressClass.ProgressStep(100);
  finally
   KernelObjectsView.Free;
   KernelObjectsView := nil;
  end;
 end;

 // ����� ������ � �������
 if (AInfoClass = 'SERVICE') then  begin
  try
   ServiceView := nil;
   ServiceView := TServiceView.Create(nil);
   ServiceView.cbServiceMode.ItemIndex := 0;
   ServiceView.cbServiceStatus.ItemIndex := 2;
   ServiceView.CreateServiceList;
   ServiceView.CreateXMLReport(ALines, HideGoodFiles);
  finally
   ServiceView.Free;
   ServiceView := nil;
  end;
 end;

 // ����� ������ � ���������
 if (AInfoClass = 'DRIVERS') then  begin
  try
   ServiceView := nil;
   ServiceView := TServiceView.Create(nil);
   ServiceView.cbServiceMode.ItemIndex := 1;
   ServiceView.cbServiceStatus.ItemIndex := 2;
   ServiceView.CreateServiceList;
   ServiceView.CreateXMLReport(ALines, HideGoodFiles);
  finally
   ServiceView.Free;
   ServiceView := nil;
  end;
 end;
 // ����� ������ � ��������� �����������
 if (AInfoClass = 'AUTORUN') then  begin
  try
   Autoruns := nil;
   Autoruns := TAutoruns.Create(nil);
   Autoruns.RefreshItems(true);
   Autoruns.CreateXMLReport(ALines, HideGoodFiles);
  finally
   Autoruns.Free;
   Autoruns := nil;
  end;
 end;
 // ����� ������ � BHO
 if (AInfoClass = 'BHO') then  begin
  try
   BHOManager := nil;
   BHOManager := TBHOManager.Create(nil);
   BHOManager.RefreshBHOList;
   BHOManager.CreateXMLReport(ALines, HideGoodFiles);
  finally
   BHOManager.Free;
   BHOManager := nil;
  end;
 end;
 // ����� ������ � ����������� ����������
 if (AInfoClass = 'EXPLOREREXT') then  begin
  try
   ExplorerExtManager := nil;
   ExplorerExtManager := TExplorerExtManager.Create(nil);
   ExplorerExtManager.RefreshExplorerExtList;
   ExplorerExtManager.CreateXMLReport(ALines, HideGoodFiles);
  finally
   ExplorerExtManager.Free;
   ExplorerExtManager := nil;
  end;
 end;
 // ����� ������ � ����������� ������� ������
 if (AInfoClass = 'PRINTEXT') then  begin
  try
   PrintExtManager := nil;
   PrintExtManager := TPrintExtManager.Create(nil);
   PrintExtManager.RefreshPrintExtList;
   PrintExtManager.CreateXMLReport(ALines, HideGoodFiles);
  finally
   PrintExtManager.Free;
   PrintExtManager := nil;
  end;
 end;
 // ����� ������ � �������� ������������
 if (AInfoClass = 'TASKSCHEDULER') then  begin
  try
   TaskScheduler := nil;
   TaskScheduler := TTaskScheduler.Create(nil);
   TaskScheduler.RefreshTaskSchedulerJobs;
   TaskScheduler.CreateXMLReport(ALines, HideGoodFiles);
  finally
   TaskScheduler.Free;
   TaskScheduler := nil;
  end;
 end;
 // ����� ������ � SPI/LSP/NSP �����������
 if (AInfoClass = 'SPI') then  begin
  try
   SPIView := nil;
   SPIView := TSPIView.Create(nil);
   SPIView.ResreshLists;
   //SPIView.CreateXMLReport(ALines, HideGoodFiles);
  finally
   SPIView.Free;
   SPIView := nil;
  end;
 end;
 // ����� ������ � DPF
 if (AInfoClass = 'DPF') then  begin
  try
   DPFManager := nil;
   DPFManager := TDPFManager.Create(nil);
   DPFManager.RefreshDPFList;
   DPFManager.CreateXMLReport(ALines, HideGoodFiles);
  finally
   DPFManager.Free;
   DPFManager := nil;
  end;
 end;
 // ����� ������ � CPL
 if (AInfoClass = 'CPL') then  begin
  try
   CPLManager := nil;
   CPLManager := TCPLManager.Create(nil);
   CPLManager.RefreshCPLList;
   CPLManager.CreateXMLReport(ALines, HideGoodFiles);
  finally
   CPLManager.Free;
   CPLManager := nil;
  end;
 end;
 // ����� ������ � Active Setup
 if (AInfoClass = 'ACTIVESETUP') then  begin
  try
   ActiveSetupManager := nil;
   ActiveSetupManager := TActiveSetupManager.Create(nil);
   ActiveSetupManager.RefreshASList;
   ActiveSetupManager.CreateXMLReport(ALines, HideGoodFiles);
  finally
   ActiveSetupManager.Free;
   ActiveSetupManager := nil;
  end;
 end;
 // ����� ������ � ���������� HOSTS �����
 if (AInfoClass = 'HOSTS') then  begin
  try
   HostsManager := nil;
   HostsManager := THostsManager.Create(nil);
   HostsManager.RefreshInfo;
   HostsManager.CreateXMLReport(ALines, HideGoodFiles);
  finally
   HostsManager.Free;
   HostsManager := nil;
  end;
 end;
end;

// ���������� �ustom ������� �� ���� (AID-����� �������, AMode - ��� ������, Res - ��� ��������)
function AVZ_RunCustomScript(ppAVZAScanKernel, ppDBHandle : pointer; AID, AMode : dword; var Res : dword) : DWORD; stdcall;
var
 ModeStr, S : string;
 CustomScripts : TCustomScripts;
 DBInds : dword;
 i : integer;
begin
 Res    := 0;
 Result := AVZ_Error;
 {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript');{$ENDIF}
 // �������� ������������ ������ ����
 Result := AVZ_InvalidKernelHandle;
 // �������� ��������� �� ����
 if not(CheckKernelPtr(ppAVZAScanKernel)) then exit;
 // �������� ������ ����
 if not(CheckDBPtr(ppDBHandle)) then begin
  Result := AVZ_InvalidScriptDBHandle;
  exit;
 end;
 {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript DB handle OK');{$ENDIF}
 // ��������� ����
 SetKernel(ppAVZAScanKernel);
 SetupPath((TObject(ppAVZAScanKernel) as TAVZKernel));
 {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript SetKernel OK');{$ENDIF}
 CustomScripts := TCustomScripts(ppDBHandle);
 DBInds := $FFFFFFFF;
 {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript Search script by ID='+inttostr(AID));{$ENDIF}
 for i := 0 to Length(CustomScripts.Scripts)-1 do
  if CustomScripts.Scripts[i].ID = AID then begin
   DBInds := i;
   break;
  end;
 {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript Search script complete, Index='+inttostr(DBInds));{$ENDIF}
 // �������� ������������ ������� �������
 if (DBInds = $FFFFFFFF) or not(DBInds < Length(CustomScripts.Scripts)) then begin
  Result := AVZ_InvalidScriptID;
  exit;
 end;
 // ���������� ������ � �������� �������� �������
 S := Trim(DeCompressString(CustomScripts.Scripts[DBInds].CompressedName));
 S := (TObject(ppAVZAScanKernel) as TAVZKernel).AVZScanKernel.LocalizeStr(S);
 ZLoggerClass.AddToLog(S, logInfo);
 // ������������ ���� ������
 ModeStr := '';
 case (AMode and $FFFF) of
  smCheck    : ModeStr := 'CHECK'; // ����� ��������
  smFix      : ModeStr := 'FIX'; // ���� ��������
  smSuperFix : ModeStr := 'SUPERFIX'; // ��������� (����������� �������� ������)
  // ��������, ���� �� �����
  smCheckUndo : begin
                {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript CheckUndo');{$ENDIF}
                 if (TObject(ppAVZAScanKernel) as TAVZKernel).BackupEngine.BackUpExists(IntToStr(AID)) then
                  Res := 1
                 else Res := 0;
                {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript CheckUndo Res='+InttoStr(Res));{$ENDIF}
                 Result := AVZ_OK;
                 exit;
                end;
  // ���������� ������
  smUndo      : begin
                {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript Undo');{$ENDIF}
                 if (TObject(ppAVZAScanKernel) as TAVZKernel).BackupEngine.UndoChanges(IntToStr(AID), true) then
                  Res := 0
                 else Res := 1;
                {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript Undo Res ='+InttoStr(Res));{$ENDIF}
                 Result := AVZ_OK;
                 exit;
                end;
 end;
 // ��� ������ �� ������� ���������� - ����� � �������
 if ModeStr = '' then begin
  Result := AVZ_InvalidScriptMode;
  exit;
 end;
 {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript ModeStr='+ModeStr);{$ENDIF}
 // ���������� �������
 AvzUserScript.StopF := false;
 StopF := false;
 try
  // ���������� �� ���� �������, ��� ������������ � ������
  S := Trim(DeCompressString(CustomScripts.Scripts[DBInds].CompressedText));
  S := S + #$0D#$0A+' begin if AFilename = ''FIX'' then OutRes := IntToStr(Fix) else if AFilename = ''SUPERFIX'' then begin SetupAVZ(''ExtDelete=Y'');OutRes := IntToStr(Fix); end else OutRes := IntToStr(Check); end.';
  {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript Script='+S);{$ENDIF}
  // ������
  AvzUserScript.BackupEngine.BackupId := IntToStr(AID);
  if AvzUserScript.ExecuteScript(ModeStr, S) then begin
   {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript Call Scrip=OK, Res='+AvzUserScript.OutRes);{$ENDIF}
   Result := AVZ_OK;
   // �������� ���� ��������
   Res    := StrToIntDef(AvzUserScript.OutRes, AVZ_Error);
   if Res = AVZ_Error then begin
    Result := AVZ_Error;
    Res    := 0;
   end;
  end;
  if StopF then
   Result := AVZ_Cancel;
 except
   {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript Call Scrip=ERROR, Res='+AvzUserScript.OutRes);{$ENDIF}
   if StopF then
    Result := AVZ_Cancel
   else
    Result := AVZ_Error;
 end;
end;

// ���������� �������
function AVZ_ExecuteMacro(ppAVZAScanKernel : pointer; szMacro : String; Stream : IStream) : DWORD;
var
 S, ST : string;
 Lines : TStringList;
 cbWritten: Longint;
 X1, X2, DW : dword;
 MS : TMemoryStream;
begin
 Result := AVZ_Error;
 szMacro := Trim(szMacro);
 {$IFDEF DEBUG} DebugOutput('AVZ_ExecuteMacro (internal function) Macro="'+szMacro+'"');{$ENDIF}
 // ��������� ������� �������� ## (� ������ ���������� ������, ��� ����������� �������� ���)
 if copy(szMacro, 1, 2) <>  '##' then exit;
 Delete(szMacro, 1, 2);
 szMacro := Trim(szMacro);
 // ������ ������� ������ � ������� XML
 if pos('GETXMLINFO', UpperCase(szMacro)) = 1 then begin
  // �������� ����-�����
  S := copy(szMacro, pos('=', szMacro)+1, maxint);
  Lines := TStringList.Create;
  Result := AVZ_GetXMLInfo(S, Lines);
  if Result = AVZ_OK then begin
   Lines.Insert(0, '<AVZ>');
   Lines.Add('</AVZ>');
   S := Lines.Text;
   Stream.Write(@S[1],Length(S), @cbWritten);
  end;
  exit;
 end;

 // �������� ��� ������
 if pos('BACKUP.LOAD', UpperCase(szMacro)) = 1 then begin
  // �������� ��� �����
  S := Trim(copy(szMacro, pos('=', szMacro)+1, maxint));
 {$IFDEF DEBUG} DebugOutput('AVZ_ExecuteMacro (internal function) BACKUP.LOAD, File="'+S+'"');{$ENDIF}
  MS := TMemoryStream.Create;
  // ������� ��������� ����
  try
   MS.LoadFromFile(S);
  {$IFDEF DEBUG} DebugOutput('BACKUP.LOAD - File load OK');{$ENDIF}
  except
   on e : exception do begin
    Result := AVZ_Error;
    {$IFDEF DEBUG} DebugOutput('BACKUP.LOAD - ERROR= '+e.message);{$ENDIF}
    MS.Free;
    exit;
   end;
  end;
  {$IFDEF DEBUG} DebugOutput('BACKUP.LOAD - MS Size = '+inttostr(MS.Size));{$ENDIF}
  if (TObject(ppAVZAScanKernel) as TAVZKernel).BackupEngine.LoadBackupDB(MS) then begin
   {$IFDEF DEBUG} DebugOutput('BACKUP.LOAD - DB load OK');{$ENDIF}
   {$IFDEF DEBUG} DebugOutput('BACKUP.LOAD, ItemsCount='+inttostr((TObject(ppAVZAScanKernel) as TAVZKernel).BackupEngine.BackupDB.Count));{$ENDIF}
   Result := AVZ_OK;
  end else
   Result := AVZ_Error;
  MS.Free;
  exit;
 end;

 // ���������� ��� ������
 if pos('BACKUP.SAVE', UpperCase(szMacro)) = 1 then begin
  // �������� ��� �����
  S := Trim(copy(szMacro, pos('=', szMacro)+1, maxint));
 {$IFDEF DEBUG} DebugOutput('AVZ_ExecuteMacro (internal function) BACKUP.SAVE, File="'+S+'"');{$ENDIF}
  MS := TMemoryStream.Create;
  // ���������� ���� � �����
  {$IFDEF DEBUG} DebugOutput('AVZ_ExecuteMacro (internal function) BACKUP.SAVE, ItemsCount='+inttostr((TObject(ppAVZAScanKernel) as TAVZKernel).BackupEngine.BackupDB.Count));{$ENDIF}
  if (TObject(ppAVZAScanKernel) as TAVZKernel).BackupEngine.SaveBackupDB(MS) then
   Result := AVZ_OK;
  {$IFDEF DEBUG} DebugOutput('AVZ_ExecuteMacro (internal function) BACKUP.SAVE, MS.Size='+inttostr(MS.Size));{$ENDIF}
  // ������� ��������� ����
  try
   // �������� �����
   zForceDirectories(ExtractFilePath(S));
   // ���������� ����
   MS.Seek(0,0);
   MS.SaveToFile(S);
  {$IFDEF DEBUG} DebugOutput('BACKUP.SAVE - OK, File="'+S+'"');{$ENDIF}
  except
   on e : exception do begin
    Result := AVZ_Error;
    {$IFDEF DEBUG} DebugOutput('BACKUP.SAVE - ERROR= '+e.message);{$ENDIF}
    MS.Free;
    exit;
   end;
  end;
  MS.Free;
  exit;
 end;

 // ���������� ��� ������
 if pos('GUI.FILESEARCH', UpperCase(szMacro)) = 1 then begin
  try
   FileSearchDLG := TFileSearchDLG.Create(nil);
   FileSearchDLG.DefaultMonitor := dmPrimary;
   FileSearchDLG.Execute;
   Result := AVZ_OK;
  finally
   FileSearchDLG.Free;
   FileSearchDLG := nil;
  end;
 end;

 { // ������ �������� ���� AVZ � ���������
 if pos('SCRIPTDB.LOAD', UpperCase(szMacro)) = 1 then begin
  S := copy(szMacro, pos('=', szMacro)+1, maxint);
  // �������� ����
  if (CustomScripts.LoadBinDatabase(S) then
   Result := AVZ_OK;
  exit;
 end;
 // ������ ������� ���������� �������� � ����
 if pos('SCRIPTDB.COUNT', UpperCase(szMacro)) = 1 then begin
  if Stream <> nil then begin
   DW := Length((TObject(ppAVZAScanKernel) as TAVZKernel).CustomScripts.Scripts);
   Stream.Write(@DW, 4, @cbWritten);
   if cbWritten = 4 then
    Result := AVZ_OK;
  end;
  exit;
 end;
 // ������ ������� ���������� �������� � ����
 if pos('SCRIPTDB.RUN', UpperCase(szMacro)) = 1 then begin
  if Stream = nil then exit;
  // ��������� ����������
  S := Trim(copy(szMacro, pos('=', szMacro)+1, maxint));
  // �������� 1 (����� �������)
  X1 := StrToIntDef(copy(S, 1, pos(',',S)-1), $FFFFFFFF);
  Delete(S, 1, pos(',', S));
  S := Trim(S);
  // �������� 2 (����� �������)
  X2 := StrToIntDef(S, $FFFFFFFF);
  //Result := AVZ_RunCustomScript(ppAVZAScanKernel, X1, X2, DW);
  Stream.Write(@DW, 4, @cbWritten);
  exit;
 end;}
end;

// ���������� �������
function AVZ_RunScript(ppAVZAScanKernel : pointer; szScript : PWChar; Stream : IStream) : DWORD; stdcall;
begin
 Result := AVZ_Error;
 {$IFDEF DEBUG} DebugOutput('AVZ_RunScript');{$ENDIF}
 // �������� ��������� �� ������
 if szScript = nil then exit;
 ExtMenuScripts := nil;
 // �������� ������������ ������ ����
 Result := AVZ_InvalidKernelHandle;
 // �������� ��������� �� ����
 if not(CheckKernelPtr(ppAVZAScanKernel)) then exit;
 // ��������� ����
 SetKernel(ppAVZAScanKernel);
 SetupPath((TObject(ppAVZAScanKernel) as TAVZKernel));
 {$IFDEF DEBUG} DebugOutput('AVZ_RunScript SetKernel OK');{$ENDIF}
 {$IFDEF DEBUG} DebugOutput('AVZ_RunScript QuarantineDir = '+GetQuarantineDirName('Quarantine'));{$ENDIF}
 // ��������� ��������-����������
 ZProgressClass.Max  := 0;
 // ���� ����� ������� ���������� � ##, �� ��� �� ������, � ������
 if copy(String(szScript), 1, 2) = '##' then
  Result := AVZ_ExecuteMacro(ppAVZAScanKernel, String(szScript), Stream)
 else begin
  // ���������� �������
  AvzUserScript.StopF := false;
  StopF := false;
  try
   if AvzUserScript.ExecuteScript('', String(szScript)) then begin
    AddToLog('$AVZ0990', logNormal);
    Result := AVZ_OK;
   end else
    AddToLog('$AVZ0630: '+AvzUserScript.LastError+' $AVZ0093 '+AvzUserScript.LastErrorPos, logError);
   if StopF then
    Result := AVZ_Cancel;
  except
    if StopF then
     Result := AVZ_Cancel
    else
     Result := AVZ_Error;
  end;
 end;
end;

// �������� ���� �ustom ��������
function AVZ_LoadCustomScriptDB(ppAVZAScanKernel : pointer; szDBFilename : PWideChar; var ppDBHandle : pointer) : DWORD; stdcall;
var
 CustomScripts : TCustomScripts;
begin
 Result := AVZ_Error;
 ppDBHandle := nil;
 {$IFDEF DEBUG} DebugOutput('AVZ_LoadCustomScriptDB. File = '+szDBFilename);{$ENDIF}
 // �������� ��������� �� ������
 if szDBFilename = nil then exit;
 // �������� ������������ ������ ����
 Result := AVZ_InvalidKernelHandle;
 // �������� ��������� �� ����
 if not(CheckKernelPtr(ppAVZAScanKernel)) then exit;
 // ��������� ����
 SetKernel(ppAVZAScanKernel);
 {$IFDEF DEBUG} DebugOutput('AVZ_LoadCustomScriptDB SetKernel OK');{$ENDIF}
 CustomScripts := TCustomScripts.Create;
 SetupPath((TObject(ppAVZAScanKernel) as TAVZKernel));
 // �������� ����
 if CustomScripts.LoadBinDatabase(string(szDBFilename)) then begin
  Result := AVZ_OK;
  // ���������� ����� ���� � ������ ���
  DBList.Add(CustomScripts);
  ppDBHandle := pointer(CustomScripts);
 {$IFDEF DEBUG} DebugOutput('AVZ_LoadCustomScriptDB. Load = OK');{$ENDIF}
 end else begin
 {$IFDEF DEBUG} DebugOutput('AVZ_LoadCustomScriptDB. Load = ERROR');{$ENDIF}
  ppDBHandle := nil;
  CustomScripts.Free;
  CustomScripts := nil;
 end;
end;

// ������ ���-�� �������� �� ����
function AVZ_GetCustomScriptDBScrCount(ppAVZAScanKernel, ppDBHandle : pointer; var RecCount : dword) : DWORD; stdcall;
var
 CustomScripts : TCustomScripts;
begin
 RecCount := 0;
 Result := AVZ_Error;
 {$IFDEF DEBUG} DebugOutput('AVZ_GetCustomScriptDBScrCount');{$ENDIF}
 // �������� ������������ ������ ����
 Result := AVZ_InvalidKernelHandle;
 // �������� ��������� �� ����
 if not(CheckKernelPtr(ppAVZAScanKernel)) then exit;
 // ��������� ����
 SetKernel(ppAVZAScanKernel);
 {$IFDEF DEBUG} DebugOutput('AVZ_GetCustomScriptDBScrCount SetKernel OK');{$ENDIF}
 // �������� ������ ����
 if not(CheckDBPtr(ppDBHandle)) then begin
  Result := AVZ_InvalidScriptDBHandle;
  exit;
 end;
 {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript DB handle OK');{$ENDIF}
 CustomScripts := TObject(ppDBHandle) as TCustomScripts;
 // �������� ����
 RecCount := Length(CustomScripts.Scripts);
 Result := AVZ_OK;
end;

// ������ ���-�� �������� �� ����
function AVZ_FreeCustomScriptDB(ppAVZAScanKernel, ppDBHandle : pointer) : DWORD; stdcall;
var
 CustomScripts : TCustomScripts;
 X : integer;
begin
 Result := AVZ_Error;
 {$IFDEF DEBUG} DebugOutput('AVZ_FreeCustomScriptDB');{$ENDIF}
 // �������� ������������ ������ ����
 Result := AVZ_InvalidKernelHandle;
 // �������� ��������� �� ����
 if not(CheckKernelPtr(ppAVZAScanKernel)) then exit;
 // ��������� ����
 SetKernel(ppAVZAScanKernel);
 {$IFDEF DEBUG} DebugOutput('AVZ_FreeCustomScriptDB SetKernel OK');{$ENDIF}
 // �������� ������ ����
 if not(CheckDBPtr(ppDBHandle)) then begin
  Result := AVZ_InvalidScriptDBHandle;
  exit;
 end;
 {$IFDEF DEBUG} DebugOutput('AVZ_RunCustomScript DB handle OK');{$ENDIF}
 CustomScripts := TObject(ppDBHandle) as TCustomScripts;
 // �������� ���� �� ������ ��������������������� ���
 X := DBList.IndexOf(CustomScripts);
 if X >= 0 then
  DBList.Delete(X);
 // ������������ ������
 CustomScripts.Free;
 CustomScripts := nil;
 Result := AVZ_OK;
end;

function  AVZ_DeserializeXML(ppAVZAScanKernel : pointer; XMLStream : IStream; szTagName, szBufFormat : PWideChar; var ppAVZBuffer : pointer; var BufSize : dword): DWORD; stdcall;
var
 XMLParser   : TXMLParser;
 DataToken   : TXMLToken;
 Str2Bin     : TStr2Bin;
 S, ST, FieldName, FieldType, FieldDef  : string;
 i, j, BW : integer;
 FieldTypeCode : TZFieldType;
 Tmp         : int64;
 BytesReaded : longint;
 Ptr, PrevPtr : pointer;
begin
 BufSize := 0;
 Str2Bin := nil;
 Result := AVZ_InvalidKernelHandle;
 {$IFDEF DEBUG} DebugOutput('AVZ_DeserializeXML');{$ENDIF}
 ppAVZBuffer := nil;
 // �������� ������������ ������ ����
 if not(CheckKernelPtr(ppAVZAScanKernel)) then exit;
 // �������� ��������� �� �����
 Result := AVZ_InvalidStream;
 if XMLStream = nil then exit;
 // �������� ���������� �� ������
 Result := AVZ_Error;
 if (szTagName = nil) or (szBufFormat = nil) then exit;
 {$IFDEF DEBUG} DebugOutput('AVZ_DeserializeXML - ��� �������� ������');{$ENDIF}
 // ���������� � �������� ��������� ������
 // ���������� ������ � ��������
 S := Trim(String(szBufFormat)) + ';';
 {$IFDEF DEBUG} DebugOutput('AVZ_DeserializeXML - szBufFormat='+S);{$ENDIF}
 // ������������� ����������
 Str2Bin := TStr2Bin.Create;
 // ������������� �������
 XMLParser := TXMLParser.Create;
 try
   // ���� ���������� ���������� �����
   while pos(';', S) > 0 do begin
    // ��������� ���������� ��������
    ST := Trim(copy(S, 1, pos(';', S)-1));
    Delete(S, 1, pos(';', S));
    // ������� ������ ��������
    if ST = '' then continue;
    // ��������� ����� ����
    FieldName := Trim(copy(ST, 1, pos('=', ST)-1));
    Delete(ST, 1, pos('=', ST));
    // ��������� ����
    FieldType := Trim(UpperCase(copy(ST, 1, pos(',', ST)-1)));
    // ��������� �������� �� ���������
    FieldDef  := Trim(copy(ST, pos(',', ST)+1, maxint));
    // ����������� ���� ���� �� ��� �����
    FieldTypeCode := ftNotDefined;
    if FieldType = 'FTBYTE' then FieldTypeCode := ftByte else
    if FieldType = 'FTWORD' then FieldTypeCode := ftWord else
    if FieldType = 'FTDWORD' then FieldTypeCode := ftDWord else
    if FieldType = 'FTINTEREG' then FieldTypeCode := ftInteger else
    if FieldType = 'FTPCHAR' then FieldTypeCode := ftPChar else
    if FieldType = 'FTPWCHAR' then FieldTypeCode := ftPWChar;
    {$IFDEF DEBUG} DebugOutput('AVZ_DeserializeXML - FormatParser. FieldName="'+FieldName+'", FieldType="'+FieldType+'"');{$ENDIF}
    // ���������� �������� - ������ ���� ��� � �������������� ���
    if (FieldName = '') or (FieldTypeCode = ftNotDefined) then begin
     {$IFDEF DEBUG} DebugOutput('AVZ_DeserializeXML - FormatParser. Error !!');{$ENDIF}
     Result := AVZ_InvalidFormatMask;
     exit;
    end;
    // ���������� ����
    if FieldTypeCode in [ftByte, ftWord, ftDWord, ftInteger] then
     Str2Bin.AddFieldDef(FieldName, FieldTypeCode, StrToInt64Def(FieldDef, 0))
      else Str2Bin.AddFieldDef(FieldName, FieldTypeCode, FieldDef);
   end;
   // ***** �������� XML �� ������ *****
   // ����������� �������
   XMLStream.Seek(0, 2, Tmp);
   // ��������� ������
   SetLength(S, Tmp);
   // ������
   try
    XMLStream.Seek(0, 0, Tmp);
    XMLStream.Read(@S[1], Length(S), @BytesReaded);
    {$IFDEF DEBUG} DebugOutput('AVZ_DeserializeXML - stream readed. BytesReaded = '+IntToStr(BytesReaded));{$ENDIF}
   except
    on e : exception do begin
     Result := AVZ_StreamReadError;
     exit;
    end;
   end;
   // �������
   try
    XMLParser.ParseXML(S);
    {$IFDEF DEBUG} DebugOutput('AVZ_DeserializeXML - XMLParser.ParseXML complete.');{$ENDIF}
   except
    on e : exception do begin
     Result := AVZ_XMLParseError;
     exit;
    end;
   end;
   // ����� ���������� ����
   {$IFDEF DEBUG} DebugOutput('AVZ_DeserializeXML - search tag "'+szTagName+'"');{$ENDIF}
   DataToken := XMLParser.SearchToken(String(szTagName));
   if DataToken = nil then begin
    Result := AVZ_XMLTokenNotFound;
    exit;
   end;
   // ********* ��� ������, ����� ����������� �������������� *********
   {$IFDEF DEBUG} DebugOutput('AVZ_DeserializeXML - calk buf size');{$ENDIF}
   // ������, ������� � ��� ����� � �������
   Tmp := 0;
   Str2Bin.CalkStaticDataSize;
   for i := 0 to DataToken.SubNodes.Count - 1 do
    if DataToken.SubNodes[i].UpperTokenName = 'ITEM' then begin
    {$IFDEF DEBUG} DebugOutput('AVZ_DeserializeXML - calk size, step = '+inttostr(i));{$ENDIF}
     for j := 0 to Length(Str2Bin.FieldDefs)-1 do
      case Str2Bin.FieldDefs[j].FieldType of
       ftByte, ftWord, ftDWORD, ftInteger :  Str2Bin.FieldDefs[j].Value := DataToken.SubNodes[i].ReadInteger(Str2Bin.FieldDefs[j].FieldName, Str2Bin.FieldDefs[j].DefVal);
       ftPChar, ftPWChar                  :  Str2Bin.FieldDefs[j].Value := DataToken.SubNodes[i].ReadString(Str2Bin.FieldDefs[j].FieldName,  Str2Bin.FieldDefs[j].DefVal);
      end;
     inc(Tmp, Str2Bin.CalkDataSize);
    end;
   {$IFDEF DEBUG} DebugOutput('AVZ_DeserializeXML - calk buf complete. Size='+InttoStr(BufSize));{$ENDIF}
   // ����, ����� ����� �������� - ��������� ��������� ������
   BufSize     := Tmp;
   ppAVZBuffer := GetMemory(BufSize);
   ZeroMemory(ppAVZBuffer, BufSize);
   if ppAVZBuffer = nil then begin
    Result := AVZ_Error;
    exit;
   end;
   {$IFDEF DEBUG} DebugOutput('AVZ_DeserializeXML - GetMem complete, size = '+IntToStr(BufSize));{$ENDIF}
   // ���� ���������� ������
   Ptr     := ppAVZBuffer;
   PrevPtr := nil;
   for i := 0 to DataToken.SubNodes.Count - 1 do
    if DataToken.SubNodes[i].UpperTokenName = 'ITEM' then begin
    {$IFDEF DEBUG} DebugOutput('AVZ_DeserializeXML - save data, step = '+inttostr(i));{$ENDIF}
     for j := 0 to Length(Str2Bin.FieldDefs)-1 do
      case Str2Bin.FieldDefs[j].FieldType of
       ftByte, ftWord, ftDWORD, ftInteger :  Str2Bin.FieldDefs[j].Value := DataToken.SubNodes[i].ReadInteger(Str2Bin.FieldDefs[j].FieldName, Str2Bin.FieldDefs[j].DefVal);
       ftPChar, ftPWChar                  :  Str2Bin.FieldDefs[j].Value := DataToken.SubNodes[i].ReadString(Str2Bin.FieldDefs[j].FieldName,  Str2Bin.FieldDefs[j].DefVal);
      end;
      if Str2Bin.AddDataToBuf(Ptr, Tmp, BW) then
       if PrevPtr <> nil then
        DWORD(PrevPtr^) := DWORD(Ptr);
      // ������������� ����������
      PrevPtr := Ptr;
      Ptr     := Pointer(DWORD(Ptr)+BW);
    end;
   {$IFDEF DEBUG} DebugOutput('AVZ_DeserializeXML - create buf');{$ENDIF}
   Result := AVZ_OK;
 finally
  S := '';
  Str2Bin.Free;
  XMLParser.Free;
 end;
end;

function  AVZ_Free(ppAVZAScanKernel : pointer; pPtr : pointer) : DWORD; stdcall;
begin
 {$IFDEF DEBUG} DebugOutput('AVZ_Free');{$ENDIF}
 // �������� ������������ ������ ����
 Result := AVZ_InvalidKernelHandle;
 // �������� ��������� �� ����
 if not(CheckKernelPtr(ppAVZAScanKernel)) then exit;
 // ��������� ����
 SetKernel(ppAVZAScanKernel);
 // ����������� ������
 AVZFreeMemory(pPtr);
 Result := AVZ_OK;
end;

// **************************************************************************************
// ******************* ������� ������� ����� �� ��������� ������ ************************
// **************************************************************************************

// ������������� ������ ������� �����
function  AVZ_SR_Init(ppAVZAScanKernel : pointer; AFileName : PWChar; var pSessionID : dword) : DWORD; stdcall;
var
 TMP : TSRSession;
begin
 Result := AVZ_Error;
 {$IFDEF DEBUG} DebugOutput('AVZ_SR_Init FileName='+AFileName);{$ENDIF}
 {$IFDEF DEBUG} DebugOutput(' SRSystem.API_DB='+IntToStr(Length(SRSystem.API_DB)));{$ENDIF}
 {$IFDEF DEBUG} DebugOutput(' SRSystem.SPR_DB='+IntToStr(Length(SRSystem.SPR_DB)));{$ENDIF}
 // �������� ������ �������
 TMP := TSRSession.Create;
 if TMP = nil then exit;
 // ���������� ��� �����
 if AFileName <> nil then
  TMP.FileName := AFileName
   else TMP.FileName := '';
 // �������� ������ ������� � ������ �������� �������
 SRSessions.Add(TMP);
 // ���������� ����� ������
 pSessionID := dword(TMP);
 Result     := AVZ_OK;
 {$IFDEF DEBUG} DebugOutput('AVZ_SR_Init OK');{$ENDIF}
end;

// �������� ������������ ������ �������
function CheckSRSession(ASessionID : DWORD) : boolean;
begin
 Result := SRSessions.IndexOf(pointer(ASessionID)) >= 0;
end;

// �������� ������ ������� ����� � ����������� ������
function  AVZ_SR_Done(ASessionID : DWORD) : DWORD; stdcall;
begin
 {$IFDEF DEBUG} DebugOutput('AVZ_SR_Done');{$ENDIF}
 Result := AVZ_SR_InvalidSession;
 // �������� ������������ ������ �������
 if not(CheckSRSession(ASessionID)) then exit;
 // �������� ������ �� ������� ������
 SRSessions.Delete(SRSessions.IndexOf(TSRSession(ASessionID)));
 TSRSession(ASessionID).Free;
 Result := AVZ_OK;
 {$IFDEF DEBUG} DebugOutput('AVZ_SR_Done OK');{$ENDIF}
end;

// ���������� �������. ���������� ���������� ����������� ��� �������� ��������� ������� � ��������� ���������� �����
// AEventType - ��� ���� �������; AEventData - ��������� �� ����� � �������, ������������ �������; AEventDataSize - ������ ������
function  AVZ_SR_AddEvent(ASessionID : DWORD; AEventType : DWORD; AEventData : pointer; AEventDataSize : dword) : DWORD; stdcall;
var
 S : string;
begin
 Result := AVZ_SR_InvalidSession;
 {$IFDEF DEBUG} DebugOutput('AVZ_SR_AddEvent');{$ENDIF}
 // �������� ������������ ������ �������
 if not(CheckSRSession(ASessionID)) then exit;
 // ��������, ��������������� �� ������ �������
 if SRSystem = nil then begin
  Result := AVZ_SR_NotInitialized;
  exit;
 end;
 // �������� ������������ �������
 if (AEventData = nil) or (AEventDataSize = 0) then begin
  Result := AVZ_SR_InvalidEvent;
  exit;
 end;
 // ��������, ���� �� ����� ������������� �������
 if (TSRSession(ASessionID).SummRating >= 100) or TSRSession(ASessionID).IsMalware then begin
  Result := AVZ_OK;
  exit;
 end;
 // ����������� ������ � ������
 SetLength(S, AEventDataSize);
 CopyMemory(@S[1], AEventData, AEventDataSize);
 // ��������� ������ �������
 {$IFDEF DEBUG} DebugOutput('AVZ_SR_AddEvent Event='+S);{$ENDIF}
 SRSystem.CheckAPIEvent(TSRSession(ASessionID), S);
 S := '';
 Result := AVZ_OK;
end;

// ���������� �������. ���������� ���������� ����������� ��� �������� ��������� ������� � ��������� ���������� �����
// AEventType - ��� ���� �������; AEventData - ��������� �� ����� � �������, ������������ �������; AEventDataSize - ������ ������
function  AVZ_SR_AddEventEx(ASessionID : DWORD; AEventType : DWORD; AEventData : pointer; AEventDataSize : dword; var Rating, RuleID : dword) : DWORD; stdcall;
var
 S : string;
begin
 Rating := 0;
 RuleID := 0;
 Result := AVZ_SR_InvalidSession;
 {$IFDEF DEBUG} DebugOutput('AVZ_SR_AddEvent');{$ENDIF}
 // �������� ������������ ������ �������
 if not(CheckSRSession(ASessionID)) then exit;
 // ��������, ��������������� �� ������ �������
 if SRSystem = nil then begin
  Result := AVZ_SR_NotInitialized;
  exit;
 end;
 // �������� ������������ �������
 if (AEventData = nil) or (AEventDataSize = 0) then begin
  Result := AVZ_SR_InvalidEvent;
  exit;
 end;
 // ����������� ������ � ������
 SetLength(S, AEventDataSize);
 CopyMemory(@S[1], AEventData, AEventDataSize);
 // ��������� ������ �������
 {$IFDEF DEBUG} DebugOutput('AVZ_SR_AddEvent Event='+S);{$ENDIF}
 Rating := SRSystem.CheckAPIEvent(TSRSession(ASessionID), S);
 RuleID := TSRSession(ASessionID).LastRule;
 S := '';
 Result := AVZ_OK;
end;

// �������� ����� ������ ��� �������. ���������� ���������� �����������
// ABaseAddr - ������� �����, AMemory - ��������� �� ����� ������, ADataSize - ������ ������
function  AVZ_SR_Memory(ASessionID : DWORD; AProcessID : DWORD; ABaseAddr : DWORD; AMemory : pointer; ADataSize : dword) : DWORD; stdcall;
begin
 Result := AVZ_SR_InvalidSession;
 // �������� ������������ ������ �������
 if not(CheckSRSession(ASessionID)) then exit;
 // ��������, ��������������� �� ������ �������
 if SRSystem = nil then begin
  Result := AVZ_SR_NotInitialized;
  exit;
 end;
 Result := AVZ_OK;
end;

// ������ SecurityRating. ARatingType - ��� ���� ��������
function  AVZ_SR_GetSecurityRating(ASessionID : DWORD; ARatingType : DWORD; var Res : dword) : DWORD; stdcall;
begin
 Res := 0;
 Result := AVZ_SR_InvalidSession;
 // �������� ������������ ������ �������
 if not(CheckSRSession(ASessionID)) then exit;
 // ���������� ��������� �������, ��������� ARatingType
 if ARatingType = 0 then
  Res := TSRSession(ASessionID).SummRating
 else
  Res := TSRSession(ASessionID).GetGroupRating(ARatingType);
 Result := AVZ_OK;
end;

{ TAVZAScanKernel }
// ******************************* TAVZAScanKernel ***************************************************
constructor TAVZScanKernel.Create;
begin
 Loaded := false;
 AVZCallBackProc      := nil;
 AVZGetLocalizedStr   := nil;
 AVZFreeLocalizedStr  := nil;
 AVZExternalCheckFile := nil;
 LogText := TStringList.Create;
end;

destructor TAVZScanKernel.Destroy;
begin
 AVZCallBackProc      := nil;
 AVZGetLocalizedStr   := nil;
 AVZFreeLocalizedStr  := nil;
 AVZExternalCheckFile := nil;
 LogText.Free;
 inherited;
end;

  // �����������  ������
function TAVZScanKernel.LocalizeStr(S : string) : string;
var
 Res, poz      : dword;
 ItemId        : string;
 pLocalizedStr : PWideChar;
begin
 Result := S;
 if S = '' then exit;
 // ���������� �������� ��� �������, ��� ��� ��������
 if AVZGetLocalizedStr  = nil then exit;
 if AVZFreeLocalizedStr = nil then exit;
 pLocalizedStr := nil;
 poz := pos('$AVZ', Result);
 while poz > 0 do begin
  // � ������ ��� �������� ���������� ������
  ItemId := copy(Result, poz, 8);
  if Length(ItemId) <> 8 then break;
  // �������
  pLocalizedStr := nil;
  Res  := TGetLocalizedStr(AVZGetLocalizedStr)(pTaskContext,
                           PChar(copy(ItemId, 2, 8)), pLocalizedStr);
  // ��������, ��� ������ AVZ_OK � ��������� ��������� ���������
  if (Res = AVZ_OK) and (pLocalizedStr <> nil) then begin
   {$IFDEF LOC_DEBUG} DebugOutput('TGetLocalizedStr OK: ItemId='+ItemId+', LocalizedStr='+String(pLocalizedStr));{$ENDIF}
   // ������ ���� ���������
   Delete(Result, poz, 8);
   insert(String(pLocalizedStr), Result, poz);
   // ����������� ������
   TFreeLocalizedStr(AVZFreeLocalizedStr)(pTaskContext, pLocalizedStr);
  end else begin
  {$IFDEF LOC_DEBUG} DebugOutput('TGetLocalizedStr ERROR: ItemId='+ItemId+', Res='+IntToStr(Res));{$ENDIF}
   Delete(Result, poz, 8);
   insert('[?? - '+copy(ItemId, 2, 8)+']', Result, poz);
  end;
  poz := pos('$AVZ', Result)
 end;
end;

// ������������ ����� �� ������
function TAVZScanKernel.VirusScan(AFileName: string; ArcInfo : TAVZArcInfoArray): integer;
var
 FileScanner     : TFileScanner;
 VirusDescr      : TVirusDescr;
 DeleteModeCode  : integer;
 S : string;
 i : integer;
 Function LogFileName : string;
 begin
  Result := AFileName;
  if ArcInfo <> nil then
   Result := FormatArcFileName(ArcInfo);
 end;
 Function GetBaseFileName : string;
 begin
  Result := AFileName;
  if ArcInfo <> nil then
   Result := ArcInfo[0].MainArcName;
 end;
begin
 Result := -1;
 FileScanner := TFileScanner.Create;
 try
  // �������� �����
  FileScanner.CheckFile(AFileName);
  // ������ ����������
  Result := MainAntivirus.CheckFile(FileScanner.PEFileInfo, VirusDescr);
  case Result of
   0 : begin
       end;
   1 : begin
        AddToList(VirusName, MainAntivirus.VirusName);
        FullResult := 1;
       end;
   2 : begin
        AddToList(VirusName, 'Suspictios: '+MainAntivirus.VirusName);
        if FullResult = 0 then FullResult := 2;
       end;
  end;
  // ��� ����� ??
  try
   AVZDecompress.ScanFile(AFileName, FileScanner, ArcInfo);
   if AVZDecompress.ArchiveError then
    if FullResult = 0 then FullResult := 3;
  except
   on e : exception do
    if FullResult = 0 then FullResult := 3;
  end;
 finally
  FileScanner.Free;
 end;
end;

procedure TAVZScanKernel.AddToLogEvent(AMsg : string; InfoType : integer);
var
 S : WideString;
 res : DWORD;
begin
 res := 0;
 AMsg := LocalizeStr(AMsg);
 S := AMsg;
 // ���������� � ��������
 if Trim(AMsg) <> '' then
  LogText.AddObject(AMsg, pointer(InfoType));
 if AVZCallBackProc <> nil then
  Res := TAVZCallBackProc(AVZCallBackProc)(pTaskContext, FCurr, FMax, PWideChar(S), length(S)*2, InfoType);
 {$IFDEF DEBUG} DebugOutput('[LOG] '+S);{$ENDIF}
 // ��������� ��������� - ���������� ����� "����"
 if res <> 0 then begin
  AvzUserScript.StopF := true;
  StopF := true;
 end;
 S := '';
end;

procedure TAVZScanKernel.AddToDebugLogEvent(AMsg : string);
begin
 AddToLogEvent(AMsg, logDebug);
end;

procedure TAVZScanKernel.GetLog(ALog : TStrings);
begin
 // ���������� ������� ��������
 ALog.AddStrings(LogText);
end;

procedure TAVZScanKernel.Progress(AMax, ACurr : integer);
begin
 FMax  := AMax;
 FCurr := ACurr;
 AddToLogEvent('', logInfo);
end;

// ���������� "�������� ��������� ����"
function TAVZScanKernel.OnAVZFileExtracted(AVZArcInfo : TAVZArcInfoArray): boolean;
var
 S, ST : string;
 Tmp : TAVZArcInfo;
 i : integer;
begin
 if (AVZArcInfo = nil) or (Length(AVZArcInfo) = 0) then exit;
 Tmp := AVZArcInfo[Length(AVZArcInfo)-1];
 VirusScan(Tmp.TmpFileName, AVZArcInfo);
 // ����������� ������������� ������ � ��������� ����� ��� ������� �������
 if CopyUnpackedFiles then begin
   i := -1;
   repeat
    inc(i);
    ST := AVZArcInfo[Length(AVZArcInfo)-1].ArcType;
    if pos(':', ST) > 0 then        //#DNL
     Delete(ST, pos(':', ST), 100); //#DNL
    S := UnpackedPath+ST+'\'; //#DNL
    S := S + ExtractFileName(AVZArcInfo[Length(AVZArcInfo)-1].MainArcName);
    if i > 0 then
     S := S + IntToStr(i);
    ST := AVZArcInfo[Length(AVZArcInfo)-1].AArcFileName;
    ST := StringReplace(ST, '/','\', [rfReplaceAll]); //#DNL
    if copy(ST, 1, 1) = '\' then delete(ST, 1, 1);
    S := NormalDir(S) + ST;
   until not FileExists(S);
   zForceDirectories(ExtractFilePath(S));
   CopyFile(PChar(Tmp.TmpFileName), PChar(S), false);
 end;
end;

procedure TAVZScanKernel.OnFileSignCheck(AFileName : string; var AStatus : integer);
var
 Res : dword;
begin
 if AStatus = 0 then exit;
 if DoCheckFile(AFileName) = AVZCR_CleanBase then
  AStatus := 0;
end;

function TAVZScanKernel.OnTranslateEvent(AStr : string) : string;
begin
 Result := LocalizeStr(AStr);
end;

function  TAVZScanKernel.DoCheckFile(AFileName : string) : dword;
var
 Res : dword;
begin
 Result := AVZ_Error;
 // ���������� �������� ��� �������, ��� ��� �������
 if AVZExternalCheckFile  = nil then exit;
 // ����� �������
 if TExternalCheckFile(AVZExternalCheckFile)(pTaskContext, PWideChar(AFileName), Res) = AVZ_OK then
  Result := Res;
end;

// ********* �������������� ������� ************
exports
  AVZ_InitializeExA index 1 name 'Z1',
  AVZ_InitializeExW index 2 name 'Z2',
  AVZ_Done index 3 name 'Z3',
  AVZ_CheckFile index 4 name 'Z4',
  AVZ_ReloadBase index 5 name 'Z5',
  AVZ_RunScript  index 6 name 'Z6',
  AVZ_Free  index 7 name 'Z7',
  AVZ_GetDBStatus index 8 name 'Z8',
  AVZ_DeserializeXML index 9 name 'Z9',
  AVZ_SetCallbackProc index 10 name 'Z10',
  AVZ_SetCallbackCtx index 11 name 'Z11',
  // ���� ����������� �������� (�������, ������ ������������ � �.�.)
  AVZ_RunCustomScript  index 12 name 'Z12',
  AVZ_LoadCustomScriptDB index 13 name 'Z13',
  AVZ_GetCustomScriptDBScrCount  index 14 name 'Z14',
  AVZ_FreeCustomScriptDB  index 15 name 'Z15',
  // ���������� ���������, ��������� ������� � �� ���������
  AVZ_SR_Init index 16 name 'Z16',
  AVZ_SR_Done index 17 name 'Z17',
  AVZ_SR_AddEvent index 18 name 'Z18',
  AVZ_SR_Memory index 19 name 'Z19',
  AVZ_SR_GetSecurityRating index 20 name 'Z20',
  AVZ_SR_AddEventEx index 21 name 'Z21';

begin
 // ������ ���������� �� ������� ���� "����" � ���������� �� ����
 KrnlList   := TList.Create;
 DBList     := TList.Create;
 SRSessions := TList.Create;
 // �������� ���������� ������ Delphi � ���, ��� DLL "�������������"
 IsMultiThread := true;
 // ������������� COM
 CoInitialize(nil);
 // ��������� ����������� ����������������
 {$IFDEF DEBUG}
  DebugLogMode := true;
  //ShowMessage('�� �������������� ��� DLL, ��� ������� � ���������� ������ - ��. ���� avzkrnl.dbg');
 {$ENDIF}
end.
