#pragma once
#include "../../lib/model/actor.h"
#include "../attack/attackManager.h"
#include "../shot/shotManager.h"
#include "../shadow/shadow.h"

enum tagCharacterType	//キャラクターの種類
{
	TYPE_PLAYER,				//プレイヤー
	TYPE_ENEMY,					//敵

};

enum tagState						//キャラクターの状態
{
	WAIT,							//待機
	WALK,							//歩く
	JUMP,							//ジャンプ
	AIR,							//空中
	LANDING,						//着地
	DODGEROLL,						//回避
	ATTACK_IN,						//攻撃前
	ATTACK,							//攻撃中
	ATTACK_OUT,						//攻撃後
	ITEM_USE_IN,					//アイテム使用前
	ITEM_USE,						//アイテム使用中
	ITEM_USE_OUT,					//アイテム使用後
	ITEM_LIFT_UP,					//アイテムを持ち上げる
	ITEM_PUT_DOWN,					//アイテムを下ろす
	ITEM_THROW_IN,					//アイテムを投げる前
	ITEM_THROW,						//アイテムを投げる
	ITEM_THROW_OUT,					//アイテムを投げた後
	STAGGER,						//怯み
	BLOW_AWAY,						//吹き飛んだ状態
	DOWN,							//ダウン状態
	DOWN_IN,						//ダウン前
	GET_UP,							//起き上がり状態
	DIE,							//死亡
	READY,							//準備完了
	READY_OUT,						//準備完了を解除
};

class CCharacterBase:public CActor
{
protected:
	int m_maxHp;						//体力の最大値
	int m_hp;							//体力
	int m_blown;						//吹っ飛び蓄積量
	int m_atk;							//攻撃力
	tagState m_state;					//状態
	tagCharacterType m_type;			//種類
	CShadow m_shadow;					//丸影のクラス

public:
	//コンストラクタ
	CCharacterBase();

	//初期化
	virtual void Init();

	//モデルのロード
	virtual void Load();

	//毎フレームする処理
	virtual void Step(CAttackManager* _attackManager, CShotManager* _shotManager);

	//毎フレームする処理(座標取得用)
	virtual void Step(VECTOR _pos);
	
	//数値の更新
	void Update();

	//モデルの描写
	virtual void Draw();

	//終了処理
	virtual void Exit();

	//攻撃を食らった時にする処理
	virtual void HitAttack(int _atk,int _blown,float _rotY = 0.0f);

	//体力を取得
	int GetHp() { return m_hp; }

	//攻撃力を取得
	int GetAtk() { return m_atk; }

	//状態を取得
	tagState GetState() { return m_state; }

	//種類を取得
	tagCharacterType GetType() { return m_type; }
	
	//種類を設定
	void SetType(tagCharacterType _type) { m_type = _type; }

	//丸影を取得
	CShadow* GetShadow() { return &m_shadow; }

protected:

	//待機処理
	virtual void Wait();

	//歩く処理
	virtual void Walk();

	//ジャンプ
	virtual void Jump();

	//空中
	virtual void Air();

	//着地
	virtual void Landing();

	//回避
	virtual void Dodgeroll();

	//攻撃前
	virtual void AttackIn();

	//攻撃中
	virtual void Attack(CAttackManager* _attackManager,CShotManager* _shotManager);

	//攻撃後
	virtual void AttackOut();

	//攻撃チャージ前
	virtual void AttackChargeIn();

	//攻撃チャージ
	virtual void AttackCharge();

	//スキル使用前
	virtual void SkillIn();

	//スキル使用
	virtual void Skill();

	//スキル使用後
	virtual void SkillOut();

	//アイテム使用前
	virtual void ItemUseIn();

	//アイテム使用中
	virtual void ItemUse();

	//アイテム使用後
	virtual void ItemUseOut();

	//アイテムを持ち上げる
	virtual void ItemLiftUp();

	//アイテムを下ろす
	virtual void ItemPutDown();

	//アイテムを投げる前
	virtual void ItemThrowIn();

	//アイテムを投げる
	virtual void ItemThrow();

	//アイテムを投げた後
	virtual void ItemThrowOut();

	//怯み
	virtual void Stagger();

	//吹き飛んだ
	virtual void BlowAway();

	//ダウン前
	virtual void DownIn();

	//ダウン
	virtual void Down();

	//起き上がり
	virtual void GetUp();

	//死亡
	virtual void Die();

	//ノックバック処理
	void KnockBack();

};

