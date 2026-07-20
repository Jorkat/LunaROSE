#include "iocpSOCKET.h"

#include <cassert>

#include <winsock.h>
#include <windows.h>

#include <tchar.h>

#include "classLOG.h"
#include "classIOCP.h"
#include "classUTIL.h"
#include "LIB_Util.h"

iocpSOCKET::iocpSOCKET()
	: m_Socket(INVALID_SOCKET)
	, m_iSocketIDX(0)
	, m_IP()
	, m_HashKeyIP()
	, m_bVerified(false)
	, m_dwConnTIME(0)
	, m_csSOCKET()
	, m_csSendQ()
	, m_csRecvQ(4000)
	, m_SendList()
	, m_bWritable(true)
	, m_RecvList()
	, m_dwCheckTIME(0)
{
	this->Init_SCOKET();
}

iocpSOCKET::~iocpSOCKET()
{
	assert(0 == this->m_iSocketIDX);
	this->Clear_LIST();
}


void iocpSOCKET::CloseSocket(void)
{
	if(m_Socket != INVALID_SOCKET)
	{
		struct linger li = {0, 0};

		#ifndef SD_BOTH // From winsock2.h
			#define SD_BOTH         0x02
		#endif
		::shutdown(m_Socket, SD_BOTH);
		::setsockopt(m_Socket, SOL_SOCKET, SO_LINGER, (char *)&li, sizeof(li));
		::closesocket(m_Socket);

		m_Socket = INVALID_SOCKET;
		m_bWritable = false;
	}
}

void iocpSOCKET::Clear_LIST(void)
{
	classDLLNODE<tagIO_DATA> *pNode;

	m_csRecvQ.Lock();
	{
		pNode = m_RecvList.GetHeadNode();
		while(pNode)
		{
			m_RecvList.DeleteNode( pNode );
			this->Free_RecvIODATA( &pNode->DATA );

			pNode = m_RecvList.GetHeadNode();
		}
	}
	m_csRecvQ.Unlock();

	m_csSendQ.Lock();
	{
		pNode = m_SendList.GetHeadNode();
		while(pNode)
		{
			m_SendList.DeleteNode( pNode );
			this->Free_SendIODATA ( &pNode->DATA );

			pNode = m_SendList.GetHeadNode();
		}
	}
	m_csSendQ.Unlock();
}

//-------------------------------------------------------------------------------------------------
// pRecvNode에 이어 받기.
ePacketRECV iocpSOCKET::Recv_Continue (tagIO_DATA *pRecvDATA)
{
	assert(pRecvDATA->m_pCPacket->GetRefCnt() == 1);

	if(0 == ::ReadFile(
		(HANDLE)m_Socket,
		&pRecvDATA->m_pCPacket->m_pDATA[pRecvDATA->m_dwIOBytes],
		MAX_PACKET_SIZE - pRecvDATA->m_dwIOBytes,
		nullptr,
		(LPOVERLAPPED)pRecvDATA))
	{
		// Function failed ..
		if(ERROR_IO_PENDING != ::GetLastError())
		{
			DWORD dwCode = ::GetLastError ();
			g_LOG.CS_ODS(
				0xffff,
				"$$$$$$$  SocketIDX: %d : ERROR[ %d:%s ] ::: ReadFile \n",
				this->m_iSocketIDX,
				dwCode,
				CUtil::GetLastErrorMsg(dwCode));

			// false 리턴하면 접속 끊자...
			return eRESULT_PACKET_DISCONNECT;
		}
	}

	return eRESULT_PACKET_OK;
}

// 새로 받기.
ePacketRECV iocpSOCKET::Recv_Start (void)
{
	classDLLNODE<tagIO_DATA> *pRecvNODE;

	pRecvNODE = this->Alloc_RecvIODATA();
	if(NULL == pRecvNODE)
		return eRESULT_PACKET_DISCONNECT;

	assert(pRecvNODE->DATA.m_IOmode == ioREAD);
	assert(pRecvNODE->DATA.m_dwIOBytes == 0);

	return this->Recv_Continue( &pRecvNODE->DATA );
}

