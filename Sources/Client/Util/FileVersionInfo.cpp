#include "stdafx.h"
#include ".\fileversioninfo.h"

CFileVersionInfo::CFileVersionInfo(void)
{
	m_iMajorVersion			= 0;
	m_MinorVersion			= 0;
	m_BuildNumber			= 0;
	m_RevisionNumber		= 0;
}

CFileVersionInfo::~CFileVersionInfo(void)
{
}

char const *UTF16ToUTF8(wchar_t *input)
{
	size_t const inputLength = wcslen(input);

	auto const returnWithError = []() -> char const*
	{
		switch(GetLastError())
		{
		case ERROR_INVALID_FLAGS:
		case ERROR_INVALID_PARAMETER:
			assert(false && "Fix code lol");
			return nullptr;
			break;
		case ERROR_NO_UNICODE_TRANSLATION:
			assert(false && "Invalid UTF-8 found in string? ?????????????");
			return nullptr;
			break;
		}
	};

	int const requiredBufSize = WideCharToMultiByte(
		CP_UTF8,
		WC_ERR_INVALID_CHARS | WC_NO_BEST_FIT_CHARS,
		input,
		inputLength,
		nullptr,
		0,
		nullptr,
		FALSE);

	if(!requiredBufSize)
		return returnWithError();

	char *const output = new char[requiredBufSize];

	int const error = WideCharToMultiByte(
		CP_UTF8,
		WC_ERR_INVALID_CHARS | WC_NO_BEST_FIT_CHARS,
		input,
		inputLength,
		output,
		requiredBufSize,
		nullptr,
		FALSE);

	if(!error)
	{
		delete[] output;
		return returnWithError();
	}

	return output;
}

bool CFileVersionInfo::GetVersionInfo( const wchar_t* pFileName )
{
	DWORD dwHandle = 0, dwLen = 0;
	UINT BufLen = 0;
	LPWSTR lpData = 0, lpBuffer = 0;
	VS_FIXEDFILEINFO *pFileInfo = 0;	

	dwLen = GetFileVersionInfoSizeW ( pFileName, &dwHandle);		
	if (!dwLen)	
	{
		assert ( 0 && "VersionInfo           not found\n");
		return false;
	}
	lpData = (LPWSTR) new LPWSTR[ dwLen ];
	if (!lpData) 
	{		
		return false;
	}
	if (!GetFileVersionInfoW ( pFileName, dwHandle, dwLen, lpData ) )
	{
		assert ( 0 && "GetFileVersionInfo failed\n");
		delete[] lpData;
		return false;
	}

	if (!VerQueryValueW ( lpData, L"\\", (LPVOID*) &pFileInfo, (PUINT) &BufLen ) ) 
	{
		assert ( 0 && "VersionInfo           not found\n");
	}
	else 
	{
		m_iMajorVersion		= HIWORD(pFileInfo->dwFileVersionMS);
		m_MinorVersion		= LOWORD(pFileInfo->dwFileVersionMS);
		m_BuildNumber		= HIWORD(pFileInfo->dwFileVersionLS);
		m_RevisionNumber	= LOWORD(pFileInfo->dwFileVersionLS);		
	}
	
	if (!VerQueryValueW (lpData, L"\\StringFileInfo\\040904E4\\FileVersion",
			(LPVOID*) &lpBuffer, (PUINT) &BufLen)) 
	{
	    /* language ID 040904E4: U.S. English, char set = Windows, Multilingual */
		//assert ( 0 && "FileVersion           not found\n");		
	}
	else
	{
		char const *const utf8 = UTF16ToUTF8(lpBuffer);
		m_strFileVersion = utf8;
		delete[] utf8;
	}

	if (!VerQueryValueW (lpData, L"\\StringFileInfo\\040904E4\\LibToolFileVersion",
			(LPVOID*) &lpBuffer, (PUINT) &BufLen)) 
	{
	    /* language ID 040904E4: U.S. English, char set = Windows, Multilingual */
		//assert ( 0 && "LibToolFileVersion           not found\n");				
	}
	else
	{
		char const *const utf8 = UTF16ToUTF8(lpBuffer);
		m_strLibToolFileVersion = utf8;
		delete[] utf8;
	}
	
	delete[] lpData;

	return true;
}
