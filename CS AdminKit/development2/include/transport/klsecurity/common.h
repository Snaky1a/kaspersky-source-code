/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	klsecurity/common.h
 * \author	Mikhail Karmazine
 * \date	28.02.2003 18:27:21
 * \brief	
 * 
 */


#ifndef __KLSECURITY_COMMON_H__
#define __KLSECURITY_COMMON_H__

namespace KLSEC
{
	/*!
		\brief DLLType - ��� DLL, ������������ �������������� �������� 
	*/
    enum DLLType
    {
        eClean = 0,
		eCommon = 1
    };


	/*!
		\brief DLLVersion - ������� ��������� ��� �������� ������ 
            �� 4-� ����� (��������, {1.2.3.4}). � ��� ����� 
            ���������� ��������� ��������� (==, !=, <, <=, etc).
            ������������ �������������� ��������.
	*/
    struct DLLVersion
    {
        int nVersion1;  // ������� �����
        int nVersion2;
        int nVersion3;
        int nVersion4;  // ������� �����


        /*!
          \brief	operator== ���������� ��� ����
          \param	const DLLVersion& other 
          \return	bool 
        */
        bool operator==( const DLLVersion& other )
        {
            return  ( nVersion1==other.nVersion1 ) &&
                    ( nVersion2==other.nVersion2 ) &&
                    ( nVersion3==other.nVersion3 ) &&
                    ( nVersion4==other.nVersion4 );
        }


        /*!
          \brief	operator<  �������, ��� ���� ������ ������ ������,
            ��������� ��������������� ���� �� ������ ��������. ��� ������
            ������� ������������ ������ ������ �� ���������, ��������� ������������,
            �.�. {1.2.3.4} ������ ��� {2.1.3.4}
          \param	const DLLVersion& other
          \return	bool 
        */
        bool operator<( const DLLVersion& other )
        {
            if( nVersion1 != other.nVersion1 )
            {
                return nVersion1 < other.nVersion1;
            } else
            if( nVersion2 != other.nVersion2 )
            {
                return nVersion2 < other.nVersion2;
            } else
            if( nVersion3 != other.nVersion3 )
            {
                return nVersion3 < other.nVersion3;
            } else
            {
                return nVersion4 < other.nVersion4;
            }
        }
        
        /* ��������� ��������� ��������� ������������ 
           �� ���� ������������ ������ ����: */
        bool operator!=( const DLLVersion& other )
        {
            return ! operator==( other );
        }

        bool operator<=( const DLLVersion& other )
        {
            return operator<( other ) || operator==( other );
        }

        bool operator>( const DLLVersion& other )
        {
            return ! operator<=( other );
        }

        bool operator>=( const DLLVersion& other )
        {
            return ! operator<( other );
        }
    };
}

#endif //__KLSECURITY_COMMON_H__

// Local Variables:
// mode: C++
// End:
