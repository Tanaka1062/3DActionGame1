#include "itemInventory.h"

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
	//for (int i = 0; i < ITEM_INVENTORY_MAX; i++)
	//{
	//	m_item[i]->Init(nullptr);
	//}

	m_itemNum = 0;
	m_player = _player;
}

//------------------
//毎フレームする処理
//------------------
void CItemInventory::Step()
{
	//アイテムを使用していたら現在選択されているアイテムを使用
	if (m_player->GetIsItemUse() == true)
	{
		m_item[m_player->GetItemSelectNum()]->Use();
	}
}

//------------------
//	  数値の更新
//------------------
void CItemInventory::Update()
{

}

//アイテムを設定
void CItemInventory::SetItem(CItemBase* _item)
{
	//すでにアイテムが入っている場合消す
	if (m_item[m_player->GetItemSelectNum()] != nullptr)
	{
		delete m_item[m_player->GetItemSelectNum()];
	}

	//アイテムのコピーを作成し設定
	m_item[m_player->GetItemSelectNum()] = new CItemBase(*_item);
}
