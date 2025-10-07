#pragma once
#include "../enemy.h"

class CFlyEnemy : public CEnemy
{
private:

public:

	//初期化
	void Init();

	//毎フレームする処理
	//追いかける相手の座標
	void Step(VECTOR _pos);

	//更新処理
	void Update();

};

