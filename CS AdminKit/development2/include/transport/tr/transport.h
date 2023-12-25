/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file Transport.h
 * \author ����� �����������
 * \date 2002
 * \brief ������� ��������� ������������� ������ ��� ����� �����-�������
 *
 *  ������ ���� �������� �������� ������������ ���������� ������������� ������ 
 *  ��� ����� �����-������� Transport.
 *  ������ ������ �������� �� ��������� gSOAP � ������������ ��� �������� ����������
 *  ������� ���������� � ��������� �������� ��������� ���������� �������� �� ��������� 
 *  �������.
 */


#ifndef KLTR_TRANSPORT_H
#define KLTR_TRANSPORT_H

#include <string>
#include <list>

#include <std/par/params.h>

#include <kca/prci/componentid.h>
#include <transport/wat/common.h>
#include <transport/wat/authserver.h>
#include <transport/tr/trafficmanager.h>

#include "common.h"
#include "errors.h"
#include "notifier.h"

// forward declaration
struct soap;

namespace KLTRAP {	

	const int g_TransportCurrentVersion = 2;

//#define KL_OPENSSL_SUPPORT
	
/*!
 * \brief ������� ��������� ������������� ������.
 *	
 *		����� ���������� ���������� ������������ ������ ����������. ��� �����������
 *			ComponentId � ����������� ��� � ������� ����������� �������� 
 *			( ConvertComponentIdToTransportName � ConvertTransportNameToComponentId ��. ���� )
 */ 	

	const int c_DefaultMaxNumberOfConns = 200;
	const int c_DefaultInactiveConnTimeout = 120000;

	const wchar_t	c_TRLocalLocationPrefic[]	= L"http://127.0.0.1";
	const wchar_t	c_TRLocationPrefic[]		= L"http://";
	const int		c_TRLocationPreficLen		= 7;

	const wchar_t c_AnyAddrLocation[]	= L"*any_addr*";

	const int c_DefaultNumberOfConncurentThreads = 5;

	//!< ������� ��������� �������� ������� ����������� gSOAP
	typedef int (*SoapServeFunc)( struct soap *soap );	

	//! ������ ���� ����������
	typedef std::list<std::wstring> ConnectionsNameList;

	class ConnectionControl : public KLSTD::KLBaseQI
	{
	public:
		
		enum ActionType
		{
			ConnectionEstablished,	// ���� ������� CheckConnection ������ false ��� ������� 
									// �������� ���������� ����� ������������� �������
			UnusedConnectionCheck	// � ������ �������� ������������� �������� �����������
									// ������� ������ ��������� ��� ����� �������������� � �� 
									// ��������� ��� ������� ����������������. true - ������ 
									// ���������� ����� ���� �������. ������������ ���������� 
									// ��������� ���������������� ���������� ������ ���� ��������� 
									// ����� ���������� ����������� � ������ ��������
		};

		virtual bool CheckConnection( ActionType actionType, 
				const std::wstring &localName,
				const std::wstring &remoteName,
				bool remoteConnection ) = 0;
	};

	
	/*!\typedef �������� ������ ��� ���������� */
	struct ProxyInfo{
		std::wstring	location;		//!< Location ������ ������� ( format: http://proxy_host:proxy_port )
		std::wstring	authUserName;	//!< ��� ������������, ���� ������ ������� ��������������
		std::string		authUserPswd;	//!< ������ ������������
	};

	class Transport 
	{
	public:

		/*!\enum ���� ���������� ��������� ������� ���������� */
		enum ConnectionStatus{			
			ComponentConnected,			//!< ��������� ���������� � ��������� �����������
			ComponentDisconnected,		//!< ���������� � ��������� ����������� ����������
			ConnectionEstablished,		//!< ���������� ���� ������� ������������
			ConnectionBroken,			//!< ���������� ���������			
			UnicastPacketArrived,		//!< ������ unicast �����
			PingTimeoutElapsed			//!< ������� ����� Ping'�
		};
		
		/*!\enum ���������� ���������� */
		enum ConnectionPriority
		{
			PriorityLow		= 1,
			PriorityNormal	= 0,		// �������� �� ���������
			PriorityHigh	= 2
		};

		/*!\struct ��������� location'� */
		struct Location{
			Location() { unicastConnectFlag = useSSLUnicast = bCompressTraffic = false; }
			Location( const Location &l ) { 
				location			= l.location;				
				remoteComponentName = l.remoteComponentName;
				unicastConnectFlag	= l.unicastConnectFlag;
				useSSLUnicast		= l.useSSLUnicast;
                proxyInfo           = l.proxyInfo;
				bCompressTraffic	= l.bCompressTraffic;
			}			
			std::wstring		remoteComponentName;	//!< ��� ��������� ����������
			std::wstring		location;				//!< URL
			bool				unicastConnectFlag;		//!< ������� unicast ����������
			bool				useSSLUnicast;			//!< ��� ������� unicast ������������ ������� SSL ( ����������� �������� � ������������� listener'� )			
			ProxyInfo			proxyInfo;				//!< ���������� � ������ ������� ( ������������ ���� location � ��������� �� ������ ������ )
			bool				bCompressTraffic;		//!< ������������ ������ ������� ��� ���������� ������
		};

		/*!\typedef ������ ����������*/
		typedef std::vector<Location> LocationsList;

		/*!\struct ��������� ����������*/
		struct ConnectionFullName{
			ConnectionFullName() {}
			ConnectionFullName( const ConnectionFullName &c ) {
				localComponentName = c.localComponentName;
				remoteComponentName = c.remoteComponentName;
			}
			std::wstring		localComponentName;		//!< ��� ��������� ����������
			std::wstring		remoteComponentName;	//!< ��� ��������� ����������
		};

