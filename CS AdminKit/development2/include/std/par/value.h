/*KLCSAK_PUBLIC_HEADER*/
/*KLCSAK_PUBLIC_HEADER*/

#ifndef KLPRM_VALUE_H
#define KLPRM_VALUE_H

#include <std/base/klbase.h>
#include <std/err/error.h>
#include <avp/avp_data.h>
#include <std/time/kltime.h>

namespace KLPAR {

    class StringValue;
    class BoolValue;
    class IntValue;
    class LongValue;
    class DateTimeValue;
    class DateValue;
    class BinaryValue;
    class FloatValue;
    class DoubleValue;
    class ParamsValue;
    class ArrayValue;
    class Params;


   /*!
    * \brief ��������� ��� �������� �������� ������ Value.
    *
    */ 
    class KLSTD_NOVTABLE ValuesFactory: public KLSTD::KLBase{
	public:
        /*!
        \brief ������� � heap ����� ������ ������ StringValue 
                � ���������� ��������� �� ����.

        \return ��������� �� ����� ��������� ������.

        */
        virtual void CreateStringValue(StringValue** ppVal) = 0;
        virtual void CreateBoolValue(BoolValue** ppVal)  = 0;
        virtual void CreateIntValue(IntValue** ppVal)  = 0;
        virtual void CreateLongValue(LongValue** ppVal)  = 0;
        virtual void CreateDateTimeValue(DateTimeValue** ppVal)  = 0;
        virtual void CreateDateValue(DateValue** ppVal)  = 0;
        virtual void CreateBinaryValue(BinaryValue** ppVal)  = 0;
        virtual void CreateFloatValue(FloatValue** ppVal)  = 0;
        virtual void CreateDoubleValue(DoubleValue** ppVal) = 0;
        virtual void CreateParamsValue(ParamsValue** ppVal)  = 0;
        virtual void CreateArrayValue(ArrayValue** ppVal)  = 0;
    };

    typedef KLSTD::CAutoPtr<KLPAR::ValuesFactory> ValuesFactoryPtr;


    /*!
    * \brief ������� ��������� ��� ��������, ����������� � ���������� Params.
    *  
    */ 

    class KLSTD_NOVTABLE Value: public KLSTD::KLBase{
	public:
        //! ������ ����� ��������, ����������� � Params. ����������� ����
        //  ��������� � ������, ������������� � XML Schema.
        enum Types {
            EMPTY_T,  /*!< ������ �������� (�������� �� ���������� */
            STRING_T, /*!< wchar_t ������ */  
            BOOL_T,   /*!< boolean �������� */
            INT_T,    /*!< 32-bit integer */
            LONG_T,   /*!< 64-bit integer */
            DATE_TIME_T,  /*!< time_t */
            DATE_T,   /*!< ������ � ������� ��YY-MM-DD */
            BINARY_T, /*!< �������� ������������������ */
            FLOAT_T,  /*!< 32-bit IEEE float */
            DOUBLE_T, /*!< 64-bit IEEE float */
            PARAMS_T, /*!< ��������� ��������� Params */
            ARRAY_T   /*!< ��������� ��������� Array */
        };

 
   /*!
      \brief ���������� ��� ��������.

      \return ��� ��������.

    */

      virtual Types	GetType() const = 0;
	  virtual void	Clone(Value** ppValue) const =0;

   /*!
      \brief ���������� ������ Value � pValue

      \return ��� ��������:
			< 0 ������ Value ������ pValue
			= 0 ������ Value ����� pValue
			> 0 ������ Value ������ pValue

    */
	  virtual int Compare(const Value* pValue) const =0;
	protected:
    };

    typedef KLSTD::CAutoPtr<Value>  ValuePtr;

   /*!
    * \brief �������� ���� STRING_T, ����������� � ���������� Params.
    *  
    */ 
    class KLSTD_NOVTABLE StringValue : public Value {
    public:

        /*!
            \brief ������������� ��������. ������ ���������� �� ���������� �����.
            � ����������� ������ ����� �������������.

            \param value [in] ������ �� ��������� ��� StringValue 

        */
        virtual void SetValue( const wchar_t * value ) = 0;

