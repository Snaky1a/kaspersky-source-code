// -------------------------------------------
// Copyright � Kaspersky Labs 1996-2003.
// -------------------------------------------
// Project     -- Not defined
// Sub project -- Not defined
// Purpose     -- Not defined
// Author      -- Doukhvalow
// File Name   -- avs.cpp
// -------------------------------------------

#include "avs.h"
#include "scan.h"

#define fCOMPARE_FLAGS  (fSTRING_COMPARE_CASE_INSENSITIVE|fSTRING_COMPARE_SLASH_INSENSITIVE)

// -------------------------------------------

/* ���������� �������
����� ��� �����
1) *.exe - ��� ����� � ������ *.exe
2) test  - ��� ����� � ������ test

����� � ����������� ������
3) C:\dir\*.* - ��� ����� � ���������� C:\dir\
4) C:\dir\*.exe - ��� ����� � ������ *.exe � ���������� C:\dir\
5) C:\dir\test - ������ ���� C:\dir\test
6) C:\dir\ - ��� ����� � ���������� C:\dir\ � ���� � ��������������

����� � �������������� ������
7) dir\*.* - ��� ����� �� ���� ����������� dir\
8) dir\test - ��� ����� test �� ���� ����������� dir\
9) dir\*.exe - ��� ����� � ������� *.exe �� ���� ����������� dir\
10) dir\ - ��� ����� �� ���� ����������� dir\ � ���� �� ��������������
*/

/* ����� �������
����� ��� �����
1)  *.exe        - ��� ����� � ������ *.exe
2)  test         - ��� ����� � ������ test

����� � ����������� ������
3)  C:\dir\*.*   - ��� ����� � ���������� C:\dir\
4)  C:\dir\*     - ��� ����� � ���������� C:\dir\
5)  C:\dir\      - ��� ����� � ���������� C:\dir\
6)  C:\dir\*.exe - ��� ����� � ������ *.exe � ���������� C:\dir\
7)  C:\dir\test  - ����� � ������ test � ���������� C:\dir\

����� � �������������� ������
8)  dir\*.*      - ��� ����� � ���������� dir\
9)  dir\*        - ��� ����� � ���������� dir\
10) dir\         - ��� ����� � ���������� dir\
11) dir\*.exe    - ��� ����� � ������ *.exe � ���������� dir\
12) dir\test     - ����� � ������ test � ���������� dir\

��� ������� ����� 1 � 2 ����� �� ������� � ��������������, ���� bRecurse = false
*/

// -------------------------------------------

//* s - �������������� ������
//* p - ������. ������ \ �������� ������������ �����������.
bool CMaskChecker::MatchStrings(cStringPtr s, cStringPtr p)
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
		case '/':          // a*\*b 
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

// -------------------------------------------

CMaskChecker::CMaskChecker(cStringObj& strPath, bool bShort) :
	m_strPath(strPath),
	m_bShort(bShort),
	m_nNamePos(m_strPath, m_strPath.find_last_of(L"\\/"))
{
	if( !*m_nNamePos )
		m_nNamePos = m_strPath;
	else
		m_nNamePos++;
}

bool CMaskChecker::MatchPath(cStringObj& strMask, bool bRecurse, bool bCheckAbsolute)
{
	if( !m_nNamePos && !m_nNamePos.size() )
		return false;

	bool bAbsolute = IsAbsolute(strMask);
	if( bAbsolute && !bCheckAbsolute )
		return false;

	if( m_bShort && strMask.find_first_of(L"*") != cStrObj::npos )
		return false;

	cStringPtr nMaskNamePos(strMask, strMask.find_last_of("\\/"));
	if( !*nMaskNamePos )
		nMaskNamePos = strMask;
	else
		nMaskNamePos++;

	if( m_nNamePos < nMaskNamePos )
		return false;

	if( bAbsolute ) // ����� � ����������� ������
	{
		// ���� �� ��������� ���� ����� � �������, �� ������������
		if( m_strPath.compare(0, nMaskNamePos, strMask, 0, nMaskNamePos, fCOMPARE_FLAGS) )
			return false;

		// ���� ��������� ������������� � ���� �������������� ����, �� ������������
		if( !bRecurse && (tUINT)nMaskNamePos != (tUINT)m_nNamePos )
			return false;
	}
	else if( (tUINT)nMaskNamePos ) // ����� � �������������� ������
	{
		// ���� �� ������ ���� ����� � ���� �������, �� ������������
		cStringPtr nMaskDirPos(m_strPath, m_strPath.find(cStringObj(strMask, 0, nMaskNamePos),
			0, cStringObj::whole, fCOMPARE_FLAGS|fSTRING_FIND_BACKWARD));

		if( !*nMaskDirPos )
			return false;

        // check subpath found to start exactly at folder begining
        if( (tUINT)nMaskDirPos != 0 && *(nMaskDirPos-1) != '\\' && *(nMaskDirPos-1) != '/' )
            return false;

		// ���� ��������� ������������� � ���� �������������� ���� ����� ���������� ���� �����, �� ������������
		if( !bRecurse && (((tUINT)nMaskDirPos + (tUINT)nMaskNamePos) != (tUINT)m_nNamePos) )
			return false;
	}
	
	// ���� ����� "���"
	if( !*nMaskNamePos || !nMaskNamePos.compare("*") || !nMaskNamePos.compare("*.*") )
	{
		// ���� ��� �� ������, �� ����������
		if( !!*m_nNamePos )
			return true;
		
		// ���� ���������� � ����������, �� ����������
		if( bRecurse && (tUINT)nMaskNamePos )
			return true;
		
		// ����� ������������
		return false;
	}

	// ���� ����� ������������� �� ".*" ��� �� ".", � ��� ����� ��� ����������, �� �������� ����� �� �����
	tDWORD nMaskSize = nMaskNamePos.size();
	if (*m_nNamePos && nMaskSize >= 2)
	{
		tDWORD nPointEndOffset = 0;
		if (nMaskNamePos[nMaskSize - 2] == L'.' && nMaskNamePos[nMaskSize - 1] == L'*')
			nPointEndOffset = 2;
		else if (nMaskNamePos[nMaskSize - 1] == L'.')
			nPointEndOffset = 1;
		if (nPointEndOffset)
		{
			tDWORD nExtPos = m_strPath.find(L".", (tUINT)m_nNamePos, cStrObj::whole, fSTRING_FIND_BACKWARD);
			if( nExtPos == cStrObj::npos )
			{
				cStrObj strNameOnlyMask;
				strNameOnlyMask.assign(strMask, (tUINT)nMaskNamePos, nMaskSize - nPointEndOffset);
				return MatchStrings(m_nNamePos, cStringPtr(strNameOnlyMask));
			}
		}
	}
	
	return MatchStrings(m_nNamePos, nMaskNamePos);
}

// -------------------------------------------
