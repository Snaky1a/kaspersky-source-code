unit uSysCheck;
// ���������� ���� ������������ �������

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, zSharedFunctions, ShellAPI, zHTMLTemplate,
  ExtCtrls, ComCtrls, ZLogSystem, zAVZVersion, zVirFileList;

type
  TSysCheck = class(TForm)
    GroupBox1: TGroupBox;
    cbProcess: TCheckBox;
    cbProcessLib: TCheckBox;
    cbKernelModules: TCheckBox;
    cbAutorun: TCheckBox;
    cbSPI: TCheckBox;
    SaveDialog: TSaveDialog;
    cbService: TCheckBox;
    cbOpenPorts: TCheckBox;
    cbIEExt: TCheckBox;
    cbProcessMode: TComboBox;
    GroupBox2: TGroupBox;
    cbHideGoodFiles: TCheckBox;
    cbAddLastLog: TCheckBox;
    Panel1: TPanel;
    mbStart: TBitBtn;
    cbZipArchive: TCheckBox;
    cbExplorerExt: TCheckBox;
    cbPrintExt: TCheckBox;
    BitBtn1: TBitBtn;
    cbTaskScheduler: TCheckBox;
    ProgressBar: TProgressBar;
    cbHosts: TCheckBox;
    cbProtocols: TCheckBox;
    cbServiceMode: TComboBox;
    cbAddScript: TCheckBox;
    cbDPF: TCheckBox;
    cbCPL: TCheckBox;
    cbAS: TCheckBox;
    cbXMLRep: TCheckBox;
    procedure FormCreate(Sender: TObject);
    procedure mbStartClick(Sender: TObject);
  public
   // ����� ���������� ������ ������ � XML (0-��� � HTML ������, 1-������ ��������, 2-������ �����������)
   XMLHideGoodFilesMode : integer;
   // ���������� � ���������� ������
   Function Execute : boolean;
   // ���������� ������������ ������� (AScriptMode - ������� ����, ��� ������������ �������� ��������)
   Function ExecuteSysCheck(AFileName : string; AScriptMode : boolean) : boolean;
  end;

var
  SysCheck: TSysCheck;

// ����� �� GUI
Function ExecuteSysCheck : boolean;
// ����� �� �������
Function ExecuteSysCheckScript(AFileName : string; ACheckFlags : dword; AAllServices : boolean; ARepParams : dword) : boolean;
implementation

uses uProcessView, uKernelObjectsView, zutil, ntdll, uAutoruns, uSPIView, uServiceView,
  uBHOManager, uExplorerExtManager, uOpenPorts, AbZipper,
  uPrintExtManager, uTaskScheduler, uHostsManager, uProtocolManager,
  uDPFManager, uCPLManager, uActiveSetup, zAVKernel, zAVZkernel, zTranslate;

{$R *.dfm}

// ����� �� GUI
Function ExecuteSysCheck : boolean;
begin
 SysCheck := nil;
 try
  SysCheck := TSysCheck.Create(nil);
  Result := SysCheck.Execute;
 finally
  SysCheck.Free;
  SysCheck := nil;
 end;
end;

