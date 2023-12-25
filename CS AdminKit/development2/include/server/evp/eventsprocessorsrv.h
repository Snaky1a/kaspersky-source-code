/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file server/evp/eventsprocessorsrv.h
 * \author Andrew Lashchenkov
 * \date 21/07/2005
 * \brief ��������� ��������� EventsProcesor
 *
 */

#ifndef KLEVP_EVENTSPROCESSORSRV_H
#define KLEVP_EVENTSPROCESSORSRV_H

#include <server/srv_common.h>
#include <srvp/evp/eventsprocessor.h>
#include <server/db/dbconnection.h>

#define KLEVP_EVENT_DB_ID  L"KLEVP_EVENT_DB_ID"

namespace KLSRV {
    struct EventAndCallerInfo : public KLEVP::EventInfo
    {
        EventAndCallerInfo()
        {
        }

        EventAndCallerInfo( const KLEVP::EventInfo& eventInfo )
        {
            *((KLEVP::EventInfo*)this) = eventInfo;
        }

        std::wstring deliveryId;
        std::wstring domain;
        std::wstring hostName;
        std::wstring agentId;
    };
};

namespace KLEVP {

    class EventsProcessorSrv : public KLSTD::KLBaseImpl<KLSTD::KLBase> {
    public:
    /*!
      \brief ����� ��������� �� ��������� ����� ������� �� ������.

		\param pDbConn		[in] ���������� � ��
        \param package      [in] ����� ������� ��� ���������.
        \param deliveryId   [in] ������������� ������ �������, ������������ 
                                 �� ������ �����������������.
        \param domain       [in] ������������� ������ ����, ������� ���������� �������.
        \param hostName     [in] ������������� �����, ������� ���������� �������.
		\param nHostId		[in] ������������� �����; ����� ���� 0, ����� ����������� �� hostName
        \param agentId      [in] ������������� ������ �����������������, �������
                                 ���������� �������.
       
    */
        virtual void Process ( 
			KLDB::DbConnectionPtr pDbConn,
            const std::vector<EventInfo>& package,
            const std::wstring & deliveryId,
            const std::wstring & domain,
            const std::wstring & hostName,
			long nHostId,
            const std::wstring & agentId,
			std::vector<long>* pVecEventsDbIds) = 0;

		virtual void ProcessHostNFSection(
			KLDB::DbConnectionPtr pDbConn, 
			const std::wstring& wstrHostName, 
			const std::wstring& wstrProductName,
			const std::wstring& wstrProductVersion,
			KLPAR::ParamsPtr parHostNFSection) = 0;
		
        // virtual KLSTD::CAutoPtr<KLSTD::CriticalSection> GetCriticalSection() = 0;
    };

    class EventsProcessorSrvFactory : public KLSTD::KLBase
    {
    public:
        virtual void CreateInstance( EventsProcessorSrv ** pEventsProcessor ) = 0;
    };

}

#endif // KLEVP_EVENTSPROCESSORSRV_H

