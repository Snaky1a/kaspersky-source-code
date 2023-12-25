#ifndef __USERSETTINGS_OG_H__
#define __USERSETTINGS_OG_H__

#include "DEFS.H"
#include "BaseMarshal.h"
#include <algorithm>

#pragma warning(disable : 4251) // 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable : 4275) // non - DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#pragma warning(disable : 4786) // 'identifier' : identifier was truncated to 'number' characters in the debug information


//******************************************************************************
// �������� Office Guard
//******************************************************************************

//! ������� OfficeGuard.
enum EOffGuardEvents
{
	ogWORD_OPTIONS_SAVENORMALPROMPT,	//!< ���������� ������� �� ���������� ������� Normal
	ogWORD_OPTIONS_VIRUSPROTECTION,	//!< ���������� ������ �� �������
	ogWORD_MACROCOPY,	//!< ������� MacroCopy
	ogWORD_ORGANIZER_COPY,	//!< ����������� ������� (OrganizerCopy)
	ogWORD_ORGANIZER_DELETE,	//!< �������� ������� (OrganizerDelete)
	ogWORD_ORGANIZER_RENAME,	//!< �������������� ������� (OrganizerRename)
	ogVBCA,	//!< �������� ������
	ogVBCR,	//!< �������� ������
	ogVBCE,	//!< ������� �������
	ogVBCI,	//!< ������ �������
	ogADDFROMFILE,	//!< ������� ����� ������� � ������ �� �����
	ogADDFROMSTRING,	//!< ���������� ����� � ������
	ogINSERTLINE,	//!< ������� ����� � ������
	ogREPLACELINE,	//!< ������ ����� � �������
	ogDELETELINE,	//!< �������� ����� �������
	ogCREATEPROCEDURE,	//!< �������� ���������
	ogOPENFORWRITE,	//!< �������� ����� � ������ ������
	ogCHANGEFILEATTR,	//!< ����� ���������� �����
	ogKILLFILE,	//!< �������� ������
	ogMAKEDIR,	//!< �������� �����
	ogREMOVEDIR,	//!< �������� �����
	ogSHELLCOMMAND,	//!< ������� Shell
	ogCREATEOBJECT,	//!< �������� �������� ActiveX
	ogCREATEOBJECT2,	//!< �������� ������� ActiveX �� �������� ����������
	ogGETOBJECT,	//!< ������ � ActiveX �������
	ogSENDKEYS,	//!< �������� ������� ������
	ogEXCEL_COPY,	//!< ����������� ������ Excel
	ogAPIFUNCTION,	//!< ����� API-�������
	ogCLOSEFILE_notused_bug16913,	//!< �������� �����
	ogOTHER,	//!< ������ �������
	ogVBCS,	//!< ������
	ogMACRO,	//!< �������
	ogFILEOPERATIONS,	//!< �������� ��������

	ogLast
};

//! �������� �� ������� OfficeGuard.
enum EUserAnswer
{
	uaAskUser = 0,	//!< �������� ������������.
	uaAllow,		//!< ��������� ����������.
	uaBlockMacro,	//!< ����������� ���������� �������.
	uaBlockScript,	//!< ����������� ���������� �������.
	
	uaDefaultForUnknown = uaAskUser,	//!< �������� �� ��������� ��� ����������� ������� (����� ���������� � ������ ��������� ������������ OfficeGuard).
	uaDefault = uaBlockMacro	//!< �������� �� ��������� (���� �� �����-�� �������� ��� ����������� �������� ������������).
};

IMPLEMENT_MARSHAL_ENUM(EOffGuardEvents);
IMPLEMENT_MARSHAL_ENUM(EUserAnswer);

namespace Private
{
	struct CEventAnswer
	{
		CEventAnswer(EOffGuardEvents ev_ = ogVBCA): ev(ev_), answ(uaDefaultForUnknown) {}
		EOffGuardEvents ev;
		EUserAnswer answ;
		bool operator<(const CEventAnswer& rhs) const { return ev < rhs.ev; }
		bool operator==(const CEventAnswer& rhs) const { return ev == rhs.ev  && answ == rhs.answ; }
		PoliType & MarshalImpl(PoliType& pt)
		{
			return pt << ev << answ;
		}
	};
	
	IMPLEMENT_MARSHAL(Private::CEventAnswer);
	
	class CCIFACEEXPORT COfficeGuardSettings_v1 : public CCBaseMarshal<PID_USER_SETTINGS_OFFICE_GUARD>
	{
	public:
		typedef std::vector< CEventAnswer > CIdToAction;
		
		virtual PoliType & MarshalImpl(PoliType& pt)
		{
			return BaseMarshal::MarshalImpl (pt) << m_IdToAction;
		}
		
	protected:
		mutable CIdToAction m_IdToAction;
	};
} // namespace Private

struct CCIFACEEXPORT COfficeGuardSettings: public DeclareExternalName<Private::COfficeGuardSettings_v1>
{
	COfficeGuardSettings() { PPro_SetRecommended(); }

	EUserAnswer GetAnswer(EOffGuardEvents ev) const { return Get(ev).answ; }
	void SetAnswer(EOffGuardEvents ev, EUserAnswer answ) { Get(ev).answ = answ; }
	const CIdToAction& GetActionList() const { return m_IdToAction; }
	
	void PPro_SetMaximalProtection();
	void PPro_SetRecommended();
	void PPro_SetMaximalSpeed();

	bool PPro_IsMaximalProtection() const;
	bool PPro_IsRecommended() const;
	bool PPro_IsMaximalSpeed() const;

	bool operator == (const COfficeGuardSettings & rhs) const
	{
		return m_IdToAction == rhs.m_IdToAction;
	}
	
private:
	Private::CEventAnswer& Get(EOffGuardEvents ev) const
	{
		CIdToAction::iterator it = std::lower_bound(
			m_IdToAction.begin(), m_IdToAction.end(), Private::CEventAnswer(ev));
		if (it != m_IdToAction.end() && it->ev == ev)
			return *it;
		return *m_IdToAction.insert(it, Private::CEventAnswer(ev));
	}
};

#endif // __USERSETTINGS_OG_H__