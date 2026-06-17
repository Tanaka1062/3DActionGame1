#include "player.h"
#include "../data.h"
#include "../../lib/myMath/myMath.h"
#include <math.h>
#include "../common.h"
#include "../../lib/input/controllerManager.h"
#include"../../lib/input/keyInput.h"
#include "playerManager.h"
#include "../../lib/effekseer/effekseer.h"
#include "../system/effectData/effectData.h"
#include "../item/itemBase.h"
#include "../system/sound/soundManager.h"

using namespace PlayerData;

//-----------------------
//	コンストラクタ
//-----------------------
CPlayer::CPlayer()
{
	m_name = PLAYER_NONE;
	CCharacterBase::Init();
	m_dropCoin = 0;
	m_pos = V_ZERO;
	m_rad = 0.0f;
	m_maxHp = 0;
	m_hp = 0;
	m_atk = 0;
	m_isJump = false;
	m_attackNum = ATTACK_NONE;
	m_money = INIT_MONEY;
	m_attackId = -1;
	for (int effectHndl_i = 0; effectHndl_i < PlayerData::EF_HNDL_NUM; effectHndl_i++)
	{
		m_effectHndl[effectHndl_i] = -1;
	}
	m_padName = PAD_NONE;
	m_weaponId = WEAPON_ID_HAND;
	m_weaponDurability = 0;
	m_itemState = ITEM_STATE_NONE;
	m_targetPos = nullptr;
	m_isCpu = false;
	m_getUpTime = 0;
}

//-----------------------
//	デストラクタ
//-----------------------
CPlayer::~CPlayer()
{
	Exit();
}

//-----------------------
//		初期化
//-----------------------
void CPlayer::Init(tagPlayerName _name, tagPadName _padName)
{
	CCharacterBase::Init();

	m_dropCoin = 0;
	m_pos = V_ZERO;
	m_rad = RADIUS;
	m_maxHp = MAX_HP;
	m_hp = m_maxHp;
	m_atk = ATK;
	m_attackNum = ATTACK_NONE;
	m_weaponDurability = 0;
	m_money = INIT_MONEY;
	m_padName = _padName;
	m_weaponId = WEAPON_ID_HAND;
	m_name = _name;
	m_shadow.Init(m_pos, SHADOW_SIZE);
	m_objectName = OBJECT_PLAYER;
	m_isCpu = false;
	m_getUpTime = 0;
}

//-----------------------
//	モデルロード
//-----------------------
void CPlayer::Load(int _modelHndl)
{
	CObject::DuplicateModel(_modelHndl);
	m_shadow.Load();
}

