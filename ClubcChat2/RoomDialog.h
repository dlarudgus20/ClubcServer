#pragma once
#include "afxwin.h"
#include "resource.h"

// CRoomDialog ��ȭ �����Դϴ�.
class CClientSock;

class CRoomDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CRoomDialog)

public:
	CRoomDialog(CWnd* pParent, CClientSock *pSock);   // ǥ�� �������Դϴ�.
	virtual ~CRoomDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ROOM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
