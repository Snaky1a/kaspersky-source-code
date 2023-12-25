////////////////////////////////////////////////////////////////////
//
//  Parray.h
//  CSList template
//  General purpose
//  Andrey Doukhvalov [petrovitch@avp.ru], Kaspersky Labs. 1999
//  Victor Matiouchenkov [victor@avp.ru], Kaspersky Labs. 1999
//  Copyright (c) Kaspersky Labs
//
////////////////////////////////////////////////////////////////////

#ifndef __SLIST_H
#define __SLIST_H

#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#ifndef _INC_MEMORY
#include <memory.h>
#endif

#include "StdDefs.h"

///////////////////////////////////////////////////////
// ������� ������
// ---
template <class Type>
class  CPListItem {
public:
  CPListItem<Type>* next;                       // ��������� �� ��������� �������
	Type*           data;                       // ��������� �� ���� ������

	CPListItem()                                  { next = 0; data = 0; }
	CPListItem( Type* d )                         { next = 0; data = d; }
	CPListItem( Type* d, CPListItem<Type>* prev );  // �������� ���� ����� ��������� ��������
};


template <class Type>
class  CPLIterator;

///////////////////////////////////////////////////////
// ������ ���������� �� ��������
// ---
template <class Type>
class  CPList {
public:

	CPList( bool ownsEl = true )                           { owns = ownsEl; first = last = 0; count=0; }
	~CPList()                                              { Remove(); }

	bool   OwnsElem() const                              { return owns; }
	void   OwnsElem( bool ownsEl )                       { owns = ownsEl; }

	void   Add( Type* data );                            // �������� ������� � ����� ������
  void   Add( Type* data, const Type* after );         // �������� ������� ����� ��������� ��������
  void   Add( Type* data, bool check );                // �������� ������� � ����� ������ � ��������� �� �������������
  void   Add( CPListItem<Type>* item );                  // �������� ������� � ����� ������
  void   Add( CPList<Type>& list );                      // �������� ������ list � ����� ������� ������
	void   AddAndEat( CPList<Type>& list );                // ������ ������ list � ����� ������� ������

	void   Insert( Type* data );                         // �������� ������� � ������ ������
	void   Insert( CPListItem<Type>* item );               // �������� ������� � ������ ������
	void   Insert( CPList<Type>& list );                   // �������� ������ list � ������ ������� ������
	void   InsertAndEat( CPList<Type>& list );             // ������ ������ list � ������ ������� ������

	void   Flush( DelType shdl=defDelete )               { Remove( shdl ); }  // ������� ��� �������� ������
	void   Remove( DelType shdl=defDelete );             // ������� ��� �������� ������
	bool   Remove( Type* del, DelType=defDelete );       // ������� ���� ������� ������
	uint32 Remove( CPList<Type>& del, DelType=defDelete ); // ������� ��� �������� ������������� ������ del
	bool   Detach( const Type* del );                    // ����������� ���� ������� ������
	uint32 Detach( CPList<Type>& del );                    // ����������� �� ������ ������ ������ ���������

	CPList<Type>* Break( CPListItem<Type>* curr );           // ������� ������ �� ��� ������

	void  Close();                                       // �������� ������
	void  Split();                                       // ���������� ������

	uint32 Count()    const { return count;      }       // ���� ���������� ��������� � ������
	uint32 ReCalc();                                     // ����������� ���������� ��������� � ������
	bool   IsEmpty () const { return first == 0; }       // ���������, ������ �� ������

	bool   IsExist( const Type* ) const;                 // ����� ������� �� ��������� ����������

	Type*  GetFirstData() const { return first->data; }  // �������� ������ ������� �������� ������
	Type*  GetLastData()  const { return last->data; }   // �������� ������ ���������� �������� ������

protected :
	friend class  CPLIterator<Type>;

	bool            owns;                                // ������� �������� ����������
	uint32          count;                               // ���-�� ��-��� � ������
	CPListItem<Type>* first;                               // ��������� �� ������ ������� � ������
	CPListItem<Type>* last;                                // ��������� �� ��������� ������� � ������

private :
	CPListItem<Type>* findPrev( CPListItem<Type>* now );

	CPList( const CPList<Type>& other );                     // ��������� !!!
	void operator = ( const CPList<Type>& other );         // ��������� !!!
#if _MSC_VER > 1300
  template<typename U> friend void   add_to_list( CPList<U>& to, CPList<U>& from );
  template<typename U> friend void   add_to_list( CPList<U>& list, Type* data, const Type* after );
  template<typename U> friend void   insert_to_list( CPList<U>& to, CPList<U>& from );
  template<typename U> friend void   remove_from_list( CPList<U>& list, DelType shdl );
  template<typename U> friend uint32 remove_from_list( CPList<U>& from, CPList<U>& deList, DelType shdl );
  template<typename U> friend bool   detach_from_list( CPList<U>& from, const Type* del );
  template<typename U> friend uint32 recalc_list( CPList<U>& list );
  template<typename U> friend uint32 is_exist_in_list( const CPList<U>& list, const U* what );
  template<typename U> friend CPListItem<U>* find_prev_in_list( const CPList<U>& list, CPListItem<U>* now );
  template<typename U> friend void   insert_to_iter( CPLIterator<U>& iter, CPList<U>& l );
#else
  friend void   add_to_list( CPList<Type>& to, CPList<Type>& from );
  friend void   add_to_list( CPList<Type>& list, Type* data, const Type* after );
  friend void   insert_to_list( CPList<Type>& to, CPList<Type>& from );
  friend void   remove_from_list( CPList<Type>& list, DelType shdl );
  friend uint32 remove_from_list( CPList<Type>& from, CPList<Type>& deList, DelType shdl );
  friend bool   detach_from_list( CPList<Type>& from, const Type* del );
  friend uint32 recalc_list( CPList<Type>& list );
  friend uint32 is_exist_in_list( const CPList<Type>& list, const Type* what );
  friend CPListItem<Type>* find_prev_in_list( const CPList<Type>& list, CPListItem<Type>* now );
  friend void   insert_to_iter( CPLIterator<Type>& iter, CPList<Type>& l );
#endif
};




///////////////////////////////////////////////////////
// �������� ������
// ---
template <class Type>
class  CPLIterator {
protected :
  CPList<Type>*     list;
  CPListItem<Type>* curr;
public:
	CPLIterator()                                       { list=0; curr=0; }
	CPLIterator( const CPList<Type>& l )                  { Set(l); }
	CPLIterator( const CPLIterator<Type>& i )             { list = i.list; curr = i.curr; }
	void  Set( const CPList<Type>& l )                  { list=(CPList<Type>*)&l; Restart(); }
  CPLIterator<Type>& operator =( const CPList<Type>& l ){ Set(l); return* this; }
  CPLIterator<Type>& operator =( const CPLIterator<Type>& o ){ list=o.list; curr = o.curr; return* this; }
  void  Restart()                                   { curr = list->first; }
  Type* GetData()                             const { return curr ? curr->data : 0; }
  Type* GetDataAndGo();                             // ����� ������ � ���������� ��������
  CPList<Type>*     GetList()                   const { return list; }

	Type& operator*   ()                        const { return* curr->data; }
	Type* operator () ()                        const { return curr ? curr->data : 0; }
        operator CPListItem<Type>* ()           const { return curr; }
        operator CPListItem<Type>& ()           const { return* curr; }
  Type* operator ++()                               { if(curr) {curr=curr->next; return curr ? curr->data : 0;} else return 0; }
  Type* operator ++(int)                            { if(curr) {Type* ret=curr->data; curr=curr->next; return ret;} else return 0; }
	Type* operator --()                               { curr=list->findPrev(curr); return curr ? curr->data : 0; }
  Type* operator --(int)                            { if(curr) {Type* ret=curr->data; curr=list->findPrev(curr); return ret;} else return 0; }
	Type* operator ->()                               { return curr ? curr->data : 0; }
  bool  operator ==(const CPLIterator<Type>& o) const { return list==o.list && curr==o.curr; }
  bool  operator !=(const CPLIterator<Type>& o) const { return !operator==(o); }

  void  Add( Type* data );                          // �������� ������� ����� ��������� ��������
  void  Add( Type* data, bool check );              // �������� ������� ����� ��������� �������� � ��������� �� �������������
  void  Add( CPLIterator<Type>& item );               // �������� ������� ����� ��������� ��������
	void  Add( CPList<Type>& list );                    // �������� list ����� ��������� ��������
	void  AddAndEat( CPList<Type>& list );              // ������ list ����� ��������� ��������

	void  Insert( Type* data );                       // �������� ������� ����� �������� ���������
	void  Insert( CPLIterator<Type>& item);             // �������� ������� ����� �������� ���������
	void  Insert( CPList<Type>& list );                 // �������� list ����� �������� ���������
	void  InsertAndEat( CPList<Type>& list );           // ������ list ����� �������� ���������

