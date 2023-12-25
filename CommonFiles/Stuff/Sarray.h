////////////////////////////////////////////////////////////////////
//
//  Sarray.h
//  CSArray template
//  General purpose
//  Andrey Doukhvalov [petrovitch@avp.ru], Kaspersky Labs. 1999
//  Victor Matiouchenkov [victor@avp.ru], Kaspersky Labs. 1999
//  Copyright (c) Kaspersky Labs
//
////////////////////////////////////////////////////////////////////

#ifndef __SARRAY_H
#define __SARRAY_H

#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#ifndef _INC_MEMORY
#include <memory.h>
#endif

#include "stddefs.h"

#define SYS_MAX_UINT  (0xffffffff)

///////////////////////////////////////////////////////
// ���������� ������ �������� �� ���������� ���������� !!!!!!!
// � ������� ������ ������� ��'���� ���������� ��������� ���
// ������ � �����������, � ����� ����������� ������ � ������������
// ---
template <class Type>
class CSArray {
protected :
  uint   count; // ����������� �������
	uint   upper;
	uint16 delta;
	Type*  parr;

public :
	CSArray( uint i_max=0, uint16 i_delta=1 );
	CSArray( const CSArray<Type>& other );
	~CSArray() { delete [] (char *)(parr); parr = 0; count = 0;}

	uint16 Delta() const                                 { return delta; }
	void   Delta( uint16 newDelta )                      { delta = newDelta; }

  void   SetSize( uint newSize, bool clear=true );     // ������� ����� ������ �������
  void   Reserve( uint additionalSpace );              // ��������������� ����� ��� ��������
  void   Flush() { count = 0; }                        // �������� ���������� ���������
  void   HardFlush() { Flush(); Adjust(); }            // ���������� ��� ������
  void   Adjust();                                     // ������� ������ ������
  Type*  Add();                                        // �������� ������� � ����� �������
  Type*  AddItems( uint n );                           // �������� n ��������� � ����� �������
  Type*  Add(const Type& ent);                         // �������� ������� � ����� �������
  Type*  AddAt( const Type& ent, uint index )          { return InsertInd( index, ent ); }
  Type*  AddAfter( const Type& ent, uint index );      // �������� ������� ����� ����������
  Type*  InsertObj( const Type& index, const Type& ent ); // �������� ������� ����� ���������
  Type*  InsertInd( uint index, const Type& ent );        // �������� ������� ����� ���������
  void   RemoveInd( uint delIndex );                   // ������� ������� �� �������
  void   RemoveObj( const Type& delObject );           // ������� ������� �� �������
  void   Fill( uint fillCount, const Type& fillData ); // ��������� ������ ����������
  uint   FindIt( const Type& object ) const;           // ������� ������ �������� � �������
  bool   IsExist( const Type& object ) const;          // true ���� ������� ������
  uint   Count()    const { return count; }            // ���� ���������� ��������� �������
  int    MaxIndex() const { return count-1; }          // ���� ���������� ��������� �������

  CSArray<Type>& operator = ( const CSArray<Type>& o );
  CSArray<Type>& operator += ( const CSArray<Type>& o );
  Type& operator []( uint loc ) const { return parr[loc]; }

  typedef int (*CompFunc)( const Type *, const Type * );
	void   Sort( CompFunc comp );                        // ����������� ������

	Type	*GetAddr() { return parr; }	                   // ������ ����� ������ �������

protected :
	bool   CatchMemory();                                // ��������� ������

  #if _MSC_VER >= 1300
    template<class Type>
  #endif
  friend void  set_array_size( CSArray<Type>& to, uint newSize, bool clear );
  
  #if _MSC_VER >= 1300
    template<class Type>
  #endif
  friend Type* add_n_to_array( CSArray<Type>& to, uint n );

  #if _MSC_VER >= 1300
    template<class Type>
  #endif
  friend uint  find_in_array( const CSArray<Type>& arr, const Type& object );

  #if _MSC_VER >= 1300
    template<class Type>
  #endif
  friend void  fill_array( CSArray<Type>& arr, uint fillCount, const Type& fillData );

  #if _MSC_VER >= 1300
    template<class Type>
  #endif
  friend void  reserve_space( CSArray<Type>& arr, uint addSpace );
};


// ---
template <class Type>
class SBIterator {
  CSArray<Type>& array;
  uint          curr;
public:
  SBIterator( const CSArray<Type>& arr ) 
    : array( arr ),
      curr( arr.count-1 ) {
  }
  operator bool()        const { return curr != SYS_MAX_UINT; }
  operator Type&()       const { return array[curr]; }
  Type& operator --(int)       { return array[ ((bool)*this) ? curr-- : 0 ]; }
};



///////////////////////////////////////////////////////
// ������ � ������������ �-����
// ---
template <class Type>
class  SIArray : public CSArray<Type> {
public :
	SIArray( uint i_max=0, uint16 i_delta=1 )
		: CSArray<Type>( i_max, i_delta ) {}
	SIArray( const CSArray<Type>& other )
		: CSArray<Type>( other ) {}

	typedef void ( *IteratorFunc ) ( Type& obj );
	void   ForEach( IteratorFunc func ) const;

	typedef void ( *ParIteratorFunc ) ( Type& obj, void *pars );
	void   ForEach( ParIteratorFunc func, void *pars ) const;

	typedef bool ( *CompareFunc ) ( Type& obj, void *pars );
	uint   FirstThat( CompareFunc func, void *pars, uint from=0 ) const;
  
  friend void  for_each_in_array( const SIArray<Type>& arr, IteratorFunc func );
  friend void  for_each_in_array( const SIArray<Type>& arr, ParIteratorFunc func, void* pars );
  friend uint  first_that_in_array( const SIArray<Type>& arr, CompareFunc func, void* pars, uint from );
};



///////////////////////////////////////////////////////
// ����������� �������
// ---
template <class Type>
inline CSArray<Type>::CSArray( uint i_max, uint16 i_delta ) {
  count = 0;
	upper = 0;
	parr  = 0;
	delta = i_delta;
	SetSize( i_max );
}



///////////////////////////////////////////////////////
// ����������� ����������� �������
// ---
template <class Type>
inline CSArray<Type>::CSArray( const CSArray<Type>& o ) {
  count = o.count;
  upper = o.upper;
  delta = o.delta;
  parr  = !upper? 0 : (Type*)new char[ upper*sizeof(Type) ];
  if ( count ) {
    if ( count > upper )
      count = upper;
    memcpy( parr, o.parr, count*sizeof(Type) );
  }
}



///////////////////////////////////////////////////////
// ������� ����� ������ �������
// ���� clear != 0 ������ ���������
// ---
template <class Type>
inline void CSArray<Type>::SetSize( uint newSize, bool clear ) {
  set_array_size( *this, newSize, clear );
}




///////////////////////////////////////////////////////
// ��������������� ����� ��� n ���������
// ---
template <class Type>
inline void CSArray<Type>::Reserve( uint additionalSpace ) {
  reserve_space( *this, additionalSpace );
}


///////////////////////////////////////////////////////
// ������ �������������� �����
// ---
template <class Type>
inline void CSArray<Type>::Adjust() {
  if ( count < upper )
    SetSize( count, 0 );
}



///////////////////////////////////////////////////////
// �������� ������� � ����� �������
// � ������� ��������� �� ����
// --- !!!!!!!!!!!
template <class Type>
inline Type* CSArray<Type>::Add() {
  if ( CatchMemory() )
		return &parr[ count++ ];
	return (Type*)0;
}




///////////////////////////////////////////////////////
// �������� n ��������� � ����� �������
// � ������� ��������� �� ������ �����������
// --- 
template <class Type>
inline Type* CSArray<Type>::AddItems( uint n ) {
  return n ? add_n_to_array(*this,n) : 0;
}




///////////////////////////////////////////////////////
// �������� ������� � ����� �������
// ---
template <class Type>
inline Type* CSArray<Type>::Add( const Type& ent ) {
  if ( CatchMemory() )
		return (Type*)memcpy( parr+count++, &ent, sizeof(Type) );
	return (Type*)0;
}




///////////////////////////////////////////////////////
// �������� ������� ����� ���������
// ---
template <class Type>
inline Type* CSArray<Type>::AddAfter( const Type& ent, uint index ) {
  if ( CatchMemory() ) {
		memmove( parr+index+2, parr+index+1, sizeof(Type)*(count++-index-1) );
		return (Type*)memcpy( parr+index+1, &ent, sizeof(Type) );
	}
	return (Type*)0;
}




///////////////////////////////////////////////////////
// �������� ������� ����� ���������
// ---
template <class Type>
inline Type* CSArray<Type>::InsertInd( uint index, const Type& ent ) {
  if ( CatchMemory() ) {                             // �������� ������, ���� ��� ������������
		memmove( parr+index+1, parr+index, (count++-index) * sizeof(Type) );
																							 // ���������� ������ ��� �������� ������� � ���������� �� ����������
		return (Type*)memcpy( parr+index, &ent, sizeof(Type) );  // ���������� ����� �������
	}
	return (Type*)0;
}



///////////////////////////////////////////////////////
// �������� ������� ����� ���������
// ---
template <class Type>
inline Type* CSArray<Type>::InsertObj( const Type& ind, const Type& ent ) {
  uint index = FindIt(ind);
  if ( index != SYS_MAX_UINT )
    return InsertInd( index, ent );
  else
    return 0;
}



///////////////////////////////////////////////////////
// ������� ������ �������� � �������
// --- 
template <class Type>
inline uint CSArray<Type>::FindIt( const Type& object ) const {
  return find_in_array( *this, object );
}




///////////////////////////////////////////////////////
// true ���� ������� ������
// --- 
template <class Type>
inline bool CSArray<Type>::IsExist( const Type& object ) const {
  return find_in_array( *this, object ) != SYS_MAX_UINT;
}



///////////////////////////////////////////////////////
// ������� ������� �� �������
// ---
template <class Type>
inline void CSArray<Type>::RemoveObj( const Type& delObject ) {
  uint ind = FindIt( delObject );
  if ( ind != SYS_MAX_UINT )
    RemoveInd( ind );
}




///////////////////////////////////////////////////////
// ������� ������� �� �������
// ---
template <class Type>
inline void CSArray<Type>::RemoveInd( uint delIndex ) { 
  memcpy( parr+delIndex, parr+delIndex+1, (count-- - delIndex-1)*sizeof(Type) );
} 


///////////////////////////////////////////////////////
// ��������� ������ ����������
// ---
template <class Type>
inline void CSArray<Type>::Fill( uint fillCount, const Type& fillData ) {
  fill_array( *this, fillCount, fillData );
}




///////////////////////////////////////////////////////
// ���������� ������� �������
// ---
template <class Type>
inline CSArray<Type>& CSArray<Type>::operator = ( const CSArray<Type>& o ) {
  if ( upper < o.count ) {
    delete [] (char *)( parr );
    upper=o.count;
    parr = o.count ? (Type*)new char[ o.count * sizeof(Type) ] : 0;
  }
  count = o.count;
  memcpy( parr, o.parr, count * sizeof(Type) );
  return *this;
}




///////////////////////////////////////////////////////
// ���������� ������� �������
// ---
template <class Type>
inline CSArray<Type>& CSArray<Type>::operator += ( const CSArray<Type>& o ) {
  if ( upper < count + o.count ) {
    upper = uint16(count + o.count);
		Type* p_tmp = upper ? (Type*)new char[ upper * sizeof(Type) ] : 0;
		memcpy( p_tmp, parr, count * sizeof(Type) );
		delete [] (char *)( parr );
		parr = p_tmp;
  }
  memcpy( parr+count, o.parr, o.count * sizeof(Type) );
	count += o.count;
  return *this;
}




///////////////////////////////////////////////////////
// ������ �������� ����� ������ ( ���� ����� )
// ---
template <class Type>
inline bool CSArray<Type>::CatchMemory() {
	if (upper == count) {
    uint   cpy = upper;
		Type *p_tmp = (Type*)new char[ (upper+delta) * sizeof(Type) ];
		if ( p_tmp ) {
			upper+=delta;
			if ( parr ) {
				memcpy( p_tmp, parr, cpy * sizeof(Type) );
				delete [] (char *)( parr );
			}
			parr = p_tmp;
			return true;
		}
		return false;
  }
	return true;
}




///////////////////////////////////////////////////////
// ��������� ������� ��� ������� ��������
// ---
template <class Type>
inline void SIArray<Type>::ForEach( IteratorFunc func ) const {
  for_each_in_array( *this, func );
}




///////////////////////////////////////////////////////
// ��������� ������� � ����������� ��� ������� ��������
// ---
template <class Type>
inline void SIArray<Type>::ForEach( ParIteratorFunc func, void* pars ) const {
  for_each_in_array( *this, func, pars );
}




///////////////////////////////////////////////////////
// ����� ������� �� �������
// ---
template <class Type>
inline uint SIArray<Type>::FirstThat( CompareFunc func, void* pars, uint from ) const {
  return first_that_in_array( *this, func, pars, from );
}




///////////////////////////////////////////////////////
// ����������� ������
// --- !!!!!!!!!!
template <class Type>
inline void CSArray<Type>::Sort( CompFunc fcmp ) {
  typedef int (*QCompFunc)( const void*, const void* );
	qsort( (void *)parr, count, sizeof(Type), (QCompFunc)fcmp );
}


// ---
template <class Type>
void set_array_size( CSArray<Type>& arr, uint newSize, bool clear ) {
  if ( newSize != arr.upper ) {
    arr.upper = newSize;
    Type *p_tmp = newSize ? (Type*)new char[ newSize * sizeof(Type) ] : 0;
    if ( clear )
      arr.count = 0;
    else {
      arr.count = arr.count < newSize ? arr.count : newSize;
      if ( arr.count && arr.parr )
        memcpy( p_tmp, arr.parr, arr.count * sizeof(Type) );
    }
    delete [] (char *)( arr.parr );
    arr.parr = p_tmp;
  }
  else if ( clear )
    arr.count = 0;
}


// ---
template <class Type>
Type* add_n_to_array( CSArray<Type>& to, uint n ) {
  uint oc = to.count;
  to.count += n;
  if (to.upper < to.count ) {
    while( to.upper < to.count )
      to.upper += to.delta;
    Type *p_tmp = (Type*)new char[ to.upper * sizeof(Type) ];
    memcpy( p_tmp, to.parr, oc * sizeof(Type) );
    delete [] (char *)( to.parr );
    to.parr = p_tmp;
  }
  return &to.parr[oc];
}


// ---
template <class Type>
uint find_in_array( const CSArray<Type>& arr, const Type& object ) {
  Type* parr = (Type*)arr.parr;
  for( uint i=0; i<arr.count; i++,parr++ )
    if ( !memcmp( parr, &object, sizeof(Type) ) )
      return i;
  return SYS_MAX_UINT;
}


// ---
template <class Type>
void fill_array( CSArray<Type>& arr, uint fillCount, const Type& fillData ) {
  if ( arr.upper < fillCount ) {
    delete [] (char *)( arr.parr );
    arr.parr = (Type*)new char[ (arr.upper=fillCount) * sizeof(Type) ];
  }
  arr.count = fillCount;
  Type* parr = (Type*)arr.parr;
  for ( uint i=0; i<arr.count; i++,parr++ )
    memcpy( parr, &fillData, sizeof(Type) );
}


// ---
template <class Type>
#if _MSC_VER < 1300
void for_each_in_array( const SIArray<Type>& arr, SIArray<Type>::IteratorFunc func ) {
#else
void for_each_in_array( const SIArray<Type>& arr, typename SIArray<Type>::IteratorFunc func ) {
#endif
  Type* parr = (Type*)arr.parr;
	for( uint i=0; i<arr.count; i++,parr++ )
		func( *parr );
}


// ---
template <class Type>
#if _MSC_VER < 1300
void for_each_in_array( const SIArray<Type>& arr, SIArray<Type>::ParIteratorFunc func, void* pars ) {
#else
void for_each_in_array( const SIArray<Type>& arr, typename SIArray<Type>::ParIteratorFunc func, void* pars ) {
#endif
  Type* parr = (Type*)arr.parr;
	for( uint i=0; i<arr.count; i++,parr++ )
		func( *parr, pars );
}


// ---
template <class Type>
#if _MSC_VER < 1300
uint first_that_in_array( const SIArray<Type>& arr, SIArray<Type>::CompareFunc func, void* pars, uint from ) {
#else
uint first_that_in_array( const SIArray<Type>& arr, typename SIArray<Type>::CompareFunc func, void* pars, uint from ) {
#endif
  Type* parr = ((Type*)arr.parr) + from;
	for( uint i=from; i<arr.count; i++,parr++ ) {
		if ( func(*parr,pars) )
			return i;
	}
	return SYS_MAX_UINT;
}


// ---
template <class Type>
void reserve_space( CSArray<Type>& arr, uint additionalSpace ) {
  uint space = arr.upper - arr.count;
  if ( additionalSpace > space ) {
    additionalSpace -= space;
    arr.upper += additionalSpace;
    Type *p_tmp = (Type*)new char[ arr.upper * sizeof(Type) ];
    if ( arr.count && arr.parr )
      memcpy( p_tmp, arr.parr, arr.count * sizeof(Type) );
    delete [] (char *)( arr.parr );
    arr.parr = p_tmp;
  }
}



#endif  // __SARRAY_H

