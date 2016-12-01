// ClubcChatSock.cpp : 구현 파일입니다.
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

// CClubcChatSock 멤버 함수


void CInterClubcChatSock::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pfnOnReceive(this, nErrorCode);

	CSocket::OnReceive(nErrorCode);
}


void CInterClubcChatSock::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pfnOnClose(this, nErrorCode);

	CSocket::OnClose(nErrorCode);
}
