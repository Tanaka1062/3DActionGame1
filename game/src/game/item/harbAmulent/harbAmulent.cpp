#include "harbAmulent.h"

static const int ADD_HP = 10;		//体力の回復量

//-------------
//コンストラクタ
//-------------
CHarbAmulent::CHarbAmulent()
{
	Init(nullptr);
}

//-------------
//	 初期化
//-------------
void CHarbAmulent::Init(CPlayer* _player)
{
	CItemBase::Init(_player);
	m_type = TYPE_USE;
	m_name = ITEM_HARB_AMULENT;
}

//-------------
//使用した時の処理
//-------------
void CHarbAmulent::Use()
{
	m_player->AddHp(ADD_HP);
}
