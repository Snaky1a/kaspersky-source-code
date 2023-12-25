#ifndef __LOG_H
#define __LOG_H

#include "defs.h"
#include <windows.h>
#include <string>
#include <vector>
#include <stdarg.h>
#include <tchar.h>
#include "inl/smart_ptr.hpp"
#include "inl/synchro.h"
//#include "../Stuff/thread.h"

#pragma warning (disable: 4251) // need dll-linkage

namespace KLUTIL
{
	//! ���� ���������.
	enum ELogMessageType
	{
		eLM_Error,		//!< "������" - ��������� ���� � ������, ���������� ���������� �������� �������� ����������.
		eLM_Warning,	//!< "��������������" - ��������� ���� � ������, ������� ������� ���������.
		eLM_Info,		//!< "����������" - ��������� � ���������� ���������� �������� ����������.
		eLM_Debug,		//!< "�������" - ���������, ���������� ���������� ����������.
	};

	//! ������� �������� ���������.
	enum ELogMessageLevel
	{
		L0 = 0,	//!< �������� ������.
		L1 = 1,
		L2 = 2,
		L3 = 3,
		L4 = 4,
		L5 = 5,
		LMAX = 255
	};

	//! ��������� "�����������" ����. ������������ ������ �� ��������.
	class KLUTIL_API ILogMedia
	{
	public:
		virtual ~ILogMedia() {}
		//! ���������� ���������.
		virtual void Write(
			ELogMessageType type,	//!< [in] ��� ���������.
			ELogMessageLevel nLevel,//!< [in] ������� �������� (L0 - �������� ������).
			LPCTSTR pszDate,		//!< [in] ���� ������ ���������.
			LPCTSTR pszTime,		//!< [in] ����� ������ ���������.
			LPCTSTR pszThreadId,	//!< [in] ������������� ������, �� �������� �������� ���������.
			LPCTSTR pszThreadName,	//!< [in] ��� ������, �� �������� �������� ���������.
			LPCTSTR pszModule,		//!< [in] ������, �� �������� �������� ���������.
			LPCTSTR pszMessage		//!< [in] ���������.
			) = 0;
		//! ���������, ��������� ��� ������������ ���������.
		//!   \return false - ��������� ������������.
		virtual bool Check(
			ELogMessageType type,	//!< [in] ��� ���������.
			ELogMessageLevel nLevel,//!< [in] ������� �������� (L0 - �������� ������).
			LPCTSTR pszModule		//!< [in] ������, �� �������� �������� ���������.
			)
		{
			type; nLevel; pszModule;
			return true;
		};
		//! ����������, �������� �� ���.
		//! ���� ��� ��� �������� ������ (��������, ������ ��� �����), ������ �� ���� ����� �����.
		virtual bool IsWorking() const { return true; }
	};

	typedef boost::shared_ptr<ILogMedia> TLogMediaPtr;

	//! ���-��������.
	class KLUTIL_API CLogMediaProxy: public ILogMedia
	{
	public:
		CLogMediaProxy(const TLogMediaPtr& pLog = TLogMediaPtr());
		~CLogMediaProxy();
		void SetLog(const TLogMediaPtr& pLog);
		virtual void Write(ELogMessageType type, ELogMessageLevel nLevel, LPCTSTR pszDate, LPCTSTR pszTime, LPCTSTR pszThreadId, LPCTSTR pszThreadName, LPCTSTR pszModule, LPCTSTR pszMessage);
		virtual bool Check(ELogMessageType type, ELogMessageLevel nLevel, LPCTSTR pszModule);
	private:
		TLogMediaPtr m_pLog;
		CCritSec m_cs;
	};

	//! ����������� "����������" �����.
	class KLUTIL_API CLogMediaColl: public ILogMedia
	{
		typedef std::vector<TLogMediaPtr> TMediaColl;
	public:
		CLogMediaColl();
		~CLogMediaColl();
		void Add(const TLogMediaPtr& pMedia);
		virtual void Write(ELogMessageType type, ELogMessageLevel nLevel, LPCTSTR pszDate, LPCTSTR pszTime, LPCTSTR pszThreadId, LPCTSTR pszThreadName, LPCTSTR pszModule, LPCTSTR pszMessage);
		virtual bool Check(ELogMessageType type, ELogMessageLevel nLevel, LPCTSTR pszModule);
	private:
		TMediaColl m_MediaColl;
		CCritSec m_cs;
	};

	//! ��������� ���������� ��������� ����.
	class KLUTIL_API IFilter
	{
	public:
		virtual ~IFilter() {}
		//! ���������, ��������� ��� ������������ ���������.
		//!   \return false - ��������� ������������.
		virtual bool Check(
			ELogMessageType& type,		//!< [in/out] ��� ���������.
			ELogMessageLevel& nLevel,	//!< [in/out] ������� �������� (L0 - �������� ������).
			LPCTSTR pszModule			//!< [in] ������, �� �������� �������� ���������.
			) = 0;
	};

