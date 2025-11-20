#pragma once
#include <iostream>
#include <list>
#include "itemBase.h"
#include "../data.h"
#include "../player/playerManager.h"
#include "../shot/shotManager.h"
#include "itemShotBase.h"

using namespace std;

//アイテムの名前
enum tagItemName
{
	ITEM_NONE = -1,			//何もない	
	ITEM_BOMB,				//アイテム爆弾

	ITEM_NUM,				//アイテムの数
};

//アイテムのタイプ
enum tagItemType
{
	ITEM_TYPE_NONE = -1,	//何もないタイプ
	ITEM_OBJECT_TYPE,		//オブジェクトタイプ

	ITEM_TYPE_NUM,			//アイテムのタイプの数
};


//アイテムマネージャークラス
class CItemManager
{
private:
	list<CItemBase*> m_item;				//アイテムのクラス
	int m_hndl[ITEM_NUM];					//アイテムのモデルハンドル
	int m_spawnTime;						//時間カウント

public:
	//コンストラクタ・デストラクタ
	CItemManager();
	~CItemManager();

	//初期化
	void Init();
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
	void SpawnItem();
};

