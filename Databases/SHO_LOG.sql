if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[CHECK_MAINCALL_IP]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[CHECK_MAINCALL_IP]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_AddUnsigned]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_AddUnsigned]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_ConvertToWordArray]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_ConvertToWordArray]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_F]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_F]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_FF]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_FF]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_G]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_G]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_GG]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_GG]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_H]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_H]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_HH]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_HH]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_I]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_I]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_II]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_II]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_LShift]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_LShift]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_RShift]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_RShift]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_RotateLeft]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_RotateLeft]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_WordToHex]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_WordToHex]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_m_2Power]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_m_2Power]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[MD5_m_OnBits]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[MD5_m_OnBits]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[udf_hex_to_number]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[udf_hex_to_number]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[udf_number_to_hex]') and xtype in (N'FN', N'IF', N'TF'))
drop function [dbo].[udf_number_to_hex]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[AddCharacterLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[AddCharacterLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[AddCheatLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[AddCheatLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[AddClanLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[AddClanLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[AddCreateLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[AddCreateLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[AddDieLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[AddDieLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[AddGemmingLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[AddGemmingLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[AddItemLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[AddItemLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[AddLevelUpLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[AddLevelUpLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[AddLoginLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[AddLoginLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[AddPeriodicCHARLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[AddPeriodicCHARLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[AddQuestLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[AddQuestLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[AddSkillLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[AddSkillLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[AddUpgradeLog]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[AddUpgradeLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[DeleteGS_Log]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[DeleteGS_Log]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[gs_M_DefLOG]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[gs_M_DefLOG]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[gs_M_DescLOG]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[gs_M_DescLOG]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[gs_M_LogInOut]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[gs_M_LogInOut]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[gs_M_ObjDescLOG]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[gs_M_ObjDescLOG]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[gs_M_ObjLOG]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[gs_M_ObjLOG]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[sp_getGameTime]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[sp_getGameTime]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GS_ChangeAbility]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GS_ChangeAbility]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GS_CharacterLog]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GS_CharacterLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GS_CreateLog]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GS_CreateLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GS_DieLog]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GS_DieLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GS_GemmingLog]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GS_GemmingLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GS_ItemLog]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GS_ItemLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GS_LevelUpLog]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GS_LevelUpLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GS_PeriodicCHARLog]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GS_PeriodicCHARLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GS_QuestLog]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GS_QuestLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GS_SkillLog]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GS_SkillLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GS_UnionLog]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GS_UnionLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[GS_UpgradeLog]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[GS_UpgradeLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[UpdatePoint_Log]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[UpdatePoint_Log]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[WS_CheatLog]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[WS_CheatLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[WS_ClanLog]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[WS_ClanLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[WS_LoginLog]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[WS_LoginLog]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[tblGS_ERROR]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[tblGS_ERROR]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[tblGS_LogIN]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[tblGS_LogIN]
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS OFF 
GO



CREATE FUNCTION CHECK_MAINCALL_IP ()  
RETURNS INT AS  
BEGIN
declare @total INT, @u_count int
SELECT   @total = count(user_ip)
from dbo.Player_Login
where isp_id  <> 0 and logout_time = '1900/1/1'
SELECT    @u_count = count(distinct user_ip)
from dbo.Player_Login
where isp_id  <> 0 and logout_time = '1900/1/1'
return @total - @u_count
END



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5 
* Description: MD5 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5( 
     @sOrigMess    NVARCHAR(4000) 
) 
RETURNS CHAR(32) 
-- WITH ENCRYPTION 
AS 
BEGIN 
    --==================================== 
    DECLARE @S11 TINYINT 
    DECLARE @S12 TINYINT 
    DECLARE @S13 TINYINT 
    DECLARE @S14 TINYINT 
    DECLARE @S21 TINYINT 
    DECLARE @S22 TINYINT 
    DECLARE @S23 TINYINT 
    DECLARE @S24 TINYINT 
    DECLARE @S31 TINYINT 
    DECLARE @S32 TINYINT 
    DECLARE @S33 TINYINT 
    DECLARE @S34 TINYINT 
    DECLARE @S41 TINYINT 
    DECLARE @S42 TINYINT 
    DECLARE @S43 TINYINT 
    DECLARE @S44 TINYINT 
    SELECT @S11 = 7, @S12 = 12, @S13 = 17, @S14 = 22 
    SELECT @S21 = 5, @S22 = 9, @S23 = 14, @S24 = 20 
    SELECT @S31 = 4, @S32 = 11, @S33 = 16, @S34 = 23 
    SELECT @S41 = 6, @S42 = 10, @S43 = 15, @S44 = 21 
    --==================================== 
    DECLARE @a INT 
    DECLARE @b INT 
    DECLARE @c INT 
    DECLARE @d INT 
    DECLARE @AA    INT 
    DECLARE @BB    INT 
    DECLARE @CC    INT 
    DECLARE @DD    INT 
    SELECT   @a = 0x67452301 
            ,@b = 0xEFCDAB89 
            ,@c = 0x98BADCFE 
            ,@d = 0x10325476 
    --==================================== 
    DECLARE @sRes    VARCHAR(32) 
    SET @sRes = '' 
    DECLARE @iWordArrayLen        INT 
    DECLARE @iWordArrayCount    INT 
    DECLARE @tTmp TABLE([ID] INT, [Word] INT) 
    INSERT INTO @tTmp SELECT * FROM dbo.MD5_ConvertToWordArray(@sOrigMess) 
    SELECT @iWordArrayCount=0, @iWordArrayLen = COUNT(*) FROM @tTmp 
    WHILE(@iWordArrayCount < @iWordArrayLen) 
    BEGIN 
        SELECT @AA = @a, @BB = @b, @CC = @c, @DD = @d 
        SELECT @a = dbo.MD5_FF(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 0), @S11, 0xD76AA478) 
        SELECT @d = dbo.MD5_FF(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 1), @S12, 0xE8C7B756) 
        SELECT @c = dbo.MD5_FF(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 2), @S13, 0x242070DB) 
        SELECT @b = dbo.MD5_FF(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 3), @S14, 0xC1BDCEEE) 
        SELECT @a = dbo.MD5_FF(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 4), @S11, 0xF57C0FAF) 
        SELECT @d = dbo.MD5_FF(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 5), @S12, 0x4787C62A) 
        SELECT @c = dbo.MD5_FF(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 6), @S13, 0xA8304613) 
        SELECT @b = dbo.MD5_FF(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 7), @S14, 0xFD469501) 
        SELECT @a = dbo.MD5_FF(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 8), @S11, 0x698098D8) 
        SELECT @d = dbo.MD5_FF(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 9), @S12, 0x8B44F7AF) 
        SELECT @c = dbo.MD5_FF(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 10), @S13, 0xFFFF5BB1) 
        SELECT @b = dbo.MD5_FF(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 11), @S14, 0x895CD7BE) 
        SELECT @a = dbo.MD5_FF(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 12), @S11, 0x6B901122) 
        SELECT @d = dbo.MD5_FF(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 13), @S12, 0xFD987193) 
        SELECT @c = dbo.MD5_FF(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 14), @S13, 0xA679438E) 
        SELECT @b = dbo.MD5_FF(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 15), @S14, 0x49B40821) 
        SELECT @a = dbo.MD5_GG(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 1), @S21, 0xF61E2562) 
        SELECT @d = dbo.MD5_GG(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 6), @S22, 0xC040B340) 
        SELECT @c = dbo.MD5_GG(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 11), @S23, 0x265E5A51) 
        SELECT @b = dbo.MD5_GG(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 0), @S24, 0xE9B6C7AA) 
        SELECT @a = dbo.MD5_GG(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 5), @S21, 0xD62F105D) 
        SELECT @d = dbo.MD5_GG(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 10), @S22, 0x2441453) 
        SELECT @c = dbo.MD5_GG(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 15), @S23, 0xD8A1E681) 
        SELECT @b = dbo.MD5_GG(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 4), @S24, 0xE7D3FBC8) 
        SELECT @a = dbo.MD5_GG(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 9), @S21, 0x21E1CDE6) 
        SELECT @d = dbo.MD5_GG(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 14), @S22, 0xC33707D6) 
        SELECT @c = dbo.MD5_GG(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 3), @S23, 0xF4D50D87) 
        SELECT @b = dbo.MD5_GG(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 8), @S24, 0x455A14ED) 
        SELECT @a = dbo.MD5_GG(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 13), @S21, 0xA9E3E905) 
        SELECT @d = dbo.MD5_GG(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 2), @S22, 0xFCEFA3F8) 
        SELECT @c = dbo.MD5_GG(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 7), @S23, 0x676F02D9) 
        SELECT @b = dbo.MD5_GG(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 12), @S24, 0x8D2A4C8A) 
        SELECT @a = dbo.MD5_HH(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 5), @S31, 0xFFFA3942) 
        SELECT @d = dbo.MD5_HH(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 8), @S32, 0x8771F681) 
        SELECT @c = dbo.MD5_HH(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 11), @S33, 0x6D9D6122) 
        SELECT @b = dbo.MD5_HH(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 14), @S34, 0xFDE5380C) 
        SELECT @a = dbo.MD5_HH(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 1), @S31, 0xA4BEEA44) 
        SELECT @d = dbo.MD5_HH(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 4), @S32, 0x4BDECFA9) 
        SELECT @c = dbo.MD5_HH(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 7), @S33, 0xF6BB4B60) 
        SELECT @b = dbo.MD5_HH(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 10), @S34, 0xBEBFBC70) 
        SELECT @a = dbo.MD5_HH(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 13), @S31, 0x289B7EC6) 
        SELECT @d = dbo.MD5_HH(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 0), @S32, 0xEAA127FA) 
        SELECT @c = dbo.MD5_HH(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 3), @S33, 0xD4EF3085) 
        SELECT @b = dbo.MD5_HH(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 6), @S34, 0x4881D05) 
        SELECT @a = dbo.MD5_HH(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 9), @S31, 0xD9D4D039) 
        SELECT @d = dbo.MD5_HH(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 12), @S32, 0xE6DB99E5) 
        SELECT @c = dbo.MD5_HH(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 15), @S33, 0x1FA27CF8) 
        SELECT @b = dbo.MD5_HH(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 2), @S34, 0xC4AC5665) 
        SELECT @a = dbo.MD5_II(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 0), @S41, 0xF4292244) 
        SELECT @d = dbo.MD5_II(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 7), @S42, 0x432AFF97) 
        SELECT @c = dbo.MD5_II(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 14), @S43, 0xAB9423A7) 
        SELECT @b = dbo.MD5_II(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 5), @S44, 0xFC93A039) 
        SELECT @a = dbo.MD5_II(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 12), @S41, 0x655B59C3) 
        SELECT @d = dbo.MD5_II(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 3), @S42, 0x8F0CCC92) 
        SELECT @c = dbo.MD5_II(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 10), @S43, 0xFFEFF47D) 
        SELECT @b = dbo.MD5_II(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 1), @S44, 0x85845DD1) 
        SELECT @a = dbo.MD5_II(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 8), @S41, 0x6FA87E4F) 
        SELECT @d = dbo.MD5_II(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 15), @S42, 0xFE2CE6E0) 
        SELECT @c = dbo.MD5_II(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 6), @S43, 0xA3014314) 
        SELECT @b = dbo.MD5_II(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 13), @S44, 0x4E0811A1) 
        SELECT @a = dbo.MD5_II(@a, @b, @c, @d, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 4), @S41, 0xF7537E82) 
        SELECT @d = dbo.MD5_II(@d, @a, @b, @c, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 11), @S42, 0xBD3AF235) 
        SELECT @c = dbo.MD5_II(@c, @d, @a, @b, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 2), @S43, 0x2AD7D2BB) 
        SELECT @b = dbo.MD5_II(@b, @c, @d, @a, (SELECT [Word] FROM @tTmp WHERE [ID] = @iWordArrayCount + 9), @S44, 0xEB86D391) 
        SET @a = dbo.MD5_AddUnsigned(@a, @AA) 
        SET @b = dbo.MD5_AddUnsigned(@b, @BB) 
        SET @c = dbo.MD5_AddUnsigned(@c, @CC) 
        SET @d = dbo.MD5_AddUnsigned(@d, @DD) 
        SET @iWordArrayCount = @iWordArrayCount + 16 
    END 
    SET @sRes = dbo.MD5_WordToHex(@a) + dbo.MD5_WordToHex(@b) + dbo.MD5_WordToHex(@c) + dbo.MD5_WordToHex(@d) 
    SET @sRes = LOWER(@sRes) 
    RETURN(@sRes) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_AddUnsigned 
