#include "itemObjectBase.h"
#include "../../../lib/myMath/myMath.h"
	
constexpr float THROW_SPEED = 12.0f;				//投げられるスピード
constexpr float RADIUS = 10.0f;						//半径

CItemObjectBase::CItemObjectBase()
{
	m_isLift = false;
}

//初期化
void CItemObjectBase::Init()
{
	CItemBase::Init();

	m_rad = RADIUS;
	m_isLift = false;
	m_isDrop = false;
	m_isPushed = true;
	m_itemType = ITEM_TYPE_OBJECT;
}

//毎フレームする処理
void CItemObjectBase::Step()
{
	if (m_isActive == false)
	{
		m_isDrop = false;
	}

	//持ち上げられていたらプレイヤーについていく
	if (m_isLift == true)
	{
		m_isGravity = false;

		//当たり判定を小さくする
		m_rad = 1.0f;

		CPlayer* player = nullptr;
		player = dynamic_cast<CPlayer*>(m_owner);
		
		m_pos = player->GetItemHavePos();

		//アイテムを手放したら落とす
		if (player->GetItemState() == PlayerData::ITEM_STATE_NONE)
		{
			m_owner = nullptr;
			m_isLift = false;
		}

		//アイテムを落としていたら
		if (player->GetItemState() == PlayerData::ITEM_STATE_DROP)
		{
			m_isDrop = true;
			m_owner = nullptr;
			m_isLift = false;
		}

		//投げられたいたら投げる処理にする
		if (player->GetItemState() == PlayerData::ITEM_STATE_THROW)
		{
			m_isLift = false;
			m_isDrop = true;

			//角度ゼロで進む速度
			VECTOR defaultDir = { 0.0f,-0.5f,-THROW_SPEED };
			//上記を行列に変換する
			MATRIX dir = CMyMath::GetTranslateMatrix(defaultDir);
			//Y軸回転行列
			MATRIX mRotY = CMyMath::GetYawMatrix(player->GetRot().y);
			//行列の合成
			MATRIX res = CMyMath::MatMult(mRotY, dir);

			//移動をスピードに代入
			m_speed.x = res.m[0][3];
			m_speed.y = res.m[1][3];
			m_speed.z = res.m[2][3];

			m_state = ITEM_FLYING;
			m_owner = nullptr;
			m_isGravity = true;
		}

	}
	else
	{
		m_isGravity = true;
		m_rad = RADIUS;
	}

	//飛んでいる状態ならだんだん速度を落とす
	if (m_state == ITEM_FLYING)
	{
		m_speed.x *= 0.91f;
		m_speed.z *= 0.91f;

		VECTOR speed = m_speed;

		speed.y = 0.0f;

		float speedLen = VSize(speed);

		if (speedLen <= 0.1f)
		{
			m_speed.x = 0.0f;
			m_speed.z = 0.0f;
			m_state = ITEM_WAIT;
			m_isGravity = true;
		}

	}

	CItemBase::Step();

}

//--------------------------
//	  当たった時の処理
//--------------------------
void CItemObjectBase::HitCalc(CObject* _hitObject)
{

	//プレイヤーの場合の処理------------------------------
	if (_hitObject->GetObjectName() == OBJECT_PLAYER)
	{

		CPlayer* player = nullptr;

		player = dynamic_cast<CPlayer*>(_hitObject);

		//プレイヤーがアイテムを取ろうとしていたらする処理
		if (player->GetItemState() == PlayerData::ITEM_STATE_PICK_UP &&
			player->GetWeaponId() == PlayerData::WEAPON_ID_HAND)
		{
			//誰にも持たれていなかったら購入できる
			if (m_owner == nullptr)
			{
				bool isPickUp = false;

				if (m_isBuy == false)
				{
					//お金が足りたら持ち上げれる
					if (player->SubMoney(m_cost) == true)
					{
						isPickUp = true;
					}
				}
				else
				{
					isPickUp = true;

				}

				if (isPickUp == true)
				{
					m_isBuy = true;
					m_isLift = true;
					m_owner = player;
					player->SetItemState(PlayerData::ITEM_STATE_GET);
				}

			}
		}

		//アイテムが飛んでいる状態なら壊れる
		if (m_state == ITEM_FLYING)
		{
			Break();
		}

	}
	//----------------------------------------------------
}

//--------------------------
//			壊れる
//--------------------------
void CItemObjectBase::Break()
{
	m_isActive = false;
}

