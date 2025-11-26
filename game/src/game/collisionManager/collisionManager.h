#pragma once
#include "../enemy/enemyManager.h"
#include"../shot/shotManager.h"
#include "../player/playerManager.h"
#include "../goal/goal.h"
#include "../map/map.h"
#include "../item/itemManager.h"
#include "../attack/attackManager.h"
#include "../item/powerCoin/powerCoinManager.h"
#include "../../lib/model/3DObject.h"

class CCollisionManager
{
private:

	//オブジェクト同士の当たり判定
	static void CheckHitObjectToObject(CObject* _objectA,CObject* _objectB);

public:

	//プレイヤーと攻撃判定の当たり判定
	static void CheckHitPlayerToPlayerAttack(CPlayerManager& _playerManager,
		CAttackManager& _attackManager);

	//プレイヤーとプレイヤーの当たり判定
	static void CheckHitPlayerToPlayer(CPlayerManager& _playerManager);

	//プレイヤーとマップの当たり判定
	static void CheckHitPlayerToMap(CPlayerManager& _playerManager,CMap& _map);

	//プレイヤーとパワーコインの当たり判定
	static void CheckHitPlayerToPowerCoin(CPlayerManager& _playerManager,
		CPowerCoinManager& _powerCoinManager);

	//パワーコインとマップの当たり判定
	static void CheckHitPowerCoinToMap(CPowerCoinManager& _powerCoinManager, CMap& _map);

	//アイテムとマップの当たり判定
	static void CheckHitItemToMap(CItemManager& _itemManager,CMap& _map);

	//アイテムとプレイヤーの当たり判定
	static void CheckHitPlayerToItem(CPlayerManager& _playerManager, CItemManager& _itemManager);

};

