#include "stdafx.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

// ������� �Ϲ� ������ ���� Ư�� ������ ���� ����˴ϴ�.
// ������� ���õ� ������ �����Ϸ���
// �� Ư�� ���� �����Ͻʽÿ�.
//
[assembly:AssemblyTitleAttribute("IPAddressControl")];
[assembly:AssemblyDescriptionAttribute("Win32�� IPAddress ���� ��Ʈ���� �����մϴ�.")];
#ifdef _DEBUG
[assembly:AssemblyConfigurationAttribute("debug")];
#else
[assembly:AssemblyConfigurationAttribute("release")];
#endif
[assembly:AssemblyCompanyAttribute("IKH")];
[assembly:AssemblyProductAttribute("IPAddressControl")];
[assembly:AssemblyCopyrightAttribute("Copyright (c) IKH 2011")];
[assembly:AssemblyTrademarkAttribute("IPAddressControl")];
[assembly:AssemblyCultureAttribute("")];

//
// ������� ���� ������ ���� �� ���� ������ �����˴ϴ�.
//
//      �� ����
//      �� ����
//      ���� ��ȣ
//      ���� ����
//
// ��� ���� �����ϰų� �Ʒ��� ���� '*'�� ����Ͽ� ���� ��ȣ �� ���� ������ �ڵ�����
// �����ǵ��� �� �� �ֽ��ϴ�.

[assembly:AssemblyVersionAttribute("1.0.0.0")];

[assembly:ComVisible(false)];

[assembly:CLSCompliantAttribute(true)];

[assembly:SecurityPermission(SecurityAction::RequestMinimum, UnmanagedCode = true)];
