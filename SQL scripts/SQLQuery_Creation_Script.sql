--detele tables

USE [SDI_Db]
GO

DROP TABLE [dbo].[Country]
GO

DROP TABLE [dbo].[Category]
GO


--create tables

USE [SDI_Db]
GO

CREATE TABLE Category (
	Id int NOT NULL IDENTITY(1,1) PRIMARY KEY,
	Description nvarchar(255)
)

CREATE TABLE Country (
	Id int NOT NULL IDENTITY(1,1) PRIMARY KEY,
	Country nvarchar(255),
	City nvarchar(255),
	Currency nvarchar(255),
	CategoryId int NOT NULL,
	CONSTRAINT FK_Category FOREIGN KEY (CategoryId) REFERENCES Category(Id)
)

INSERT INTO Category
VALUES('ok'),
('maybe'),
('I don''t know'),
('not ok')

INSERT INTO Country
VALUES ('France', 'Paris', 'euro', '1'), 
('Hungary', 'Budapest', 'forint', '3'), 
('Georgia', 'Tbilisi', 'lari', '2'),
('Romania', 'Bucharest', 'leu', '3'),
('Rusia', 'Moscow', 'ruble', '3'),
('Turkey', 'Istanbul', 'lira', '4'),
('Zair', 'Kinshasa', 'zaire', '4')