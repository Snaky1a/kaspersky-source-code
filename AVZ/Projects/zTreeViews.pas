unit zTreeViews;

interface
uses
 Windows, Messages, Classes, Controls, ComCtrls, ShellApi;
type
  // ������� "������ �� ������ �������"
  TOnTreeNodeStateIconClick    = procedure(Sender : TObject; Node : TTreeNode) of object;
  TOnNewTreeNodeSetState       = procedure(Sender : TObject; Node, NewNode : TTreeNode; var State : integer) of object;

  // ����� "������" (��� �������� ������������ ������)
  TZStringClass = class
   Text : string;
   constructor Create(AText : String);
  end;

  // ������  ����-������ ��� ����� ����������� �� ��������
  TZCheckTreeView = class(TTreeView)
  private
    FOnTreeNodeStateIconClick: TOnTreeNodeStateIconClick;
    procedure SetOnTreeNodeStateIconClick(
      const Value: TOnTreeNodeStateIconClick);
  protected
   procedure CreateParams(var Params: TCreateParams); override;
   procedure WMLButtonDown(var Message: TWMLButtonDown); message WM_LBUTTONDOWN;
   procedure WMLButtonDblClk(var Message: TWMLButtonDblClk); message WM_LBUTTONDBLCLK;
  public
   procedure SetChildNodesState(ANode : TTreeNode; ANewState : integer);
  published
   // ������� "������ �� ������ �������"
   property OnTreeNodeStateIconClick : TOnTreeNodeStateIconClick read FOnTreeNodeStateIconClick write SetOnTreeNodeStateIconClick;
  end;

  // ������, ������������ ����� �������
  TZShellTreeView = class(TZCheckTreeView)
   function CanExpand(Node: TTreeNode): Boolean; override;
  private
    FIconsImageList : TImageList;
    FOnNewTreeNodeSetState: TOnNewTreeNodeSetState;
    procedure SetOnNewTreeNodeSetState(
      const Value: TOnNewTreeNodeSetState);
  public
   constructor Create(AOwner: TComponent); override;
   // ���������� ����� � ������ ������
   function AddRootFolder(AName : string) : boolean;
   // ��������� ���� � ����� (� �������������)
   function GetPath(ATreeNode : TTreeNode) : string;
   // ����� ����� � ������
   function SearchDirNode(AName : string) : TTreeNode;
  published
   property OnNewTreeNodeSetState : TOnNewTreeNodeSetState read FOnNewTreeNodeSetState write SetOnNewTreeNodeSetState;
  end;

procedure Register;

implementation
uses SysUtils, ZUtil;
{ TZShellTreeView }

procedure Register;
begin
  RegisterComponents('Samples', [TZCheckTreeView, TZShellTreeView]);
end;

// ��������� ���� ������ ��� ��������� ����
function GetShellImage(APath : string; Large, Open: Boolean): Integer;
var
  FileInfo: TSHFileInfo;
  Flags: Integer;
begin
  Flags := SHGFI_SYSICONINDEX;
  if Open then Flags := Flags or SHGFI_OPENICON;
  if Large then Flags := Flags or SHGFI_LARGEICON
   else Flags := Flags or SHGFI_SMALLICON;
  SHGetFileInfo(PChar(APath),
                0,
                FileInfo,
                SizeOf(FileInfo),
                Flags);
  Result := FileInfo.iIcon;
end;

function TZShellTreeView.AddRootFolder(AName: string): boolean;
var
 FileInfo: TSHFileInfo;
 Tmp : TTreeNode;
