#pragma once

#include <windows.h>
#include <shlobj.h>
#include <tchar.h>
#include <io.h>

#include "resource.h"

#define FOLDER_INPUT_TITLE TEXT("��ġ ��θ� �Է��Ͻʽÿ�.")

BOOL CALLBACK DialogFunc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
bool Install(HWND hWnd, const TCHAR *InstallDir);
