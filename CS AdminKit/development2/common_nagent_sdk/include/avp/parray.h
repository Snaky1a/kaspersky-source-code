////////////////////////////////////////////////////////////////////
//
//  Parray.h
//  CPArray template
//  General purpose
//  Victor Matiouchenkov [victor@avp.ru], Kaspersky Labs. 1999
//  Copyright (c) Kaspersky Labs
//
////////////////////////////////////////////////////////////////////


#ifndef __PARRAY_H
#define __PARRAY_H

#include <stdlib.h>
#include <string.h>
//#include <memory.h>

#include <avp/stddefs.h>

#define SYS_MAX_UINT  (0xffffffff)

///////////////////////////////////////////////////////
// ���������� ������ ���������� �� �������
// ������ � �����������
// ---


#if defined(N_PLAT_NLM) || defined(__unix)
template <class Type> class  CPArray;


template <class Type> void destroy_rest_array( CPArray<Type>& arr, uint size );
template <class Type> void  destroy_array( CPArray<Type>& arr );
template <class Type> void destroy_rest_array( CPArray<Type>& arr, uint size );
template <class Type> void join_arrays( CPArray<Type>& to, CPArray<Type>& from );
template <class Type> void insert_array( CPArray<Type>& to, CPArray<Type>& from, uint index );
template <class Type> uint find_in_array( const CPArray<Type>& arr, const Type* el );


#endif

template <class Type>
class  CPArray {

public :
	typedef Type* TPtr;
protected :
  bool          owns;  // �������� ����� �������
	uint          count; // ����������� �������
  uint          upper;
  uint16        delta;
  TPtr*         parr;  // ������ ��������� �� ��������
  typedef CPArray<Type> _self_type;

public :

	CPArray();
	CPArray( uint i_upper, uint16 i_delta=1, bool shouldDelete=true );
	virtual ~CPArray();

	bool     OwnsElem() const                              { return owns; }
	void     OwnsElem( bool ownsEl )                       { owns = ownsEl; }

	uint16   Delta() const                                 { return delta; }
	void     Delta( uint16 newDelta )                      { delta = newDelta; }

	void     Add( Type* ent );                             // �������� ������� � ����� �������
	void     AddAt( Type *ent, uint index )                { Insert( index, ent ); }
  void     AddAfter(Type* ent, uint index );             // �������� ������� ����� ����������
	void     Add( CPArray<Type>& o );                       // �������� ������
  void     Add( CPArray<Type>& o, uint index );           // �������� ������ � �������
  void     Insert( uint index, Type *ent );              // �������� ������� ����� ���������
  void     EatAway( CPArray<Type>& o );                   // ������ ������
	void     EatAway( CPArray<Type>& o, uint index );       // ������ ������
  CPArray<Type>& operator +=( CPArray<Type>& o );          // �������� ������

	void     Flush( DelType = defDelete );                 // ������� ��� ��������
	void		 SetSize( uint size, DelType = defDelete);		 // ���������� ������
  void     Adjust();                                     // ������� ������ ������
	void     RemoveAll( DelType shdl = defDelete )            { Flush(shdl); } // ������� ��� �������� �������� ���������� ���������
  Type*    RemoveObj( Type *delObject, DelType=defDelete ); // ������� ������� �� �������
  Type*    RemoveInd( uint delIndex, DelType del=defDelete ); // ������� ������� �� �������
	void     DetachInd( uint delIndex );                      // ����������� ������� �� �������
	void     DetachObj( const Type *delObject );              // ����������� ������� �� �������

	uint     FindIt( const Type *el ) const;               // ����� ������� �� ���������
	bool     IsExist( const Type *el ) const;              // true ���� ������� ������
	uint     Count()    const { return count; }            // ���� ���������� ��������� �������
  int      MaxIndex() const { return count-1; }          // ���� ���������� ��������� �������

	Type*&   operator []( uint loc ) const                 { return parr[loc]; }

protected:
	bool     CatchMemory();                                // ��������� ������

private:
	CPArray( const CPArray<Type>& other );                   // ��������� !!!
	CPArray<Type>& operator =( const CPArray<Type>& o );     // ��������� !!!

#if defined(_MSC_VER) //|| defined(N_PLAT_NLM) // not all compilers support explicit template function
        friend void destroy_array( CPArray<Type>& arr );
	friend void destroy_rest_array( CPArray<Type>& arr, uint size );
        friend void join_arrays( CPArray<Type>& to, CPArray<Type>& from );
        friend void insert_array( CPArray<Type>& to, CPArray<Type>& from, uint index );
        friend uint find_in_array( const CPArray<Type>& arr, const Type* el );
#else // may be need more customization...
        friend void destroy_array<Type>( CPArray<Type>& arr );
	friend void destroy_rest_array<Type>( CPArray<Type>& arr, uint size );
        friend void join_arrays<Type>( CPArray<Type>& to, CPArray<Type>& from );
        friend void insert_array<Type>( CPArray<Type>& to, CPArray<Type>& from, uint index );
        friend uint find_in_array<Type>( const CPArray<Type>& arr, const Type* el );
#endif
};

#ifdef N_PLAT_NLM
template <class Type>
void destroy_rest_array( CPArray<Type>& arr, uint size )
{
  typedef typename CPArray<Type>::TPtr _t_ptr;

  uint i = size;
  for( _t_ptr* parr=arr.parr + size; i<arr.count; i++,parr++ ) {
    delete *parr;
    *parr = 0;
  }  
  arr.count = size;
}
#endif

// ---
template <class Type>
class PBIterator {
  CPArray<Type>& array;
  uint          curr;
public:
  PBIterator( const CPArray<Type>& arr ) 
    : array( arr ),
      curr( arr.count-1 ) {
  }
  operator bool()        const { return curr != SYS_MAX_UINT; }
  operator Type*()       const { return array[curr]; }
  Type* operator --()          { --curr; return ((bool)*this) ? array[ curr ] : 0; }
  Type* operator --(int)       { return ((bool)*this) ? array[ curr-- ] : 0; }
};



///////////////////////////////////////////////////////
// ������ � ������������ �-����
// ---
template <class Type>
class  CPIArray : virtual public CPArray<Type> {
public :
	CPIArray()
		: CPArray<Type>() {}
	CPIArray( uint i_upper, uint16 i_delta=1, bool shouldDelete=true )
		: CPArray<Type>( i_upper, i_delta, shouldDelete ) {}

	typedef void ( *IteratorFunc ) ( Type* );
	void   ForEachI( IteratorFunc func ) const;

	typedef void ( *ParIteratorFunc ) ( Type*, void* );
	void   ForEachI( ParIteratorFunc func, void* ) const;

	typedef bool ( *CompareFunc ) ( Type*, void* );
	uint   FirstThatI( CompareFunc func, void* pars, uint from=0 ) const;

#if defined(_MSC_VER) || defined(N_PLAT_NLM) || defined(__unix) // not all compilers support explicit template function
  friend void  for_each_in_array( const CPIArray<Type>& arr, IteratorFunc func );
  friend void  for_each_in_array( const CPIArray<Type>& arr, ParIteratorFunc func, void* pars );
  friend uint  first_that_in_array( const CPIArray<Type>& arr, CompareFunc func, void* pars, uint from );
#else // may be need more customization
  friend void  for_each_in_array<Type>( const CPIArray<Type>& arr, IteratorFunc func );
  friend void  for_each_in_array<Type>( const CPIArray<Type>& arr, ParIteratorFunc func, void* pars );
  friend uint  first_that_in_array<Type>( const CPIArray<Type>& arr, CompareFunc func, void* pars, uint from );
#endif
};


