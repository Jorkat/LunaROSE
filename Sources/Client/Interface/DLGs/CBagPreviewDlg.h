#ifndef _CBAGPREVIEWDLG_H_
#define _CBAGPREVIEWDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "TDialog.h"

class CWinCtrl;

class CBagPreviewDlg : public CTDialog
{
public:
    CBagPreviewDlg();
    virtual ~CBagPreviewDlg();

    virtual unsigned int Process(
        UINT uiMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    virtual void Draw();
    virtual void Show();
    virtual void Hide();

    void SetBagID(int iBagID);
    int GetBagID() const;

    enum
    {
        IID_BTN_CLOSE = 10,

        IID_ZLIST_REWARDS = 30,
        IID_SCROLL_REWARDS = 31,
        IID_SCROLLBOX_REWARDS = 32,

        IID_PANE_REWARDS = 100
    };

protected:
    bool On_LButtonUP(unsigned int uiControlID);
    bool On_LButtonDN(unsigned int uiControlID);

    CWinCtrl* FindChildInPane(
        unsigned int uiPaneID,
        unsigned int uiChildID
    );

private:
    void LoadRewards();

private:
    int m_iBagID;
};

#endif