        /*!
            \brief ������������� �������� �� ������. 
            
            ������ �� ���������� �� ���������� �����, ������ ����� ������������
            ���������� ���������.  ����� ����� ����������� ��������� ������ ����
            ������, ��� ����� ����� StringValue.  � ����������� ������ �������
            �������� � ���������� ���������� �� ����������.

            \param value [in] ������ �� ��������� ��� StringValue 

        */
        virtual void SetValueRef( const wchar_t * value ) = 0;

        /*!
            \brief ���������� ��������� �� ������, ���������� � SetValue ���
                    SetValueRef.

            \return ��������, ����������� � StringValue

        */
        virtual const wchar_t * GetValue() const = 0;
    };
    
    typedef KLSTD::CAutoPtr<KLPAR::StringValue> StringValuePtr;


   /*!
    * \brief �������� ���� BOOL_T, ����������� � ���������� Params.
    *  
    */ 
    class KLSTD_NOVTABLE BoolValue : public Value {
    public:
        virtual void SetValue( bool value ) = 0;
        virtual bool GetValue() const = 0;
    };

    typedef KLSTD::CAutoPtr<KLPAR::BoolValue> BoolValuePtr;

   /*!
    * \brief �������� ���� INT_T, ����������� � ���������� Params.
    *  
    */ 
    class KLSTD_NOVTABLE IntValue : public Value {
    public:
        virtual void SetValue( long value ) = 0;
        virtual long GetValue() const = 0;
    };

    typedef KLSTD::CAutoPtr<KLPAR::IntValue> IntValuePtr;


   /*!
    * \brief �������� ���� LONG_T, ����������� � ���������� Params.
    *  
    */ 
    class KLSTD_NOVTABLE LongValue : public Value {
    public:
        virtual void SetValue( AVP_longlong value ) = 0;
        virtual AVP_longlong GetValue() const = 0;
    };

    typedef KLSTD::CAutoPtr<KLPAR::LongValue> LongValuePtr;

   /*!
    * \brief �������� ���� DATETIME_T, ����������� � ���������� Params.
    *  
    */ 
    class KLSTD_NOVTABLE DateTimeValue : public Value {
    public:
        virtual void SetValue( KLSTD::klstd_old_time_t value ) = 0;
        virtual KLSTD::klstd_old_time_t GetValue() const = 0;
    };

    typedef KLSTD::CAutoPtr<KLPAR::DateTimeValue> DateTimeValuePtr;


   /*!
    * \brief �������� ���� DATE_T, ����������� � ���������� Params.
    *  
    */ 
    class KLSTD_NOVTABLE DateValue : public Value {
    public:
        virtual void SetValue( const char * value ) = 0;
        virtual const char * GetValue() const = 0;
    };

    typedef KLSTD::CAutoPtr<KLPAR::DateValue> DateValuePtr;

    /*!
		\brief Callback - ������� ��� ������������ ������, ���������� � BinaryValue

		\param buff [in]  ����� ������ ��� ������������.
		\param context [in] ��������, ��������� � ���� �������.
	*/
    typedef void (*FreeBufferCallback)(void * buff, void * context );


   /*!
    * \brief �������� ���� BINARY_T, ����������� � ���������� Params.
    *  
    */ 
    class KLSTD_NOVTABLE BinaryValue : public Value {
    public:

        /*!
            \brief ������������� �������� ��� BinaryValue.
            
            ������������ ��������� ������ ���� ���������� ��� ����� ����� BinaryValue.
            ����� ������ ����� ������ ��������������� �� ���������� ����������
            ������� ����� �� BinaryValue.  ����� ������������� � �����������
            BinaryValue ����� ������ ������ free ���� � ������ 
            ������ ������������ ������ SetValue.

            \param value [in]  ����� ��� ������������� � BinaryValue.
            \param bytes [in]  ������ ������ � ������.

        */
        virtual void SetValue( void * value, size_t bytes ) = 0;

