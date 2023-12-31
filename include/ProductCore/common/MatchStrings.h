/*!
*		
*		
*		(C) 2002 Kaspersky Lab 
*		
*		\file	trafficmonitor_types.h
*		\brief	����� �������� ���� �������� ������������ �������-��������
*		
*		\author Vitaly DVi Denisov
*		\date	11.03.2004 17:32:41
*		
*		Example:	
*		
*		
*		
*/		

#ifndef _S_MATCHSTRINGS_H_
#define _S_MATCHSTRINGS_H_

//* s - �������������� ������
//* p - ������. ������ \ �������� ������������ �����������.
inline bool MatchStrings(cStringPtr s, cStringPtr p)
{
#define  V(c)   (c.at(0,cCP_SYSTEM_DEFAULT, cSTRING_TO_UPPER))
#define  U(c,p) c=V(p), p++;

	tDWORD scc; // ������� ������ ������                 
	tDWORD c, cc, lc;   // lc - ���������� ������ � [...] ������ 
	tBOOL  ok, notflag;
	
	for(;;)
	{
        U(scc,s);          // ��������� ������ ������  
		U(c,p);
        switch (c)
		{ // ��������� ������ ������� 
		case '\\':          // a*\*b 
		//case '/':          // a*\*b 
            U(c,p);
            if( c == 0 ) return false; // ������: pattern\ 
            else goto def;
		case '[':   // ����� ������ �� ������ 
            ok = notflag = 0;
            lc = 077777;      // ���������� ������� ����� 
            if(*p == '!')
			{ notflag=1; ++p; }
			
			U(cc,p);
            while( cc )
			{
				if(cc == ']')
				{   // ����� ������������ 
					if (ok)
						break;      // �������������      
					return false;     // �� �������������   
				}
				if(cc == '-')
				{   // �������� ��������  
					U(c,p);
					--s;
					if( lc <= V(s) && V(s) >= c )
						ok++;
					else if( notflag )
						// �� ��������� - ������� 
						return false;
					++s;
				}
				else
				{
					if (cc == '\\')
					{      // [\[\]] 
						U(cc,p);
						if(!cc) return false;// ������ 
					}
					if (notflag)
					{
						if (scc && scc != (lc = cc))
							ok++;          // �� ������ � ������ 
						else return false;
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
				return false;        // ������ 
			}
            continue;
		case '*':   // ����� ����� ����� �������� 
			{
            if(!*p)  return true;
            for(--s; *s; s++)
				if(MatchStrings(s, p))
					return true;
			}
			return false;
		case 0:
            return (scc == 0);
		default: def:
            if(c != scc) return false;
            continue;
		case '?':   // ���� ����� ������ 
            if (scc == 0) return false;
            continue;
		}
	}
}

//	/***********************************************************************
//	**                                                                    **
//	**   �������     :  patmat                                            **
//	**                                                                    **
//	**   ������      :  ������������ ��������� �������                    **
//	**                                                                    **
//	**   �������������: ��������� ��� �������� �� ������. ������ ���������**
//	**                  ���������� ������, ������ - ������.               **
//	**                  ���� ������ ������������� �������, �������        **
//	**                  ���������� 1, ����� ������������ 0                **
//	**                                                                    **
//	**                  ��������,                                         **
//	**                       patmat("abcdefghi","*ghi") ������ 1.         **
//	**                       patmat("abcdefghi","??c??f*") ������ 1.      **
//	**                       patmat("abcdefghi","*dh*") ������ 0.         **
//	**                       patmat("abcdefghi","*def") ������ 0.         **
//	**                       patmat("abcdef*hi","abcdef\\*hi") ������ 1.  **
//	**                       patmat("abcdef\hi","abcdef\\\\hi") ������ 1. **
//	**                                                                    **
//	**                  ��������� ���������� ����� ������� �� �������     **
//	**                  ��������� ���������, ��������� �� �������� '*'.   **
//	**                  ���� ������� ? ���������� ���� ����� ������       **
//	**                  � ������ ������� ������.                          **
//	**                  ���������� "*?" ��� "?*" ��� "**" ���������       **
//	**                  ������������� � ��������� ������ ������� �����    **
//	**                  ���� �������������� (���� ������ �����, ���       **
//	**                  ���������� ���������).                            **
//	**                                                                    **
//	**   �����       :  Sreenath Chary, Vitaly DVi Denisov (���������� �����)**
//	**                                                                    **
//	**   ������      :  ������������ ������� ������, ������� �����        **
//	**                  ������������ � ������ ������ - ��������.          **
//	**                  ������ ������ ������� ������������ � ��������     **
//	**                  ������. ���� ������� ���������, ���������� �����  **
//	**                  ������ ���������� � ������� � �������� ���������� **
//	**                  � ��� ��������� ����������� �� ��� ���, ���� ���  **
//	**                  ������ �� ��������� � ��������. ���� �� �����     **
//	**                  ���� ������ �� ������������� �������, ��          **
//	**                  ������������ �� ���������� ������� � ���� �����   **
//	**                  �� ������� '*', ���������� ��������� � ���������� **
//	**                  �������, ����� ������������ ��� �� ������� �����. **
//	**                  ���� ������� �����������, ���� �� ����� ��������� **
//	**                  ������ �������.                                   **
//	**                                                                    **
//	***********************************************************************/
//	inline bool patmat(const char *raw, const char *pat)
//	{  
//		int  i, slraw;
//	   if ((*pat == '\0') && (*raw == '\0'))    /* ���� ����� ������ � �������,   */
//		 return( 1 ) ;                          /* ���������� 1                   */
//	   if (*pat == '\0')                        /* ���� ����� �������             */
//		 return( 0 ) ;                          /* ���������� 0                   */
//	   if (                                     /* ������������� ����������� �����*/
//		   (*pat == '\\') && 
//		   (*raw != '\0') &&
//		   (*(pat+1) != '\0')
//		   )    
//		   if ( 
//			   (*(pat+1) == '*'  && *raw == '*') ||
//			   (*(pat+1) == '?'  && *raw == '?') ||
//			   (*(pat+1) == '\\' && *raw == '\\') 
//			   )
//				if (patmat(raw+1,pat+2) == 1)   /* ���������� ���������� �����    */
//				   return( 1 ) ;
//	   if (*pat == '*')                         /* ���� ������� ������ - '*'      */
//		{ if (*(pat+1) == '\0')                 /* ���� ����� ����� ����� ������� */
//			 return( 1 ) ;                      /* �� ���������� 1                */
//		  for(i=0,slraw=strlen(raw);i<=slraw;i++)/* ������������ ���������� ����� */
//			if ((*(raw+i) == *(pat+1)) ||       /*      ������ � �������          */
//				(*(pat+1) == '?') ||
//				(*(pat+1) == '*'))
//				if (patmat(
//					raw+i+( *(pat+1) != '*' ),
//					pat+2) == 1)                 /* ���� ������ ������������� �������*/
//					return( 1 ) ;                /*     ���������� 1               */
//		}
//	   else
//		{ if (*raw == '\0')                     /* ���� ����� ������              */
//			 return( 0 ) ;                      /*    ���������� 0                */
//		  if ((*pat == '?') || (*pat == *raw))  /* ���� ������� ���������         */
//			if (patmat(raw+1,pat+1) == 1)       /* ���������� ���������� �����    */
//			   return( 1 ) ;
//		}
//	   return( 0 ) ;                            /*  ���������� 0                  */
//	}
//

#endif//_S_MATCHSTRINGS_H_
