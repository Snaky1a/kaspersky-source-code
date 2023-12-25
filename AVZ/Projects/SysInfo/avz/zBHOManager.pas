unit zBHOManager;

interface
uses Windows, SysUtils, winsock, registry, Variants, Classes, zSharedFunctions,
  RxVerInf, zutil;
type
 // ���������� � BHO
 TBHOInfo = record
   BinFileName     : string;  // ��� ������������ �����
   Descr           : string;  // �������� (���� ����)
   BinFileExists   : boolean; // ������� ������������� ����� �� �����
   BinFileInfo     : string;  // ���������� � ����������� �����
   CheckResults    : boolean; // ���������� ��������
   RegRoot         : HKEY;    // ���� �������
   RegKEY          : string;  // ���� �������
   RegValue        : string;  // ���� ��� �������� �������, ���������������� BHO
   RegType         : integer; // ��� ����� BHO
 end;

 // �������� BHO
 TBHOManager = class
   // ������ ����������� ����
   BHOListReg  : array of  TBHOInfo;
   constructor Create;
   // ���������� �������
   function Refresh : boolean;
 end;
implementation

{ TBHOManager }

constructor TBHOManager.Create;
begin
 BHOListReg := nil;
end;

function TBHOManager.Refresh: boolean;
begin
 BHOListReg := nil;
end;

end.
