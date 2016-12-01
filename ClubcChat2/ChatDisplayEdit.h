#pragma once


// CChatDisplayEdit

class CChatDisplayEdit : public CEdit
{
	DECLARE_DYNAMIC(CChatDisplayEdit)

public:
	CChatDisplayEdit();
	virtual ~CChatDisplayEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


