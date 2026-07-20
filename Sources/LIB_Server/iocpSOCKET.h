#ifndef iocpSOCKETH
#define iocpSOCKETH

#include <cassert>
#include <memory>
#include <queue>

#include <winsock.h>

#include "classHASH.h"
#include "classSTR.h"
#include "classSYNCOBJ.h"
#include "DLLIST.h"
#include "CDLList.h"
#include "classTIME.h"
#include "ioDataPOOL.h"

enum ePacketRECV
{
	eRESULT_PACKET_OK = 0,
	eRESULT_PACKET_DISCONNECT
};

class iocpSOCKET
{
public:
	void CloseSocket(void);

	iocpSOCKET();
	virtual ~iocpSOCKET();

	void LockSOCKET()
	{
		m_csSOCKET.Lock();
	}

	void UnlockSOCKET()
	{
		m_csSOCKET.Unlock();
	}

	void Init_SCOKET()
	{
		m_iSocketIDX = 0;
		m_Socket = INVALID_SOCKET;
		m_bWritable = true;
		m_bVerified = false;
		m_pSockNODE = NULL;
	}

	SOCKET Get_SOCKET()
	{
		return m_Socket;
	}

	char*  Get_IP()
	{
		return m_IP.Get();
	}

	DWORD  Get_CheckTIME()
	{
		return m_dwCheckTIME;
	}

	void Clear_LIST(void);

	ePacketRECV Recv_Start(void);
	ePacketRECV Recv_Complete(tagIO_DATA *pRecvDATA);

	bool Send_Start(classPACKET *pCPacket);
	bool Send_Complete(tagIO_DATA *pSendDATA);

	virtual bool Recv_Done(tagIO_DATA *pRecvDATA);
	virtual bool HandlePACKET(t_PACKETHEADER *pPacket) = 0;

	virtual WORD  E_SendP(t_PACKETHEADER *pPacket)
	{
		return pPacket->m_nSize;
	}

	virtual WORD  D_RecvH(t_PACKETHEADER *pPacket)
	{
		return pPacket->m_nSize;
	}

	virtual short D_RecvB(t_PACKETHEADER *pPacket)
	{
		return pPacket->m_nSize;
	}

	virtual WORD P_Length(t_PACKETHEADER *pPacket)
	{
		return pPacket->m_nSize;
	}

	classDLLNODE<tagIO_DATA> *Alloc_RecvIODATA(void)
	{
		classDLLNODE<tagIO_DATA> *pRecvDATA;

		pRecvDATA = CPoolRECVIO::GetInstance()->Pool_Alloc();
		if(pRecvDATA)
		{
			//ZeroMemory(&pRecvDATA->m_Overlapped, sizeof(OVERLAPPED));
			// 2003. 11. 12 반드시 0으로 초기화 !!!, 빼먹어서 Recv_Start에서 기존의 쓰레기 패킷 뒤에 추가로 받아졌다.
			CPoolRECVIO::GetInstance()->InitData(pRecvDATA);
			pRecvDATA->DATA.m_pCPacket = CPoolPACKET::GetInstance()->AllocNLock();
		}

		return pRecvDATA;
	}

	static void Free_RecvIODATA(tagIO_DATA *pRecvDATA)
	{
		assert(pRecvDATA->m_pCPacket->GetRefCnt() == 1);

		CPoolPACKET::GetInstance()->ReleaseOnly(pRecvDATA->m_pCPacket);
		CPoolRECVIO::GetInstance()->Pool_Free(pRecvDATA->m_pNODE);
	}

	classDLLNODE<tagIO_DATA> *Alloc_SendIODATA(classPACKET *pCPacket)
	{
		if(0 == pCPacket->GetLength())
		{
			pCPacket->SetLength(this->E_SendP(&pCPacket->m_HEADER));
		}

		classDLLNODE<tagIO_DATA> *pSendDATA;
		pSendDATA = CPoolSENDIO::GetInstance()->Pool_Alloc();
		if(nullptr != pSendDATA)
		{
			//ZeroMemory(&pSendDATA->m_Overlapped, sizeof(OVERLAPPED));
			// 2003. 11. 12 반드시 0으로 초기화 !!!, 빼먹어서 Recv_Start에서 기존의 쓰레기 패킷 뒤에 추가로 받아졌다.
			//pSendDATA->m_dwIOBytes = 0;

			//pSendDATA->m_IOmode = ioWRITE;
			//pSendDATA->m_pCPacket = pCPacket;
			CPoolSENDIO::GetInstance()->InitData(pSendDATA);
			pSendDATA->DATA.m_pCPacket = pCPacket;

			pCPacket->IncRefCnt();

			assert(pSendDATA->DATA.m_IOmode == ioWRITE);
			assert(pSendDATA->DATA.m_dwIOBytes == 0);
		}
		return pSendDATA;
	}

	static void  Free_SendIODATA(tagIO_DATA *pSendDATA)
	{
		// pSendDATA->m_pCPacket->m_pIOData = pSendDATA;

		CPoolPACKET::GetInstance()->DecRefCount(pSendDATA->m_pCPacket);
		CPoolSENDIO::GetInstance()->Pool_Free(pSendDATA->m_pNODE);
	}

public:
	SOCKET		m_Socket;
	int			m_iSocketIDX;
	CStrVAR		m_IP;
	t_HASHKEY	m_HashKeyIP;

	bool		m_bVerified;						// 맞는 클라이언트에서 접속된거냐 ??
	CDLList<iocpSOCKET*>::tagNODE *m_pSockNODE;
	DWORD		m_dwConnTIME;						// 접속된 시간

private:
	ePacketRECV Recv_Continue(tagIO_DATA *pRecvDATA);

	bool Send_Continue(tagIO_DATA *pSendDATA);

	CCriticalSection			m_csSOCKET;

protected:
	CCriticalSection			m_csSendQ;
	CCriticalSection			m_csRecvQ;

	// Client에게 보낼 데이타 리스트.
	classDLLIST<tagIO_DATA> m_SendList;
	bool m_bWritable; // WriteFile에 보낼수 있냐 ?

	// Client에서 받은 데이타 리스트.
	classDLLIST<tagIO_DATA> m_RecvList;
	DWORD m_dwCheckTIME; // 마지막 보내기 시도한 시간
};
#endif
