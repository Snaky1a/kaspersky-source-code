/*!
 * Kaspersky lab application info file
 * Copyright (C) 2005 Kaspersky Labs.
 *
 * \file DataBase.h
 * \author Vitaly Denisov
 * \date 2005
 * \brief message classes for KIS-interface
 *
 */

#ifndef  _MESSAGE_INFO_H
#define  _MESSAGE_INFO_H


#ifndef pgMESSAGE_PART_CONTENT_LENGTH
    #define pgMESSAGE_PART_CONTENT_LENGTH   0
#endif
#ifndef pgMESSAGE_INTERNET_HEADERS
    #define pgMESSAGE_INTERNET_HEADERS   0
#endif


class INFO
{
public:
	// GetPropStr ���������� ��������� �� ��������� �������� (��������, pgMESSAGE_FROM)
	// � ������ ���������� �������� ������������ NULL
	// ��������� ���, ���� ��� ������ INFO.
	virtual const char* GetPropStr(  unsigned long ulPropID ) = 0;
	// GetPropLong ���������� ��������� �� �������� �������� (��������, pgMESSAGE_PART_CONTENT_LENGTH)
	// � ������ ���������� �������� ������������ 0
	virtual const long  GetPropLong( unsigned long ulPropID ) = 0;
};

class MESSAGEPART_INFO : public INFO
{
public:
	// GetData ���������� ��������� �� ����� ������.
	// ��������� ���, ���� �� ������� ReleaseData � ��� ������ MESSAGEPART_INFO. 
	// ��������� ������ ���� ���������� ������� ReleaseData.
	virtual IStream* GetData() = 0;
	virtual void ReleaseData();
};

class MESSAGE_INFO : public INFO
{
public:
    // GetMessagePart ��������� ��������� �� MESSAGEPART_INFO �� ����������� ������ num
	// ��������� ������ ���� ���������� ������� ReleaseMessagePart
    virtual MESSAGEPART_INFO* GetMessagePart(unsigned long num) = 0;
	virtual void ReleaseMessagePart(MESSAGEPART_INFO* pMessagePart) = 0;
};

#endif//_MESSAGE_INFO
