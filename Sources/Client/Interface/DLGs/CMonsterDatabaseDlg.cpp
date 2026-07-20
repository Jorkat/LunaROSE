#include "stdafx.h"
#include "CMonsterDatabaseDlg.h"

#include "../it_mgr.h"

#include "CMonsterListItem.h"

#include "../Icon/CIconItem.h"
#include "../../GameCommon/Item.h"
#include "../CToolTipMgr.h"

#include "ResourceMgr.h"
#include "IO_ImageRes.h"
#include "ZListBox.h"
#include "TScrollBar.h"
#include "TPane.h"
#include <Common/io_stb.h>
#include "TEditBox.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <System/CGame.h>

static std::string MakeLowerCase(const char* pszText)
{
    std::string strResult;

    if (pszText == NULL)
        return strResult;

    strResult = pszText;

    for (std::string::size_type i = 0;
        i < strResult.length();
        ++i)
    {
        strResult[i] = (char)tolower(
            (unsigned char)strResult[i]
        );
    }

    return strResult;
}

CMonsterDatabaseDlg::CMonsterDatabaseDlg()
    : m_iSelectedMonsterID(0)
{
}

CMonsterDatabaseDlg::~CMonsterDatabaseDlg()
{
    ClearMonsterDrops();
}

unsigned int CMonsterDatabaseDlg::Process(
    UINT uiMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    if (!IsVision())
        return 0;

    unsigned int uiProcessID = 0;

    uiProcessID =
        CTDialog::Process(uiMsg, wParam, lParam);

    UpdateSearch();

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

void CMonsterDatabaseDlg::Draw()
{
    if (!IsVision())
        return;

    CTDialog::Draw();

    DrawMonsterInfo();

    POINT ptMouse;
    CGame::GetInstance().Get_MousePos(ptMouse);

    
    DrawMonsterDrops();
    UpdateMonsterDrops(ptMouse);
}

void CMonsterDatabaseDlg::Show()
{
    CTDialog::Show();

    m_LastSearchText.clear();

    LoadMonsters();
    UpdateMonsterList();
}

void CMonsterDatabaseDlg::Hide()
{
    CTDialog::Hide();
}

void CMonsterDatabaseDlg::LoadMonsters()
{
    m_MonsterIDs.clear();
    m_iSelectedMonsterID = 0;

    for (int iNpcID = 1;
        iNpcID < g_TblNPC.m_nDataCnt;
        ++iNpcID)
    {
        const char* pszName = NPC_NAME(iNpcID);

        if (pszName == NULL)
            continue;

        if (pszName[0] == '\0')
            continue;

        // Interne of gegroepeerde STB-rijen negeren
        if (pszName[0] == '[')
            continue;

        m_MonsterIDs.push_back(iNpcID);
    }
}

void CMonsterDatabaseDlg::UpdateSearch()
{
    CWinCtrl* pCtrl = FindChildInPane(
        IID_PANE_MONSTER_LIST,
        IID_EDIT_SEARCH
    );

    if (pCtrl == NULL)
        return;

    if (pCtrl->GetControlType() != CTRL_EDITBOX)
        return;

    CTEditBox* pEditBox =
        (CTEditBox*)pCtrl;

    const char* pszSearchText =
        pEditBox->get_text();

    std::string strSearchText;

    if (pszSearchText != NULL)
        strSearchText = pszSearchText;

    if (strSearchText == m_LastSearchText)
        return;

    m_LastSearchText = strSearchText;

    UpdateMonsterList();
}

void CMonsterDatabaseDlg::UpdateMonsterList()
{
    CWinCtrl* pCtrl = FindChildInPane(
        IID_PANE_MONSTER_LIST,
        IID_ZLIST_MONSTERS
    );

    if (pCtrl == NULL)
    {
        LogString(
            LOG_DEBUG,
            "Monster Database: ZListBox not found.\n"
        );

        return;
    }

    if (pCtrl->GetControlType() != CTRL_ZLISTBOX)
    {
        LogString(
            LOG_DEBUG,
            "Monster Database: invalid list control type.\n"
        );

        return;
    }

    CZListBox* pList =
        (CZListBox*)pCtrl;

    pList->Clear();
    m_VisibleMonsterIDs.clear();

    /*
        Zoektekst ophalen
    */
    std::string strSearchText;

    CWinCtrl* pEditCtrl = FindChildInPane(
        IID_PANE_MONSTER_LIST,
        IID_EDIT_SEARCH
    );

    if (pEditCtrl &&
        pEditCtrl->GetControlType() == CTRL_EDITBOX)
    {
        CTEditBox* pEditBox =
            (CTEditBox*)pEditCtrl;

        const char* pszSearchText =
            pEditBox->get_text();

        strSearchText =
            MakeLowerCase(pszSearchText);
    }

    /*
        Monsters filteren en aan de zichtbare lijst toevoegen
    */
    for (unsigned int i = 0;
        i < m_MonsterIDs.size();
        ++i)
    {
        int iNpcID = m_MonsterIDs[i];

        const char* pszMonsterName =
            NPC_NAME(iNpcID);

        if (pszMonsterName == NULL)
            continue;

        std::string strMonsterName =
            MakeLowerCase(pszMonsterName);

        /*
            Bij een lege zoektekst worden alle monsters getoond.

            Anders moet de monsternaam de zoektekst bevatten.
        */
        if (!strSearchText.empty())
        {
            if (strMonsterName.find(strSearchText) ==
                std::string::npos)
            {
                continue;
            }
        }

        m_VisibleMonsterIDs.push_back(iNpcID);

        CMonsterListItem* pItem =
            new CMonsterListItem(iNpcID);

        pItem->SetControlID(
            IID_ZLIST_MONSTER_ITEM
        );

        pItem->Show();

        pList->Add(pItem);
    }

    /*
        Eerste zoekresultaat selecteren
    */
    if (pList->GetSize() > 0)
    {
        pList->SetSelected(0);

        m_iSelectedMonsterID =
            m_VisibleMonsterIDs[0];

        LoadSelectedMonsterDrops();
    }
    else
    {
        /*
            Geen zoekresultaten
        */
        m_iSelectedMonsterID = 0;
        ClearMonsterDrops();
    }

    /*
        Scrollbar altijd terug naar boven zetten
    */
    CWinCtrl* pScrollCtrl =
        FindChildInPane(
            IID_PANE_MONSTER_LIST,
            IID_SCROLL_MONSTERS
        );

    if (pScrollCtrl &&
        pScrollCtrl->GetControlType() == CTRL_SCROLLBAR)
    {
        CTScrollBar* pScrollBar =
            (CTScrollBar*)pScrollCtrl;

        pScrollBar->SetValue(0);
    }
}

void CMonsterDatabaseDlg::DrawMonsterDrops()
{
    if (m_MonsterDrops.empty())
        return;

    CWinCtrl* pPane =
        Find(IID_PANE_MONSTER_INFO);

    if (pPane == NULL)
        return;

    POINT ptDialog = GetPosition();
    POINT ptPaneOffset = pPane->GetOffset();

    const int iStartX =
        ptDialog.x + ptPaneOffset.x + 20;

    const int iStartY =
        ptDialog.y + ptPaneOffset.y + 218;

    const int iIconsPerRow = 6;
    const int iSpacingX = 42;
    const int iSpacingY = 42;

    for (unsigned int i = 0;
        i < m_MonsterDrops.size();
        ++i)
    {
        CIconItem* pIcon =
            m_MonsterDrops[i].pIcon;

        if (pIcon == NULL)
            continue;

        int iColumn =
            i % iIconsPerRow;

        int iRow =
            i / iIconsPerRow;

        POINT ptIcon;

        ptIcon.x =
            iStartX + iColumn * iSpacingX;

        ptIcon.y =
            iStartY + iRow * iSpacingY;

        pIcon->SetPosition(ptIcon);
        pIcon->Draw();
    }
}

void CMonsterDatabaseDlg::UpdateMonsterDrops(
    POINT ptMouse)
{
    for (unsigned int i = 0;
        i < m_MonsterDrops.size();
        ++i)
    {
        CIconItem* pIcon =
            m_MonsterDrops[i].pIcon;

        if (pIcon == NULL)
            continue;

        pIcon->Update(ptMouse);

        if (pIcon->IsInside(ptMouse))
        {
            CInfo ToolTip;

            pIcon->GetToolTip(
                ToolTip,
                DLG_TYPE_MONSTER_DATABASE,
                0
            );

            if (!ToolTip.IsEmpty())
            {
                POINT ptToolTip = ptMouse;

                ptToolTip.x += 18;
                ptToolTip.y += 18;

                ToolTip.SetPosition(ptToolTip);

                CToolTipMgr::GetInstance().RegistInfo(
                    ToolTip
                );
            }

            break;
        }
    }
}

void CMonsterDatabaseDlg::UpdateSelectedMonster()
{
    CWinCtrl* pCtrl = FindChildInPane(
        IID_PANE_MONSTER_LIST,
        IID_ZLIST_MONSTERS
    );

    if (pCtrl == NULL)
        return;

    if (pCtrl->GetControlType() != CTRL_ZLISTBOX)
        return;

    CZListBox* pList =
        (CZListBox*)pCtrl;

    int iSelectedIndex =
        pList->GetSelectedItemIndex();

    if (iSelectedIndex < 0)
        return;

    if (iSelectedIndex >=
        (int)m_VisibleMonsterIDs.size())
    {
        return;
    }

    m_iSelectedMonsterID =
        m_VisibleMonsterIDs[iSelectedIndex];

    LoadSelectedMonsterDrops();
}

void CMonsterDatabaseDlg::LoadSelectedMonsterDrops()
{
    ClearMonsterDrops();

    if (m_iSelectedMonsterID <= 0)
        return;

    if (m_iSelectedMonsterID >= g_TblNPC.m_nDataCnt)
        return;

    int iDropTableID =
        NPC_DROP_TYPE(m_iSelectedMonsterID);

    if (iDropTableID < 0)
        return;

    if (iDropTableID >= g_TblDropITEM.m_nDataCnt)
        return;

    for (int iColumn = 0;
        iColumn < g_TblDropITEM.m_nColCnt;
        ++iColumn)
    {
        int iDropItem =
            DROPITEM_ITEMNO(
                iDropTableID,
                iColumn
            );

        // 0 en 1 t/m 4 zijn geen rechtstreekse items
        if (iDropItem <= 1000)
            continue;

        int iItemType = iDropItem / 1000;
        int iItemNo = iDropItem % 1000;

        if (iItemType <= 0 || iItemNo <= 0)
            continue;

        bool bAlreadyAdded = false;

        for (unsigned int i = 0;
            i < m_MonsterDrops.size();
            ++i)
        {
            if (m_MonsterDrops[i].iItemType == iItemType &&
                m_MonsterDrops[i].iItemNo == iItemNo)
            {
                bAlreadyAdded = true;
                break;
            }
        }

        if (bAlreadyAdded)
            continue;

        tagITEM sItem;
        ZeroMemory(&sItem, sizeof(tagITEM));

        sItem.m_cType =
            (BYTE)iItemType;

        sItem.m_nItemNo =
            iItemNo;

        sItem.m_uiQuantity =
            1;

        if (sItem.IsEquipITEM() ||
            sItem.GetTYPE() == ITEM_TYPE_RIDE_PART)
        {
            sItem.m_nLife =
                MAX_ITEM_LIFE;

            sItem.m_cDurability =
                ITEM_DURABITY(
                    sItem.GetTYPE(),
                    sItem.GetItemNO()
                );
        }

        SMonsterDrop sDrop;

        sDrop.iItemType = iItemType;
        sDrop.iItemNo = iItemNo;
        sDrop.pIcon = new CIconItem(&sItem);

        m_MonsterDrops.push_back(sDrop);
    }
}

void CMonsterDatabaseDlg::ClearMonsterDrops()
{
    for (unsigned int i = 0;
        i < m_MonsterDrops.size();
        ++i)
    {
        SAFE_DELETE(m_MonsterDrops[i].pIcon);
    }

    m_MonsterDrops.clear();
}

bool CMonsterDatabaseDlg::On_LButtonUP(
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

bool CMonsterDatabaseDlg::On_LButtonDN(
    unsigned int uiControlID)
{
    switch (uiControlID)
    {
    case IID_ZLIST_MONSTER_ITEM:
        UpdateSelectedMonster();
        return true;

    default:
        break;
    }

    return false;
}

CWinCtrl* CMonsterDatabaseDlg::FindChildInPane(
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

void CMonsterDatabaseDlg::DrawMonsterInfo()
{
    if (m_iSelectedMonsterID <= 0)
        return;

    if (m_iSelectedMonsterID >= g_TblNPC.m_nDataCnt)
        return;

    CWinCtrl* pPane = Find(IID_PANE_MONSTER_INFO);
    if (pPane == NULL)
        return;

    POINT ptDialog = GetPosition();
    POINT ptPaneOffset = pPane->GetOffset();

    D3DXMATRIX mat;
    D3DXMatrixTranslation(
        &mat,
        (float)ptDialog.x,
        (float)ptDialog.y,
        0.0f
    );
    ::setTransformSprite(mat);

    HNODE hFont = g_GameDATA.m_hFONT[FONT_NORMAL];
    HNODE hHeaderFont = g_GameDATA.m_hFONT[FONT_OUTLINE_11_BOLD];

    const char* pszName = NPC_NAME(m_iSelectedMonsterID);
    if (pszName == NULL)
        pszName = "";

    char szHeader[256] = { 0 };
    _snprintf(
        szHeader,
        sizeof(szHeader) - 1,
        "%s (Lv. %d)",
        pszName,
        NPC_LEVEL(m_iSelectedMonsterID)
    );
    szHeader[sizeof(szHeader) - 1] = '\0';

    /// Pane basis
    const int iBaseX = ptPaneOffset.x;
    const int iBaseY = ptPaneOffset.y;

    /// Header
    const int iHeaderX = iBaseX + 22;
    const int iHeaderY = iBaseY + 37;

    /// Kolommen
    const int iCol1LabelX = iBaseX + 22;
    const int iCol1ValueX = iBaseX + 110;

    const int iCol2LabelX = iBaseX + 160;
    const int iCol2ValueX = iBaseX + 250;

    const int iLineHeight = 26;
    int iY = iBaseY + 77;

    drawFont(
        hHeaderFont,
        true,
        iHeaderX,
        iHeaderY,
        g_dwYELLOW,
        szHeader
    );

    /// Rij 1
    drawFont(hFont, true, iCol1LabelX, iY, g_dwBLACK, "HP");
    drawFontf(
        hFont,
        true,
        iCol1ValueX,
        iY,
        g_dwWHITE,
        "%d",
        NPC_HP(m_iSelectedMonsterID) * 2
    );

    drawFont(hFont, true, iCol2LabelX, iY, g_dwBLACK, "Attack Sp.");
    drawFontf(
        hFont,
        true,
        iCol2ValueX,
        iY,
        g_dwWHITE,
        "%d",
        NPC_ATK_SPEED(m_iSelectedMonsterID)
    );

    iY += iLineHeight;

    /// Rij 2
    drawFont(hFont, true, iCol1LabelX, iY, g_dwBLACK, "Attack");
    drawFontf(
        hFont,
        true,
        iCol1ValueX,
        iY,
        g_dwWHITE,
        "%d",
        NPC_ATK(m_iSelectedMonsterID)
    );

    drawFont(hFont, true, iCol2LabelX, iY, g_dwBLACK, "Accuracy");
    drawFontf(
        hFont,
        true,
        iCol2ValueX,
        iY,
        g_dwWHITE,
        "%d",
        NPC_HIT(m_iSelectedMonsterID)
    );

    iY += iLineHeight;

    /// Rij 3
    drawFont(hFont, true, iCol1LabelX, iY, g_dwBLACK, "Defense");
    drawFontf(
        hFont,
        true,
        iCol1ValueX,
        iY,
        g_dwWHITE,
        "%d",
        NPC_DEF(m_iSelectedMonsterID)
    );

    drawFont(hFont, true, iCol2LabelX, iY, g_dwBLACK, "Magic Def.");
    drawFontf(
        hFont,
        true,
        iCol2ValueX,
        iY,
        g_dwWHITE,
        "%d",
        NPC_RES(m_iSelectedMonsterID)
    );

    iY += iLineHeight;

    /// Rij 4
    drawFont(hFont, true, iCol1LabelX, iY, g_dwBLACK, "Dodge");
    drawFontf(
        hFont,
        true,
        iCol1ValueX,
        iY,
        g_dwWHITE,
        "%d",
        NPC_AVOID(m_iSelectedMonsterID)
    );

    drawFont(hFont, true, iCol2LabelX, iY, g_dwBLACK, "Mov. Speed");
    drawFontf(
        hFont,
        true,
        iCol2ValueX,
        iY,
        g_dwWHITE,
        "%d",
        NPC_WALK_SPEED(m_iSelectedMonsterID)
    );

    /// Drops titel
    iY += 46;

    drawFont(
        hFont,
        true,
        iCol1LabelX,
        iY,
        g_dwYELLOW,
        "Drops"
    );

    // Hier komen later de drop-iconen
    const int iStartY =
        ptDialog.y + ptPaneOffset.y + 218;
}