#include "stdafx.h"
#include "ClubcChat2.h"
#include "ClientSock.h"
#include "ChildFrm.h"
#include "MainFrm.h"
#include "RoomDialog.h"

CClientSock::~CClientSock()
{
	if(IsConnected())
	{
		CString str;

		str.Format(IDS_UNCONMSG_FMT, m_pWnd->m_Nickname);
		SendChatString(str);
	}
}

void CClientSock::OnReceive(const char *str, int nErrorCode)
{
	wchar_t *strUni = ChrCvt_UTF8ToWideChar(str);

	m_pWnd->AddChatString(CString(strUni));

	delete [] strUni;
}

int CClientSock::SendChatString(const CString &str)
{
	char *strSend = ChrCvt_WideCharToUTF8(CStringW(str));
	int nRet;

	nRet = SendString(strSend);
	ChrCvt_Free(strSend);

	return nRet;
}

void CClientSock::OnClose(int nErrorCode)
{
	if(!IsConnected())
	{
		// 접속 실패시
		m_pWnd->MessageBox(CClubcChat2App::ResStr(IDS_MSGBOX_SOCK_CREATE_ERR), CClubcChat2App::ResStr(IDS_MSGBOX_TITLE_ERR), MB_OK | MB_ICONERROR);
	}
	m_pWnd->DestroyWindow();
}

void CClientSock::OnConnect()
{
	CString CntMsg;
	wchar_t *strUni = ChrCvt_UTF8ToWideChar(GetMyNickname());

	m_pWnd->m_Nickname = CString(strUni);
	ChrCvt_Free(strUni);

	CntMsg.Format(IDS_CONMSG_FMT, m_pWnd->m_Nickname);
	if(SendChatString(CntMsg) <= 0)
	{
		m_pWnd->MessageBox(CClubcChat2App::ResStr(IDS_MSGBOX_SOCK_CREATE_ERR), CClubcChat2App::ResStr(IDS_MSGBOX_TITLE_ERR), MB_OK | MB_ICONERROR);
		m_pWnd->DestroyWindow();
		return;
	}

	m_pWnd->m_ChatEdit.EnableWindow();
}

void CClientSock::OnEvent(ClubcChatSockEvent e, void *param)
{
	CClubcChatSock::OnEvent(e, param);
	// TODO: 사용자 코드
	wchar_t *strUni;

	switch(e)
	{
	case CLUBCSOCKEVENT_ADD_CNTLIST:
		strUni = ChrCvt_UTF8ToWideChar((const char *)param);

		m_pWnd->m_CntListBox.AddString(CString(strUni));

		ChrCvt_Free(strUni);
		break;
	case CLUBCSOCKEVENT_REMOVE_CNTLIST:
		strUni = ChrCvt_UTF8ToWideChar((const char *)param);

		m_pWnd->m_CntListBox.DeleteString(m_pWnd->m_CntListBox.FindString(0, CString(strUni)));

		ChrCvt_Free(strUni);
		break;
	case CLUBCSOCKEVENT_UPDATE_CNTLIST:
		{
			int i, count = m_pWnd->m_CntListBox.GetCount();
			list<string>::const_iterator it;

			for(i = 0; i < count; i++)
			{
				m_pWnd->m_CntListBox.DeleteString(0);
			}

			for(it = GetConnectList().begin(); it != GetConnectList().end(); it++)
			{
				wchar_t *strUni = ChrCvt_UTF8ToWideChar(it->c_str());
				m_pWnd->m_CntListBox.AddString(CString(strUni));
				ChrCvt_Free(strUni);
			}
			break;
		}
	}

	if (m_pDlg != NULL)
	{
		const wchar_t *str;
		switch (e)
		{
		case CLUBCSOCKEVENT_UPDATE_ROOMLIST:
			UpdateRoomDialog();
			break;
		case CLUBCSOCKEVENT_ADD_ROOMLIST:
			str = ChrCvt_UTF8ToWideChar((char_utf8 *)param);
			m_pDlg->m_RoomList.AddString(str);
			ChrCvt_Free(str);
			break;
		case CLUBCSOCKEVENT_REMOVE_ROOMLIST:
			str = ChrCvt_UTF8ToWideChar((char_utf8 *)param);
			m_pDlg->m_RoomList.DeleteString(m_pDlg->m_RoomList.FindString(0, str));
			ChrCvt_Free(str);
		}
	}
}

void CClientSock::OnRoomExt()
{
	const wchar_t *str = ChrCvt_UTF8ToWideChar(GetRoomListStr().c_str());
	m_pWnd->SetWindowText(str);
	ChrCvt_Free(str);

	m_pWnd->m_ChatEdit.EnableWindow(TRUE);
}

void CClientSock::AttachRoomDialog(CRoomDialog *dialog)
{
	m_pDlg = dialog;
	UpdateRoomDialog();
}

void CClientSock::DeAttechRoomDialog()
{
	m_pDlg = NULL;
}

void CClientSock::UpdateRoomDialog()
{
	for (int i = 0; i < m_pDlg->m_RoomList.GetCount(); i++)
		m_pDlg->m_RoomList.DeleteString(0);

	const wchar_t *wstr;

	for each (string_utf8 str in GetRoomList())
	{
		wstr = ChrCvt_UTF8ToWideChar(str.c_str());
		m_pDlg->m_RoomList.AddString(wstr);
		ChrCvt_Free(wstr);
	}
}

void CClientSock::MyChangeRoom(const CString &room)
{
	m_NowRoom = room;

	const char *str = ChrCvt_WideCharToUTF8(room);
	ChangeRoom(str);
	ChrCvt_Free(str);
}

CString CClientSock::GetNowRoom()
{
	return m_NowRoom;
}
