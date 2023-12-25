/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file PRES/EventsStorage.h
 * \author ������ �������
 * \date 2002
 * \brief ��������� ��� ������ �� ������� �������, ����������� � �������������� ������.
 *
 */

#ifndef KLPRES_EVENTSSTORAGE_H
#define KLPRES_EVENTSSTORAGE_H

#include <time.h>
#include <string>

#include "std/err/error.h"
#include "std/par/params.h"

#include "kca/prci/componentid.h"

namespace KLPRES {
    /*!
    * \brief Range - �������� �������. ������ �������� � ��������, ���� � ID ��������� �����
        first � second, ��� ����� ������ �� ���� ��������. ����������� �������� �������
        �������� first � second.
    */
    typedef std::pair<long, long> Range;

    typedef std::vector<Range> RangeVector;


	// ������� ������������ PRES ��� ����������/�������� ��������
	/* const wchar_t PRES_EVENT_SUBSCRIPTION_ADDED[] = L"KLPRES_EVENT_SUBSCRIPTION_ADDED";			// ��������� ��������
	const wchar_t PRES_EVENT_SUBSCRIPTION_DELETED[] = L"KLPRES_EVENT_SUBSCRIPTION_DELETED";		// ������� ��������
	const wchar_t PRES_EVENT_SUBSCRIPTION_UPDATED[] = L"KLPRES_EVENT_SUBSCRIPTION_UPDATED";		// ��������� �������� */

	// ������� ������������ PRES ��� ���������� �������
	const wchar_t PRES_EVENT_ADDED[] = L"KLPRES_EVENT_ADDED";	// ������� �������� �������� � ���������
																// ������� ������������ ��� � 5 ������ ���� � ���� 
																// ���������� ���� ��������� ���� �� ���� �������

	// ������� ������������ PRES ��� ������ ���������� ������� � ���������
	const wchar_t PRES_ERR_ADD_EVENT[] = L"KLPRES_ERR_ADD_EVENT";

	// ����� ����� � EventBody
	const wchar_t PRES_EVENT_BODY_PARAM_SUBSCR_NAME[] = L"KLPRES_EVENT_BODY_PARAM_SUBSCR_NAME";		// STRING_T ��� �����������/��������� ��������

	const int EVENTS_STORING_TIME_INTERVAL_INFINITE = -1;		// ����� ���������� ������� ��� �������� ������������
	const int EVENTS_STORING_NUMBER_INFINITE = -1;				// ���������� ����������� ������� ��� �������� ������������
	const int JRNL_PAGE_SIZE_INFINITE = -1;						// ������ �������� ������� ������� �����������

    /* ID_ACROSS_PRES_INSTANCE - LONG_T, ID �������, ���������� ����� �������, �����������
        ����� ����������� PRES-�������. ���� ��� ������� ��������� ����� � ��� ��
        ����������� PRES�, �� � ������������ ������ ID ����� ������. */
    const wchar_t ID_ACROSS_PRES_INSTANCE[] = L"PRES_ID_ACROSS_INSTANCE";	

    /* PRES_INSTANCE_ID - STRING_T, GUID - ������������� ���������� PRES-�������. �.�. ����
        PRES_INSTANCE_ID / ID_ACROSS_PRES_INSTANCE - ���������� ������������� �������, ������������ � PRES�
    */
    const wchar_t PRES_INSTANCE_ID[] = L"PRES_INSTANCE_ID";

    /*!
    * \brief ����� �������� �������
    *  
    */
	const wchar_t EVENT_STORAGE_NAME_LOCAL[] = L"PRES_EVENTS_STORAGE_LOCAL";	// ��������� ���������

    /*!
    * \brief ��������� �������, ������������ ��� ������������ ������� SubscriptionInfo::parEventParametersMask
		����� ������ �������:
			������ (Params)
				|
				+--[EVENT_CLASS_MASK_XXX1 (XxxValue)]
				|	....
				+--[EVENT_CLASS_MASK_XXXn (XxxValue)]

		Value ���� ���������, ����� EVENT_CLASS_MASK_EVENT_PARAMS ������������.
		EVENT_CLASS_MASK_EVENT_PARAMS �������� ���������� ���� �������
    */

	const wchar_t EVENT_CLASS_MASK_PUBLISHER_CID[] = L"KLPRES_ECM_PUBLISHER_SID";	// STRING_T
	const wchar_t EVENT_CLASS_MASK_EVENT_TYPE[] = L"KLPRES_ECM_EVENT_TYPE";			// STRING_T
	const wchar_t EVENT_CLASS_MASK_EVENT_TIME[] = L"KLPRES_ECM_EVENT_TIME";			// DATE_TIME_T
	const wchar_t EVENT_CLASS_MASK_EVENT_LIFETIME[] = L"KLPRES_ECM_EVENT_LIFETIME";	// INT_T
	const wchar_t EVENT_CLASS_MASK_EVENT_PARAMS[] = L"KLPRES_ECM_EVENT_PARAMS";		// PARAMS_T