	void  Remove( DelType = defDelete );              // ������� ������� ������ � ���������� ������
	void  Detach();                                   // ����������� ������� ������

	bool  IsOK()                                const { return curr != 0; }
	CPListItem<Type>* Next()                      const { return curr->next; }
	void  Go()                                        { if(curr) curr = curr->next; }
	void  GoLast()                                    { curr = list->last; }

	bool  IsFirst()                             const { return curr == list->first; }
	bool  IsLast()                              const { return curr == list->last; }
#if _MSC_VER > 1300
  template<typename U> friend void add_to_iter( CPLIterator<U>& iter, CPList<U>& l );
  template<typename U> friend void insert_to_iter( CPLIterator<U>& iter, CPList<U>& l );
#else
  friend void add_to_iter( CPLIterator<Type>& iter, CPList<Type>& l );
  friend void insert_to_iter( CPLIterator<Type>& iter, CPList<Type>& l );
#endif
};



///////////////////////////////////////////////////////
// ������ ���������� �� �������� � �-���� ��������
// ---
template <class Type>
class  CPIList : virtual public CPList<Type> {
public :
	CPIList( bool ownsEl = true )
		: CPList<Type>( ownsEl ) {}

	typedef void (*IterType1) ( Type* );
	void  ForEachI( IterType1 iFunc ) const;       // ��������� ������� ��� ������� �������� IterType1

	typedef void (*IterType2) ( Type*, void* );
	void  ForEachI( IterType2 iFunc, void* args ) const; // ��������� ������� ��� ������� �������� IterType2 � �����������

	typedef bool (*CompType) ( Type*, void* );
	Type* FirstThatI( CompType cFunc, void* ) const;// ����� ������� �� �������
#if _MSC_VER > 1300
  template<typename U> friend void  for_each_in_list( const CPIList<U>& list, IterType1 iFunc );
  template<typename U> friend void  for_each_in_list( const CPIList<U>& list, IterType2 iFunc, void* args );
  template<typename U> friend U* first_that_in_list( const CPIList<U>& list, CompType cFunc, void* args );
#else
  friend void  for_each_in_list( const CPIList<Type>& list, IterType1 iFunc );
  friend void  for_each_in_list( const CPIList<Type>& list, IterType2 iFunc, void* args );
  friend Type* first_that_in_list( const CPIList<Type>& list, CompType cFunc, void* args );
#endif
};



///////////////////////////////////////////////////////
// ������ ���������� �� �������� � ��������� �-���� ��������
// ---
template <class Type>
class  CPMIList : virtual public CPList<Type> {
public :
	CPMIList( bool ownsEl = true )
		: CPList<Type>( ownsEl ) {}

	typedef void (Type::*IterMemType1) ();
	void  ForEach( IterMemType1 iFunc ) const;       // ��������� ������� ��� ������� �������� IterMemType1

	typedef void (Type::*IterMemType2) (void*);
	void  ForEach( IterMemType2 iFunc, void* args ) const; // ��������� ������� ��� ������� �������� IterMemType2 � �����������

	typedef bool  (Type::*CompMemType) (void* );
	Type* FirstThat( CompMemType cFunc, void* ) const;// ����� ������� �� �������

#if _MSC_VER > 1300
  template<typename U> friend void  for_each_in_list( const CPMIList<U>& list, IterMemType1 iFunc );
  template<typename U> friend void  for_each_in_list( const CPMIList<U>& list, IterMemType2 iFunc, void* args );
  template<typename U> friend U* first_that_in_list( const CPMIList<U>& list, CompMemType cFunc, void* args );
#else
  friend void  for_each_in_list( const CPMIList<Type>& list, IterMemType1 iFunc );
  friend void  for_each_in_list( const CPMIList<Type>& list, IterMemType2 iFunc, void* args );
  friend Type* first_that_in_list( const CPMIList<Type>& list, CompMemType cFunc, void* args );
#endif
};



///////////////////////////////////////////////////////
// ������ ���������� �� �������� � ��������� � �� ��������� �-���� ��������
// ---
template <class Type>
class  CMIIList : public CPIList<Type>, public CPMIList<Type> {
public :
	CMIIList( bool ownsEl = 1 )
		: CPList<Type>(ownsEl), CPIList<Type>(), CPMIList<Type>() {}
};



