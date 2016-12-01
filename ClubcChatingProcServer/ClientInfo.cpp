#include "stdafx.h"
#include "Data.h"

Room *ClientInfo::MyRoomDef()
{
	return MyRoom == NULL ? Data.RoomList[0].get() : MyRoom;
}
