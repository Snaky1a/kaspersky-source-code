#include <stdio.h>
#include <string.h>
#include <locale.h>
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

    // ���������, ��� smy ����� ����� smax � smin
int syinsy(unsigned smin, unsigned smy, unsigned smax)
     {
      char left   [2];
      char right  [2];
      char middle [2];

      left  [0]   = smin;  left  [1]   = '\0';
      right [0]   = smax;  right [1]   = '\0';
      middle[0]   = smy;   middle[1]   = '\0';

//      return (strcoll(left, middle) <= 0 && strcoll(middle, right) <= 0);
        return (strcmp(left, middle) <= 0 && strcmp(middle, right) <= 0);
     }

    #define  U(c) ((c) & 0377)  // ���������� ���������� ����� 
    #define  QUOT    '\\'       // ������������ ������         
    #ifndef  MATCH_ERR
//    # define MATCH_ERR printf("��� ]\n")
    # define MATCH_ERR
    #endif

    //* s - �������������� ������
    //* p - ������. ������ \ �������� ������������ �����������.

int match(const register char *s, const register char *p)
     {
      register int    scc; // ������� ������ ������                 
      int     c, cc, lc;   // lc - ���������� ������ � [...] ������ 
      int     ok, notflag;

      for(;;)
       {
        scc = U(*s++);          // ��������� ������ ������  
        switch (c = U (*p++))
         { // ��������� ������ ������� 
          case QUOT:          // a*\*b 
            c = U (*p++);
            if( c == 0 ) return(0); // ������: pattern\ 
            else goto def;
          case '[':   // ����� ������ �� ������ 
            ok = notflag = 0;
            lc = 077777;      // ���������� ������� ����� 
            if(*p == '!')
             { notflag=1; p++; }

            while (cc = U (*p++))
             {
              if(cc == ']')
               {    // ����� ������������ 
                if (ok)
                      break;      // �������������      
                return (0);     // �� �������������   
               }
              if(cc == '-')
               {    // �������� ��������  
                if (notflag)
                 {
                  // �� �� ��������� - OK 
                  if (!syinsy (lc, scc, U (*p++)))
                     ok++;
                  // �� ��������� - ������� 
                  else return (0);
                 }
                else
                 {
                  // ������ �� ��������� - OK 
                  if (syinsy (lc, scc, U (*p++)))
                     ok++;
                 }
               }
              else
               {
                if (cc == QUOT)
                 {      // [\[\]] 
                  cc = U(*p++);
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
             }
            if (cc == 0)
             {    // ����� ������ 
              MATCH_ERR;
              return (0);        // ������ 
             }
            continue;
          case '*':   // ����� ����� ����� �������� 
            if(!*p)  return (1);
            for(s--; *s; s++)
                if(match (s, p))
                    return (1);
            return (0);
          case 0:
            return (scc == 0);
          default: def:
            if(c != scc) return (0);
            continue;
          case '?':   // ���� ����� ������ 
            if (scc == 0) return (0);
            continue;
         }
       }
     }


// �������� �������� �� ��, ��� � UNIX �����������  ��������  ����  ������,  �����  *.c,
// ����������  ��  ������������ ������� (��� � MS DOS), � ���������-������������� ������
// ������������ (shell: /bin/sh, /bin/csh, /bin/ksh).   ���  ���������  ������������  (�
// ��������) ������ ����� �������� ����.