* Description: MD5_AddUnsigned 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_AddUnsigned( 
     @iX        INT 
    ,@iY        INT 
) 
RETURNS INT 
-- WITH ENCRYPTION 
AS 
BEGIN 
    DECLARE @iRes    BIGINT 
    SET @iRes = CAST(CAST(@iX AS BINARY(8)) AS BIGINT) + CAST(CAST(@iY AS BINARY(8)) AS BIGINT) 
    RETURN(CAST(@iRes & 0x00000000FFFFFFFF AS BINARY(4))) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS OFF 
GO



/***************************************************************************** 
* Name: MD5_ConvertToWordArray 
* Description: MD5_ConvertToWordArray 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_ConvertToWordArray( 
     @sOrigMess        VARCHAR(8000)    = '' 
) 
RETURNS @tWordArray TABLE([ID] INT IDENTITY(0,1),[Word] INT) 
-- WITH ENCRYPTION 
AS 
BEGIN 
    IF @sOrigMess IS NULL 
        SET @sOrigMess = '' 
    DECLARE @iLenOfMess            INT 
    DECLARE @iWordArrayLen        INT 
    DECLARE @iPosOfWord            INT 
    DECLARE @iPosOfMess            INT 
    DECLARE @iCountOfWord        INT 
    SET @iLenOfMess = LEN(@sOrigMess) 
    SET @iWordArrayLen = ((@iLenOfMess + 8)/64 + 1) * 16 
    SET @iCountOfWord = 0 
    WHILE(@iCountOfWord<@iWordArrayLen) 
    BEGIN 
        INSERT INTO @tWordArray([Word]) VALUES(0) 
        SET @iCountOfWord = @iCountOfWord + 1 
    END 
    SELECT @iPosOfMess = 0, @iPosOfWord = 0, @iCountOfWord = 0 
    WHILE(@iPosOfMess < @iLenOfMess) 
    BEGIN 
        SELECT @iCountOfWord = @iPosOfMess / 4, @iPosOfWord = @iPosOfMess % 4 
        UPDATE @tWordArray 
            SET [Word] = [Word] | dbo.MD5_LShift(UNICODE(SUBSTRING(@sOrigMess,@iPosOfMess+1,1)),@iPosOfWord*8) 
            WHERE [ID] = @iCountOfWord 
        SET @iPosOfMess = @iPosOfMess + 1 
    END 
     
    SELECT @iCountOfWord = @iPosOfMess / 4, @iPosOfWord = @iPosOfMess % 4 
    UPDATE @tWordArray 
        SET [Word] = [Word] | dbo.MD5_LShift(0x80,@iPosOfWord*8) 
        WHERE [ID] = @iCountOfWord 
    UPDATE @tWordArray 
        SET [Word] = [Word] | dbo.MD5_LShift(@iLenOfMess,3) 
        WHERE [ID] = @iWordArrayLen - 2 
    UPDATE @tWordArray 
        SET [Word] = [Word] | dbo.MD5_RShift(@iLenOfMess,29) 
        WHERE [ID] = @iWordArrayLen - 1 
    RETURN 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_F 
* Description: MD5_F 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_F( 
     @x        INT 
    ,@y        INT 
    ,@z        INT 
) 
RETURNS INT 
-- WITH ENCRYPTION 
AS 
BEGIN 
    RETURN((@x & @y) | ((~@x) & @z)) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_FF 
* Description: MD5_FF 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_FF( 
     @a        INT 
    ,@b        INT 
    ,@c        INT 
    ,@d        INT 
    ,@x        INT 
    ,@s     INT 
    ,@ac    INT 
) 
RETURNS INT 
-- WITH ENCRYPTION 
AS 
BEGIN 
    SET @a = dbo.MD5_AddUnsigned(@a, dbo.MD5_AddUnsigned(dbo.MD5_AddUnsigned(dbo.MD5_F(@b, @c, @d), @x), @ac)) 
    SET @a = dbo.MD5_RotateLeft(@a, @s) 
    SET @a = dbo.MD5_AddUnsigned(@a, @b) 
    RETURN(@a) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_G 
* Description: MD5_G 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_G( 
     @x        INT 
    ,@y        INT 
    ,@z        INT 
) 
RETURNS INT 
-- WITH ENCRYPTION 
AS 
BEGIN 
    RETURN((@x & @z) | (@y & (~@z))) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_GG 
* Description: MD5_GG 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_GG( 
     @a        INT 
    ,@b        INT 
    ,@c        INT 
    ,@d        INT 
    ,@x        INT 
    ,@s     INT 
    ,@ac    INT 
) 
RETURNS INT 
-- WITH ENCRYPTION 
AS 
BEGIN 
    SET @a = dbo.MD5_AddUnsigned(@a, dbo.MD5_AddUnsigned(dbo.MD5_AddUnsigned(dbo.MD5_G(@b, @c, @d), @x), @ac)) 
    SET @a = dbo.MD5_RotateLeft(@a, @s) 
    SET @a = dbo.MD5_AddUnsigned(@a, @b) 
    RETURN(@a) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_H 
* Description: MD5_H 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_H( 
     @x        INT 
    ,@y        INT 
    ,@z        INT 
) 
RETURNS INT 
-- WITH ENCRYPTION 
AS 
BEGIN 
    RETURN(@x ^ @y ^ @z) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_HH 
* Description: MD5_HH 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_HH( 
     @a        INT 
    ,@b        INT 
    ,@c        INT 
    ,@d        INT 
    ,@x        INT 
    ,@s     INT 
    ,@ac    INT 
) 
RETURNS INT 
-- WITH ENCRYPTION 
AS 
BEGIN 
    SET @a = dbo.MD5_AddUnsigned(@a, dbo.MD5_AddUnsigned(dbo.MD5_AddUnsigned(dbo.MD5_H(@b, @c, @d), @x), @ac)) 
    SET @a = dbo.MD5_RotateLeft(@a, @s) 
    SET @a = dbo.MD5_AddUnsigned(@a, @b) 
    RETURN(@a) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_I 
* Description: MD5_I 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_I( 
     @x        INT 
    ,@y        INT 
    ,@z        INT 
) 
RETURNS INT 
-- WITH ENCRYPTION 
AS 
BEGIN 
    RETURN(@y ^ (@x | (~@z))) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_II 
* Description: MD5_II 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_II( 
     @a        INT 
    ,@b        INT 
    ,@c        INT 
    ,@d        INT 
    ,@x        INT 
    ,@s     INT 
    ,@ac    INT 
) 
RETURNS INT 
-- WITH ENCRYPTION 
AS 
BEGIN 
    SET @a = dbo.MD5_AddUnsigned(@a, dbo.MD5_AddUnsigned(dbo.MD5_AddUnsigned(dbo.MD5_I(@b, @c, @d), @x), @ac)) 
    SET @a = dbo.MD5_RotateLeft(@a, @s) 
    SET @a = dbo.MD5_AddUnsigned(@a, @b) 
    RETURN(@a) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_LShift 
* Description: MD5_LShift 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_LShift( 
     @iValue        INT 
    ,@iShiftBits    TINYINT 
) 
RETURNS INT 
-- WITH ENCRYPTION 
AS 
BEGIN 
    DECLARE @iRes    BIGINT 
    SET @iRes = CAST(@iValue AS BINARY(8)) 
    SET @iRes = @iRes * dbo.MD5_m_2Power(@iShiftBits) 
    RETURN(CAST(@iRes & 0x00000000FFFFFFFF AS BINARY(4))) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_RShift 
* Description: MD5_RShift 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_RShift( 
     @iValue        INT 
    ,@iShiftBits    TINYINT 
) 
RETURNS INT 
-- WITH ENCRYPTION 
AS 
BEGIN 
    DECLARE @iRes    BIGINT 
    SET @iRes = CAST(@iValue AS BINARY(8)) 
    SET @iRes = @iRes / dbo.MD5_m_2Power(@iShiftBits) 
    RETURN(CAST(@iRes & 0x00000000FFFFFFFF AS BINARY(4))) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_RotateLeft 
* Description: MD5_RotateLeft 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_RotateLeft( 
     @iValue        INT 
    ,@iShiftBits    TINYINT 
) 
RETURNS INT 
-- WITH ENCRYPTION 
AS 
BEGIN 
    RETURN(dbo.MD5_LShift(@iValue, @iShiftBits) | dbo.MD5_RShift(@iValue, (32 - @iShiftBits))) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_WordToHex 
* Description: MD5_WordToHex 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_WordToHex( 
     @iValue        INT 
) 
RETURNS CHAR(8) 
-- WITH ENCRYPTION 
AS 
BEGIN 
    DECLARE @sRes    VARCHAR(8) 
    DECLARE @iTmp    INT 
    DECLARE @iCount TINYINT 
    SELECT @sRes = '', @iCount = 0 
    WHILE(@iCount<4) 
    BEGIN 
        SET @iTmp = dbo.MD5_RShift(@iValue,@iCount*8) & 0x000000FF 
        SET @sRes = @sRes + CASE @iTmp / 16 WHEN 0  THEN '0' 
                                            WHEN 1  THEN '1' 
                                            WHEN 2  THEN '2' 
                                            WHEN 3  THEN '3' 
                                            WHEN 4  THEN '4' 
                                            WHEN 5  THEN '5' 
                                            WHEN 6  THEN '6' 
                                            WHEN 7  THEN '7' 
                                            WHEN 8  THEN '8' 
                                            WHEN 9  THEN '9' 
                                            WHEN 10 THEN 'A' 
                                            WHEN 11 THEN 'B' 
                                            WHEN 12 THEN 'C' 
                                            WHEN 13 THEN 'D' 
                                            WHEN 14 THEN 'E' 
                                            WHEN 15 THEN 'F' 
                                            ELSE '' END 
                          + CASE @iTmp % 16 WHEN 0 THEN '0' 
                                            WHEN 1  THEN '1' 
                                            WHEN 2  THEN '2' 
                                            WHEN 3  THEN '3' 
                                            WHEN 4  THEN '4' 
                                            WHEN 5  THEN '5' 
                                            WHEN 6  THEN '6' 
                                            WHEN 7  THEN '7' 
                                            WHEN 8  THEN '8' 
                                            WHEN 9  THEN '9' 
                                            WHEN 10 THEN 'A' 
                                            WHEN 11 THEN 'B' 
                                            WHEN 12 THEN 'C' 
                                            WHEN 13 THEN 'D' 
                                            WHEN 14 THEN 'E' 
                                            WHEN 15 THEN 'F' 
                                            ELSE '' END 
        SET @iCount = @iCount + 1 
    END 
    RETURN(@sRes) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_m_2Power 
* Description: 常?? 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_m_2Power( 
    @i    TINYINT 
) 
RETURNS INT 
-- WITH ENCRYPTION 
AS 
BEGIN 
    DECLARE @iRes    INT 
    SELECT @iRes = 
        CASE @i 
            WHEN 0  THEN 1            -- 00000000000000000000000000000001 
            WHEN 1  THEN 2            -- 00000000000000000000000000000010 
            WHEN 2  THEN 4            -- 00000000000000000000000000000100 
            WHEN 3  THEN 8            -- 00000000000000000000000000001000 
            WHEN 4  THEN 16           -- 00000000000000000000000000010000 
            WHEN 5  THEN 32           -- 00000000000000000000000000100000 
            WHEN 6  THEN 64           -- 00000000000000000000000001000000 
            WHEN 7  THEN 128          -- 00000000000000000000000010000000 
            WHEN 8  THEN 256          -- 00000000000000000000000100000000 
            WHEN 9  THEN 512          -- 00000000000000000000001000000000 
            WHEN 10 THEN 1024         -- 00000000000000000000010000000000 
            WHEN 11 THEN 2048         -- 00000000000000000000100000000000 
            WHEN 12 THEN 4096         -- 00000000000000000001000000000000 
            WHEN 13 THEN 8192         -- 00000000000000000010000000000000 
            WHEN 14 THEN 16384        -- 00000000000000000100000000000000 
            WHEN 15 THEN 32768        -- 00000000000000001000000000000000 
            WHEN 16 THEN 65536        -- 00000000000000010000000000000000 
            WHEN 17 THEN 131072       -- 00000000000000100000000000000000 
            WHEN 18 THEN 262144       -- 00000000000001000000000000000000 
            WHEN 19 THEN 524288       -- 00000000000010000000000000000000 
            WHEN 20 THEN 1048576      -- 00000000000100000000000000000000 
            WHEN 21 THEN 2097152      -- 00000000001000000000000000000000 
            WHEN 22 THEN 4194304      -- 00000000010000000000000000000000 
            WHEN 23 THEN 8388608      -- 00000000100000000000000000000000 
            WHEN 24 THEN 16777216     -- 00000001000000000000000000000000 
            WHEN 25 THEN 33554432     -- 00000010000000000000000000000000 
            WHEN 26 THEN 67108864     -- 00000100000000000000000000000000 
            WHEN 27 THEN 134217728    -- 00001000000000000000000000000000 
            WHEN 28 THEN 268435456    -- 00010000000000000000000000000000 
            WHEN 29 THEN 536870912    -- 00100000000000000000000000000000 
            WHEN 30 THEN 1073741824   -- 01000000000000000000000000000000 
            ELSE 0 
        END 
    RETURN(@iRes) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO



/***************************************************************************** 
* Name: MD5_m_OnBits 
* Description: 常?? 
*****************************************************************************/ 
CREATE FUNCTION dbo.MD5_m_OnBits( 
    @i    TINYINT 
) 
RETURNS INT 
-- WITH ENCRYPTION 
AS 
BEGIN 
    DECLARE @iRes    INT 
    SELECT @iRes = 
        CASE @i 
            WHEN 0  THEN 1            -- 00000000000000000000000000000001 
            WHEN 1  THEN 3            -- 00000000000000000000000000000011 
            WHEN 2  THEN 7            -- 00000000000000000000000000000111 
            WHEN 3  THEN 15           -- 00000000000000000000000000001111 
            WHEN 4  THEN 31           -- 00000000000000000000000000011111 
            WHEN 5  THEN 63           -- 00000000000000000000000000111111 
            WHEN 6  THEN 127          -- 00000000000000000000000001111111 
            WHEN 7  THEN 255          -- 00000000000000000000000011111111 
            WHEN 8  THEN 511          -- 00000000000000000000000111111111 
            WHEN 9  THEN 1023         -- 00000000000000000000001111111111 
            WHEN 10 THEN 2047         -- 00000000000000000000011111111111 
            WHEN 11 THEN 4095         -- 00000000000000000000111111111111 
            WHEN 12 THEN 8191         -- 00000000000000000001111111111111 
            WHEN 13 THEN 16383        -- 00000000000000000011111111111111 
            WHEN 14 THEN 32767        -- 00000000000000000111111111111111 
            WHEN 15 THEN 65535        -- 00000000000000001111111111111111 
            WHEN 16 THEN 131071       -- 00000000000000011111111111111111 
            WHEN 17 THEN 262143       -- 00000000000000111111111111111111 
            WHEN 18 THEN 524287       -- 00000000000001111111111111111111 
            WHEN 19 THEN 1048575      -- 00000000000011111111111111111111 
            WHEN 20 THEN 2097151      -- 00000000000111111111111111111111 
            WHEN 21 THEN 4194303      -- 00000000001111111111111111111111 
            WHEN 22 THEN 8388607      -- 00000000011111111111111111111111 
            WHEN 23 THEN 16777215     -- 00000000111111111111111111111111 
            WHEN 24 THEN 33554431     -- 00000001111111111111111111111111 
            WHEN 25 THEN 67108863     -- 00000011111111111111111111111111 
            WHEN 26 THEN 134217727    -- 00000111111111111111111111111111 
            WHEN 27 THEN 268435455    -- 00001111111111111111111111111111 
            WHEN 28 THEN 536870911    -- 00011111111111111111111111111111 
            WHEN 29 THEN 1073741823   -- 00111111111111111111111111111111 
            WHEN 30 THEN 2147483647   -- 01111111111111111111111111111111 
            ELSE 0 
        END 
    RETURN(@iRes) 