///////////////////////////////////////////////////////
// �������� ������, ���������� �������� ��������
// ---
template <class Type>
class  CPILIterator : virtual public CPLIterator<Type> {
public :
	CPILIterator()
		: CPLIterator<Type>() {}
	CPILIterator( const CPList<Type>& l )
		: CPLIterator<Type>(l) {}
	CPILIterator( const CPLIterator<Type>& i )
		: CPLIterator<Type>( i ) {}

	typedef bool (*CondType)(Type*,void*);
	bool GoI( CondType f, void* arg );                // ����� ������� ��������������� �������
#if _MSC_VER > 1300
	template<typename U> friend bool go_iter( CPILIterator<U>& iter, typename CPILIterator<U>::CondType f, void* arg );
#else
  friend bool go_iter( CPILIterator<Type>& iter, CPILIterator<Type>::CondType f, void* arg );
#endif
};



///////////////////////////////////////////////////////
// �������� ������, ���������� �������� �������� ��������
// ---
template <class Type>
class  CPMILIterator : virtual public CPLIterator<Type> {
public :
	CPMILIterator()
		: CPLIterator<Type>() {}
	CPMILIterator( const CPList<Type>& l )
		: CPLIterator<Type>(l) {}
	CPMILIterator( const CPLIterator<Type>& i )
		: CPLIterator<Type>( i ) {}

	typedef bool (Type::*CondMemType)(void* arg);
	bool Go( CondMemType f, void* arg );                // ����� ������� ��������������� �������
#if _MSC_VER > 1300
	template<typename U> friend bool go_iter( CPMILIterator<U>& iter, typename CPILIterator<U>::CondMemType f, void* arg );
#else
  friend bool go_iter( CPMILIterator<Type>& iter, CPILIterator<Type>::CondMemType f, void* arg );
#endif
};



///////////////////////////////////////////////////////
// �������� ������, ���������� �������� � �� ������� ��������� ��������
// ---
template <class Type>
class  CPMIILIterator : public CPILIterator<Type>, public CPMILIterator<Type> {
public :
	CPMIILIterator()
		: CPLIterator<Type>(), CPILIterator<Type>(), CPMILIterator<Type>() {}
	CPMIILIterator( const CPList<Type>& l )
		: CPLIterator<Type>(l), CPILIterator<Type>(), CPMILIterator<Type>() {}
	CPMIILIterator( const CPLIterator<Type>& i )
		: CPLIterator<Type>( i ), CPILIterator<Type>(), CPMILIterator<Type>() {}
};



///////////////////////////////////////////////////////
// ��������� ���� ����� item
// ---
template <class Type>
inline CPListItem<Type>::CPListItem( Type* d, CPListItem<Type>* item )  {
	next = item->next;
	item->next = this;
	data = d;
}



///////////////////////////////////////////////////////
// �������� ������� � ����� ������
// ---
template <class Type>
inline void CPList<Type>::Add( Type* data ) {
	if ( first )
		last = new CPListItem<Type>( data, last );
	else
		first = last = new CPListItem<Type>( data );
	count++;
}




///////////////////////////////////////////////////////
// �������� ������� ����� ��������� ��������
// ---
template <class Type>
inline void CPList<Type>::Add( Type* data, const Type* after ) {
  add_to_list( *this, data, after );
}




///////////////////////////////////////////////////////
// �������� ������� � ����� ������ � ��������� �� �������������
// ---
template <class Type>
inline void CPList<Type>::Add( Type* data, bool /*check*/ ) {
	if ( !IsExist(data) )
		Add( data );
}




///////////////////////////////////////////////////////
// �������� ������� � ����� ������
// ---
template <class Type>
inline void CPList<Type>::Add( CPListItem<Type>* item ) {
	item->next = 0;
	if ( last )
		last = last->next = item;
	else
		first = last = item;
  count++;
}





///////////////////////////////////////////////////////
// �������� ������ list � ����� ������� ������
// ---
template <class Type>
inline void CPList<Type>::Add( CPList<Type>& list ) {
  add_to_list( *this, list );
}




///////////////////////////////////////////////////////
// �������� ������ list � ����� ������� ������
// !!!!! list ����� ���������� ���������� ������ !!!!!
// ---
template <class Type>
inline void CPList<Type>::AddAndEat( CPList<Type>& list ) {
  if ( list.first ) {
    if ( first ) {
      last->next = list.first;
			last = list.last;
    }
    else {
      first = list.first;
      last = list.last;
    }
    count += list.count;
    list.count = 0;
    list.first = list.last = 0;
  }
}




