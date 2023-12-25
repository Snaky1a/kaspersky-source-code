unit zXMLLogger;
// ����� ��� ����������� � ������������ �������� � XML ���. ����������
interface
uses Windows, Messages, SysUtils, Classes, Forms, ComCtrls;
type
 TXMLLogger = class
  TagList : TStringList;
  constructor Create;
  destructor Destroy; override;
  // �������
  procedure Clear;
  // ���������� �������� � �������
  function AddItem(ATagName, AItemData : string) : boolean;
  // ���������� ������ � ������� ������� �����
  function AddXMLData(ALines : TStringList) : boolean;
  // ������� ������� �� �����
  function ClearByName(ATagName : string) : boolean;
 end;

implementation

{ ZXMLLogger }

function TXMLLogger.AddItem(ATagName, AItemData: string): boolean;
var
 i   : integer;
 Tmp : TStringList;
begin
 Result := false;
 ATagName  := Trim(UpperCase(ATagName));
 AItemData := Trim(AItemData);
 if AItemData = '' then exit;
 Tmp := nil;
 // ���� ������ ����
 for i := 0 to TagList.Count - 1 do
  if ATagName = TagList[i] then begin
   Tmp := (TagList.Objects[i] as TStringList);
   Break;
  end;
 // ��� �� ������ - �������� � ������� ���
 if Tmp = nil then begin
  Tmp := TStringList.Create;
  TagList.AddObject(ATagName, Tmp);
 end;
 Tmp.Add(AItemData);
 Result := true;
end;

function TXMLLogger.AddXMLData(ALines: TStringList): boolean;
var
 i,j : integer;
 Tmp : TStringList;
begin
 // ���� ������ ������
 for i := 0 to TagList.Count - 1 do begin
  Tmp := (TagList.Objects[i] as TStringList);
  ALines.Add(' <'+Trim(UpperCase(TagList[i]))+'>');
  for j := 0 to Tmp.Count - 1 do
   ALines.Add('  '+Tmp[j]);
  ALines.Add(' </'+Trim(UpperCase(TagList[i]))+'>');
 end;
end;

procedure TXMLLogger.Clear;
var
 i : integer;
begin
 // ������� ��������� ����������
 for i := 0 to TagList.Count - 1 do begin
  (TagList.Objects[i] as TStringList).Free;
  TagList.Objects[i] := nil;
 end;
 // ������� ������ �����
 TagList.Clear;
end;

function TXMLLogger.ClearByName(ATagName: string): boolean;
var
 i, indx   : integer;
begin
 Result := false;
 ATagName  := Trim(UpperCase(ATagName));
 indx := 0;
 // ���� ������ ����
 for i := 0 to TagList.Count - 1 do
  if ATagName = TagList[i] then begin
   indx := i;
   Break;
  end;
 // ���� ��� �� ������, �� ������� ������
 if indx = 0 then exit;
 // ������
 (TagList.Objects[indx] as TStringList).Free;
 TagList.Objects[indx] := nil;
 // �������� ��������
 TagList.Delete(indx);
end;

constructor TXMLLogger.Create;
begin
 TagList := TStringList.Create;
end;

destructor TXMLLogger.Destroy;
begin
 Clear;
 TagList.Free;
 inherited;
end;

end.
