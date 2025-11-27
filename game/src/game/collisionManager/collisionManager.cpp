#include "collisionManager.h"
#include "../../lib/collision/collision.h"
#include "../FOV/FOV.h"
#include "../../lib/effekseer/effekseer.h"
#include "../system/effectData/effectData.h"

//----------------------------------------------
//			オブジェクト同士の当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitObjectToObject(CObject* _objectA, CObject* _objectB)
{
	//二つのオブジェクトが消えていたら処理をしない
	if (_objectA->GetActive() == false || _objectB->GetActive() == false)return;

	//オブジェクト同士が当たっているか
	if (CCollision::CheckHitSphereToSphere(_objectA->GetCenter(), _objectA->GetRad(),
		_objectB->GetCenter(), _objectB->GetRad()) == true)
	{
		//それぞれ当たり判定の処理をする
		_objectA->HitCalc(_objectB);
		_objectB->HitCalc(_objectA);

	}

	//どちらかのオブジェクトが押し出し処理をしない場合は押し出し処理をしない
	if (_objectA->GetIsPushed() == false || _objectB->GetIsPushed() == false)return;

	//押し戻し処理-------------------------------------------------

	//本来離れてほしい距離を求める
	float len1 = _objectA->GetRad() + _objectB->GetRad();

	//実際に離れている距離を求める
	VECTOR objectAPos = _objectA->GetPos();
	VECTOR objectBPos = _objectB->GetPos();

	VECTOR dir = VSub(objectBPos, objectAPos);
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

		objectBPos = VAdd(_objectB->GetPos(), dir);

		_objectB->SetPos(VAdd(_objectB->GetPos(), dir));


		VECTOR dir2 = VSub(objectAPos, objectBPos);
		dir2 = VNorm(dir2);
		dir2 = VScale(dir2, len3);

		objectAPos = VAdd(_objectA->GetPos(), dir2);

		_objectA->SetPos(VAdd(_objectA->GetPos(), dir2));
	}

	//-------------------------------------------------------------

}


//----------------------------------------------
//	 	 プレイヤーと攻撃判定の当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitPlayerToPlayerAttack(CPlayerManager& _playerManager,
	CAttackManager& _attackManager)
{
	for (int player_j = 0; player_j < _playerManager.GetPlayerNum(); player_j++)
	{
		//プレイヤーのクラスを取得
		CPlayer* player = _playerManager.GetPlayer(player_j);

		for (int attack_i = 0; attack_i < _attackManager.GetNum(); attack_i++)
		{
			//攻撃のクラスを取得
			CAttackBase* attack = _attackManager.GetAttack(attack_i);

			//当たり判定
			CheckHitObjectToObject(player, attack);
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

			CheckHitObjectToObject(player1, player2);
			
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

		VECTOR shadowPos = player->GetPos();

		//少しずつ座標を落として当たった場所に丸影の座標を設定する
		for (int shadowPosY_i = 0; shadowPosY_i < 1000; shadowPosY_i++)
		{
			shadowPos.y -= 0.01f * shadowPosY_i;

			col = MV1CollCheck_Sphere(_map.GetHitHndl(), -1,
				shadowPos, 1.0f);

			if (col.HitNum != 0)
			{
				shadowPos.y += 1.5f;

				player->SetShadowPos(shadowPos);
				break;
			}
		}
		//毎回データを削除
		MV1CollResultPolyDimTerminate(col);


	}
}

//----------------------------------------------
//	   プレイヤーとパワーコインの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitPlayerToPowerCoin(CPlayerManager& _playerManager,
	CPowerCoinManager& _powerCoinManager)
{
	for (int player_i = 0; player_i < _playerManager.GetPlayerNum(); player_i++)
	{
		//プレイヤーのクラスを取得
		CPlayer* player = _playerManager.GetPlayer(player_i);

		for (int powerCoin_j = 0; powerCoin_j < _powerCoinManager.GetPowerCoinNum(); powerCoin_j++)
		{
			//パワーコインのクラスを取得
			CPowerCoin* powerCoin = _powerCoinManager.GetPowerCoin(powerCoin_j);

			CheckHitObjectToObject(player, powerCoin);

		}
	}
}