	typedef boost::shared_ptr<IFilter> TFilterPtr;

	//! ������ �� ���� � ������ ���������.
	//! ��������� ��������� ����� ������������� ���� � ��������� ���������� ���� � ��������� �� ���� ���������.
	class KLUTIL_API CTypeLevelFilter: public IFilter
	{
		ELogMessageType m_type;
		ELogMessageLevel m_nLevel;
	public:
		//! �����������.
		CTypeLevelFilter(
			ELogMessageType type = eLM_Info,	//!< [in] ��������� ��������� ����������ee type.
			ELogMessageLevel nLevel = LMAX	//!< [in] ��������� ���� type � ��������� �� ���� nLevel.
			): m_type(type), m_nLevel(nLevel) {}
		virtual bool Check(ELogMessageType& type, ELogMessageLevel& nLevel, LPCTSTR)
		{
			return type < m_type || (type == m_type && nLevel <= m_nLevel);
		}
	};

	//! ����������� ���.
	class KLUTIL_API CFilterLogMedia: public ILogMedia
	{
		typedef std::vector<TFilterPtr> TFilterColl;
	public:
		//! �����������.
		CFilterLogMedia(
			const TLogMediaPtr& pMedia	//!< [in] ���, �� ������� ������������� ������.
			);
		virtual ~CFilterLogMedia();
		//! ��������� ������.
		void AddFilter(
			TFilterPtr pFilter	//!< [in] ������.
			);
		virtual void Write(ELogMessageType type, ELogMessageLevel nLevel, LPCTSTR pszDate, LPCTSTR pszTime, LPCTSTR pszThreadId, LPCTSTR pszThreadName, LPCTSTR pszModule, LPCTSTR pszMessage);
		virtual bool Check(ELogMessageType type, ELogMessageLevel nLevel, LPCTSTR pszModule);

	private:
		TLogMediaPtr m_pMedia;
		TFilterColl m_FilterColl;
		CCritSec m_cs;
	};

	//! ��������� �������� ����.
	struct KLUTIL_API CLogParam
	{
		CLogParam(
			TLogMediaPtr pMedia = TLogMediaPtr(),	//!< [in]
			LPCTSTR pszModule = NULL	//!< [in]
			): m_pMedia(pMedia), m_pszModule(pszModule) {}
		TLogMediaPtr m_pMedia;
		LPCTSTR m_pszModule;
	};

	//! "����������" ���.
	class KLUTIL_API CLogBase
	{
	public:
		virtual ~CLogBase();
		//! ���������� "����������" ��� ������� ����.
		TLogMediaPtr GetMedia() const throw() { return m_pMedia; }

		//! ���������� ��������������� ���������.
		void Write(
			ELogMessageType type,	//!< [in] ��� ���������.
			ELogMessageLevel nLevel,//!< [in] ������� �������� (L0 - �������� ������).
			LPCTSTR pszMessage,		//!< [in] ���������.
			...
			) throw()
		{
			va_list ap;
			va_start(ap, pszMessage);
			WriteVA(type, nLevel, NULL, pszMessage, ap);
			va_end(ap);
		}

		//! ���������� ��������������� Unicode-���������.
		void WriteW(
			ELogMessageType type,	//!< [in] ��� ���������.
			ELogMessageLevel nLevel,//!< [in] ������� �������� (L0 - �������� ������).
			LPCWSTR pszModule,		//!< [in] ��� ������. (NULL - ��� �� ���������)
			LPCWSTR pszMessage,		//!< [in] ���������.
			...
			) throw()
		{
			va_list ap;
			va_start(ap, pszMessage);
			WriteVAW(type, nLevel, pszModule, pszMessage, ap);
			va_end(ap);
		}

		//! ���������� ��������������� ���������.
		virtual void WriteVA(
			ELogMessageType type,	//!< [in] ��� ���������.
			ELogMessageLevel nLevel,//!< [in] ������� �������� (L0 - �������� ������).
			LPCTSTR pszModule,		//!< [in] ��� ������. (NULL - ��� �� ���������)
			LPCTSTR pszMessage,		//!< [in] ���������.
			va_list args
			) throw();

		//! ���������� ��������������� Unicode-���������.
		virtual void WriteVAW(
			ELogMessageType type,	//!< [in] ��� ���������.
			ELogMessageLevel nLevel,//!< [in] ������� �������� (L0 - �������� ������).
			LPCWSTR pszModule,		//!< [in] ��� ������. (NULL - ��� �� ���������)
			LPCWSTR pszMessage,		//!< [in] ���������.
			va_list args
			) throw();

