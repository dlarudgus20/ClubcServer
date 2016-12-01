using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using dnClubcSvrLib;

namespace dnClubcChat2
{
	public partial class Form1 : Form
	{
		private ClubcChatSock sock = new ClubcChatSock();

		public Form1()
		{
			InitializeComponent();
			MinimumSize = new Size(lstCntList.Size.Width + 1, tbChat.Size.Height + 1);
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			LoginDialog dlg = new LoginDialog();

			using (dlg)
			{
				if (dlg.ShowDialog() == DialogResult.OK)
				{
					sock.OnClose += new ClubcChatSock.CloseDele(sock_OnClose);
					sock.OnConnect += new ClubcChatSock.ConnectDele(sock_OnConnect);
					sock.OnReceive += new ClubcChatSock.ReceiveDele(sock_OnReceive);
					sock.OnEvent += new ClubcChatSock.EventDele(sock_OnEvent);
					try
					{
						sock.Create(dlg.SrvIp, dlg.Id, dlg.Password);
					}
					catch (IOException )
					{
						Close();
					}
				}
				else
				{
					Close();
				}
			}
		}

		private void Form1_FormClosed(object sender, FormClosingEventArgs e)
		{
			if (sock.IsInited)
			{
				sock.OnClose -= new ClubcChatSock.CloseDele(sock_OnClose);
				sock.OnConnect -= new ClubcChatSock.ConnectDele(sock_OnConnect);
				sock.OnReceive -= new ClubcChatSock.ReceiveDele(sock_OnReceive);
				sock.OnEvent -= new ClubcChatSock.EventDele(sock_OnEvent);

				sock.SendString(sock.Nickname + " 님께서 나가셨습니다. [2.0.0.15 (Chat) / 1.1 (.Net)]");
				sock.Dispose();
			}
		}

		void sock_OnClose(bool bError)
		{
			try
			{
				Invoke(new Action<object>(delegate(object o)
				{
					if (bError)
					{
						MessageBox.Show(this, "서버와의 통신에 에러가 발생했습니다.", "에러", MessageBoxButtons.OK, MessageBoxIcon.Error);
						Close();
					}
				}), new object[] { null });
			} catch (Exception) { }
		}

		void sock_OnConnect()
		{
			Invoke(new Action<object>(delegate(object o)
				{
					sock.SendString(sock.Nickname + " 님께서 들어오셨습니다. [2.0.0.15 (Chat) / 1.1 (.Net)]");
					tbChat.Enabled = true;
				}), new object[] { null });
		}

		void sock_OnReceive(string str)
		{
			Invoke(new Action<object>(delegate(object o)
				{
					lstChat.Items.Add(str);
					lstChat.SelectedIndex = lstChat.Items.Count - 1;
				}), new object[] { null });
		}

		void sock_OnEvent(ClubcChatSock.ClubcChatSockEvent e, object param)
		{
			Invoke(new Action<object>(delegate(object o)
				{
					switch (e)
					{
						case ClubcChatSock.ClubcChatSockEvent.CntList_Update:
							lstCntList.Items.Clear();
							lstCntList.Items.AddRange(sock.ConnectList);
							break;
						case ClubcChatSock.ClubcChatSockEvent.CntList_Add:
							lstCntList.Items.Add(param);
							break;
						case ClubcChatSock.ClubcChatSockEvent.CntList_Remove:
							lstCntList.Items.Remove(param);
							break;
					}
				}), new object[] { null });
		}

		private void tbChat_KeyPress(object sender, KeyPressEventArgs e)
		{
			if (e.KeyChar == '\r' && tbChat.Text != "")
			{
				sock.SendString(sock.Nickname + " : " + tbChat.Text);
				tbChat.Text = "";
			}
		}

		private void Form1_Layout(object sender, LayoutEventArgs e)
		{
			lstChat.Size = new Size(ClientSize.Width - lstCntList.Size.Width, ClientSize.Height - tbChat.Size.Height);
			lstCntList.Location = new Point(ClientSize.Width - lstCntList.Size.Width, 0);
			lstCntList.Size = new Size(lstCntList.Size.Width, ClientSize.Height - tbChat.Size.Height);
			tbChat.Location = new Point(0, ClientSize.Height - tbChat.Size.Height);
			tbChat.Size = new Size(ClientSize.Width, tbChat.Size.Height);
		}
	}
}
