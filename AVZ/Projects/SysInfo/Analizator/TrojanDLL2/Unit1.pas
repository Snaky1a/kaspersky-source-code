unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Spin, Mask, ToolEdit;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Label1: TLabel;
    SpinEdit1: TSpinEdit;
    FilenameEdit1: TFilenameEdit;
    Button2: TButton;
    Button3: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    function MonitoringRun(AFileName: string): boolean;
    { Private declarations }
  public
   procedure AddToLog(S : string);
   Function InjectDLLtoProcess(APID : dword; ADllName : string) : boolean;
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

{ TForm1 }

function TForm1.InjectDLLtoProcess(APID: dword; ADllName: string): boolean;
var
 hProcess       : THandle; // Handle ��������
 hRemoteThread  : THandle; // Handle ���������� ������
 NameBufPtr     : Pointer; // ����� ������ � ������ DLL
 LoadLibraryPtr : Pointer; // ����� ������� LoadLibrary
 NumberOfBytesWritten, ThreadId : dword;
begin
 Result := false;
 hProcess := 0; hRemoteThread := 0; NameBufPtr := nil;
 try
  // 1. ��������� �������
  hProcess := OpenProcess(PROCESS_ALL_ACCESS, FALSE, APID);
  if hProcess = 0 then begin
   AddToLog('������ �������� ��������');
   exit;
  end;
  // 2. ������� � ������ �������� ����� ��� ����� DLL
  NameBufPtr := VirtualAllocEx(hProcess, nil, Length(ADllName)+1, MEM_COMMIT, PAGE_READWRITE);
  if NameBufPtr = nil then begin
   AddToLog('������ ��������� ������ � ������ ��������');
   exit;
  end;
  // 3. �������� ��� � �����
  if not(WriteProcessMemory(hProcess, NameBufPtr, PChar(ADllName), Length(ADllName)+1, NumberOfBytesWritten)) then begin
   AddToLog('������ ������ � ������ ��������');
   exit;
  end;
  // 4. ��������� ����������� ������ kernel32.dll!LoadLibraryA
  LoadLibraryPtr := GetProcAddress(GetModuleHandle('kernel32.dll'), 'LoadLibraryA');
  if LoadLibraryPtr = nil then begin
   AddToLog('������ ����������� ������ LoadLibraryA');
   exit;
  end;
  // 5. ��������� �������� ���������� ������
  hRemoteThread := CreateRemoteThread(hProcess, 0, 0,
                               LoadLibraryPtr, NameBufPtr, 0, ThreadId);
  if hRemoteThread <> 0 then begin
   // 6. ���������� ���������� ������ (���� 5 ������)
   WaitForSingleObject(hRemoteThread, 5000);
   Result := true;
  end else
   AddToLog('������ �������� ���������� ������');
 finally
  // ������������ ������ � �������� Handle ������ � ��������
  if NameBufPtr <> nil then
   VirtualFreeEx(hProcess, NameBufPtr, 0, MEM_RELEASE);
  if hRemoteThread <> 0 then
   CloseHandle(hRemoteThread);
  if hProcess <> 0 then
   CloseHandle(hProcess);
 end;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
 InjectDLLtoProcess(SpinEdit1.Value, extractfilepath(application.exename)+'..\zsa.dll');
end;

procedure TForm1.AddToLog(S: string);
begin
 ;
end;

Function TForm1.MonitoringRun(AFileName : string) : boolean;
var
  si : Tstartupinfo;
  p  : Tprocessinformation;
begin
 FillChar( Si, SizeOf( Si ) , 0 );
 with Si do begin
  cb := SizeOf( Si);
  dwFlags := startf_UseShowWindow;
  wShowWindow := 4;
 end;
 // �������� ��������
 CreateProcess(nil,PChar(AFilename),
               nil,nil,false,Create_default_error_mode or CREATE_SUSPENDED,nil,nil,si,p);
 InjectDLLtoProcess(p.dwProcessId, extractfilepath(application.exename)+'zsa.dll');
 // ������ ��������
 ResumeThread(p.hThread);
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
 MonitoringRun(FilenameEdit1.FileName);
end;

// �������� ������ � ����������� �����
Function DebugOutput(s:string):boolean;
var
 f     : TextFile;
 FName : String;
begin
 // ���� ����� ������� ��������, �� �����
 Result := false;
 FName := ChangeFileEXT(Application.ExeName,'.log');
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

procedure TForm1.Button3Click(Sender: TObject);
var
 SR : TSearchRec;
 res : integer;
 Cnt : integer;
begin
 res := FindFirst('test\*.*', faAnyFile, SR);
 Cnt := 0;
 while res = 0 do begin
  Application.ProcessMessages;
  try
  if (SR.Attr and faDirectory) = 0 then begin
   Application.ProcessMessages;
   try
    DebugOutput('Test '+ExtractFilePath(Application.ExeName)+'test\'+SR.Name);
    MonitoringRun(ExtractFilePath(Application.ExeName)+'test\'+SR.Name);
   except
   end;
   Application.ProcessMessages;
   inc(cnt);
   Application.ProcessMessages;
   Caption := IntToStr(cnt)+' '+SR.Name;
   Application.ProcessMessages;
   Repaint;
   Application.ProcessMessages;
   Application.ProcessMessages;
   Refresh;
   Application.ProcessMessages;
   Application.ProcessMessages;
  end;
  except end;
  Res := FindNext(SR);
  Application.ProcessMessages;
 end;
 FindClose(SR);
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
 if ParamCount > 0 then
  FilenameEdit1.Text := ParamStr(1); 
end;

end.
