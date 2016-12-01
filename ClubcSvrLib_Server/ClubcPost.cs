using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;

namespace ClubcSvrLib_Server
{
	public static class ClubcPost
	{
		public static ClubcReader ReadPost(ClubcUser user, int id)
		{
			return ReadPost(user.UserName, user.Password, id);
		}
		public static ClubcReader ReadPost(string user, string pass, int id)
		{
			return Utility.ExecSql(string.Format("exec ReadPostFromId '{0}', '{1}', '{2}'", user, pass, id));
		}
		public static ClubcReader ReadPost(ClubcUser user, string title)
		{
			return ReadPost(user.UserName, user.Password, title);
		}
		public static ClubcReader ReadPost(string user, string pass, string title)
		{
			return Utility.ExecSql(string.Format("exec ReadPostFromTitle '{0}', '{1}', '{2}'", user, pass, title));
		}

		public static bool WritePost(ClubcUser user, string PostLevel, string title, string writing)
		{
			return WritePost(user.UserName, user.Password, PostLevel, title, writing);
		}
		public static bool WritePost(string user, string pass, string PostLevel, string title, string writing)
		{
			bool bSuccessed;
			Utility.ExecSql(string.Format("exec WritePost '{0}', '{1}', '{2}', '{3}', '{4}'", user, pass, PostLevel, title, writing), out bSuccessed);
			return bSuccessed;
		}

		public static ClubcReader QueryPostTitle(int id)
		{
			return Utility.ExecSql(string.Format("exec QueryPostTitle '{0}'", id));
		}
		public static ClubcReader QueryPostId(string title)
		{
			return Utility.ExecSql(string.Format("exec QueryPostId '{0}'", title));
		}
	}
}
