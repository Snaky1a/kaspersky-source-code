unit uFileDownloadThread;

interface

uses
  Classes, FileLoader, SysUtils;

type
  TDownloadMode = (dmDirectoty, dmFileServer, dmHTTPServer);
  TFileDownloadThread = class(TThread)
  private
   FError : string;
   procedure AddError(AMsg : string);
  protected
    procedure Execute; override;
    procedure FileCopyProgress(Sender : TObject; Size : integer);
  public
   // �����
   DownloadMode : TDownloadMode;
   ServerPath, DestPath, Filename : string;
   DownloadComplete : boolean;
   LoadedSize : integer;
   procedure ExecuteDownload;
  end;

implementation
uses OraUtil, zutil;
{ TFileDownloadThread }

procedure TFileDownloadThread.AddError(AMsg: string);
begin
 AddToList(FError, AMsg, ';');
end;

procedure TFileDownloadThread.Execute;
begin
 DownloadComplete := false;
 ExecuteDownload;
 DownloadComplete := true;
end;

procedure TFileDownloadThread.ExecuteDownload;
var
 FileLoader : TCustomFileLoader;
 Res        : boolean;
begin
 DownloadComplete := false;
 FileLoader := nil;
 LoadedSize := 0;
 // �������� ���������������� ������ ��� ������� ������
 case DownloadMode of
  dmDirectoty  : FileLoader := TDirectoryFileLoader.Create;
  dmFileServer : FileLoader := TDirectoryFileLoader.Create;
  dmHTTPServer : FileLoader := THTTPFileLoader.Create;
 end;
 // �����, ���� ��� �������� �� ��������������
 if FileLoader = nil then exit;
 // 1. �������� ���������
 ForceDirectories(DestPath);
 // 2 ��������, ������� �� ��������
 // 2.1 ��������, ������ �� ������� TempPath
 if not(DirectoryExists(DestPath)) then begin
  AddError('�� ������� ������� ������� '+DestPath);
  exit;
 end;
 try
  FileLoader.OnFileCopyProgress := FileCopyProgress;
  Res := FileLoader.LoadFile(ServerPath + Filename, DestPath + Filename);
 finally
  FileLoader.Free;
  DownloadComplete := true;
 end;
end;

procedure TFileDownloadThread.FileCopyProgress(Sender: TObject;
  Size: integer);
begin
 LoadedSize := Size;
end;

end.
