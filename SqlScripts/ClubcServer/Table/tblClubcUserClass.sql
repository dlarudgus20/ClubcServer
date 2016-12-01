USE ClubcDb

--DROP TABLE tblClubcUserClass
GO

CREATE TABLE tblClubcUserClass
(
	Class int NOT NULL PRIMARY KEY,
	Descript nvarchar(50) NOT NULL UNIQUE,
)
