#include "itemShotBase.h"

//-------------------
//	コンストラクタ
//-------------------
CItemShotBase::CItemShotBase()
{
	Init(nullptr);
}

//-------------------
//		初期化
//-------------------
void CItemShotBase::Init(CPlayer* _player)
{
	CItemBase::Init(_player);
	m_type = TYPE_SHOT;

}

