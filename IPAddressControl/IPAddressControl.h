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
	/// Win32의 IPAddress 컨트룰을 래핑합니다.
	/// </summary>
	/// <remark>
	/// Win32의 IPAddress 컨트룰을 래핑합니다.
	/// 참조 추가하면 윈폼 디자이너 편집기에서 사용할 수 있습니다.
	/// 윈폼 디자이너 편집기에서 컨트롤 이동/선택이 잘 안될 수도 있습니다.
	/// </remark>
	public ref class IPAddressControl sealed : public System::Windows::Forms::UserControl
	{
	public:
		/// <summary>
		/// 생성자입니다.
		/// <summary>
		IPAddressControl(void)
		{
			InitializeComponent();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
		}

	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
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
		/// 필수 디자이너 변수입니다.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다.
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
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
		/// 이 컨트룰이 가진 System.Net.IPAddress값입니다.
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
		/// Volue프로퍼티의 Sytem.String 형입니다.
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
