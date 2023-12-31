unit WizardNN;
// �������������

interface
uses
  Classes,IniFiles,SysUtils;

const  // ���� ������������ ��� ������ � �������
  ntMID = 0;  // �������� ������������
  ntEXP = 1;  // ���������������� ������������
  ntNONE = 3; // ��� ������������
  ntAUTO = 2; // �������������� ������������

type
  TNeuralNetwork = class (TObject)
  private
    fW : array of array of array of double; // ������ ������������� ���������
    fDW: array of array of array of double; // ������ ���������� �������������
    fWT:array of array of double          ; // ������ �������� ��������� �����
    fDWT:array of array of double         ; // ������ ���������� ��������� �����
    fEA,                                    // ����������� ������
    fEI: array of double                  ; // �������� ��������� �����������
    fConfig : array of integer            ; // ������������ �����
    fLayerOutput: array of array of double; // ������ �����(fLayerOutput[0]-����)
    fTS,                                    // �������� ��������
    fMiu: double;                           // ����������� �������
    fLC:integer;                            // ����� �����
    fMaxNeurons:integer;                    // ������������ ����� ��������
    // ������ � ������������� ����
    procedure fSetLC(LC:integer);
    function fGetL(Layer:integer):integer;
    procedure fSetL(Layer,NeuronNum:integer);
    // ������ �� �������� ����������
    function fGetIn(i:integer):double;
    procedure fSetIn(i:integer;val:double);
    // ������ � ��������� ����������
    function fGetOut(i:integer):double;
    procedure fSetTS(TS:double);
    function fGetW(i,j,k:integer):double;
    procedure fSetW(i,j,k:integer;W:double);
    function fGetWT(i,k:integer):double;
    procedure fSetWT(i,k:integer;W:double);
    //
  public
    Alpha:double;
    Epoch : integer;                       // ������� ����
    property LayerCount:integer read fLC write fSetLC; // ����� �����
    property Layers[i:integer]:integer read fGetL write fSetL;// ����� �������� � ����
    property TeachSpeed:double read fTS write fSetTS; // �������� ��������
    property Miu:double read fMiu write fMiu;// ������������� ��������
    property W[i,j,k:integer]:double read fGetW write fSetW;
    property WT[i,k:integer]:double read fGetWT write fSetWT;
    // ������ ������� ��������
    property Input[i:integer]:double read fGetIN write fSetIN;
    // ������ �������� ��������
    property Output[i:integer]:double read fGetOUT;
    // ����� ���� ���������
    procedure ResetLayer(Layer:integer);
    // �������
    procedure Compute;
    // �������� ����
    procedure Teach(Dest:array of double);
    // ������� �������� ����
    procedure Shock;
    // ������ ��������� �� ����������� �������
    procedure RestoreNet(fname:string);
    // ���������� ��������� �� ���������� �������
    procedure StoreNet(fname:string);
    // ������� ���������������� �������� ��� ���������
    procedure CountError(Dest:array of double);
    // ��������� ������� �������������
    procedure CorrectW;
    constructor Create;
  end;
  TNeuralNetworkINI = class(TNeuralNetwork)
  public
    procedure LoadFromIni(var Ini:TMemIniFile;SectionName:string);
    procedure SaveToIni(var Ini:TIniFile;SectionName:string);
    constructor Create;
  end;
  TNetworkInputDef = class(TObject)
  public
    InputName : string;  // ��� �����
    NormType  : integer; // ������ ������������
    Min,Max   : double;  // ����������� � ������������ �������� ��� ���. ������������
    alpha     : double;  // �������� ������������� ������������
    Mid,Disp  : double;  // ������� � ��������� ��� ����������������
    Value     : double;  // �������� �����
    constructor Create;
  end;

  TNetworkInput = class(TNetworkInputDef)
  public
    number : integer;         // ����� ���� � ��
    Values : array of double; // ������ ��������
  end;

  TWizardNeuralNetwork = class (TNeuralNetworkINI)
  private
    fError       : double;
    fInputsList  : TStringList;
    fOutputsList : TStringList;
    function fGetInputValues(InputName:string):double;
    procedure fSetInputValues(InputName:string;InputValue:double);
    function fGetOutputValues(OutputName:string):double;
    procedure fSetOutputValues(OutputName:string;OutputValue:double);
  public
    property Error : double read fError;  // ������ ��� ��������
    constructor Create;
    // ��������� ������ � ������� ���������
    procedure AddInput(InputDef:TNetworkInputDef);
    procedure DelInput(InputName:string);
    procedure AddOutput(OutputDef:TNetworkInputDef);
    procedure DelOutput(OutputName:string);
    // ��������� ���������� � ������ ��������� �� �����
    procedure LoadFromWizardFile(FileName:string; ALines : TStrings);virtual;
    procedure StoreToFile(FileName:string);virtual;
    // �������� ������ � ������� ���������
    property InputValues[inputName:string]:double read fGetInputValues write fSetInputValues;
    property OutputValues[inputName:string]:double read fGetOutputValues write fSetOutputValues;
    property InputsList:TStringList read fInputsList;
    property OutputsList:TStringList read fOutputsList;
    procedure Compute; // ������� ����������
    procedure Learn;   // �������� ���������
  end;

  function Sigmoid(inp:double;parm:double):double;
  function DSigmoid(inp:double;parm:double):double;

