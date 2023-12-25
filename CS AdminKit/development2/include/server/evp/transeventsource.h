/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file TransEventSource.h
 * \author ������ ��������
 * \date 18:40 22.11.2002
 * \brief 
 */


#ifndef _KLTRANSEVENTSOURCE_H__808F894F_2D08_4a03_ABA1_460E42CE1C1D__
#define _KLTRANSEVENTSOURCE_H__808F894F_2D08_4a03_ABA1_460E42CE1C1D__

#include <transport/ev/eventsource.h>

namespace KLEVP {

	typedef struct
	{
		KLPRCI::ComponentId componentId;
		std::wstring wstrHostDomain;
		std::wstring wstrHostName;
	} caller_id_t;

	/*!
	\brief Callback - ������� ��� ��������� ���������� � �������, 
		 ������������ � ���������� ��������.  ���������� ���� ������� ������ ���� 
		 ����������������. ���� ������� ����������� ����������, �� ������� ����������
		 ������������ �����������,� ���������� �������������.
		 ���� ��� callback'� ���������� ��������� (�.�. ��� ������� ����������), ��
		 ���������� Commit ����������.

		\param caller		[in]  ������ ����������, ����������� � �������
		\param pDatabase    [in]  ���� ������, � ������ �������� ���� ����������.
					�������� ��� ������������� �������� ������� �� ����������.
		\param eventType    [in]  ��� �������.
		\param eventBody    [in]  ��������� �������.
		\param time         [in]  ����� ������������� �������.
		\param pParam		[in]  ��������, ���������� ��� �������� �� �������.
	*/
	typedef void (*TransactionalEventCallback)(
		const caller_id_t& caller,
		void* pDatabase,
		const std::wstring & eventType,
		const KLPAR::Params * eventBody,
		KLSTD::precise_time_t tEventRiseTime,
		void* pParam );



    /*!
    * \brief ��������� ��� �������� � ������ �� �������� ��� �������������� �������
	*		
    */

    class KLSTD_NOVTABLE TransEventSource : public KLSTD::KLBase {
    public:
		/*!
		\brief ����������� ������� �� ��������� ���������� � 
				������������� ������� � ���������� � ������������� callback 
				��� ��������� ����������.
   
			���� ������ �� ������ ��� ������� �� ���������� ������� �� ����� ��������� 
			�� ������������.  ��� ������� �� ��������� ������� �������� ������������
			������ �� ��������� �����, �� ���� ���� ���� ���� � � ������� � � ������� �
			��� ���� �����, �� ������� ������������ ����������.

			������ ����� ����������� �� ��������� ����� �������.  � ���� ������ �� �������
			��������� ����������� ��� ������� �� ���������� �� �������� �������� �������.

			\param localId			[in]  ID ���������� ���������� (�.�. ����� �������)
			\param remoteId			[in]  ID ���������� ���������� (�.�. ������)
			\param eventType        [in]  ��� �������.
			\param eventBodyFilter  [in]  ������ �� ��������� �������, �.�. ����� NULL.
			\param callback         [in]  Callback - ������� ��� ��������� ���������� � 
											������������� �������.
			\param context          [in]  �������� �������� ��� �������� � callback - �������.
										  ������ ��������� ������ ���� ���������� ��� �����
										  ��������.
			\param subscriptionId   [out] ������������� �������� ��� ������������ ������ 
											StopSubscription.

		*/
		virtual void Subscribe(
			const std::wstring&			wstrSubscriberPersistentId,
			const std::wstring&			eventType,
			const KLPAR::Params*		eventBodyFilter,
			TransactionalEventCallback	callback,
			void*						context,
			KLEV::SubscriptionId&		subscriptionId )= 0;


		/*!
		\brief ���������� �������� ������� �� ������� ������������� ����.

			������������ �������� �������� ��� ������� ComponentProxy, 
			��������� ������� ��������� � �����������, ����������� � ������ ������.

			\param hSubscribe       [in]  ������������� ��������.

		*/
		virtual void StopSubscription( KLEV::SubscriptionId subscriptionId )=0;
	};
}

#endif // _KLTRANSEVENTSOURCE_H__808F894F_2D08_4a03_ABA1_460E42CE1C1D__

// Local Variables:
// mode: C++
// End:

