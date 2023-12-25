/*!
 * (C) 2007 Kaspersky Lab
 *
 * \file	NapUtils.h
 * \author	Eugene Rogozhnikov
 * \date	29.10.2007 17:46:31
 * \brief	
 *
 */

#ifndef __NAPUTILS_H__
#define __NAPUTILS_H__

#include<std\base\kldefs.h>
#include <nap\nap_sdk\NapProtocol.h>
#include "NapSettings.h"
#include <string>
#include <nap\nap_sdk\NapUtil.h>
#include <std/par/params.h>

namespace KLNAP
{
	HRESULT RegisterNAPSha();
	HRESULT UnregisterNAPSha();
};

#if defined(UNICODE) || defined(_UNICODE)

namespace KLNAP
{
	// true ��� ��������, �� ������� �������������� NAP
	bool IsNapPlatform();

	///////////////////////////////////////////////////////////////////
	// �����-������� ��� NapComponentRegistrationInfo, ����� � �����������
	// ������� ������
	class CNapComponentRegistrationInfo {
	public:
		CNapComponentRegistrationInfo();
		~CNapComponentRegistrationInfo();

		NapComponentRegistrationInfo* getInfo() { return &m_shvInfo; }


		void trace();

	private:
		NapComponentRegistrationInfo m_shvInfo;

		CNapComponentRegistrationInfo& operator=( const CNapComponentRegistrationInfo& );
		CNapComponentRegistrationInfo( const CNapComponentRegistrationInfo& );

	};

	///////////////////////////////////////////////////////////////////
	/*
	 *	
		��������� ����� CTypeHolder �������� �������� ��� ��������, ������� ���� �����������
		����� �������������. ������� ������������ ����� �������� "void WINAPI (T* ptr)"
	 */

	template <class T, void (WINAPI *freeT)(T* ptr)>
	class CTypeHolder {
	public:
		CTypeHolder()
		{
			m_pPtr = NULL;
		}
		~CTypeHolder()
		{
			if( m_pPtr ) freeT( m_pPtr );
		}

		operator T*() const{
			return (T*)m_pPtr;
		};
			
		T* operator->() const{
			return (T*)m_pPtr;
		};

		T& operator*() const{
			KLSTD_ASSERT(m_pPtr!=NULL);
			return *m_pPtr;
		};

		//The assert on operator& usually indicates a bug.  If this is really
		//what is needed, however, take the address of the p member explicitly.
		T** operator&()
		{
			KLSTD_ASSERT(m_pPtr==NULL);
			return &m_pPtr;
		};

		bool operator!() const
		{
			return (m_pPtr == NULL);
		};

	private:
		T* m_pPtr;

		CTypeHolder& operator=( const CTypeHolder<T, freeT>& );
		CTypeHolder( const CTypeHolder<T, freeT>& );
	};
	
	typedef CTypeHolder<SoH, FreeSoH> CSoHHolder;
	typedef CTypeHolder<IsolationInfo, FreeIsolationInfo> CIsolationInfoHolder;

	///////////////////////////////////////////////////////////////////

	// Helper Function for populating already allocated CountedString structures
	// This makes filling the NapRegistrationInfo struct cleaner in the sample code
	HRESULT FillCountedString (const WCHAR* src, CountedString * dest) throw ();

	// Helper Function for depopulating CountedString structures
	// leaves the structure intact, but frees the buffer underneath
	// for use with FillCountedString above
	HRESULT EmptyCountedString( CountedString * cs ) throw ();

	//////////////////////////////////////////////////////////////////////////////////////////////////
	// Both INapSoHConstructor::Initialize() and INapSoHProcessor::Initialize()
	// have a boolean input parameter that indicates whether the SoH being
	// manipulated is an SoH Request (TRUE) or an SoH Response (FALSE).  The
	// following variables hide the actual boolean values behind named constants
	// that are less ambiguous, to prevent confusion from other possible
	// interpretations of the literal boolean values.

	const BOOL SOH_REQUEST  = TRUE;
	const BOOL SOH_RESPONSE = FALSE;

	// Create an SoH Constructor object.
	HRESULT CreateOutputSoHConstructor(INapSoHConstructor* &pSohResponse,
									   SystemHealthEntityId  systemHealthId,
									   BOOL                  sohType) throw();


	// Create an SoH Processor object.
	HRESULT CreateInputSoHProcessor(INapSoHProcessor*   &pSohResponse,
									SystemHealthEntityId &systemHealthId,
									BOOL                  sohType,
									SoH                  *pInputSoh) throw();

	// Release a COM reference (pointer) to an IUnknown object.
	void ReleaseObject(IUnknown *pIUnknown) throw();

	/////////////////////////////////////////////////////////////////////////////////////

	bool isAdminKitAttr( SoHAttributeValue *pAttrValue );
	HRESULT readAVP( SoHAttributeValue *pAttrValue, NAP_AVP& avp );

	// ��������� pAttrValue �� ������ avp. ���������� ��������� �� �����, ���
	// �������� ������. �� ������ ����� ���� ������ � pAttrValue. ����� ����, ���
	// pAttrValue ������ �� �����, ���� ������� ����� ���������� delete[]
	BYTE* packAVP( const NAP_AVP& avp, SoHAttributeValue *pAttrValue );

	bool readAVPValue( const NAP_AVP& avp, bool& bValue);
	bool readAVPValue( const NAP_AVP& avp, long& lValue);
	bool readAVPValue( const NAP_AVP& avp, std::string& strValue);

	///////////////////////////////////////////////////////////////////////////////////////
	// ��������������� ������� ��� ������ � ����������� ������ ��� Nap SHV

	// ���������� ��� ����� � �������, ��� �������� ���������
	std::wstring GetSHVConfigDataRegKey();

	// ������� ��������� ������ SHV � params
	void ReadNAPSHVConfigParams( KLPAR::Params** ppParams );

	// �������� ��������� ������ SHV �� params
	void WriteNAPSHVConfigParams( const KLPAR::Params* pParams ); 

	///////////////////////////////////////////////////////////////////////////////////////////
	// ������� ��� ������ �� ��������
	void StartService( LPCTSTR lpServiceName, DWORD dwWaitAfterCheckPoints = 0 );
	void StopService( LPCTSTR lpServiceName, DWORD dwWaitAfterCheckPoints = 0 );

}; // namespace KLNAP

#endif //defined(UNICODE) || defined(_UNICODE)

#endif //__NAPUTILS_H__