//----------------------------------------------
//		 パワーコインとマップの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitPowerCoinToMap(CPowerCoinManager& _powerCoinManager, CMap& _map)
{
	//当たり判定情報が格納される構造体
	MV1_COLL_RESULT_POLY_DIM col;

	for (int powerCoin_i = 0; powerCoin_i < _powerCoinManager.GetPowerCoinNum(); powerCoin_i++)
	{
		CPowerCoin* powerCoin = _powerCoinManager.GetPowerCoin(powerCoin_i);

		//出現していないコインはスキップ
		if (powerCoin->GetActive() == false)continue;

		col = MV1CollCheck_Sphere(_map.GetHitHndl(), -1,
			powerCoin->GetCenter(), powerCoin->GetRad());

		//ポリゴンと当たっていたか
		if (col.HitNum != 0)
		{
			//押し戻しの計算-----------------------

			for (int j = 0; j < col.HitNum; j++)
			{

				//中心点から最近点を引き算
				VECTOR vLen = VSub(powerCoin->GetCenter(), col.Dim[j].HitPosition);
				//取得した距離を三平方の定理の長さに変換
				float fLen = VSize(vLen);
				//実際にめり込んだ距離を計算
				fLen = powerCoin->GetRad() - fLen;
				//法線をめり込んだ距離分掛け算する
				vLen = VScale(col.Dim[j].Normal, fLen);

				//プレイヤーの座標を計算した分だけ移動させる
				powerCoin->SetPos(VAdd(powerCoin->GetPos(), vLen));

				//重力をリセット
				powerCoin->GravityReset();

			}
			//-------------------------------------

			//毎回データを削除
			MV1CollResultPolyDimTerminate(col);
		}

		VECTOR shadowPos = powerCoin->GetPos();

		//少しずつ座標を落として当たった場所に丸影の座標を設定する
		for (int shadowPosY_i = 0; shadowPosY_i < 1000; shadowPosY_i++)
		{
			shadowPos.y -= 0.01f * shadowPosY_i;

			col = MV1CollCheck_Sphere(_map.GetHitHndl(), -1,
				shadowPos, 1.0f);

			if (col.HitNum != 0)
			{
				shadowPos.y += 1.5f;

				powerCoin->SetShadowPos(shadowPos);
				break;
			}
		}
		//毎回データを削除
		MV1CollResultPolyDimTerminate(col);


	}


}

//----------------------------------------------
//		アイテムとマップの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitItemToMap(CItemManager& _itemManager, CMap& _map)
{

	//当たり判定情報が格納される構造体
	MV1_COLL_RESULT_POLY_DIM col;

	for (int item_i = 0; item_i < _itemManager.GetItemNum(); item_i++)
	{
		CItemBase* item = _itemManager.GetItem(item_i);

		//中身がnullならスキップする
		if (item == nullptr)continue;

		//生きていなかったら当たり判定をしない
		if (item->GetActive() == false)continue;

		col = MV1CollCheck_Sphere(_map.GetHitHndl(), -1,
			item->GetCenter(), item->GetRad());

		//ポリゴンと当たっていたか
		if (col.HitNum != 0)
		{
			//押し戻しの計算-----------------------

			for (int j = 0; j < col.HitNum; j++)
			{

				//中心点から最近点を引き算
				VECTOR vLen = VSub(item->GetCenter(), col.Dim[j].HitPosition);
				//取得した距離を三平方の定理の長さに変換
				float fLen = VSize(vLen);
				//実際にめり込んだ距離を計算
				fLen = item->GetRad() - fLen;
				//法線をめり込んだ距離分掛け算する
				vLen = VScale(col.Dim[j].Normal, fLen);

				//プレイヤーの座標を計算した分だけ移動させる
				item->SetPos(VAdd(item->GetPos(), vLen));

				//重力をリセット
				item->GravityReset();

			}
			//-------------------------------------

			item->HitMapCalc();

			//毎回データを削除
			MV1CollResultPolyDimTerminate(col);
		}

		VECTOR shadowPos = item->GetPos();

		//少しずつ座標を落として当たった場所に丸影の座標を設定する
		for (int shadowPosY_i = 0; shadowPosY_i < 1000; shadowPosY_i++)
		{
			shadowPos.y -= 0.01f * shadowPosY_i;

			col = MV1CollCheck_Sphere(_map.GetHitHndl(), -1,
				shadowPos, 1.0f);

			if (col.HitNum != 0)
			{
				shadowPos.y += 1.5f;

				item->SetShadowPos(shadowPos);
				break;
			}
		}
		//毎回データを削除
		MV1CollResultPolyDimTerminate(col);
	}
}

//----------------------------------------------
//		アイテムとプレイヤーの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitPlayerToItem(CPlayerManager& _playerManager, CItemManager& _itemManager)
{
	for (int player_i = 0; player_i < _playerManager.GetPlayerNum(); player_i++)
	{
		CPlayer* player = _playerManager.GetPlayer(player_i);

		for (int item_i = 0; item_i < _itemManager.GetItemNum(); item_i++)
		{
			CItemBase* item = _itemManager.GetItem(item_i);

			//当たり判定
			CheckHitObjectToObject(player, item);
		}
	}
}

//----------------------------------------------
//		 アイテムとアイテムの当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitItemToItem(CItemManager& _itemManager)
{
	for (int itemA_i = 0; itemA_i < _itemManager.GetItemNum(); itemA_i++)
	{
		CItemBase* itemA = _itemManager.GetItem(itemA_i);

		for (int itemB_i = 0; itemB_i < _itemManager.GetItemNum(); itemB_i++)
		{
			//同じアイテムは処理をしない
			if (itemA_i == itemB_i)continue;

			CItemBase* itemB = _itemManager.GetItem(itemB_i);

			CheckHitObjectToObject(itemA, itemB);
		}
	}
}
