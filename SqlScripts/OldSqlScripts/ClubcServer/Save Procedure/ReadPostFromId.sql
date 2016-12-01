USE ClubcDb

DROP PROC ReadPostFromId
GO

CREATE PROC ReadPostFromId
	@User NVARCHAR(50),
	@Passwd NVARCHAR(50),
	@PostId INT
AS
	IF (SELECT ID FROM tblClubcUsers
			WHERE ID = @User AND Pass = @Passwd) IS NOT NULL
	BEGIN
		DECLARE @User_Class int
		DECLARE @Post_Class int

		SELECT @User_Class = Class FROM tblClubcUserClass
			WHERE Descript = (SELECT Class FROM tblClubcUsers
				WHERE ID = @User AND Pass = @Passwd)

		SELECT @Post_Class = Class FROM tblClubcUserClass
			WHERE Descript = (SELECT PostLevel FROM tblClubcPost
				WHERE PostId = @PostId)

		IF @User_Class <= @Post_Class
		BEGIN
			SELECT * FROM tblClubcPost WHERE PostId = @PostId
		END
	END
