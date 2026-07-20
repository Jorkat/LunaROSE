#include "stdafx.h"
#include ".\cfriendlistitem.h"
#include "../CPrivateChatDlg.h"
#include "../CMemoDlg.h"

#include "../../it_mgr.h"
#include "../../TypeResource.h"
#include "../../IO_ImageRes.h"
#include "../../CTDrawImpl.h"

#include "../../../Game.h"
#include "Net_Prototype.h"


#include "ZListBox.h"
#include "ResourceMgr.h"
CFriendListItem::CFriendListItem( DWORD dwUserTag, BYTE btStatus, const char* pszName )
{
	SetHeight( 20 );
	SetWidth( 180 );
	m_dwUserTag = dwUserTag;
	m_btStatus = btStatus;
	assert( pszName );
	if( pszName )
		m_strName = pszName;

	m_online_image_id	= CResourceMgr::GetInstance()->GetImageNID( IMAGE_RES_UI, "CLAN01_MARK_ONLINE" );;
	m_offline_image_id	= CResourceMgr::GetInstance()->GetImageNID( IMAGE_RES_UI, "CLAN01_MARK_OFFLINE" );

}

CFriendListItem::~CFriendListItem(void)
{

}
//
/////상태별 표시 추가
void CFriendListItem::Draw()
{
	/*D3DXMATRIX mat;	
	D3DXMatrixTranslation( &mat, (float)m_sPosition.x, (float)m_sPosition.y,0.0f);
	::setTransformSprite( mat );*/

	DWORD dwColor = g_dwBLACK;
	int   image_id = m_online_image_id;

	char* pszStatus  = NULL;

	switch( m_btStatus )
	{
	case FRIEND_STATUS_HUNT:// 사냥중
		pszStatus = STR_MYSTATE_IN_HUNT;
		break;
	case FRIEND_STATUS_STORE:// 장사중
		pszStatus = STR_MYSTATE_IN_TRADE;
		break;
	case FRIEND_STATUS_QUEST:// 퀘스트중
		pszStatus = STR_MYSTATE_IN_QUEST;
		break;
	case FRIEND_STATUS_EAT:// 식사중
		pszStatus = STR_MYSTATE_IN_EAT;
		break;
	case FRIEND_STATUS_REST:// 휴식중
		pszStatus = STR_MYSTATE_IN_BREAK;
		break;
	case FRIEND_STATUS_REFUSED: ///대화거절
	case FRIEND_STATUS_DELETED: ///상대방이 나를 친구목록에서 제외했다.
	case FRIEND_STATUS_OFFLINE: // 접속끊김		: 친구목록의 m_dwUserTAG가 접속끊김
		{
			dwColor   = g_dwGRAY;
			pszStatus = "OffLine";
			image_id  = m_offline_image_id;
		}
		break;
	case FRIEND_STATUS_ONLINE: // 접속됨		: 친구목록의 m_dwUserTAG가 접속했다.
	case FRIEND_STATUS_NORMAL:
	default:
		pszStatus = "OnLine";
		break;
	}

	if( IsSelected() )
		dwColor = g_dwYELLOW;
	
	
	g_DrawImpl.Draw( (int)m_sPosition.x, (int)m_sPosition.y, IMAGE_RES_UI, image_id );	

	RECT rc = { 20, 0, m_iWidth, m_iHeight };
	::drawFont( g_GameDATA.m_hFONT[ FONT_SMALL ], true, &rc, dwColor, DT_VCENTER, CStr::Printf("%-16s(%s)", m_strName.c_str(), pszStatus ) );

}

unsigned CFriendListItem::Process( unsigned uiMsg, WPARAM wParam, LPARAM lParam )
{
	if( !IsInside( LOWORD(lParam), HIWORD( lParam )) ) return 0;

	switch( uiMsg )
	{
	case WM_LBUTTONDOWN:
		SetSelected();
		return GetControlID();
	case WM_LBUTTONDBLCLK:
		{
			switch( m_btStatus )
			{
			case FRIEND_STATUS_DELETED:
				g_itMGR.OpenMsgBox(CStr::Printf(F_STR_FRIEND_DELETED , m_strName.c_str() ));
				g_itMGR.OpenDialog( DLG_TYPE_MEMO, false );
				break;
			case FRIEND_STATUS_REFUSED:
				g_itMGR.OpenMsgBox(CStr::Printf(F_STR_MESSANGER_BLOCKED , m_strName.c_str() ));
				break;
			default:
				{
					if( m_btStatus == FRIEND_STATUS_OFFLINE )
					{
						CTDialog* pDlg = g_itMGR.FindDlg( DLG_TYPE_MEMO );
						assert( pDlg );
						if( pDlg )
						{
							CMemoDlg* pMemoDlg = (CMemoDlg*)pDlg;
							pMemoDlg->SetTargetName( m_strName.c_str() );
							g_itMGR.OpenDialog( DLG_TYPE_MEMO, false );
						}
						
					}
					else
						g_itMGR.OpenPrivateChatDlg( m_dwUserTag, m_btStatus, m_strName.c_str() );
					break;
				}
			}
			return GetControlID();
		}
	default:
		break;
	}
	
	return 0;
}

void CFriendListItem::SetSelected()
{
	if( m_pParent )
	{
		if( m_pParent->GetControlType() == CTRL_ZLISTBOX )
		{
			CZListBox* pList = ( CZListBox*)m_pParent;
			pList->DeselectAll();
		}
	}
	CWinCtrl::SetSelected();
}

void	CFriendListItem::SetStatus( BYTE btStatus )
{
	m_btStatus = btStatus;

	switch( m_btStatus ) 
	{
	case FRIEND_STATUS_OFFLINE:// 접속끊김
		g_itMGR.AppendChatMsg( CStr::Printf( FSTR_FRIEND_LOGOUT, m_strName.c_str() ), IT_MGR::CHAT_TYPE_FRIEND );
		break;
	case FRIEND_STATUS_ONLINE:// 접속됨
		g_itMGR.AppendChatMsg( CStr::Printf( FSTR_FRIEND_LOGIN, m_strName.c_str() ), IT_MGR::CHAT_TYPE_FRIEND );
		break;
	default:
		break;
	}
}

const	DWORD	CFriendListItem::GetUserTag()
{
	return m_dwUserTag;
}

const	char*	CFriendListItem::GetName()
{
	return m_strName.c_str();
}

const	BYTE	CFriendListItem::GetStatus()
{
	return m_btStatus;
}