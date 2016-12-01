using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace dnClubcChat2
{
	public partial class LoginDialog : Form
	{
		public string Id { get; private set; }
		public string Password { get; private set; }
		public string SrvIp { get; private set; }

		public LoginDialog()
		{
			InitializeComponent();
			ipcSrvIP.Value = System.Net.IPAddress.Parse("14.46.56.226");
		}

		private void btnLogin_Click(object sender, EventArgs e)
		{
			Id = tbId.Text;
			Password = tbPass.Text;
			SrvIp = ipcSrvIP.Value.ToString();
			DialogResult = DialogResult.OK;
		}

		private void btnCancel_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.Cancel;
		}
	}
}