//-----------------------
//毎フレームする処理
//-----------------------
void CPlayer::Step(float _rotY, VECTOR* _targetPos, CAttackManager* _attackManager, CShotManager* _shotManager)
{
	m_targetPos = _targetPos;

	//ジャンプの上昇処理
	if (m_isJump == true)
	{
		m_isJump = false;
		m_gravity = JUMP_SPEED;
		m_isFlying = true;
	}

	if (m_targetPos != nullptr && m_isFlying == false)
	{
		switch (m_state)
		{
		case tagState::BLOW_AWAY:
		case tagState::DOWN:
		case tagState::DOWN_IN:
		case tagState::GET_UP:
		case tagState::DIE:
			break;
		default:
			//プレイヤー同士の距離
			VECTOR vLen = VSub(m_pos, *m_targetPos);
			float fLen = VSize(vLen);

			//戦いの距離になったら互いの方向を向く
			if (fLen <= FIGHT_LEN)
			{
				float rotY1 = atan2f(m_pos.x - m_targetPos->x, m_pos.z - m_targetPos->z);

				m_rot.y = rotY1;
			}

			//プレイヤーの向きを変える
			if (m_state == ITEM_THROW_IN)
			{
				float rotY = atan2f(m_pos.x - m_targetPos->x, m_pos.z - m_targetPos->z);

				m_rot.y = rotY;
			}
			break;
		}
	}

	//丸影とプレイヤーの座標が離れていたら飛んでいる
	if (m_pos.y - m_shadow.GetPos().y > FLYING_HEIGHT_THRESHOLD)
	{
		m_isFlying = true;
	}

	//空中にいたら状態を空中に変える
	if (m_isFlying == true)
	{
		switch (m_state)
		{
		case tagState::ATTACK_IN:
		case tagState::ATTACK:
		case tagState::ATTACK_OUT:
		case tagState::BLOW_AWAY:
		case tagState::DIE:
			break;
		default:
			m_state = tagState::AIR;
			break;
		}
	}

	//指定した高度よりしたに落ちたら死んで復活する
	if (m_pos.y <= DIE_POS_Y)
	{
		m_isActive = false;
	}

	//武器の耐久度処理--------------------------------
	//素手以外の場合耐久度が0以下になったら武器が壊れる
	if (m_weaponId != WEAPON_ID_HAND)
	{
		if (m_weaponDurability <= 0)
		{
			m_weaponId = WEAPON_ID_HAND;
			m_weaponDurability = 0;
		}
	}

	//------------------------------------------------
		//アイテムを手に入れていたら持ち上げる
	if (m_itemState == ITEM_STATE_GET)
	{
		m_itemState = ITEM_STATE_HAVE;
		m_state = ITEM_LIFT_UP;
	}

	//アイテムを取ろうとしていたら持っていない状態に戻す
	if (m_itemState == ITEM_STATE_PICK_UP)
	{
		m_itemState = ITEM_STATE_NONE;
	}

	CCharacterBase::Step(_attackManager, _shotManager);

	//体力が増えすぎないように
	if (m_hp >= m_maxHp)
	{
		m_hp = m_maxHp;
	}

	//コインが最大数を超えないように
	if (m_money >= MONEY_MAX)
	{
		m_money = MONEY_MAX;
	}

	//攻撃の当たり判定が消えたら攻撃のIDを初期化する
	if (_attackManager->GetActive(m_attackId) == false)
	{
		m_attackId = -1;
	}
	//攻撃中は当たり判定をプレイヤーの位置に設定する
	else
	{
		_attackManager->SetPos(m_attackId, m_pos);
	}

	//攻撃中ではない場合攻撃を消す
	if (m_state != tagState::ATTACK)
	{
		_attackManager->SetActive(m_attackId, false);
	}

	//エフェクトをプレイヤーに追従させる
	for (int effectHndl_i = 0; effectHndl_i < PlayerData::EF_HNDL_NUM; effectHndl_i++)
	{
		if (m_effectHndl[effectHndl_i] != -1)
		{
			CEffekseerCtrl::SetPosition(m_effectHndl[effectHndl_i], GetCenter());
			CEffekseerCtrl::SetRot(m_effectHndl[effectHndl_i], m_rot);
			if (CEffekseerCtrl::IsActive(m_effectHndl[effectHndl_i]) == false)
			{
				m_effectHndl[effectHndl_i] = -1;
			}
		}
	}

	//入力処理
	InputStep(_rotY);

}

//-----------------------
//		描写処理
//-----------------------
void CPlayer::Draw()
{
	CCharacterBase::Draw();

#ifdef DEBUG
	//当たり判定を表示
	DrawSphere3D(GetCenter(), m_rad, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

	VECTOR attackPos;
	attackPos.x = -sinf(m_rot.y) * ATTACK_LENGTH[m_weaponId][m_attackId];
	attackPos.z = -cosf(m_rot.y) * ATTACK_LENGTH[m_weaponId][m_attackId];

	attackPos = VAdd(attackPos, m_pos);
	float attackSize = ATTACK_SIZE[m_weaponId][m_attackNum];

	attackPos.y = m_pos.y + attackSize * 0.5f;

	DrawSphere3D(attackPos, attackSize, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);

#endif // DEBUG

}

//-----------------------
//		更新処理
//-----------------------
void CPlayer::Update()
{
	CCharacterBase::Update();

	//速度のリセット
	ResetSpeed();

}

//-----------------------
//		 終了処理
//-----------------------
void CPlayer::Exit()
{
	CCharacterBase::Exit();
}

//-----------------------
//		 復活処理
//-----------------------
void CPlayer::Respawn(VECTOR _respawnPos)
{
	m_pos = _respawnPos;
	m_isActive = true;
	switch (m_state)
	{
	//死んでいた場合
	case tagState::DIE:
		m_hp = m_maxHp;
		m_weaponId = WEAPON_ID_HAND;
		m_weaponDurability = 0;
		m_state = tagState::WAIT;
		break;
	//死んでいない場合
	default:
		m_state = tagState::WAIT;
		m_hp -= static_cast<int>(m_maxHp * FALL_OUT_DAMAGER_RATE);
		break;
	}
}

//-----------------------
//	当たり判定後の処理
//-----------------------
void CPlayer::HitCalc(CObject* _hitObject)
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

		//攻撃が命中したことを設定する
		attack->SetIsHit(true);

		//ノックバックの方向
		float rot = atan2f(attack->GetPos().x - GetCenter().x,
			attack->GetPos().z - GetCenter().z);

		HitAttack(attack->GetAtk(),attack->GetBlown(), rot);

		//呼び出すエフェクトのID
		int effectId = CEffectData::GetId(EFFECT_ATTACK);

		//エフェクトを呼び出す
		CEffekseerCtrl::Request(effectId, GetCenter(), false);

		//アイテムを落とす
		m_itemState = ITEM_STATE_DROP;

	}
	//---------------------------------------------------------------------

	//アイテムの場合の処理-------------------------------------------------
	if (_hitObject->GetObjectName() == OBJECT_ITEM)
	{
		//アイテム保存用
		CItemBase* item = nullptr;

		item = dynamic_cast<CItemBase*>(_hitObject);

		//アイテムがコインタイプ以外の場合処理をしない
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

	}

	//---------------------------------------------------------------------

}

//------------------------------
//	攻撃を食らった時にする処理
//------------------------------
void CPlayer::HitAttack(int _atk, int _blown, float _rotY)
{
	//死亡していたら処理をしない
	if (m_state == DIE)return;

	CSoundManager::Play(CSoundManager::SE_HIT, DX_PLAYTYPE_BACK);

	m_blown += _blown;

	VECTOR knockBack = KNOCK_BACK_SPEED;

	if (m_blown >= BLOWN_MAX || m_state == AIR)
	{
		knockBack = VScale(knockBack, 10.0f);
		m_blown = 0;
		
		//コインを落とす量を求める
		m_dropCoin = static_cast<int>(m_money * MONEY_DROP_RATE);

		//落としたコイン量だけお金を減らす
		m_money -= m_dropCoin;

		//吹き飛ばされ状態
		m_state = BLOW_AWAY;
	}
	else
	{
		//斧の攻撃中に怯んだら音を止める
		if (m_weaponId == WEAPON_ID_AX &&
			m_state == tagState::ATTACK)
		{
			if (CSoundManager::IsPlay(CSoundManager::SE_AX) == true)
			{
				CSoundManager::Stop(CSoundManager::SE_AX);
			}
		}

		//怯み状態にする
		m_state = STAGGER;
	}

	//既に怯み状態なら処理をしない
	if (m_state == STAGGER)return;

	//ノックバックの速度を設定------------

	//プレイヤーが目の前にいる時に進む速度
	VECTOR defaultDir = knockBack;
	//上記を行列に変換
	MATRIX dir = CMyMath::GetTranslateMatrix(defaultDir);
	//Y軸回転行列
	MATRIX mRotY = CMyMath::GetYawMatrix(_rotY);
	//行列の合成
	MATRIX res = CMyMath::MatMult(mRotY, dir);

	//移動をスピードに代入
	m_speed.x = res.m[0][3];
	m_speed.y = res.m[1][3];
	m_speed.z = res.m[2][3];

	//------------------------------------

	//Hpを攻撃力分減らす
	m_hp -= _atk;
}

//-----------------------
//	   重力リセット
//-----------------------
void CPlayer::GravityReset()
{
	CObject::GravityReset();

	if (m_state == AIR)
	{
		m_state = LANDING;
	}
}

