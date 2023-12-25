/*!
 * (C) 2003 Kaspersky Lab 
 * 
 * \file	jrnl/journal.h
 * \author	Mikhail Karmazine
 * \date	22.01.2003 11:58:09
 * \brief	��������� ��� ������ � �������� - persitent-���������� �������,
    � ������� ���� ������������ ������ � �����, ���� ��������� ������������ ������.
    ����� �������� �������� ���� ����������� �������.
 */


#ifndef __JOURNAL_H__
#define __JOURNAL_H__

#include "std/base/klbase.h"
#include "std/io/klio.h"
#include "std/par/params.h"
#include "errors.h"

#define KLJRNL_DEF_MAX_REC_NUM_IN_PAGE      100000
#define KLJRNL_DEF_MAX_PAGE_SIZE            1024  // 1 kb
#define KLJRNL_DEF_LIMIT_PAGES              true
#define KLJRNL_DEF_BINARY                   true
#define KLJRNL_DEF_OPEN_TIMEOUT             0
#define KLJRNL_DEF_PAGE_LIMIT_TYPE          KLJRNL::pltRecCount
#define KLJRNL_DEF_USE_REC_NUM_INDEX        false

namespace KLJRNL
{
    /*!
    * \brief ��������� ������ �������. ������ ������ ����� ���������� ���� � �����,
        � ��������� ���� ������.
    */
    class KLSTD_NOVTABLE JournalRecord : public KLSTD::KLBase
    {
    public:
        /*!
          \brief	Serialize
            ����� ���������� ��� ���������� ������ � ������.

          \param	strData [out] - ������ ������ ��������� ���� � ���������� ������.
        */
        virtual void Serialize( std::string & strData ) const = 0;

        /*!
          \brief	Deserialize
            ����� ���������� ��� ���������� ������ �� �������.

          \param	strData [in] - ������, �� ������� ������ ���� ��������� ������.
        */
        virtual void Deserialize( const std::string & strData ) = 0;
    };

    // \brief ��. �������� ��������� CreationInfo
    enum PageLimitType { pltRecCount, pltSize, pltUnlimited };


    /* \brief CreationInfo - ������������ � ��� �������, ����� ������ ����� ������� ��� �����������.
        �������� ���������, ����������� ��� ������������ ���������� ��������� �������.

    \param bLimitPages [in] - ���� false, �� ���������� �������
        �� ����������, ��� ����� ����������� �� ���� ���������� ��������������� ����������
        �������, � ���������, ����� ��� ������ � ��������, ����������� �� �����
        (��. �������� pageLimitType), ����� �������.
        ���� true, �� ����� ������������� �� ������ ���� �������. ����� ����� ����� ��������
        �����������, ������ �������� ���������, � ������ ��� ��������� ��� ����� ����� ��������.

    \param bBinaryFormat [in] - ���� true, �� ID, ��������� ����� � ����. 
        ��������� ���������� ������� ����� ������ � ����� � �������� ����. � ��������� ������ - 
        � ��������� (������ ����� � ����� ������ ������ � ��� ����, � ������� �������).

    \param pageLimitType [in] - ���� pltRecCount, �� �������� ����� ���������� ���-��� ����������
        � ��� ������� � ������� ��������� nMaxRecordsInPage. ���� pltSize, �� �������� �����
        ���������� ����� ���������� �������� �� ����� � ������� ��������� nMaxPageSize.
         ���� pltUnlimited, �� �������� ������ ����� ����, � ����� ������������� ��� �����������.

    \param nMaxRecordsInPage [in] - ��������� ������������ ����� �������
        � �������� - �������� ������������, ����� pageLimitType==pltRecCount, ����� ������������.

    \param nMaxRecordsInPage [in] - ��������� ������������ ������ �������� � ������ -
        - �������� ������������, ����� pageLimitType==pltSize, ����� ������������.
    */
    struct CreationInfo
    {
        CreationInfo() :
            bLimitPages(KLJRNL_DEF_LIMIT_PAGES),
            pageLimitType(KLJRNL_DEF_PAGE_LIMIT_TYPE),
            bBinaryFormat(KLJRNL_DEF_BINARY),
            nMaxRecordsInPage(KLJRNL_DEF_MAX_REC_NUM_IN_PAGE),
            nMaxPageSize(KLJRNL_DEF_MAX_PAGE_SIZE),
            bUseRecNumIndex(KLJRNL_DEF_USE_REC_NUM_INDEX)
        {};

        bool bLimitPages;
        bool bBinaryFormat;
        PageLimitType pageLimitType;
        long nMaxRecordsInPage;
        long nMaxPageSize;
        bool bUseRecNumIndex;
    };

