/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file Error.h
 * \author andkaz
 * \date 2002
 * \brief ����������� ����� ��� �������� ������, ������������ � ����� �� �������.
 *
 */

#ifndef KL_ERROR_H
#define KL_ERROR_H

#include <cwchar>

#ifdef __unix__
 #include <stdarg.h>
#endif

#include <std/err/errintervals.h>
#include <std/base/klbase.h>



#include <std/err/error_localized.h> 

/*!
	\brief	���� ���������� ������� KLERR_THROWx ��� ������������ ����������
			� x �����������.
		\params _module [in] ��� ������, �� ����� �������� ����� ��������� ����������
		\params _code [in] ��� ����������
		\params _parami [in] �������� ����������.
*/

#define KLERR_THROW0(_module, _code)	\
	KLERR_throwError(_module, _code, __FILE__, __LINE__, NULL, NULL)

#define KLERR_THROW1(_module, _code, _param1)	\
	KLERR_throwError(_module, _code, __FILE__, __LINE__, NULL, _param1)

#define KLERR_THROW2(_module, _code, _param1, _param2)	\
	KLERR_throwError(_module, _code, __FILE__, __LINE__, NULL, _param1, _param2)

#define KLERR_THROW3(_module, _code, _param1, _param2, _param3)	\
	KLERR_throwError(_module, _code, __FILE__, __LINE__, NULL, _param1, _param2, _param3)

#define KLERR_THROW4(_module, _code, _param1, _param2, _param3, _param4)	\
	KLERR_throwError(_module, _code, __FILE__, __LINE__, NULL, _param1, _param2, _param3, _param4)

/*!
	\brief	���� ���������� ������� KLERR_MYTHROWx ��� ������������ ����������
			������ ������ � x �����������. ��� �� ������������� ����������,
			����� � ������������ �� cpp-����� ��� �������� ������ KLCS_MODULENAME
			������:
				#define KLCS_MODULENAME L"KLSTD"
*/

/*!
	\brief	������� KLERR_THROWx ��� ������������ ����������
			� x �����������.
		\params _code [in] ��� ����������
		\params _parami [in] �������� ����������.
*/
#define KLERR_MYTHROW0(_code)	\
	KLERR_throwError(KLCS_MODULENAME, _code, __FILE__, __LINE__, NULL, NULL)

#define KLERR_MYTHROW1(_code, _param1)	\
	KLERR_throwError(KLCS_MODULENAME, _code, __FILE__, __LINE__, NULL, _param1)

#define KLERR_MYTHROW2(_code, _param1, _param2)	\
	KLERR_throwError(KLCS_MODULENAME, _code, __FILE__, __LINE__, NULL, _param1, _param2)

#define KLERR_MYTHROW3(_code, _param1, _param2, _param3)	\
	KLERR_throwError(KLCS_MODULENAME, _code, __FILE__, __LINE__, NULL, _param1, _param2, _param3)

#define KLERR_MYTHROW4(_code, _param1, _param2, _param3, _param4)	\
	KLERR_throwError(KLCS_MODULENAME, _code, __FILE__, __LINE__, NULL, _param1, _param2, _param3, _param4)

/*! /brief	���������� ���������� STDE_SYSTEM c ����� _code
*/
#define KLSTD_THROW_SYSTEM(_code)		KLERR_THROW2(L"KLSTD", KLSTD::STDE_SYSTEM, _code, L"?")

/*! /brief	���������� ���������� STDE_SYSTEM c ����� _code � ���������
*/
#define KLSTD_THROW_SYSTEM_MSG(_code, _msg)		KLERR_THROW2(L"KLSTD", KLSTD::STDE_SYSTEM, _code, _msg)
	
/*! /brief	���������� ���������� STDE_BADPARAM
*/
#define KLSTD_THROW_BADPARAM(_param)	KLERR_THROW1(L"KLSTD", KLSTD::STDE_BADPARAM, #_param)

/*! /brief	���� ��������� ����� NULL, �� STDE_NOMEMORY
*/
#define KLSTD_CHKMEM(_ptr)				(!(_ptr))?(KLSTD_THROW(KLSTD::STDE_NOMEMORY),NULL):1

/*! /brief	����������� ���������� STDE_NOFUNC
*/
#define KLSTD_NOTIMP()						KLSTD_THROW(KLSTD::STDE_NOFUNC)

/*! /brief	����������� ���������� STDE_NOINIT
*/
#define KLSTD_NOINIT(_name)						KLERR_THROW1(L"KLSTD", KLSTD::STDE_NOINIT, (const wchar_t*)_name)

/*! /brief	����������� ���������� STDE_SIGNFAIL
*/
#define KLSTD_SIGNFAIL(_file)   KLERR_THROW1(L"KLSTD", KLSTD::STDE_SIGNFAIL, (const wchar_t*)_file)

/*! /brief	������������� ���������� STDE_ODBC
*/
#define KLSTD_THROW_ODBC(_state, _msg)		KLERR_THROW2(L"KLSTD", KLSTD::STDE_ODBC, (const wchar_t*)_state, (const wchar_t*)_msg)


/*! /brief	���������� ���� ���������� STDE_*
*/
#define KLSTD_THROW(_code)					KLERR_THROW0(L"KLSTD", _code)

#define KLSTD_THROW1(_code,_param)			KLERR_THROW1(L"KLSTD", _code, _param)
#define KLSTD_THROW2(_code,_param1,_param2)	KLERR_THROW2(L"KLSTD", _code, _param1, _param2 )

#define KLSTD_THROW_ERRNO() KLSTD_ThrowErrnoCode(errno, __FILE__, __LINE__)
#define KLSTD_THROW_ERRNO_CODE(_code) KLSTD_ThrowErrnoCode(_code, __FILE__, __LINE__)

#define KLSTD_CHKOUTPTR(ppPtr) if(!(ppPtr)){KLSTD_THROW_BADPARAM(ppPtr);KLSTD_ASSERT(*(ppPtr) == NULL);}
#define KLSTD_CHKINPTR(pPtr) if(!(pPtr)){KLSTD_ASSERT((pPtr) != NULL); KLSTD_THROW_BADPARAM(pPtr);}
#define KLSTD_CHK(_name, _condition) if(!(_condition)){KLSTD_ASSERT((_condition)); KLSTD_THROW_BADPARAM(_name);};

/*! /brief	���������� ���������� STDE_ASSRT, ���� ������� _condition �� ���������.
*/
#define KLSTD_ASSERT_THROW(_condition)	KLSTD::assertion_check(!(!(_condition)), #_condition, __FILE__, __LINE__)

/*! /brief	��� ������������� ������������ ������ ������ ����� �� ������
			������� KLSTD_Initialize()
*/

KLCSC_DECL void KLSTD_ThrowErrnoCode( int nCode,
                                      const char* szaFile,
                                      int nLine);


KLCSC_DECL void KLSTD_ThrowLastErrorCode( const wchar_t *szwMessage,
                                          long lCode,
                                          bool bThrowAlways,
                                          const char *szaFile,
                                          int nLine,
                                          bool bTryConvert );

KLCSC_DECL void KLSTD_ThrowLastError( const wchar_t *szwMessage,
                                      const char *szaFile,
                                      int nLine,
                                      bool bTryConvert );

#define KLSTD_THROW_LASTERROR_CODE(_code) KLSTD_ThrowLastErrorCode(NULL, _code, true, __FILE__, __LINE__, true)
#define KLSTD_THROW_LASTERROR() KLSTD_ThrowLastError(NULL, __FILE__, __LINE__, true)

#ifdef _WIN32
		
	#define KLSTD_CHKHR(hr) if(FAILED(hr)) KLSTD_ThrowLastErrorCode(NULL, hr, true, __FILE__, __LINE__, true)
	

