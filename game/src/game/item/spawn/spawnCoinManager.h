#pragma once
#include <iostream>
#include <vector>
#include "../../data.h"
#include "../../player/playerManager.h"
#include "../coin/coin.h"
#include "../../map/map.h"
#include "../itemBase.h"

constexpr int SPAWN_ITEM_MAX = 20;		//アイテムの最大量

//アイテムマネージャークラス
class CSpawnCoinManager
{
private:

	struct tagSpawnData									//スポーンデータ
	{
		VECTOR pos;										//出現する座標
		bool isSpawn;									//出現したかどうか
	};

	std::vector<std::unique_ptr<CItemBase>> m_coin;			//コイン保存用
	int m_hndl;											//アイテムのモデルハンドル
	int m_spawnTime;									//時間カウント
	bool m_isItemSpawn;									//アイテムがスポーンするかどうか
	std::vector<std::vector<tagSpawnData>> m_spawnData;	//アイテムのスポーン情報
public:
	//コンストラクタ・デストラクタ
	CSpawnCoinManager();
	~CSpawnCoinManager();

	//コピーを禁止する
	CSpawnCoinManager(const CSpawnCoinManager&) = delete;
	CSpawnCoinManager& operator=(const CSpawnCoinManager&) = delete;

	//moveは許可する
	CSpawnCoinManager(CSpawnCoinManager&&) = default;
	CSpawnCoinManager& operator=(CSpawnCoinManager&&) = default;

	//初期化
	void Init(CPlayerManager* _playerManager);
	//モデルロード
	void Load();
	//毎フレームする処理
	void Step();
	//終了処理
	void Exit();

	//アイテムの数を取得
	int GetItemNum() { return static_cast<int>(m_coin.size()); }

	//アイテムのアドレスを取得
	CItemBase* GetItem(int _num);

	//アイテムを出現させる
	std::unique_ptr<CItemBase> SpawnItem(tagMapCenterId _mapId);

	//コインを出現させる
	std::unique_ptr<CItemBase> SpawnCoin();

	//アイテムがスポーンするかを取得
	bool GetIsItemSpawn() { return m_isItemSpawn; }

	//アイテムを元に戻す
	void ReturnItem(std::unique_ptr<CItemBase> _returnItme);

};

