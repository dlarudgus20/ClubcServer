#include "stdafx.h"
#include "Data.h"
#include "Log.h"

#include "../Common.h"

Room::Room(const char *n)
{
	strcpy(name, n);
	Logging(L"Create Room : " + Utf8CStrToNetStr(n));
}

Room::~Room()
{
	char buf[CHAT_DATA_BUF];

	for (shared_ptr<Room> pRoom : Data.RoomList)
	{
		for (ClientInfo *user : pRoom->users)
		{
			if (user->bUseRoomExt)
			{
				sprintf_s(buf, "%s%s", CMD_ROOMLIST_REMOVE, name);
				user->SendString(buf);
			}
		}
	}

	for (ClientInfo *user : users)
	{
		user->MyRoom = NULL;
	}

	Logging(L"Destroy Room : " + Utf8CStrToNetStr(name));
}

void Room::AddUser(ClientInfo *user)
{
	char strSend[CHAT_DATA_BUF];

	if (users.empty())
		master = user;
	users.push_back(user);
	user->MyRoom = this;

	sprintf(strSend, "%s%s", CMD_CNTLIST_ADD, user->strNickname);
	try
	{
		BroadCastString(strSend);
	}
	finally
	{
		user->bConnected = true;
	}

	user->SendString(CMD_CNTLIST_BEGIN);
	for (ClientInfo *pci : Data.RoomList[0]->users)
	{
		if(pci->bConnected)
		{
			user->SendString(pci->strNickname);
		}
	}
	user->SendString(CMD_CNTLIST_END);
}

void Room::RemoveUser(ClientInfo *user)
{
	users.remove(user);
	user->MyRoom = NULL;
	if (master == user)
	{
		master = users.empty() ? NULL : *users.begin(); 
	}

	if (user->bConnected)
	{
		char strSend[CHAT_DATA_BUF];
		sprintf(strSend, "%s%s", CMD_CNTLIST_REMOVE, user->strNickname);
		BroadCastString(strSend);
	}
}

void Room::BroadCastString(const char *str)
{
	for (ClientInfo *pci : users)
	{
		if (pci->bConnected)
		{
			pci->SendString(str);
		}
	}
}
