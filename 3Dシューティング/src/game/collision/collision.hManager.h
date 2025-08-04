#pragma once
#include "../enemy/enemyManager.h"
#include "../shot/shotManager.h"
#include "../player/player.h"

//各種の当たり判定クラス
class CCollisionManger
{
public:
	//プレイヤーの弾と敵の当たり判定
	static void CheckHitShotToEnemy(CShotManager& _shotManager,
		CEnemyManager& _enemyManager);

	//プレイヤーと敵の当たり判定
	static void CheckHitPlayerToEnemy(CPlayer& _player,
		CEnemyManager& _enemyManager);

};