// CThreadWORKER::STATUS_ReturnTRUE () 에서만 호출된다.
ePacketRECV iocpSOCKET::Recv_Complete (tagIO_DATA *pRecvDATA)
{
	ePacketRECV eResult;

	g_LOG.CS_ODS(0xffff, "Locking socket...\n");
	this->LockSOCKET();

	if(pRecvDATA->m_dwIOBytes < sizeof(t_PACKETHEADER))
	{
		// 디코딩 안된 패킷의 크기는 0이다 !!!
		assert(0 == pRecvDATA->m_pCPacket->GetLength());
		// 최소 크기의 패킷 받기...
		eResult = this->Recv_Continue(pRecvDATA);	// 이어 받기.
		goto _JUMP_RETURN;
	}

	if(0 == pRecvDATA->m_pCPacket->GetLength())
	{
		// 디코딩 안되어 있다면...
		pRecvDATA->m_pCPacket->SetLength(this->D_RecvH(&pRecvDATA->m_pCPacket->m_HEADER));
		if(0 == pRecvDATA->m_pCPacket->GetLength())
		{
			// 블랙 리스트에 ip 등록...
			g_LOG.CS_ODS(
				0xffff,
				"*** ERROR: Decode recv packet header1, IP[ %s ]\n",
				this->m_IP.Get());

			g_LOG.CS_ODS(0xffff, "Unlocking socket...\n");
			this->UnlockSOCKET();

			this->Free_RecvIODATA(pRecvDATA);

			return eRESULT_PACKET_DISCONNECT;
		}
	}

	//재영추가.... 한번에 많은 패킷이 들어오면 끊어버린다..
	/*if(pRecvDATA->m_pCPacket->GetLength() > MAX_PACKET_SIZE)
	{
		// 블랙 리스트에 ip 등록...
		g_LOG.CS_ODS(
			0xffff,
			"*** ERROR: MAX_PACKET_SIZE  recv packet header1, IP[ %s ]\n",
			this->m_IP.Get());

		g_LOG.CS_ODS(0xffff, "Unlocking socket...\n");
		this->UnlockSOCKET();
		assert(pRecvDATA == m_RecvList.front().get());
		m_RecvList.pop();
		//this->Free_RecvIODATA(pRecvDATA);

		return eRESULT_PACKET_DISCONNECT;
	}*/

	assert( pRecvDATA->m_pCPacket->GetLength() >= sizeof(t_PACKETHEADER) );

	// 2006.06.13/김대성/수정 - 해커가 고의로 pRecvDATA->m_pCPacket->GetLength() < sizeof(t_PACKETHEADER) 인 패킷을 보낼경우
	// 서버가 멈추는 것을 막기위해서 _ASSERT() 대신 에러리턴
	/*if(pRecvDATA->m_pCPacket->GetLength() < sizeof(t_PACKETHEADER))
	{
		g_LOG.CS_ODS(0xffff, "Unlocking socket...\n");
		this->UnlockSOCKET();
		assert(pRecvDATA == m_RecvList.front().get());
		m_RecvList.pop();
		//this->Free_RecvIODATA(pRecvDATA);

		// 블랙 리스트에 ip 등록...
		g_LOG.CS_ODS(0xffff, "*** ERROR: pRecvDATA->m_pCPacket->GetLength() < sizeof(t_PACKETHEADER), IP[ %s ]\n", this->m_IP.Get());
		return eRESULT_PACKET_DISCONNECT;
	}*/

	if((short)pRecvDATA->m_dwIOBytes < pRecvDATA->m_pCPacket->GetLength())
	{
		eResult = this->Recv_Continue(pRecvDATA);	// 이어 받기.
		goto _JUMP_RETURN;
	}
	else if((short)pRecvDATA->m_dwIOBytes == pRecvDATA->m_pCPacket->GetLength())
	{
		g_LOG.CS_ODS(0xffff, "Unlocking socket...\n");
		this->UnlockSOCKET();
		if(!this->Recv_Done(pRecvDATA))		// Free_RecvIODATA( pRecvDATA ); <-- Recv_done에서 호출되어옴
			return eRESULT_PACKET_DISCONNECT;//false;
		return this->Recv_Start();	// RecvComplete
	}

	// 뭉쳐온 패킷 분리.
	t_PACKETHEADER *pHEADER;
	short	nRemainBytes, nPacketSIZE;

	assert(pRecvDATA->m_dwIOBytes > pRecvDATA->m_pCPacket->GetLength());

	nRemainBytes = (short)pRecvDATA->m_dwIOBytes - pRecvDATA->m_pCPacket->GetLength();
	pHEADER = (t_PACKETHEADER*)&pRecvDATA->m_pCPacket->m_pDATA[pRecvDATA->m_pCPacket->GetLength()];
	nPacketSIZE = 0;
	while(nRemainBytes >= sizeof(t_PACKETHEADER))
	{
		if(0 == nPacketSIZE)
		{
			nPacketSIZE = this->D_RecvH(pHEADER);
			if(0 == nPacketSIZE)
			{
				g_LOG.CS_ODS(0xffff, "Unlocking socket...\n");
				this->UnlockSOCKET();

				this->Free_RecvIODATA(pRecvDATA);
				g_LOG.CS_ODS(0xffff, "*** ERROR: Decode recv packet header2, IP[ %s ]\n", this->m_IP.Get());

				// 블랙 리스트에 ip 등록...
				return eRESULT_PACKET_DISCONNECT;
			}
		}

		if(nRemainBytes == nPacketSIZE)
		{
			g_LOG.CS_ODS(0xffff, "Unlocking socket...\n");
			this->UnlockSOCKET();
			if(!this->Recv_Done(pRecvDATA))		// 완성 패킷 추가, Free_RecvIODATA( pRecvDATA );<-- Recv_done에서 호출되어옴
				return eRESULT_PACKET_DISCONNECT;//false;
			return this->Recv_Start();					// 새로 받기. :: RecvComplete
		}

		if(nRemainBytes > nPacketSIZE)
		{
			// 추가 패킷이 있다.
			nRemainBytes -= nPacketSIZE;
			pHEADER = (t_PACKETHEADER*)(pHEADER->m_pDATA + nPacketSIZE);
			nPacketSIZE = 0;
		}
		else
			break;
	}

	// 모자란 부분을 다시 읽어들일 데이타 생성.
	classDLLNODE<tagIO_DATA> *pNewNODE;
	pNewNODE = this->Alloc_RecvIODATA();
	if(pNewNODE)
	{
		if(nRemainBytes >= sizeof(t_PACKETHEADER))
		{
			// Header가 Decoding 되었다..
			pNewNODE->DATA.m_pCPacket->SetLength(this->P_Length(pHEADER));
		}

		pNewNODE->DATA.m_dwIOBytes = nRemainBytes;
		::CopyMemory(pNewNODE->DATA.m_pCPacket->m_pDATA, pHEADER, nRemainBytes);

		// 앞부분의 완성 패킷등록.
		pRecvDATA->m_dwIOBytes -= nRemainBytes;

		g_LOG.CS_ODS(0xffff, "Unlocking socket...\n");
		this->UnlockSOCKET();
		if(!this->Recv_Done(pRecvDATA))
		{
			// 2003. 11. 04 밑에 함수 추가... 빼먹어서 메모리 흘렸었음..
			this->Free_RecvIODATA(&pNewNODE->DATA);
			return eRESULT_PACKET_DISCONNECT;//false;
		}

		return this->Recv_Continue(&pNewNODE->DATA);	    			// 이어 받기.
	}

	eResult = eRESULT_PACKET_DISCONNECT;//false;

_JUMP_RETURN:
	g_LOG.CS_ODS(0xffff, "Unlocking socket...\n");
	this->UnlockSOCKET();
	return eResult;
}

// pSendNode에 이어 보내기.
bool iocpSOCKET::Send_Continue(tagIO_DATA *pSendDATA)
{
	// 2004. 10. 25 아래 assert 걸림...
	// assert( pSendDATA->m_pCPacket->GetLength() > pSendDATA->m_dwIOBytes );
	if(pSendDATA->m_dwIOBytes >= pSendDATA->m_pCPacket->GetLength())
	{
		g_LOG.CS_ODS(
			0xffff,
			">>ERROR:: Sending packet: Len: %d, completed: %d, IP:%s\n",
			pSendDATA->m_pCPacket->GetLength(),
			pSendDATA->m_dwIOBytes,
			Get_IP());

		return false;
	}

	// 2003. 12. 16
	// 한번 보내면 전송 완료 되던가, 오류가 발생되어 접속을 끊던가...
	this->m_bWritable = false;
	if(0 == ::WriteFile(
		(HANDLE)m_Socket,
		&pSendDATA->m_pCPacket->m_pDATA[pSendDATA->m_dwIOBytes],
		pSendDATA->m_pCPacket->GetLength() - pSendDATA->m_dwIOBytes,
		NULL,
		(LPOVERLAPPED)pSendDATA))
	{
		// Function failed ..
		if(ERROR_IO_PENDING != GetLastError())
		{
			DWORD dwCode = GetLastError();
			g_LOG.CS_ODS(
				0xffff,
				"$$$$$$$  SocketIDX: %d : ERROR[ %d:%s ] ::: WriteFile \n",
				m_iSocketIDX,
				dwCode,
				CUtil::GetLastErrorMsg(dwCode));

			// false 리턴하면 접속 끊자...
			return false;
		}
	}
	this->m_dwCheckTIME = ::timeGetTime();	// 마지막으로 보내기 시도한 시간...

	return true;
}

