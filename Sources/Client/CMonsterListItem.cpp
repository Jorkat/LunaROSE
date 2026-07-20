#include "stdafx.h"
#include "CMonsterListItem.h"

#include "../Game.h"
#include "CToolTipMgr.h"
#include "ZListBox.h"

CMonsterListItem::CMonsterListItem(int iNpcID)
    : m_iNpcID(iNpcID)
{
    SetHeight(24);
    SetWidth(150);

    const char* pszName = NPC_NAME(m_iNpcID);

    if (pszName == NULL)
        pszName = "";

    const RECT rect = { 10, 5, 170, 24 };

    m_Title.set_string(
        pszName,
        rect,
        FONT_NORMAL
    );
}

CMonsterListItem::~CMonsterListItem()
{
}

void CMonsterListItem::Draw()
{
    CWinCtrl::Draw();

    D3DXMATRIX mat;
    D3DXMatrixTranslation(
        &mat,
        (float)m_sPosition.x,
        (float)m_sPosition.y,
        0.0f
    );

    ::setTransformSprite(mat);

    if (IsSelected())
        m_Title.set_color(g_dwYELLOW);
    else
        m_Title.set_color(
            D3DCOLOR_RGBA(0, 0, 0, 255)
        );

    m_Title.draw();
}

unsigned int CMonsterListItem::Process(
    unsigned int uiMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    if (!IsInside(LOWORD(lParam), HIWORD(lParam)))
        return 0;

    if (uiMsg == WM_LBUTTONDOWN)
    {
        SetSelected();
        return GetControlID();
    }

    return 0;
}

void CMonsterListItem::Update(POINT ptMouse)
{
    if (!IsInside(ptMouse.x, ptMouse.y))
        return;

    if (m_Title.is_ellipsis())
    {
        CToolTipMgr::GetInstance().RegToolTip(
            m_sPosition.x + 10,
            m_sPosition.y - 18,
            m_Title.get_string()
        );
    }
}

void CMonsterListItem::SetSelected()
{
    if (m_pParent &&
        m_pParent->GetControlType() == CTRL_ZLISTBOX)
    {
        CZListBox* pList = (CZListBox*)m_pParent;
        pList->DeselectAll();
    }

    CWinCtrl::SetSelected();
}