/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
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
# include "stlport_prefix.h"

#include "locale_impl.h"
#include <locale>
#include <typeinfo>

#include <stdexcept>

#include "c_locale.h"
#include "aligned_buffer.h"


#include "locale_impl.h"
#include <stl/_codecvt.h>
#include <stl/_collate.h>
#include <stl/_ctype.h>
#include <stl/_monetary.h>
#include "message_facets.h"

_STLP_BEGIN_NAMESPACE

// #ifdef _STLP_USE_OWN_NAMESPACE
// using _STLP_VENDOR_EXCEPT_STD::bad_cast;
// #endif

static _Stl_aligned_buffer<_Locale_impl::Init> __Loc_init_buf;
long _Locale_impl::Init::_S_count = 0;

_Locale_impl::Init::Init() {
  // Lock _S_count
  if ( _S_count++ == 0 ) {
//# if defined (__BORLANDC__) && defined (_RTLDLL)
//    _Stl_loc_init_num_put();
//    _Stl_loc_init_num_get();
//    _Stl_loc_init_monetary();
//    _Stl_loc_init_time_facets();
//#endif
    _Locale_impl::_S_initialize();
  }
  // UnLock _S_count
}

_Locale_impl::Init::~Init() {
  // Lock _S_count  
  _STLP_ASSERT( _S_count != 0 );
  if ( --_S_count == 0) {
    _S_uninitialize();
  }
  // UnLock _S_count
}

_Locale_impl::_Locale_impl(const char* s) :
    name(s)
{
  new (&__Loc_init_buf) Init();
}

_Locale_impl::_Locale_impl(_Locale_impl const&)
{
  //Call just to increment the _S_count
  new (&__Loc_init_buf) Init();
}

_Locale_impl::~_Locale_impl() {
  (&__Loc_init_buf)->~Init();
}

// _Locale_impl non-inline member functions.
void _STLP_CALL
_Locale_impl::_M_throw_bad_cast() {
  _STLP_THROW(bad_cast());  
}

static void 
_Stl_loc_assign_ids() {
  // This assigns ids to every facet that is a member of a category,
  // and also to money_get/put, num_get/put, and time_get/put
  // instantiated using ordinary pointers as the input/output
  // iterators.  (The default is [io]streambuf_iterator.)

  money_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index                     = 8;
  money_get<char, const char*>::id._M_index        = 9;
  money_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index                     = 10;
  money_put<char, char*>::id._M_index              = 11;

  num_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index                       = 12;
  num_get<char, const char*>::id._M_index          = 13;
  num_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index                       = 14;
  num_put<char, char*>::id._M_index                = 15;
  time_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index                      = 16;
  time_get<char, const char*>::id._M_index         = 17;
  time_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index                      = 18;
  time_put<char, char*>::id._M_index               = 19;

# ifndef _STLP_NO_WCHAR_T

  money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                  = 27;
  money_get<wchar_t, const wchar_t*>::id._M_index  = 28;
  money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                  = 29;
  money_put<wchar_t, wchar_t*>::id._M_index        = 30;

  num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                       = 31;
  num_get<wchar_t, const wchar_t*>::id._M_index    = 32;
  num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > ::id._M_index                      = 33;
  num_put<wchar_t, wchar_t*>::id._M_index          = 34;
  time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                   = 35;
  time_get<wchar_t, const wchar_t*>::id._M_index   = 36;
  time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                   = 37;
  time_put<wchar_t, wchar_t*>::id._M_index         = 38;
  //  messages<wchar_t>::id._M_index                   = 38;
# endif

  //  locale::id::_S_max                               = 39;
}

// static _Stl_aligned_buffer<_Locale_impl> _S_classic_locale;

static _Stl_aligned_buffer<collate<char> > _S_collate_char;
static _Stl_aligned_buffer<ctype<char> > _S_ctype_char;

# ifndef _STLP_NO_MBSTATE_T
static _Stl_aligned_buffer<codecvt<char, char, mbstate_t> > _S_codecvt_char;
# endif

static _Stl_aligned_buffer<moneypunct<char, true> > _S_moneypunct_true_char;
static _Stl_aligned_buffer<moneypunct<char, false> > _S_moneypunct_false_char;
static _Stl_aligned_buffer<numpunct<char> > _S_numpunct_char;
static _Stl_aligned_buffer<messages<char> > _S_messages_char;

static _Stl_aligned_buffer<money_get<char, istreambuf_iterator<char, char_traits<char> > > > _S_money_get_char;
static _Stl_aligned_buffer<money_put<char, ostreambuf_iterator<char, char_traits<char> > > > _S_money_put_char;
static _Stl_aligned_buffer<num_get<char, istreambuf_iterator<char, char_traits<char> > > > _S_num_get_char;
static _Stl_aligned_buffer<num_put<char, ostreambuf_iterator<char, char_traits<char> > > > _S_num_put_char;
static _Stl_aligned_buffer<time_get<char, istreambuf_iterator<char, char_traits<char> > > > _S_time_get_char;
static _Stl_aligned_buffer<time_put<char, ostreambuf_iterator<char, char_traits<char> > > > _S_time_put_char;

# ifndef _STLP_NO_WCHAR_T
static _Stl_aligned_buffer<collate<wchar_t> > _S_collate_wchar;
static _Stl_aligned_buffer<ctype<wchar_t> > _S_ctype_wchar;
# ifndef _STLP_NO_MBSTATE_T
static _Stl_aligned_buffer<codecvt<wchar_t, char, mbstate_t> > _S_codecvt_wchar;
# endif
static _Stl_aligned_buffer<moneypunct<wchar_t, true> > _S_moneypunct_true_wchar;
static _Stl_aligned_buffer<moneypunct<wchar_t, false> > _S_moneypunct_false_wchar;
static _Stl_aligned_buffer<numpunct<wchar_t> > _S_numpunct_wchar;
static _Stl_aligned_buffer<messages<wchar_t> > _S_messages_wchar;

static _Stl_aligned_buffer<money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_money_get_wchar;
static _Stl_aligned_buffer<money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_money_put_wchar;
static _Stl_aligned_buffer<num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_num_get_wchar;
static _Stl_aligned_buffer<num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_num_put_wchar;
static _Stl_aligned_buffer<time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_time_get_wchar;
static _Stl_aligned_buffer<time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > > _S_time_put_wchar;

# endif

static _Messages _Null_messages;

static locale::facet* _S_classic_facets[] = {
  0,
  &_S_collate_char,
  &_S_ctype_char,
# ifndef _STLP_NO_MBSTATE_T
  &_S_codecvt_char,
# else
  0, 
# endif
  &_S_moneypunct_true_char,
  &_S_moneypunct_false_char,
  &_S_numpunct_char,
  &_S_messages_char,

  &_S_money_get_char,
  0,
  &_S_money_put_char,
  0,

  &_S_num_get_char,
  0,
  &_S_num_put_char,
  0,
  &_S_time_get_char,
  0,
  &_S_time_put_char,
  0,
# ifndef _STLP_NO_WCHAR_T
  &_S_collate_wchar,
  &_S_ctype_wchar,

# ifndef _STLP_NO_MBSTATE_T
  &_S_codecvt_wchar,
# else
  0,
# endif
  &_S_moneypunct_true_wchar,
  &_S_moneypunct_false_wchar,
  &_S_numpunct_wchar,
  &_S_messages_wchar,

  &_S_money_get_wchar,
  0,
  &_S_money_put_wchar,
  0,

  &_S_num_get_wchar,
  0,
  &_S_num_put_wchar,
  0,
  &_S_time_get_wchar,
  0,
  &_S_time_put_wchar,
  0,
# endif
  0
};

static _Stl_aligned_buffer<_Locale_impl> _Locale_classic_impl_buf;
static _Locale_impl *_Stl_global_locale_impl = new (&_Locale_classic_impl_buf) _Locale_impl("C");

struct _Stl_global_locale_impl_free
{
  ~_Stl_global_locale_impl_free()
    { _Stl_global_locale_impl->~_Locale_impl(); _Stl_global_locale_impl = 0; }
};

static _Stl_global_locale_impl_free _S_L_free;

#ifdef _STLP_LEAKS_PEDANTIC
//Small helper struct to release the global locale implementation.
//static struct _Locale_global_decr {
//  ~_Locale_global_decr() {
//    _Stl_global_locale_impl->decr();
//  }
//} _Stl_global_locale_impl_decr;
#endif