#endif

	#define KLSTD_THROW_LASTERROR_MSG(_msg)	\
				KLSTD_ThrowLastError(_msg, __FILE__, __LINE__, true)

	#define KLSTD_THROW_LASTERROR_CODEMSG(_code, _msg)	\
				KLSTD_ThrowLastErrorCode(_msg, _code, true, __FILE__, __LINE__, true)

	#define KLSTD_THROW_LASTERROR2() KLSTD_ThrowLastError(NULL, __FILE__, __LINE__, false)
	#define KLSTD_THROW_LASTERROR_CODE2(_code) KLSTD_ThrowLastErrorCode(NULL, _code, true, __FILE__, __LINE__, false)
	
	#define KLSTD_THROW_LASTERROR_MSG2(_msg)	\
				KLSTD_ThrowLastError(_msg, __FILE__, __LINE__, false)

	#define KLSTD_THROW_LASTERROR_CODEMSG2(_code, _msg)	\
				KLSTD_ThrowLastErrorCode(_msg, _code, true, __FILE__, __LINE__, false)



/*!
	\brief	������� KLERR_SAY_FAILURE ����� � ����� �������� ������ � ������� level.
		\params level [in] ������� �����������
		\params pError [in] ��������� �� ��������� Error. ���� NULL, �� ����������
					���������� ��� ��������� � �������� ������.
*/

#define KLERR_SAY_FAILURE(level, pError)		KLERR::SayFailure(level, pError, KLCS_MODULENAME, __FILE__, __LINE__)

/*!
	\brief �������� ����������.
*/

#define KLERR_BEGIN								\
			KLERR_TRY

#define KLERR_END								\
            KLERR_CATCH(pError)                 \
                ;                               \
            KLERR_ENDTRY

#define KLERR_ENDT( _traceLevel )				            \
            KLERR_CATCH(pError)                             \
                KLERR_SAY_FAILURE(_traceLevel, pError);     \
            KLERR_ENDTRY

/*!
	\brief �������� ������������� � C++ ����������� try-catch-finally.
*/

#define KLERR_TRY									\
	{												\
		KLSTD::CAutoPtr<KLERR::Error> pTmpErrorPtr;	\
		try{

#define KLERR_CATCH(_ptr)							\
		}											\
		catch(KLERR::Error* pError){				\
			KLERR_SAY_FAILURE(5, pError);			\
			if(!pError)								\
				KLERR_CreateError(					\
					&pTmpErrorPtr,					\
					L"KLSTD",						\
					KLSTD::STDE_NOMEMORY,			\
					__FILE__,						\
					__LINE__,						\
					NULL);							\
			pTmpErrorPtr.Attach(pError);			\
		};											\
		KLERR::Error* _ptr=pTmpErrorPtr;			\
		if(pTmpErrorPtr){

#define KLERR_FINALLY								\
		};											\
		{

#define KLERR_ENDTRY								\
		};											\
	};

#define KLERR_RETHROW()								\
		KLERR::rethrow_if_possible(pTmpErrorPtr)


#define KLERR_IGNORE(_expr)	KLERR_BEGIN _expr; KLERR_END

namespace KLERR
{
	const wchar_t szwModule[]=L"KLERR";
    /*!
    * \brief �������� ������, ������������ � ����� �� �������.
    *
    *  ����������� ������ ������ ���������� � ����� ������ ����������� ������
    *  � ��������� ������, ������� ����� ��������� � ������. �����
    *  �� ���� ������� ����� �������� ������ Error ����� ������ ������
    *  InitModuleDescriptions.  ����� ����� ������ Error ����� ������������
    *  �������� ������ �� ����� �������, ���� ������ �� ����� �� ����.
    *
    *  � ������, ���� ������ � ���������� ������ ����������� �� ����������� 
    *  ������, �� ���� ���� �������� ������ Errors ����� ������ ������
    *  DeinitModuleDescriptions.
    *
    */ 

    struct ErrorDescription {
        int id;
        const wchar_t * message;
    };

    class Error2;

    /*!
    * \brief ����� ��� �������� � ��������� ����������� 
    *        �������� ������, ������������ � ����� �� �������.
    *
    */ 

    class KLSTD_NOVTABLE Error: public KLSTD::KLBase{
    public :
        /*!
            \brief ���������� ������������� ������, ������������ ����������.

            ����� ������� � ������� ������ ���� ���������.  ��� ������ �����
            ��������� � ������������� ���� ��� ���������������� �������.

            \return ��� ������, ������������� ����������.

        */
        KLSTD_NOTHROW virtual const wchar_t * GetModuleName() const throw() = 0;