implementation
// ���������� ������� ������� ��
// ����� ���� ���������
procedure TNeuralNetwork.ResetLayer;
var
  xJ,xK,xLayer:integer;
begin
  for xLayer:=0 to fLC-2 do
  begin
    if (fConfig[xLayer]=0) or ((fConfig[xLayer+1]=0)) then exit;
    for xJ:=0 to High(fW[xLayer]) do
      for xK:=0 to High(fW[Layer,xJ]) do
        fW[xLayer,xJ,xK] := (Random(99)+1)/100;
  end;
end;

// ��������� �������� ��������
procedure TNeuralNetwork.fSetTS(TS:double);
begin
  fTS := TS;
end;

// ������ � �������������
procedure TNeuralNetwork.fSetLC(LC:integer);
begin
  Epoch := 0;
  fLC := LC;
  SetLength(fW,0);
  SetLength(fDW,0);
  SetLength(fConfig,0);
  SetLength(fLayerOutput,0);
  SetLength(fW,LC-1);
  SetLength(fDW,LC-1);
  SetLength(fConfig,LC);
  SetLength(fLayerOutput,LC);
  SetLength(fWT,LC-1);
  SetLength(fDWT,LC-1);
end;

procedure TNeuralNetwork.fSetL;
var
 xJ,xK:integer;
begin
  // �������� ���������
  if (Layer < 0) or (Layer > fLC-1) then
    raise Exception.Create('$AVZ0527');
  fConfig[Layer]:=NeuronNum;
  if NeuronNum > fMaxNeurons then
  begin
    fMaxNeurons := NeuronNum;
    SetLength(fEA,0);
    SetLength(fEI,0);
    SetLength(fEA,fMaxNeurons);
    SetLength(fEI,fMaxNeurons);
  end;
  Epoch := 0;
  //  ������������� ������� ������������� ��� ����
  if (Layer>0)  then
    if (fConfig[Layer-1]>0) then
    begin
      // ���� �� �������.������ ����� �������� � ���� ����
      SetLength(fW[Layer-1],0);
      SetLength(fDW[Layer-1],0);
      SetLength(fWT[Layer-1],0);
      SetLength(fDWT[Layer-1],0);
      SetLength(fW[Layer-1],fConfig[Layer-1],fConfig[Layer]);
      SetLength(fDW[Layer-1],fConfig[Layer-1],fConfig[Layer]);
      SetLength(fWT[Layer-1],fConfig[Layer]);
      SetLength(fDWT[Layer-1],fConfig[Layer]);
      // ���������� ����
      for xJ:=0 to fConfig[Layer-1]-1 do
        for xK:=0 to fConfig[Layer]-1 do
        begin
          fW[Layer-1,xJ,xK] := (Random(99)+1)/100;
        end;
      for xJ:=0 to fConfig[Layer]-1 do
        fWT[Layer-1,xJ] := (Random(99)+1)/100;
    end;
  // ������ ����� �������� �������� � ����. ����
  SetLength(fLayerOutput[Layer],0);
  SetLength(fLayerOutput[Layer],NeuronNum);
  if (Layer<fLC-1) then
    if (fConfig[Layer+1]>0) then
    begin
      // ���� �� ��������. ������ ����� �������� � ��������� ����
      SetLength(fW[Layer],0);
      SetLength(fDW[Layer],0);
      SetLength(fW[Layer],fConfig[Layer],fConfig[Layer+1]);
      SetLength(fDW[Layer],fConfig[Layer],fConfig[Layer+1]);
      // ���������� ��������� ����
      for xJ:=0 to fConfig[Layer]-1 do
        for xK:=0 to fConfig[Layer+1]-1 do
        begin
          fW[Layer,xJ,xK] := (Random(99)+1)/100;
        end;
    end;
