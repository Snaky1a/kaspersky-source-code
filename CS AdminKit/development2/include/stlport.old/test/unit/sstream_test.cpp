#include <string>
#include <sstream>
#include <memory>

#include "full_streambuf.h"

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class SstreamTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(SstreamTest);
  CPPUNIT_TEST(output);
  CPPUNIT_TEST(input);
  CPPUNIT_TEST(io);
  CPPUNIT_TEST(err);
  CPPUNIT_TEST(err_long);
  CPPUNIT_TEST(maxint);
  CPPUNIT_TEST(init_in);
  CPPUNIT_TEST(init_out);
  CPPUNIT_TEST(buf);
  CPPUNIT_TEST(rdbuf);
  CPPUNIT_TEST(streambuf_output);
  CPPUNIT_TEST(seek);
  CPPUNIT_TEST_SUITE_END();

  protected:
    void output();
    void input();
    void io();
    void err();
    void err_long();
    void maxint();
    void init_in();
    void init_out();
    void buf();
    void rdbuf();
    void streambuf_output();
    void seek();
};

CPPUNIT_TEST_SUITE_REGISTRATION(SstreamTest);

//
// tests implementation
//
void SstreamTest::output()
{
  ostringstream s;

  s << 1 << '\n' << 2.0 << '\n' << "abcd\n" << "ghk lm\n" << "abcd ef";
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( s.str() == "1\n2\nabcd\nghk lm\nabcd ef" );
}

void SstreamTest::input()
{
  istringstream s( "1\n2\nabcd\nghk lm\nabcd ef" );
  int i = 0;
  s >> i;
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( i == 1 );
  double d = 0.0;
  s >> d;
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( d == 2.0 );
  string str;
  s >> str;
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( str == "abcd" );
  char c = s.get(); // extract newline, that not extracted by operator >>
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( c == '\n' );
  getline( s, str );
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( str == "ghk lm" );
  getline( s, str );
  CPPUNIT_ASSERT( s.eof() );
  CPPUNIT_ASSERT( str == "abcd ef" );
}

void SstreamTest::io()
{
  stringstream s;
  s << 1 << '\n' << 2.0 << '\n' << "abcd\n" << "ghk lm\n" << "abcd ef";
  CPPUNIT_ASSERT( s.good() );

  int i = 0;
  s >> i;
  CPPUNIT_ASSERT( i == 1 );
  CPPUNIT_ASSERT( s.good() );
  double d = 0.0;
  s >> d;
  CPPUNIT_ASSERT( d == 2.0 );
  CPPUNIT_ASSERT( s.good() );
  string str;
  s >> str;
  CPPUNIT_ASSERT( str == "abcd" );
  CPPUNIT_ASSERT( s.good() );
  char c = s.get(); // extract newline, that not extracted by operator >>
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( c == '\n' );
  getline( s, str );
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( str == "ghk lm" );
  getline( s, str );
  CPPUNIT_ASSERT( str == "abcd ef" );
  CPPUNIT_ASSERT( s.eof() );
}

void SstreamTest::err()
{
  stringstream s( "9" );

  int i = 0;
  s >> i;
  CPPUNIT_ASSERT( !s.fail() );
  CPPUNIT_ASSERT( i == 9 );
  s >> i;
  CPPUNIT_ASSERT( s.fail() );
  CPPUNIT_ASSERT( s.eof() );
  CPPUNIT_ASSERT( i == 9 );
}

void SstreamTest::err_long()
{
  stringstream s( "9" );

  long i = 0;
  s >> i;
  CPPUNIT_ASSERT( !s.fail() );
  CPPUNIT_ASSERT( i == 9 );
  s >> i;
  CPPUNIT_ASSERT( s.fail() );
  CPPUNIT_ASSERT( s.eof() );
  CPPUNIT_ASSERT( i == 9 );
}

void SstreamTest::maxint()
{
  stringstream s;

  s << INT_MAX << " " << UINT_MAX << " " << LONG_MAX << " " << ULONG_MAX << " "
    << INT_MIN << " " << LONG_MIN;
  CPPUNIT_ASSERT( s.good() );

  int i = 0;
  unsigned int u = 0;
  long l = 0;
  unsigned long ul = 0;

  s >> i >> u >> l >> ul;
  CPPUNIT_ASSERT( s.good() );
  CPPUNIT_ASSERT( i == INT_MAX );
  CPPUNIT_ASSERT( u == UINT_MAX );
  CPPUNIT_ASSERT( l == LONG_MAX );
  CPPUNIT_ASSERT( ul == ULONG_MAX );

  s >> i >> l;
  CPPUNIT_ASSERT( !s.fail() );
  CPPUNIT_ASSERT( i == INT_MIN );
  CPPUNIT_ASSERT( l == LONG_MIN );
}

void SstreamTest::init_in()
{
  istringstream is( "12345" );
  int n;

  is >> n;
  CPPUNIT_ASSERT( !is.fail() );
  CPPUNIT_ASSERT( n == 12345 );
}