        /*!
            \brief ���������� ����� ������ ������, ������������ ����������.

            ������ ������ ������ ���� ��������� � ������� � ������ ������
            ����� ��������� �������� ������� ������, ������ �������� �� �����
            ����������� ����� ������� ����� ��������������.

            \return ����� ������.

        */
        KLSTD_NOTHROW virtual int GetId() const throw() = 0;

        /*!
            \brief ���������� ������ ������, ����������� ��� ������ ������ ������.
            \return ������ ������.

        */
		KLSTD_NOTHROW virtual long GetErrorSubcode() const throw() = 0;



        /*!
            \brief ���������� ��� ����� �������� �������, ��� ���������
                   ����������� ����������.

            ��� ����� ���������� ��� ������ ����������� ��������� �������������
            __FILE__.

            \return ��� ����� �������� �������.

        */
        KLSTD_NOTHROW virtual const char * GetFileName() const throw() =0;

        /*!
            \brief ���������� ����� ������ � ����� �������� �������, ��� ���������
                    ����������.

            ������ � ����� ���������� ��� ������ ����������� ��������� �������������
            __LINE__.

            \return ������ � ����� �������� �������.

        */
        KLSTD_NOTHROW virtual int GetLine() const throw() = 0;

        /*!
            \brief ���������� ��������� ��������� � ������.

            \return ��������� ��������� �� ������.

        */
        KLSTD_NOTHROW virtual const wchar_t * GetMsg() const throw() = 0;

        /*!
            \brief ������������� ������ ���������� � ��������� �� ������.

            ������ ����� ��������� �������� run time ���������� � ���������
            �� ������.  � �������� ��������� ������ ��� ��������� �� ������
            ������������ ����������� ������ � �������� ������.  ����� �
            ��� ����������, ������������ � arg, ������� ����������������
            ����� � ���� ����������, ������������ � ��������� ������. ���
            ������� ���������� � ��������� �� ������ ������������ �������
            vswprintf, ������� ������ ��������� �� ������ ������������ ���������
            ������� ���� �������.
				������ ��������� ����� �������������� �� ������ ��������� 511
			��������.

            \param arg [in]  ������ ���������� ��� ������� � ��������� �� ������.


        */
        KLSTD_NOTHROW virtual void SetMessageParams(va_list arg) throw() = 0;

        /*!
          \brief	Sets error subcode. (Usually os error code). 

          \param	lSubCode IN subcode
        */
		KLSTD_NOTHROW virtual void SetErrorSubcode(long lSubCode) throw() = 0;

        /*!
          \brief	Returns interface KLERR::Error2

          \return	KLERR::Error2 interface. Method never returns NULL.
        */
        KLSTD_NOTHROW virtual KLERR::Error2* GetError2() throw() = 0;
    };

    typedef KLSTD::CAutoPtr<KLERR::Error> ErrorPtr;

    /*!
    * \brief ����� ��� �������� � ��������� ����������� 
    *        �������� ������, ������������ � ����� �� �������.
    *
    */
    class KLSTD_NOVTABLE Error2
        :   public KLSTD::KLBaseQI
    {
    public:
        /*!
            \brief see description of Error interface
        */
        KLSTD_NOTHROW virtual const wchar_t * GetModuleName() const throw() = 0;

        /*!
            \brief see description of Error interface
        */
        KLSTD_NOTHROW virtual int GetId() const throw() = 0;

        /*!
            \brief see description of Error interface
        */
		KLSTD_NOTHROW virtual long GetErrorSubcode() const throw() = 0;

        /*!
            \brief see description of Error interface
        */
        KLSTD_NOTHROW virtual const char * GetFileName() const throw() =0;

        /*!
            \brief see description of Error interface
        */
        KLSTD_NOTHROW virtual int GetLine() const throw() = 0;

        /*!
            \brief see description of Error interface
        */
        KLSTD_NOTHROW virtual const wchar_t * GetMsg() const throw() = 0;

        /*!
            \brief see description of Error interface
        */
        KLSTD_NOTHROW virtual void SetMessageParams(va_list arg) throw() = 0;

        /*!
            \brief see description of Error interface
        */
		KLSTD_NOTHROW virtual void SetErrorSubcode(long lSubCode) throw() = 0;

        /*!
          \brief	Returns old Error* interface

          \return	old Error* interface. Method never returns NULL.
        */
        KLSTD_NOTHROW virtual KLERR::Error* GetError() throw() = 0;

        /*!
            \brief Sets previous (parent) error in chain. 
        */
        KLSTD_NOTHROW virtual void SetPreviousError(KLERR::Error* pError) throw() = 0;

        /*!
            \brief Sets previous (parent) error in chain. 
        */
        KLSTD_NOTHROW virtual void SetPreviousError2(KLERR::Error2* pError) throw() = 0;

        /*!
            \brief Returns previous (parent) error in chain. 
        */
        KLSTD_NOTHROW virtual void GetPreviousError(KLERR::Error** ppError) throw() = 0;

        /*!
            \brief Returns previous (parent) error in chain. 
        */
        KLSTD_NOTHROW virtual void GetPreviousError2(KLERR::Error2** ppError) throw() = 0;

        /*!
            \brief Copies error object.
            \return false in case of error (possibly out-of-memory)
        */
        KLSTD_NOTHROW virtual bool Clone(KLERR::Error2** ppError) throw() = 0;
    };

