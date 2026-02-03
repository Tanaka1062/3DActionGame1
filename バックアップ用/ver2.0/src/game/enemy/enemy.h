#pragma once
#include "../enemy/enemyBase.h"
#include "../FOV/FOV.h"
#include <iostream>
#include <vector>

using namespace std;


//敵のクラス
class CEnemy:public CEnemyBase
{
protected:

public:
	//コンストラクタ・デストラクタ
	CEnemy();
	~CEnemy();

	//初期化
	virtual void Init(CAttackManager* _attackManager = nullptr);

protected:
	//待機状態処理
	void Wait();

	//歩く状態処理
	void Walk();

	//ジャンプ状態処理
	void Jump();

	//攻撃前処理
	void AttackIn();

	//攻撃状態処理
	virtual void Attack();

	//攻撃後処理
	void AttackOut();

	//怯み状態処理
	void Stagger();

	//死亡
	void Die();

	//追いかける移動処理
	void MoveChase(VECTOR _pos);

	//ルートを移動処理
	void MoveRoot();
};

