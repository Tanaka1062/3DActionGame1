#pragma once
#include <iostream>
#include <vector>
#include "itemBase.h"
#include "../data.h"
#include "../player/playerManager.h"
#include "coin/coin.h"
#include "itemObject/box/box.h"
#include "../map/map.h"

enum tagItemSpawnPos
{
	//ITEM_SPAWN_POS_1,		//アイテムの出現座標1
	//ITEM_SPAWN_POS_2,		//アイテムの出現座標2
	//ITEM_SPAWN_POS_3,		//アイテムの出現座標3
	//ITEM_SPAWN_POS_4,		//アイテムの出現座標4
	//ITEM_SPAWN_POS_5,		//アイテムの出現座標5
	//ITEM_SPAWN_POS_6,		//アイテムの出現座標6
	//ITEM_SPAWN_POS_7,		//アイテムの出現座標7
	//ITEM_SPAWN_POS_8,		//アイテムの出現座標8
	//ITEM_SPAWN_POS_9,		//アイテムの出現座標9
	//ITEM_SPAWN_POS_10,		//アイテムの出現座標10
	//ITEM_SPAWN_POS_11,		//アイテムの出現座標11
	//ITEM_SPAWN_POS_12,		//アイテムの出現座標12
	//ITEM_SPAWN_POS_13,		//アイテムの出現座標13
	//ITEM_SPAWN_POS_14,		//アイテムの出現座標14
	//ITEM_SPAWN_POS_15,		//アイテムの出現座標15
	//ITEM_SPAWN_POS_16,		//アイテムの出現座標16
	MAP1_SPAWN_POS_NUM,			//マップ１のアイテムのスポーン場所の数
	MAP2_SPAWN_POS_NUM,			//マップ２のアイテムのスポーン場所の数

	ITEM_SPAWN_POS_NUM,		//アイテムの出現座標の数
};


constexpr int MAP1_SPAWN_POS_NUM = 8;		//マップ１のアイテムのスポーン場所の数
constexpr int MAP2_SPAWN_POS_NUM = 8;		//マップ２のアイテムのスポーン場所の数
constexpr int SPAWN_POS_ALL_NUM =			//アイテムのスポーン場所の総数
MAP1_SPAWN_POS_NUM + MAP2_SPAWN_POS_NUM;

constexpr int SPAWN_ITEM_MAX = 10;		//アイテムの最大量

//アイテムマネージャークラス
class CSpawnItemManager
{
private:

	struct tagSpawnData									//スポーンデータ
	{
		VECTOR pos;										//出現する座標
		bool isSpawn;									//出現したかどうか
	};

	std::vector<std::unique_ptr<CItemBase>> m_item;		//アイテム保存用
	std::vector<int> m_spawnProbability;				//アイテムの出現確率
	int m_hndl[ITEM_NUM];								//アイテムのモデルハンドル
	int m_spawnTime;									//時間カウント
	bool m_isItemSpawn;									//アイテムがスポーンするかどうか
	bool m_isSpawnPos[ITEM_SPAWN_POS_NUM];				//その座標でアイテムが出現したかどうか
	VECTOR m_spawnPos[ITEM_SPAWN_POS_NUM];				//アイテムの出現座標
	std::vector<std::vector<tagSpawnData>> m_spawnData;	//アイテムのスポーン情報
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
	std::unique_ptr<CItemBase> SpawnItem();

	//コインを出現させる
	std::unique_ptr<CItemBase> SpawnCoin();

	//アイテムがスポーンするかを取得
	bool GetIsItemSpawn() { return m_isItemSpawn; }

	//アイテムを元に戻す
	void ReturnItem(std::unique_ptr<CItemBase> _returnItme);

};

