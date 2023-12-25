////////////////////////////////////////////////////////////////////
//
//  _CARRAY.H
//  CPtrArray definition (without MFC)
//  General purpose
//  Alexey de Mont de Rique [graf@avp.ru], Kaspersky Labs. 1999
//  Copyright (c) Kaspersky Labs.
//
////////////////////////////////////////////////////////////////////

#ifndef ___CARRAY_H
#define ___CARRAY_H

class CPtrArray
{

public:

// Construction
	CPtrArray();

// Attributes
	int GetSize() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

	void Reserve(int nNewSize);
	void ReserveAdditional(int nAdditionalSize);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	void* GetAt(int nIndex) const;
	void SetAt(int nIndex, void* newElement);
	void*& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const void** GetData() const;
	void** GetData();

	// Potentially growing the array
	void SetAtGrow(int nIndex, void* newElement);
	int Add(void* newElement);
	int Append(const CPtrArray& src);
	void Copy(const CPtrArray& src);

	// overloaded operator helpers
	void* operator[](int nIndex) const;
	void*& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, void* newElement, int nCount = 1);
	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CPtrArray* pNewArray);

// Implementation
protected:
	void** m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

public:
	~CPtrArray();

#ifdef _DEBUG
//	void Dump(CDumpContext&) const;
//	void AssertValid() const;
#endif

protected:
	// local typedefs for class templates
	typedef void* BASE_TYPE;
	typedef void* BASE_ARG_TYPE;
};

inline int CPtrArray::GetSize() const { return m_nSize; }
inline int CPtrArray::GetUpperBound() const { return m_nSize-1; }
inline void CPtrArray::RemoveAll() { SetSize(0, -1); }
inline void* CPtrArray::GetAt(int nIndex) const { return m_pData[nIndex]; }
inline void CPtrArray::SetAt(int nIndex, void* newElement){	m_pData[nIndex] = newElement; }
inline void*& CPtrArray::ElementAt(int nIndex) { return m_pData[nIndex]; }
inline const void** CPtrArray::GetData() const { return (const void**)m_pData; }
inline void** CPtrArray::GetData() { return (void**)m_pData; }
inline void* CPtrArray::operator[](int nIndex) const { return GetAt(nIndex); }
inline void*& CPtrArray::operator[](int nIndex) { return ElementAt(nIndex); }



#endif
