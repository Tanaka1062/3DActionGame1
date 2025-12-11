#include "itemWeaponBase.h"

CWeaponBase::CWeaponBase()
{
	CItemBase::Init();
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
	m_weaponDurability = 0;
}

//毎フレームする処理
void CWeaponBase::Step()
{
	CItemBase::Step();
}

//当たった時の処理
void CWeaponBase::HitCalc(CObject* _hitObject)
{

	//プレイヤーの場合の処理-----------------------------------
	if (_hitObject->GetObjectType() == OBJECT_PLAYER)
	{
		CPlayer* player = nullptr;

		player = dynamic_cast<CPlayer*>(_hitObject);

		//プレイヤーがアイテムを取ろうとしていてなおかつ武器を持ってなかったらする処理
		if (player->GetItemState() == ITEM_STATE_PICK_UP &&
			player->GetWeaponId() == WEAPON_ID_HAND)
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
					m_owner = player;
					player->SetWeaponId(m_id);
					player->SetWeaponDurability(m_weaponDurability);
					m_isActive = false;
				}

			}
		}

	}

	//---------------------------------------------------------
}
