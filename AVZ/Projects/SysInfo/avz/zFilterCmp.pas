unit zFilterCmp;
// ��������� ��� ���������� ���������� ������
// (C) ������ �.�., 2004-2006
interface
uses classes, stdctrls, Forms, extctrls, Sysutils, Graphics, controls, dialogs, buttons;

type

 // ���� ������
 TFilterEditType = (fetNumber, fetNumberList, fetNumberDiapazon, fetString, fetDate, fetDateDiapazon, fetNone);
 // ������ ������ �������
 TFilterEditMode = (femNumber, femNumberCode, femString, femDate, femCustom);

 // ������� �������
 TFilterItem = class
  Caption   : string;           // ���������
  EditType  : TFilterEditType;  // ��� ��������� ��� �����
  WhereMask : string;           // ����� ��� ������������ �������
  Help      : string;           // ���������
  Flags     : byte;             // ������� �����, ����������� ���������� ���������
  {                             ���   ���    ����������
                                 0     1     ��������� ����� ��������������
                                 1     2     ��������� ����� ��������������
                                 2     4     ������� ����, ��� � ���� ������ �� ����� ������������
                                 3     8
                                 4    16
                                 5    32
  }
 end;

 TOnButtonClickEvent = procedure(Sender : TObject; ButtonId : byte) of object;
 TFilterEditTranslateEvent = function(Sender : TObject; AStr : string) : string of object;
 // ������� �����
 TFilterEdit = class(TCustomPanel)
  private
    FFilterEditMode: TFilterEditMode;
    FFilterCaption: String;
    FFilterCaptionWidth: integer;
    FFilterComboWidth: integer;
    FFieldName: string;
    FAutoValidate: boolean;
    FDefaultFilterItem: integer;
    FFilterItemsNull: boolean;
    FFilterReadOnly: boolean;
    FHiddenFilterText1: string;
    FHiddenFilterText2: string;
    FHiddenValuesMode: boolean;
    FButtonsVisible: boolean;
    FOnButtonClick: TOnButtonClickEvent;
    FButtonsHint: string;
    FFilterEditTranslateEvent: TFilterEditTranslateEvent;
    procedure SetFilterEditMode(const Value: TFilterEditMode);
    procedure SetFilterCaption(const Value: String);
    procedure SetFilterCaptionWidth(const Value: integer);
    procedure SetFilterComboWidth(const Value: integer);
    function  GetFilterOn: boolean;
    // ��������� ��������� ��������/���������
    procedure SetFilterOn(const Value: boolean);
    // ������� �� ���������/��������� ����������
    procedure FOnCaptionLabelClick(Sender: TObject);
    // ������� �� ����� ������� ����������
    procedure FOnComboBoxClick(Sender: TObject);
    // ������� �� �������������� �������
    procedure FOnEditChange(Sender: TObject);
    // ��������� �������� �������� ������
    function  GetTekFilterItem: TFilterItem;
    // ��������� �������� ��������
    function  CheckNumberValue(S : string) : boolean;
    // ��������� ������ �������� ��������
    function  CheckNumberValues(S : string) : boolean;
    // ��������� �������� ��������
    function  CheckDateValue(S : string) : boolean;
    // ��������� �������� ��������
    function  CheckDateValues(S : string) : boolean;
    // ���������� ����� ������������
    procedure SetAutoValidate(const Value: boolean);
    function GetButtonVisible: boolean;
    function GetTextStateDescr: string;
    procedure SetTextStateDescr(const Value: string);
    function GetTekFilterItemIndex: integer;
    function GetFilterText1: string;
    function GetFilterText2: string;
    procedure SetFilterText1(const Value: string);
    procedure SetFilterText2(const Value: string);
    procedure SetDefaultFilterItem(const Value: integer);
    procedure SetFilterItemsNull(const Value: boolean);
    procedure SetFilterReadOnly(const Value: boolean);
    procedure SetHiddenFilterText1(const Value: string);
    procedure SetHiddenFilterText2(const Value: string);
    procedure SetHiddenValuesMode(const Value: boolean);
    procedure SetButtonsVisible(const Value: boolean);
    procedure SetOnButtonClick(const Value: TOnButtonClickEvent);
    procedure SpeedButtonClick(Sender: TObject);
    procedure SetButtonsHint(const Value: string);
    procedure SetFilterEditTranslateEvent(
      const Value: TFilterEditTranslateEvent);
  protected
   FEdit1OK, FEdit2OK : boolean; // ���������� �������� �������� 1 � 2
   FFilterEdit1b : TSpeedButton; // ������ ��������� 1
   FFilterEdit2b : TSpeedButton; // ������ ��������� 2
   FDopLabel     : TLabel;       // ����� � ������������ ... ��� ���������� ����� ���������
   // ��������� ������������
   Procedure   AlignElements;
   // ��������� (����������� ��� ������ �������������)
   procedure Paint; override;
   // ���������������
   procedure Resize; override;
   // ��������� ������� ��������� ����� ��� ��������� �����������
   procedure UnderlineComponent(ACmp : TControl);
   function  DoTranslate(S : string) : string;
  public
   FFilterCombo  : TComboBox;    // �������
   FCaptionLabel : TCheckBox;    // �������������-�����
   FFilterEdit1  : TEdit;        // �������� ��� ����� ������ 1
   FFilterEdit2  : TEdit;        // �������� ��� ����� ������ 2
   ErrorMessage : string; // ��������� �� ������
   // �������� ������
   Constructor Create(AOwner: TComponent); override;
   // ���������� ������
   Destructor  Destroy; override;
   // ���������� �������� ����������
   Procedure   AddFilterItem(ACaption: string; AEditType: TFilterEditType; AWhereMask : string; AFlags : byte; AComment : string = '');
   // �������� �������� �������
   Procedure   DeleteFilterItems;
   // �������� ��������
   Function    ValidateValue : boolean;
   // ������������ SQL ������� �������� ��������� Oracle
   Function    GetSQL : string;
   // ������� ��������� ������
   property    ButtonVisible : boolean read GetButtonVisible;
   // ��������� ��������
   property    TextStateDescr : string read GetTextStateDescr write SetTextStateDescr;
  published
   // ����� �������
   property FilterEditMode  : TFilterEditMode read FFilterEditMode write SetFilterEditMode;
   // ���������
   property Caption : String read FFilterCaption write SetFilterCaption;
   // ������ ���������
   property FilterCaptionWidth : integer     read FFilterCaptionWidth write SetFilterCaptionWidth;
   // ������ ������ ��������� ����������
   property FilterComboWidth   : integer     read FFilterComboWidth   write SetFilterComboWidth;
   // ��������� ������� (��������-���������)
   property FilterOn           : boolean     read GetFilterOn         write SetFilterOn;
   // ��������� �� ������� ������� ��� nil, ���� �������� �������� ���
   property TekFilterItem      : TFilterItem read GetTekFilterItem;
   // ��������� �� ������� ������� ��� nil, ���� �������� �������� ���
   property TekFilterItemIndex : integer read GetTekFilterItemIndex;
   // ��� ���� ��� ���������, ��������� ���������� ��� �������
   property FieldName          : string read FFieldName write FFieldName;
   // ������ ������ � ������ ����� � �������� ���������� �� ������ � ������
   property FilterText1        : string read GetFilterText1 write SetFilterText1;
   property FilterText2        : string read GetFilterText2 write SetFilterText2;
   // ������ � ������� ��������� (��� ������������ ������ ������� ��� ��������� HiddenValuesMode)
   property HiddenFilterText1  : string read FHiddenFilterText1 write SetHiddenFilterText1;
   property HiddenFilterText2  : string read FHiddenFilterText2 write SetHiddenFilterText2;
   // ����� "������ ������" ��� ����� �������. �������, ���� ������� �������� � ���� �����-�� ������ ��������
   property FilterReadOnly     : boolean read FFilterReadOnly write SetFilterReadOnly;
   // ������������ (��� ������ ���������)
   property AutoValidate : boolean read FAutoValidate write SetAutoValidate;
   // ������ ���� ���������� �� ��������� (������ ������������� � 0)
   property DefaultFilterItem  : integer read FDefaultFilterItem write SetDefaultFilterItem;
   // �������� �������������� ������� ��� NULL � ����������� ��������
   property FilterItemsNull    : boolean read FFilterItemsNull write SetFilterItemsNull;
   // ����� "������� ��������"  - � ��� ������ ������� ������������ ������� ��������. ������ ��� ������������
   property HiddenValuesMode   : boolean read FHiddenValuesMode write SetHiddenValuesMode;
   // ������� ����, ��� ������ ������
   property ButtonsVisible     : boolean read FButtonsVisible write SetButtonsVisible;
   // ��������� ��� ������
   property ButtonsHint        : string read FButtonsHint write SetButtonsHint;
   // ������� "������� �� ������"
   property OnButtonClick      : TOnButtonClickEvent read FOnButtonClick write SetOnButtonClick;
   // ������� "��������� ����������� ������"
   property  FilterEditTranslateEvent : TFilterEditTranslateEvent read FFilterEditTranslateEvent write SetFilterEditTranslateEvent;
   // ����������� �������� - ����� � HINT
   property BevelInner;
   property BevelOuter;
   property ShowHint;
   property Anchors;
 end;

