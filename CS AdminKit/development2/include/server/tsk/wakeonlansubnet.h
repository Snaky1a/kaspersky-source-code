/*!
* (C) 2005 "Kaspersky Lab"
*
* \file wakeonlansubnet.h
* \author ����������� �����
* \date 2007
* \brief ��������� ������ �������������� �������� WakeOnLan ������� �� ����� ����������� � �������� �������� 
	�� ����������
*
*/

#ifndef KLTSK_WAKEONLANSUBNET_H
#define KLTSK_WAKEONLANSUBNET_H

#include <std/base/klbase.h>
#include <std/err/klerrors.h>

#include <server/srv_common.h>

namespace KLTSK {

	/*!
		\brief 

		��� ��������� ������ ���������� ��������� ����� ��������:

		1. �������� �� ������ �������� � ������, ������ ������, ������� ������������� � ������ � �������� ��������
		2. �������� ��������� ������ �� ��������� �������� �� �������� ������� ���������� �����������
		3. �������� �� ��������� ����� �� �������� ������� � ������������� �������� WakeOnLan �������		
	
	*/	

	class WakeOnLanSubnet : public KLSTD::KLBase {
	public:

		/*!
			\brief ������������� ���������� ��� ������ � �������� �������
		*/
		virtual void Init( KLSRV::SrvData* pSrvData ) = 0;

		/*!
			\brief �������� ������ ������ �� ������ �������� 
		*/
		virtual void SendSignalForTask( long nTaskId, long timeout ) = 0;

		/*!
			\brief ������������� ������ ����������
		*/
		virtual void Shutdown() = 0;		

	};

	

} // end namespace KLTSK

void KLTSK_CreateWakeOnLanSubnet( KLTSK::WakeOnLanSubnet **ppWolSubnet );

#endif // KLTSK_WAKEONLANSUBNET_H