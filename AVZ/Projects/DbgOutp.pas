unit DbgOutp;
{****************************************************************
 * ������ ����������� ������ (�) ������ �.�., ��� ���. 0-48     * 
 ****************************************************************}
interface
 // �������� ������ � ����������� �����
 Function DebugOutput(s:string):boolean;

var
 DebugMode : boolean = false;

implementation
uses Forms,Sysutils;

// �������� ������ � ����������� �����
Function DebugOutput(s:string):boolean;
var
 f     : TextFile;
 FName : String;
begin
 // ���� ����� ������� ��������, �� �����
 if Not(DebugMode) then
  exit;
 Result := false;
 FName := ChangeFileEXT(Application.ExeName,'.dbg');
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

end.
