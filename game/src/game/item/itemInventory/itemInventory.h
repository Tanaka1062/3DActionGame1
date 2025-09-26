#pragma once

#include "../itemBase.h"
#include "../../player/player.h"


//アイテムのインベントリ
class CItemInventory
{
private:
	CItemBase* m_item[ITEM_INVENTORY_MAX];		//アイテム
	int m_itemNum;								//選択されているアイテムの番号
	CPlayer* m_player;							//プレイヤーのアドレス保存用

public:
	CItemInventory();

	//初期化
	void Init(CPlayer* _player);
	//毎フレームする処理
	void Step();
	//数値の更新
	void Update();
	
	//アイテムを設定
	void SetItem(CItemBase* _item) { m_item[m_player->GetItemSelectNum()] = _item; }

};