bool iocpSOCKET::Send_Start(classPACKET *pCPacket)
{
	if(m_Socket == INVALID_SOCKET)
		return false;

	classDLLNODE<tagIO_DATA> *pSendNODE;
	pSendNODE = this->Alloc_SendIODATA( pCPacket );
	if(NULL == pSendNODE)
		return false;

	assert(pSendNODE->DATA.m_pCPacket->GetRefCnt() >= 1);
	assert(pSendNODE->DATA.m_pCPacket == pCPacket);
	assert(pSendNODE->DATA.m_IOmode == ioWRITE);
	assert(pSendNODE->DATA.m_dwIOBytes == 0);

	assert(pSendNODE->DATA.m_pCPacket->GetLength() >= sizeof(t_PACKETHEADER));
	assert(pSendNODE->DATA.m_pCPacket->GetLength() <= MAX_PACKET_SIZE);

	m_csSendQ.Lock();
	{
		m_SendList.AppendNode(pSendNODE);

		if(m_bWritable)
		{
			pSendNODE = m_SendList.GetHeadNode();

			if(!Send_Continue(&pSendNODE->DATA))
			{
				{
					m_csSendQ.Unlock();
					CloseSocket();
					return false;
				}
			}
			else
			{
				int iQedCnt = m_SendList.GetNodeCount();
				if(iQedCnt > 100)
				{
					// 보내기 시도한 후 아직까지 다음 패킷을 보내지 못하고 있는넘...
					// 패킷을 쌓놓고 있다면 짤라버려야지...
					DWORD dwPassTime = ::timeGetTime() - this->m_dwCheckTIME;
					if(dwPassTime >= 30 * 1000 || iQedCnt > 1000)
					{
						g_LOG.CS_ODS(
							0xffff,
							">>Sending timeout: packet: %d, time: %d, IP:%s\n",
							iQedCnt,
							dwPassTime,
							this->Get_IP());

						CloseSocket();

						//return false;
					}
				}
			}
		}
	}

	m_csSendQ.Unlock();
	return true;
}


