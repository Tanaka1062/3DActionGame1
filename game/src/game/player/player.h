#pragma once
#include "../character/characterBase.h"
#include "../shot/shotManager.h"
#include"../../lib/input/controllerManager.h"
#include "playerData.h"

static const int TRANSFORM_TIME = 10 * 60;					//変身している時間

//武器のID
enum tagWeaponId
{
	WEAPON_ID_HAND,		//素手
	WEAPON_ID_SWORD,	//剣
	WEAPON_ID_AX,		//斧
	WEAPON_ID_GUN,		//銃

	WEAPON_ID_NUM,		//武器の種類
};

//モデルハンドル名
enum tagHndlName
{
	NORMAL_HNDL,		//ノーマルハンドル
	TRANSFORM_HNDL,		//変身後のハンドル

	HNDL_NUM,			//ハンドルの数
};

//アイテムの状態
enum tagHaveItemState
{
	ITEM_STATE_NONE = -1,		//アイテムを持っていない
	ITEM_STATE_PICK_UP,			//アイテムを取ろうとしている
	ITEM_STATE_PUT_DOWN,		//アイテムを下ろす
	ITEM_STATE_GET,				//アイテムを手に入れる
	ITEM_STATE_HAVE,			//アイテムを持っている
	ITEM_STATE_THROW,			//アイテムを投げる
	ITEM_STATE_DROP,			//アイテムを落とした
};

//プレイヤークラス
class CPlayer:public CCharacterBase
{
private:
	int m_transformTimeCount;		//変身時間カウント
	int m_keepHndl[HNDL_NUM];		//モデルハンドル保存用
	int m_dropCoin;					//コインを落とす数
	bool m_isDodgeroll;				//回避しているかフラグ
	bool m_isTransform;				//変身しているかフラグ
	int m_attackNum;				//攻撃の番号
	int m_weaponDurability;			//武器の耐久度
	float m_dodgerollRotY;			//回避時の角度
	int m_money;					//お金
	tagPadName m_padName;			//コントローラーの名前
	tagWeaponId m_weaponId;			//武器のID
	tagPlayerName m_name;			//プレイヤーの名前
	tagHaveItemState m_itemState;	//アイテムの状態
	VECTOR* m_targetPos;			//相手の座標ポインタ

public:
	//コンストラクタ・デストラクタ
	CPlayer();
	~CPlayer();

	//初期化
	void Init(tagPlayerName _name, tagPadName _padName);

	//モデルロード
	void Load(int _modelHndl);

	//毎フレームする処理
	void Step(float _rotY,VECTOR* _targetPos, CAttackManager* _attackManager, CShotManager* _shotManager);

	//描写処理
	void Draw();

	//更新処理
	void Update();

	//終了処理
	void Exit();

	//復活処理
	void Respawn(VECTOR _respawnPos);

	//当たり判定後の処理
	void HitCalc(CObject* _hitObject);

	//攻撃を食らった時にする処理
	void HitAttack(int _atk, int _blown, float _rotY = 0.0f);

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

	//武器の耐久度をセットする
	void SetWeaponDurability(int _durability) { m_weaponDurability = _durability; }

	//名前を取得
	tagPlayerName GetPlayerName() { return m_name; }

	//アイテムの状態を取得
	tagHaveItemState GetItemState() { return m_itemState; }

	//アイテムの状態を設定
	void SetItemState(tagHaveItemState _itemState) { m_itemState = _itemState; }

	//体力を増やす
	void AddHp(int _addNum) { m_hp += _addNum; }

	//体力の最大値を取得
	int GetHpMax() { return m_maxHp; }

	//お金を取得
	int GetMoney() { return m_money; }

	//お金を増やす
	void AddMoney(int _addMoney) { m_money += _addMoney; }

	//お金を減らす
	bool SubMoney(int _subMoney);

	//持っているアイテムの座標を取得
	VECTOR GetItemHavePos();

	//武器の座標を取得
	VECTOR GetWeaponPos();

	//座標をアドレスを取得
	VECTOR* GetPosPoint() { return &m_pos; }

	//変身時間を取得する
	int GetTransformTimeCount() { return m_transformTimeCount; }

	//変身しているかを取得する
	bool GetIsTransform() { return m_isTransform; }

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
	void Attack(CAttackManager* _attackManager, CShotManager* _shotManager);

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

	//アイテムを持ち上げる
	void ItemLiftUp();

	//アイテムを下ろす
	void ItemPutDown();

	//アイテムを投げる前
	void ItemThrowIn();

	//アイテムを投げる
	void ItemThrow();

	//アイテムを投げた後
	void ItemThrowOut();

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

