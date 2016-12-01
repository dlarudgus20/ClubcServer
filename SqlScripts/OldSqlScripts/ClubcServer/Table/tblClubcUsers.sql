USE ClubcDb

DROP TABLE tblClubcUsers
GO

CREATE TABLE tblClubcUsers
(
	ID nvarchar(50) NOT NULL PRIMARY KEY,
	Pass nvarchar(50) NOT NULL,
	Class nvarchar(50) NOT NULL REFERENCES tblClubcUserClass(Descript),
	Nickname nvarchar(50) NOT NULL UNIQUE
)
