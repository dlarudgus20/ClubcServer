#include "stdafx.h"
#include "Network.h"
#include "SubNetwork.h"
#include "Utility.h"
#include "Data.h"
#include "Log.h"
#include "Login.h"

#include "../Common.h"

void DoCommunicate(IAsyncResult ^ar)
{
	ClientInfo cinfo;

	try
	{
		Monitor::Enter(Data.WaitObject);

		cinfo.sock = Data.ServerSock->EndAcceptTcpClient(ar);
		Data.ServerSock->BeginAcceptTcpClient(gcnew AsyncCallback(DoCommunicate), nullptr);

		Logging(L"Connect : " + cinfo.sock->Client->RemoteEndPoint);
	}
	finally
	{
		Monitor::Exit(Data.WaitObject);
	}

	try
	{
		array<Byte> ^RecvBuffer = gcnew array<Byte>(CHAT_DATA_BUF);
		array<Byte> ^RecvString = gcnew array<Byte>(CHAT_DATA_BUF + 1);
		Int32 rcv;
		int i, j;

		while(1)
		{
			rcv = cinfo.sock->GetStream()->Read(RecvBuffer, 0, RecvBuffer->Length);
			for(i = 0; i < rcv; i++)
			{
				RecvString[j] = RecvBuffer[i];
				if(RecvBuffer[i] == NULL)
				{
					if(!ProcessString(cinfo, RecvString))
					{
						goto DoCommunicate_End;
					}
					j = 0;
				}
				else
				{
					j++;
				}
			}
			if(j != 0)
			{
				RecvString[j] = NULL;
				if(!ProcessString(cinfo, RecvString))
				{
					goto DoCommunicate_End;
				}
			}
		}
DoCommunicate_End:;
	}
	catch(InvalidOperationException ^)
	{

	}
	catch(IOException ^)
	{

	}
	catch(Exception ^e)
	{
		Logging(L"Uncaughted exception : " + e->GetType() + L", descript : " + e->Message +
			L", client info : " + Utf8CStrToNetStr(cinfo.strNickname));
	}
	finally
	{
		FinallyProcess(cinfo);
	}
}

bool ProcessString(ClientInfo &cinfo, array<Byte> ^ar)
{
	char str[CHAT_DATA_BUF + 1];

	ByteArrToCStr(ar, str);

	try
	{
		Monitor::Enter(Data.WaitObject);

		if(!cinfo.bReceivedVersion)
		{
			if(strcmp(str, CLUBCCHATINGPROC_VERSION_STR) != 0)
			{
				return false;
			}
			cinfo.bReceivedVersion = true;
		}
		else if(!cinfo.bReceivedId)
		{
			strcpy_s(cinfo.strNickname, str);
			cinfo.bReceivedId = true;
		}
		else if(!cinfo.bReceivedPassword)
		{
			if (Login(cinfo.strNickname, str, cinfo.UserInfo))
			{
				LoginProcess(cinfo, ar);
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (!ProcessCommand(cinfo, str))
			{
				cinfo.MyRoomDef()->BroadCastString(str);
			}
		}
	}
	finally
	{
		Monitor::Exit(Data.WaitObject);
	}

	return true;
}

bool ProcessCommand(ClientInfo &cinfo, const char *str)
{
	if (strcmp(str, CMD_USE_ROOMEXT) == 0)
	{
		cinfo.bUseRoomExt = true;
		cinfo.SendString(CMD_ROOMLIST_BEGIN);
		for (shared_ptr<Room> pRoom : Data.RoomList)
		{
			cinfo.SendString(pRoom->name);
		}
		cinfo.SendString(CMD_ROOMLIST_END);

		Logging(L"Use RoomExt : " + cinfo.DebugName());
	}
	else if (strncmp(str, CMD_CHANGE_ROOM, strlen(CMD_CHANGE_ROOM)) == 0)
	{
		const char *name = &str[strlen(CMD_CHANGE_ROOM)];
		vector<shared_ptr<Room> >::iterator it = find_if(Data.RoomList.begin(), Data.RoomList.end(),
			[name](const shared_ptr<Room> &ptr) {
				return strcmp(ptr->name, name) == 0;
			});

		Logging(L"Change Room : " + cinfo.DebugName());
		if (it != Data.RoomList.end())
		{
			(*it)->AddUser(&cinfo);
		}
		else
		{
			char buf[CHAT_DATA_BUF];

			Room *pRoom = new Room(name);
			sprintf_s(buf, "%s%s", CMD_ROOMLIST_ADD, name);
			AllBroadCastString(buf);

			pRoom->AddUser(&cinfo);
			Data.RoomList.push_back(shared_ptr<Room>(pRoom));
		}
	}
	else
	{
		return false;
	}

	return true;
}