/*
 * This object is instanciated here to guarantee creation of the classic locale
 * before creation of the dependent Standard streams cout, cin, wcout...
 */
//static ios_base::Init _IosInit; // not required or should be moved a bit a top:
                                  // all made in _Locale_impl just before...

void _Locale_impl::make_classic_locale() {
  // The classic locale contains every facet that belongs to a category.
  _Locale_impl* classic = &_Locale_classic_impl_buf;
  
  // new (classic) _Locale_impl("C");

  classic->facets = _S_classic_facets;
  classic->_M_size = locale::id::_S_max;

  // ctype category
  new(&_S_ctype_char) ctype<char>(0, false, 1);
  // collate category
  new(&_S_collate_char) collate<char>(1);
  new(&_S_codecvt_char) codecvt<char, char, mbstate_t>(1);
  // numeric punctuation category
  new(&_S_numpunct_char) numpunct<char>(1);
  // numeric category
  new (&_S_num_get_char) num_get<char, istreambuf_iterator<char, char_traits<char> > >(1);
  new (&_S_num_put_char) num_put<char, ostreambuf_iterator<char, char_traits<char> > >(1);
  // time category
  new (&_S_time_get_char) time_get<char, istreambuf_iterator<char, char_traits<char> > >(1);
  new (&_S_time_put_char) time_put<char, ostreambuf_iterator<char, char_traits<char> > >(1);
  // monetary category
  new (&_S_moneypunct_true_char) moneypunct<char, true>(1);
  new (&_S_moneypunct_false_char) moneypunct<char, false>(1);
  new (&_S_money_get_char) money_get<char, istreambuf_iterator<char, char_traits<char> > >(1);
  new (&_S_money_put_char) money_put<char, ostreambuf_iterator<char, char_traits<char> > >(1);
  // messages category
  new (&_S_messages_char)messages<char>(&_Null_messages);

# ifndef _STLP_NO_WCHAR_T
  // ctype category
  new(&_S_ctype_wchar) ctype<wchar_t>(1);
  // collate category
  new(&_S_collate_wchar) collate<wchar_t>(1);
  new(&_S_codecvt_wchar) codecvt<wchar_t, char, mbstate_t>(1);
  // numeric punctuation category
  new(&_S_numpunct_wchar) numpunct<wchar_t>(1);
  // numeric category
  new (&_S_num_get_wchar) num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
  new (&_S_num_put_wchar) num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
  // time category
  new (&_S_time_get_wchar) time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
  new (&_S_time_put_wchar) time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
  // monetary category
  new (&_S_moneypunct_true_wchar) moneypunct<wchar_t, true>(1);
  new (&_S_moneypunct_false_wchar) moneypunct<wchar_t, false>(1);
  new (&_S_money_get_wchar) money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
  new (&_S_money_put_wchar) money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1);
  // messages category
  new (&_S_messages_wchar)messages<wchar_t>(&_Null_messages);
# endif
}

#ifdef _STLP_LEAKS_PEDANTIC
void _Locale_impl::free_classic_locale() {
# ifndef _STLP_NO_WCHAR_T
  (&_S_messages_wchar)->~messages<wchar_t>();
  (&_S_money_put_wchar)->~money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >();
  (&_S_money_get_wchar)->~money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >();
  (&_S_moneypunct_false_wchar)->~moneypunct<wchar_t, false>();
  (&_S_moneypunct_true_wchar)->~moneypunct<wchar_t, true>();
  (&_S_time_put_wchar)->~time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >();
  (&_S_time_get_wchar)->~time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >();
  (&_S_num_put_wchar)->~num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >();
  (&_S_num_get_wchar)->~num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >();
  (&_S_numpunct_wchar)->~numpunct<wchar_t>();
  (&_S_codecvt_wchar)->~codecvt<wchar_t, char, mbstate_t>();
  (&_S_collate_wchar)->~collate<wchar_t>();
  (&_S_ctype_wchar)->~ctype<wchar_t>();
# endif

  (&_S_messages_char)->~messages<char>();
  (&_S_money_put_char)->~money_put<char, ostreambuf_iterator<char, char_traits<char> > >();
  (&_S_money_get_char)->~money_get<char, istreambuf_iterator<char, char_traits<char> > >();
  (&_S_moneypunct_false_char)->~moneypunct<char, false>();
  (&_S_moneypunct_true_char)->~moneypunct<char, true>();
  (&_S_time_put_char)->~time_put<char, ostreambuf_iterator<char, char_traits<char> > >();
  (&_S_time_get_char)->~time_get<char, istreambuf_iterator<char, char_traits<char> > >();
  (&_S_num_put_char)->~num_put<char, ostreambuf_iterator<char, char_traits<char> > >();
  (&_S_num_get_char)->~num_get<char, istreambuf_iterator<char, char_traits<char> > >();
  (&_S_numpunct_char)->~numpunct<char>();
  (&_S_codecvt_char)->~codecvt<char, char, mbstate_t>();
  (&_S_collate_char)->~collate<char>();
  (&_S_ctype_char)->~ctype<char>();
}
#endif // _STLP_LEAKS_PEDANTIC