///////////////////////////////////////////////////////
// �������� ������� � ������ ������
// ---
template <class Type>
inline void CPList<Type>::Insert( Type* data ) {
  CPListItem<Type>* old = first;
  first = new CPListItem<Type>( data );
  first->next = old;
  if ( !last )
    last = first;
  count++;
}




///////////////////////////////////////////////////////
// �������� ������� � ������ ������
// ---
template <class Type>
inline void CPList<Type>::Insert( CPListItem<Type>* item ) {
  CPListItem<Type>* old = first;
  first = item;
  first->next = old;
  if ( !last )
    last = first;
  count++;
}





///////////////////////////////////////////////////////
// �������� ������ list � ������ ������� ������
// ---
template <class Type>
inline void CPList<Type>::Insert( CPList<Type>& list ) {
  insert_to_list( *this, list );
}




///////////////////////////////////////////////////////
// ������ ������ list � ������ ������� ������
// ---
template <class Type>
inline void CPList<Type>::InsertAndEat( CPList<Type>& list ) {
  if ( list.first ) {
    if ( first ) {
      list.last->next = first;
      first = list.first;
    }
    else {
      first = list.first;
      last = list.last;
    }
    count += list.count;
		list.count = 0;
    list.first = list.last = 0;
  }
}




///////////////////////////////////////////////////////
// ������� ��� �������� ������
// ---
template <class Type>
inline void CPList<Type>::Remove( DelType shdl ) {
  remove_from_list( *this, shdl );
}



///////////////////////////////////////////////////////
// ������� ���� ������� ������
// ---
template <class Type>
inline bool CPList<Type>::Remove( Type* del, DelType shdl ) {
  if ( Detach(del) ) {
    if ( shdl==Delete || (shdl==defDelete && owns) )
      delete del;
    return true;
  }
  else
    return false;
}




///////////////////////////////////////////////////////
// ����������� �� ������ ������ ������ ���������
// ---
template <class Type>
inline uint32 CPList<Type>::Remove( CPList<Type>& deList, DelType shdl ) {
  return remove_from_list( *this, deList, shdl );
}



///////////////////////////////////////////////////////
// ����������� ���� ������� ������
// ---
template <class Type>
inline bool CPList<Type>::Detach( const Type* del ) {
  return detach_from_list( *this, del );
}





///////////////////////////////////////////////////////
// ����������� �� ������ ������ ������ ���������
// ---
template <class Type>
inline uint32 CPList<Type>::Detach( CPList<Type>& deList ) {
  return Remove( deList, noDelete );
}



///////////////////////////////////////////////////////
// ������� ������ �� ��� ������
// ������ ������ ����� ���������� � curr
// ---
template <class Type>
inline CPList<Type>* CPList<Type>::Break( CPListItem<Type>* curr ) {
	CPList<Type>* newList = new CPList<Type>;

  if ( curr ) {
    if ( curr == first ) { // ������� ������� ������ � ������
			newList->first = 0;
			newList->last = 0;
    }
    else {
      newList->first = first;
      newList->last = findPrev( curr );
      newList->last->next = 0;

      first = curr;
    }
  }
  else {
    newList->first = first;
    newList->last = last;

    first = 0;
    last = 0;
  }

  return newList;
}





///////////////////////////////////////////////////////
// �������� ������
// ---
template <class Type>
inline void CPList<Type>::Close() {
  if ( last )
    last->next = first;
}




///////////////////////////////////////////////////////
// ���������� ������
// ---
template <class Type>
inline void CPList<Type>::Split() {
  if ( last )
    last->next = 0;
}




///////////////////////////////////////////////////////
// ���� ���������� ��������� � ������
// ---
template <class Type>
inline uint32 CPList<Type>::ReCalc() {
  return recalc_list( *this );
}




///////////////////////////////////////////////////////
// ����� ������� �� ������� (��������� ����������)
// ---
template <class Type>
inline bool CPList<Type>::IsExist( const Type* what ) const {
  return is_exist_in_list( *this, what );
}



///////////////////////////////////////////////////////
// ����� ����������
// ---
template <class Type>
inline CPListItem<Type>* CPList<Type>::findPrev( CPListItem<Type>* now ) {
  return find_prev_in_list( *this, now );
}



///////////////////////////////////////////////////////
// ��������� ������� ��� ������� ��������
// ---
template <class Type>
inline void CPIList<Type>::ForEachI( IterType1 iFunc ) const {
  for_each_in_list( *this, iFunc );
}




///////////////////////////////////////////////////////
// ��������� ������� ��� ������� ��������
// ---
template <class Type>
inline void CPIList<Type>::ForEachI( IterType2 iFunc, void* args ) const {
  for_each_in_list( *this, iFunc, args );
}