procedure Register;
implementation

procedure Register;
begin
  RegisterComponents('Data Controls', [TFilterEdit]);
end;

// �������� ������
constructor TFilterEdit.Create(AOwner: TComponent);
begin
 inherited;
 Height := 32;
 Width  := 400;
 FFilterEditTranslateEvent := nil;
 FFilterEdit1b  := nil;
 FFilterEdit2b  := nil;
 FOnButtonClick := nil;
 FFilterReadOnly := false;
 FHiddenFilterText1 := '';
 FHiddenFilterText2 := '';
 FHiddenValuesMode  := false;
 FButtonsVisible    := false;
 FFilterCaptionWidth  := 70;
 FFilterComboWidth    := 150;
 BorderWidth := 0;
 BorderStyle := bsNone;
 FAutoValidate := false;
 FFilterItemsNull := false;
 // �������� ��������� ���������
 FCaptionLabel := TCheckBox.Create(self);
 FFilterCombo  := TComboBox.Create(self);
 FFilterEdit1  := TEdit.Create(self);
 FFilterEdit2  := TEdit.Create(self);
 FDopLabel     := TLabel.Create(self);

 // ������������� ������� � ���������
 FCaptionLabel.Visible  := true;
 FCaptionLabel.Caption  := FFilterCaption;
 FCaptionLabel.Parent   := self;
 FCaptionLabel.OnClick  := FOnCaptionLabelClick;
 FCaptionLabel.Name     := 'FilterCaption';

 // ������������� ������ ��������� �������
 FFilterCombo.Visible  := true;
 FFilterCombo.Parent   := self;
 FFilterCombo.Style    := csDropDownList;
 FFilterCombo.OnClick  := FOnComboBoxClick;
 FFilterCombo.Top      := 1;
 FFilterCombo.Name     := 'FFilterCombo';

 // ������������� ��������� ������ 1
 FFilterEdit1.Visible  := true;
 FFilterEdit1.Parent   := self;
 FFilterEdit1.OnChange := FOnEditChange;
 FFilterEdit1.Name     := 'FFilterEdit';
 FFilterEdit1.Top      := 1;
 FFilterEdit1.Text     := '';

 // ������������� ��������� ������ 2
 FFilterEdit2.Parent   := self;
 FFilterEdit2.OnChange := FOnEditChange;
 FFilterEdit2.Name     := 'FFilterEdit1';
 FFilterEdit2.Top      := 1;
 FFilterEdit2.Text     := '';
 FFilterEdit2.Visible  := false;

 FDopLabel.Name     := 'FDopLabel';
 FDopLabel.Visible  := false;
 FDopLabel.AutoSize := true;
 FDopLabel.Caption  := '...';
 FDopLabel.Parent   := self;


 inherited Caption := '';
 // ������������ ���������
 AlignElements;
