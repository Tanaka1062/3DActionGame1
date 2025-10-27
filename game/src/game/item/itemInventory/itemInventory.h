#pragma once

#include "../itemBase.h"
#include "../../player/playerManager.h"


//アイテムのインベントリ
class CItemInventory
{
private:
	CItemBase* m_useItem[PLAYER_ID_NUM];		//使用するアイテム
	CItemBase* m_skillItem[PLAYER_ID_NUM];		//スキルアイテム
	CPlayer* m_player[PLAYER_ID_NUM];			//プレイヤーのアドレス保存用

public:
	CItemInventory();

	//初期化
	void Init(CPlayerManager& _player);
	//毎フレームする処理
	void Step(CShotManager* _shot);
	//数値の更新
	void Update();
	//描写処理
	void Draw();
	
	//アイテムを設定
	CItemBase* SetItem(CItemBase* _item,CPlayer& _player); 

};

