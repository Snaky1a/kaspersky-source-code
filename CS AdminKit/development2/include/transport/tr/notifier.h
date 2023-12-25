/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file notifier.h
 * \author ����� �����������
 * \date 2004
 * \brief ��������� ��� ����������� ������������ ������� ���������
 * 
 */


#ifndef KLTR_NOTIFIER_H
#define KLTR_NOTIFIER_H

#include <string>
#include <list>

#include <std/par/params.h>

#include "common.h"
#include "errors.h"

namespace KLTR {	

	const int  NumberOfNotification = 11;

	enum NotificationType
	{
		ComponentConnected,			//!< ��������� ���������� � ��������� �����������

		ComponentDisconnected,		//!< ���������� � ��������� ����������� ����������

		ConnectionEstablished,		//!< ���������� ���� ������� ������������ 
									// ( ���� ���� �� ������������������ ������� ������ 
									// false ���������� ����� ������������� ������� )

		ConnectionOnClose,			//!< ���������� ����� ������ ������ ����������� ����� �������

		ConnectionBroken,			//!< ���������� ��������� 
									// ( ���������� ����� ����� ������� ���������� )

		UnicastPacketArrived,		//!< ������ unicast ����� ��� �������� ����������

		PingTimeoutElapsed,			//!< ������� ����� Ping'�

		UnusedConnectionCheck,
									//!< � ������ ����������� ������������� �������� �����������
									// ������� ������ ��������� ��� ����� �������������� � �� 
									// ��������� ��� ������� ����������������. true - ������ 
									// ���������� ����� ���� �������. ������������ ���������� 
									// ��������� ���������������� ���������� ������ ���� ��������� 
									// ����� ���������� ����������� � ������ ��������
		ParamsUnicastPacketArrived, //!< ������ unicast ����� � �����������

		MulticastPacketArrived,		//!< ������ multicast �����
		
		ConnectByLocation = (NumberOfNotification - 1)
									//!< ���������� �� �������� ���������� �� ������ ������ ( ������������ 
									//		��� ����������� ���������� ��������� ���������� ) ��. NotificationConnectByLocation
	};

	class NotificationReceiverBase : public KLSTD::KLBaseQI
	{
	};

	class NotificationReceiver : public NotificationReceiverBase
	{
	public:
		
		virtual bool TransportNotification( NotificationType actionType, 
				const std::wstring &localName,
				const std::wstring &remoteName,
				bool remoteConnectionFlag ) = 0;
	};

	class NotificationUnicastPacket : public NotificationReceiverBase
	{
	public:
		
		virtual void UnicastPacketArrived( const KLPAR::Params *pParams, 
			const KLPAR::BinaryValue *pTransportPacket ) = 0;
	};

	class NotificationMulticastPacket : public NotificationReceiverBase
	{
	public:
		
		virtual void MulticastPacketArrived( const std::wstring &mcGroupName,
			const KLPAR::BinaryValue *pTransportPacket ) = 0;
	};
	
	class NotificationConnectByLocation : public NotificationReceiverBase
	{
	public:

		enum ConnectByLocationStatus
		{
			Connected,			// �������� �����������
								// remoteLocation [in] - ��� ���������� ����� ����������� � ������� AddConnection
								// remoteIpAddr [in] - ip ����� ���������� ����� � ������� xxx.xxx.xxx.xxx
								// return - true ����� ������� �������� � ���������

			ResolvedError,		// ������ ������������ ip ������ �� ����� �����
								// remoteLocation [in] - ��� ���������� ����� ����������� � ������� AddConnection
								// remoteIpAddr [out] - ip ����� �� �������� ���������� ���������� ��������� ������� �����������
								//						� ������� xxx.xxx.xxx.xxx
								// return - true ����� ������� � ���������� remoteIpAddr

			ConnectionError		// ������ ����������� �� ���������� ����� �����
								// remoteLocation [in] - ��� ���������� ����� ����������� � ������� AddConnection
								// remoteIpAddr [out] - ip ����� �� �������� ���������� ���������� ��������� ������� �����������
								//						� ������� xxx.xxx.xxx.xxx
								// return - true ����� ������� � ���������� remoteIpAddr
		};
		
		virtual bool ConnectByLocationNotification( ConnectByLocationStatus status, 
			const std::wstring &remoteLocation,
			std::wstring &remoteIpAddr ) = 0;
	};


	class TransportNotifier
	{
	public:
		/*!
			\brief ��������� ���������� ����������� ����������

			\param receiver [in] ����������
			\param needType [in] ����������� ���������� ��� �����������
		*/
		virtual void AddNotificationReceiver( NotificationReceiverBase *receiver, 
			NotificationType needType ) = 0;

		/*!
			\brief ��������� �������� ���������� ����������� ����������
			( ����� ���������� ��� ����. �����������:
				ComponentConnected,
				ComponentDisconnected,
				UnicastPacketArrived,
				PingTimeoutElapsed. )

			\param receiver [in] ����������			
		*/		
		virtual void AddSimpleNotificationReceiver( NotificationReceiverBase *receiver ) = 0;

		/*!
			\brief ������� ���������� �� ������ 

			������ ���������� ���������� �������� ��� ����������� �� ����������
		*/
		virtual void DeleteNotificationReceiver( NotificationReceiverBase *receiver ) = 0;
	};


} // end namespace KLTR

#endif // KLTR_NOTIFIER_H
