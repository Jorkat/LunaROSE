#include "stdafx.h"
#include "libCrc.h"
#include "classCRC.h"


// Crc ｰｪﾀｻ ﾁｶｻ酩ﾑｴﾙ
DWORD CLibCrc::GetIcarusCrc ( const unsigned char * pbtData, int lLength)
{
	return classCRC::DataCRC32 (pbtData, lLength, true );
};