#pragma once

#include "Utility.h"

struct Room;

struct ClientInfo
{
	gcroot<TcpClient ^> sock;
	Room *MyRoom;

	bool bReceivedVersion;
	bool bReceivedId;
	bool bReceivedPassword;
	char strNickname[CHAT_DATA_BUF]; // 로긴 이전엔 ID 저장
	bool bConnected;

	bool bUseRoomExt;

	gcroot<ClubcUser ^> UserInfo;

	ClientInfo()
		: bReceivedVersion(false), bReceivedId(false), bReceivedPassword(false), bConnected(false),
		bUseRoomExt(false),
		MyRoom(NULL)
	{
		UserInfo = gcnew ClubcUser;
	}

	void SendString(const char *str)
	{
		sock->GetStream()->Write(CStrToByteArr(str), 0, strlen(str) + 1);
	}

	void SendBinary(const void *ptr, int size)
	{
		if (size > CHAT_DATA_BUF - 1)
			throw gcnew IOException();

		char buf[CHAT_DATA_BUF];
		memcpy(buf, ptr, size);
		buf[size] = '\0';
		SendString(buf);
	}

	void SendInt(int i)
	{
		SendBinary(&i, sizeof(i));
	}

	Room *MyRoomDef();

	String ^DebugName()
	{
		return (sock->Client->RemoteEndPoint + L" (" + Utf8CStrToNetStr(strNickname) + L")");
	}

	bool operator ==(const ClientInfo &other) { return (TcpClient ^)sock == (TcpClient ^)other.sock; }
	bool operator !=(const ClientInfo &other) { return !(*this == other); }
};
