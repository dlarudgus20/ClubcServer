#pragma once

#include <msclr/marshal.h>
#include <vcclr.h>
using namespace msclr::interop;

#include <windows.h>
#include <time.h>

#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;

#include "../ClubcSvrLib/ChatDataBuf.h"

#include "../CharConvert/CharConvert.h"
#ifdef _DEBUG
#pragma comment(lib, "../CharConvert/CharConvert_Dd.lib")
#else
#pragma comment(lib, "../CharConvert/CharConvert_D.lib")
#endif

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;
using namespace System::Net::Sockets;
using namespace System::Net;
using namespace System::Threading;
using namespace System::IO;
using namespace System::Text;

using namespace ClubcSvrLib_Server;