    class SubscriptionInfo {
	public:
		typedef enum {
			SI_STORE_AS_BINARY = 0,			// ������� ������� � �������� ����
			SI_STORE_AS_TEXT				// ������� ������� � ���� �����, ������������ �������� <Tab> (0x08)
		};

		KLPRCI::ComponentId filter;			///< ������ �� �������������� ����������� ��� ����������� �������.
		std::vector<std::wstring> eventTypes;		///< ���� ������� ��� �����������.     
		KLSTD::CAutoPtr<KLPAR::Params> bodyFilter;  ///< ������ �� ���� ������� ��� �����������.
		KLPRCI::ComponentId subscriber;		// ���������, ��� �������� ������������� �������������� �������.
		bool isSubscriptionPersist;			// �������� �� �������� ��������������.  ��������������
											// �������� �������������� ������������� ��� ������ ����������.
		int maxEvents;		// ������������ ������ (� ��) ������ �������, ����������� ��� ������ ��������.
		int maxPageSize;	// ������������ ������ �������� ������� (� ��) (��. ����� JRNL_PAGE_SIZE_INFINITE)
		KLSTD::CAutoPtr<KLPAR::Params> parEventParametersMask;	// ����� ���������� ������� ������� ����� ���������� � ES
		std::vector<std::wstring> arEventParametersSortMask;	// ����� ���������� ������� ������������ ������� ����� � ����� ��� SI_STORE_AS_TEXT
																// ���� �� ������, �� ������������ ���������� �� ��������
																// ��� �������� ������ ����������� ������� _MakeSortMaskItem
		int nCloseWriteOpenedJournalTimeout;// ����� (msec) ����� ������� ����� ������� ��������� ������� �������� �� ������
		bool bPaused;						// �������� �� ������������ �������

		int nStoreEventsAs;					// ��������� � ����� ���� ������� ������� �� �����
		wchar_t cFieldDelimiter;			// ������ ������-����������� ��� ���������� ����� ������� � ��������� (��� ���� SI_STORE_AS_TEXT)
		std::wstring sEventsListFileName;	// ������ ���� � ����� ��� ���������� ������� 
											// (���� �� ������ ������������ ���������� ����� � �������� ��� ������������� ES ������� �������)
		bool bUseRecNumIndex;				// ��������� ��� ��� ������ �� ������ ������ � ���������
		bool bKeepEventsWhenSubscriptionIsDeleted;	// ��������� ��� ��� ���� � ��������� �������� �� ����� 
													// ����� �������� ���������

		SubscriptionInfo() :
			isSubscriptionPersist(false),
			maxEvents(10),
			maxPageSize(JRNL_PAGE_SIZE_INFINITE),
			nCloseWriteOpenedJournalTimeout(0),
			bPaused(false),
			nStoreEventsAs(SI_STORE_AS_BINARY),
			cFieldDelimiter(L'\t'),
			bUseRecNumIndex(false),
			bKeepEventsWhenSubscriptionIsDeleted(false)
		{
		}
	};

	KLCSKCA_DECL std::wstring SubscriptionInfo_MakeSortMaskItem(std::vector<std::wstring> &arAddress);

	KLCSKCA_DECL long SubscriptionInfo_GetAdjustableMaxEvents(); // �������� � ���������� ������������ ������ (� ��) ������ �������, ����������� ��� ��������.
	KLCSKCA_DECL void SubscriptionInfo_SetAdjustableMaxEvents(long lAdjustableMaxEvents);

    /*!
    * \brief ��������� ��� ������ �� ������� �������, ����������� � �������������� 
    *        ���� ����������� ������.
    *  
    *  ��� ���������� �� ��������� ������ �������� � ����� � ��� �� ���������� �������.
    *  ��������� ����� �������� � ���������� ������� ���������� �� ����, ������� �� ������
    *  ����� ����������������� ��� ���.  ��������� ������� ������������� ���������
    *  ����������������:
    *
    *   1. ����������� ��� ���������� ���������� ��������� ������� � ��������� �������.
    *   2. ����������� �������� ������� �� ��������� �������.
    *   3. ����������� ��������� ���� ���������� �������� �� �������.
    *   4. ����������� ����������� � ������������� ������ �������� ��� ����������.
    *  
    */

