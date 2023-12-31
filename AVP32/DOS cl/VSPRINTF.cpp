#define OS2

#include <os2.h>
#include <string.h>
#include <dos.h>
#include <stdarg.h>
//#include <varargs.h>
#include "avp_os2.h"
#include "disk.h"

static int skip_atoi(const char **s);
static char far* number(char far*str, long num, int base, int size, int precision, int type);
int _sprintf(char * buf, const char *fmt, ...);
int _VSPrintf(char far *buf, const char *fmt, va_list args);

size_t strnlen(const char * s, size_t count)
 {
  const char *sc;

  for (sc = s; *sc != '\0' && count--; ++sc)
  /* nothing */;
  return sc - s;
 }

// we use this so that we can do without the ctype library
#define is_digit(c)     ((c) >= '0' && (c) <= '9')

static int skip_atoi(const char **s)
 {
  int i=0;

  while(is_digit(**s)) i = i*10 + *((*s)++) - '0';
  return i;
}

#define ZEROPAD 1               /* pad with zero */
#define SIGN    2               /* unsigned/signed long */
#define PLUS    4               /* show plus */
#define SPACE   8               /* space if plus */
#define LEFT    16              /* left justified */
#define SPECIAL 32              /* 0x */
#define LARGE   64              /* use 'ABCDEF' instead of 'abcdef' */

static char far* number(char far*str, long num, int base, int size, int precision
        ,int type)
 {
  char c,sign,tmp[66];
  const char *digits="0123456789abcdefghijklmnopqrstuvwxyz";
  int i;

  if(type & LARGE) digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if(type & LEFT)  type &= ~ZEROPAD;
  if(base < 2 || base > 36) return 0;
  c=(type & ZEROPAD) ? '0' : ' ';
  sign=0;
  if(type & SIGN)
   {
    if(num < 0)
     {
      sign = '-';
      num = -num;
      size--;
     }
    else
     if (type & PLUS)
      {
       sign = '+';
       size--;
      }
     else
      if (type & SPACE)
       {
        sign = ' ';
        size--;
       }
   }
  if(type & SPECIAL)
   {
    if(base==16) size -= 2;
    else
     if (base==8) size--;
   }
  i = 0;
  if(num == 0) tmp[i++]='0';
  else
   while (num != 0)
    {
     unsigned long __res;
     __res = ((unsigned long) num) % (unsigned long) base;
     num = ((unsigned long) num) / (unsigned long) base;
     tmp[i++] = digits[__res];
    }
  if (i > precision)
          precision = i;
  size -= precision;
  if (!(type&(ZEROPAD+LEFT)))
          while(size-->0)
                  *str++ = ' ';
  if(sign) *str++ = sign;
  if(type & SPECIAL)
   if (base==8) *str++ = '0';
   else
    if (base==16)
     {
      *str++ = '0';
      *str++ = digits[33];
     }
  if(!(type & LEFT))
    while (size-- > 0) *str++ = c;
  while(i < precision--) *str++ = '0';
  while(i-- > 0) *str++ = tmp[i];
  while(size-- > 0) *str++ = ' ';
  return str;
}

int _VSPrintf(char far*buf, const char *fmt, va_list args)
 {
  int len;
  unsigned long num;
  int i, base;
  char far*str, far*s;

  int flags;              /* flags to number() */

  int field_width;        /* width of output field */
  int precision;          /* min. # of digits for integers; max
                                   number of chars for from string */
  int qualifier;          /* 'h', 'l', or 'L' for integer fields */

  for(str=buf; *fmt ; ++fmt)
   {
    if(*fmt != '%')
     {
      switch (*fmt)
        {
         case '\t':
           for(i=8-((str - buf) % 8);i>0;i--)  *str++=' ';
           break;
         case '\n': *str++='\r';
         default:   *str++=*fmt;
        }
      continue;
     }

    /* process flags */
    flags = 0;
    repeat:
    ++fmt;          /* this also skips first '%' */
    switch (*fmt)
     {
      case '-': flags |= LEFT; goto repeat;
      case '+': flags |= PLUS; goto repeat;
      case ' ': flags |= SPACE; goto repeat;
      case '#': flags |= SPECIAL; goto repeat;
      case '0': flags |= ZEROPAD; goto repeat;
     }

    /* get field width */
    field_width = -1;
    if(is_digit(*fmt))
     field_width=skip_atoi((const char**)(&fmt));
    else
     if(*fmt == '*')
      {
       ++fmt;
       /* it's the next argument */
       field_width = va_arg(args, int);
       if (field_width < 0)
        {
         field_width = -field_width;
         flags |= LEFT;
        }
      }

    /* get the precision */
    precision = -1;
    if(*fmt == '.')
     {
      ++fmt;
      if(is_digit(*fmt))
        precision=skip_atoi((const char**)(&fmt));
      else
       if (*fmt == '*')
        {
         ++fmt;
         /* it's the next argument */
         precision = va_arg(args, int);
        }
      if(precision < 0) precision = 0;
     }

    /* get the conversion qualifier */
    qualifier = -1;
    if(*fmt == 'h' || *fmt == 'l' || *fmt == 'L')
     {
      qualifier = *fmt;
      ++fmt;
     }

    /* default base */
    base = 10;

    switch (*fmt)
    {
      case 'c':
        if(!(flags & LEFT))
          while (--field_width > 0) *str++ = ' ';
        *str++ = (unsigned char) va_arg(args, int);
        while (--field_width > 0) *str++ = ' ';
        continue;
      case 's':
        s = va_arg(args, char *);
        if (!s) s = "<NULL>";

        len = strnlen((char*)s, precision);

        if(!(flags & LEFT)) while (len < field_width--) *str++ = ' ';
        for(i=0;i<len;++i)
          switch (*s)
           {
            case '\t':
              int j;
              for(j=8-((str - buf) % 8);j>0;j--)  *str++=' ';
              break;
            case '\n': *str++='\r';
            default:   *str++=*s++;
           }
        while(len < field_width--) *str++ = ' ';
        continue;
      case 'p':
        if (field_width == -1)
         {
          field_width = 2*sizeof(void *);
          flags |= ZEROPAD;
         }
        str =number(str,(unsigned long) va_arg(args, void *), 16,
                field_width, precision, flags);
        continue;
      case 'n':
        if (qualifier == 'l')
         {
          long * ip = va_arg(args, long *);
          *ip = (str - buf);
         }
        else
         {
          int * ip = va_arg(args, int *);
          *ip = (str - buf);
         }
        continue;

    /* integer number formats - set up the flags and "break" */
      case 'o':
        base = 8;
        break;
      case 'X':
        flags |= LARGE;
      case 'x':
        base = 16;
        break;
      case 'd':
      case 'i':
        flags |= SIGN;
      case 'u':
        break;
      default:
        if (*fmt != '%') *str++ = '%';
        if (*fmt) *str++ = *fmt;
         else  --fmt;
      continue;
     }
    if(qualifier == 'l') num = va_arg(args, unsigned long);
    else
     if(qualifier == 'h')
      if (flags & SIGN) num = va_arg(args, short);
       else num = va_arg(args, unsigned short);
    else
     if(flags & SIGN) num = va_arg(args, int);
    else num = va_arg(args, unsigned int);
    str=number(str, num, base, field_width, precision, flags);
   }
  //*str='$';//'\0';
  *str='\0';

  return str-buf;
 }

int _sprintf(char *str,char const *fmt, ...)
 {
  int ret;
  va_list ArgPtr;

  va_start(ArgPtr,fmt);
  ret=_VSPrintf(str,fmt,ArgPtr);
  va_end(ArgPtr);
  return (ret);
 }

int _printf(char const *fmt, ...)
 {
  int ret;
  va_list ap;
  RMI   rmi;

   {
    SS.offset=0;

    va_start(ap, fmt);
    ret=_VSPrintf(SS.str,fmt,ap);
    SS.str[ret]='$';
    va_end(ap);

    memset(&rmi,0,sizeof(RMI));
    rmi.EAX = 0x0900;
    rmi.DS  = SS.segment;
    rmi.EDX = 0;

    ret=SimulateRMInt(0x21,&rmi);
   }

  return(ret);
 }

void FastChar(char cymb);
#pragma aux FastChar=  \
  "int 029h"           \
  parm   [ax]          ;

int _puts(char *str)
 {
  int i;

  for(; *str; ++str)
   switch (*str)
    {
     case '\t':
       for(i=8-(StrPos() % 8);i>0;i--)  FastChar(' ');//*SS.str++=' ';
       break;
     case '\n': FastChar('\r');//*SS.str++='\r';
     default:   FastChar(*str);//*SS.str++=*str;
    }
  return TRUE;
 }

UCHAR attr;
UCHAR GetCharAttr(void)
 {
  RMI    rmi;

  memset(&rmi,0,sizeof(RMI));
  rmi.EAX = 0x0800;
  rmi.EBX = 0;
  SimulateRMInt(0x10,&rmi);
  return (UCHAR)(rmi.EAX>>8);
 }

BOOL PutStrAttr(char* strWrt,UCHAR strAttr)
 {//INT 10 - VIDEO - WRITE STRING (AT and later,EGA)
  for(; *strWrt; ++strWrt)
   switch (*strWrt)
    {
     case '\n':
//       SetCharAttr(attr,' ');
       FastChar('\n');
     case '\r':
       FastChar('\r');
       SetCharAttr(attr,' ');
       break;
     default: SetCharAttr(strAttr,*strWrt);
    }

  return TRUE;
 }

