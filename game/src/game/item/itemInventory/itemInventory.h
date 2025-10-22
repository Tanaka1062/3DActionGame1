#pragma once

#include "../itemBase.h"
#include "../../player/player.h"


//アイテムのインベントリ
class CItemInventory
{
private:
	CItemBase* m_useItem;	//使用するアイテム
	CItemBase* m_skillItem;	//スキルアイテム
	CPlayer* m_player;		//プレイヤーのアドレス保存用

public:
	CItemInventory();

	//初期化
	void Init(CPlayer* _player);
	//毎フレームする処理
	void Step(CShotManager* _shot);
	//数値の更新
	void Update();
	//描写処理
	void Draw();
	
	//アイテムを設定
	CItemBase* SetItem(CItemBase* _item); 

};

