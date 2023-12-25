#include "stdafx.h"
#include "msi_misc.h"
#include "../common/ca_misc.h"
#include "../common/ca_data_parser.h"

/*!
  \brief
	MySplitString - �������� �� ������ wstr ��������, ����������� ������� wstrDelim,
        � ��������� ��� ������ vectValues, � ��� �� �������, � ����� ��� ����������� � �������� ������.
        ��� ���� wstrDelim �� ����������� � �������� ��������, � ������� ����������� � ������� ���������, 
        �.�. ������� ����� ���� ��� ������ ���������, ��� � ������ wstrDelim.
        ���� wstrDelim ����������, �� ������������ ��� ������ wstr. ���� ����� ���������� wstrDelim
        ������ ���, �� � ����� ������ ����� ������ ������. ���� ��� wstrDelim �������
        ���� �� ������, �� � ������������� ����� ����� ������ ������.
        � ������ ������ ������� ������� vectValues.

  \param	 const std::wstring & wstr - [in] �������� ������
  \param	const std::wstring & wstrDelim - [in] �����������
  \param	std::vector<std::wstring> & vectValues - [out] ���������
*/
void MySplitString( const std::string & str,
                        const std::string & strDelim,
                        std::vector<std::string> & vectValues ) {
	using namespace std;

    vectValues.clear();

    if( str.size() && strDelim.size() )
    {
        std::string::size_type pos = 0;
        std::string::size_type posStart = 0;
        while( pos != string::npos )
        {
            pos = str.find( strDelim, posStart );
            std::string::const_pointer pStart = str.c_str() + posStart;
            if( pos == string::npos )
            {
                vectValues.push_back( string( pStart ) );
            } else
            {
                vectValues.push_back( string( pStart, pos - posStart ) );
                posStart = pos + strDelim.size();
            }
        }
    }
}
