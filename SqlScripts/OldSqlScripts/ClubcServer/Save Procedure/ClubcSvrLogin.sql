USE ClubcDb

CREATE PROC ClubcSvrLogin
	@UserName NVARCHAR(50),
	@Passwd NVARCHAR(50)
AS
	select * from tblClubcUsers where ID = @UserName AND Pass = @Passwd
