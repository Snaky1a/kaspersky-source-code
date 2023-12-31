unit uAboutDLG;
// ������ "� ���������"
interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms,
  ShellAPI, ExtCtrls, StdCtrls, Buttons, ComCtrls, Grids, ValEdit,
  zAntivirus, zAVKernel, zAVZVersion, zTranslate;

type
  TAboutDLG = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label8: TLabel;
    BitBtn1: TBitBtn;
    Image1: TImage;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    lbLKSite: TLabel;
    Label9: TLabel;
    Label11: TLabel;
    Label10: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Timer1: TTimer;
    Label15: TLabel;
    vlBaseInfo: TValueListEditor;
    lbTranslate: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    procedure Timer1Timer(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Label4Click(Sender: TObject);
    procedure Label5Click(Sender: TObject);
    procedure lbLKSiteClick(Sender: TObject);
    procedure Label11Click(Sender: TObject);
    procedure Label12Click(Sender: TObject);
    procedure Label14Click(Sender: TObject);
    procedure Label15Click(Sender: TObject);
    procedure Label17Click(Sender: TObject);
  private
    { Private declarations }
  public
    ShowTime : integer;
    Function Execute  : boolean;
    Function ExecuteT : boolean;
    procedure RefreshBaseInfo;
  end;

var
  AboutDLG: TAboutDLG;

procedure ExecuteAboutDLG;

implementation
uses unit1;
var
 Time : integer;

{$R *.DFM}

Function TAboutDLG.Execute : boolean;
begin
 RefreshBaseInfo;
 Time:=0;
 Timer1.Enabled:=false;
 ShowModal;
 Timer1.Enabled:=false;
end;

Function TAboutDLG.ExecuteT : boolean;
begin
 Time:=0;
 Timer1.Enabled:=true;
 ShowModal;
 Timer1.Enabled:=false;
end;

procedure TAboutDLG.Timer1Timer(Sender: TObject);
begin
 inc(Time);
 if Time>ShowTime then begin
  ModalResult:=mrOk;
  Time:=0;
 end;
end;

procedure TAboutDLG.FormCreate(Sender: TObject);
begin
 ShowTime:=5;
 Label2.caption :=  TranslateStr(VER_INFO);
 if LangCode = 'EN' then begin
  lbTranslate.Caption := 'English translation by Nick Golovko';
  lbLKSite.Caption := 'http://www.kaspersky.com/';
 end;
 TranslateForm(Self);
end;

procedure TAboutDLG.Label4Click(Sender: TObject);
begin
 ShellExecute(0, nil,'http://z-oleg.com/secur/avz',nil,nil,1);
end;

procedure TAboutDLG.Label5Click(Sender: TObject);
begin
 ShellExecute(0, nil,PChar('mailto:avz@z-oleg.com?subject='+TranslateStr('$AVZ0133')),nil,nil,1);
end;

procedure TAboutDLG.lbLKSiteClick(Sender: TObject);
begin
 if LangCode <> 'RU' then
  ShellExecute(0, nil,'http://www.kaspersky.com/',nil,nil,1)
 else
  ShellExecute(0, nil,'http://www.kaspersky.ru/',nil,nil,1)
end;

procedure ExecuteAboutDLG;
begin
 AboutDLG := nil;
 try
  AboutDLG := TAboutDLG.Create(nil);
  AboutDLG.Execute;
 finally
  AboutDLG.Free;
  AboutDLG := nil;
 end;
end;

procedure TAboutDLG.Label11Click(Sender: TObject);
begin
 ShellExecute(0, nil,PChar('mailto:newvirus@z-oleg.com?subject='+TranslateStr('$AVZ0744')),nil,nil,1);
end;

procedure TAboutDLG.Label12Click(Sender: TObject);
begin
 ShellExecute(0, nil,'http://virusinfo.info/forum.php?referrerid=775',nil,nil,1);
end;

procedure TAboutDLG.Label14Click(Sender: TObject);
begin
 ShellExecute(0, nil,'http://z-oleg.com/secur/avz_doc/',nil,nil,1);
end;

procedure TAboutDLG.Label15Click(Sender: TObject);
begin
 ShellExecute(0, nil,'http://z-oleg.com/secur/avz/uploadvir.php',nil,nil,1);
end;

procedure TAboutDLG.RefreshBaseInfo;
var
 SR  : TSearchRec;
 Res, BytesRead: Integer;
 VirusBaseHeader : TVirusBaseHeader;
 f : file;
 S : string;
begin
 vlBaseInfo.Strings.Clear;
 Res := FindFirst(MainAntivirus.FDatabasePath+'*.avz', faAnyFile, SR);
 while Res = 0 do begin
  try
   AssignFile(F, MainAntivirus.FDatabasePath+SR.Name); reset(f,1);
   BlockRead(f, VirusBaseHeader, SizeOf(VirusBaseHeader), BytesRead);
   S := DateToStr(VirusBaseHeader.DateTime);
   CloseFile(F);
  except
   S := TranslateStr('$AVZ1121');
  end;
  vlBaseInfo.Strings.Add(SR.Name+'='+TranslateStr('$AVZ0206='+S));
  Res := FindNext(SR);
 end;
 FindClose(SR);
end;

procedure TAboutDLG.Label17Click(Sender: TObject);
begin
 ShellExecute(0, nil,'http://www.z-oleg.com/secur/avz/report.php',nil,nil,1);
end;

end.