    class EventsStorage : public KLSTD::KLBase {
    public:

    /*!
      \brief �������������, ����� ������� ������ ���������������� �����������
            � Events Storage.

        \param info         [in]  ���������� � ��������.
		\param subscription [in/out]  ������������� ��������. ���� ������������ ������ �� ������, 
									  �� ��� ������������ ��� ������������� ����� ��������, ����� -
									  ����� ������ ����� ���������� �������������.
    */
        virtual void StartSubscription (
            const SubscriptionInfo & info,
			std::wstring &subscription )  = 0;

    /*!
      \brief ��������� ��������� �������� �������� � Events Storage.

		\param subscription [in]  ������������� ��������. ���� ������������ ������ �� ������, 
									  �� ��� ������������ ��� ������������� ����� ��������, ����� -
									  ����� ������ ����� ���������� �������������.
        \param info         [in]  ���������� � ��������.
								  !!! �� ������ ������ �������� ��������� ���� eventTypes � bodyFilter. 
								  !!! ��������� ���� �����������.

    */
	    virtual void UpdateSubscription(
			const std::wstring subscription, 
			const SubscriptionInfo &info) = 0;

    /*!
      \brief �������� �������� �������������� �������(��������� �� ������� ResumeSubscription)

		\param subscription [in]  ������������� ��������.
    */
	    virtual void PauseSubscription(
			const std::wstring subscription) = 0;

    /*!
      \brief �������� ����� �������� �������������� �������

		\param subscription [in]  ������������� ��������.
    */
	    virtual void ResumeSubscription(
			const std::wstring subscription) = 0;
		
    /*!
      \brief ������������� �� ������ �������� ��� ������� ���� ��������
             ��� ���������� ����������-����������.

        \param subscriber   [in]  ������������� ����������-����������. ����
                                    ���� ��� ��������� ����� �� ������, ������������ ���
                                    �������� ��� ���� �����������, � �������
                                    ��������� ���������� ����.  ���� �� ������ ��
                                    ���� �� �����, ������������ ��� �������� �
                                    EventsStorage.
        \param nTimeout [in]      ��� ������ �� ��������� EventsStorage ��������
            ������������. ��� ������ �� EventsStorage, ����������� � ������
            �������� ���� �������� ���������� ����� ����� ��������� (� ���.) ��
            ������� ����� ��������������� ��������� � ���������. �������� �����
            ��������� � ������� ��� �������� �� ���������� ������� ������
            �� EventsStorage, � ��� ���������� ����� ���������.
    */
        virtual void ResetSubscriptionsIterator ( 
            const KLPRCI::ComponentId & subscriber,
            int nTimeout = 60 ) = 0;


    /*!
      \brief ���������� ���������� � ��������.


        \param info         [out]  ���������� � ��������.
        \param subscription [out]  ������������� ��������.

		\return true, ���� ���� ��� ������� � ������.       
    */
        virtual bool GetNextSubscription (
            SubscriptionInfo** info,
            std::wstring &subscription) = 0;


    /*!
      \brief ���������� �������� � �������� ���������������.

        \param subscription   [in]  ������������� ��������.

       
    */
        virtual void StopSubscription ( const std::wstring subscription )  = 0;


    /*!
      \brief ������������� �� ������ �������� ��� ������� ������ �������,
             ����������� ��� ���������� ����������.  ������������
             ������� ������������ �� �������������� ��������.

        \param subscription   [in]  ������������� ��������.

		\
       
    */
        virtual void ResetEventsIterator (const std::wstring subscription)  = 0;


   /*!
      \brief ��������� �� ��������� ������� � ������ �������.  

        \param subscription     [in]   ������������� ��������. ���� "",
                        �� ������������ ��������, ��������� ��� ������ SetEventsIterator, MoveToEventWithIndex ���
                        ResetEventsIterator. �������� �������� ������ ��� ���������� ������, ��� GSOAP-������ ������������.

		\return		true ���� ���� �������
    */
        virtual bool NextEvent(const std::wstring & subscription = L"") = 0;

   /*!
      \brief ��������� ��������� �� �������� �� ������������ ������� ��� ��� ����� ������

		\return		true ���� ���� �������
    */
        virtual bool IsEvent() = 0;

    /*!
      \brief	SetEventsIterator
        ������������� �������� �� ������ � �������� ID. ���� ����� ������ ���, ��
        �������� ��������������� �� ��������� ������. ���� ���������� ������
        �����������, �� ��������� ��������������� �� ����� ������� (IsEOF()==true).
		\param subscription   [in]  ������������� ��������.
        \param	nId [in] - ID ������.
    */
		virtual void SetEventsIterator( const std::wstring subscription, long eventID ) = 0;

