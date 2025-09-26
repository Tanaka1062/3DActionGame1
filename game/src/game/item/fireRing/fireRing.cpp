#include "fireRing.h"
//アイテム関連--------------------------------
static const float SHOT_SIZE = 3.0f;				//弾の大きさ
static const float SHOT_SPEED = 3.0f;				//弾のスピード
static const int SHOT_ATK = 10;						//弾の攻撃力
static const int SHOT_LOST_TIME = 240;				//弾の消えるまでのスピード
//----------------------------------------------

//初期化
void CFireRing::Init(CPlayer* _player)
{
	CItemBase::Init(_player);
	m_name = ITEM_FIRE_RING;
	m_type = TYPE_SHOT;
}

//使用した時の処理
void CFireRing::Use()
{


}

