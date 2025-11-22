#pragma once
#include "../character/characterBase.h"
#include "../shot/shotManager.h"
#include"../../lib/input/controllerManager.h"
#include "playerData.h"

enum tagWeaponId
{
	WEAPON_ID_HAND,
	WEAPON_ID_SWORD,

	WEAPON_ID_NUM,
};

enum tagHndlName
{
	NORMAL_HNDL,		//ノーマルハンドル
	TRANSFORM_HNDL,		//変身後のハンドル

	HNDL_NUM,			//ハンドルの数
};

//プレイヤークラス
class CPlayer:public CCharacterBase
{
private:
	int m_transformTimeCount;		//変身時間カウント
	int m_keepHndl[HNDL_NUM];		//モデルハンドル保存用
	int m_dropCoin;					//コインを落とす数
	bool m_isPickUpItem;			//アイテムを取ろうとしているかフラグ		
	bool m_isItemUse;				//アイテム使用フラグ
	bool m_isItem;					//アイテムを持っているフラグ
	bool m_isDodgeroll;				//回避しているかフラグ
	bool m_isTransform;				//変身しているかフラグ
	int m_attackNum;				//攻撃の番号
	int m_powerUp;					//パワーアップ
	float m_dodgerollRotY;			//回避時の角度
	tagPadName m_padName;			//コントローラーの名前
	tagWeaponId m_weaponId;			//武器のID
	tagPlayerName m_name;			//プレイヤーの名前

public:
	//コンストラクタ・デストラクタ
	CPlayer();
	~CPlayer();

	//初期化
	void Init(CAttackManager* _attackManager,tagPlayerName _name, tagPadName _padName);

	//モデルロード
	void Load(int _modelHndl);

	//毎フレームする処理
	void Step(float _rotY);

	//描写処理
	void Draw();

	//更新処理
	void Update();

	//終了処理
	void Exit();

	//当たり判定後の処理
	void HitCalc(CObject* _hitObject);

	//アイテムを取るかを取得
	bool GetIsPickUp() { return m_isPickUpItem; }

	//アイテム使用しているかを取得
	bool GetIsItemUse() { return m_isItemUse; }
	
	//アイテムを持っているかを設定
	void SetIsItem(bool _isItem) { m_isItem = _isItem; }

	//回避しているかを取得
	bool GetIsDodgeroll() { return m_isDodgeroll; }

	//コインを落としているかを取得
	int GetDropCoin() { return m_dropCoin; }
	//コインを落としているかを設定
	void SetDropCoin(int _dropCoin) { m_dropCoin = _dropCoin; }

	//コントローラーの名前を取得
	tagPadName GetPadName() { return m_padName; }

	//武器のIDを取得
	tagWeaponId GetWeaponId() { return m_weaponId; }
	//武器のIDを設定
	void SetWeaponId(tagWeaponId _weaponId) { m_weaponId = _weaponId; }

	//名前を取得
	tagPlayerName GetPlayerName() { return m_name; }

	//体力を増やす
	void AddHp(int _addNum) { m_hp += _addNum; }

	//体力の最大値を取得
	int GetHpMax() { return m_maxHp; }

	//パワーアップを増やす
	void AddPowerUp() { m_powerUp++; }
	//パワーアップを減らす
	void SubPowerUp() { m_powerUp--; }


private:
	//待機状態処理
	void Wait();

	//歩く状態処理
	void Walk();

	//ジャンプ状態処理
	void Jump();

	//回避
	void Dodgeroll();

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

	//ジャンプの呼び出し処理
	void RequestJump();

	//回避に移行する処理
	void RequestDodgeroll(float _rotY);

	//アイテム処理
	void Item();

	//アイテムを拾う
	void PickUpItem();

};

