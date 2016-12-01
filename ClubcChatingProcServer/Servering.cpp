#include "stdafx.h"
#include "ClubcChatingProcServer.h"
#include "Network.h"
#include "Log.h"

bool OnStart()
{
	Data.hService = RegisterServiceCtrlHandler(SERVICE_PROG_NAME, ClubcChatingProcServiceHandler);
	if(Data.hService == NULL) throw CLUBCCHATINGPROC_ERROR_SERVICE_INIT;

	MySetStatus(SERVICE_START_PENDING);

	int i;

	for(i = 0; i < EVENT_SVCE_MAX; i++)
	{
		Data.hEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
	}

	InitService();

	MySetStatus(SERVICE_RUNNING);

	return true;
}

bool OnStop()
{
	CleanupService();

	int i;

	for(i = 0; i < EVENT_SVCE_MAX; i++)
	{
		CloseHandle(Data.hEvents[i]);
	}

	return true;
}

bool OnPause()
{
	return CleanupService();
}

bool OnContinue()
{
	return InitService();
}

bool InitService()
{
	try
	{
		Data.ServerSock = gcnew TcpListener(IPAddress::Any, SERVER_PORT);
		Data.ServerSock->Start();
	}
	catch(SocketException ^/*e*/)
	{
		throw CLUBCCHATINGPROC_ERROR_SOCK_CREATE;
	}

	try
	{
		Data.ServerSock->BeginAcceptTcpClient(gcnew AsyncCallback(DoCommunicate), nullptr);
	}
	catch(SocketException ^/*e*/)
	{
		throw CLUBCCHATINGPROC_ERROR_ACCEPT;
	}

	return true;
}

bool CleanupService()
{
	try
	{
		Monitor::Enter(Data.WaitObject);

		for (ClientInfo *pci : Data.RoomList[0]->users)
		{
			pci->sock->Close();
		}
		vector<shared_ptr<Room> >().swap(Data.RoomList);
	}
	finally
	{
		Monitor::Exit(Data.WaitObject);
	}

	Data.ServerSock->Stop();
	return true;
}
