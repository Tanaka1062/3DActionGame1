#pragma once
#include "../enemy/enemyManager.h"
#include"../shot/shotManager.h"
#include "../player/player.h"
#include "../goal/goal.h"
#include "../map/map.h"
#include "../item/itemManager.h"
#include "../item/itemInventory/itemInventory.h"

class CCollisionManager
{
public:

	//敵の視界とプレイヤーの当たり判定
	static void CheckHitEnemyFOVToPlayer(CEnemyManager& _enemyManager,
		CPlayer& _player);

	//敵の攻撃範囲とプレイヤーの当たり判定
	static void CheckHitEnemyAttackToPlayer(CEnemyManager& _enemyManager,
		CPlayer& _player);

	//敵とプレイヤーの当たり判定
	static void CheckHitEnemyToPlayer(CEnemyManager& _enemyManager,
		CPlayer& _player);

	//敵と敵の当たり判定
	static void CheckHitEnemyToEnemy(CEnemyManager& _enemyManager);

	//弾と敵の当たり判定
	static void CheckHitShotToEnemy(CShotManager& _shotManager,
		CEnemyManager& _enemyManager);

	//プレイヤーとゴールの当たり判定
	static void CheckHitPlayerToGoal(CPlayer& _player, CGoal& _goal);

	//プレイヤーとマップの当たり判定
	static void CheckHitPlayerToMap(CPlayer& _player,CMap& _map);

	//敵とマップの当たり判定
	static void CheckHitEnemyToMap(CEnemyManager& _enemy, CMap& _map);

	//アイテムとプレイヤーの当たり判定
	static void CheckHitItemToPlayer(CItemManager& _item,
		CItemInventory& _itemInventory, CPlayer& _player);

};

