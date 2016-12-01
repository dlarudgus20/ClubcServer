namespace dnClubcChat2
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
			this.lstChat = new System.Windows.Forms.ListBox();
			this.tbChat = new System.Windows.Forms.TextBox();
			this.lstCntList = new System.Windows.Forms.ListBox();
			this.SuspendLayout();
			// 
			// lstChat
			// 
			this.lstChat.HorizontalExtent = 4000;
			this.lstChat.HorizontalScrollbar = true;
			this.lstChat.ItemHeight = 12;
			this.lstChat.Location = new System.Drawing.Point(0, 0);
			this.lstChat.Name = "lstChat";
			this.lstChat.Size = new System.Drawing.Size(664, 316);
			this.lstChat.TabIndex = 0;
			// 
			// tbChat
			// 
			this.tbChat.Enabled = false;
			this.tbChat.Location = new System.Drawing.Point(0, 326);
			this.tbChat.Name = "tbChat";
			this.tbChat.Size = new System.Drawing.Size(751, 21);
			this.tbChat.TabIndex = 2;
			this.tbChat.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbChat_KeyPress);
			// 
			// lstCntList
			// 
			this.lstCntList.FormattingEnabled = true;
			this.lstCntList.ItemHeight = 12;
			this.lstCntList.Location = new System.Drawing.Point(670, 0);
			this.lstCntList.Name = "lstCntList";
			this.lstCntList.Size = new System.Drawing.Size(81, 316);
			this.lstCntList.TabIndex = 1;
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(750, 347);
			this.Controls.Add(this.lstCntList);
			this.Controls.Add(this.tbChat);
			this.Controls.Add(this.lstChat);
			this.Name = "Form1";
			this.Text = "dnClubcChat2";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosed);
			this.Load += new System.EventHandler(this.Form1_Load);
			this.Layout += new System.Windows.Forms.LayoutEventHandler(this.Form1_Layout);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ListBox lstChat;
		private System.Windows.Forms.TextBox tbChat;
		private System.Windows.Forms.ListBox lstCntList;
	}
}

