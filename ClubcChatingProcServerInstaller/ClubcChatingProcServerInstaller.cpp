#include "stdafx.h"

#include "../Common.h"
#include "../ServerCommon.h"

#ifndef SERVER_DEVELOP
#define COPY
#endif

#ifdef COPY
LPCTSTR CopyFileTable[] = {
	SERVICE_FILE_NAME,
	UNINSTALLER_FILE_NAME,
	SEVER_LIBRARY_FILE_NAME,
	NULL
};
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, DialogFunc);
}

BOOL CALLBACK DialogFunc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR InstallDir[MAX_PATH];
	BROWSEINFO binfo = { 0 };
	LPITEMIDLIST pidl;
	LPMALLOC pMalloc;

	switch(iMessage)
	{
	case WM_INITDIALOG:
		SHGetSpecialFolderLocation(hDlg, CSIDL_PROGRAM_FILES, &pidl);
		SHGetPathFromIDList(pidl, InstallDir);
		SHGetMalloc(&pMalloc);
		pMalloc->Free(pidl);
		pMalloc->Release();

		lstrcat(InstallDir, TEXT("\\") SERVICE_PROG_NAME);
		SetDlgItemText(hDlg, IDC_INSTALLDIR, InstallDir);
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_DIRFIND:
			binfo.hwndOwner = hDlg;
			binfo.lpszTitle = FOLDER_INPUT_TITLE;
			binfo.ulFlags = BIF_RETURNONLYFSDIRS;
			pidl = SHBrowseForFolder(&binfo);
			if(pidl == NULL)
			{
				return TRUE;
			}
			SHGetPathFromIDList(pidl, InstallDir);
			SHGetMalloc(&pMalloc);
			pMalloc->Free(pidl);
			pMalloc->Release();

			SetDlgItemText(hDlg, IDC_INSTALLDIR, InstallDir);
			return TRUE;
		case IDOK:
			GetDlgItemText(hDlg, IDC_INSTALLDIR, InstallDir, MAX_PATH);
			if(InstallDir[lstrlen(InstallDir) - 1] == '\\')
			{
				InstallDir[lstrlen(InstallDir) - 1] = '\0';
			}

			if(!Install(hDlg, InstallDir))
			{
				return TRUE;
			}
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

bool Install(HWND hWnd, const TCHAR *InstallDir)
{
	TCHAR ServicePath[MAX_PATH], SrcPath[MAX_PATH];
	SERVICE_DESCRIPTION lpDes;
	SC_HANDLE hScm, hService;

	hScm = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if(hScm != NULL)
	{
		if(_taccess(InstallDir, 0) != 0)
		{
			if(!CreateDirectory(InstallDir, NULL))
			{
				MessageBox(hWnd, TEXT("설치 폴더를 만들 수 없습니다."), TEXT("에러"), MB_OK | MB_ICONERROR);
				CloseServiceHandle(hScm);
				return false;
			}
		}
#ifdef COPY
		for(int i = 0; CopyFileTable[i] != NULL; i++)
		{
			wsprintf(ServicePath, TEXT("%s\\%s"), InstallDir, CopyFileTable[i]);
			GetCurrentDirectory(MAX_PATH, SrcPath);
			lstrcat(SrcPath, TEXT("\\"));
			lstrcat(SrcPath, CopyFileTable[i]);
			if(!CopyFile(SrcPath, ServicePath, FALSE))
			{
				MessageBox(hWnd, TEXT("파일 복사 실패"), TEXT("에러"), MB_OK | MB_ICONERROR);
				CloseServiceHandle(hScm);
				return false;
			}
		}
		wsprintf(ServicePath, TEXT("%s\\%s"), InstallDir, SERVICE_FILE_NAME);
#else
		lstrcpy(ServicePath, SERVICE_FILE_NAME);
#endif
		hService = CreateService(hScm, SERVICE_PROG_NAME, SERVICE_DISPLAY_NAME,
			SERVICE_PAUSE_CONTINUE | SERVICE_CHANGE_CONFIG,
			SERVICE_WIN32_OWN_PROCESS, SERVICE_START_TYPE, SERVICE_ERROR_NORMAL, ServicePath, NULL, NULL, NULL, NULL, NULL);
		if(hService != NULL)
		{
			lstrcpy(SrcPath, SERVICE_DESCRIPT);
			lpDes.lpDescription = SrcPath;
			ChangeServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, &lpDes);

			MessageBox(hWnd, TEXT("서비스 설치 완료"), TEXT("완료"), MB_OK);
			CloseServiceHandle(hService);
			CloseServiceHandle(hScm);

			return true;
		}
		else
		{
			MessageBox(hWnd, TEXT("서비스 설치 실패"), TEXT("에러"), MB_OK | MB_ICONERROR);
			CloseServiceHandle(hScm);
		}
	}
	else
	{
		MessageBox(hWnd, TEXT("SCM을 열 수 없습니다."), TEXT("에러"), MB_OK | MB_ICONERROR);
	}

	return false;
}