		/*!\typedef ������ ���������� ����������*/
		typedef std::vector<ConnectionFullName> ConnectionsFullNameList;


		/*!\struct ����������� ��������� location'� */
		struct LocationEx{
			LocationEx() { unicastConnectFlag = useSSLUnicast = false; userData = NULL; }
			LocationEx( const LocationEx &l ) { 
				location			= l.location;
				ports				= l.ports;
				remoteComponentName = l.remoteComponentName;
				localComponentName	= l.localComponentName;
                userData            = l.userData;
				unicastConnectFlag  = l.unicastConnectFlag;
				useSSLUnicast		= l.useSSLUnicast;
			}
			bool operator == ( const LocationEx &lex )
			{
				if (	remoteComponentName==lex.remoteComponentName &&
						localComponentName==lex.localComponentName &&
						location==lex.location &&
						ports==lex.ports &&
						unicastConnectFlag==lex.unicastConnectFlag &&
						userData==lex.userData ) return true;
				else
					return false;
			}
			std::wstring		remoteComponentName;	//!< ��� ��������� ����������
			std::wstring		localComponentName;		//!< ������������ ��� ������ ��� ������������� ����������� ( ������ � ������ ���� location ������ )
			std::wstring		location;				//!< URL ��� �����
			std::vector<short>	ports;					//!< ������ ������ ��� ����������� 
			void				*userData;				//!< ������ ������������ ( �������� �� ������� ������ ������������ ���������� ��� )
			bool				unicastConnectFlag;		//!< ������� unicast ����������
			bool				useSSLUnicast;			//!< ��� ������� unicast ������������ ������� SSL ( ����������� �������� � ������������� listener'� )
		};

		/*!\typedef ������ ����������*/
		typedef std::vector<LocationEx> LocationExList;
		
				
		/*!\struct ��������� ��� �������� ���������� */
		struct ConnectionInfo
		{
			ConnectionInfo()
			{
				pingTimeout = c_Undefined;
				priority = PriorityNormal;
				pCustomCredentials = NULL;
				pCustomAuthClientCtx = NULL;
				pRemotePublicSSLKey = NULL;
				pLocalPublicSSLKey = NULL;
				bConnForGateway = false;
				pProxyInfo = NULL;
				bMakeTwoWayAuth = false;
				bCompressTraffic = false;
				bCreateSSLConnection = false;
				bSimpleConnection = false;
				bDontCloseByTimeoutError = false;				
			}

			std::wstring		localName;			//!< ��������� ��� ����������
			std::wstring		remoteName;			//!< ��������� ��� ����������
			std::wstring		remoteLocation;		//!< ����� ��������� ����������

			int					pingTimeout;		//!< ������ ���������� ����������� ����������
			ConnectionPriority	priority;			//!< ��������� ������������ ����������

			KLPAR::Params	   *pCustomCredentials;		//!< ������������ ��� ���������������� ��������������
			KLWAT::ClientContext *pCustomAuthClientCtx;	//!< ����������� �������� ��� ������� ����������

			bool				bCreateSSLConnection;	//!< ��������� SSL ���������� ���� ���� pRemotePublicSSLKey == NULL
			KLPAR::BinaryValue *pRemotePublicSSLKey;	//!< ��������� ���� SSL ��������� ����������
			KLPAR::BinaryValue *pLocalPublicSSLKey;		//!< ��������� ���� SSL ��������� ���������� ���������� 
														// ������������ ����. ����� �����������
			bool				bConnForGateway;		//!< ���� ������������� ������� ���������� ��� gateway

			const ProxyInfo		*pProxyInfo;			//!< ���������� ��� �������� ���������� ����� ������ ������

			bool				bMakeTwoWayAuth;		//!< ��� ������� ���������� ����� ����������� ������������ ��������������

			bool				bCompressTraffic;		//!< ������� ������ ������� ��� ������� ����������

			bool				bSimpleConnection;		//!< ��� �������� ������� ���������� �� ������������� handshake. �� ���������
														// ������� ��� ���������� ���������� ����� ������������� �������������� ���������� ���.
														// ����������������� hanshake ����� ����������� �� �����
			
			bool				bDontCloseByTimeoutError;		//!< ������� �� ��������� ���������� � ������ ������������� ������ timeout expired
		};
		

		/*!\enum ��������� ���������� � Broeadcast ������� */
		enum BroadcastState {
			BroadcastConnectionEstablished,		//!< ������������ ����������
			BroadcastConnectError,				//!< ���������� ���������� ����������
			BroadcastFinished					//!< ���������� broadcast ���������
		};

		typedef int BroadcastId;

		class Broadcast : public KLSTD::KLBase
		{
		public:
			/*!\brief Callback ������� broadcast ������ */
			virtual int BroadcastCallback( BroadcastId broadcastId, 
				BroadcastState state, 
				const wchar_t *localComponentName, 
				const wchar_t *remoteComponentName,
				void *userData ) = 0;
		};

	/*!
		\brief Callback - ������� ��� ���������� �� ��������� ������� ����������

		
		\param status  [in]  ������ ����������
		\param remoteComponentName [in] ������������ ��� ���������� � ������� ������������� ����������
		\param localComponentName [in] ������������ ��� ���������� �� ���� ������� 
				���� ������������ ������ ����������		

		\return ���� �� ������������
	*/
		typedef int (*StatusNotifyCallback)( Transport::ConnectionStatus status, 
			const wchar_t *remoteComponentName, const wchar_t *localComponentName,
			bool remoteConnFlag );

