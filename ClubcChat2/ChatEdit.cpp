// ChatEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ClubcChat2.h"
#include "ChatEdit.h"
#include "ChildFrm.h"
#include "MainFrm.h"

// CChatEdit

IMPLEMENT_DYNAMIC(CChatEdit, CEdit)

CChatEdit::CChatEdit(CChildFrame *pWnd)
	: m_pWnd(pWnd)
{

}

CChatEdit::~CChatEdit()
{
}


BEGIN_MESSAGE_MAP(CChatEdit, CEdit)
END_MESSAGE_MAP()



// CChatEdit 메시지 처리기입니다.




BOOL CChatEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	switch(pMsg->message)
	{
	case WM_CHAR:
		if((TCHAR)pMsg->wParam == _T('\r') && GetWindowTextLength() > 0 && m_pWnd->m_sock.IsConnected())
		{
			// TODO: 엔터 입력시 처리
			CString strTitle, strSend;

			GetWindowText(strTitle);
			strSend.Format(TEXT("%s : %s"), CString(m_pWnd->m_Nickname), strTitle);

			if(m_pWnd->m_sock.SendChatString(strSend) <= 0)
			{
				m_pWnd->DestroyWindow();
			}

			SetWindowText(_T(""));
			return TRUE;
		}
	case WM_KEYDOWN:
		if(GetKeyState(VK_RCONTROL) < 0 || GetKeyState(VK_LCONTROL) < 0)
		{
			switch((TCHAR)pMsg->wParam)
			{
			case _T('X'):
				Cut();
				return TRUE;
			case _T('C'):
				Copy();
				return TRUE;
			case _T('V'):
				Paste();
				return TRUE;
			}
		}
	}
	return CEdit::PreTranslateMessage(pMsg);
}
