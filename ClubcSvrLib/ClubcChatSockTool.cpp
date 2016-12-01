#include "stdafx.h"
#include "ClubcSvrLib.h"
#include "InterClubcChatSock.h"
#include "ClubcChatSockApi.h"
#include "ClubcChatSockTool.h"

void ReceiveHandler(CInterClubcChatSock *pSock, int nErrorCode)
{
	if(nErrorCode == 0)
	{
		char RecvBuffer[CHAT_DATA_BUF];
		char RecvString[CHAT_DATA_BUF + 1];
		int rcv, i, j = 0;

		rcv = pSock->Receive(RecvBuffer, sizeof(RecvBuffer));
		if(rcv > 0)
		{
			for(i = 0; i < rcv; i++)
			{
				RecvString[j] = RecvBuffer[i];
				if(RecvBuffer[i] == NULL)
				{
					OnStrReceive(pSock, RecvString, nErrorCode);
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
				OnStrReceive(pSock, RecvString, nErrorCode);
			}
		}
		else
		{
			goto Receive_Error;
		}
	} 
	else
	{
Receive_Error:
		pSock->pfnOnReceive((HClubcChatSock)pSock, NULL, nErrorCode);
	}
}

void CloseHandler(CInterClubcChatSock *pSock, int nErrorCode)
{
	pSock->pfnOnClose((HClubcChatSock)pSock, nErrorCode);
}

void OnStrReceive(CInterClubcChatSock *pSock, const char *str, int nErrorCode)
{
	if(strcmp(str, CMD_CNT_SUCCEED) == 0)
	{
		pSock->bConnected = true;
		pSock->pfnOnConnect((HClubcChatSock)pSock);
	}
	else if(strncmp(str, CMD_MY_NICKNAME, strlen(CMD_MY_NICKNAME)) == 0)
	{
		pSock->Nickname = &str[strlen(CMD_MY_NICKNAME)];
	}
	else if(strncmp(str, CMD_CNTLIST_ADD, strlen(CMD_CNTLIST_ADD)) == 0)
	{
		pSock->ConnectList.insert(&str[strlen(CMD_CNTLIST_ADD)]);
		pSock->pfnOnEvent((HClubcChatSock)pSock, CLUBCSOCKEVENT_ADD_CNTLIST, (void *)&str[strlen(CMD_CNTLIST_ADD)]);
	}
	else if(strncmp(str, CMD_CNTLIST_REMOVE, strlen(CMD_CNTLIST_REMOVE)) == 0)
	{
		pSock->ConnectList.erase(&str[strlen(CMD_CNTLIST_REMOVE)]);
		pSock->pfnOnEvent((HClubcChatSock)pSock, CLUBCSOCKEVENT_REMOVE_CNTLIST, (void *)&str[strlen(CMD_CNTLIST_REMOVE)]);
	}
	else if(strcmp(str, CMD_CNTLIST_BEGIN) == 0)
	{
		pSock->ConnectList.clear();
		pSock->bCntList = true;
	}
	else if(strcmp(str, CMD_CNTLIST_END) == 0)
	{
		pSock->bCntList = false;
		pSock->pfnOnEvent((HClubcChatSock)pSock, CLUBCSOCKEVENT_UPDATE_CNTLIST, NULL);
	}
	else if(strncmp(str, CMD_ROOMLIST_ADD, strlen(CMD_ROOMLIST_ADD)) == 0)
	{
		pSock->RoomList.push_back(&str[strlen(CMD_ROOMLIST_ADD)]);
		pSock->pfnOnEvent((HClubcChatSock)pSock, CLUBCSOCKEVENT_ADD_ROOMLIST, (void *)&str[strlen(CMD_ROOMLIST_ADD)]);
	}
	else if(strncmp(str, CMD_ROOMLIST_REMOVE, strlen(CMD_CNTLIST_REMOVE)) == 0)
	{
		pSock->RoomList.erase(find(pSock->RoomList.begin(), pSock->RoomList.end(), &str[strlen(CMD_ROOMLIST_REMOVE)]));
		pSock->pfnOnEvent((HClubcChatSock)pSock, CLUBCSOCKEVENT_REMOVE_ROOMLIST, (void *)&str[strlen(CMD_CNTLIST_REMOVE)]);
	}
	else if(strcmp(str, CMD_ROOMLIST_BEGIN) == 0)
	{
		pSock->RoomList.clear();
		pSock->bRoomList = true;
	}
	else if(strcmp(str, CMD_ROOMLIST_END) == 0)
	{
		pSock->bRoomList = false;
		pSock->pfnOnEvent((HClubcChatSock)pSock, CLUBCSOCKEVENT_UPDATE_ROOMLIST, NULL);
		if (pSock->bRoomExtProc)
		{
			pSock->pfnOnRoomExt((HClubcChatSock)pSock);
			pSock->bRoomExtProc = false;
		}
	}
	else
	{
		if (pSock->bCntList)
		{
			pSock->ConnectList.insert(str);
		}
		else if (pSock->bRoomList)
		{
			pSock->RoomList.push_back(str);
		}
		else
		{
			pSock->pfnOnReceive((HClubcChatSock)pSock, str, nErrorCode);
		}
	}
}