// ����� �� �������
Function ExecuteSysCheckScript(AFileName : string; ACheckFlags : dword; AAllServices : boolean; ARepParams : dword) : boolean;
begin
 SysCheck := nil;
 try
  SysCheck := TSysCheck.Create(nil);
  SysCheck.cbZipArchive.Checked := true;
  // ***** ��������� ����������� ����������� *****
  // ��������
  SysCheck.cbProcess.Checked := (ACheckFlags and 1) > 0;
  // DLL
  SysCheck.cbProcessLib.Checked := (ACheckFlags and 2) > 0;
  // ������ � ��������
  SysCheck.cbService.Checked := (ACheckFlags and 4) > 0;
  // ������ ������������ ����
  SysCheck.cbKernelModules.Checked := (ACheckFlags and 8) > 0;
  // ����������
  SysCheck.cbAutorun.Checked := (ACheckFlags and 16) > 0;
  // SPI
  SysCheck.cbSPI.Checked := (ACheckFlags and 32) > 0;
  // �������� �����
  SysCheck.cbOpenPorts.Checked := (ACheckFlags and 64) > 0;
  // ���������� IE
  SysCheck.cbIEExt.Checked := (ACheckFlags and 128) > 0;
  // ���������� Explorer
  SysCheck.cbExplorerExt.Checked := (ACheckFlags and 256) > 0;
  // ���������� ������� ������
  SysCheck.cbPrintExt.Checked := (ACheckFlags and 512) > 0;
  // ������� ������������
  SysCheck.cbTaskScheduler.Checked := (ACheckFlags and 1024) > 0;
  // ���� Hosts
  SysCheck.cbHosts.Checked := (ACheckFlags and 2048) > 0;
  // ����������� ����������
  SysCheck.cbProtocols.Checked := (ACheckFlags and $1000) > 0;
  // DPF
  SysCheck.cbDPF.Checked := (ACheckFlags and $2000) > 0;
  // CPL �����
  SysCheck.cbCPL.Checked := (ACheckFlags and $4000) > 0;
  // Active Setup
  SysCheck.cbAS.Checked := (ACheckFlags and $8000) > 0;
  // ��������� ������ ������ �� �������� � ���������� (������ �������� ��� ���)
  if AAllServices then
   SysCheck.cbServiceMode.ItemIndex := 1;
  // ��������� ������� ������ ��������
  SysCheck.cbHideGoodFiles.Checked := (ARepParams and 1) > 0;
  if (ARepParams and 2) > 0 then
   SysCheck.XMLHideGoodFilesMode := 1;
  if (ARepParams and 4) > 0 then
   SysCheck.XMLHideGoodFilesMode := 2;
  // ��������� �������� ������
  if (ARepParams and 32) > 0 then
   SysCheck.cbZipArchive.Checked := false;
  // ���������� ������������
  SysCheck.ExecuteSysCheck(AFileName, SysCheck.cbAddScript.Checked);
  // �������� ������ (�� ������, ���� ����� �� ��� �� �����)
  if (ARepParams and 8) > 0 then
   DeleteFile(AFileName);
  if (ARepParams and 16) > 0 then
   DeleteFile(ChangeFileExt(AFileName, '.xml'));
 finally
  SysCheck.Free;
  SysCheck := nil;
 end;
end;

// ���������� �������
function TSysCheck.Execute: boolean;
begin
 ShowModal;
 Result := ModalResult = mrOk;
end;

// ���������� ������������
function TSysCheck.ExecuteSysCheck(AFileName: string; AScriptMode : boolean): boolean;
var
 RepLines    : TStringList;
 XMLRepLines : TStringList;
 DLL_Rep_Mode, i : integer;
 ZipArchive : TAbZipper;
 MS, MS1 : TMemoryStream;
 fXMLHideGoodFiles : boolean;
 S, FileInfoStr : string;
 // ���������� ������ � ������ � ���������
 procedure AddRepLine(S : string);
 begin
  RepLines.Add(TranslateStr(S));
 end;
