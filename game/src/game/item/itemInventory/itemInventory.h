#pragma once

#include "../itemBase.h"
#include "../../player/playerManager.h"
#include "../../lib/input/controllerManager.h"

//アイテムのインベントリ
class CItemInventory
{
private:
	CItemBase* m_useItem[PAD_NUM];		//使用するアイテム
	CItemBase* m_skillItem[PAD_NUM];	//スキルアイテム
	CPlayer* m_player[PAD_NUM];			//プレイヤーのアドレス保存用

public:
	CItemInventory();

	//初期化
	void Init(CPlayerManager* _playerManager);
	//毎フレームする処理
	void Step(CShotManager* _shot);
	//数値の更新
	void Update();
	//描写処理
	void Draw();
	
	//アイテムを設定
	CItemBase* SetItem(CItemBase* _item,CPlayer* _player); 

};

