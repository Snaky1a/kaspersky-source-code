program avz_db_compile;
// ������� ��� ������ ��� ������.
// ������ �.�., ��������� ����������� 20.09.2007
{$APPTYPE CONSOLE}

uses
  SysUtils, Classes, Windows,
  zAntivirus,
  zStringCompressor,
  zutil;

var
 LogFileName : string = '';  // ��� ����� ��� �������� ���������
 Params      : TStringList;  // ������ ���������� ��������� ������
 DBFile      : string;       // ��� ����� ���� ������
 DBSrcPath   : string;       // ���� � ����� � �����������
 RusLangFile : string;       // ���� � ��������� ����� � ������� ������
 ScrFiles    : TStringList;  // ������ ��������, ����������� � ����

// �������� ������ � �������� � ��������� �����
Function AddToFileLog(s:string):boolean;
var
 f     : TextFile;
begin
 Result := false;
 if LogFileName = '' then exit;
 AssignFile(f, LogFileName);
 try
  // ���� ���� ���������� - ��������, �� ���������� - ��������
  if FileExists(LogFileName) then Append(f)
   else Rewrite(f);
 except
  exit;
 end;
 try
  Writeln(f, DateTimetoStr(Now)+' : '+s); // ����� ������
 finally
  CloseFile(f); // � ����� ����������� ������� ����
 end;
end;

// ����� ������ � �������� � �� �������
procedure AddToLog(S  :string);
begin
 writeln(S);
 AddToFileLog(S);
end;

// ������� ���������� ��������� ������ � ���������� ������ ���������
procedure ParseParams;
var
 i : integer;
begin
 Params.Clear;
 // ���������� ������ ����������
 for i := 1 to ParamCount do
  if pos('=', ParamStr(i)) > 0 then
   Params.Add(ParamStr(i));
 // ��������� ����������
 if Params.Values['LogFile'] <> '' then
  LogFileName := Params.Values['LogFile'];
end;

// �������� ������� ��������
function LoadProfile(AProfileName : string) : boolean;
var
 INI : TStringList;
begin
 DBFile := ''; DBSrcPath   := '';  RusLangFile := '';
 Result := false;
 // ��� ����� ������� �����������
 if AProfileName = '' then exit;
 // ���� �� ������
 if not(FileExists(AProfileName)) then exit;
 // �������� �������
 INI := TStringList.Create;
 INI.LoadFromFile(AProfileName);
 // �������� ��������
 DBFile      := Trim(INI.Values['DBFile']);
 DBSrcPath   := Trim(INI.Values['DBSrcPath']);
 DBSrcPath   := NormalDir(DBSrcPath);
 RusLangFile := Trim(INI.Values['RusLangFile']);
 LogFileName := Trim(INI.Values['LogFile']);
 Result := true;
 INI.Free;
end;

// ���������� �������� ������� ��������
function CheckProfile : boolean;
begin
 Result := false;
 // �������� ����� � ����� � ����
 if not(DirectoryExists(DBSrcPath)) then begin
  AddToLog('DB folder not found. Path="'+DBSrcPath+'"');
  exit;
 end;
 // �������� ������� ����� � ������������
 if not(FileExists(RusLangFile)) then begin
  AddToLog('Russian lang file not found. File name="'+RusLangFile+'"');
  exit;
 end;
 Result := true;
end;

// �������� ������ ������, ���������� � ����
function CreateScriptList : boolean;
var
 SR  : TSearchRec;
 Res : integer;
begin
 Res := FindFirst(DBSrcPath + '*.txt', faAnyFile, SR);
 ScrFiles.Clear;
 while Res = 0 do begin
  // ���������� ����� ���������� �����
  ScrFiles.Add(SR.Name);
  Res := FindNext(SR);
 end;
 SysUtils.FindClose(SR);
 // ���������� ������
 ScrFiles.Sort;
end;

// ������������ ������� - �������� �� ���� ���� ������ �����
function NormalizeScriptSrc(AScript : TStrings) : boolean;
var
 i : integer;
begin
 Result := false;
 i := 1; // ������ ������ (�� ������ 0) �� ������� - ��� ��������� �������
 while i < AScript.Count do begin
  // �������� ������ �����
  if Trim(AScript[i]) = '' then begin
   AScript.Delete(i);
   Continue;
  end;
  // �������� ������������
  if copy(Trim(AScript[i]), 1, 2) = '//' then begin
   AScript.Delete(i);
   Continue;
  end;
  inc(i);
 end;
 Result := true;
end;

// �������� �������
function CheckScript(AScript : TStrings) : boolean;
var
 i : integer;
begin
 Result := false;
 // ������ ������ ��������� ������� ��� ������ (����������� � ������, begin � end.
 if AScript.Count < 3 then begin
  AddToLog('>> Error: empty script = '+ScrFiles[i]);
  exit;
 end;
 Result := true;
end;

// ���������� ����� �������
function ExtractScriptName(AScript : TStrings) : string;
begin
 Result := '';
 // ������ ������ ��������� ������� ��� ������ (����������� � ������, begin � end.
 if AScript.Count = 0 then exit;
 Result := Trim(AScript[0]);
 if pos('//', Result) = 1 then
  Delete(Result, 1, 2)
   else begin
    Result := '';
    exit;
   end;
 AScript.Delete(0);
