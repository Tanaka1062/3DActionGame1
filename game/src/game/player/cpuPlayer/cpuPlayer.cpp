#include "cpuPlayer.h"
#include "../../data.h"
#include "../../../lib/myMath/myMath.h"
#include <math.h>
#include "../../common.h"
#include "../../../lib/input/controllerManager.h"
#include"../../../lib/input/keyInput.h"
#include "../playerManager.h"
#include "../../../lib/effekseer/effekseer.h"
#include "../../system/effectData/effectData.h"
#include "../../item/itemBase.h"
#include "../../camera/cameraManager.h"

using namespace PlayerData;

//定義関連---------------------------
constexpr float ATTACK_START_DISTANCE = 15.0f;		//攻撃に移行する距離
constexpr int	ADD_CPU_STATE_PROBABILITY = 10;		//行動状態の上昇確率
constexpr int	CPU_STATE_CHANGE_TIME = 3 * 60;		//行動が変わるまでの時間
//-----------------------------------

//-----------------------
//	コンストラクタ
//-----------------------
CCpuPlayer::CCpuPlayer()
{
	m_targetPos = nullptr;
	m_FOV = nullptr;
	m_cpuState = CPU_STATE_NONE;
	m_targetObject = nullptr;
	m_changeTime = 0;

	for (int cpuState_i = 0; cpuState_i < CPU_STATE_NUM; cpuState_i++)
	{
		m_cpuStateProbability[cpuState_i] = 0;
	}
}

//-----------------------
//		初期化
//-----------------------
void CCpuPlayer::Init(tagPlayerName _name, tagPadName _padName)
{
	CPlayer::Init(_name, _padName);

	m_FOV->Init();
	m_cpuState = CPU_STATE_NONE;
	m_targetObject = nullptr;
	m_isCpu = true;
	m_changeTime = 0;

}

//-----------------------
//毎フレームする処理
//-----------------------
void CCpuPlayer::Step(float _rotY, VECTOR* _targetPos, CAttackManager* _attackManager, CShotManager* _shotManager)
{

	m_FOV->SetPos(CCameraManager::GetFocusPos());
	m_FOV->Step(this);

	CPlayer::Step(_rotY,_targetPos,_attackManager,_shotManager);

	//行動状態が無かったら変更する
	if (m_cpuState == CPU_STATE_NONE || m_targetObject == nullptr)
	{
		ChangeCpuState();
	}
	else
	{
		m_changeTime++;
	}

	if (m_changeTime >= CPU_STATE_CHANGE_TIME)
	{
		m_changeTime = 0;
		ChangeCpuState();
	}

	//ターゲットのオブジェクトが視界から消えたらターゲットを解除する---------------------
	
	//ターゲットが視界内にいるかどうかフラグ
	bool isFOVTargetObject = false;

	for (int FOVObject_i = 0; FOVObject_i < m_FOV->GetObjectBufNum(); FOVObject_i++)
	{
		if (m_targetObject == m_FOV->GetObjectBuf(FOVObject_i)) 
		{
			isFOVTargetObject = true;
			break;
		}
	}

	if (isFOVTargetObject == false)
	{
		m_targetObject = nullptr;
	}

	//-----------------------------------------------------------------------------------

	//攻撃状態中の行動変化
	if (m_cpuState == CPU_STATE_ATTACK)
	{
		if (_attackManager->GetIsHit(m_attackId) == false)
		{
			//最後の攻撃が終わったら行動を変更する
			if (m_state == ATTACK_OUT)
			{
				m_cpuState = CPU_STATE_NONE;
				m_attackNum = 0;
			}
		}
	}


	//自動で立ち上がるよう
	if (m_state == tagState::DOWN)
	{
		m_state = tagState::GET_UP;
	}
}

//-----------------------
//		描写処理
//-----------------------
void CCpuPlayer::Draw()
{
	CPlayer::Draw();
	m_FOV->Draw();
}

