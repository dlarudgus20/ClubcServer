using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ClubcSvrLib_Server;

namespace CreateClubcUser
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			List<string> ClassStrList = ClubcUser.GetClassStrList();

			if (ClassStrList != null)
			{
				cbxUserClass.DataSource = ClassStrList;
			}
			else
			{
				MessageBox.Show("SQL 명령 실행에 실패했습니다.", "에러", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}

		private void btnCreateUser_Click(object sender, EventArgs e)
		{
			ClubcUser user = ClubcUser.CreateUser(tbUserId.Text, tbUserPass.Text, cbxUserClass.Text, tbNickname.Text);

			if (user != null)
			{
				MessageBox.Show(string.Format("아이디 : {0}\n비밀번호 : {1}\n등급 : {2}", user.UserName, user.Password, user.UserClassStr),
					"성공", MessageBoxButtons.OK, MessageBoxIcon.Information);
			}
			else
			{
				MessageBox.Show("계생 생성에 실패했습니다.", "에러", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
	}
}
