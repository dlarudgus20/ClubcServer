// ClubcSvrLib.h : ClubcSvrLib DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CClubcSvrLibApp
// �� Ŭ������ ������ ������ ClubcSvrLib.cpp�� �����Ͻʽÿ�.
//
#include "../Common.h"

class CClubcSvrLibApp : public CWinApp
{
public:
	CClubcSvrLibApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
