#pragma once

#include "ClubcChat2.h"

class CChildFrame;
class CRoomDialog;

class CClientSock : public CClubcChatSock
{
private:
	CChildFrame *m_pWnd;
	CRoomDialog *m_pDlg;

	CString m_NowRoom;

protected:
	virtual void OnReceive(const char *str, int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect();
	virtual void OnEvent(ClubcChatSockEvent e, void *param);
	virtual void OnRoomExt();
public:
	CClientSock(CChildFrame *pWnd) : m_pWnd(pWnd), m_pDlg(NULL), m_NowRoom(TEXT("default")) { }
	virtual ~CClientSock();

	int SendChatString(const CString &str);

	void AttachRoomDialog(CRoomDialog *dialog);
	void DeAttechRoomDialog();
	void UpdateRoomDialog();

	void MyChangeRoom(const CString &room);

	CString GetNowRoom();
};
