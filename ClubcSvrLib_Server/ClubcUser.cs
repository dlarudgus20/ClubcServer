using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;

namespace ClubcSvrLib_Server
{
	public sealed class ClubcUser
	{
		public static string GuestUserClassStr
		{
			get
			{
				return "손님";
			}
		}
		public static int GuestUserClassLevel
		{
			get
			{
				return GetClassLevel(GuestUserClassStr);
			}
		}

		public static ClubcUser CreateUser(string user, string pass, string ClassStr, string Nickname)
		{
			bool bSuccessed;
			ClubcReader r = Utility.ExecSql(string.Format("exec CreateClubcUser '{0}', '{1}', '{2}', '{3}'", user, pass, ClassStr, Nickname),
				out bSuccessed);

			if (bSuccessed)
			{
				ClubcUser cu = new ClubcUser();
				cu.UserName = user;
				cu.Password = pass;
				cu.Nickname = Nickname;
				cu.m_UserClassStr = ClassStr;
				return cu;
			}
			else
			{
				return null;
			}
		}

		public static List<string> GetClassStrList()
		{
			ClubcReader r = Utility.ExecSql("select Descript from tblClubcUserClass order by Class");

			if (r != null)
			{
				List<string> ClassStrList = new List<string>();

				do
				{
					ClassStrList.Add((string)r["Descript"]);
				} while (r.Next());

				return ClassStrList;
			}
			else
			{
				return null;
			}
		}

		public static int GetClassLevel(string ClassStr)
		{
			SqlConnection con = new SqlConnection();
			SqlDataReader reader;
			SqlCommand cmd;
			string strCmd;

			try
			{
				con.ConnectionString = "Server=(local);database=ClubcDb;User ID=sa;Pwd=qax_sa_1939";
				con.Open();
			}
			catch (SqlException /*ex*/)
			{
				return -1;
			}

			try
			{
				strCmd = string.Format("select * from tblClubcUserClass where Descript = '{0}'", ClassStr);
				cmd = new SqlCommand(strCmd, con);
				reader = cmd.ExecuteReader();

				if (reader.Read())
				{
					return (int)reader["Class"];
				}
				else
				{
					return -1;
				}
			}
			catch (InvalidOperationException /*ex*/)
			{
				return -1;
			}
			finally
			{
				con.Close();
			}
		}

		public static string GetClassStr(int ClassLevel)
		{
			SqlConnection con = new SqlConnection();
			SqlDataReader reader;
			SqlCommand cmd;
			string strCmd;

			try
			{
				con.ConnectionString = "Server=(local);database=ClubcDb;User ID=sa;Pwd=qax_sa_1939";
				con.Open();
			}
			catch (SqlException /*ex*/)
			{
				return null;
			}

			try
			{
				strCmd = string.Format("select * from tblClubcUserClass where Class = \'{0}\'", ClassLevel);
				cmd = new SqlCommand(strCmd, con);
				reader = cmd.ExecuteReader();

				if (reader.Read())
				{
					return (string)reader["Descript"];
				}
				else
				{
					return null;
				}
			}
			catch (InvalidOperationException /*ex*/)
			{
				return null;
			}
			finally
			{
				con.Close();
			}
		}

		public static bool IsClassLevel(int ClassLevel)
		{
			return GetClassStr(ClassLevel) != "";
		}

		public static bool IsClassStr(string ClassStr)
		{
			return GetClassLevel(ClassStr) != -1;
		}

		public string UserName;
		public string Password;
		public string Nickname;

		internal string m_UserClassStr;

		public int UserClassLevel
		{
			get
			{
				return GetClassLevel(m_UserClassStr);
			}
			set
			{
				string str = GetClassStr(value);

				if(str != null)
				{
					m_UserClassStr = str;
				}
				else
				{
					throw new InvalidOperationException("무효한 ClassLevel입니다.");
				}
			}
		}

		public string UserClassStr
		{
			get
			{
				return (string)m_UserClassStr.Clone();
			}
			set
			{
				if(IsClassStr(value))
				{
					m_UserClassStr = value;
				}
				else
				{
					throw new InvalidOperationException("무효한 ClassStr입니다.");
				}
			}
		}
	}
}
