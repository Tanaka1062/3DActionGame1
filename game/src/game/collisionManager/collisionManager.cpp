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
	CPlayer& _player)
{
	//プレイヤーが死んでいたら処理をしない
	if (_player.GetActive() == false)return;

	for (int i = 0; i < _enemyManager.GetEnemyNum(); i++)
	{
		//敵のクラスを取得
		CEnemyBase* enemy = _enemyManager.GetEnemy(i);
		
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
		CEnemyBase* enemy = _enemyManager.GetEnemy(i);

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

			//呼び出すエフェクトのID
			int effectId = CEffectData::GetId(EFFECT_ATTACK);

			//エフェクトを呼び出す
			CEffekseerCtrl::Request(effectId, _player.GetCenter(), false);

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
			//呼び出すエフェクトのID
			int effectId = CEffectData::GetId(EFFECT_ATTACK);

			//エフェクトを呼び出す
			CEffekseerCtrl::Request(effectId,enemy->GetCenter(),false);

			//ノックバックの方向
			float rot = atan2f(_player.GetCenter().x - enemy->GetCenter().x,
				_player.GetCenter().z - enemy->GetCenter().z);

			//敵にプレイヤーの攻撃力分ダメージ
			enemy->HitAttack(_player.GetAtk(),rot);
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
		if (attack->GetAttackType() != ATTACK_TYPE_PLAYER)continue;

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
	CPlayer& _player)
{
	//プレイヤーが死んでいたら処理をしない
	if (_player.GetActive() == false)return;

	for (int i = 0; i < _enemyManager.GetEnemyNum(); i++)
	{
		//敵のクラスを取得
		CEnemyBase* enemy = _enemyManager.GetEnemy(i);

		//敵が死んでいたら処理をしない
		if (enemy->GetActive() == false)continue;

		//押し戻し処理-------------------------------------------------

		//本来離れてほしい距離を求める
		float len1 = enemy->GetRad() + _player.GetRad();

		//実際に離れている距離を求める
		VECTOR playerPos = _player.GetPos();
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

			dir = VScale(dir,len3);

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
//		  プレイヤーとゴールの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitPlayerToGoal(CPlayer& _player, CGoal& _goal, bool _isFlg)
{
	if (_isFlg == false)return;

	//プレイヤーかゴールが無ければ処理をしない
	if (_player.GetActive() == false ||
		_goal.GetActive() == false)return;

	//プレイヤーがゴールに触れているか
	if (CCollision::CheckHitSphereToSphere(_player.GetCenter(),_player.GetRad(),
		_goal.GetCenter(),_goal.GetRad()) == true)
	{
		//ゴールフラグをtrueに
		_goal.HitCalc();
	}
}

//----------------------------------------------
//		  プレイヤーとマップの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitPlayerToMap(CPlayer& _player,CMap& _map)
{

	//当たり判定情報が格納される構造体
	MV1_COLL_RESULT_POLY_DIM col;

	col = MV1CollCheck_Sphere(_map.GetHitHndl(), -1,
		_player.GetCenter(), _player.GetRad());

	//ポリゴンと当たっていたか
	if (col.HitNum != 0)
	{
		//押し戻しの計算-----------------------
		
		for (int i = 0; i < col.HitNum; i++)
		{

			//中心点から最近点を引き算
			VECTOR vLen = VSub(_player.GetCenter(), col.Dim[i].HitPosition);
			//取得した距離を三平方の定理の長さに変換
			float fLen = VSize(vLen);
			//実際にめり込んだ距離を計算
			fLen = _player.GetRad() - fLen;
			//法線をめり込んだ距離分掛け算する
			vLen = VScale(col.Dim[i].Normal, fLen);

			//プレイヤーの座標を計算した分だけ移動させる
			_player.SetPos(VAdd(_player.GetPos(), vLen));

			//重力をリセット
			_player.GravityReset();

		}
		//-------------------------------------

		//毎回データを削除
		MV1CollResultPolyDimTerminate(col);
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
	CItemInventory& _itemInventory, CPlayer& _player)
{
	//プレイヤーが死んでいたら処理をしない
	if (_player.GetActive() == false)return;

	for (int i = 0; i < _item.GetNum(); i++)
	{
		//アイテムのクラスを取得
		CItemBase* item = _item.GetItem(i);
		
		//アイテムにプレイヤーが当たっているか
		if (CCollision::CheckHitSphereToSphere(item->GetCenter(), item->GetRad(),
			_player.GetCenter(), _player.GetRad()) == true)
		{
			//アイテムを取っていたらプレイヤーがアイテムを取得する
			if (_player.GetIsPickUp() == true)
			{
				//インベントリのアイテム保存用
				CItemBase* inventoryItem = nullptr;
				//アイテムをインベントリに入れる
				inventoryItem = _itemInventory.SetItem(item);
				//インベントリからアイテムに入れる
				_item.SetItem(i,inventoryItem);

				return;
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
void CCollisionManager::CheckHitPlayerToBox(CPlayer& _player, CBoxManager& _box)
{
	//プレイヤーが死んでいたら処理をしない
	if (_player.GetActive() == false)return;

	for (int i = 0; i < _box.GetNum(); i++)
	{
		//ボックス保存用
		CBox* box = _box.GetBox(i);

		//ボックスがなかったらスキップ
		if (box->GetActive() == false)continue;

		
		//押し戻し処理-------------------------------------------------

		//本来離れてほしい距離を求める
		float len1 = box->GetRad() + _player.GetRad();

		//実際に離れている距離を求める
		VECTOR playerPos = _player.GetPos();
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

			playerPos = VAdd(_player.GetPos(), dir);

			_player.SetPos(VAdd(_player.GetPos(), dir));


		}

		//-------------------------------------------------------------

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

