#include <list>
#include <algorithm>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class ListTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(ListTest);
  CPPUNIT_TEST(list1);
  CPPUNIT_TEST(list2);
  CPPUNIT_TEST(list3);
  CPPUNIT_TEST(list4);
  CPPUNIT_TEST(erase)
  CPPUNIT_TEST(push_back);
  CPPUNIT_TEST(push_front);
  CPPUNIT_TEST_SUITE_END();

protected:
  void list1();
  void list2();
  void list3();
  void list4();
  void erase();
  void push_back();
  void push_front();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ListTest);

//
// tests implementation
//
void ListTest::list1()
{
  int array1 [] = { 9, 16, 36 };
  int array2 [] = { 1, 4 };

  list<int> l1(array1, array1 + 3);
  list<int> l2(array2, array2 + 2);
  list<int>::iterator i1 = l1.begin();
  list<int>::const_iterator ci(i1);
  list<int>::const_iterator ci1(ci);
  l1.splice(i1, l2);
  list<int>::iterator i2 = l1.begin();
  CPPUNIT_ASSERT(*i2++==1);
  CPPUNIT_ASSERT(*i2++==4);
  CPPUNIT_ASSERT(*i2++==9);
  CPPUNIT_ASSERT(*i2++==16);
  CPPUNIT_ASSERT(*i2++==36);

  //Default construct check (_STLP_DEF_CONST_PLCT_NEW_BUG)
  list<int> l(2);
  i1 = l.begin();
  CPPUNIT_ASSERT( *(i1++) == 0 );
  CPPUNIT_ASSERT( *i1 == 0 );
#if 0
  //A small compilation time check to be activated from time to time,
  //compilation should fail.
  {
    list<char>::iterator l_char_ite;
    list<int>::iterator l_int_ite;
    CPPUNIT_ASSERT( l_char_ite != l_int_ite );
  }
#endif
}
void ListTest::list2()
{
  int array1 [] = { 1, 16 };
  int array2 [] = { 4, 9 };

  list<int> l1(array1, array1 + 2);
  list<int> l2(array2, array2 + 2);
  list<int>::iterator i = l1.begin();
  i++;
  l1.splice(i, l2, l2.begin(), l2.end());
  i = l1.begin();
  CPPUNIT_ASSERT(*i++==1);
  CPPUNIT_ASSERT(*i++==4);
  CPPUNIT_ASSERT(*i++==9);
  CPPUNIT_ASSERT(*i++==16);
}
void ListTest::list3()
{
  char array [] = { 'x', 'l', 'x', 't', 's', 's' };

  list<char> str(array, array + 6);
  list<char>::iterator i;

  str.reverse();
  i = str.begin();
  CPPUNIT_ASSERT(*i++=='s');
  CPPUNIT_ASSERT(*i++=='s');
  CPPUNIT_ASSERT(*i++=='t');
  CPPUNIT_ASSERT(*i++=='x');
  CPPUNIT_ASSERT(*i++=='l');
  CPPUNIT_ASSERT(*i++=='x');

  str.remove('x');
  i = str.begin();
  CPPUNIT_ASSERT(*i++=='s');
  CPPUNIT_ASSERT(*i++=='s');
  CPPUNIT_ASSERT(*i++=='t');
  CPPUNIT_ASSERT(*i++=='l');

  str.unique();
  i = str.begin();
  CPPUNIT_ASSERT(*i++=='s');
  CPPUNIT_ASSERT(*i++=='t');
  CPPUNIT_ASSERT(*i++=='l');

  str.sort();
  i = str.begin();
  CPPUNIT_ASSERT(*i++=='l');
  CPPUNIT_ASSERT(*i++=='s');
  CPPUNIT_ASSERT(*i++=='t');
}
void ListTest::list4()
{
  int array1 [] = { 1, 3, 6, 7 };
  int array2 [] = { 2, 4 };

  list<int> l1(array1, array1 + 4);
  list<int> l2(array2, array2 + 2);
  l1.merge(l2);
  list<int>::iterator i = l1.begin();
  CPPUNIT_ASSERT(*i++==1);
  CPPUNIT_ASSERT(*i++==2);
  CPPUNIT_ASSERT(*i++==3);
  CPPUNIT_ASSERT(*i++==4);
  CPPUNIT_ASSERT(*i++==6);
  CPPUNIT_ASSERT(*i++==7);

  //We use distance to avoid a simple call to an internal counter
  CPPUNIT_ASSERT(distance(l1.begin(), l1.end()) == 6);
  CPPUNIT_ASSERT(distance(l2.begin(), l2.end()) == 0);

  l1.swap(l2);
  
  CPPUNIT_ASSERT(distance(l1.begin(), l1.end()) == 0);
  CPPUNIT_ASSERT(distance(l2.begin(), l2.end()) == 6);
}

void ListTest::erase()
{
  list<int> l;
  l.push_back( 1 );
  l.erase(l.begin());
  CPPUNIT_ASSERT( l.empty() );
  
  int array[] = { 0, 1, 2, 3 };
  l.assign(array, array + 4);
  list<int>::iterator lit;
  lit = l.erase(l.begin());
  CPPUNIT_ASSERT( *lit == 1 );

  lit = l.erase(l.begin(), --l.end());
  CPPUNIT_ASSERT( *lit == 3 );

  l.clear();
  CPPUNIT_ASSERT( l.empty() );
}

void ListTest::push_back()
{
  list<int> l;
  l.push_back( 1 );
  l.push_back( 2 );
  l.push_back( 3 );

  list<int>::reverse_iterator r = l.rbegin();

  CPPUNIT_ASSERT( *r == 3 );
  l.push_back( 4 );
  /*
   * Following lines are commented, because ones show standard contradiction
   * (24.4.1 and 23.2.2.3); but present behaviour is valid, 24.4.1, paragraphs 1 and 2,
   * 24.4.1.3.3 and 23.1 paragraph 9 (Table 66). The 24.4.1 is more common rule,
   * so it has preference under 23.2.2.3, by my opinion.
   *
   *      - ptr
   */
  // CPPUNIT_ASSERT( *r == 3 );
  // ++r;
  // CPPUNIT_ASSERT( *r == 2 );
}

void ListTest::push_front()
{
  list<int> l;
  l.push_back( 1 );
  l.push_back( 2 );
  l.push_back( 3 );

  list<int>::iterator i = l.begin();

  CPPUNIT_ASSERT( *i == 1 );
  l.push_front( 0 );
  CPPUNIT_ASSERT( *i == 1 );
  ++i;
  CPPUNIT_ASSERT( *i == 2 );
}


