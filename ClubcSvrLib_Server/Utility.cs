using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;

namespace ClubcSvrLib_Server
{
	public static class Utility
	{
		public static ClubcReader ExecSql(string sql)
		{
			bool b;
			return ExecSql(sql, out b);
		}

		public static ClubcReader ExecSql(string sql, out bool bSuccessed)
		{
			SqlConnection con = new SqlConnection();
			SqlDataReader reader;
			SqlCommand cmd;

			try
			{
				con.ConnectionString = "Server=(local);database=ClubcDb;User ID=sa;Pwd=qax_sa_1939";
				con.Open();
			}
			catch (SqlException /*ex*/)
			{
				bSuccessed = false;
				return null;
			}

			try
			{
				cmd = new SqlCommand(sql, con);
				reader = cmd.ExecuteReader();

				bSuccessed = true;

				if (reader.Read())
				{
					return new ClubcReader(con, reader);
				}
				else
				{
					return null;
				}
			}
			catch (SqlException /*ex*/)
			{
				bSuccessed = false;
				return null;
			}
			catch (InvalidOperationException /*ex*/)
			{
				bSuccessed = false;
				return null;
			}
		}
	}
}
