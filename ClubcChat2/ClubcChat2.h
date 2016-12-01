
// ClubcChat2.h : ClubcChat2 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CClubcChat2App:
// �� Ŭ������ ������ ���ؼ��� ClubcChat2.cpp�� �����Ͻʽÿ�.
//

class CClubcChat2App : public CWinAppEx
{
public:
	CClubcChat2App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	static CString ResStr(int nResId)
	{
		TCHAR strRes[1024];

		::LoadString(::GetModuleHandle(NULL), nResId, strRes, sizeof(strRes) / sizeof(strRes[0]));
		return strRes;
	}
};

extern CClubcChat2App theApp;

#include "../ClubcSvrLib/ClubcChatSockApi.hpp"
#ifdef _DEBUG
#pragma comment(lib, "../Debug/ClubcSvrLib.lib")
#else
#pragma comment(lib, "../Release/ClubcSvrLib.lib")
#endif

using namespace IkhPrograms;
