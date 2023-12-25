/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file Common.h
 * \author ����� �����������
 * \date 2002
 * \brief �������� ����� �����������.
 *
 */


#ifndef KLEV_COMMON_H
#define KLEV_COMMON_H

#include "std/base/kldefs.h"
#include "std/base/klbase.h"
#include "std/err/error.h"
#include "std/par/params.h"

#include "kca/prci/componentid.h"

class SOAPComponentId;

namespace KLEV {

	/*!
		\brief ������� ��������� ComponentId

			���� � first ������� ������ �������, �� �������������� ���� � ComponentId
			� �������� ��������� �� ���������.

		\return true - ���������� �����
	*/
	KLCSTR_DECL bool MatchComponentIds( const KLPRCI::ComponentId &first, 
		const KLPRCI::ComponentId &second, bool sendToAgentFlag = false,
		const std::wstring agentProductName = L"", 
		const std::wstring agentVersionName = L"" );

	inline bool ComponentIdsIsEqual( const KLPRCI::ComponentId &first, 
		const KLPRCI::ComponentId &second )
	{
		if ( first.instanceId != second.instanceId ) return false;
		if ( first.productName != second.productName ) return false;		
		if ( first.componentName != second.componentName ) return false;
		if ( first.version != second.version ) return false;
		return true;
	}

	KLCSTR_DECL bool MatchEventBody( KLPAR::Params* pParBody, KLPAR::Params* pParFilter,
		KLPAR::ParamsNames& namesOfFilter );

	/*!\brief ����������� �� ��������� SOAPComponentId � KLPRCI::ComponentId */
	KLCSTR_DECL void ConvertComponentIdFromSOAP( KLPRCI::ComponentId &compId, const SOAPComponentId *soapCompId );
	/*!\brief ����������� �� KLPRCI::ComponentId � SOAPComponentId */
	KLCSTR_DECL void ConvertComponentIdToSOAP( struct soap *soap, SOAPComponentId *soapCompId, const KLPRCI::ComponentId &compId );

	/*!\brief ����������� �� ��� ���������� � KLPRCI::ComponentId*/
	KLCSTR_DECL bool ConvertComponentIdFromTransportName( KLPRCI::ComponentId &compId, const std::wstring &connName );

	/*!\brief ����������� �� KLPRCI::ComponentId � ��� ���������� */
	KLCSTR_DECL bool ConvertComponentIdToTransportName( std::wstring &connName, const KLPRCI::ComponentId &compId );
	
	class EventSource;

}; // namespace KLEV

/*\brief ������� ������������� ���������� Eventing'�.
*   ������ ������� ������� ���� ������ ������ EventSource, ������� �������� ���� �������
*	KLEV_GetEventSource. 
*/
/*\brief ������� ���������� ���������� ������ ������ EventSource */
DECLARE_MODULE_INIT_DEINIT2( KLCSTR_DECL, KLEV );

/*\brief ���������� ��������� �� ���������� ������ ������ EventSource */
KLCSTR_DECL KLEV::EventSource *KLEV_GetEventSource();

KLCSTR_DECL void KLEV_GetEventSourceWithLock(KLSTD::CAutoPtr<KLEV::EventSource> &ppEventSource);

#define KLEV_GET_GLOBAL_EVENTSOURCE()\
	KLSTD::CAutoPtr<KLEV::EventSource> pGlobalEventSource;\
	KLEV_GetEventSourceWithLock(pGlobalEventSource);

#define KLEV_ACCESS_DENIED (-5)

#endif // KLEV_COMMON_H
