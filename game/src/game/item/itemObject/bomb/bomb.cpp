#include "bomb.h"
#include "../../../attack/attackManager.h"
#include "../../../../lib/effekseer/effekseer.h"
#include "../../../system/effectData/effectData.h"
#include "../../../system/sound/soundManager.h"

constexpr int EXPLOSION_TIME = 5 * 60;				//爆発する時間
constexpr int EXPLOSION_IN_TIME = 1 * 60;			//爆発する前の時間
constexpr float EXPLOSION_RADIUS = 60.0f;			//爆発の半径
constexpr float POWER_UP_EXPLOSION_RADIUS = 1.0f;	//パワーアップ後の爆発の半径
constexpr int EXPLOSION_ATK = 50;					//爆発の攻撃力
constexpr int COST = 0;								//価格

//アニメーション一覧----------------------------------
enum tagAnim
{
	ANIMID_DEFAULT,			//デフォルト
	ANIMID_EXPLOSION_IN,	//爆発前
};
//----------------------------------------------------

CBomb::CBomb()
{
	m_timeCount = 0;
}

//---------------------
//		  初期化
//---------------------
void CBomb::Init()
{
	CItemObjectBase::Init();

	m_timeCount = 0;
	m_cost = COST;
	m_itemName = ITEM_BOMB;
}

//---------------------
// 毎フレームする処理
//---------------------
void CBomb::Step()
{
	CItemObjectBase::Step();

	if (m_isActive == false)return;

	m_timeCount++;

	if (EXPLOSION_TIME - m_timeCount <= EXPLOSION_IN_TIME &&
		m_animData.m_id != ANIMID_EXPLOSION_IN)
	{
		RequestAnim(ANIMID_EXPLOSION_IN, 1.0f, true);
	}

	//爆発時間を過ぎたら爆時させる
	if (m_timeCount >= EXPLOSION_TIME)
	{
		CSoundManager::Play(CSoundManager::SE_EXPLOSION, DX_PLAYTYPE_BACK);
		m_isActive = false;
		m_timeCount = 0;
		m_isLift = false;

		Explosion();
	}
}

//---------------------
//		 壊れる
//---------------------
void CBomb::Break()
{
	m_timeCount = 0;
	m_isActive = false;
	m_isLift = false;

	Explosion();
}

//---------------------
//		 爆発
//---------------------
void CBomb::Explosion()
{
	VECTOR explosionPos = m_pos;

	explosionPos.y -= EXPLOSION_RADIUS;

	//呼び出すエフェクトのID
	int effectId = CEffectData::GetId(EFFECT_EXPLOSION);

	//エフェクトを呼び出す
	CEffekseerCtrl::Request(effectId, m_pos, false);

	CAttackManager* attack = CAttackManager::GetInstance();

	attack->Request(explosionPos, EXPLOSION_RADIUS, EXPLOSION_ATK,100, PLAYER_NONE);

	RequestAnim(ANIMID_DEFAULT, 1.0f, true);
}

