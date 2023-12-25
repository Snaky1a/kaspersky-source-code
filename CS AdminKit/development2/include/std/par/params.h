/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file Params.h
 * \author ������ ��������
 * \date 2002
 * \brief ������� ��������� ������ Params.
 *
 */
/*KLCSAK_PUBLIC_HEADER*/

#ifndef KLPRM_PARAMS_H
#define KLPRM_PARAMS_H

/*KLCSAK_BEGIN_PRIVATE*/
#include <string>
#include <vector>
/*KLCSAK_END_PRIVATE*/

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
    
/*KLCSAK_BEGIN_PRIVATE*/
    //!obsolete
    typedef std::vector< std::wstring > ParamsNames;
    //!obsolete
    KLCSC_DECL void _GetParamsNames(const KLPAR::Params* p, ParamsNames& names);
/*KLCSAK_END_PRIVATE*/
    
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

/*KLCSAK_BEGIN_PRIVATE*/
    //! inlines
         void AddValue(const std::wstring& name, Value * value)
        {
            this->AddValue(name.c_str(), value);
        };

         void ReplaceValue(const std::wstring& name, Value * value)
        {
            this->ReplaceValue(name.c_str(), value);
        };

         bool DeleteValue(const std::wstring& name, int bThrow = false)
        {
            return this->DeleteValue(name.c_str(), bThrow);
        };

         void SetValue(const std::wstring& name, Value * value)
        {
            this->SetValue(name.c_str(), value);
        };

         void GetValue(const std::wstring& name, Value** ppValue)
        {
            this->GetValue(name.c_str(), ppValue);
        };

         bool GetValueNoThrow(const std::wstring& name, Value** ppValue)
        {
            return this->GetValueNoThrow(name.c_str(), ppValue);
        };

         bool DoesExist(const std::wstring& name) const
        {
            return this->DoesExist(name.c_str());
        };

         void GetNames(ParamsNames &names) const
         {
             _GetParamsNames(this, names);
         };

//! DEPRECATED !!!! DO NOT USE !!!
		const Value* GetValue2(const std::wstring& name, bool bThrow) const
        {
            KLSTD::CAutoPtr<Value> pValue;
            if(bThrow)
                const_cast<KLPAR::Params*>(this)->GetValue(name.c_str(), &pValue);
            else
                const_cast<KLPAR::Params*>(this)->GetValueNoThrow(name.c_str(), &pValue);
            return pValue;
        };

		const Value* GetValue(const std::wstring& name, int bThrow) const
        {
            return GetValue2(name, bThrow?true:false);
        };

		Value* GetValue2(const std::wstring& name, bool bThrow)
        {
            KLSTD::CAutoPtr<Value> pValue;
            if(bThrow)
                this->GetValue(name.c_str(), &pValue);
            else
                this->GetValueNoThrow(name.c_str(), &pValue);
            return pValue;
        };
/*KLCSAK_END_PRIVATE*/
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