    /*!
    * \brief ��������� �������. ��� �������� �� ������ ������ ����������� � ������������
        ������ �� ������, �.�. ������ � ���� ������ ����� ������������ ������ ���� 
        ��������� ������.
    */
    class KLSTD_NOVTABLE Journal : public KLSTD::KLBase
    {
    public:
        virtual ~Journal() { };

        /* \brief ��������� ������ ��� ������ ��� ������. ��� �������� ��� ������ �����
            ������� ���, ���� ������� �� ������������ (��. ��������� ����).
            ������������� ��������� ������ ������ � ��������� �����, ��� ��� ������ 
            ������ ������� �� ���������� ������.

            ���� ������ ���������, �� ���� ����� ���������� ���������� ERR_CORRUPTED. �
                ����� ������ ��� �������������� ������� ���������� ������� ����� Repair.

  		    \param wstrPath [in] - ���� � ����� �������. Hint ��� �������� �������: ������
                ���� - �� ����������� � ������� (�� �������� �����������), ������� ������
                ������ ������������� ��������� � ��������� �����.

            \param flagsCreation [in] - ��. �������� KLSTD::CREATION_FLAGS.
                � ������ �������� ������ �� ������ (�.�. �������� flagsAccessFlags == AF_READ):
                    �) ������ �������� ����� ��������� ������ �������� CF_OPEN_EXISTING.
                    �) ���� ������ �� ����������, �� ���������� ����������.
                � ������ �������� �� ������, ���� ������ �� �����������, ��� ���� ������������
                  �����������, ��������� � ���������� nMaxRecordsInPage, bLimitPages � bBinaryFormat.
                  � ��������� ������ ��� ��������� ������������.
                ���� ������ ���� CF_CLEAR, � ������ ��� �����������, �� ������ ����� ������,
                    �� ����������� ��� ����� ��������� �������� (�.�. ���������-����������� �����-����
                    �������������)

            \param flagsAccessFlags [in] - ���������, ��������� ������ �� ������ ��� �� ������.

            \param creationInfo [in] - ������������ ������ ��� �������� ������� (��. �������� 
                ���������� flagsCreation � flagsAccessFlags). �������� ���������, ����������� ���
                 ������������ ���������� ��������� �������. ��.�������� ��������� CreationInfo.

            \param nTimeout [in] - ����� � ����, � ���. �������� ���� ����� ����� �����, ����� ������ 
                ������ �������� ������ (���� ������ ������ ������ ������). ����� �������� �������, �� ������
                ��� ��� ����� �����, �� ����� ��������� ���������� STDE_TIMEOUT. ���� �������� ����� 0, 
                �� ����� �� ����� �����, � ����� �������� ����������, ���� ������ ����� �����. ���� �������� �����
                KLSTD_INFINITE, �� ����� ����� �����, ���� �� ��������.
        */
        virtual void Open(
            const std::wstring &    wstrPath,
            KLSTD::CREATION_FLAGS   flagsCreation,
            KLSTD::ACCESS_FLAGS     flagsAccessFlags,
            const CreationInfo &    creationInfo = CreationInfo(),
            long                    nTimeout = KLJRNL_DEF_OPEN_TIMEOUT ) = 0;

        /*!
          \brief	GetUsedCreationInfo
            ���������� ��������� ��������� ��������� �������
          \param creationInfo [out] - ��������� ��������� ��������� �������.
                ��.�������� ��������� CreationInfo.
        */
        virtual void GetUsedCreationInfo( CreationInfo & creationInfo ) = 0;

        /*!
          \brief	ChangeLimits
            ������ ����������� ������� - ��. �������� ������ Open. ��������� ������
                � ������������ ������, � �.�. � �� ������.

          \param	wstrPath [in] - ���� � ����� �������.

          \param creationInfo [in] - �������� ���������, ����������� ���
                ������������ ���������� ��������� �������. ��.�������� ��������� CreationInfo.
        */
        virtual void ChangeLimits(const std::wstring& wstrPath, const CreationInfo& creationInfo) = 0;

        /*!
          \brief	Close
            ��������� ������
        */
        virtual void Close() = 0;

        /*!
          \brief	CloseAndRemoveFiles
            ��������� �����. �������� ������, � ����� ��������
            ��������� ������� �����, ������� ���������� ������. ���� ������
            � ��� ����� ������ ������ ��������, �� ����������� ����������, ��� ���� 
            �� ��������� ������. �� ���� ���� ��������� ���, ���� ������.
        */
        virtual void CloseAndRemoveFiles() = 0;

        /*!
          \brief	IsOpened
            ��������� ��������� ���������� ������ - ������/������.

          \return	bool - true ���� ������ ������, false otherwise.
        */
        virtual bool IsOpened() = 0;
        
        /*!
          \brief	GetJournalSize
            ���������� ������ �������. ������ ������ ���� ������.

          \return	AVP_longlong - ������ �������.
        */
        virtual AVP_longlong GetJournalSize() = 0;