        /*!
            \brief ������������� �������� ��� BinaryValue.
            
            ������������ ��������� ������ ���� ���������� ��� ����� ����� BinaryValue.
            ����� ������ ����� ������ ��������������� �� ���������� ����������
            ������� ����� �� BinaryValue.  ����� ������������� � �����������
            BinaryValue ����� ������ ���������� callback - ������� � ����������,
            ���������� ��� ������� ������ ���� � ������ ������ ������������ 
            ������ SetValue.

            \param value [in]  ����� ��� ������������� � BinaryValue.
            \param bytes [in]  ������ ������ � ������.
            \param callback [in]  Callback - ������� ��� ������������ ���������� ������.
            \param context [in] �������� ��� ������ Callback - �������.

        */
        virtual void SetValue( void * value, 
                               size_t bytes,
                               FreeBufferCallback callback,
                               void * context ) = 0;

        /*!
            \brief ���������� ��������� �� ����� BinaryValue.  � ������, ����
            ����� �� ����������, ���������� 0.
        */

        virtual void * GetValue() const = 0;

        /*!
            \brief ���������� ������ ������ BinaryValue � ������.  � ������, ����
            ����� �� ����������, ���������� 0.
        */

        virtual size_t GetSize() const = 0;
    };

    typedef KLSTD::CAutoPtr<KLPAR::BinaryValue> BinaryValuePtr;

   /*!
    * \brief �������� ���� FLOAT_T, ����������� � ���������� Params.
    *  
    */ 
    class KLSTD_NOVTABLE FloatValue : public Value {
    public:
        virtual void SetValue( float value ) = 0;
        virtual float GetValue() const = 0;
    };

    typedef KLSTD::CAutoPtr<KLPAR::FloatValue> FloatValuePtr;


   /*!
    * \brief �������� ���� DOUBLE_T, ����������� � ���������� Params.
    *  
    */ 
    class KLSTD_NOVTABLE DoubleValue : public Value {
    public:
        virtual void SetValue( double value ) = 0;
        virtual double GetValue() const = 0;
    };

    typedef KLSTD::CAutoPtr<KLPAR::DoubleValue> DoubleValuePtr;


   /*!
    * \brief �������� ���� PARAMS_T, ����������� � ���������� Params.
    *  
    */ 
    class KLSTD_NOVTABLE ParamsValue : public Value {
    public:

        /*!
            \brief ������������� �������� ��� ParamsValue.
            
            ������������ ��������� ������ ���� ���������� ��� ����� ����� ParamsValue.
            ����� ������ ����� ������ ��������������� �� ���������� ����������
            �������� Params ����� �� ParamsValue.  ���������� ������ Params
            ������������� � ����������� ParamsValue ����� ������ ��������� delete
            ���� � ������ ������ ������������ ������ SetValue.

            \param value [in]  ����� ��� ������������� � BinaryValue.
            \param bytes [in]  ������ ������ � ������.

        */
        virtual void SetValue( Params * value ) = 0;


        /*!
            \brief ���������� ��������� �� ����������� ������ Params.  � ������, ����
            ������ Params �� ����������, ���������� 0.
        */

        virtual Params * GetValue() const = 0;
    };

    typedef KLSTD::CAutoPtr<KLPAR::ParamsValue> ParamsValuePtr;


   /*!
    * \brief �������� ���� ARRAY_T, ����������� � ���������� Params.
    *  
    */ 
    class KLSTD_NOVTABLE ArrayValue : public Value {
    public:

        /*!
            \brief ��������� ���������� ������ �������
        */
		virtual void SetSize(size_t size)=0;

        /*!
            \brief ��������� �������� ������ �������
        */
		virtual size_t GetSize() const =0;

        /*!
            \brief ��������� �������� nIndex-� ������� �������.
        */
		virtual void SetAt(size_t nIndex, Value* value)=0;

        /*!
            \brief ��������� ������� nIndex-� ������� �������.
        */
        virtual void GetAt(size_t nIndex, Value** value) = 0;
		virtual const Value* GetAt(size_t nIndex) const = 0;
    };

    typedef KLSTD::CAutoPtr<KLPAR::ArrayValue> ArrayValuePtr;
}

/*!
   \brief �������� ������� �������� Value. 
        ������� � heap ����� ������ ������ ValuesFactory � ���������� ��������� �� ����.

   \return ��������� �� ����� ��������� ������.

*/

KLCSC_DECL void KLPAR_CreateValuesFactory(KLPAR::ValuesFactory**);


#endif // KLPRM_VALUE_H
