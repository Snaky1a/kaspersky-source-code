#include <vector>
#include <algorithm>
#include <sstream>
#include <numeric>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class IterTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(IterTest);
  CPPUNIT_TEST(iter1);
  CPPUNIT_TEST(iter3);
  CPPUNIT_TEST(iter4);
  CPPUNIT_TEST(iterswp0);
  CPPUNIT_TEST(iterswp1);
  CPPUNIT_TEST(iterswp2);
  CPPUNIT_TEST_SUITE_END();

protected:
  void iter1();
  void iter3();
  void iter4();
  void iterswp0();
  void iterswp1();
  void iterswp2();
};

CPPUNIT_TEST_SUITE_REGISTRATION(IterTest);

//
// tests implementation
//
void IterTest::iter1()
{
  vector<const char*> v; // Vector of character strings.
  v.push_back((char*) "zippy"); // First element.
  v.push_back((char*) "motorboy"); // Second element.
  typedef vector<const char*> vec;
  vec::iterator i = v.begin(); // Position at end.
  unsigned counter=0;
  for(i = v.begin(); i != v.end(); i++, counter++) {
    switch( counter ) {
      case 0:
          CPPUNIT_ASSERT(!strcmp(*i,"zippy"));
      break;
      case 1:
          CPPUNIT_ASSERT(!strcmp(*i,"motorboy"));
      break;
      default:
          CPPUNIT_ASSERT(false);
      break;
    }
  }
}
void IterTest::iter3()
{
  typedef vector<const char*> Vec;
  Vec v; // Vector of character strings.
  v.push_back((char*) "zippy"); // First element.
  v.push_back((char*) "motorboy"); // Second element.
  Vec::reverse_iterator it;
  unsigned counter=0;
  for(it = v.rbegin(); it != v.rend(); it++, counter++) {
    switch( counter ) {
      case 1:
          CPPUNIT_ASSERT(!strcmp(*it,"zippy"));
      break;
      case 0:
          CPPUNIT_ASSERT(!strcmp(*it,"motorboy"));
      break;
      default:
          CPPUNIT_ASSERT(false);
      break;
    }
  }

  CPPUNIT_ASSERT(true);
}
void IterTest::iter4()
{
  vector<int> v; // Empty vector of integers.
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  // Position immediately after last item.
  std::vector<int>::iterator i = v.end(); 
  // Move back one and then access.
  CPPUNIT_ASSERT((*--i)==3);
  i -= 2; // Jump back two items.
  CPPUNIT_ASSERT((*i)==1);
}
void IterTest::iterswp0()
{
  int numbers[6] = { 0, 1, 2, 3, 4, 5 };

  iter_swap(numbers, numbers + 3);

  CPPUNIT_ASSERT(numbers[0]==3);
  CPPUNIT_ASSERT(numbers[1]==1);
  CPPUNIT_ASSERT(numbers[2]==2);
  CPPUNIT_ASSERT(numbers[3]==0);
  CPPUNIT_ASSERT(numbers[4]==4);
  CPPUNIT_ASSERT(numbers[5]==5);

}
void IterTest::iterswp1()
{
  vector<int> v1(6);

  iota( v1.begin(), v1.end(), 0);
  iter_swap( v1.begin(), v1.begin() + 3 );

  CPPUNIT_ASSERT(v1[0]==3);
  CPPUNIT_ASSERT(v1[1]==1);
  CPPUNIT_ASSERT(v1[2]==2);
  CPPUNIT_ASSERT(v1[3]==0);
  CPPUNIT_ASSERT(v1[4]==4);
  CPPUNIT_ASSERT(v1[5]==5);
}
void IterTest::iterswp2()
{
  vector<bool> boolVector;

  boolVector.push_back( true );
  boolVector.push_back( false );

  vector<bool>::iterator i1 = boolVector.begin();
  vector<bool>::iterator i2 = boolVector.begin();
  ++i2;

  bool v0 = *i1;
  bool v1 = *i2;

  iter_swap( i1, i2 );

  CPPUNIT_ASSERT(( *i1 == v1 && *i2 == v0 ));

}
