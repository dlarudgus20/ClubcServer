#pragma once
#include "afxcmn.h"


// CLoginDialog ��ȭ �����Դϴ�.

class CLoginDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDialog)

public:
	CLoginDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLoginDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LOGIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