        /*!
          \brief	Repair
            ���� ��� �������� ������� ���� �������� ���������� ERR_CORRUPTED (��.�������� ������ Open),
                �� ������� ����� ������ ����� ����� ������ (� ����� � �� ������ :) )
                ��������� ������ � ������������ ������, � �.�. � �� ������.

            \param	const std::wstring & wstrPath [in] - ���� � ����� �������.
            \param	const CreationInfo & creationInfo - ������ ����� ������������ � ������ �����������
        */
        virtual void Repair(const std::wstring& wstrPath, const CreationInfo& creationInfo) = 0;

        /*!
          \brief	Add
            ��������� ������ � ������. 

          \param	pParams [in] - �������� �������������� � � ����� ���� ������������ 
                � ����� �������.
          \return	long - id ����� ������.
        */
        virtual long Add(const KLPAR::Params* pParams) = 0;

        /*!
          \brief	Add
            ��������� ������ � ������. 

          \param	pRecord [in] - ��� ��������� ���������� ��� ����� Serialize, ������� 
            ������ �������� ���� � �����.
          \return	long - id ����� ������.
        */
        virtual long Add(JournalRecord* pRecord) = 0;
        
        /*!
          \brief	Add
            ��������� ������ � ������. 

          \param	str [in] - ������, �������������� �� ���� ������. ����� ��������� �����
            �������, � ��� ����� ����. ������ ��������������� ��� ������� ������,
            ������������ � str.c_str(), �������� str.size().
          \return	long - id ����� ������.
        */
        virtual long Add( const std::string & str ) = 0;
        
        /*!
          \brief	Update
            ��������� ������� ������ � �������. ������ ������ ���� ���� �� �������,
                ��� � ������ ������ - �.�. ��������������� � ������ �������� ������
                ����� ��� �� ������.

          \param	pParams [in] - �������� �������������� � � ����� ���� ������������ 
                � ������.
        */
        virtual void Update( const KLPAR::Params* pParams ) = 0;

        /*!
          \brief	Update
            ��������� ������� ������ � �������. ������ ������ ���� ���� �� �������,
                ��� � ������ ������ - �.�. ��������������� � ������ �������� ������
                ����� ��� �� ������.

          \param	JournalRecord [in] - �������� �������������� � � ����� ����
            ������������ � ������.
        */
        virtual void Update( JournalRecord* pRecord ) = 0;

        /*!
          \brief	Update
            ��������� ������� ������ � �������. ������ ������ ���� ���� �� �������,
                ��� � ������ ������.

          \param	str [in] - ������, �������������� �� ���� ������. ����� ��������� �����
            �������, � ��� ����� ����. ������ ��������������� ��� ������� ������,
            ������������ � str.c_str(), �������� str.size().
        */
        virtual void Update( const std::string & str ) = 0;

        /*!
          \brief	Flush - ������ Flush �������.
        */
        virtual void Flush() = 0;

        /*!
          \brief	ResetIterator
            ������������� �������� ������� �� ������ �������. ����� ����� �����, 
                ���� IsEOF()==false, ����� �������� ������ �� GetCurrent().
        */
        virtual void ResetIterator() = 0;
        
        /*!
          \brief	SetIterator
            ������������� �������� �� ������ � �������� ID. ���� ����� ������ ���, ��
            �������� ��������������� �� ��������� ������. ���� ���������� ������
            �����������, �� ��������� ��������������� �� ����� ������� (IsEOF()==true).
            \param	nId [in] - ID ������.
			\return bool - true ���� ������ ����� �� ������ � �������� ID, false otherwise.
        */
        virtual bool SetIterator( long nId ) = 0;

        /*!
          \brief	GotoNthRecord
            ������������� �������� �� N-� ������ �� ������. ������ ������ ����� ������ 0.
            ���� nRecIdx ������ ��� ����� ���������� ������� � �������, �� �������� 
            ��������������� �� ����� ������� (IsEOF()==true).
            \param	nRecIdx [in] - ����� ������ �� ������. ������ ������ ����� ����� 0.

        */
        virtual void MoveToRecordN( long nRecIdx ) = 0;
        
        /*!
          \brief	GetRecordCount
            ���������� ���������� ������� � �������.
            \param	long - ���������� ������� � �������.
        */
        virtual long GetRecordCount() = 0;
        
        /*!
          \brief	Next
            ��������� �������� �� ��������� ������.
        */
        virtual void Next() = 0;

        /*!
          \brief	IsEOF
            ��������� ����� �������.

          \return	bool - false ���� ������ ����� ���� ��������, true ���� ���������
            ����� �������.
        */
        virtual bool IsEOF() = 0;

