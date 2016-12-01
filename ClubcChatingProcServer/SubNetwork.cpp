#include "stdafx.h"
#include "SubNetwork.h"
#include "Data.h"
#include "Log.h"

#include "../Common.h"

void LoginProcess(ClientInfo &cinfo, array<Byte> ^ar)
{
	char strSend[CHAT_DATA_BUF];

	char *strNickTmp;
	pin_ptr<const wchar_t> strUniNick = PtrToStringChars(cinfo.UserInfo->Nickname);
	strNickTmp = ChrCvt_WideCharToUTF8(strUniNick);
	try
	{
		strcpy(cinfo.strNickname, strNickTmp);
	}
	finally
	{
		ChrCvt_Free(strNickTmp);
		strUniNick = nullptr;
	}

	sprintf_s(strSend, "%s%s", CMD_MY_NICKNAME, cinfo.strNickname);

	cinfo.SendString(strSend);
	cinfo.bReceivedPassword = true;
	cinfo.SendString(CMD_CNT_SUCCEED);

	Data.RoomList[0]->AddUser(&cinfo);

	Logging(L"Login : " + cinfo.DebugName() + ", Count : " + Data.RoomList[0]->users.size());
}

void FinallyProcess(ClientInfo &cinfo)
{
	try
	{
		Monitor::Enter(Data.WaitObject);

		cinfo.sock->Close();
		cinfo.MyRoomDef()->RemoveUser(&cinfo);
	}
	catch (InvalidOperationException ^/*e*/)
	{

	}
	catch (IOException ^/*e*/)
	{

	}
	finally
	{
		Monitor::Exit(Data.WaitObject);
	}
}

void AllBroadCastString(const char *str)
{
	for (shared_ptr<Room> pRoom : Data.RoomList)
	{
		for (ClientInfo *pci : pRoom->users)
		{
			pci->SendString(str);
		}
	}
}