end;

function TNeuralNetwork.fGetL;
begin
  // �������� ���������
  if (Layer < 0) or (Layer > fLC-1) then
    raise Exception.Create('$AVZ0527');
  result := fConfig[Layer];
end;


// ������ �� �������� ����������
function TNeuralNetwork.fGetIn(i:integer):double;
begin
  if fLC = 0 then
    raise Exception.Create('$AVZ0950');
  if (i<0) or (i > fConfig[0]-1) then
    raise Exception.Create('$AVZ0491');
  result := fLayerOutput[0,i];
end;

procedure TNeuralNetwork.fSetIn(i:integer;val:double);
begin
  if fLC = 0 then
    raise Exception.Create('$AVZ0950');
  if (i<0) or (i > fConfig[0]-1) then
    raise Exception.Create('$AVZ0491');
  fLayerOutput[0,i] := val;
end;

// ������ � ��������� ���������
function TNeuralNetwork.fGetOut(i:integer):double;
begin
  if fLC = 0 then
    raise Exception.Create('$AVZ0950');
  if (i<0) or (i > fConfig[fLC-1]-1) then
    raise Exception.Create('$AVZ0491');
  result := fLayerOutput[fLC-1,i];
end;

// ������ � ����������
// �������
procedure TNeuralNetwork.Compute;
var
  xI,xJ,xK,xTmp :integer;
  xSum :double;
begin
  // ������������ �� ����� ����
  for xI:=0 to fLC-2 do
  begin
    // ������������ �� I-�� ����
    // ������� �� �������� ����
    xTmp := fConfig[xI]-1;
    for xK:=0 to fConfig[xI+1]-1 do
    begin
      // ������� ���������� ���� K-�� ������� � I-� ����
      xSum := 0;
      // xTmp - ����� ������ xI-�� ���� ��
      for xJ:=0 to xTmp do
        xSum := xSum + fLayerOutput[xI,xJ]*fW[xI,xJ,xK];
      // ��������� ����� ��������
      xSum := xSum+fWT[xI,xK];
      // ������� K-� ����� ����
      fLayerOutput[xI+1,xK] := Sigmoid(xSum,Alpha);
    end;
  end;
end;

// �������� ����
procedure TNeuralNetwork.Teach;
var
  xI,xJ,xK: integer;
  xTmp: integer;
  xSum: double;
begin
  // ��������� ������ ������ ��� ��������� ����
  xTmp:=fConfig[fLC-1];
  dec(xTmp);
  for xK:=0 to xTmp do
    fEA[xK]:=fLayerOutput[fLC-1,xK]-Dest[xK];
  // ������������ �������� ����
  for xI:=fLC-2 downto 0 do
  begin
    // ������������ ������ �������� ��������� ������
    xTmp := fConfig[xI+1]-1;
    // xTmp - ����� �������� � xI - � ���� ��
    // xK - ����� �������� ������� ���� xI
    for xK:=0 to xTmp do
    begin
      fEI[xK] := fEA[xK]*DSigmoid(fLayerOutput[xI+1,xK],Alpha);
      fEA[xK] := 0;
    end;
    // ���������� ���������� �������������
    // xJ - ����� �������� ����� ���� xI
    for xJ:=0 to fConfig[xI]-1 do
    begin
      xSum := 0;
      for xK:=0 to xTmp do
      begin
        xSum:=xSum + fEI[xK]*fW[xI,xJ,xK];
        fDW[xI,xJ,xK]:=-fTS*fEI[xK]*fLayerOutput[xI,xJ]+fMiu*fDW[xI,xJ,xK];
        fW[xI,xJ,xK]:=fW[xI,xJ,xK]+fDW[xI,xJ,xK];
        // ������� ��������� ����� ��������
        if xJ=0 then
        begin
          fDWT[xI,xK] := -fTS*fEI[xK]+fMiu*fDWT[xI,xK];
          fWT[xI,xK] := fWT[xI,xK]+fDWT[xI,xK];
        end;
      end;
      // �������������� ����������� �� ���������� ����
      fEA[xJ]:=xSum;
    end;
  end;
end;

constructor TNeuralNetwork.Create;
begin
  inherited Create;
  fTS := 0.95;
  fMiu := 0.1;
  fMaxNeurons:=0;
  Alpha := 0.5;
end;

// ������� �������� ����
procedure TNeuralNetwork.Shock;
var
  xI,xJ,xK: integer;
