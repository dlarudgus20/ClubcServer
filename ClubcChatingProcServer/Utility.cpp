#include "stdafx.h"
#include "Utility.h"
#include "Data.h"

void ByteArrToCStr(array<Byte> ^ar, char *buf)
{
	pin_ptr<Byte> pData = &ar[0];

	CopyMemory(buf, pData, ar->Length);
}

array<Byte> ^CStrToByteArr(const char *str)
{
	int len = strlen(str) + 1;
	array<Byte> ^ar = gcnew array<Byte>(len);

	Marshal::Copy((IntPtr)(void *)str, ar, 0, len);
	return ar;
}
