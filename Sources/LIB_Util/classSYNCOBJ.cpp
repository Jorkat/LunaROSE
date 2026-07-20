#include <windows.h>
#include <tchar.h>
#include <crtdbg.h>
#include "classSYNCOBJ.h"

classEVENT::classEVENT(
	LPSECURITY_ATTRIBUTES lpEventAttributes,
	BOOL bManualReset,
	BOOL bInitialState,
	LPCTSTR lpName )
{
	m_Event = CreateEvent( lpEventAttributes, bManualReset, bInitialState, lpName );
	if ( NULL == m_Event )
	{
		DWORD dwErrCode;
		dwErrCode = ::GetLastError ();
	} else {
		_ASSERT( ::GetLastError() != ERROR_ALREADY_EXISTS );
	}
}

classEVENT::~classEVENT ()
{
	if ( m_Event )
	{
		::CloseHandle( m_Event );
	}
}

DWORD classEVENT::WaitFor ( DWORD dwMilliseconds )
{
	DWORD dwResult = ::WaitForSingleObject( m_Event, dwMilliseconds );
	return dwResult;
}
void classEVENT::SetEvent(void)
{
	::SetEvent( m_Event );
}
void classEVENT::ResetEvent(void)
{
	::ResetEvent( m_Event );
}

CCriticalSection::CCriticalSection( DWORD dwSpinCount )
{
	if ( dwSpinCount ) {
		::InitializeCriticalSectionAndSpinCount( &m_CS, dwSpinCount );
	} else
		::InitializeCriticalSection( &m_CS );		
}
