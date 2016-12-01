USE ClubcDb

DROP PROC QueryPostTitle
GO

CREATE PROC QueryPostTitle
	@PostId INT
AS
	SELECT PostTitle FROM tblClubcPost WHERE PostId = @PostId
