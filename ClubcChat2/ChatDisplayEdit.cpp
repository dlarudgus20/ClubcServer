// ChatDisplayEdit.cpp : ���� �����Դϴ�.
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



// CChatDisplayEdit �޽��� ó�����Դϴ�.




BOOL CChatDisplayEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
