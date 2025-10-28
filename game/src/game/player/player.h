#pragma once
#include "../character/characterBase.h"
#include "../shot/shotManager.h"
#include"../../lib/input/controllerManager.h"

static const int PLAYER_NUM = 1;			//プレイヤーの数
static const int ITEM_INVENTORY_MAX = 1;	//アイテムインベントリの最大数

enum tagAttackId							//攻撃のID
{
	ATTACK_ID_A,							//攻撃A
	ATTACK_ID_B,							//攻撃B

	ATTACK_NUM,								//攻撃の数						
};

enum tagSkillId
{
	SKILL_ID_NONE = -1,						//スキルが無い
	SKILL_ID_A,								//スキルA

	SKILL_NUM,								//スキルの数
};

//プレイヤークラス
class CPlayer:public CCharacterBase
{
private:
	bool m_isPickUpItem;			//アイテムを取ろうとしているかフラグ		
	bool m_isItemUse;				//アイテム使用フラグ
	int m_attackId;					//攻撃のID
	int m_skillId;					//スキルのID
	tagPadName m_padName;			//コントローラーの名前

public:
	//コンストラクタ・デストラクタ
	CPlayer();
	~CPlayer();

	//初期化
	void Init(CAttackManager* _attackManager = nullptr, tagPadName _padName = PAD_NONE);

	//モデルロード
	void Load(int _modelHndl);

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
	
	//攻撃のID設定
	void SetAttackId(tagAttackId _id) { m_attackId = _id; }

	//スキルのID設定
	void SetSkillId(tagSkillId _id) { m_skillId = _id; }

	//コントローラーの名前を取得
	tagPadName GetPadName() { return m_padName; }

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

	//スキル使用前
	void SkillIn();

	//スキル使用
	void Skill();

	//スキル使用後
	void SkillOut();

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