END 



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS OFF 
GO



CREATE FUNCTION [dbo].[udf_hex_to_number]
(
	@c char(1)
)  
RETURNS int AS  
BEGIN
	declare @n int
	Set @n = Case @c 
		WHEN '0'  THEN 0 
		WHEN '1'  THEN 1 
		WHEN '2'  THEN 2 
		WHEN '3'  THEN 3 
		WHEN '4'  THEN 4 
		WHEN '5'  THEN 5 
		WHEN '6'  THEN 6 
		WHEN '7'  THEN 7 
		WHEN '8'  THEN 8 
		WHEN '9'  THEN 9 
		WHEN 'a' THEN 10 
		WHEN 'b' THEN 11 
		WHEN 'c' THEN 12 
		WHEN 'd' THEN 13 
		WHEN 'e' THEN 14 
		WHEN 'f' THEN 15 
		ELSE 0 END 
	return(@n)
END



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS OFF 
GO



CREATE FUNCTION [dbo].[udf_number_to_hex]
(
	@N int
)  
RETURNS char(1) AS  
BEGIN
	declare @chr char(1)
	Set @chr = Case @N % 16 
		WHEN 0  THEN '0' 
		WHEN 1  THEN '1' 
		WHEN 2  THEN '2' 
		WHEN 3  THEN '3' 
		WHEN 4  THEN '4' 
		WHEN 5  THEN '5' 
		WHEN 6  THEN '6' 
		WHEN 7  THEN '7' 
		WHEN 8  THEN '8' 
		WHEN 9  THEN '9' 
		WHEN 10 THEN 'a' 
		WHEN 11 THEN 'b' 
		WHEN 12 THEN 'c' 
		WHEN 13 THEN 'd' 
		WHEN 14 THEN 'e' 
		WHEN 15 THEN 'f' 
		ELSE '' END 
	return(@chr)
