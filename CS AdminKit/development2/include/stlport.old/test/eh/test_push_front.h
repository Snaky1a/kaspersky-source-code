/***********************************************************************************
	test_push_front.h
	
 * Copyright (c) 1997
 * Mark of the Unicorn, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Mark of the Unicorn makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
		
***********************************************************************************/
#ifndef test_push_front_H_
#define test_push_front_H_

# if defined (EH_NEW_HEADERS)
#  include <cassert>
# else
#  include <assert.h>
# endif
# include "Prefix.h"

# if defined(_STLP_ASSERTIONS) || defined(_STLP_DEBUG)
#  define _STLP_FILE_UNIQUE_ID TEST_PUSH_FRONT_H
_STLP_INSTRUMENT_FILE();
# endif

template <class C>
struct test_push_front
{
	test_push_front( const C& orig ) : original( orig ) {
            gTestController.SetCurrentTestName("push_front() method");
        }
	
	void operator()( C& c ) const
	{
      typedef typename C::value_type _value_type;
		c.push_front( _value_type() );
		EH_ASSERT( c.size() == original.size() + 1 );
		typename C::const_iterator next = c.begin();

		EH_ASSERT( EH_STD::equal( original.begin(), original.end(), ++next ) );
	}
private:
	const C& original;
};

# if defined(_STLP_ASSERTIONS) || defined(_STLP_DEBUG)
#  undef _STLP_FILE_UNIQUE_ID
# endif

#endif // test_push_front_H_
