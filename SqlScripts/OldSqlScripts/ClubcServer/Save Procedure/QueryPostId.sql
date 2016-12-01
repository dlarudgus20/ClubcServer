USE ClubcDb

DROP PROC QueryPostId
GO

CREATE PROC QueryPostId
	@PostTitle NVARCHAR(50)
AS
	SELECT PostId FROM tblClubcPost WHERE PostTitle = @PostTitle