//-----------------------
//	   お金を減らす
//-----------------------
bool CPlayer::SubMoney(int _subMoney)
{
	//消費量が今のお金より少なかったら購入しない
	if (m_money < _subMoney)
	{
		return false;
	}

	m_money -= _subMoney;

	return true;
}

//-----------------------
//		入力処理
//-----------------------
void CPlayer::InputStep(float _rotY)
{
	//攻撃の呼び出し
	if ((CheckHitKey(KEY_INPUT_J) != 0 ||
		CControllerManager::IsTrg(BUTTON_X, m_padName)) &&
		m_attackId == -1)
	{
		RequestAttack();
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

	//移動処理
	Move(MoveInput(_rotY));

	if ((CControllerManager::IsTrg(BUTTON_A, m_padName) && !m_isFlying) ||
		(CheckHitKey(KEY_INPUT_SPACE) && !m_isFlying))
	{
		//ジャンプ処理
		RequestJump();
	}

	if (CheckHitKey(KEY_INPUT_I) != 0 ||
		CControllerManager::IsTrg(BUTTON_B, m_padName) == true)
	{
		//アイテムを拾う処理
		PickUpItem();
	}


}

//-----------------------
//		待機処理
//-----------------------
void CPlayer::Wait()
{
	//アイテムを持っている場合待機のモーションが変わる
	if (m_itemState == ITEM_STATE_HAVE)
	{
		//物を持ち上げた状態の待機アニメーションを再生
		RequestAnim(ANIMID_WAIT_LIFTING_UP, 0.5f, true);
	}
	else
	{
		//待機アニメーションを再生
		RequestAnim(ANIMID_WAIT, 0.5f, true);
	}
	
}

//-----------------------
//		歩く処理
//-----------------------
void CPlayer::Walk()
{
	//アイテムを持っている場合歩きのモーションが変わる
	if (m_itemState == ITEM_STATE_HAVE)
	{
		//物を持ち上げた状態の歩くアニメーション
		RequestAnim(ANIMID_WALK_LIFTING_UP, 1.0f, true);
	}
	else
	{
		//歩くアニメーション
		RequestAnim(ANIMID_WALK, 1.0f, true);
	}


	//止まっていたら待機状態に移行
	if (m_speed.x == 0.0f &&
		m_speed.z == 0.0f)
	{
		m_state = WAIT;
	}

}

//-----------------------
//		ジャンプ
//-----------------------
void CPlayer::Jump()
{
	RequestAnim(ANIMID_JUMP, JUMP_ANIM_SPEED);

	if (GetAnimEnd() == true)
	{
		m_isJump = true;
		m_state = AIR;
	}
}

//-----------------------
//			空中
//-----------------------
void CPlayer::Air()
{
	RequestAnim(ANIMID_AIR, 1.0f, true);

	if (m_isFlying == false)
	{
		m_state = WAIT;
	}
}

//-----------------------
//			着地
//-----------------------
void CPlayer::Landing()
{
	RequestAnim(ANIMID_LANDING, LANDING_ANIM_SPEED);

	if (GetAnimEnd() == true)
	{
		m_isJump = false;

		m_state = WAIT;
	}
}

//-----------------------
//		攻撃前
//-----------------------
void CPlayer::AttackIn()
{
	if (m_isFlying == true)
	{
		m_attackNum = ATTACK_AIR;
	}

	switch (m_weaponId)
	{
	//武器が素手の場合
	case WEAPON_ID_HAND:
		switch (m_attackNum)
		{
		case tagAttackNum::ATTACK:
			//攻撃前のアニメーション
			if (RequestAnim(ANIMID_ATTACK_HAND_IN, 0.7f) == true)
			{
				int effectId = CEffectData::GetId(EFFECT_HAND);

				m_effectHndl[PlayerData::EF_HNDL_ATTACK] = CEffekseerCtrl::Request(effectId, m_pos, false);
				CEffekseerCtrl::SetRot(m_effectHndl[PlayerData::EF_HNDL_ATTACK],m_rot);
			}

			break;
		case tagAttackNum::ATTACK_AIR:
			//空中の攻撃前アニメーション
			RequestAnim(ANIMID_AIR_ATTACK_HAND_IN, 1.0f);
			break;
		}

		break;
	//武器がハンマーの場合
	case WEAPON_ID_HAMMER:
		switch (m_attackNum)
		{
		case tagAttackNum::ATTACK:
			//攻撃前のアニメーション
			RequestAnim(ANIMID_ATTACK_HAMMER_IN, 0.6f);
			break;
		case tagAttackNum::ATTACK_AIR:
			if (m_animData.m_id != ANIMID_AIR_ATTACK_HAMMER_IN)
			{
				float len = m_pos.y - m_shadow.GetPos().y;
				if (HAMMER_FALL_MIN_LENGTH >= len)
				{
					m_state = WAIT;
					return;
				}
			}
			//空中の攻撃前アニメーション
			RequestAnim(ANIMID_AIR_ATTACK_HAMMER_IN, 0.7f);
			if (m_animData.m_frame >= HAMMER_FALL_FRAME)
			{
				m_gravity = -HAMMER_ATTACK_AIR_FALL_SPEED;
			}
			else
			{
				m_gravity = 0;
			}
			break;
		}

		break;
	//武器が斧の場合
	case WEAPON_ID_AX:
		m_attackNum = 0;
		//攻撃前のアニメーション
		RequestAnim(ANIMID_ATTACK_AX_IN, 0.5f);
		break;
	}

	//ハンマーの空中攻撃は着地するまで続く
	if (m_weaponId == WEAPON_ID_HAMMER &&
		m_attackNum == ATTACK_AIR)
	{
		if (m_isFlying == false)
		{
			m_state = tagState::ATTACK;
		}
		return;
	}

	//アニメーションが終わったら攻撃中に移行
	if (GetAnimEnd() == true)
	{
		m_state = tagState::ATTACK;
	}

}

//-----------------------
//		攻撃中
//-----------------------
void CPlayer::Attack(CAttackManager* _attackManager, CShotManager* _shotManager)
{
	//攻撃の座標
	VECTOR attackPos;
	attackPos.x = -sinf(m_rot.y) * ATTACK_LENGTH[m_weaponId][m_attackId];
	attackPos.z = -cosf(m_rot.y) * ATTACK_LENGTH[m_weaponId][m_attackId];

	attackPos = VAdd(attackPos, m_pos);

	attackPos.y = m_pos.y;

	//攻撃力を計算
	int atk = static_cast<int>(m_atk * ATTACK_MAGNIFICATION[m_weaponId][m_attackNum]);

	int blown = ATTACK_BLOWN[m_weaponId][m_attackNum];

	float attackSize = ATTACK_SIZE[m_weaponId][m_attackNum];

	switch (m_weaponId)
	{
	//武器が素手の場合
	case WEAPON_ID_HAND:
		CSoundManager::Play(CSoundManager::SE_HAND, DX_PLAYTYPE_BACK);

		switch (m_attackNum)
		{
		case tagAttackNum::ATTACK:
			//攻撃中のアニメーション
			if (RequestAnim(ANIMID_ATTACK_HAND, 1.0f) == true)
			{
				_attackManager->Request(attackPos, attackSize, atk, blown, m_name);
			}
			break;
		case ATTACK_AIR:
			//空中の攻撃中アニメーション
			if (RequestAnim(ANIMID_AIR_ATTACK_HAND, 1.2f) == true)
			{
				_attackManager->Request(attackPos, attackSize, atk, blown, m_name);
			}
			break;
		}

		break;
	//武器がハンマーの場合
	case WEAPON_ID_HAMMER:
		CSoundManager::Play(CSoundManager::SE_HAMMER, DX_PLAYTYPE_BACK);

		switch (m_attackNum)
		{
		case tagAttackNum::ATTACK:
			//攻撃中のアニメーション
			RequestAnim(ANIMID_ATTACK_HAMMER, 0.6f);
			break;
		case tagAttackNum::ATTACK_AIR:
			//空中の攻撃中アニメーション
			if (RequestAnim(ANIMID_AIR_ATTACK_HAMMER, 0.6f) == true)
			{
				_attackManager->Request(attackPos, attackSize, atk, blown, m_name);
				
				int effectId = CEffectData::GetId(EFFECT_SHOCK_WAVE);
				
				CEffekseerCtrl::Request(effectId, attackPos, false);
			};
			break;
		}
		break;
	//武器が斧の場合
	case WEAPON_ID_AX:
		if (CSoundManager::IsPlay(CSoundManager::SE_AX) == false)
		{
			CSoundManager::Play(CSoundManager::SE_AX, DX_PLAYTYPE_LOOP);
		}
		//攻撃中のアニメーション
		if (RequestAnim(ANIMID_ATTACK_AX, 1.0f,true) == true)
		{
			m_attackId = _attackManager->Request(attackPos, attackSize, atk, blown, m_name, AX_ATTACK_NUM, AX_ATTACK_TIME);
		}
		break;
	}

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true || _attackManager->GetActive(m_attackId) == false)
	{
		//武器の耐久度が減る
		if (m_weaponId != WEAPON_ID_HAND)
		{
			m_weaponDurability--;
		}

		m_state = ATTACK_OUT;
	}

}

//-----------------------
//		攻撃後
//-----------------------
void CPlayer::AttackOut()
{
	switch (m_weaponId)
	{
	//武器が素手の場合
	case WEAPON_ID_HAND:
		switch (m_attackNum)
		{
		case tagAttackNum::ATTACK:
			//攻撃後のアニメーション
			RequestAnim(ANIMID_ATTACK_HAND_OUT, 0.5f);
			break;
		case tagAttackNum::ATTACK_AIR:
			//空中の攻撃後アニメーション
			RequestAnim(ANIMID_AIR_ATTACK_HAND_OUT, 1.2f);
			break;
		}
	
		break;
	//武器がハンマーの場合
	case WEAPON_ID_HAMMER:
		switch (m_attackNum)
		{
		case tagAttackNum::ATTACK:
			//攻撃後のアニメーション
			RequestAnim(ANIMID_ATTACK_HAMMER_OUT, 0.6f,true);

			if (m_animData.m_id == ANIMID_ATTACK_HAMMER_OUT)
			{
				float len = m_pos.y - m_shadow.GetPos().y;
				if (HAMMER_FALL_MIN_LENGTH <= len)
				{
					m_state = ATTACK_IN;
					m_attackNum = ATTACK_NONE;
				}
				m_isJump = true;
			}

			break;
		case tagAttackNum::ATTACK_AIR:
			//空中の攻撃後アニメーション
			RequestAnim(ANIMID_AIR_ATTACK_HAMMER_OUT, 0.6f);
			break;
		}
	
		break;
	//武器が斧の場合
	case WEAPON_ID_AX:
		//攻撃後のアニメーション
		RequestAnim(ANIMID_ATTACK_AX_OUT, 0.5f);
		CSoundManager::Stop(CSoundManager::SE_AX);
		break;
	}

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
		m_attackNum = ATTACK_NONE;
		m_state = WAIT;
	}

}

//-----------------------
//	アイテムを持ち上げる
//-----------------------
void CPlayer::ItemLiftUp()
{
	//アイテムを持ち上げるアニメーション
	RequestAnim(ANIMID_LIFT_UP, 1.0f);

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
		m_state = WAIT;
	}
}

//-----------------------
//	 アイテムを下ろす
//-----------------------
void CPlayer::ItemPutDown()
{
	//アイテムを下ろすアニメーション
	RequestAnim(ANIMID_PUT_DOWN, 1.0f);

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
		m_itemState = ITEM_STATE_NONE;
		m_state = WAIT;
	}

}

//-----------------------
//  アイテムを投げる前
//-----------------------
void CPlayer::ItemThrowIn()
{
	//アイテムを投げる前のアニメーション
	RequestAnim(ANIMID_THROW_IN, 1.0f);

	//アニメーションが終わったらアイテムを投げている状態にする
	if (GetAnimEnd() == true)
	{
		m_state = ITEM_THROW;
	}

}

//-----------------------
//    アイテムを投げる
//-----------------------
void CPlayer::ItemThrow()
{
	//アイテムを投げるアニメーション
	RequestAnim(ANIMID_THROW, 1.0f);

	//アニメーションが終わったらアイテムを投げた後状態にする
	if (GetAnimEnd() == true)
	{
		m_itemState = ITEM_STATE_THROW;
		m_state = ITEM_THROW_OUT;
	}

}

