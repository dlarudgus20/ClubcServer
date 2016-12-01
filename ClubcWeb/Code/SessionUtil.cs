using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;

namespace ClubcWeb
{
	public static class SessionUtil
	{
		public static T ReadSession<T>(this Page p, string idx, T def)
		{
			try
			{
				return (T)p.Session[idx];
			}
			catch (InvalidCastException)
			{
				return def;
			}
		}
		public static T ReadSession<T>(this Page p, string idx) where T:class
		{
			try
			{
				return (T)p.Session[idx];
			}
			catch (InvalidCastException)
			{
				return null;
			}
		}
	}
}