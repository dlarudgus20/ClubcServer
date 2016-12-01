using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using ClubcSvrLib_Server;

namespace ClubcWeb
{
	public static class Utility
	{
		public static void RunJScript(this Page p, string script)
		{
			p.Response.Write("<script type=\"text/javascript\">" + script + "</script>");
		}

		public static void ErrorMsg(this Page p, string msg)
		{
			p.RunJScript("alert('" + msg + "'); location.href = 'Default.aspx';");
		}

		public static bool CheckLogined(this Page p)
		{
			ClubcUser usr;
			return p.CheckLogined(out usr);
		}
		public static bool CheckLogined(this Page p, out ClubcUser usr)
		{
			usr = p.ReadSession<ClubcUser>("usr");
			if (usr != null)
			{
				return true;
			}
			else
			{
				p.ErrorMsg("로그인하지 않았습니다!");
				return false;
			}
		}
	}
}