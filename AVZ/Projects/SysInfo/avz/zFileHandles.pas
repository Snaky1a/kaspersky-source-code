unit zFileHandles;

interface
uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ComCtrls, StdCtrls, winsvc, Grids, RXGrids, SystemMonitor, RxVerInf, md5,
  ValEdit, Buttons, ExtCtrls, registry, ntdll, zprocess, RXSplit, Menus,
  zPELoader, ShellAPI, zHTMLTemplate, uRegSearch, zProcessMemory,
  WinTrust;
type
 TAlternativeHandles = class
  Function RefreshHandlesList : boolean;
 end;
implementation

{ TAlternativeHandles }

function TAlternativeHandles.RefreshHandlesList: boolean;
var
  Res : NTSTATUS;
  NTDLL_DLL : THandle;
  Buf : pointer;
  BufSize, ResBufSize, i : DWORD;
  ZwQuerySystemInformation: TNativeQuerySystemInformation;
  PL1, Lines : TStrings;
  FSysProcessInfo : TSysProcessInfo;
begin
 // �������� ���������� ���������
 if ISNT then
  FSysProcessInfo := TPSAPIProcessInfo.Create else
   FSysProcessInfo := TToolHelpProcessInfo.Create;
 // �������� ���������� � ����� �������
 NTDLL_DLL := GetModuleHandle(NTDLL_DLL_name);
 // ����� �������
 if NTDLL_DLL <> 0 then @ZwQuerySystemInformation := GetProcAddress(NTDLL_DLL,'ZwQuerySystemInformation')
  else exit;
 if @ZwQuerySystemInformation = nil then exit;
 // ����� � �������� ������ �������
 BufSize := 100000;
 repeat
  GetMem(Buf, BufSize);
  ZeroMemory(Buf, BufSize);
  Res := ZwQuerySystemInformation(SystemHandleInformation, Buf, BufSize, @ResBufSize);
  if Res = STATUS_INFO_LENGTH_MISMATCH then begin
   FreeMem(Buf, BufSize);
   BufSize := BufSize * 2;
  end;
 until Res <> STATUS_INFO_LENGTH_MISMATCH;
 if Res <> STATUS_SUCCESS then exit;

 Lines       := TStringList.Create;
 PL1         := TStringList.Create;
 // ������� ������� HANDLE
 for i := 0 to TSystemHandleInformationRec(Buf^).NumberOfHandles - 1 do begin
  // TSystemHandleInformationRec(Buf^).Information[i].Handle;
 end;
 // ������������ ������
 FreeMem(Buf, BufSize);
 FSysProcessInfo.Free;
 Lines.Free;
 PL1.Free;
end;

end.
 
