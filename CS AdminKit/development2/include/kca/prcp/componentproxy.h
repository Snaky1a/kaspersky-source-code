/*!
 * (C) 2002 Kaspersky Lab 
 * 
 * \file	ComponentProxy.h
 * \author	Andrew Kazachkov
 * \date	01.10.2002 12:34:51
 * \brief	������� ��������� ������ Product Component Proxy (PRCP).
 * 
 */

#ifndef KLPRCP_COMPONENTPROXY_H
#define KLPRCP_COMPONENTPROXY_H

#include <time.h>
#include <string>
#include <vector>

#include "std/err/error.h"
#include "std/par/params.h"
#include "kca/prci/componentinstance.h"
#include "kca/prci/producttaskscontrol.h"
#include "errors.h"
#include "prcp_const.h"

namespace KLPRCP {	

   /*!
		\brief Callback - ������� ��� ��������� ���������� � �������, 
         ������������ � ���������� ��������.  ���������� ���� ������� ������ ���� 
         ����������������.

        \param id           [in]  ������������� ����������, ������������ �������.
		\param eventType    [in]  ��� �������.
        \param eventBody    [in]  ��������� �������.
        \param time         [in]  ����� ������������� �������.
        \param context      [in]  ��������, ���������� � �������� �� �������.

        ������ ������� EventCallback ��������� ��������� ��������.
        1. �������� ������
        2. �������� �� ������� � �������.
        3. ���������� ������ ����������� � �����.
        4. ��������� � SettingsStorage, EventStorage � TasksStorage.
        5. �������� ������� �������.
	*/

    typedef void (*EventCallback)(
        const KLPRCI::ComponentId & id,
        const std::wstring & eventType,
        const KLPAR::Params * eventBody,
        time_t time,
        void * context );
    
    //! using this constant as asyncid results in calling method instead of a task
    const wchar_t c_szwAsyncMethod[] = L"KLPRCP_METHOD";


    /*!
    * \brief ������� ��������� ������ Product Component Proxy (PRCP).
    *  
    *  ������ ��������� �������� �������������� ���������������� ���������� �������� 
    *  ��� ������ ����������� ��������. 
    *
    */
    

    class KLSTD_NOVTABLE ComponentProxy: public KLSTD::KLBase {
    public:
    /*!
      \brief ���������� ������������� ����������.

      ������������� ���������� �������� ���������� ��� ���� ����������� ������
      � ���� �� ����, ������������� ������ � ���� �� ��������. �������������
      ���������� ������ ������ ����.
      
      \return ������������� ����������.
 
    */

        virtual void GetInstanceId(std::wstring& wstrID) const = 0;


    /*!
      \brief ���������� �����, � ������� �������� ���������� ��������� ������
                ���������� ������ ����������������� � ����� ���������� ������.

      \return   ������������ ����� ���������� � ���������� ������ (msec) ���
                KLSTD_INFINITE, ���� ��������� �� ���������� ����������.
      
      \exception ������ ����� �� ����������� ����������.
 
    */
        virtual long GetPingTimeout() const = 0;



    /*!
      \brief ���������� ������� ��������� ����������.

      \return ��������� ����������.
 
    */

        virtual KLPRCI::ComponentInstanceState GetState() const = 0;


    /*!
      \brief ���������� ���������� ������ ����������. ���� � ���������� ����������
      ������ ����� �����, ������������ ���������� ������ ��� ���� �����.

       \param statistics [in,out] ���������� ������ ����������.

    */

        virtual void GetStatistics(KLPAR::Params * statistics) const = 0;


    /*!
      \brief ������������� ������ ����������.

    */

        virtual void Stop() = 0;


    /*!
      \brief ���������������� ������ ����������.

    */

        virtual void Suspend() = 0;


    /*!
      \brief ������������ ������ ����������.

    */

        virtual void Resume() = 0;
    

    /*!
      \brief ��������� ������ ���������� �� ����������.

        \param taskName       [in]  ��� ����������� ������.
        \param params         [in]  ��������� ��� ���������� ������.
        \param timeout        [in]  ������������ ����� ���������� ������ (msec).

        \return ������������� ���������� ������.

    */

        virtual long RunTask(
								const std::wstring& taskName,
								const KLPAR::Params* params,
								const std::wstring& asyncId=L"",
								long timeout = 0) = 0;

    /*!
      \brief ��������� ������ ���������� �� ���������� (���������) �
            ������� ���������� ������.

        \param taskName       [in]  ��� ����������� ������.
        \param params         [in]  ��������� ��� ���������� ������.
        \param results        [out] ���������� ���������� ������. 
                                    ���� ������ �� ���������� �����������, 
        \param timeout        [in]  ������������ ����� ���������� ������ (msec). 
                                    <=0 - ����������� �����.
        \param pTaskState     [out] ��c������, � ������� ����������� ������

        \return ������������� ����������� ������.

    */

		virtual long RunTaskSync(
                        const std::wstring&		taskName, 
                        const KLPAR::Params*	params,
                        KLPAR::Params**			results,
                        long					timeout=KLSTD_INFINITE,
						const std::wstring&		asyncId = L"",
                        KLPRCI::TaskState*      pTaskState=NULL) = 0;

