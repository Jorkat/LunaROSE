#ifndef _CMONSTERDATABASEDLG_H_
#define _CMONSTERDATABASEDLG_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "TDialog.h"

#include <vector>
#include <string>

class CIconItem;

struct SMonsterDrop
{
    int iItemType;
    int iItemNo;

    CIconItem* pIcon;
};

class CMonsterDatabaseDlg : public CTDialog
{
public:
    CMonsterDatabaseDlg();
    virtual ~CMonsterDatabaseDlg();

    virtual unsigned int Process(
        UINT uiMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    virtual void Draw();
    virtual void Show();
    virtual void Hide();

    enum
    {
        IID_BTN_CLOSE = 10,

        IID_EDIT_SEARCH = 20,

        IID_ZLIST_MONSTERS = 30,
        IID_SCROLL_MONSTERS = 31,
        IID_SCROLLBOX_MONSTERS = 32,

        IID_ZLIST_MONSTER_ITEM = 40,

        IID_PANE_MONSTER_LIST = 100,
        IID_PANE_MONSTER_INFO = 200
    };

protected:
    bool On_LButtonUP(unsigned int uiControlID);
    bool On_LButtonDN(unsigned int uiControlID);

    CWinCtrl* FindChildInPane(
        unsigned int uiPaneID,
        unsigned int uiChildID
    );

private:
    void LoadMonsters();
    void UpdateMonsterList();
    void UpdateSelectedMonster();
    void UpdateSearch();

    void DrawMonsterInfo();

    void LoadSelectedMonsterDrops();
    void ClearMonsterDrops();
    void DrawMonsterDrops();
    void UpdateMonsterDrops(POINT ptMouse);

private:
    int m_iSelectedMonsterID;

    std::vector<int> m_MonsterIDs;
    std::vector<int> m_VisibleMonsterIDs;

    std::string m_LastSearchText;

    std::vector<SMonsterDrop> m_MonsterDrops;
};

#endif