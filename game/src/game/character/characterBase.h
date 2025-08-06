#pragma once
#include "../../lib/model/actor.h"

enum tagCharacterType	//キャラクターの種類
{
	TYPE_PLAYER,				//プレイヤー
	TYPE_ENEMY,					//敵

};

class CCharacterBase:public CActor
{
protected:
	int m_hp;					//体力
	int m_attack;				//攻撃力
	enum tagState				//キャラクターの状態
	{
		WAIT,					//待機
		WALK,					//歩く
		JUMP,					//ジャンプ
		ATTACK,					//攻撃
		STAGGER,				//怯み

	};
	tagState m_state;			//状態
	tagCharacterType m_type;	//種類

public:
	//コンストラクタ
	CCharacterBase();

	//初期化
	virtual void Init();

	//毎フレームする処理
	virtual void Step();

	//データを取得・設定---------------
	//体力を取得
	int GetHp() { return m_hp; }

	//攻撃力を取得
	int GetAttack() { return m_attack; }

	//種類を取得
	tagCharacterType GetType() { return m_type; }
	
	//種類を設定
	void SetType(tagCharacterType _type) { m_type = _type; }
	//---------------------------------


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