    /*!
      \brief	MoveToEventWithIndex
        ������������� �������� �� N-� ������ �� ������. ������ ������ ����� ������ 0.
        ���� nRecIdx ������ ��� ����� ���������� ������� � �������, �� �������� 
        ��������������� �� ����� ������� (IsEOF()==true).
		\param subscription   [in]  ������������� ��������.
        \param	nIndex [in] - ����� ������ �� ������. ������ ������ ����� ����� 0.

    */
        virtual void MoveToEventWithIndex( const std::wstring subscription, long nIndex ) = 0;
        
    /*!
      \brief	GetEventsCount
        ���������� ���������� �������.
		\param subscription   [in]  ������������� ��������.
        \param	long - ���������� �������
    */
        virtual long GetEventsCount(const std::wstring subscription) = 0;

   /*!
      \brief ���������� ���������� � �������, ��������� � ���������� 
             � ����������� � EventsStorage.  
       
        \param id               [out]  ������������� ����������, ������������ �������.
		\param eventType        [out]  ��� �������.
        \param eventBody        [out]  ��������� �������.
        \param eventTime        [out]  ����� ������������� �������.
		\param eventID			[out]  ������������� �������.
        \param subscription     [in]   ������������� ��������. ���� "",
                        �� ������������ ��������, ��������� ��� ������ SetEventsIterator, MoveToEventWithIndex ���
                        ResetEventsIterator. �������� �������� ������ ��� ���������� ������, ��� GSOAP-������ ������������.
        
		\return		true ���� ���� �������
    */
        virtual bool GetEvent(
                        KLPRCI::ComponentId & id,
                        std::wstring & eventType,
                        KLPAR::Params ** eventBody,
                        time_t  & eventTime,
						long &eventID,
                        const std::wstring & subscription = L"")  = 0;

   /*!
      \brief ������� ������� �� ������ �� ���������� ������� ������������
       
		\param subscription   [in]  ������������� ��������.
		\param StopEventID	  [in]  ������������� ��������� �������.
    */
        virtual void DeleteEvents(const std::wstring subscription, const long StopEventID) = 0;

   /*!
      \brief DeleteOneEventByID ������� ������� � ��������� ID � ��������� ��������
       
		\param subscription   [in]  ������������� ��������.
		\param nEventID	  [in]  ������������� �������.
    */
		virtual void DeleteOneEventByID(const std::wstring subscription, const long nEventID) = 0;
        
   /*!
      \brief DeleteRanges - ������� ������ �� �������, ���������� � ���������� ���������.
		\param subscription   [in]  ������������� ��������.
		\param	vectRanges [in] - ������ ���������� �������, ������� ���� �������.
    */
		virtual void DeleteRanges(const std::wstring subscription, const RangeVector & vectRanges) = 0;


    /*

    /*!
      \brief ������� ������ �������, ����������� ��� ��������� ��������.

        \param subscription   [in]  ������������� ��������.
    */
        virtual void ClearEventsList (const std::wstring subscription) = 0;

    /*!
      \brief ���������� ������� ������ ��������� �������

        \param subscription   [in]  ������������� ��������.
    */
        virtual AVP_longlong GetEventStorageFileSize (const std::wstring subscription) = 0;

    /*!
      \brief ������� �� �������� ������������ � ����� ������ �� ���� �������,
			 ����������� maxEvents ��������.

        \param subscription   [in]  ������������� ��������.
    */
        virtual void RemoveExpiredEvents (const std::wstring subscription)  = 0;

    /*!
      \brief ������������� �� ������ �������� ��� ������� ������ �������,
             ����������� ��� ���������� ����������.  ������������
             ������� ������������ �� �������������� ��������.

        \param subscription   [in]  ������������� ��������.

		���������� ������������� ����� �������, ������� ������������ ������ ���, 
		����� ��������� ����� Central File
    */
        virtual std::wstring ResetEventsIteratorEx(const std::wstring& subscription) = 0;
		
    /*!
      \brief	SetEventsIterator
        ������������� �������� �� ������ � �������� ID. ���� ����� ������ ���, ��
        �������� ��������������� �� ��������� ������. ���� ���������� ������
        �����������, �� ��������� ��������������� �� ����� ������� (IsEOF()==true).
		\param subscription   [in]  ������������� ��������.
        \param	nId [in] - ID ������.

		���������� ������������� ����� �������, ������� ������������ ������ ���, 
		����� ��������� ����� Central File
    */
		virtual std::wstring SetEventsIteratorEx(const std::wstring subscription, long eventID) = 0;
    };
    
}

