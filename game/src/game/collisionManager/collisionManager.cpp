#include "collisionManager.h"
#include "../../lib/collision/collision.h"
#include "../FOV/FOV.h"
#include "../attack/attack.h"
#include "../../lib/effekseer/effekseer.h"
#include "../system/effectData/effectData.h"

//----------------------------------------------
//		敵の視界とプレイヤーの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitEnemyFOVToPlayer(CEnemyManager& _enemyManager,
	CPlayerManager& _playerManager)
{
	for (int i = 0; i < _playerManager.GetPlayerNum(); i++)
	{
		//プレイヤーのクラスを取得
		CPlayer* player = _playerManager.GetPlayer(i);

		//プレイヤーが死んでいたら処理をしない
		if (player->GetActive() == false)continue;

		for (int j = 0; j < _enemyManager.GetEnemyNum(); j++)
		{
			//敵のクラスを取得
			CEnemyBase* enemy = _enemyManager.GetEnemy(j);

			//敵が死んでいたら処理をしない
			if (enemy->GetActive() == false)continue;

			//敵の視界範囲クラスを取得
			CFOV* enemyFOV = enemy->GetFOV();

			//プレイヤーが敵の視界範囲に入っているかを確認
			if (CCollision::CheckHitSphereToSphere(player->GetCenter(), player->GetRad(), enemyFOV->GetPos(), enemyFOV->GetRad()) == true)
			{
				enemyFOV->HitCalc();
			}
		}
	}
}

//----------------------------------------------
//	  敵の攻撃範囲とプレイヤーの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitEnemyAttackToPlayer(CEnemyManager& _enemyManager,
	CPlayerManager& _playerManager)
{
	for (int i = 0; i < _playerManager.GetPlayerNum(); i++)
	{

		//プレイヤーのクラスを取得
		CPlayer* player = _playerManager.GetPlayer(i);

		//プレイヤーが死んでいたら処理をしない
		if (player->GetActive() == false)continue;

		for (int j = 0; j < _enemyManager.GetEnemyNum(); j++)
		{
			//敵のクラスを取得
			CEnemyBase* enemy = _enemyManager.GetEnemy(j);

			//敵が死んでいたら処理をしない
			if (enemy->GetActive() == false)continue;

			//敵の攻撃クラスを取得
			CAttack* attack = enemy->GetAttack();

			//敵の攻撃可能範囲にプレイヤーが入っているか
			if (CCollision::CheckHitSphereToSphere(player->GetCenter(), player->GetRad(), enemy->GetCenter(), attack->GetAttackableRad()) == true)
			{
				attack->SetIsAttackable(true);
			}
			else
			{
				attack->SetIsAttackable(false);
			}

			//敵の攻撃がプレイヤーに当たっているか
			if (CCollision::CheckHitSphereToSphere(player->GetCenter(), player->GetRad(),
				attack->GetCenter(), attack->GetRad()) == true &&
				attack->GetActive() == true)
			{

				//呼び出すエフェクトのID
				int effectId = CEffectData::GetId(EFFECT_ATTACK);

				//エフェクトを呼び出す
				CEffekseerCtrl::Request(effectId, player->GetCenter(), false);

				//プレイヤーに敵の攻撃力分ダメージ
				player->HitAttack(enemy->GetAtk());
			}

			//プレイヤーの攻撃クラスを取得
			attack = player->GetAttack();

			//プレイヤーの攻撃が敵に当たっているか
			if (CCollision::CheckHitSphereToSphere(enemy->GetCenter(), enemy->GetRad(),
				attack->GetCenter(), attack->GetRad()) == true &&
				attack->GetActive() == true)
			{
				//呼び出すエフェクトのID
				int effectId = CEffectData::GetId(EFFECT_ATTACK);

				//エフェクトを呼び出す
				CEffekseerCtrl::Request(effectId, enemy->GetCenter(), false);

				//ノックバックの方向
				float rot = atan2f(player->GetCenter().x - enemy->GetCenter().x,
					player->GetCenter().z - enemy->GetCenter().z);

				//敵にプレイヤーの攻撃力分ダメージ
				enemy->HitAttack(player->GetAtk(), rot);
			}
		}
	}

}

//----------------------------------------------
//	プレイヤーの攻撃とプレイヤーの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitPlayerAttackToPlayer(CAttackManager& _attackManager,
	CPlayerManager& _playerManager)
{
	for (int attack_i = 0; attack_i < _attackManager.GetNum(); attack_i++)
	{
		//攻撃のクラスを取得
		CAttackBase* attack = _attackManager.GetAttack(attack_i);

		//プレイヤー以外の攻撃はスキップ
		switch (attack->GetAttackType())
		{
		case ATTACK_TYPE_PLAYER1:
		case ATTACK_TYPE_PLAYER2:
			break;
		default:
			continue;
			break;
		}

		for (int player_j = 0; player_j < _playerManager.GetPlayerNum(); player_j++)
		{
			//プレイヤーのクラスを取得
			CPlayer* player = _playerManager.GetPlayer(player_j);

			//プレイヤーが死んでいたらスキップ
			if (player->GetActive() == false)continue;

			//プレイヤーと攻撃のタイプが同じ場合スキップ
			if (player->GetAttackType() == attack->GetAttackType())continue;

			//プレイヤーの攻撃がプレイヤーに当たっているか
			if (CCollision::CheckHitSphereToSphere(attack->GetPos(), attack->GetRad(),
				player->GetCenter(), player->GetRad()) == true &&
				attack->GetIsAttack() == true)
			{
				//呼び出すエフェクトのID
				int effectId = CEffectData::GetId(EFFECT_ATTACK);

				//エフェクトを呼び出す
				CEffekseerCtrl::Request(effectId, player->GetCenter(), false);

				//ノックバックの方向
				float rot = atan2f(attack->GetPos().x - player->GetCenter().x,
					attack->GetPos().z - player->GetCenter().z);

				//敵にプレイヤーの攻撃力分ダメージ
				player->HitAttack(attack->GetAtk(), rot);
			}

		}
	}

}

//----------------------------------------------
//		プレイヤーの攻撃と敵の当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitPlayerAttackToEnemy(CAttackManager& _attackManager,
	CEnemyManager& _enemyManager)
{
	for (int i = 0; i < _attackManager.GetNum(); i++)
	{
		//攻撃のクラスを取得
		CAttackBase* attack = _attackManager.GetAttack(i);
		
		//プレイヤー以外の攻撃はスキップ
		if (attack->GetAttackType() != ATTACK_TYPE_PLAYER1)continue;

		for (int j = 0; j < _enemyManager.GetEnemyNum(); j++)
		{
			//敵のクラスを取得
			CEnemyBase* enemy = _enemyManager.GetEnemy(j);

			//敵が死んでいたらスキップ
			if (enemy->GetActive() == false)continue;

			//プレイヤーの攻撃が敵に当たっているか
			if (CCollision::CheckHitSphereToSphere(attack->GetPos(), attack->GetRad(),
				enemy->GetCenter(), enemy->GetRad()) == true &&
				attack->GetIsAttack() == true)
			{
				//呼び出すエフェクトのID
				int effectId = CEffectData::GetId(EFFECT_ATTACK);

				//エフェクトを呼び出す
				CEffekseerCtrl::Request(effectId, enemy->GetCenter(), false);

				//ノックバックの方向
				float rot = atan2f(attack->GetPos().x - enemy->GetCenter().x,
					attack->GetPos().z - enemy->GetCenter().z);

				//敵にプレイヤーの攻撃力分ダメージ
				enemy->HitAttack(attack->GetAtk(), rot);
			}

		}
	}
}

//----------------------------------------------
//			敵とプレイヤーの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitEnemyToPlayer(CEnemyManager& _enemyManager,
	CPlayerManager& _playerManager)
{

	for (int i = 0; i < _playerManager.GetPlayerNum(); i++)
	{
		//プレイヤーのクラスを取得
		CPlayer* player = _playerManager.GetPlayer(i);

		//プレイヤーが死んでいたら処理をしない
		if (player->GetActive() == false)continue;

		for (int j = 0; j < _enemyManager.GetEnemyNum(); j++)
		{
			//敵のクラスを取得
			CEnemyBase* enemy = _enemyManager.GetEnemy(j);

			//敵が死んでいたら処理をしない
			if (enemy->GetActive() == false)continue;

			//押し戻し処理-------------------------------------------------

			//本来離れてほしい距離を求める
			float len1 = enemy->GetRad() + player->GetRad();

			//実際に離れている距離を求める
			VECTOR playerPos = player->GetPos();
			playerPos.y = 0.0f;
			VECTOR enemyPos = enemy->GetPos();
			enemyPos.y = 0.0f;

			VECTOR dir = VSub(enemyPos, playerPos);
			float len2 = VSize(dir);

			//めり込んでいたら
			if (len1 > len2)
			{
				//めり込み量を求める
				float len3 = len1 - len2;

				//len3 = len3 * 0.5f;

				//移動させるベクトルを求める

				//方向ベクトルなので正規化する
				dir = VNorm(dir);

				dir = VScale(dir, len3);

				enemyPos = VAdd(enemy->GetPos(), dir);

				enemy->SetPos(VAdd(enemy->GetPos(), dir));


				VECTOR dir2 = VSub(playerPos, enemyPos);
				dir2 = VNorm(dir2);
				dir2 = VScale(dir2, len3);

				//playerPos = VAdd(playerPos, dir2);

				//_player.SetPos(VAdd(playerPos, dir2));
			}

			//-------------------------------------------------------------

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
		CEnemyBase* enemy1 = _enemyManager.GetEnemy(i);

		//敵１が死んだらスキップ
		if (enemy1->GetActive() == false)continue;

		for (int j = 0; j < _enemyManager.GetEnemyNum(); j++)
		{
			//敵２を保存
			CEnemyBase* enemy2 = _enemyManager.GetEnemy(j);

			//敵２が死ぬまたは敵１と敵２が同じだったらスキップ
			if (enemy2->GetActive() == false || i == j)continue;

			//押し戻し処理-------------------------------------------------

			//本来離れてほしい距離を求める
			float len1 = enemy1->GetRad() + enemy2->GetRad();

			//実際に離れている距離を求める
			VECTOR enemy1Pos = enemy1->GetPos();
			enemy1Pos.y = 0.0f;
			VECTOR enemy2Pos = enemy2->GetPos();
			enemy2Pos.y = 0.0f;

			VECTOR dir = VSub(enemy1Pos, enemy2Pos);
			float len2 = VSize(dir);

			//めり込んでいたら
			if (len1 > len2)
			{
				//めり込み量を求める
				float len3 = len1 - len2;

				len3 = len3 * 0.5f;

				//移動させるベクトルを求める

				//方向ベクトルなので正規化する
				dir = VNorm(dir);

				dir = VScale(dir, len3);

				//enemy1Pos = VAdd(enemy1->GetPos(), dir);

				enemy1->SetPos(VAdd(enemy1->GetPos(), dir));

				VECTOR dir2 = VSub(enemy2Pos, enemy1Pos);
				dir2 = VNorm(dir2);
				dir2 = VScale(dir2, len3);

				enemy2Pos = VAdd(enemy2->GetPos(), dir2);

				enemy2->SetPos(enemy2Pos);
			}

			//-------------------------------------------------------------

		}

	}
}

//----------------------------------------------
//		プレイヤーとプレイヤーの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitPlayerToPlayer(CPlayerManager& _playerManager)
{
	for (int player1_i = 0; player1_i < _playerManager.GetPlayerNum(); player1_i++)
	{
		//プレイヤー1のクラスを取得
		CPlayer* player1 = _playerManager.GetPlayer(player1_i);

		//プレイヤー1が死んでいたら処理をしない
		if (player1->GetActive() == false)continue;

		for (int player2_j = 0; player2_j < _playerManager.GetPlayerNum(); player2_j++)
		{
			//同じプレイヤー同士では処理をしない
			if (player1_i == player2_j)continue;

			//敵のクラスを取得
			CPlayer* player2 = _playerManager.GetPlayer(player2_j);

			//敵が死んでいたら処理をしない
			if (player2->GetActive() == false)continue;
			
			//押し戻し処理-------------------------------------------------

			//本来離れてほしい距離を求める
			float len1 = player1->GetRad() + player2->GetRad();

			//実際に離れている距離を求める
			VECTOR player1Pos = player1->GetPos();
			player1Pos.y = 0.0f;
			VECTOR player2Pos = player2->GetPos();
			player2Pos.y = 0.0f;

			VECTOR dir = VSub(player2Pos, player1Pos);
			float len2 = VSize(dir);

			//めり込んでいたら
			if (len1 > len2)
			{
				//めり込み量を求める
				float len3 = len1 - len2;

				len3 = len3 * 0.5f;

				//移動させるベクトルを求める

				//方向ベクトルなので正規化する
				dir = VNorm(dir);

				dir = VScale(dir, len3);

				player2Pos = VAdd(player2->GetPos(), dir);

				player2->SetPos(VAdd(player2->GetPos(), dir));


				VECTOR dir2 = VSub(player1Pos, player2Pos);
				dir2 = VNorm(dir2);
				dir2 = VScale(dir2, len3);

				player1Pos = VAdd(player1->GetPos(), dir2);

				player1->SetPos(VAdd(player1->GetPos(), dir2));
			}

			//-------------------------------------------------------------

		}
	}

}

//----------------------------------------------
//				弾と敵の当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitShotToEnemy(CShotManager& _shotManager,
	CEnemyManager& _enemyManager)
{
	//弾の数が0発なら処理をしない
	if (_shotManager.GetNum() == 0)return;
	//敵が全部死んでいたら処理をしない
	if (_enemyManager.GetIsAllDie() == true)return;

	//弾のクラス保存用
	CShotBase* shot ;
	for (int i = 0; i < _shotManager.GetNum(); i++)
	{
		//弾を保存
		shot = _shotManager.GetShot(i);

		for (int j = 0; j < _enemyManager.GetEnemyNum(); j++)
		{
			//敵を保存
			CEnemyBase* enemy = _enemyManager.GetEnemy(j);

			//敵が死んだらスキップ
			if (enemy->GetActive() == false)continue;

			//弾と敵の当たり判定
			if (CCollision::CheckHitSphereToSphere(shot->GetCenter(), shot->GetRad(),
				enemy->GetCenter(), enemy->GetRad()) == true)
			{
				
				//ノックバックの方向
				float rot = atan2f(shot->GetCenter().x - enemy->GetCenter().x,
					shot->GetCenter().z - enemy->GetCenter().z);

				//敵に弾の攻撃力分のダメージを与える
				enemy->ShotAttack(shot->GetAtk(),rot);

				//弾を消す
				shot->SetActive(false);
			}
			
		}
	}
}

//----------------------------------------------
//		  プレイヤーとマップの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitPlayerToMap(CPlayerManager& _playerManager,CMap& _map)
{
	for (int i = 0; i < _playerManager.GetPlayerNum(); i++)
	{
		//プレイヤーのクラスを取得
		CPlayer* player = _playerManager.GetPlayer(i);

		//プレイヤーが死んでいたらスキップ
		if (player->GetActive() == false)continue;

		//当たり判定情報が格納される構造体
		MV1_COLL_RESULT_POLY_DIM col;

		col = MV1CollCheck_Sphere(_map.GetHitHndl(), -1,
			player->GetCenter(), player->GetRad());

		//ポリゴンと当たっていたか
		if (col.HitNum != 0)
		{
			//押し戻しの計算-----------------------

			for (int j = 0; j < col.HitNum; j++)
			{

				//中心点から最近点を引き算
				VECTOR vLen = VSub(player->GetCenter(), col.Dim[j].HitPosition);
				//取得した距離を三平方の定理の長さに変換
				float fLen = VSize(vLen);
				//実際にめり込んだ距離を計算
				fLen = player->GetRad() - fLen;
				//法線をめり込んだ距離分掛け算する
				vLen = VScale(col.Dim[j].Normal, fLen);

				//プレイヤーの座標を計算した分だけ移動させる
				player->SetPos(VAdd(player->GetPos(), vLen));

				//重力をリセット
				player->GravityReset();

			}
			//-------------------------------------

			//毎回データを削除
			MV1CollResultPolyDimTerminate(col);
		}
	}
}

//----------------------------------------------
//			敵とマップの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitEnemyToMap(CEnemyManager& _enemy, CMap& _map)
{
	//当たり判定情報が格納される構造体
	MV1_COLL_RESULT_POLY_DIM col;

	for (int i = 0; i < _enemy.GetEnemyNum(); i++)
	{
		//敵のクラスを取得
		CEnemyBase* enemy = _enemy.GetEnemy(i);
		//敵が生きていなかったらスキップ
		if (enemy->GetActive() == false)continue;

		col = MV1CollCheck_Sphere(_map.GetHitHndl(), -1,
			enemy->GetCenter(), enemy->GetRad());

		//ポリゴンと当たっていたか
		if (col.HitNum != 0)
		{
			//押し戻しの計算-----------------------

			for (int i = 0; i < col.HitNum; i++)
			{

				//中心点から最近点を引き算
				VECTOR vLen = VSub(enemy->GetCenter(), col.Dim[i].HitPosition);
				//取得した距離を三平方の定理の長さに変換
				float fLen = VSize(vLen);
				//実際にめり込んだ距離を計算
				fLen = enemy->GetRad() - fLen;
				//法線をめり込んだ距離分掛け算する
				vLen = VScale(col.Dim[i].Normal, fLen);

				//敵の座標を計算した分だけ移動させる
				enemy->SetPos(VAdd(enemy->GetPos(), vLen));

				//重力をリセット
				enemy->GravityReset();

			}
			//-------------------------------------

		}
		//毎回データを削除
		MV1CollResultPolyDimTerminate(col);
	}

}

//----------------------------------------------
//		アイテムとプレイヤーの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitItemToPlayer(CItemManager& _item,
	CItemInventory& _itemInventory, CPlayerManager& _playerManager)
{
	for (int i = 0; i < _playerManager.GetPlayerNum(); i++)
	{
		//プレイヤーのクラスを取得
		CPlayer* player = _playerManager.GetPlayer(i);

		//プレイヤーが死んでいたら処理をしない
		if (player->GetActive() == false)return;

		for (int j = 0; j < _item.GetNum(); j++)
		{
			//アイテムのクラスを取得
			CItemBase* item = _item.GetItem(j);

			//アイテムにプレイヤーが当たっているか
			if (CCollision::CheckHitSphereToSphere(item->GetCenter(), item->GetRad(),
				player->GetCenter(), player->GetRad()) == true)
			{
				//アイテムを取っていたらプレイヤーがアイテムを取得する
				if (player->GetIsPickUp() == true)
				{
					//インベントリのアイテム保存用
					CItemBase* inventoryItem = nullptr;
					//アイテムをインベントリに入れる
					inventoryItem = _itemInventory.SetItem(item,player);
					//インベントリからアイテムに入れる
					_item.SetItem(j, inventoryItem,player);

					return;
				}
			}

		}
	}
}

//----------------------------------------------
//			  攻撃と箱の当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitAttackToBox(CAttackManager& _attack, CBoxManager& _box)
{
	for (int i = 0; i < _attack.GetNum(); i++)
	{
		//攻撃のクラスを取得
		CAttackBase* attack = _attack.GetAttack(i);

		//攻撃していなかったらスキップ
		if (attack->GetActive() == false)continue;

		for (int j = 0; j < _box.GetNum(); j++)
		{
			//箱のクラスを取得
			CBox* box = _box.GetBox(j);
			
			//箱が無かったらスキップする
			if (box->GetActive() == false)continue;

			//攻撃に触れていたら箱にダメージを与える
			if (CCollision::CheckHitSphereToSphere(attack->GetCenter(), attack->GetRad(),
				box->GetCenter(), box->GetRad()))
			{
				//攻撃の攻撃力分、箱の体力を減らす
				box->SubHp(attack->GetAtk());
			}
		}
	}
}

//----------------------------------------------
//			プレイヤーと箱の当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitPlayerToBox(CPlayerManager& _playerManager, CBoxManager& _box)
{

	for (int i = 0; i < _playerManager.GetPlayerNum(); i++)
	{
		//プレイヤーのクラスを取得
		CPlayer* player = _playerManager.GetPlayer(i);

		//プレイヤーが死んでいたら処理をしない
		if (player->GetActive() == false)return;

		for (int j = 0; j < _box.GetNum(); j++)
		{
			//ボックス保存用
			CBox* box = _box.GetBox(j);

			//ボックスがなかったらスキップ
			if (box->GetActive() == false)continue;


			//押し戻し処理-------------------------------------------------

			//本来離れてほしい距離を求める
			float len1 = box->GetRad() + player->GetRad();

			//実際に離れている距離を求める
			VECTOR playerPos = player->GetPos();
			playerPos.y = 0.0f;
			VECTOR boxPos = box->GetPos();
			boxPos.y = 0.0f;

			VECTOR dir = VSub(playerPos, boxPos);
			float len2 = VSize(dir);

			//めり込んでいたら
			if (len1 > len2)
			{
				//めり込み量を求める
				float len3 = len1 - len2;

				//len3 = len3 * 0.5f;

				//移動させるベクトルを求める

				//方向ベクトルなので正規化する
				dir = VNorm(dir);

				dir = VScale(dir, len3);

				playerPos = VAdd(player->GetPos(), dir);

				player->SetPos(VAdd(player->GetPos(), dir));


			}

			//-------------------------------------------------------------

		}
	}
}

//----------------------------------------------
//			   箱とマップの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitBoxToMap(CBoxManager& _box, CMap& _map)
{
		//当たり判定情報が格納される構造体
	MV1_COLL_RESULT_POLY_DIM col;

	for (int i = 0; i < _box.GetNum(); i++)
	{
		//ボックス保存用
		CBox* box = _box.GetBox(i);

		//ボックスがなかったらスキップ
		if (box->GetActive() == false)continue;

		col = MV1CollCheck_Sphere(_map.GetHitHndl(), -1,
			box->GetCenter(), box->GetRad());
	
		//ポリゴンと当たっていたか
		if (col.HitNum != 0)
		{
			//押し戻しの計算-----------------------
			
			for (int j = 0; j < col.HitNum; j++)
			{
	
				//中心点から最近点を引き算
				VECTOR vLen = VSub(box->GetCenter(), col.Dim[j].HitPosition);
				//取得した距離を三平方の定理の長さに変換
				float fLen = VSize(vLen);
				//実際にめり込んだ距離を計算
				fLen = box->GetRad() - fLen;
				//法線をめり込んだ距離分掛け算する
				vLen = VScale(col.Dim[j].Normal, fLen);
	
				//プレイヤーの座標を計算した分だけ移動させる
				box->SetPos(VAdd(box->GetPos(), vLen));
	
				//重力をリセット
				box->GravityReset();
	
			}
			//-------------------------------------
	
			//毎回データを削除
			MV1CollResultPolyDimTerminate(col);
		}
	}

}

