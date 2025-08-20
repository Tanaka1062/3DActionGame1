#include "collisionManager.h"
#include "../../lib/collision/collision.h"
#include "../FOV/FOV.h"

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
		//敵のクラスを取得
		CEnemy* enemy = _enemyManager.GetEnemy(i);
		
		//敵が死んでいたら処理をしない
		if (enemy->GetActive() == false)continue;

		//敵の視界範囲クラスを取得
		CFOV* enemyFOV = enemy->GetFOV();

		//プレイヤーが敵の視界範囲に入っているかを確認
		if (CCollision::CheckHitSphereToSphere(_player.GetCenter(), _player.GetRad(), enemyFOV->GetPos(), enemyFOV->GetRad()) == true)
		{
			enemyFOV->HitCalc();
		}
	}
}

//----------------------------------------------
//			敵とプレイヤーの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitEnemyToPlayer(CEnemyManager& _enemyManager,
	CPlayer& _player)
{
	//プレイヤーが死んでいたら処理をしない
	if (_player.GetActive() == false)return;

	for (int i = 0; i < _enemyManager.GetEnemyNum(); i++)
	{
		//敵のクラスを取得
		CEnemy* enemy = _enemyManager.GetEnemy(i);

		//敵が死んでいたら処理をしない
		if (enemy->GetActive() == false)continue;

		//移動後の敵とプレイヤーが当たっているかどうか
		if (CCollision::CheckHitSphereToSphere(enemy->GetMovePos(), enemy->GetRad(), _player.GetMovePos(), _player.GetRad()) == true)
		{
			// 敵からプレイヤーまでの距離を計算
			float lengthX = _player.GetMovePos().x - enemy->GetMovePos().x;	// どうせ2乗するとマイナスが消えるので、順番はどうでもいい
			lengthX *= lengthX;
			float lengthY = _player.GetMovePos().y - enemy->GetMovePos().y;	// どうせ2乗するとマイナスが消えるので、順番はどうでもいい
			lengthY *= lengthY;
			float lengthZ = _player.GetMovePos().z - enemy->GetMovePos().z;	// どうせ2乗するとマイナスが消えるので、順番はどうでもいい
			lengthZ *= lengthZ;
			float length = lengthX + lengthY + lengthZ;		// これがaの2乗＋bの2乗

			// 2つの円の半径を加算し、2乗する
			float lengthRadius = _player.GetRad() + enemy->GetRad();
			lengthRadius *= lengthRadius;

			//押し出す量を求める
			float push = (lengthRadius - length) / 2.0f;

			//プレイヤーの押し出す角度
			float playerRotX = atan2f(enemy->GetMovePos().y - _player.GetMovePos().y, 
				enemy->GetMovePos().x - _player.GetMovePos().x);
			float playerRotY = atan2f(enemy->GetMovePos().x - _player.GetMovePos().x,
				enemy->GetMovePos().z - _player.GetMovePos().z);

			//プレイヤーの押し出し計算
			VECTOR playerPush;
			playerPush.x = cosf(playerRotX) * push;
			playerPush.y = sinf(playerRotX) * push;
			playerPush.z = cosf(playerRotY) * push;
			
			//プレイヤーを押し出す
			_player.ObjPush(playerPush);

			//敵の押し出し角度
			float enemyRotX = atan2f(_player.GetMovePos().y - enemy->GetMovePos().y,
				_player.GetMovePos().x - _player.GetMovePos().x);
			float enemyRotY = atan2f(_player.GetMovePos().x - enemy->GetMovePos().x,
				_player.GetMovePos().z - enemy->GetMovePos().z);

			//敵の押し出し計算
			VECTOR enemyPush;
			enemyPush.x = cosf(enemyRotX) * push;
			enemyPush.y = sinf(enemyRotX) * push;
			enemyPush.z = cosf(enemyRotY) * push;

			//敵を押し出す
			enemy->ObjPush(enemyPush);

		}
		
	}
}