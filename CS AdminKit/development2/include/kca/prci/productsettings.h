/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file PRCI/ProductSettings.h
 * \author ������ ��������
 * \date 2002
 * \brief ��������� ������, ���������������� ���������������� �� ������� � ����������
 *          ��������.
 *
 */

#ifndef KLPRCI_PRODUCTSETTINGS_H
#define KLPRCI_PRODUCTSETTINGS_H

#include <string>

#include "prci_const.h"
#include "kca/prss/settingsstorage.h"
#include "std/err/error.h"
#include "std/par/value.h"

namespace KLPRCI
{	

    /*!
		\brief Callback - ������� ��� ��������� ���������� � ��������� ��������. 
         ���������� ���� ������� ������ ���� ����������������.

        \param productName      [in]  ��� �������� ��� �������� ���������� ���������.
        \param version          [in]  ������ ��������.
		\param section          [in]  ��� ������ �������� � ���������� ���������.
		\param parameterName    [in]  ��� ����������� ��������� ��������.
        \param oldValue         [in]  ������ �������� ���������.
        \param newValue         [in]  ����� �������� ���������.
	*/
    typedef void (*SettingsChangeCallback)(
		void*				context,
        const std::wstring&	productName, 
        const std::wstring&	version,
        const std::wstring&	section, 
        const std::wstring&	parameterName,
        const KLPAR::Value*	oldValue,
        const KLPAR::Value*	newValue );

    /*!
    * \brief ��������� ������ Product Settings.
    *  
    *  ������ ������ ������������ ��� ��������� ������ ��������� ��������
    *  �������� � ��� ���������/�������� ����������� � ��������� ��������.
    *
    */
    
    class KLSTD_NOVTABLE ProductSettings: public KLSTD::KLBaseQI
    {
    public:
    /*!
      \brief ���������� ������������ ��������� ��������, � ������� �������� ��������� �����������.

    */
        virtual std::wstring GetSettingsStorageLocation(
                  KLPRSS::SS_OPEN_TYPE nOpenType=KLPRSS::SSOT_SMART) const = 0;


    /*!
      \brief ����������� ��������� �������� �� ��������� ���������� � 
            ��������� �������� � ������������� callback ��� ��������� ����������.
       
        ���� ������ �� ������ ���� �� ���������� �������� (��� ��������, ������,
        ������, ��� ���������), �� ���������� ������� �� ����� ��������� �� ������������.
        ������ ����� ����������� �� ��������� ����� �������.  � ���� ������ �� �������
        ��������� ����������� ��� ������� �� ���������� �� �������� �������� �������.

        \param productName      [in]  ��� �������� ��� �������� ���������� ���������.
        \param version          [in]  ������ ��������.
		\param section          [in]  ��� ������ �������� � ���������� ���������.
		\param parameterName    [in]  ��� ����������� ��������� ��������.
        \param callback         [in]  Callback - ������� ��� ��������� ���������� � 
                                        ��������� ��������.
		\param hSubscription	[out] ������������� ��������

    */

       virtual void SubscribeOnSettingsChange( 
                        const std::wstring&		productName, 
                        const std::wstring&		version,
                        const std::wstring&		section, 
                        const std::wstring&		parameterName,
						void*					context,
                        SettingsChangeCallback	callback,
						KLPRCI::HSUBSCRIBE&		hSubscription)  = 0;

    /*!
      \brief �������� �������� �� ��������� ���������� � ��������� ��������.       

        \param hSubscription    [in]  ������������� ��������
    */

       virtual void CancelSettingsChangeSubscription(
						KLPRCI::HSUBSCRIBE		hSubscription)  = 0;



    /*!
		\brief ������� ��� ����������� � ��������� ��������.

        \param productName      [in]  ��� �������� ��� �������� ���������� ���������.
        \param version          [in]  ������ ��������.
		\param section          [in]  ��� ������ �������� � ���������� ���������.
		\param parameterName    [in]  ��� ����������� ��������� ��������.
        \param oldValue         [in]  ������ �������� ���������.
        \param newValue         [in]  ����� �������� ���������.
        \param type             [in]  ���������, ����� ������ ��������� ����
                                      ��������.
        
        ��������:
        �������� ���������
        wstrLocation=pInstance->GetSettingsStorageLocation(SSOT_CURRENT_USER);
        CAutoPtr<SettingsStorage> pSS;        
        KLPRSS::KLPRSS_OpenSettingsStorageRW(wstrLocation, &pSS);
        ... ����� � ���������...
        pInstance->NotifyAboutSettingsChange(
                                        MY_PRODUCT,
                                        MY_VERSION,
                                        MY_SECTION,
                                        L"",
                                        NULL,
                                        NULL,
                                        SSOT_CURRENT_USER);// ��� ���������
                              
	*/
    virtual void NotifyAboutSettingsChange(
        const std::wstring & productName, 
        const std::wstring & version,
        const std::wstring & section, 
        const std::wstring & parameterName,
        const KLPAR::Value * oldValue,
        const KLPAR::Value * newValue,
        KLPRSS::SS_OPEN_TYPE type = KLPRSS::SSOT_SMART) = 0;
    
    };



}


#endif // KLPRCI_PRODUCTSETTINGS_H
