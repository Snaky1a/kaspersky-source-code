/*!
 * (C) 2002 "Kaspersky Lab"
 *
 * \file FilesList.h
 * \author ����� �����������
 * \date 2004
 * \brief ��������� ������ ������� ������
 * 
 */

#ifndef KLFT_FILESLIST_H
#define KLFT_FILESLIST_H

#include <std/base/klbase.h>
#include <kca/prci/componentid.h>

namespace KLFT {

	/*!
    * \brief ������ ������� ������ ���������� FT.
    *  
    */

	class KLSTD_NOVTABLE FilesList : public KLSTD::KLBase 
	{			
	public:

		/*!
			\brief �������� �� ������
		*/
		virtual void Reset() = 0;

		/*!
			\brief �������� �� ������
		*/
		virtual bool Next() = 0;


		/*!
			\brief ��������� ���������� �� �������� �����
		*/
		virtual const FileDescription &Next() = 0;

	};

} // end namespace KLFT

#endif // !defined(KLFT_FILESLIST_H)