///////////////////////////////////////////////////////
// ������ � ������������ �-����, ������� �������
// ---
template <class Type>
class  CPMIArray : virtual public CPArray<Type> {
public :
	CPMIArray()
		: CPArray<Type>() {}
	CPMIArray( uint i_upper, uint16 i_delta=1, uint8 shouldDelete=1 )
		: CPArray<Type>( i_upper, i_delta, shouldDelete ) {}

	typedef void ( Type::*IteratorMemFunc ) (void);
	void   ForEach( IteratorMemFunc func ) const;

	typedef void ( Type::*ParIteratorMemFunc ) (void *pars);
	void   ForEach( ParIteratorMemFunc func, void *pars ) const;

	typedef bool ( Type::*CompareMemFunc ) (void *pars);
	uint   FirstThat( CompareMemFunc func, void *pars, uint from=0 ) const;

#if defined(_MSC_VER) || defined(N_PLAT_NLM) || defined(__unix)  // add version
  friend void  for_each_in_array( const CPMIArray<Type>& arr, IteratorMemFunc func );
  friend void  for_each_in_array( const CPMIArray<Type>& arr, ParIteratorMemFunc func, void* pars );
  friend uint  first_that_in_array( const CPMIArray<Type>& arr, CompareMemFunc func, void* pars, uint from );
#else // may be need more customization
  friend void  for_each_in_array<Type>( const CPMIArray<Type>& arr, IteratorMemFunc func );
  friend void  for_each_in_array<Type>( const CPMIArray<Type>& arr, ParIteratorMemFunc func, void* pars );
  friend uint  first_that_in_array<Type>( const CPMIArray<Type>& arr, CompareMemFunc func, void* pars, uint from );
#endif
};



///////////////////////////////////////////////////////
// ������ �� ������� ������������ �-����, ��� ������� ��� � �� �������
// ---
template <class Type>
class  PMIIArray : public CPIArray<Type>, public CPMIArray<Type> {
public :
	PMIIArray()
		: CPArray<Type>(), CPIArray<Type>(), CPMIArray<Type>() {}
	PMIIArray( uint i_upper, uint16 i_delta=1, uint8 shouldDelete=1 )
		: CPArray<Type>( i_upper, i_delta, shouldDelete ), CPIArray<Type>(), CPMIArray<Type>() {}
};



///////////////////////////////////////////////////////
// ����������� �������
// ---
template <class Type>
inline CPArray<Type>::CPArray()
  : owns( true ),
    count( 0 ),
    upper( 0 ),
    delta( 1 ),
    parr( 0 ) {
}




///////////////////////////////////////////////////////
// ����������� �������
// ---
template <class Type>
inline CPArray<Type>::CPArray( uint i_upper, uint16 i_delta, bool shouldDelete )
  : owns( shouldDelete ),
    count( 0 ),
    upper( i_upper ),
    delta( i_delta ),
    parr( i_upper ? new TPtr[i_upper] : 0 ) {
}




///////////////////////////////////////////////////////
// ���������� �������
// ---
template <class Type>
inline CPArray<Type>::~CPArray() {
  if ( owns )
    destroy_array( *this );
  delete [] parr;
	parr = 0;
}




///////////////////////////////////////////////////////
// �������� ���������� ���������
// ---
template <class Type>
inline void CPArray<Type>::Flush( DelType del ) {
	if ( del==Delete || (del==defDelete && owns) )
    destroy_array( *this );
  else
    count = 0;
}



///////////////////////////////////////////////////////
// ���������� ���������� ���������
// ---
template <class Type>
inline void CPArray<Type>::SetSize( uint size, DelType del ) {
	if ( size <= count ) {
		if ( del==Delete || (del==defDelete && owns) )
			destroy_rest_array<Type>( *this, size );
		count = size;
	}
}



///////////////////////////////////////////////////////
// ������� ������ ������
// ---
template <class Type>
inline void CPArray<Type>::Adjust() {
  if ( count < upper ) {
    TPtr* p_tmp = ((upper = count) > 0) ? (TPtr*)memcpy(new TPtr[upper],parr,upper*sizeof(TPtr)) : 0;
    delete [] parr;
    parr = p_tmp;
  }
}



///////////////////////////////////////////////////////
// �������� ������� � ����� �������
// ---
template <class Type>
inline void CPArray<Type>::Add( Type* ent ) {
  if ( CatchMemory() )
		parr[count++] = ent;
}




///////////////////////////////////////////////////////
// �������� ������� ����� ���������
// ---
template <class Type>
inline void CPArray<Type>::AddAfter( Type* ent, uint index ) {
  if ( CatchMemory() ) {    // �������� ������, ���� ��� ������������
		if ( ((int)index) > ((int)(count-1)) )
			index = count - 1;
		if ( count ) {
			// ���������� ������ ��� �������� ������� � index+1 �� ����������
			memmove( parr+index+2, parr+index+1, (count-index-1)*sizeof(TPtr) ); 
		}
		parr[ index+1 ] = ent; // ���������� ����� �������
		count++;
	}
}


///////////////////////////////////////////////////////
// �������� ������
// � ����������� �� �������� ��-���� � ���������
// ������� �������� � ��������� ����� ����������
// ---
template <class Type>
inline void CPArray<Type>::Add( CPArray<Type>& o ) {
  join_arrays( *this, o );
}



///////////////////////////////////////////////////////
// �������� ������ � ������� index
// (���� index>count, �� � �����)
// � ����������� �� �������� ��-���� � ���������
// ������� �������� � ��������� ����� ����������
// ---
template <class Type>
inline void CPArray<Type>::Add( CPArray<Type>& o, uint index ) {
  insert_array( *this, o, index );
}




///////////////////////////////////////////////////////
// �������� ������� ����� ���������
// ---
template <class Type>
inline void CPArray<Type>::Insert( uint index, Type *ent ) {
  if ( CatchMemory() ) {         // �������� ������, ���� ��� ������������
		if ( index > count )
			index = count;
		memmove( parr+index+1, parr+index, (count-index) * sizeof(TPtr) );
													 // ���������� ������ ��� �������� ������� � ���������� �� ����������
		parr[index] = ent;     // ���������� ����� �������
		count++;
	}
}




///////////////////////////////////////////////////////
// ������ ������
// ---
template <class Type>
inline void CPArray<Type>::EatAway( CPArray<Type>& o ) {
  Add( o );  // ������ ���� 'o.owns'
  o.count = 0;
}





///////////////////////////////////////////////////////
// ������ ������
// ---
template <class Type>
inline void CPArray<Type>::EatAway( CPArray<Type>& o, uint index ) {
  Add( o, index );  // ������ ���� 'o.owns'
  o.count = 0;
}





///////////////////////////////////////////////////////
// ����������� ���� ������ � ������
// � ���������� �� �������� �������� ����������
// ������� ���������, ��������� ����� ������������
// ��� ������������
// ---
template <class Type>
inline CPArray<Type>& CPArray<Type>::operator += ( CPArray<Type>& o ) {
  Add( o );
  return *this;
}




///////////////////////////////////////////////////////
// ������� ������ �������� � �������
// ---
template <class Type>
inline uint CPArray<Type>::FindIt( const Type *el ) const {
  return find_in_array( *this, el );
}



///////////////////////////////////////////////////////
// ������� ������ �������� � �������
// ---
template <class Type>
inline bool CPArray<Type>::IsExist( const Type *el ) const {
  return find_in_array( *this, el ) != SYS_MAX_UINT;
}



///////////////////////////////////////////////////////
// ������� ������� �� �������
// ---
template <class Type>
inline Type* CPArray<Type>::RemoveInd( uint delIndex, DelType del ) {
  TPtr* d = parr + delIndex;
  TPtr  r = (del==Delete || (del==defDelete && owns)) ? (delete *d,(TPtr)0) : *d;
  memcpy( d, d+1, (count-- - delIndex - 1)*sizeof(TPtr) );
  return r;
}




