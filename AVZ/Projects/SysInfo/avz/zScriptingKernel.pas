unit zScriptingKernel;
// ������-����
interface
uses
  Types,
  SysUtils,
  Windows,
  zUserScripting;
threadvar
 // ������-������
 AvzUserScript : TAvzUserScript;

// ������������� ����
function InitScriptingKernel : boolean;

implementation

// ������������� ����
function InitScriptingKernel : boolean;
begin
 // �������� ������ ������-������
 AvzUserScript := TAvzUserScript.Create;
end;

end.
 
