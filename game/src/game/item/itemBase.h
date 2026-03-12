#pragma once

#include "../../lib/model/actor.h"
#include "../player/player.h"
#include "../shadow/shadow.h"

//アイテムのタイプ
enum tagItemType
{
	ITEM_TYPE_COIN,			//コインタイプ
	ITEM_TYPE_OBJECT,		//オブジェクトタイプ
	ITEM_TYPE_WEAPON,		//武器タイプ

	ITEM_TYPE_NUM,			//アイテムのタイプの数
};

//アイテムの名前
enum tagItemName
{
	ITEM_NONE = -1,			//何もない	
	ITEM_BOMB,				//爆弾
	ITEM_SWORD,				//剣
	ITEM_GUN,				//銃
	ITEM_AX,				//斧

	ITEM_NUM,				//アイテムの数
};

enum tagItemState
{
	ITEM_FLYING,	//飛んでいる状態
	ITEM_WAIT,		//待機状態

};

//アイテムのベースクラス
class CItemBase :public CActor
{
protected:
	bool m_isSpawn;			//スポーンするかフラグ
	bool m_isBuy;			//購入されているか
	int m_cost;				//価格
	CShadow m_shadow;		//丸影のクラス
	tagItemType m_itemType;	//アイテムのタイプ
	tagItemState m_state;	//状態
	tagItemName m_itemName;	//アイテムの名前

public:
	//コンストラクタ
	CItemBase();

	//初期化
	virtual void Init();

	//モデルのロード(一つのモデルしか使わない)
	virtual void Load(const char* _modelPath);

	//モデルのロード(同じモデルを複数使う場合)
	virtual void Load(int _hndl);

	//毎フレームする処理
	virtual void Step();

	//数値の更新
	virtual void Update();

	//モデルの描写
	virtual void Draw();

	//終了処理
	virtual void Exit();

	//使用した時の処理
	virtual void Use();

	//アイテムのドロップ
	virtual void Drop(VECTOR _pos, float _rotY);

	//丸影を取得
	CShadow* GetShadow() { return &m_shadow; }

	//スポーン可能かを取得
	bool GetIsSpawn() { return m_isSpawn; }

	//スポーン可能かを設定
	void SetIsSpawn(bool _isSpawn) { m_isSpawn = _isSpawn; }

	//アイテムのタイプを取得
	tagItemType GetItemType() { return m_itemType; }

	//状態を取得
	tagItemState GetState() { return m_state; }

	//アイテムの名前を取得
	tagItemName GetItemName() { return m_itemName; }

	//購入されているかどうかを設定
	void SetIsBuy(bool _isBuy) { m_isBuy = _isBuy; }

	//出現座標をセット
	virtual void SetSpawnPos(VECTOR _pos) {}

	//価格を取得
	int GetCost() { return m_cost; }

};


