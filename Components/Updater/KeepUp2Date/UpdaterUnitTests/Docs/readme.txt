��ࠬ���� ����᪠ ��������� ��ப� UnitTest.exe:
-ini		���� � 䠩�� ���䨣��樨
-log		���� � 䠩�� ����� ����ᮢ �������

��ࠬ���� 䠩�� ���䨣��樨 UnitTest.exe

[TESTCLASSES]		����� � ���筥� ����ᮢ ��� ���஢����
FileTransaction		FileTransaction
LocalFile		LocalFile
NetCore			NetCore, NetTransfer, NetFTP, netSMB
UpdaterTransaction	UpdaterTransaction

[COMMON]		����� ���� ��ࠬ��஢
BaseFolder		������ ��⠫�� �� �����쭮� ��設� ��� ࠡ��� ��⮢ (�� ��⠫�� ��� �⭮�⥫��!)
DiffTool		���� � ��⠫��� �⨫��� ����୮�� �ࠢ����� ��⠫����


[FILETRANSACTION]	����� ��ࠬ��஢ ��� ���஢���� FileTransaction � UpdaterTRansaction
Source          	���� � ��⠫��� ���筨��� ����������
SourceEtalon		���� � ��⠫��� �⠫���� ���筨��� ����������
Destination		���� � ��⠫��� ��� ������� 䠩���
DestinationEtalon	���� � ��⠫��� ��� �⠫���� ������� 䠩���
Backup			���� � ��⠫��� ����
BackupEtalon		���� � ��⠫��� �⠫��� ����
FilesStorage		���� � ��⠫��� 䠩��� ��� �࠭���権 ���ᨨ 1                                          	
FilesStorage2		���� � ��⠫��� 䠩��� ��� �࠭���権 ���ᨨ 2
FilesStorage3		���� � ��⠫��� 䠩��� ��� �࠭���権 ���ᨨ 3
DiffTool		���� � ��⠫��� � �⨫�⮩ �ࠢ����� 䠩���
                                                                                

[LOCALFILE]		����� ��ࠬ��஢ ��� ���஢���� LocalFile
Source          	���� � ��⠫��� ���筨��� ����������
SourceEtalon		���� � ��⠫��� �⠫���� ���筨��� ����������
Destination		���� � ��⠫��� ��� ������� 䠩���
DestinationEtalon	���� � ��⠫��� ��� �⠫���� ������� 䠩���
FilesStorage		���� � ��⠫��� 䠩��� ��� �࠭���権 ���ᨨ 1                                          	

[NETCORE]		����� ��ࠬ��஢ ��� ���஢���� NetCore, NetTransfer, NetFTP, NetSMB
Destination		���� � ��⠫��� ��� ������� 䠩���
DestinationEtalon	���� � ��⠫��� ��� �⠫���� ������� 䠩���
FilesStorage		���� � ��⠫��� 䠩��� ��� �࠭���権 ���ᨨ 1                                          	
