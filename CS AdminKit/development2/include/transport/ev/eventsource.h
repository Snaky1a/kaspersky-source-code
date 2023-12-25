/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file EventSource.h
 * \author ����� �����������
 * \date 2002
 * \brief ��������� ������ �������, ������� �������� �������� �������������� �������� 
 *			���������� Eventing
 * 
 */


#ifndef KLEV_EVENT_SOURCE_H
#define KLEV_EVENT_SOURCE_H

#include <string>

#include "event.h"
#include "subscriptioniterator.h"
#include "std/tp/threadspool.h"

namespace KLEV {

	/*!
		\brief EventsSource - �������� ����� ������ � �������� Eventing.
			������ ����� ������������ ��� �������� � ���������� �������.
	*/

	/*!
		\brief Callback - ������� ���������� � ��������� �������, 
			������������ � ���������� ��������. ���������� ���� ������� ������ ���� 
			����������������.

        \param subscriber  [in]  ���������� ����������.
        \param publisher   [in]  ���������� �������������� �������.        
		\param event	   [in]  �������.
	*/
    typedef void (*EventCallback)(
        const KLPRCI::ComponentId & subscriber, 
        const KLPRCI::ComponentId & publisher,        
        const Event *event,
		void *context );

	// ������������� ��������
	typedef int SubscriptionId;

	// ������������� ������������� ��������
	const SubscriptionId UndefinedSubId = (-1);

	struct SubscriptionOptions {
		SubscriptionOptions() 
		{
			persiatance = false;
			lifeTime	= 0;
			sendToAgent = false;
			local		= false;
			useSubscriberConnectionsOnly	= false;
			useOnlyLocalConnection			= true;
		}

		bool			persiatance;	//!< ������� ���������� ��������
		unsigned long	lifeTime;		//!< ����� ����� ��������
		bool			sendToAgent;	/*!< ���� ������� �������� ������. � ������ ������ 
										*    ����������� ������� ��������������� ������ �������� 
										*	 �������� ������ � ������, ���� ������ ��������
										*    ������������� ����� �������. ������������ ��� 
										*	 �������� �� ������� �� ���������, ������ �����
										*	 � �������� ���������� ��������� �� �����.
										*/
		bool			local;			/*!< ������� ������ ��������� �������� ( ��������
										*    � ������ ��������� �� ����� ���������������� ��
										*	 ������ ��������
										*/
		std::wstring	agentProductName;	/*!< ������������ ��� �������� ����� ������. ������ */
		std::wstring	agentVersionName;	/*	���������� ��������� ��� ������������ �� ������
											*	������ ���������� ��������� ��������
											*/
		bool			useSubscriberConnectionsOnly;	
							/*!< ������������ � ������ ������������� ������� �������� �� 
								 ��������� ���������. � ������ ��������� ������� ����� 
								 �������� ����� ����������� ������ �� ���������� ����������
								 �� ����� ���������� ( Subscriber ) */
		bool			useOnlyLocalConnection;
							/*!< ��� �������� ������ �������� ����� �������������� 
								������ ��������� ���������� */
														
	};

	class EventSource : public KLTP::ThreadsPool::Worker
	{
		public:

			virtual ~EventSource() {}

			/*!
				\brief ������� �������� �� �������.
			
					���� ������ �� ������ ���� �� ���������� �������� (��� ��������, ������,
					��� ����������, ������������� ����������, ��� �������), 
					�� ���������� ������� �� ����� ��������� 
					�� ������������.  ��� ������� �� ��������� ������� �������� ������������
					������ �� ��������� �����, �� ���� ���� ���� ���� � � ������� � � ������� �
					��� ���� �����, �� ������� ������������ ����������.
			   
				 
				 \param subscriber [in] ���������� ���������� 
						( ��� ���������� �� ���� ������� ������������� �������� ).
						������������ � ������������� �����.
				 \param publisher [in] ���������� ����������� ( ��� ����������, ������� �� ������� ���������� ���������� )
				 \param type [in] ��� �������
				 \param filterBody [in] ������ �� ��������� �������
				 \param callback [in]  Callback - ������� ��� ��������� ���������� � 
                                        ������������� �������.
				 \param callbackContext [in] ��������� ��� callback �������
			*/
			virtual SubscriptionId Subscribe( const KLPRCI::ComponentId &subscriber,
				const KLPRCI::ComponentId &publisher, const std::wstring &type, 
				KLPAR::Params * eventBodyFilter, EventCallback callback,
				void *callbackContext,
				const SubscriptionOptions &subOptions = SubscriptionOptions() )= 0;

			/*!
				\brief ���������� ������� ����������.
				
				  ������� �������� ��������������� ��������� ���� �������� 
				  ��������� - ����������.

				\param subscriber [in] ��������� ���������
				\param publisher [in] ���������� ����������. ���� = NULL �� ��������� ��� 
						�������� ���������� ����������
			*/
			virtual void Unsubscribe( const KLPRCI::ComponentId &subscriber, 
				const KLPRCI::ComponentId *publisher = NULL ) = 0;

			/*!
				\brief ���������� �������.
				
				  ������� �������� � ��������������� ���������������.

				\param subId [in] ������������� ��������				
			*/
			virtual bool Unsubscribe( const SubscriptionId &subId ) = 0;

			/*!
				\breif ���������� �������� ��������
			*/
			virtual void CreateSubscriptionIterator( SubscriptionIterator **pSubsIterator ) = 0;

			/*!
				\brief ������� ����������� ���� �� ��� ������� ���� ������� ��������.
				
				\param publisher [in] ���������� �������
				\param eventType [in] ��� �������
				\param eventBody [in] ��������� ������� ( ����� ��������� NULL )
				\return true - ���� �� ������ ���� ������� ���� ��������
			*/
			virtual bool CheckEventsSubscription( const KLPRCI::ComponentId &publisher, 
				const std::wstring &eventType, 
				KLPAR::Params * eventBody = NULL ) = 0;

			/*!
				\brief ������� ���������� �������.

					������� ���������������� ��������� ������� �� ���� ��������� � �������.

				\param event [in] ������� ��� ���������� 
			*/
			virtual void PublishEvent( Event *event ) = 0;

			/*!
				\brief ������� ������� ������������ ������� ������� ���� 
					���� �������� �� ��������� ����������

				\param componentName [in] - ��� ���������� � ������������ ����
			*/
			virtual void WaitForCleanEventsQueue( const std::wstring &transportComponentName,
				bool remoteConn = false ) = 0;
			

			//!\brief ������� ����������
			virtual void Stop() = 0;
	};

} // namespace KLEV


#endif // KLEV_EVENT_SOURCE_H
