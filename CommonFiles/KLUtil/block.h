#ifndef __BLOB_H
#define __BLOB_H

#include "defs.h"
#include <string>

namespace KLUTIL
{

//! ������� ������ ��������� �� ������ � ��������.
class KLUTIL_API CBlockBase
{
private:
	char*  m_pData;
	size_t m_nDataSize;
	friend class CBlock;
public:
	CBlockBase(const CBlockBase& t) throw();
	//! "�����������" ��� ������.
	CBlockBase(const void* pData, size_t nDataSize) throw();
	//! ��������� �������� ������ � HEX ������������� (����� ���� ������).
	std::string	GetHex() const;
	//! ���������� ������ ��� ������.
	std::string   ToString() const;
	//! ���������� ��������� �� ������ ������.
	const void*	GetData() const throw() { return m_pData; }
	//! ���������� ������ ������.
	size_t	GetDataSize() const throw() { return m_nDataSize; }
};

//! �������� ���� (�������� ���������� ������).
class KLUTIL_API CBlock: public CBlockBase
{
public:
	CBlock() throw();
	CBlock(const CBlockBase& blob);
	CBlock(const CBlock& blob);
	//! �������� ��� ������.
	CBlock(const void* pData, size_t nDataSize);
	//! ����������� nReserveSize ������, ������ ������ ����� 0.
	CBlock(size_t nReserveSize);
	//! ��������� �� Hex � �������� ������.
	//!   \throw runtime_error � ������ ��������� HEX �������.
	CBlock(const std::string& szHexData);
	~CBlock();
	//! �������� ������ ������.
	void	Clear() throw();
	//! �������� ������ � ������.
	void	ClearSecure() throw();
	//! ������ ��������� �� ����� nSize ������.
	void	MakeAvailable(size_t nSize);
	//! ����������� ����� ����� ������ �� ����� nReserveSize ������.
	void	MakeReserve(size_t nReserveSize);
	//! ������������� ������ ����� ������.
	void	SetSize(size_t nSize, char fill = 0);
	//! ���������� ��������� �� ������ ������.
	void*	GetData() throw();
	//! ���������� ��������� �� ������ ������.
	const void*	GetData() const throw() { return CBlockBase::GetData(); }
	//! ���������� ��������� �� ������ ����������������� ����.
	void*	GetDataEnd() throw();
	//! ���������� ��������� ������ ����� ������ (���������� � AddDataSize).
	size_t	GetReserveSize() const throw();
	//! ���������� ��������� ������.
	size_t	GetAllocatedSize() const throw();
	void	AppendData(size_t nDataSize, const void* pData);
	//! ��������� � ������� ������ nAddSize.
	void	AddDataSize(int nAddSize) throw();
	//! �������� � rBlob ��� ������ (rBlob.m_pData = NULL).
	void	operator <<(CBlock& rBlob) throw();
	//! ����������� ��������� �� ������.
	void	AttachData(void* pData, size_t nDataSize) throw();
	//! �������� � this ��� ������ (this.m_pData = NULL), ����� delete[] x;
	void*	DetachData() throw();
private:
	size_t m_nAllocatedSize;
};

//! ���������� �������� ���� (������� ������ ��� ����������).
class KLUTIL_API CSecBlock: public CBlock
{
public:
	CSecBlock() throw();
	CSecBlock(const CBlockBase& blob);
	CSecBlock(const void* pData, size_t nDataSize);
	CSecBlock(size_t nReserveSize);
	//! ��������� �� Hex � �������� ������.
	//!   \throw runtime_error � ������ ��������� HEX �������.
	CSecBlock(const std::string& szHexData);
	~CSecBlock();
};

} // namespace KLUTIL

#endif