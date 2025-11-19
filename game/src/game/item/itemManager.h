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
	ITEM_FIRE_RING,			//ファイアリング
	ITEM_HARB_AMULENT,		//薬草のお守り

	ITEM_NUM,				//アイテムの種類
};
//アイテムのタイプ
enum tagItemType
{
	ITEM_TYPE_NONE = -1,	//何もないタイプ
	ITEM_TYPE_SHOT,			//弾発射タイプ
	ITEM_TYPE_USE,			//使用タイプ
	ITEM_TYPE_SKILL,		//スキルタイプ
};


//アイテムマネージャークラス
class CItemManager
{
private:
	list<CItemBase*> m_item;				//アイテムのクラス
	int m_hndl[ITEM_NUM];
	CShotManager* m_shot;					//弾のマネージャーのアドレス保存用
public:
	//コンストラクタ・デストラクタ
	CItemManager();
	~CItemManager();

	//初期化
	void Init(CShotManager* _shot);
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
	// _pos		:出現させるアイテムの位置
	// _name	:出現させるアイテムの名前
	//			:名前を入力しない場合ランダムなアイテムが出現する
	void SpawnItem(VECTOR _pos);
};

