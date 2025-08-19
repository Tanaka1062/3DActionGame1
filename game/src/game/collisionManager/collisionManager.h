#pragma once
#include "../enemy/enemyManager.h"
#include "../player/player.h"

class CCollisionManager
{
public:

	//“G‚Ì‹ŠE‚ÆƒvƒŒƒCƒ„[‚Ì“–‚½‚è”»’è
	static void CheckHitEnemyFOVToPlayer(CEnemyManager& _enemyManager,
		CPlayer& _player);


};

