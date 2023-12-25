unit str_serialize;

interface
uses SysUtils, Types;
type
 // �������������� ���� �����
 TZFieldType = (ftByte, ftWord, ftDWORD, ftInteger, ftPChar, ftPWChar, ftNotDefined);
 // �������� ����
 TZFiledDef = record
  FieldName : String;      // ��� ����
  FieldType : TZFieldType; // ��� ������ ����
  DefVal    : variant;     // �������� �� ���������
  Value     : variant;     // ��������
 end;
 // ����� - ���������
 TStr2Bin = class
  FStaticSize : integer;
  FieldDefs : array of TZFiledDef;
  private
    function GetFieldValue(const FieldName: string): Variant;
    procedure SetFieldValue(const AFieldName: string; const Value: Variant);
  public
   constructor Create;
   // ������� ������ ���������� �����
   function ClearFieldDefs : boolean;
   // ���������� ����
   function AddFieldDef(AFieldName : string; AFieldType : TZFieldType; ADefVal : variant) : boolean;
   // ���������� ������������ ������� ������
   procedure CalkStaticDataSize;
   // ��������� ���� ����� �������� �� ���������
   function SetDefFieldsVal : boolean;
   function CalkDynamicDataSize : integer;
   // ������� ������ � ������� � ���������� �����
   function ParseString(AStr : string; ADivStr : string) : boolean;
   // ���������� ������� ������ � ��������� �����
   function AddDataToBuf(Buf : pointer; BufSize : integer; var BytesWritten : integer) : boolean;
   // ���������� ������� ������� ������ � ������
   function CalkDataSize : dword;
   property FieldValues[const FieldName: string]: Variant read GetFieldValue write SetFieldValue; default;
 end;
implementation

// ����������� ������� � ������ �� ����
function GetStaticSizeByType(AFieldType: TZFieldType) : integer;
begin
 Result := 0;
 case AFieldType of
  ftByte   : Result := 1;
  ftWord   : Result := 2;
  ftDWORD, ftInteger  : Result := 4;
  ftPWChar, ftPChar : Result := 4; // 4 ����� - ��������� �� ���� ������
 end;
end;

{ TStr2Bin }
function TStr2Bin.AddDataToBuf(Buf: pointer; BufSize : integer;
  var BytesWritten: integer): boolean;
var
 i : integer;
 DynamicSize, BufDynamicSize : integer;
 StartPtr, DynDataPtr : pointer;
begin
 Result := false;
 BytesWritten := 0;
 // ����� = NIL, �� ��� ������ � ��������
 if Buf = nil then exit;
 // ���� � ����� �� ������ ����������� �����, �� ��� ������ � ��������
 if BufSize < FStaticSize then exit;
 // ���� � ����� �� ������ ����������� + ������������ �����, �� �����
 if BufSize < FStaticSize + CalkDynamicDataSize then exit;
 BufDynamicSize := BufSize - FStaticSize;
 // ���������� ������� � ������
 StartPtr    := Buf;
 DynDataPtr  := Pointer(dword(Buf) + FStaticSize);
 // ��������� ���������
 DWORD(Buf^) := 0;
 // ������� ��������� �� N+1 �������
 Buf := Pointer(dword(Buf) + 4);
 // ���� ��������������
 for i := 0 to Length(FieldDefs) - 1 do begin
  case FieldDefs[i].FieldType of
   ftByte  : begin
              byte(Buf^) := byte(FieldDefs[i].Value);
              Buf := Pointer(dword(Buf) + 1);
             end;
   ftWord  : begin
              Word(Buf^)    := Word(FieldDefs[i].Value);
             end;
   ftDWORD : begin
              DWORD(Buf^)   := DWORD(FieldDefs[i].Value);
             end;
   ftInteger : begin
              LongInt(Buf^) := LongInt(FieldDefs[i].Value);
             end;
   ftPWChar : begin
               DWORD(Buf^) := DWORD(DynDataPtr);
               // ������ ������
               StringToWideChar(FieldDefs[i].Value, DynDataPtr, BufDynamicSize);
               // �������� ��������� �� L*2 + 2 �����
               DynDataPtr := Pointer(DWORD(DynDataPtr) + Length(FieldDefs[i].Value) * 2 + 2);
               dec(BufDynamicSize, Length(FieldDefs[i].Value) * 2 + 2);
              end;
  end;
  // �������� ��������� � ������� ������
  Buf := Pointer(dword(Buf) + GetStaticSizeByType(FieldDefs[i].FieldType));
 end;
 // ���������� ����������� �������
 BytesWritten := DWORD(DynDataPtr) - DWORD(StartPtr);
 Result := true;
end;

function TStr2Bin.AddFieldDef(AFieldName: string; AFieldType: TZFieldType;
  ADefVal: variant): boolean;
begin
 Result := false;
 // ���������� ��������
 SetLength(FieldDefs, Length(FieldDefs) + 1);
 // ���������� �����
 with FieldDefs[Length(FieldDefs) - 1] do begin
  FieldName := Trim(UpperCase(AFieldName));
  FieldType := AFieldType;
  DefVal    := ADefVal;
 end;
 FStaticSize := FStaticSize + GetStaticSizeByType(AFieldType);
 Result := true;
end;

function TStr2Bin.CalkDataSize: dword;
begin
 Result := FStaticSize + CalkDynamicDataSize;
end;

function TStr2Bin.CalkDynamicDataSize: integer;
var
 i : integer;
begin
 Result := 0;
 try
  for i := 0 to Length(FieldDefs) - 1 do
   case FieldDefs[i].FieldType of
    ftPWChar : Result := Result + Length(String(FieldDefs[i].Value)) * 2 + 2;
   end;
 except
 end;
end;

procedure TStr2Bin.CalkStaticDataSize;
var
 i : integer;
begin
 // ����� ������ ���������� ����, ��������� ������ �� N+1 �������
 FStaticSize := 4;
 // ���������� ���������� ������� �����
 for i := 0 to Length(FieldDefs) - 1 do
  FStaticSize := FStaticSize + GetStaticSizeByType(FieldDefs[i].FieldType);
end;

function TStr2Bin.ClearFieldDefs: boolean;
begin
 // ������� ������ �����
 FieldDefs := nil;
 // ����� ������ ���������� ����, ��������� ������ �� N+1 �������
 FStaticSize := 4;
end;

constructor TStr2Bin.Create;
begin
 ClearFieldDefs;
end;

// ������� ������ � ������� � ���������� �����
function TStr2Bin.GetFieldValue(const FieldName: string): Variant;
begin
 ;;
end;

function TStr2Bin.ParseString(AStr: string; ADivStr : string): boolean;
var
 i : integer;
begin
 Result := false;
 // ������� ����� (� ��� ��������� ��������� ��������)
 SetDefFieldsVal;
 AStr := AStr + ADivStr;
 // ���� ��������
 for i := 0 to Length(FieldDefs) - 1 do begin
 end;
 Result := true;
end;

// ��������� ���� ����� �������� �� ���������
function TStr2Bin.SetDefFieldsVal: boolean;
var
 i : integer;
begin
 for i := 0 to Length(FieldDefs) - 1 do
  FieldDefs[i].Value := FieldDefs[i].DefVal;
 Result := true;
end;

procedure TStr2Bin.SetFieldValue(const AFieldName: string;
  const Value: Variant);
var
 i : integer;
 FieldName : string;
begin
 FieldName := Trim(UpperCase(AFieldName));
 for i := 0 to Length(FieldDefs) - 1 do
  if FieldName = FieldDefs[i].FieldName then begin
   FieldDefs[i].Value := Value;
   exit;
  end;
end;

end.
