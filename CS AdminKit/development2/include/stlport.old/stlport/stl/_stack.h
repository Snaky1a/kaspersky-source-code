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

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef _STLP_INTERNAL_STACK_H
#define _STLP_INTERNAL_STACK_H

#ifndef _STLP_INTERNAL_DEQUE_H
# include <stl/_deque.h>
#endif

_STLP_BEGIN_NAMESPACE

# if !defined ( _STLP_LIMITED_DEFAULT_TEMPLATES )
template <class _Tp, class _Sequence = deque<_Tp> >
# elif defined ( _STLP_MINIMUM_DEFAULT_TEMPLATE_PARAMS )
# define _STLP_STACK_ARGS _Tp
template <class _Tp>
# else
template <class _Tp, class _Sequence>
# endif
class stack 
#if defined (_STLP_USE_PARTIAL_SPEC_WORKAROUND)
#  if defined (_STLP_STACK_ARGS)
            : public __stlport_class<stack<_Tp> >
#  else
            : public __stlport_class<stack<_Tp, _Sequence> >
#  endif
#endif
{
# ifdef _STLP_STACK_ARGS 
  typedef deque<_Tp> _Sequence;
  typedef stack<_Tp> _Self;
# else
  typedef stack<_Tp, _Sequence> _Self;
# endif

public:
  typedef typename _Sequence::value_type      value_type;
  typedef typename _Sequence::size_type       size_type;
  typedef          _Sequence                  container_type;

  typedef typename _Sequence::reference       reference;
  typedef typename _Sequence::const_reference const_reference;
protected:
  _Sequence _M_s;
public:
  stack() : _M_s() {}
  explicit stack(const _Sequence& __s) : _M_s(__s) {}

  stack(__move_source<_Self> src)
    : _M_s(_AsMoveSource(src.get()._M_s)) {
  }

  bool empty() const { return _M_s.empty(); }
  size_type size() const { return _M_s.size(); }
  reference top() { return _M_s.back(); }
  const_reference top() const { return _M_s.back(); }
  void push(const value_type& __x) { _M_s.push_back(__x); }
  void pop() { _M_s.pop_back(); }
  const _Sequence& _Get_s() const { return _M_s; }
};

# ifndef _STLP_STACK_ARGS
#  define _STLP_STACK_ARGS _Tp, _Sequence
#  define _STLP_STACK_HEADER_ARGS class _Tp, class _Sequence
# else
#  define _STLP_STACK_HEADER_ARGS class _Tp
# endif

template < _STLP_STACK_HEADER_ARGS >
inline bool _STLP_CALL  operator==(const stack< _STLP_STACK_ARGS >& __x,
                                   const stack< _STLP_STACK_ARGS >& __y) {
  return __x._Get_s() == __y._Get_s();
}

template < _STLP_STACK_HEADER_ARGS >
inline bool _STLP_CALL  operator<(const stack< _STLP_STACK_ARGS >& __x,
                                  const stack< _STLP_STACK_ARGS >& __y) {
  return __x._Get_s() < __y._Get_s();
}

_STLP_RELOPS_OPERATORS(template < _STLP_STACK_HEADER_ARGS >, stack< _STLP_STACK_ARGS >)
    
#  undef _STLP_STACK_ARGS
#  undef _STLP_STACK_HEADER_ARGS

#ifdef _STLP_CLASS_PARTIAL_SPECIALIZATION
template <class _Tp, class _Sequence>
struct __move_traits<stack<_Tp, _Sequence> > :
  __move_traits_aux<_Sequence>
{};
#endif /* _STLP_CLASS_PARTIAL_SPECIALIZATION */

_STLP_END_NAMESPACE

#endif /* _STLP_INTERNAL_STACK_H */

// Local Variables:
// mode:C++
// End:
