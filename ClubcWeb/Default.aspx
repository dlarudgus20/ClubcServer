<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="ClubcWeb.Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
	<head runat="server">
		<title>ClubcWeb HomePage</title>
		<link rel="stylesheet" type="text/css" href="Styles/Style.css" />
	</head>
	<body>
		<form id="form1" runat="server">
			<div>
				<center><h3>ClubcWeb HomePage</h3></center>

				<asp:Panel ID="LoginPanel" runat="server">
					<asp:Login ID="LoginBox" runat="server" BackColor="#F7F7DE" BorderColor="#CCCC99" 
							BorderStyle="Solid" BorderWidth="1px" Font-Names="Verdana" Font-Size="10pt" 
						onauthenticate="LoginBox_Authenticate" DisplayRememberMe="False">
						<TitleTextStyle BackColor="#6B696B" Font-Bold="True" ForeColor="#FFFFFF" />
					</asp:Login>
				</asp:Panel>

				<asp:Panel ID="MainPanel" runat="server">
					<h3><b>환영합니다, <asp:Label ID="NickLabel" runat="Server" /> 님!</b></h3><br />
					<p>
						<asp:Button ID="GoChatBtn" runat="server" Text="채팅방 가기" 
							onclick="GoChatBtn_Click" />
					</p>
					<p>
						<asp:Button ID="LogoutBtn" runat="server" Text="로그아웃" onclick="LogoutBtn_Click" 
							PostBackUrl="~/Default.aspx" />
					</p>
				</asp:Panel>
			</div>
		</form>
	</body>
</html>