end;

// ���������� ������
destructor TFilterEdit.Destroy;
begin
  inherited;
end;

procedure TFilterEdit.AlignElements;
var
 BtnWidth : integer;
begin
 // ��������� �����
 FCaptionLabel.Left  := 2; FCaptionLabel.Top := FFilterCombo.Height - FCaptionLabel.Height+3;
 FCaptionLabel.Width := FilterCaptionWidth;

 // ��������� ������
 FFilterCombo.Left  := FFilterCaptionWidth+1;
 FFilterCombo.Width := FFilterComboWidth;
 // ������ ������ (��� ������ � ������� ������ �� ����� ��������������
 BtnWidth := 0;
 // ��������/���������� ������ �� ���� �������������
 if FButtonsVisible then begin
  BtnWidth := 20;
  // ������ ������
  if not(Assigned(FFilterEdit1b)) then begin
   FFilterEdit1b := TSpeedButton.Create(Self);
   FFilterEdit1b.Visible := FFilterEdit1.Visible;
   FFilterEdit1b.Height  := FFilterEdit1.Height-3;
   FFilterEdit1b.Top     := FFilterEdit1.Top+2;
   FFilterEdit1b.Width   := BtnWidth;
   FFilterEdit1b.Caption := '...'; FFilterEdit1b.Font.Style := [fsBold];
   FFilterEdit1b.Enabled := FCaptionLabel.Checked;
   FFilterEdit1b.Parent  := Self;
   FFilterEdit1b.Hint    := ButtonsHint;
   FFilterEdit1b.ShowHint := true;
   FFilterEdit1b.OnClick := SpeedButtonClick;
  end;
  // ������ ������
  if not(Assigned(FFilterEdit2b)) then begin
   FFilterEdit2b := TSpeedButton.Create(Self);
   FFilterEdit2b.Visible := FFilterEdit2.Visible;
   FFilterEdit2b.Height  := FFilterEdit2.Height-3;
   FFilterEdit2b.Top     := FFilterEdit2.Top+2;
   FFilterEdit2b.Width   := BtnWidth;
   FFilterEdit2b.Caption := '...'; FFilterEdit2b.Font.Style := [fsBold];
   FFilterEdit2b.Enabled := FCaptionLabel.Checked;
   FFilterEdit2b.Parent := Self;
   FFilterEdit2b.Hint    := ButtonsHint;
   FFilterEdit2b.ShowHint := true;
   FFilterEdit2b.OnClick := SpeedButtonClick;
  end;
 end else begin
  // ���� ������ �� ���������, �� ��� �����������, ����� �� ���������� �������
  BtnWidth := 0;
  FFilterEdit1b.Free; FFilterEdit1b := nil;
  FFilterEdit2b.Free; FFilterEdit2b := nil;
 end;
 // ��������� ��������� ��� ����� ��������
 if not(FFilterEdit2.Visible) then begin  // ���� ��������
  FDopLabel.Visible := false;
  FFilterEdit2.Left := -1000;
  FFilterEdit1.Left   := FFilterCombo.Left + FFilterComboWidth+2;
  FFilterEdit1.Height := FFilterCombo.Height-1;
  FFilterEdit1.Width  := Width - FFilterEdit1.Left - 3 - BtnWidth;
  if FButtonsVisible then
   FFilterEdit1b.Left := FFilterEdit1.Left + FFilterEdit1.Width+1;
 end else begin                        // ��� ���������
   FDopLabel.Visible  := true;
   FDopLabel.Font.Style := [fsBold];
   FFilterEdit1.Left   := FFilterCombo.Left + FFilterComboWidth+2;
  if not(FButtonsVisible) then begin    // ��� ������
   FFilterEdit1.Width  := (Width - FFilterEdit1.Left) div 2  - FDopLabel.Width + 3;
   FDopLabel.Left     := FFilterEdit1.Left + FFilterEdit1.Width+1;
   FDopLabel.Top      := FFilterEdit1.Height - FDopLabel.Height+1;
   FFilterEdit2.Left  := FDopLabel.Left + FDopLabel.Width + 1;
   FFilterEdit2.Width := FFilterEdit1.Width;
   FFilterEdit1.Height := FFilterCombo.Height-1;
   FFilterEdit2.Height := FFilterCombo.Height-1;
  end else begin                      // � ��������
   FFilterEdit1.Width  := (Width - FFilterEdit1.Left - BtnWidth*2) div 2  - FDopLabel.Width + 3;
   FFilterEdit1b.Left  :=  FFilterEdit1.Left + FFilterEdit1.Width+1;
   FDopLabel.Left     := FFilterEdit1b.Left + FFilterEdit1b.Width+1;
   FDopLabel.Top      := FFilterEdit1.Height - FDopLabel.Height+1;
   FFilterEdit2.Left  := FDopLabel.Left + FDopLabel.Width + 1;
   FFilterEdit2.Width := FFilterEdit1.Width;
   FFilterEdit1.Height := FFilterCombo.Height-1;
   FFilterEdit2.Height := FFilterCombo.Height-1;
   FFilterEdit2b.Left  :=  FFilterEdit2.Left + FFilterEdit2.Width+1;
   FFilterEdit2b.Visible := true;
  end;
 end;
 // ����������� ����� ������������
 Repaint;
end;

procedure TFilterEdit.SetFilterCaption(const Value: String);
begin
  FFilterCaption := Value;
  FCaptionLabel.Caption := FFilterCaption;
end;

procedure TFilterEdit.SetFilterEditMode(const Value: TFilterEditMode);
begin
  FFilterEditMode := Value;
  DeleteFilterItems;
  case FFilterEditMode of
   femNumber : begin
                DeleteFilterItems;
                AddFilterItem('$AVZ0887',     fetNumberList,     '{FLD} IN ({X})',     1, '$AVZ0230');
                AddFilterItem('$AVZ0485', fetNumberList,     '{FLD} NOT IN ({X})', 1, '$AVZ0230');
                AddFilterItem('$AVZ0079',    fetNumber,         '{FLD} > {X}',        1);
                AddFilterItem('$AVZ0402',    fetNumber,         '{FLD} < {X}',        1);
                AddFilterItem('$AVZ0088',   fetNumberDiapazon, '{FLD} BETWEEN {X1} AND {X2}',     2);
                AddFilterItem('$AVZ0112', fetNumberDiapazon, '{FLD} NOT BETWEEN {X1} AND {X2}', 2);
                if FFilterItemsNull then begin
                 AddFilterItem('$AVZ0273',   fetNumber, '{FLD} IS NOT NULL', 0 + 4);
                 AddFilterItem('$AVZ0474', fetNumber, '{FLD} IS NULL', 0 + 4);
                end;
               end;
   femNumberCode : begin
                DeleteFilterItems;
                AddFilterItem('$AVZ0887',     fetNumberList,     '{FLD} IN ({X})',     1, '$AVZ0230');
                AddFilterItem('$AVZ0485', fetNumberList,     '{FLD} NOT IN ({X})', 1, '$AVZ0230');
                if FFilterItemsNull then begin
                 AddFilterItem('$AVZ0273',   fetNumber, '{FLD} IS NOT NULL', 0 + 4);
                 AddFilterItem('$AVZ0474', fetNumber, '{FLD} IS NULL', 0 + 4);
                end;
               end;
   femString : begin
                DeleteFilterItems;
                AddFilterItem('$AVZ1012',             fetString, 'UPPER({FLD}) LIKE UPPER(''%''||''{X}''||''%'')', 1);
                AddFilterItem('$AVZ0486',          fetString, 'UPPER({FLD}) NOT LIKE UPPER(''%''||''{X}''||''%'')', 1);
                AddFilterItem('$AVZ0467',     fetString, 'UPPER({FLD}) LIKE UPPER(''{X}''||''%'')', 1);
                AddFilterItem('$AVZ0265 ...', fetString, 'UPPER({FLD}) LIKE UPPER(''%''||''{X}'')', 1);
                AddFilterItem('$AVZ0886',                fetString, 'UPPER({FLD}) LIKE UPPER(''{X}'')', 1);
                AddFilterItem('$AVZ0484',             fetString, 'UPPER({FLD}) LIKE UPPER(''{X}'')', 1);
                if FFilterItemsNull then begin
                 AddFilterItem('$AVZ0273',   fetString, 'LTRIM({FLD}) IS NOT NULL', 4);
                 AddFilterItem('$AVZ0474', fetString, 'LTRIM({FLD}) IS NULL', 4);
                end;
               end;
   femDate : begin
                DeleteFilterItems;
                AddFilterItem('$AVZ0887',     fetDate, 'TRUNC({FLD}) =  TO_DATE(''{X}'',''DD.MM.YYYY'')', 1, '$AVZ1132');
                AddFilterItem('$AVZ0485', fetDate, 'TRUNC({FLD}) != TO_DATE(''{X}'',''DD.MM.YYYY'')', 1, '$AVZ1132');
                AddFilterItem('$AVZ0079',    fetDate, 'TRUNC({FLD}) > TO_DATE(''{X}'',''DD.MM.YYYY'')', 1);
                AddFilterItem('$AVZ0402',    fetDate, 'TRUNC({FLD}) < TO_DATE(''{X}'',''DD.MM.YYYY'')', 1);
                AddFilterItem('$AVZ0088',   fetDateDiapazon, 'TRUNC({FLD}) BETWEEN TO_DATE(''{X1}'',''DD.MM.YYYY'') AND TO_DATE(''{X2}'',''DD.MM.YYYY'')', 2);
                AddFilterItem('$AVZ0112', fetDateDiapazon, 'TRUNC({FLD}) NOT BETWEEN TO_DATE(''{X1}'',''DD.MM.YYYY'') AND TO_DATE(''{X2}'',''DD.MM.YYYY'')', 2);
                if FFilterItemsNull then begin
                 AddFilterItem('$AVZ0273',   fetDate, '{FLD} IS NOT NULL', 4);
                 AddFilterItem('$AVZ0474', fetDate, '{FLD} IS NULL', 4);
                end;
               end;
   femCustom : begin
                 DeleteFilterItems;
               end;
  end;
  // ����� �������� �� ���������
  if (FFilterCombo.Items.Count > 0) and
     (FFilterCombo.ItemIndex < 0) then begin
      FFilterCombo.ItemIndex := 0;
      if DefaultFilterItem > 0 then
       try FFilterCombo.ItemIndex := DefaultFilterItem; except end;
     end;