/*!
  \brief ������� proxy-������ ��� EventsStorage

    \param sServerObjectID		[in] ���������� ������������� ��� ������� � ���������� ���������� �������
	\param cidLocalComponent	[in] ������������ �������, �� ���� �������� ����� ������������� ��������� ������
	\param cidComponent			[in] ������������ ���������� ������� (Event Storage Server)
    \param ppEventsStorage      [out] ��������� �� proxy-������
	\param bLocalProxy			[in] ������������ ��� ��� ��������� ��� ������� � ��������� �����
*/
KLCSKCA_DECL void KLPRES_CreateEventsStorageProxy(const std::wstring sServerObjectID, 
												const KLPRCI::ComponentId& cidLocalComponent, 
												const KLPRCI::ComponentId& cidComponent, 
												KLPRES::EventsStorage** ppEventsStorage, 
												bool bLocalProxy = false);
/*!
  \brief ������� ������ EventsStorage

    \param sServerObjectID					[in] ���������� ������������� ���������� ���������� �������
    \param sProductName						[in] ��� ��������
    \param sProductVersion					[in] ������ ��������
    \param sSubscriptionStorageFilePath     [in] ������ ���� � ����� ��������� Subscriptions
	\param sEventsStorageFolder			    [in] ������ ���� � ����� �������� Events
    \param bSubscribeToEventsToStore        [in] ���� true, �� ������ ����� ������������� �� �������,
                                                    ������� �� ������ ��������� � ���������.
                                                    ���� false, �� ������ ����� �������������� ������
                                                    ��� �������� ������� � ��������� (����� ���-�
                                                    EventsStorage), � �.�. ���
                                                    ����������/����������/�������� ��������.
*/
KLCSKCA_DECL void KLPRES_CreateEventsStorageServer(const std::wstring sServerObjectID, 
												 const std::wstring sProductName,
												 const std::wstring sProductVersion,
												 const std::wstring sSubscriptionsStorageFilePath,
												 const std::wstring sEventsStorageFolder,
                                                 bool bSubscribeToEventsToStore = true );

/*!
  \brief ������� ������ EventsStorage

    \param sServerObjectID					[in] ���������� ������������� ���������� ���������� �������
    \param cidAgent							[in] Component ID ������
    \param sSubscriptionStorageFilePath     [in] ������ ���� � ����� ��������� Subscriptions
	\param sEventsStorageFolder			    [in] ������ ���� � ����� �������� Events
    \param bSubscribeToEventsToStore        [in] ���� true, �� ������ ����� ������������� �� �������,
                                                    ������� �� ������ ��������� � ���������.
                                                    ���� false, �� ������ ����� �������������� ������
                                                    ��� �������� ������� � ��������� (����� ���-�
                                                    EventsStorage), � �.�. ���
                                                    ����������/����������/�������� ��������.
*/
KLCSKCA_DECL void KLPRES_CreateEventsStorageServer2(const std::wstring sServerObjectID, 
												 const KLPRCI::ComponentId& cidAgent, 
												 const std::wstring sSubscriptionsStorageFilePath,
												 const std::wstring sEventsStorageFolder,
                                                 bool bSubscribeToEventsToStore = true );

///*!
//  \brief ������� ������ EventsStorage
//
//    \param sServerObjectID					[in] ���������� ������������� ���������� ���������� �������
//    \param sProductName						[in] ��� ��������
//    \param sProductVersion					[in] ������ ��������
//    \param sSubscriptionStorageFilePath     [in] ������ ���� � ����� ��������� Subscriptions
//	\param sEventsStorageFolder			    [in] ������ ���� � ����� �������� Events
//*/
//KLCSKCA_DECL void KLPRES_CreateEventsStorageServerAndListener(const std::wstring sServerObjectID, 
//												 const KLPRCI::ComponentId& cidComponent,
//												 const std::wstring sProductName,
//												 const std::wstring sProductVersion,
//												 const std::wstring sSubscriptionsStorageFilePath,
//												 const std::wstring sEventsStorageFolder);
//
/*!
  \brief ������� ��������� ������ EventsStorage

    \param sServerObjectID		[in] ���������� ������������� ��� ������� � ���������� ���������� �������
	\param bWaitEventQueueEmpty	[in] ����� ���� ��� ������� � ������� EventsSource ����� ��������� � ���������
									 �������� ��� ��������������� ���������
*/
KLCSKCA_DECL void KLPRES_DeleteEventsStorageServer(const std::wstring sServerObjectID, bool bWaitEventQueueEmpty = false);

#endif // KLPRES_EVENTSSTORAGE_H
