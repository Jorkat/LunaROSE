#ifndef	__CDATAPOOL_H
#define	__CDATAPOOL_H
#include "crtdbg.h"
#include "SLLIST.h"
#include "classSYNCOBJ.h"
#include "classSTR.h"
#include "classLOG.h"
#include <new>
//-------------------------------------------------------------------------------------------------

template <class t_DATA>
class CDataPOOL: public CCriticalSection
{
protected:
	struct CDataNODE: public t_DATA
	{
		bool		 m_POOL_bUsed;
		CDataNODE	*m_POOL_pNextNODE;
		CDataNODE()
		{
			m_POOL_bUsed = false;
			m_POOL_pNextNODE = nullptr;
		}
	};

	UINT					m_uiTotalDataCNT;
	UINT					m_uiIncDataCNT;
	int						m_iUsedCNT;

	CStrVAR					m_PoolName;
	classSLLIST<CDataNODE*> m_BlockLIST;
	CDataNODE			   *m_pHeadNODE;
	CDataNODE			   *m_pTailNODE;

	CDataNODE *Create(UINT uiDataCNT)
	{
		CDataNODE *pDataBLOCK = nullptr;

		try
		{
			pDataBLOCK = new CDataNODE[uiDataCNT];
		}
		catch (const std::bad_alloc&)
		{
			g_LOG.CS_ODS(
				0xffff,
				">>>> ERROR:: Pool[ %s ] allocation failed. "
				"Requested: %u, total: %u, used: %d\n",
				m_PoolName.Get(),
				uiDataCNT,
				m_uiTotalDataCNT,
				m_iUsedCNT
			);

			return nullptr;
		}

		m_BlockLIST.AllocNAppend(pDataBLOCK);
		m_uiTotalDataCNT += uiDataCNT;

		CDataNODE *pNextNODE = nullptr;
		CDataNODE *pDataNODE = nullptr;

		m_pTailNODE = &pDataBLOCK[uiDataCNT - 1];
		m_pTailNODE->m_POOL_pNextNODE = nullptr;
		for(int iC = uiDataCNT - 1; iC >= 0; iC--)
		{
			pDataNODE = &pDataBLOCK[iC];

			pDataNODE->m_POOL_pNextNODE = pNextNODE;
			pNextNODE = pDataNODE;
		}

		g_LOG.CS_ODS(
			0xffff,
			">>>> Pool[ %s ] Increase %u data, total: %u, used: %d, free: %u\n",
			m_PoolName.Get(),
			uiDataCNT,
			m_uiTotalDataCNT,
			m_iUsedCNT,
			m_uiTotalDataCNT - static_cast<UINT>(m_iUsedCNT)
		);


		return pDataBLOCK;
	}

public:
	char *GetPoolNAME()
	{
		return	m_PoolName.Get();
	}
	int	  GetUsedCNT()
	{
		return	m_iUsedCNT;
	}


	CDataPOOL(char *szName, UINT uiInitDataCNT, UINT uiIncDataCNT): CCriticalSection(4000)
	{
		m_PoolName.Set(szName);

		m_uiIncDataCNT = uiIncDataCNT;
		m_uiTotalDataCNT = 0;
		m_iUsedCNT = 0;

		m_pTailNODE = nullptr;
		m_pHeadNODE = this->Create(uiInitDataCNT);
	}
	virtual ~CDataPOOL()
	{
		classSLLNODE< CDataNODE* > *pBlockNODE;

		pBlockNODE = m_BlockLIST.DeleteHead();
		while(pBlockNODE)
		{
			SAFE_DELETE_ARRAY(pBlockNODE->DATA);
			SAFE_DELETE(pBlockNODE);
			pBlockNODE = m_BlockLIST.DeleteHead();
		}
	}

	t_DATA* Pool_Alloc()
	{
		t_DATA* pDATA = nullptr;

		this->Lock();

		if (m_pHeadNODE != nullptr)
		{
			CDataNODE* allocatedNode = m_pHeadNODE;

			if (allocatedNode->m_POOL_pNextNODE == nullptr)
			{
				allocatedNode->m_POOL_pNextNODE =
					this->Create(m_uiIncDataCNT);
			}

			allocatedNode->m_POOL_bUsed = true;
			m_pHeadNODE = allocatedNode->m_POOL_pNextNODE;

			pDATA = static_cast<t_DATA*>(allocatedNode);
			++m_iUsedCNT;
		}
		else
		{
			g_LOG.CS_ODS(
				0xffff,
				">>>> ERROR:: Pool[ %s ] exhausted. Total: %u, Used: %d\n",
				m_PoolName.Get(),
				m_uiTotalDataCNT,
				m_iUsedCNT
			);
		}

		this->Unlock();

		return pDATA;
	}

	void	Pool_Free(t_DATA *pDATA)
	{
		CDataNODE *pDataNODE = reinterpret_cast<CDataNODE*>(pDATA);
		this->Lock();
		{
			// 두번 풀리는거 체크...
			if(pDataNODE->m_POOL_bUsed)
			{
				pDataNODE->m_POOL_bUsed = false;

				this->m_iUsedCNT--;
				_ASSERT(this->m_iUsedCNT >= 0);

				this->m_pTailNODE->m_POOL_pNextNODE = pDataNODE;
				this->m_pTailNODE = pDataNODE;
				this->m_pTailNODE->m_POOL_pNextNODE = nullptr;

				if(nullptr == this->m_pHeadNODE)
				{
					this->m_pHeadNODE = this->m_pTailNODE;
				}
			}
			else
			{
				g_LOG.CS_ODS(
					0xffff,
					">>>> ERROR:: Pool[ %s ] duplicated free, used: %d, total: %u\n",
					m_PoolName.Get(),
					m_iUsedCNT,
					m_uiTotalDataCNT
				);
			}
		}
		this->Unlock();
	}
};
#endif