begin
  for xI:=0 to fLC-2 do
    for xJ:=0 to fConfig[xI]-1 do
      for xK:=0 to fConfig[xI+1]-1 do
        fW[xI,xJ,xK] := fW[xI,xJ,xK]+Random*0.5-0.25;
end;

// ���������� ��������� � �����
procedure TNeuralNetwork.StoreNet;
var
  xFile: TFileStream;
  xI,xJ,xK: integer;
  xTmp: integer;
  xVal: double;
begin
  xFile :=  nil;
  try
    if FileExists(fname) then
      DeleteFile(fname);
    // ��������� ����
    xFile := TFileStream.Create(fname,fmCreate or fmOpenWrite);
    // ���������� � ���� ���������
    xFile.Write('Neural network',15);
    // ���������� � ���� ����� ����� ����
    xFile.Write(fLC,sizeof(integer));
    // ���������� ������������ �����
    for xI:=0 to fLC-1 do
    begin
      xTmp := fConfig[xI];
      xFile.Write(xTmp,sizeof(xTmp));
    end;
    // ���������� ���� � ����
    for xI:=0 to fLC-2 do
      for xJ:=0 to fConfig[xI]-1 do
        for xK:=0 to fConfig[xI+1]-1 do
        begin
          xVal := fW[xI,xJ,xK];
          xFile.Write(xVal,sizeof(xVal));
        end;
    // ���������� ��������
    xVal := fTS;
    xFile.Write(xVal,sizeof(xVal));
    // ���������� ��
    xVal := fMiu;
    xFile.Write(xVal,sizeof(xVal));
    // ���������� �������� ������� �����
    for xI:=0 to fLC-2 do
      for xJ:=0 to fConfig[xI+1]-1 do
      begin
        xVal := fWT[xI,xJ];
        xFile.Write(xVal,sizeof(xVal));
      end;
    // ����� �������� Alpha
    xVal := Alpha;
    xFile.Write(xVal,sizeof(xVal));  
    xFile.Destroy;
  except
    if xFile<> nil then xFile.Destroy;
  end;
end;

// ������ ��������� �� �����
procedure TNeuralNetwork.RestoreNet;
var
  xFile: TFileStream;
  xI,xJ,xK: integer;
  xTmp: integer;
  xVal: double;
  xSign: string[16];
begin
  xFile := nil;
  try
    // ��������� ����
    xFile := TFileStream.Create(fname,fmOpenRead);
    // ������ ���������
    xFile.Read(xSign,15);
    // ������ �� ����� ����� ����� ����
    xFile.Read(xTmp,sizeof(xTmp));
    LayerCount := xTmp;
    // ������ ���������� � ����� ����
    for xI:=0 to fLC-1 do
    begin
      xFile.Read(xTmp,sizeof(xTmp));
      Layers[xI] := xTmp
    end;
    // ������ ���� �� �����
    for xI:=0 to fLC-2 do
      for xJ:=0 to fConfig[xI]-1 do
        for xK:=0 to fConfig[xI+1]-1 do
        begin
          xFile.Read(xVal,sizeof(xVal));
          fW[xI,xJ,xK] := xVal;
        end;
    // ������ ��������
    xFile.Read(xVal,sizeof(xVal));
    fTS := xVal;
    // ������ ��
    xFile.Read(xVal,sizeof(xVal));
    fMiu := xVal;
    // ������ �������� ������� �����
    for xI:=0 to fLC-2 do
      for xJ:=0 to fConfig[xI+1]-1 do
      begin
        xFile.Read(xVal,sizeof(xVal));
        fWT[xI,xJ] := xVal;
      end;
    // ������ �������� Alpha
    xFile.Read(xVal,sizeof(xVal));
    Alpha := xVal;
    xFile.Destroy;
  except
    if xFile<> nil then xFile.Destroy;
  end;
end;

function TNeuralNetwork.fGetW(i,j,k:integer):double;
begin
  result := fW[i,j,k];
end;

procedure TNeuralNetwork.fSetW(i,j,k:integer;W:double);
begin
  fW[i,j,k]:=W;
end;

function TNeuralNetwork.fGetWT(i,k:integer):double;
begin
  result := fWT[i,k];
end;

procedure TNeuralNetwork.fSetWT(i,k:integer;W:double);
begin
  fWT[i,k]:=W;
end;

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ������� ��������� �� ������
procedure TNeuralNetwork.CountError;
var
  xI,xJ,xK: integer;
  xTmp: integer;
  xSum: double;
