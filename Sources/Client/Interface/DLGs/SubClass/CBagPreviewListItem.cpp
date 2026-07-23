#include "stdafx.h"
#include "CBagPreviewListItem.h"

#include "../Game.h"
#include "../../Icon/CIconItem.h"
#include "../../InterfaceType.h"
#include "ZListBox.h"

#include "../../../GameCommon/Item.h"
#include <CToolTipMgr.h>

CBagPreviewListItem::CBagPreviewListItem(
    int iItemType,
    int iItemNo,
    int iQuantity)
    : m_iItemType(iItemType),
    m_iItemNo(iItemNo),
    m_iQuantity(iQuantity),
    m_pIcon(NULL)
{
    SetHeight(42);
    SetWidth(150);

    tagITEM sItem;
    ZeroMemory(&sItem, sizeof(tagITEM));

    sItem.m_cType = (BYTE)m_iItemType;
    sItem.m_nItemNo = m_iItemNo;
    sItem.m_uiQuantity =
        m_iQuantity > 0 ? m_iQuantity : 1;

    /*
        Voor equipment moeten life en durability gezet worden,
        anders kan de tooltip het item als kapot beschouwen.
    */
    if (sItem.IsEquipITEM() ||
        sItem.GetTYPE() == ITEM_TYPE_RIDE_PART)
    {
        sItem.m_nLife = MAX_ITEM_LIFE;

        sItem.m_cDurability =
            ITEM_DURABITY(
                sItem.GetTYPE(),
                sItem.GetItemNO()
            );
    }

    m_pIcon = new CIconItem(&sItem);

    const char* pszName =
        ITEM_NAME(m_iItemType, m_iItemNo);

    if (pszName == NULL)
        pszName = "";

    const RECT rect =
    {
        52,
        16,
        175,
        32
    };

    m_Title.set_string(
        pszName,
        rect,
        FONT_OUTLINE_11_BOLD
    );
}

CBagPreviewListItem::~CBagPreviewListItem()
{
    SAFE_DELETE(m_pIcon);
}

void CBagPreviewListItem::Draw()
{
    CWinCtrl::Draw();

    if (m_pIcon)
    {
        POINT ptIcon;

        ptIcon.x = m_sPosition.x + 5;
        ptIcon.y = m_sPosition.y + 5;

        m_pIcon->SetPosition(ptIcon);
        m_pIcon->Draw();
    }

    D3DXMATRIX mat;

    D3DXMatrixTranslation(
        &mat,
        (float)m_sPosition.x,
        (float)m_sPosition.y,
        0.0f
    );

    ::setTransformSprite(mat);



    m_Title.set_color(
        g_dwYELLOW
    );

    m_Title.draw();
}

unsigned int CBagPreviewListItem::Process(
    unsigned int uiMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    /*
        Previewitems zijn voorlopig niet aanklikbaar.
        Ze kunnen dus niet geselecteerd of versleept worden.
    */
    return 0;
}

void CBagPreviewListItem::Update(POINT ptMouse)
{
    if (m_pIcon)
    {
        POINT ptIcon;

        ptIcon.x = m_sPosition.x + 5;
        ptIcon.y = m_sPosition.y + 5;

        m_pIcon->SetPosition(ptIcon);
        m_pIcon->Update(ptMouse);

        if (m_pIcon->IsInside(ptMouse))
        {
            CInfo ToolTip;

            m_pIcon->GetToolTip(
                ToolTip,
                DLG_TYPE_BAG_PREVIEW,
                INFO_STATUS_DETAIL
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
        }
    }

    /*
        Toon de volledige naam wanneer ze afgekort wordt.
    */
    if (IsInside(ptMouse.x, ptMouse.y) &&
        m_Title.is_ellipsis())
    {
        CToolTipMgr::GetInstance().RegToolTip(
            m_sPosition.x + 45,
            m_sPosition.y - 18,
            m_Title.get_string()
        );
    }
}

void CBagPreviewListItem::SetSelected()
{
    /*
        Geen selectie nodig in de preview.
    */
}