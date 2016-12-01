#pragma once

#include "ClientInfo.h"
#include "Room.h"

enum ClubcChatingProcEvents
{
	EVENT_SVCE_STOP,
	EVENT_SVCE_PAUSE_CONTINUE,

	EVENT_SVCE_MAX
};

struct tagData
{
	SERVICE_STATUS_HANDLE hService;

	DWORD NowState;
	bool bCleanuped;

	HANDLE hEvents[EVENT_SVCE_MAX];

	gcroot<TcpListener ^> ServerSock;
	vector<shared_ptr<Room> > RoomList;

	gcroot<Object ^> WaitObject;

	tagData()
	{
		WaitObject = gcnew Object;
		RoomList.push_back(shared_ptr<Room>(new Room));
	}
};

extern tagData Data;
