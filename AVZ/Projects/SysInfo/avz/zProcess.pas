unit zProcess;

interface
uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, ntdll,
  SystemMonitor;

type
  TProcessFileInfo = record
   ProcessName     : string;  // ���
   PID             : DWord;   // PID ��� hModule
   Size            : DWord;   // ������
   Descr           : string;  // ��������
   LegalCopyright  : string;  // ���������
   MD5             : string;  // ����� MD5
   CheckResult     : integer; // ���������� ��������
   VirResult       : integer; // ��������� �������� �� ���� ����������
   VirName         : string;
   Visible         : integer; // ������� ���������
   FullProcessName : string;  // ������ ��� �����
   FileDateTime    : TDateTime; // ���� � ����� �����
   VisibleLevel    : integer;   // ������� ���������
   Prim            : string;    // ����������
   CmdLine         : string;    // ��������� ������
   EPROCESS        : dword;     // EPROCESS
  end;

  TProcessInfoArray = array of TProcessFileInfo;

  TProcessManager = class
   FSysProcessInfo : TSysProcessInfo;
   public
    FProcessList, FModulesList    : TProcessInfoArray;
    constructor Create;
    // �������� ������ ���������
    Function CreateProcessList : boolean;
    // �������� ������ �������
    Function CreateModuleList(APID : dword) : boolean;
    destructor Destroy; override;
  end;
implementation

{ TProcessManager }

constructor TProcessManager.Create;
begin

end;

function TProcessManager.CreateModuleList(APID: dword): boolean;
begin

end;

function TProcessManager.CreateProcessList: boolean;
begin
 FProcessList        := nil;
 FModulesList        := nil;
 if ISNT then
  FSysProcessInfo := TPSAPIProcessInfo.Create else
   FSysProcessInfo := TToolHelpProcessInfo.Create;
end;

destructor TProcessManager.Destroy;
begin
 FSysProcessInfo.Free;
 FSysProcessInfo := nil;
 FProcessList    := nil;
 FModulesList    := nil;
 inherited;
end;

end.
