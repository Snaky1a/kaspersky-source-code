/*!
 * (C) 2004 "Kaspersky Lab"
 *
 * \file conn/settings_synchronizer.h
 * \author ������ ��������
 * \date 2004
 * \brief ���������, ���������� �� ������������� ��������
 *        ���������� � ����������� ������� �����������������. 
 *
 */

#ifndef KLCONN_SETTINGS_SYNCHRONIZER_H
#define KLCONN_SETTINGS_SYNCHRONIZER_H
/*KLCSAK_PUBLIC_HEADER*/

#include "./conn_types.h"

#include "./settings_synchronizer_base.h"

namespace KLCONN
{
    /*!
     \brief ���������, ���������� �� ������������� �������� ����������
	        � ����������� ������� �����������������.

        ��������� ����������� ����������� ����������.
        ��������� ������������ �������� �����������������.

        ������ ������� ���������� ����� ������������ �� ������ �����, �� ���
        ���� ������������� ���������� ��������.

        ��������� ������� �� ����� ���������� ������. ������ ������ 
        ������������ ������ � ���������� -- ����������� Params.
        ��� ������  ������������� � �������� ��������, ����� ����� �� 
        ������� ��� 31 ������, �� ����� ��������� ������� \ / : * ? \ " < > 
        � �� ������ ���������� �� �����.
    */

    class KLSTD_NOVTABLE SettingsSynchronizer : public SettingsSynchronizerBase
    {
    public:

    /*!
      \brief ���������� ������ ���� ������ �������� ����������.
        � ������ ������ ������������� ���������� ���� KLERR::Error*

	  \param vecSections [out] ������ ��������� � ���������� ������ ��������
                    ������������ ������ ����������� ���������� �������.

    */
        virtual void GetSectionsList(
                    KLSTD::AKWSTRARR& vecSections)  = 0;

    /*!
      \brief ���������� ������� �������� �������� ��� �������� ������.
        � ������ ������ ������������� ���������� ���� KLERR::Error*

		\param szwSection [in]	��� ������ ��� ������ ��������.
        \param pFilter    [in]  ������; ������������, �� ������� ����, ��
                ����������, ������� ������������ � �������; ���� �����
                NULL, ������������ ��� ���������� ������.
		\param ppSettings [out]	��������� Params �� ���������� ������
                ������. ���������� ���������� �� ������ ������� ������ ��
                ������ ��������� � ��� ����������.
		
		\exception KLSTD::STDE_NOTFOUND - ������ � ��������� ������ ��
            ����������
    */
        virtual void GetSection (
			        const wchar_t*  szwSection,
                    KLPAR::Params*  pFilter,
			        KLPAR::Params** ppSettings) = 0;


    /*!
      \brief ���������� ������ � ���������. ���� ������ �� ����������, ���
        ���������; ���� ������ ��� ����������, �� �� ������ ����������
        ���������� �� pData.
        � ������ ������ ������������� ���������� ���� KLERR::Error*
        
		\param szwSection   [in] ��� ������ ��� ����������.
		\param pData	    [in] ���������� ��� ������ ������.
        \param ppUnsupported[out] ���������������� ����������, �.�. 
                ����������� ���������� ���������� �� pData, ������� ��
                ����� ���� �� ����������� ���������.

    */
        virtual void PutSection (
			        const wchar_t*  szwSection,
			        KLPAR::Params*  pData,
                    KLPAR::Params** ppUnsupported)  = 0;

    /*!
      \brief ������� ������ � �������� ������.
        � ������ ������ ������������� ���������� ���� KLERR::Error*

		\param szwSection [in] ��� ������ ��� ��������.

		\return false - ���� ������ �� ����������
        \return true - ���� ������ ���� ������� �������

    */
        virtual bool DeleteSection (
			        const wchar_t*  szwSection)  = 0;

    };
    
}


#endif // KLCONN_SETTINGS_SYNCHRONIZER_H