//-------------------------------------------------------------------------------------------------
// CThreadWORKER::STATUS_ReturnTRUE() 에서만 호출된다.
bool iocpSOCKET::Send_Complete(tagIO_DATA *pSendDATA)
{
	m_csSendQ.Lock();
	{
		if(0 == this->m_iSocketIDX) // 종료됐다.
		{
			// 2004. 10. 3... 
			// _ASSERT( pHeadNODE == pSendDATA->m_pNODE ); 에서 오류 발생...
			// m_SendList.GetNodeCount() == 0인상태에서 이리로 들어 와서 뻑~~~
			// this->m_iSocketIDX = 0이고, pSendDATA->m_dwIOBytes = 0, pSendDATA->m_pCPacket->GetLength()=10 이었지만
			// 아래 pSendDATA->m_dwIOBytes == (WORD)pSendDATA->m_pCPacket->GetLength() 조건을 통과했다.
			// 1. 동시에 여러 워커 쓰래드에서 IO발생
			// 2. 다른 워커쓰레드에서 소켓 종료 => m_SendList초기화 됨( 현재 pSendDATA가 Pool에 반납됨 )
			// 3. 현재 워커쓰레드에서 이 함수로 접근pSendDATA->m_dwIOBytes == (WORD)pSendDATA->m_pCPacket->GetLength() 조건통과.
			// 4. 다른 소켓에의해 pSendDATA가 할당, 최기화됨.
			// 5. 현재 워커쓰레드 뻑~~~
			m_csSendQ.Unlock();
			return false;
		}

		this->m_bWritable = true;
		if(pSendDATA->m_dwIOBytes == pSendDATA->m_pCPacket->GetLength()) // 전체 전송 완료..
		{
			// ** 아래 라인에서 m_SendList에서 pSendNode를 삭제하는 과정에서
			//    오류가 난것은 pUSER가 이미 접속종료되어 ClearIOList() 함수를
			//    실행하여 m_SendList가 이미 비어있기 때문이다.
			classDLLNODE<tagIO_DATA> *pHeadNODE = m_SendList.GetHeadNode();
			assert(pHeadNODE == pSendDATA->m_pNODE);

			classDLLNODE<tagIO_DATA> *pNextNODE = m_SendList.GetNextNode(pHeadNODE);
			if(pNextNODE)
				assert(pNextNODE->DATA.m_dwIOBytes == 0);

			m_SendList.DeleteNode(pSendDATA->m_pNODE);
			this->Free_SendIODATA(pSendDATA);

			classDLLNODE<tagIO_DATA> *pSendNODE = m_SendList.GetHeadNode();
			if(pSendNODE)
			{
				assert(pSendNODE->DATA.m_dwIOBytes == 0);

				if(!this->Send_Continue(&pSendNODE->DATA))
				{
					m_csSendQ.Unlock();
					return false;
				}
			}
		}
		else if(pSendDATA->m_dwIOBytes < pSendDATA->m_pCPacket->GetLength()) // 부분 전송됨..
		{
			if(!this->Send_Continue(pSendDATA))
			{
				m_csSendQ.Unlock();
				return false;
			}
		}
		else
		{
			assert(false);
		}
	}
	m_csSendQ.Unlock();

	return true;
}

bool iocpSOCKET::Recv_Done(tagIO_DATA *pRecvDATA)
{
	// 바로 처리하는 함수...
	//assert(pRecvDATA == m_RecvList.front().get());
	t_PACKETHEADER *pPacket = (t_PACKETHEADER*)&pRecvDATA->m_pCPacket->m_pDATA;

	do
	{
		short const nTotalPacketLEN = this->D_RecvB(pPacket);
		if(!nTotalPacketLEN)
		{
			// 패킷이 변조되어 왔다.
			// 헤킹인가 ???
			g_LOG.CS_ODS(
				0xffff,
				"*** ERROR: Decode recv packet body, IP[ %s ]\n",
				this->m_IP.Get());

			this->Free_RecvIODATA(pRecvDATA);

			// 블랙 리스트에 ip 등록...

			return false;
		}

		if(!this->HandlePACKET(pPacket))
		{
			this->Free_RecvIODATA(pRecvDATA);
			return false;
		}

		pRecvDATA->m_dwIOBytes -= nTotalPacketLEN;
		pPacket = (t_PACKETHEADER*)(pPacket->m_pDATA + nTotalPacketLEN);
	} while(pRecvDATA->m_dwIOBytes);

	this->Free_RecvIODATA(pRecvDATA);

	return true;
}