		void Debug(LPCTSTR pszMessage, ...) throw() { va_list ap; va_start(ap, pszMessage); WriteVA(eLM_Debug, L0, NULL, pszMessage, ap); va_end(ap); }
		void Debug(ELogMessageLevel nLevel, LPCTSTR pszMessage, ...) throw() { va_list ap; va_start(ap, pszMessage); WriteVA(eLM_Debug, nLevel, NULL, pszMessage, ap); va_end(ap); }

		void Info(LPCTSTR pszMessage, ...) throw() { va_list ap; va_start(ap, pszMessage); WriteVA(eLM_Info, L0, NULL, pszMessage, ap); va_end(ap); }
		void Info(ELogMessageLevel nLevel, LPCTSTR pszMessage, ...) throw() { va_list ap; va_start(ap, pszMessage); WriteVA(eLM_Info, nLevel, NULL, pszMessage, ap); va_end(ap); }

		void Warning(LPCTSTR pszMessage, ...) throw() { va_list ap; va_start(ap, pszMessage); WriteVA(eLM_Warning, L0, NULL, pszMessage, ap); va_end(ap); }
		void Warning(ELogMessageLevel nLevel, LPCTSTR pszMessage, ...) throw() { va_list ap; va_start(ap, pszMessage); WriteVA(eLM_Warning, nLevel, NULL, pszMessage, ap); va_end(ap); }

		void Error(LPCTSTR pszMessage, ...) throw() { va_list ap; va_start(ap, pszMessage); WriteVA(eLM_Error, L0, NULL, pszMessage, ap); va_end(ap); }
		void Error(ELogMessageLevel nLevel, LPCTSTR pszMessage, ...) throw() { va_list ap; va_start(ap, pszMessage); WriteVA(eLM_Error, nLevel, NULL, pszMessage, ap); va_end(ap); }
		
		//! ���������, ������ �� ��� ��������� � ���.
		bool IsFiltered(ELogMessageType type, ELogMessageLevel nLevel);
		
		//! ������������� �������� ������.
		static void SetThreadName(
			LPCTSTR pszThreadName	//!< [in] ��� ������. ��������� ������ ���� �������� � ������� ������ ������.
			);
		
		//! ��������� ������������� �������� ������.
		static LPCTSTR GetThreadName();
		
		//! ���������� "����������" ��� ����������. (������������ ����� CLogMediaProxy)
		static TLogMediaPtr GetAppLogMedia();
		
		//! ������������� "����������" ��� ����������.
		static void SetAppLogMedia(TLogMediaPtr pLog);
		
		static TLogMediaPtr CreateConsoleMedia();
		
		static TLogMediaPtr CreateFileMedia(
			LPCTSTR pszFilename,	//!< [in] ��� �����.
			bool bAppend,	//!< [in] ���� ���������� � �����.
			bool bFlush	= false	//!< [in] ���� ������ �� ���� ����� ������� Write.
			);
		
		enum EDebugMediaStartParams
		{
			DEBUGMEDIA_NORMAL = 0x1,
			DEBUGMEDIA_FORCE = 0x2,			//!< ������� ���� ���� ��� ���������.
			DEBUGMEDIA_REPORTERRORS = 0x4,	//!< �������� ������ ����� _CrtDbgReport.
		};
		static TLogMediaPtr CreateDebugMedia(
			DWORD dwParam = DEBUGMEDIA_NORMAL	//!< [in] ������� ���� ���� ��� ���������.
			);
		
		/*! ������ ��� �� �������� � �������.
		� ��������� ����� ����� ��������� ��������� ����������:
		  REG_SZ	"TraceHeader" - ������ ������� � ��� ����� �������� ���� �����
		  REG_SZ	"TraceFile" - ��� ����� ��������� � �����, ���������� � �������� ����������
		  REG_DWORD	"TraceFileAppend" (def: 1) - ���� ���������� � ����� �����
		  REG_DWORD	"TraceFileFlush" (def: 0) - ���� ������ �� ���� ����� ������ ������
		  REG_DWORD	"TraceToApp" = 1 - ��� ����� ��������� � ���� ����������.
		  REG_DWORD	"TraceToConsole" = 1 - ��� ����� ��������� � ���� �������
		  REG_DWORD	"TraceToDebug" = 1 - ��� ����� ��������� � ���� ��������� (Debug Output).
		  �� ��� ��� ���� ����� �������� ������.
		    �������� ��������� �������:
				REG_SZ		"TraceType" = ["debug"|"info"|"warning"|"error"] - ���, ��������� ���� �������� ������������ �� �����.
				REG_DWORD	"TraceLevel" = [0|1|2|...] - ������� ���� TraceType, ��������� ���� �������� ������������ �� �����.
		  ���� ���������� ����������� ������� ������������� ��� ������� ����, ��� ����������
		  ��������� ����� ������ ���� (��������, ������ � ��� �����), �� � ��������� �����
		  ����� ������� �������� "Trace1" "Trace2" � �.�. (������ ���� ��������������� ������� � 1)
		  � ������� ����� ������� �������������� ���� � �������.
		  ������� � ����� ������ � �� �������� ����!
		  ������:
			HLKM\....\SomeComp
				REG_SZ		"TraceFile" = "c:\my.log"
			HLKM\....\SomeComp\Trace1
				REG_DWORD	"TraceToDebug" = 1
				REG_SZ		"TraceType" = "warning"
				REG_DWORD	"TraceLevel" = 5
			��������: ������ � ���� ��, � ����� ��� ������ � �������������� ������ 5 � ����.


		   \return ���, ������� ����� �������� � CLog.
		*/
		static TLogMediaPtr CreateMediaFromRegistry(
			HKEY hRoot,				//!< [in] �������� ������� �������.
			LPCTSTR pszPath,		//!< [in] ���� �� ��������� ��������, �� �������, ����������� �������� ����.
			bool bAppLog = false	//!< [in] ��� ���� ���������� ������ ���� true. ����� ������������� ��� ���������� (SetAppLogMedia()).
			);

