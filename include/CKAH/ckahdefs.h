#ifndef __CKAHDEFS_H__
#define __CKAHDEFS_H__

namespace CKAHUM
{
	// ���� �������� ������� 
	enum OpResult
	{
		srOK,								// ��� ������
		srNeedReload,						// ���������� ������� Reload ��� ���������� (�������� ������ �����)
		srInvalidArg,						// �������� ��������
		srManifestNotFound,					// ���� ��������� �� ���������� ���� �� ������
		srWrongManifestFormat,				// ��������� ������ ��� ������� ��������� ��-�� ������������� �������
		srErrorReadingPersistentManifest,	// ��������� ������ ��� ������ ��������� �� �������� ���������
		srNeedReboot,						// ��������� ������������
		srNotStarted,						// ��������� �� �������
		srAlreadyStarted,					// ��������� ��� �������
		srNoPersistentManifest,				// ����������� persistent ��������� (������� Initialize �� ���� �������)
        srInsufficientBuffer,               // 
		
		srOpFailed,							// �������� ������ ���������
	};

	// ������� �����������
	enum LogLevel
	{
		lError = 1,
		lWarning = 2,
		lInfo = 3
	};

}; //namespace CKAHUM


#endif