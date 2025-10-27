#pragma once
#include "../enemy/enemyManager.h"
#include"../shot/shotManager.h"
#include "../player/playerManager.h"
#include "../goal/goal.h"
#include "../map/map.h"
#include "../item/itemManager.h"
#include "../item/itemInventory/itemInventory.h"
#include "../attack/attackManager.h"
#include "../box/boxManager.h"

class CCollisionManager
{
public:

	//敵の視界とプレイヤーの当たり判定
	static void CheckHitEnemyFOVToPlayer(CEnemyManager& _enemyManager,
		CPlayerManager& _player);

	//敵の攻撃範囲とプレイヤーの当たり判定
	static void CheckHitEnemyAttackToPlayer(CEnemyManager& _enemyManager,
		CPlayerManager& _player);

	//プレイヤーの攻撃と敵の当たり判定
	static void CheckHitPlayerAttackToEnemy(CAttackManager& _attackManager,
		CEnemyManager& _enemyManager);

	//敵とプレイヤーの当たり判定
	static void CheckHitEnemyToPlayer(CEnemyManager& _enemyManager,
		CPlayerManager& _player);

	//敵と敵の当たり判定
	static void CheckHitEnemyToEnemy(CEnemyManager& _enemyManager);

	//弾と敵の当たり判定
	static void CheckHitShotToEnemy(CShotManager& _shotManager,
		CEnemyManager& _enemyManager);

	//プレイヤーとマップの当たり判定
	static void CheckHitPlayerToMap(CPlayerManager& _player,CMap& _map);

	//敵とマップの当たり判定
	static void CheckHitEnemyToMap(CEnemyManager& _enemy, CMap& _map);

	//アイテムとプレイヤーの当たり判定
	static void CheckHitItemToPlayer(CItemManager& _item,
		CItemInventory& _itemInventory, CPlayerManager& _player);

	//攻撃と箱の当たり判定
	static void CheckHitAttackToBox(CAttackManager& _attack, CBoxManager& _box);

	//プレイヤーと箱の当たり判定
	static void CheckHitPlayerToBox(CPlayerManager& _player, CBoxManager& _box);

	//箱とマップの当たり判定
	static void CheckHitBoxToMap(CBoxManager& _box, CMap& _map);
};

