/*!
 * (C) 2004 "Kaspersky Lab"
 *
 * \file TransportTimeout.h
 * \author ����� �����������
 * \date 2004
 * \brief ����� ��� ������� timeout'�� ��� ������ � �����������
 * 
 */


#ifndef KLTR_TRANSPORT_TIMEOUT_H
#define KLTR_TRANSPORT_TIMEOUT_H

#include "std/err/error.h"
#include "errors.h"

namespace KLTRAP {

	const int c_DefaultTimeout				= 10000;				// 10 ���
	const int c_DefaultMaxTransportTimeout	= 24 * 60 * 60 * 1000;	// 24 ����

	class TransportTimeout
	{
        //<-- Changed by andkaz 07.05.2004 18:33:07
    public:
        // -->    
		TransportTimeout( int connectTimeout = c_DefaultTimeout, int maxTimeout = c_DefaultMaxTransportTimeout )
		{        
            Create(connectTimeout,maxTimeout);
		}
        
        void Create( int connectTimeout = c_DefaultTimeout, int maxTimeout = c_DefaultMaxTransportTimeout )
		{
			m_timeout = connectTimeout;
			m_timeoutDelta = connectTimeout;
			m_initiateTimeout = m_timeout;
			m_maxTimeout = maxTimeout;			
		}
        

		/*!
		    \brief ����������� timeout
		*/
		int Increment()
		{
			if ( m_timeout < m_maxTimeout )
				m_timeout += m_timeoutDelta;

			return m_timeout;
		}

		/*!
		    \brief ��������� timeout
		*/
		int Decrement()
		{
			if ( (m_timeout - m_timeoutDelta) > 0 )
				m_timeout -= m_timeoutDelta;

			return m_timeout;
		}

		/*!
		    \brief ����������� ��� ������ � � ������ ������������� ����������� timeout
		*/
		void CheckFault( KLERR::Error *pErr )
		{
			if ( std::wstring(pErr->GetModuleName())==KLTRAP_ModuleName )
			{
				if ( pErr->GetId()==TRERR_REMOTE_SERVER_IS_BUSY ||
					pErr->GetId()==TRERR_TIMEOUT ) 
				{
					Increment();
				}
				else
				{
					// � ������ ���� ��������� ������ ���������� �� default �������
					Create( m_initiateTimeout, m_maxTimeout );
				}
			}
		}

		/*!
		    \brief ������ �� �������� �������� ���������� 
					( � ������� ������ ������� ��������� timeout )
		*/
		void GoodAttempt()
		{
			Decrement();
		}

		/*!
			\brief ���������� ������� �������� timeout'�
		*/
		int Get()
		{
			return m_timeout;
		}

	private:
		
		int m_timeout;
		int m_timeoutDelta;
		int m_initiateTimeout;
		int m_maxTimeout;
	};

};

#endif // KLTR_TRANSPORT_TIMEOUT_H
