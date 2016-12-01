#pragma once
#include "afxcmn.h"


// CLoginDialog 대화 상자입니다.

class CLoginDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDialog)

public:
	CLoginDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLoginDialog();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LOGIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	DWORD m_iSrvIp;
public:
	CString m_Id;
	CString m_Pass;
	CString m_SrvIp;

	void WriteDataToReg();

	afx_msg void OnBnClickedOk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
