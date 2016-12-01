#include "stdafx.h"
#include "ClubcSvrLib.h"
#include "InterClubcChatSock.h"
#include "ClubcChatSockApi.h"
#include "ClubcChatSockTool.h"

_CLUBCCHATSOCK_API HClubcChatSock CreateClubcChatSock(
	const wchar_t *Server,
	ClubcSockReceiveHandler pfnOnReceive, ClubcSockCloseHandler pfnOnClose,
	ClubcSockConnectHandler pfnOnConnect, ClubcSockEventHandler pfnOnEvent,
	ClubcSockRoomExtHandler pfnOnRoomExt,
	const char_utf8 *id, const char_utf8 *pw, void *UserData)
{
	CInterClubcChatSock *pSock = new CInterClubcChatSock(ReceiveHandler, CloseHandler);

	pSock->pfnOnReceive = pfnOnReceive;
	pSock->pfnOnClose = pfnOnClose;
	pSock->pfnOnConnect = pfnOnConnect;
	pSock->pfnOnEvent = pfnOnEvent;
	pSock->pfnOnRoomExt = pfnOnRoomExt;
	pSock->UserData = UserData;

	if(pSock->Create())
	{
		if(pSock->Connect(Server, SERVER_PORT))
		{
			// TODO: 로그인&초기화 코드
			if(pSock->Send(CLUBCCHATINGPROC_VERSION_STR, strlen(CLUBCCHATINGPROC_VERSION_STR) + 1) <= 0) goto CreateClubcChatSock_Err;
			if(pSock->Send(id, strlen(id) + 1) <= 0) goto CreateClubcChatSock_Err;

			if(pSock->Send(pw, strlen(pw) + 1) <= 0) goto CreateClubcChatSock_Err;

			return (HClubcChatSock)pSock;
		}
	}
CreateClubcChatSock_Err:
	delete pSock;
	return NULL;
}

_CLUBCCHATSOCK_API void DeleteClubcChatSock(HClubcChatSock sock)
{
	delete (CInterClubcChatSock *)sock;
}

_CLUBCCHATSOCK_API int SendStringClubcChatSock(HClubcChatSock sock, const char_utf8 *str)
{
	return ((CInterClubcChatSock *)sock)->Send(str, strlen(str) + 1);
}

_CLUBCCHATSOCK_API const char_utf8 *GetMyNicknameClubcChatSock(HClubcChatSock sock)
{
	if(((CInterClubcChatSock *)sock)->bConnected)
	{
		return ((CInterClubcChatSock *)sock)->Nickname.c_str();
	} 
	else
	{
		return NULL;
	}
}

_CLUBCCHATSOCK_API void GetConnectListClubcChatSock(HClubcChatSock sock, char_utf8 *buf, int size)
{
	string str;

	for each(string s in ((CInterClubcChatSock *)sock)->ConnectList)
	{
		str.append(s).append("\n");
	}

	strcpy_s(buf, size, str.c_str());
}

_CLUBCCHATSOCK_API int IsConnectedClubcChatSock(HClubcChatSock sock)
{
	return (int)((CInterClubcChatSock *)sock)->bConnected;
}

_CLUBCCHATSOCK_API void SetUserDataClubcChatSock(HClubcChatSock sock, void *UserData)
{
	((CInterClubcChatSock *)sock)->UserData = UserData;
}

_CLUBCCHATSOCK_API void *GetUserDataClubcChatSock(HClubcChatSock sock)
{
	return ((CInterClubcChatSock *)sock)->UserData;
}

_CLUBCCHATSOCK_API void EnableRoomExtClubcChatSock(HClubcChatSock sock)
{
	((CInterClubcChatSock *)sock)->bRoomExtProc = true;
	((CInterClubcChatSock *)sock)->Send(CMD_USE_ROOMEXT, strlen(CMD_USE_ROOMEXT) + 1);
}

_CLUBCCHATSOCK_API void GetRoomListClubcChatSock(HClubcChatSock sock, char_utf8 *buf, int size)
{
	string str;

	for each(string s in ((CInterClubcChatSock *)sock)->RoomList)
	{
		str.append(s).append("\n");
	}

	strcpy_s(buf, size, str.c_str());
}

_CLUBCCHATSOCK_API void ChangeRoomClubcChatSock(HClubcChatSock sock, const char_utf8 *room)
{
	((CInterClubcChatSock *)sock)->Send(CMD_CHANGE_ROOM, strlen(CMD_CHANGE_ROOM));
	((CInterClubcChatSock *)sock)->Send(room, strlen(room) + 1);
}
