#pragma once

#include <fstream>

class Log
{
private:
	std::fstream m_LogFile;
	gcroot<Object ^> m_WaitObj;

	Log() : m_LogFile("D:\\ClubcChatingProcServerLog.txt", ios_base::out), m_WaitObj(gcnew Object)
	{
		Logging("Server Start");
	}
public:
	static Log &Get();
	void Logging(const char *str);
	void Logging(const wchar_t *str);
	void Logging(String ^str);

	void lf(const char *format, ...);
	void lf(const wchar_t *format, ...);
};

inline void Logging(const char *str)
{
	Log::Get().Logging(str);
}

inline void Logging(const wchar_t *str)
{
	Log::Get().Logging(str);
}

inline void Logging(String ^str)
{
	Log::Get().Logging(str);
}
