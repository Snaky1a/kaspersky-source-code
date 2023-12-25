unit zUserScripting;
// ************* ������� ������������� �������� **************************
interface
uses Windows, Messages, SysUtils, Classes, Forms, ComCtrls,
     zStringCompressor,
     fs_iinterpreter,
     fs_ipascal,
     fs_iclassesrtti,
     fs_idialogsrtti,
     zLSP, zSharedFunctions,
     uInfectedView,
     uSysCheck,
     Registry, INIFiles,
     zFileSearch,
     IdMessage, IdMessageClient, IdSMTP, IdUDPClient,
     SystemMonitor,
     zAutoruns,
     zAVZDriverN,
     zAVZDriverRK,
     zAVZDriverBC,
     zServices,
     zLogSystem,
     zAVZVersion,
     zTranslate,
     zHTMLTemplate,
     zBackupEngine,
     zXML,
     zIEAPI;
const
 guiGet = 0; // ������� "������� ��������"
 guiSet = 1; // ������� "���������� ��������"
 ShellFoldersKey = 'Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders';

type
 TInitiateSystemShutdownEx = function(lpMachineName : PChar; lpMessage : PChar; dwTimeout : DWORD; bForceAppsClosed : BOOL; bRebootAfterShutdown : BOOL; dwReason : DWORD) : BOOL;

 // ������� ��� ����� � GUI
 TGUILink   = function (Sender : TObject; OpCode : integer; AMessage, AParam : string; var Res : variant) : boolean of object;
 TSetupLink = function (Sender : TObject; ASetting : string) : boolean of object;
 // ����� "������-������"
 TAvzUserScript = class
  private
    FLogEnabled: boolean;
    FGUILink: TGUILink;
    FSetupLink: TSetupLink;
    FOnRunLine: TfsRunLineEvent;
    FBackupEngine: TZBackupEngine;
    procedure SetLogEnabled(const Value: boolean);
    function SendNetMessage(AHost, AFromSt, AToSt, AMessageSt: string) : boolean;
    function SendSyslogMessage(AHost, AMessageSt: string): boolean;
    function SendEmail(AServer, AFrom, ARecipients, ASubject,
      AMessageSt: string; AIdentification: boolean; ALogin,
      APasswd: string;AAttachFile1, AAttachFile2, AAttachFile3 : string): boolean;
    function OnScriptCallMetodStdScr(Instance: TObject; ClassType: TClass;
      const MethodName: String; var Params: Variant): Variant;
    procedure SetGUILink(const Value: TGUILink);
    procedure SetSetupLink(const Value: TSetupLink);
    procedure SetBackupEngine(const Value: TZBackupEngine);
    function OnScriptCallMetodDFM(Instance: TObject; ClassType: TClass;
      const MethodName: String; var Params: Variant): Variant;
    function OnScriptCallMetodSC(Instance: TObject; ClassType: TClass;
      const MethodName: String; var Params: Variant): Variant;
  protected
   fsScriptRuntime : TfsScript;
   fsPascal        : TfsPascal;
   fsClassesRTTI   : TfsClassesRTTI;
   // ������ XML ��� �������� ������, ��������� ������������� �������
   XML             : TXMLParser;
   CurrentXMLNode  : TXMLToken;
   // ����������� "����" ������
   // ������� ���������� ��� ���� "������" ������
   function OnScriptCallMetod(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ������ � Syscheck Menu
   function OnScriptCallMetodSM(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ������ �� ������� ���������
   function OnScriptCallMetodPL(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // �������� ��������� � ����� �� �����
   function OnScriptCallSendMessage(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ������ � ���������, ������������ � ����� ������ ��� �������
   function OnScriptCallMetodBuf(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   //  ����������� ��������
   function OnScriptCallMetodBufSearch(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ������
   function OnScriptCallMetodReg(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ����� � �������
   function OnScriptCallMetodRegSearch(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // �������������� �������
   function OnScriptCallMetodInfo(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // INI �����
   function OnScriptCallMetodINI(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // �������������� �������
   function OnScriptCallMetodParam(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ����� �������
   function OnScriptCallMetodRegBackup(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ������ �� �������� � ����������
   function OnScriptCallMetodService(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ���������� AVZGuard
   function OnScriptCallMetodGuard(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ���������� AVZPM
   function OnScriptCallMetodPM(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ������������
   function OnScriptCallMetodReboot(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ������ � SPI/LSP
   function OnScriptCallMetodSPI(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ������ � Winlogon Notify
   function OnScriptCallMetodWinlogon(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // �������� ������
   function OnScriptCallMetodClean(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // �������������� �������
   function OnScriptCallMetodRepair(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ��������� BootCleaner
   function OnScriptCallMetodBC(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ������ � Hosts ������
   function OnScriptCallMetodHosts(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // ������ � Hosts ������
   function OnScriptCallMetodIE(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   // �������� ����� �� AV �����
   function OnScriptCallMetodScan(Instance: TObject; ClassType: TClass; const MethodName: String;
                             var Params: Variant): Variant;
   function OnScriptCallMetodEV(Instance: TObject; ClassType: TClass; const MethodName: String; var Params: Variant): Variant;
   // ����� ������ � ����� �� �����
   function CallFindClassMethod(Instance: TObject; ClassType: TClass; const MethodName: String; var Params: Variant): Variant;
   // ������� ��� ���
   function OnScriptCallMetodEvGroup(Instance: TObject; ClassType: TClass; const MethodName: String; var Params: Variant): Variant;
   // ���������� ��������-���������
   function OnScriptCallMetodProgress(Instance: TObject; ClassType: TClass; const MethodName: String; var Params: Variant): Variant;
  private
   BC_Files, BC_Keys, BC_Svc, BC_SvcReg, BC_DisableSvc, BC_QrFiles, BC_QrSvc, BC_CpFiles : TStringList; // ������ �������� ��� BootCleaner
   LastCheckTxt : string;
   BC_log : string; // ��� ����� ��������� ��� BootCleaner
   // ����� ��� ������ � ��������
   Reg : TRegistry;
   // ��������� RootKey �� �����
   function SetRootKeyByName(AName : string) : boolean;
   // �������� ����� �������
   function  RegKeyDelete(ARoot, AKey : string) : boolean;
   // �������� ����� �������
   function  RegKeyCreate(ARoot, AKey : string) : boolean;
   // �������� ������������� ����� �������
   function  RegKeyExists(ARoot, AKey : string) : boolean;
   // �������� ������������� ��������� �������
   function  RegKeyParamExists(ARoot, AKey, AParam : string) : boolean;
   // �������� ��������� �������
   function  RegKeyParamDelete(ARoot, AKey, AParam : string) : boolean;
   // ���������� ��������� �������
   function  RegKeyStrParamSet(ARoot, AKey, AParam, AValue : string) : boolean;
   function  RegKeyIntParamSet(ARoot, AKey, AParam : string; AValue : dword) : boolean;
   function  RegKeyBinParamSet(ARoot, AKey, AParam : string; AValue : string) : boolean;
   // ������ ��������� �������
   function  RegKeyStrParamGet(ARoot, AKey, AParam : string) : string;
   function  RegKeyIntParamGet(ARoot, AKey, AParam : string) : integer;
   // ���������� ������� ��������� � ������ �������
   function RegKeyEnumVal(ARoot, AKey : string; AList : TStrings) : boolean;
   function RegKeyEnumKey(ARoot, AKey : string; AList : TStrings) : boolean;
   function AddLineToTxtFile(AFileName, S : string) : boolean;
  public
   ReadOnlyMode  : boolean; // ����� "������ ������" (������� � �� �����������)
   StopF         : boolean; // ���� "��������� ��������� ������ �������"
   Running       : boolean; // ������� ����, ��� ������ ��������
   QurantinePath : string;  // ���� ��� ��������� ������
   ScanBuf       : packed array of byte; // ����� ��� ������������ ������ � �������
   LastError     : string;  // ��������� ������ � �� ������� � �������
   LastErrorPos  : string;
   ProcessList     : TStrings; // ������ ���������
   DeletedFilesList, QrFilesList : TStringList; // ������ ��������� � ��������������� ������
   OutRes : string; // ����������, ����������� ��������
   constructor Create;
   destructor Destroy; override;
   // ��������� ���������������� - ��� �������� � GUI �������� ����� ZLogSystem
   procedure AddToLog(s : string);
   // ������� ����� - ���������� �������
   function  ExecuteScript(AFileName, AScript : string; AScriptName : string=''; ACheckNoRun : boolean = false) : boolean;
   // ���������� CLSID
   function PrepareCLSID(s :string) : string;
   // �������� ����� ���������
   function DeleteQurantineFolder : boolean;
   // ������ �������� �� �� ��������
   function ReplaceMacrosStr(s : string) : string;
   // ���������� ������ �����, ���������� �� ������������
   function CreateScanPathStr : string;
   // ��������� �������
   function ExecuteProcess(AFileName, AParams: string; Mode : integer; WaitTime : integer; Terminate : boolean) : boolean;
   // ����� ����� � GUI
   function CallGUILink(OpCode : integer; AMessage, AParam : string; var Res : variant) : boolean; overload;
   function CallGUILink(OpCode : integer; AMessage, AParam : string) : boolean; overload;
   // ����� BackUp ������������
   function DoAddBackupDeleteKey(ARoot, AKey : string) : boolean;
   function DoAddBackupDeleteParam(ARoot, AKey, AParamName : string) : boolean;
   function DoAddBackupChangeParam(ARoot, AKey, AParamName : string) : boolean;
   // ���������� ���������������� - ��������� ��������� ��� � ������ ��������� ������������
   property LogEnabled : boolean read FLogEnabled write SetLogEnabled;
   // �������������� CLSID
   procedure FormatCLSID(var ACLSID: string);
   // �������� CLSID
   procedure DelCLSID(ACLSID: string);
   procedure DelInterface(ACLSID: string);
   // �������� BHO
   procedure DelBHO(ACLSID: string);
   // �������� ��������� Active Setup
   procedure DelActiveSetup(ACLSID: string);
   // �������� Shell Extention
   procedure DelShellExt(ACLSID: string);
   // �������� ������ Shared Task Scheduller
   procedure DelSharedTaskSch(ACLSID: string);
   // �������� ����������� Winlogon (�� ����� ����� � �� ����� �����)
   procedure DelWinlogonNotifyByFileName(AFileName: string);
   procedure DelWinlogonNotifyByKeyName(AKeyName: string);
   // �������� �������� Autorun
   function  DelAutorunByFileName(AFileName: string) : boolean;
  published
   // ���������� ��� ����� � GUI
   property GUILink : TGUILink read FGUILink write SetGUILink;
   // ���������� ��� ����� � ����������� ��������� ����� �����
   property SetupLink : TSetupLink read FSetupLink write SetSetupLink;
   // ������� "����������� ������ �������"
   property OnRunLine : TfsRunLineEvent read FOnRunLine write FOnRunLine;
   // �����, ���������� �� ������� ������
   property BackupEngine : TZBackupEngine read FBackupEngine write SetBackupEngine;
 end;

implementation
uses zutil, uAutoQurantine, uAutoUpdate, orautil,
     zAntivirus, zAVKernel, zScriptingKernel, zAVZKernel, Variants;
{ TAvzUserScript }

// �������� ��������� �� NET SEND
function TAvzUserScript.SendNetMessage(AHost, AFromSt, AToSt, AMessageSt: string) : boolean;
var
 hSlot : THandle;
 s  : string;
 cb : DWORD;
begin
 Result := false;
 try
  hSlot := CreateFile(PChar('\\'+AHost+'\mailslot\messngr'),
     GENERIC_WRITE, FILE_SHARE_READ, 0,
     OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  if hSlot <> INVALID_HANDLE_VALUE then begin
    AMessageSt := DecodeToDos(AMessageSt);
    s := AFromSt + #0 + AToSt + #0 + AMessageSt + #0;
    cb := length(S);
    Result := WriteFile(hSlot, s[1], cb, cb, 0);
    CloseHandle(hSlot);
  end;
 except
 end;
end;

// ������ � SYSLOG
function TAvzUserScript.SendSyslogMessage(AHost, AMessageSt: string) : boolean;
var
 IdUDPSyslogClient : TIdUDPClient;
begin
 try
  IdUDPSyslogClient := TIdUDPClient.Create(nil);
  try
   IdUDPSyslogClient.Host   := AHost;
   IdUDPSyslogClient.Port   := 514;
   IdUDPSyslogClient.Active := true;
   IdUDPSyslogClient.Send(AMessageSt);
   IdUDPSyslogClient.Active := false;
  finally
   IdUDPSyslogClient.Free;
  end;
 except
 end;
end;

// �������� ������
function TAvzUserScript.SendEmail(AServer, AFrom, ARecipients, ASubject, AMessageSt: string; AIdentification : boolean; ALogin, APasswd : string; AAttachFile1, AAttachFile2, AAttachFile3 : string) : boolean;
var
 IdSMTP : TIdSMTP;
 Msg    : TidMessage;
begin
 IdSMTP := TIdSMTP.Create(nil);
 try
  // ����� ��������� �������
  IdSMTP.Host := AServer;
  IdSMTP.MailAgent := 'AVZ';
  //��� ����������� �� SMTP �������
  if AIdentification then begin
   IdSMTP.Username   := ALogin;
   IdSMTP.Password   := APasswd;
   IdSMTP.AuthenticationType := atLogin;
  end else
   IdSMTP.AuthenticationType := atNone;
  Msg := TIdMessage.Create(nil);
  Msg.Subject := '';
  Msg.ContentType := 'text/plain; charset=windows-1251';
  Msg.From.Address  := AFrom;
  Msg.Recipients.EMailAddresses := ARecipients;
  Msg.Body.Text := AMessageSt;
  Msg.ExtraHeaders.Add('Subject: '+ASubject);
  // ��������
  if (AAttachFile1 <> '') and FileExists(AAttachFile1) then
   TIdAttachment.Create(Msg.MessageParts, AAttachFile1);
  if (AAttachFile2 <> '') and FileExists(AAttachFile2) then
   TIdAttachment.Create(Msg.MessageParts, AAttachFile2);
  if (AAttachFile3 <> '') and FileExists(AAttachFile3) then
   TIdAttachment.Create(Msg.MessageParts, AAttachFile3);
  try
   IdSMTP.Connect;
   if AIdentification then
    IdSMTP.Authenticate;
   IdSMTP.Send(Msg);
   IdSMTP.Disconnect;
  finally
   try IdSMTP.Disconnect; except end;
  end;
 finally
  IdSMTP.Free;
 end;
end;

// ����������������
procedure TAvzUserScript.AddToLog(s: string);
begin
 if FLogEnabled then
  ZLogSystem.AddToLog(s, logInfo);
end;

// ����������� ������
constructor TAvzUserScript.Create;
begin
 Running := false;
 LastCheckTxt := '';
 // �����������
 FSetupLink := nil;
 FOnRunLine := nil;
 // ����� ������������� �������
 ScanBuf := nil;
 FBackupEngine := nil;
 // ������ XML
 XML := nil;
 CurrentXMLNode := nil;
 // ������������� �������
 fsScriptRuntime := TfsScript.Create(nil);
 fsScriptRuntime.Parent := fsGlobalUnit;
 fsPascal        := TfsPascal.Create(nil);
 fsClassesRTTI   := TfsClassesRTTI.Create(nil);
 ProcessList     := TStringList.Create;
 DeletedFilesList := TStringList.Create;
 QrFilesList      := TStringList.Create;
 BC_Files  := TStringList.Create;
 BC_Files.Sorted := true;
 BC_QrFiles := TStringList.Create;
 BC_QrSvc   := TStringList.Create;
 BC_Keys   := TStringList.Create;
 BC_Svc    := TStringList.Create;
 BC_SvcReg := TStringList.Create;
 BC_DisableSvc := TStringList.Create;
 BC_CpFiles    := TStringList.Create;
 Reg := TRegistry.Create;
 BC_log    := '';
 ReadOnlyMode := false;
 FLogEnabled := true;
end;

// ���������� ������ �����, ���������� �� ������������
function TAvzUserScript.CreateScanPathStr: string;
var
 X : Variant;
begin
 Result := '';
 if CallGUILink(guiGet, 'ScanPath', '', X) then
  Result := X;
end;

destructor TAvzUserScript.Destroy;
begin
 Running := false;
 fsScriptRuntime.Free;
 fsPascal.Free;
 fsClassesRTTI.Free;
 ProcessList.Free;
 DeletedFilesList.Free;
 QrFilesList.Free;
 BC_Files.Free;
 BC_QrFiles.Free;
 BC_QrSvc.Free;
 BC_Keys.Free;
 BC_Svc.Free;
 BC_SvcReg.Free;
 BC_DisableSvc.Free;
 BC_CpFiles.Free;
 Reg.Free;
 // ��������� ������ XML
 CurrentXMLNode := nil;
 if XML <> nil then
  XML.Free;
 XML := nil; 
 inherited;
end;

function TAvzUserScript.ExecuteScript(AFileName, AScript,
  AScriptName: string; ACheckNoRun : boolean): boolean;
begin
 LastCheckTxt := '';
 // ������� �������
 DeletedFilesList.Clear; QrFilesList.Clear;
 BC_Files.Clear; BC_Keys.Clear; BC_Svc.Clear; BC_QrFiles.Clear; BC_QrSvc.Clear;
 ProcessList.Clear;
 LastError := '';
 LastErrorPos := '';
 Result := false;
 StopF  := false;
 Running := true;
 try
   QurantinePath := NormalDir(QurantinePath);
   // ���������� ������� �������
   if Trim(AScript) = '' then exit;
   // ���������� ������ �������
   fsScriptRuntime.Clear;
   fsScriptRuntime.Lines.Text := AScript;
   // ��������� � ������ �������
   fsScriptRuntime.AddConst('AScriptName', 'string', AScriptName);
   // ���������� ���� DWord
   fsScriptRuntime.AddType('DWord', fvtVariant);
   // ��������� � ������ ����� (��� �������� ������� � ������� ������)
   fsScriptRuntime.AddConst('AFileName', 'string', AFileName);
   // �������� ���������� - ���������, ������� ������ ����� ������� ����
   fsScriptRuntime.AddVariable('OutRes', 'string', '');
   // ����� ��� ������ ������ � �����
   with fsScriptRuntime.AddClass(TFileSearch, 'TComponent') do begin
    AddMethod('function FindFirst(AFileMask : string) : boolean', CallFindClassMethod);
    AddMethod('function FindNext : boolean', CallFindClassMethod);
    AddMethod('function FindClose : boolean', CallFindClassMethod);
   end;
{   with fsScriptRuntime.AddClass(TStringList, 'TPersistent') do begin
    AddProperty('CommaText', 'string', StringsGetProp, StringsSetProp);
    AddProperty('Count', 'Integer', StringsGetProp, nil);
    AddIndexProperty('Objects', 'Integer', 'TObject', StringsCallMethod);
    AddDefaultProperty('Strings', 'Integer', 'string', StringsCallMethod);
   end;}
   // ****** ���������� �������� � �������. ����������� � �������� ������� - ��� ��������������� �������� � ���� ������ *****

   {SCRIPT-DECL-START}
   // ������� ������ ���������� [1]
   fsScriptRuntime.AddMethod('function StringReplace(S, OldPattern, NewPattern: string) : string', OnScriptCallMetod); {���������� ������ S, � ������� ��� ��������� ������ OldPattern �������� �� NewPattern (��� ����� ��������)}
   fsScriptRuntime.AddMethod('function StrToIntDef(S : string; ADefVal : integer) : integer', OnScriptCallMetod); {���������� ����� �� ��� ���������� �������������, � ������ ������ ������������ AdefVal|*|4.28}
   // ������� ��� ���������
   fsScriptRuntime.AddMethod('function AddEvAlarmByCLSID(AName, AVirus, AFileList : string) : boolean', OnScriptCallMetodEvGroup);
   fsScriptRuntime.AddMethod('function AddEvAlarmByName(AName, AVirus, AFileList : string) : boolean', OnScriptCallMetodEvGroup);
   // ���������������� [2]
   fsScriptRuntime.AddMethod('procedure AddToLog(S : string)', OnScriptCallMetod); {���������� ������ � ��������|*}
   fsScriptRuntime.AddMethod('procedure SaveLog(AFileName : string)', OnScriptCallMetod); {���������� ��������� � ���� � ��������� ������|���������� ���������}
   fsScriptRuntime.AddMethod('procedure SaveCSVLog(AFileName : string)', OnScriptCallMetod); {���������� ��������� ������������ ������� � ������� CSV|���������� ��������� � CSV}
   fsScriptRuntime.AddMethod('function AddLineToTxtFile(AFileName, S : string) : boolean', OnScriptCallMetod); {���������� ������ S � ���������� �����. � ������ ����������� ���� ���������|���������� ������ � ���������� �����}

   // ���������� AVZ [3]
   fsScriptRuntime.AddMethod('procedure SetupAVZ(S : string)', OnScriptCallMetod); {��������� AVZ, S - �������� ���� ���=��������|��������� AVZ}
   fsScriptRuntime.AddMethod('procedure RunScan', OnScriptCallMetod); {������ ������������, ������ ������� ������ "����" �� ������� ����|������ ������������}
   fsScriptRuntime.AddMethod('procedure ExitAVZ', OnScriptCallMetod); {���������� ������ AVZ|*}
   fsScriptRuntime.AddMethod('procedure ActivateWatchDog(Interval : integer)', OnScriptCallMetod); {��������� ����������� �������|*}
   fsScriptRuntime.AddMethod('procedure ExecuteSysCheck(AFileName : string)', OnScriptCallMetod); {���������� ������������ ������� � ����������� ��������� ��� ������ AFileName|������������ �������}
   fsScriptRuntime.AddMethod('procedure ExecuteSysCheckEx(AFileName : string; ACheckMode : dword; AScanAllSvc : boolean; ARepParams : dword)', OnScriptCallMetod); {���������� ������������ ������� � ����������� ��������� ��� ������ AFileName - ����������� �����|������������ �������-����������� �����|4.28}
   fsScriptRuntime.AddMethod('procedure ExecuteSysChkIPU', OnScriptCallMetodEV); {���������� ������������� �������� ������� - �������� ������������� ����������� (���)|����� ������������� �����������|4.26}
   fsScriptRuntime.AddMethod('procedure ExecuteSysChkEV',  OnScriptCallMetodEV); {���������� ������������� �������� �������|*|4.26}
   fsScriptRuntime.AddMethod('function  ExecuteWizard(ADBName : string; ACheckLevel, AFixLevel : integer; AUseBackup : boolean; ACheckID : integer = -1) : integer',  OnScriptCallMetodEV); {���������� ������� ������ � ���������� �������|*|4.28}
   fsScriptRuntime.AddMethod('procedure SearchRootkit(UserModeLock, KernelModeLock : boolean)', OnScriptCallMetod); {����� ��������, ��������� ��������� �������������� ����������|����������}
   fsScriptRuntime.AddMethod('procedure SearchKeylogger', OnScriptCallMetodEV); {����� �����������|*|4.26}
   fsScriptRuntime.AddMethod('procedure Sleep(AInterval : integer)', OnScriptCallMetod); {����� � ������ �� AInterval ����������� (1000�� = 1 ���)|����� � ������}

   // ���������� � AVZ [4]
   fsScriptRuntime.AddMethod('function  GetAVZDirectory : string', OnScriptCallMetod); {������ ��������, �� �������� ������� AVZ|*}
   fsScriptRuntime.AddMethod('function  GetAVZVersion : double', OnScriptCallMetod); {������ ������ AVZ � ���� ����� � ��������� �������|������ ������ AVZ}
   fsScriptRuntime.AddMethod('function  GetAVZVersionTxt : string', OnScriptCallMetod); {������ ������ AVZ � ��������� ����|������ ������ AVZ}
   fsScriptRuntime.AddMethod('function  GetAVZSvcName(ID : integer) : string', OnScriptCallMetod); {������ ����� ������ AVZ|*|4.26}

   // �������������� ������� [5]
   fsScriptRuntime.AddMethod('function  GetSystemBootMode:integer', OnScriptCallMetodInfo); {������ ���� ������ �������� ������� (������� ����� ��� ����������)}
   fsScriptRuntime.AddMethod('function  GetTempDirectoryPath : String', OnScriptCallMetodInfo); {������ ���� � ��������� �����}
   fsScriptRuntime.AddMethod('function  GetScanPath:string', OnScriptCallMetodInfo); {������ ������ ���������, ���������� �� ������������. ����������� - ";"}
   fsScriptRuntime.AddMethod('function  GetSuspCount:integer', OnScriptCallMetodInfo); {������ ���������� �������������� ������}
   fsScriptRuntime.AddMethod('function  GetDetectedCount:integer', OnScriptCallMetodInfo); {������ ���������� ��������������� malware}
   fsScriptRuntime.AddMethod('function  GetEnvironmentVariable(AName : string):string', OnScriptCallMetodInfo); {������ ���������� ��������� � ������ AName|������ ���������� ���������|4.26}

   // ��������� [6]
   fsScriptRuntime.AddMethod('procedure LockInterface', OnScriptCallMetod); {���������� ����������|*}
   fsScriptRuntime.AddMethod('procedure UnLockInterface', OnScriptCallMetod); {������������� ����������|*}
   fsScriptRuntime.AddMethod('procedure SetStatusBarText(AMsg : string)', OnScriptCallMetod); {����������� ������ S � ������ ������� �������� ����}

   // ���� ��������� ������� � ������������ ������� [7]
   fsScriptRuntime.AddMethod('procedure AddSyscheckMenu(ANaim, ACmd : string; AddMode : integer)', OnScriptCallMetodSM); {���������� � ���� ���������� ������� � ��������� ������������ ������� �������}
   fsScriptRuntime.AddMethod('procedure ClearSyscheckMenu', OnScriptCallMetodSM); {������� ���� ���������� ������� � ��������� ������������ �������}

   // ���������� ��� [8]
   fsScriptRuntime.AddMethod('function  ExecuteAVUpdate : boolean', OnScriptCallMetod); {���������� ���|*}
   fsScriptRuntime.AddMethod('function  ExecuteAVUpdateEx(AServerURL : string; AConnectMode : byte; ProxyServer, ProxyUser, ProxyPass : string) : boolean', OnScriptCallMetod); {���������� ��� � ���������� ���� ����������|*}

   // ���������� � ���������� [9]
   fsScriptRuntime.AddMethod('function  GetComputerName : string', OnScriptCallMetod); {������ ����� ����������|*}
   fsScriptRuntime.AddMethod('function  GetComputerComments : string', OnScriptCallMetod); {������ ��������� �������� ����������|*}
   fsScriptRuntime.AddMethod('function  IsNT : boolean', OnScriptCallMetod); {�������� ���� ��������� - ���������� true ��� NT � false ��� Win9x|�������� ���� ���������|4.26}

   // �������� ����� [10]
   fsScriptRuntime.AddMethod('function  CheckFile(AFileName : string) : integer', OnScriptCallMetodScan); {�������� ����� �� ���� malware � ������ ������|*}
   fsScriptRuntime.AddMethod('function  GetLastCheckTxt : string', OnScriptCallMetodScan); {������ �������� ����� CheckFile|*}

   // ����� ����������� �������� [11]
   fsScriptRuntime.AddMethod('function ExecuteRepair(ID : integer) : boolean', OnScriptCallMetodRepair); {����� ������� �������������� ������� ����� ID|����� ������� �������������� ������� }
   fsScriptRuntime.AddMethod('function ExecuteStdScr(ID : integer) : boolean', OnScriptCallMetodStdScr); {����� ������������ ������� ����� ID|����� ������������ ������� }

   // ���������� ������ � ������������ [12]
   fsScriptRuntime.AddMethod('procedure ShutdownWindows(AForce : boolean)', OnScriptCallMetodReboot); {���������� ������|*}
   fsScriptRuntime.AddMethod('procedure RebootWindows(AForce : boolean)',   OnScriptCallMetodReboot); {������������|*}

   // SPI/LSP [13]
   fsScriptRuntime.AddMethod('function  CheckSPI : integer', OnScriptCallMetodSPI); {����� ������ �� ���������� SPI|*|4.26}
   fsScriptRuntime.AddMethod('procedure DelSPIByFileName(ALibrary : string; NameCompare : boolean)', OnScriptCallMetodSPI); {�������� SPI ���������� �� ����� �����|*}
   fsScriptRuntime.AddMethod('procedure AutoFixSPI', OnScriptCallMetodSPI); {�������������� ����������� ������ SPI|*}

   // Winlogon � ���������� [14]
   fsScriptRuntime.AddMethod('procedure DelWinlogonNotifyByFileName(AFileName : string)', OnScriptCallMetodWinlogon); {�������� �������� Winlogon �� ����� �����|�������� �������� Winlogon}
   fsScriptRuntime.AddMethod('procedure DelWinlogonNotifyByKeyName(AKeyName : string)', OnScriptCallMetodWinlogon); {�������� �������� Winlogon �� ����� ����� �������|�������� �������� Winlogon}
   fsScriptRuntime.AddMethod('function  DelAutorunByFileName(AFileName : string) : boolean', OnScriptCallMetodWinlogon); {�������� �������� ����������� �� ����� �����|�������� �������� �����������|4.26}

   // ����� � ����� [15]
   fsScriptRuntime.AddMethod('procedure CreateDirectory(ADirName : string)', OnScriptCallMetod); {�������� ��������|*}
   fsScriptRuntime.AddMethod('procedure DeleteDirectory(ADirName : string)', OnScriptCallMetod); {�������� ��������|*}
   fsScriptRuntime.AddMethod('function DirectoryExists(ADirName : string) : boolean', OnScriptCallMetod); {��������, ���������� �� ��������� �������|*}
   fsScriptRuntime.AddMethod('function FileExists(AFileName : string) : boolean', OnScriptCallMetod); {��������, ���������� �� ��������� ����|*}
   fsScriptRuntime.AddMethod('function GetFileSize(AFileName : string) : integer', OnScriptCallMetod); {������ ������� ����� � ������. ���������� -1, ���� ���� �� ������|������ ������� �����}
   fsScriptRuntime.AddMethod('function DeleteFile(AFileName : string) : boolean', OnScriptCallMetod); {�������� �����. ���� �������� �� �������, �� ����������� ����� �� ���������� ��������|�������� �����}
   fsScriptRuntime.AddMethod('function CalkFileMD5(AFileName : string) : string', OnScriptCallMetod); {��������� MD5 ����� ���������� �����|*|4.28}
   fsScriptRuntime.AddMethod('function DeleteFileMask(ADir, AMask : string; ARecurse : boolean) : boolean', OnScriptCallMetodDFM); {����� � �������� ������ � �������� �������� �� �����. ���� �������� �� �������, �� ����������� ����������� ������ �� ���������� ��������|�������� ����� �� �����|4.28}
   fsScriptRuntime.AddMethod('function CopyFile(AFromName, AToName : string) : boolean', OnScriptCallMetod); {����������� �����|*}
   fsScriptRuntime.AddMethod('function RenameFile(AFromName, AToName : string) : boolean', OnScriptCallMetod);{�������������� ��� ������� �����|*}
   fsScriptRuntime.AddMethod('function NormalDir(ADirName : string) : string', OnScriptCallMetod); {������������ ����� ��������|*}
   fsScriptRuntime.AddMethod('function NormalFileName(AName : string) : string', OnScriptCallMetod); {������������ ����� �����|*}
   fsScriptRuntime.AddMethod('function GetCurrentDirectory : string', OnScriptCallMetod); {������ �������� ��������|*}
   fsScriptRuntime.AddMethod('function GetSystemDisk : string', OnScriptCallMetod); {������ ����� ���������� �����|*}
   fsScriptRuntime.AddMethod('function ExtractFileName(AName : string) : string', OnScriptCallMetod); {���������� �� ������ ����� �����|*}
   fsScriptRuntime.AddMethod('function ExtractFilePath(AName : string) : string', OnScriptCallMetod); {���������� �� ������ ���� � �����|*}
   fsScriptRuntime.AddMethod('function ExtractFileExt(AName : string) : string', OnScriptCallMetod); {���������� �� ������ ���������� �����|*}
   fsScriptRuntime.AddMethod('function GetDriveType(ADirName : string) : integer', OnScriptCallMetod); {����������� ���� ����� (HDD, �������, CDROM)|����������� ���� �����|4.26}

   // ������ [16]
   fsScriptRuntime.AddMethod('procedure RegKeyDel(ARoot, AName : string)', OnScriptCallMetodReg); {�������� ����� �������|*}
   fsScriptRuntime.AddMethod('procedure RegKeyCreate(ARoot, AName : string)', OnScriptCallMetodReg); {�������� ����� �������|*}
   fsScriptRuntime.AddMethod('procedure RegKeyParamDel(ARoot, AName, AParam : string)', OnScriptCallMetodReg); {�������� ��������� �� ����� �������|*}
   fsScriptRuntime.AddMethod('procedure RegKeyStrParamWrite(ARoot, AName, AParam, AValue : string)', OnScriptCallMetodReg); {�������� ��� ����������� ��������� ���� REG_SZ|*}
   fsScriptRuntime.AddMethod('procedure RegKeyIntParamWrite(ARoot, AName, AParam : string; AValue : dword)', OnScriptCallMetodReg); {�������� ��� ����������� ��������� ���� REG_DWORD|*}
   fsScriptRuntime.AddMethod('procedure RegKeyBinParamWrite(ARoot, AName, AParam : string; AValue : string)', OnScriptCallMetodReg); {�������� ��� ����������� ��������� ���� REG_BINARY|*}
   fsScriptRuntime.AddMethod('function RegKeyStrParamRead(ARoot, AName, AParam : string) : string', OnScriptCallMetodReg); {������ ��������� ���� REG_SZ|*}
   fsScriptRuntime.AddMethod('function RegKeyIntParamRead(ARoot, AName, AParam : string) : dword', OnScriptCallMetodReg); {������ ��������� ���� REG_DWORD|*}
   fsScriptRuntime.AddMethod('function RegKeyExists(ARoot, AName : string) : boolean', OnScriptCallMetodReg); {��������, ���������� �� ��������� ����|*}
   fsScriptRuntime.AddMethod('function RegKeyParamExists(ARoot, AName, AParam : string) : boolean', OnScriptCallMetodReg);{��������, ���������� �� ��������� ��������|*}
   fsScriptRuntime.AddMethod('function RegSearch(ARoot, AName, AValue : string) : boolean', OnScriptCallMetodRegSearch); {����� � �������. ���������� �������� � ��������|����� � �������}
   fsScriptRuntime.AddMethod('function ExpRegKey(ARoot, AName, AFileName : string) : boolean', OnScriptCallMetodReg); {������� ����� ������� � ����|*|4.26}
   fsScriptRuntime.AddMethod('function ExpRegKeyEx(ARoot, AName : string; Lines : TStrings) : boolean', OnScriptCallMetodReg); {������� ����� ������� � ������ �����|*|4.26}
   fsScriptRuntime.AddMethod('function RegKeyEnumVal(ARoot, AName : string; AList : TStrings) : boolean', OnScriptCallMetodReg); {���������� ������ ���������� ��������� �����|*|4.28}
   fsScriptRuntime.AddMethod('function RegKeyEnumKey(ARoot, AName : string; AList : TStrings) : boolean', OnScriptCallMetodReg); {���������� ������ ��������� ������|*|4.28}

   // ������� ������ � INI ������� [17]
   fsScriptRuntime.AddMethod('function  INIStrParamRead(AFileName, ASectionName, AParamName, ADefVal : string) : string', OnScriptCallMetodINI); {������ ��������� INI �����|*|4.26}
   fsScriptRuntime.AddMethod('function  INIStrParamWrite(AFileName, ASectionName, AParamName, AParamVal : string) : boolean', OnScriptCallMetodINI); {������ ��������� INI �����|*|4.26}
   fsScriptRuntime.AddMethod('function  INISectionExists(AFileName, ASectionName : string) : boolean', OnScriptCallMetodINI); {��������, ���������� �� ��������� ������ � INI �����|*|4.26}
   fsScriptRuntime.AddMethod('function  INIEraseSection(AFileName, ASectionName : string) : boolean', OnScriptCallMetodINI); {�������� ������ INI �����|*|4.26}
   fsScriptRuntime.AddMethod('function  INIEraseParam(AFileName, ASectionName, AParamName : string) : boolean', OnScriptCallMetodINI); {�������� ��������� INI �����|*|4.26}

   // ������ � CLSID [18]
   fsScriptRuntime.AddMethod('function  CLSIDExists(CLSID : string) : boolean', OnScriptCallMetod); {��������, ���������� �� ��������� CLSID}
   fsScriptRuntime.AddMethod('function  CLSIDFileExists(CLSID : string) : boolean', OnScriptCallMetod); {��������, ���������� �� ��������� CLSID � ��������� � ��� ����}
   fsScriptRuntime.AddMethod('function  CLSIDFileName(CLSID : string) : string', OnScriptCallMetod); {������ ����� �����, ���������� � CLSID}
   fsScriptRuntime.AddMethod('procedure DelCLSID(CLSID : string)', OnScriptCallMetod); {�������� CLSID � ���� ������ �� ���� (BHO, Active Setup ...)}

   // ������ � BHO [19]
   fsScriptRuntime.AddMethod('function  BHOExists(BHO : string) : boolean', OnScriptCallMetod); {��������, ���������� �� ��������� BHO}
   fsScriptRuntime.AddMethod('procedure DelBHO(BHO : string)', OnScriptCallMetod); {�������� BHO|*}

   // ������ � ���������� � �������� [20]
   fsScriptRuntime.AddMethod('function  ServiceExists(AName : string) : boolean', OnScriptCallMetodService); {��������, ���������� �� �������� ������/�������}
   fsScriptRuntime.AddMethod('function  ServiceAndFileExists(AName : string) : boolean', OnScriptCallMetodService); {��������, ���������� �� �������� ������/������� � ��������� � ��� ����}
   fsScriptRuntime.AddMethod('function  StartService(AName : string) : boolean', OnScriptCallMetodService); {������ ������/�������� ��������|*}
   fsScriptRuntime.AddMethod('function  StopService(AName : string) : boolean', OnScriptCallMetodService);{��������� ������/�������� ��������|*}
   fsScriptRuntime.AddMethod('function  DeleteService(AName : string; ADelFile : boolean = false) : boolean', OnScriptCallMetodService); {�������� ������/��������. ���� ADelFile=true, �� ��������� � ��������������� ����|�������� ������}
   fsScriptRuntime.AddMethod('function  GetServiceFile(AName : string) : string', OnScriptCallMetodService); {������ ����� ����� ��������� ������/��������}
   fsScriptRuntime.AddMethod('function GetServiceStart(AServiceName: string): integer', OnScriptCallMetodService); {������ ���� ������ ������� ������|*|4.26}
   fsScriptRuntime.AddMethod('function SetServiceStart(AServiceName: string; AStart: integer): boolean', OnScriptCallMetodService); {��������� ���� ������ ������� ������|*|4.26}
   fsScriptRuntime.AddMethod('function GetServiceName(AServiceName: string): string', OnScriptCallMetodService);  {������ ����� ������|*|4.26}

   // �������� [21]
   fsScriptRuntime.AddMethod('function  ClearQuarantine:boolean', OnScriptCallMetod); {������� ���������|*}
   fsScriptRuntime.AddMethod('procedure ExecuteAutoQuarantine', OnScriptCallMetod);{���������� �������������|*}
   fsScriptRuntime.AddMethod('function  CreateQurantineArchive(AFileName : string):boolean', OnScriptCallMetod); {�������� ������ � ���������� ��������� �� ������� ����|*}
   fsScriptRuntime.AddMethod('function  CreateInfectedArchive(AFileName : string):boolean', OnScriptCallMetod);  {�������� ������ � ���������� Infected �� ������� ����|*}
   fsScriptRuntime.AddMethod('function  QuarantineFile(AFileName, AMsg : string):boolean', OnScriptCallMetod); {���������� ���������� ����� � ��������|*}

   // �������� [22]
   fsScriptRuntime.AddMethod('function  RefreshProcessList:boolean', OnScriptCallMetodPL); {���������� ������ ���������|*}
   fsScriptRuntime.AddMethod('function  GetProcessCount:integer', OnScriptCallMetodPL); {������ ���������� ��������� � ������|*}
   fsScriptRuntime.AddMethod('function  GetProcessName(Indx : integer):string', OnScriptCallMetodPL); {������ ����� ������������ ����� �������� ����� Indx}
   fsScriptRuntime.AddMethod('function  GetProcessPID(Indx : integer):dword', OnScriptCallMetodPL); {������ PID �������� ����� Indx|*}
   fsScriptRuntime.AddMethod('function  TerminateProcess(PID : dword):boolean', OnScriptCallMetodPL); {���������� �������� �� ��� PID|*}
   fsScriptRuntime.AddMethod('function  TerminateProcessByName(AName : string):boolean', OnScriptCallMetodPL); {���������� �������� �� ����� ������������ �����|���������� �������� �� ����� �����}
   fsScriptRuntime.AddMethod('function  KillProcess(PID : dword):boolean', OnScriptCallMetodPL); {���������� �������� �� ��� PID|*}
   fsScriptRuntime.AddMethod('function  ExecuteFile(FileName, Params: string; Mode : integer; WaitTime : integer; ATerminate : boolean) : boolean', OnScriptCallMetod); {������ ��������}

   // ������ � ������ Hosts [23]
   fsScriptRuntime.AddMethod('function  GetHostsFileName : String', OnScriptCallMetodHosts); {������ ������� ����� ����� Hosts|*}
   fsScriptRuntime.AddMethod('function  ClearHostsFile : boolean', OnScriptCallMetodHosts); {������� ����� Hosts - �������� ���� ����� ����� ������������ � ������������ ������ localhost|������� ����� Hosts}

   // ���������� AVZGuard [24]
   fsScriptRuntime.AddMethod('function  SetAVZGuardStatus(ANewStatus : boolean) : boolean', OnScriptCallMetodGuard);{���������� AVZGuard (true-��������,false-���������)|���������� AVZGuard}
   fsScriptRuntime.AddMethod('function  GetAVZGuardStatus : boolean', OnScriptCallMetodGuard);{������ ��������� AVZGuard (true-�������,false-��������)|������ ��������� AVZGuard}

   // ���������� AVZPM [25]
   fsScriptRuntime.AddMethod('function  SetAVZPMStatus(ANewStatus : boolean) : boolean', OnScriptCallMetodPM);{���������� AVZPM (true-��������,false-���������)|���������� AVZPM}
   fsScriptRuntime.AddMethod('function  GetAVZPMStatus : boolean', OnScriptCallMetodPM);{������ ��������� AVZPM (true-�������,false-��������)|������ ��������� AVZPM}

   // ���������� AVZ BOOT CLEANER [26]
   fsScriptRuntime.AddMethod('function  BC_Activate : boolean', OnScriptCallMetodBC);{��������� BootCleaner � �������� �������|��������� BootCleaner}
   fsScriptRuntime.AddMethod('function  BC_DeActivate : boolean', OnScriptCallMetodBC); {����������� BootCleaner � �������� �������|����������� BootCleaner}
   fsScriptRuntime.AddMethod('function  BC_Execute : boolean', OnScriptCallMetodBC); {��������� BootCleaner, �������� ������� � ����������� ������ BC, ��� ������������|������ BootCleaner}
   fsScriptRuntime.AddMethod('function  BC_Clear : boolean', OnScriptCallMetodBC);{������� ������� BootCleaner|*}
   fsScriptRuntime.AddMethod('function  BC_ImportDeletedList : boolean', OnScriptCallMetodBC); {������ � ������� BootCleaner ������ ������, ��������� ��������|*}
   fsScriptRuntime.AddMethod('function  BC_ImportQuarantineList : boolean', OnScriptCallMetodBC); {������ � ������� BootCleaner ������ ������, ���������� � �������� ��������|*}
   fsScriptRuntime.AddMethod('function  BC_ImportALL : boolean', OnScriptCallMetodBC); {������ � ������� BootCleaner ������ ������, ��������� � ���������� � �������� ��������|*|4.24}
   fsScriptRuntime.AddMethod('function  BC_LogFile(AFileName : string) : boolean', OnScriptCallMetodBC);{��������� ���������������� BootCleaner - �������� ����� �������� � ���� AFileName|��������� ���������������� BootCleaner}
   fsScriptRuntime.AddMethod('function  BC_QrFile(AFileName : string) : boolean', OnScriptCallMetodBC); {���������� � ������� BootCleaner ������� ��������� �����|BC-�������� �����}
   fsScriptRuntime.AddMethod('function  BC_DeleteFile(AFileName : string) : boolean', OnScriptCallMetodBC); {���������� � ������� BootCleaner ������� �������� �����|BC-�������� �����|}
   fsScriptRuntime.AddMethod('function  BC_CopyFile(AFromName, AToName : string) : boolean', OnScriptCallMetodBC); {���������� � ������� BootCleaner ������� ����������� �����|BC-����������� �����|4.26}
   fsScriptRuntime.AddMethod('function  BC_DeleteReg(AKeyName : string) : boolean', OnScriptCallMetodBC); {���������� � ������� BootCleaner ������� �������� ����� �������|BC-�������� ����� �������}
   fsScriptRuntime.AddMethod('function  BC_DeleteSvcReg(ASvcName : string) : boolean', OnScriptCallMetodBC); {���������� � ������� BootCleaner ������� �������� ����� ������� � ��������� ��������� ������/��������}
   fsScriptRuntime.AddMethod('function  BC_QrSvc(ASvcName : string) : boolean', OnScriptCallMetodBC); {���������� � ������� BootCleaner ������� ��������� ������/��������|BC-�������� ������/��������}
   fsScriptRuntime.AddMethod('function  BC_DeleteSvc(ASvcName : string) : boolean', OnScriptCallMetodBC); {���������� � ������� BootCleaner ������� �������� ������/�������� (��������� ���� ������� � ���� �� �����)|BC-�������� ������/��������}
   fsScriptRuntime.AddMethod('function  BC_DisableSvc(ASvcName : string) : boolean', OnScriptCallMetodBC); {���������� � ������� BootCleaner ������� ���������� ����������� ������/��������}

   // ������ ������� [27]
   fsScriptRuntime.AddMethod('function  ExecuteSysClean : boolean', OnScriptCallMetodClean); {������������� ������ �������|*}
   fsScriptRuntime.AddMethod('procedure SysCleanAddFile(AFileName : string)', OnScriptCallMetodClean); {���������� ����� � ������ AFileName � ������, ������������ �������� ������������� ������ ������� ExecuteSysClean}
   fsScriptRuntime.AddMethod('procedure SysCleanGetFilesList(AFileList : TStrings)', OnScriptCallMetodClean); {������ ������ ������, ������������� �������� ������������� ������ ������� ExecuteSysClean}
   fsScriptRuntime.AddMethod('procedure SysCleanSetFilesList(AFileList : TStrings)', OnScriptCallMetodClean); {��������� ������ ������, ������������� �������� ������������� ������ ������� ExecuteSysClean}
   fsScriptRuntime.AddMethod('procedure SysCleanDelFilesList', OnScriptCallMetodClean);{������� ������ ������, ������������ �������� ������������� ������ ������� ExecuteSysClean}

   // ��������� ��������� ������ [28]
   fsScriptRuntime.AddMethod('function  GetParamCount:integer', OnScriptCallMetodParam); {������ ���������� ���������� ��������� ������}
   fsScriptRuntime.AddMethod('function  GetParamStr(AParamId:integer) : string', OnScriptCallMetodParam); {������ ��������� ��������� ������ � ������� AParamId|�������� ��������� ������ �� ������}
   fsScriptRuntime.AddMethod('function  GetParamByName(AParamName:string) : string', OnScriptCallMetodParam); {������ ��������� ��������� ������ � ������ AParamName (��� ���������� ������ ������� ��������� ������ ����� ������ ���=��������|�������� ��������� ������ �� �����|4.26}

   // ���������� [29]
   fsScriptRuntime.AddMethod('function  SendNetMessage(AHost, AFromSt, AToSt, AMessageSt: string) : boolean', OnScriptCallSendMessage); {�������� �������� �� ����, ������ NET SEND|�������� �������� �� ����}
   fsScriptRuntime.AddMethod('function  SendSyslogMessage(AHost, AMessageSt: string) : boolean', OnScriptCallSendMessage); {�������� �������� ������ SYSLOG (���� 514/UDP)|�������� �������� ������ SYSLOG}
   fsScriptRuntime.AddMethod('function  SendEmailMessage(AServer, AFrom, ARecipients, ASubject, AMessageSt: string; AIdentification : boolean; ALogin, APasswd : string; AAttachFile1, AAttachFile2, AAttachFile3 : string) : boolean', OnScriptCallSendMessage); {�������� ������ �� ����������� �����|*}

   // ����������� ������ [30]
   fsScriptRuntime.AddMethod('function  LoadFileToBuffer(AFile : string) : boolean', OnScriptCallMetodBuf); {�������� ����� � ����� ������������ �����������}
   fsScriptRuntime.AddMethod('function  LoadFileToBufferEx(AFile : string; ARel : integer; ALen : integer) : boolean', OnScriptCallMetodBuf); {�������� ��������� ����� � ����� ������������ �����������}
   fsScriptRuntime.AddMethod('function  FreeBuffer : boolean', OnScriptCallMetodBuf); {������� ������ ������������ �����������. ����������� ������������� ��������� LoadFileToBuffer*}
   fsScriptRuntime.AddMethod('function  GetBufferSize : integer', OnScriptCallMetodBuf); {������ ������� ������ � ������}
   fsScriptRuntime.AddMethod('function  GetBufferByte(ARel : integer) : byte', OnScriptCallMetodBuf); {���������� �� ������ ����� �� ��������� ��������}
   fsScriptRuntime.AddMethod('function  GetBufferWord(ARel : integer) : word', OnScriptCallMetodBuf); {���������� �� ������ ����� �� ��������� ��������}
   fsScriptRuntime.AddMethod('function  GetBufferDWord(ARel : integer) : dword', OnScriptCallMetodBuf); {���������� �� ������ �������� ����� �� ��������� ��������}
   fsScriptRuntime.AddMethod('function  GetBufferStr(ARel : integer; ALen : integer) : string', OnScriptCallMetodBuf); {����������� �� ������ ������ �������� ������ �� ���������� ��������}
   fsScriptRuntime.AddMethod('function  SearchSign(ASign : string; ARel : integer; ALen : integer) : integer', OnScriptCallMetodBufSearch); {����������� �����}

   // ������� ���������� ��������-��������� [31]
   fsScriptRuntime.AddMethod('procedure GlobalProgressAddMax(X : integer)', OnScriptCallMetodProgress); {���������� � M�X ����������� ��������-���������� ��������� ����� �����}
   fsScriptRuntime.AddMethod('procedure GlobalProgressStep(X : integer = 1) : boolean', OnScriptCallMetodProgress); {����������� ����������� ��������-���������� �� X �����}

   // ��������� ����������� [32]
   fsScriptRuntime.AddMethod('function BackupRegKey(ARoot, AName, ABackupName : string) : boolean', OnScriptCallMetodRegBackup); {��������� ����������� ����� ������� � ����|*|4.26}
   fsScriptRuntime.AddMethod('function SaveBackupData(AData, ABackupName : string) : boolean', OnScriptCallMetodRegBackup); {���������� ��������� ������ � ����� Backup|*|4.26}
   fsScriptRuntime.AddMethod('function SaveBackupDataSt(AData : TStrings; ABackupName : string) : boolean', OnScriptCallMetodRegBackup); {���������� ��������� ������ � ����� Backup|*|4.26}

   // ������ � ����� IE [33]
   fsScriptRuntime.AddMethod('function GetIECacheItemsCount : integer', OnScriptCallMetodIE); {������ ���������� ������� � ���� IE|*|4.28}
   fsScriptRuntime.AddMethod('function ClearIECache : boolean', OnScriptCallMetodIE); {������� ���� IE|*|4.28}

   // ������ � ������������ ������������ ������� [34]
   fsScriptRuntime.AddMethod('function SC_INIT(AFileName : string = '') : boolean', OnScriptCallMetodSC); {������������� ������� ������� ��������� ������������|*|4.28}
   fsScriptRuntime.AddMethod('function SC_FREE : boolean', OnScriptCallMetodSC); {��������������� ������� �������|*|4.28}
   fsScriptRuntime.AddMethod('function SC_SelectNode(ANode : string) : boolean', OnScriptCallMetodSC); {����� ����� � ������� � ������ ANode|*|4.28}
   fsScriptRuntime.AddMethod('function SC_GetItemsCount : integer', OnScriptCallMetodSC); {������ ���������� ������� ��������� �����|*|4.28}
   fsScriptRuntime.AddMethod('function SC_GetParamVal(AIndx : integer; AName, ADefVal : string) : string', OnScriptCallMetodSC); {������ ��������|*|4.28}
   fsScriptRuntime.AddMethod('function SC_GetTagName(AIndx : integer) : string', OnScriptCallMetodSC); {������ ��������|*|4.28}
   fsScriptRuntime.AddMethod('function SC_SearchItem(AName, AVal : string; AFullComp : boolean) : integer', OnScriptCallMetodSC); {����� �� �������|*|4.28}
   {SCRIPT-DECL-END}

   // ���������� � ����������
   if fsScriptRuntime.Compile then begin
    if ACheckNoRun then begin
     Result := true;
     exit;
    end;
    fsScriptRuntime.OnRunLine := FOnRunLine;
    fsScriptRuntime.Execute;
    OutRes := fsScriptRuntime.Variables['OutRes'];
    Result := true;
   end else begin
    AddToLog('$AVZ0681: '+fsScriptRuntime.ErrorMsg+', $AVZ0745 ['+fsScriptRuntime.ErrorPos+']');
    LastError := fsScriptRuntime.ErrorMsg;
    LastErrorPos := fsScriptRuntime.ErrorPos;
   end;
 finally
  Running := false;
  CallGUILink(guiSet, 'MAIN-ENABLE', '');
 end;
end;

function TAvzUserScript.OnScriptCallMetod(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 s : string;
 StrSize,OldMode : dword;
 TimeInt : cardinal;
 SR : TSearchRec;
 Res : boolean;
begin
 Application.ProcessMessages;
 if StopF then Abort;
 try
   // ���������� � ��������
   if MethodName = 'ADDTOLOG' then begin
    AddToLog(Params[0]);
    exit;
   end;
   // ���������
   if MethodName = 'SETUPAVZ' then begin
    if Assigned(FSetupLink) then
     FSetupLink(Self, Params[0]);
    exit;
   end;
   // ������
   if MethodName = 'RUNSCAN' then begin
    CallGUILink(guiSet, 'MAIN-START', '');
   end;
   // ������ ��������� � ������
   if MethodName = 'STRINGREPLACE' then begin
    Result := StringReplace(Params[0], Params[1], Params[2], [rfReplaceAll, rfIgnoreCase]);
    exit;
   end;
   // ������ � �����
   if MethodName = 'STRTOINTDEF' then begin
    Result := StrToIntDef(Params[0], Params[1]);
    exit;
   end;
   // �����
   if MethodName = 'EXITAVZ' then begin
    CallGUILink(guiSet, 'MAIN-TERMINATE', '');
    exit;
   end;
   // ��������� ����� ��
   if MethodName = 'GETCOMPUTERNAME' then begin
    SetLength(S, 200);
    StrSize := length(s);
    GetComputerName(PChar(S), StrSize);
    Result := copy(S, 1, StrSize);
    exit;
   end;
   // ��������� �������� ��
   if MethodName = 'GETCOMPUTERCOMMENTS' then begin
    Result := RegKeyStrParamGet('HKEY_LOCAL_MACHINE', 'SYSTEM\ControlSet001\Services\lanmanserver\parameters', 'srvcomment');
    exit;
   end;
   // ��������� �������� "��������� NT"
   if MethodName = 'ISNT' then begin
    Result := IsNT;
    exit;
   end;
   // ���������� ���������
   if MethodName = 'SAVELOG' then begin
    try
     try
      if ExtractFilePath(Params[0]) <> '' then
       zForceDirectories(ExtractFilePath(Params[0]));
     except end;
     CallGUILink(guiSet, 'MAIN-SAVELOG', Params[0]);
    except end;
   end;
   // ���������� ���������
   if MethodName = 'SAVECSVLOG' then begin
    try
     try
      if ExtractFilePath(Params[0]) <> '' then
       zForceDirectories(ExtractFilePath(Params[0]));
     except end;
     VirFileList.SaveAsCSV(Params[0]);
    except end;
    exit;
   end;
   // ������������
   if MethodName = 'EXECUTEAUTOQUARANTINE' then begin
    try
     AddToLog('$AVZ0190');
     ExecuteAutoQurantineAuto;
     AddToLog('$AVZ0040');
    except end;
    exit;
   end;
   // �������� �������
   if MethodName = 'EXECUTESYSCHECK' then begin
    try
     AddToLog('$AVZ0191');
     ExecuteSysCheckScript(Params[0], $FFFFFFFF, false, 1);
     AddToLog('$AVZ0323');
    except end;
    exit;
   end;
   // �������� �������
   if MethodName = 'EXECUTESYSCHECKEX' then begin
    try
     AddToLog('$AVZ0191');
     ExecuteSysCheckScript(Params[0], Params[1], Params[2], Params[3]);
     AddToLog('$AVZ0323');
    except end;
    exit;
   end;
   // ��������� WatchDog
   if MethodName = 'ACTIVATEWATCHDOG' then begin
    if Params[0] > 0 then begin
     CallGUILink(guiSet, 'MAIN-SETWATCHDOG', inttostr(Params[0]));
    end else
     CallGUILink(guiSet, 'MAIN-DISABLEWATCHDOG', '');
    exit;
   end;
   // ����������� � ��������
   if MethodName = 'QUARANTINEFILE' then begin
    Result := false;
    CopyToInfected(ReplaceMacrosStr(Params[0]), '$AVZ0981 '+Params[1], 'Quarantine');
    QrFilesList.Add(ReplaceMacrosStr(Params[0]));
    S := NTFileNameToNormalName(ReplaceMacrosStr(Params[0]));
    QrFilesList.Add(S);
    CopyToInfected(S, '$AVZ0981 '+Params[1], 'Quarantine');
    // �������� �� ��������� �����
    if pos(':', S) <> 2 then begin
     if FileExists(GetWindowsDirectoryPath + S) then begin
      CopyToInfected(GetWindowsDirectoryPath + S, '$AVZ0981 '+Params[1], 'Quarantine');
      QrFilesList.Add(GetWindowsDirectoryPath + S);
     end;
     if FileExists(GetSystemDirectoryPath + S) then begin
      CopyToInfected(GetSystemDirectoryPath + S, '$AVZ0981 '+Params[1], 'Quarantine');
      QrFilesList.Add(GetWindowsDirectoryPath + S);
     end;
     if FileExists(GetSystemDirectoryPath + 'Drivers\' + S) then begin
      CopyToInfected(GetSystemDirectoryPath + 'Drivers\' + S, '$AVZ0981 '+Params[1], 'Quarantine');
      QrFilesList.Add(GetSystemDirectoryPath + 'Drivers\' + S);
     end;
     if FileExists(GetTempDirectoryPath + S) then begin
      CopyToInfected(GetTempDirectoryPath + S, '$AVZ0981 '+Params[1], 'Quarantine');
      QrFilesList.Add(GetTempDirectoryPath +  S);
     end;
     if FileExists(copy(GetSystemDirectoryPath, 1, 3) + S) then begin
      CopyToInfected(copy(GetSystemDirectoryPath, 1, 3) + S, '$AVZ0981 '+Params[1], 'Quarantine');
      QrFilesList.Add(copy(GetSystemDirectoryPath, 1, 3) +  S);
     end;
    end;
    // ����� ����� �� �����
    Res := FindFirst(S, faAnyFile, SR) = 0;
    S := NormalDir(ExtractFilePath(S));
    while Res do begin
     if SR.Attr and faDirectory = 0 then begin
      Result := CopyToInfected(S + SR.Name, '$AVZ0981 '+Params[1], 'Quarantine');
      AddToLog('$AVZ0183 '+NTFileNameToNormalName(S + SR.Name));
     end;
     Res := FindNext(SR) = 0;
    end;
    if copy(S, 2, 1) <> ':' then
     CopyToInfected(SearchSysPath(S), '$AVZ0981 '+Params[1], 'Quarantine');
    exit;
   end;
   // ����� BHO
   if MethodName = 'BHOEXISTS' then begin
    Result := BHOExists(PrepareCLSID(Params[0]));
    exit;
   end;
   // ����� CLSID
   if MethodName = 'CLSIDEXISTS' then begin
    Result := CLSIDExists(PrepareCLSID(Params[0]));
    exit;
   end;
   // ����� CLSID+�����
   if MethodName = 'CLSIDFILEEXISTS' then begin
    S := CLSIDFileName(PrepareCLSID(Params[0]));
    // ��������� ������ ��������� ������
    if S <> '' then begin
     OldMode := SetErrorMode(SEM_NOOPENFILEERRORBOX + SEM_FAILCRITICALERRORS);
     try
      Result := FileExists(NormalProgramFileName(S, '.dll'))
     except
      Result := false;
     end;
     SetErrorMode(OldMode);
    end else Result := false;
    exit;
   end;
   // ������ ����� ����� �� CLSID
   if MethodName = 'CLSIDFILENAME' then begin
    Result := CLSIDFileName(PrepareCLSID(Params[0]));
    exit;
   end;
   // �������� CLSID
   if MethodName = 'DELCLSID' then begin
    DelCLSID(Params[0]);
    exit;
   end;
   // �������� BHO
   if MethodName = 'DELBHO' then begin
    DelBHO(Params[0]);
    exit;
   end;
   // ����� ��������
   if MethodName = 'SEARCHROOTKIT' then begin
    Result := ScanRootKit(Params[0], Params[1]);
    exit;
   end;
   // ��������� �������� ��������
   if MethodName = 'GETCURRENTDIRECTORY' then begin
    Result := NormalDir(GetCurrentDir);
    exit;
   end;
   // �������� ������� ��������
   if MethodName = 'DIRECTORYEXISTS' then begin
    Result := DirectoryExists(NormalDir(ReplaceMacrosStr(Params[0])));
    exit;
   end;
   if MethodName = 'EXTRACTFILENAME' then begin
    Result := ExtractFileName(ReplaceMacrosStr(Params[0]));
    exit;
   end;
   if MethodName = 'EXTRACTFILEPATH' then begin
    Result := ExtractFilePath(ReplaceMacrosStr(Params[0]));
    exit;
   end;
   if MethodName = 'EXTRACTFILEEXT' then begin
    Result := ExtractFileExt(ReplaceMacrosStr(Params[0]));
    exit;
   end;
   // �������� ������� �����
   if MethodName = 'FILEEXISTS' then begin
    // ��������� ������ ��������� ������
    OldMode := SetErrorMode(SEM_NOOPENFILEERRORBOX + SEM_FAILCRITICALERRORS);
    try
     Result := FileExists(NTFileNameToNormalName(ReplaceMacrosStr(Params[0])));
    except
     Result := false;
    end;
    SetErrorMode(OldMode);
    exit;
   end;
   // ������ �����
   if MethodName = 'GETFILESIZE' then begin
    S := NTFileNameToNormalName(ReplaceMacrosStr(Params[0]));
    Result := -1;
    if FindFirst(s, faAnyFile, SR) = 0 then begin
     Result := SR.Size;
     FindClose(SR);
    end;
    exit;
   end;
   // MD5 �����
   if MethodName = 'CALKFILEMD5' then begin
    S := NTFileNameToNormalName(ReplaceMacrosStr(Params[0]));
    Result := CalkFileMD5(S);
    exit;
   end;
   // �������� �����
   if MethodName = 'DELETEFILE' then begin
    AddToLog('$AVZ1081:'+Params[0]);
    Result := AVZDeleteFile(NTFileNameToNormalName(ReplaceMacrosStr(Params[0])));
    DeletedFilesList.Add(ReplaceMacrosStr(Params[0]));
    if ReplaceMacrosStr(Params[0]) <> NTFileNameToNormalName(ReplaceMacrosStr(Params[0])) then
     DeletedFilesList.Add(NTFileNameToNormalName(ReplaceMacrosStr(Params[0])));
    exit;
   end;
   // ����������� �����
   if MethodName = 'COPYFILE' then begin
    AddToLog('$AVZ0357:'+Params[0]+'->'+Params[1]);
    try
     Result := CopyFile(PChar(NTFileNameToNormalName(ReplaceMacrosStr(Params[0]))), PChar(NTFileNameToNormalName(ReplaceMacrosStr(Params[1]))), true);
    except
     Result := false;
    end;
    exit;
   end;
   // ����������� �������������� �����
   if MethodName = 'RENAMEFILE' then begin
    AddToLog('$AVZ0704:'+Params[0]+'->'+Params[1]);
    try
     Result := RenameFile(NTFileNameToNormalName(ReplaceMacrosStr(Params[0])),
                          NTFileNameToNormalName(ReplaceMacrosStr(Params[1])));
    except
     Result := false;
    end;
    exit;
   end;
   // ��������� �������� AVZ
   if MethodName = 'GETAVZDIRECTORY' then begin
    Result := NormalDir(ExtractFilePath(Application.ExeName));
    exit;
   end;
   // ��������� ������ AVZ
   if MethodName = 'GETAVZVERSION' then begin
    Result := StrToFloatDef(StringReplace(VER_NUM, '.', DecimalSeparator, []), 0);
    exit;
   end;
   // ��������� ������ AVZ
   if MethodName = 'GETAVZVERSIONTXT' then begin
    Result := TranslateStr(VER_INFO);
    exit;
   end;
   // ��������� ����� ������ AVZ
   if MethodName = 'GETAVZSVCNAME' then begin
    Result := GenerateRandomName(8, integer(Params[0]));
    exit;
   end;
   // �������� ������ � ���������� ����� Qurantine
   if MethodName = 'CREATEQURANTINEARCHIVE' then begin
    AddToLog('$AVZ1018');
    Result := ExecuteInfectedViewAndCreateArchive('Quarantine', ReplaceMacrosStr(Params[0]), 'virus');
    AddToLog('$AVZ1019');
    exit;
   end;
   // �������� ������ � ���������� ����� Infected
   if MethodName = 'CREATEINFECTEDARCHIVE' then begin
    AddToLog('$AVZ1016');
    Result := ExecuteInfectedViewAndCreateArchive('Infected', ReplaceMacrosStr(Params[0]), 'virus');
    AddToLog('$AVZ1017');
    exit;
   end;
   // �������� �����
   if MethodName = 'CREATEDIRECTORY' then begin
    zForceDirectories(NormalDir(ReplaceMacrosStr(Params[0])));
    exit;
   end;
   // DeleteDirectory - �������� ��������
   if MethodName = 'DELETEDIRECTORY' then begin
    RemoveDirectory(PChar(NormalDir(ReplaceMacrosStr(Params[0]))));
    exit;
   end;
   // ������ ���������� �����
   if MethodName = 'GETSYSTEMDISK' then begin
    Result := copy(GetWindowsDirectoryPath, 1, 1);
    exit;
   end;
   // ���������� ����������
   if MethodName = 'LOCKINTERFACE' then begin
    CallGUILink(guiSet, 'MAIN-LOCKINTERFACE', '');
    exit;
   end;
   // ������������� ����������
   if MethodName = 'UNLOCKINTERFACE' then begin
    CallGUILink(guiSet, 'MAIN-UNLOCKINTERFACE', '');
    exit;
   end;
   // ������ �� �������� �������� �������
   if MethodName = 'SLEEP'  then begin
    TimeInt := GetTickCount;
    while GetTickCount - TimeInt < Params[0]*1000 do begin
     Application.ProcessMessages;
     Sleep(200);
     Application.ProcessMessages;
    end;
    exit;
   end;
   // ��������������
   if MethodName = 'EXECUTEAVUPDATE'  then begin
    Application.ProcessMessages;
    AddToLog('$AVZ0276');
    Result := ExecuteAutoUpdateNoGUI(0, '', 0, '','','');
    if Result then S := ' $AVZ1102' else S := '$AVZ0936';
    AddToLog('$AVZ0048 '+S);
    exit;
   end;
   // ��������������
   if MethodName = 'EXECUTEAVUPDATEEX'  then begin
    Application.ProcessMessages;
    S := Trim(Params[0]);
    // ���������� / � ������ URL
    if S <> '' then
     if (copy(S, length(S), 1) <> '/') and (copy(S, length(S), 1) <> '\') then
      S := S + '/';
    AddToLog('$AVZ0275');
    AddToLog('$AVZ0696:'+GetSetupDescr(Params[1], Params[2], Params[3], Params[4]));
    Result := ExecuteAutoUpdateNoGUI(0, S, Params[1], Params[2], Params[3], Params[4]);
    if Result then S := ' $AVZ1102' else S := '$AVZ0936';
    AddToLog('$AVZ0048 '+S);
    exit;
   end;
   // ������������ ����� ��������
   if MethodName = 'NORMALDIR'  then begin
    Result := NormalDir(ReplaceMacrosStr(Params[0]));
    exit;
   end;
   // ������������ ����� ��������
   if MethodName = 'NORMALFILENAME'  then begin
    Result := ExpandFileNameEx(NTFileNameToNormalName(ReplaceMacrosStr(Params[0])));
    exit;
   end;
   // ������������ ����� ��������
   if MethodName = 'SETSTATUSBARTEXT'  then begin
    CallGUILink(guiSet, 'MAIN-StatusBar', Params[0]);
    exit;
   end;
   // ������ �����
   if MethodName = 'EXECUTEFILE'  then begin
    Result := ExecuteProcess(ReplaceMacrosStr(Params[0]), Params[1], Params[2], Params[3], Params[4]);
    exit;
   end;
   // ������� ���������
   if MethodName = 'CLEARQUARANTINE'  then begin
    Result := DeleteQurantineFolder;
    exit;
   end;
   // ������� ���������
   if MethodName = 'ADDLINETOTXTFILE'  then begin
    Result := AddLineToTxtFile(ReplaceMacrosStr(Params[0]), Params[1]);
    exit;
   end;
   // ������ ���� �����
   if MethodName = 'GETDRIVETYPE' then begin
    Result := GetDriveType(PChar(String(Params[0])));
    exit;
   end;
 except
  on e : exception do
   AddToLog('$AVZ0654 '+MethodName+', $AVZ0631 - '+e.Message);
 end;
end;

function TAvzUserScript.PrepareCLSID(s: string): string;
begin
 Result := UpperCase(Trim(S));
 Result := StringReplace(Result, '{', '', []);
 Result := StringReplace(Result, '}', '', []);
end;

procedure TAvzUserScript.SetLogEnabled(const Value: boolean);
begin
 FLogEnabled := Value;
end;

function TAvzUserScript.OnScriptCallMetodBuf(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 FS : TFileStream;
 x, y : integer;
 w : word;
 dw : dword;
 S : string;
begin
  // ������ ������� ������
  if MethodName = 'GETBUFFERSIZE' then begin
   Result := Length(ScanBuf);
   exit;
  end;
  // ������ ����� ������
  if MethodName = 'GETBUFFERBYTE' then begin
   Result := 0;
   X := Params[0];
   if X < 0 then X := Length(ScanBuf) - 1 + X;
   if X < 0 then X := 0;
   if (X < Length(ScanBuf)) then
    Result := ScanBuf[X];
   exit;
  end;
  // ������ WORD ������
  if MethodName = 'GETBUFFERWORD' then begin
   Result := 0;
   X := Params[0];
   if X < 0 then X := Length(ScanBuf) - 1 + X;
   if X < 0 then X := 0;
   if (X < Length(ScanBuf)-1) then
    CopyMemory(@W, @ScanBuf[X], 2);
    Result := W;
   exit;
  end;
  // ������ DWORD ������
  if MethodName = 'GETBUFFERDWORD' then begin
   Result := 0;
   X := Params[0];
   if X < 0 then X := Length(ScanBuf) - 1 + X;
   if X < 0 then X := 0;
   if (X < Length(ScanBuf)-3) then
    CopyMemory(@DW, @ScanBuf[X], 4);
    Result := DW;
   exit;
  end;
  // ������ ��������� ������
  if MethodName = 'GETBUFFERSTR' then begin
   Result := '';
   X := Params[0];
   if X < 0 then X := Length(ScanBuf) - 1 + X;
   if X < 0 then X := 0;
   Y := Params[1];
   if Y = 0 then Y := Length(ScanBuf) - X;
   if X + Y > Length(ScanBuf) then Y := Length(ScanBuf) - X;
   if (X < Length(ScanBuf)) and (Y <= Length(ScanBuf)) then begin
    SetLength(S, Y);
    CopyMemory(@S[1], @ScanBuf[X], Y);
    Result := S;
   end;
   exit;
  end;
  // ������� ������
  if MethodName = 'FREEBUFFER' then begin
   ScanBuf := nil;
   Result := true;
   exit;
  end;
  // �������� ����� � �����
  if MethodName = 'LOADFILETOBUFFER' then begin
   ScanBuf := nil;
   Result := false;
   try
    FS := nil;
    FS := TFileStream.Create(ReplaceMacrosStr(Params[0]), fmOpenRead	or fmShareDenyNone);
    SetLength(ScanBuf, FS.Size);
    FS.Read(ScanBuf[0], FS.Size);
    Result := true;
    FS.Free;
   except
    ScanBuf := nil; // ������� ������ � ������ ����� ������
   end;
   exit;
  end;
  // �������� ����� � ����� - �����������
  if MethodName = 'LOADFILETOBUFFEREX' then begin
   ScanBuf := nil;
   Result := false;
   try
    FS := nil;
    FS := TFileStream.Create(ReplaceMacrosStr(Params[0]), fmOpenRead	or fmShareDenyNone);
    X := Params[1];
    Y := Params[2];
    if X < 0 then X := FS.Size + X;
    if X < 0 then X := 0;
    if Y = 0 then Y := FS.Size;
    if X + Y > FS.Size then Y := FS.Size;
    SetLength(ScanBuf, Y);
    FS.Seek(X, 0);
    FS.Read(ScanBuf[0], Y);
    Result := true;
    FS.Free;
   except
    ScanBuf := nil; // ������� ������ � ������ ����� ������
   end;
   exit;
  end;
end;

function TAvzUserScript.OnScriptCallMetodBufSearch(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
type
 TSignItem = record
  Operation : byte; // ��� ��������
  Data      : byte; // ��������
  Data1     : byte; // ��������
 end;
var
 FromRel, ToRel, Poz : integer;
 SignItems : array of TSignItem;
 Tmp : TSignItem;
 S, ST, TmpS : string;
 function SearchSign : boolean;
 var
  ScanPoz, SignPoz : integer;
 begin
  Result := false;
  ScanPoz := Poz;
  SignPoz := 0;
  while (SignPoz < Length(SignItems)) and (ScanPoz < ToRel) do begin
   case SignItems[SignPoz].Operation of
    0 : begin    // ������� �����
         inc(ScanPoz, SignItems[SignPoz].Data);
         inc(SignPoz, 1);
        end;
    1 : begin   // ������� 0..N ���� �� ��������
         if ScanBuf[ScanPoz] = SignItems[SignPoz].Data then inc(SignPoz, 1);
         inc(ScanPoz, 1);
        end;
    2 : begin  // ���� �� ����� ���������
         if (ScanBuf[ScanPoz] = SignItems[SignPoz].Data) then exit;
         inc(SignPoz, 1);
         inc(ScanPoz, 1);
        end;
    3 : begin // ���� ����� ���������
         if (ScanBuf[ScanPoz] <> SignItems[SignPoz].Data) then exit;
         inc(SignPoz, 1);
         inc(ScanPoz, 1);
        end;
    4 : begin // ���� ����� ��������� �� �����
         if ((ScanBuf[ScanPoz] and SignItems[SignPoz].Data1) <> SignItems[SignPoz].Data) then exit;
         inc(SignPoz, 1);
         inc(ScanPoz, 1);
        end;
   end;
  end;
  Result := not(SignPoz < Length(SignItems)) and (ScanPoz < ToRel);
 end;
begin
 Result := -1;
 FromRel := 0;
 ToRel   := length(ScanBuf) - 1;
 S := Trim(Params[0]) + ' ';
 // ������ ���� ������
 if Params[1] > 0 then
  FromRel := Params[1];
 if Params[1] < 0 then
  FromRel := (length(ScanBuf) - 1) + Params[1];
 if FromRel < 0 then FromRel := 0;
 // ����� ���� ������
 if Params[2] > 0 then
  ToRel := FromRel + Params[2];
 if Params[2] = 0 then
  ToRel := (length(ScanBuf) - 1);
 if ToRel > (length(ScanBuf) - 1) then
  ToRel := (length(ScanBuf) - 1);
 // �������� ������������ ���������
 if (FromRel < 0) or (FromRel > (length(ScanBuf) - 1)) then exit;
 if (ToRel < 0)   or (ToRel > (length(ScanBuf) - 1)) then exit;
 if (FromRel > ToRel) then exit;
 // ***** ������ ��������� ******
 SignItems := nil;
 while pos(' ', S) > 0 do begin
  ST := Trim(copy(S, 1, pos(' ', S)-1));
  delete(S, 1, pos(' ', S));
  if ST <> '' then begin
   // ������� ����� ��� ���������
   if copy(ST, 1, 1) = '?' then begin
    Tmp.Operation := 0;
    Tmp.Data := StrToIntDef(copy(ST, 2, 20), 1);
    if Tmp.Data = 0 then Tmp.Data := 1;
   end else
   // ����� ����� ���� �� ����������� ��������
   if copy(ST, 1, 1) = '*' then begin
    Tmp.Operation := 1;
    Tmp.Data      := StrToInt('$'+copy(ST, 2, 5));
   end else
   // �����
   if copy(ST, 1, 1) = '~' then begin
    Tmp.Operation := 4;
    TmpS := copy(ST, 2, 5);
    if pos(',', TmpS) = 0 then exit;
    Tmp.Data      := StrToInt('$'+copy(TmpS, 1, pos(',', TmpS)-1));
    Delete(TmpS, 1, pos(',', TmpS));
    Tmp.Data1     := StrToInt('$'+Trim(TmpS));
   end else
   // ���� �� ����� ���������
   if copy(ST, 1, 1) = '!' then begin
    Tmp.Operation := 2;
    Tmp.Data      := StrToInt('$'+copy(ST, 2, 5));
   end else
   // ���� ����� ���������
   begin
    Tmp.Operation := 3;
    Tmp.Data      := StrToInt('$'+ST);
   end;
   SetLength(SignItems, Length(SignItems)+1);
   SignItems[Length(SignItems)-1] := Tmp;
  end;
 end;
 // ��������� �� ������ - �����
 if Length(SignItems) = 0 then exit;
 // ������� ������
 Poz := FromRel;
 while Poz < ToRel do begin
  // ����� ���������
  if SearchSign then begin
   Result := Poz;
   exit;
  end;
  inc(Poz);
  if StopF then Abort;
 end;
end;

function TAvzUserScript.CallFindClassMethod(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
begin
 if StopF then Abort;
 if MethodName = 'FINDFIRST' then begin
  Result := (Instance as TFileSearch).FindFirst(ReplaceMacrosStr(Params[0]));
  exit;
 end;
 if MethodName = 'FINDNEXT' then begin
  Result := (Instance as TFileSearch).FindNext;
  exit;
 end;
 if MethodName = 'FINDCLOSE' then begin
  Result := (Instance as TFileSearch).FindClose;
  exit;
 end;
end;

function TAvzUserScript.ReplaceMacrosStr(s: string): string;
var
 Tmp : string;
begin
 Result := s;
 S := LowerCase(S);
 //
 // ����������� ���� � AppData
 if pos('%appdata%', S) > 0 then begin
  Tmp := RegKeyReadString(HKEY_CURRENT_USER, ShellFoldersKey, 'AppData');
  Result := StringReplace(Result, '%AppData%', NormalNameDir(Tmp), [rfReplaceAll, rfIgnoreCase]);
 end;
 // ����������� ���� � Personal
 if pos('%personal%', S) > 0 then begin
  Tmp := RegKeyReadString(HKEY_CURRENT_USER, ShellFoldersKey, 'Personal');
  Result := StringReplace(Result, '%Personal%', NormalNameDir(Tmp), [rfReplaceAll, rfIgnoreCase]);
 end;
 // ����������� ���� � allusersprofile
 if pos('%allusersprofile%', S) > 0 then begin
  Tmp := RegKeyReadString(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows NT\CurrentVersion\ProfileList', 'ProfilesDirectory');
  Tmp := NormalDir(Tmp);
  Tmp := Tmp+RegKeyReadString(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows NT\CurrentVersion\ProfileList', 'AllUsersProfile');
  Result := StringReplace(Result, '%allusersprofile%', NormalNameDir(Tmp), [rfReplaceAll, rfIgnoreCase]);
 end;
 // ����������� ���� � allusersprofile
 if pos('%profiledir%', S) > 0 then begin
  Tmp := RegKeyReadString(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows NT\CurrentVersion\ProfileList', 'ProfilesDirectory');
  Result := StringReplace(Result, '%profiledir%', NormalNameDir(Tmp), [rfReplaceAll, rfIgnoreCase]);
 end;
 // ����������� ���� � userprofile
 if pos('%userprofile%', S) > 0 then begin
  Tmp := GetEnvironmentVariable('USERPROFILE');
  Result := StringReplace(Result, '%USERPROFILE%', NormalNameDir(Tmp), [rfReplaceAll, rfIgnoreCase]);
 end;
 // ������ ������� �� �������� ����
 Result := StringReplace(Result, '%SystemRoot%', NormalNameDir(GetWindowsDirectoryPath), [rfReplaceAll, rfIgnoreCase]);
 // ������ ������� �� �������� ����
 Result := StringReplace(Result, '%System32%', NormalNameDir(GetSystemDirectoryPath), [rfReplaceAll, rfIgnoreCase]);
 // ������ ������� �� �������� ����
 Result := StringReplace(Result, '%WinDir%', NormalNameDir(GetWindowsDirectoryPath), [rfReplaceAll, rfIgnoreCase]);
 // ������ ������� �� �������� ����
 Result := StringReplace(Result, '%SysDisk%', copy(GetSystemDirectoryPath, 1, 2), [rfReplaceAll, rfIgnoreCase]);
 Result := StringReplace(Result, '%SYSTEMDRIVE%', copy(GetSystemDirectoryPath, 1, 2), [rfReplaceAll, rfIgnoreCase]);
 // ������ ������� �� �������� ����
 Result := StringReplace(Result, '%PF%', copy(GetSystemDirectoryPath, 1, 3)+'Program Files', [rfReplaceAll, rfIgnoreCase]);
 // ������ ������� �� �������� ����
 Result := StringReplace(Result, '%Tmp%', NormalNameDir(GetTempDirectoryPath), [rfReplaceAll, rfIgnoreCase]);
end;

function TAvzUserScript.OnScriptCallSendMessage(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
begin
 if StopF then Abort;
   // �������� ��������� �� ����
   if MethodName = 'SENDNETMESSAGE'  then begin
    AddToLog('$AVZ0620');
    Result := SendNetMessage(Params[0], Params[1], Params[2], Params[3]);
    exit;
   end;
   // �������� ������
   if MethodName = 'SENDEMAILMESSAGE'  then begin
    AddToLog('$AVZ0621');
    Result := SendEmail(Params[0], Params[1], Params[2], Params[3], Params[4], Params[5], Params[6], Params[7], Params[8], Params[9], Params[10]);
    exit;
   end;
   // �������� ��������� SysLog
   if MethodName = 'SENDSYSLOGMESSAGE'  then begin
    AddToLog('$AVZ0619');
    Result := SendSyslogMessage(Params[0], Params[1]);
    exit;
   end;
end;

function TAvzUserScript.ExecuteProcess(AFileName, AParams: string;
  Mode, WaitTime: integer; Terminate : boolean): boolean;
var
 StartupInfo         : TStartupInfo;
 ProcessInformation  : TProcessInformation;
 T : dword;
begin
 AddToLog('$AVZ0279 '+AFileName+' '+AParams);
 // ������ ���������� �������� �������� ����������
 FillChar( StartupInfo, SizeOf(StartupInfo), 0);
 with StartupInfo do begin
  cb := SizeOf(StartupInfo);
  dwFlags := startf_UseShowWindow;
  wShowWindow := Mode;
 end;
 // �������� ��������
 Result := CreateProcess(nil, PChar(AFileName+' '+AParams),nil,nil,false,Create_default_error_mode,nil,nil,StartupInfo,ProcessInformation);
 if WaitTime > 0 then begin
  T := GetTickCount;
  while (WaitForSingleObject(ProcessInformation.hProcess, 100) = WAIT_TIMEOUT) and (GetTickCount - T < WaitTime) do begin
   Application.ProcessMessages;
   if StopF then Break;
  end;
   // ��������� ��������
   if (WaitForSingleObject(ProcessInformation.hProcess, 0) = WAIT_TIMEOUT) and Terminate then begin
    AddToLog('$AVZ0799 '+IntToStr(WaitTime)+' $AVZ1294');
    TerminateProcess(ProcessInformation.hProcess, 0);
    CloseHandle(ProcessInformation.hProcess);
   end;
 end;
end;

function TAvzUserScript.DeleteQurantineFolder: boolean;
var
 SR               : TSearchRec;
 Res              : integer;
 InfectedFolder   : string;
 Year, Month, Day : word;
begin
 Result := false;
 InfectedFolder := NormalDir(ExtractFilePath(Application.ExeName)+'Quarantine');
   // ������������ ������������ ����� (���-�����-����)
 DecodeDate(Now, Year, Month, Day);
 InfectedFolder := InfectedFolder + IntToStr(Year) + '-' +
                    FormatFloat('00', Month) + '-' + FormatFloat('00', Day)+'\';
 Res := FindFirst(InfectedFolder+'*.*', faAnyFile, SR);
 while Res = 0 do begin
   if (LowerCase(ExtractFileExt(SR.Name)) = '.ini') or
      (LowerCase(ExtractFileExt(SR.Name)) = '.dta') then
        DeleteFile(InfectedFolder+SR.Name);
   Res := FindNext(SR);
  end;
  FindClose(SR);
  // �������� �����
  RemoveDirectory(PChar(NormalDir(InfectedFolder)));
  RemoveDirectory(PChar(NormalNameDir(InfectedFolder)));
  Result := not(DirectoryExists(InfectedFolder));
end;

function TAvzUserScript.OnScriptCallMetodPL(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 SysProcessInfo  : TSysProcessInfo;
 Tmp : dword;
 S, ST : string;
 i : integer;
begin
 // ���������� ������ ���������
 if MethodName = 'REFRESHPROCESSLIST'  then begin
  // �������� ������ "���������� � ���������" � ����������� �� ���� ��
  if ISNT then
   SysProcessInfo := TPSAPIProcessInfo.Create
    else SysProcessInfo := TToolHelpProcessInfo.Create;
  // ���������� ������ ���������
  SysProcessInfo.CreateProcessList(ProcessList);
  SysProcessInfo.Free;
  Result := true;
  exit;
 end;
 // ���-�� ���������
 if MethodName = 'GETPROCESSCOUNT'  then begin
  Result := ProcessList.Count;
  exit;
 end;
 // ������ ����� �������� N
 if MethodName = 'GETPROCESSNAME'  then begin
  Result := '';
  if (Params[0] >= 0) and ((Params[0] < ProcessList.Count)) then
   Result := (ProcessList.Objects[Params[0]] as TProcessInfo).ExeFileName;
  exit;
 end;
 // ������ PID �������� N
 if MethodName = 'GETPROCESSPID'  then begin
  Result := '';
  if (Params[0] >= 0) and ((Params[0] < ProcessList.Count)) then
   Result := (ProcessList.Objects[Params[0]] as TProcessInfo).PID;
  exit;
 end;
 // ��������� ��������
 if MethodName = 'TERMINATEPROCESS'  then begin
  Result := '';
  if ISNT then
   SysProcessInfo := TPSAPIProcessInfo.Create
    else SysProcessInfo := TToolHelpProcessInfo.Create;
   Result := SysProcessInfo.KillProcessByPID(Params[0], true);
   SysProcessInfo.Free;
  exit;
 end;
 // ��������� �������� �� �����
 if MethodName = 'TERMINATEPROCESSBYNAME'  then begin
  Result := '';
  if ISNT then
   SysProcessInfo := TPSAPIProcessInfo.Create
    else SysProcessInfo := TToolHelpProcessInfo.Create;
   Result := true;
   SysProcessInfo.CreateProcessList(ProcessList);
   S := AnsiLowerCase(Trim(Params[0]));
   for i := 0 to ProcessList.Count - 1 do begin
    Tmp := (ProcessList.Objects[i] as TProcessInfo).PID;
    ST  := ExtractFileName((ProcessList.Objects[i] as TProcessInfo).ExeFileName);
    if pos(S, AnsiLowerCase((ProcessList.Objects[i] as TProcessInfo).ExeFileName)) > 0 then
     if not(SysProcessInfo.KillProcessByPID(Tmp, true)) then begin
      AddToLog('[TerminateProcess]: '+'$AVZ0668' + inttostr(Tmp) + ' '+ ST);
      Result := false;
     end else
      AddToLog('[TerminateProcess]: '+'$AVZ0878 (' + inttostr(Tmp) + ' '+ ST+')');
   end;
   SysProcessInfo.Free;
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.RegKeyDelete(ARoot, AKey: string): boolean;
begin
 Result := false;
 if not(SetRootKeyByName(ARoot)) then exit;
 if trim(AKey) = '' then exit;
 // BackUp ����� ���������
 DoAddBackupDeleteKey(ARoot, AKey);
 // �������� �����
 Reg.Access := KEY_ALL_ACCESS;
 Result := Reg.DeleteKey(AKey);
 if Result then
  AddToLog('$AVZ0417 '+ARoot+'\'+AKey);
end;

function TAvzUserScript.OnScriptCallMetodReg(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 Lines : TStrings;
begin
 if MethodName = 'REGKEYDEL' then begin
  Result := RegKeyDelete(Params[0], Params[1]);
  exit;
 end;
 if MethodName = 'REGKEYCREATE' then begin
  Result := RegKeyCreate(Params[0], Params[1]);
  exit;
 end;
 if MethodName = 'REGKEYPARAMDEL' then begin
  Result := RegKeyParamDelete(Params[0], Params[1], Params[2]);
  exit;
 end;
 if MethodName = 'REGKEYEXISTS' then begin
  Result := RegKeyExists(Params[0], Params[1]);
  exit;
 end;
 if MethodName = 'REGKEYPARAMEXISTS' then begin
  Result := RegKeyParamExists(Params[0], Params[1], Params[2]);
  exit;
 end;
 if MethodName = 'REGKEYSTRPARAMWRITE' then begin
  Result := RegKeyStrParamSet(Params[0], Params[1], Params[2], Params[3]);
  exit;
 end;
 if MethodName = 'REGKEYINTPARAMWRITE' then begin
  Result := RegKeyINTParamSet(Params[0], Params[1], Params[2], Params[3]);
  exit;
 end;
 if MethodName = 'REGKEYBINPARAMWRITE' then begin
  Result := RegKeyBINParamSet(Params[0], Params[1], Params[2], Params[3]);
  exit;
 end;
 if MethodName = 'REGKEYSTRPARAMREAD' then begin
  Result := RegKeyStrParamGet(Params[0], Params[1], Params[2]);
  exit;
 end;
 if MethodName = 'REGKEYINTPARAMREAD' then begin
  Result := RegKeyIntParamGet(Params[0], Params[1], Params[2]);
  exit;
 end;
 if MethodName = 'REGKEYENUMVAL' then begin
  Result := false;
  Lines := TStrings(Integer(Params[2]));
  if Lines = nil then exit;
  if not(Lines is TStrings) then exit;
  Result := RegKeyEnumVal(Params[0], Params[1], Lines);
  exit;
 end;
 if MethodName = 'REGKEYENUMKEY' then begin
  Result := false;
  Lines := TStrings(Integer(Params[2]));
  if Lines = nil then exit;
  if not(Lines is TStrings) then exit;
  Result := RegKeyEnumKey(Params[0], Params[1], Lines);
  exit;
 end;
 // ������� ����� �������
 if pos('EXPREGKEYEX', MethodName) = 1 then begin
  Result := false;
  Lines := TStrings(Integer(Params[2]));
  if Lines = nil then exit;
  if not(Lines is TStrings) then exit;
  try
   Result := ExpRegKey(StrToRootKey(Params[0]), Params[1], Lines);
  except
  end;
  exit;
 end;
 // ������� ����� �������
 if pos(MethodName, 'EXPREGKEY') = 1 then
  Result := true;
  if StrToRootKey(Params[0]) > 0 then begin
    Lines := TStringList.Create;
   Lines.Add('REGEDIT4');
   Lines.Add('');
   ExpRegKey(StrToRootKey(Params[0]), Params[1], Lines);
  try
   zForceDirectories(ExtractFilePath(Params[2]));
   Lines.SaveToFile(Params[2]);
   Result := true;
  except
  end;
  Lines.Free;
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodReboot(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 InitiateSystemShutdownEx : TInitiateSystemShutdownEx;
 H : THandle;
 Res : boolean;
begin
 H := LoadLibrary('Advapi32.dll');
 @InitiateSystemShutdownEx := GetProcAddress(H, 'InitiateSystemShutdownEx');
 Res := AdjustPrivileges('SeShutdownPrivilege', true);     //#DNL
 AddToDebugLog('SeShutdownPrivilege GetLastError='+IntToStr(GetLastError));
 AddToDebugLog('SeShutdownPrivilege Res='+BoolToStr(Res));
 if MethodName = 'SHUTDOWNWINDOWS' then begin
  if Params[0] then
   Res := ExitWindowsEx(EWX_SHUTDOWN or EWX_FORCE, 0)
    else Res := ExitWindowsEx(EWX_SHUTDOWN, 0);
  exit;
 end;
 if MethodName = 'REBOOTWINDOWS' then begin
  if Params[0] then
   Res := ExitWindowsEx(EWX_REBOOT or EWX_FORCE, 0)
    else Res := ExitWindowsEx(EWX_REBOOT, 0);
   AddToDebugLog('ExitWindowsEx GetLastError = '+IntToStr(GetLastError));
   AddToDebugLog('ExitWindowsEx = '+BoolToStr(Res));
  exit;
 end;
end;


function TAvzUserScript.RegKeyCreate(ARoot, AKey: string): boolean;
begin
 Result := false;
 if not(SetRootKeyByName(ARoot)) then exit;
 if trim(AKey) = '' then exit;
 Reg.Access := KEY_ALL_ACCESS;
 Result := Reg.CreateKey(AKey);
 if Result then
  AddToLog('$AVZ0414 '+ARoot+'\'+AKey);
end;

function TAvzUserScript.RegKeyExists(ARoot, AKey: string): boolean;
begin
 Result := false;
 if not(SetRootKeyByName(ARoot)) then exit;
 if trim(AKey) = '' then exit;
 Result := Reg.KeyExists(AKey);
end;

function TAvzUserScript.RegKeyIntParamGet(ARoot, AKey,
  AParam: string): integer;
begin
 Result := -1;
 if not(SetRootKeyByName(ARoot)) then exit;
 if trim(AKey) = '' then exit;
 if Reg.OpenKeyReadOnly(AKey) then begin
  try
   Result := Reg.ReadInteger(AParam);
  except
  end;
  Reg.CloseKey;
 end;
end;

function TAvzUserScript.RegKeyParamDelete(ARoot, AKey,
  AParam: string): boolean;
begin
 Result := false;
 if not(SetRootKeyByName(ARoot)) then exit;
 Reg.Access := KEY_ALL_ACCESS;
 if trim(AKey) = '' then exit;
 if Reg.OpenKey(AKey, false) then begin
  // BackUp ��������� ����� ���������
  DoAddBackupDeleteParam(ARoot, AKey, AParam);
  // ��������
  Reg.Access := KEY_ALL_ACCESS;
  Result := Reg.DeleteValue(AParam);
  if Result then
   AddToLog('$AVZ0418 '+AParam+' $AVZ0339 '+ARoot+'\'+AKey);
  Reg.CloseKey;
 end;
end;

function TAvzUserScript.RegKeyParamExists(ARoot, AKey,
  AParam: string): boolean;
begin
 Result := false;
 if not(SetRootKeyByName(ARoot)) then exit;
 if trim(AKey) = '' then exit;
 if Reg.OpenKeyReadOnly(AKey) then begin
  Result := Reg.ValueExists(AParam);
  Reg.CloseKey;
 end;
end;

function TAvzUserScript.RegKeyStrParamGet(ARoot, AKey,
  AParam: string): string;
begin
 Result := '';
 if not(SetRootKeyByName(ARoot)) then exit;
 if trim(AKey) = '' then exit;
 if Reg.OpenKeyReadOnly(AKey) then begin
  try
   Result := Reg.ReadString(AParam);
  except
  end;
  Reg.CloseKey;
 end;
end;

function TAvzUserScript.RegKeyStrParamSet(ARoot, AKey, AParam,
  AValue: string): boolean;
begin
 Result := false;
 // ���������� ��������
 if not(SetRootKeyByName(ARoot)) then exit;
 if trim(AKey) = '' then exit;
 // ����������� �����
 Reg.Access := KEY_ALL_ACCESS;
 if Reg.OpenKey(AKey, true) then begin
  // BackUp ���������
  DoAddBackupChangeParam(ARoot, AKey, AParam);
  try
   Reg.Access := KEY_ALL_ACCESS;
   Reg.WriteString(AParam, AValue);
   Result := true;
  except
  end;
  AddToLog('$AVZ0413 '+AParam+' $AVZ0339 '+ARoot+'\'+AKey);
  Reg.CloseKey;
 end;
end;

function TAvzUserScript.SetRootKeyByName(AName: string): boolean;
begin
 Result := false;
 if StrToRootKey(AName) > 0 then begin
  Reg.RootKey := StrToRootKey(AName);
  Result := true;
 end;
end;

function TAvzUserScript.OnScriptCallMetodGuard(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 Tmp : boolean;
begin
 // ���������-�����������
 if MethodName = 'SETAVZGUARDSTATUS' then begin
  Tmp := Params[0];
  if Tmp = AVZGuardIsOn then begin
   CallGUILink(guiSet, 'MAIN-RefreshInterface', '');
   Result := true;
   exit;
  end;
  if Tmp then
   Result := ActivateAVZGuard
  else
   Result := DeActivateAVZGuard;
  CallGUILink(guiSet, 'MAIN-RefreshInterface', '');
  exit;
 end;
 // ������ �������� ���������
 if MethodName = 'GETAVZGUARDSTATUS' then begin
  Result := AVZGuardIsOn;
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.RegKeyIntParamSet(ARoot, AKey, AParam : string; AValue : dword): boolean;
begin
 Result := false;
 if not(SetRootKeyByName(ARoot)) then exit;
 if trim(AKey) = '' then exit;
 Reg.Access := KEY_ALL_ACCESS;
 if Reg.OpenKey(AKey, true) then begin
  // BackUp ���������
  DoAddBackupChangeParam(ARoot, AKey, AParam);
  try
   Reg.Access := KEY_ALL_ACCESS;
   Reg.WriteInteger(AParam, AValue);
   Result := true;
  except
  end;
  AddToLog('$AVZ0413 '+AParam+' $AVZ0339 '+ARoot+'\'+AKey);
  Reg.CloseKey;
 end;
end;

procedure TAvzUserScript.DelInterface(ACLSID: string);
begin
 FormatCLSID(ACLSID);
 if ACLSID = '' then exit;
 Reg.RootKey := HKEY_CLASSES_ROOT;
 // �������� ����� �������
 try
  Reg.Access := KEY_ALL_ACCESS;
  if Reg.DeleteKey('CLSID\Interface\'+ACLSID) then
   AddToLog('$AVZ0416 '+ACLSID);
 except end;
end;

procedure TAvzUserScript.DelBHO(ACLSID: string);
begin
 // ���������� � �������������� CLSID
 FormatCLSID(ACLSID);
 if ACLSID = '' then exit;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 Reg.Access := KEY_ALL_ACCESS;
 if Reg.DeleteKey('SOFTWARE\Microsoft\Internet Explorer\Explorer Bars\'+ACLSID) then
  AddToLog('$AVZ0423'+ACLSID);
 if Reg.DeleteKey('SOFTWARE\Microsoft\Internet Explorer\Extensions'+ACLSID) then
  AddToLog('$AVZ0425'+ACLSID);
 if Reg.DeleteKey('SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Browser Helper Objects\'+ACLSID) then
  AddToLog('$AVZ0425'+ACLSID);
 if Reg.OpenKey('SOFTWARE\Microsoft\Internet Explorer\ToolBar', false) then begin
  if Reg.DeleteValue(ACLSID) then
   AddToLog('$AVZ0423'+ACLSID);
  Reg.CloseKey;
 end;
 Reg.RootKey := HKEY_CURRENT_USER;
 Reg.Access := KEY_ALL_ACCESS;
 if Reg.DeleteKey('SOFTWARE\Microsoft\Internet Explorer\Explorer Bars\'+ACLSID) then
  AddToLog('$AVZ0423'+ACLSID);
 if Reg.DeleteKey('SOFTWARE\Microsoft\Internet Explorer\Extensions'+ACLSID) then
  AddToLog('$AVZ0425'+ACLSID);
 if Reg.OpenKey('SOFTWARE\Microsoft\Internet Explorer\ToolBar', false) then begin
  if Reg.DeleteValue(ACLSID) then
   AddToLog('$AVZ0423'+ACLSID);
  Reg.CloseKey;
 end;
end;

procedure TAvzUserScript.DelActiveSetup(ACLSID: string);
begin
 // ���������� � �������������� CLSID
 FormatCLSID(ACLSID);
 if ACLSID = '' then exit;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 Reg.Access := KEY_ALL_ACCESS;
 if Reg.DeleteKey('SOFTWARE\Microsoft\Active Setup\Installed Components\'+ACLSID) then
  AddToLog('$AVZ0419 '+ACLSID);
end;

procedure TAvzUserScript.DelShellExt(ACLSID: string);
begin
 FormatCLSID(ACLSID);
 if Trim(ACLSID) = '' then exit;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 Reg.Access := KEY_ALL_ACCESS;
 if Reg.DeleteKey('SOFTWARE\Microsoft\Windows\CurrentVersion\Shell Extensions\Approved'+ACLSID) then
  AddToLog('$AVZ0421 '+ACLSID);
end;

procedure TAvzUserScript.DelSharedTaskSch(ACLSID: string);
begin
 FormatCLSID(ACLSID);
 if Trim(ACLSID) = '' then exit;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 Reg.Access := KEY_ALL_ACCESS;
 if Reg.OpenKey('SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\SharedTaskScheduler\', false) then begin
  if Reg.ValueExists(ACLSID) then
   if Reg.DeleteValue(ACLSID) then
    AddToLog('$AVZ0420 '+ACLSID);
  Reg.CloseKey;
 end;
end;


procedure TAvzUserScript.DelCLSID(ACLSID: string);
begin
 FormatCLSID(ACLSID);
 if ACLSID = '' then exit;
 Reg.RootKey := HKEY_CLASSES_ROOT;
 Reg.Access := KEY_ALL_ACCESS;
 // �������� ����� �������
 if Reg.DeleteKey('CLSID\'+ACLSID) then
  AddToLog('$AVZ0415 '+ACLSID);
 // �������� ������ � Shell Extensions\Approved
 RegKeyParamDelete('HKEY_LOCAL_MACHINE', 'SOFTWARE\Microsoft\Windows\CurrentVersion\Shell Extensions\Approved', ACLSID);
 // �������� ����������
 DelInterface(ACLSID);
 // �������� BHO
 DelBHO(ACLSID);
 // �������� ActiveSetup
 DelActiveSetup(ACLSID);
 // �������� Shell Extention
 DelShellExt(ACLSID);
 // �������� SharedTaskScheduler
 DelSharedTaskSch(ACLSID);
end;


procedure TAvzUserScript.FormatCLSID(var ACLSID: string);
begin
 // ���������� � �������������� CLSID
 ACLSID := Trim(ACLSID);
 if ACLSID = '' then exit;
 if copy(ACLSID, 1, 1) <> '{' then
  ACLSID := '{' + ACLSID;
 if copy(ACLSID, length(ACLSID), 1) <> '}' then
  ACLSID := ACLSID + '}';
end;

function TAvzUserScript.OnScriptCallMetodSPI(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 LSPManager : TLSPManager;
 Lines      : TStringList;
 i          : integer;
begin
 LSPManager := nil;
 try
   // �������� LSP
   if MethodName = 'DELSPIBYFILENAME' then begin
    LSPManager := TLSPManager.Create;
    LSPManager.Refresh;
    LSPManager.DeleteNameSpaceByBinaryName(ReplaceMacrosStr(Params[0]), Params[1]);
    LSPManager.DeleteProtocolByBinaryName(ReplaceMacrosStr(Params[0]), Params[1]);
    LSPManager.DeleteNameSpaceByBinaryName(ReplaceMacrosStr(Params[0]), Params[1]);
    LSPManager.DeleteProtocolByBinaryName(ReplaceMacrosStr(Params[0]), Params[1]);
    LSPManager.Free;
    LSPManager := nil;
    exit;
   end;
   // ������� SPI
   if MethodName = 'AUTOFIXSPI' then begin
    LSPManager := TLSPManager.Create;
    LSPManager.Refresh;
    LSPManager.AutoRepairNameSpace;
    LSPManager.AutoRepairProtocol;
    LSPManager.Free;
    LSPManager := nil;
    exit;
   end;
   if MethodName = 'CHECKSPI' then begin
    LSPManager := TLSPManager.Create;
    LSPManager.Refresh;
    Lines := TStringList.Create;
    i := LSPManager.SearchErrors(Lines);
    Result := i;
    if i > 0 then begin
     for i := 0 to Lines.Count - 1 do
      ZLogSystem.AddToLog(Lines[i], logAlert);
    end;
    Lines.Free;
    LSPManager.Free;
    LSPManager := nil;
    exit;
   end;
   AddToLog('$AVZ0630 [2, '+MethodName+']');
 finally
  LSPManager.Free;
 end;
end;

procedure TAvzUserScript.DelWinlogonNotifyByFileName(AFileName: string);
var
 Reg   : TRegistry;
 Lines : TStringList;
 i     : integer;
 S     : string;
begin
 AFileName := Trim(AnsiLowerCase(AFileName));
 Reg := nil;
 Reg   := TRegistry.Create;
 Reg.Access := KEY_ALL_ACCESS;
 Lines := TStringList.Create;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 if Reg.OpenKey('SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon\Notify', false) then begin
  Reg.GetKeyNames(Lines);
  Reg.CloseKey;
  // ���� ������ �����
  for i := 0 to Lines.Count - 1 do
   if Reg.OpenKey('SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon\Notify\'+Lines[i], false) then begin
    if Reg.ValueExists('DllName') then begin
     S :=  AnsiLowerCase(Trim(NTFileNameToNormalName(LowerCase(Trim(Reg.ReadString('DllName'))))));
     if ExtractFilePath(S) = '' then begin
      if FileExists(GetSystemDirectoryPath+S) then S := GetSystemDirectoryPath + S;
     end;
     if pos(AFileName, S) = Length(S) - Length(AFileName)+1  then begin
      Reg.Access := KEY_ALL_ACCESS;
      Reg.DeleteKey('SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon\Notify\'+Lines[i]);
      AddToLog('$AVZ1072 '+AFileName);
     end;
    end;
    try Reg.CloseKey; except end;
   end;
 end;
 Reg.Free;
 Lines.Free;
end;

procedure TAvzUserScript.DelWinlogonNotifyByKeyName(AKeyName: string);
var
 Reg   : TRegistry;
begin
 Reg := nil;
 Reg   := TRegistry.Create;
 Reg.RootKey := HKEY_LOCAL_MACHINE;
 Reg.Access := KEY_ALL_ACCESS;
 if Reg.DeleteKey('SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon\Notify\'+AKeyName) then begin
  AddToLog('$AVZ1071 '+AKeyName);
 end;
 Reg.Free;
end;

function TAvzUserScript.OnScriptCallMetodWinlogon(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
begin
 if MethodName = 'DELWINLOGONNOTIFYBYFILENAME'  then begin
  DelWinlogonNotifyByFileName(Params[0]);
  exit;
 end;
 if MethodName = 'DELWINLOGONNOTIFYBYKEYNAME'  then begin
  DelWinlogonNotifyByKeyName(Params[0]);
  exit;
 end;
 if MethodName = 'DELAUTORUNBYFILENAME'  then begin
  DelAutorunByFileName(Params[0]);
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodClean(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
begin
 if MethodName = 'EXECUTESYSCLEAN'  then begin
  ExtSystemClean(DeletedFilesList);
  DeletedFilesList.Clear;
  exit;
 end;
 if MethodName = 'SYSCLEANADDFILE'  then begin
  DeletedFilesList.Add(ReplaceMacrosStr(Params[0]));
  exit;
 end;
 if MethodName = 'SYSCLEANDELFILESLIST'  then begin
  DeletedFilesList.Clear;
  exit;
 end;
end;

function TAvzUserScript.RegKeyBinParamSet(ARoot, AKey, AParam,
  AValue: string): boolean;
var
 Buf, S, ST : string;
begin
 Result := false;
 if not(SetRootKeyByName(ARoot)) then exit;
 if trim(AKey) = '' then exit;
 Buf := '';
 Reg.Access := KEY_ALL_ACCESS;
 // �������� ��������
 S := StringReplace(Trim(AValue), ' ', '', [rfReplaceAll])+',';
 while pos(',', S) > 0 do begin
  ST := copy(S, 1, pos(',', S) - 1);
  delete(S, 1, pos(',', S));
  try
   Buf := Buf+chr(StrToInt('$'+ST));
  except
   exit;
  end;
 end;
 if Buf = '' then exit;
 // ��������� ��������
 if Reg.OpenKey(AKey, true) then begin
  // BackUp ���������
  DoAddBackupChangeParam(ARoot, AKey, AParam);
  try
   Reg.Access := KEY_ALL_ACCESS;
   Reg.WriteBinaryData(AParam, Buf[1], length(Buf));
   AddToLog('$AVZ0413 '+AParam+' $AVZ0339 '+ARoot+'\'+AKey);
   Result := true;
  except
  end;
  Reg.CloseKey;
 end;
end;

function TAvzUserScript.AddLineToTxtFile(AFileName, S: string): boolean;
var
 f     : TextFile;
begin
 if AFileName = '' then exit;
 AssignFile(f, AFileName);
 try
  // ���� ���� ���������� - ��������, �� ���������� - ��������
  if FileExists(AFileName) then Append(f)
   else Rewrite(f);
 except
  exit; // ��� ������� ����������� �����, ���� �� ���������� ��������� ���������
 end;
 try
  try
   Writeln(f, S);
   Result := true;
  except end;
 finally
  CloseFile(f); // � ����� ����������� ������� ����
 end;
end;

function TAvzUserScript.OnScriptCallMetodPM(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 Tmp : boolean;
begin
 // ���������-�����������
 if MethodName = 'SETAVZPMSTATUS' then begin
  Tmp := Params[0];
  if AVZDriverRK = nil then exit;
  // ���� ����� ��� ���������� - ����� �� ������ ������, ����� ���������� ����������
  if Tmp = AVZDriverRK.Loaded then begin
   CallGUILink(guiSet, 'MAIN-RefreshInterface', '');
   Result := true;
   exit;
  end;
  if Tmp then
   Result := InstallPMDriver
  else
   Result := UninstallPMDriver(false);
  CallGUILink(guiSet, 'MAIN-RefreshInterface', '');
  exit;
 end;
 // ������ �������� ���������
 if MethodName = 'GETAVZPMSTATUS' then begin
  Result := AVZDriverRK.Loaded;
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodService(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
const
 ServiceKey = 'SYSTEM\CurrentControlSet\Services\';
 function GetServiceImageName(AService : string) : string;
 begin
  Result := '';
  Reg.RootKey := HKEY_LOCAL_MACHINE;
  if Reg.OpenKey(ServiceKey+Trim(Params[0]), false) then begin
   if Reg.ValueExists('ImagePath') then
    Result := NormalProgramFileName(Reg.ReadString('ImagePath'), '.sys');
   Reg.CloseKey;
  end;
 end;
var
 S : string;
 ServiceManager : TServiceManager;
begin
 try
   // ��������, ���������� �� ����� ������
   if MethodName = 'SERVICEEXISTS' then begin
    Reg.RootKey := HKEY_LOCAL_MACHINE;
    Result := Reg.KeyExists(ServiceKey+Trim(Params[0]));
    exit;
   end;
   // �������� ������� ������� � �����
   if MethodName = 'SERVICEANDFILEEXISTS' then begin
    Result := false;
    S := GetServiceImageName(Params[0]);
    if S <> '' then
      Result := FileExists(S) or
                FileExists(S);
    exit;
   end;
   // ��������� ����� �������
   if MethodName = 'GETSERVICEFILE' then begin
    Result := GetServiceImageName(Params[0]);
    exit;
   end;
   // �������� �������
   if MethodName = 'DELETESERVICE' then begin
    Result := false;
    AddToLog('$AVZ1079: '+Params[0]);
    S := GetServiceImageName(Params[0]);
    Reg.RootKey := HKEY_LOCAL_MACHINE;
    Reg.Access := KEY_ALL_ACCESS;
    Result := Reg.DeleteKey(ServiceKey+Trim(Params[1]));
    if (S <> '') and Params[1] then begin
     AddToLog('$AVZ1081:'+S);
     AVZDeleteFile(S);
    end;
    exit;
   end;
   // ������ �������
   if MethodName = 'STARTSERVICE' then begin
    ServiceManager := TServiceManager.Create;
    Result := ServiceManager.StartService(Trim(Params[0]));
    ServiceManager.Free;
    exit;
   end;
   // ������� �������
   if MethodName = 'STOPSERVICE' then begin
    ServiceManager := TServiceManager.Create;
    Result := ServiceManager.StopService(Trim(Params[0]));
    ServiceManager.Free;
    exit;
   end;
   // ������ ���� Start �������/��������
   if MethodName = 'GETSERVICESTART' then begin
    ServiceManager := TServiceManager.Create;
    Result := ServiceManager.GetServiceStart(Trim(Params[0]));
    ServiceManager.Free;
    exit;
   end;
   // ������ ���� Start �������/��������
   if MethodName = 'GETSERVICENAME' then begin
    ServiceManager := TServiceManager.Create;
    Result := ServiceManager.GetServiceName(Trim(Params[0]));
    ServiceManager.Free;
    exit;
   end;
   // ��������� ���� Start �������/��������
   if MethodName = 'SETSERVICESTART' then begin
    ServiceManager := TServiceManager.Create;
    Result := ServiceManager.SetServiceStart(Trim(Params[0]), Params[1]);
    ServiceManager.Free;
    exit;
   end;
   AddToLog('$AVZ0630 [2, '+MethodName+']');
 except
  Result := false;
 end;
end;

function TAvzUserScript.OnScriptCallMetodRepair(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 AvzUserScript : TAvzUserScript;
 Script        : integer;
begin
 Result := false;
 AvzUserScript := nil;
 if MethodName = 'EXECUTEREPAIR' then begin
  try
   Script := Params[0];
   SystemRepair.LoadBinDatabase;
   if Script <= 0 then exit;
   if Script > Length(SystemRepair.RepairScripts) then exit;
   AvzUserScript := TAvzUserScript.Create;
   try
    Result := AvzUserScript.ExecuteScript('', DeCompressString(SystemRepair.RepairScripts[Script-1].CompressedText), '');
   finally
    AvzUserScript.Free;
   end;
  except
  end;
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodStdScr(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 AvzUserScript : TAvzUserScript;
 Script        : integer;
begin
 Result := false;
 AvzUserScript := nil;
 if MethodName = 'EXECUTESTDSCR' then begin
  try
   Script := Params[0];
   Result := StdScripts.LoadBinDatabase;
   if Script <= 0 then exit;
   if Script > Length(StdScripts.Scripts) then exit;
   AvzUserScript := TAvzUserScript.Create;
   try
    Result := AvzUserScript.ExecuteScript('', DeCompressString(StdScripts.Scripts[Script-1].CompressedText), '');
   finally
    AvzUserScript.Free;
   end;
  except
  end;
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodBC(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
begin
 Result := false;
 // ���������
 if MethodName = 'BC_ACTIVATE' then begin
  AVZDriverBC.UnInstallDriver;
  Result := AVZDriverBC.InstallDriver(BC_Files, BC_Keys, BC_SvcReg, BC_Svc, BC_DisableSvc, BC_QrFiles, BC_QrSvc, BC_CpFiles, BC_log);
  exit;
 end;
 // �����������
 if MethodName = 'BC_DEACTIVATE' then begin
  Result := AVZDriverBC.UnInstallDriver;
  exit;
 end;
 // �����������
 if MethodName = 'BC_EXECUTE' then begin
  AVZDriverBC.UnInstallDriver;
  Result := AVZDriverBC.InstallDriver(BC_Files, BC_Keys, BC_SvcReg, BC_Svc, BC_DisableSvc, BC_QrFiles, BC_QrSvc, BC_CpFiles, BC_log);
  AVZDriverBC.LoadDriver;
  AVZDriverBC.UnInstallDriver;
  exit;
 end;
 // ������� �������
 if MethodName = 'BC_CLEAR' then begin
  BC_Files.Clear;
  BC_Keys.Clear;
  BC_Svc.Clear;
  BC_SvcReg.Clear;
  BC_DisableSvc.Clear;
  BC_QrFiles.Clear;
  BC_CpFiles.Clear;
  BC_QrSvc.Clear;
  BC_log := '';
  Result := true;
  exit;
 end;
 // ��������� ����������������
 if MethodName = 'BC_LOGFILE' then begin
  BC_log := Params[0];
  Result := true;
  exit;
 end;
 // �������� �����
 if MethodName = 'BC_QRFILE' then begin
  BC_QrFiles.Add(ExpandFileNameEx(NTFileNameToNormalName(ReplaceMacrosStr((Params[0])))));
  Result := true;
  exit;
 end;
 // �������� �����
 if MethodName = 'BC_QRSVC' then begin
  BC_QrSvc.Add(Params[0]);
  Result := true;
  exit;
 end;
 // �������� �����
 if MethodName = 'BC_DELETEFILE' then begin
  BC_Files.Add(ExpandFileNameEx(NTFileNameToNormalName(ReplaceMacrosStr((Params[0])))));
  Result := true;
  exit;
 end;
 // ����������� �����
 if MethodName = 'BC_COPYFILE' then begin
  BC_CpFiles.Add(ExpandFileNameEx(NTFileNameToNormalName(ReplaceMacrosStr((Params[0]))) +
                                  '||'+
                                  NTFileNameToNormalName(ReplaceMacrosStr((Params[1])))));
  Result := true;
  exit;
 end;
 // �������� ����� �������
 if MethodName = 'BC_DELETEREG' then begin
  BC_Keys.Add(Trim(Params[0]));
  Result := true;
  exit;
 end;
 // �������� ������
 if MethodName = 'BC_DELETESVCREG' then begin
  BC_SvcReg.Add(Params[0]);
  Result := true;
  exit;
 end;
 // �������� ������
 if MethodName = 'BC_DELETESVC' then begin
  BC_Svc.Add(Params[0]);
  Result := true;
  exit;
 end;
 // �������� ������
 if MethodName = 'BC_DISABLESVC' then begin
  BC_DisableSvc.Add(Params[0]);
  Result := true;
  exit;
 end;
 // ������ ������ ��������� ������
 if MethodName = 'BC_IMPORTDELETEDLIST' then begin
  BC_Files.Duplicates := dupIgnore;
  BC_Files.AddStrings(DeletedFilesList);
  Result := true;
  exit;
 end;
 // ������ ������ ���������
 if MethodName = 'BC_IMPORTQUARANTINELIST' then begin
  BC_QrFiles.Duplicates := dupIgnore;
  BC_QrFiles.AddStrings(QrFilesList);
  Result := true;
  exit;
 end;
 // ������ ������ ���������
 if MethodName = 'BC_IMPORTALL' then begin
  BC_Files.Duplicates := dupIgnore;
  BC_Files.AddStrings(DeletedFilesList);
  BC_QrFiles.Duplicates := dupIgnore;
  BC_QrFiles.AddStrings(QrFilesList);
  Result := true;
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodHosts(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 Lines : TStringList;
 S : string;
 i : integer;
begin
 // ��������� ����� ����� Hosts
 if MethodName = 'GETHOSTSFILENAME' then begin
  Result := GetHostsFileName;
  exit;
 end;
 // ������� ����� Hosts
 if MethodName = 'CLEARHOSTSFILE' then begin
  Result := false;
  S      := GetHostsFileName;
  if S = '' then exit;
  Lines := TStringList.Create;
  if not(FileExists(S)) then begin
   try
    Lines.Add('# Hosts file, cleared by AVZ');
     Lines.Add('127.0.0.1       localhost');
    Lines.SaveToFile(S);
    Result := true;
   except
   end;
  end else begin
   try
    Lines.LoadFromFile(S);
    i := 0;
    while i < Lines.Count do
     if copy(Trim(Lines[i]), 1, 1) <> '#' then Lines.Delete(i)
      else inc(i);
    Lines.Add('127.0.0.1       localhost');
    Lines.SaveToFile(S);
    Result := true;
   except
   end;
  end;
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodScan(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 FileScanner     : TFileScanner;
 FFileName       : string;
 VirusDescr      : TVirusDescr;
begin
 // �������� �����
 if MethodName = 'CHECKFILE' then begin
  LastCheckTxt := '';
  Result := -1;
  FFileName := NTFileNameToNormalName(ReplaceMacrosStr(Params[0]));
  FileScanner := TFileScanner.Create;
  try
   // �������� �����
   if not(FileScanner.CheckFile(FFileName)) then exit;
   // �������� �� ���� ����������
   if FileSignCheck.CheckFile(FFileName)  = 0 then begin
    Result := 3;
    exit;
   end;
   // �������� �� ���� ���������
   Result := MainAntivirus.CheckFile(FileScanner.PEFileInfo, VirusDescr);
   if not(integer(Result) in [0..2]) then
    Result := -1;
   if integer(Result) in [1..2] then
    LastCheckTxt := VirusDescr.Name;
  finally
   FileScanner.Free;
  end;
  exit;
 end;
 // ������ ���������� �������� �������
 if MethodName = 'GETLASTCHECKTXT' then begin
  Result := LastCheckTxt;
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodRegSearch(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 SearchSample : string;
 GlobalKeyCounter : integer;
 procedure AddFoundKey(ARootKey : HKEY; APath, AValueName, AValue : string);
 begin
  AddToLog('[RegSearch]: '+RootKeyToStr(ARootKey)+'\'+APath+' '+AValueName+'="'+AValue+'"');
 end;
 function ScanRegistryKey(ARootKey : HKEY; APath : string): boolean;
  var
   Reg   : TRegistry;
   Lines : TStrings;
   i, KeyNum : integer;
   S : string;
  begin
   if StopF then exit;
   KeyNum := 0;
   Reg := TRegistry.Create;
   Lines := TStringList.Create;
   Reg.RootKey := ARootKey;
   // ����� � ������ ������
   if (pos(SearchSample, AnsiLowerCase(APath)) > 0) then
    AddFoundKey(ARootKey, APath, '', '');
   // ������������ ������ �������
   if Reg.OpenKey(APath, false) then begin
    Reg.GetKeyNames(Lines);
    for i := 0 to Lines.Count - 1 do
     if Lines[i] <> '' then begin
      ScanRegistryKey(ARootKey, APath + '\'+ Lines[i]);
     end;
    // �������� ��������
    Lines.Clear;
    Reg.GetValueNames(Lines);
    for i := 0 to Lines.Count - 1 do
     if (Reg.GetDataType(Lines[i]) = rdString) or (Reg.GetDataType(Lines[i]) = rdExpandString) then begin
      S := AnsiLowerCase(Reg.ReadString(Lines[i]));
      // ����� � ������ ��������
      if pos(SearchSample, AnsiLowerCase(Lines[i])) > 0 then
       AddFoundKey(ARootKey, APath, Lines[i], '');
      // ����� � ��������
      if pos(SearchSample, S) > 0 then
       AddFoundKey(ARootKey, APath, Lines[i], Reg.ReadString(Lines[i]));
      inc(KeyNum);
      if KeyNum mod $FF = 0 then
       Application.ProcessMessages;
     end;
    inc(GlobalKeyCounter);
    if GlobalKeyCounter mod 10 = 0 then
     Application.ProcessMessages;
    // ������� ����
    Reg.CloseKey;
   end;
   Lines.Free;
   Reg.Free;
  end;
begin
 SearchSample := AnsiLowerCase(Trim(Params[2]));
 GlobalKeyCounter := 0;
 ScanRegistryKey(StrToRootKey(Trim(Params[0])), Trim(Params[1]));
 Result := true;
end;

procedure TAvzUserScript.SetGUILink(const Value: TGUILink);
begin
  FGUILink := Value;
end;

function TAvzUserScript.CallGUILink(OpCode: integer; AMessage,
  AParam: string; var Res: variant): boolean;
begin
 Result := false;
 // ���� ����������� ���, �� ���������� �����
 if not Assigned(FGUILink) then exit;
 AMessage := trim(UpperCase(AMessage));
 Res      := Null;
 // ����� �����������
 Result := FGUILink(Self, OpCode, AMessage, AParam, Res);
end;

function TAvzUserScript.CallGUILink(OpCode: integer; AMessage,
  AParam: string): boolean;
var
 X : variant;
begin
 Result := CallGUILink(OpCode, AMessage, AParam, X);
end;

function TAvzUserScript.OnScriptCallMetodEvGroup(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
begin
 if MethodName = 'ADDEVALARMBYCLSID' then begin
  Result := EvSysFileCheckByCLSID(Params[0], Params[1], Params[2]);
  exit;
 end;
 if MethodName = 'ADDEVALARMBYNAME' then begin
  Result := EvSysFileCheckByName(Params[0], Params[1], Params[2]);
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

procedure TAvzUserScript.SetSetupLink(const Value: TSetupLink);
begin
  FSetupLink := Value;
end;

function TAvzUserScript.DelAutorunByFileName(AFileName: string): boolean;
var
 AM : TAutorunManager;
begin
 Result := false;
 AM := TAutorunManager.Create;
 try
   try
    Result := AM.DeleteFromAutorun(AFileName);
   except
   end;
 finally
  AM.Free;
 end;
end;

function TAvzUserScript.OnScriptCallMetodSM(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
begin
 // ���������� ������ ���� ���������� �������
 if MethodName = 'ADDSYSCHECKMENU' then begin
  SetLength(ExtMenuScripts, Length(ExtMenuScripts)+1);
  ExtMenuScripts[Length(ExtMenuScripts)-1].Name    := Params[0];
  ExtMenuScripts[Length(ExtMenuScripts)-1].CmdText := Params[1];
  ExtMenuScripts[Length(ExtMenuScripts)-1].AddMode := Params[2];
  exit;
 end;
 // ������� ����
 if MethodName = 'CLEARSYSCHECKMENU' then begin
  ExtMenuScripts := nil;
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodEV(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
begin
 // ��������� - ���
 if MethodName = 'EXECUTESYSCHKIPU' then begin
  EvSysCheckIPU(nil);
  exit;
 end;
 // ������������ ��������
 if MethodName = 'EXECUTESYSCHKEV' then begin
  EvSysCheck(nil);
  exit;
 end;
 // ����� ����������� � ���������� DLL
 if MethodName = 'SEARCHKEYLOGGER' then begin
  SearchKeyloggers;
  exit;
 end;
 // ������ ������ � ���������� �������
 if MethodName = 'EXECUTEWIZARD' then begin
  Result := RunWizardScripts(GUILink, Params[0], Params[1], Params[2], Params[3]);
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;


function TAvzUserScript.OnScriptCallMetodProgress(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
begin
 // ******** ���������� ��� ����� �������� � ������� ����������� �������� ���������
 // �������� �������� � ���������
 if MethodName = 'GLOBALPROGRESSADDMAX' then begin
  ZProgressClass.AddProgressMax(Params[0]);
  exit;
 end;
 // �������� ��� � ���������
 if MethodName = 'GLOBALPROGRESSSTEP' then begin
  ZProgressClass.ProgressStep(Params[0]);
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodRegBackup(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 Lines : TStrings;
 S     : string;
 X     : integer;
begin
 // ��������� ����� ����� �������
 if pos('BACKUPREGKEY', MethodName) = 1 then begin
  Result := false;
  if StrToRootKey(Params[0]) > 0 then begin
    Lines := TStringList.Create;
   Lines.Add('REGEDIT4');
   Lines.Add('');
   ExpRegKey(StrToRootKey(Params[0]), Params[1], Lines);
   if Lines.Count > 0 then
   try
    zForceDirectories(GetQuarantineDirName('Backup'));
    X := 0;
    repeat
     S := GetQuarantineDirName('Backup')+Params[2]+'_'+FormatDateTime('YYYYMMDD-HHNNSS', Now);
     if X > 0 then S := S + '_'+FormatFloat('00', X);
     S := S + '.reg';
     inc(X);
    until not FileExists(S);
    Lines.SaveToFile(S);
    Result := true;
   except
   end;
  Lines.Free;
  end;
  exit;
 end;
 // ��������� ����� ��������� ������
 if pos('SAVEBACKUPDATAST', MethodName) = 1 then begin
  Result := false;
  Lines := TStrings(Integer(Params[0]));
  if Lines = nil then exit;
  if not(Lines is TStrings) then exit;
  if Length(Lines.Text) > 0 then
   try
    zForceDirectories(GetQuarantineDirName('Backup'));
    X := 0;
    repeat
     S := GetQuarantineDirName('Backup')+ChangeFileExt(Params[1],'')+'_'+FormatDateTime('YYYYMMDD-HHNNSS', Now);
     if X > 0 then S := S + '_'+FormatFloat('00', X);
     S := S + ExtractFileExt(Params[1]);
     inc(X);
    until not FileExists(S);
    Lines.SaveToFile(S);
    Result := true;
   except
   end;
  exit;
 end;
 // ��������� ����� ��������� ������
 if pos('SAVEBACKUPDATA', MethodName) = 1 then begin
  Result := false;
  Lines := TStringList.Create;
  Lines.Text := Params[0];
  if Length(Params[0]) > 0 then
   try
    zForceDirectories(GetQuarantineDirName('Backup'));
    X := 0;
    repeat
     S := GetQuarantineDirName('Backup')+ChangeFileExt(Params[1],'')+'_'+FormatDateTime('YYYYMMDD-HHNNSS', Now);
     if X > 0 then S := S + '_'+FormatFloat('00', X);
     S := S + ExtractFileExt(Params[1]);
     inc(X);
    until not FileExists(S);
    Lines.SaveToFile(S);
    Result := true;
   except
   end;
  Lines.Free;
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodInfo(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
begin
 // ���������� ���������� ���������
 if MethodName = 'GETENVIRONMENTVARIABLE' then begin
  Result := GetEnvironmentVariable(params[0]);
  exit;
 end;
 // ��������� ������ �������� �������
 if MethodName = 'GETSYSTEMBOOTMODE' then begin
  Result := GetSystemMetrics(SM_CLEANBOOT);
  exit;
 end;
 // ��������� �������� Temp AVZ
 if MethodName = 'GETTEMPDIRECTORYPATH' then begin
  Result := NormalDir(AVZTempDirectoryPath);
  exit;
 end;
 // ��������� ������ ����������� �����
 if MethodName = 'GETSCANPATH' then begin
  Result := CreateScanPathStr;
  exit;
 end;
 // ������ ���-�� ��������������
 if MethodName = 'GETSUSPCOUNT'  then begin
  CallGUILink(guiGet, 'MAIN-PodVirCount', '', Result);
  exit;
 end;
 // ������ ���-�� ���������������
 if MethodName = 'GETDETECTEDCOUNT'  then begin
  CallGUILink(guiGet, 'MAIN-VirCount', '', Result);
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodParam(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 i, poz : integer;
begin
 // ������ ���-�� ���������� ��������� ������
 if MethodName = 'GETPARAMCOUNT'  then begin
  Result := ParamCount;
  exit;
 end;
 // ������ ��������� ��������� ������
 if MethodName = 'GETPARAMSTR'  then begin
  if (Params[0] >= 0) and (Params[0] <= ParamCount) then
   Result := ParamStr(Params[0])
    else Result := '';
  exit;
 end;
 // ������ ��������� ��������� ������ �� �����
 if MethodName = 'GETPARAMBYNAME'  then begin
  Result := '';
  if (Params[0] = '') then  exit;
  for i := 1 to ParamCount do begin
   poz := pos('=', ParamStr(i));
   if poz > 0 then
    if UpperCase(Trim(copy(ParamStr(i), 1, poz-1))) = UpperCase(Trim(Params[0])) then begin
     Result := copy(ParamStr(i), poz+1, maxint);
     exit;
    end;
  end;
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodINI(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 INI : TIniFile;
begin
  INI := nil;
  try
    // ������ ������ �� INI �����
    if MethodName = 'INISTRPARAMREAD'  then begin
     Result := '';
     try
      INI := TIniFile.Create(Params[0]);
      Result := INI.ReadString(Params[1], Params[2], Params[3]);
     except
     end;
     exit;
    end;
    // ������ ������ � INI ����
    if MethodName = 'INISTRPARAMWRITE'  then begin
     Result := false;
     try
      INI := TIniFile.Create(Params[0]);
      INI.WriteString(Params[1], Params[2], Params[3]);
      Result := true;
     except
     end;
     exit;
    end;
    // �������� ������� ������
    if MethodName = 'INISECTIONEXISTS'  then begin
     Result := false;
     try
      INI := TIniFile.Create(Params[0]);
      Result := INI.SectionExists(Params[1]);
     except
     end;
     exit;
    end;
    // �������� ������
    if MethodName = 'INIERASESECTION'  then begin
     Result := false;
     try
      INI := TIniFile.Create(Params[0]);
      Result := INI.SectionExists(Params[1]);
     except
     end;
     exit;
    end;
    // �������� ���������
    if MethodName = 'INIERASEPARAM'  then begin
     Result := false;
     try
      INI := TIniFile.Create(Params[0]);
      Result := INI.ValueExists(Params[1], Params[2]);
     except
     end;
     exit;
    end;
  finally
   INI.Free;
   INI := nil;
  end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.RegKeyEnumKey(ARoot, AKey: string;
  AList: TStrings): boolean;
begin
 AList.Clear;
 Result := false;
 if not(SetRootKeyByName(ARoot)) then exit;
 if trim(AKey) = '' then exit;
 if Reg.OpenKeyReadOnly(AKey) then begin
  try
   Reg.GetKeyNames(AList);
   Result := true;
  except
  end;
  Reg.CloseKey;
 end;
end;

function TAvzUserScript.RegKeyEnumVal(ARoot, AKey: string;
  AList: TStrings): boolean;
begin
 AList.Clear;
 Result := false;
 if not(SetRootKeyByName(ARoot)) then exit;
 if trim(AKey) = '' then exit;
 if Reg.OpenKeyReadOnly(AKey) then begin
  try
   Reg.GetValueNames(AList);
   Result := true;
  except
  end;
  Reg.CloseKey;
 end;
end;

procedure TAvzUserScript.SetBackupEngine(const Value: TZBackupEngine);
begin
  FBackupEngine := Value;
end;

function TAvzUserScript.DoAddBackupChangeParam(ARoot, AKey,
  AParamName: string): boolean;
begin
 Result := false;
 if not(Assigned(FBackupEngine)) then exit;
 Result := FBackupEngine.AddBackupChangeParam(ARoot, AKey, AParamName);
end;

function TAvzUserScript.DoAddBackupDeleteKey(ARoot, AKey: string): boolean;
begin
 Result := false;
 if not(Assigned(FBackupEngine)) then exit;
 Result := FBackupEngine.AddBackupDeleteKey(ARoot, AKey);
end;

function TAvzUserScript.DoAddBackupDeleteParam(ARoot, AKey,
  AParamName: string): boolean;
begin
 Result := false;
 if not(Assigned(FBackupEngine)) then exit;
 Result := FBackupEngine.AddBackupDeleteParam(ARoot, AKey, AParamName);
end;

function TAvzUserScript.OnScriptCallMetodIE(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
begin
 // ������ ���-�� ��������� � ����
 if MethodName = 'GETIECACHEITEMSCOUNT'  then begin
  Result := GetIECacheItemsCount;
  exit;
 end;
 // ������ ���-�� ��������� � ����
 if MethodName = 'CLEARIECACHE'  then begin
  Result := ClearIECache;
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodDFM(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 FDir, FMask, st : string;
 IncludeMackList : TStringList;

 // �������� ����� �� �����
 procedure FDeleteFiles(ADir : string; ARecurseDel, ARootDir : boolean);
 var
  SR  : TSearchRec;
  Res : integer;
 begin
  ADir := NormalDir(ADir);
  Res := FindFirst(ADir+'*.*', faAnyFile, SR);
  while Res = 0 do begin
   if (SR.Name <> '.') and (SR.Name <> '..') then begin
    if ARecurseDel and ((SR.Attr and faDirectory) = faDirectory) then
     FDeleteFiles(ADir+SR.Name, ARecurseDel, false);
    // ��� ����� ������������� ����� �� ����� ?
    if ((SR.Attr and faDirectory) = 0) and MatchesMask(SR.Name, IncludeMackList) then begin
     AVZDeleteFile(ADir + SR.Name);
     DeletedFilesList.Add(ReplaceMacrosStr(Params[0]));
    end;
   end;
   Res := FindNext(SR);
  end;
  FindClose(SR);
  // ������� �������� ������� ��������
  if not(ARootDir) then
   RemoveDirectory(PChar(ADir));
 end;
begin
 // �������� ������ �� �����
 if MethodName = 'DELETEFILEMASK' then begin
  FDir    := Trim(NormalDir(ReplaceMacrosStr(Params[0])));
  FMask   := Trim(Params[1]);
  Result := false;
  if FMask = '' then exit;
  // ���������� ������ �����
  IncludeMackList := TStringList.Create;
  FMask := StringReplace(FMask, ';', ',', [rfReplaceAll]);
  FMask := StringReplace(FMask, '  ', ' ', [rfReplaceAll]);
  FMask := StringReplace(FMask, ' ', ',', [rfReplaceAll]);
  FMask := FMask + ',';
  while pos(',', FMask) > 0 do begin
   st := LowerCase(Trim(copy(FMask, 1, pos(',', FMask)-1)));
   delete(FMask, 1, pos(',', FMask));
   if st <> '' then
    IncludeMackList.Add(st);
  end;
  AddToLog('$AVZ1081:' + FDir + ' '+Trim(Params[1]));
  FDeleteFiles(FDir, Params[2], true);
  IncludeMackList.Clear;
  IncludeMackList.Free;
  Result := true;
  exit;
 end;
 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

function TAvzUserScript.OnScriptCallMetodSC(Instance: TObject;
  ClassType: TClass; const MethodName: String;
  var Params: Variant): Variant;
var
 i : integer;
 s, st : string;
begin
 // �������� ������� � ������� ���������� XML
 if MethodName = 'SC_INIT' then begin
  Result := false;
  CurrentXMLNode := nil;
  // ������������ ����������� ���������� �������
  if XML <> nil then XML.Free;
  XML := nil;
  if (LastSysCheckXML = '') and (Params[0] = '') then exit;
  // �������� ������ ����������
  XML := TXMLParser.Create;
  if Params[0] = '' then
   Result := XML.ParseXML(LastSysCheckXML)
  else begin
   try
    Result := XML.LoadAndParseXML(Params[0]);
   except
    Result := False;
   end;
  end;
  exit;
 end;

 // ���������� ������� � ������������ ������
 if MethodName = 'SC_FREE' then begin
  CurrentXMLNode := nil;
  if XML <> nil then XML.Free;
  XML := nil;
  Result := true;
  exit;
 end;

 // ����� ���� �� �����
 if MethodName = 'SC_SELECTNODE' then begin
  Result := false;
  CurrentXMLNode := nil;
  if XML = nil then exit;
  CurrentXMLNode := XML.SearchToken(Params[0]);
  Result := CurrentXMLNode <> nil;
  exit;
 end;

 // ������ ���-�� ���������
 if MethodName = 'SC_GETITEMSCOUNT' then begin
  Result := -1;
  // ������ - ������� ��������� ������ ��� ������� ���� � �������
  if XML = nil then exit;
  if CurrentXMLNode = nil then exit;
  result := CurrentXMLNode.SubNodes.Count;
  exit;
 end;

 // ������ �������� ���������
 if MethodName = 'SC_GETPARAMVAL' then begin
  Result := Params[2];
  // ������ - ������� ��������� ������ ��� ������� ���� � �������
  if XML = nil then exit;
  if CurrentXMLNode = nil then exit;
  if Params[0] = -1 then begin
   // ������ ��������
   Result := CurrentXMLNode.ReadString(Params[1], Params[2]);
   exit;
  end;
  // ������ - �������� ���������
  if Params[0] < 0 then exit;
  if Params[0] >= CurrentXMLNode.SubNodes.Count then exit;
  try
   // ������ ��������
   Result := CurrentXMLNode.SubNodes[Params[0]].ReadString(Params[1], Params[2]);
  except end;
  exit;
 end;

 // ������ ����� ����
 if MethodName = 'SC_GETTAGNAME' then begin
  Result := '';
  // ������ - ������� ��������� ������ ��� ������� ���� � �������
  if XML = nil then exit;
  if CurrentXMLNode = nil then exit;
  if Params[0] = -1 then begin
   // ������ �����
   Result := CurrentXMLNode.UpperTokenName;
   exit;
  end;
  // ������ - �������� ���������
  if Params[0] < 0 then exit;
  if Params[0] >= CurrentXMLNode.SubNodes.Count then exit;
  try
   // ������ �����
   Result := CurrentXMLNode.SubNodes[Params[0]].UpperTokenName;
  except end;
  exit;
 end;

 // ����� ���� �� ��������
 if MethodName = 'SC_SEARCHITEM' then begin
  Result := -1;
  // ������ - ������� ��������� ������ ��� ������� ���� � �������
  if XML = nil then exit;
  if CurrentXMLNode = nil then exit;
  // ��� � ������ ���� - �������� �����
  if CurrentXMLNode.SubNodes.Count = 0 then exit;
  ST := Trim(AnsiLowerCase(Params[1]));
  for i := 0 to CurrentXMLNode.SubNodes.Count - 1 do begin
   S := Trim(AnsiLowerCase(CurrentXMLNode.SubNodes[i].ReadString(Params[0], '')));
   // �������� �� ������ ����������
   if Params[2] and (S = ST) then begin
    Result := i;
    exit;
   end;
   // �������� �� ��������� ����������
   if not(Params[2]) and (pos(ST, S) > 0) then begin
    Result := i;
    exit;
   end;
  end;
  exit;
 end;

 AddToLog('$AVZ0630 [2, '+MethodName+']');
end;

end.

{



begin
 AddToLog(GetEnvironmentVariable('PATH'));
end.

begin
 DeleteFileMask('%Tmp%', '*.*', true);
end.

var
 Res : boolean;
begin
 Res := SC_INIT(GetAVZDirectory + 'LOG\avz_sysinfo.xml');
 if Res then
  AddToLog('�������� � ������� ��$AVZ1304����� ��������� $AVZ1102')
 else begin
  AddToLog('$AVZ0630 �������� � �������� ��$AVZ1304�����');
  exit;
 end;
 if SC_SelectNode('AVZ\KERNELOBJ') then
  AddToLog('��� KERNELOBJ ������')
 else begin
  AddToLog('��� KERNELOBJ �� ������');
  exit;
 end;
 // ������ ���������� ��������� �����
 AddToLog('SC_GetItemsCount = '+inttostr(SC_GetItemsCount));
end.
}

{


begin
 QuarantineFile('C:\autorun.inf','');
 QuarantineFile('D:\autorun.inf','');
 QuarantineFile('F:\autorun.inf','');
 QuarantineFile('C:\WINDOWS\system32\severe.exe','');
 QuarantineFile('C:\WINDOWS\system32\qvkwjh.exe','');
 QuarantineFile('C:\WINDOWS\system32\qvkwjh.dll','');
 QuarantineFile('c:\windows\system32\drivers\conime.exe','');
 DeleteFile('c:\windows\system32\drivers\conime.exe');
 DeleteFile('c:\windows\system32\qvkwjh.exe');
 DeleteFile('c:\windows\system32\severe.exe');
 DeleteFile('C:\WINDOWS\system32\qvkwjh.dll');
 DeleteFile('C:\autorun.inf');
 DeleteFile('D:\autorun.inf');
 DeleteFile('F:\autorun.inf');

 BC_ImportAll;
 BC_Activate;
 ExecuteSysClean;
 ExecuteRepair(16);

end.


}
