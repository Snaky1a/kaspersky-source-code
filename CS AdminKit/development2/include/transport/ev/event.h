/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file Event.h
 * \author ����� �����������
 * \date 2002
 * \brief ��������� ������ �������, ������� �������� �������� �������������� �������� 
 *			���������� Eventing
 * 
 */


#ifndef KLEV_EVENT_H
#define KLEV_EVENT_H

#include <string>

#include "std/base/klbase.h"
#include "std/par/params.h"

#include "kca/prci/componentid.h"

#include "transport/ev/common.h"

namespace KLEV {

	class Event : public KLSTD::KLBase
	{
		public:

			virtual ~Event() {}

			/*!
				\brief ������� ������������� �������.
		
				\param publisher [in] ������������ ����������� 
				\param type [in] ��� �������
				\param body [in] ��������� �������
				\param birthTime [in] ����� �������������� ������� 
							( ���� ����� 0 �� � ������� ����� ������������ ������� ����� )
				\param lifeTime [in] ����� ����� ������� � ��������
			*/
			virtual void Init( const KLPRCI::ComponentId &publisher, const std::wstring &type, 
				KLPAR::Params *body, const time_t birthTime = 0, 
				const int lifeTime = 0 ) = 0;

			/*!
				\brief ���������� ��� ����������� �������
			*/
			virtual const KLPRCI::ComponentId &GetPublisher( ) const = 0;

			/*!
				\brief ������������� ��� ����������� �������

				\param newPublisher [out] ����� ��� ����������� 
			*/
			virtual void SetPublisher( const KLPRCI::ComponentId &newPublisher ) = 0;

			/*!
				\brief ���������� ��� �������
			*/
			virtual const std::wstring &GetType() const = 0;

			/*!
				\brief ������������� ��� �������

				\param eventType [in] ����� ��� �������
			*/
			virtual void SetType( const std::wstring &eventType ) = 0;

			/*!
				\brief ���������� ��������� �������

					������� ���������� ������� ��������� �� ���������� Params ������.
					������������ ������ �������� Params ���������� �� ������. ��� �����������
					��������� AddRef �� ����������.
			*/
			virtual KLPAR::Params *GetParams() const = 0;

			/*!
				\brief ������������� ��������� �������

				\param eventParams [in] ����� ��������� �������
			*/
			virtual void SetParams( KLPAR::Params *eventParams ) = 0;

			/*!
				\brief ���������� ����� ������������� �������
			*/
			virtual time_t GetBirthTime() const = 0;

			/*!
				\brief ������������� ����� ������������� �������

				\param eventBirthTime [in] ����� ����� ������������� �������
			*/
			virtual void SetBirthTime( const time_t eventBirthTime ) = 0;

			/*!
				\brief ���������� ����� ����� ������� � ��������				
			*/
			virtual int GetLifeTime() const = 0;

			/*!
				\brief ������������� ����� ����� ������� � ��������

				\param eventLifeTime [in] ����� ����� ����� �������
			*/
			virtual void SetLifeTime( const int eventLifeTime ) = 0;
	};

} // namespace KLEV

/*!
   \brief ����� ��� �������� ������� Event. 
        �������� Event � �������������� ��� ����������� �����������.

   \return ��������� �� ����� ��������� ������.
*/
KLCSTR_DECL void KLEV_CreateEvent( KLEV::Event **ppEvent, const KLPRCI::ComponentId &publisher, 
				const std::wstring &type, KLPAR::Params *body, 
				const time_t birthTime = 0, int lifeTime = 0 );

#endif // KLEV_EVENT_H

// Local Variables:
// mode: C++
// End:
