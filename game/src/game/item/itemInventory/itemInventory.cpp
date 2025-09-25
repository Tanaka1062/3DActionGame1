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
	for (int i = 0; i < ITEM_INVENTORY_NUM; i++)
	{
		m_item[i].Init();
	}

	m_itemNum = 0;
	m_player = _player;
}

//------------------
//毎フレームする処理
//------------------
void CItemInventory::Step()
{
	
}

//------------------
//	  数値の更新
//------------------
void CItemInventory::Update()
{

}

