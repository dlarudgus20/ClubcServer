#pragma once

#ifndef SERVER_DEVELOP
#define SERVICE_PROG_NAME TEXT("ClubcChatingProcServer")

#define SERVICE_DISPLAY_NAME TEXT("ClubcChatingProc Sever Program")

#define SERVICE_DESCRIPT TEXT("Clubc ChatingProc Server (Service Program)")
#else
#define SERVICE_PROG_NAME TEXT("ClubcChatingProcServer_2")

#define SERVICE_DISPLAY_NAME TEXT("ClubcChatingProc Sever Program_2")

#define SERVICE_DESCRIPT TEXT("Clubc ChatingProc Server (Service Program)_2")
#endif

#define SERVICE_FILE_NAME TEXT("ClubcChatingProcServer.exe")
#define SEVER_LIBRARY_FILE_NAME TEXT("ClubcSvrLib_Server.dll")
#define UNINSTALLER_FILE_NAME TEXT("ClubcChatingProcServerUninstaller.exe")

#define SERVICE_START_TYPE SERVICE_AUTO_START

enum ClubcChatingProcException
{
	CLUBCCHATINGPROC_SUCCESS = 0,

	CLUBCCHATINGPROC_ERROR_SERVICE_INIT,

	CLUBCCHATINGPROC_ERROR_SOCK_CREATE,
	CLUBCCHATINGPROC_ERROR_LISTEN,
	
	CLUBCCHATINGPROC_ERROR_ACCEPT,
	CLUBCCHATINGPROC_ERROR_RECEIVE,
	CLUBCCHATINGPROC_ERROR_SEND
};
