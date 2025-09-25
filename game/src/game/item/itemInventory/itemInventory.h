#pragma once

#include "../itemBase.h"
#include "../../player/player.h"

static const int ITEM_INVENTORY_NUM = 1;	//アイテムインベントリの数

//アイテムのインベントリ
class CItemInventory
{
private:
	CItemBase m_item[ITEM_INVENTORY_NUM];		//アイテム
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

};

