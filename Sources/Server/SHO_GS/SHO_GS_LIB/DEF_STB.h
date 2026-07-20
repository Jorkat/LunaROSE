#ifndef	__DEF_STB_H
#define	__DEF_STB_H
#include "IO_STB.h"
//-------------------------------------------------------------------------------------------------


#define	SP_LEVEL(L)				g_TblSkillPoint.m_ppDATA[ L ][ 0 ]
#define	SP_POINT(L)				g_TblSkillPoint.m_ppDATA[ L ][ 1 ]


extern STBDATA	g_TblSkillPoint;

//-------------------------------------------------------------------------------------------------
// Custom bag/box reward table
//-------------------------------------------------------------------------------------------------

#define MAX_BAG_REWARD_SLOTS 10

enum eLIST_BAGS_COLUMN
{
    BAG_COL_ID = 0,
    BAG_COL_REWARD_COUNT = 1,

    BAG_COL_ITEM_1 = 2,
    BAG_COL_ITEM_1_COUNT = 3,

    BAG_COL_ITEM_2 = 4,
    BAG_COL_ITEM_2_COUNT = 5,

    BAG_COL_ITEM_3 = 6,
    BAG_COL_ITEM_3_COUNT = 7,

    BAG_COL_ITEM_4 = 8,
    BAG_COL_ITEM_4_COUNT = 9,

    BAG_COL_ITEM_5 = 10,
    BAG_COL_ITEM_5_COUNT = 11,

    BAG_COL_ITEM_6 = 12,
    BAG_COL_ITEM_6_COUNT = 13,

    BAG_COL_ITEM_7 = 14,
    BAG_COL_ITEM_7_COUNT = 15,

    BAG_COL_ITEM_8 = 16,
    BAG_COL_ITEM_8_COUNT = 17,

    BAG_COL_ITEM_9 = 18,
    BAG_COL_ITEM_9_COUNT = 19,

    BAG_COL_ITEM_10 = 20,
    BAG_COL_ITEM_10_COUNT = 21
};


#define BAG_IS_VALID(R) \
    ((R) > 0 && (R) < g_TblBAGS.m_nDataCnt)

#define BAG_ID(R) (R)

#define BAG_REWARD_COUNT(R) \
    (BAG_IS_VALID(R) ? \
        g_TblBAGS.m_ppDATA[(R)][BAG_COL_REWARD_COUNT] : 0)

#define BAG_ITEM(R, SLOT) \
    (BAG_IS_VALID(R) && \
     (SLOT) >= 0 && \
     (SLOT) < MAX_BAG_REWARD_SLOTS ? \
        g_TblBAGS.m_ppDATA[(R)][BAG_COL_ITEM_1 + ((SLOT) * 2)] : 0)

#define BAG_ITEM_COUNT(R, SLOT) \
    (BAG_IS_VALID(R) && \
     (SLOT) >= 0 && \
     (SLOT) < MAX_BAG_REWARD_SLOTS ? \
        g_TblBAGS.m_ppDATA[(R)][BAG_COL_ITEM_1_COUNT + ((SLOT) * 2)] : 0)

extern STBDATA g_TblBAGS;

//-------------------------------------------------------------------------------------------------
#endif