//-----------------------
//	当たり判定後の処理
//-----------------------
void CCpuPlayer::HitCalc(CObject* _hitObject)
{
	//_hitObjectがnullだったら処理をしない
	if (_hitObject == nullptr)return;

	//攻撃の当たり判定の場合の処理-----------------------------------------
	if (_hitObject->GetObjectName() == OBJECT_ATTACK)
	{
		//ダウン状態と起き上がり中は判定をしない
		if (m_state == tagState::DOWN ||
			m_state == tagState::DOWN_IN ||
			m_state == tagState::GET_UP)
			return;


		//当たり判定保存用
		CAttackBase* attack = nullptr;

		attack = dynamic_cast<CAttackBase*>(_hitObject);

		//攻撃判定が消えている場合処理をしない
		if (attack->GetIsAttack() == false)return;

		//自分が出した攻撃の場合処理をしない
		if (attack->GetAttackName() == m_name)return;

		//ノックバックの方向
		float rot = atan2f(attack->GetPos().x - GetCenter().x,
			attack->GetPos().z - GetCenter().z);

		HitAttack(attack->GetAtk(), attack->GetBlown(), rot);

		//呼び出すエフェクトのID
		int effectId = CEffectData::GetId(EFFECT_ATTACK);

		//エフェクトを呼び出す
		CEffekseerCtrl::Request(effectId, GetCenter(),false);

		//アイテムを落とす
		m_itemState = ITEM_STATE_DROP;
		
		//行動状態をリセット
		m_cpuState = CPU_STATE_NONE;

		return;
	}
	//---------------------------------------------------------------------

	//アイテムの場合の処理-------------------------------------------------
	if (_hitObject->GetObjectName() == OBJECT_ITEM)
	{
		//アイテム保存用
		CItemBase* item = nullptr;

		item = dynamic_cast<CItemBase*>(_hitObject);

		if (m_cpuState == CPU_STATE_PICK_UP_ITEM && (m_state == WAIT || m_state == WALK))
		{
			//アイテムを拾う処理
			PickUpItem();

			m_cpuState = CPU_STATE_NONE;
		}

		//コインに触れたときにエフェクトを表示する
		if (item->GetItemType() == ITEM_TYPE_COIN)
		{
			if (m_effectHndl[PlayerData::EF_HNDL_COIN_GET] != -1)
			{
				CEffekseerCtrl::Stop(m_effectHndl[PlayerData::EF_HNDL_COIN_GET]);
				m_effectHndl[PlayerData::EF_HNDL_COIN_GET] = -1;
			}

			//呼び出すエフェクトのID
			int effectId = CEffectData::GetId(EFFECT_COIN_GET);

			//プレイヤーの位置にエフェクトを呼び出す
			m_effectHndl[PlayerData::EF_HNDL_COIN_GET] = CEffekseerCtrl::Request(effectId, GetCenter(), false);
		}

		return;
	}
	//---------------------------------------------------------------------

	//弾の場合の処理-------------------------------------------------------
	if (_hitObject->GetObjectName() == OBJECT_SHOT)
	{

		CShotBase* shot = nullptr;

		shot = dynamic_cast<CShotBase*>(_hitObject);

		//自分が出した攻撃の場合処理をしない
		if (shot->GetShotName() == m_name)return;

		//ノックバックの方向
		float rot = atan2f(shot->GetPos().x - GetCenter().x,
			shot->GetPos().z - GetCenter().z);

		CCharacterBase::HitAttack(shot->GetAtk(), 90, rot);

		shot->SetActive(false);

		//呼び出すエフェクトのID
		int effectId = CEffectData::GetId(EFFECT_ATTACK);

		//エフェクトを呼び出す
		CEffekseerCtrl::Request(effectId, GetCenter(),false);

		//アイテムを落とす
		m_itemState = ITEM_STATE_DROP;

		return;
	}

	//---------------------------------------------------------------------

}

//-----------------------
//		入力処理
//-----------------------
void CCpuPlayer::InputStep(float _rotY)
{
	//相手が攻撃可能範囲にいたら攻撃する-------------------------------------------------
	if (m_cpuState == CPU_STATE_ATTACK && m_targetObject != nullptr)
	{

		if (m_targetObject->GetObjectName() == OBJECT_PLAYER)
		{
			//銃と投げるアイテムはターゲットがいたら攻撃する
			if (m_itemState == ITEM_STATE_HAVE &&
				m_targetPos != nullptr)
			{
				RequestAttack();
			}

			VECTOR vec = VSub(m_pos, m_targetObject->GetPos());

			float len = VSize(vec);

			if (len <= ATTACK_START_DISTANCE + RADIUS)
			{
				RequestAttack();
			}

		}
	}
	else
	{
		switch (m_state)
		{
		case tagState::WAIT:
		case tagState::WALK:
			m_attackNum = 0;
			break;
		}
	}

	//-----------------------------------------------------------------------------------

	//移動処理
	Move(_rotY);
}

//-----------------------
//		移動処理
//-----------------------
void CCpuPlayer::Move(float _rotY)
{
	//待機状態と移動状態以外は移動を出来ないようにする
	switch (m_state)
	{
	case tagState::WAIT:
	case tagState::WALK:
	case tagState::AIR:
		break;
	case tagState::ATTACK:
		if (m_weaponId != WEAPON_ID_AX)return;
		break;
	default:
		return;
	}

	if (m_targetObject == nullptr)return;

	//ターゲットに近すぎたら動かない
	VECTOR vec = VSub(m_pos, m_targetObject->GetPos());

	vec.y = 0.0f;

	float len = VSize(vec);

	if (len <= RADIUS)return;

	float moveSpeed = MOVE_SPEED;

	//移動ベクトル
	VECTOR speed = { 0.0f,0.0f,-MOVE_SPEED };

	VECTOR targetPos = m_targetObject->GetPos();

	float targetRotY = atan2f(m_pos.x - targetPos.x,m_pos.z - targetPos.z);

	//カメラの角度がオールゼロの時に進む速度
	VECTOR defaultDir = { speed.x,0.0f,speed.z };
	//上記を行列に変換
	MATRIX dir = CMyMath::GetTranslateMatrix(defaultDir);
	//Y軸回転行列
	MATRIX mRotY = CMyMath::GetYawMatrix(targetRotY);
	//行列の合成
	MATRIX res = CMyMath::MatMult(mRotY, dir);

	//移動をスピードに代入
	m_speed.x = res.m[0][3];
	m_speed.y = res.m[1][3];
	m_speed.z = res.m[2][3];

	if (m_state == tagState::ATTACK)return;

	//移動していたら歩きモーションに以降
	if ((speed.x != 0.0f ||
		speed.z != 0.0f) &&
		m_state != tagState::AIR)
	{
		m_state = tagState::WALK;
	}

	//移動方向を向く
	if (m_speed.x != 0 || m_speed.z != 0)
		m_rot.y = atan2f(-m_speed.x,-m_speed.z);

}

