#pragma once
#include <iostream>
#include <vector>
#include "itemBase.h"
#include "../data.h"
#include "../player/playerManager.h"
#include "coin/coin.h"
#include "itemObject/box/box.h"

using namespace std;

enum tagItemSpawnPos
{
	ITEM_SPAWN_POS_1,		//アイテムの出現座標1
	ITEM_SPAWN_POS_2,		//アイテムの出現座標2
	ITEM_SPAWN_POS_3,		//アイテムの出現座標3
	ITEM_SPAWN_POS_4,		//アイテムの出現座標4
	ITEM_SPAWN_POS_5,		//アイテムの出現座標5
	ITEM_SPAWN_POS_6,		//アイテムの出現座標6
	ITEM_SPAWN_POS_7,		//アイテムの出現座標7
	ITEM_SPAWN_POS_8,		//アイテムの出現座標8

	ITEM_SPAWN_POS_NUM,		//アイテムの出現座標の数
};

static const int SPAWN_ITEM_MAX = 10;		//アイテムの最大量

//アイテムマネージャークラス
class CSpawnItemManager
{
private:
	//vector<CItemBase*> m_item;							//アイテムのクラス
	vector<unique_ptr<CItemBase>> m_item;
	int m_hndl[ITEM_NUM];								//アイテムのモデルハンドル
	int m_spawnTime;									//時間カウント
	bool m_isItemSpawn;									//アイテムがスポーンするかどうか
	bool m_isSpawnPos[ITEM_SPAWN_POS_NUM];				//その座標でアイテムが出現したかどうか
	VECTOR m_spawnPos[ITEM_SPAWN_POS_NUM];				//アイテムの出現座標
public:
	//コンストラクタ・デストラクタ
	CSpawnItemManager();
	~CSpawnItemManager();

	//コピーを禁止する
	CSpawnItemManager(const CSpawnItemManager&) = delete;
	CSpawnItemManager& operator=(const CSpawnItemManager&) = delete;

	//moveは許可する
	CSpawnItemManager(CSpawnItemManager&&) = default;
	CSpawnItemManager& operator=(CSpawnItemManager&&) = default;

	//初期化
	void Init(CPlayerManager* _playerManager);
	//モデルロード
	void Load();
	//毎フレームする処理
	void Step();
	//終了処理
	void Exit();

	//アイテムの数を取得
	int GetItemNum() { return static_cast<int>(m_item.size()); }

	//アイテムのアドレスを取得
	CItemBase* GetItem(int _num);

	//アイテムを出現させる
	CItemBase* SpawnItem();

	//アイテムがスポーンするかを取得
	bool GetIsItemSpawn() { return m_isItemSpawn; }

	//アイテムを元に戻す
	void ReturnItem(CItemBase* _returnItme);

};

