/* boost random/linear_congruential.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without fee provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation,
 *
 * Jens Maurer makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id: linear_congruential.hpp,v 1.1.1.2 2003/05/14 12:22:24 ptr Exp $
 *
 * Revision history
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_LINEAR_CONGRUENTIAL_HPP
#define BOOST_RANDOM_LINEAR_CONGRUENTIAL_HPP

#include <iostream>
#include <cassert>
#include <stdexcept>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/static_assert.hpp>
#include <boost/random/detail/const_mod.hpp>

namespace boost {
namespace random {

// compile-time configurable linear congruential generator
template<class IntType, IntType a, IntType c, IntType m, IntType val>
class linear_congruential
{
public:
  typedef IntType result_type;
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
  static const bool has_fixed_range = true;
  static const result_type min_value = ( c == 0 ? 1 : 0 );
  static const result_type max_value = m-1;
#else
  BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);
#endif
  BOOST_STATIC_CONSTANT(IntType, multiplier = a);
  BOOST_STATIC_CONSTANT(IntType, increment = c);
  BOOST_STATIC_CONSTANT(IntType, modulus = m);

  // MSVC 6 and possibly others crash when encountering complicated integral
  // constant expressions.  Avoid the check for now.
  // BOOST_STATIC_ASSERT(m == 0 || a < m);
  // BOOST_STATIC_ASSERT(m == 0 || c < m);

  explicit linear_congruential(IntType x0 = 1)
    : _modulus(modulus), _x(_modulus ? (x0 % _modulus) : x0)
  { 
    assert(c || x0); /* if c == 0 and x(0) == 0 then x(n) = 0 for all n */
    // overflow check
    // disabled because it gives spurious "divide by zero" gcc warnings
    // assert(m == 0 || (a*(m-1)+c) % m == (c < a ? c-a+m : c-a)); 

    // MSVC fails BOOST_STATIC_ASSERT with std::numeric_limits at class scope
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
    BOOST_STATIC_ASSERT(std::numeric_limits<IntType>::is_integer);
#endif
  }

  template<class It>
  linear_congruential(It& first, It last) { seed(first, last); }

  // compiler-generated copy constructor and assignment operator are fine
  void seed(IntType x0 = 1)
  {
    assert(c || x0);
    _x = (_modulus ? (x0 % _modulus) : x0);
  }

  template<class It>
  void seed(It& first, It last)
  {
    if(first == last)
      throw std::invalid_argument("linear_congruential::seed");
    IntType value = *first++;
    _x = (_modulus ? (value % _modulus) : value);
  }

  result_type min() const { return c == 0 ? 1 : 0; }
  result_type max() const { return modulus-1; }

  IntType operator()()
  {
    _x = const_mod<IntType, m>::mult_add(a, _x, c);
    return _x;
  }

  static bool validation(IntType x) { return val == x; }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
  template<class CharT, class Traits>
  friend std::basic_ostream<CharT,Traits>&
  operator<<(std::basic_ostream<CharT,Traits>& os,
             const linear_congruential& lcg)
  { os << lcg._x; return os; }

  template<class CharT, class Traits>
  friend std::basic_istream<CharT,Traits>&
  operator>>(std::basic_istream<CharT,Traits>& is, linear_congruential& lcg)
  { is >> lcg._x; return is; }
#endif

  friend bool operator==(const linear_congruential& x,
                         const linear_congruential& y)
  { return x._x == y._x; }
  friend bool operator!=(const linear_congruential& x,
                         const linear_congruential& y)
  { return !(x == y); }
#else
  // Use a member function; Streamable concept not supported.
  bool operator==(const linear_congruential& rhs) const
  { return _x == rhs._x; }
  bool operator!=(const linear_congruential& rhs) const
  { return !(*this == rhs); }
#endif

private:
  IntType _modulus;   // work-around for gcc "divide by zero" warning in ctor
  IntType _x;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class IntType, IntType a, IntType c, IntType m, IntType val>
const bool linear_congruential<IntType, a, c, m, val>::has_fixed_range;
template<class IntType, IntType a, IntType c, IntType m, IntType val>
const typename linear_congruential<IntType, a, c, m, val>::result_type linear_congruential<IntType, a, c, m, val>::min_value;
template<class IntType, IntType a, IntType c, IntType m, IntType val>
const typename linear_congruential<IntType, a, c, m, val>::result_type linear_congruential<IntType, a, c, m, val>::max_value;
#endif

} // namespace random

// validation values from the publications
typedef random::linear_congruential<int32_t, 16807, 0, 2147483647, 
  1043618065> minstd_rand0;
typedef random::linear_congruential<int32_t, 48271, 0, 2147483647,
  399268537> minstd_rand;


#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
// emulate the lrand48() C library function; requires support for uint64_t
class rand48 
{
public:
  typedef int32_t result_type;
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
  static const bool has_fixed_range = true;
  static const int32_t min_value = 0;
  static const int32_t max_value = integer_traits<int32_t>::const_max;
#else
  enum { has_fixed_range = false };
#endif
  int32_t min() const { return 0; }
  int32_t max() const { return std::numeric_limits<int32_t>::max(); }
  
  explicit rand48(int32_t x0 = 1) : lcf(cnv(x0)) { }
  explicit rand48(uint64_t x0) : lcf(x0) { }
  template<class It> rand48(It& first, It last) : lcf(first, last) { }
  // compiler-generated copy ctor and assignment operator are fine
  void seed(int32_t x0) { lcf.seed(cnv(x0)); }
  void seed(uint64_t x0) { lcf.seed(x0); }
  template<class It> void seed(It& first, It last) { lcf.seed(first,last); }

  int32_t operator()() { return lcf() >> 17; }
  // by experiment from lrand48()
  static bool validation(int32_t x) { return x == 1993516219; }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
  template<class CharT,class Traits>
  friend std::basic_ostream<CharT,Traits>&
  operator<<(std::basic_ostream<CharT,Traits>& os, const rand48& r)
  { os << r.lcf; return os; }

  template<class CharT,class Traits>
  friend std::basic_istream<CharT,Traits>&
  operator>>(std::basic_istream<CharT,Traits>& is, rand48& r)
  { is >> r.lcf; return is; }
#endif

  friend bool operator==(const rand48& x, const rand48& y)
  { return x.lcf == y.lcf; }
  friend bool operator!=(const rand48& x, const rand48& y)
  { return !(x == y); }
#else
  // Use a member function; Streamable concept not supported.
  bool operator==(const rand48& rhs) const
  { return lcf == rhs.lcf; }
  bool operator!=(const rand48& rhs) const
  { return !(*this == rhs); }
#endif
private:
  random::linear_congruential<uint64_t,
    uint64_t(0xDEECE66DUL) | (uint64_t(0x5) << 32), // xxxxULL is not portable
    0xB, uint64_t(1)<<48, /* unknown */ 0> lcf;
  static uint64_t cnv(int32_t x) 
  { return (static_cast<uint64_t>(x) << 16) | 0x330e;  }
};
#endif /* !BOOST_NO_INT64_T && !BOOST_NO_INTEGRAL_INT64_T */

} // namespace boost

#endif // BOOST_RANDOM_LINEAR_CONGRUENTIAL_HPP
