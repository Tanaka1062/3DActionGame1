#pragma once
#include <iostream>
#include <list>
#include "itemBase.h"
#include "../data.h"
#include "../player/playerManager.h"
#include "itemObject/box/box.h"
#include "mapItemManager.h"
#include "spawnItemManager.h"
#include "../map/map.h"
#include "spawn/spawnCoinManager.h"

//アイテムマネージャークラス
class CItemManager
{
private:
	std::list<std::unique_ptr<CItemBase>> m_item;		//アイテムのクラス
	CMapItemManager m_mapItemManager;					//マップに置いてあるアイテムマネージャー
	CSpawnItemManager m_spawnItemManager;				//スポーンするアイテムのマネージャー
	CSpawnCoinManager m_coinManager;					//コインのマネージャークラス

public:
	//コンストラクタ・デストラクタ
	CItemManager();
	~CItemManager();


	//コピーを禁止する
	CItemManager(const CItemManager&) = delete;
	CItemManager& operator = (const CItemManager&) = delete;

	//moveは許可する
	CItemManager(CItemManager&&) = default;
	CItemManager& operator = (CItemManager&&) = default;

	//初期化
	void Init(CPlayerManager* _playerManager);
	//モデルロード
	void Load();
	//毎フレームする処理
	void Step(CPlayerManager* _playerManager, tagMapCenterId _mapId);
	//数値の更新
	void Update();
	//オブジェクトの描写
	void Draw();
	//終了処理
	void Exit();

	//アイテムの数を取得
	int GetItemNum() { return static_cast<int>(m_item.size()); }

	//アイテムのクラス全体を取得
	std::list<std::unique_ptr<CItemBase>>& GetItemList() { return m_item; };

	//アイテムのアドレスを取得
	CItemBase* GetItem(int _num);

};

