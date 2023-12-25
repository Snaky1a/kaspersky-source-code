/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file PRCI/ComponentId.h
 * \author ������ ��������
 * \date 2002
 * \brief ������������� ���������� �������� � ������� �����������������.
 *
 */

#ifndef KLPRCI_COMPONENTID_H
#define KLPRCI_COMPONENTID_H

#include <string>

#include <std/base/kldefs.h>

// #define KLPRCI_WELLKNOWN_AGENT	KLPRSS_PRODUCT_NAME L"-" KLPRSS_COMPONENT_AGENT


// By Damir 04/11/23 #define KLPRCI_WELLKNOWN_SERVER	KLCS_WELLKNOWN_SERVER

namespace KLPRCI {

    /*!
    * \brief ������������� ���������� �������� � ������� �����������������.
    *  
    * ������ ��������� ������������ � ������� ����������������� ��� ������������
    * � ��������� ����������� ��������.  � ������, ���� ���� �� ����� ���������
    * �� ������ (������������ ����� ������ ������), �� � ������ ������������� �
    * �������� ��������� �� ���������� �� �� ��������� ���� �� ������������. ���
    * ���������, ��������, ����������� �� ��� ������� �� ���� ����������� ��������
    * (�� ������ ��� ����������).
    *
    */

    
struct ComponentId
{

    ComponentId()
      { }

    ComponentId( const std::wstring& productName_, 
                 const std::wstring& version_,
                 const std::wstring& componentName_,
                 const std::wstring& instanceId_) :
        productName(productName_),
        version(version_),
        componentName(componentName_),
        instanceId(instanceId_)
      { }

    ComponentId( const ComponentId& x ) :
        productName(x.productName),
        version(x.version),
        componentName(x.componentName),
        instanceId(x.instanceId)
      { }

    int Compare( const ComponentId& x ) const
      {
      // return wcscmp(instanceId.c_str(), x.instanceId.c_str());
        return instanceId == x.instanceId ? 0 : (instanceId > x.instanceId ? 1 : -1);
      }
    bool operator == (const ComponentId& x) const
      { return instanceId == x.instanceId; }
    bool operator < (const ComponentId& x)const
      { return instanceId < x.instanceId; }
    bool operator > (const ComponentId& x)const
      { return instanceId > x.instanceId; }

	KLCSKCA_DECL std::wstring PutToString() const;
	KLCSKCA_DECL void GetFromString(const std::wstring& s);
	
    std::wstring productName; ///< ��� ��������. 
    std::wstring version; ///< ������ ��������.
    std::wstring componentName; ///< ��� ���������� (��������� ������ ��������).
    std::wstring instanceId; ///< ������������� ���������� ����� ����������.
};

} // namespace KLPRCI

#endif // KLPRCI_COMPONENTID_H

// Local Variables:
// mode: C++
// End:
