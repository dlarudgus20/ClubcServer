// ClubcChatSock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ClubcSvrLib.h"
#include "InterClubcChatSock.h"


// CClubcChatSock

CInterClubcChatSock::CInterClubcChatSock(InterClubcSockHandler pfnOnReceive, InterClubcSockHandler pfnOnClose)
	: m_pfnOnReceive(pfnOnReceive), m_pfnOnClose(pfnOnClose), bConnected(false),
	bCntList(false), bRoomList(false), bRoomExtProc(false)
{
}

// CClubcChatSock ��� �Լ�


void CInterClubcChatSock::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pfnOnReceive(this, nErrorCode);

	CSocket::OnReceive(nErrorCode);
}


void CInterClubcChatSock::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pfnOnClose(this, nErrorCode);

	CSocket::OnClose(nErrorCode);
}
