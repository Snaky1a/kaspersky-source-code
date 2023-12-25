program qrc;

{$APPTYPE CONSOLE}

uses
  SysUtils,
  INIFiles,
  Classes,
  zutil;

function ProcessDir(ADirName: string; ARecusive : boolean = false): boolean;
var
 SR : TSearchRec;
 Res : integer;
 Path, S, OldName, NewName : string;
 WorkDir : string;
 INI : TIniFile;
 Lines : TStringList;
begin
 Lines := TStringList.Create;
 Path := NormalDir(ADirName);
 Writeln('Scan folder: '+Path);
 // �������������� ������ ��������� AVZ
 Res := FindFirst(Path + '*.ini', faAnyFile, SR);
 while res = 0 do begin
  if FileExists(Path + SR.Name) then begin
   INI := TIniFile.Create(Path + SR.Name);
   S := Trim(INI.ReadString('InfectedFile','Src', ''));
   OldName := ChangeFileExt(Path + SR.Name, '.dta');
   NewName := Path + copy(S, 4, 500);
   ForceDirectories(ExtractFilePath(NewName));
   if RenameFile(OldName, NewName) then begin
    DeleteFile(Path + SR.Name);
    Writeln(' rename "'+OldName+'" --> "'+NewName+'"');
   end;
   INI.Free;
  end;
  Res := FindNext(SR);
 end;
 FindClose(SR);
 // �������������� ������, ���������� � ����� �����
 Res := FindFirst(Path + 'vf*.dta', faAnyFile, SR);
 while res = 0 do begin
  if FileExists(Path + SR.Name) then begin
   WorkDir := NormalDir(Path + ChangeFileExt(ExtractFileName(SR.Name), ''));
   ForceDirectories(WorkDir);
   // ����������� ��������
   RenameFile(ChangeFileExt(Path + SR.Name, '.txt'), WorkDir+ExtractFileName(ChangeFileExt(Path + SR.Name, '.txt')));
   // ����������� �����
   try
    Lines.LoadFromFile(WorkDir+ExtractFileName(ChangeFileExt(Path + SR.Name, '.txt')));
    NewName := Lines.Values['FName'];
    RenameFile(Path + SR.Name, WorkDir+NewName);
    Writeln(' rename "'+Path + SR.Name+'" --> "'+WorkDir+NewName+'"');
   except
   end;
  end;
  Res := FindNext(SR);
 end;
 FindClose(SR);

 // ����������� ������ ��������� ���������
 if ARecusive then begin
   Res := FindFirst(Path + '*.*', faAnyFile, SR);
   while res = 0 do begin
    if (SR.Attr and faDirectory <> 0) and (SR.Name <> '.') and (SR.Name <> '..') then
     ProcessDir(Path + Sr.Name, ARecusive);
    Res := FindNext(SR);
   end;
   FindClose(SR);
 end;  
 Lines.Free;
end;

var
 RecurseF : boolean; // ������� ����, ��� ����� ����������� ���������
begin
 Writeln('AVZ Quarantine files rename tool');
 // �������� ���-�� ���������� � ������������� ��������
 if not(ParamCount in [1,2]) or not(DirectoryExists(ParamStr(1))) then begin
  Writeln('qrc <directory> [/R]');
  Writeln('<directory> - Full path to a folder with files of quarantine');
  Writeln('/R - Recursive processing of folders');
  exit;
 end;
 // ���� "����������� ���������"
 RecurseF := (UpperCase(paramstr(2)) = '/R') or (UpperCase(paramstr(2)) = '\R');
 // ������ ���������
 ProcessDir(ParamStr(1), RecurseF);
end.
