#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#if !defined(_UNICODE)
__inline unsigned int __cdecl _wcsnextc(const wchar_t * _cpc) { return (unsigned int)*_cpc; }
__inline wchar_t * __cdecl _wcsninc(const wchar_t * _pc, size_t _sz) { return (wchar_t *)(_pc+_sz); }
__inline wchar_t * __cdecl _wcsdec(const wchar_t * _cpc1, const wchar_t * _cpc2) { return (wchar_t *)((_cpc1)>=(_cpc2) ? NULL : ((_cpc2)-1)); }
__inline wchar_t * __cdecl _wcsinc(const wchar_t * _pc) { return (wchar_t *)(_pc+1); }
_CRTIMP wchar_t*  __cdecl wcscat(wchar_t *, const wchar_t *);
#endif

// 7.41.  �������� ������� match(������,������); ��� �������� ������������ ������  ����-
// ������� ����������� ��������� � ����� ����. ����������� �������:
// 
//         * - ����� ����� ����� �������� (0 � �����);
//         ? - ���� ����� ������.
//                       ����������:
//         [�����]  - ����� �� ������������� ����.
//         [!�����] - ����� �� ����, ����� �������������.
//         [h-z]    - ����� �� ���� �� h �� z ������������.
// 
// ��������: ��� �������� "�������" ������ ����������� ����������� ����� ����  ��  ����-
// ���.
//      ��������� ��� �������, �������� ���������,  �������  ��������  ��  �����  �����,
// ���������������  ��������� ������� (��������, "[��]*�*�"). ������� � ����, ��� ������
// ������ ���� ������� ������� �� �����, � ����� ��������� ������ �����.

//    #include <stdio.h>
//    #include <string.h>
//    #include <locale.h>

// ---
#define SWAB(a, b) { a^=b; b^=a; a^=b; }

// ���������, ��� smy ����� ����� smax � smin
int syinsyW(unsigned smin, unsigned smy, unsigned smax)
     {
			if ( smin & 0xffffff00 ) SWAB(*((char *)&smin + 0), *((char *)&smin + 1));
			if ( smax & 0xffffff00 ) SWAB(*((char *)&smax + 0), *((char *)&smax + 1));
			if ( smy  & 0xffffff00 ) SWAB(*((char *)&smy  + 0), *((char *)&smy  + 1));

//      return (strcoll(left, middle) <= 0 && strcoll(middle, right) <= 0);
        return (wcscmp((wchar_t *)&smin, (wchar_t *)&smy) <= 0 && wcscmp((wchar_t *)&smy, (wchar_t *)&smax) <= 0);
     }

    #define  U(c,p) c=_wcsnextc(p) & 0xffff; p=_wcsinc(p);  // ���������� ���������� ����� 
    #define  QUOT    L'\\'       // ������������ ������         
    #ifndef  MATCH_ERR
//    # define MATCH_ERR printf("��� ]\n")
    # define MATCH_ERR
    #endif

    //* s - �������������� ������
    //* p - ������. ������ \ �������� ������������ �����������.

int matchW(const register wchar_t *s, const register wchar_t *p)
     {
      register int    scc; // ������� ������ ������                 
      int     c, cc, lc;   // lc - ���������� ������ � [...] ������ 
      int     ok, notflag;
			const wchar_t  *ss = s;

      for(;;)
       {
        U(scc,s);          // ��������� ������ ������  
				U(c,p);
        switch (c)
         { // ��������� ������ ������� 
          case QUOT:          // a*\*b 
            U(c,p);
            if( c == 0 ) return(0); // ������: pattern\ 
            else goto def;
          case L'[':   // ����� ������ �� ������ 
            ok = notflag = 0;
            lc = 077777;      // ���������� ������� ����� 
            if(_wcsnextc(p) == L'!')
             { notflag=1; p=_wcsinc(p); }

						U(cc,p);
            while (cc)
             {
              if(cc == L']')
               {    // ����� ������������ 
                if (ok)
                      break;      // �������������      
                return (0);     // �� �������������   
               }
              if(cc == L'-')
               {    // �������� ��������  
                if (notflag)
                 {
                  // �� �� ��������� - OK 
									U(c,p);
                  if (!syinsyW (lc, scc, c))
                     ok++;
                  // �� ��������� - ������� 
                  else return (0);
                 }
                else
                 {
                  // ������ �� ��������� - OK 
									U(c,p);
                  if (syinsyW (lc, scc, c))
                     ok++;
                 }
               }
              else
               {
                if (cc == QUOT)
                 {      // [\[\]] 
									U(cc,p);
                  if(!cc) return(0);// ������ 
                 }
                if (notflag)
                 {
                  if (scc && scc != (lc = cc))
                    ok++;          // �� ������ � ������ 
                  else return (0);
                 }
                else
                 {
                  if (scc == (lc = cc)) // ������ � ������ 
                    ok++;
                 }
               }
							U(cc,p);
						}
            if (cc == 0)
             {    // ����� ������ 
              MATCH_ERR;
              return (0);        // ������ 
             }
            continue;
          case L'*':   // ����� ����� ����� �������� 
            if(!*p)  return (1);
            for(s=_wcsdec(ss, s); s && _wcsnextc(s); s=_wcsinc(s))
              if(matchW(s, p))
                return (1);
            return (0);
          case 0:
            return (scc == 0);
          default: def:
            if(c != scc) return (0);
            continue;
          case L'?':   // ���� ����� ������ 
            if (scc == 0) return (0);
            continue;
         }
       }
     }


// ����������� ������ ������� ��� �������� �������� ���� (Windows). 
// �� �������������� ��������� ���� "[��]", "[!��]", "\Uu"
int matchWF(const register wchar_t *s, const register wchar_t *p)
	{
	register int  scc; // ������� ������ ������                 
	int     c;  
	const wchar_t  *ss = s;
	
	for(;;)
		{
		  U(scc,s);          // ��������� ������ ������  
			U(c,p);
      switch (c)
				{ // ��������� ������ ������� 
        case L'*':   // ����� ����� ����� �������� 
          if(!*p)  return (1);
          for(s=_wcsdec(ss, s); s && _wcsnextc(s); s=_wcsinc(s))
            if(matchW(s, p))
              return (1);
						return (0);
        case 0:
          return (scc == 0);
        default: 
          if(c != scc) return (0);
          continue;
        case L'?':   // ���� ����� ������ 
          if (scc == 0) return (0);
          continue;
			}
		}
	}

// �������� �������� �� ��, ��� � UNIX �����������  ��������  ����  ������,  �����  *.c,
// ����������  ��  ������������ ������� (��� � MS DOS), � ���������-������������� ������
// ������������ (shell: /bin/sh, /bin/csh, /bin/ksh).   ���  ���������  ������������  (�
// ��������) ������ ����� �������� ����.