end;

procedure TFilterEdit.SetFilterCaptionWidth(const Value: integer);
begin
 FFilterCaptionWidth := Value;
 AlignElements;
end;

procedure TFilterEdit.SetFilterComboWidth(const Value: integer);
begin
 FFilterComboWidth := Value;
 AlignElements;
end;

function TFilterEdit.GetFilterOn: boolean;
begin
 Result := FCaptionLabel.Checked;
end;

procedure TFilterEdit.SetFilterOn(const Value: boolean);
begin
 FCaptionLabel.Checked := Value;
 FFilterCombo.Enabled  := Value;
 FFilterEdit1.Enabled   := Value;
 FFilterEdit2.Enabled  := Value;
 if FButtonsVisible then begin
  if FFilterEdit1b <> nil then
   FFilterEdit1b.Enabled   := Value;
  if FFilterEdit2b <> nil then
   FFilterEdit2b.Enabled  := Value;
 end;
 Repaint;
end;

// ������� �� ���������/��������� ����������
procedure TFilterEdit.FOnCaptionLabelClick(Sender: TObject);
begin
 SetFilterOn(FCaptionLabel.Checked);
end;

// ���������� �������� ����������
procedure TFilterEdit.AddFilterItem(ACaption: string; AEditType: TFilterEditType; AWhereMask : string;  AFlags : byte; AComment : string = '');
var
 Tmp : TFilterItem;
