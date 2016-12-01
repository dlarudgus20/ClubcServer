#include "stdafx.h"
#include "ClubcChatingProcServer.h"
#include "Log.h"

// 아무 것도 #define 하지 않으면 디폴트(SQL 서버 이용)
//#define _SRV_FOR_OTHRES

class Crit
{
private:
	CRITICAL_SECTION m_crit;
public:
	Crit() { InitializeCriticalSection(&m_crit); }
	~Crit() { DeleteCriticalSection(&m_crit); }
	class Enter
	{
	private:
		Crit *m_pCrit;
	public:
		Enter(Crit *pCrit) : m_pCrit(pCrit) { EnterCriticalSection(&m_pCrit->m_crit); }
		~Enter() { LeaveCriticalSection(&m_pCrit->m_crit); }
	};
};

#if defined(_SRV_FOR_OTHRES)
bool Login(const char *id, const char *pw, ClubcUser ^usr)
{
	const wchar_t *uid = ChrCvt_UTF8ToWideChar(id);
	const wchar_t *upw = ChrCvt_UTF8ToWideChar(pw);

	try
	{
Log::Get().lf(L"Login Try : %s %s", uid, upw);

		usr->UserName = gcnew String(uid);
		usr->Password = gcnew String(upw);
		usr->Nickname = usr->UserName;
	}
	finally
	{
		ChrCvt_Free(uid);
		ChrCvt_Free(upw);
	}
	return true;
}
#else
bool Login(const char *id, const char *pw, ClubcUser ^usr)
{
	const wchar_t *uid = ChrCvt_UTF8ToWideChar(id);
	const wchar_t *upw = ChrCvt_UTF8ToWideChar(pw);

	try
	{
Log::Get().lf("Login Try : %s %s", uid, upw);
		return Authentication::Login(gcnew String(uid), gcnew String(upw), usr);
	}
	finally
	{
		ChrCvt_Free(uid);
		ChrCvt_Free(upw);
	}
}
#endif
