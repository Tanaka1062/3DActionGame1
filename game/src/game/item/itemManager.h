#pragma once
#include <iostream>
#include <list>
#include "itemBase.h"
#include "../data.h"
#include "../player/playerManager.h"
#include "coin/coin.h"
#include "itemObject/box/box.h"
#include "mapItemManager.h"
#include "spawnItemManager.h"

using namespace std;

//アイテムマネージャークラス
class CItemManager
{
private:
	list<CItemBase*> m_item;							//アイテムのクラス
	CMapItemManager m_mapItemManager;					//マップに置いてあるアイテムマネージャー
	CSpawnItemManager m_spawnItemManager;				//スポーンするアイテムのマネージャー

public:
	//コンストラクタ・デストラクタ
	CItemManager();
	~CItemManager();

	//初期化
	void Init(CPlayerManager* _playerManager);
	//モデルロード
	void Load();
	//毎フレームする処理
	void Step(CPlayerManager* _playerManager);
	//数値の更新
	void Update();
	//オブジェクトの描写
	void Draw();
	//終了処理
	void Exit();

	//アイテムの数を取得
	int GetItemNum() { return static_cast<int>(m_item.size()); }

	//アイテムのアドレスを取得
	CItemBase* GetItem(int _num);

};