begin
 // �������� ���������� ������ "������"
 Tmp := TFilterItem.Create;
 ACaption := DoTranslate(ACaption);
 //  ���������� �����
 Tmp.Caption   := ACaption;
 Tmp.EditType  := AEditType;
 Tmp.WhereMask := AWhereMask;
 Tmp.Flags     := AFlags;
 // ����������
 FFilterCombo.Items.AddObject(ACaption, Tmp);
end;

procedure TFilterEdit.DeleteFilterItems;
begin
 FFilterCombo.Items.Clear;
end;

// ��������� �������� �������� ������
function TFilterEdit.GetTekFilterItem: TFilterItem;
begin
 Result := nil;
 // ������ ��� ��������� ��������� ������������
 try
  if (FFilterCombo.Items.Count > 0) and (FFilterCombo.ItemIndex >= 0) then
   Result := TFilterItem(FFilterCombo.Items.Objects[FFilterCombo.ItemIndex]);
 except end;
end;

procedure TFilterEdit.FOnComboBoxClick(Sender: TObject);
begin
 // ��������� ��������� ���������
 if (TekFilterItem = nil) then begin
  FFilterEdit2.Visible := false;
 end else begin
  case (TekFilterItem.Flags and 3) of
   0 : begin                               // ���� ����� �� ���������
        FFilterEdit2.Visible := false;
        FFilterEdit1.Visible  := false;
       end;
   1 : begin                               // ���� ���� �����
        FFilterEdit2.Visible := false;
        FFilterEdit1.Visible  := true;
       end;
   2 : begin                               // ��� ���� �����
        FFilterEdit2.Visible := true;
        FFilterEdit1.Visible  := true;
       end;
  end;
 end;
 // ������������ � ��������� �������� ����
 AlignElements;
 // ������������
 if AutoValidate then
  ValidateValue;
 Repaint;
end;

function TFilterEdit.ValidateValue: boolean;
var
 Res : boolean;
begin
 try
   Result := false;
   FEdit1OK := false; FEdit2OK := false;
   ErrorMessage := '';
   // ��� ����������
   if (TekFilterItem = nil) then  begin
    ErrorMessage := '$AVZ0471';
    exit;
   end;
   // ���������� �������� �����
   if (TekFilterItem.Flags and 4) > 0 then begin
    Result := true;
    exit;
   end;
   // ������
   if TekFilterItem.EditType = fetString then begin
    if not(Trim(FilterText1) <> '') then begin
     ErrorMessage := '$AVZ0469';
     exit;
    end;
   end;
   // ���� �����
   if TekFilterItem.EditType = fetNumber then begin
    if not CheckNumberValue(FilterText1) then begin
     ErrorMessage := '$AVZ0510';
     exit;
    end;
   end;
   // ������ �����
   if TekFilterItem.EditType = fetNumberList then begin
    if not CheckNumberValues(FilterText1) then begin
     ErrorMessage := '$AVZ0511';
     exit;
    end;
   end;
   // �������� �����
   if TekFilterItem.EditType = fetNumberDiapazon then begin
    Res := true;
    if not CheckNumberValue(FilterText1) then begin
     ErrorMessage := '$AVZ0507';
     Res := false;
    end else FEdit1OK := true;
    if not CheckNumberValue(FilterText2) then begin
     ErrorMessage := '$AVZ0506';
     Res := false;
    end else FEdit2OK := true;
    if not(res) then exit;
    if StrToFloat(Trim(FilterText1)) > StrToFloat(Trim(FilterText2)) then begin
     ErrorMessage := '$AVZ0354';
     FEdit1OK := false; FEdit2OK := false;
    end;
   end;
   // ���� ����
   if TekFilterItem.EditType = fetDate then begin
    if not CheckDateValue(FilterText1) then begin
     ErrorMessage := '$AVZ0503';
     exit;
    end;
   end;
   // �������� ���
   if TekFilterItem.EditType = fetDateDiapazon then begin
    if not CheckDateValue(FilterText1) then begin
     ErrorMessage := '$AVZ0505';
     exit;
    end else FEdit1OK := true;
    if not CheckDateValue(FilterText2) then begin
     ErrorMessage := '$AVZ0504';
     exit;
    end else FEdit2OK := true;
   end;
   Result := true;
   FEdit1OK := true; FEdit2OK := true;
 finally
  ErrorMessage := DoTranslate(ErrorMessage);
  FFilterEdit1.Hint := ErrorMessage;
  FFilterEdit2.Hint := ErrorMessage;
 end;
