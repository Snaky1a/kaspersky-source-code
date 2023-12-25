/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file Sync.h
 * \author ������ ��������, ����� �����������
 * \date 2002
 * \brief ������� �������������.
 *
 */

#ifndef KL_SYNC_H_6A0778F4_B132_45c7_AFEB_AC689542E38D
#define KL_SYNC_H_6A0778F4_B132_45c7_AFEB_AC689542E38D

#include "std/base/klbase.h"

namespace KLSTD{

#define KLSTD_INFINITE (-1L)

	/*!
		\brief Critical section

	*/
	class KLSTD_NOVTABLE CriticalSection: public KLBase
    {
	public:
		virtual unsigned long AddRef()=0;
		virtual unsigned long Release()=0;
		virtual void Enter()=0;
		virtual void Leave()=0;
	};	

	/*!
		\brief ����� ��� �������������� ������ �� ����������� ������

	*/
	template<class T>
		class AutoCriticalSectionT{
	public:
		AutoCriticalSectionT(CriticalSection* pCritSec){
			m_pCritSec=pCritSec;
			if(m_pCritSec)
				m_pCritSec->Enter();
		};
		~AutoCriticalSectionT(){
			if(m_pCritSec)
				m_pCritSec->Leave();
		};
	private:
		T m_pCritSec;
	};

	typedef AutoCriticalSectionT< CAutoPtr<CriticalSection> > AutoCriticalSection;
	typedef AutoCriticalSectionT< CriticalSection* > AutoCriticalSectionST;


	/*!
		\brief ����� ������� ������������� �������.
	*/

	class KLSTD_NOVTABLE Semaphore : public KLBase
    {
	public:
		/*!
            \brief ��������� �������� ��������.

            \param msec [in] ����� �������� � ������������. ��� ������������ �������� ������� <0.
            \return true  - �������� �������� ���� ������� ���������
					false - ������� ����� ��������

        */
		virtual bool Wait( int msec = (-1) )=0;
		/*!
			\brief ����������� �������� ��������.
		*/
		virtual void Post()=0;
	};	

} // namespace KLSTD

KLCSC_DECL bool KLSTD_CreateCriticalSection(KLSTD::CriticalSection** pCritSec);



//!\brief ������� ���������� ������� ���� �������
KLCSC_DECL bool KLSTD_CreateSemaphore( KLSTD::Semaphore** pCritSec, int initValue );

/*!
	\brief �������������� ��������� ���������� ���� long.
	������ ������� �� ������ ���������� �� ������ main.
*/
KLCSC_DECL long KLSTD_FASTCALL KLSTD_InterlockedIncrement(long volatile* x);

/*!
	\brief �������������� ��������� ���������� ���� long.
	������ ������� �� ������ ���������� �� ������ main.
*/
KLCSC_DECL long KLSTD_FASTCALL KLSTD_InterlockedDecrement(long volatile* x);


/*!
  \brief	Sleeps for lTimeout mlliseconds

  \param	lTimeout time to sleep, ms
*/
KLSTD_NOTHROW KLCSC_DECL void KLSTD_Sleep(long lTimeout) throw();


#endif //KL_SYNC_H_6A0778F4_B132_45c7_AFEB_AC689542E38D

// Local Variables:
// mode: C++
// End:
