#pragma once
#include <iostream>
#include <vector>
#include "../../data.h"
#include "../../player/playerManager.h"
#include "../../map/map.h"
#include "../itemBase.h"

//アイテムマネージャークラス
class CSpawnCoinManager
{
private:

	std::vector<std::unique_ptr<CItemBase>> m_mapCoin;		//マップのコイン保存用
	std::vector<std::unique_ptr<CItemBase>> m_dropCoin;		//ドロップするコイン保存用
	int m_hndl;											//アイテムのモデルハンドル
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
	void Init();
	//モデルロード
	void Load();
	//毎フレームする処理
	void Step();
	//終了処理
	void Exit();

	//マップのコインの数を取得
	int GetMapCoinNum() { return static_cast<int>(m_mapCoin.size()); }

	//マップのコインのアドレスを取得
	std::unique_ptr<CItemBase> GetMapCoin(int _num);

	//コインを出現させる
	std::unique_ptr<CItemBase> SpawnCoin();

	//アイテムを元に戻す
	void ReturnItem(std::unique_ptr<CItemBase> _returnItme);

	//ハンドルを取得
	int GetHndl() { return m_hndl; }

};

