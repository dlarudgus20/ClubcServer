<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="WebClubcChat2.aspx.cs" Inherits="ClubcWeb.WebClubcChat2" %>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>WebClubcChat2 1.0</title>
	<link rel="stylesheet" type="text/css" href="Styles/Style.css" />
</head>
<body>
	<form id="form1" runat="server">
	<div>
		<asp:ScriptManager ID="ScriptManager1" runat="server">
		</asp:ScriptManager>

		<h4>로그아웃을 하거나 세션이 만료될 때까지 채팅방 로그인이 유지됩니다.</h4>
		<asp:UpdatePanel ID="UpdatePanel1" runat="server">
			<ContentTemplate>
				<asp:ListBox ID="ChatList" runat="server" Height="90%" Width="80%">
				</asp:ListBox>
				<asp:ListBox ID="CntList" runat="server" Height="90%" Width="19%">
				</asp:ListBox>
				<asp:Timer ID="Timer1" runat="server" OnTick="Timer1_Tick" Interval="375">
				</asp:Timer>
			</ContentTemplate>
		</asp:UpdatePanel>

		<br />
		<asp:TextBox ID="ChatBox" runat="server" Width="100%" 
			ontextchanged="ChatBox_TextChanged" TextMode="MultiLine"></asp:TextBox>
	</div>
	</form>
</body>
</html>