begin
 RepLines := TStringList.Create;
 XMLRepLines := TStringList.Create;
 XMLRepLines.Add('<?xml version="1.0" encoding="windows-1251" ?>');
 XMLRepLines.Add('<!-- AVZ XML Report -->');
 XMLRepLines.Add('<AVZ>');
 RepLines.AddStrings(HTML_StartLines);
 // ����� ���������� ������ � XML
 case XMLHideGoodFilesMode of
  0 : fXMLHideGoodFiles := cbHideGoodFiles.Checked;
  1 : fXMLHideGoodFiles := false;
  2 : fXMLHideGoodFiles := true;
 end;
 // ���������� ������������� ��������
 if AScriptMode then
  RepLines.AddStrings(HTML_Scripts);
 FScriptLogMode := AScriptMode;
 RepLines.AddStrings(HTML_BODYLines);
 AddRepLine(TranslateStr('<H1 align=center>$AVZ0870</H1>'));
 AddRepLine(TranslateStr('<p align=center>AVZ '+VER_NUM+' <a href="http://z-oleg.com/secur/avz/" target=_blank>http://z-oleg.com/secur/avz/</a>'+'</p>'));
 ProgressBar.Position := 0;
 ProgressBar.Position := ProgressBar.Position + 1;
 ProgressBar.Max := 15;
 ZProgressClass.AddProgressMax(ProgressBar.Max * 100);

 // ��������� ���������
 if StopF then exit;
 // �������� � ����������
 Application.ProcessMessages;
 if cbProcess.Checked then
  try
   ProcessView := nil;
   ProcessView := TProcessView.Create(nil);
   ProcessView.CreateProcessList;
   ProgressBar.Position := ProgressBar.Position + 1;
   AddRepLine('<H2 align=center>$AVZ1038</H2>');
   DLL_Rep_Mode := 0;
   if cbProcessLib.Checked then
    case cbProcessMode.ItemIndex of
     0 : DLL_Rep_Mode := 1;
     1 : DLL_Rep_Mode := 2;
    end;
   ProcessView.CreateHTMLProcessLog(RepLines, cbHideGoodFiles.Checked, DLL_Rep_Mode);
   if cbXMLRep.Checked then
    ProcessView.CreateXMLProcessLog(XMLRepLines, fXMLHideGoodFiles);
   ZProgressClass.ProgressStep(100);
  finally
   ProcessView.Free;
   ProcessView := nil;
  end;
 // ��������� ���������
 if StopF then exit;
 // ������ ����
 Application.ProcessMessages;
 if IsNT and cbKernelModules.Checked then
  try
   KernelObjectsView := nil;
   KernelObjectsView := TKernelObjectsView.Create(nil);
   KernelObjectsView.RefreshModuleList;
   AddRepLine('<H2 align=center>$AVZ0430</H2>');
   KernelObjectsView.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked);
   if cbXMLRep.Checked then
    KernelObjectsView.CreateXMLReport(XMLRepLines, fXMLHideGoodFiles);
   ProgressBar.Position := ProgressBar.Position + 1;
   ZProgressClass.ProgressStep(100);
  finally
   KernelObjectsView.Free;
   KernelObjectsView := nil;
  end;
 // ��������� ���������
 if StopF then exit;
 // ������ � ��������
 Application.ProcessMessages;
 if IsNT and cbService.Checked then
  try
   ServiceView := nil;
   ServiceView := TServiceView.Create(nil);
   AddRepLine('<H2 align=center>$AVZ1001</H2>');
   ServiceView.cbServiceMode.ItemIndex := 0;
   case cbServiceMode.ItemIndex of
    0 : ServiceView.cbServiceStatus.ItemIndex := 0;
    1 : ServiceView.cbServiceStatus.ItemIndex := 2;
   end;
   ServiceView.SortKey := -1;
   ServiceView.CreateServiceList;
   ServiceView.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked, false);
   if cbXMLRep.Checked then
    ServiceView.CreateXMLReport(XMLRepLines, fXMLHideGoodFiles);
   AddRepLine('<H2 align=center>$AVZ0237</H2>');
   ServiceView.cbServiceMode.ItemIndex := 1;
   case cbServiceMode.ItemIndex of
    0 : ServiceView.cbServiceStatus.ItemIndex := 0;
    1 : ServiceView.cbServiceStatus.ItemIndex := 2;
   end;
   ServiceView.CreateServiceList;
   ServiceView.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked, true);
   if cbXMLRep.Checked then
    ServiceView.CreateXMLReport(XMLRepLines, fXMLHideGoodFiles);
   ProgressBar.Position := ProgressBar.Position + 1;
   ZProgressClass.ProgressStep(100);
  finally
   ServiceView.Free;
   ServiceView := nil;
  end;
 // ��������� ���������
 if StopF then exit;
 // ����������
 Application.ProcessMessages;
 if cbAutorun.Checked then
  try
   Autoruns := nil;
   Autoruns := TAutoruns.Create(nil);
   Autoruns.RefreshItems(true);
   AddRepLine('<H2 align=center>$AVZ0038</H2>');
   Autoruns.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked);
   if cbXMLRep.Checked then
    Autoruns.CreateXMLReport(XMLRepLines, fXMLHideGoodFiles);
   ProgressBar.Position := ProgressBar.Position + 1;
   ZProgressClass.ProgressStep(100);
  finally
   Autoruns.Free;
   Autoruns := nil;
  end;
 // ��������� ���������
 if StopF then exit;
 // ���������� IE
 Application.ProcessMessages;
 if cbIEExt.Checked then
  try
   BHOManager := nil;
   BHOManager := TBHOManager.Create(nil);
   BHOManager.RefreshBHOList;
   AddRepLine('<H2 align=center>$AVZ0433</H2>');
   BHOManager.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked);
   if cbXMLRep.Checked then
    BHOManager.CreateXMLReport(XMLRepLines, fXMLHideGoodFiles);
   ProgressBar.Position := ProgressBar.Position + 1;
   ZProgressClass.ProgressStep(100);
  finally
   BHOManager.Free;
   BHOManager := nil;
  end;
 // ��������� ���������
 if StopF then exit;
 // ���������� ����������
 Application.ProcessMessages;
 if cbExplorerExt.Checked then
  try
   ExplorerExtManager := nil;
   ExplorerExtManager := TExplorerExtManager.Create(nil);
   ExplorerExtManager.RefreshExplorerExtList;
   AddRepLine('<H2 align=center>$AVZ0434</H2>');
   ExplorerExtManager.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked);
   if cbXMLRep.Checked then
    ExplorerExtManager.CreateXMLReport(XMLRepLines, fXMLHideGoodFiles);
   ProgressBar.Position := ProgressBar.Position + 1;
   ZProgressClass.ProgressStep(100);
  finally
   ExplorerExtManager.Free;
   ExplorerExtManager := nil;
  end;
 // ��������� ���������
 if StopF then exit;
 // ���������� ������
 Application.ProcessMessages;
 if cbPrintExt.Checked then
  try
   PrintExtManager := nil;
   PrintExtManager := TPrintExtManager.Create(nil);
   PrintExtManager.RefreshPrintExtList;
   AddRepLine('<H2 align=center>$AVZ0436</H2>');
   PrintExtManager.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked);
   if cbXMLRep.Checked then
    PrintExtManager.CreateXMLReport(XMLRepLines, fXMLHideGoodFiles);
   ProgressBar.Position := ProgressBar.Position + 1;
   ZProgressClass.ProgressStep(100);
  finally
   PrintExtManager.Free;
   PrintExtManager := nil;
  end;
 // ��������� ���������
 if StopF then exit;
 // ����������� �����
 if cbTaskScheduler.Checked then
  try
   TaskScheduler := nil;
   TaskScheduler := TTaskScheduler.Create(nil);
   TaskScheduler.RefreshTaskSchedulerJobs;
   AddRepLine('<H2 align=center>$AVZ0261</H2>');
   TaskScheduler.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked);
   if cbXMLRep.Checked then
    TaskScheduler.CreateXMLReport(XMLRepLines, fXMLHideGoodFiles);
   ProgressBar.Position := ProgressBar.Position + 1;
   ZProgressClass.ProgressStep(100);
  finally
   TaskScheduler.Free;
   TaskScheduler := nil;
  end;
 // ��������� ���������
 if StopF then exit;
 // SPI
 Application.ProcessMessages;
 if cbSPI.Checked then
  try
   SPIView := nil;
   SPIView := TSPIView.Create(nil);
   SPIView.ResreshLists;
   AddRepLine('<H2 align=center>$AVZ0465</H2>');
   SPIView.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked);
   ProgressBar.Position := ProgressBar.Position + 1;
   ZProgressClass.ProgressStep(100);
  finally
   SPIView.Free;
   SPIView := nil;
  end;
 // ��������� ���������
 if StopF then exit;
 // �����
 Application.ProcessMessages;
 try
 if cbOpenPorts.Checked then
  try
   NetOpenPorts := nil;
   NetOpenPorts := TNetOpenPorts.Create(nil);
   NetOpenPorts.RefresConnections;
   AddRepLine('<H2 align=center>$AVZ0785</H2>');
   ProgressBar.Position := ProgressBar.Position + 1;
   ZProgressClass.ProgressStep(100);
   try
    NetOpenPorts.IPPorts.LoadPortDescr(ExtractFilePath(Application.ExeName)+'Base\ports.avz')
   except end;
   NetOpenPorts.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked);
  finally
   NetOpenPorts.Free;
   NetOpenPorts := nil;
  end;
  except end;
 // ��������� ���������
 if StopF then exit;
 // DPF
 Application.ProcessMessages;
 if cbDPF.Checked then
  try
   DPFManager := nil;
   DPFManager := TDPFManager.Create(nil);
   DPFManager.RefreshDPFList;
   AddRepLine('<H2 align=center>Downloaded Program Files (DPF)</H2>');
   DPFManager.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked);
   if cbXMLRep.Checked then
    DPFManager.CreateXMLReport(XMLRepLines, fXMLHideGoodFiles);
   ProgressBar.Position := ProgressBar.Position + 1;
   ZProgressClass.ProgressStep(100);
  finally
   DPFManager.Free;
   DPFManager := nil;
  end;
 // ��������� ���������
 if StopF then exit;
 // CPL
 Application.ProcessMessages;
 if cbCPL.Checked then
  try
   CPLManager := nil;
   CPLManager := TCPLManager.Create(nil);
   CPLManager.RefreshCPLList;
   AddRepLine('<H2 align=center>$AVZ0067</H2>');
   ProgressBar.Position := ProgressBar.Position + 1;
   CPLManager.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked);
   if cbXMLRep.Checked then
    CPLManager.CreateXMLReport(XMLRepLines, fXMLHideGoodFiles);
   ZProgressClass.ProgressStep(100);
  finally
   CPLManager.Free;
   CPLManager := nil;
  end;
 // ��������� ���������
 if StopF then exit;
  // Active Setup
 Application.ProcessMessages;
 if cbAS.Checked then
  try
   ActiveSetupManager := nil;
   ActiveSetupManager := TActiveSetupManager.Create(nil);
   ActiveSetupManager.RefreshASList;
   ProgressBar.Position := ProgressBar.Position + 1;
   AddRepLine('<H2 align=center>Active Setup</H2>');
   ActiveSetupManager.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked);
   if cbXMLRep.Checked then
    ActiveSetupManager.CreateXMLReport(XMLRepLines, fXMLHideGoodFiles);
   ZProgressClass.ProgressStep(100);
  finally
   ActiveSetupManager.Free;
   ActiveSetupManager := nil;
  end;
 // ��������� ���������
 if StopF then exit;
 // HOSTS
 Application.ProcessMessages;
 if cbHosts.Checked then
  try
   HostsManager := nil;
   HostsManager := THostsManager.Create(nil);
   HostsManager.RefreshInfo;
   AddRepLine('<H2 align=center>$AVZ1111</H2>');
   ProgressBar.Position := ProgressBar.Position + 1;
   HostsManager.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked);
   if cbXMLRep.Checked then
    HostsManager.CreateXMLReport(XMLRepLines, fXMLHideGoodFiles);
   ZProgressClass.ProgressStep(100);
  finally
   HostsManager.Free;
   HostsManager := nil;
  end;
 // ��������� ���������
 if StopF then exit;
 // Protocols
 Application.ProcessMessages;
 if cbProtocols.Checked then
  try
   ProtocolManager := nil;
   ProtocolManager := TProtocolManager.Create(nil);
   ProtocolManager.RefreshList;
   AddRepLine('<H2 align=center>$AVZ0872</H2>');
   ProgressBar.Position := ProgressBar.Position + 1;
   ProtocolManager.CreateHTMLReport(RepLines, cbHideGoodFiles.Checked);
   ZProgressClass.ProgressStep(100);
  finally
   ProtocolManager.Free;
   ProtocolManager := nil;
  end;
 // ��������� ���������
 if StopF then exit;
  // ���������� ������ � ������������� ������
 if cbAddLastLog.Checked then begin
  AddRepLine('<H2 align=center>$AVZ1598</H2>');
  AddRepLine('<TABLE '+HTML_TableFormat1+'>');
  AddRepLine('<TR '+HTMP_TableHeader+'>'+HTML_TableHeaderTD+'$AVZ1109'+HTML_TableHeaderTD+'$AVZ0581'+HTML_TableHeaderTD+'$AVZ1062');
  for i := 0 to VirFileList.VirFileCount - 1 do begin
   FileInfoStr := FormatFileInfo(NTFileNameToNormalName(VirFileList.VirFileList[i].FileName), ', ');
   case VirFileList.VirFileList[i].VirType of
    vrtVirus          : S := '$AVZ0150';
    vrtVirusPartSign  : S := '$AVZ0739';
    vrtVirusEv        : S := '$AVZ0740';
    vrtVirusRootKit   : S := '$AVZ0729';
    vrtKeyLogger      : S := '$AVZ0725';
   end;
   AddRepLine('<TR bgColor='+HTMP_BgColor2+'><TD>'+'<a title="'+FileInfoStr+'" href="">'+HTMLNVL(VirFileList.VirFileList[i].FileName)+'</a>'+ GenScriptTxt(VirFileList.VirFileList[i].FileName)+
                        '<TD>'+S+
                        '<TD>'+VirFileList.VirFileList[i].Descr);
  end;
  AddRepLine('</TABLE>');
  AddRepLine('<BR><HR></B></I>');
  AddRepLine('<PRE>');
  // ������ ��������� � ���������� ����������������
  ZLoggerClass.GetLog(RepLines);
 end;
 if AScriptMode then begin
  AddRepLine('<br>');
  AddRepLine('<b>$AVZ0352</b><form name="ScriptForm"> <textarea rows=10 cols=80 name="CureScript"></textarea></form>');
  AddRepLine('$AVZ0216:<br>'+GenScriptMenu);
  AddRepLine('<b>$AVZ1040</b><form name="FilesForm"> <textarea rows=10 cols=80 name="FileList"></textarea></form>');
 end;
 AddRepLine('</BODY></HTML>');
 // ���������� � �������� ������ � �������������� ������
 if cbXMLRep.Checked then begin
  XMLRepLines.Add(' <SuspFiles>');
  for i := 0 to VirFileList.VirFileCount - 1 do
   if VirFileList.VirFileList[i].VirType <> 1 then
    XMLRepLines.Add('  <ITEM '+
                     'File="'+XMLStr(VirFileList.VirFileList[i].FileName)+'" '+
                     'VirType="'+IntToStr(VirFileList.VirFileList[i].VirType)+'" '+
                     'Descr="'+XMLStr(VirFileList.VirFileList[i].Descr)+'" '+
                     ' />');
  XMLRepLines.Add(' </SuspFiles>');
 end;
 XMLLogger.AddXMLData(XMLRepLines);
 // ���������� ���������
 RepLines.SaveToFile(AFileName);
 // ���������� XML ���������
 XMLRepLines.Add('</AVZ>');
 if cbXMLRep.Checked then
  XMLRepLines.SaveToFile(ChangeFileExt(AFileName, '.xml'));
 // ��������� ��������� �������� XML � ���������� ��� ������������ �������
 LastSysCheckXML := XMLRepLines.Text;
 FScriptLogMode := false;
 // ��������� ���������
 if StopF then exit;
 // �������� ������
 if cbZipArchive.Checked then
  try
   // �������� ������ � ����������
   MS  := TMemoryStream.Create;
   MS1 := TMemoryStream.Create;
   RepLines.SaveToStream(MS);
   XMLRepLines.SaveToStream(MS1);
   // �������� ������
   ZipArchive := TAbZipper.Create(nil);
   DeleteFile(ChangeFileExt(AFileName, '.zip'));
   ZipArchive.FileName := ChangeFileExt(AFileName, '.zip');
   ZipArchive.AddFromStream('avz_sysinfo.htm', MS);
   ZipArchive.AddFromStream('avz_sysinfo.xml', MS1);
   ProgressBar.Position := ProgressBar.Position + 1;
   // �������� ������
   ZipArchive.Save;
   ZipArchive.free;
   MS.Free;
   MS1.Free;
  except
  end;
 RepLines.Free;
 ProgressBar.Position := 0;
end;

procedure TSysCheck.FormCreate(Sender: TObject);
begin
 XMLHideGoodFilesMode := 0;
 cbProcessMode.ItemIndex := 1;
 cbServiceMode.ItemIndex := 0;
 TranslateForm(Self);
end;

procedure TSysCheck.mbStartClick(Sender: TObject);
begin
 StopF := false;
 SaveDialog.FileName := 'avz_sysinfo.htm';
 if not(SaveDialog.Execute and (SaveDialog.FileName <> '')) then exit;
 ExecuteSysCheck(SaveDialog.FileName,  cbAddScript.Checked);
 // ����������� ���������
 ShowHTMLLog(SaveDialog.FileName, true);
end;

end.