begin
 Result := true;
 // �������� ������ ����
 Tmp := Items.AddChild(nil, AName);
 Tmp.HasChildren := true;
 // ������������ ����
 AName := NormalNameDir(AName);
 // ����������� �������� ������
 Tmp.ImageIndex    := GetShellImage(AName+'\', false, false);
 Tmp.SelectedIndex := GetShellImage(AName+'\', false, true);
 // ����� ���� ��������� ����������
 Tmp.StateIndex := 1;
 // ���������� ���� � ����������� �������
 Tmp.Data       := TZStringClass.Create(AName);
 // ���������� ��������� �������� ���� � ����������� ���
 SHGetFileInfo(PChar(AName+'\'),
                0,
                FileInfo,
                SizeOf(FileInfo),
                SHGFI_DISPLAYNAME);
 Tmp.Text := FileInfo.szDisplayName;
end;

// ��������, ���� �� � ����� �����������
function SubDirFound(APath : string) : boolean;
var
 SR   : TSearchRec;
 Res  : integer;
begin
 Result := false;
 // ����� �����
 Res := FindFirst(APath+'\*.*', faDirectory or faHidden or faReadOnly or faSysFile or faArchive, SR);
 while Res = 0 do begin
  if ((SR.Attr and faDirectory) <> 0) then
   if (SR.Name <> '.') and (SR.Name <> '..') then begin
    Result := true;
    Break;
   end;
  Res := FindNext(SR);
 end;
 FindClose(SR);
end;

function TZShellTreeView.CanExpand(Node: TTreeNode): Boolean;
var
 SR   : TSearchRec;
 Path : String;
 Tmp  : TTreeNode;
 Res, StateIndex  : integer;
 DirFound : boolean;
 FileInfo: TSHFileInfo;
begin
 if Node.Count > 0 then begin
  Result := true;
  exit;
 end;
 // ���������� ����
 Path := GetPath(Node);
 // ����� �����
 Res := FindFirst(Path+'\*.*', faDirectory or faHidden or faReadOnly or faSysFile or faArchive, SR);
 DirFound := false;
 while Res = 0 do begin
  if ((SR.Attr and faDirectory) <> 0) then
   if (SR.Name <> '.') and (SR.Name <> '..') then begin
    Tmp := (Node.TreeView as TTreeView).Items.AddChild(Node, SR.Name);
    //Tmp.HasChildren := SubDirFound(Path+'\'+SR.Name);
    Tmp.HasChildren := true;
    DirFound := true;
    Tmp.ImageIndex    := 0;
    Tmp.SelectedIndex := 1;
    Tmp.Data          := nil;
    StateIndex    := Node.StateIndex;
    if Assigned(FOnNewTreeNodeSetState) then
     FOnNewTreeNodeSetState(Self, Node, Tmp, StateIndex);
    Tmp.StateIndex    := StateIndex;
    Tmp.ImageIndex    := GetShellImage(Path + '\' + SR.Name, false, false);
    Tmp.SelectedIndex := GetShellImage(Path + '\' + SR.Name, false, true);
   end;
  Res := FindNext(SR);
 end;
 FindClose(SR);
 // ����������
 if DirFound then
  Node.AlphaSort(true);
 Result           := DirFound;
 Node.HasChildren := DirFound;
end;

constructor TZShellTreeView.Create(AOwner: TComponent);
var
 FileInfo: TSHFileInfo;
 Tmp : TTreeNode;
begin
 inherited;
 FIconsImageList := TImageList.Create(nil);
 FIconsImageList.ShareImages := true;
 FIconsImageList.Handle := SHGetFileInfo('',
                                         0, FileInfo, SizeOf(FileInfo),
                                         SHGFI_SYSICONINDEX or SHGFI_SMALLICON);
 Images      := FIconsImageList;
end;

procedure TZCheckTreeView.WMLButtonDblClk(var Message: TWMLButtonDblClk);
var
 Tmp : TTreeNode;
begin
 // �����, ���� �� � ����� ����� ����� ������
 Tmp := GetNodeAt(Message.XPos, Message.YPos);
 // ����� ������ ��� - ����� ������������� ����������� � �����
 if Tmp = nil then begin
  inherited;
  exit;
 end;
 // ����� ���� - ��������, �� ����� �� ������ � ���� ������ ������� (���� ����� - ����� ���)
 if (htOnStateIcon in GetHitTestInfoAt(Message.XPos, Message.YPos)) then begin
  Message.Msg := 0;
  exit;
 end;
 inherited;
end;

procedure TZCheckTreeView.WMLButtonDown(var Message: TWMLButtonDown);
var
 Tmp : TTreeNode;
begin
 // �����, ���� �� � ����� ����� ����� ������
 Tmp := GetNodeAt(Message.XPos, Message.YPos);
 // ����� ��� - ����� ��������� ����������� � �����
 if Tmp = nil then begin
  inherited;
  exit;
 end;
 // ���� �������� �� ������ ��������� ?
 if (htOnStateIcon in GetHitTestInfoAt(Message.XPos, Message.YPos)) then begin
  // ����� �����������
  if Assigned(FOnTreeNodeStateIconClick) then
   FOnTreeNodeStateIconClick(Self, Tmp);
  Message.Msg := 0;
  exit;
 end;
 inherited;
end;

function TZShellTreeView.GetPath(ATreeNode: TTreeNode): string;
var
 tmp : TTreeNode;
begin
 Result := '';
 // ���������� ����
 Tmp := ATreeNode;
 while Tmp <> nil do begin
  // ���������� �����������
  if Result <> '' then Result := '\' + Result;
  // ���������� ���������� �������� (��� ��� �������� � ������ ��� ��������� �������)
  if Tmp.Data = nil then
   Result := Tmp.Text + Result
    else Result := TZStringClass(Tmp.Data).Text + Result;
  // ������� �� ������� ����
  Tmp := Tmp.Parent;
 end;
end;

function TZShellTreeView.SearchDirNode(AName: string): TTreeNode;
var
 i, j : integer;
 Tmp : TTreeNode;
 Res : boolean;
begin
 Result := nil;
 Tmp    := nil;
 AName := NormalDir(LowerCase(AName));
 for i := 0 to Items.Count - 1 do
  if (Items[i].Parent = nil) then
   if pos(NormalDir(LowerCase(GetPath(Items[i]))), AName) = 1 then begin
    Tmp := Items[i];
    break;
   end;
 // ���������� ��� - �����
 if Tmp = nil then exit;
 while (true) do begin
  // ���� ��������� ??
  if NormalDir(LowerCase(GetPath(Tmp))) = AName then begin
   Result := Tmp;
   exit;
  end;
  // ���� �� ������, ���������� �����
  Tmp.Expand(false);
  Res := false;
  for i := 0 to Tmp.Count-1 do
   if pos(NormalDir(LowerCase(GetPath(Tmp.Item[i]))), AName) = 1 then begin
    Tmp := Tmp.Item[i];
    Res := true;
    Break;
   end;
   // ����� ������� � ���� ������ ??
   if not(Res) then exit;
 end;
end;

procedure TZShellTreeView.SetOnNewTreeNodeSetState(
  const Value: TOnNewTreeNodeSetState);
begin
  FOnNewTreeNodeSetState := Value;
end;

{ TZStringClass }

constructor TZStringClass.Create(AText: String);
begin
 Text := AText;
end;

{ TZCheckTreeView }

procedure TZCheckTreeView.SetOnTreeNodeStateIconClick(
  const Value: TOnTreeNodeStateIconClick);
begin
  FOnTreeNodeStateIconClick := Value;
end;

procedure TZCheckTreeView.CreateParams(var Params: TCreateParams);
begin
  inherited;
end;

procedure TZCheckTreeView.SetChildNodesState(ANode: TTreeNode;
  ANewState: integer);
var
 i : integer;
begin
 if ANode.Count <= 0 then exit;
 for i := 0 to ANode.Count-1 do begin
  ANode.Item[i].StateIndex := ANewState;
  SetChildNodesState(ANode.Item[i], ANewState);
 end;
end;

end.