///////////////////////////////////////////////////////
// ����� ������� �� �������
// ---
template <class Type>
inline Type* CPIList<Type>::FirstThatI( CompType cFunc, void* args ) const {
  return first_that_in_list( *this, cFunc, args );
}




///////////////////////////////////////////////////////
// ��������� ������� ��� ������� ��������
// ---
template <class Type>
inline void CPMIList<Type>::ForEach( IterMemType1 iFunc ) const {
  for_each_in_list( *this, iFunc );
}




///////////////////////////////////////////////////////
// ��������� ������� ��� ������� ��������
// ---
template <class Type>
inline void CPMIList<Type>::ForEach( IterMemType2 iFunc, void* args ) const {
  for_each_in_list( *this, iFunc, args );
}



///////////////////////////////////////////////////////
// ����� ������� �� �������
// ---
template <class Type>
inline Type* CPMIList<Type>::FirstThat( CompMemType cFunc, void* args ) const {
  return first_that_in_list( *this, cFunc, args );
}




///////////////////////////////////////////////////////
// ����� ������ � ���������� ��������
// ---
template <class Type>
inline Type* CPLIterator<Type>::GetDataAndGo() {
	if ( curr ) {
		Type* ret = curr->data;
		curr = curr->next;
		return ret;
	}
	else
		return 0;
}



///////////////////////////////////////////////////////
// �������� ������� ����� ��������� ��������
// --- !!!!!!!!!!
template <class Type>
inline void CPLIterator<Type>::Add( Type* data ) {
	if ( curr ) {
		new CPListItem<Type>( data, curr );
		list->count++;
	}
	else
		list->Add( data );
}



///////////////////////////////////////////////////////
// �������� ������� ����� ��������� ��������
// ---
template <class Type>
inline void CPLIterator<Type>::Add( CPLIterator<Type>& item ) {
  if ( item.curr )
    Add( item() );
}



///////////////////////////////////////////////////////
// �������� list ����� ��������� ��������
// ---
template <class Type>
inline void CPLIterator<Type>::Add( CPList<Type>& l ) {
  add_to_iter( *this, l );
}




///////////////////////////////////////////////////////
// ������ list ����� ��������� ��������
// ---
template <class Type>
inline void CPLIterator<Type>::AddAndEat( CPList<Type>& l ) {
  if ( curr ) {
    l.last->next = curr->next;
    curr->next = l.first;
    list->count += l.count;
    l.count = 0;
    l.first = l.last = 0;
	}
  else
    list->Add( l );
}




///////////////////////////////////////////////////////
// �������� ������� ����� item
// ---
template <class Type>
inline void CPLIterator<Type>::Insert( Type* data ) {
  CPListItem<Type>* prev = list->findPrev( curr );
  if ( prev ) {
    new CPListItem<Type>( data, prev );
    list->count++;
  }
  else
    list->Insert( data );
}




///////////////////////////////////////////////////////
// �������� ������� ����� item
// ---
template <class Type>
inline void CPLIterator<Type>::Insert( CPLIterator<Type>& item ) {
  if ( item.curr ) {
    CPListItem<Type>* prev = list->findPrev(curr);
    if ( prev ) {
      prev->next = item.curr;
      item.curr->next = curr;
      list->count++;
    }
    else
      list->Insert( item );
  }
}




///////////////////////////////////////////////////////
// �������� list ����� �������� ���������
// ---
template <class Type>
inline void CPLIterator<Type>::Insert( CPList<Type>& l ) {
  insert_to_iter( *this, l );
}



///////////////////////////////////////////////////////
// ������ list ����� �������� ���������
// ---
template <class Type>
inline void CPLIterator<Type>::InsertAndEat( CPList<Type>& l ) {
  if ( l.first ) {
    CPListItem<Type>* prev = list->findPrev(curr);
    if ( prev ) {
      prev->next = l.first;
      l.last->next = curr;
      list->count += l.count;
			l.count = 0;
      l.first = l.last = 0;
    }
    else
      list->InsertAndEat( l );
  }
}



///////////////////////////////////////////////////////
// ������� ������� ������
// --- !!!!!!!!!!
template <class Type>
inline void CPLIterator<Type>::Remove( DelType shdl ) {
  if ( curr ) {
    if ( shdl==Delete || (shdl==defDelete && list->owns) )
      delete curr->data;
    Detach();
  }
}




