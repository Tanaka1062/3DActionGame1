#pragma once
#include "../character/characterBase.h"
#include "../shot/shotManager.h"
#include"../../lib/input/controllerManager.h"
#include "playerData.h"

namespace PlayerData{
	//定義関連---------------------------

//プレイヤー関連--------------------------------
	constexpr char MODEL_PATH[] =
		"data/model/player/playerTransformTest.mv1";			//ロードするファイル名
	constexpr VECTOR INIT_POS = { 0.0f,1.0f,0.0f };				//初期座標
	constexpr float SHADOW_SIZE = 0.5f;							//丸影の大きさ
	constexpr int MAX_HP = 200;									//体力
	constexpr int ATK = 20;										//攻撃力
	constexpr float MOVE_SPEED = 1.2f * 1.5f;					//移動スピード
	constexpr float RADIUS = 10.0f;								//半径
	constexpr float JUMP_SPEED = 3.0f;							//ジャンプスピード
	constexpr int BLOWN_MAX = 100;								//吹き飛び最大値
	constexpr VECTOR KNOCK_BACK_SPEED = { 0.0f,3.0f,-0.8f };	//吹き飛ぶスピード
	constexpr int INIT_MONEY = 0;								//最初の所持金
	constexpr int MONEY_MAX = 50;								//コインを持てる最大の数
	constexpr float MONEY_DROP_RATE = 0.4f;						//落とすお金の割合
	constexpr float MONEY_RESPAWN_RATE = 0.5f;					//復活するときに消費するお金の割合
	constexpr float DIE_POS_Y = -100.0f;						//死ぬ高さ
	constexpr float FALL_OUT_DAMAGER_RATE = 0.3f;				//ステージから落下したときの割合ダメージ
	constexpr int GET_UP_MAX_TIME = 3 * 60;						//起き上がるまでの最大時間
	constexpr float LANDING_ANIM_SPEED = 3.0f;					//着地するまでの速さ
	constexpr float JUMP_ANIM_SPEED = 3.0f;						//ジャンプするまでの速さ
	//----------------------------------------------

	//攻撃関連---------------------------
	constexpr int ATTACKB_ATK = 100;							//攻撃Bの攻撃力
	constexpr float ATTACK_MOVE_SPEED = 0.5f;					//攻撃時に前進する力
	constexpr float FIGHT_LEN = 40.0f;							//戦う距離
	constexpr float SHOT_SIZE = 10.0f;							//弾の大きさ
	constexpr float SHOT_SPEED = 2.5f;							//弾の速度
	constexpr int SHOT_LOST_TIME = 2 * 60;						//弾が消えるまでの時間
	constexpr float HAMMER_ATTACK_AIR_FALL_SPEED = 4.0f;		//ハンマーの空中攻撃の落下スピード
	constexpr float HAMMER_FALL_FRAME = 13.0f;					//ハンマーの落下するまでのフレーム
	constexpr float HAMMER_FALL_MIN_LENGTH = 30.0f;				//ハンマーの落下攻撃ができる最小の高さ
	//-----------------------------------

};

//武器のID
enum tagWeaponId
{
	WEAPON_ID_HAND,		//素手
	WEAPON_ID_HAMMER,	//ハンマー
	WEAPON_ID_AX,		//斧

	WEAPON_ID_NUM,		//武器の種類
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
protected:
	int					m_dropCoin;				//コインを落とす数
	bool				m_isJump;				//ジャンプしているかフラグ
	int					m_attackNum;			//攻撃の番号
	int					m_weaponDurability;		//武器の耐久度
	int					m_money;				//お金
	int					m_attackId;				//攻撃のID
	int					m_effectId;				//エフェクトのID
	tagPadName			m_padName;				//コントローラーの名前
	tagWeaponId			m_weaponId;				//武器のID
	tagPlayerName		m_name;					//プレイヤーの名前
	tagHaveItemState	m_itemState;			//アイテムの状態
	VECTOR*				m_targetPos;			//相手の座標ポインタ
	bool				m_isCpu;				//cpuかどうかフラグ
	int					m_getUpTime;			//起き上がるまでの時間
	//アニメーション一覧---------------------------

	enum tagAnim {
		ANIMID_AIR,						//空中にいるときのアニメーション
		ANIMID_AIR_ATTACK_HAMMER,		//空中でハンマー攻撃中アニメーション
		ANIMID_AIR_ATTACK_HAMMER_IN,	//空中でハンマー攻撃前アニメーション
		ANIMID_AIR_ATTACK_HAMMER_OUT,	//空中でハンマー攻撃後アニメーション
		ANIMID_AIR_ATTACK_HAND,			//空中で素手攻撃中アニメーション
		ANIMID_AIR_ATTACK_HAND_IN,		//空中で素手攻撃前アニメーション
		ANIMID_AIR_ATTACK_HAND_OUT,		//空中で素手攻撃後アニメーション
		ANIMID_ATTACK1_AX,				//斧攻撃1中アニメーション
		ANIMID_ATTACK1_AX_IN,			//斧攻撃1前アニメーション
		ANIMID_ATTACK1_AX_OUT,			//斧攻撃1後アニメーション
		ANIMID_ATTACK1_HAMMER,			//ハンマー攻撃1中アニメーション
		ANIMID_ATTACK1_HAMMER_IN,		//ハンマー攻撃1前アニメーション
		ANIMID_ATTACK1_HAMMER_OUT,		//ハンマー攻撃1後アニメーション
		ANIMID_ATTACK2_HAMMER,			//ハンマー攻撃2中アニメーション
		ANIMID_ATTACK2_HAMMER_IN,		//ハンマー攻撃2前アニメーション
		ANIMID_ATTACK2_HAMMER_OUT,		//ハンマー攻撃2後アニメーション
		ANIMID_ATTACK3_HAMMER,			//ハンマー攻撃3中アニメーション
		ANIMID_ATTACK3_HAMMER_IN,		//ハンマー攻撃3前アニメーション
		ANIMID_ATTACK3_HAMMER_OUT,		//ハンマー攻撃3後アニメーション
		ANIMID_ATTACK1_HAND,			//素手攻撃1中アニメーション
		ANIMID_ATTACK1_HAND_IN,			//素手攻撃1前アニメーション
		ANIMID_ATTACK1_HAND_OUT,		//素手攻撃1後アニメーション
		ANIMID_ATTACK2_HAND,			//素手攻撃2中アニメーション
		ANIMID_ATTACK2_HAND_IN,			//素手攻撃2前アニメーション
		ANIMID_ATTACK2_HAND_OUT,		//素手攻撃2後アニメーション
		ANIMID_ATTACK3_HAND,			//素手攻撃3中アニメーション
		ANIMID_ATTACK3_HAND_IN,			//素手攻撃3前アニメーション
		ANIMID_ATTACK3_HAND_OUT,		//素手攻撃3後アニメーション
		ANIMID_BLOW_AWAY,				//吹き飛んでいるアニメーション
		ANIMID_DEFAULT,					//デフォルトのアニメーション
		ANIMID_DIE,						//死亡時のアニメーション
		ANIMID_DOWN,					//ダウン中のアニメーション
		ANIMID_DOWN_IN,					//ダウン前のアニメーション
		ANIMID_GET_UP,					//起き上がりのアニメーション
		ANIMID_HIT,						//被弾のアニメーション
		ANIMID_JUMP,					//ジャンプするアニメーション
		ANIMID_LANDING,					//着地するアニメーション
		ANIMID_LIFT_UP,					//物を持ち上げるアニメーション
		ANIMID_PUT_DOWN,				//物を下ろすアニメーション
		ANIMID_READY,					//準備完了のアニメーション
		ANIMID_READY_OUT,				//準備完了をやめるアニメーション
		ANIMID_RESULT_POSE1,			//リザルト画面の1位ポーズのアニメーション
		ANIMID_RESULT_POSE1_IN,			//リザルト画面の1位ポーズ前のアニメーション
		ANIMID_RESULT_POSE2,			//リザルト画面の2位ポーズのアニメーション
		ANIMID_RESULT_POSE2_IN,			//リザルト画面の2位ポーズ前のアニメーション
		ANIMID_RESULT_POSE3,			//リザルト画面の3位ポーズのアニメーション
		ANIMID_RESULT_POSE3_IN,			//リザルト画面の3位ポーズ前のアニメーション
		ANIMID_RESULT_POSE4,			//リザルト画面の4位ポーズのアニメーション
		ANIMID_RESULT_POSE4_IN,			//リザルト画面の4位ポーズ前のアニメーション
		ANIMID_THROW,					//物を投げる中のアニメーション
		ANIMID_THROW_IN,				//物を投げる前のアニメーション
		ANIMID_THROW_OUT,				//物を投げる後のアニメーション
		ANIMID_TITLE_POSE1,				//タイトルポーズ1のアニメーション
		ANIMID_TITLE_POSE2,				//タイトルポーズ2のアニメーション
		ANIMID_TITLE_POSE3,				//タイトルポーズ3のアニメーション
		ANIMID_TITLE_POSE4,				//タイトルポーズ4のアニメーション
		ANIMID_WAIT,					//待機状態のアニメーション
		ANIMID_WAIT_LIFTING_UP,			//物を持ち上げている待機状態のアニメーション
		ANIMID_WALK,					//歩きのアニメーション
		ANIMID_WALK_LIFTING_UP,			//物を持ち上げている歩きのアニメーション
		ANIMID_WISH,					//願っているアニメーション
	};

	//---------------------------------------------

public:
	//コンストラクタ・デストラクタ
	CPlayer();
	virtual ~CPlayer();

	//初期化
	virtual void Init(tagPlayerName _name, tagPadName _padName);

	//モデルロード
	virtual void Load(int _modelHndl);

	//毎フレームする処理
	virtual void Step(float _rotY,VECTOR* _targetPos, CAttackManager* _attackManager, CShotManager* _shotManager);

	//描写処理
	virtual void Draw();

	//更新処理
	virtual void Update();

	//終了処理
	virtual void Exit();

	//復活処理
	void Respawn(VECTOR _respawnPos);

	//当たり判定後の処理
	virtual void HitCalc(CObject* _hitObject);

	//攻撃を食らった時にする処理
	void HitAttack(int _atk, int _blown, float _rotY = 0.0f);

	//重力リセット
	void GravityReset();

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

	//お金を設定
	void SetMoney(int _money) { m_money = _money; }

	//お金を増やす
	void AddMoney(int _addMoney) { m_money += _addMoney; }

	//お金を減らす
	bool SubMoney(int _subMoney);

	//持っているアイテムの座標を取得
	VECTOR GetItemHavePos();

	//座標をアドレスを取得
	VECTOR* GetPosPoint() { return &m_pos; }

	//cpuかどうかを取得
	bool GetIsCpu() { return m_isCpu; }

	//状態を設定
	void SetState(tagState _state) { m_state = _state; }

protected:

	//入力処理
	virtual void InputStep();

	//待機状態処理
	void Wait();

	//歩く状態処理
	void Walk();

	//ジャンプ状態処理
	void Jump();

	//空中状態処理
	void Air();

	//着地状態処理
	void Landing();

	//攻撃前処理
	void AttackIn();

	//攻撃状態処理
	void Attack(CAttackManager* _attackManager, CShotManager* _shotManager);

	//攻撃後処理
	void AttackOut();

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

	//吹き飛んだ
	void BlowAway();

	//ダウン前
	void DownIn();

	//ダウン
	void Down();

	//起き上がり
	void GetUp();

	//死亡
	void Die();

	//準備完了
	void Ready();

	//準備完了を解除
	void ReadyOut();

	//移動処理
	virtual void Move(float _rotY);

	//攻撃を呼び出す処理
	virtual void RequestAttack();

	//ジャンプの呼び出し処理
	virtual void RequestJump();

	//アイテムを拾う
	void PickUpItem();

};

