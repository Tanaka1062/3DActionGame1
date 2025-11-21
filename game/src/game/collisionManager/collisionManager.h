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
#include "../item/powerCoin/powerCoinManager.h"

class CCollisionManager
{
public:

	//プレイヤーと攻撃判定の当たり判定
	static void CheckHitPlayerToPlayerAttack(CPlayerManager& _playerManager,
		CAttackManager& _attackManager);

	//プレイヤーとプレイヤーの当たり判定
	static void CheckHitPlayerToPlayer(CPlayerManager& _playerManager);

	//プレイヤーとマップの当たり判定
	static void CheckHitPlayerToMap(CPlayerManager& _playerManager,CMap& _map);

	//攻撃と箱の当たり判定
	static void CheckHitAttackToBox(CAttackManager& _attack, CBoxManager& _box);

	//プレイヤーと箱の当たり判定
	static void CheckHitPlayerToBox(CPlayerManager& _playerManager, CBoxManager& _box);

	//箱とマップの当たり判定
	static void CheckHitBoxToMap(CBoxManager& _box, CMap& _map);

	//プレイヤーとパワーコインの当たり判定
	static void CheckHitPlayerToPowerCoin(CPlayerManager& _playerManager,
		CPowerCoinManager& _powerCoinManager);

	//パワーコインとマップの当たり判定
	static void CheckHitPowerCoinToMap(CPowerCoinManager& _powerCoinManager, CMap& _map);

	//アイテムとマップの当たり判定
	static void CheckHitItemToMap(CItemManager& _itemManager,CMap& _map);

};

