using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Threading;
using System.IO;

namespace dnClubcSvrLib
{
	/// <summary>
	/// ClubC 서버와 연결하기 위한 소켓 클래스입니다.
	/// </summary>
	/// <remarks>
	/// ClubC 서버와 연결하기 위한 소켓 클래스입니다.<br/>
	/// 주요한 이벤트들이 발생하면 이 클래스의 event 멤버가 호출됩니다. 예를 들어, 소켓이 닫히면 <see cref="OnClose" />가 호출됩니다.
	/// <p><font color="blue">참고 : 공식 Clubc Server의 IP 주소는 14.46.56.226 입니다. 이 정보는 언제든지 바뀔 수도 있습니다. 자세한건 <a href="http://cafe.naver.com/clubc">http://cafe.naver.com/clubc</a>를 참조하십시오.</font></p>
	/// <p><font color="red">주의! : 이벤트들은 다른 작업자 스레드에서 호출됩니다. Windows Forms 프로그래밍을 하고 있다면 <see cref="System.Windows.Forms.Control.Invoke(Delegate,object[])" /> 메서드를 사용해 주십시오.</font></p>
	/// </remarks>
	/// <example>
	/// 다음은 이 클래스를 활용하는 예시를 보여줍니다.
	/// <code>
	/// using System;
	/// using dnClubcSvrLib;
	///
	/// class Program
	/// {
	///     private static ClubcChatSock s;
	///     private static bool bClose = false;
	///
	///     static void Main()
	///     {
	///         s = new ClubcChatSock();
	///         s.OnReceive += OnReceive;
	///         s.OnClose += OnClose;
	///         s.OnConnect += OnConnect;
	///         s.OnEvent += OnEvent;
	///         try
	///         {
	///             s.Create("14.46.56.226", "1", "1"); ///  아이디 1 비밀번호 1은 손님용 계정입니다.
	/// 
	///             while (true)
	///             {
	///                 string input = Console.ReadLine();
	///                 if (bClose) break;
	///                 s.SendString(input);
	///             }
	///         }
	///         catch (System.IO.IOException)
	///         {
	///             Console.WriteLine("접속 에러");
	///         }
	///     }
	///     static void OnReceive(string str)
	///     {
	///         Console.WriteLine(str);
	///     }
	///     static void OnClose(bool bError)
	///     {
	///         Console.WriteLine("소켓이 종료되었습니다.");
	///         bClose = true;
	///     }
	///     static void OnConnect()
	///     {
	///         s.SendString(s.Nickname + "님이 입장하셨습니다!");
	///     }
	///     static void OnEvent(ClubcChatSock.ClubcChatSockEvent e, object param)
	///     {
	///         switch (e)
	///         {
	///             case ClubcChatSock.ClubcChatSockEvent.CntList_Update:
	///                 Console.WriteLine("현재 접속 목록 : ");
	///                 foreach (string nick in s.ConnectList)
	///                 {
	///                     Console.WriteLine("\t" + nick);
	///                 }
	///                 break;
	///             case ClubcChatSock.ClubcChatSockEvent.CntList_Add:
	///                 Console.WriteLine((string)param + "님이 접속하셨습니다.");
	///                 break;
	///             case ClubcChatSock.ClubcChatSockEvent.CntList_Remove:
	///                 Console.WriteLine((string)param + "님이 나가셨습니다.");
	///                 break;
	///         }
	///     }
	/// }
	/// </code>
	/// 더 자세한 예제는 같이 배포되는 dnClubcChat2 프로젝트를 참조하십시오.
	/// </example>
	public sealed partial class ClubcChatSock : IDisposable
	{
		/// <summary>
		/// 통신할 수 있는 최대 바이트 수입니다.
		/// </summary>
		/// <remarks>
		/// 통신할 수 있는 최대 바이트 수입니다.<br/>
		/// <font color="red">주의! : 이 수치는 바이트 단위입니다. Char은 2byte임을 주의하십시오.</font>
		/// </remarks>
		public const int MaxBuffer = 1024;