///////////////////////////////////////////////////////
// ����������� ������� ������
// --- !!!!!!!!!!
template <class Type>
inline void CPLIterator<Type>::Detach() {
  if ( curr ) {
    CPListItem<Type>* prev = list->findPrev( curr );
    CPListItem<Type>* next = curr->next;
    if ( prev )
      prev->next = next;
    else
      list->first = next;
    if ( !next )
      list->last = prev;
    delete curr;
    curr = next;
    list->count--;
  }
}




///////////////////////////////////////////////////////
// ������ �� ���������� ���������������� �������
// ---
template <class Type>
inline bool CPILIterator<Type>::GoI( typename CPILIterator<Type>::CondType f, void* arg ) {
  return go_iter( *this, f, arg );
}




///////////////////////////////////////////////////////
// ������ �� ���������� ���������������� �������
// ---
template <class Type>
inline bool CPMILIterator<Type>::Go( typename CPMILIterator<Type>::CondMemType f, void* arg ) {
  return go_iter( *this, f, arg );
}


// ---
template <class Type>
void add_to_list( CPList<Type>& list, Type* data, const Type* after ) {
	CPListItem<Type>* c = list.first;
	while ( c )
		if ( c->data == after ) {
			new CPListItem<Type>( data, c );
			list.count++;
			return;
		}
		else
			c = c->next;
	list.Add( data );
}



// ---
template <class Type>
void add_to_list( CPList<Type>& to, CPList<Type>& from ) {
  CPLIterator<Type> i = from;
  while( i )
    to.Add( i++ );
  if ( to.owns )
    from.owns = false;
}


// ---
template <class Type>
void insert_to_list( CPList<Type>& to, CPList<Type>& from ) {
  CPLIterator<Type> i = from;
  while( i )
    to.Insert( i++ );
  if ( to.owns )
    from.owns = false;
}



// ---
template <class Type>
void remove_from_list( CPList<Type>& list, DelType shdl ) {
  bool del = shdl==Delete || (shdl==defDelete && list.owns);
  CPListItem<Type> *first = list.first;
  list.first  = 0;
  list.last   = 0;
  list.count  = 0;
  while ( first ) {
    CPListItem<Type> *temp = first;
    first = first->next;
    if ( del )
      delete temp->data;
    delete temp;
  }
}


// ---
template <class Type>
uint32 remove_from_list( CPList<Type>& list, CPList<Type>& deList, DelType shdl ) {
  if ( !list.first )                    // ������ ���� !
    return 0;

  bool willDel = shdl==Delete || (shdl==defDelete && list.owns);

  list.last->next      = list.first;    // ���������� ������
  CPListItem<Type> *curr = list.first;    // ������ �������
  CPListItem<Type> *prev = list.last;
  CPListItem<Type> *del  = deList.first;  // ������� ���������
  CPListItem<Type> *pdel = 0;             // ���������� ���������
  uint32          deleted = 0;          // ����������� 0

  while( del && list.count ) {          // ���� ��� ���� ���� ������� � ������
    CPListItem<Type> *from  = curr;       // �������� � ��������
    bool            found = false;
    do {
      if ( curr->data == del->data ) {  // �������� !!
        found = true;
        if ( list.first == curr )            // ���� ����� � ������ ������ -
          list.first = curr->next;           // ������ ��������

        if ( list.last == curr )             // ���� ����� � ����� ������ -
          list.last = prev;                  // ����� ��������

        prev->next = curr->next;        // ������� ���������

        Type *data = curr->data;

        delete curr;                    // ������ ��������

        if ( willDel )                  // ���� ���� ������ ������
          delete data;

        curr = prev->next;              // �����������
        list.count--; deleted++;        // ������������� ��������
        break;
      }
      else {                            // ���� �� ����� ����������� �� ���������
        prev = curr;
        curr = curr->next;
      }
    } while( curr != from );            // ���� ��� ��������

    if ( found && willDel ) {           // ������� �������� � list'� �������� ������ ���������
      CPListItem<Type> *next = del->next;
      if ( pdel )
        pdel->next = next;
      else
        deList.first = next;
      if ( !next )
        deList.last = pdel;

      delete del;                       // ������, ��� ������ �� ��� �������
      deList.count--;
      del = next;
    }
    else {
      pdel = del;
      del = del->next;
    }
  }
  if ( list.count )
    list.last->next = 0;                // ��������� ������
  else
    list.first = list.last = 0;
  return deleted;
}