		virtual ~Transport() {}

	/*!
      \brief ������� ������������� ����������. 

      \param maxNumberOfConns [in] ������������ ���������� ����������.      
      \exception TRERR_INVALID_PARAMETER 
    */
        virtual void Initialize( int maxNumberOfConns, SoapServeFunc soapServe = NULL ) = 0;

	/*!
	  \brief ������������� ��������� ����� ������
	*/
		virtual void SetIOPortMode( bool usePort = true, 
			int numberOfThreads = c_DefaultNumberOfConncurentThreads ) = 0;
		
	/*!
      \brief ������� ��������� timeout'��.

      ��������� ��� ������ ������ ������� �������� ����� ������������ � ����������
	  � �������� timeout ��� ������� ������������ ��������.

      \param recvTimeout [in] ������� ��� �������� receive ( � ������������ ).
      \param sendTimeout [in] ������� ��� �������� send ( � ������������ ).
	  \param connectTimeout [in] ������� ��� �������� connect � accept ( � ������������ ).
      \exception TRERR_INVALID_PARAMETER 
    */
        virtual void SetTimeouts( int recvTimeout, int sendTimeout, int connectTimeout ) = 0;
		
	/*!
	  \brief ������� ��� ��������� timeout'��

	  \param recvTimeout [in] ������� ��� �������� receive ( � ������������ ).
      \param sendTimeout [in] ������� ��� �������� send ( � ������������ ).
	  \param connectTimeout [in] ������� ��� �������� connect � accept ( � ������������ ).
      \exception TRERR_INVALID_PARAMETER 
    */
        virtual void SetRemoteCallsTimeouts( int recvTimeout, int sendTimeout, int connectTimeout ) = 0;

	/*!
	  \brief ������� ��� ��������� timeout'��

	  \param recvTimeout [in] ������� ��� �������� receive ( � ������������ ).
      \param sendTimeout [in] ������� ��� �������� send ( � ������������ ).
	  \param connectTimeout [in] ������� ��� �������� connect � accept ( � ������������ ).
      \exception TRERR_INVALID_PARAMETER 
    */
        virtual void SetLocalCallsTimeouts( int recvTimeout, int sendTimeout, int connectTimeout ) = 0;

	/*!
	  \brief ������� ��������� connectTimeout
	
	  \return ���������� ��������
	 */
		virtual int SetConnectTimeout( int connectTimeout ) = 0;

	/*!
      \brief �������� ��������� callback �������.

      ������ callback ������� ������������� ��� ���������� ������� � ��������� �������
	  ��������������� ����������. ������� ��������� ������� ���������� ������ ����� ����� 
	  ������ ������� ���������� �������. ��� ��������������� ���������� ������
	  ���������� � ��������� ����� ���������� ������� ���������.
	  
      \param newCallback [in] callback ������� ��� ����������.      
	  \return ���������� ������� ��������� ��� NULL
    */
        virtual StatusNotifyCallback SetStatusCallback( StatusNotifyCallback newCallback ) = 0;

	/*!
      \brief �������� ��������� callback �������.

		� ������� �� ������� SetStatusCallback callba�k ������ ���������� ��� ���������� 
		������� ���������� � ����� ���� ������� ������������ �� ������ �������.
	 */
		virtual StatusNotifyCallback SetStatusCallback2( StatusNotifyCallback newCallback ) = 0;

	/*!
	  \brief ���������� ��������� ��� ����������� ����������� ����������� �� ����������

	  ����� ����������� ������� �� ��������� � �������������� SetStatusCallback
	*/
		virtual KLTR::TransportNotifier *Notifier() = 0;

	/*!
      \brief �������� ��������� location ��� ������� � ������ ���������� �� ������� ��������.
      

	  \param localComponentName [in] ��� ���������� �� ���� ������� ���������� ����������
				location'�.
      \param location [in] location ��� ������������� ( ������ http://127.0.0.1:port ).      
	  \param usedPort [out] ����� �����, �� ������� ����� ������������� listen. ���� � location
			���� �� ������ ( http://127.0.0.1 ) ��� ����� 0 ( http://127.0.0.1:0 ) ���� �����
			������ �������������.

	  \exception TRERR_INVALID_PARAMETER, TRERR_WRONG_ADDR, TRERR_LOCATION_ALREADY_EXISTS
    */
        virtual void AddListenLocation( const wchar_t *localComponentName, 
			const wchar_t *location, int &usedPort ) = 0;

	/*!
	  \brief ��������� SSL location ��� ������� � ������ ���������� �� ������� ��������.

	  \param  binaryPrivateSSLKey [in] ��������� ���� ���������� ��������
	  \param  binaryPublicSSLKey [in] ������ SSL ���� 
	  \param  keyPassword [in] ������ ��� ���������� �����
	*/
		virtual void AddSSLListenLocation( const wchar_t *localComponentName, 
			const wchar_t *location, int &usedPort, 
			KLPAR::BinaryValue *binaryPrivateSSLKey,
			KLPAR::BinaryValue *binaryPublicSSLKey,
			const wchar_t *keyPassword ) = 0;

	/*!
      \brief �������� ��������� location ��� ������������� unicast �������.

	  ��� ������� unicast ������ ����� �������� callback ������� ���������� �� ��������
	  UnicastPacketArrived.

	  \exception TRERR_INVALID_PARAMETER, TRERR_WRONG_ADDR, TRERR_LOCATION_ALREADY_EXISTS
    */
        virtual void AddUnicastListenLocation( int unicastPort ) = 0;

	/*!
      \brief �������� ������� location ��� ������� � ������ ����������.

	  \param localComponentName [in] ��� ���������� �� ���� ������� ��� �������� ������
				location.
      \param location [in] location ��� ������������� ( ������ http://127.0.0.1:port ).      
	  \param usedPort [out] ����� �����, ������� ��� ��������� �������� AddListenLocation �
			������ ���������� ������� location'�.
	  \exception TRERR_INVALID_PARAMETER, TRERR_NOT_FOUND_CONNECTION	  
    */
        virtual void DeleteListenLocation( const wchar_t *localComponentName, 
			const wchar_t *location, int usedPort ) = 0;
		
	/*!
      \brief �������� ������� location ��� ������� � ������ ���������� � ����������� 
		��� ��������� � ������ ���������� ����������.

	  \param localComponentName [in] ��� ���������� �� ���� ������� ��� �������� ������
				location.
      \param location [in] location ��� ������������� ( ������ http://127.0.0.1:port ).      
	  \param usedPort [out] ����� �����, ������� ��� ��������� �������� AddListenLocation �
			������ ���������� ������� location'�.
	  \exception TRERR_INVALID_PARAMETER, TRERR_NOT_FOUND_CONNECTION	  
    */
        virtual void DeleteListenerAndCloseConnections( const wchar_t *localComponentName, 
			const wchar_t *location, int usedPort ) = 0;


	/*!
      \brief �������� ������� unicast listener.
    */
        virtual void DeleteUnicastListenLocation( int unicastPort ) = 0;

	/*!
      \brief �������� ��������� ���������� ����������.

      ������� �������� ���������� ���������� ���������� � ��������.

	  \param localComponentName [in] ������������ �������, �� ���� �������� ������������� 
				������ ����������. ������ ��� ����� ������������� �� ������ ������� � 
				�������� ����� ��������� ����������. �������� ������������ ������� ����������.
	  \param remoteComponentName [in]	��� ����������� ���������� ( ������������ � ���������� ��� ������� � ������� ���������� ).
				������ ��� �������� ������������ ������ ��������� ����������.
      \param remoteServerLocation [in] location ���������� ������� ( ������ http://ip_addr:port ).	  
	  \param pingTimeout [in] ��������� ������ ������ Ping ������ �� ������� � �������.
	  \param connForGateway [in] ������ ����������� ����� �������������� ��� gateway. ���� ���������� 
				������ ����, �� ��������� ������ ����������� �� ����� �������������� ��� ��������������� 
				��������
	  \param priority [in] ��������� ������������ ����������
	  \param makeTwoWayAuthentication [in] ���� ��������� ���������������� ��������������.
				�� �������� �������������� ������������� ������ �� ���������� �������
				
	  \exception TRERR_INVALID_PARAMETER, TRERR_WRONG_ADDR, TRERR_CONN_ALREADY_EXISTS,
			TRERR_CONN_HANSHAKE
	  
	  \return ��������� �������� false - ���������� � ��������� ������� �� �������������
    */
        virtual bool AddClientConnection( const wchar_t *localComponentName, 
			const wchar_t *remoteComponentName, const wchar_t *remoteServerLocation,
			int pingTimeout = c_Undefined, bool connForGateway = false,
			const KLPAR::Params * pCustomCredentials = NULL,
			ConnectionPriority priority = PriorityNormal,
			bool makeTwoWayAuthentication = false,
			KLWAT::ClientContext *customAuthClientCtx = NULL,
			const ProxyInfo* proxyInfo = NULL ) = 0;

	/*!
      \brief �������� ��������� ���������� SSL ����������.

	  \param  binaryPublicSSLKey [in] ������ SSL ����
	  \param  keyPassword [in] ������ ��� ���������� �����
	*/		
        virtual bool AddSSLClientConnection( const wchar_t *localComponentName, 
			const wchar_t *remoteComponentName, const wchar_t *remoteServerLocation,			
			KLPAR::BinaryValue *binaryPublicSSLKey, const KLPAR::Params * pCustomCredentials = NULL,
			int pingTimeout = c_Undefined, bool connForGateway = false,
			ConnectionPriority priority = PriorityNormal,
			KLWAT::ClientContext *customAuthClientCtx = NULL,
			const ProxyInfo* proxyInfo = NULL ) = 0;

	/*!
	  \brief ������� �������� Unicast ����� � ���� �������� ���������� ��������� ��������

	*/
		virtual bool SendUnicastAndWaitConnection( const wchar_t *remoteLocation,
			const wchar_t *waitRemoteComponentName, const wchar_t *waitLocalComponentName,
			int timeout ) = 0;

	/*!
      \brief ��������� ������������ ���������� ����������.
        
	  \param localComponentName [in] ������������ �������, �� ���� �������� ���� �������� 
				������ ����������.
	  \param remoteComponentName [in]	��� ����������� ����������	  	  	  
	  
	  \return ��������� �������� false - ���������� ���������� �� ������� � ������ �������������� ����������
    */
        virtual bool CloseClientConnection( const wchar_t *localComponentName, 
			const wchar_t *remoteComponentName ) = 0;

	/*!
	  \brief ���������� ������ ���� �������� ����������

	  \param connsList [out] ������ �������� ����������
	*/
		virtual void GetConnectionsList( ConnectionsNameList &connsList ) = 0;

	/*!
	  \brief ���������� ������ ���� �������� ����������

	  \param connsList [out] ������ �������� ����������
	*/
		virtual void GetConnectionsList( ConnectionsFullNameList &connsList ) = 0;