//-----------------------
//		行動を変更
//-----------------------
void CCpuPlayer::ChangeCpuState()
{
	//確率をリセット
	for (int cpuState_i = 0; cpuState_i < CPU_STATE_NUM; cpuState_i++)
	{
		m_cpuStateProbability[cpuState_i] = 0;
	}

	int playerNum = 0;
	int itemNum = 0;
	int coinNum = 0;

	//視界内にあるオブジェクトの数で確率を求める
	for (int object_i = 0; object_i < m_FOV->GetObjectBufNum(); object_i++)
	{
		CObject* object = m_FOV->GetObjectBuf(object_i);

		//自分はカウントしない
		if (this == object)continue;

		switch (object->GetObjectName())
		{
		case OBJECT_PLAYER:
			playerNum++;
			m_cpuStateProbability[CPU_STATE_ATTACK] += ADD_CPU_STATE_PROBABILITY;
			break;
		case OBJECT_ITEM:
			//アイテムを持っている状態なら持つアイテムをカウントしない
			if (m_itemState == ITEM_STATE_HAVE)
			{
				//持つアイテムか調べる
				CItemBase* item = dynamic_cast<CItemBase*>(object);
				if (item->GetItemType() == ITEM_TYPE_OBJECT)break;
			}

			CItemBase* item = dynamic_cast<CItemBase*>(object);

			if (item->GetItemType() == ITEM_TYPE_COIN)
			{
				coinNum++;
			}

			itemNum++;
			m_cpuStateProbability[CPU_STATE_PICK_UP_ITEM] += ADD_CPU_STATE_PROBABILITY;
			break;
		}
	}

	//確率の合計を求める
	int sum = 0;
	for (int cpuState_i = 0; cpuState_i < CPU_STATE_NUM; cpuState_i++)
	{
		sum += m_cpuStateProbability[cpuState_i];
	}

	if (sum == 0)return;

	//合計から乱数を求める
	int randNum = GetRand(sum);

	//乱数から行動を求める
	int stateProbability = 0;
	for (int cpuState_i = 0; cpuState_i < CPU_STATE_NUM; cpuState_i++)
	{
		stateProbability += m_cpuStateProbability[cpuState_i];

		if (randNum <= stateProbability)
		{
			m_cpuState = static_cast<tagCpuState>(cpuState_i);
			break;
		}
	}

	int targetObjectNum = 0;

	//ターゲットを決める
	switch (m_cpuState)
	{
	case CPU_STATE_ATTACK:
		targetObjectNum = GetRand(playerNum);
		playerNum = 0;
		for (int object_i = 0; object_i < m_FOV->GetObjectBufNum(); object_i++)
		{
			CObject* object = m_FOV->GetObjectBuf(object_i);

			if (this == object ||object->GetObjectName() == OBJECT_ITEM)continue;

			if (playerNum == targetObjectNum)
			{
				m_targetObject = object;
				break;
			}
			playerNum++;
		}
		break;
	case CPU_STATE_PICK_UP_ITEM:
		if (coinNum != 0)
		{
			targetObjectNum = GetRand(coinNum);
			coinNum = 0;

			for (int object_i = 0; object_i < m_FOV->GetObjectBufNum(); object_i++)
			{
				CObject* object = m_FOV->GetObjectBuf(object_i);

				if (object->GetObjectName() != OBJECT_ITEM)continue;

				CItemBase* item = dynamic_cast<CItemBase*>(object);

				if (item->GetItemType() != ITEM_TYPE_COIN)continue;

				if (coinNum == targetObjectNum)
				{
					m_targetObject = item;
					break;
				}

				coinNum++;
			}
		}
		else
		{
			targetObjectNum = GetRand(itemNum);
			itemNum = 0;
			for (int object_i = 0; object_i < m_FOV->GetObjectBufNum(); object_i++)
			{
				CObject* object = m_FOV->GetObjectBuf(object_i);

				if (object->GetObjectName() != OBJECT_ITEM)continue;

				CItemBase* item = dynamic_cast<CItemBase*>(object);

				if (itemNum == targetObjectNum)
				{
					m_targetObject = object;
					break;
				}
				itemNum++;
			}

		}
		break;
	}
}