begin
  // ��������� ������ ������ ��� ��������� ����
  xTmp:=fConfig[fLC-1];
  dec(xTmp);
  for xK:=0 to xTmp do
    fEA[xK]:=fLayerOutput[fLC-1,xK]-Dest[xK];
  // ������������ �������� ����
  for xI:=fLC-2 downto 0 do
  begin
    // ������������ ������ �������� ��������� ������
    xTmp := fConfig[xI+1]-1;
    // xTmp - ����� �������� � xI - � ���� ��
    // xK - ����� �������� ������� ���� xI
    for xK:=0 to xTmp do
    begin
      fEI[xK] := fEA[xK]*DSigmoid(fLayerOutput[xI+1,xK],Alpha);
      fEA[xK] := 0;
    end;
    // ���������� ���������� �������������
    // xJ - ����� �������� ����� ���� xI
    for xJ:=0 to fConfig[xI]-1 do
    begin
      xSum := 0;
      for xK:=0 to xTmp do
      begin
        xSum:=xSum + fEI[xK]*fW[xI,xJ,xK];
        fDW[xI,xJ,xK]:=-fTS*fEI[xK]*fLayerOutput[xI,xJ]+fMiu*fDW[xI,xJ,xK];
        // ������� ��������� ����� ��������
        if xJ=0 then
        begin
          fDWT[xI,xK] := -fTS*fEI[xK]+fMiu*fDWT[xI,xK];
        end;
      end;
      // �������������� ����������� �� ���������� ����
      fEA[xJ]:=xSum;
    end;
  end;
end;
// ��������� �����
procedure TNeuralNetwork.CorrectW;
var
  xI,xJ,xK : integer;
begin
  // ������������ �������� ����
  for xI:=fLC-2 downto 0 do
  begin
    for xJ:=0 to fConfig[xI]-1 do
    begin
      for xK:=0 to fConfig[xI+1]-1 do
      begin
        fW[xI,xJ,xK]:=fW[xI,xJ,xK]+fDW[xI,xJ,xK];
        fDW[xI,xJ,xK]:=0;
        // ������� ��������� ����� ��������
        if xJ=0 then
        begin
          fWT[xI,xK] := fWT[xI,xK]+fDWT[xI,xK];
          fDWT[xI,xK]:=0;
        end;
      end;
    end;
  end;
end;

function Sigmoid(inp:double;parm:double):double;
begin
  result := 1/(1+exp(-parm*inp));
end;

function DSigmoid(inp:double;parm:double):double;
begin
  result := parm*inp*(1-inp);
end;

// ���������� ������ ����������� ���������
constructor TNeuralNetworkINI.Create;
begin
  inherited Create;
  Miu := 0.9;
  TeachSpeed := 0.1;
  LayerCount := 3;
  Layers[0] := 10;
  Layers[1] := 5;
  Layers[2] := 1;
end;

procedure TNeuralNetworkINI.SaveToIni;
var
  xI,xJ,xK:integer;
begin
  // ����� ��������� ��
  Ini.EraseSection(SectionName);
  Ini.WriteFloat(SectionName,'TeachSpeed',TeachSpeed);
  Ini.WriteFloat(SectionName,'Miu',Miu);
  Ini.WriteFloat(SectionName,'Alpha',Alpha);
  Ini.WriteInteger(SectionName,'Epoch',Epoch);
  // ��������� ������������ ��
  Ini.WriteInteger(SectionName,'CountLayers',LayerCount);
  // ��������� ���������� � �����
  for xI:=0 to LayerCount-1 do
    Ini.WriteInteger(SectionName,'Layer_'+IntToStr(xI),Layers[xI]);
  // ��������� ���������� � �����
  for xI:=0 to LayerCount-2 do // �� ���� ����� ����
    for xJ:=0 to Layers[xI]-1 do
      for xK:=0 to Layers[xI+1]-1 do
        Ini.WriteFloat(SectionName,'W_'+IntToStr(xI)+'_'+IntToStr(xJ)+'_'+
                        IntToStr(xK),W[xI,xJ,xK]);
  // ����� ����� ��������
  for xI:=0 to LayerCount-2 do
    for xK:=0 to Layers[xI+1]-1 do
      Ini.WriteFloat(SectionName,'WT_'+IntToStr(xI)+'_'+
                      IntToStr(xK),WT[xI,xK]);
end;

procedure TNeuralNetworkINI.LoadFromIni(var Ini:TMemIniFile;SectionName:string);
var
  xI,xJ,xK:integer;
