#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Net;

namespace IPAddressControl {

	/// <summary>
	/// Win32�� IPAddress ��Ʈ���� �����մϴ�.
	/// </summary>
	/// <remark>
	/// Win32�� IPAddress ��Ʈ���� �����մϴ�.
	/// ���� �߰��ϸ� ���� �����̳� �����⿡�� ����� �� �ֽ��ϴ�.
	/// ���� �����̳� �����⿡�� ��Ʈ�� �̵�/������ �� �ȵ� ���� �ֽ��ϴ�.
	/// </remark>
	public ref class IPAddressControl sealed : public System::Windows::Forms::UserControl
	{
	public:
		/// <summary>
		/// �������Դϴ�.
		/// <summary>
		IPAddressControl(void)
		{
			InitializeComponent();
			//
			//TODO: ������ �ڵ带 ���⿡ �߰��մϴ�.
			//
		}

	protected:
		/// <summary>
		/// ��� ���� ��� ���ҽ��� �����մϴ�.
		/// </summary>
		~IPAddressControl()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// �ʼ� �����̳� �����Դϴ�.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����̳� ������ �ʿ��� �޼����Դϴ�.
		/// �� �޼����� ������ �ڵ� ������� �������� ���ʽÿ�.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// IPAddressControlControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->MaximumSize = System::Drawing::Size(150, 24);
			this->MinimumSize = System::Drawing::Size(150, 24);
			this->Name = L"IPAddressControlControl";
			this->Size = System::Drawing::Size(150, 24);
			this->Load += gcnew System::EventHandler(this, &IPAddressControl::IPAddressControlControl_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
		HWND hIP;
	private: System::Void IPAddressControlControl_Load(System::Object^  sender, System::EventArgs^  e) {
				   hIP = ::CreateWindow(WC_IPADDRESS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, 0, 0, 150, 24,
					   (HWND)(void *) Handle, NULL, ::GetModuleHandle(NULL), 0);
			   }
	public:
		/// <summary>
		/// �� ��Ʈ���� ���� System.Net.IPAddress���Դϴ�.
		/// </summary>
		property IPAddress ^Value
		{
			IPAddress ^get()
			{
				DWORD dwIp;

				::SendMessage(hIP, IPM_GETADDRESS, 0, (LPARAM) &dwIp);
				return gcnew IPAddress(gcnew array<Byte>(4) {
					FIRST_IPADDRESS(dwIp), SECOND_IPADDRESS(dwIp), THIRD_IPADDRESS(dwIp), FOURTH_IPADDRESS(dwIp)});
			}
			void set(IPAddress ^ip)
			{
				array<Byte> ^ar = ip->GetAddressBytes();
				DWORD dwIp = 0;

				dwIp += ar[3];
				dwIp += ar[2] << 8;
				dwIp += ar[1] << 16;
				dwIp += ar[0] << 24;

				::SendMessage(hIP, IPM_SETADDRESS, 0, (LPARAM) dwIp);
			}
		}

		/// <summary>
		/// Volue������Ƽ�� Sytem.String ���Դϴ�.
		/// </summary>
		property String ^Text
		{
			virtual String ^get() override
			{
				return Value->ToString();
			}
			virtual void set(String ^str) override
			{
				Value = IPAddress::Parse(str);
			}
		}
	};
}