//----------------------------------------------------------------------

// Declarations of (non-template) facets' static data members
size_t locale::id::_S_max = 39;

_STLP_STATIC_MEMBER_DECLSPEC locale::id collate<char>::id = { 1 };
_STLP_STATIC_MEMBER_DECLSPEC locale::id ctype<char>::id = { 2 };

# ifndef _STLP_NO_MBSTATE_T
_STLP_STATIC_MEMBER_DECLSPEC locale::id codecvt<char, char, mbstate_t>::id = { 3 };
#  ifndef _STLP_NO_WCHAR_T
_STLP_STATIC_MEMBER_DECLSPEC locale::id codecvt<wchar_t, char, mbstate_t>::id = { 22 };
#  endif
# endif

_STLP_STATIC_MEMBER_DECLSPEC locale::id moneypunct<char, true>::id = { 4 };
_STLP_STATIC_MEMBER_DECLSPEC locale::id moneypunct<char, false>::id = { 5 };
_STLP_STATIC_MEMBER_DECLSPEC locale::id numpunct<char>::id = { 6 } ;
_STLP_STATIC_MEMBER_DECLSPEC locale::id messages<char>::id = { 7 };

# ifndef _STLP_NO_WCHAR_T
_STLP_STATIC_MEMBER_DECLSPEC locale::id collate<wchar_t>::id = { 20 };
_STLP_STATIC_MEMBER_DECLSPEC locale::id ctype<wchar_t>::id = { 21 };

_STLP_STATIC_MEMBER_DECLSPEC locale::id moneypunct<wchar_t, true>::id = { 23 } ;
_STLP_STATIC_MEMBER_DECLSPEC locale::id moneypunct<wchar_t, false>::id = { 24 } ;

_STLP_STATIC_MEMBER_DECLSPEC locale::id numpunct<wchar_t>::id = { 25 };
_STLP_STATIC_MEMBER_DECLSPEC locale::id messages<wchar_t>::id = { 26 };
# endif

//
// locale class
//
_LocaleBase::facet::~facet() {}

#if ! defined ( _STLP_MEMBER_TEMPLATES ) || defined (_STLP_INLINE_MEMBER_TEMPLATES)
// members that fail to be templates 
bool _LocaleBase::operator()(const string& __x,
                             const string& __y) const {
  return __locale_do_operator_call(this, __x, __y);
}

#  if !defined (_STLP_NO_WCHAR_T)
bool _LocaleBase::operator()(const wstring& __x,
                             const wstring& __y) const {
  return __locale_do_operator_call(this, __x, __y);
}
#  endif
#endif

//During lib initialization _Stl_global_locale_impl points to the classic locale implementation.
static locale _Stl_loc_classic_locale(_Stl_global_locale_impl);
_STLP_STATIC_MUTEX _Stl_loc_global_locale_lock _STLP_MUTEX_INITIALIZER;

//----------------------------------------------------------------------
// class locale
void _STLP_CALL
_LocaleBase::_M_throw_runtime_error(const char* name) {
  char buf[256];

  if (name) {
    const char* prefix = "bad locale name: ";
    strcpy(buf, prefix);
    strncat(buf, name, 256 - strlen(prefix));
    buf[255] = '\0';
  }
  else {
    strcpy(buf, "locale error");
  }
  _STLP_THROW(runtime_error(buf));
}

// Initialization of the locale system.  This must be called before
// any locales are constructed.  (Meaning that it must be called when
// the I/O library itself is initialized.)
void _STLP_CALL
_Locale_impl::_S_initialize() {
  _Stl_loc_assign_ids();
  make_classic_locale();
}

