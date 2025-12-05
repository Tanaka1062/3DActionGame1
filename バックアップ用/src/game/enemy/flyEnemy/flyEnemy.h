#pragma once
#include "../enemy.h"

class CFlyEnemy : public CEnemy
{
private:
	int m_downTime;			//ダウンする時間
	int m_downTimeCount;	//ダウンする時間のカウント
	bool m_isDown;			//ダウン状態かどうか

public:

	//初期化
	void Init(CAttackManager* _attackManager = nullptr);

	//毎フレームする処理
	//追いかける相手の座標
	void Step(VECTOR _pos);

	//更新処理
	void Update();

	//弾を食らった時にする処理
	void ShotAttack(int _atk, float _rotY = 0.0f);

protected:
	//攻撃状態処理
	void Attack();

};

