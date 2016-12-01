
// ChildFrm.cpp : CChildFrame 클래스의 구현
//

#include "stdafx.h"
#include "ClubcChat2.h"

#include "ChildFrm.h"
#include "MainFrm.h"

#include "RoomDialog.h"

#include "../Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()

	ON_COMMAND(ID_FONT_CHANGE, &CChildFrame::OnFontChange)

	ON_COMMAND(ID_CHAT_SCROLL, &CChildFrame::OnChatScroll)
	ON_UPDATE_COMMAND_UI(ID_CHAT_SCROLL, &CChildFrame::OnUpdateChatScroll)

	ON_COMMAND(ID_SOUND_ON, &CChildFrame::OnSoundOn)
	ON_COMMAND(ID_SOUND_OFF, &CChildFrame::OnSoundOff)
	ON_COMMAND(ID_SOUND_ONDISABLE, &CChildFrame::OnSoundOndisable)
	ON_UPDATE_COMMAND_UI(ID_SOUND_ON, &CChildFrame::OnUpdateSoundOn)
	ON_UPDATE_COMMAND_UI(ID_SOUND_OFF, &CChildFrame::OnUpdateSoundOff)
	ON_UPDATE_COMMAND_UI(ID_SOUND_ONDISABLE, &CChildFrame::OnUpdateSoundOndisable)

	ON_COMMAND(ID_TASKBAR_ON, &CChildFrame::OnTaskbarOn)
	ON_COMMAND(ID_TASKBAR_OFF, &CChildFrame::OnTaskbarOff)
	ON_COMMAND(ID_TASKBAR_ONDISABLE, &CChildFrame::OnTaskbarOndisable)
	ON_UPDATE_COMMAND_UI(ID_TASKBAR_ON, &CChildFrame::OnUpdateTaskbarOn)
	ON_UPDATE_COMMAND_UI(ID_TASKBAR_OFF, &CChildFrame::OnUpdateTaskbarOff)
	ON_UPDATE_COMMAND_UI(ID_TASKBAR_ONDISABLE, &CChildFrame::OnUpdateTaskbarOndisable)

	ON_COMMAND(ID_SOUND_BELL1, &CChildFrame::OnSoundBell1)
	ON_COMMAND(ID_SOUND_BELL2, &CChildFrame::OnSoundBell2)
	ON_COMMAND(ID_SOUND_BELL3, &CChildFrame::OnSoundBell3)
	ON_COMMAND(ID_SOUND_BELLOTHER, &CChildFrame::OnSoundBellother)
	ON_UPDATE_COMMAND_UI(ID_SOUND_BELL1, &CChildFrame::OnUpdateSoundBell1)
	ON_UPDATE_COMMAND_UI(ID_SOUND_BELL2, &CChildFrame::OnUpdateSoundBell2)
	ON_UPDATE_COMMAND_UI(ID_SOUND_BELL3, &CChildFrame::OnUpdateSoundBell3)
	ON_UPDATE_COMMAND_UI(ID_SOUND_BELLOTHER, &CChildFrame::OnUpdateSoundBellother)
	ON_COMMAND(ID_ACT_CLEAN, &CChildFrame::OnActClean)

	ON_COMMAND(ID_ACT_USE_ROOMEXT, &CChildFrame::OnUseRoomext)
	ON_COMMAND(ID_ACT_CHANGE_ROOM, &CChildFrame::OnActChangeRoom)
	ON_UPDATE_COMMAND_UI(ID_ACT_USE_ROOMEXT, &CChildFrame::OnUpdateUseRoomext)
	ON_UPDATE_COMMAND_UI(ID_ACT_CHANGE_ROOM, &CChildFrame::OnUpdateActChangeRoom)
END_MESSAGE_MAP()

// CChildFrame 생성/소멸

CChildFrame::CChildFrame()
	: m_sock(this), m_ChatEdit(this), m_FontName(_T("")), m_bChatScroll(true), bClickedUseRoomExt(false)
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~FWS_ADDTOTITLE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서 Window 클래스 또는 스타일을 수정합니다.
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 진단

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 메시지 처리기


