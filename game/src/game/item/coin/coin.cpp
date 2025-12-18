#include "coin.h"
#include "../../lib/myMath/myMath.h"

constexpr float ROT_SPEED = 0.05f;			//回転速度
constexpr int ADD_MONEY = 1;				//増えるお金の量

CCoin::CCoin()
{
	m_state = ITEM_WAIT;
}

CCoin::~CCoin()
{
	
}

//---------------------
//		 初期化
//---------------------
void CCoin::Init()
{
	CItemBase::Init();


	m_isActive = false;
	m_itemType = ITEM_TYPE_COIN;
	m_isPushed = false;
	m_itemName = ITEM_COIN;
}

//---------------------
// 毎フレームする処理
//---------------------
void CCoin::Step()
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
//		数値の更新
//---------------------
void CCoin::Update()
{
	CItemBase::Update();

}

//---------------------
//	当たった時の処理
//---------------------
void CCoin::HitCalc(CObject* _hitObject)
{
	//_hitObjectがnullだったら処理をしない
	if (_hitObject == nullptr)return;

	//プレイヤーの場合の処理----------------------------------
	if (_hitObject->GetObjectType() == OBJECT_PLAYER)
	{
		//飛んでいる場合は処理をしない
		if (m_state == ITEM_FLYING)return;

		//プレイヤーデータ保存用
		CPlayer* player = nullptr;

		//プレイヤークラスにダウンキャストする
		player = dynamic_cast<CPlayer*>(_hitObject);

		//プレイヤーをパワーアップさせる
		player->AddMoney(ADD_MONEY);

		m_isActive = false;
		m_owner = player;
	}
	//--------------------------------------------------------

}

//---------------------
//	   コインの消失
//---------------------
void CCoin::Delete()
{
	m_state = ITEM_WAIT;
	m_isSpawn = true;
}