begin
  // ������ ��������� ��
  TeachSpeed :=  Ini.ReadFloat(SectionName,'TeachSpeed',0);
  Miu :=  Ini.ReadFloat(SectionName,'Miu',0);
  Alpha :=  Ini.ReadFloat(SectionName,'Alpha',0);
  // ������ ������������ ��
  LayerCount := Ini.ReadInteger(SectionName,'CountLayers',0);
  // ������ ���������� � �����
  for xI:=0 to LayerCount-1 do
    Layers[xI] := Ini.ReadInteger(SectionName,'Layer_'+IntToStr(xI),0);
  // ������ ���������� � �����
  for xI:=0 to LayerCount-2 do // �� ���� ����� ����
    for xJ:=0 to Layers[xI]-1 do
      for xK:=0 to Layers[xI+1]-1 do
        W[xI,xJ,xK] := Ini.ReadFloat(SectionName,'W_'+IntToStr(xI)+'_'+
                       IntToStr(xJ)+'_'+IntToStr(xK),0);
  // ������ ����� ��������
  for xI:=0 to LayerCount-2 do
    for xK:=0 to Layers[xI+1]-1 do
      WT[xI,xK] := Ini.ReadFloat(SectionName,'WT_'+IntToStr(xI)+'_'+
                   IntToStr(xK),0);
  Epoch :=  Ini.ReadInteger(SectionName,'Epoch',0);
end;
// ����������� ���� � �������� 0...1
function NormalizeCoeff(InpDef:TNetworkInputDef):double;
var
  xTmp:double;
begin
  with InpDef do
  begin
    xTmp := Value;
    // �����������
    case NormType of
      ntMID : xTmp := (xTmp-Min)/(Max-Min);
      ntEXP : xTmp := 1/(1+exp(-Alpha*xTmp));
      ntAUTO: xTmp := 1/(1+exp(-(xTmp-Mid)/Disp));
    end;
  end;
  result := xTmp;
end;
// �������������� � �������� �������
function DenormalizeCoeff(InpDef:TNetworkInputDef):double;
var
  xTmp : double;
begin
  with InpDef do
  begin
    xTmp := Value;
    case NormType of
      ntMID: xTmp := xTmp*(Max-Min)+Min;
      ntEXP: xTmp := -ln(1/xTmp-1)/Alpha;
      ntAUTO:
      begin
        xTmp := -ln(1/xTmp-1);
        xTmp := xTmp*Disp+Mid;
      end;
    end;
  end;
  result := xTmp;
end;

constructor TNetworkInputDef.Create;
begin
  inherited Create;
end;

constructor TWizardNeuralNetwork.Create;
begin
  inherited Create;
  fInputsList := TStringList.Create;
  fOutputsList := TStringList.Create;
end;

function TWizardNeuralNetwork.fGetInputValues;
begin
  if fInputsList.IndexOf(InputName)=-1 then
    raise Exception.Create('$AVZ0163 '+InputName+' $AVZ0488');
  result := (fInputsList.Objects[fInputsList.IndexOf(InputName)] as TNetworkInputDef)
             .Value;
end;

procedure TWizardNeuralNetwork.fSetInputValues(InputName:string;InputValue:double);
begin
  if fInputsList.IndexOf(InputName)=-1 then
    raise Exception.Create('$AVZ0163 '+InputName+' $AVZ0488');
  (fInputsList.Objects[fInputsList.IndexOf(InputName)] as TNetworkInputDef).Value :=
  InputValue;
end;

function TWizardNeuralNetwork.fGetOutputValues(OutputName:string):double;
begin
  if fOutputsList.IndexOf(OutputName)=-1 then
    raise Exception.Create('$AVZ0163 '+OutputName+' $AVZ0488');
  result := (fOutputsList.Objects[fOutputsList.IndexOf(OutputName)] as TNetworkInputDef)
             .Value;
end;

procedure TWizardNeuralNetwork.fSetOutputValues(OutputName:string;OutputValue:double);
begin
  if fOutputsList.IndexOf(OutputName)=-1 then
    raise Exception.Create('$AVZ0163 '+OutputName+' $AVZ0488');
  (fOutputsList.Objects[fOutputsList.IndexOf(OutputName)] as TNetworkInputDef).Value :=
  OutputValue;
end;

