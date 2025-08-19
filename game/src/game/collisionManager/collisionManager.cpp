#include "collisionManager.h"
#include "../../lib/collision/collision.h"

//----------------------------------------------
//		敵の視界とプレイヤーの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitEnemyFOVToPlayer(CEnemyManager& _enemyManager,
	CPlayer& _player)
{
	//プレイヤーが死んでいたら処理をしない
	if (_player.GetActive() == false)return;

	for (int i = 0; i < _enemyManager.GetEnemyNum(); i++)
	{
		CEnemy* enemy = _enemyManager.GetEnemy(i);
		
	}
}
