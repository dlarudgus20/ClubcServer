// LoginDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ClubcChat2.h"
#include "LoginDialog.h"
#include "afxdialogex.h"


// CLoginDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CLoginDialog, CDialogEx)

CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDialog::IDD, pParent)
	, m_Id(_T(""))
	, m_Pass(_T(""))
	, m_iSrvIp(0)
{

}

CLoginDialog::~CLoginDialog()
{
}

void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ID_EDIT, m_Id);
	DDX_Text(pDX, IDC_PW_EDIT, m_Pass);
	DDX_IPAddress(pDX, IDC_SERVER_IP, m_iSrvIp);
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDialog::OnBnClickedOk)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CLoginDialog �޽��� ó�����Դϴ�.


void CLoginDialog::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	m_SrvIp.Format(TEXT("%d.%d.%d.%d"),
		BYTE(m_iSrvIp >> 24), BYTE(m_iSrvIp >> 16), BYTE(m_iSrvIp >> 8), BYTE(m_iSrvIp));

	CDialogEx::OnOK();
}


int CLoginDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	m_iSrvIp = AfxGetApp()->GetProfileInt(TEXT("Login"), TEXT("ServerIp"), 0x0E2E38E2);
	m_Id = AfxGetApp()->GetProfileString(TEXT("Login"), TEXT("ID"), TEXT("guest"));
	m_Pass = AfxGetApp()->GetProfileString(TEXT("Login"), TEXT("Pass"), TEXT("guest"));

	return 0;
}


void CLoginDialog::WriteDataToReg()
{
	AfxGetApp()->WriteProfileInt(TEXT("Login"), TEXT("ServerIp"), m_iSrvIp);
	AfxGetApp()->WriteProfileString(TEXT("Login"), TEXT("ID"), m_Id);
	AfxGetApp()->WriteProfileString(TEXT("Login"), TEXT("Pass"), m_Pass);
}
