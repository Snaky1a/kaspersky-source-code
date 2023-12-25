unit zHostsFile;

interface
uses
  Windows, Messages, SysUtils, Classes, ActiveX, MsTask, MsTaskUtils,
  RxVerInf, AuxProcs, zSharedFunctions, registry;
type
 // ���������� ������ ����� Hosts
 THostsFileRec = record
  IsComment : boolean;  // ������� ����, ��� ��� ������ �������� ������������
  Str       : string;   // ������ ����� Hosts
  Field1    : string;   // ���� 1 - IP �����
  Field2    : string;   // ���� 2 - ���
 end;

 // ������ �������
 THostsFileRecArray = array of THostsFileRec;

 // ����� ��� ������� ����� Hosts
 THostsFile = class
  HostsFileRecArray : THostsFileRecArray;
  FileName          : string;
  constructor Create;
  destructor Destroy; override;
  // �������� �����
  Function LoadHostFile : boolean;
  // ���������� �����
  Function SaveHostFile : boolean;
  function DeleteItem(AIndex : integer): boolean;
 end;

implementation
uses ntdll;
{ THostsFile }

constructor THostsFile.Create;
begin
 HostsFileRecArray := nil;
 if FileName = '' then
  FileName := GetHostsFileName;
end;

function THostsFile.DeleteItem(AIndex: integer): boolean;
var
 i : integer;
begin
 if AIndex < 0 then exit;
 if AIndex > Length(HostsFileRecArray) then exit;
 for i := AIndex to Length(HostsFileRecArray) - 2 do
  HostsFileRecArray[i] := HostsFileRecArray[i+1];
 SetLength(HostsFileRecArray, Length(HostsFileRecArray) - 1);
end;

destructor THostsFile.Destroy;
begin
 HostsFileRecArray := nil;
 inherited;
end;

function THostsFile.LoadHostFile: boolean;
var
 Lines : TStringList;
 i     : integer;
 S     : string;
begin
 Result := false;
 HostsFileRecArray := nil;
 Lines := TStringList.Create;
 try Lines.LoadFromFile(FileName); except end;
 SetLength(HostsFileRecArray, Lines.Count);
 for i := 0 to Lines.Count - 1 do begin
  HostsFileRecArray[i].Str := Lines[i];
  HostsFileRecArray[i].Field1 := '';
  HostsFileRecArray[i].Field2 := '';
  HostsFileRecArray[i].IsComment := copy(Trim(Lines[i]), 1, 1) = '#';
  if not(HostsFileRecArray[i].IsComment) then begin
   S := AnsiLowerCase(Trim(Lines[i]));
   S := StringReplace(S, #9, ' ', [rfReplaceAll]);
   // ��������� �����
   if pos(' ', S) > 0 then begin
    // ��������� ���� 1 (IP)
    HostsFileRecArray[i].Field1 := Trim(copy(S, 1, pos(' ', S)));
    // ��������� ���� 2 (��� �����)
    HostsFileRecArray[i].Field2 := Trim(copy(S, pos(' ', S), maxint));
    // �������� ������������ ����� ������
    if pos('#', HostsFileRecArray[i].Field2) > 0 then begin
     Delete(HostsFileRecArray[i].Field2, pos('#', HostsFileRecArray[i].Field2), maxint);
     HostsFileRecArray[i].Field2 := Trim(HostsFileRecArray[i].Field2);
    end;
    // �������� - ������� ����������� ������ ������������
    if (HostsFileRecArray[i].Field1 = '') or (HostsFileRecArray[i].Field2 = '') then
     HostsFileRecArray[i].IsComment := true;
   end;
  end;
 end;
 Lines.Free;
 Result := true;
end;

function THostsFile.SaveHostFile: boolean;
var
 Lines : TStringList;
 i     : integer;
begin
 Result := false;
 Lines := TStringList.Create;
 for i := 0 to Length(HostsFileRecArray) - 1 do begin
  if HostsFileRecArray[i].IsComment then
   Lines.Add(HostsFileRecArray[i].Str) else
    Lines.Add(HostsFileRecArray[i].Field1 + ' '+HostsFileRecArray[i].Field2)
 end;
 try
  SetFileAttributes(PChar(FileName), faArchive);
  Lines.SaveToFile(FileName);
  SetFileAttributes(PChar(FileName), faArchive or faReadOnly);
  Result := true;
 except
 end;
 Lines.Free;
end;

end.
