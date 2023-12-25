/*!
 * (C) 2004 "Kaspersky Lab"
 *
 * \file conn/connector.h
 * \author ������ ��������
 * \date 2004
 * \brief ���������, ���������� �� ���������� ���������� � �������� 
            �����������������. 
 *
 */
/*KLCSAK_PUBLIC_HEADER*/

#ifndef KLCONN_CONNECTOR_H
#define KLCONN_CONNECTOR_H

#include "./conn_types.h"
#include "./settings_synchronizer.h"
#include "./task_settings_synchronizer.h"
#include "./tasks_synchronizer.h"
#include "./app_synchronizer.h"
#include "./notifier.h"


namespace KLCONN
{
#ifdef _WIN32
    #define KLCONN_CALL __cdecl
#else
    #define KLCONN_CALL
#endif

/*!
    \brief ������, ���������� �� ���������� ���������� � ��������
        �����������������.
	
    ������ ������ ������������ �������������� ���������� ��� ����������
    ���������� � �������� �����������������.  ������������ ���������
    ������ ����������:

    1) ���������� ����� ����� ��������, ������� ������������ � �������.
    2) ���������������� ���������� �������������� �������������� � ����
        ������ �����. ������ ����� ��������� � ����� ����������� �������,
        �� ���������� ���� ��� ������ ����������.  ����������� ������
        ������ ������������ ����������� ������ � ����������� �����������
        ��� ����������� ����������.
    3) ���������� ��������� ����� �������.  ������� ������� �� �������
        ������������ ���������������.
    4) ���������� ������������� ����� �������������� ����������� �����
        ������.
    5) ������������� ����� ���������� �������� ��� �������� � �����
       ����������.  ������ � ��������, ����������� � ���������
       ���������������, ����� ��������� ��� ���������� �����������
       ����������.


    ��� ������ ������� �����������, ����������� ����������� ����������,
    ����� ������������ �� ������ �����, �� ��� ���� ������������� 
    ���������� ��������. �.�. ������������ �� ����� ���� ������� ������� 
    ������, ������������� � ������ ���������� ����������.

        �� ������ ���������� ���������� �������� �� ����� �� ������ ����. 
    ������, ��� �������������, ���������� ���������� ����� ����
    ���������������� ��� ������ � "������������" ������ - � ���� ������ 
    ����� ��������� ���������� ���������� ����� ������ "�������" �����,
    � ��������� �������� ����� ���������� ��� ������, ������������� � 
    ���������� ����������; ����� �������� ����������  ���������� �����
    �������� ���� ������. 

        ����� "������������" ����� ����� ���� �������, ��������, ����
    ���������� ���������� ���������� COM -- � ���� ������, � ������
    Connector::StartIntegration ���������� ����� �������  CoInitialize(),
    ����� ������������������� COM ��� "��������" ������, ����� ��������� �
    ���������� ���������� �������� ������ �� ���� ������, ��� ���������
    ������ � ������ Connector::StopIntegration() ���������� ����� �������
    CoUninitialize().

    ��������� � ���������� ���������� � �������� ����������������� �����
    ��������� � ��������� CS AdminKit Product Integration.doc.    
    */

	/*!
		\brief ��������� DLL ����������.
		DLL ���������� ������ �������������� ������� KLCONN_INITDLL, 
        KLCONN_DEINITDLL � KLCONN_CREATECONNECTOR (��. ����).        
        ������� ����������������� ����������� ������ ���� ������� �
        ��������� ��������, �.�. ������������ �� ����� ��� ���� ���� �����
        ��������� ������ ����� �� ���� �������. ���������� �������
        KLCONN_INITDLL ������ ����� ���������� ������� KLCONN_DEINITDLL.
	*/

	/*!
		\brief �������������  DLL ����������.
        

		__declspec(dllexport)
			bool KLCONN_INITDLL(KLERR::Error**  ppError)
		{			
			//��������� �����-���� ��������
			//.............................
		};

	  \param	ppError [out] �������� ������ ��������� ��� �������������
            ��������� ����������
      \return true - ���� ������������� ������ �������, false - � ������
            ������.
      \exception  ������� �� ����������� ����������
	*/

	#define KLCONN_INITDLL  KLCONN_Init
	
	typedef bool (KLCONN_CALL * InitDll)(KLERR::Error** ppError);

	/*!
		\brief ��������������� DLL ����������.

        \exception ������� �� ����������� ����������

	    __declspec(dllexport)
		    void KLCONN_DEINITDLL()
		{			
			//��������� �����-���� ��������
			//.............................
		};	
	*/

	#define KLCONN_DEINITDLL    KLCONN_Deinit

	typedef void (KLCONN_CALL * DeinitDll)();

	/*!
		\brief ��������� ��������� �� ��������� KLCONN::Connector ���
            ���������� ����������.

        \param szwProduct [in] - ��� ����������
        \param szwVersion [in] - ������ ����������
        \param ppConnector [out] - ��������� �� ����������, � �������
                                ����� ������� ��������� �� ���������
        \param ppError [out] - ��������� �� ����������, � �������
                                ����� �������� �������� ������

        \exception ������� �� ����������� ����������

	    __declspec(dllexport)
		    void KLCONN_CREATECONNECTOR(
                    const wchar_t*      szwProduct,
                    const wchar_t*      szwVersion,
                    KLCONN::Connector** ppConnector,
                    KLERR::Error**		ppError)
		{			
			//��������� �����-���� ��������
			//.............................
		};
	
	*/

	#define KLCONN_CREATECONNECTOR  KLCONN_CreateConnector

    class Connector;

	typedef void (KLCONN_CALL * CreateConnector)(
                            const wchar_t*      szwProduct,
                            const wchar_t*      szwVersion,                            
                            KLCONN::Connector** ppConnector,
                            KLERR::Error**		ppError);



    /*!
    \brief ������� ��������� ������, ����������� �� ���������� 
        ���������� � �������� �����������������. 

        ������ ��������� �������� ������ ����� ��� �������
        ����������������� � ������������� ��� ��������� ��� ����������
        ����������.

        ��������� ����������� ����������� ����������
        ��������� ������������ �������� �����������������.

        ������ ������� ���������� ����� ������������ �� ������ �����, �� ���
        ���� ������������� ���������� ��������.
    */


    //! ��� ���������� "���������"
    #define KLCONN_COMPONENT_NAME       L"Connector"
    
    //! ������� ������ ���������� "���������"
    #define KLCONN_COMPONENT_VERSION    L"1.0.0.0"

    #define KLCONN_MAKE_WELLKNOWN(_product) (_product + L"-" + KLCONN_COMPONENT_NAME)



    class KLSTD_NOVTABLE Connector : public KLSTD::KLBaseQI
    {
    public:
    /*!
        \brief ���������� ��������� �� ���������, ������������ ���
            ������������� �������� ����������.

        \param ppSynchronizer	[out]	��������� �� ����������, � �������
            ����� ������� ��������� �� ���������, ������������ ���
            ������������� ��������.

    */
        virtual void CreateSettingsSynchronizer(
			    KLCONN::SettingsSynchronizer ** ppSynchronizer) = 0;

    /*!
      \brief ���������� ��������� �� ���������, ������������ ���
            ������������� �������� ����������.

        \param ppSynchronizer	[out]	��������� �� ����������, � �������
            ����� ������� ��������� �� ���������, ������������ ���
            ������������� �������� ���������� (��. "..\prss\prssconst.h").

        ��������� ��������    
            ��������� ������:
                <container1_name>
                 +---<var1_name>=value1 //type1
                 +---<var2_name>=value2 //type2


            ��������������� �� ��������� ��������:
                <container1_name>                              //PARAMS
                 +---<c_szwSPS_Value>                          //PARAMS_T
                 |          +---<var1_name>                    //PARAMS_T
                 |               +---<c_szwSPS_Value>=value1   //type1
                 |               +---c_szwSPS_Mandatory        //BOOL_T
                 |          +---<var2_name>                    //PARAMS_T
                 |               +---<c_szwSPS_Value>=value2   //type2
                 |               +---c_szwSPS_Mandatory        //BOOL_T
                 +---c_szwSPS_Mandatory                        //BOOL_T

    */
        virtual void CreatePolicySynchronizer(
                KLCONN::SettingsSynchronizer ** ppSynchronizer)  = 0;

    /*!
      \brief ���������� ��������� �� ���������, ������������ ���
            ������������� �������� ����� ����������.

        \param ppSynchronizer	[out]	��������� �� ����������, � �������
            ����� ������� ��������� �� ���������, ������������ ���
            ������������� �������� ����� ����������.
    */
        virtual void CreateTaskSettingsSynchronizer (
			    KLCONN::TaskSettingsSynchronizer ** ppSynchronizer)  = 0;


	/*!
      \brief ���������� ��������� �� ���������, ������������ ���
            ������������� �������� ��������� ����� ����������.

        \param ppSynchronizer	[out]	��������� �� ����������, � �������
            ����� ������� ��������� �� ���������, ������������ ���
            ������������� �������� ��������� ����� ����������.
    */
        virtual void CreateTasksSynchronizer (
			    KLCONN::TasksSynchronizer ** ppSynchronizer)  = 0;

    /*!
      \brief ���������� ��������� �� ���������, ������������ ���
            ������������� �������� ��������� ����������.

        \param ppSynchronizer	[out]	��������� �� ����������, � �������
            ����� ������� ��������� �� ���������, ������������ ���
            ������������� �������� ��������� ����������.
    */
        virtual void CreateAppSynchronizer(
                KLCONN::AppSynchronizer** connector)  = 0;

    /*!
         \brief	������ ����� ���������� ����� ���������� ������������� 
         ������� �����������������. ���������� ���������� �������� 
         ��������� �� KLCONN::Notifier � ����� �������� ��� ������.
         ����� ������ ����� ������ ������� ����������������� ��������
         ������������ ����������, ���������� � ������� ������������� ����
         �������. ���������� ������� StartIntegration ������ �����
         ���������� ������� StopIntegration.

         \param	pNotifier [in] ��������� �� 
    */
        virtual void StartIntegration(KLCONN::Notifier*   pNotifier) = 0;
        
    /*!
         ������ ����� ���������� ����� ������� ��������������� ������� 
         �����������������. ����� ������ �� ����� ������ ���������� 
         ���������� �� ������ �������� ������ ���������� KLCONN::Notifier.
         ����� ������ ������� ������ ������� ����������������� ����������
         ������������ ����������, ���������� � ������� ������������� ����
         �������. ���������� ������� StopIntegration ������ ����� 
         ���������� ������� StartIntegration.
         
         \exception ������ ����� �� ����������� ����������.
    */
        KLSTD_NOTHROW virtual void StopIntegration() throw() = 0;
    };
    
}


#endif // KLCONN_CONNECTOR_H


