// LoginDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ClubcChat2.h"
#include "LoginDialog.h"
#include "afxdialogex.h"


// CLoginDialog 대화 상자입니다.

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


// CLoginDialog 메시지 처리기입니다.


void CLoginDialog::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_SrvIp.Format(TEXT("%d.%d.%d.%d"),
		BYTE(m_iSrvIp >> 24), BYTE(m_iSrvIp >> 16), BYTE(m_iSrvIp >> 8), BYTE(m_iSrvIp));

	CDialogEx::OnOK();
}


int CLoginDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

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