	/*!
	  \brief ���������� ���������� ���������� ����������
	  
	  \param remoteComponentName [in] ��� ���������� ��� ��������
	  \return ������� ����������
	*/
		virtual bool IsConnectionActive( const wchar_t *remoteComponentName ) = 0;

	/*!
	  \brief ���������� ���������� ���������� ����������
	  
	  \param localComponentName [in] ������������ �������, �� ���� �������� ���� �������� 
				������ ����������.
	  \param remoteComponentName [in] ��� ���������� ��� ��������
	  \return ������� ����������
	*/
		virtual bool IsConnectionActive( const wchar_t *localComponentName,
			const wchar_t *remoteComponentName ) = 0;

	/*!
      \brief ������ ���������� location ���������� ����������.

      \param remoteComponentName [in] ��� ����������� ���������� 
	  \param result [out]  location ������� ( ������ http://ip_addr:port ).
    */
        virtual void GetLocation( const wchar_t *remoteComponentName, std::wstring &location ) = 0;

	/*!
	   \brief ������� ����������� ������������ �� ��������� ��������� ����������

		��������� ����������� ���������� � ��� ������ ���� �� ���� ���������� ��� �������� 
		location ��� ������� ( ������� AddListenLocation )

		\param componentName [in] ������������ ��� ����������
	*/
		virtual bool IsLocalComponent( const wchar_t *componentName ) = 0;

	/*!
      \brief ���������� ��������� soap ��� ���������� ����������� ����������.

	  ������������ ������ ������� ��������� SOAP ������ ���� ������������� �������� ��� 
	  ������������� ������� ��������� �������. ������������ ��������� �� ������ �� ����� ������� 
	  ���������������� ��������.

	  \param localComponentName [in] ������������ �������, �� ���� �������� ����� ������������� ����� � 
						�������������� ������������ ���������
      \param remoteComponentName [in] ��� ����������� ���������� 
	  \param lockConnection [in] ���� ���������� ������� ���������� �� ������� �� ������ �������. ����������
					��������� ������� ������� FreeClientConnection.
	  \param result [out] ��������� �� ��������� soap. ���� ����� NULL, �� �������� ������� ���������� �����������
		( ��. �������
    */
        virtual void GetClientConnection( const wchar_t *localComponentName, const wchar_t *remoteComponentName, 
			bool lockConnection, struct soap **result ) = 0;

	/*!
	  \brief ����������� ��������� soap �������� �������� GetClientConnection

	   ����� ������ ������ ������� ������������ ��������� soap ������

	   \param soap [in] ��������� �� ��������� soap. 
	   \param unlockConnection [in] ������� ������ ���������� � ����������
	*/
		virtual void FreeClientConnection( struct soap *soap, bool unlockConnection ) = 0;

	/*!
      \brief ���������� ��������� ������ ��� �������� ��������� Ping.

	  ���� ������ ��������� ������������ ����� ��� Ping'�, �� ������ ������ � ���������
	  ���������� ������������ ������� Ping ��������� ��� ������ ������� SendPingMessage

	  \param localComponentName [in] ��� �������, �� ���� �������� ���� ������������ ����������
      \param remoteComponentName [in] ��� ����������
	  \return ��������� ������. ���� ����� 0 �� ������ �� ������� ������� Ping ��������� 
				�� �������
    */
        virtual int GetPingTimeout( const wchar_t *localComponentName, const wchar_t *remoteComponentName ) = 0;

	/*!
      \brief ������� ������������ �������� ping ���������.

	  \param localComponentName [in] ��� �������, �� ���� �������� ���� ������������ ����������
      \param remoteComponentName [in] ��� ����������� ����������
    */
        virtual bool SendPingMessage( const wchar_t *localComponentName, const wchar_t *remoteComponentName ) = 0;

	/*!
	  \brief ������� ����������� ����� ���������� �� ��������� SOAP.
		
		  ������ ������� ��������� ������ ����������, ��������������� ������ ���������� soap
		  � ���� ���������� ������� ���������� ��� ���������� ����������.

	  \param soap [in] ��������� soap �������� ����������
	  \param connName [out] ��� ���������� ����������
	  \result false - ���� ������ ���������� ��� ���������
	*/
		virtual bool GetConnectionName( const struct soap *soap, std::wstring &connName ) const = 0;

	/*!
	  \brief ������� ����������� ����� ���������� �� ��������� SOAP.
		
		  ������ ������� ��������� ������ ����������, ��������������� ������ ���������� soap
		  � ���� ���������� ������� ���������� ��� ���������� ����������.

	  \param soap [in] ��������� soap �������� ����������
	  \param connName [out] ������ ��� ���������� ���������� ����������
	  \result false - ���� ������ ���������� ��� ���������
	*/
		virtual bool GetConnectionName( const struct soap *soap, ConnectionFullName &connName ) const = 0;

	/*!
	  \breif ������� ���������� ���������� ��������� ���������� ��� ����������� ��������

	  \param remoteClineName [in] ��� ���������� ( � ������������ ���� ) ��� ���������� ����������
	*/
		virtual void LockConnectHandshake( const wchar_t *remoteClientName ) = 0;

	/*!
	  \brief ������� ���������� � ��������� ����������
	*/
		virtual void UnlockConnectHandshake() = 0;

	/*!
	  \brief ������ ������� ������� �������� ��� broadcast ������

	  Broadcast �������� ������������ � ���������� ������� � ����� ��������� 
	  ����������� �������� callback ������� � �������������� �������� ���������
	  � ��� ��������� ���������� ����������.

	  \param localComponentName [in] ������������ ��� ���������� �� ���� ������� 
				����� ������������ ������ ����������		
	  \param locsList [in] ������ �������
	  \param callback [in] Callback �������, ������� ����� �������� ��� ������� ����������
				��. �������� ������� �������
	  \param callbackContext [in] �������� ��� callback �������
	  \exception TRERR_INVALID_PARAMETER
	*/
		virtual BroadcastId CreateBroadcast( const wchar_t *localComponentName, 
			LocationExList &locsList, Broadcast *broadcast ) = 0;

	/*!
	  \brief ������� ��������� broadcast �����

	   � ������ ������� ���������� ������������� ���������� �� ������� CreateBroadcastCall

	   \exception TRERR_INVALID_PARAMETER
	*/
		virtual void StartBroadcast( const BroadcastId broadcastId ) = 0; 

	/*!
	  \brief ������� ������������� ������ broadcast ������

	  \param broadcastId [in] ������������� ������
	   \exception TRERR_INVALID_PARAMETER
	*/
		virtual void StopBroadcast( const BroadcastId broadcastId ) = 0;

	/*!
	  \brief ������� ������������� gateway ����������

	  \param localComponentName [in] ������������ �������, �� ���� �������� ������������� 
				������ ����������. 
	  \param locsList [in]	������ �����, ����� ������� ������� ���� ����������� ����������      
	  \param pingTimeout [in] ��������� ������ ������ Ping ������ �� ������� � �������.
				
	  \exception TRERR_INVALID_PARAMETER, TRERR_WRONG_ADDR, TRERR_CONN_ALREADY_EXISTS,
			TRERR_CONN_HANSHAKE
	  
	  \return ��������� �������� false - ���������� � ��������� ������� �� �������������
	*/
		virtual bool CreateGatewayConnection( const wchar_t *localComponentName, 
			LocationsList &locsList, int connectTimeout = c_Undefined,			
			ConnectionPriority priority = PriorityNormal,			
			KLWAT::ClientContext *customAuthClientCtx = NULL ) = 0;

	/*!
	  \brief ������� ����������� ���������� �������� ������� � ����������

	  \param timeOut [in] ����� �������� �������� �������� � �������������. ���� timeout 
				����� 0 �� ������� �������� ������ ������� ��������� �������
	*/
		virtual int ProcessRequests( int timeOut = 0 ) = 0;

	/*!
	   \brief ������� ����������� ��� ���������� � ������� �������������� ��������� soap

		\param soap [in] ��������� �� ��������� soap, ���������� �������� GetClientConnection
	*/
		virtual bool IsLocalConnection( const struct soap *soap ) = 0;
		
	/*!
      \brief �������� ��������� ���������� SSL ����������.	  
	*/		
        virtual bool AddSSLClientConnection( const wchar_t *localComponentName, 
			const wchar_t *remoteComponentName, const wchar_t *remoteServerLocation,			
			int pingTimeout = c_Undefined, bool connForGateway = false,
			ConnectionPriority priority = PriorityNormal,
			const ProxyInfo* proxyInfo = NULL ) = 0;

	/*!
	  \brief ������������� ��������� ����������

	  \param maxConnsNum [in] ����������� ���������� ���-�� ����������
	  \param maxInactiveConnTime [in] ����������� ���������� ����� ������������ ���������� 
			( Ping �� ���������� �� ������ ), ����� �������� ������ ���������� ����� ���� �������
	*/
		virtual void SetConnectionsParams( int maxConnsNum = c_DefaultMaxNumberOfConns,			
			int maxInactiveConnTime = c_DefaultInactiveConnTimeout ) = 0;
		
	/*!
	  \brief ������� ������������� gateway ���������� � ������������� SSL

	  \param localComponentName [in] ������������ �������, �� ���� �������� ������������� 
				������ ����������. 
	  \param locsList [in]	������ �����, ����� ������� ������� ���� ����������� ����������      
	  \param pingTimeout [in] ��������� ������ ������ Ping ������ �� ������� � �������.
				
	  \exception TRERR_INVALID_PARAMETER, TRERR_WRONG_ADDR, TRERR_CONN_ALREADY_EXISTS,
			TRERR_CONN_HANSHAKE
	  
	  \return ��������� �������� false - ���������� � ��������� ������� �� �������������
	*/
		virtual bool CreateSSLGatewayConnection( const wchar_t *localComponentName, 
			LocationsList &locsList, int connectTimeout = c_Undefined,
			ConnectionPriority priority = PriorityNormal,
			KLWAT::ClientContext *customAuthClientCtx = NULL ) = 0;
		
	/*!
	  \brief ������� ��������� ���������� ������ ����������

	  \param soap ��������� �������� ���������

	  \return ��������� location. ������ http://xxx.xxx.xxx.xxx ��� �����
				� ������ ������ ���������� ������ ������
	*/
		virtual std::wstring GetRemoteLocation( struct soap *soap ) = 0;

	/*!
	  \brief ������� ��������� ���������� ������ ����������

	  \param soap ��������� �������� ���������

	  \return ��������� location. ������ http://xxx.xxx.xxx.xxx ��� �����
				� ������ ������ ���������� ������ ������
	*/
		virtual std::wstring GetLocalLocation( struct soap *soap ) = 0;
		
	/*!
      \brief �������� ��������� location ��� ������������� unicast ������� � ��������� SSL �������.

	  ��� ������� unicast ������ ����� �������� callback ������� ���������� �� ��������
	  UnicastPacketArrived.

	  \exception TRERR_INVALID_PARAMETER, TRERR_WRONG_ADDR, TRERR_LOCATION_ALREADY_EXISTS
    */
        virtual void AddSSLUnicastListenLocation( int unicastPort, KLPAR::BinaryValue *binaryPublicSSLKey ) = 0;

