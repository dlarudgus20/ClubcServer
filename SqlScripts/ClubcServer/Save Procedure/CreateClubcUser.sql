USE ClubcDb

--DROP PROC CreateClubcUser
GO

CREATE PROC CreateClubcUser
	@User NVARCHAR(50),
	@Passwd NVARCHAR(50),
	@Class NVARCHAR(50),
	@Nickname NVARCHAR(50)
AS
	INSERT INTO tblClubcUsers VALUES ( @User, @Passwd, @Class, @Nickname )
