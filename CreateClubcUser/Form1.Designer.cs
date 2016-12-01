namespace CreateClubcUser
{
	partial class Form1
	{
		/// <summary>
		/// 필수 디자이너 변수입니다.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		/// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form 디자이너에서 생성한 코드

		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다.
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
		/// </summary>
		private void InitializeComponent()
		{
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.tbUserPass = new System.Windows.Forms.TextBox();
			this.tbUserId = new System.Windows.Forms.TextBox();
			this.cbxUserClass = new System.Windows.Forms.ComboBox();
			this.btnCreateUser = new System.Windows.Forms.Button();
			this.tbNickname = new System.Windows.Forms.TextBox();
			this.label4 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(27, 23);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(65, 12);
			this.label1.TabIndex = 0;
			this.label1.Text = "아이디    : ";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(27, 51);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(61, 12);
			this.label2.TabIndex = 2;
			this.label2.Text = "비밀번호 :";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(27, 79);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(65, 12);
			this.label3.TabIndex = 4;
			this.label3.Text = "등급       : ";
			// 
			// tbUserPass
			// 
			this.tbUserPass.Location = new System.Drawing.Point(94, 48);
			this.tbUserPass.Name = "tbUserPass";
			this.tbUserPass.Size = new System.Drawing.Size(121, 21);
			this.tbUserPass.TabIndex = 3;
			// 
			// tbUserId
			// 
			this.tbUserId.Location = new System.Drawing.Point(94, 20);
			this.tbUserId.Name = "tbUserId";
			this.tbUserId.Size = new System.Drawing.Size(121, 21);
			this.tbUserId.TabIndex = 1;
			// 
			// cbxUserClass
			// 
			this.cbxUserClass.FormattingEnabled = true;
			this.cbxUserClass.Location = new System.Drawing.Point(94, 76);
			this.cbxUserClass.Name = "cbxUserClass";
			this.cbxUserClass.Size = new System.Drawing.Size(121, 20);
			this.cbxUserClass.TabIndex = 5;
			// 
			// btnCreateUser
			// 
			this.btnCreateUser.Location = new System.Drawing.Point(84, 138);
			this.btnCreateUser.Name = "btnCreateUser";
			this.btnCreateUser.Size = new System.Drawing.Size(75, 23);
			this.btnCreateUser.TabIndex = 8;
			this.btnCreateUser.Text = "만들기";
			this.btnCreateUser.UseVisualStyleBackColor = true;
			this.btnCreateUser.Click += new System.EventHandler(this.btnCreateUser_Click);
			// 
			// tbNickname
			// 
			this.tbNickname.Location = new System.Drawing.Point(94, 103);
			this.tbNickname.Name = "tbNickname";
			this.tbNickname.Size = new System.Drawing.Size(121, 21);
			this.tbNickname.TabIndex = 7;
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(27, 107);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(65, 12);
			this.label4.TabIndex = 6;
			this.label4.Text = "별명       : ";
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(243, 180);
			this.Controls.Add(this.tbNickname);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.btnCreateUser);
			this.Controls.Add(this.cbxUserClass);
			this.Controls.Add(this.tbUserId);
			this.Controls.Add(this.tbUserPass);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.Name = "Form1";
			this.Text = "ClubcServer 회원가입";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox tbUserPass;
		private System.Windows.Forms.TextBox tbUserId;
		private System.Windows.Forms.ComboBox cbxUserClass;
		private System.Windows.Forms.Button btnCreateUser;
		private System.Windows.Forms.TextBox tbNickname;
		private System.Windows.Forms.Label label4;
	}
}