void SstreamTest::init_out()
{
  ostringstream os( "12345" );
  CPPUNIT_ASSERT( os.str() == "12345" );

  os << 67;
  CPPUNIT_ASSERT( os.good() );

  // This satisfy to the Standard:
  CPPUNIT_ASSERT( os.str() == "67345" );
  // But we don't know the reason, why standard state that.

  os.str( "89ab" );
  CPPUNIT_ASSERT( os.str() == "89ab" );

  os << 10;
  CPPUNIT_ASSERT( os.good() );
  CPPUNIT_ASSERT( os.str() == "10ab" );
}

void SstreamTest::buf()
{
  stringstream ss;

  ss << "1234567\n89\n";
  char buf[10];
  buf[7] = 'x';
  ss.get( buf, 10 );
  CPPUNIT_ASSERT( !ss.fail() );
  CPPUNIT_ASSERT( buf[0] == '1' );
  CPPUNIT_ASSERT( buf[1] == '2' );
  CPPUNIT_ASSERT( buf[2] == '3' );
  CPPUNIT_ASSERT( buf[3] == '4' );
  CPPUNIT_ASSERT( buf[4] == '5' );
  CPPUNIT_ASSERT( buf[5] == '6' );
  CPPUNIT_ASSERT( buf[6] == '7' ); // 27.6.1.3 paragraph 10, paragraph 7
  CPPUNIT_ASSERT( buf[7] == 0 ); // 27.6.1.3 paragraph 8
  char c;
  c = ss.get();
  CPPUNIT_ASSERT( !ss.fail() );
  CPPUNIT_ASSERT( c == '\n' ); // 27.6.1.3 paragraph 10, paragraph 7
  c = ss.get();
  CPPUNIT_ASSERT( !ss.fail() );
  CPPUNIT_ASSERT( c == '8' );
}

void SstreamTest::rdbuf()
{
  stringstream ss;

  ss << "1234567\n89\n";

  ostringstream os;
  ss.get( *os.rdbuf(), '\n' );
  CPPUNIT_ASSERT( !ss.fail() );
  char c;
  c = ss.get();
  CPPUNIT_ASSERT( !ss.fail() );
  CPPUNIT_ASSERT( c == '\n' ); // 27.6.1.3 paragraph 12
  CPPUNIT_ASSERT( os.str() == "1234567" );
}

void SstreamTest::streambuf_output()
{
  {
    istringstream in("01234567890123456789");
    CPPUNIT_ASSERT( in );

    auto_ptr<full_streambuf> pfull_buf(new full_streambuf(10));
    ostream out(pfull_buf.get());
    CPPUNIT_ASSERT( out );

    out << in.rdbuf();
    CPPUNIT_ASSERT( out );
    CPPUNIT_ASSERT( in );
    //out is good we can check what has been extracted:
    CPPUNIT_ASSERT( pfull_buf->str() == "0123456789" );

    out << in.rdbuf();
    CPPUNIT_ASSERT( out.fail() );
    CPPUNIT_ASSERT( in );

    ostringstream ostr;
    ostr << in.rdbuf();
    CPPUNIT_ASSERT( ostr );
    CPPUNIT_ASSERT( in );
    CPPUNIT_ASSERT( ostr.str() == "0123456789" );
  }

#if defined (_STLP_USE_EXCEPTIONS)
  {
    //If the output stream buffer throws:
    istringstream in("01234567890123456789");
    CPPUNIT_ASSERT( in );

    auto_ptr<full_streambuf> pfull_buf(new full_streambuf(10, true));
    ostream out(pfull_buf.get());
    CPPUNIT_ASSERT( out );

    out << in.rdbuf();
    CPPUNIT_ASSERT( out.bad() );
    CPPUNIT_ASSERT( in );
    //out is bad we have no guaranty on what has been extracted:
    //CPPUNIT_ASSERT( pfull_buf->str() == "0123456789" );

    out.clear();
    out << in.rdbuf();
    CPPUNIT_ASSERT( out.fail() && out.bad() );
    CPPUNIT_ASSERT( in );

    ostringstream ostr;
    ostr << in.rdbuf();
    CPPUNIT_ASSERT( ostr );
    CPPUNIT_ASSERT( in );
    CPPUNIT_ASSERT( ostr.str() == "01234567890123456789" );
  }
#endif
}

void SstreamTest::seek()
{
  stringstream s( "0123456789" );

  CPPUNIT_ASSERT( s.tellg() == stringstream::pos_type(0) );
  s.seekg( 6, ios::beg );
  CPPUNIT_ASSERT( s.tellg() == stringstream::pos_type(6) );
  s.seekg( -3, ios::cur );
  CPPUNIT_ASSERT( s.tellg() == stringstream::pos_type(3) );

  istringstream is( "0123456789" );
  CPPUNIT_ASSERT( is.tellg() == stringstream::pos_type(0) );
  is.seekg( 6, ios::beg );
  CPPUNIT_ASSERT( is.tellg() == stringstream::pos_type(6) );
  is.seekg( -3, ios::cur );
  CPPUNIT_ASSERT( is.tellg() == stringstream::pos_type(3) );
}
