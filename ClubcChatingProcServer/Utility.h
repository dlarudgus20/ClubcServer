#pragma once

void ByteArrToCStr(array<Byte> ^ar, char *buf);
array<Byte> ^CStrToByteArr(const char *str);

inline String ^Utf8CStrToNetStr(const char *str)
{
	return Encoding::UTF8->GetString(CStrToByteArr(str));
}
