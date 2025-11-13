#pragma once
#include <iostream>
#include <list>
#include "itemBase.h"
#include "../data.h"
#include "../player/playerManager.h"
#include "../shot/shotManager.h"
#include "itemShotBase.h"

using namespace std;


//アイテムマネージャークラス
class CItemManager
{
private:
	list<CItemBase*> m_item;				//アイテムのクラス
	int m_hndl[ITEM_NUM];					//アイテムのモデルハンドル
	CShotManager* m_shot;					//弾のマネージャーのアドレス保存用
public:
	//コンストラクタ・デストラクタ
	CItemManager();
	~CItemManager();

	//初期化
	void Init(CShotManager* _shot);
	//モデルロード
	void Load();
	//毎フレームする処理
	void Step();
	//数値の更新
	void Update();
	//オブジェクトの描写
	void Draw();
	//終了処理
	void Exit();

	//アイテムの数を取得
	int GetNum() { return static_cast<int>(m_item.size()); }

	//アイテムのアドレスを取得
	CItemBase* GetItem(int _num);

	//アイテムを設定
	void SetItem(int _num, CItemBase* _item,CPlayer* _player);

	//アイテムを出現させる
	// _pos		:出現させるアイテムの位置
	// _name	:出現させるアイテムの名前
	//			:名前を入力しない場合ランダムなアイテムが出現する
	void SpawnItem(VECTOR _pos, tagItemName _name = ITEM_NONE);
};

