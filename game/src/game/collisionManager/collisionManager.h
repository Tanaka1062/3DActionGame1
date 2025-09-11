#pragma once
#include "../enemy/enemyManager.h"
#include"../shot/shotManager.h"
#include "../player/player.h"

class CCollisionManager
{
public:

	//“G‚Ì‹ŠE‚ÆƒvƒŒƒCƒ„[‚Ì“–‚½‚è”»’è
	static void CheckHitEnemyFOVToPlayer(CEnemyManager& _enemyManager,
		CPlayer& _player);

	//“G‚ÌUŒ‚”ÍˆÍ‚ÆƒvƒŒƒCƒ„[‚Ì“–‚½‚è”»’è
	static void CheckHitEnemyAttackToPlayer(CEnemyManager& _enemyManager,
		CPlayer& _player);

	//“G‚ÆƒvƒŒƒCƒ„[‚Ì“–‚½‚è”»’è
	static void CheckHitEnemyToPlayer(CEnemyManager& _enemyManager,
		CPlayer& _player);

	//“G‚Æ“G‚Ì“–‚½‚è”»’è
	static void CheckHitEnemyToEnemy(CEnemyManager& _enemyManager);

	//’e‚Æ“G‚Ì“–‚½‚è”»’è
	static void CheckHitShotToEnemy(CShotManager& _shotManager,
		CEnemyManager& _enemyManager);
};

