using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using ClubcSvrLib_Server;
using dnClubcSvrLib;

namespace ClubcWeb
{
	public class ClientSock : IDisposable
	{
		private ClubcChatSock m_sock = new ClubcChatSock();
		private ICollection<string> m_ChatStr = new List<string>();

		public ICollection<string> ChatStr { get { return m_ChatStr; } }
		public string Nickname { get { return m_sock.Nickname; } }

		public ICollection<string> CntList { get { return m_sock.ConnectList; } }

		private bool m_CntListUpdated = false;
		public bool CntListUpdated
		{
			get
			{
				bool ret = m_CntListUpdated;
				m_CntListUpdated = false;
				return ret;
			}
			private set
			{
				m_CntListUpdated = value;
			}
		}

		public bool IsClosed { get; private set; }

		public ClientSock(ClubcUser usr)
		{
			m_sock.OnClose += new ClubcChatSock.CloseDele(m_sock_OnClose);
			m_sock.OnConnect += new ClubcChatSock.ConnectDele(m_sock_OnConnect);
			m_sock.OnEvent += new ClubcChatSock.EventDele(m_sock_OnEvent);
			m_sock.OnReceive += new ClubcChatSock.ReceiveDele(m_sock_OnReceive);

			m_sock.Create("127.0.0.1", usr.UserName, usr.Password);
		}

		public void SendString(string str)
		{
			m_sock.SendString(str);
		}

		void m_sock_OnReceive(string str)
		{
			lock (this)
			{
				m_ChatStr.Add(str);
			}
		}

		void m_sock_OnEvent(ClubcChatSock.ClubcChatSockEvent e, object param)
		{
			CntListUpdated = true;
		}

		void m_sock_OnConnect()
		{
			m_sock.SendString(m_sock.Nickname + "님께서 들어오셨습니다. [2.0.0.15 (ClubcChat) / 1.0 (Web)]");
		}

		void m_sock_OnClose(bool bError)
		{
			IsClosed = true;
		}

		public void Dispose()
		{
			if (m_sock.IsConnected)
			{
				m_sock.SendString(m_sock.Nickname + "님께서 나가셨습니다. [2.0.0.15 (ClubcChat) / 1.0 (Web)]");
				m_sock.Dispose();
			}
		}
	}
}