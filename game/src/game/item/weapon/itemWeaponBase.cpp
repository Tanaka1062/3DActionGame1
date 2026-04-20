#include "itemWeaponBase.h"
#include "../../system/soundManager.h"

constexpr float ROT_SPEED = 0.01f;				//回転速度

CWeaponBase::CWeaponBase()
{
	Init();
}

CWeaponBase::~CWeaponBase()
{
	CItemBase::Exit();
}

//初期化
void CWeaponBase::Init()
{
	CItemBase::Init();

	m_id = WEAPON_ID_HAND;
	m_durability = 0;
	m_itemType = ITEM_TYPE_WEAPON;
}

//毎フレームする処理
void CWeaponBase::Step()
{
	CItemBase::Step();

	m_rot.y += ROT_SPEED;
}

//当たった時の処理
void CWeaponBase::HitCalc(CObject* _hitObject)
{

	//プレイヤーの場合の処理-----------------------------------
	if (_hitObject->GetObjectName() == OBJECT_PLAYER)
	{
		CPlayer* player = nullptr;

		player = dynamic_cast<CPlayer*>(_hitObject);

		//プレイヤーが武器を持ってなかったらする処理
		if (player->GetWeaponId() == WEAPON_ID_HAND)
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
						if (m_cost > 0)
						{
							CSoundManager::Play(CSoundManager::SE_BUY, DX_PLAYTYPE_BACK);
						}

						isPickUp = true;
					}
				}
				else
				{
					isPickUp = true;

				}

				if (isPickUp == true)
				{
					player->SetWeaponId(m_id);
					player->SetWeaponDurability(m_durability);
					m_isActive = false;
				}

			}
		}

	}

	//---------------------------------------------------------
}

