#pragma once
#include "../character/characterBase.h"
#include "../shot/shotManager.h"


static const int PLAYER_NUM = 1;			//プレイヤーの数
static const int ITEM_INVENTORY_MAX = 1;	//アイテムインベントリの最大数

//プレイヤークラス
class CPlayer:public CCharacterBase
{
private:
	bool m_isPickUpItem;		//アイテムを取ろうとしているかフラグ		
	bool m_isItemUse;			//アイテム使用フラグ
	int m_itemSelectNum;		//現在選択しているアイテムの番号	
	int m_attackId;				//攻撃のID

public:
	//コンストラクタ・デストラクタ
	CPlayer();
	~CPlayer();

	//初期化
	void Init(CAttackManager* _attackManager = nullptr);

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step(float _rotY);

	//描写処理
	void Draw();

	//更新処理
	void Update();

	//アイテムを取るかを取得
	bool GetIsPickUp() { return m_isPickUpItem; }

	//アイテム使用しているかを取得
	bool GetIsItemUse() { return m_isItemUse; }
	
	//現在選択しているアイテムの番号を取得
	int GetItemSelectNum() { return m_itemSelectNum; }

	//体力を増やす
	void AddHp(int _addNum) { m_hp += _addNum; }

private:
	//待機状態処理
	void Wait();

	//歩く状態処理
	void Walk();

	//ジャンプ状態処理
	void Jump();

	//攻撃前処理
	void AttackIn();

	//攻撃状態処理
	void Attack();

	//攻撃後処理
	void AttackOut();

	//攻撃チャージ前
	void AttackChargeIn();

	//攻撃チャージ
	void AttackCharge();

	//アイテム使用前
	void ItemUseIn();

	//アイテム使用中
	void ItemUse();

	//アイテム使用後
	void ItemUseOut();

	//怯み状態処理
	void Stagger();

	//死亡
	void Die();

	//移動処理
	void Move(float _rotY);

	//攻撃を呼び出す処理
	void RequestAttack();

	//アイテム処理
	void Item();

	//アイテムを拾う
	void PickUpItem();

};