// ---
template <class Type>
bool detach_from_list( CPList<Type>& from, const Type* del ) {
  CPListItem<Type>* curr = from.first;
  CPListItem<Type>* prev = 0;
  while( curr ) {
		if ( curr->data == del ) {
      if ( prev )
        prev->next = curr->next;
      else
        from.first = curr->next;
      if ( !curr->next )
        from.last = prev;

      delete curr;
      from.count--;
      return true;
    }
    else {
      prev = curr;
      curr = curr->next;
    }
  }
  return false;
}



// ---
template <class Type>
uint32 recalc_list( CPList<Type>& list ) {
	CPLIterator<Type> c = (CPList<Type>&)list;
  uint32& count = list.count;
	for( count=0; c; count++,c++ );
	return count;
}


// ---
template <class Type>
uint32 is_exist_in_list( const CPList<Type>& list, const Type* what ) {
	CPListItem<Type>* c = list.first;
	while ( c )
		if ( c->data == what )
			return true;
		else
			c = c->next;
	return false;
}



// ---
template <class Type>
CPListItem<Type>* find_prev_in_list( const CPList<Type>& list, CPListItem<Type>* now ) {
	if ( now ) {
		CPListItem<Type>* tmp = list.first;
		while( tmp && tmp->next != now )
			tmp = tmp->next;
    return tmp;
	}
	else
		return 0;
}


// ---
template <class Type>
void for_each_in_list( const CPIList<Type>& list, void (*iFunc) ( Type* ) ) {
	CPLIterator<Type> curr = list;
	while ( curr )
		iFunc( curr++ );
}


// ---
template <class Type>
void for_each_in_list( const CPIList<Type>& list, void (*iFunc) ( Type*,void* ), void* args ) {
	CPLIterator<Type> curr = list;
	while ( curr )
		iFunc( curr++, args );
}


// ---
template <class Type>
Type* first_that_in_list( const CPIList<Type>& list, bool (*cFunc) ( Type*,void* ), void* args ) {
	CPLIterator<Type> curr = list;
	while ( curr )
		if ( cFunc(curr(),args) )
			return curr();
		else
			curr++;
	return 0;
}



// ---
template <class Type>
void for_each_in_list( const CPMIList<Type>& list, void (Type::*iFunc) () ) {
	CPLIterator<Type> curr = list;
	while ( curr )
		((curr++)->*iFunc)();
}


// ---
template <class Type>
void for_each_in_list( const CPMIList<Type>& list, void (Type::*iFunc) (void*), void* args ) {
	CPLIterator<Type> curr = list;
	while ( curr )
		((curr++)->*iFunc)( args );
}


// ---
template <class Type>
Type* first_that_in_list( const CPMIList<Type>& list, bool (Type::*cFunc) (void*), void* args ) {
	CPLIterator<Type> curr = list;
	while ( curr )
		if ( (curr()->*cFunc)(args) )
			return curr();
		else
			curr++;
	return 0;
}



// ---
template <class Type>
void add_to_iter( CPLIterator<Type>& iter, CPList<Type>& l ) {
	if ( iter.curr ) {
		CPLIterator<Type> f = l;
		CPLIterator<Type> t = iter;
		while( f ) {
			t.Add( f++ );
			t++;
		}
	}
	else
		iter.list->Add( l );
	if ( iter.list->OwnsElem() )
		l.OwnsElem( false );
}



// ---
template <class Type>
void insert_to_iter( CPLIterator<Type>& iter, CPList<Type>& l ) {
  if ( l.first ) {
    CPListItem<Type>* prev = iter.list->findPrev( iter.curr );
		if ( prev ) {
      CPLIterator<Type> f = l;
      while( f )
        prev = new CPListItem<Type>( f++, prev );
      iter.list->count += l.count;
      if ( iter.list->OwnsElem() )
        l.OwnsElem( false );
    }
    else
      iter.list->Insert( l );
  }
}



// ---
template <class Type>
bool go_iter( CPILIterator<Type>& iter, typename CPILIterator<Type>::CondType f, void* arg ) {
  iter.curr = iter.curr->next;
  while( iter.curr ) {
    if ( f(iter.curr->data,arg) )
      return true;
    iter.curr = iter.curr->next;
  }
  return false;
}



// ---
template <class Type>
bool go_iter( CPMILIterator<Type>& iter, bool (Type::*f)(void*), void* arg ) {
  iter.curr = iter.curr->next;
  while( iter.curr ) {
		if ( (iter.curr->data->*f)(arg) )
      return true;
    iter.curr = iter.curr->next;
  }
  return false;
}
#endif



