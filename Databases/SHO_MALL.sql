USE [master]
GO
/****** Object:  Database [SHO_Mall]    Script Date: 01/05/2019 00:55:39 ******/
CREATE DATABASE [SHO_Mall] ON  PRIMARY 
( NAME = N'SHO_Mall', FILENAME = N'D:\Program Files\Microsoft SQL Server\MSSQL10_50.MSSQL\MSSQL\DATA\SHO_Mall.mdf' , SIZE = 3072KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'SHO_Mall_log', FILENAME = N'D:\Program Files\Microsoft SQL Server\MSSQL10_50.MSSQL\MSSQL\DATA\SHO_Mall_log.ldf' , SIZE = 1024KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [SHO_Mall].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [SHO_Mall] SET ANSI_NULL_DEFAULT OFF
GO
ALTER DATABASE [SHO_Mall] SET ANSI_NULLS OFF
GO
ALTER DATABASE [SHO_Mall] SET ANSI_PADDING OFF
GO
ALTER DATABASE [SHO_Mall] SET ANSI_WARNINGS OFF
GO
ALTER DATABASE [SHO_Mall] SET ARITHABORT OFF
GO
ALTER DATABASE [SHO_Mall] SET AUTO_CLOSE OFF
GO
ALTER DATABASE [SHO_Mall] SET AUTO_CREATE_STATISTICS ON
GO
ALTER DATABASE [SHO_Mall] SET AUTO_SHRINK OFF
GO
ALTER DATABASE [SHO_Mall] SET AUTO_UPDATE_STATISTICS ON
GO
ALTER DATABASE [SHO_Mall] SET CURSOR_CLOSE_ON_COMMIT OFF
GO
ALTER DATABASE [SHO_Mall] SET CURSOR_DEFAULT  GLOBAL
GO
ALTER DATABASE [SHO_Mall] SET CONCAT_NULL_YIELDS_NULL OFF
GO
ALTER DATABASE [SHO_Mall] SET NUMERIC_ROUNDABORT OFF
GO
ALTER DATABASE [SHO_Mall] SET QUOTED_IDENTIFIER OFF
GO
ALTER DATABASE [SHO_Mall] SET RECURSIVE_TRIGGERS OFF
GO
ALTER DATABASE [SHO_Mall] SET  DISABLE_BROKER
GO
ALTER DATABASE [SHO_Mall] SET AUTO_UPDATE_STATISTICS_ASYNC OFF
GO
ALTER DATABASE [SHO_Mall] SET DATE_CORRELATION_OPTIMIZATION OFF
GO
ALTER DATABASE [SHO_Mall] SET TRUSTWORTHY OFF
GO
ALTER DATABASE [SHO_Mall] SET ALLOW_SNAPSHOT_ISOLATION OFF
GO
ALTER DATABASE [SHO_Mall] SET PARAMETERIZATION SIMPLE
GO
ALTER DATABASE [SHO_Mall] SET READ_COMMITTED_SNAPSHOT OFF
GO
ALTER DATABASE [SHO_Mall] SET  READ_WRITE
GO
ALTER DATABASE [SHO_Mall] SET RECOVERY SIMPLE
GO
ALTER DATABASE [SHO_Mall] SET  MULTI_USER
GO
ALTER DATABASE [SHO_Mall] SET PAGE_VERIFY CHECKSUM
GO
ALTER DATABASE [SHO_Mall] SET DB_CHAINING OFF
GO
USE [SHO_Mall]
GO
/****** Object:  Table [dbo].[ItemStorageHistory_T]    Script Date: 01/05/2019 00:55:39 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ItemStorageHistory_T](
	[intSeq] [bigint] IDENTITY(1,1) NOT NULL,
	[UserID] [varchar](20) NOT NULL,
	[CharName] [varchar](30) NOT NULL,
	[UserIP] [varchar](20) NOT NULL,
	[ServerIP] [varchar](50) NOT NULL,
	[Mallidx] [bigint] NOT NULL,
	[ItemType] [int] NOT NULL,
	[ItemNo] [int] NOT NULL,
	[ItemCount] [int] NOT NULL,
	[regdate] [datetime] NOT NULL,
	[RecvUserID] [varchar](20) NULL,
	[RecvCharName] [varchar](30) NULL,
	[btLogType] [tinyint] NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[tblCART]    Script Date: 01/05/2019 00:55:39 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[tblCART](
	[intID] [bigint] IDENTITY(1,1) NOT NULL,
	[dateREG] [datetime] NULL,
	[txtACCOUNT] [nvarchar](35) NOT NULL,
	[nItemTYPE] [smallint] NOT NULL,
	[nItemNO] [smallint] NOT NULL,
	[nDupCNT] [smallint] NOT NULL,
	[txtFromACC] [nvarchar](35) NULL,
	[txtFromCHAR] [nvarchar](30) NULL,
	[txtToCHAR] [nvarchar](30) NULL,
	[txtDESC] [nvarchar](80) NULL,
	[txtFromIP] [nvarchar](20) NULL,
	[nTime] [int] NULL,
	[nTime2] [int] NULL
) ON [PRIMARY]
GO
/****** Object:  StoredProcedure [dbo].[PickOutITEM]    Script Date: 01/05/2019 00:55:40 ******/
SET ANSI_NULLS OFF
GO
SET QUOTED_IDENTIFIER OFF
GO
CREATE PROCEDURE [dbo].[PickOutITEM]
	@szAccount	nvarchar(30),
	@szCharName	nvarchar(30),
	@szUserIP	nvarchar(20),
	@szServerIP	nvarchar(20),
	@biSqlID	bigint,
	@nPickOutCnt	smallint 
AS
	DECLARE @nItemType int, @nItemNo int, @nDupCnt  int, @nRemainCount int, @ntime int

	SELECT  @nItemType=nItemTYPE, @nItemNo=nItemNO, @nDupCnt=nDupCNT, @ntime=nTime from tblCART where intID = @biSqlID and txtAccount = @szAccount;
	IF @@ROWCOUNT <= 0
		RETURN 0;

	BEGIN TRAN

	IF @nDupCnt > @nPickOutCnt
	BEGIN
		-- 기존 레코드의 nDupCnt를 @nPickOutCnt만큼... 감소
		set @nRemainCount = @nDupCnt - @nPickOutCnt;
		update tblCART set nDupCNT=@nRemainCount where intID = @biSqlID and txtAccount = @szAccount;
		IF @@ERROR = 0
		BEGIN
			COMMIT TRAN
			-- 아이템 꺼내간 로그 남길곳....
			INSERT ItemStorageHistory_T ( UserID,CharName,UserIP,ServerIP,Mallidx,ItemType,ItemNo,ItemCount ) VALUES ( @szAccount,@szCharName,@szUserIP,@szServerIP,@biSqlID, @nItemType,@nItemNo,@nPickOutCnt );

			SELECT @nItemType, @nItemNo, @nPickOutCnt, @nRemainCount, @ntime;
			RETURN 1;
		END
	END
	ELSE
	BEGIN
		DELETE from tblCART where intID = @biSqlID and txtAccount = @szAccount;
		IF @@ERROR = 0
		BEGIN
			COMMIT TRAN
			-- 아이템 꺼내간 로그 남길곳....
			INSERT ItemStorageHistory_T ( UserID,CharName,UserIP,ServerIP,Mallidx,ItemType,ItemNo,ItemCount ) VALUES ( @szAccount,@szCharName,@szUserIP,@szServerIP,@biSqlID, @nItemType,@nItemNo,@nDupCnt );

			SELECT @nItemType, @nItemNo, @nDupCnt, 0, @ntime;
			RETURN 1;
		END
	END

	ROLLBACK TRAN
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[NewPickOutITEM]    Script Date: 01/05/2019 00:55:40 ******/
SET ANSI_NULLS OFF
GO
SET QUOTED_IDENTIFIER OFF
GO
CREATE PROCEDURE [dbo].[NewPickOutITEM]
	@szAccount	nvarchar(30),
	@szCharName	nvarchar(30),
	@szUserIP	nvarchar(20),
	@szServerIP	nvarchar(20),
	@biSqlID	bigint,
	@nPickOutCnt	smallint 
AS
	DECLARE @nItemType int, @nItemNo int, @nDupCnt  int, @nRemainCount int

	SELECT  @nItemType=nItemTYPE, @nItemNo=nItemNO, @nDupCnt=nDupCNT from tblCART where intID = @biSqlID and txtAccount = @szAccount;
	IF @@ROWCOUNT <= 0
		RETURN 0;

	BEGIN TRAN

	DELETE from tblCART where intID = @biSqlID and txtAccount = @szAccount;
	IF @@ERROR = 0
		BEGIN
		COMMIT TRAN
		-- 아이템 꺼내간 로그 남길곳....
		INSERT ItemStorageHistory_T ( UserID,CharName,UserIP,ServerIP,Mallidx,ItemType,ItemNo,ItemCount ) VALUES ( @szAccount,@szCharName,@szUserIP,@szServerIP,@biSqlID, @nItemType,@nItemNo,@nDupCnt );
		SELECT @nItemType, @nItemNo, @nDupCnt, 0;
		RETURN 1;
		END
	

	ROLLBACK TRAN
	RETURN 0;
GO
/****** Object:  StoredProcedure [dbo].[GiveITEM]    Script Date: 01/05/2019 00:55:40 ******/
SET ANSI_NULLS OFF
GO
SET QUOTED_IDENTIFIER ON
GO
-- 리턴값은 남은 아이템 갯수...
CREATE PROCEDURE [dbo].[GiveITEM]  
	@biItemID		bigint,
	@szFromAccount	nvarchar(30),
	@szFromChar		nvarchar(30),
	@szToAccount		nvarchar(30),
	@szToChar		nvarchar(30),
	@szDesc		nvarchar(80),
	@szUserIP		nvarchar(20),
	@szServerIP		nvarchar(20),
	@nGiveCnt		smallint
AS
	DECLARE @nItemType int, @nItemNo int, @nDupCnt  int

	SELECT  @nItemType=nItemTYPE, @nItemNo=nItemNO, @nDupCnt=nDupCNT from tblCART where intID = @biItemID and txtAccount = @szFromAccount;
	IF @@ROWCOUNT <= 0
		RETURN -1;

	-- 분할 전달이 안될경우...
	IF @nDupCnt <= @nGiveCnt
	BEGIN
		-- 레코드 통채로 변경
		BEGIN TRAN
		UPDATE tblCART SET 	txtACCOUNT=@szToAccount,
				            	txtFromACC=@szFromAccount,
					txtFromCHAR=@szFromChar,
					txtToCHAR=@szToChar,
					txtDesc=@szDesc,
					txtFromIP=@szServerIP
					WHERE intID=@biItemID and txtACCOUNT=@szFromAccount
		IF @@ERROR <> 0
		BEGIN
			ROLLBACK TRAN
			RETURN -1;
		END
	
		COMMIT TRAN
	
		-- 선물한 로그...
		INSERT ItemStorageHistory_T ( UserID,CharName,UserIP,ServerIP,Mallidx,ItemType,ItemNo,ItemCount,RecvUserID,RecvCharName,btLogType ) 
			VALUES ( @szFromAccount,@szFromChar,@szUserIP,@szServerIP,@biItemID, @nItemType,@nItemNo,@nDupCnt, @szToAccount,@szToChar,1 );
	
		RETURN 0;
	END


	BEGIN TRAN
	-- 아이템 @nGiveCn개짜리 추가...
	INSERT tblCART ( txtACCOUNT,nItemTYPE,nItemNO,nDupCNT,txtFromACC,txtFromCHAR,txtToCHAR,txtDesc,txtFromIP) VALUES
		 ( @szToAccount, @nItemType, @nItemNo, @nGiveCnt, @szFromAccount, @szFromChar, @szToChar, @szDesc, @szServerIP );
	IF @@ERROR <> 0
	BEGIN
		ROLLBACK TRAN
		RETURN -1;
	END

	-- 기존꺼에서 갯수 감소.	
	UPDATE tblCART SET	nDupCNT=@nDupCnt-@nGiveCnt WHERE intID=@biItemID and txtACCOUNT=@szFromAccount
	IF @@ERROR <> 0
	BEGIN
		ROLLBACK TRAN
		RETURN -1;
	END

	COMMIT TRAN

	-- 선물한 로그...
	INSERT ItemStorageHistory_T ( UserID,CharName,UserIP,ServerIP,Mallidx,ItemType,ItemNo,ItemCount,RecvUserID,RecvCharName,btLogType ) 
		VALUES ( @szFromAccount,@szFromChar,@szUserIP,@szServerIP,@biItemID, @nItemType,@nItemNo,@nGiveCnt, @szToAccount,@szToChar,1 );

	RETURN @nDupCnt-@nGiveCnt;
GO
/****** Object:  StoredProcedure [dbo].[GetItemLIST]    Script Date: 01/05/2019 00:55:40 ******/
SET ANSI_NULLS OFF
GO
SET QUOTED_IDENTIFIER OFF
GO
CREATE PROCEDURE [dbo].[GetItemLIST]
	@szAccount	nvarchar(30),
	@biStartID	bigint
AS
	SELECT top 48 intID, nItemTYPE,nItemNO,nDupCNT,txtFromCHAR,txtToCHAR,txtDESC,txtFromIP, nTime  from tblCART where txtACCOUNT = @szAccount and intID > @biStartID
GO
/****** Object:  Default [DF_tblCART_nTime]    Script Date: 01/05/2019 00:55:39 ******/
ALTER TABLE [dbo].[tblCART] ADD  CONSTRAINT [DF_tblCART_nTime]  DEFAULT ((0)) FOR [nTime]
GO
