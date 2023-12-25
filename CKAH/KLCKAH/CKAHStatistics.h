// CKAHStatistics.h: interface for the CCKAHStatistics class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CKAHSTATISTICS_H__AFB4AB27_3BDE_4EF3_BC15_C094E5DC2EC6__INCLUDED_)
#define AFX_CKAHSTATISTICS_H__AFB4AB27_3BDE_4EF3_BC15_C094E5DC2EC6__INCLUDED_

#include "../../../../CommonFiles/KLUtil/inl/PoliStorage.h"
#include <stuff/thread.h>

namespace KLCKAH
{

class CCKAHStatistics : CStaticSync<CCKAHStatistics>
{
public:
	CCKAHStatistics()
	{
		Reset ();
	}

	void Reset ()
	{
		CLock lock;
		m_AttackCount = 0;
	}

	void AddNumAttacks ()
	{
		CLock lock;
		m_AttackCount++;
	}

	LONG GetNumAttacks ()
	{
		CLock lock;
		return m_AttackCount;
	}

    PoliType &MarshalImpl (PoliType &pt);
	
protected:
	LONG m_AttackCount;
	// ��� ���������� ����� ������ ������, ��� ������ �������� 2 ���� ����������
	// � ���������� m_AttackCount
	// � ���� ������ ���� ������� ��������� � ������ �������� ����� ���������� �� ����� ������ ��������
};

inline
PoliType &CCKAHStatistics::MarshalImpl (PoliType &pt)
{
	CLock lock;
	return pt << m_AttackCount;
}

IMPLEMENT_MARSHAL(CCKAHStatistics)

} // namespace KLCKAH

#endif // !defined(AFX_CKAHSTATISTICS_H__AFB4AB27_3BDE_4EF3_BC15_C094E5DC2EC6__INCLUDED_)
