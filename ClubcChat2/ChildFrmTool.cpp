// ChildFrm.cpp : CChildFrame 클래스의 구현
//

#include "stdafx.h"
#include "ClubcChat2.h"

#include "ChildFrm.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


struct MyFindFontStruct
{
	LPCTSTR strFont;
	BOOL bFind;
	LOGFONT lfont;
};
HFONT CChildFrame::FindFont(HDC hdc, LPCTSTR font)
{
	MyFindFontStruct s = { font, FALSE, };

	EnumFontFamilies(hdc, NULL, (FONTENUMPROC)FindFontProc, (LPARAM)&s);
	if(s.bFind)
	{
		s.lfont.lfWidth = 8;
		s.lfont.lfHeight = 16;
		return ::CreateFontIndirect(&s.lfont);
	}
	else
	{
		return NULL;
	}
}
int CALLBACK CChildFrame::FindFontProc(ENUMLOGFONT *lpelf, NEWTEXTMETRIC *lpntm, int FontType, LPARAM lParam)
{
	if(lstrcmp(lpelf->elfFullName, ((MyFindFontStruct *)lParam)->strFont) == 0)
	{
		((MyFindFontStruct *)lParam)->lfont = lpelf->elfLogFont;
		((MyFindFontStruct *)lParam)->bFind = TRUE;
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


void CChildFrame::SetListBoxHScrollBar(CListBox &ListBox)
{
	// SetListBoxHScrollBar source is made by "sizeof"
	DWORD Style = ::GetWindowLongPtr(ListBox, GWL_STYLE);
	::SetWindowLongPtr(ListBox, GWL_STYLE, Style | LB_SETHORIZONTALEXTENT);
	::SendMessage(ListBox, LB_SETHORIZONTALEXTENT, 4000, 0);
	::SetScrollRange(ListBox, SB_HORZ, 0, 4000, TRUE);
}