int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	try
	{
		RECT rt = { 0, 0, 100, 100 };
		CString CntMsg;

		SetWindowText(TEXT("ClubcChat2 - No Room Ext"));

		if(m_LoginDialog.DoModal() != IDOK)
		{
			return -1;
		}

		m_ChatDisplay.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL
			| ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE, rt, this, 1);
		m_ChatEdit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, rt, this, 2);
		m_CntListBox.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | /*WS_VSCROLL | WS_HSCROLL |*/ LBS_SORT, rt, this, 3);

		SetListBoxHScrollBar(m_CntListBox);

		m_ChatEdit.SetLimitText(CHAT_DATA_BUF / 2 - 1);
		m_ChatEdit.EnableWindow(FALSE);

		InitOption();

		struct SIdPw
		{
			char *strId, *strPass;
			SIdPw(CChildFrame *pWnd)
			{
				strId = ChrCvt_WideCharToUTF8(CStringW(pWnd->m_LoginDialog.m_Id));
				strPass = ChrCvt_WideCharToUTF8(CStringW(pWnd->m_LoginDialog.m_Pass));
			}
			~SIdPw()
			{
				ChrCvt_Free(strId);
				ChrCvt_Free(strPass);
			}
		} IdPw(this);
		m_sock.Create(m_LoginDialog.m_SrvIp, IdPw.strId, IdPw.strPass);

		m_LoginDialog.WriteDataToReg();
	}
	catch(CClubcChatSock::CClubcChatSockException /*e*/)
	{
		MessageBox(CClubcChat2App::ResStr(IDS_MSGBOX_SOCK_CREATE_ERR), CClubcChat2App::ResStr(IDS_MSGBOX_TITLE_ERR), MB_OK | MB_ICONERROR);
		return -1;
	}

	return 0;
}


void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWndEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	UpdateScreen();
}


void CChildFrame::OnDestroy()
{
	CMDIChildWndEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SaveOption();
}


void CChildFrame::UpdateScreen()
{
	const int CntListXSize = 150;
	int ChatEditYSize = abs(m_lFont.lfHeight);//HIWORD(::GetDialogBaseUnits());
	CView *pView = GetActiveView();
	RECT rt;

	if(IsWindow(*pView))
	{
		pView->GetClientRect(&rt);
		if(IsWindow(m_ChatDisplay))
		{
			m_ChatDisplay.MoveWindow(0, 0, rt.right + 1 - CntListXSize, rt.bottom - ChatEditYSize);
		}

		if(IsWindow(m_ChatEdit))
		{
			m_ChatEdit.MoveWindow(0, rt.bottom - ChatEditYSize, rt.right + 1 - CntListXSize, rt.bottom);
		}

		if(IsWindow(m_CntListBox))
		{
			m_CntListBox.MoveWindow(rt.right + 1 - CntListXSize, 0, rt.right + 1, rt.bottom);
		}
	}
}


void CChildFrame::AddChatString(const CString &str)
{
	CString strDisplay;
	int nLine;

	m_ChatDisplay.GetWindowText(strDisplay);
	if(strDisplay != _T(""))
	{
		strDisplay += _T("\r\n");
	}
	strDisplay += str;
	m_ChatDisplay.SetWindowText(strDisplay);

	if(m_bChatScroll)
	{
		nLine = m_ChatDisplay.GetLineCount();
		m_ChatDisplay.LineScroll(nLine);
	}

	if((m_SoundOpt == ALWAYS) || ((m_SoundOpt == ON_DISABLE) && !((CMainFrame *)AfxGetMainWnd())->m_bActiveState))
	{
		PlayChatSound();
	}

	if((m_TaskbarOpt == ALWAYS) || ((m_TaskbarOpt == ON_DISABLE) && !((CMainFrame *)AfxGetMainWnd())->m_bActiveState))
	{
		SetForegroundWindow();
	}
}


void CChildFrame::PlayChatSound()
{
	if(m_SoundKind == CChildFrame::OTHER_BELL)
	{
		PlaySound(m_OtherBellPath, AfxGetInstanceHandle(), SND_ASYNC | SND_FILENAME);
	} 
	else
	{
		PlaySound(MAKEINTRESOURCE(m_SoundKind), AfxGetInstanceHandle(), SND_ASYNC | SND_RESOURCE);
	}
}


void CChildFrame::UpdateFont(bool bUpdateScreen)
{
	HFONT hfont = ::CreateFontIndirect(&m_lFont);

	::SendMessage(m_ChatEdit, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(FALSE, 0));
	::SendMessage(m_ChatDisplay, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(FALSE, 0));
	::SendMessage(m_CntListBox, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(FALSE, 0));

	m_ChatEdit.Invalidate();
	m_ChatDisplay.Invalidate();
	m_CntListBox.Invalidate();

	AfxGetApp()->WriteProfileBinary(_T("ChatSetting"), _T("ChatFontBin"), (LPBYTE)&m_lFont, sizeof(m_lFont));

	// DeleteObject를 하면 위쪽의 WM_SETFONT가 되지 않는 것 같으므로
	// DeleteObject()를 하지 않음.
	//::DeleteObject((HGDIOBJ)hfont);

	UpdateScreen();
}

void CChildFrame::InitOption()
{
	LOGFONT *plfont;
	UINT n;

	m_SoundOpt = (ChatOption)AfxGetApp()->GetProfileInt(_T("ChatSetting"), _T("SoundOpt"), ON_DISABLE);
	m_TaskbarOpt = (ChatOption)AfxGetApp()->GetProfileInt(_T("ChatSetting"),  _T("TaskbarOpt"), ON_DISABLE);

	m_SoundKind = AfxGetApp()->GetProfileInt(_T("ChatSetting"), _T("SoundKind"), IDR_BELL1);

	if(AfxGetApp()->GetProfileBinary(_T("ChatSetting"), _T("ChatFontBin"), (LPBYTE *)&plfont, &n))
	{
		if(n == sizeof(LOGFONT))
		{
			m_lFont = *plfont;
			UpdateFont();
		}
		else goto DefFont;
	}
	else
	{
DefFont:
		::GetObject((HGDIOBJ)(HFONT)GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &m_lFont);
	}
	delete [] plfont;
}

void CChildFrame::SaveOption()
{
	AfxGetApp()->WriteProfileInt(_T("ChatSetting"),  _T("SoundOpt"), m_SoundOpt);
	AfxGetApp()->WriteProfileInt(_T("ChatSetting"),  _T("TaskbarOpt"), m_TaskbarOpt);

	if(m_SoundKind == OTHER_BELL)
	{
		AfxGetApp()->WriteProfileInt(_T("ChatSetting"),  _T("SoundKind"), IDR_BELL1);
	}
	else
	{
		AfxGetApp()->WriteProfileInt(_T("ChatSetting"),  _T("SoundKind"), m_SoundKind);
	}
}


void CChildFrame::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(((CMainFrame *)AfxGetMainWnd())->MDIGetActive() == NULL)
	{
		AfxGetMainWnd()->DestroyWindow();
	}

	CMDIChildWndEx::PostNcDestroy();
}


void CChildFrame::OnUseRoomext()
{
	if (m_sock.IsConnected())
	{
		m_sock.EnableRoomExt();
		m_ChatEdit.EnableWindow(FALSE);
		bClickedUseRoomExt = true;
	}
}


void CChildFrame::OnActChangeRoom()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CRoomDialog dialog(this, &m_sock);

	if (dialog.DoModal() == IDOK)
	{
		m_sock.MyChangeRoom(dialog.m_RoomName);
		SetWindowText(m_sock.GetNowRoom());
	}
}


void CChildFrame::OnUpdateUseRoomext(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(!bClickedUseRoomExt);
	pCmdUI->SetCheck((int)bClickedUseRoomExt);
}


void CChildFrame::OnUpdateActChangeRoom(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(m_sock.IsUseRoomExt());
}