	/*!
	  \brief ������� �������� Unicast ����� � ���� �������� ���������� ��������� ��������

		����� ������������� SSL ������������

	*/
		virtual bool SendSSLUnicastAndWaitConnection( const wchar_t *remoteLocation,
			const wchar_t *waitRemoteComponentName, const wchar_t *waitLocalComponentName,
			int timeout, KLPAR::BinaryValue *binaryPrivateSSLKey, const wchar_t *keyPassword ) = 0;
		
	/*!
	  \brief ������� ������������� gateway ���������� � ������������� SSL � custom authentication

	  \exception TRERR_INVALID_PARAMETER, TRERR_WRONG_ADDR, TRERR_CONN_ALREADY_EXISTS,
			TRERR_CONN_HANSHAKE
	  
	  \return ��������� �������� false - ���������� � ��������� ������� �� �������������
	*/
		virtual bool CreateSSLGatewayConnection( const wchar_t *localComponentName, 
			LocationsList &locsList, KLPAR::BinaryValue *binaryPublicSSLKey,
			const KLPAR::Params * pCustomCredentials, 
			int connectTimeout = c_Undefined,
			ConnectionPriority priority = PriorityNormal,
			KLWAT::ClientContext *customAuthClientCtx = NULL ) = 0;
		
	/*!
	   \brief ������� ����������� ��� ����������		
	*/
		virtual bool IsLocalConnection( const wchar_t *localComponentName, 
			const wchar_t *remoteComponentName ) = 0;

	/*!
	   \brief ������� ��������� callback'a ��� �������� ��� ������������
	*/
		virtual void SetConnectionControl( ConnectionControl *connControl ) = 0;

	/*!
	   \brief ������� ������������� ������������ ���-�� ���������� ��� ������� ��������
	*/
		virtual void SetMaxNumberOfConnections( int maxNumberOfConns ) = 0;

	/*!
	   \brief ������� ���������� ������������ ���-�� ���������� ��� ������� ��������
	*/
		virtual int GetMaxNumberOfConnections() = 0;
		
	/*!
      \brief �������� ��������� ���������� ����������.

      ������� �������� ���������� ���������� ���������� � ��������.

	  \param connInfo [in] ��������� ��� �������� ����������
				
	  \exception TRERR_INVALID_PARAMETER, TRERR_WRONG_ADDR, TRERR_CONN_ALREADY_EXISTS,
			TRERR_CONN_HANSHAKE
	  
	  \return ��������� �������� false - ���������� � ��������� ������� �� �������������
    */
		virtual bool AddClientConnection2( const ConnectionInfo &connInfo ) = 0;

	/*!
	  \brief ������� �������� Unicast ����� 

	  \return false - ������ �������� unicast ������ 

	  \param remoteLocation [in] ����� ���������� ����������
	  \param pParams [in] ��������� ��� �������
	  \param binaryPrivateSSLKey [in] Private ���� ��� ������� ������
	  \param keyPassword [in] ������ �����
	  \param timeout [in] ����� � ������� �������� ����� ������������ Unicast ������ ( msec )
						������ ������� �������� 200 msec

	  \exception TRERR_INVALID_PARAMETER, TRERR_LOAD_CERT_ERR
	*/
		virtual bool SendUnicastPacket( const wchar_t *remoteLocation,
			KLPAR::Params *pParams,
			KLPAR::BinaryValue *binaryPrivateRSAKey,
			int timeout = 500 ) = 0;

	/*!
	  \brief ��������� SSL ������� Unicast ������ 

	  \return false - ������ �������� �������

	  \param pTransportPacket [in] ����� ��� ��������	  
	  \param binaryPublicSSLKey [in] Public ���� ��� �������� ������� ������
	  
	  \exception TRERR_INVALID_PARAMETER
	*/
		virtual bool CheckPacketSSLSign( 
			const KLPAR::BinaryValue *pTransportPacket,
			const KLPAR::BinaryValue *binaryPublicRSAKey ) = 0;

	/*!
	  \brief ��������� ��������� �������� listiner ��� ������� ����������� ( ��� �������������� � 
			������������� hanshake'� )
			������������ ��� ������ ��������� ��������� ��� �������������� � �������� �����������������
			( ������: FileTransferBridge - ����������� � ������� ������� ��� ��������� ������ ���������� )
	  
		\exception TRERR_INVALID_PARAMETER, TRERR_WRONG_ADDR, TRERR_LOCATION_ALREADY_EXISTS
    */
        virtual void AddSimpleSocketListenLocation( const wchar_t *localComponentName, 
				const wchar_t *location, int &usedPort ) = 0;

	/*!
	  \brief ������� ���������� ������������ � Multicast ������ � ������������ �������� �������

		\exception TRERR_INVALID_PARAMETER, TRERR_WRONG_ADDR, TRERR_LOCATION_ALREADY_EXISTS
	*/
		virtual void CreateMulticastGroupSender( const wchar_t *multicastGroupLocation,
			KLPAR::BinaryValue *binaryPrivateSSLKey ) = 0;

	/*!
	  \brief ������� ���������� ������������ � Multicast ������ � ������������ ��������� �������
			������ ���������� �� ������� ���������� ����� �������� �� ��������� ������� ����������
			KLTR::TransportNotifier � ����� ����������� MulticastPacketArrived

		\exception TRERR_INVALID_PARAMETER, TRERR_WRONG_ADDR, TRERR_LOCATION_ALREADY_EXISTS
	*/
		virtual void JoinMulticastGroup( const wchar_t *multicastGroupLocation,
			KLPAR::BinaryValue *binaryPublicSSLKey ) = 0;

