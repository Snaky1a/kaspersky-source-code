 /*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

# define __PUT_STATIC_DATA_MEMBERS_HERE
# define _STLP_EXPOSE_GLOBALS_IMPLEMENTATION

# include "stlport_prefix.h"


# if !defined(_STLP_DEBUG) && ! defined (_STLP_ASSERTIONS)
#  if !(defined(__APPLE__) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 3))))
#  define _STLP_ASSERTIONS 1
#  endif
# endif

#include <utility>
#include <memory>
#include <vector>
#include <set>
#include <list>
#include <slist>
#include <deque>
#include <stl/_hashtable.h>
#include <limits>
#include <string>
#include <stdexcept>
#include <bitset>

# if ( _STLP_STATIC_TEMPLATE_DATA < 1 )
// for rope, locale static members
#  include <rope>
#  include <locale>
# endif

# if defined (_STLP_UNIX) && !defined(_STLP_NO_THREADS)
#  define _STLP_HAS_PERTHREAD_ALLOCATOR
# include <stl/_pthread_alloc.h>
# endif

// boris : this piece of code duplicated from _range_errors.h
#undef _STLP_THROW_MSG
#if defined(_STLP_THROW_RANGE_ERRORS)
# ifndef _STLP_STDEXCEPT
#  include <stdexcept>
# endif
# ifndef _STLP_STRING
#  include <string>
# endif
# define _STLP_THROW_MSG(ex,msg)  throw ex(string(msg))
#else
# if defined (_STLP_WINCE) || defined (_STLP_RTTI_BUG)
#  define _STLP_THROW_MSG(ex,msg)  TerminateProcess(GetCurrentProcess(), 0)
# else
#  include <cstdlib>
#  include <cstdio>
#  define _STLP_THROW_MSG(ex,msg)  puts(msg),_STLP_ABORT()
# endif
#endif

#ifdef _STLP_MSVC
#pragma optimize("g",off)
#endif 

_STLP_BEGIN_NAMESPACE

void _STLP_DECLSPEC _STLP_CALL __stl_throw_range_error(const char* __msg) { 
  _STLP_THROW_MSG(range_error, __msg); 
}

void _STLP_DECLSPEC _STLP_CALL __stl_throw_out_of_range(const char* __msg) { 
  _STLP_THROW_MSG(out_of_range, __msg); 
}

void _STLP_DECLSPEC _STLP_CALL __stl_throw_length_error(const char* __msg) { 
  _STLP_THROW_MSG(length_error, __msg); 
}

void _STLP_DECLSPEC _STLP_CALL __stl_throw_invalid_argument(const char* __msg) { 
  _STLP_THROW_MSG(invalid_argument, __msg); 
}

void _STLP_DECLSPEC _STLP_CALL __stl_throw_overflow_error(const char* __msg) { 
  _STLP_THROW_MSG(overflow_error, __msg); 
}

_STLP_DECLSPEC const char*  _STLP_CALL
__get_c_string(const string& __str) { 
  return __str.c_str(); 
}


# if defined (_STLP_NO_EXCEPTION_HEADER) || defined(_STLP_BROKEN_EXCEPTION_CLASS)
exception::exception() _STLP_NOTHROW {}
exception::~exception() _STLP_NOTHROW {}
bad_exception::bad_exception() _STLP_NOTHROW {}
bad_exception::~bad_exception() _STLP_NOTHROW {}
const char* exception::what() const _STLP_NOTHROW {return "class exception";}
const char* bad_exception::what() const _STLP_NOTHROW {return "class bad_exception";}
# endif

# ifdef _STLP_OWN_STDEXCEPT
__Named_exception::__Named_exception(const string& __str) {
  strncpy(_M_name, __get_c_string(__str), _S_bufsize);
  _M_name[_S_bufsize - 1] = '\0';
}

const char* __Named_exception::what() const _STLP_NOTHROW_INHERENTLY { return _M_name; }

// boris : those are needed to force typeinfo nodes to be created in here only
__Named_exception::~__Named_exception() _STLP_NOTHROW_INHERENTLY {}

logic_error::~logic_error() _STLP_NOTHROW_INHERENTLY {}
runtime_error::~runtime_error() _STLP_NOTHROW_INHERENTLY {}
domain_error::~domain_error() _STLP_NOTHROW_INHERENTLY {}
invalid_argument::~invalid_argument() _STLP_NOTHROW_INHERENTLY {}
length_error::~length_error() _STLP_NOTHROW_INHERENTLY {}
out_of_range::~out_of_range() _STLP_NOTHROW_INHERENTLY {}
range_error::~range_error() _STLP_NOTHROW_INHERENTLY {}
overflow_error::~overflow_error() _STLP_NOTHROW_INHERENTLY {}
underflow_error::~underflow_error() _STLP_NOTHROW_INHERENTLY {}

# endif /* _STLP_OWN_STDEXCEPT */

# if !defined(_STLP_WCE_EVC3)
# ifdef  _STLP_NO_BAD_ALLOC
const nothrow_t nothrow /* = {} */;
# endif
# endif

# ifndef _STLP_NO_FORCE_INSTANTIATE

#  if defined (_STLP_DEBUG) || defined (_STLP_ASSERTIONS)
template struct _STLP_CLASS_DECLSPEC __stl_debug_engine<bool>;
#  endif

