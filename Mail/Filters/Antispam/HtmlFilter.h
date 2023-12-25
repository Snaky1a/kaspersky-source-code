// HtmlFilter.h: interface for the CHtmlFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLFILTER_H__1FE509B1_01DA_4189_BA19_4648A53AEF93__INCLUDED_)
#define AFX_HTMLFILTER_H__1FE509B1_01DA_4189_BA19_4648A53AEF93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include <sstream>
#include "html_parser/htmparse.h"

#define HTML_COLOR_SEEM_LENGHT	5	// ������������ ������� ���� ������, ���������� ������������� �����

class CHtmlFilter  
{
public:
	CHtmlFilter();
	virtual ~CHtmlFilter();

	typedef vector<string> tokens_t;
	struct results_t 
	{
		unsigned long ulKnownDefsCount;			// ���������� ����� � ���� HTML
		unsigned long ulUnknownDefsCount;		// ���������� �������������� �����
		unsigned long ulSeemsColors;			// ���������� ������ ������ � ������ ����
		unsigned long ulSmallText;				// ���������� ������ � ����� ��������� �������
		unsigned long ulInvisibleCharCount;		// ���������� ��������� ��������
		unsigned long ulVisibleCharCount;		// ���������� ������� ��������
		unsigned long ulObjects;				// ���������� ���������� �������� (� ��� ����� �������)
		unsigned long ulExternalObjects;		// ���������� ���������� ������� ��������
		unsigned long ulScripts;				// ���������� ��������
		unsigned long ulHiddenElements;			// ���������� ������� ��������� (style="visibility:hidden")
		std::string   szVisibleText;			// ������� �����
		std::string   szCharset;				// ��������� ���������
		tokens_t tokens;						// ������ �������

		void clear()
		{
			ulKnownDefsCount = 0;
			ulUnknownDefsCount = 0;
			ulSeemsColors = 0;
			ulSmallText = 0;
			ulInvisibleCharCount = 0;
			ulVisibleCharCount = 0;
			ulObjects = 0;
			ulExternalObjects = 0;
			ulScripts = 0;
			ulHiddenElements = 0;
			szVisibleText.erase();
			szCharset.erase();
			tokens.clear();
		};
	};

	struct state_t								// ��������� �������� � ������ ����� ��������
	{
		bool bNeedDelimiter;					// ��� ������ ������ ���������� �������� ��� �� ����������� �����
		bool bCheckOnly;						// ������� ������� ��������� ������ �������, �� �� �������� �� ������
		unsigned long rgb_color;				// ������� ���� ������
		unsigned long rgb_bgcolor;				// ������� ���� ����
		double font_size;						// ������� ������ ��������
		
		void clear()
		{
			bNeedDelimiter = false;
			bCheckOnly = false;
			rgb_color = 0;
			rgb_bgcolor = 0xffffff;
			font_size = 7;
		}
	};

	void Process(hIO is, results_t& results);

private:
	results_t m_results;
	bool m_bBodyPresented;

	void print_element(
						html_element* pElement, 
						const state_t &state
						);

	bool CheckColors(
					 html_elt_tag* pNextTag,
					 unsigned long &rgb_color,
					 unsigned long &rgb_bgcolor
					 );

	bool CheckFontSize(
					 html_elt_tag* pNextTag,
					 double& font_size
					 );
	bool CheckHiddenText(html_elt_tag* pNextTag);
//	void ExtractTokenFromURL(const char* url);

};

#endif // !defined(AFX_HTMLFILTER_H__1FE509B1_01DA_4189_BA19_4648A53AEF93__INCLUDED_)