	/*!
	  \brief ���������� �������� mutlticast ������

		\exception 
	*/
		virtual void SendMulticastPacket( const wchar_t *multicastGroupLocation, 
			KLPAR::BinaryValue *pMulticastPacket ) = 0;

	/*!
	  \brief ������� ����� ��������� multicast ���������� ��������� CreateMulticastGroupSender �
			JoinMulticastGroup

		\exception TRERR_INVALID_PARAMETER, TRERR_WRONG_ADDR, TRERR_LOCATION_ALREADY_EXISTS
	*/
		virtual void DeleteMulticastConnection( const wchar_t *multicastGroupLocation ) = 0;
		
	/*!
      \brief �������� ��������� ������������ unicast listiner ( SSL ����������� ���������� )

	  ��� ������� unicast ������ ����� �������� callback ������� ���������� �� ��������
	  UnicastPacketArrived.

	  \exception TRERR_INVALID_PARAMETER, TRERR_WRONG_ADDR, TRERR_LOCATION_ALREADY_EXISTS
    */
        virtual void UpdateSSLUnicastListenLocation( int unicastPort, KLPAR::BinaryValue *binaryPublicSSLKey ) = 0;


	/*!
	  \brief ��������� �������� SSL listiner ��� ������� ����������� ( ��� �������������� � 
			������������� hanshake'� )
	  
		\exception TRERR_INVALID_PARAMETER, TRERR_WRONG_ADDR, TRERR_LOCATION_ALREADY_EXISTS
    */
        virtual void AddSSLSimpleSocketListenLocation( const wchar_t *localComponentName, 
				const wchar_t *remoteNameForConnection,
				const wchar_t *location, int &usedPort,
				KLPAR::BinaryValue *binaryPrivateSSLKey,
				KLPAR::BinaryValue *binaryPublicSSLKey,
				const wchar_t *keyPassword,
				const int maxNumberOfConcurentThreads = 0 ) = 0;

	/*!
	  \brief ������������� ���������������� �������� �������������� ��� �������� ����������.
			����� ������ ������� �������� ������ � ������ ��������� gSOAP �������

		\exception TRERR_NOT_FOUND_CONNECTION, TRERR_INVALID_PARAMETER
	*/
		virtual void SetCustomAuthContextForConnection( const struct soap *soap,
			const KLWAT::CustomAccessToken& customAccessToken ) = 0;

	/*!
      \brief ��������� ������������ ���������� ����������.
        
	  \param localComponentName [in] ������������ �������, �� ���� �������� ���� �������� 
				������ ����������.
	  \param remoteComponentName [in]	��� ����������� ����������	  	  	  
	  \param waitCleanEventQueue [in] false - �� ����������� �������� �������� ����������
	  
	  \return ��������� �������� false - ���������� ���������� �� ������� � ������ �������������� ����������
    */
        virtual bool CloseClientConnection2( const wchar_t *localComponentName, 
			const wchar_t *remoteComponentName, bool waitCleanEventQueue ) = 0;

	/*!
	  \brief ���������� ��������� �� TrafficManager
	*/
		virtual KLTR::TrafficManager *GetTrafficManager() = 0;

	/*!
      \brief ���������� ��������� soap ��� ���������� ����������� ����������.

	  ������������ ������ ������� ��������� SOAP ������ ���� ������������� �������� ��� 
	  ������������� ������� ��������� �������. ������������ ��������� �� ������ �� ����� ������� 
	  ���������������� ��������.
    */
        virtual void GetClientConnectionById( int connId, 
			bool lockConnection, struct soap **result ) = 0;

	/*!
      \brief ���������� ������������� ����������� ����������.	  
    */
		virtual int GetConnectionId( const wchar_t *localComponentName,
			const wchar_t *remoteComponentName ) = 0;

	/*!
      \brief ���������� ���������� �������� ���������� ���� NULL �� ���������� �� �������
    */
		virtual void GetConnectionClientContext( int connId, 
			KLSTD::CAutoPtr<KLWAT::ClientContext> &pClientContext ) = 0;

	/*!
      \brief ���������� ��������� ����� �������, ������� ������������ ��� ����������
		��� ����������� �� ���������� location.
    */
		virtual void GetLocalSubnetMaskForConnection( const wchar_t *remoteLocation, 
			unsigned long &localSubnetMask ) = 0;
	};

	/*!
		\brief ����������� �� KLPRCI::ComponentId � ������������� ��� ����������.

			������ ������������� ������������� ���������� ����� ��������� ������:
					"ProductName;Version;ComponentName;InstanceId"

		\param trComponentName [out] - ������������ ��� ����������
		\param componentId [in] - ������������� ����������
	*/	
	KLCSTR_DECL void ConvertComponentIdToTransportName( std::wstring &trComponentName, 
		const KLPRCI::ComponentId &componentId );

	/*!
		\brief ����������� �� ������������� ��� ���������� � KLPRCI::ComponentId.

		\param componentId [out] - ������������� ����������
		\param trComponentName [in] - ������������ ��� ����������		

		\return true - ����������� ����� ������ �������
	*/	
	KLCSTR_DECL bool ConvertTransportNameToComponentId( KLPRCI::ComponentId &componentId,
		const std::wstring &trComponentName );

} // namespace KLTRAP



#endif // KLTR_TRANSPORT_H

// Local Variables:
// mode: C++
// End:

