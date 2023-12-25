#ifndef __USERSETTINGS_SC_H__
#define __USERSETTINGS_SC_H__

#define SS_NO_CONVERSION
#define SS_NO_BSTR
#include "DEFS.H"
#include "BaseMarshal.h"
#include "../release_type.h"

#pragma warning(disable : 4251) // 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable : 4275) // non - DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#pragma warning(disable : 4786) // 'identifier' : identifier was truncated to 'number' characters in the debug information

namespace Private {
	
	//! �������������� ��������� Script Checker ��� Personal Pro.
	struct CCIFACEEXPORT CUserSettingsSC_v1: public CCBaseMarshal < PID_USER_SETTINGS_SC >
	{
		//! ���� �������� Script Checker'�.
		enum ESCAction
		{
			eSCAction_AskUser = 0x1,	//!< �������� ������������.
			eSCAction_Block = 0x2,		//!< ������������� ������.
			eSCAction_Allow = 0x3,		//!< ��������� ������.
		};
		
		ESCAction m_eAction;	//!< �������� �� ���������� �������.
		
		CUserSettingsSC_v1()
			:
#ifdef __WKS
			m_eAction(eSCAction_Block)
#else
			m_eAction(eSCAction_AskUser)
#endif
		{
		}
		
		bool operator == (const CUserSettingsSC_v1& Settings) const
		{
			return m_eAction == Settings.m_eAction;
		}
		
		CUserSettingsSC_v1& operator = (const CUserSettingsSC_v1& rhs)
		{
			m_eAction = rhs.m_eAction;
			return *this;
		}
		
		bool IsDefault() const
		{
			return *this == CUserSettingsSC_v1();
		}
		
		PoliType & MarshalImpl ( PoliType & pt )
		{
			return BaseMarshal::MarshalImpl ( pt ) << SIMPLE_DATA_SER(m_eAction);
		}
	};
	
} // namespace Private

typedef DeclareExternalName<Private::CUserSettingsSC_v1> CUserSettingsSC;

#endif // __USERSETTINGS_SC_H__