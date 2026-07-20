#ifndef _CMONSTERLISTITEM_H_
#define _CMONSTERLISTITEM_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "winctrl.h"
#include "SinglelineString.h"

class CMonsterListItem : public CWinCtrl
{
public:
    CMonsterListItem(int iNpcID);
    virtual ~CMonsterListItem();

    virtual void Draw();

    virtual unsigned int Process(
        unsigned int uiMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    virtual void Update(POINT ptMouse);
    virtual void SetSelected();

    int GetNpcID() const
    {
        return m_iNpcID;
    }

protected:
    int m_iNpcID;
    CSinglelineString m_Title;
};

#endif