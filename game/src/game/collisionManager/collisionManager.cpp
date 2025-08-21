#include "collisionManager.h"
#include "../../lib/collision/collision.h"
#include "../FOV/FOV.h"
#include "../attack/attack.h"

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
//	  敵の攻撃範囲とプレイヤーの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitEnemyAttackToPlayer(CEnemyManager& _enemyManager,
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

		//敵の攻撃クラスを取得
		CAttack* attack = enemy->GetAttack();

		//敵の攻撃範囲にプレイヤーが入っているかどうか
		if (CCollision::CheckHitSphereToSphere(_player.GetCenter(), _player.GetRad(), attack->GetPos(), attack->GetRad()) == true)
		{
			attack->SetIsAttackable(true);
		}
		else
		{
			attack->SetIsAttackable(false);
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
			float playerRotY = atan2f(_player.GetMovePos().x - enemy->GetMovePos().x,
				_player.GetMovePos().z - enemy->GetMovePos().z);

			//プレイヤーの押し出し計算
			VECTOR playerPush;
			playerPush.x = cosf(playerRotY) * push;
			playerPush.y = 0;
			playerPush.z = sinf(playerRotY) * push;
			
			//プレイヤーを押し出す
			//_player.ObjPush(playerPush);
			//_player.SetSpeed();

			//敵の押し出し角度
			float enemyRotY = atan2f(enemy->GetMovePos().x -_player.GetMovePos().x,
				enemy->GetMovePos().z - _player.GetMovePos().z);

			//敵の押し出し計算
			VECTOR enemyPush;
			enemyPush.x = cosf(enemyRotY) * push;
			enemyPush.y = 0;
			enemyPush.z = sinf(enemyRotY) * push;

			//敵を押し出す
			//enemy->ObjPush(enemyPush);
			enemy->SetSpeed();
		}
		
	}
}

//----------------------------------------------
//				敵と敵の当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitEnemyToEnemy(CEnemyManager& _enemyManager)
{
	for (int i = 0; i < _enemyManager.GetEnemyNum(); i++)
	{
		//敵１を保存
		CEnemy* enemy1 = _enemyManager.GetEnemy(i);

		//敵１が死んだらスキップ
		if (enemy1->GetActive() == false)continue;

		for (int j = 0; j < _enemyManager.GetEnemyNum(); j++)
		{
			//敵２を保存
			CEnemy* enemy2 = _enemyManager.GetEnemy(j);

			//敵２が死ぬまたは敵１と敵２が同じだったらスキップ
			if (enemy2->GetActive() == false || i == j)continue;

			//当たっているかどうか
			if (CCollision::CheckHitSphereToSphere(enemy1->GetMovePos(), enemy1->GetRad(), enemy2->GetMovePos(), enemy2->GetRad()) == true)
			{
				// 敵１から敵２までの距離を計算
				float lengthX = enemy1->GetMovePos().x - enemy2->GetMovePos().x;	// どうせ2乗するとマイナスが消えるので、順番はどうでもいい
				lengthX *= lengthX;
				float lengthY =  enemy1->GetMovePos().y - enemy2->GetMovePos().y;	// どうせ2乗するとマイナスが消えるので、順番はどうでもいい
				lengthY *= lengthY;
				float lengthZ = enemy1->GetMovePos().z - enemy2->GetMovePos().z;	// どうせ2乗するとマイナスが消えるので、順番はどうでもいい
				lengthZ *= lengthZ;
				float length = lengthX + lengthY + lengthZ;		// これがaの2乗＋bの2乗

				// 2つの円の半径を加算し、2乗する
				float lengthRadius = enemy1->GetRad() + enemy2->GetRad();
				lengthRadius *= lengthRadius;

				//押し出す量を求める
				float push = (lengthRadius - length) / 2.0f;

				//プレイヤーの押し出す角度
				float enemy1RotY = atan2f(enemy1->GetMovePos().x - enemy2->GetMovePos().x,
					enemy1->GetMovePos().z - enemy2->GetMovePos().z);

				//プレイヤーの押し出し計算
				VECTOR enemy1Push;
				enemy1Push.x = cosf(enemy1RotY) * push;
				enemy1Push.y = 0;
				enemy1Push.z = sinf(enemy1RotY) * push;

				//プレイヤーを押し出す
				enemy1->ObjPush(enemy1Push);

				//敵の押し出し角度
				float enemy2RotY = atan2f(enemy2->GetMovePos().x - enemy1->GetMovePos().x,
					enemy2->GetMovePos().z - enemy2->GetMovePos().z);

				//敵の押し出し計算
				VECTOR enemy2Push;
				enemy2Push.x = cosf(enemy2RotY) * push;
				enemy2Push.y = 0;
				enemy2Push.z = sinf(enemy2RotY) * push;

				//敵を押し出す
				enemy2->ObjPush(enemy2Push);
			}
		}

	}
}
