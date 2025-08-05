#pragma once
#include "../../lib/model/actor.h"

class CCharacterBase:public CActor
{
protected:
	int m_hp;			//体力
	int m_attack;		//攻撃力
	enum tagState		//キャラクターの状態
	{
		WAIT,			//待機
		WALK,			//歩く
		JUMP,			//ジャンプ
		ATTACK,			//攻撃
		STAGGER,		//怯み

	};
	tagState m_state;	//状態

public:
	//コンストラクタ
	CCharacterBase();

	//初期化
	virtual void Init();

	//毎フレームする処理
	virtual void Step();

	//データを取得---------------
	//体力を取得
	int GetHp() { return m_hp; }

	//攻撃力を取得
	int GetAttack() { return m_attack; }

	//---------------------------


protected:

	//待機処理
	virtual void Wait();

	//歩く処理
	virtual void Walk();

	//ジャンプ
	virtual void Jump();

	//攻撃
	virtual void Attack();

	//怯み
	virtual void Stagger();

};