//-----------------------
//  アイテムを投げた後
//-----------------------
void CPlayer::ItemThrowOut()
{
	//アイテムを投げた後のアニメーション
	RequestAnim(ANIMID_THROW_OUT, 1.0f);

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
		m_itemState = ITEM_STATE_NONE;
		m_state = WAIT;
	}

}

//-----------------------
//		怯み
//-----------------------
void CPlayer::Stagger()
{
	//被弾のアニメーション
	RequestAnim(ANIMID_HIT, 1.4f);

	//被弾のアニメーションが終わったら戻す
	if (GetAnimEnd() == true)
	{
		m_state = WAIT;
	}
}

//-----------------------
//		吹き飛んだ
//-----------------------
void CPlayer::BlowAway()
{
	//吹き飛んだアニメーション
	RequestAnim(ANIMID_BLOW_AWAY, 1.0f);

	//移動している反対方向を向く
	if (m_speed.x != 0 || m_speed.z != 0)
		m_rot.y = atan2f(m_speed.x, m_speed.z);

	//着地したらダウン状態に移行する
	if(GetAnimEnd() == true &&
		m_isFlying == false)
	{
		m_state = DOWN;
	}
}

//-----------------------
//		 ダウン前
//-----------------------
void CPlayer::DownIn()
{
	//ダウン前のアニメーション
	RequestAnim(ANIMID_DOWN_IN, 1.0f);

	if (GetAnimEnd() == true)
	{
		m_state = DOWN;
	}
}

//-----------------------
//		  ダウン
//-----------------------
void CPlayer::Down()
{
	//ダウンのアニメーション
	RequestAnim(ANIMID_DOWN, 1.0f, true);

	m_getUpTime++;

	//移動の入力をされたら起き上がりに移行する
	if ((CControllerManager::GetLX(m_padName) != 0.0f ||
		CControllerManager::GetLY(m_padName) != 0.0f) ||
		m_getUpTime >= GET_UP_MAX_TIME)
	{
		m_getUpTime = 0;
		m_state = GET_UP;
	}
}

//-----------------------
//		起き上がり
//-----------------------
void CPlayer::GetUp()
{
	//起き上がりのアニメーション
	RequestAnim(ANIMID_GET_UP,0.8f);

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
		m_state = WAIT;
	}
}

//-----------------------
//		死亡
//-----------------------
void CPlayer::Die()
{
	//死亡のアニメーション
	if (RequestAnim(ANIMID_DIE, 0.5f) == true)
	{
		m_dropCoin = static_cast<int>(m_money * MONEY_RESPAWN_RATE);
		m_money -= m_dropCoin;
	}

	//死亡アニメーションが終わったら消える
	if (GetAnimEnd() == true)
	{
		m_isActive = false;
	}
}

//-----------------------
//		  準備完了
//-----------------------
void CPlayer::Ready()
{
	//準備完了のアニメーション
	RequestAnim(ANIMID_READY, 1.0f);
}

//-----------------------
//	  準備完了を解除
//-----------------------
void CPlayer::ReadyOut()
{
	//準備完了をやめるアニメーション
	RequestAnim(ANIMID_READY_OUT, 1.0f);

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
		m_state = WAIT;
	}
}

//-----------------------
//		 移動入力
//-----------------------
VECTOR CPlayer::MoveInput(float _rotY)
{
	//コントローラーを使っているか
	bool isController = false;

	if (CControllerManager::GetLY(m_padName) != 0.0f ||
		CControllerManager::GetLX(m_padName) != 0.0f)
	{
		isController = true;
	}

	float moveSpeed = MOVE_SPEED;

	VECTOR speed = V_ZERO;
	//コントローラー用前進後退
	if (isController == true)
	{
		speed.z = CControllerManager::GetLY(m_padName) * moveSpeed;
	}
	//キーボード用前進
	else if (CheckHitKey(KEY_INPUT_W) != 0)
	{
		speed.z = -moveSpeed;
	}
	//キーボード用後退
	else if (CheckHitKey(KEY_INPUT_S) != 0)
	{
		speed.z = moveSpeed;
	}

	//左右にどれだけ移動するか
	//コントローラー用左右移動
	if (isController == true)
	{
		speed.x = -CControllerManager::GetLX(m_padName) * moveSpeed;
	}
	//キーボード用左移動
	else if (CheckHitKey(KEY_INPUT_A) != 0)
	{
		speed.x = moveSpeed;
	}
	//キーボード用右移動
	else if (CheckHitKey(KEY_INPUT_D) != 0)
	{
		speed.x = -moveSpeed;
	}

	////カメラの角度がオールゼロの時に進む速度
	VECTOR defaultDir = { speed.x,0.0f,speed.z };
	//上記を行列に変換
	MATRIX dir = CMyMath::GetTranslateMatrix(defaultDir);
	//Y軸回転行列
	MATRIX mRotY = CMyMath::GetYawMatrix(_rotY);
	//行列の合成
	MATRIX res = CMyMath::MatMult(mRotY, dir);

	//行列をVECTORに代入
	VECTOR move = V_ZERO;
	move.x = res.m[0][3];
	move.y = res.m[1][3];
	move.z = res.m[2][3];

	return move;
}

//-----------------------
//		移動処理
//-----------------------
void CPlayer::Move(VECTOR _move)
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

	//移動をスピードに代入
	m_speed = _move;

	if (m_state == tagState::ATTACK)return;

	//移動していたら歩きモーションに以降
	if ((m_speed.x != 0.0f ||
		m_speed.z != 0.0f) &&
		m_state != AIR)
	{
		m_state = WALK;
	}

	//移動方向を向く
	if (m_speed.x != 0 || m_speed.z != 0)
		m_rot.y = atan2f(-m_speed.x,-m_speed.z);

}

//-----------------------
//攻撃を呼び出す処理
//-----------------------
void CPlayer::RequestAttack()
{

	switch (m_state)
	{
	case tagState::AIR:
	case tagState::WAIT:
	case tagState::WALK:
	case tagState::ATTACK_OUT:
		break;
	default:
		return;
	}

	//アイテムを持ち上げている状態ではアイテムを投げる
	if (m_itemState == ITEM_STATE_HAVE)
	{
		//攻撃ボタンを押したら投げる
		m_state = tagState::ITEM_THROW_IN;

		return;
	}

	//攻撃してない時に攻撃前に移行する
	m_state = tagState::ATTACK_IN;
}

//-----------------------
//ジャンプの呼び出し処理
//-----------------------
void CPlayer::RequestJump()
{
	switch (m_state)
	{
	case tagState::WAIT:
	case tagState::WALK:
		break;
	default:
		return;
	}

	m_state = tagState::JUMP;
}

//-----------------------
//	  アイテムを拾う
//-----------------------
void CPlayer::PickUpItem()
{
	//空中いるときは攻撃を出せない
	if (m_isFlying == true)return;

	switch (m_state)
	{
	case tagState::WAIT:
	case tagState::WALK:
		break;
	default:
		return;
	}

	//アイテムを取得・下ろす

	//アイテムをすでに持っている場合はアイテムを下ろす
	if (m_itemState == ITEM_STATE_HAVE)
	{
		m_state = tagState::ITEM_PUT_DOWN;
		m_itemState = ITEM_STATE_PUT_DOWN;
	}
	//アイテムを持っていない場合アイテムを取得する
	else
	{
		m_itemState = ITEM_STATE_PICK_UP;
	}

}

//-----------------------
//持っているアイテムの座標を取得
//-----------------------
VECTOR CPlayer::GetItemHavePos()
{
	VECTOR itemPos = MV1GetFramePosition(m_hndl, 18);

	return itemPos;
}