///////////////////////////////////////////////////////
// ������� ������� �� �������
// ---
template <class Type>
inline Type* CPArray<Type>::RemoveObj( Type *delObject, DelType del ) {
  uint i = find_in_array( *this, delObject );
  return ( i != SYS_MAX_UINT ) ? RemoveInd(i,del) : 0;
}




///////////////////////////////////////////////////////
// ����������� ������� �� �������
// ---
template <class Type>
inline void CPArray<Type>::DetachInd( uint delIndex ) {
  memcpy( parr+delIndex, parr+delIndex+1, (count-- - delIndex - 1)*sizeof(TPtr) );
}




///////////////////////////////////////////////////////
// ����������� ������� �� �������
// ---
template <class Type>
inline void CPArray<Type>::DetachObj( const Type *delObject ) {
  uint i = find_in_array( *this, delObject );
  if ( i != SYS_MAX_UINT )
    DetachInd( i );
}





///////////////////////////////////////////////////////
// ������ �������� ����� ������ ( ���� ����� )
// ---
template <class Type>
inline bool CPArray<Type>::CatchMemory() {
	if ( upper == count ) {
    uint size = upper;
		TPtr* p_tmp = new TPtr[upper+delta];
		if ( p_tmp ) {
			upper+=delta;
			if ( parr )	{
				memcpy( p_tmp, parr, size*sizeof(TPtr) );
				delete [] parr;
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
inline void CPIArray<Type>::ForEachI( IteratorFunc func ) const {
  for_each_in_array( *this, func );
}



///////////////////////////////////////////////////////
// ��������� ������� � ����������� ��� ������� ��������
// ---
template <class Type>
inline void CPIArray<Type>::ForEachI( ParIteratorFunc func, void *pars ) const {
  for_each_in_array( *this, func, pars );
}



///////////////////////////////////////////////////////
// ����� ������� �� �������
// ---
template <class Type>
inline uint CPIArray<Type>::FirstThatI( CompareFunc func, void* pars, uint from ) const {
  return first_that_in_array( *this, func, pars, from );
}




///////////////////////////////////////////////////////
// ��������� ������� ��� ������� ��������
// ---
template <class Type>
inline void CPMIArray<Type>::ForEach( IteratorMemFunc func ) const {
  for_each_in_array( *this, func );
}



///////////////////////////////////////////////////////
// ��������� ������� � ����������� ��� ������� ��������
// ---
template <class Type>
inline void CPMIArray<Type>::ForEach( ParIteratorMemFunc func, void *pars ) const {
  for_each_in_array( *this, func, pars );
}



///////////////////////////////////////////////////////
// ����� ������� �� �������
// ---
template <class Type>
inline uint CPMIArray<Type>::FirstThat( CompareMemFunc func, void *pars, uint from ) const {
  return first_that_in_array( *this, func, pars, from );
}


// ---
template <class Type>
void destroy_array( CPArray<Type>& arr ) {
  typedef typename CPArray<Type>::TPtr _t_ptr;
  uint i = 0;
  for( _t_ptr* parr=arr.parr; i<arr.count; i++,parr++ ) {
    delete *parr;
    *parr = 0;
  }  
  arr.count = 0;
}



// ---
#ifndef N_PLAT_NLM

template <class Type>
void destroy_rest_array( CPArray<Type>& arr, uint size )
{
  typedef typename CPArray<Type>::TPtr _t_ptr;

  uint i = size;
  for( _t_ptr* parr=arr.parr + size; i<arr.count; i++,parr++ ) {
    delete *parr;
    *parr = 0;
  }  
  arr.count = size;
}
#endif


// ---
template <class Type>
void join_arrays( CPArray<Type>& to, CPArray<Type>& from )
{
  typedef typename CPArray<Type>::TPtr _t_ptr;

  uint newUpper;
  uint newCount = to.count + from.count;

  for( newUpper=to.upper; newUpper<newCount; newUpper+=to.delta );
  if ( newUpper > to.upper ) {
    _t_ptr* p_tmp = (_t_ptr*)memcpy( new _t_ptr[ to.upper = newUpper ], to.parr, to.count * sizeof(_t_ptr) );
    delete [] to.parr;
    to.parr = p_tmp;
  }
  memcpy( to.parr+to.count, from.parr, from.count * sizeof(_t_ptr) );
  to.count = newCount;

  if ( to.owns )
    from.owns = 0;
}



// ---
template <class Type>
void insert_array( CPArray<Type>& to, CPArray<Type>& from, uint index )
{
  typedef typename CPArray<Type>::TPtr _t_ptr;

	if ( index > to.count )
		index = to.count;

  uint newUpper;
  uint newCount = to.count + from.count;
                                 
  for( newUpper=to.upper; newUpper < newCount; newUpper+=to.delta );
  _t_ptr* p_tmp = new _t_ptr[ to.upper = newUpper ];
  memcpy( p_tmp,                  to.parr,       index * sizeof(_t_ptr) );
  memcpy( p_tmp+index,            from.parr,     from.count * sizeof(_t_ptr) );
  memcpy( p_tmp+index+from.count, to.parr+index, (to.count-index) * sizeof(_t_ptr) );

  delete [] to.parr;
  to.parr = p_tmp;
  to.count = newCount;

  if ( to.owns )
		from.owns = 0;
}



// ---
template <class Type>
uint find_in_array( const CPArray<Type>& arr, const Type* el ) {
  typename CPArray<Type>::TPtr* parr = arr.parr;

  for( uint i=0,c=arr.count; i<c; i++,parr++ )
    if ( *parr == el )
      return i;
  return SYS_MAX_UINT;
}



// ---
template <class Type>
void for_each_in_array( const CPIArray<Type>& arr, void ( *func ) ( Type* ) ) {
  typename CPArray<Type>::TPtr* parr = arr.parr;
	for( uint i=0,c=arr.count; i<c; i++,parr++ )
		func( *parr );
}


// ---
template <class Type>
void for_each_in_array( const CPIArray<Type>& arr, void ( *func ) ( Type*,void* ), void* pars ) {
  typename CPArray<Type>::TPtr* parr = arr.parr;
	for( uint i=0,c=arr.count; i<c; i++,parr++ )
		func( *parr, pars );
}


// ---
template <class Type>
uint first_that_in_array( const CPIArray<Type>& arr, bool ( *func ) ( Type*,void* ), void* pars, uint from ) {
  typename CPArray<Type>::TPtr* parr = arr.parr+from;
	for( uint i=from; i<arr.count; i++,parr++ ) {
		if ( func( *parr, pars ) )
			return i;
	}
	return SYS_MAX_UINT;
}



// ---
template <class Type>
void for_each_in_array( const CPMIArray<Type>& arr, void ( Type::*func ) (void) ) {
  typename CPArray<Type>::TPtr* parr = arr.parr;
	for( uint i=0; i<arr.count; i++,parr++ )
		((*parr)->*func)();
}


// ---
template <class Type>
void for_each_in_array( const CPMIArray<Type>& arr, void ( Type::*func ) (void *), void* pars ) {
  typename CPArray<Type>::TPtr* parr = arr.parr;
	for( uint i=0; i<arr.count; i++,parr++ )
		((*parr)->*func)( pars );
}


// ---
template <class Type>
uint first_that_in_array( const CPMIArray<Type>& arr, bool ( Type::*func ) (void *), void* pars, uint from ) {
  typename CPArray<Type>::TPtr* parr = arr.parr + from;
	for( uint i=from; i<arr.count; i++,parr++ ) {
		if ( ((*parr)->*func)(pars) )
			return i;
	}
	return SYS_MAX_UINT;
}


#endif  // __PARRAY_H


// Local Variables:
// mode: C++
// End:
