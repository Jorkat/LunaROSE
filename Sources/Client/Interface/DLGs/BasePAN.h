
#ifndef _BASE_PAN_H
#define _BASE_PAN_H


#include "../../../TGameCtrl\\TDialog.h"
// *--------------------------------------------------------------------* //
// ｱ篌ｻﾆﾇｳｾﾃ｢ 
// *--------------------------------------------------------------------* //

enum basePAN {
	BASE_IMG			= 1,		//1,ﾆﾇｳｾ
	BASE_BTN_CHAR_OPEN,				//2,ﾄｳｸｯﾅﾍﾁ､ｺｸｹｰ
	BASE_BTN_INV_OPEN,				//3.ﾀﾎｺ･ﾅ荳ｮｿﾀﾇﾂ 
	BASE_BTN_SKILL_OPEN,			//4.ｽｺﾅｳﾃ｢ｿﾀﾇﾂ 
	BASE_BTN_QUEST_OPEN,			//5.ﾄｺﾆｮﾃ｢ｿﾀﾇﾂ 
	BASE_BTN_COMMUNITY_OPEN,		//6.ﾄｿｹﾂｴﾏﾆｼｿﾀﾇﾂ 
	BASE_BTN_OPTION_OPEN,			//7.ｽﾃｽｺﾅﾛｸﾞｴｺｿﾀﾇﾂ 
	BASE_BTN_SYS_OPEN,				//8.ｽﾃｽｺﾅﾛｸﾞｴｺｿﾀﾇﾂ 
	BASE_MAX_CTRL_CNT		
};

class CBasePAN : public CTDialog
{
public:
	CBasePAN();
	~CBasePAN();


	virtual unsigned int Process( UINT uiMsg,WPARAM wParam,LPARAM lParam );
	virtual void Update( POINT ptMouse );

private:
	bool On_LButtonUP( unsigned iProcID);

};



#endif