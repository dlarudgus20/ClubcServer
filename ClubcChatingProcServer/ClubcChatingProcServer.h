#pragma once

#include "../Common.h"
#include "../ServerCommon.h"

#include "Servering.h"

#include "Data.h"

#define MySetSpecErrorStatus(dwServiceSpecificExitCode) (MySetErrorStatus(ERROR_SERVICE_SPECIFIC_ERROR, (dwServiceSpecificExitCode)))

void MySetStatus(DWORD dwState, DWORD dwAccept = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE);
void MySetErrorStatus(DWORD dwWin32ExitCode, DWORD dwServiceSpecificExitCode = 0);

void WINAPI ClubcChatingProcServiceMain(DWORD argc, LPTSTR *argv);
void CALLBACK ClubcChatingProcServiceHandler(DWORD opCode);
