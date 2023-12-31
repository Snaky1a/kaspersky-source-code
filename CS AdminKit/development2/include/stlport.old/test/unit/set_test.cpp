#include <set>
#include <algorithm>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class SetTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(SetTest);
  CPPUNIT_TEST(set1);
  CPPUNIT_TEST(set2);
  CPPUNIT_TEST(erase);
  CPPUNIT_TEST(insert);
  CPPUNIT_TEST(find);
  CPPUNIT_TEST(bounds);
  CPPUNIT_TEST(specialized_less);
  CPPUNIT_TEST_SUITE_END();

  protected:
    void set1();
    void set2();
    void erase();
    void insert();
    void find();
    void bounds();
    void specialized_less();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SetTest);


//
// tests implementation
//
void SetTest::set1()
{
  set<int, less<int> > s;
  CPPUNIT_ASSERT (s.count(42) == 0);
  s.insert(42);
  CPPUNIT_ASSERT (s.count(42) == 1);
  s.insert(42);
  CPPUNIT_ASSERT (s.count(42) == 1);
  int count = s.erase(42);
  CPPUNIT_ASSERT (count == 1);
}

void SetTest::set2()
{
  typedef set<int, less<int> > int_set;
  int_set s;
  pair<int_set::iterator, bool> p = s.insert(42);
  CPPUNIT_ASSERT (p.second == true);
  p = s.insert(42);
  CPPUNIT_ASSERT (p.second == false);

  int array1 [] = { 1, 3, 6, 7 };
  s.insert(array1, array1 + 4);
  CPPUNIT_ASSERT (distance(s.begin(), s.end()) == 5);

  int_set s2;
  s2.swap(s);
  CPPUNIT_ASSERT (distance(s2.begin(), s2.end()) == 5);
  CPPUNIT_ASSERT (distance(s.begin(), s.end()) == 0);

  int_set s3;
  s3.swap(s);
  s3.swap(s2);
  CPPUNIT_ASSERT (distance(s.begin(), s.end()) == 0);
  CPPUNIT_ASSERT (distance(s2.begin(), s2.end()) == 0);
  CPPUNIT_ASSERT (distance(s3.begin(), s3.end()) == 5);
}

void SetTest::erase()
{
  set<int, less<int> > s;
  s.insert(1);
  s.erase(s.begin());
  CPPUNIT_ASSERT( s.empty() );
  
  unsigned int nb = s.erase(1);
  CPPUNIT_ASSERT(nb == 0);
}

void SetTest::insert()
{
  set<int> s;
  set<int>::iterator i = s.insert( s.end(), 0 );
  CPPUNIT_ASSERT( *i == 0 );
}

void SetTest::find()
{
  set<int> s;

  CPPUNIT_ASSERT( s.find(0) == s.end() );

  set<int> const& crs = s;

  CPPUNIT_ASSERT( crs.find(0) == crs.end() );
}

void SetTest::bounds()
{
  int array1 [] = { 1, 3, 6, 7 };
  set<int> s(array1, array1 + sizeof(array1) / sizeof(array1[0]));
  set<int> const& crs = s;

  set<int>::iterator sit;
  set<int>::const_iterator scit;
  pair<set<int>::iterator, set<int>::iterator> pit;
  pair<set<int>::const_iterator, set<int>::const_iterator> pcit;

  //Check iterator on mutable set
  sit = s.lower_bound(2);
  CPPUNIT_ASSERT( sit != s.end() );
  CPPUNIT_ASSERT( *sit == 3 );

  sit = s.upper_bound(5);
  CPPUNIT_ASSERT( sit != s.end() );
  CPPUNIT_ASSERT( *sit == 6 );

  pit = s.equal_range(6);
  CPPUNIT_ASSERT( pit.first != pit.second );
  CPPUNIT_ASSERT( pit.first != s.end() );
  CPPUNIT_ASSERT( *pit.first == 6 );
  CPPUNIT_ASSERT( pit.second != s.end() );
  CPPUNIT_ASSERT( *pit.second == 7 );

  //Check const_iterator on mutable set
  scit = s.lower_bound(2);
  CPPUNIT_ASSERT( scit != s.end() );
  CPPUNIT_ASSERT( *scit == 3 );

  scit = s.upper_bound(5);
  CPPUNIT_ASSERT( scit != s.end() );
  CPPUNIT_ASSERT( *scit == 6 );

#ifdef _STLP_MEMBER_TEMPLATES
  pcit = s.equal_range(6);
  CPPUNIT_ASSERT( pcit.first != pcit.second );
  CPPUNIT_ASSERT( pcit.first != s.end() );
  CPPUNIT_ASSERT( *pcit.first == 6 );
  CPPUNIT_ASSERT( pcit.second != s.end() );
  CPPUNIT_ASSERT( *pcit.second == 7 );
#endif

  //Check const_iterator on const set
  scit = crs.lower_bound(2);
  CPPUNIT_ASSERT( scit != crs.end() );
  CPPUNIT_ASSERT( *scit == 3 );

  scit = crs.upper_bound(5);
  CPPUNIT_ASSERT( scit != crs.end() );
  CPPUNIT_ASSERT( *scit == 6 );

  pcit = crs.equal_range(6);
  CPPUNIT_ASSERT( pcit.first != pcit.second );
  CPPUNIT_ASSERT( pcit.first != crs.end() );
  CPPUNIT_ASSERT( *pcit.first == 6 );
  CPPUNIT_ASSERT( pcit.second != crs.end() );
  CPPUNIT_ASSERT( *pcit.second == 7 );
}


class SetTestClass {
public:
  SetTestClass (int data) : _data(data)
  {}

  int data() const {
    return _data;
  }

private:
  int _data;
};

namespace std {
  template <>
  struct less<SetTestClass> {
    bool operator () (SetTestClass const& lhs, SetTestClass const& rhs) const {
      return lhs.data() < rhs.data();
    }
  };
};

void SetTest::specialized_less()
{
  set<SetTestClass> s;
  s.insert(SetTestClass(1));
  s.insert(SetTestClass(3));
  s.insert(SetTestClass(2));
  s.insert(SetTestClass(0));

  set<SetTestClass>::iterator sit(s.begin()), sitEnd(s.end());
  int i = 0;
  for (; sit != sitEnd; ++sit, ++i) {
    CPPUNIT_ASSERT( sit->data() == i );
  }
}

