unit orautil;
// ��������� OraUtil - ��������� �������, ����������� Oracle ����������������
// (C) ������ �.�.
// ���� ��������� ������ 22.02.2001

interface
Uses Classes,Sysutils,Variants;

// ������ NULL ������ �������
Function NVL(AVal:variant) : variant;overload;
// ������ NULL ��������� ���������
Function NVL(AVal:variant; NullVal  : variant) : variant; overload;
// �������� �� NULL
Function IsNull(AVal:variant):boolean;
// �������� �� �� NULL
Function IsNotNull(AVal:variant):boolean;
// ����������� ����� �������, ��������� �� �����-�����������
Function ModifySQLQuery(const ASQL:TStrings;AKey,ANewStr:string):boolean;
// ���������� ������� � ������ �������
Function AddToList(var AList:string;AItem:string;ADelim:string=','):boolean;
// ��������� ������ ��� ������� �� ����� � �������
Function SplitTableName(ATable : string; var Shema, Table : string) : boolean;

Function IntToStrNVL(AVal:variant; NullVal  : string = '') : string;
Function FloatToStrNVL(AVal:variant; NullVal  : string = '') : string;
Function DateToStrNVL(AVal:variant; NullVal  : string = '') : string;
implementation

// �������� �� NULL
Function IsNull(AVal:variant):boolean;
begin
 Result :=  VarIsNull(AVal) or  VarIsEmpty(AVal);
end;

// �������� �� �� NULL
Function IsNotNull(AVal:variant):boolean;
begin
 Result :=  Not(IsNull(AVal));
end;

// ������ NULL ������ �������
Function NVL(AVal:variant) : variant;
begin
 Result := AVal;
 if VarIsNull(AVal) or VarIsEmpty(AVal) then
  Result := '';
end;

// ������ NULL ��������� ���������
Function NVL(AVal:variant; NullVal  : variant) : variant;
begin
 Result := AVal;
 if VarIsNull(AVal) or VarIsEmpty(AVal) then
  Result := NullVal;
end;

// ����������� ����� �������, ��������� �� �����-�����������
Function ModifySQLQuery(const ASQL:TStrings;AKey,ANewStr:string):boolean;
var
 i : integer;
 Key : string;
begin
 Result := false;
 // ���������� ����� ������
 Key := AnsiUpperCase(Trim(AKey));
 // ��� ������ ����� ������ �� ����
 if AKey='' then exit;
 for i:=0 to ASQL.Count-1 do
  // ����� ?? ���� ��, �� ������
  if Pos(Key,ASQL[i]) > 0 then begin
   ASQL[i] := ANewStr + ' '+ Key;
   Result := true;
  end;
end;

// ���������� ������� � ������ �������
Function AddToList(var AList:string;AItem:string;ADelim:string=','):boolean;
var
 FItem : string;
begin
 Result := false;
 // �������� ������ ��������
 FItem := Trim(AItem);
 // ������ �������� �� ���������
 if FItem='' then exit;
 // ���� ������ �� ������, �� ������� � ���� �����������
 if Trim(AList) <> '' then
  AList := AList + ADelim;
 // ������� �������
 AList := AList + AItem;
 Result := true;
end;

// ��������� ������ ��� ������� �� ����� � �������
Function SplitTableName(ATable : string; var Shema, Table : string) : boolean;
begin
 // ���������� �� ������� �����
 if pos('.', ATable) > 0 then begin
  Shema := copy(ATable, 1, pos('.', ATable)-1);
  Table := copy(ATable, pos('.', ATable)+1, 100);
 end else begin
  Shema := '';
  Table := ATable;
 end;
 Result := true;
end;

Function IntToStrNVL(AVal:variant; NullVal  : string) : string;
begin
 if IsNull(AVal) then
  Result := NullVal
   else Result := IntToStr(AVal);
end;

Function FloatToStrNVL(AVal:variant; NullVal  : string) : string;
begin
 if IsNull(AVal) then
  Result := NullVal
   else Result := FloatToStr(AVal);
end;

Function DateToStrNVL(AVal:variant; NullVal  : string) : string;
begin
 if IsNull(AVal) then
  Result := NullVal
   else Result := DateToStr(AVal);
end;

end.
