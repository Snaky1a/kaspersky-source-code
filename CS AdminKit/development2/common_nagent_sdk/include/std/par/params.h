/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file Params.h
 * \author ������ ��������
 * \date 2002
 * \brief ������� ��������� ������ Params.
 *
 */

#ifndef KLPRM_PARAMS_H
#define KLPRM_PARAMS_H


#include <std/err/error.h>
#include <std/base/klbase.h>
#include "./errors.h"
#include "./value.h"

/*!
	\brief �������� ���� ����������. 
		\param _ptr ��������� ��������� �� Value ��� �� ���������� Value
		\param _type ������� ������������ KLPAR::Value::Types (��������, INT_T)
		\param _name ��������� const wchar_t* �� ��� ����������
*/

#define KLPAR_CHKTYPE(_ptr, _type, _name)											\
	if((_ptr)->GetType()!=KLPAR::Value::_type)										\
		KLERR_THROW1(L"KLPAR", KLPAR::WRONG_VALUE_TYPE, (const wchar_t*)(_name));

#define KLPAR_CHKTYPE2(_ptr, _type, _name)											\
	if((_ptr)->GetType()!=_type)										\
		KLERR_THROW1(L"KLPAR", KLPAR::WRONG_VALUE_TYPE, (const wchar_t*)(_name));


namespace KLPAR {

    /*!
    * \brief ��������� ���������� Params (�� thread-safe !!!!!).
    *  
    *  ��������� Params ������������ ��� ������������� ������ � ������� ���� �������
    *  CS Admin Kit.  ��������� ������������ ����� ����� ��� ��� - ��������.  
    *  ��� ������������ ����� wchar_t ������, �������� ����� ���� ���� �������, ����
    *  ������� �����.  ������ �������������� ����� ��������� � ������������ Value::Types.
    *  ������� ��� ����� ���� ���� � ���� ������� ����������� Params, ���� ��������
    *  ��������.
    *
    */
    
    
    typedef KLSTD::AKWSTRARR names_t;

    class Params: public KLSTD::KLBaseQI
    {
    public:        
		/*!
		  \brief	����� ���������� �������� �� ������ ����������� � ��������.
					�.�. ��� ������� �������� Value* � �������� �������� �����.
					���������� ��������� � �� ��� ���������� ����������
					��������� ����������� �� ��������� ����������.
		  \param	ppParams [out] ��������� �� ����������, � ������� �����
					������� ��������� �� ��������� ��������� Params
		*/
		virtual void Clone(Params** ppParams) const =0;

		/*!
		  \brief	����� ���������� �������� �� ������ ����������� � ��������.
					� ������� �� ������ Clone, ����� Duplicate ������������
					����������� ������ ��� ���������� ���� ParamsValue, ���
					���������� ������ ����� ������������ ���� �����������
					������.
		  \param	ppParams [out] ��������� �� ����������, � ������� �����
					������� ��������� �� ��������� ��������� Params
		*/
		virtual void Duplicate(Params** ppParams) = 0;
   /*!
      \brief ���������� ������ Params � pParams

      \return ��� ��������:
			< 0 ������ Params ������ pParams
			= 0 ������ Params ����� pParams
			> 0 ������ Params ������ pParams

    */
	  virtual int Compare(const Params* pParams) const =0;

    /*!
      \brief ��������� ����� �������� � ����������.

      \param name [in] ��� ������������ ���������.
      \param value [in] �������� ������������ ���������.
	  \param bReplace [in] ���� �������� � ������ name ��� ����������, �� ��������� ������ ALREADY_EXIST.
    */

        virtual void AddValue(const wchar_t* name, Value * value) = 0;        

    /*!
      \brief ��������� ����� �������� � ����������, ���� ��� �� ����������,
			�������� �������� ��������, ���� �� ��� ����������.

      \param name [in] ��� ������������ ���������.
      \param value [in] �������� ������������ ���������.
    */
        virtual void ReplaceValue(const wchar_t* name, Value * value) = 0;


    /*!
      \brief ������� �������� �� ����������.

      \param name [in] ��� ���������� ���������.
	  \param bThrow [in] ���������, ����� �� ����������� ���������� NOT_EXIST ��� ���������� ���������
			��� ���������� false.

    */

        virtual bool DeleteValue(const wchar_t* name, int bThrow = false) = 0;


    /*!
      \brief ������������� ����� �������� ��� ���������, ������������� � ����������.

      \param name [in] ��� ����������� ���������.
      \param value [in] ����� �������� ���������.

	    ���� �������� � ������ name �� ������, �� ������������� ���������� NOT_EXIST.

    */
        virtual void SetValue(const wchar_t* name, Value * value) = 0;

    /*!
      \brief ���������� ��������� �� ����������� � ���������� ��������.

      \param name [in] ��� ��������� ��� ��������� ��������.
	  \param ppValue [out] ��������� �� ������ Value, ����������� � ����������
    */
		virtual void GetValue(const wchar_t* name, Value** ppValue) = 0;

    /*!
      \brief ���������� ��������� �� ����������� � ���������� ��������.


      \param name [in] ��� ��������� ��� ��������� ��������.
	  \param ppValue [out] ��������� �� ������ Value, ����������� � ����������
	  ���� �������� � ������ name �� ������, �� ������������ false, ����� true.

    */
		virtual bool GetValueNoThrow(const wchar_t* name, Value** ppValue) = 0;

    /*!
      \brief ���������� ����� ���� ����������� � ���������� ��������.
	  \param names [out] ������ ���� ����������� � ���������� ���� ����������.

    */
        virtual void GetNames(names_t &names) const  = 0;        

    /*!
      \brief ��������� ������� ��� ���������� ���������� Params.

 
    */
        virtual void Clear() = 0;

	/*!
	  \brief	��������� ������� ���������

	  \param	name [in] ��� ���������
	  \return	���� �������� ����������, ���������� true, ����� -- false
	*/
        virtual bool DoesExist(const wchar_t* name) const= 0;

    /*!
      \brief �������� ���������� ���������� pSrc � ������ ���������.
		��� ���� ������������ ���������� ������� ���������� ���������� 
		����������� ���������� pSrc.
     */
		virtual void CopyFrom(const Params* pSrc) = 0;

    /*!
      \brief ���������� ���������� ���������� pSrc � ������ ���������.
		��� ���� ������������ ���������� ������� ���������� ���������� 
		����������� ���������� pSrc.
     */
		virtual void MoveFrom(Params* pSrc) = 0;

    /*!
      \brief	Returns number of items 

      \return	number of items 
    */
        virtual size_t GetSize() const = 0;

    /*!
      \brief	Makes container and all its subcontainers read-only
    */
        virtual void MakeReadOnly() = 0;

    };
    
    typedef KLSTD::CAutoPtr<Params>  ParamsPtr;
}

#ifndef _HELPERS_H_11102C22_1458_4de9_8DD4_7A08981B188A
# include "../par/helpers.h"
#endif

/*!
   \brief ����� ��� �������� ���������� Params. 
        ������� � heap ����� ������ ������ Params � ���������� ��������� �� ����.

   \return ��������� �� ����� ��������� ������.

*/
KLCSC_DECL void KLPAR_CreateParams(KLPAR::Params** ppParams) ;

#endif // KLPRM_PARAMS_H

// Local Variables:
// mode: C++
// End:
