#ifndef _CBAGPREVIEWLISTITEM_H_
#define _CBAGPREVIEWLISTITEM_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "winctrl.h"
#include "SinglelineString.h"

class CIconItem;

class CBagPreviewListItem : public CWinCtrl
{
public:
    CBagPreviewListItem(
        int iItemType,
        int iItemNo,
        int iQuantity
    );

    virtual ~CBagPreviewListItem();

    virtual void Draw();

    virtual unsigned int Process(
        unsigned int uiMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    virtual void Update(POINT ptMouse);
    virtual void SetSelected();

    int GetItemType() const
    {
        return m_iItemType;
    }

    int GetItemNo() const
    {
        return m_iItemNo;
    }

private:
    int m_iItemType;
    int m_iItemNo;
    int m_iQuantity;

    CIconItem* m_pIcon;
    CSinglelineString m_Title;
};

#endif