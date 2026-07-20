#ifndef _OBJECT_TARGET_EFFECT_
#define _OBJECT_TARGET_EFFECT_


class CEffect;
class CObjCHAR;

//----------------------------------------------------------------------------------------------------
/// ｰﾔﾀﾓｳｻ ﾅｸｰﾙﾀｻ ｼｱﾅﾃ( ﾀｯﾁｮ, ｸｺﾅﾍ, NPC )ﾇﾟﾀｻｶｧ ｼｱﾅﾃﾇ･ｽﾃ ﾀﾌﾆ衄ｮ ﾃ箙ﾂ
/// class CObjectTargetEffect
//----------------------------------------------------------------------------------------------------

class CObjectTargetEffect
{
	CEffect*			m_pEffect;
	CObjCHAR*			m_pParent;

public:
	CObjectTargetEffect(void);
	~CObjectTargetEffect(void);

	void				Init();
	void				Clear();

	void				Attach( CObjCHAR* pObjCHAR );
	void				Detach();	
};


#endif //_OBJECT_TARGET_EFFECT_