		/// <summary>
		/// <see cref="OnEvent"/>에 발생하는 이벤트입니다.
		/// </summary>
		public enum ClubcChatSockEvent
		{
			/// <summary>
			/// 접속자 리스트가 새로 바뀝니다.
			/// 추가 파라미터는 없습니다.
			/// </summary>
			CntList_Update,
			/// <summary>
			/// 접속자가 추가됩니다.
			/// 추가 파라미터엔 추가된 접속자의 닉네임이 옵니다.
			/// </summary>
			CntList_Add,
			/// <summary>
			/// 접속자가 제거됩니다.
			/// 추가 파라미터엔 제거된 접속자의 닉네임이 옵니다.
			/// </summary>
			CntList_Remove
		}

		/// <summary>
		/// 사용자가 임의로 사용할 수 있는 변수입니다.
		/// </summary>
		public object UserData;

		/// <summary>
		/// 소켓이 종료될때 호출되는 델리게이트입니다.
		/// </summary>
		/// <param name="bError">비정상 종료인지의 여부를 나타냅니다.</param>
		/// <seealso cref="Dispose"/>
		public delegate void CloseDele(bool bError);
		/// <summary>
		/// 소켓이 종료될 때 호출됩니다.
		/// </summary>
		/// <remarks>
		/// 소켓이 종료될 때 호출됩니다.
		/// 이 이벤트는 다른 작업자 스레드에서 발생합니다.
		/// </remarks>
		/// <seealso cref="Dispose"/>
		public event CloseDele OnClose;

		/// <summary>
		/// 소켓이 서버와 연결될때 호출되는 델리게이트입니다.
		/// </summary>
		/// <seealso cref="IsConnected"/>
		public delegate void ConnectDele();
		/// <summary>
		/// 소켓이 서버와 연결될 때 호출됩니다.
		/// </summary>
		/// <remarks>
		/// 소켓이 서버와 연결될 때 호출됩니다.
		/// 이 이벤트는 다른 작업자 스레드에서 발생합니다.
		/// </remarks>
		/// <seealso cref="IsConnected"/>
		public event ConnectDele OnConnect;

		/// <summary>
		/// 문자열을 받았을 때 호출되는 델리게이트입니다.
		/// </summary>
		/// <param name="str">받은 문자열입니다.</param>
		public delegate void ReceiveDele(string str);
		/// <summary>
		/// 문자열을 받았을 때 호출됩니다.
		/// </summary>
		/// <remarks>
		/// 문자열을 받았을 때 호출됩니다.
		/// 이 이벤트는 다른 작업자 스레드에서 발생합니다.
		/// </remarks>
		public event ReceiveDele OnReceive;

		/// <summary>
		/// 이벤트가 발생했을 때 호출되는 델리게이트입니다.
		/// </summary>
		/// <param name="e">발생한 이벤트입니다.</param>
		/// <param name="param">추가 파라미터입니다. 발생한 이벤트에 따라 의미가 달라집니다.</param>
		public delegate void EventDele(ClubcChatSockEvent e, object param);
		/// <summary>
		/// 이벤트가 발생했을 때 호출되는 델리게이트입니다.
		/// </summary>
		/// <remarks>
		/// 이벤트가 발생했을 때 호출되는 델리게이트입니다.
		/// 이 이벤트는 다른 작업자 스레드에서 발생합니다.
		/// </remarks>
		/// <seealso cref="ClubcChatSockEvent"/>
		public event EventDele OnEvent;

		/// <summary>
		/// 생성자입니다.
		/// </summary>
		/// <remarks>
		/// 기본 생성자입니다. <see cref="Create(string,string,string,object)"/>를 호출하기 전까지 이 객체는 무효한 상태가 됩니다.
		/// </remarks>
		public ClubcChatSock() { }

