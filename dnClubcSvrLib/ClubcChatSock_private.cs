using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Threading;
using System.IO;

namespace dnClubcSvrLib
{
	partial class ClubcChatSock
	{
		private const int m_port = 35729;

		private static byte[] m_cntstr;				// m_cnt~, m_cmd는 상수입니다. 다만 컴파일 오류가 있어서 일반 static으로 선언됩니다.
		private static byte[] m_cnt_succeed;
		private static byte[] m_cmd_mynick;

		private static byte[] m_cmd_cntlist_begin;
		private static byte[] m_cmd_cntlist_end;

		private static byte[] m_cmd_cntlist_add;
		private static byte[] m_cmd_cntlist_remove;

		private TcpClient m_sock = null;
		private Thread m_thrd = null;

		private bool m_bConnected = false;
		private string m_Nickname = null;
		private List<string> m_CntList = new List<string>();
		private bool m_bProcCntList = false;

		// 1.1 bugfix
		private bool bNormalClose = false;

		static ClubcChatSock()
		{
			m_cntstr = new byte[] { (byte)0xa2, (byte)0xa0, (byte)0xa0, (byte)0xb4, 0 };
			m_cnt_succeed = new byte[] { (byte)0x7f, (byte)0x0a, (byte)0x2f, (byte)0x55, (byte)0xda, (byte)0x72, 0 };
			m_cmd_mynick = new byte[] { (byte)0xf2, (byte)0x3b, (byte)0x7f, (byte)0xee, (byte)0xc9, (byte)0x76 };

			m_cmd_cntlist_begin = new byte[] { (byte)0xe9, (byte)0x3f, (byte)0x77, (byte)0x79, (byte)0x1d, (byte)0x36, (byte)0x9a, (byte)0x83, 0 };
			m_cmd_cntlist_end = new byte[] { (byte)0x93, (byte)0x11, (byte)0xf8, (byte)0x8e, (byte)0x0a, (byte)0xf0, (byte)0x5a, (byte)0x82, 0 };

			m_cmd_cntlist_add = new byte[] { (byte)0x98, (byte)0x1f, (byte)0x9c, (byte)0x3a, (byte)0x9f, (byte)0xef, (byte)0xf9, (byte)0xfa, (byte)0x7b };
			m_cmd_cntlist_remove = new byte[] { (byte)0xa1, (byte)0xfa, (byte)0x93, (byte)0x91, (byte)0x82, (byte)0x90, (byte)0x46, (byte)0x72, (byte)0x13 };
		}

		private void Close()
		{
			try
			{
				OnClose(false);
			}
			catch (NullReferenceException) { }

			if (m_sock != null)
			{
				bNormalClose = true;  // 1.1 bugfix
				m_sock.Close();
			}
		}

		private void ReceiverThread()
		{
			byte[] ReadBuf = new byte[MaxBuffer];
			MemoryStream arRecv;
			
			int i, nRead;

			try
			{
				while (true)
				{
					if ((nRead = m_sock.GetStream().Read(ReadBuf, 0, ReadBuf.Length)) <= 0) throw new IOException("socket read error");

					arRecv = new MemoryStream();
					for (i = 0; i < nRead; i++)
					{
						arRecv.WriteByte(ReadBuf[i]);
						if (ReadBuf[i] == 0)
						{
							InterOnReceive(arRecv.ToArray());
							arRecv.Dispose();
							arRecv = new MemoryStream();
						}
					}
					if (ReadBuf[i - 1] != 0)
					{
						InterOnReceive(arRecv.ToArray());
					}
					arRecv.Dispose();
				}
			}
			catch (IOException)
			{

			}
			catch (ObjectDisposedException)
			{

			}

			try
			{
				m_sock = null;

				if (!bNormalClose)  // 1.1 bugfix
					OnClose(true);
			} catch (NullReferenceException) { }
		}

		private void InterOnReceive(byte[] arRecv)
		{
			byte[] tmpar;

			try
			{
				if (byteArrCmp(arRecv, m_cnt_succeed))
				{
					m_bConnected = true;
					OnConnect();
				}
				else if (byteArrNCmp(arRecv, m_cmd_mynick, m_cmd_mynick.Length))
				{
					tmpar = subByteArr(arRecv, m_cmd_mynick.Length, arRecv.Length - m_cmd_mynick.Length - 1);
					m_Nickname = Encoding.UTF8.GetString(tmpar);
				}
				else if (byteArrNCmp(arRecv, m_cmd_cntlist_add, m_cmd_cntlist_add.Length))
				{
					tmpar = subByteArr(arRecv, m_cmd_cntlist_add.Length);
					string str = Encoding.UTF8.GetString(tmpar);
					m_CntList.Add(str);
					OnEvent(ClubcChatSockEvent.CntList_Add, str);
				}
				else if (byteArrNCmp(arRecv, m_cmd_cntlist_remove, m_cmd_cntlist_remove.Length))
				{
					tmpar = subByteArr(arRecv, m_cmd_cntlist_remove.Length);
					string str = Encoding.UTF8.GetString(tmpar);
					m_CntList.Remove(str);
					OnEvent(ClubcChatSockEvent.CntList_Remove, str);
				}
				else if (byteArrCmp(arRecv, m_cmd_cntlist_begin))
				{
					m_bProcCntList = true;
				}
				else if (byteArrCmp(arRecv, m_cmd_cntlist_end))
				{
					m_bProcCntList = false;
					OnEvent(ClubcChatSockEvent.CntList_Update, null);
				}
				else
				{
					if (m_bProcCntList)
					{
						m_CntList.Add(Encoding.UTF8.GetString(arRecv));
					}
					else
					{
						OnReceive(Encoding.UTF8.GetString(arRecv));
					}
				}
			}
			catch (NullReferenceException)
			{
				
			}
		}

		private bool byteArrCmp(byte[] ar1, byte[] ar2)
		{
			return byteArrNCmp(ar1, ar2, ar2.Length);
		}

		private bool byteArrNCmp(byte[] ar1, byte[] ar2, int n)
		{
			int i = 0;
			if (ar1.Length == 0)
			{
				if (ar2.Length == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				while (i < n)
				{
					if (ar1[i] != ar2[i]) return false;
					i++;
				}
				return true;
			}
		}

		private byte[] subByteArr(byte[] ar, int off)
		{
			return subByteArr(ar, off, ar.Length - off);
		}
		private byte[] subByteArr(byte[] ar, int off, int n)
		{
			byte[] result = new byte[n];
			Array.Copy(ar, off, result, 0, n);
			return result;
		}
	}
}
