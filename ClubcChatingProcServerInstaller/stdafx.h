#pragma once

#include <windows.h>
#include <shlobj.h>
#include <tchar.h>
#include <io.h>

#include "resource.h"

#define FOLDER_INPUT_TITLE TEXT("설치 경로를 입력하십시오.")

BOOL CALLBACK DialogFunc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
bool Install(HWND hWnd, const TCHAR *InstallDir);
