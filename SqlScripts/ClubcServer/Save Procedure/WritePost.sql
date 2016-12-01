USE ClubcDb

--DROP PROC WritePost
GO

CREATE PROC WritePost
	@Writer NVARCHAR(50),
	@Passwd NVARCHAR(50),
	@PostLevel NVARCHAR(50),
	@PostTitle NVARCHAR(50),
	@Writing NVARCHAR(MAX)
AS	
	IF (SELECT ID FROM ClubcDb.dbo.tblClubcUsers
		WHERE ID = @Writer AND Pass = @Passwd) IS NOT NULL
	BEGIN
		INSERT INTO ClubcDb.dbo.tblClubcPost
			(Writer, PostLevel, PostTitle, Writing)
			VALUES (@Writer, @PostLevel, @PostTitle, @Writing);
	END
