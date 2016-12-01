// RoomDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "RoomDialog.h"
#include "afxdialogex.h"

#include "ClientSock.h"

// CRoomDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRoomDialog, CDialogEx)

CRoomDialog::CRoomDialog(CWnd* pParent, CClientSock *pSock)
	: CDialogEx(CRoomDialog::IDD, pParent)
	, m_RoomName(_T("")), m_pSock(pSock)
{

}

CRoomDialog::~CRoomDialog()
{
}

void CRoomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ROOM_LIST, m_RoomList);
	DDX_Text(pDX, IDC_EDIT1, m_RoomName);
}


BEGIN_MESSAGE_MAP(CRoomDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRoomDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CRoomDialog �޽��� ó�����Դϴ�.


BOOL CRoomDialog::OnInitDialog()
{
	if (!CDialogEx::OnInitDialog())
		return FALSE;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_pSock->AttachRoomDialog(this);

	return TRUE;
}


void CRoomDialog::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();

	if (m_RoomName == TEXT("") && m_RoomList.GetCurSel() != LB_ERR)
	{
		m_RoomName = (LPCTSTR)m_RoomList.GetItemDataPtr(m_RoomList.GetCurSel()); //?
	}

	if (!(m_RoomName == TEXT("") || m_RoomName == m_pSock->GetNowRoom()))
	{
		m_pSock->DeAttechRoomDialog();
		CDialogEx::OnOK();
	}
	else
	{
		MessageBox(CClubcChat2App::ResStr(IDS_MSGBOX_NO_SEL_ROOM),
			CClubcChat2App::ResStr(IDS_MSGBOX_TITLE_ERR), MB_OK | MB_ICONINFORMATION);
	}
}