END



GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

CREATE TABLE [dbo].[GS_ChangeAbility] (
	[index] [int] IDENTITY (1, 1) NOT NULL ,
	[dateREG] [datetime] NULL ,
	[Account] [nvarchar] (20) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[CharID] [int] NOT NULL ,
	[CharName] [nvarchar] (30) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[AbilityType] [smallint] NULL ,
	[UsedPoint] [smallint] NULL ,
	[BonusPoint] [smallint] NULL ,
	[IP] [char] (15) COLLATE Korean_Wansung_CI_AS NULL ,
	[Location] [varchar] (24) COLLATE Korean_Wansung_CI_AS NULL ,
	[LocX] [int] NULL ,
	[LocY] [int] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[GS_CharacterLog] (
	[Index] [int] IDENTITY (1, 1) NOT NULL ,
	[dateREG] [datetime] NULL ,
	[AccountName] [nvarchar] (20) COLLATE Korean_Wansung_CI_AS NULL ,
	[CharName] [nvarchar] (30) COLLATE Korean_Wansung_CI_AS NULL ,
	[DelAdd] [tinyint] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[GS_CreateLog] (
	[Index] [int] IDENTITY (1, 1) NOT NULL ,
	[dateREG] [datetime] NULL ,
	[CharID] [int] NOT NULL ,
	[CharName] [nvarchar] (30) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[ItemID] [varchar] (10) COLLATE Korean_Wansung_CI_AS NULL ,
	[ItemName] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
	[Stuff1] [varchar] (30) COLLATE Korean_Wansung_CI_AS NULL ,
	[Stuff2] [varchar] (30) COLLATE Korean_Wansung_CI_AS NULL ,
	[Stuff3] [varchar] (30) COLLATE Korean_Wansung_CI_AS NULL ,
	[Stuff4] [varchar] (30) COLLATE Korean_Wansung_CI_AS NULL ,
	[Making] [tinyint] NULL ,
	[Success] [tinyint] NULL ,
	[Location] [varchar] (24) COLLATE Korean_Wansung_CI_AS NULL ,
	[LocX] [int] NULL ,
	[LocY] [int] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[GS_DieLog] (
	[Index] [int] IDENTITY (1, 1) NOT NULL ,
	[dateREG] [datetime] NULL ,
	[CharName] [varchar] (32) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[Money] [bigint] NULL ,
	[CharLevel] [smallint] NULL ,
	[Exp] [int] NULL ,
	[KillPos] [varchar] (24) COLLATE Korean_Wansung_CI_AS NULL ,
	[PosX] [int] NULL ,
	[PosY] [int] NULL ,
	[ObjectName] [varchar] (32) COLLATE Korean_Wansung_CI_AS NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[GS_GemmingLog] (
	[Index] [int] IDENTITY (1, 1) NOT NULL ,
	[dateREG] [datetime] NULL ,
	[CharID] [int] NOT NULL ,
	[CharName] [nvarchar] (30) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[ItemID] [varchar] (10) COLLATE Korean_Wansung_CI_AS NULL ,
	[ItemName] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
	[JewelID] [varchar] (10) COLLATE Korean_Wansung_CI_AS NULL ,
	[JewelName] [varchar] (24) COLLATE Korean_Wansung_CI_AS NULL ,
	[Gemming] [tinyint] NULL ,
	[Success] [tinyint] NULL ,
	[Location] [varchar] (24) COLLATE Korean_Wansung_CI_AS NULL ,
	[LocX] [int] NULL ,
	[LocY] [int] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[GS_ItemLog] (
	[Index] [int] IDENTITY (1, 1) NOT NULL ,
	[dateREG] [datetime] NULL ,
	[Action] [int] NOT NULL ,
	[SbjAccount] [nvarchar] (20) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[SbjCharID] [int] NOT NULL ,
	[SbjCharName] [nvarchar] (30) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[ItemID] [varchar] (10) COLLATE Korean_Wansung_CI_AS NULL ,
	[ItemName] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
	[ItemCount] [smallint] NULL ,
	[ItemSN] [bigint] NULL ,
	[ItemOpt] [smallint] NULL ,
	[Money] [bigint] NULL ,
	[Location] [varchar] (24) COLLATE Korean_Wansung_CI_AS NULL ,
	[LocX] [int] NULL ,
	[LocY] [int] NULL ,
	[ObjAccount] [nvarchar] (20) COLLATE Korean_Wansung_CI_AS NULL ,
	[ObjCharID] [int] NULL ,
	[ObjCharName] [nvarchar] (30) COLLATE Korean_Wansung_CI_AS NULL ,
	[SbjIP] [varchar] (15) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[ObjIP] [varchar] (15) COLLATE Korean_Wansung_CI_AS NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[GS_LevelUpLog] (
	[Index] [int] IDENTITY (1, 1) NOT NULL ,
	[dateREG] [datetime] NULL ,
	[CharID] [int] NOT NULL ,
	[CharName] [nvarchar] (30) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[toLevel] [smallint] NULL ,
	[BPoint] [smallint] NULL ,
	[SPoint] [smallint] NULL ,
	[Location] [varchar] (24) COLLATE Korean_Wansung_CI_AS NULL ,
	[LocX] [int] NULL ,
	[LocY] [int] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[GS_PeriodicCHARLog] (
	[Index] [int] IDENTITY (1, 1) NOT NULL ,
	[dateREG] [datetime] NULL ,
	[CharName] [varchar] (32) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[Channel] [tinyint] NULL ,
	[CharLevel] [smallint] NULL ,
	[Money] [bigint] NULL ,
	[Exp] [int] NULL ,
	[BPoint] [smallint] NULL ,
	[SPoint] [smallint] NULL ,
	[Location] [varchar] (24) COLLATE Korean_Wansung_CI_AS NULL ,
	[LocX] [int] NULL ,
	[LocY] [int] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[GS_QuestLog] (
	[Index] [int] IDENTITY (1, 1) NOT NULL ,
	[dateREG] [datetime] NULL ,
	[CharID] [int] NOT NULL ,
	[CharName] [nvarchar] (30) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[QuestID] [int] NULL ,
	[QuestDo] [tinyint] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[GS_SkillLog] (
	[Index] [int] IDENTITY (1, 1) NOT NULL ,
	[dateREG] [datetime] NULL ,
	[CharID] [int] NOT NULL ,
	[CharName] [nvarchar] (30) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[SkillID] [int] NULL ,
	[SkillName] [varchar] (24) COLLATE Korean_Wansung_CI_AS NULL ,
	[SkillLevel] [smallint] NULL ,
	[SPoint] [smallint] NULL ,
	[Location] [varchar] (24) COLLATE Korean_Wansung_CI_AS NULL ,
	[LocX] [int] NULL ,
	[LocY] [int] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[GS_UnionLog] (
	[Index] [int] IDENTITY (1, 1) NOT NULL ,
	[dateREG] [datetime] NULL ,
	[iCharID] [int] NOT NULL ,
	[szCharName] [nvarchar] (30) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[nAction] [smallint] NOT NULL ,
	[nCurUnion] [smallint] NOT NULL ,
	[iCurPoint] [int] NOT NULL ,
	[nAfterUnion] [smallint] NOT NULL ,
	[iAfterPoint] [int] NOT NULL ,
	[szLocation] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
	[iLocX] [int] NULL ,
	[iLocY] [int] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[GS_UpgradeLog] (
	[Index] [int] IDENTITY (1, 1) NOT NULL ,
	[dateREG] [datetime] NULL ,
	[CharID] [int] NOT NULL ,
	[CharName] [nvarchar] (30) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[ItemID] [varchar] (10) COLLATE Korean_Wansung_CI_AS NULL ,
	[ItemName] [varchar] (50) COLLATE Korean_Wansung_CI_AS NULL ,
	[UpLevel] [smallint] NULL ,
	[Success] [tinyint] NULL ,
	[Location] [varchar] (24) COLLATE Korean_Wansung_CI_AS NULL ,
	[LocX] [int] NULL ,
	[LocY] [int] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[UpdatePoint_Log] (
	[updatepoint_log_no] [bigint] IDENTITY (1, 1) NOT NULL ,
	[Account_No] [int] NULL ,
	[Save_Point] [int] NULL ,
	[Cdt] [datetime] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[WS_CheatLog] (
	[Index] [int] NULL ,
	[dateREG] [datetime] NULL ,
	[Account] [nvarchar] (20) COLLATE SQL_Latin1_General_CP437_BIN NULL ,
	[CharName] [nvarchar] (30) COLLATE SQL_Latin1_General_CP437_BIN NULL ,
	[ChannelNo] [char] (1) COLLATE SQL_Latin1_General_CP437_BIN NULL ,
	[CheatCode] [nvarchar] (255) COLLATE SQL_Latin1_General_CP437_BIN NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[WS_ClanLog] (
	[Index] [int] IDENTITY (1, 1) NOT NULL ,
	[dateREG] [datetime] NULL ,
	[CharName] [nvarchar] (32) COLLATE Korean_Wansung_CI_AS NULL ,
	[ClanName] [nvarchar] (20) COLLATE Korean_Wansung_CI_AS NULL ,
	[ClanLevel] [smallint] NULL ,
	[Point] [int] NULL ,
	[Success] [tinyint] NULL ,
	[Location] [varchar] (24) COLLATE Korean_Wansung_CI_AS NULL ,
	[LocX] [int] NULL ,
	[LocY] [int] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[WS_LoginLog] (
	[Index] [int] IDENTITY (1, 1) NOT NULL ,
	[dateREG] [datetime] NULL ,
	[Login] [tinyint] NULL ,
	[CharName] [nvarchar] (30) COLLATE Korean_Wansung_CI_AS NULL ,
	[Channel] [tinyint] NULL ,
	[CharLevel] [smallint] NULL ,
	[Money] [bigint] NULL ,
	[Location] [varchar] (24) COLLATE Korean_Wansung_CI_AS NULL ,
	[LocX] [int] NULL ,
	[LocY] [int] NULL ,
	[LoginIP] [varchar] (15) COLLATE Korean_Wansung_CI_AS NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[tblGS_ERROR] (
	[Index] [int] NULL ,
	[dateREG] [datetime] NULL ,
	[txtIP] [varchar] (15) COLLATE Korean_Wansung_CI_AS NULL ,
	[txtACCOUNT] [nvarchar] (20) COLLATE Korean_Wansung_CI_AS NULL ,
	[txtCHAR] [nvarchar] (32) COLLATE Korean_Wansung_CI_AS NULL ,
	[txtFILE] [char] (255) COLLATE Korean_Wansung_CI_AS NULL ,
	[intLINE] [int] NULL ,
	[txtDESC] [nvarchar] (512) COLLATE Korean_Wansung_CI_AS NULL 
) ON [PRIMARY]
GO

CREATE TABLE [dbo].[tblGS_LogIN] (
	[dateREG] [datetime] NOT NULL ,
	[txtACCOUNT] [nchar] (30) COLLATE Korean_Wansung_CI_AS NOT NULL ,
	[txtServerIP] [char] (20) COLLATE Korean_Wansung_CI_AS NOT NULL 
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[GS_ChangeAbility] ADD 
	CONSTRAINT [DF_GS_ChangeAbility_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[GS_CreateLog] ADD 
	CONSTRAINT [DF_GS_CreateLog_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[GS_DieLog] ADD 
	CONSTRAINT [DF_GS_DieLog_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[GS_GemmingLog] ADD 
	CONSTRAINT [DF_GS_GemmingLog_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[GS_ItemLog] ADD 
	CONSTRAINT [DF_GS_ItemLog_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[GS_LevelUpLog] ADD 
	CONSTRAINT [DF_GS_LevelUpLog_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[GS_PeriodicCHARLog] ADD 
	CONSTRAINT [DF_GS_PeriodicCHARLog_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[GS_QuestLog] ADD 
	CONSTRAINT [DF_GS_QuestLog_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[GS_SkillLog] ADD 
	CONSTRAINT [DF_GS_SkillLog_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[GS_UnionLog] ADD 
	CONSTRAINT [DF_GS_UnionLog_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[GS_UpgradeLog] ADD 
	CONSTRAINT [DF_GS_UpgradeLog_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[WS_CheatLog] ADD 
	CONSTRAINT [DF_WS_CheatLog_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[WS_ClanLog] ADD 
	CONSTRAINT [DF_WS_ClanLog_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[WS_LoginLog] ADD 
	CONSTRAINT [DF_WS_LoginLog_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[tblGS_ERROR] ADD 
	CONSTRAINT [DF_tblGS_ERROR_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

ALTER TABLE [dbo].[tblGS_LogIN] ADD 
	CONSTRAINT [DF_tblGS_LogIN_dateREG] DEFAULT (getdate()) FOR [dateREG]
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

Create Proc [dbo].[AddCharacterLog] @AccountName nvarchar(20), @CharName nvarchar(30), @DelAdd tinyint AS Insert Into GS_CharacterLog( dateREG, AccountName, CharName, DelAdd) Values (Default, @AccountName, @CharName, @DelAdd) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

CREATE PROCEDURE [dbo].[AddCheatLog] @Account nvarchar(20), @CharName nvarchar(30), @ChannelNo tinyint, @CheatCode nvarchar(55) AS Set NoCount On Declare @AID int set @AID=(select max([Index]) from SHO_LOG..WS_CheatLog) set @AID=@AID+1 Insert Into WS_CheatLog ([Index],dateREG,Account, CharName, ChannelNo, CheatCode) Values(@AID,getDate(),@Account, @CharName, @ChannelNo, @CheatCode)
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

CREATE Proc [dbo].[AddClanLog] @CharName nvarchar(32), @ClanName nvarchar(20), @ClanLevel smallint, @Point int, @Success tinyint, @Location varchar(24), @LocX int, @LocY int As Insert Into WS_ClanLog (dateREG, CharName, ClanName, ClanLevel, Point, Success, Location, LocX, LocY) Values (Default, @CharName, @ClanName, @ClanLevel, @Point, @Success, @Location, @LocX, @LocY) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

Create Proc [dbo].[AddCreateLog] @CharID int, @CharName nvarchar(30), @ItemID varchar(10), @ItemName varchar(50), @Stuff1 varchar(24), @Stuff2 varchar(24), @Stuff3 varchar(24), @Stuff4 varchar(24), @Making tinyint, @Success tinyint, @Location varchar(24), @LocX int, @LocY int AS Insert Into GS_CreateLog ( dateREG, CharID, CharName, ItemID, ItemName, Stuff1, Stuff2, Stuff3, Stuff4, Making, Success, Location, LocX, LocY) Values ( Default, @CharID, @CharName, @ItemID, @ItemName, @Stuff1, @Stuff2, @Stuff3, @Stuff4, @Making, @Success, @Location, @LocX, @LocY ) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

CREATE Proc [dbo].[AddDieLog] @CharName varchar(32), @Money bigint, @KillPos varchar(24), @CharLevel smallint, @Exp int, @PosX int, @PosY int, @ObjectName varchar(50) As Insert Into GS_DieLog (dateREG, CharName, [Money], CharLevel, [Exp], KillPos, PosX, PosY, ObjectName) Values(Default, @CharName, @Money, @CharLevel, @Exp, @KillPos, @PosX, @PosY, @ObjectName) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

CREATE Proc [dbo].[AddGemmingLog] @CharID int, @CharName nvarchar(30), @ItemID varchar(10), @ItemName varchar(50), @JewelID varchar(10), @JewelName varchar(24), @Gemming tinyint, @Success tinyint, @Location varchar(24), @LocX int, @LocY int AS Insert Into GS_GemmingLog ( dateREG, CharID, CharName, ItemID, ItemName, JewelID, JewelName, Gemming, Success, Location, LocX, LocY) Values ( Default, @CharID, @CharName, @ItemID, @ItemName, @JewelID, @JewelName, @Gemming, @Success, @Location, @LocX, @LocY) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

CREATE Proc [dbo].[AddItemLog] @Action int, @SbjAccount nvarchar(20), @SbjCharID int, @SbjCharName nvarchar(30), @ItemID varchar(10), @ItemName varchar(50), @ItemCount smallint, @ItemSN bigint, @Money bigint, @Location varchar(24), @LocX int, @LocY int, @ObjAccount nvarchar(20), @ObjCharID int, @ObjCharName nvarchar(30), @SbjIP varchar(15), @ObjIP varchar(15) AS Insert Into GS_ItemLog ( dateREG, [Action], SbjAccount, SbjCharID, SbjCharName, ItemID, ItemName, ItemCount, ItemSN, [Money], Location, LocX, LocY, ObjAccount, ObjCharID, ObjCharName, SbjIP, ObjIP) Values (Default, @Action, @SbjAccount, @SbjCharID, @SbjCharName, @ItemID, @ItemName, @ItemCount, @ItemSN, @Money, @Location, @LocX, @LocY, @ObjAccount, @ObjCharID, @ObjCharName, @SbjIP, @ObjIP) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

Create Proc [dbo].[AddLevelUpLog] @CharID int, @CharName nvarchar(30), @toLevel smallint, @BPoint smallint, @SPoint smallint, @Location varchar(24), @LocX int, @LocY int AS Insert Into GS_LevelUpLog ( dateREG, CharID, CharName, toLevel, BPoint, SPoint, Location, LocX, LocY) Values (Default, @CharID, @CharName, @toLevel, @BPoint, @SPoint, @Location, @LocX, @LocY) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

CREATE Proc [dbo].[AddLoginLog] @Login tinyint, @CharName nvarchar(30), @Channel tinyint, @CharLevel smallint, @Money bigint, @Location varchar(24), @LocX int, @LocY int, @LoginIP varchar(15) AS Insert Into WS_LoginLog( dateREG, Login, CharName, Channel, CharLevel, [Money], Location, LocX, LocY, LoginIP) Values (Default, @Login, @CharName, @Channel, @CharLevel, @Money, @Location, @LocX, @LocY, @LoginIP) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

Create Proc [dbo].[AddPeriodicCHARLog] @CharName varchar(32), @Channel tinyint, @CharLevel smallint, @Money bigint, @Exp int, @BPoint smallint, @SPoint smallint, @Location varchar(24), @LocX int, @LocY int As Insert Into GS_PeriodicCHARLog(dateREG, CharName, Channel, CharLevel, [Money], [Exp], BPoint, SPoint, Location, LocX, LocY) Values (Default, @CharName, @Channel, @CharLevel, @Money, @Exp, @BPoint, @SPoint, @Location, @LocX, @LocY) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

Create Proc [dbo].[AddQuestLog] @CharID int, @CharName nvarchar(30), @QuestID int, @QuestDo tinyint AS Insert Into GS_QuestLog( dateREG, CharID, CharName, QuestID, QuestDo) Values (Default, @CharID, @CharName, @QuestID, @QuestDo) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

Create Proc [dbo].[AddSkillLog] @CharID int, @CharName nvarchar(30), @SkillID int, @SkillName varchar(24), @SkillLevel smallint, @SPoint smallint, @Location varchar(24), @LocX int, @LocY int AS Insert Into GS_SkillLog( dateREG, CharID, CharName, SkillID, SkillName, SkillLevel, SPoint, Location, LocX, LocY) Values (Default, @CharID, @CharName, @SkillID, @SkillName, @SkillLevel, @SPoint, @Location, @LocX, @LocY) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

Create Proc [dbo].[AddUpgradeLog] @CharID int, @CharName nvarchar(30), @ItemID varchar(10), @ItemName varchar(50), @UpLevel smallint, @Success tinyint, @Location varchar(24), @LocX int, @LocY int AS Insert Into GS_UpgradeLog( dateREG, CharID, CharName, ItemID, ItemName, UpLevel, Success, Location, LocX, LocY) Values ( Default, @CharID, @CharName, @ItemID, @ItemName, @UpLevel, @Success, @Location, @LocX, @LocY) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

CREATE PROC dbo.DeleteGS_Log AS --Change of DB Recovery Model : Full ALTER DATABASE SHO_Log SET RECOVERY FULL --Change Transaction Log File Growth : Unlimited ALTER DATABASE SHO_Log MODIFY FILE ( NAME = SHO_Log_Log, SIZE = 30MB, MAXSIZE = UNLIMITED, FILEGROWTH = 50% ) --Deleted for Yesterday Data Delete From GS_CharacterLog WHERE dateREG < CONVERT(CHAR(10), GETDATE(), 20) Delete From GS_CreateLog WHERE dateREG < CONVERT(CHAR(10), GETDATE(), 20) Delete From GS_DieLog WHERE dateREG < CONVERT(CHAR(10), GETDATE(), 20) Delete From GS_GemmingLog WHERE dateREG < CONVERT(CHAR(10), GETDATE(), 20) Delete From GS_ItemLog WHERE dateREG < CONVERT(CHAR(10), GETDATE(), 20) Delete From GS_LevelUpLog WHERE dateREG < CONVERT(CHAR(10), GETDATE(), 20) Delete From GS_PeriodicCHARLog WHERE dateREG < CONVERT(CHAR(10), GETDATE(), 20) Delete From GS_QuestLog WHERE dateREG < CONVERT(CHAR(10), GETDATE(), 20) Delete From GS_SkillLog WHERE dateREG < CONVERT(CHAR(10), GETDATE(), 20) Delete From GS_UpgradeLog WHERE dateREG < CONVERT(CHAR(10), GETDATE(), 20) Delete From WS_CheatLog WHERE dateREG < CONVERT(CHAR(10), GETDATE(), 20) Delete From WS_ClanLog WHERE dateREG < CONVERT(CHAR(10), GETDATE(), 20) Delete From WS_LoginLog WHERE dateREG < CONVERT(CHAR(10), GETDATE(), 20) DELETE FROM tblGS_ERROR WHERE dateREG < CONVERT(CHAR(10), GETDATE(), 20) --Shrinkfile SHO_Log's Data & Log File size DBCC SHRINKFILE(SHO_Log_Data) DBCC SHRINKFILE(SHO_Log_Log, NOTRUNCATE) --Change Transaction Log File Growth : Limited ALTER DATABASE SHO_Log MODIFY FILE ( NAME = SHO_Log_Log, SIZE = 10MB, MAXSIZE = UNLIMITED, FILEGROWTH = 10% ) --Change of DB Recovery Model : Simple ALTER DATABASE SHO_Log SET RECOVERY SIMPLE 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

CREATE PROCEDURE dbo.gs_M_DefLOG @iMoney int, @szSUB nvarchar(32), @szSBJIP varchar(15), @szACT varchar(24), @szLOC nvarchar(50), @szITEM nvarchar(200) AS INSERT tblGS_LOG ( dateREG, intMoney, txtSUBJECT, txtSBJIP, txtACTION, txtLOC, txtITEM ) VALUES( default, @iMoney, @szSUB, @szSBJIP, @szACT, @szLOC, @szITEM ) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

CREATE PROCEDURE dbo.gs_M_DescLOG @iMoney int, @szSUB nvarchar(32), @szSBJIP varchar(15), @szACT varchar(24), @szLOC nvarchar(50), @szITEM nvarchar(200), @szDESC nvarchar(200) AS INSERT tblGS_LOG ( dateREG, intMoney, txtSUBJECT, txtSBJIP, txtACTION, txtLOC, txtITEM,txtDESC ) VALUES( default, @iMoney, @szSUB, @szSBJIP, @szACT, @szLOC, @szITEM, @szDESC ) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

CREATE PROCEDURE dbo.gs_M_LogInOut @iMoney int, @szSUB nvarchar(32), @szOBJ nvarchar(32), @szSBJIP varchar(15), @szACT varchar(24), @szLOC nvarchar(50), @szITEM nvarchar(200) AS INSERT tblGS_LOG ( dateREG, intMoney, txtSUBJECT, txtSBJIP, txtACTION, txtLOC, txtITEM, txtOBJECT ) VALUES( default, @iMoney, @szSUB, @szSBJIP, @szACT, @szLOC, @szITEM, @szOBJ ) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

CREATE PROCEDURE dbo.gs_M_ObjDescLOG @iMoney int, @szSUB nvarchar(32), @szSBJIP varchar(15), @szACT varchar(24), @szLOC nvarchar(50), @szITEM nvarchar(200), @szOBJ nvarchar(32), @szOBJIP nvarchar(15), @szDESC nvarchar(200) AS INSERT tblGS_LOG ( dateREG, intMoney, txtSUBJECT, txtSBJIP, txtACTION, txtLOC, txtITEM, txtOBJECT, txtOBJIP, txtDESC ) VALUES( default, @iMoney, @szSUB, @szSBJIP, @szACT, @szLOC, @szITEM, @szOBJ, @szOBJIP, @szDESC ) 
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS OFF 
GO

CREATE PROCEDURE dbo.gs_M_ObjLOG @iMoney int, @szSUB nvarchar(32), @szSBJIP varchar(15), @szACT varchar(24), @szLOC nvarchar(50), @szITEM nvarchar(200), @szOBJ nvarchar(32), @szOBJIP nvarchar(15) AS INSERT tblGS_LOG ( dateREG, intMoney, txtSUBJECT, txtSBJIP, txtACTION, txtLOC, txtITEM, txtOBJECT, txtOBJIP ) VALUES( default, @iMoney, @szSUB, @szSBJIP, @szACT, @szLOC, @szITEM, @szOBJ, @szOBJIP )
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS OFF 
GO

CREATE proc sp_getGameTime @charname varchar(60) as 
declare @date2 datetime,@addtime int,@startday datetime, @endday datetime, @currentday datetime

	set @startday=(select top 1 dateREG from SHO_LOG..WS_LoginLog where CharName=@charname and Login=0 and dateREG>'2006-11-11 21:55:09.630' order by dateREG)
	set @endday=(select top 1 dateREG from SHO_LOG..WS_LoginLog where CharName=@charname and Login=1 and dateREG>'2006-11-11 21:55:09.630' order by dateREG desc)
	set @currentday=@startday
	set @addtime=0

	while (@currentday<@endday)
	begin
		set @date2=(select top 1 dateREG from SHO_LOG..WS_LoginLog where CharName=@charname and Login=1 and dateREG>'2006-11-11 21:55:09.630' and dateREG>@currentday order by dateREG)
		set @addtime=@addtime+datediff(minute,@currentday,@date2)
		set @currentday=(select top 1 dateREG from SHO_LOG..WS_LoginLog where CharName=@charname and Login=0 and dateREG>'2006-11-11 21:55:09.630' and dateREG>@date2 order by dateREG)
	end

select @addtime
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

