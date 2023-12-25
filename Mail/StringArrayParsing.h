/*!
*		
*		
*		(C) 2002 Kaspersky Lab 
*		
*		\file	StringArrayParsing.h
*		\brief	���������� ������� ������ _szPatternArray_ � �������, ������������ _szDelimeter_
*				� �������� �������� ����������� ������� ��������� ����� ������.
*				����� ���������� #include "stringarrayparsing.h" ���������� �������� ���� �������� 
*				���� _std_string_
*		
*		\author Vitaly DVi Denisov
*		\date	21.11.2002 19:04:22
*		
*		Example:	
*		#include <string>
*		#include "stringarrayparsing.h"
*
*		//...
*
*		std::string szScript = "blah,blah,blah"
*		STRINGARRAYPARSING_BEGIN(std::string, szScript, std::string(",") )
*		{
*			DoParsedParam(_szPattern);
*		}
*		STRINGARRAYPARSING_END
*		
*		
*		
*/		


#ifndef _STRINGARRAYPARSING_H_
#define _STRINGARRAYPARSING_H_

//! \fn				: STRINGARRAYPARSING_BEGIN
//! \brief			:	����������� ������. ��. ������ ������������� � ������ �����
//! \param          : _std_string_		-	��� ������. ����� ���� std::string ��� std::wstring 
//!											���� ����� ��������� �� ���� ���� �����. 
//! \param          : _szPatternArray_	-	����������� ���� _std_string_. 
//!											������ ������� szPatternArray ���������� _��_�����_
//! \param          : _szDelimeter_		-	�����������. ����������� ���� _std_string_
#define STRINGARRAYPARSING_BEGIN(_std_string_, _szPatternArray_, _szDelimeter_)						\
	{                                                         						\
		_std_string_	_szPattern;               									\
		int				_iCount			=	-1;                   					\
		int				_iCountOld		=	_iCount;               					\
		bool			_bIsLastPattern	=	false;                					\
		_std_string_	_pszSeparator	=	_szDelimeter_; 							\
		int				_iSeparatorSize	=	_pszSeparator.length();					\
		int				_iPatternSize	=	0;                    					\
		                                                      						\
		do{                                                   						\
			if ( _iCount >= 0 )                                						\
				_iCount = _szPatternArray_.find(_pszSeparator, _iCount + _iSeparatorSize);\
			else                                                        			\
				_iCount = _szPatternArray_.find(_pszSeparator);             		\
			if ( ( !_pszSeparator.empty() ) && ( -1 != _iCount ) )                  \
			{                                                           			\
				if (_iCountOld >= 0)                                     			\
				{                                                       			\
					_iPatternSize = _iCount - _iCountOld - _iSeparatorSize;			\
					if (_iPatternSize)												\
					{																\
						_szPattern = _szPatternArray_.substr(						\
							_iCountOld + _iSeparatorSize,							\
							_iPatternSize											\
							);														\
					}         														\
				}             														\
				else          														\
				{             														\
					_iPatternSize = _iCount;             							\
					if ( _iPatternSize )                							\
						_szPattern = _szPatternArray_.substr(						\
							0,                         								\
							_iPatternSize               							\
							);                         								\
				}                                      								\
				_iCountOld = _iCount;                    							\
			}                                          								\
			else                                       								\
			{                                          								\
				if ( -1 == _iCountOld )                 							\
					_szPattern = _szPatternArray_;        							\
				else                                   								\
				{                                      								\
					_iPatternSize = _szPatternArray_.length() - _iCountOld;			\
					if ( _iPatternSize )                							\
						_szPattern = _szPatternArray_.substr(						\
							_iCountOld + _iSeparatorSize,							\
							_iPatternSize               							\
							);                         								\
				}                                      								\
				_bIsLastPattern = true;                 							\
			}                                                                                   


//! \fn				: STRINGARRAYPARSING_END
//! \brief			:	����������� ������ ��� STRINGARRAYPARSING_BEGIN
#define STRINGARRAYPARSING_END			                                             \
			;                                                                        \
		}                                                                            \
		while ( !_bIsLastPattern );                                                  \
	}


#endif // _STRINGARRAYPARSING_H_