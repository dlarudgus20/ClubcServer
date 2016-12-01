CREATE DATABASE ClubcDb
GO

USE ClubcDb

CREATE TABLE tblClubcUserClass
(
	Class int NOT NULL PRIMARY KEY,
	Descript nvarchar(50) NOT NULL UNIQUE,
)
GO

CREATE TABLE tblClubcUsers
(
	ID nvarchar(50) NOT NULL PRIMARY KEY,
	Pass nvarchar(50) NOT NULL,
	Class nvarchar(50) NOT NULL REFERENCES tblClubcUserClass(Descript),
	Nickname nvarchar(50) NOT NULL UNIQUE DEFAULT '¼Õ´Ô'
)
GO

CREATE TABLE tblClubcPost
(
	PostID INT IDENTITY(1, 1) NOT NULL PRIMARY KEY,
	Writer NVARCHAR(50) NOT NULL,
	PostLevel NVARCHAR(50) NOT NULL REFERENCES tblClubcUserClass(Descript),
	PostTitle NVARCHAR(50) NOT NULL UNIQUE,
	Writing NVARCHAR(MAX) NOT NULL
);
GO

CREATE TABLE tblClubcWaring
(
	Name NVARCHAR(50) NOT NULL PRIMARY KEY,
	Waring_LV1 INT NOT NULL CHECK(Waring_LV1 >= 0) DEFAULT 0,
	Waring_LV2 INT NOT NULL CHECK(Waring_LV2 <= 3 AND Waring_LV2 >= 0) DEFAULT 0
)
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
GO

CREATE PROC ReadPostFromTitle
	@User NVARCHAR(50),
	@Passwd NVARCHAR(50),
	@PostTitle NVARCHAR(50)
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
				WHERE PostTitle = @PostTitle)

		IF @User_Class <= @Post_Class
		BEGIN
			SELECT * FROM tblClubcPost WHERE PostTitle = @PostTitle
		END
	END
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
GO

CREATE PROC QueryPostTitle
	@PostId INT
AS
	SELECT PostTitle FROM tblClubcPost WHERE PostId = @PostId
GO

CREATE PROC QueryPostId
	@PostTitle NVARCHAR(50)
AS
	SELECT PostId FROM tblClubcPost WHERE PostTitle = @PostTitle
GO

CREATE PROC CreateClubcUser
	@User NVARCHAR(50),
	@Passwd NVARCHAR(50),
	@Class NVARCHAR(50),
	@Nickname NVARCHAR(50)
AS
	INSERT INTO tblClubcUsers VALUES ( @User, @Passwd, @Class, @Nickname )
GO

CREATE PROC ClubcSvrLogin
	@UserName NVARCHAR(50),
	@Passwd NVARCHAR(50)
AS
	select * from tblClubcUsers where ID = @UserName AND Pass = @Passwd