	/*!
	  \brief	���������� ��� ������ � ��������������� taskId.

	  \param	taskId [in]
	  \param	wstrTaskName [out]
	*/
		virtual void GetTaskName(long taskId, std::wstring& wstrTaskName) const =0;

    /*!
      \brief ������������� ���������� ������ ����������� � ������� ������ ��
             ������ ����������� ����������� �����.  ����� ������ �����������.
             ���������� ���������� ������� ������������ � ������� c_EventTaskState.

        \param taskId         [in]  ������������� ���������� ������.

    */		
        virtual void StopTask(long taskId) = 0;

    /*!
      \brief ���������������� ���������� ������ �����������.  ����� ������ 
                �����������.

        \param taskId         [in]  ������������� ���������� ������.

    */
        virtual void SuspendTask(long taskId) = 0;


    /*!
      \brief ������������ ���������� ������ �����������.  ����� ������ �����������.

        \param taskId         [in]  ������������� ���������� ������.

    */
        virtual void ResumeTask(long taskId) = 0;

        virtual void ReloadTask(long taskId, KLPAR::Params* pNewSettings) = 0;
        

    /*!
      \brief ���������� ������ ����������� ����������� �����.

        \param ids [out] ������ ��������������� ����������� ����������� �����.

    */
        virtual void GetTasksList( std::vector<long> & ids) const  = 0;

    /*!
      \brief ���������� ��������� ������.
	*/		
		virtual void GetTaskParams(
							long			idTask,
							KLPAR::Params*	pFilter, 
							KLPAR::Params**	ppResult) = 0;

    /*!
      \brief ���������� ������� ��������� ����������� ����������� ������.

        \param taskId         [in]  ������������� ������.

        \return ��������� ����������� ����������� ������.

    */
        virtual KLPRCI::TaskState GetTaskState(long taskId) const = 0;

    /*!
      \brief ���������� ������� ���������� ������.

        \param taskId         [in]  ������������� ������.

        \return ������� ���������� ������.

    */
        virtual int GetTaskCompletion(long taskId) const = 0;



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

		\param eventType        [in]  ��� �������.
        \param eventBodyFilter  [in]  ������ �� ��������� �������, �.�. ����� NULL.
        \param callback         [in]  Callback - ������� ��� ��������� ���������� � 
                                        ������������� �������.
        \param context          [in]  �������� �������� ��� �������� � callback - �������.
                                      ������ ��������� ������ ���� ���������� ��� �����
                                      ��������.
        \param hSubscribe       [out] ������������� �������� ��� ������������ ������ 
                                        StopSubscription.

    */

       virtual void Subscribe( 
                        const std::wstring&		eventType,
                        const KLPAR::Params*	eventBodyFilter,
                        EventCallback			callback,
                        void*					context,
						KLPRCI::HSUBSCRIBE&		hSubscribe)= 0;

    /*!
      \brief ���������� �������� ������� �� ������� ������������� ����.
       
        ������������ �������� �������� ��� ������� ComponentProxy, 
        ��������� ������� ��������� � �����������, ����������� � ������ ������.

		\param hSubscribe       [in]  ������������� ��������.

    */

       virtual void StopSubscription(KLPRCI::HSUBSCRIBE hSubscribe)=0;


	/*!
	  \brief	���������� ComponentId proxy

	  \return	ComponentId proxy
	*/
	   virtual KLPRCI::ComponentId GetComponentID()=0;


	/*!
	  \brief	���������� ComponentId ����������, � ������� proxy "������ �����"

	  \return	ComponentId ����������
	*/
	   virtual KLPRCI::ComponentId GetRemoteComponentID()=0;  

		/*!
		  \brief	��������� ������� ��������� ���������� � �����������. ����
					���������� false, �� ���������� � ����������� ���������, �
					������������ ������ ������ ��� ������.
					������� ������ ���������, ��� ���������� ����� �����������
					����� ������ ������ �������, �� �� ������������� �������
					������.

		  \return	true, ���� ���������� ������������
		*/
	   virtual bool IsValid() = 0;
    };

}

/*!
	\brief ������� ����� ������ ComponentProxy ��� ���������� �������� ����������.

	���� ��������� ����������� �������� � �������������� ����������, ����������� �
	��������� id, �� ������������ ��������� �� ������������ ���������.

	\param id      [in]  ������������� ���������� ��������� proxy ����������.
	\param proxy   [out] ��������� �� ����������, � ������� ����� �������
		��������� �� ��������� ������.

	\exception	ERR_CANT_CONNECT ���������� ��������� �� �������
*/

KLCSKCA_DECL void KLPRCP_CreateComponentProxy( 
                        const KLPRCI::ComponentId & id,
                        KLPRCP::ComponentProxy**	ppProxy);


/*!
  \brief	������������� ��������� ��� ����������� � ������� ����������.
			��� ������� ������� ������ �������� ����� ����� �����������.
*/
KLCSKCA_DECL void KLPRCP_UnloadInProcessComponents();

/*!
  \brief	���������� ������ �����������, ����������� � �������� ������������
			������� ��������.
*/
KLCSKCA_DECL void KLPRCP_GetLoadedInProcessComponents(
						KLPRCI::ComponentId&			filter,
						std::vector<KLPRCI::ComponentId>&	ids);



#endif // KLPRCI_COMPONENTPROXY_H
