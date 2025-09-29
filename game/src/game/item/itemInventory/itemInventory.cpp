#include "itemInventory.h"
#include "../itemShotBase.h"

//------------------
//	コンストラクタ
//------------------
CItemInventory::CItemInventory()
{
	Init(nullptr);
}

//------------------
//	  初期化
//------------------
void CItemInventory::Init(CPlayer* _player)
{
	for (int i = 0; i < ITEM_INVENTORY_MAX; i++)
	{
		m_item[i] = nullptr;
	}

	m_itemNum = 0;
	m_player = _player;
}

//------------------
//毎フレームする処理
//------------------
void CItemInventory::Step(CShotManager* _shot)
{
	//アイテムを使用していたら現在選択されているアイテムを使用
	if (m_player->GetIsItemUse() == true &&
		m_item[m_player->GetItemSelectNum()] != nullptr)
	{
		switch (m_item[m_player->GetItemSelectNum()]->GetType())
		{
		case ITEM_TYPE_USE:
			m_item[m_player->GetItemSelectNum()]->Use();
			break;
		case ITEM_TYPE_SHOT:
			CItemShotBase* shotItem = dynamic_cast<CItemShotBase*>(m_item[m_player->GetItemSelectNum()]);
			shotItem->Use(_shot);
			break;
		}
	}
}

//------------------
//	  数値の更新
//------------------
void CItemInventory::Update()
{

}

//------------------
//	  描写処理
//------------------
void CItemInventory::Draw()
{
	if (m_item[0] == nullptr)
	{
		DrawFormatString(32, 128, GetColor(255, 0, 0), "何もない");
		return;
	}

	switch (m_item[0]->GetName())
	{
	case ITEM_FIRE_RING:
		DrawFormatString(32, 128, GetColor(255, 0, 0), "ファイアリング");
		break;
	case ITEM_HARB_AMULENT:
		DrawFormatString(32, 128, GetColor(255, 0, 0), "薬草のお守り");
		break;
	}
}

//アイテムを設定
CItemBase* CItemInventory::SetItem(CItemBase* _item)
{
	//アドレス保存用
	CItemBase* item = nullptr;
	//すでにアイテムが入っている場合交換する
	if (m_item[m_player->GetItemSelectNum()] != nullptr)
	{
		//今のアイテムのアドレスを保存
		item = m_item[m_player->GetItemSelectNum()];
	}

	//インベントリにアイテムのアドレスを取得
	m_item[m_player->GetItemSelectNum()] = _item;

	//アドレスを渡す
	return item;
}
