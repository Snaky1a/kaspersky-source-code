/*!
* (C) 2007 "Kaspersky Lab"
*
* \file trafficmanager.h
* \author ����������� �����
* \date 2007
* \brief ��������� ������ ���������� ����������� ������� 
*
*/
#ifndef TR_TRAFFICMANAGER_H
#define TR_TRAFFICMANAGER_H

#include <map>

#include "std/base/klbase.h"
#include "std/thr/sync.h"

#include "transport/tr/transport.h"
#include "transport/tr/common.h"

namespace KLTR {

	class TrafficManager : public KLSTD::KLBase
	{
	public:

		struct Restriction
		{
			struct IPInterval
			{	
				IPInterval()
				{
					nMaskOrLo = nSubnetOrHi = 0;
					bIsSubnet = false;
				}
				unsigned long nMaskOrLo;
				unsigned long nSubnetOrHi;
				bool bIsSubnet;
			};

			struct	TimedLimit
			{
				TimedLimit()
				{
					iStartHour = iStartMin = 0;
					iEndHour = iEndMin = 0;
					iLimit = 0;
				}
				int iStartHour, iStartMin;
				int iEndHour, iEndMin;	//! ������ ������ � ����� �������� ������ ������� � ����� � ������� ( 0 - 23, 0 - 59 )

				int iLimit;					//! ����� ������� � kb/sec
			};

			Restriction()
			{
				nId = 0;
				bUseTotalLimit = false;
				iTotalLimit = 0;
			}

			long	nId;				//! ������������� �����������

			bool	bUseTotalLimit;		//! ���� ������������� ������ ����������� �������� 
										// ( �� ��������� ������� ������� �� ����������� � ��������� ������������ )
			int		iTotalLimit;		//! ����� ����� ������� � kb/sec


			TimedLimit	timedLimit;		//! ����� � ��������� ������� ��������

			IPInterval	interval;		//! IP ��������
		};


		typedef std::map<long,Restriction> RestrictionsMap;
		typedef std::list<Restriction> RestrictionsList;

		/*!
		  \brief ��������� ����������� �������� ��� ���������� ��������� IP �������
		*/
		virtual void ReplaceRestriction( const Restriction &restriction ) = 0;

		/*!
		  \brief ������� ���������� �����������
		*/
		virtual void DeleteRestriction( long nRestrictionId ) = 0;
	};

} // namespace KLTR

#endif // TR_TRAFFICMANAGER_H