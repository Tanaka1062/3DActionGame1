#include "fireRing.h"
//アイテム関連--------------------------------
static const float SHOT_SIZE = 3.0f;				//弾の大きさ
static const float SHOT_SPEED = 3.0f;				//弾のスピード
static const int SHOT_ATK = 10;						//弾の攻撃力
static const int SHOT_LOST_TIME = 240;				//弾の消えるまでのスピード
//----------------------------------------------

//-------------------
//	コンストラクタ
//-------------------
CFireRing::CFireRing()
{
	Init(nullptr, nullptr);
}

//-------------------
//		初期化
//-------------------
void CFireRing::Init(CPlayer* _player, CShotManager* _shot)
{
	CItemShotBase::Init(_player, _shot);
	m_name = ITEM_FIRE_RING;
}

//-------------------
// 使用した時の処理
//-------------------
void CFireRing::Use()
{
	m_shot->Request(m_player->GetCenter(), m_player->GetRot(),
		SHOT_SPEED, SHOT_ATK, SHOT_LOST_TIME);

}

