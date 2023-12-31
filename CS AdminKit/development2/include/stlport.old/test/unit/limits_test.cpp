/* boost limits_test.cpp   test your <limits> file for important
 *
 * Copyright Jens Maurer 2000
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without fee provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation,
 *
 * Jens Maurer makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 * $Id: limits_test.cpp,v 1.1.2.1 2004/08/09 19:49:35 dums Exp $
 */

#include <limits>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class LimitTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(LimitTest);
  CPPUNIT_TEST(test);
  CPPUNIT_TEST_SUITE_END();

protected:
  void test();
};

CPPUNIT_TEST_SUITE_REGISTRATION(LimitTest);


#define CHECK_COND(X) if (!(X)) return false;

template<class _Tp>
bool test_integral_limits(const _Tp &) {
  typedef std::numeric_limits<_Tp> lim;

  CHECK_COND(lim::is_specialized);
  CHECK_COND(lim::is_integer);
  /*CHECK_COND(lim::is_modulo);*/
  CHECK_COND(lim::min() < lim::max());

  return true;
}

template <class _Tp>
bool test_float_limits(const _Tp &) {
  typedef std::numeric_limits<_Tp> lim;
  CHECK_COND(lim::is_specialized);
  CHECK_COND(!lim::is_modulo);
  CHECK_COND(!lim::is_integer);
  CHECK_COND(lim::is_signed);

  const _Tp infinity = lim::infinity();
  const _Tp qnan = lim::quiet_NaN();

  CHECK_COND(lim::max() > 1000);
  CHECK_COND(lim::min() > 0);
  CHECK_COND(lim::min() < 0.001);
  CHECK_COND(lim::epsilon() > 0);

  if (lim::is_iec559) {
    CHECK_COND(lim::has_infinity);
    CHECK_COND(lim::has_quiet_NaN);
    CHECK_COND(lim::has_signaling_NaN);
  }

  if (lim::has_infinity) {
    /* Make sure those values are not 0 or similar nonsense.
    * Infinity must compare as if larger than the maximum representable value.
    */
    CHECK_COND(infinity > lim::max());
    CHECK_COND(-infinity < -lim::max());
  }

  if (lim::has_quiet_NaN) {
    /* NaNs shall always compare "false" when compared for equality
    * If one of these fail, your compiler may be optimizing incorrectly,
    * or the STLport is incorrectly configured.
    */
    CHECK_COND(! (qnan == 42));
    CHECK_COND(! (qnan == qnan));
    CHECK_COND(qnan != 42);
    CHECK_COND(qnan != qnan);

    /* The following tests may cause arithmetic traps.
    * CHECK_COND(! (qnan < 42));
    * CHECK_COND(! (qnan > 42));
    * CHECK_COND(! (qnan <= 42));
    * CHECK_COND(! (qnan >= 42));
    */
  }

  return true;
}

void LimitTest::test() {
  CPPUNIT_ASSERT(test_integral_limits(bool()));
  CPPUNIT_ASSERT(test_integral_limits(char()));
  typedef signed char signed_char;
  CPPUNIT_ASSERT(test_integral_limits(signed_char()));
  typedef unsigned char unsigned_char;
  CPPUNIT_ASSERT(test_integral_limits(unsigned_char()));
#  if defined (_STLP_HAS_WCHAR_T)
  CPPUNIT_ASSERT(test_integral_limits(wchar_t()));
#  endif
  CPPUNIT_ASSERT(test_integral_limits(short()));
  typedef unsigned short unsigned_short;
  CPPUNIT_ASSERT(test_integral_limits(unsigned_short()));
  CPPUNIT_ASSERT(test_integral_limits(int()));
  typedef unsigned int unsigned_int;
  CPPUNIT_ASSERT(test_integral_limits(unsigned_int()));
  CPPUNIT_ASSERT(test_integral_limits(long()));
  typedef unsigned long unsigned_long;
  CPPUNIT_ASSERT(test_integral_limits(unsigned_long()));
#  if defined (_STLP_LONG_LONG)
  typedef _STLP_LONG_LONG long_long;
  CPPUNIT_ASSERT(test_integral_limits(long_long()));
  typedef unsigned _STLP_LONG_LONG unsigned_long_long;
  CPPUNIT_ASSERT(test_integral_limits(unsigned_long_long()));
#endif

  CPPUNIT_ASSERT(test_float_limits(float()));
  CPPUNIT_ASSERT(test_float_limits(double()));
#  if !defined ( _STLP_NO_LONG_DOUBLE )
  typedef long double long_double;
  CPPUNIT_ASSERT(test_float_limits(long_double()));
#  endif
}
