namespace dnClubcChat2
{
	partial class LoginDialog
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LoginDialog));
			this.label1 = new System.Windows.Forms.Label();
			this.tbPass = new System.Windows.Forms.TextBox();
			this.tbId = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.btnLogin = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.label3 = new System.Windows.Forms.Label();
			this.ipcSrvIP = new IPAddressControl.IPAddressControl();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(12, 15);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(65, 12);
			this.label1.TabIndex = 0;
			this.label1.Text = "아이디    : ";
			// 
			// tbPass
			// 
			this.tbPass.Location = new System.Drawing.Point(83, 39);
			this.tbPass.Name = "tbPass";
			this.tbPass.Size = new System.Drawing.Size(148, 21);
			this.tbPass.TabIndex = 3;
			// 
			// tbId
			// 
			this.tbId.Location = new System.Drawing.Point(83, 12);
			this.tbId.Name = "tbId";
			this.tbId.Size = new System.Drawing.Size(148, 21);
			this.tbId.TabIndex = 1;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(12, 42);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(65, 12);
			this.label2.TabIndex = 2;
			this.label2.Text = "비밀번호 : ";
			// 
			// btnLogin
			// 
			this.btnLogin.Location = new System.Drawing.Point(45, 100);
			this.btnLogin.Name = "btnLogin";
			this.btnLogin.Size = new System.Drawing.Size(75, 23);
			this.btnLogin.TabIndex = 6;
			this.btnLogin.Text = "로그인";
			this.btnLogin.UseVisualStyleBackColor = true;
			this.btnLogin.Click += new System.EventHandler(this.btnLogin_Click);
			// 
			// btnCancel
			// 
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.Location = new System.Drawing.Point(126, 100);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(75, 23);
			this.btnCancel.TabIndex = 7;
			this.btnCancel.Text = "취소";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(12, 72);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(60, 12);
			this.label3.TabIndex = 4;
			this.label3.Text = "서버 IP   :";
			// 
			// ipcSrvIP
			// 
			this.ipcSrvIP.Location = new System.Drawing.Point(81, 66);
			this.ipcSrvIP.MaximumSize = new System.Drawing.Size(150, 24);
			this.ipcSrvIP.MinimumSize = new System.Drawing.Size(150, 24);
			this.ipcSrvIP.Name = "ipcSrvIP";
			this.ipcSrvIP.Size = new System.Drawing.Size(150, 24);
			this.ipcSrvIP.TabIndex = 5;
			this.ipcSrvIP.Value = ((System.Net.IPAddress)(resources.GetObject("ipcSrvIP.Value")));
			// 
			// LoginDialog
			// 
			this.AcceptButton = this.btnLogin;
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.btnCancel;
			this.ClientSize = new System.Drawing.Size(247, 138);
			this.Controls.Add(this.ipcSrvIP);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.btnLogin);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.tbId);
			this.Controls.Add(this.tbPass);
			this.Controls.Add(this.label1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "LoginDialog";
			this.Text = "LoginDialog";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox tbPass;
		private System.Windows.Forms.TextBox tbId;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Button btnLogin;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Label label3;
		private IPAddressControl.IPAddressControl ipcSrvIP;
	}
}