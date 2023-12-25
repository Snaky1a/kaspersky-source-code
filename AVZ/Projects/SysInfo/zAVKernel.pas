unit zAVKernel;

interface
uses
  Types,
  Classes,
  SysUtils,
  Windows,
  zAVZArcKernel,
  // ������ ����� � ����������
  zAVZDriver,  zAVZDriverN,  zAVZDriverRK,  zAVZDriverBC,
  WIZARDNN,
  zAntivirus,
  zVirFileList,
  zESScripting,
  zLogSystem,
  zXMLLogger;

threadvar
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
 // ������� Backup
 BackupScripts : TBackupScripts;
 // ���� ���� kernel-mode
 KMBase       : TKMBase;
 // �������
 AVZDriver     : TAVZDriver;
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
 // XML ������ ��� ���-������, ���������� � ���� ������������ �������
 XMLLogger   : TXMLLogger;
 // Boot Cleaner
 AVZDriverBC : TAVZDriverBC;

var
 // �����, � ������� ��������� ����
 AVPath : string;
 // �����, � ������� �������� ��������
 QuarantineBaseFolder : string;
 // ������� ����, ��� AVZ �������� �� ����
 NetWorkMode : boolean = false;
 // ������� ����, ��� ��������� ������������
 RebootNeed : boolean;
 DeletedVirusList  : TStrings;
 // �����, � ������� ����������� ��������� �����
 AVZTempDirectoryPath : string;
 // ����� ���������� ����� ��� KAV
 KAVQuarantineMode : boolean = false;

 // ������������� ����
function InitAVKernel(ALangId : string; AKavMode : byte = 0) : boolean;
// ��������� ���� � ����� ���������
function GetQuarantineDirName(ASubFolder : string; ABaseFolder : boolean = false) : string;

implementation
uses zutil, zTranslate;

function InitAVKernel(ALangId : string; AKavMode : byte = 0) : boolean;
begin
 Result := false;
 ALangId := Trim(UpperCase(ALangId));
 KMBase   := nil;
 // �������� ������ "���������"
 MainAntivirus   := TAntivirus.Create(AVPath);//#DNL
 // ������� �������� ��������
 FileSignCheck   := TFileSignCheck.Create(AVPath);  //#DNL
 // �������� �������� ��������������
 WizardNeuralNetwork := TWizardNeuralNetwork.Create;

 // ����� 0 - �������� ������� �� ���� AVZ
 if AKavMode = 0 then begin
  // ������������� ��������� ���������
  KMBase   := TKMBase.Create(AVPath);//#DNL
  KMBase.LoadBinDatabase;
  // �������� ������ ��� ���������� ���������
  AVZDriver     := TAVZDriver.Create;
  AVZDriver.KMBase := KMBase;
  AVZDriver.DriverPath := GetSystemDirectoryPath+'Drivers\';

  // ��������� AVZDriverSG
  AVZDriverSG.KMBase := KMBase;
  AVZDriverSG.DriverPath := GetSystemDirectoryPath+'Drivers\';

  // ������� ������������ �����������
  AVZDriverRK := TAVZDriverRK.Create;
  AVZDriverRK.KMBase := KMBase;
  AVZDriverRK.DriverPath := AVZDriverSG.DriverPath;

  // ������� Boot Cleaner
  AVZDriverBC := TAVZDriverBC.Create;
  AVZDriverBC.KMBase := KMBase;
  AVZDriverBC.DriverPath := AVZDriverSG.DriverPath;
 end;

 // ����� 1 - ������� KIS
 if AKavMode = 1 then begin
  // ������������� ��������� ��������� (� ��� ��� ��� - ��������)
  KMBase   := nil;
  // �������� ������ ��� ���������� ���������
  AVZDriver     := TAVZDriverKIS.Create;
  AVZDriver.KMBase := nil;

  // ��������� AVZDriverSG
  AVZDriverSG.KMBase := nil;
  AVZDriverSG.DriverPath := '-';

  // ������� Boot Cleaner
  AVZDriverBC := TAVZDriverBCKIS.Create;
  AVZDriverBC.KMBase := nil;
  AVZDriverBC.DriverPath := '-';
 end;

 ESUserScript  := TESUserScript.Create;

 // �������� �������� ����������
 KeyloggerBase := TKeyloggerBase.Create(AVPath);//#DNL
 // �������� �������� �����������
 RootkitBase   := TRootkitBase.Create(AVPath);//#DNL
 // �������� ������ ��� ������ ������������ � ���������� Office
 OfficeMacroBase := TOfficeMacroBase.Create(AVPath);//#DNL
 // �������� ������ �������� �������
 SystemCheck   := TSystemCheck.Create(AVPath);//#DNL
 // �������� ������ ������ ������������� �����������
 SystemIPU     := TSystemIPU.Create(AVPath);//#DNL
 // ��������� �������������� �������
 SystemRepair  := TSystemRepair.Create(AVPath);//#DNL
 // ���� ������������ ������
 MemScanBase   := TMemScanBase.Create(AVPath);//#DNL
 // ���� ����������� ��������
 StdScripts   := TStdScripts.Create(AVPath);//#DNL
 // ���� �������� backup
 BackupScripts := TBackupScripts.Create(AVPath);//#DNL

 // �������� ������-�������������
 AVZDecompress := TAVZDecompress.Create(AVPath);//#DNL
 AVZDecompress.LoadBinDatabase;

 // ������������� ��������
 ESSystem    := TESSystem.Create(AVPath);//#DNL
 // ����������
 TranslateSys  := TTranslate.Create(AVPath);//#DNL
 TranslateSys.LoadBinDatabase(ALangId);
 LangCode :=  ALangId;

 // �������� ������ "������ �������"
 VirFileList := TVirFileList.Create;
 DeletedVirusList  := TStringList.Create;

 // �������� XML �������
 XMLLogger   := TXMLLogger.Create;
end;

// ��������� ���� � ����� ���������
function GetQuarantineDirName(ASubFolder : string; ABaseFolder : boolean = false) : string;
var
 Year, Month, Day : word;
 S : string;
 StrSize : dword;
begin
 if KAVQuarantineMode then begin
  if ASubFolder = 'Quarantine' then ASubFolder := 'AVZ_Quarantine' else
  if ASubFolder = 'Infected' then ASubFolder := 'AVZ_Infected' else
  if ASubFolder = 'Backup' then ASubFolder := 'AVZ_Backup';

 end;
 // ������������ �������� ����
 Result := QuarantineBaseFolder + ASubFolder + '\';
 // ���������� � ������� ������ ����� �� � ����
 if NetWorkMode then begin
  SetLength(S, 200);
  StrSize := length(s);
  GetComputerName(PChar(S), StrSize);
  Result := Result + copy(S, 1, StrSize) + '\';
 end;
 // ������������ ������������ ����� (���-�����-����)
 DecodeDate(Now, Year, Month, Day);
 if not(ABaseFolder) then
  Result := Result + IntToStr(Year) + '-' +
            FormatFloat('00', Month) + '-' + FormatFloat('00', Day)+'\';
 Result := NormalDir(Result);
end;


end.
