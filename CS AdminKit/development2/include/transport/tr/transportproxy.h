/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file TransportProxy.h
 * \author ����� �����������
 * \date 2002
 * \brief ��������� ������ proxy ��� ������ � ������������ �����������.
 *
 *  ������ ����� ������������ ��� ���������� proxy �������� � ���������� ����������.
 *  ���������� ����� ������ ���� ���������� �� ��� ������ � ������ ������������ ������
 *  ��������� ������� ��� ������ ���������������� ������ ������� �����������.
 */


#ifndef KLTR_TRANSPORTPROXY_H
#define KLTR_TRANSPORTPROXY_H

#include <string>

#include "std/base/klbase.h"

#include "transport/tr/common.h"
#include "transport/tr/errors.h"

struct soap;

namespace KLTRAP {

	class Transport;
	
	class KLCSTR_DECL TransportProxy 
	{
	public:		

		TransportProxy()
		{
			localComponentName = connectionName = NULL;
		}

		virtual ~TransportProxy() 
		{
			if ( localComponentName!=NULL ) delete[] localComponentName;
			if ( connectionName!=NULL ) delete[] connectionName;
		}

	/*!
      \brief ������� �������������.

      \param localComponentName [in] ������������ �������, �� ���� �������� ����� ������������� ����� � 
						��������� ������
      \param remoteComponentName [in] ������������ ���������� �������
      \exception TRERR_INVALID_PARAMETER, TRERR_CANT_ESTABLISH_CONNECTION 
    */
        void Initialize( const wchar_t *localComponentName, const wchar_t *remoteComponentName );
		
	/*!
      \brief ������� ���������� ��������� ����������.
		
	  ������� ���������� ��������� ���������� ������� ����������� � ��������
	  ��������� soap. ��������� �� ������ ��������� ������ �������������� ��� ������������� 
	  ������ �������. ����� ������ � ���������� ���������� ������� ������� CheckResult �
	  ���������� releasePtr = true.
	  ������ �������� ������:
	  int GetMaxSize()	//!< ������� ������ �������������� �� TransportProxy
	  {
	      int res = 0;

		  struct soap *soap = GetConnectionDesc(); //!< �������� ��������� ����������

		  // �������� ����� ������� ( ������� pinf_getmaxsize ���� �������������� ������������ gSOAP)
		  pinf_getmaxsize( soap, NULL, NULL, &res ); 
		  
		  // ��������� ��������� ���������� ��������� �������� � ����������� ������
		  CheckResult( &soap, true ); 
	  }
      
      \exception TRERR_NOT_INITIALIZED,  
	  \return	 ��������� �� ��������� soap. 
    */
        struct soap *GetConnectionDesc( bool lockConnection = true );

	/*!
      \brief ��������� ������ ���������� ��������� ��������.

      ������ callback ������� ������������� ��� ���������� ������� � ��������� �������
	  ��������������� ����������.

      \param soap [in] ��������� ����������, ��� ������ �������� ������������� �����
	  

	  \exception TRERR_TRANSPORT_ERROR, TRERR_WRONG_METHOD, TRERR_WRONG_METHOD_PARAMETERS  
    */
        void CheckResult( struct soap **soap );

	/*!
	  \brief ����������� ��������� ����������

	  ������� ������������ ��������� ���������� ����������� �������� GetConnectionDesc
	  ����� ������ ������ ������� ��������� �� ��������� ����� ����� NULL.
	*/
		void ReleaseConnectionDesc( struct soap **soap );


	private:
		// ���������� ���������� ������
		
		wchar_t *localComponentName;	//!< ��� ��������� ����������
		wchar_t *connectionName;		//!< ��� ����������				
		bool lockConnection;				//!< ������� ���������� ������� ����������

	protected:
		void ReleaseConnectionDescAndFillLocation( struct soap **soap, std::wstring *locConn );

	};

	/*
		\brief ��������������� ����� ��� ������ � TransportProxy

		������ ����� �������� ������ � TransportProxy � ������������� ������� � ����������
		��������� ����������.
	*/
	class TransportConnectionLocker 
	{
	public:
		TransportConnectionLocker( TransportProxy* pProxy )
		{
			ptrProxy = pProxy;
			soap=ptrProxy->GetConnectionDesc(true);
		}

		~TransportConnectionLocker( )
		{
			 ptrProxy->ReleaseConnectionDesc( &soap );
		}
		
		void Release()
		{
			if ( soap!=NULL ) ptrProxy->ReleaseConnectionDesc( &soap );
		}

		struct soap* Get()
		{
			return soap;
		}

		struct soap* CheckResult()
		{
			ptrProxy->CheckResult( &soap );
			return soap;
		}

	protected:
		struct soap*				soap;
		TransportProxy*			ptrProxy;
	};

} // namespace KLTRAP



#endif // KLTR_TRANSPORTPROXY_H

// Local Variables:
// mode: C++
// End:

