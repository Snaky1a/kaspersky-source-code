/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file PRCI/ProductStatistics.h
 * \author ������ ��������
 * \date 2002
 * \brief ��������� ��� �������������� ����������� �������� ���������� ����� ������.
 *
 */

#ifndef KLPRCI_PRODUCTSTATISTICS_H
#define KLPRCI_PRODUCTSTATISTICS_H

#include <string>

#include "prci_const.h"
#include "std/err/error.h"
#include "std/par/params.h"

namespace KLPRCI {


    /*!
    * \brief ��������� ��� �������������� ����������� �������� ���������� ����� ������.
    */


    class KLSTD_NOVTABLE ProductStatistics: public KLSTD::KLBaseQI{
    public:

    /*!
		\brief ������������� ������� �������� ���������� ������ ����������.

        ����� ������ ����� ������ ��������������� �� ���������� ����������
        ����������� Params ����� �� ������ ProductStatistics.  ������ �� ������
        �����-���� ������� �������������� �������� ���������� ���������� 
        Params ����� ������ ����� ������.

        \param statistics       [in]  ���������� ������ ����������.
	*/

       virtual void SetStatisticsData( KLPAR::Params * statistics )  = 0;


    /*!
		\brief ��������� �������� ���������� ���������� ������ ����������.

        ���� � ���������� �� ����������� ������ ���������� ��� ����������
        ����� ���������, �� ��� ��� ���������� ��������.  ���� �� ���������� �
        ������ ������� �� ����������, ��� ����������� � ���������� �� �����������
        ������ ����������.

        \param statistics       [in]  ����� ���������� � ������ ����������
                                      ���������� ������ ����������.
	*/

       virtual void ReplaceStatisticsData( KLPAR::Params * statistics ) = 0;


    /*!
      \brief ������� ��������� ����������.

      ������ ����� ������� ��������� ���������� � �������, ����������� � 
      ��������� statistics.  ���� ���������� � ������ ������� �� ����������, 
      ������������ ���������� NOT_EXIST.
	*/

	   virtual void DeleteStatisticsData(KLPAR::Params * statistics ) =0;

    };



}


#endif // KLPRCI_PRODUCTSTATISTICS_H