		/// <summary>
		/// 생성자입니다.
		/// </summary>
		/// <exception cref="IOException">소켓 생성 및 통신 에러입니다.</exception>
		/// <param name="onclose">OnClose 이벤트가 발생할때 호출될 델리게이트입니다.</param>
		/// <param name="onconnect">OnConnect 이벤트가 발생할때 호출될 델리게이트입니다.</param>
		/// <param name="onrecv">OnReceive 이벤트가 발생할때 호출될 델리게이트입니다.</param>
		/// <param name="onevent">OnEvent 이벤트가 발생할때 호출될 델리게이트입니다.</param>
		/// <param name="server">서버의 주소입니다.</param>
		/// <param name="id">로그인할 아이디입니다.</param>
		/// <param name="pw">로그인할 비밀번호입니다.</param>
		/// <example>
		/// 다음 예제는 이 생성자를 이용해 ClubcChat 서버와 연결하는 법을 보여줍니다.
		/// <code>
		/// ClubcChatSock Login(string id, string pw)
		/// {
		///		return new ClubcChatSock(new ClubcChatSock.CloseDele(OnClose), new ClubcChatSock.ConnectDele(OnConnect),
		///			new ClubcChatSock.ReceiveDele(OnReceive), new ClubcChatSock.EventDele(OnEvent), "14.46.56.226", id, pw);
		///		// 14.46.56.226은 공식 Clubc Server의 IP입니다.
		/// }
		/// </code>
		/// </example>
		/// <seealso cref="UserData"/>
		public ClubcChatSock(CloseDele onclose, ConnectDele onconnect, ReceiveDele onrecv, EventDele onevent, 
			string server, string id, string pw)
			: this(onclose, onconnect, onrecv, onevent, server, id, pw, null) { }

		/// <summary>
		/// 생성자입니다.
		/// </summary>
		/// <exception cref="IOException">소켓 생성 및 통신 에러입니다.</exception>
		/// <param name="onclose">OnClose 이벤트가 발생할때 호출될 델리게이트입니다.</param>
		/// <param name="onconnect">OnConnect 이벤트가 발생할때 호출될 델리게이트입니다.</param>
		/// <param name="onrecv">OnReceive 이벤트가 발생할때 호출될 델리게이트입니다.</param>
		/// <param name="onevent">OnEvent 이벤트가 발생할때 호출될 델리게이트입니다.</param>
		/// <param name="server">서버의 주소입니다.</param>
		/// <param name="id">로그인할 아이디입니다.</param>
		/// <param name="pw">로그인할 비밀번호입니다.</param>
		/// <param name="usr">UserData의 초기값입니다.</param>
		/// <example>
		/// 다음 예제는 이 생성자를 이용해 ClubcChat 서버와 연결하는 법을 보여줍니다.
		/// <code>
		/// ClubcChatSock Login(string id, string pw)
		/// {
		///		return new ClubcChatSock(new ClubcChatSock.CloseDele(OnClose), new ClubcChatSock.ConnectDele(OnConnect),
		///			new ClubcChatSock.ReceiveDele(OnReceive), new ClubcChatSock.EventDele(OnEvent), "14.46.56.226", id, pw, null);
		///		// 14.46.56.226은 공식 Clubc Server의 IP입니다.
		/// }
		/// </code>
		/// </example>
		/// <seealso cref="UserData"/>
		public ClubcChatSock(CloseDele onclose, ConnectDele onconnect, ReceiveDele onrecv, EventDele onevent,
			string server, string id, string pw, object usr)
		{
			OnClose += onclose;
			OnConnect += onconnect;
			OnReceive += onrecv;
			OnEvent += onevent;
			Create(server, id, pw, usr);
		}

		/// <summary>
		/// 소켓을 생성하는 함수입니다.
		/// </summary>
		/// <exception cref="IOException">소켓 생성 및 통신 에러입니다.</exception>
		/// <param name="server">서버의 주소입니다.</param>
		/// <param name="id">로그인할 아이디입니다.</param>
		/// <param name="pw">로그인할 비밀번호입니다.</param>
		/// <example>
		/// 다음 예제는 이 함수를 이용해 ClubcChat 서버와 연결하는 법을 보여줍니다.
		/// <code>
		/// void Login(ClubcChatSock sock, string id, string pw)
		/// {
		///		sock.Create("14.46.56.226", id, pw);
		///		// 14.46.56.226은 공식 Clubc Server의 IP입니다.
		/// }
		/// </code>
		/// </example>
		/// <seealso cref="UserData"/>
		public void Create(string server, string id, string pw)
		{
			Create(server, id, pw, null);
		}

