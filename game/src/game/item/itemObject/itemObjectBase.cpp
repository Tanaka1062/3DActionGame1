#include "itemObjectBase.h"

CItemObjectBase::CItemObjectBase()
{
	m_isLift = false;
}

//初期化
void CItemObjectBase::Init(CPlayer* _player)
{
	CItemBase::Init(_player);

	m_isLift = false;
	m_itemType = ITEM_TYPE_OBJECT;
}

//毎フレームする処理
void CItemObjectBase::Step()
{
	if (m_isActive == true)
	{
		m_isSpawn = false;
	}
	else
	{
		m_isSpawn = true;
	}

	if (m_isLift == true)
	{
		CPlayer* player = nullptr;
		player = dynamic_cast<CPlayer*>(m_owner);
		
		m_pos = player->GetItemHavePos();

		if (player->GetItemState() == ITEM_STATE_NONE)
		{
			m_isLift = false;
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
	if (_hitObject->GetObjectType() == OBJECT_PLAYER)
	{

		CPlayer* player = nullptr;

		player = dynamic_cast<CPlayer*>(_hitObject);

		//プレイヤーがアイテムを取ろうとしていたらする処理
		if (player->GetItemState() == ITEM_STATE_PICK_UP)
		{
			m_isLift = true;
			m_owner = player;
			player->SetItemState(ITEM_STATE_GET);
		}

	}
	//----------------------------------------------------
}

