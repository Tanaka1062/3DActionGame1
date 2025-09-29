#include "fireRing.h"
//アイテム関連--------------------------------
static const float SHOT_RADIUS = 5.0f;				//弾の大きさ
static const float SHOT_SPEED = 1.0f;				//弾のスピード
static const int SHOT_ATK = 20;						//弾の攻撃力
static const int SHOT_LOST_TIME = 240;				//弾の消えるまでのスピード
//----------------------------------------------

//-------------------
//	コンストラクタ
//-------------------
CFireRing::CFireRing()
{
	Init(nullptr);
}

//-------------------
//		初期化
//-------------------
void CFireRing::Init(CPlayer* _player)
{
	CItemShotBase::Init(_player);
	m_name = ITEM_FIRE_RING;
}

//-------------------
// 使用した時の処理
//-------------------
void CFireRing::Use(CShotManager* _shot)
{
	_shot->Request(m_player->GetCenter(), m_player->GetRot(),
		SHOT_RADIUS,SHOT_SPEED, SHOT_ATK, SHOT_LOST_TIME);

}

