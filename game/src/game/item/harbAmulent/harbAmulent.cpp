#include "harbAmulent.h"
#include "../../system/effectData/effectData.h"
#include "../../lib/effekseer/effekseer.h"

static const int ADD_HP = 50;		//体力の回復量
static const int USE_MAX = 3;		//使用回数

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
	m_type = ITEM_TYPE_SKILL;
	m_name = ITEM_HARB_AMULENT;
	m_useCount = USE_MAX;
}

//-------------
//使用した時の処理
//-------------
void CHarbAmulent::Use()
{
	//if (m_useCount <= 0)return;
	//m_useCount--;

	////呼び出すエフェクトのID
	//int effectId = CEffectData::GetId(EFFECT_HEAL);

	////エフェクトのハンドル
	//int effectHndl = CEffekseerCtrl::Request(effectId, m_player->GetPos(), false);

	//m_player->AddHp(ADD_HP);

	m_player->SetWeaponId(WEAPON_ID_SWORD);
}