procedure TWizardNeuralNetwork.AddOutput;
begin
  if fOutputsList.IndexOf(OutputDef.InputName)<>-1 then
    raise Exception.Create('$AVZ0196 '+OutputDef.InputName+' $AVZ1099');
  fOutputsList.AddObject(OutputDef.InputName,OutputDef);
  // ������������� ���������
  Layers[LayerCount-1] := fOutputsList.Count;
end;

procedure TWizardNeuralNetwork.DelOutput;
begin
  if fOutputsList.IndexOf(OutputName)=-1 then
    raise Exception.Create('$AVZ0163 '+OutputName+' $AVZ0488');
  fOutputsList.Delete(fOutputsList.IndexOf(OutputName));
  // ������������ ���������
  Layers[LayerCount-1] := fOutputsList.Count;
end;

procedure TWizardNeuralNetwork.AddInput;
begin
  if fInputsList.IndexOf(InputDef.InputName)<>-1 then
    raise Exception.Create('$AVZ0163 '+InputDef.InputName+' $AVZ1099');
  fInputsList.AddObject(InputDef.InputName,InputDef);
  // ������������� ���������
  Layers[0] := fInputsList.Count;
end;

procedure TWizardNeuralNetwork.DelInput;
begin
  if fInputsList.IndexOf(InputName)=-1 then
    raise Exception.Create('$AVZ0163 '+InputName+' $AVZ0488');
  fInputsList.Delete(fInputsList.IndexOf(InputName));
  // ������������ ���������
  Layers[0] := fInputsList.Count;
end;


procedure TWizardNeuralNetwork.LoadFromWizardFile(FileName:string; ALines : TStrings);
var
  xCount,xI,xFieldType : integer;
  xFieldsInfo : TNetworkInputDef;
  xIniFile: TMemIniFile;
  begin
  xIniFile := TMemIniFile.Create(FileName);
  // ������ �� �����, ������� ������ Wizard-��
  if ALines <> nil then begin
   xIniFile.Clear;
   xIniFile.SetStrings(ALines);
  end;
  // ��������������� ����� ��������� �����
  xCount:= xIniFile.ReadInteger('Phase2','AvailableFieldsCount',0);
  // ������ ����
  fInputsList.Clear;
  fOutputsList.Clear;
  for xI:=0 to xCount-1 do
  begin
    xFieldsInfo := TNetworkInputDef.Create;
    xFieldType := xIniFile.ReadInteger('Phase2','FieldType_'+
                                IntToStr(xI),0);
    xFieldsInfo.InputName := xIniFile.ReadString('Phase2','FieldName_'+
                                IntToStr(xI),'');
    xFieldsInfo.NormType := xIniFile.ReadInteger('Phase2','NormType_'+
                               IntToStr(xI),0);
    xFieldsInfo.Max := xIniFile.ReadFloat('Phase2','MAX_'+IntToStr(xI),0);
    xFieldsInfo.Min := xIniFile.ReadFloat('Phase2','MIN_'+IntToStr(xI),0);
    xFieldsInfo.Mid := xIniFile.ReadFloat('Phase2','MID_'+IntToStr(xI),0);
    xFieldsInfo.Disp := xIniFile.ReadFloat('Phase2','DISP_'+IntToStr(xI),0);
    xFieldsInfo.Alpha := xIniFile.ReadFloat('Phase2','ALPHA_'+IntToStr(xI),0);
    case xFieldType of
      0: AddInput(xFieldsInfo);
      1: AddOutput(xFieldsInfo);
    end;
  end;
  // ��������������� ��������� ������������
  // ������ ����� ������� ����� ��
  LayerCount := xIniFile.ReadInteger('Phase3','HideLayers',1)+2;
  Layers[0] := fInputsList.Count;
  // ������ ������������ ����� ��
  for xI:=1 to LayerCount-2 do
    Layers[xI] := xIniFile.ReadInteger('Phase3','Layer_'+IntToStr(xI),5);
  Layers[LayerCount-1] := fOutputsList.Count;
  // ������ �������� ���������
  Alpha := xIniFile.ReadFloat('Phase3','Alpha',1);
  // ��������� ������ ������������� ����
  LoadFromIni(xIniFile,'Network');
  // �����������
  xIniFile.Free;
end;

procedure TWizardNeuralNetwork.StoreToFile;
var
  xCount,xI   : integer;
  xFieldsInfo : TNetworkInputDef;
  IniFile     : TIniFile;
