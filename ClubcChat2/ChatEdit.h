#pragma once


// CChatEdit
class CChildFrame;

class CChatEdit : public CEdit
{
	DECLARE_DYNAMIC(CChatEdit)

public:
	CChatEdit(CChildFrame *pWnd);
	virtual ~CChatEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	CChildFrame *m_pWnd;
};


