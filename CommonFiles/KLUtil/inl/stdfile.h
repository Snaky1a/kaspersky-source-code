#ifndef _KLUTIL_STDFILE_H__INCLUDED_
#define _KLUTIL_STDFILE_H__INCLUDED_

#include <stdio.h>
#include <errno.h>
#include <tchar.h>
#include <wtypes.h>
#include "../except.h"
#include <string>

namespace KLUTIL
{
	
	//////////////////////////////////////////////////////////////////////////
	// CStdFile
	//////////////////////////////////////////////////////////////////////////
	
	//! �������� ����������.
	DEFINE_LIBID(EID_StdFileLib, 0xCE84, 0x4AC5, 0x8C24, 0xDD6E);
	typedef CLibExcept<EID_StdFileLib> CFileException;
	
#define THROW_FILEEX() THROW(CFileException, errno, (GetErrHead() + strerror(errno)).c_str() ) 
	
	//! ������� ������ ������������ �����.
	class CStdFile
	{
		FILE* m_f;
		std::string m_szFilename;
		std::string GetErrHead() const
		{
			return "���� \"" + m_szFilename + "\": ";    
		}
	public:
		
		CStdFile(): m_f(NULL) {}
		
		//! �����������.
		//!   \throw CFileException � ������ ���� �� ������� ������� ����.
		CStdFile(
			LPCTSTR pszFname,	//!< [in] ���� � �����.
			LPCTSTR pszAccess	//!< [in] ����� ������� (��. fopen).
			): m_f(NULL) { Open(pszFname, pszAccess); }
		
		~CStdFile() { if (m_f) fclose(m_f); }
		
		//! �������� ����.
		//!   \return \b false � ������ ���� �� ������� ������� ����. ��� ������ \b errno.
		bool TryOpen(
			LPCTSTR pszFname,	//!< [in] ���� � �����.
			LPCTSTR pszAccess	//!< [in] ����� ������� (��. fopen).
			) throw()
		{
			Close();
			m_szFilename = pszFname;
			m_f = _tfopen(pszFname, pszAccess);
			return m_f != NULL;
		}
		
		//! �������� ����.
		//!   \throw CFileException � ������ ���� �� ������� ������� ����.
		void Open(
			LPCTSTR pszFname,	//!< [in] ���� � �����.
			LPCTSTR pszAccess	//!< [in] ����� ������� (��. fopen).
			)
		{
			if (!TryOpen(pszFname, pszAccess))
				THROW_FILEEX();
		}
		
		//! ��������� ����.
		void Close() throw()
		{
			if (m_f)
			{
				fclose(m_f);
				m_f = NULL;
			}
		}
		
		operator FILE* () throw() { return m_f; }
		
		//@{
		//! ��������� ��������� ������.
		//!   \return \b false, ���� ��������� ����� �����.
		//!   \throw CFileException � ������ ������.
		bool ReadLine(
			char* pBuf,		//!< [out] ����� ��� ������.
			size_t nBufSize	//!< [in] ������ ������ \e pBuf � ������.
			)
		{
			if (fgets(pBuf, static_cast<int>(nBufSize), m_f) != NULL)
				return true;
			if (feof(m_f))
				return false;
			THROW_FILEEX();
		}
		
		bool ReadLine(
			std::string& line	//!< [out] C�����.
			)
		{
			line.swap(std::string()); // clear() missing workaround
			char buf[1024];
			if (!ReadLine(buf, sizeof(buf)))
				return false;
			do
			{
				line += buf;
				if (*line.rbegin() == '\n')
				{
					line.resize( line.size()-1 );
					return true;
				}
			} while(ReadLine(buf, sizeof(buf)));
			return true;
		}
		//@}
		
		//@{
		//! ���������� ��������� ������.
		//!   \throw CFileException � ������ ������.
		void WriteLine(
			const char* pText	//!< [in] ��������� ������.
			)
		{
			if (fputs(pText, m_f) == EOF)
				THROW_FILEEX();
		}
		
		void WriteLine(
			const std::string& text	//!< [in] ��������� ������.
			)
		{
			WriteLine(text.c_str());
		}
		//@}
		
		//! ��������� ���� ������.
		//!   \return ���������� ��������� ��������� ���������.
		//!   \throw CFileException � ������ ������.
		size_t Read(
			void* pBuf,		//!< [out] ����� ��� ������.
			size_t nItemSize,	//!< [in] ������ �������� � ������.
			size_t nItemCount	//!< [in] ������������ ���������� ��������� ��� ������.
			)
		{
			size_t res = fread(pBuf, nItemSize, nItemCount, m_f);
			if (nItemCount<=res || feof(m_f))
				return res;
			THROW_FILEEX();
		}
		
		//! ���������� ���� ������.
		//!   \throw CFileException � ������ ������.
		void Write(
			const void* pBuf,	//!< [in] ��������� �� ������.
			size_t nItemSize,	//!< [in] ������ �������� � ������.
			size_t nItemCount	//!< [in] ������������ ���������� ��������� ��� ������.
			)
		{
			if (fwrite(pBuf, nItemSize, nItemCount, m_f) != nItemCount)
				THROW_FILEEX();
		}
		
		//! �������� ��������� �� ����� �����.
		//!   \return \b true - ����� ����� ��� ���������.
		bool Eof() throw() { return feof(m_f) != 0; }
		
		//! ��������� ���� ������.
		//!   \throw CFileException � ������ ������.
		char Get()
		{
			int res = fgetc(m_f);
			if (res != EOF || feof(m_f))
				return res;
			THROW_FILEEX();
		}
		
		//! ���������� ���� ������.
		//!   \throw CFileException � ������ ������.
		void Put(
			char c	//!< [in] ������������ ������.
			)
		{
			if (fputc(c, m_f) == EOF)
				THROW_FILEEX();
		}
		
		//! ������������� ������� �������.
		//!   \throw CFileException � ������ ������.
		void Seek(
			long nOffest,		//!< [in] ���������� ������ �� ����� ������� \e nOrigin.
			int nOrigin = SEEK_SET	//!< [in] ����� �������.\n
			//!< \b SEEK_CUR �� ������� �������.\n
			//!< \b SEEK_END �� ����� �����.\n
			//!< \b SEEK_SET �� ������ �����.
			)
		{
			if (fseek(m_f, nOffest, nOrigin) != 0)
				THROW_FILEEX();
		}
		
		//! ���������� ������� �������.
		//!   \return ������� �������.
		//!   \throw CFileException � ������ ������.
		long Tell()
		{
			long res = ftell(m_f);
			if (res != -1L)
				return res;
			THROW_FILEEX();
		}
		
		//! ������������� ������� ������� �� ������.
		void Rewind() throw()
		{
			rewind(m_f);
		}
};

} // namespace KLUTIL

#endif // _KLUTIL_STDFILE_H__INCLUDED_