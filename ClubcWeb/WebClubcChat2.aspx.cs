using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.Services;
using ClubcSvrLib_Server;

namespace ClubcWeb
{
	public partial class WebClubcChat2 : System.Web.UI.Page
	{
		protected void Page_Load(object sender, EventArgs e)
		{
			ClubcUser usr;
			if (this.CheckLogined(out usr))
			{
				ClientSock sock = this.ReadSession<ClientSock>("ChatSock");
				if (sock == null)
				{
					try
					{
						Session["ChatSock"] = new ClientSock(usr);
					}
					catch (System.IO.IOException)
					{
						this.ErrorMsg("소켓 열기에 실패했습니다.");
					}
				}
			}
		}

		protected void ChatBox_TextChanged(object sender, EventArgs e)
		{
			if (ChatBox.Text.Length >= 2 && ChatBox.Text[ChatBox.Text.Length - 1] == '\n')
			{
				ClientSock sock = (ClientSock)Session["ChatSock"];
				sock.SendString(sock.Nickname + " : " + ChatBox.Text);
			}
		}

		protected void Timer1_Tick(object sender, EventArgs e)
		{
			ClientSock sock = (ClientSock)Session["ChatSock"];
			if (sock != null)
			{
				lock (sock)
				{
					foreach (string str in sock.ChatStr)
					{
						ChatList.Items.Add(str);
					}
					sock.ChatStr.Clear();
	
					if (sock.CntListUpdated)
					{
						CntList.Items.Clear();
						foreach (string str in sock.CntList)
						{
							CntList.Items.Add(str);
						}
					}
				}
			}
		}
	}
}