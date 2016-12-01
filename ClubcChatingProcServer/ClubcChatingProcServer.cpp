#include "stdafx.h"
#include "ClubcChatingProcServer.h"

void main()
{
	SERVICE_TABLE_ENTRY ste[] =
	{
		{ SERVICE_PROG_NAME, ClubcChatingProcServiceMain },
		{ NULL, NULL }
	};

	StartServiceCtrlDispatcher(ste);
}

void WINAPI ClubcChatingProcServiceMain(DWORD argc, LPTSTR *argv)
{
	// º¯¼ö
	bool bPaused = false;
	DWORD dwObject;

	try
	{
		OnStart();
		while(1)
		{
			dwObject = WaitForMultipleObjects(EVENT_SVCE_MAX, Data.hEvents, FALSE, INFINITE) - WAIT_OBJECT_0;
			if(dwObject == EVENT_SVCE_STOP)
			{
				OnStop();
				MySetStatus(SERVICE_STOPPED);
				return;
			}
			else if(dwObject == EVENT_SVCE_PAUSE_CONTINUE)
			{
				if(!bPaused)
				{
					ResetEvent(Data.hEvents[EVENT_SVCE_PAUSE_CONTINUE]);
					OnPause();
					MySetStatus(SERVICE_PAUSED);
					bPaused = true;
				} 
				else
				{
					ResetEvent(Data.hEvents[EVENT_SVCE_PAUSE_CONTINUE]);
					OnContinue();
					MySetStatus(SERVICE_RUNNING);
					bPaused = false;
				}
			}
		}
	}
	catch(ClubcChatingProcException e)
	{
		MySetSpecErrorStatus((DWORD) e);
		return;
	}
}

void CALLBACK ClubcChatingProcServiceHandler(DWORD opCode)
{
	switch(opCode)
	{
	case SERVICE_CONTROL_PAUSE:
		MySetStatus(SERVICE_PAUSE_PENDING, 0);
		SetEvent(Data.hEvents[EVENT_SVCE_PAUSE_CONTINUE]);
		break;
	case SERVICE_CONTROL_CONTINUE:
		MySetStatus(SERVICE_CONTINUE_PENDING, 0);
		SetEvent(Data.hEvents[EVENT_SVCE_PAUSE_CONTINUE]);
		break;
	case SERVICE_CONTROL_STOP:
		MySetStatus(SERVICE_STOP_PENDING, 0);
		SetEvent(Data.hEvents[EVENT_SVCE_STOP]);
		break;
	case SERVICE_CONTROL_INTERROGATE:
	default:
		MySetStatus(Data.NowState);
		break;
	}
}

void MySetStatus(DWORD dwState, DWORD dwAccept)
{
	SERVICE_STATUS ss;

	ss.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	ss.dwCurrentState = dwState;
	ss.dwControlsAccepted = dwAccept;
	ss.dwWin32ExitCode = 0;
	ss.dwServiceSpecificExitCode = 0;
	ss.dwCheckPoint = 0;
	ss.dwWaitHint = 0;

	Data.NowState = dwState;
	SetServiceStatus(Data.hService, &ss);
}

void MySetErrorStatus(DWORD dwWin32ExitCode, DWORD dwServiceSpecificExitCode)
{
	SERVICE_STATUS ss;

	ss.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	ss.dwCurrentState = SERVICE_STOPPED;
	ss.dwControlsAccepted = 0;
	ss.dwWin32ExitCode = dwWin32ExitCode;
	ss.dwServiceSpecificExitCode = dwServiceSpecificExitCode;
	ss.dwCheckPoint = 0;
	ss.dwWaitHint = 0;

	Data.NowState = SERVICE_STOPPED;
	SetServiceStatus(Data.hService, &ss);
}
