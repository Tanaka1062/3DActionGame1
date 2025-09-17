#pragma once
#include "../../lib/model/actor.h"
#include "../attack/attack.h"
#include "../shot/shotManager.h"

enum tagCharacterType	//キャラクターの種類
{
	TYPE_PLAYER,				//プレイヤー
	TYPE_ENEMY,					//敵

};

class CCharacterBase:public CActor
{
protected:
	float m_gravity;			//重力
	int m_hp;					//体力
	int m_atk;					//攻撃力
	enum tagState				//キャラクターの状態
	{
		WAIT,					//待機
		WALK,					//歩く
		JUMP,					//ジャンプ
		ATTACK_IN,				//攻撃前
		ATTACK,					//攻撃中
		ATTACK_OUT,				//攻撃後
		ITEM_USE_IN,			//アイテム使用前
		ITEM_USE,				//アイテム使用中
		ITEM_USE_OUT,			//アイテム使用後
		STAGGER,				//怯み
		DIE,					//死亡
	};
	tagState m_state;			//状態
	tagCharacterType m_type;	//種類
	CAttack m_attack;			//攻撃クラス
	CShotManager* m_shot;		//弾のアドレス

public:
	//コンストラクタ
	CCharacterBase();

	//初期化
	virtual void Init();

	//初期化(弾を出すキャラ用)
	virtual void Init(CShotManager* _shot);

	//毎フレームする処理
	virtual void Step();

	//毎フレームする処理(座標取得用)
	virtual void Step(VECTOR _pos);

	//攻撃を食らった時にする処理
	virtual void HitAttack(int _atk);

	//数値の更新
	void Update();

	//体力を取得
	int GetHp() { return m_hp; }

	//攻撃力を取得
	int GetAtk() { return m_atk; }

	//種類を取得
	tagCharacterType GetType() { return m_type; }
	
	//種類を設定
	void SetType(tagCharacterType _type) { m_type = _type; }

	//攻撃を取得
	CAttack* GetAttack() { return &m_attack; }

	//重力リセット
	void GravityReset();

protected:

	//待機処理
	virtual void Wait();

	//歩く処理
	virtual void Walk();

	//ジャンプ
	virtual void Jump();

	//攻撃前
	virtual void AttackIn();

	//攻撃中
	virtual void Attack();

	//攻撃後
	virtual void AttackOut();

	//アイテム使用前
	virtual void ItemUseIn();

	//アイテム使用中
	virtual void ItemUse();

	//アイテム使用後
	virtual void ItemUseOut();

	//怯み
	virtual void Stagger();

	//死亡
	virtual void Die();

	//重力処理
	void Gravity();

};

