// ChildFrm.cpp : CChildFrame 클래스의 구현
//

#include "stdafx.h"
#include "ClubcChat2.h"

#include "ChildFrm.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define VAR_MENU(cls, menu, var, def)			\
	void cls::On##menu()						\
	{											\
		(var) = (def);							\
	}											\
	void cls::OnUpdate##menu(CCmdUI *pCmdUI)	\
	{											\
		pCmdUI->SetCheck((var) == (def));		\
	}

#define BOOL_MENU(cls, menu, var)				\
	void cls::On##menu()						\
	{											\
		(var) = !(var);							\
	}											\
	void cls::OnUpdate##menu(CCmdUI *pCmdUI)	\
	{											\
		pCmdUI->SetCheck((var));				\
	}

void CChildFrame::OnFontChange()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFontDialog dialog(&m_lFont, CF_EFFECTS | CF_SCREENFONTS | CF_FORCEFONTEXIST | CF_NOVERTFONTS);

	if(dialog.DoModal() == IDOK)
	{
		dialog.GetCurrentFont(&m_lFont);

		UpdateFont();
	}
}


void CChildFrame::OnActClean()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_ChatDisplay.SetWindowText(_T(""));
}


BOOL_MENU(CChildFrame, ChatScroll, m_bChatScroll)

VAR_MENU(CChildFrame, SoundOn, m_SoundOpt, ALWAYS)
VAR_MENU(CChildFrame, SoundOff, m_SoundOpt, NON)
VAR_MENU(CChildFrame, SoundOndisable, m_SoundOpt, ON_DISABLE)

VAR_MENU(CChildFrame, TaskbarOn, m_TaskbarOpt, ALWAYS)
VAR_MENU(CChildFrame, TaskbarOff, m_TaskbarOpt, NON)
VAR_MENU(CChildFrame, TaskbarOndisable, m_TaskbarOpt, ON_DISABLE)

VAR_MENU(CChildFrame, SoundBell1, m_SoundKind, IDR_BELL1)
VAR_MENU(CChildFrame, SoundBell2, m_SoundKind, IDR_BELL2)
VAR_MENU(CChildFrame, SoundBell3, m_SoundKind, IDR_BELL3)

void CChildFrame::OnSoundBellother()
{
	CFileDialog dialog(TRUE, _T("wav"), NULL, OFN_PATHMUSTEXIST, NULL, this);

	if(dialog.DoModal() == IDOK)
	{
		m_OtherBellPath = dialog.GetPathName();
		m_SoundKind = OTHER_BELL;
	}
}
void CChildFrame::OnUpdateSoundBellother(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_SoundKind == OTHER_BELL);
}