template class _STLP_CLASS_DECLSPEC __node_alloc<false,0>;
template class _STLP_CLASS_DECLSPEC __node_alloc<true,0>;
template class _STLP_CLASS_DECLSPEC __debug_alloc< __node_alloc<true,0> >;
template class _STLP_CLASS_DECLSPEC __debug_alloc< __node_alloc<false,0> >;
template class _STLP_CLASS_DECLSPEC __debug_alloc<__new_alloc>;
template class _STLP_CLASS_DECLSPEC __malloc_alloc<0>;

#  if defined (_STLP_THREADS) && ! defined ( _STLP_ATOMIC_EXCHANGE ) && (defined(_STLP_PTHREADS) || defined (_STLP_UITHREADS)  || defined (_STLP_OS2THREADS))
template class _STLP_CLASS_DECLSPEC _Swap_lock_struct<0>;
#  endif

template class _STLP_CLASS_DECLSPEC allocator<void*>;
template class _STLP_CLASS_DECLSPEC _STLP_alloc_proxy<void**, void*, allocator<void*> >;
template class _STLP_CLASS_DECLSPEC _Vector_base<void*,allocator<void*> >;
#  if defined (_STLP_DEBUG) && ! defined (__SUNPRO_CC)
template class _STLP_CLASS_DECLSPEC __WORKAROUND_DBG_RENAME(vector) <void*,allocator<void*> >;
template class _STLP_CLASS_DECLSPEC __construct_checker<__WORKAROUND_DBG_RENAME(vector) <void*,allocator<void*> > >;
#  endif
template class _STLP_CLASS_DECLSPEC vector<void*,allocator<void*> >;

#  ifndef _STLP_DONT_USE_PTR_SPECIALIZATIONS
template class _STLP_CLASS_DECLSPEC _Vector_impl<void*, allocator<void*> >;

template class _STLP_CLASS_DECLSPEC _List_base<void*,allocator<void*> >;
template class _STLP_CLASS_DECLSPEC _List_impl<void*,allocator<void*> >;

template class _STLP_CLASS_DECLSPEC _Slist_base<void*, allocator<void*> >;
template class _STLP_CLASS_DECLSPEC _Slist_impl<void*, allocator<void*> >;

template class _STLP_CLASS_DECLSPEC _STLP_alloc_proxy<size_t, void*, allocator<void*> >;
template class _STLP_CLASS_DECLSPEC _STLP_alloc_proxy<void***, void**, allocator<void**> >;
template class _STLP_CLASS_DECLSPEC _Deque_base<void*,allocator<void*> >;
template class _STLP_CLASS_DECLSPEC _Deque_impl<void*,allocator<void*> >;
#  endif /* _STLP_DONT_USE_PTR_SPECIALIZATIONS */

template class _STLP_CLASS_DECLSPEC _Rb_global<bool>;
template class _STLP_CLASS_DECLSPEC _List_global<bool>;
template class _STLP_CLASS_DECLSPEC _Sl_global<bool>;
template class _STLP_CLASS_DECLSPEC _Stl_prime<bool>;
template class _STLP_CLASS_DECLSPEC _LimG<bool>;
template class _STLP_CLASS_DECLSPEC _Bs_G<bool>;

template class _STLP_CLASS_DECLSPEC allocator<char>;
template class _STLP_CLASS_DECLSPEC _STLP_alloc_proxy<char *,char, allocator<char> >;
template class _STLP_CLASS_DECLSPEC _String_base<char, allocator<char> >;

#  if defined (_STLP_DEBUG) && ! defined (__SUNPRO_CC)
template class _STLP_CLASS_DECLSPEC _STLP_NON_DBG_NO_MEM_T_NAME(str)<char, char_traits<char>, allocator<char> >;
template class _STLP_CLASS_DECLSPEC __construct_checker<_STLP_NON_DBG_NO_MEM_T_NAME(str)<char, char_traits<char>, allocator<char> > >;
#  endif

template class _STLP_CLASS_DECLSPEC _STLP_NO_MEM_T_NAME(str)<char, char_traits<char>, allocator<char> >;
#endif /* _STLP_NO_FORCE_INSTANTIATE */

_STLP_END_NAMESPACE

#if defined(_STLP_LEAKS_PEDANTIC) && defined(_STLP_USE_DYNAMIC_LIB)
/*
 * This small helper class purpose is to guaranty that the node
 * allocator memory pool will only be returned to the system
 * once the STLport library will have been unloaded.
 */
static struct _Node_alloc_helper {
  _Node_alloc_helper() {
    _STLP_STD::__node_alloc<false,0>::_S_alloc_call();
    _STLP_STD::__node_alloc<true,0>::_S_alloc_call();
  }
  ~_Node_alloc_helper() {
    _STLP_STD::__node_alloc<false,0>::_S_dealloc_call();
    _STLP_STD::__node_alloc<true,0>::_S_dealloc_call();
  }
} _Node_alloc_helper_inst;
#endif

#define FORCE_SYMBOL extern

# if defined (_WIN32) && defined (_STLP_USE_DECLSPEC) && !defined (_STLP_USE_STATIC_LIB)
// stlportmt.cpp : Defines the entry point for the DLL application.
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#undef FORCE_SYMBOL 
#define FORCE_SYMBOL APIENTRY

extern "C" {

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
      DisableThreadLibraryCalls((HINSTANCE)hModule);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
    }
  return TRUE;
}

} /* extern "C" */

_STLP_BEGIN_NAMESPACE

void FORCE_SYMBOL
force_link() {
  set<int>::iterator iter;
  // _M_increment; _M_decrement instantiation
  ++iter;
  --iter;
}

_STLP_END_NAMESPACE

# endif
