// RoomDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "RoomDialog.h"
#include "afxdialogex.h"

#include "ClientSock.h"

// CRoomDialog 대화 상자입니다.

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


// CRoomDialog 메시지 처리기입니다.


BOOL CRoomDialog::OnInitDialog()
{
	if (!CDialogEx::OnInitDialog())
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_pSock->AttachRoomDialog(this);

	return TRUE;
}


void CRoomDialog::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