end;

// ��������� �������� ��������
function TFilterEdit.CheckNumberValue(S: string): boolean;
begin
 result := false;
 S := trim(s);
 // �������� �����������
 if S = '' then exit;
 // �������� ������������
 try
  S := StringReplace(S, '.', DecimalSeparator, []);
  StrToFloat(S);
  Result := true;
 except
  // ���������� ��������� � ������ ������ ����������� ������ � �����
 end;
end;

// ��������� ������ �������� ��������
function TFilterEdit.CheckNumberValues(S: string): boolean;
var
 st : string;
begin
 Result := false;
 s := trim(s) + ',';
 while pos(',', s) > 0 do begin
  st := copy(s, 1, pos(',', s)-1);
  if not CheckNumberValue(st) then
   exit;
  Delete(s, 1, pos(',', s));
 end;
 Result := true;
end;

// ������������ �������
function TFilterEdit.GetSQL: string;
var
 Text1, Text2 : string;
begin
 Result := '';
 if not(FCaptionLabel.Checked) or not(ValidateValue) then exit;
 result := TekFilterItem.WhereMask;
 Text1 := Trim(FilterText1);
 Text2 := Trim(FilterText2);
 if FilterEditMode =  femString then begin
  Text1 := StringReplace(Text1, '*', '%',[rfReplaceAll]); Text1 := StringReplace(Text1, '?', '_', [rfReplaceAll]);
  Text2 := StringReplace(Text2, '*', '%',[rfReplaceAll]); Text2 := StringReplace(Text2, '?', '_', [rfReplaceAll]);
 end;
 // ����������� �����
 Result := StringReplace(Result, '{FLD}', FieldName, [rfReplaceAll, rfIgnoreCase]);
 Result := StringReplace(Result, '{X}',  Text1, [rfReplaceAll, rfIgnoreCase]);
 Result := StringReplace(Result, '{X1}', Text1, [rfReplaceAll, rfIgnoreCase]);
 Result := StringReplace(Result, '{X2}', Text2, [rfReplaceAll, rfIgnoreCase]);
end;

// ��������� (����������� ��� ������ �������������)
procedure TFilterEdit.Paint;
begin
  inherited;
  if not(FilterOn) then exit;
  if not FEdit1OK then
   UnderlineComponent(FFilterEdit1);
  if not FEdit2OK then
   UnderlineComponent(FFilterEdit2);
end;

// ��������� ������� ��������� ����� ��� ��������� �����������
procedure TFilterEdit.UnderlineComponent(ACmp: TControl);
var
 i, x, y, dy, line_width : integer;
begin
 // ��� ���������� ���������� ��������� �����������
 if not ACmp.Visible then exit;
 Canvas.pen.Color := clRed;
 line_width := ACmp.Width;
 y := ACmp.Height + ACmp.Top + 2;
 dy := 2;
 // ��������� �����
 for i := 1 to line_width div 4 do begin
  x := ACmp.Left + i*4;
  Canvas.MoveTo(x - 4, y + dy);
  Canvas.LineTo(x - 2, y - dy);
  Canvas.LineTo(x, y + dy);
 end;
end;

procedure TFilterEdit.FOnEditChange(Sender: TObject);
begin
 if csLoading in ComponentState then exit;
 if AutoValidate then begin
  ValidateValue;
  Repaint;
 end;
end;

procedure TFilterEdit.Resize;
begin
  inherited;
  AlignElements;
end;

procedure TFilterEdit.SetAutoValidate(const Value: boolean);
begin
  FAutoValidate := Value;
  if FAutoValidate then
   ValidateValue;
  Repaint;
end;

function TFilterEdit.CheckDateValue(S: string): boolean;
var
 DayS, MonS, YearS : string;
begin
 Result := false;
 S := Trim(S);
 // �������� �����������
 if S = '' then exit;
 S := S + '....';
 DayS  := copy(S, 1, pos('.',S)-1); delete(S, 1, pos('.',S));
 MonS  := copy(S, 1, pos('.',S)-1); delete(S, 1, pos('.',S));
 YearS := copy(S, 1, pos('.',S)-1); delete(S, 1, pos('.',S));
 if Not(CheckNumberValue(DayS) and CheckNumberValue(MonS) and CheckNumberValue(YearS)) then
  exit;
 if (StrToInt(YearS) < 1800) or (StrToInt(YearS) > 2200) then
  exit;
 try
  EncodeDate(StrToInt(YearS), StrToInt(MonS), StrToInt(DayS));
  Result := true;
 except
  result := true;
 end;
end;

