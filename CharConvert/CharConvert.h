#pragma once

#include <windows.h>

#define _CHAR_CONVERT_API extern "C"

_CHAR_CONVERT_API char *ChrCvt_WideCharToCodePage(const wchar_t *str, UINT CodePage);
_CHAR_CONVERT_API wchar_t *ChrCvt_MultiByteToCodePage(const char *str, UINT CodePage);

#define ChrCvt_WideCharToMultiByte(str) ChrCvt_WideCharToCodePage(str, CP_ACP)
#define ChrCvt_WideCharToUTF8(str) ChrCvt_WideCharToCodePage(str, CP_UTF8)

#define ChrCvt_MultiByteToWideChar(str) ChrCvt_MultiByteToCodePage(str, CP_ACP)
_CHAR_CONVERT_API char *ChrCvt_MultiByteToUTF8(const char *str);

#define ChrCvt_UTF8ToWideChar(str) ChrCvt_MultiByteToCodePage(str, CP_UTF8)
_CHAR_CONVERT_API char *ChrCvt_UTF8ToMultiByte(const char *str);

_CHAR_CONVERT_API void ChrCvt_Free(const void *ptr);