        /*!
          \brief	GetCurrent
            ���������� ������� ������. ��� ��������� pRecord ���������� ���
             ����� Deserialize(), ������� ������ ������� ���� �� ������.

          \param	 long & nId [out] - id ������.
          \param	JournalRecord* pRecord [in] - �������� �� ��������� JournalRecord.
        */
        virtual void GetCurrent( long & nId, JournalRecord* pRecord ) = 0;

        /*!
          \brief	GetCurrent
            ���������� ������� ������. 

          \param	 long & nId [out] - id ������.
          \param	KLPAR::Params** ppParams [out] - Params, � ������� �������������� ������
        */
        virtual void GetCurrent( long & nId, KLPAR::Params** ppParams ) = 0;

        /*!
          \brief	GetCurrent
            ���������� ������� ������.

          \param	 long & nId [out] - id ������.
          \param	std::string & strData [in] - ������, �������������� �� ���� ������.
            ����� ��������� ����� �������, � ��� ����� ����. ������ ��������������� ���
            ������� ������, ������������ � str.c_str(), �������� str.size().
        */
        virtual void GetCurrent( long & nId, std::string & strData ) = 0;


        /*!
          \brief	DeleteOldRecords
            ������� ������, �������� nRecordsToLeave ����� ����� �������.
                ���� nRecordsToLeave >= ������ ���������� �������, �� ��������
                �� ������������.

          \param	long nRecordsToLeave - ������������ ���������� �������, �������
            ����� ��������.
        */
        virtual void DeleteOldRecords( long nRecordsToLeave ) = 0;

        /*!
          \brief	DeleteCurrent
            ������� ������� ������.
        */
        virtual void DeleteCurrent() = 0;

        /*!
          \brief	DeleteOlderThanID
            ������� ������, ����������� ������, ��� ������ � ���������� ID,
                � ���� ������ � ����� ID.
          \param	long nID - ID ������, �� ������� ����� �������.
        */
        virtual void DeleteOlderThanID( long nID ) = 0;

        /*!
          \brief	DeleteRanges - ������� ������ �� �������, ���������� � ���������� ���������.
          \param	vectRanges [in] - ������ ���������� �������, ������� ���� �������.
        */
        virtual void DeleteRanges( const std::vector< std::pair<long, long> > & vectRanges ) = 0;

        /*!
          \brief	DeleteAll
            ������� ��� ������.
        */
        virtual void DeleteAll() = 0;
		
        /*!
          \brief	DeleteAll
            ������� �������������� ������ �� .ctrl �����.
        */
		virtual void ShrinkCentralFile(            
			const std::wstring &    wstrPath,
            const CreationInfo &    creationInfo = CreationInfo(),
            long                    nTimeout = KLJRNL_DEF_OPEN_TIMEOUT ) = 0;

        /*!
          \brief	ResetIterator
            ������������� �������� ������� �� ������ �������. ����� ����� �����, 
                ���� IsEOF()==false, ����� �������� ������ �� GetCurrent().

			\param	wstrJournalID [out] - ���������� ������������� ����� �������, 
										  ������� ������������ ������ ���, ����� ��������� 
										  ����� Central File
        */
		virtual void ResetIteratorEx(std::string& strJournalID) = 0;

        /*!
          \brief	SetIterator
            ������������� �������� �� ������ � �������� ID. ���� ����� ������ ���, ��
            �������� ��������������� �� ��������� ������. ���� ���������� ������
            �����������, �� ��������� ��������������� �� ����� ������� (IsEOF()==true).
            \param	nId [in] - ID ������.
			\param	wstrJournalID [out] - ���������� ������������� ����� �������, 
										  ������� ������������ ������ ���, ����� ��������� 
										  ����� Central File
			\return bool - true ���� ������ ����� �� ������ � �������� ID, false otherwise.
        */
		virtual bool SetIteratorEx(long nId, std::string& strJournalID) = 0;
    };

}


/*!
  \brief	KLJRNL_CreateJournal
                ������� ������� � ��������� �� ����� ������������� �������.
  \param	KLJRNL::Journal** ppJournal
  \param	bool bMultiThread
  \return	void 
*/
KLCSKCA_DECL void KLJRNL_CreateJournal(KLJRNL::Journal** ppJournal, bool bMultiThread );

/*!
  \brief	KLJRNL_CreateJournal
                ������� ������������� �������, ���������� ������� ����� ���� 
                ������������� � ��������� �����������, ����� ��� MS SQL � Excel.
                ������ ����������� �� �������� "���� ������ = ���� ������", ��������
                ������ �������� ���������� ������ ���������.
  \param	KLJRNL::Journal** ppJournal
  \param	bool bMultiThread
  \return	void 
*/
KLCSKCA_DECL void KLJRNL_CreateSimpleJournal( KLJRNL::Journal** ppJournal, bool bMultiThread );

#endif //__JOURNAL_H__

// Local Variables:
// mode: C++
// End:
