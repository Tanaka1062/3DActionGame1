#include "coinBase.h"
#include "../../../lib/myMath/myMath.h"
#include "../../system/sound/soundManager.h"
#include "../../../lib/effekseer/effekseer.h"
#include "../../system/effectData/effectData.h"

constexpr float ROT_SPEED = 0.05f;			//回転速度
constexpr int	ADD_MONEY = 1;				//増えるお金の量

CCoinBase::CCoinBase()
{
	m_state = ITEM_WAIT;
}

CCoinBase::~CCoinBase()
{
	
}

//---------------------
//		 初期化
//---------------------
void CCoinBase::Init()
{
	CItemBase::Init();

	m_isActive = false;
	m_itemType = ITEM_TYPE_COIN;
}

//---------------------
// 毎フレームする処理
//---------------------
void CCoinBase::Step()
{
	//少しずつ回転させる
	m_rot.y += ROT_SPEED;

	//コインを飛ばす
	if (m_state == ITEM_FLYING)
	{
		m_speed.x *= 0.9f;
		m_speed.z *= 0.9f;

		VECTOR speed = m_speed;

		speed.y = 0.0f;

		float speedLen = VSize(speed);

		if (speedLen <= 0.1f)
		{
			m_speed.x = 0.0f;
			m_speed.z = 0.0f;
			m_state = ITEM_WAIT;
		}
	}

	CItemBase::Step();
}

//---------------------
//	当たった時の処理
//---------------------
void CCoinBase::HitCalc(CObject* _hitObject)
{
	//_hitObjectがnullだったら処理をしない
	if (_hitObject == nullptr)return;

	//プレイヤーの場合の処理----------------------------------
	if (_hitObject->GetObjectName() == OBJECT_PLAYER)
	{
		//飛んでいる場合は処理をしない
		if (m_state == ITEM_FLYING)return;

		CSoundManager::Play(CSoundManager::SE_COINGET, DX_PLAYTYPE_BACK);
		//プレイヤーデータ保存用
		CPlayer* player = nullptr;

		//プレイヤークラスにダウンキャストする
		player = dynamic_cast<CPlayer*>(_hitObject);

		//プレイヤーのお金を増やす
		player->AddMoney(ADD_MONEY);

		m_isActive = false;
		m_owner = player;
	}
	//--------------------------------------------------------

}

//---------------------
//	   コインの消失
//---------------------
void CCoinBase::Delete()
{
	m_state = ITEM_WAIT;
}

