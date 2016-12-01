using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;

namespace ClubcSvrLib_Server
{
	public static class Authentication
	{
		public static bool Login(string UserName, string Password)
		{
			return Login(UserName, Password, null);
		}

		public static bool Login(string UserName, string Password, ClubcUser user)
		{
			SqlConnection con = new SqlConnection();
			SqlDataReader reader;
			SqlCommand cmd;
			string strCmd;
			bool bRet;

			try
			{
				con.ConnectionString = "Server=(local);database=ClubcDb;User ID=sa;Pwd=qax_sa_1939";
				con.Open();

				strCmd = string.Format("exec ClubcSvrLogin \'{0}\', \'{1}\'", UserName, Password);
				cmd = new SqlCommand(strCmd, con);
				reader = cmd.ExecuteReader();

				if (reader.Read())
				{
					if(user != null)
					{
						user.UserName = (string)reader["ID"];
						user.Password = (string)reader["Pass"];
						user.Nickname = (string)reader["Nickname"];
						user.m_UserClassStr = (string)reader["Class"];
					}
					bRet = true;
				}
				else
				{
					bRet = false;
				}
			}
			catch (SqlException /*ex*/)
			{
				//
				return false;
			}
			catch (InvalidOperationException /*ex*/)
			{
				//
				return false;
			}

			con.Close();
			return bRet;
		}
	}
}
