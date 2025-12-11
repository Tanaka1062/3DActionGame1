#pragma once
#include <iostream>
#include <vector>
#include "itemBase.h"
#include "../data.h"
#include "itemObject/box/box.h"

using namespace std;

//アイテムの名前
enum tagMapItemSpawnPos
{
	MAP_ITEM_SPAWN_POS_1,	//マップに置かれているアイテムの出現座標1
	MAP_ITEM_SPAWN_POS_2,	//マップに置かれているアイテムの出現座標2
	MAP_ITEM_SPAWN_POS_3,	//マップに置かれているアイテムの出現座標3
	MAP_ITEM_SPAWN_POS_4,	//マップに置かれているアイテムの出現座標4

	MAP_ITEM_SPAWN_POS_NUM,	//マップに置かれているアイテムの出現座標の数
};

//アイテムマネージャークラス
class CMapItemManager
{
private:
	vector<unique_ptr<CItemBase>> m_item;
	int m_hndl;											//アイテムのモデルハンドル

public:
	//コンストラクタ・デストラクタ
	CMapItemManager();
	~CMapItemManager();

	//初期化
	void Init();
	//モデルロード
	void Load();
	//毎フレームする処理
	void Step();
	//終了処理
	void Exit();

	//アイテムの数を取得
	int GetItemNum() { return MAP_ITEM_SPAWN_POS_NUM; }

	//アイテムのアドレスを取得
	unique_ptr<CItemBase> GetItem(int _num);

};

