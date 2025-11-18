#include "collisionManager.h"
#include "../../lib/collision/collision.h"
#include "../FOV/FOV.h"
#include "../../lib/effekseer/effekseer.h"
#include "../system/effectData/effectData.h"

//----------------------------------------------
//	プレイヤーと攻撃判定の当たり判定
//----------------------------------------------
void CCollisionManager::CheckHitPlayerToPlayerAttack(CPlayerManager& _playerManager,
	CAttackManager& _attackManager)
{
	for (int player_j = 0; player_j < _playerManager.GetPlayerNum(); player_j++)
	{
		//プレイヤーのクラスを取得
		CPlayer* player = _playerManager.GetPlayer(player_j);

		//プレイヤーが死んでいたらスキップ
		if (player->GetActive() == false)continue;

		//プレイヤーが回避中ならスキップ
		if (player->GetIsDodgeroll() == true)continue;

		for (int attack_i = 0; attack_i < _attackManager.GetNum(); attack_i++)
		{
			//攻撃のクラスを取得
			CAttackBase* attack = _attackManager.GetAttack(attack_i);

			//攻撃判定がないやつはスキップ
			if (attack->GetIsAttack() == false)continue;

			//自分が出した攻撃はスキップ
			if (player->GetPlayerName() == attack->GetAttackName())continue;

			//プレイヤーの攻撃がプレイヤーに当たっているか
			if (CCollision::CheckHitSphereToSphere(attack->GetPos(), attack->GetRad(),
				player->GetCenter(), player->GetRad()) == true)
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
			VECTOR player2Pos = player2->GetPos();

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
			VECTOR boxPos = box->GetPos();

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

		//プレイヤーが死んでいたらスキップ
		if (player->GetActive() == false)continue;

		for (int powerCoin_j = 0; powerCoin_j < _powerCoinManager.GetPowerCoinNum(); powerCoin_j++)
		{
			//パワーコインのクラスを取得
			CPowerCoin* powerCoin = _powerCoinManager.GetPowerCoin(powerCoin_j);

			//パワーコインが出ていなかったらスキップ
			if (powerCoin->GetActive() == false)continue;

			//パワーコインが飛んでいたらスキップ
			if (powerCoin->GetState() == POWER_COIN_FLYING)continue;

			if (CCollision::CheckHitSphereToSphere(player->GetCenter(), player->GetRad(),
				powerCoin->GetCenter(), powerCoin->GetRad()) == true)
			{
				powerCoin->HitCalc(player->GetPlayerName());

				player->AddPowerUp();
			}
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

