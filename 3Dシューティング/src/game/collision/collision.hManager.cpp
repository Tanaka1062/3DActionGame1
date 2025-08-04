#include "collision.hManager.h"
#include "../../lib/collision.h"

//プレイヤーの弾と敵の当たり判定
void CCollisionManger::CheckHitShotToEnemy(CShotManager& _shotManager,
	CEnemyManager& _enemyManager)
{
	//弾の数だけループ
	for (int i = 0; i < _shotManager.GetNum(); i++)
	{
		//弾の情報を取得
		CShot& shot = _shotManager.GetShot(i);
		//弾が出現していなかったらコンテニュー
		if (!shot.GetIsActive())continue;

		//敵の数だけループ
		for (int j = 0; j < _enemyManager.GetNum(); j++)
		{
			//敵一体分の情報を取得
			CEnemy& enemy = _enemyManager.GetEnemy(j);

			//敵が出現していなかったらコンテニュー
			if (!enemy.GetIsActive())continue;

			//弾の情報
			VECTOR shotPos = shot.GetPos();
			float shotRadius = shot.GetRadius();
			//敵の情報
			VECTOR enemyPos = enemy.GetPos();
			float enemyRadius = enemy.GetRadius();

			//当たり判定
			bool isHit = CCollision::CheckHitSphereToSphere(
				shotPos, shotRadius, enemyPos, enemyRadius);
			if (isHit)
			{

				shot.HitCalc();
				enemy.HitCalc();

			}
		}
	}
}

//プレイヤーと敵の当たり判定
void CCollisionManger::CheckHitPlayerToEnemy(CPlayer& _player,
	CEnemyManager& _enemyManager)
{
	//プレイヤーが生きてなかったら処理をしない
	if (_player.GetActive() == false)return;

	for (int i = 0; i < _enemyManager.GetNum(); i++)
	{
		//敵一体分の情報を取得
		CEnemy& enemy = _enemyManager.GetEnemy(i);

		if (enemy.GetIsActive() == false)return;

		//弾の情報
		VECTOR playerPos = _player.GetPos();
		float playerRadius = _player.GetRadius();
		//敵の情報
		VECTOR enemyPos = enemy.GetPos();
		float enemyRadius = enemy.GetRadius();

		//プレイヤーと敵が当たったかを判定
		bool isHit = CCollision::CheckHitSphereToSphere(
			playerPos, playerRadius, enemyPos, enemyRadius);

		//当たったら
		if (isHit == true)
		{
			_player.HitCalc();
		}
	}

}