		/// <summary>
		/// 소켓을 생성하는 함수입니다.
		/// </summary>
		/// <exception cref="IOException">소켓 생성 및 통신 에러입니다.</exception>
		/// <param name="server">서버의 주소입니다.</param>
		/// <param name="id">로그인할 아이디입니다.</param>
		/// <param name="pw">로그인할 비밀번호입니다.</param>
		/// <param name="usr">UserData의 초기값입니다.</param>
		/// <example>
		/// 다음 예제는 이 함수를 이용해 ClubcChat 서버와 연결하는 법을 보여줍니다.
		/// <code>
		/// void Login(ClubcChatSock sock, string id, string pw)
		/// {
		///		sock.Create("14.46.56.226", id, pw, null);
		///		// 14.46.56.226은 공식 Clubc Server의 IP입니다.
		/// }
		/// </code>
		/// </example>
		/// <seealso cref="UserData"/>
		public void Create(string server, string id, string pw, object usr)
		{
			UserData = usr;
			bNormalClose = true; // 1.1 bugfix

			try
			{
				m_sock = new TcpClient(server, m_port);

				m_thrd = new Thread(this.ReceiverThread);
				m_thrd.IsBackground = true;
				m_thrd.Start();

				lock (m_sock)
				{
					m_sock.GetStream().Write(m_cntstr, 0, m_cntstr.Length);
				}
				SendString(id);
				SendString(pw);
			}
			catch (SocketException e)
			{
				throw new IOException(e.Message, e);
			}
			catch (ObjectDisposedException e)
			{
				throw new IOException(e.Message, e);
			}
		}

		/// <summary>
		/// 파괴자입니다.
		/// </summary>
		~ClubcChatSock()
		{
			Close();
		}

		/// <summary>
		/// 객체를 명시적으로 해제합니다.
		/// </summary>
		/// <seealso cref="OnClose"/>
		public void Dispose()
		{
			Close();
			GC.SuppressFinalize(this);
		}

		/// <summary>
		/// 문자열을 전송합니다.
		/// </summary>
		/// <param name="str">전송할 문자열입니다.</param>
		/// <example>
		/// 다음 예제는 이 함수로 문자열을 전송하는 예를 보여줍니다.
		/// <code>
		/// sock.SendString("안녕하세요? " + sock.Nickname + " 입니다.");
		/// </code>
		/// </example>
		public void SendString(string str)
		{
			try
			{
				byte[] utf8 = Encoding.UTF8.GetBytes(str);

				byte[] send = new byte[utf8.Length + 1];
				utf8.CopyTo(send, 0);
				send[utf8.Length] = 0;

				lock (m_sock)
				{
					m_sock.GetStream().Write(send, 0, send.Length);
				}
			}
			catch (ObjectDisposedException e)
			{
				throw new IOException(e.Message, e);
			}
		}

		/// <summary>
		/// 소켓이 생성됬는지 여부를 조사합니다.
		/// </summary>
		public bool IsInited { get { return m_sock != null; } }

		/// <summary>
		/// 소켓이 서버와 연결됬는지 여부를 조사합니다.
		/// </summary>
		/// <seealso cref="OnConnect"/>
		public bool IsConnected { get { return m_bConnected; } }

		/// <summary>
		/// 접속자 목록입니다.
		/// </summary>
		public string[] ConnectList { get { return m_CntList.ToArray(); } }

		/// <summary>
		/// 접속자 목록입니다.
		/// </summary>
		/// <remarks>
		/// 접속자 목록입니다.<br/>
		/// 소켓이 연결되지 않았을 경우 null입니다.
		/// </remarks>
		/// <seealso cref="IsConnected"/>
		/// <seealso cref="OnConnect"/>
		public string Nickname { get { return m_Nickname; } }
	}
}
