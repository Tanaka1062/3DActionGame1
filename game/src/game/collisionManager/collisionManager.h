#pragma once
#include "../enemy/enemyManager.h"
#include "../player/player.h"

class CCollisionManager
{
public:

	//敵の視界とプレイヤーの当たり判定
	static void CheckHitEnemyFOVToPlayer(CEnemyManager& _enemyManager,
		CPlayer& _player);

	//敵とプレイヤーの当たり判定
	static void CheckHitEnemyToPlayer(CEnemyManager& _enemyManager,
		CPlayer& _player);

};