// Release of the classic locale ressources. Has to be called after the last
// locale destruction and not only after the classic locale destruction as
// the facets can be shared between different facets.
void _STLP_CALL
_Locale_impl::_S_uninitialize() {
#ifdef _STLP_LEAKS_PEDANTIC
  free_classic_locale();
#endif
}

// Default constructor: create a copy of the global locale.
_LocaleBase::_LocaleBase() : _M_impl(0) {
  _M_impl = _Stl_global_locale_impl; // _S_copy_impl(_Stl_global_locale_impl); ??? - ptr
}

_LocaleBase::_LocaleBase(_Locale_impl* impl)  : _M_impl(impl) {
  /*
   * No incrementation of the _Locale_impl ref counter here as this
   * is only used once at the classic locale creation from a classic
   * locale implementation that do not have a ref counter.
   */
  _M_impl = impl; // _S_copy_impl(impl);
}

// Copy constructor
_LocaleBase::_LocaleBase(const _LocaleBase& L) _STLP_NOTHROW
  : _M_impl(0) {
  _M_impl = L._M_impl; // _S_copy_impl(L._M_impl);
}

// Destructor.
_LocaleBase::~_LocaleBase() _STLP_NOTHROW {
  // _M_impl->decr();
}

// Assignment operator.  Much like the copy constructor: just a bit of
// pointer twiddling.
const _LocaleBase& _LocaleBase::operator=(const _LocaleBase& L) _STLP_NOTHROW {
  if (this->_M_impl != L._M_impl) {
    // this->_M_impl->decr(); // ??? - ptr
    this->_M_impl = L._M_impl; // _S_copy_impl(L._M_impl); ??? - ptr
  }
  return *this;
}

_LocaleBase::facet* _LocaleBase::_M_get_facet(const _LocaleBase::id& n) const {
  return n._M_index < _M_impl->size() ? _M_impl->facets[n._M_index] : 0;
}

_LocaleBase::facet* _LocaleBase::_M_use_facet(const _LocaleBase::id& n) const {
  _LocaleBase::facet* f = (n._M_index < _M_impl->size()
                      ? _M_impl->facets[n._M_index] : 0);
  if (!f)
    _M_impl->_M_throw_bad_cast();
  return f;
}

string _LocaleBase::name() const {
  return _M_impl->name;
}

static string _Nameless("*");

// Compare two locales for equality.
bool _LocaleBase::operator==(const _LocaleBase& L) const {
  return this->_M_impl == L._M_impl ||
         (this->name() == L.name() && this->name() != _Nameless);
}

bool _LocaleBase::operator!=(const _LocaleBase& L) const {
  return !(*this == L);
}

// Static member functions.
const locale&  _STLP_CALL
_LocaleBase::classic() {
  return _Stl_loc_classic_locale;
}

locale _STLP_CALL
_LocaleBase::global(const _LocaleBase& L) {
  locale old;                   // A copy of the old global locale.

  // L._M_impl->incr();
  {
    _STLP_auto_lock lock(_Stl_loc_global_locale_lock);
    //_Stl_global_locale_impl->decr();     // We made a copy (old), so it can't be zero.
    _Stl_global_locale_impl = L._M_impl;
  }

  // Set the global C locale, if appropriate.
#if !defined(_STLP_NO_LOCALE_SUPPORT) && !defined(_STLP_WINCE) && !defined(_STLP_WCE_NET)
  if (L.name() != _Nameless)
    setlocale(LC_ALL, L.name().c_str());
#endif

  return old;
}


// static data members.

# if !defined (_STLP_STATIC_CONST_INIT_BUG) && ! defined (_STLP_USE_DECLSPEC)

const _LocaleBase::category _LocaleBase::none;
const _LocaleBase::category _LocaleBase::collate;
const _LocaleBase::category _LocaleBase::ctype;
const _LocaleBase::category _LocaleBase::monetary;
const _LocaleBase::category _LocaleBase::numeric;
const _LocaleBase::category _LocaleBase::time; 
const _LocaleBase::category _LocaleBase::messages;
const _LocaleBase::category _LocaleBase::all;

# endif

_STLP_END_NAMESPACE

//
// Facets included in classic locale :
//

