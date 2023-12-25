/*!
 * (C) 2007 "Kaspersky Lab"
 *
 * \file trafficmanageproxy.h
 * \author ����� �����������
 * \date 2007
 * \brief ������ ���������� �������� �������
 */

#if !defined(KLTRFP_TRAFFICMANAGERPROXY)
#define KLTRFP_TRAFFICMANAGERPROXY

#include <std/base/klbase.h>
//#include <server/trf/trafficmanagerserver.h>
#include <transport/tr/trafficmanager.h>

namespace KLTRFP
{
	class KLSTD_NOVTABLE TrafficManagerProxy : public KLSTD::KLBaseQI 
	{
    public:

		/*!
		  \brief ��������� ����������� �������� ��� ���������� ��������� IP �������
		*/
		virtual long AddRestriction( const KLTR::TrafficManager::Restriction &restriction ) = 0;

		/*!
		  \brief ������������ ����������� �������� ��� ���������� ��������� IP �������
		*/
		virtual long UpdateRestriction( long nRestrictionId, const KLTR::TrafficManager::Restriction &restriction ) = 0;

		/*!
		  \brief ������� ���������� �����������
		*/
		virtual void DeleteRestriction( long nRestrictionId ) = 0;

		/*!
		  \brief ���������� ��� ����������� �������� 
		*/
		virtual void GetRestrictions( KLTR::TrafficManager::RestrictionsMap &restrictList ) = 0;
	};
}

#endif // !defined(KLTRFP_TRAFFICMANAGERPROXY)