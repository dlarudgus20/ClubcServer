// ChatDisplayEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ClubcChat2.h"
#include "ChatDisplayEdit.h"


// CChatDisplayEdit

IMPLEMENT_DYNAMIC(CChatDisplayEdit, CEdit)

CChatDisplayEdit::CChatDisplayEdit()
{

}

CChatDisplayEdit::~CChatDisplayEdit()
{
}


BEGIN_MESSAGE_MAP(CChatDisplayEdit, CEdit)
END_MESSAGE_MAP()



// CChatDisplayEdit 메시지 처리기입니다.




BOOL CChatDisplayEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		if(GetKeyState(VK_RCONTROL) < 0 || GetKeyState(VK_LCONTROL) < 0)
		{
			switch((TCHAR)pMsg->wParam)
			{
			case _T('C'):
				Copy();
				return TRUE;
			}
		}
		return TRUE;
	}
	return CEdit::PreTranslateMessage(pMsg);
}