	protected:
		//! �����������.
		CLogBase(
			TLogMediaPtr pMedia,	//!< [in] ���.
			LPCTSTR pszModule		//!< [in] ��� ������.
			);
		TLogMediaPtr m_pMedia;
		std::basic_string<TCHAR> m_szModule;
	};

	class KLUTIL_API CLocalLog: public CLogBase
	{
	public:
		//! ����������� ��� ���-����������.
		CLocalLog(
			const CLogParam& param,	//!< [in] ��������� �������� ����.
			LPCTSTR pszModule		//!< [in] ��� ������ �� ���������.
			);
		//! �����������.
		CLocalLog(
			TLogMediaPtr pMedia,	//!< [in] ���.
			LPCTSTR pszModule		//!< [in] ��� ������.
			);
		//! �����������.
		CLocalLog(
			const CLogBase& log,	//!< [in] ���.
			LPCTSTR pszModule		//!< [in] ��� ������.
			);
		virtual ~CLocalLog();
	};

	class KLUTIL_API CLog: public CLogBase
	{
	public:
		//! ����������� ��� ���-����������.
		CLog(
			const CLogParam& param,	//!< [in] ��������� �������� ����.
			LPCTSTR pszModule		//!< [in] ��� ������ �� ���������.
			);
		//! ����������� ��� �������� ���� ���������� ��� ����������.
		CLog(
			TLogMediaPtr pMedia,	//!< [in] ���.
			LPCTSTR pszModule		//!< [in] ��� ������.
			);
		//! ����������� ��� ���-����������.
		CLog(
			const CLogBase& log,	//!< [in] ���.
			LPCTSTR pszModule		//!< [in] ��� ������.
			);
		virtual ~CLog();
		void SetParams(
			TLogMediaPtr pMedia,		//!< [in] ����� ���.
			LPCTSTR pszModule = NULL	//!< [in] ����� ��� ������. ����� ���� NULL.
			);
		//! ���������� ��������������� ���������.
		virtual void WriteVA(
			ELogMessageType type,	//!< [in] ��� ���������.
			ELogMessageLevel nLevel,//!< [in] ������� �������� (L0 - �������� ������).
			LPCTSTR pszModule,		//!< [in] ��� ������.
			LPCTSTR pszMessage,		//!< [in] ���������.
			va_list args
			) throw();
		//! ���������� ��������������� Unicode-���������.
		virtual void WriteVAW(
			ELogMessageType type,	//!< [in] ��� ���������.
			ELogMessageLevel nLevel,//!< [in] ������� �������� (L0 - �������� ������).
			LPCWSTR pszModule,		//!< [in] ��� ������.
			LPCWSTR pszMessage,		//!< [in] ���������.
			va_list args
			) throw();
	private:
		CCritSec m_cs;
	};


	//! "����������" ��� � �����������.
	class KLUTIL_API CFilterLog: public CLog
	{
		typedef boost::shared_ptr<CFilterLogMedia> TFilterLogMediaPtr;
		TFilterLogMediaPtr GetFilterLogMedia() { return boost::static_pointer_cast<CFilterLogMedia>(GetMedia()); }
	public:
		CFilterLog(const CLogParam& param, LPCTSTR pszModule): CLog(param, pszModule)
		{
			TLogMediaPtr pMedia = GetMedia();
			if (pMedia)
				SetParams(TLogMediaPtr(new CFilterLogMedia(pMedia)));
		}
		virtual ~CFilterLog();
		void AddFilter(TFilterPtr pFilter) { if (GetFilterLogMedia()) GetFilterLogMedia()->AddFilter(pFilter); }
	};

} // namespace KLUTIL

#endif