function TFilterEdit.CheckDateValues(S: string): boolean;
var
 st : string;
begin
 Result := false;
 s := trim(s) + ',';
 while pos(',', s) > 0 do begin
  st := copy(s, 1, pos(',', s)-1);
  if not CheckDateValue(st) then
   exit;
  Delete(s, 1, pos(',', s));
 end;
 Result := true;
end;

function TFilterEdit.GetButtonVisible: boolean;
begin
 Result := true;
end;

function TFilterEdit.GetTextStateDescr: string;
var
 Lines : TStringList;
begin
 Lines := TStringList.Create;
 if FilterOn then
  Lines.add('on=1') else Lines.add('on=0');
 Lines.add('mode='+inttostr(FFilterCombo.ItemIndex));
 Lines.add('ed1='+FilterText1);
 Lines.add('ed2='+FilterText2);
 Result := Lines.CommaText;
end;

procedure TFilterEdit.SetTextStateDescr(const Value: string);
var
 Lines : TStringList;
begin
 Lines := TStringList.Create;
 try
  Lines.CommaText := Value;
  FilterOn := Lines.Values['on'] = '1';
  FFilterCombo.ItemIndex := StrToInt(Lines.Values['mode']);
  FOnComboBoxClick(FFilterCombo);
  FilterText1  := Lines.Values['ed1'];
  FilterText2 := Lines.Values['ed2'];
 except end;
end;

function TFilterEdit.GetTekFilterItemIndex: integer;
begin
 Result := FFilterCombo.ItemIndex;
end;

function TFilterEdit.GetFilterText1: string;
begin
 if FHiddenValuesMode then
  Result := FHiddenFilterText1
 else
  Result := FFilterEdit1.Text;
end;

function TFilterEdit.GetFilterText2: string;
begin
 if FHiddenValuesMode then
  Result := FHiddenFilterText2
 else
  Result := FFilterEdit2.Text;
end;

procedure TFilterEdit.SetFilterText1(const Value: string);
begin
 FFilterEdit1.Text := value;
 if FAutoValidate then
  ValidateValue;
end;

procedure TFilterEdit.SetFilterText2(const Value: string);
begin
 FFilterEdit2.Text := value;
 if FAutoValidate then
  ValidateValue;
end;

procedure TFilterEdit.SetDefaultFilterItem(const Value: integer);
begin
  FDefaultFilterItem := Value;
  SetFilterEditMode(FFilterEditMode);
end;

procedure TFilterEdit.SetFilterItemsNull(const Value: boolean);
begin
  FFilterItemsNull := Value;
  SetFilterEditMode(FFilterEditMode);
end;

procedure TFilterEdit.SetFilterReadOnly(const Value: boolean);
begin
 FFilterReadOnly := Value;
 FFilterEdit1.ReadOnly := Value;
 FFilterEdit2.ReadOnly := Value;
end;

procedure TFilterEdit.SetHiddenFilterText1(const Value: string);
begin
 FHiddenFilterText1 := Value;
 if FAutoValidate then
  ValidateValue;
end;

procedure TFilterEdit.SetHiddenFilterText2(const Value: string);
begin
 FHiddenFilterText2 := Value;
 if FAutoValidate then
  ValidateValue;
end;

procedure TFilterEdit.SetHiddenValuesMode(const Value: boolean);
begin
 FHiddenValuesMode := Value;
 if FAutoValidate then
  ValidateValue;
end;

procedure TFilterEdit.SetButtonsVisible(const Value: boolean);
begin
 FButtonsVisible := Value;
 AlignElements;
end;

procedure TFilterEdit.SetOnButtonClick(const Value: TOnButtonClickEvent);
begin
  FOnButtonClick := Value;
end;

procedure TFilterEdit.SpeedButtonClick(Sender: TObject);
begin
 if not(Assigned(FOnButtonClick)) then exit;
 if Sender = FFilterEdit1b then
  FOnButtonClick(Self, 1);
 if Sender = FFilterEdit2b then
  FOnButtonClick(Self, 2);
end;

procedure TFilterEdit.SetButtonsHint(const Value: string);
begin
 FButtonsHint := Value;
 if FButtonsVisible then begin
  if FFilterEdit1b <> nil then  FFilterEdit1b.Hint := Value;
  if FFilterEdit2b <> nil then  FFilterEdit2b.Hint := Value;
 end;
end;

procedure TFilterEdit.SetFilterEditTranslateEvent(
  const Value: TFilterEditTranslateEvent);
begin
  FFilterEditTranslateEvent := Value;
end;

function TFilterEdit.DoTranslate(S: string): string;
begin
 Result := S;
 if Assigned(FFilterEditTranslateEvent) then
  Result := FFilterEditTranslateEvent(Self, S);
end;

end.
