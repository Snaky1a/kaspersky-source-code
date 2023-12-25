unit zxml;
// ***************************************************************************
// ***************** ���������� ������� ��� ������ �  XML ********************
// ********************** (C) ������ �.�.,2002 �. ****************************
// ***************************************************************************
interface
 uses classes, Sysutils;
 const
  // �������, ��������� ��������
  SpaceChars : set of char = [' ', #9, #$0D, #$0A];
  // �������, ��������� ���������
  QuoteChars : set of char = ['"', ''''];
  // ������� "������� ������/������� �������"
  CRLF = #$0D#$0A;
  // ������� ������������ ������� � ��� ���� � HTML
  HTMLCodes : array[1..5,1..2] of string = (
          ('&',  '&amp;'),
          ('<',  '&lt;'),
          ('>',  '&gt;'),
          ('"',  '&quot;'),
          ('''', '&apos;'));

 type
  // ���������� ��� ������ �������� ���������
  EXMLParserError = class(Exception)
  end;

  // ��� ���� XML
  TXmlTokenType = (
    xttProcessingInstruction,  // ���������� ��������� <? ... ?>
    xttDocumentType,           // ��� ��������� <!DOCTYPE ... >
    xttComment,                // ����������� <!-- -->
    xttCData,                  // ��������������� ������ <![CDATA[ ... ]]>
    xttEntity,                 // ��������������� ������ <!ENTITY ... ]]>
    xttTag,                    // ������� ���
    xttText                    // ��������� ��������� ������ ����
  );

  TXMLToken = class;
  TXMLParser = class;

  // ������ ������ XML
  TXMLTokenList = class
   protected
    FTokenList : TList;
   private
    function GetCount: integer;
    function GetToken(Index: integer): TXMLToken;
    procedure SetToken(Index: integer; const Value: TXMLToken);
   public
    Constructor Create;
    Destructor  Destroy; override;
    // �������� ���� �����
    Procedure Clear;
    // ���������� ����
    Procedure Add(XMLToken : TXMLToken);
    // �������� �� �������
    Procedure Delete(AIndex    : integer);
    // �������� �� ����
    Procedure DeleteToken(AToken  : TXmlToken);
    // ����� ���� �� �����
    Function  GetTokenByName(AName : string) : TXMLToken;
    // ����������
    procedure Sort(Compare: TListSortCompare);
    // ���-�� �����
    property  Count : integer read GetCount;
    // ������ �����
    property  Tokens[Index : integer] : TXMLToken read GetToken write SetToken; default;
  end;

  // ����� XML
  TXMLToken = class
   private
    FParentToken : TXMLToken;
    FParams     : TStringList;
    FSubNodes   : TXMLTokenList;
    FFTokenType : TXmlTokenType;
    FTokenType  : TXmlTokenType;
    FTokenName: string;
    FText: String;
    procedure SetTokenType(const Value: TXmlTokenType);
    function GetIsEmpty: boolean;
    function GetUpperTokenName: string;
   public
    Constructor Create(AParentToken : TXmlToken; ATokenType : TXmlTokenType; ATagText : string);
    Destructor  Destroy; override;
    // ���������� ����
    Function AddToken(ATokenType : TXmlTokenType; ATagText : string) : TXMLToken;
    // ������ ����������
    Function ParseParams(ATagText : string) : boolean;
    // ��������� ������ = ����� ���� ��������� ���������
    Function GetFullText : String;
    // ������ ����������
    Function ReadString(AName : string;  ADefVal : String)   : String;
    Function ReadInteger(AName : string; ADefVal : integer)  : Integer;
    Function ReadFloat(AName : string;   ADefVal : Double)   : Double;
    Function ReadBool(AName : string;    ADefVal : Boolean)  : Boolean;
    // ������ ����������
    Procedure WriteString(AName : string;  AValue : String);
    Procedure WriteInteger(AName : string; AValue : integer);
    Procedure WriteFloat(AName : string;   AValue : Double);
    Procedure WriteBool(AName : string;    AValue : Boolean);
    // �������� ������������� ���������
    Function ValueExists(AName : string) : boolean;
    // �������� ���������
    Function DeleteParam(AName : string) : boolean;
    //                 **** �������� ****
    // ��� ����
    property TokenName        : string read FTokenName write FTokenName;
    property UpperTokenName   : string read GetUpperTokenName;
    // ��� ����
    property TokenType   : TXmlTokenType read FTokenType write SetTokenType;
    // ������������ ��� (Nil � ���������)
    property ParentToken : TXmlToken read FParentToken;
    // ������ ����������
    property Params   : TStringList read FParams;
    // ������ ����������� �����
    property SubNodes : TXMLTokenList read FSubNodes;
    // ������ ����� ���� ��������� ���������
    property Text     : String read FText write FText;
    // ��������, �������� �� ��� ������
    property IsEmpty  : boolean read GetIsEmpty;
  end;

  // ���������� ���������� ���������
  TXMLDebugHandler = procedure(Sender:TXMLParser; Msg : String) of object;

  // ������ XML ������
  TXMLParser = class
   private
    FXMLText        : String;            // ����� XML
    FXmlTextPoz     : integer;           // ������� ������ XML
    FCurrentXMLNode : TXMLToken;         // ������� ����� XML
    FXMLRootToken   : TXMLToken;         // �������� ����� XML
    FOnXMLDebug     : TXMLDebugHandler;  // ��������� �� �������� XML
    function GetEOF : boolean;
    procedure SkipSpaces;
    procedure SkipChar;
    procedure SkipChars(ACount : integer);
    Function SearchOpenTag : boolean;
    Function SearchCloseTag(ATagEnd : string) : integer;
    Function GetXMLChar(Index: Integer): char;
    Function SaveXMLToken(AXMLToken : TXMLToken; Lines : TStrings; Level : integer) : boolean;
    Function doDebugLog(S : string) : boolean;
    procedure SetOnXMLDebug(const Value: TXMLDebugHandler);
   public
    // ��������
    Constructor Create;
    // �������
    Procedure Clear;
    // �������� � ������� XML
    Function LoadAndParseXML(AXMLFile : String) : boolean;
    // ������� XML
    Function ParseXML(AXMLText : String) : boolean;
    // ���������� ���������� ���� � ������ �����
    Function AddTag(ATokenType : TXmlTokenType;ATagText : String)  : boolean;
    // ���������� ���������� ��������� � ������� ���
    Function AddTagText(ATagText : String) : boolean;
    // ���� ����
    Function SearchToken(ATagName : String) : TXMLToken;
    // ���������� � Strings
    Function SaveToStrings(Lines : TStrings) : boolean;
    // ���������� � ����
    Function SaveToFile(AFileName : string) : boolean;
    // ������� ����� �����
    property EOF : boolean Read GetEOF;
    // ������ XML � �������
    property XMLChar[Index: Integer] : char Read GetXMLChar;
    // ��������� �� �������� �������
    property XMLRootToken : TXMLToken read FXMLRootToken write FXMLRootToken;
    // ���������� ���������� ���������
    property OnXMLDebug : TXMLDebugHandler read FOnXMLDebug write SetOnXMLDebug;
  end;

  // ���������� ����� ���� (�������� / � ������ � ����� �����)
  Function ExtractTagName(ATagText : string) : string;
implementation

// ���������� ����� ����
Function ExtractTagName(ATagText : string) : string;
var
 i : integer;
begin
 // ����� ������� �������, ���������� ��������
 i := 1;
 while (i <= length(ATagText)) and not(ATagText[i] in SpaceChars) do
  inc(i);
 // ��������� ����� ����
 Result := Trim(copy(ATagText, 1, i));
 // �������� ������ �������� / � ������ � ����� �����
 if copy(Result, 1, 1) = '/' then
  delete(Result, 1, 1);
 if copy(Result, length(Result), 1) = '/' then
  delete(Result, length(Result), 1);
end;

// ������� 3 ���� � 4 ������� �� Base64 �����������
Function Code3to4(AValue : string) : ShortString;
begin

end;

{ TXMLParser }
// �����������
constructor TXMLParser.Create;
begin
 // �������� ������
 FCurrentXMLNode := nil;
 FOnXMLDebug     := nil;
end;

// ��������, �������� �� �� ����� ������
function TXMLParser.GetEOF: boolean;
begin
 Result := FXmlTextPoz > Length(FXMLText);
end;

// ����������� ������� XML ���������
function TXMLParser.GetXMLChar(Index: Integer): char;
begin
 if (Index > 0) and (Index < Length(FXMLText)) then
  Result := FXMLText[index]
   else Result := #0;
end;

// ������� ��������
procedure TXMLParser.SkipSpaces;
begin
 while not(EOF) and (FXMLText[FXmlTextPoz] in SpaceChars) do
  inc(FXmlTextPoz);
end;

// ������� ������ �������
procedure TXMLParser.SkipChar;
begin
 if not(EOF) then
  inc(FXmlTextPoz);
end;

// ������� ���������� ��������
procedure TXMLParser.SkipChars(ACount: integer);
begin
 inc(FXmlTextPoz, ACount);
end;

// ����� ������������ ����
function TXMLParser.SearchOpenTag: boolean;
begin
 while not(EOF) and (FXMLText[FXmlTextPoz] <> '<') do
  inc(FXmlTextPoz);
 Result := not(EOF);
end;

// ����� ������������ ����
function TXMLParser.SearchCloseTag(ATagEnd: string): integer;
var
 XMLLength, TagEndLen, poz : integer;
 FirstTagChar : char;
begin
 Result := 0;
 TagEndLen := Length(ATagEnd);
 if TagEndLen = 0 then exit;
 FirstTagChar := ATagEnd[1];
 XMLLength := Length(FXMLText);
 poz       := FXmlTextPoz;
 if ATagEnd = '' then exit;
  while not(poz > XMLLength) do
   if FXMLText[poz] <> FirstTagChar then inc(Poz)
    else
     if copy(FXMLText, Poz, TagEndLen) = ATagEnd then Break
      else inc(Poz);
 if copy(FXMLText, Poz, TagEndLen) = ATagEnd then
  Result := Poz;
end;


// ������ XML ���������
function TXMLParser.ParseXML(AXMLText: String): boolean;
var
 s   : string;
 poz : integer;
begin
 Result := false;
 // ������� ���������� �����������
 FCurrentXMLNode := nil;
 FXMLRootToken   := nil;
 FXMLText := AXMLText;
 FXmlTextPoz := 1;
 // �������� ������ �������� � ������ �����
 SkipSpaces;
 while not EOF do begin
  SkipSpaces;
  poz := FXmlTextPoz;
  // ����� ������� ������������ ����
  if not SearchOpenTag then begin Result := true; exit; end;
  // �� "<" ���� ���� ������ - ���� ��, �� ������� �� � ������� ����
  if (poz <> FXmlTextPoz) then
   AddTagText(Copy(FXMLText, poz, FXmlTextPoz - poz));
  // ������� ������� '<'
  SkipChar;
  // ��������� 8-�� �������� ����
  // *** ��������, �� �������� �� ��� ����� ������������ ���� ***
  if (XMLChar[FXmlTextPoz] in ['!','?']) then begin
    S := copy(FXMLText, FXmlTextPoz, 8);
    // ��� ����������� ?
    if pos('!--', S) = 1 then begin
     SkipChars(3);
     poz := FXmlTextPoz;
     while not(EOF) and (copy(FXMLText, FXmlTextPoz, 3) <> '-->') do
      inc(FXmlTextPoz);
     AddTag(xttComment, Copy(FXMLText, poz, FXmlTextPoz - poz));
     // ������� �������� "-->"
     SkipChars(3);
     Continue;
    end;
    // ��� CDATA ??
    if pos('![CDATA[', S) = 1 then begin
     SkipChars(8);
     poz := SearchCloseTag(']]>');
     if poz >= FXmlTextPoz then begin
      AddTag(xttCData, copy(FXMLText, FXmlTextPoz, poz - FXmlTextPoz));
      FXmlTextPoz := poz + 3;
     end;
     Continue;
    end;
    // ��� !DOCTUPE ??
    if pos('!DOCTYPE', S) = 1 then begin
     SkipChars(8);
     poz := SearchCloseTag('>');
     if poz >= FXmlTextPoz then begin
      AddTag(xttDocumentType, copy(FXMLText, FXmlTextPoz, poz - FXmlTextPoz));
      FXmlTextPoz := poz + 1;
     end;
     Continue;
    end;
    // ��� !ENTITY ??
    if pos('!ENTITY', S) = 1 then begin
     SkipChars(6);
     poz := SearchCloseTag('>');
     if poz >= FXmlTextPoz then begin
      AddTag(xttEntity, copy(FXMLText, FXmlTextPoz, poz - FXmlTextPoz));
      FXmlTextPoz := poz + 1;
     end;
     Continue;
    end;
    // ��� ��� ���� <? ?>
    if copy(S,1,1) = '?' then begin
     SkipChar;
     poz := SearchCloseTag('?>');
     if poz >= FXmlTextPoz then begin
      AddTag(xttProcessingInstruction, copy(FXMLText, FXmlTextPoz, poz - FXmlTextPoz));
      FXmlTextPoz := poz + 3;
     end;
     Continue;
    end;
   end;
   // *** ��� ������� ��� ***
   poz := SearchCloseTag('>');
   if poz >= FXmlTextPoz then begin
    AddTag(xttTag, copy(FXMLText, FXmlTextPoz, poz - FXmlTextPoz));
    FXmlTextPoz := poz + 1;
   end;
 end;
 FXMLText := '';
 Result := true;
end;


// ���������� ���������� ���� � ������ �����
function TXMLParser.AddTag(ATokenType : TXmlTokenType;ATagText : String)  : boolean;
var
 s, TagName : string;
begin
 ATagText := Trim(ATagText);
 if ATagText = '' then exit;
 // ������������ ����������� ���������
 s := '';
 case ATokenType of
  xttProcessingInstruction : s := ' xttProcInstr : ';
  xttDocumentType          : s := ' xttDocType   : ';
  xttComment               : s := ' xttComment   : ';
  xttCData                 : s := ' xttCData     : ';
  xttEntity                : s := ' xttEntity    : ';
  xttTag                   : s := ' xttTag       : ';
 end;
 doDebugLog(s + ATagText);
 // ���� �������� ���� ���, �� ������� ���
 if FCurrentXMLNode = nil then begin
  FCurrentXMLNode := TXMLToken.Create(nil, xttTag, 'ROOT');
  FXMLRootToken   := FCurrentXMLNode;
 end;
 // ��� ��������� ����� ��������� ����� ��� �������� "����������"
 if ATokenType in [xttProcessingInstruction, xttDocumentType,
                   xttCData, xttComment, xttEntity] then begin
  FCurrentXMLNode.AddToken(ATokenType, ATagText);
 end else begin
  // ��� ������ ��� ?? ���� ��, �� ������� ��� ��� �������� ����������
  if copy(ATagText, length(ATagText), 1) = '/' then begin
   FCurrentXMLNode.AddToken(ATokenType, ATagText);
  end else
  // ��� ����������� ��� ?? ���� ��, �� ����������� �� ������� �����
  if copy(ATagText,1,1) = '/' then begin
   if FCurrentXMLNode.ParentToken = nil then
    doDebugLog('Error: ����������� ��� ��� ������������: '+ATagText);
   // ��������, ���� �� ��� ���������
   if FCurrentXMLNode.ParentToken <> nil then begin
    // ��������� ����� ����
    TagName := ExtractTagName(ATagText);
    // �������� ������������ ����� ����
    if (FCurrentXMLNode.TokenName <> TagName) then
     doDebugLog('Error: �������������� ������������ � ������������ �����: ������ "'+TagName+'", �������� "'+FCurrentXMLNode.TokenName+'"')
    else FCurrentXMLNode := FCurrentXMLNode.ParentToken;
   end;
  end else begin
   // ��� �� ������ ��� � �� ����������� - ������� "����������"
   FCurrentXMLNode := FCurrentXMLNode.AddToken(ATokenType, ATagText);
  end;
 end;
end;

// ���������� ���������� ��������� � ������� ���
function TXMLParser.AddTagText(ATagText: String): boolean;
begin
 doDebugLog('   TAG text  : ' + ATagText);
 FCurrentXMLNode.AddToken(xttText, ATagText);
end;

{ TXMLNode }

// ���������� ����
function TXMLToken.AddToken(ATokenType: TXmlTokenType;
  ATagText: string): TXMLToken;
begin
 // �������� ������ ����
 Result := TXMLToken.Create(Self, ATokenType, ATagText);
 // ��������� ��� � ������
 FSubNodes.Add(Result);
end;

// ��������
constructor TXMLToken.Create(AParentToken : TXmlToken; ATokenType : TXmlTokenType; ATagText : string);
begin
 FParams      := TStringList.Create;
 FSubNodes    := TXMLTokenList.Create;
 FParentToken := AParentToken;
 FTokenType   := ATokenType;
 FText        := '';
 case FTokenType of
  xttText    : begin
                FTokenName := 'TEXT';
                FText      := ATagText;
               end;
  xttComment : begin
                FTokenName := 'COMMENT';
                FText      := ATagText;
               end;
  xttCData   : begin
                FTokenName := 'CDATA';
                FText      := ATagText;
               end;
  else FTokenName   := ExtractTagName(ATagText);

 end;
 // ��� ���������� ��������� � ����� ����� ����������� ���������
 if FTokenType in [xttProcessingInstruction, xttTag] then
   ParseParams(ATagText);
end;

// ������ ����������
function TXMLToken.ParseParams(ATagText: string): boolean;
var
 i, poz : integer;
 ParamName, ParamVal : string; // ��� � �������� ���������
 QuoteChar  : char;            // ������ �������
begin
 FParams.Clear;
 ATagText := Trim(ATagText);
 if ATagText = '' then exit;
 // � ������������ ���� �� ����� ���� ����������
 if copy(ATagText, 1, 1) = '/' then exit;
 // ��������� ������ ����� ���� ����� "/" - ������ ���
 if copy(ATagText, length(ATagText), 1) = '/' then
  delete(ATagText, length(ATagText), 1);
 // �������� ��� � ������� ��� �� ����� ������� �������, ���������� ��������
 i := 1;
 while (i <= length(ATagText)) and not(ATagText[i] in SpaceChars) do
  inc(i);
 delete(ATagText, 1, i);
 // ����, ��������� ��������, �������� �������
 ATagText := Trim(ATagText);
 if ATagText <> '' then
  repeat
   poz := pos('=', ATagText);
   if poz > 0 then begin
    // ��������� ����� ����
    ParamName := Trim(copy(ATagText, 1, poz - 1));
    Delete(ATagText, 1, poz);
    // ** ����� ����������� � ����������� ������� **
    ATagText := Trim(ATagText);
    // ��������� ������� ��������� �������
    QuoteChar := #0;
    if length(ATagText) > 0 then
     QuoteChar := ATagText[1];
    // ���� ��� ������ �������� ��������, �� ���� �����-�� �����������
    if QuoteChar in QuoteChars then begin
     // ������� ����������� �������
     Delete(ATagText, 1, 1);
     // ����� �����������
     i := pos(QuoteChar, ATagText);
     // ������� ??
     if i > 0 then begin
      ParamVal := copy(ATagText, 1, i-1);
      Delete(ATagText, 1, i);
      FParams.Add(ParamName + '=' + ParamVal);
     end;
    end;
   end;
  until poz = 0; // ����� �� ��� ���, ���� ���� ���������
end;

// ��������, �������� �� ��� ������
function TXMLToken.GetIsEmpty: boolean;
begin
 Result := FSubNodes.Count = 0;
end;

// ��������� ����� ����
procedure TXMLToken.SetTokenType(const Value: TXmlTokenType);
begin
  FTokenType := Value;
end;

// �������� ����
function TXMLParser.SaveXMLToken(AXMLToken: TXMLToken; Lines: TStrings;
  Level: integer): boolean;
var
 ParamsStr : string;  // ����������������� ������ ����������
 i         : integer;
 st, s, TagText, CloseTagText, FormatText : string;
begin
 // ������ ��� �� ���������
 if AXMLToken = nil then
  exit;
 FormatText := '';
 for i := 1 to Level do
  FormatText := FormatText + ' ';
 // **** �������������� ���������� ****
 ParamsStr := '';
 for i := 0 to AXMLToken.Params.Count - 1 do begin
  if ParamsStr <> '' then
   ParamsStr := ParamsStr + ' ';
  s := copy(AXMLToken.Params[i], 1, pos('=', AXMLToken.Params[i]));
  st := copy(AXMLToken.Params[i], pos('=', AXMLToken.Params[i])+1, MaxInt);
  // ������������� ����������� ��������
  st := StringReplace(st, '<', '&lt;',[rfReplaceAll, rfIgnoreCase]);
  st := StringReplace(st, '>', '&gt;',[rfReplaceAll, rfIgnoreCase]);
  st := StringReplace(st, '"', '&quot;',[rfReplaceAll, rfIgnoreCase]);
  st := StringReplace(st, '''', '&apos;',[rfReplaceAll, rfIgnoreCase]);
  s := s+'"'+st+'"';
  ParamsStr := ParamsStr + s;
 end;
 // ����� ������������ � ������������ �����
 TagText := ''; CloseTagText := '';
 // ��������� ������ ���������� �������� (���� ������ ��������)
 if ParamsStr <> '' then
  ParamsStr := ' ' + ParamsStr;
 // ���������� ���� � ����������� �� ���� � ����������
 case AXMLToken.TokenType of
  xttProcessingInstruction : TagText  := '<?'+AXMLToken.TokenName+ParamsStr+'?>';
  xttDocumentType          : TagText  := '<!DOCTYPE '+AXMLToken.Text+'>';
  xttComment               : TagText  := '<!--'+AXMLToken.Text+'-->';
  xttCData                 : TagText  := '<![CDATA['+AXMLToken.Text+']]>';
  xttEntity                : TagText  := '<!ENTITY'+AXMLToken.Text+'>';
  xttTag                   : begin
                              TagText  := '<'+AXMLToken.TokenName+ParamsStr;
                              if AXMLToken.IsEmpty then TagText := TagText + '/>'
                               else begin
                                TagText := TagText + '>';
                                CloseTagText := '</'+AXMLToken.TokenName+'>';
                               end;
                             end;
  xttText                  : TagText  := AXMLToken.Text;
 end;
 // ���������� ����
 if AXMLToken <> XMLRootToken then begin
  Lines.Add(FormatText + TagText);
  // ���������� ���� ��������� �����
  for i := 0 to AXMLToken.SubNodes.Count - 1 do
   SaveXMLToken(AXMLToken.SubNodes[i], Lines, Level+1);
  // ���������� ������������ ���� (���� ����)
  if CloseTagText <> '' then
   Lines.Add(FormatText + CloseTagText);
 end else begin
  // ���������� ���� ��������� �����
  for i := 0 to AXMLToken.SubNodes.Count - 1 do
   SaveXMLToken(AXMLToken.SubNodes[i], Lines, Level);
 end;
end;

// �������� � ������ �����
function TXMLParser.SaveToStrings(Lines : TStrings): boolean;
begin
 Result := false;
 // ���� ��� ��������� ����, �� �����
 if FXMLRootToken = nil then exit;
 // ������� ������� �����
 Lines.Clear;
 // ����������� ��������
 SaveXMLToken(XMLRootToken, Lines, 0);
end;

// ���������� ���������� ��������
function TXMLParser.doDebugLog(S: string): boolean;
begin
 if Assigned(FOnXMLDebug) then
  FOnXMLDebug(Self, S);
end;


// ������ ������
function TXMLToken.ReadString(AName, ADefVal: String): String;
var
  I: Integer;
begin
 I := FParams.IndexOfName(AName);
 if I >= 0 then begin
  Result := Copy(FParams[I], Length(AName) + 2, Maxint);
  Exit;
 end;
 Result := ADefVal;
end;

// ������ ���������� ����������
function TXMLToken.ReadBool(AName: string; ADefVal: Boolean): Boolean;
var
 BoolStr : string;
begin
 Result := ADefVal;
 BoolStr := Trim(ReadString(AName, ''));
 if BoolStr <> '' then begin
  // ��� ������ "Y" ��� "1" ?
  if BoolStr[1] in ['Y', 'y', '1'] then begin
   Result := true;
   exit;
  end;
  // ��� ��������� ����� ?
  Result := ReadInteger(AName, Ord(ADefVal)) <> 0;
 end;
end;

// ������ �������� �����
function TXMLToken.ReadFloat(AName: string; ADefVal: Double): Double;
var
  FloatStr: string;
begin
  FloatStr := ReadString(AName, '');
  Result := ADefVal;
  if FloatStr <> '' then
  try
    Result := StrToFloat(FloatStr);
  except
    on EConvertError do
    else raise;
  end;
end;

// ������ ������ �����
function TXMLToken.ReadInteger(AName: string; ADefVal: integer): Integer;
var
  IntStr: string;
begin
  IntStr := ReadString(AName, '');
  if (Length(IntStr) > 2) and (UpperCase(copy(IntStr,1,2)) = '0X') then
    IntStr := '$' + Copy(IntStr, 3, Maxint);
  Result := StrToIntDef(IntStr, ADefVal);
end;

// ������ ���������� ����������
procedure TXMLToken.WriteBool(AName: string; AValue: Boolean);
const
  Values: array[Boolean] of string = ('0', '1');
begin
  WriteString(AName, Values[AValue]);
end;

// ������ �������� �����
procedure TXMLToken.WriteFloat(AName: string; AValue: Double);
begin
 WriteString(AName, FloatToStr(AValue));
end;

// ������ ������ �����
procedure TXMLToken.WriteInteger(AName: string; AValue: integer);
begin
 WriteString(AName, IntToStr(AValue));
end;

// ������ ������
procedure TXMLToken.WriteString(AName, AValue: String);
var
  I: Integer;
  S: string;
begin
  S := AName + '=' + AValue;
  I := FParams.IndexOfName(AName);
  if I >= 0 then FParams[I] := S else FParams.Add(S);
end;

// �������� ������� ��������� � ��������� ������
function TXMLToken.ValueExists(AName : string): boolean;
begin
 Result := FParams.IndexOfName(AName) >= 0;
end;

// ��������� ������ = ����� ���� ��������� ���������
function TXMLToken.GetFullText: String;
var
 i : integer;
begin
 Result := '';
 // ��� ��������� ��� - ������ �����
 if FTokenType = xttText then begin
  Result := Text;
  exit;
 end;
 // ��� ������� ��� - ���� ��������� ���������
 for i := 0 to FSubNodes.Count - 1 do
  if FSubNodes[i].TokenType = xttText then
   Result := Result + ' ' + FSubNodes[i].Text;
end;

// �������� ��������� ���������
procedure TXMLParser.SetOnXMLDebug(const Value: TXMLDebugHandler);
begin
  FOnXMLDebug := Value;
end;

{ ********************** TXMLTokenList ********************* }

// ��������
constructor TXMLTokenList.Create;
begin
 FTokenList := TList.Create;
end;

// ���������� ����
procedure TXMLTokenList.Add(XMLToken: TXMLToken);
begin
 FTokenList.Add(XMLToken);
end;

// �������� ���������� �����
function TXMLTokenList.GetCount: integer;
begin
 Result := FTokenList.Count;
end;

// ��������� ���� �� �������
function TXMLTokenList.GetToken(Index: integer): TXMLToken;
begin
 Result := FTokenList[Index];
end;

// ��������� ���� �� �������
procedure TXMLTokenList.SetToken(Index: integer; const Value: TXMLToken);
begin
 FTokenList[Index] := Value;
end;

// ����� ���� �� ����� (���������� ������ � �������� ������ ��� NIL)
function TXMLTokenList.GetTokenByName(AName: string): TXMLToken;
var
 i : integer;
begin
 Result := nil;
 // ���������� ����� (����� �� ����������������������)
 AName := UpperCase(Trim(AName));
 // �����
 for i := 0 to FTokenList.Count - 1 do
  if AName = UpperCase(Tokens[i].TokenName) then begin
   Result := Tokens[i]; // ��� ������ - ������� � �����
   break;
  end;
end;


// �������� ���� �����
procedure TXMLTokenList.Clear;
var
 i : integer;
begin
 for i := 0 to FTokenList.Count - 1 do
  TXMLToken(FTokenList[i]).Free;
 FTokenList.Clear;
end;

// �������� �� �������
procedure TXMLTokenList.Delete(AIndex: integer);
begin
 FTokenList.Delete(AIndex);
end;

// �������� �� ����
procedure TXMLTokenList.DeleteToken(AToken: TXmlToken);
var
 i : integer;
begin
 // ����� ����
 for i := 0 to FTokenList.Count - 1 do
  if FTokenList[i] = AToken then begin
   Delete(i); // ��� ������ - �������� �� �������
   exit;
  end;
end;

function TXMLParser.SearchToken(ATagName: String): TXMLToken;
var
 Tmp : TXMLToken;
 s : string;
begin
 Result := nil;
 ATagName := trim(UpperCase(ATagName));
 if ATagName = '' then exit;
 if FXMLRootToken = nil then exit;
 tmp := FXMLRootToken;
 while Length(ATagName) > 0 do begin
  if pos('\',ATagName) > 0 then begin
   s := copy(ATagName, 1, pos('\',ATagName) - 1);
   delete(ATagName, 1, pos('\',ATagName));
  end else begin
   s := ATagName;
   ATagName := '';
  end;
  Tmp  := Tmp.SubNodes.GetTokenByName(s);
  if Tmp = nil then exit;
 end;
 Result := Tmp;
end;

function TXMLToken.DeleteParam(AName: string): boolean;
var
  I: Integer;
begin
 I := FParams.IndexOfName(AName);
 if I >= 0 then
  FParams.Delete(i);
 Result := i>=0;
end;

function TXMLToken.GetUpperTokenName: string;
begin
 Result := UpperCase(Trim(TokenName));
end;

// �������� � ������� XML
function TXMLParser.LoadAndParseXML(AXMLFile: String): boolean;
var
 FS : TFileStream;
 AFileData : AnsiString;
begin
 Result := false;
 // �������� ������
 FS := TFileStream.Create(AXMLFile, fmOpenRead);
 try
   // �������� ������
   FS.Position := 0;
   SetLength(AFileData, FS.Size);
   FS.ReadBuffer(AFileData[1], FS.Size);
   FS.Free;
   // �������
   Result := ParseXML(AFileData);
   AFileData := '';
 except
  raise;
 end;
end;

procedure TXMLParser.Clear;
begin
 FCurrentXMLNode := nil;
// FXMLRootToken.Free;
 FXMLRootToken   := nil;
end;

destructor TXMLToken.Destroy;
begin
 FParams.Free;
 FSubNodes.Free;
 FParentToken := nil;
 inherited;
end;

destructor TXMLTokenList.Destroy;
begin
 Clear;
 FTokenList.Free;
 FTokenList := nil;
 inherited;
end;

procedure TXMLTokenList.Sort(Compare: TListSortCompare);
begin
 FTokenList.Sort(Compare);
end;

function TXMLParser.SaveToFile(AFileName: string): boolean;
var
 Lines : TStrings;
begin
 try
  Lines := TStringList.Create;
  // �������� Strings � �������������� XML
  SaveToStrings(Lines);
  // ���������� ����������� XML � ����
  Lines.SaveToFile(AFileName);;
 finally
  Lines.Free;
 end;
end;

end.


