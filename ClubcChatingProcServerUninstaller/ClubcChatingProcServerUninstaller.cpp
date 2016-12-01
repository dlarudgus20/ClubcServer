#include "stdafx.h"

#include "../Common.h"
#include "../ServerCommon.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	SC_HANDLE hScm, hService;
	SERVICE_STATUS ss;
	TCHAR cdir[MAX_PATH], msg[MAX_PATH * 2];

	hScm = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if(hScm != NULL)
	{
		hService = OpenService(hScm, SERVICE_PROG_NAME, SERVICE_ALL_ACCESS);
		if(hService != NULL)
		{
			QueryServiceStatus(hService, &ss);
			if(ss.dwCurrentState != SERVICE_STOPPED)
			{
				ControlService(hService, SERVICE_CONTROL_STOP, &ss);
				Sleep(2000);
			}

			if(DeleteService(hService))
			{
				GetCurrentDirectory(MAX_PATH, cdir);
				wsprintf(msg, TEXT("제거 완료. 언인스톨 프로그램 종료 후 다음 설치폴더를 삭제하십시오. [%s]\n")
					TEXT("단, 정상적이지 않은 경로에서 언인스톨러를 실행했을 경우 직접 설치폴더를 찾아야 합니다."), cdir);
				MessageBox(NULL, msg, TEXT("알림"), MB_OK | MB_ICONINFORMATION);
				return 0;
			}
			else
			{
				MessageBox(NULL, TEXT("서비스 제거 실패."), TEXT("에러"), MB_OK | MB_ICONERROR);
				CloseServiceHandle(hService);
				CloseServiceHandle(hScm);
			}
		}
		else
		{
			MessageBox(NULL, TEXT("서비스 열기 실패."), TEXT("에러"), MB_OK | MB_ICONERROR);
			CloseServiceHandle(hScm);
		}
	}
	else
	{
		MessageBox(NULL, TEXT("SCM을 열 수 없습니다."), TEXT("에러"), MB_OK | MB_ICONERROR);
	}

	return -1;
}