begin
  // ������� ��������� ������, � �������, ����������� � �������� :)
  IniFile := TIniFile.Create(FileName);
  // ���������� ����� ��������� �����
  xCount := fInputsList.Count+fOutputsList.Count;
  IniFile.WriteInteger('Phase2','AvailableFieldsCount',xCount);
  // c�������� �����
  for xI:=0 to fInputsList.Count-1 do
  begin
    xFieldsInfo := fInputsList.Objects[xI] as TNetworkInputDef;
    IniFile.WriteInteger('Phase2','FieldType_'+
                                IntToStr(xI),0);
    IniFile.WriteString('Phase2','FieldName_'+IntToStr(xI),xFieldsInfo.InputName);
    IniFile.WriteInteger('Phase2','NormType_'+IntToStr(xI),xFieldsInfo.NormType);
    IniFile.WriteFloat('Phase2','MAX_'+IntToStr(xI),xFieldsInfo.Max);
    IniFile.WriteFloat('Phase2','MIN_'+IntToStr(xI),xFieldsInfo.Min);
    IniFile.WriteFloat('Phase2','ALPHA_'+IntToStr(xI),xFieldsInfo.Alpha);
  end;
  // ��������� ������
  for xI:=fInputsList.Count to fInputsList.Count+fOutputsList.Count-1 do
  begin
    xFieldsInfo := fInputsList.Objects[xI-fInputsList.Count] as TNetworkInputDef;
    IniFile.WriteInteger('Phase2','FieldType_'+
                                IntToStr(xI),1);
    IniFile.WriteString('Phase2','FieldName_'+IntToStr(xI),xFieldsInfo.InputName);
    IniFile.WriteInteger('Phase2','NormType_'+IntToStr(xI),xFieldsInfo.NormType);
    IniFile.WriteFloat('Phase2','MAX_'+IntToStr(xI),xFieldsInfo.Max);
    IniFile.WriteFloat('Phase2','MIN_'+IntToStr(xI),xFieldsInfo.Min);
    IniFile.WriteFloat('Phase2','ALPHA_'+IntToStr(xI),xFieldsInfo.Alpha);
  end;
  // ����� ����� ������� ����� ��
  IniFile.WriteInteger('Phase3','HideLayers',LayerCount-2);
  // ����� ������������ ����� ��
  for xI:=1 to LayerCount-1 do
    IniFile.WriteInteger('Phase3','Layer_'+IntToStr(xI),Layers[xI]);
  // ����� �������� ���������
  IniFile.WriteFloat('Phase3','Alpha',Alpha);
  // ��������� ������ ������������� ����
  SaveToIni(IniFile,'Network');
  IniFile.Free;
end;

procedure TWizardNeuralNetwork.Compute;
var
  xI:integer;
begin
  // ��������� ����� ���������
  for xI:=0 to fInputsList.Count-1 do
  begin
    Input[xI] := NormalizeCoeff((fInputsList.Objects[xI] as TNetworkInputDef))*2-1;
  end;
  inherited Compute;
  // ������ ������ ���������
  for xI:=0 to fOutputsList.Count-1 do
  begin
   (fOutputsList.Objects[xI] as TNetworkInputDef).Value := Output[xI];
   (fOutputsList.Objects[xI] as TNetworkInputDef).Value :=
      DenormalizeCoeff((fOutputsList.Objects[xI] as TNetworkInputDef));
  end;
end;

procedure TWizardNeuralNetwork.Learn;
var
  xI:integer;
    xTmp: array of double;
begin
  // ��������� ����� ���������
  for xI:=0 to fInputsList.Count-1 do
  begin
    Input[xI] := NormalizeCoeff((fInputsList.Objects[xI] as TNetworkInputDef))*2-1;
  end;
  // ���������� ������
  SetLength(xTmp,fOutputsList.Count);
  for xI:=0 to fOutputsList.Count-1 do
  begin
    xTmp[xI] := NormalizeCoeff((fOutputsList.Objects[xI] as TNetworkInputDef));
  end;
  // ���������� ������ ����
  Compute;
  // ���������� ������
  fError := 0;
  for xI:=0 to fOutputsList.Count-1 do
    fError := fError + sqr(xTmp[xI]-Output[xI]);
  for xI:=0 to fOutputsList.Count-1 do
  begin
   (fOutputsList.Objects[xI] as TNetworkInputDef).Value := Output[xI];
   (fOutputsList.Objects[xI] as TNetworkInputDef).Value :=
      DenormalizeCoeff((fOutputsList.Objects[xI] as TNetworkInputDef));
  end;
  // � ������ ��
  Teach(xTmp);
end;

initialization
  DecimalSeparator := '.';
end.