    typedef KLSTD::CAutoPtr<KLERR::Error2> Error2Ptr;

    class ErrAdapt
    {
    public:
        ErrAdapt(KLERR::Error* pError)
            :   m_pError(pError)
            ,   m_pError2(pError?m_pError->GetError2():NULL)
        {;};
        ErrAdapt(KLERR::Error2* pError2)
            :   m_pError2(pError2)
            ,   m_pError(pError2?m_pError2->GetError():NULL)
        {;};
        operator KLERR::Error*()
        {
            return m_pError;
        };

        operator KLERR::Error2*()
        {
            return m_pError2;
        };

        operator KLSTD::KLBaseQI*()
        {
            return (KLERR::Error2*)m_pError2;
        };
    protected:
        KLERR::ErrorPtr     m_pError;
        KLERR::Error2Ptr    m_pError2;
    };

    /*!
        \brief ��������������� �������
	*/
	KLSTD_NOTHROW KLCSC_DECL void SayFailure(
										int level,
										Error* perror,
										const wchar_t* module,
										const char* file,
										int line) throw();

	inline void rethrow_if_possible(KLERR::Error* pError)
	{
		if(pError){
			pError->AddRef();
			throw pError;
		};
	};

}

	/*!
		\brief ������� ������, ���������� ���������� �� ������.

		������� ������, ���������� ��������� �� ������.  ���� ������
		���������� message, ��� ��������� ������������ ������ ���������,
		������������� � InitModuleDescriptions.
    
		\param ppError [out] ��������� �� ��������� Error
		\param szwModule [in] ��� ������, ����������� ������  (������������� � �������� !!!).
		\param nId  [in] ������������� ������.
		\param szaFile [in] ��� ����� �������� �������, ��� ��������� ������.
		\param nLine [in] ������ � ����� �������� �������, ��� ��������� ������.
		\param szwMessage [in]  ��������� �� ������.

		\return true � ������ ������ ����� false 
	*/

	KLSTD_NOTHROW KLCSC_DECL void KLERR_CreateError(
		KLERR::Error** ppError,
		const wchar_t*	szwModule,
		int				nId,
		const char*		szaFile=NULL, 
		int				nLine=0,
		const wchar_t*	szwMessage=NULL) throw();


	KLSTD_NOTHROW KLCSC_DECL void KLERR_CreateError2(
		KLERR::Error** ppError,
		const wchar_t*	szwModule,
		int				nId,
		const char*		szaFile, 
		int				nLine,
		const wchar_t*	szwMessage, ...) throw();


    /*!
        \brief �������������� ������ ��������� �� ������� ������ ���
               ������������� � ������ Error.

        ���� ����� ������������� ������������ ����� ���������� �������
        � �������� � ����������� �� �������.  ������ ������ ���� 
        ���������� ��� ����� ������� ����� ������ (�� ������� ������
        DeinitModuleDescripitons).  ������ ������ ������� 
        DeinitModuleDescriptions � �������� ����������� ������ ������.
        ��������������� �� ����������� �������, ���������� ��� ������� �
        ��������� ������ ������, ����� �� ������� ������ Error.  ����� ������
        ����� ������ ������ �� ������ ������ ������ � ��������� ������.
        
        \param szwModule [in] ��� ������ ��� ������������� ������� ������ (������������� � �������� !!!).
        \param descr [in] ������ � ��������� ������.
        \param arraySize [in] ������ ������� � ��������� ������.

    */

	KLSTD_NOTHROW KLCSC_DECL void KLERR_InitModuleDescriptions( 
        const wchar_t*					szwModule, 
        const KLERR::ErrorDescription*	descr,
        int								arraySize) throw();


    /*!
        \brief ���������������� ������ ��������� �� ������� ������ ���
               ������������� � ������ Error.

        ���� ����� ��������� ������������ ����� ���������� �������
        � �������� � ����������� �� �������.  ����� ����� ������
        ������ Error ��������� ������������ ������ � ����������
        ������ ��� �������� ��������� �� �������.
        
        \param szaModule [in] ��� ������ ��� ��������������� ������� ������.

    */

	KLSTD_NOTHROW KLCSC_DECL void KLERR_DeinitModuleDescriptions(const wchar_t* szaModule) throw();

    /*!
        \brief ����� �������� ������ �� ���� �������.

            Code sample:
                    KLSTD::klwstr_t wstrModule, wstrString;
                    KLERR_FindString(
                            1186,
                            wstrModule.outref(),
                            wstrString.outref());

			\param	nCode [in] ��� ����������, ������� ��������� �����
			\param	wstrModule [out] ��������� ��� ������
			\param	wstrString [out] ��������� �������� ������

			\return true � ������ ������ ����� false 
	*/

	KLSTD_NOTHROW KLCSC_DECL bool KLERR_FindString(
										int             nCode,
										KLSTD::AKWSTR&  wstrModule,
										KLSTD::AKWSTR&  wstrString) throw();

    /*!
        \brief ����� �������� ������

            Code sample:
                    KLSTD::klwstr_t wstrString;
                    KLERR_FindModuleString(
                            KLSTD::STDE_BADPARAM,
                            L"KLSTD",
                            wstrString.outref());

			\param	nCode [in] ��� ����������, ������� ��������� �����
			\param	szwModule [in] ��� ������
			\param	wstrString [out] ��������� �������� ������

			\return true � ������ ������ ����� false 
	*/
    KLSTD_NOTHROW KLCSC_DECL bool KLERR_FindModuleString(
								int				nCode,
								const wchar_t*  szwModule,
								KLSTD::AKWSTR&	wstrString) throw();

    /*!
      \brief	Finds error description in a sorted array of 
                KLERR::ErrorDescription
      \param	nCode IN code 
      \param	pData IN array
      \param	nData IN array length
      \return	description or L"" if not found
  
    */
    KLSTD_NOTHROW KLCSC_DECL const wchar_t* KLERR_FindString2(
							int				                nCode,
                            const KLERR::ErrorDescription*  pData,
                            size_t                          nData) throw();

    /*!
        \brief ����� � ����������� ����������. ���� ������������ ������ ��� �������� ����������,
					������ ���� ������������� ��������� ������� STDE_NOMEMORY
			\param szwModule [in] ��� ������
			\param nId [in] ��� ����������
			\param szaFile [in] ��� �����, �� �������� ������������� ���������� (__FILE__)
			\param nLine [in] ������ � ������� ������������� ���������� (__LINE__)
			\param szwMessage [in] �������������� �������� ����������
			\param ... [in] ���������, ����������� ��� ������� ����������
	*/

	KLCSC_DECL KLSTD_NORETURN void KLERR_throwError(
		const wchar_t*	szwModule,
		int				nId,
		const char*		szaFile, 
		int				nLine,
		const wchar_t*	szwMessage...);


    /*!
      \brief	

      \param	Error code
      \param	Zero ended array opf codes to ignore
      \return	Returns true if ignore exception
    */
    KLSTD_NOTHROW KLCSC_DECL bool KLERR_IfIgnore(long lCode, ...)throw();

#endif // KL_ERROR_H

// Local Variables:
// mode: C++
// End:
