using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;

namespace ClubcSvrLib_Server
{
	public class ClubcReader : IDisposable
	{
		private readonly SqlConnection m_Connection;
		private readonly SqlDataReader m_Reader;

		internal ClubcReader(SqlConnection c, SqlDataReader r)
		{
			m_Connection = c;
			m_Reader = r;
		}

		public object this[string str]
		{
			get { return m_Reader[str]; }
		}

		public object this[int idx]
		{
			get { return m_Reader[idx]; }
		}

		public bool Next()
		{
			return m_Reader.Read();
		}

		~ClubcReader()
		{
			Dispose(false);
		}

		public void Dispose()
		{
			Dispose(true);
			GC.SuppressFinalize(this);
		}

		protected void Dispose(bool bManage)
		{
			if (!m_Reader.IsClosed)
			{
				m_Reader.Close();
			}

			try
			{
				m_Connection.Close();
			}
			catch (InvalidOperationException /*e*/)
			{

			}
		}
	}
}
