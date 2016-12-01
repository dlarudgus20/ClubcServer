using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using ClubcSvrLib_Server;

namespace ClubcWeb
{
	public partial class Default : System.Web.UI.Page
	{
		protected void Page_Load(object sender, EventArgs e)
		{
			ClubcUser usr = this.ReadSession<ClubcUser>("usr");
			if (usr == null)
			{
				LoginPanel.Visible = true;
				MainPanel.Visible = false;
			}
			else
			{
				NickLabel.Text = usr.Nickname;

				LoginPanel.Visible = false;
				MainPanel.Visible = true;
			}
		}

		protected void LoginBox_Authenticate(object sender, AuthenticateEventArgs e)
		{
			ClubcUser usr = new ClubcUser();

			if (Authentication.Login(LoginBox.UserName, LoginBox.Password, usr))
			{
				Session["usr"] = usr;
				e.Authenticated = true;
			}
			else
			{
				e.Authenticated = false;
			}
		}

		protected void GoChatBtn_Click(object sender, EventArgs e)
		{
			Response.Redirect("~/WebClubcChat2.aspx");
		}

		protected void LogoutBtn_Click(object sender, EventArgs e)
		{
			Session["usr"] = null;
			if (Session["ChatSock"] != null)
			{
				((ClientSock)Session["ChatSock"]).Dispose();
			}
			Response.Redirect("~/Default.aspx");
		}
	}
}