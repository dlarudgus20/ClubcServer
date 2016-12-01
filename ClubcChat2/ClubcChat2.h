
// ClubcChat2.h : ClubcChat2 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CClubcChat2App:
// 이 클래스의 구현에 대해서는 ClubcChat2.cpp을 참조하십시오.
//

class CClubcChat2App : public CWinAppEx
{
public:
	CClubcChat2App();


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
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
