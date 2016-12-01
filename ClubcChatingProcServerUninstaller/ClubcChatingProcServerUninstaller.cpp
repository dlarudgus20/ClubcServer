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
				wsprintf(msg, TEXT("���� �Ϸ�. ���ν��� ���α׷� ���� �� ���� ��ġ������ �����Ͻʽÿ�. [%s]\n")
					TEXT("��, ���������� ���� ��ο��� ���ν��緯�� �������� ��� ���� ��ġ������ ã�ƾ� �մϴ�."), cdir);
				MessageBox(NULL, msg, TEXT("�˸�"), MB_OK | MB_ICONINFORMATION);
				return 0;
			}
			else
			{
				MessageBox(NULL, TEXT("���� ���� ����."), TEXT("����"), MB_OK | MB_ICONERROR);
				CloseServiceHandle(hService);
				CloseServiceHandle(hScm);
			}
		}
		else
		{
			MessageBox(NULL, TEXT("���� ���� ����."), TEXT("����"), MB_OK | MB_ICONERROR);
			CloseServiceHandle(hScm);
		}
	}
	else
	{
		MessageBox(NULL, TEXT("SCM�� �� �� �����ϴ�."), TEXT("����"), MB_OK | MB_ICONERROR);
	}

	return -1;
}
