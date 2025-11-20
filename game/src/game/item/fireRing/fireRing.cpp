#include "fireRing.h"
#include "../../system/effectData/effectData.h"
#include "../../lib/effekseer/effekseer.h"

//アイテム関連--------------------------------
static const int SHOT_NUM = 3;						//弾を撃つ回数
static const float SHOT_RADIUS = 2.0f;				//弾の大きさ
static const float SHOT_SPEED = 2.0f;				//弾のスピード
static const int SHOT_ATK = 10;						//弾の攻撃力
static const int SHOT_LOST_TIME = 60;				//弾の消えるまでのスピード
//----------------------------------------------
static const int USE_MAX = 10;		//使用回数

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
}

//-------------------
// 使用した時の処理
//-------------------
void CFireRing::Use(CShotManager* _shot)
{

	for (int i = 0; i < SHOT_NUM; i++)
	{
		VECTOR shotPos = m_player->GetCenter();
		shotPos.y += static_cast<float>(i * 5);
		
		//呼び出すエフェクトのID
		int effectId = CEffectData::GetId(EFFECT2);

		//エフェクトのハンドル
		int effectHndl = CEffekseerCtrl::Request(effectId, GetCenter(), false);

		_shot->Request(shotPos, m_player->GetRot(),
			SHOT_RADIUS,SHOT_SPEED, SHOT_ATK, SHOT_LOST_TIME, effectHndl);

	}


}

