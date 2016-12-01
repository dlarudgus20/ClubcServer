#include "stdafx.h"
#include "Log.h"
#include <stdarg.h>

Log &Log::Get()
{
	static Log g;
	return g;
}

void Log::Logging(const char *str)
{
	Monitor::Enter(m_WaitObj);

	try
	{
		char buf[512];
		time_t t;

		time(&t);
		strcpy_s(buf, ctime(&t));
		buf[strlen(buf) - 1] = '\0';

		m_LogFile << str << " [" << buf << ']' << endl;
	}
	finally
	{
		Monitor::Exit(m_WaitObj);
	}
}

void Log::Logging(const wchar_t *str)
{
	const char *astr = ChrCvt_WideCharToMultiByte(str);
	Logging(astr);
	ChrCvt_Free(astr);
}

void Log::Logging(String ^str)
{
	const char *chars = (const char*)Marshal::StringToHGlobalAnsi(str).ToPointer();
	Logging(chars);
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void Log::lf(const char *format, ...)
{
	char buf[2048];
	va_list va;

	va_start(va, format);

	vsnprintf(buf, sizeof(buf) / sizeof(buf[0]), format, va);
	this->Logging(buf);

	va_end(va);
}

void Log::lf(const wchar_t *format, ...)
{
	wchar_t buf[2048];
	va_list va;

	va_start(va, format);

	_vsnwprintf(buf, sizeof(buf) / sizeof(buf[0]), format, va);
	this->Logging(buf);

	va_end(va);
}
