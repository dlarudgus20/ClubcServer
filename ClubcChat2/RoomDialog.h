#pragma once
#include "afxwin.h"
#include "resource.h"

// CRoomDialog 대화 상자입니다.
class CClientSock;

class CRoomDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CRoomDialog)

public:
	CRoomDialog(CWnd* pParent, CClientSock *pSock);   // 표준 생성자입니다.
	virtual ~CRoomDialog();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ROOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	CClientSock *m_pSock;

public:
	afx_msg void OnBnClickedOk();
private:
	friend CClientSock;

	CListBox m_RoomList;
public:
	CString m_RoomName;

	virtual BOOL OnInitDialog();
};
