#include "itemShotBase.h"

//-------------------
//	コンストラクタ
//-------------------
CItemShotBase::CItemShotBase()
{
	Init(nullptr, nullptr);
}

//-------------------
//		初期化
//-------------------
void CItemShotBase::Init(CPlayer* _player, CShotManager* _shot)
{
	CItemBase::Init(_player);
	m_type = TYPE_SHOT;
	m_shot = _shot;

}

