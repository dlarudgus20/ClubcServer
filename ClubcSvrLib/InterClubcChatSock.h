#pragma once

// CClubcChatSock 명령 대상입니다.
#include "ClubcChatSockApi.h"

class CInterClubcChatSock : public CSocket
{
public:
	typedef void (*InterClubcSockHandler)(CInterClubcChatSock *pSock, int nErrorCode);
private:
	InterClubcSockHandler m_pfnOnReceive, m_pfnOnClose;
public:
	void *UserData;

	ClubcSockReceiveHandler pfnOnReceive;
	ClubcSockCloseHandler pfnOnClose;
	ClubcSockConnectHandler pfnOnConnect;
	ClubcSockEventHandler pfnOnEvent;
	ClubcSockRoomExtHandler pfnOnRoomExt;

	string Nickname;
	bool bConnected;

	multiset<string> ConnectList;
	bool bCntListComplete;
	bool bCntList;

	vector<string> RoomList;
	bool bRoomListComplete;
	bool bRoomList;
	bool bRoomExtProc;

	CInterClubcChatSock(InterClubcSockHandler pfnOnReceive, InterClubcSockHandler pfnOnClose);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};
