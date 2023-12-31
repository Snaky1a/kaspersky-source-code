/* boost random/cauchy_distribution.hpp header file
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
 * $Id: cauchy_distribution.hpp,v 1.1.1.2 2003/05/14 12:22:24 ptr Exp $
 *
 * Revision history
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_CAUCHY_DISTRIBUTION_HPP
#define BOOST_RANDOM_CAUCHY_DISTRIBUTION_HPP

#include <cmath>
#include <boost/random/uniform_01.hpp>

namespace boost {

#if defined(__GNUC__) && (__GNUC__ < 3)
// Special gcc workaround: gcc 2.95.x ignores using-declarations
// in template classes (confirmed by gcc author Martin v. Loewis)
  using std::tan;
#endif

// Cauchy distribution: p(x) = sigma/(pi*(sigma**2 + (x-median)**2))
template<class UniformRandomNumberGenerator, class RealType = double,
         class Adaptor = uniform_01<UniformRandomNumberGenerator, RealType> >
class cauchy_distribution
{
public:
  typedef Adaptor adaptor_type;
  typedef UniformRandomNumberGenerator base_type;
  typedef RealType result_type;

  explicit cauchy_distribution(base_type & rng,
                               result_type median = result_type(0), 
                               result_type sigma = result_type(1))
    : _rng(rng), _median(median), _sigma(sigma) { }

  // compiler-generated copy ctor and assignment operator are fine

  adaptor_type& adaptor() { return _rng; }
  base_type& base() const { return _rng.base(); }
  result_type median() const { return _median; }
  result_type sigma() const { return _sigma; }
  void reset() { _rng.reset(); }

  result_type operator()()
  {
    // Can we have a boost::mathconst please?
    const result_type pi = result_type(3.14159265358979323846);
#ifndef BOOST_NO_STDC_NAMESPACE
    using std::tan;
#endif
    return _median + _sigma * tan(pi*(_rng()-result_type(0.5)));
  }
#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
  friend bool operator==(const cauchy_distribution& x, 
                         const cauchy_distribution& y)
  {
    return x._median == y._median && x._sigma == y._sigma && x._rng == y._rng; 
  }

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
  template<class CharT, class Traits>
  friend std::basic_ostream<CharT,Traits>&
  operator<<(std::basic_ostream<CharT,Traits>& os, const cauchy_distribution& cd)
  {
    os << cd._median << " " << cd._sigma;
    return os;
  }

  template<class CharT, class Traits>
  friend std::basic_istream<CharT,Traits>&
  operator>>(std::basic_istream<CharT,Traits>& is, cauchy_distribution& cd)
  {
    is >> std::ws >> cd._median >> std::ws >> cd._sigma;
    return is;
  }
#endif

#else
  // Use a member function
  bool operator==(const cauchy_distribution& rhs) const
  {
    return _median == rhs._median && _sigma == rhs._sigma && _rng == rhs._rng;
  }
#endif
private:
  adaptor_type _rng;
  result_type _median, _sigma;
};

} // namespace boost

#endif // BOOST_RANDOM_CAUCHY_DISTRIBUTION_HPP
