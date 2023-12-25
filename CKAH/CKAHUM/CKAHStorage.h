#if !defined(AFX_CKAHSTORAGE_H__A5A05CC4_95EB_430E_80A3_487E55CB561B__INCLUDED_)
#define AFX_CKAHSTORAGE_H__A5A05CC4_95EB_430E_80A3_487E55CB561B__INCLUDED_

#include <CKAH/ckahumdefs.h>

// ��������� ��� ������ � persistent storage
class CCKAHStorage
{
public:
	//
	// ����� ���������� ����� ���:
	//
	// Name1\Name2\...\NameN
	//
	// ��� ���������� - ����-��������������� ������
	//

	// ��������� �������� szParamName � ����� szParamValue ����� nParamValueBufferLength
	// ���������� ������ ������ � ������, ��������� ��� ���������� ���������, ������� ��������� '\0'
	// 0 - � ������ ������
	// ����� ������ ����������� ����� ��������� ������, ������� � 2 � 3 ��������� 0 � NULL ��������������
	virtual DWORD GetParam (LPCWSTR IN szParamName, DWORD IN nParamValueBufferLength, LPWSTR OUT szParamValue) = 0;

	// �������� �������� szParamName �� ��������� szParamValue
	// ���������� true � ������ ������
	virtual bool SetParam (LPCWSTR IN szParamName, LPCWSTR IN szParamValue) = 0;

	// ������� ��� ��������� (��������� ����������), ������� ������ szParamValue
	virtual bool ClearParams (LPCWSTR IN szParamName) = 0;

    // ������� ��� persistent storage (�� �������������)
    virtual bool Cleanup() = 0;
};

typedef CCKAHStorage *LPCKAHSTORAGE;

//////////////////////////////////////////////////////////////////////////

// �������������� ���������� ���������� CCKAHStorage ����� ������
class CKAHUMEXPORT CCKAHRegStorageImpl : public CCKAHStorage
{
public:
	// �����������
	// hKey, szSubKey ���������� ������ ����� �������, � ������� ����� �������������
	// ������ � �����������
	CCKAHRegStorageImpl (HKEY hKey, LPCWSTR szSubKey);

	virtual ~CCKAHRegStorageImpl ();

    virtual void SetPath (HKEY hKey, LPCWSTR szSubKey);

	virtual DWORD GetParam (LPCWSTR IN szParamName, DWORD IN nParamValueBufferLength, LPWSTR OUT szParamValue);
	virtual bool SetParam (LPCWSTR IN szParamName, LPCWSTR IN szParamValue);
	virtual bool ClearParams (LPCWSTR IN szParamName);
    virtual bool Cleanup ();

protected:
	HKEY m_hKey;
	LPCWSTR m_szSubKey;
};

#endif // !defined(AFX_CKAHSTORAGE_H__A5A05CC4_95EB_430E_80A3_487E55CB561B__INCLUDED_)
