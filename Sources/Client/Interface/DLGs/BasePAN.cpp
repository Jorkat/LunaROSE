
#include "StdAfx.h"
#include "BasePAN.h"
#include "../IT_MGR.h"
#include "../CToolTipMgr.h"
#include "../../OBJECT.h"

CBasePAN::CBasePAN()
{

}

CBasePAN::~CBasePAN()
{

}

void CBasePAN::Update( POINT ptMouse )
{
	CTDialog::Update( ptMouse );

	///ﾀﾌﾇﾏ ﾅﾁ ﾇ･ｽﾃ
	CTDialog* pDlg = CTDialog::GetProcessMouseOverDialog();
	if( pDlg && pDlg != this )
			return ;

	WINCTRL_LIST_ITOR iter;
	CWinCtrl*	pCtrl;


	for( iter = m_listChild.begin(); iter != m_listChild.end(); ++iter)
	{
		pCtrl = *iter;
		if( pCtrl->GetControlType() == CTRL_IMAGE )
			continue;

		if( pCtrl->IsInside(ptMouse.x, ptMouse.y ) )
		{
			CToolTipMgr::GetInstance().RegUIInfo( ptMouse.x, ptMouse.y, GetDialogType(), pCtrl->GetControlID());
			break;
		}
	}
}

unsigned int CBasePAN::Process( UINT uiMsg,WPARAM wParam,LPARAM lParam )
{
	unsigned iProcID = 0;
	if( iProcID = CTDialog::Process(uiMsg,wParam,lParam)) 
	{
		switch(uiMsg)
		{
		case WM_LBUTTONUP:
			if(On_LButtonUP(iProcID))
				return uiMsg;
			break;
		default:
			break;
		}
		return uiMsg;
	}
	return 0;
}

bool CBasePAN::On_LButtonUP( unsigned iProcID)
{
	switch( iProcID )
	{
	case BASE_BTN_CHAR_OPEN:		// ﾄｳｸｯﾅﾍﾃ｢ﾀｻ ｿｬｴﾙ 
		g_itMGR.OpenDialog( DLG_TYPE_CHAR );
		return true;
	case BASE_BTN_INV_OPEN:			// ﾀﾎｺ･ﾅ荳ｮﾃ｢ﾀｻ ｿｬｴﾙ 
		return true;
	case BASE_BTN_SKILL_OPEN:		// ｽｺﾅｳﾃ｢ﾀｻ ｿｬｴﾙ 
		g_itMGR.OpenDialog( DLG_TYPE_SKILL );
		return true;	
	case BASE_BTN_QUEST_OPEN:		// ﾄｺﾆｮﾃ｢ﾀｻ ｿｬｴﾙ 
		g_itMGR.OpenDialog( DLG_TYPE_QUEST );
		return true;
	case BASE_BTN_OPTION_OPEN:
		g_itMGR.OpenDialog( DLG_TYPE_OPTION );
		break;
	case BASE_BTN_COMMUNITY_OPEN:	// ﾄｿｹﾂｴﾏﾆｼﾃ｢ﾀｻ ｿｬｴﾙ 
		///REMARK TEST CODE
		return true;
	case BASE_BTN_SYS_OPEN:			// ｽﾃｽｺﾅﾛ ﾃ｢ﾀｻ ｿｬｴﾙ 
		g_itMGR.OpenDialog( DLG_TYPE_SYSTEM );
		return true;
	}	

	return false;
}

