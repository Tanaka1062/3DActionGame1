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

		//敵の攻撃可能範囲にプレイヤーが入っているか
		if (CCollision::CheckHitSphereToSphere(_player.GetCenter(), _player.GetRad(), enemy->GetCenter(), attack->GetAttackableRad()) == true)
		{
			attack->SetIsAttackable(true);
		}
		else
		{
			attack->SetIsAttackable(false);
		}

		//敵の攻撃がプレイヤーに当たっているか
		if (CCollision::CheckHitSphereToSphere(_player.GetCenter(), _player.GetRad(),
			attack->GetCenter(), attack->GetRad()) == true &&
			attack->GetActive() == true)
		{
			//プレイヤーに敵の攻撃力分ダメージ
			_player.HitAttack(enemy->GetAtk());
		}

		//プレイヤーの攻撃クラスを取得
		attack = _player.GetAttack();

		//プレイヤーの攻撃が敵に当たっているか
		if (CCollision::CheckHitSphereToSphere(enemy->GetCenter(), enemy->GetRad(),
			attack->GetCenter(), attack->GetRad()) == true &&
			attack->GetActive() == true)
		{
			//敵にプレイヤーの攻撃力分ダメージ
			enemy->HitAttack(_player.GetAtk());
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

		//プレイヤーの押し戻し処理-------------------------------------
		
		//判定用のプレイヤー座標を保存
		VECTOR playerPos = _player.GetCenter();
		//プレイヤーの速度を保存
		VECTOR playerSpeed = _player.GetSpeed();

		//Xだけ移動した時の座標
		playerPos.x += playerSpeed.x;

		//Xだけ移動したプレイヤーと敵の当たり判定
		if (CCollision::CheckHitSphereToSphere(playerPos, _player.GetRad(),
			enemy->GetCenter(), enemy->GetRad()) == true)
		{
			//Xの移動だけを取り消す
			playerSpeed.x = 0.0f;
		}

		//Yだけ移動したときの座標
		playerPos = _player.GetCenter();
		playerPos.y += playerSpeed.y;

		//Yだけ移動したプレイヤーと敵の当たり判定
		if (CCollision::CheckHitSphereToSphere(playerPos, _player.GetRad(),
			enemy->GetCenter(), enemy->GetRad()) == true)
		{
			//Yの移動だけを取り消す
			playerSpeed.y = 0.0f;
		}

		//Zだけ移動したときの座標
		playerPos = _player.GetCenter();
		playerPos.z += playerSpeed.z;

		//Zだけ移動したプレイヤーと敵の当たり判定
		if (CCollision::CheckHitSphereToSphere(playerPos, _player.GetRad(),
			enemy->GetCenter(), enemy->GetRad()) == true)
		{
			//Zの移動だけを取り消す
			playerSpeed.z = 0.0f;
		}

		//変更したスピードをセット
		_player.SetSpeed(playerSpeed);

		//-------------------------------------------------------------

		//敵の押し戻し処理------------------------------------------------

		//判定用の敵座標を保存
		VECTOR enemyPos = enemy->GetCenter();
		//敵の速度を保存
		VECTOR enemySpeed = enemy->GetSpeed();

		//Xだけ移動した時の座標
		enemyPos.x += enemySpeed.x;

		//Xだけ移動した敵とプレイヤーの当たり判定
		if (CCollision::CheckHitSphereToSphere(enemyPos, enemy->GetRad(),
			_player.GetCenter(), _player.GetRad()) == true)
		{
			//Xの移動だけを取り消す
			enemySpeed.x = 0.0f;
		}

		//Yだけ移動したときの座標
		enemyPos = enemy->GetCenter();
		enemyPos.y += enemySpeed.y;

		//Yだけ移動した敵とプレイヤーの当たり判定
		if (CCollision::CheckHitSphereToSphere(enemyPos, enemy->GetRad(),
			_player.GetCenter(), _player.GetRad()) == true)
		{
			//Zの移動だけを取り消す
			enemySpeed.y = 0.0f;
		}

		//Zだけ移動したときの座標
		enemyPos = enemy->GetCenter();
		enemyPos.z += enemySpeed.z;

		//Zだけ移動した敵とプレイヤーの当たり判定
		if (CCollision::CheckHitSphereToSphere(enemyPos, enemy->GetRad(),
			_player.GetCenter(), _player.GetRad()) == true)
		{
			//Zの移動だけを取り消す
			enemySpeed.z = 0.0f;
		}

		//変更したスピードをセット
		enemy->SetSpeed(enemySpeed);
		//----------------------------------------------------------------

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

			//敵1の押し戻し処理------------------------------------------------

			//判定用の敵1座標を保存
			VECTOR enemy1Pos = enemy1->GetCenter();
			//敵1の速度を保存
			VECTOR enemy1Speed = enemy1->GetSpeed();

			//Xだけ移動した時の座標
			enemy1Pos.x += enemy1Speed.x;

			//Xだけ移動した敵1と敵2の当たり判定
			if (CCollision::CheckHitSphereToSphere(enemy1Pos, enemy1->GetRad(),
				enemy2->GetCenter(), enemy2->GetRad()) == true)
			{
				//Xの移動だけを取り消す
				enemy1Speed.x = 0.0f;
			}

			//Yだけ移動したときの座標
			enemy1Pos = enemy1->GetCenter();
			enemy1Pos.y += enemy1Speed.y;

			//Yだけ移動した敵1と敵2の当たり判定
			if (CCollision::CheckHitSphereToSphere(enemy1Pos, enemy1->GetRad(),
				enemy2->GetCenter(), enemy2->GetRad()) == true)
			{
				//Zの移動だけを取り消す
				enemy1Speed.y = 0.0f;
			}

			//Zだけ移動したときの座標
			enemy1Pos = enemy1->GetCenter();
			enemy1Pos.z += enemy1Speed.z;

			//Zだけ移動した敵1と敵2の当たり判定
			if (CCollision::CheckHitSphereToSphere(enemy1Pos, enemy1->GetRad(),
				enemy2->GetCenter(), enemy2->GetRad()) == true)
			{
				//Zの移動だけを取り消す
				enemy1Speed.z = 0.0f;
			}

			//変更したスピードをセット
			enemy1->SetSpeed(enemy1Speed);
			//----------------------------------------------------------------

			//敵2の押し戻し処理------------------------------------------------

			//判定用の敵2座標を保存
			VECTOR enemy2Pos = enemy2->GetCenter();
			//敵1の速度を保存
			VECTOR enemy2Speed = enemy2->GetSpeed();

			//Xだけ移動した時の座標
			enemy2Pos.x += enemy2Speed.x;

			//Xだけ移動した敵2と敵1の当たり判定
			if (CCollision::CheckHitSphereToSphere(enemy2Pos, enemy2->GetRad(),
				enemy1->GetCenter(), enemy1->GetRad()) == true)
			{
				//Xの移動だけを取り消す
				enemy2Speed.x = 0.0f;
			}

			//Yだけ移動したときの座標
			enemy2Pos = enemy2->GetCenter();
			enemy2Pos.y += enemy2Speed.y;

			//Yだけ移動した敵2と敵1の当たり判定
			if (CCollision::CheckHitSphereToSphere(enemy2Pos, enemy2->GetRad(),
				enemy1->GetCenter(), enemy1->GetRad()) == true)
			{
				//Zの移動だけを取り消す
				enemy2Speed.y = 0.0f;
			}

			//Zだけ移動したときの座標
			enemy2Pos = enemy2->GetCenter();
			enemy2Pos.z += enemy2Speed.z;

			//Zだけ移動した敵1と敵2の当たり判定
			if (CCollision::CheckHitSphereToSphere(enemy2Pos, enemy2->GetRad(),
				enemy1->GetCenter(), enemy1->GetRad()) == true)
			{
				//Zの移動だけを取り消す
				enemy2Speed.z = 0.0f;
			}

			//変更したスピードをセット
			enemy2->SetSpeed(enemy2Speed);
			//----------------------------------------------------------------

		}

	}
}
