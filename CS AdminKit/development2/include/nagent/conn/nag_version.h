#ifndef __NAG_VERSION_H__
#define __NAG_VERSION_H__

#include "./conn_types.h"

namespace KLCONN
{

    /*!
     \brief         
        ��������� ����������� �������� �����������������.
        ��������� ������������ ����������� ����������.

        ������ ������� ���������� ����� ������������ �� ������ �����.

        �������������� ������� ������� � ������ 6.0 (6.0.0.0)
        ������ ��������� ��������� ���������� ����� ��������� 
        ����� KLCONN::Notifier::QueryInterface
    
        ������

            KLSTD::CAutoPtr<KLCONN::Notifier> pNotifier;
            ...  
            KLSTD::CAutoPtr<KLCONN::NagentVersionInfo>  pNagentVersionInfo;
            pNotifier->QueryInterface(
                    KLSTD_IIDOF(KLCONN::NagentVersionInfo),
                    (void**)&pNagentVersionInfo);
            if(pNagentVersionInfo)
            {
                ...
            };
    */
    class KLSTD_NOVTABLE  NagentVersionInfo
        :   public KLSTD::KLBaseQI
    {
    public:

        /*!
          \brief	���������� ������ �������� ������. 

          \return	AVP_qword, 4 16-����� ����� �������� �������� 4 
                    ���������� ������. 
                    ��������, ��� ������ 6.0.1288.0
                    |6|0|1288|0|
                    0x0006000005080000
        */
        virtual AVP_qword GetNagentVersion() = 0;
    };
};

#endif //__NAG_VERSION_H__
