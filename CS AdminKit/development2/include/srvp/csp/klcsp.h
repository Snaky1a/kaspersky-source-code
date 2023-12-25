/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	klcsp.h
 * \author	Andrew Kazachkov
 * \date	16.06.2003 19:34:25
 * \brief	Common server proxy classes
 * 
 */

#ifndef __KL__CSP_H__
#define __KL__CSP_H__

#define KLCSP_ITERATOR_ARRAY    L"KLCSP_ITERATOR_ARRAY" //ARRAY_T

namespace KLPAR{
	class Params;
};

namespace KLCSP
{
    //! ���������, ���������� ������������� ���������� ����������.
	typedef struct {
		//! ��� ������, � ������� ������ ����.
		std::wstring domain;
		//! ��� ���������� � ������.
		std::wstring host;
	}host_id_t;
    
	//! �������� ���������� �� ������ ���� 
	typedef struct 
	{
		std::wstring wstrFieldName;	// ����, �� �������� ��������������� ����������
		bool bOrder;				// ���� true, �� ���������� ������, ���� false - �� ��������.
	} field_order_t;
    
    typedef std::vector<field_order_t>   vec_field_order_t;

    class KLSTD_NOVTABLE ForwardIterator : public KLSTD::KLBase
	{
	public:

	/*!
	  \brief	GetNextItems

	  \param	lCount [in, out] ���������� �������, ������� ���������� �������.
									���� �� ��������� ���������� ������� ��������� �������.
	  \param	ppData [out] - �������� ������ ���������
	  \return	bool - false, ���� ��������� ����� ������.
	*/
		virtual bool GetNextItems(long& lCount, KLPAR::Params** ppData)=0;
	};

    class KLSTD_NOVTABLE ChunkAccessor : public KLSTD::KLBase
	{
	public:

	/*!
	  \brief	GetRecordsCount

	  \return	long - ����� ���������� �������.
	*/
		virtual long GetRecordsCount()=0;

	/*!
	  \brief	GetChunk

	  \param	lStart [in] ����� ������ ������, ������� ���������� �������.
	  \param	lCount [in] ���������� �������, ������� ���������� �������.
	  \param	ppData [out] - �������� ������ ���������.
	  \return	long - ���������� ������� ��������� �������.
	*/
		virtual long GetChunk(long lStart, long lCount, KLPAR::Params** ppData)=0;
	};
};

#endif //__KL__CSP_H__

// Local Variables:
// mode: C++
// End:
