
// ChildFrm.h : CChildFrame 클래스의 인터페이스
//

#pragma once
#include "afxwin.h"
#include "chatdisplayedit.h"
#include "chatedit.h"
#include "logindialog.h"
#include "clientsock.h"

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
private:
	friend CChatEdit;
	friend CClientSock;

	enum ChatOption { ALWAYS, NON, ON_DISABLE };
	enum { OTHER_BELL = 0 };

	static int CALLBACK FindFontProc(ENUMLOGFONT *lpelf, NEWTEXTMETRIC *lpntm, int FontType, LPARAM lParam);

	static void SetListBoxHScrollBar(CListBox &ListBox);
	static HFONT FindFont(HDC hdc, LPCTSTR font);

	void UpdateScreen();

	void PlayChatSound();
	void UpdateFont(bool bUpdateScreen = true);

	void InitOption();
	void SaveOption();

	CLoginDialog m_LoginDialog;
	CString m_Nickname;

	CChatDisplayEdit m_ChatDisplay;
	CChatEdit m_ChatEdit;
	CListBox m_CntListBox;

	CClientSock m_sock;

	ChatOption m_SoundOpt, m_TaskbarOpt;
	bool m_bChatScroll;

	UINT m_SoundKind;
	CString m_OtherBellPath;

	CString m_FontName;
	LOGFONT m_lFont;

	bool bClickedUseRoomExt;
public:
	void AddChatString(const CString &str);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnFontChange();
	afx_msg void OnDestroy();

	afx_msg void OnChatScroll();
	afx_msg void OnUpdateChatScroll(CCmdUI *pCmdUI);

	afx_msg void OnSoundOn();
	afx_msg void OnSoundOff();
	afx_msg void OnSoundOndisable();
	afx_msg void OnTaskbarOn();
	afx_msg void OnTaskbarOff();
	afx_msg void OnTaskbarOndisable();
	afx_msg void OnSoundBell1();
	afx_msg void OnSoundBell2();
	afx_msg void OnSoundBell3();
	afx_msg void OnSoundBellother();
	afx_msg void OnUpdateSoundOn(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSoundOff(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSoundOndisable(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTaskbarOn(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTaskbarOff(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTaskbarOndisable(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSoundBell1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSoundBell2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSoundBell3(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSoundBellother(CCmdUI *pCmdUI);

	afx_msg void OnActClean();

	afx_msg void OnUseRoomext();
	afx_msg void OnActChangeRoom();
	afx_msg void OnUpdateUseRoomext(CCmdUI *pCmdUI);
	afx_msg void OnUpdateActChangeRoom(CCmdUI *pCmdUI);

	virtual void PostNcDestroy();
};
