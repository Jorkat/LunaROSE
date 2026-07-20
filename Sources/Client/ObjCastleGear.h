#ifndef _OBJ_CASTLE_GEAR_
#define _OBJ_CASTLE_GEAR_

#include "cobjcart.h"


enum enumCASTLE_GEAR_ANI
{
	CASTLE_GEAR_ANI_STOP1 = 0,
	CASTLE_GEAR_ANI_MOVE,	
	CASTLE_GEAR_ANI_ATTACK01,	
	CASTLE_GEAR_ANI_ATTACK02,	
	CASTLE_GEAR_ANI_ATTACK03,	
	CASTLE_GEAR_ANI_DIE,	
	CASTLE_GEAR_ANI_CASTING,
	CASTLE_GEAR_ANI_SKILL,
};


//----------------------------------------------------------------------------------------------------
/// class CObjCastleGear
/// switch ｹｮﾀｸｷﾎ CObjCART ｷﾎ ﾃｳｸｮ ﾇﾒｼｵ ﾀﾖｾ愠ｸ ﾂﾄ Castle Gear ｸｸﾀﾇ ｱ箒ﾉﾃﾟｰ｡ｸｦ ﾀｧﾇﾘｼｭ ｺﾐｸｮ..
//----------------------------------------------------------------------------------------------------

class CObjCastleGear :	public CObjCART
{
public:
	CObjCastleGear(void);
	~CObjCastleGear(void);

	//////////////////////////////////////////////////////////////////////////////////////////	
	/// < Inherited from CGameOBJ virtual functions
	/// <

	/*override*/virtual int		Get_TYPE()				{	return OBJ_CGEAR;					}	

	/// <
	/// < end	
	//////////////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////////////////	
	/// < Inherited from CObjAI virtual functions
	/// <

	/*override*/virtual int		GetANI_Stop();
	/*override*/virtual int		GetANI_Move();
	/*override*/virtual int		GetANI_Attack();
	/*override*/virtual int		GetANI_Die ();
	/*override*/virtual int		GetANI_Hit();
	/*override*/virtual int		GetANI_Casting();
	/*override*/virtual int		GetANI_Skill();

	
	/*override*/virtual void	SetCMD_ATTACK (int iServerTarget, WORD wSrvDIST, const D3DVECTOR& PosGOTO);	
	/// <
	/// < End
	//////////////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////////////////	
	/// < Inherited from CObjCHAR virtual functions
	/// <
	
	/// <
	/// < end	
	//////////////////////////////////////////////////////////////////////////////////////////


	virtual bool	Create( CObjCHAR* pParent, int iCartType, D3DVECTOR &Position );

};

#endif ///_OBJ_CASTLE_GEAR_