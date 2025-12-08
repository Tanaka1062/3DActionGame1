#pragma once
#include <iostream>
#include <vector>
#include "itemBase.h"
#include "../data.h"
#include "../player/playerManager.h"
#include "coin/coin.h"
#include "itemObject/box/box.h"

using namespace std;

//アイテムの名前
enum tagItemName
{
	ITEM_NONE = -1,			//何もない	
	ITEM_COIN_RED,			//赤コイン
	ITEM_COIN_GREEN,		//緑コイン
	ITEM_COIN_BLUE,			//青コイン
	ITEM_BOMB,				//爆弾

	ITEM_NUM,				//アイテムの数
};

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

static const int COIN_MAX_NUM = 3;		//コインの最大数

//アイテムマネージャークラス
class CSpawnItemManager
{
private:
	vector<CItemBase*> m_item;							//アイテムのクラス
	int m_hndl[ITEM_NUM];								//アイテムのモデルハンドル
	int m_spawnTime;									//時間カウント
	bool m_isSpawnPos[ITEM_SPAWN_POS_NUM];				//その座標でアイテムが出現したかどうか
	VECTOR m_spawnPos[ITEM_SPAWN_POS_NUM];				//アイテムの出現座標
	CPlayerManager* m_playerManager;					//プレイヤーのマネージャークラス

public:
	//コンストラクタ・デストラクタ
	CSpawnItemManager();
	~CSpawnItemManager();

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

	//コインのアドレスを取得
	CPowerCoin* GetCoin(int _num);

	//アイテムを出現させる
	void SpawnItem();
};