end;

// ��������� ������ ������� �� �����
function GetScriptNum(AFileName : string) : word;
begin
 Result := $FFFF;
 AFileName := Trim(UpperCase(AFileName));
 // �������� ���������� �����
 if pos('.', AFileName) > 0 then
  Delete(AFileName, pos('.', AFileName), maxint);
 AFileName := Trim(AFileName);
 // �������� ���������� ��������
 while (Length(AFileName) > 0) and (pos(AFileName[1], '0123456789')=0) do
  Delete(AFileName, 1, 1);
 Result := StrToIntDef(AFileName, $FFFF);
end;

// �������� ��������� AVZ �����
function CreateBinScriptsDatabase: boolean;
var
 MS    : TMemoryStream;             // ����� ��� ������ � �������� ������
 i     : integer;
 S, ScriptName : string;
 buf_w  : word;
 BaseHeader : TVirusBaseHeader;     // ��������� ����
 RecCount   : integer;              // ���-�� �������
 ScriptText : TStringList;          // �������� ����� �������
begin
 // ��������� �����
 BaseHeader.Sign[1] := 'A';
 BaseHeader.Sign[2] := 'V';
 BaseHeader.Sign[3] := 'Z';
 // ������
 BaseHeader.MinAvzVersion := 4.27;
 // ���� ������
 BaseHeader.DateTime      := Now;
 Result := false;
 RecCount := 0;
 ScriptText := TStringList.Create;
 try
   // �������� ������ ��� �������������� ������
   MS    := TMemoryStream.Create;
   MS.Write(BaseHeader, sizeof(BaseHeader));
   // ���� ���������
   for i :=0 to ScrFiles.Count - 1 do begin
      // �������� ��������� �������
      ScriptText.LoadFromFile(DBSrcPath + ScrFiles[i]);
      // ������������ �������
      NormalizeScriptSrc(ScriptText);
      // �������� �������
      if not(CheckScript(ScriptText)) then begin
       AddToLog('>>> Invalid script = '+ScrFiles[i]);
       exit;
      end;
      // ���������� ����� �������
      ScriptName := ExtractScriptName(ScriptText);
      if ScriptName = '' then begin
       AddToLog('>>> Script name not found = '+ScrFiles[i]);
       exit;
      end;
      // ���������� ������ �������
      buf_w := GetScriptNum(ScrFiles[i]);
      MS.Write(buf_w, 2);
      // ���������� ����� �������
      S := CompressString(ScriptName);
      buf_w := length(S);
      MS.Write(buf_w, 2);
      MS.Write(S[1], buf_w);
      // ���������� �������
      S := CompressString(Trim(ScriptText.Text));
      buf_w := length(S);
      MS.Write(buf_w, 2);
      MS.Write(S[1], buf_w);
      // ��������
      AddToLog('Script add to DB: '+ScrFiles[i]);
      inc(RecCount);
   end;
   // ���������� ����� ���������
   BaseHeader.RecCount := RecCount;
   // ��������� ���������� �����, ������������ � �������� �����
   Randomize;
   // ��������� ����� � ����
   BaseHeader.code_num := Random(254)+1;
   // ��������� �� ��������� ����������� ���� ���������� - � ���� ������������ ���� ������
   BaseHeader.NextHeaderPtr := 0;
   // ������ ��������� � ������ �����
   MS.Seek(0,0);
   MS.Write(BaseHeader, sizeof(BaseHeader));
   // ������� �������� (��� 4 - ����� ����� �������� ��� ��) � ���������� CRC
   CodeBinData(MS, 4);
   MS.Seek(0,0);
   // ���������� ������ � ����
   MS.SaveToFile(DBFile);
   Result := true;
   MS.Free;
 finally
  ScriptText.free;
  AddToLog('DB creation complete. ScriptCount = '+IntToStr(RecCount))
 end;
end;

begin
 AddToLog('AVZ Script DB compilator. v1.01');
 Params := TStringList.Create;
 // ������� ����������
 ParseParams;
 // ���� ���������� ���, �� �����
 if Params.Count = 0 then begin
  AddToLog('Params not found. Run avz_db_compile.exe profile=<full profile file name>');
  exit;
 end;
 // �������� ������� ��������
 if not(LoadProfile(Params.Values['Profile'])) then begin
  AddToLog('Profile load error');
  exit;
 end;
 // �������� ����������, ����������� � �������
 if not(CheckProfile) then begin
  AddToLog('Profile data error');
  exit;
 end;
 // �������� ������ ������, ���������� � ����
 ScrFiles  := TStringList.Create;
 // �������� ������ ��������
 CreateScriptList;
 // ��������, ������ �� ���� ���� ������
 if ScrFiles.Count = 0 then begin
  AddToLog('Scripts not found ! DB path = '+DBSrcPath);
  exit;
 end;
 AddToLog('AVZ Script DB compilator. v1.01 - Compilation started ...');
 // �������� ���� ������ ������� AVZ
 if CreateBinScriptsDatabase then
  AddToLog('Compilation sucessefully complete')
   else AddToLog('Compilation ERROR !!');
end.

