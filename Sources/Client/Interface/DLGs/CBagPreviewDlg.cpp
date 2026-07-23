#include "stdafx.h"
#include "CBagPreviewDlg.h"

#include "../it_mgr.h"
#include "SubClass/CBagPreviewListItem.h"

#include <ZListBox.h>
#include <TPane.h>
#include <TScrollBar.h>
#include <Common/io_stb.h>
#include <System/CGame.h>

CBagPreviewDlg::CBagPreviewDlg()
    : m_iBagID(0)
{
}

CBagPreviewDlg::~CBagPreviewDlg()
{
}

unsigned int CBagPreviewDlg::Process(
    UINT uiMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    if (!IsVision())
        return 0;

    if (uiMsg == WM_MOUSEWHEEL)
    {
        CWinCtrl* pListCtrl =
            FindChildInPane(
                IID_PANE_REWARDS,
                IID_ZLIST_REWARDS
            );

        if (pListCtrl &&
            pListCtrl->GetControlType() == CTRL_ZLISTBOX)
        {
            POINT ptMouse;
            CGame::GetInstance().Get_MousePos(ptMouse);

            if (pListCtrl->IsInside(ptMouse.x, ptMouse.y))
            {
                CZListBox* pList =
                    (CZListBox*)pListCtrl;

                int iNewValue = pList->GetValue();

                const short nWheelDelta =
                    GET_WHEEL_DELTA_WPARAM(wParam);

                if (nWheelDelta > 0)
                {
                    --iNewValue;
                }
                else if (nWheelDelta < 0)
                {
                    ++iNewValue;
                }

                pList->SetValue(iNewValue);

                CWinCtrl* pScrollCtrl =
                    FindChildInPane(
                        IID_PANE_REWARDS,
                        IID_SCROLL_REWARDS
                    );

                if (pScrollCtrl &&
                    pScrollCtrl->GetControlType() == CTRL_SCROLLBAR)
                {
                    CTScrollBar* pScrollBar =
                        (CTScrollBar*)pScrollCtrl;

                    pScrollBar->SetValue(
                        pList->GetValue()
                    );
                }

                return uiMsg;
            }
        }
    }

    unsigned int uiProcessID =
        CTDialog::Process(uiMsg, wParam, lParam);

    if (uiProcessID)
    {
        switch (uiMsg)
        {
        case WM_LBUTTONUP:
            if (On_LButtonUP(uiProcessID))
                return uiMsg;
            break;

        case WM_LBUTTONDOWN:
            if (On_LButtonDN(uiProcessID))
                return uiMsg;
            break;

        default:
            break;
        }

        return uiMsg;
    }

    return 0;
}

void CBagPreviewDlg::Draw()
{
    if (!IsVision())
        return;

    CTDialog::Draw();
}

void CBagPreviewDlg::Show()
{
    CTDialog::Show();

    LoadRewards();
}

void CBagPreviewDlg::Hide()
{
    CTDialog::Hide();
}

void CBagPreviewDlg::SetBagID(int iBagID)
{
    m_iBagID = iBagID;
}

int CBagPreviewDlg::GetBagID() const
{
    return m_iBagID;
}

bool CBagPreviewDlg::On_LButtonUP(
    unsigned int uiControlID)
{
    switch (uiControlID)
    {
    case IID_BTN_CLOSE:
        Hide();
        return true;

    default:
        break;
    }

    return false;
}

bool CBagPreviewDlg::On_LButtonDN(
    unsigned int uiControlID)
{
    return false;
}

CWinCtrl* CBagPreviewDlg::FindChildInPane(
    unsigned int uiPaneID,
    unsigned int uiChildID)
{
    CWinCtrl* pCtrl = Find(uiPaneID);

    if (pCtrl &&
        pCtrl->GetControlType() == CTRL_PANE)
    {
        CTPane* pPane =
            (CTPane*)pCtrl;

        return pPane->FindChild(uiChildID);
    }

    return NULL;
}

void CBagPreviewDlg::LoadRewards()
{
    CWinCtrl* pCtrl =
        FindChildInPane(
            IID_PANE_REWARDS,
            IID_ZLIST_REWARDS
        );

    if (pCtrl == NULL)
    {
        LogString(
            LOG_DEBUG,
            "Bag Preview: ZListBox not found.\n"
        );

        return;
    }

    if (pCtrl->GetControlType() != CTRL_ZLISTBOX)
    {
        LogString(
            LOG_DEBUG,
            "Bag Preview: invalid list control type.\n"
        );

        return;
    }

    CZListBox* pList =
        (CZListBox*)pCtrl;

    pList->Clear();
    pList->SetValue(0);

    if (m_iBagID <= 0 ||
        m_iBagID >= g_TblBAGS.m_nDataCnt)
    {
        LogString(
            LOG_DEBUG,
            "Bag Preview: invalid BagID %d.\n",
            m_iBagID
        );

        return;
    }

    const int iBagRow = m_iBagID;

    for (int iColumn = 2;
        iColumn + 1 < g_TblBAGS.m_nColCnt;
        iColumn += 2)
    {
        const int iItemCode =
            g_TblBAGS.m_ppDATA[iBagRow][iColumn];

        const int iQuantity =
            g_TblBAGS.m_ppDATA[iBagRow][iColumn + 1];

        if (iItemCode <= 0)
            continue;

        const int iItemType =
            iItemCode / 1000;

        const int iItemNo =
            iItemCode % 1000;

        if (iItemType <= 0 ||
            iItemNo <= 0)
        {
            continue;
        }

        if (iItemType > ITEM_TYPE_RIDE_PART)
            continue;

        if (g_pTblSTBs[iItemType] == NULL)
            continue;

        if (iItemNo >=
            g_pTblSTBs[iItemType]->m_nDataCnt)
        {
            continue;
        }

        CBagPreviewListItem* pItem =
            new CBagPreviewListItem(
                iItemType,
                iItemNo,
                iQuantity > 0 ? iQuantity : 1
            );

        pItem->Show();
        pList->Add(pItem);
    }

    pList->SetValue(0);

    CWinCtrl* pScrollCtrl =
        FindChildInPane(
            IID_PANE_REWARDS,
            IID_SCROLL_REWARDS
        );

    if (pScrollCtrl &&
        pScrollCtrl->GetControlType() == CTRL_SCROLLBAR)
    {
        CTScrollBar* pScrollBar =
            (CTScrollBar*)pScrollCtrl;

        pScrollBar->SetValue(0);
    }
}