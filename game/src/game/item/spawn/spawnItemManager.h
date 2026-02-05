#pragma once
#include <iostream>
#include <vector>
#include "../itemBase.h"
#include "../../data.h"
#include "../../player/playerManager.h"
#include "../coin/coin.h"
#include "../itemObject/box/box.h"
#include "../../map/map.h"

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

	//アイテムを出現させる
	std::unique_ptr<CItemBase> SpawnItem(tagMapCenterId _mapId);

	//アイテムがスポーンするかを取得
	bool GetIsItemSpawn() { return m_isItemSpawn; }

	//アイテムを元に戻す
	void ReturnItem(std::unique_ptr<CItemBase> _returnItme);

};

