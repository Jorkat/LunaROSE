
#include <windows.h>
#include <tchar.h>
#include <crtdbg.h>
#include "classLOG.h"
#include "CIocpTHREAD.h"

//-------------------------------------------------------------------------------------------------
CIocpTHREAD::CIocpTHREAD (bool bCreateSuspended)
	: classTHREAD( bCreateSuspended )
	, m_hIOCP(nullptr)
	, m_iThreadNO(0)
{
}

//-------------------------------------------------------------------------------------------------
void CIocpTHREAD::Execute()
{
	DWORD		 dwBytesIO = 0;
	DWORD        dwCompletionKey = 0;
	LPOVERLAPPED lpOverlapped = nullptr;

	g_LOG.CS_ODS(
		0xffff,
		">>>> CIocpTHREAD::Execute() ThreadID: %d(0x%x),  WorkerNO: %d \n",
		this->ThreadID,
		this->ThreadID,
		m_iThreadNO);

	while(!Terminated)
	{
		if(0 == GetQueuedCompletionStatus(
			m_hIOCP,
			&dwBytesIO,
			&dwCompletionKey,
			(LPOVERLAPPED *)&lpOverlapped,
			INFINITE))
		{
			/*
			If *lpOverlapped is NULL and the function does not dequeue a completion packet from the completion port,
			the RETURN VALUE IS ZERO.
			The function does not store information in the variables pointed to by
			the lpNumberOfBytesTransferred and lpCompletionKey parameters.

			If *lpOverlapped is not NULL and the function dequeues a completion packet
			for a failed I/O operation from the completion port, the RETURN VALUSE IS ZERO.
			return value is zero.
			The function stores information in the variables pointed to by
			lpNumberOfBytesTransferred, lpCompletionKey, and lpOverlapped.
			*/
			if(nullptr != lpOverlapped)
			{
				// 소켓 종료
				DWORD dwErrCODE = ::GetLastError();

				// ErrorCode == 64
				// 지정된 네트웍크 이름을 더이상 사용할수 없습니다 == 클라이언트 끊어진 상태.
				if(dwErrCODE != 64)
				{
					LPVOID lpMsgBuf = nullptr;
					if(::FormatMessage(
						FORMAT_MESSAGE_ALLOCATE_BUFFER |
						FORMAT_MESSAGE_FROM_SYSTEM |
						FORMAT_MESSAGE_IGNORE_INSERTS,
						nullptr,
						dwErrCODE,
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
						(LPTSTR)&lpMsgBuf,
						0,
						nullptr))
					{
						// Display the string.
						g_LOG.CS_ODS(
							0xffff,
							"$$$$ ERROR[%d]:: socketIdx: %d, %s\n",
							dwErrCODE,
							dwCompletionKey,
							lpMsgBuf);

						::LocalFree(lpMsgBuf);
					}
				}

				STATUS_ReturnFALSE(lpOverlapped, dwCompletionKey);
				continue;
			}

			// 시스템 오류 !!!
			g_LOG.CS_ODS(
				0xffff,
				"* ERROR:: WorkerThread ID: %d(0x%x),  WorkerNO: %d : lpOverlapped == NULL \n",
				this->ThreadID,
				this->ThreadID,
				m_iThreadNO);
			break;
		}

		if(0 == dwBytesIO)
		{
			g_LOG.CS_ODS(0xffff, "Returning false...\n");
			STATUS_ReturnFALSE(lpOverlapped, dwCompletionKey);
			continue;
		}
		if((int)dwBytesIO == -1)
		{
			// 0 == dwCompletionKey
			// IOCP is freed ?
			g_LOG.CS_ODS(
				0xffff,
				"* Break:: WorkerThread ID: %d(0x%x),  WorkerNO: %d : dwBytesIO == -1 \n",
				this->ThreadID,
				this->ThreadID,
				m_iThreadNO);
			break;
		}

		g_LOG.CS_ODS(0xffff, "Returning true...\n");
		STATUS_ReturnTRUE(lpOverlapped, dwCompletionKey, dwBytesIO);
	}

	g_LOG.CS_ODS(
		0xffff,
		"<<<< CIocpTHREAD::Execute() ThreadID: %d(0x%x),  WorkerNO: %d \n",
		this->ThreadID,
		this->ThreadID,
		m_iThreadNO);
}

bool CIocpTHREAD::Init (HANDLE hIOCP, int iThreadNO)
{
    m_hIOCP = hIOCP;
    m_iThreadNO = iThreadNO;

    return true;
}

void CIocpTHREAD::Free (void)
{
    this->Terminate ();

	g_LOG.CS_ODS(
		0xffff,
		">>> CIocpTHREAD::Free ThreadID: %d(0x%x),  WorkerNO: %d \n",
		this->ThreadID,
		this->ThreadID,
		m_iThreadNO);

	do {
        if ( 0 == ::PostQueuedCompletionStatus( m_hIOCP, -1, 0, NULL) ) {
            g_LOG.CS_ODS(
				0xffff,
				"ThreadWORKER::Free() PostQueuedCompletionStatus() return 0"
				", LastERROR: %d(0x%x)",
				GetLastError(),
				GetLastError());
			break;
        }
	} while( !this->IsFinished() ) ;

	g_LOG.CS_ODS(
		0xffff,
		"<<< CIocpTHREAD::Free ThreadID: %d(0x%x),  WorkerNO: %d \n",
		this->ThreadID,
		this->ThreadID,
		m_iThreadNO);
}
