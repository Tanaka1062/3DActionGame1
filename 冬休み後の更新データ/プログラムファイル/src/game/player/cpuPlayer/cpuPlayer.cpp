#include "cpuPlayer.h"
#include "../../data.h"
#include "../../lib/myMath/myMath.h"
#include <math.h>
#include "../../common.h"
#include "../../lib/input/controllerManager.h"
#include"../../lib/input/keyInput.h"
#include "../playerManager.h"
#include "../../lib/effekseer/effekseer.h"
#include "../../system/effectData/effectData.h"
#include "../../item/itemBase.h"

//定義関連---------------------------

//プレイヤー関連--------------------------------
static const char MODEL_PATH[] =
 "data/model/player/playerTransformTest.mv1" ;			//ロードするファイル名
constexpr VECTOR INIT_POS = { 0.0f,1.0f,0.0f };			//初期座標
constexpr float SHADOW_SIZE = 0.5f;						//丸影の大きさ
constexpr int MAX_HP = 200;								//体力
constexpr int ATK = 20;									//攻撃力
constexpr float MOVE_SPEED = 1.2f;						//移動スピード
constexpr float RADIUS = 10.0f;							//半径
constexpr float DODGEROLL_SPEED = 1.5f;					//回避スピード
constexpr float JUMP_SPEED = 3.0f;						//ジャンプスピード
constexpr int TRANSFORM_COIN_NUM = 3;					//変身に必要なコインの数
constexpr int POWER_UP_ATK = 1;							//増加する攻撃力
constexpr float TRANSFORM_UP_SPEED = 0.3f;				//変身後のスピードアップ
constexpr int BLOWN_MAX = 100;							//吹き飛び最大値
static const VECTOR KNOCK_BACK_SPEED = { 0.0f,3.0f,-0.8f };	//吹き飛ぶスピード
constexpr int INIT_MONEY = 3;							//最初の所持金
constexpr float MONEY_DROP_RATE = 0.4f;					//落とすお金の割合
constexpr float MONEY_RESPAWN_RATE = 0.5f;				//復活するときに消費するお金の割合
constexpr float DIE_POS_Y = -100.0f;					//死ぬ高さ
constexpr float FALL_OUT_DAMAGER_RATE = 0.3f;			//ステージから落下したときの割合ダメージ
//----------------------------------------------

//攻撃関連---------------------------
constexpr float ATTACK_LENGTH = 15.0f;				//攻撃の長さ
constexpr int ATTACKB_ATK = 100;					//攻撃Bの攻撃力
constexpr float ATTACK_MOVE_SPEED = 0.5f;			//攻撃時に前進する力
constexpr float FIGHT_LEN = 40.0f;					//戦う距離
constexpr float SHOT_SIZE = 10.0f;					//弾の大きさ
constexpr float SHOT_SPEED = 2.5f;					//弾の速度
constexpr int SHOT_LOST_TIME = 2 * 60;				//弾が消えるまでの時間
//-----------------------------------

constexpr int ADD_CPU_STATE_PROBABILITY = 10;		//行動状態の上昇確率
constexpr int CPU_STATE_CHANGE_TIME = 3 * 60;		//行動が変わるまでの時間

enum tagAttackNum
{
	ATTACK_NONE = -1,	//攻撃をしていない
	ATTACK_1,			//一段階目の攻撃
	ATTACK_2,			//二段階目の攻撃
	ATTACK_3,			//三段階目の攻撃

	ATTACK_NUM,			//攻撃の数
};

static const float ATTACK_MAGNIFICATION[WEAPON_ID_NUM][ATTACK_NUM] =	//攻撃の倍率
{
	{0.5f,0.8f,1.0f},
	{0.7f,1.0f,1.2f},
	{1.0f,1.2f,1.5f},
	{1.0f,1.0f,1.0f},
};

static const int ATTACK_BLOWN[WEAPON_ID_NUM][ATTACK_NUM] =				//攻撃の吹き飛び度
{
	{40,40,80},
	{40,40,80},
	{40,50,80},
	{60,60,80},
};

static const float ATTACK_SIZE[WEAPON_ID_NUM][ATTACK_NUM] =
{
	{12.0f,12.0f,12.0f},
	{16.0f,16.0f,20.0f},
	{24.0f,24.0f,26.0f},
	{16.0f,16.0f,16.0f},
};

//---------------------------------------------------------

//-----------------------
//	コンストラクタ
//-----------------------
CCpuPlayer::CCpuPlayer()
{
	m_transformTimeCount = 0;
	m_name = PLAYER_NONE;
	CCharacterBase::Init();
	for (int keepHndl_i = 0; keepHndl_i < HNDL_NUM; keepHndl_i++)
	{
		m_keepHndl[keepHndl_i] = -1;
	}
	m_dropCoin = 0;
	m_pos = ZERO;
	m_rad = 0.0f;
	m_maxHp = 0;
	m_hp = 0;
	m_atk = 0;
	m_isDodgeroll = false;
	m_isTransform = false;
	m_isJump = false;
	m_attackNum = ATTACK_NONE;
	m_money = INIT_MONEY;
	m_dodgerollRotY = 0.0f;
	m_padName = PAD_NONE;
	m_weaponId = WEAPON_ID_HAND;
	m_weaponDurability = 0;
	m_itemState = ITEM_STATE_NONE;
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
//	デストラクタ
//-----------------------
CCpuPlayer::~CCpuPlayer()
{
	Exit();
}

//-----------------------
//		初期化
//-----------------------
void CCpuPlayer::Init(tagPlayerName _name, tagPadName _padName)
{
	CCharacterBase::Init();

	m_transformTimeCount = TRANSFORM_TIME;
	for (int keepHndl_i = 0; keepHndl_i < HNDL_NUM; keepHndl_i++)
	{
		m_keepHndl[keepHndl_i] = -1;
	}
	m_dropCoin = 0;
	m_pos = ZERO;
	m_rad = RADIUS;
	m_maxHp = MAX_HP;
	m_hp = m_maxHp;
	m_atk = ATK;
	m_isDodgeroll = false;
	m_isTransform = false;
	m_attackNum = ATTACK_NONE;
	m_weaponDurability = 0;
	m_money = INIT_MONEY;
	m_padName = _padName;
	m_dodgerollRotY = 0.0f;
	m_weaponId = WEAPON_ID_HAND;
	m_name = _name;
	m_shadow.Init(m_pos, SHADOW_SIZE);
	m_objectTypy = OBJECT_PLAYER;
	m_CoinNowUi.Init();
	m_FOV->Init();
	m_cpuState = CPU_STATE_NONE;
	m_targetObject = nullptr;
	m_isCpu = true;
	m_changeTime = 0;

}

//-----------------------
//	モデルロード
//-----------------------
void CCpuPlayer::Load(int _modelHndl)
{
	CObject::DuplicateModel(_modelHndl);
	m_keepHndl[NORMAL_HNDL] = m_hndl;
	m_keepHndl[TRANSFORM_HNDL] = MV1LoadModel(MODEL_PATH);
	m_shadow.Load();
	m_CoinNowUi.Load();
}

//-----------------------
//毎フレームする処理
//-----------------------
void CCpuPlayer::Step(float _rotY, VECTOR* _targetPos, CAttackManager* _attackManager, CShotManager* _shotManager)
{
	m_CoinNowUi.Step(m_pos,m_rad,m_money, UI_TYPE_COIN);

	m_targetPos = _targetPos;

	m_FOV->SetPos(m_pos);

	m_FOV->Step(this);

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

	//相手が攻撃可能範囲にいたら攻撃する-------------------------------------------------
	if (m_cpuState == CPU_STATE_ATTACK && m_targetObject != nullptr)
	{

		if (m_targetObject->GetObjectType() == OBJECT_PLAYER)
		{
			//銃と投げるアイテムはターゲットがいたら攻撃する
			if ((m_itemState == ITEM_STATE_HAVE || m_weaponId == WEAPON_ID_GUN) &&
				m_targetPos != nullptr)
			{
				RequestAttack();
			}

			VECTOR vec = VSub(m_pos, m_targetObject->GetPos());

			float len = VSize(vec);

			if (len <= ATTACK_LENGTH + RADIUS)
			{
				RequestAttack();
			}

		}
	}
	else
	{
		switch (m_state)
		{
		case WAIT:
		case WALK:
			m_attackNum = 0;
			break;
		}
	}

	//-----------------------------------------------------------------------------------

	//最後の攻撃が終わったら行動を変更する
	if (m_state == ATTACK_OUT && m_attackNum == ATTACK_3)
	{
		m_cpuState = CPU_STATE_NONE;
		m_attackNum = ATTACK_NONE;
	}

	if (m_isJump == true)
	{
		m_isJump = false;
		m_gravity = JUMP_SPEED;
		m_isFlying = true;
	}

	if (m_targetPos != nullptr)
	{
		//プレイヤー同士の距離
		VECTOR vLen = VSub(m_pos, *m_targetPos);
		float fLen = VSize(vLen);

		//戦いの距離になったら互いの方向を向く
		if (fLen <= FIGHT_LEN)
		{
			if (!m_isDodgeroll)
			{
				float rotY1 = atan2f(m_pos.x - m_targetPos->x, m_pos.z - m_targetPos->z);

				m_rot.y = rotY1;
			}
		}

		//プレイヤーの向きを変える
		if (m_state == ITEM_THROW_IN)
		{
			float rotY = atan2f(m_pos.x - m_targetPos->x, m_pos.z - m_targetPos->z);

			m_rot.y = rotY;
		}
	}

	//丸影とプレイヤーの座標が離れていたら飛んでいる
	if (m_pos.y - m_shadow.GetPos().y > 0.0f)
	{
		m_isFlying = true;
	}

	//空中にいたら状態を空中に変える
	if (m_isFlying == true)
	{
		switch (m_state)
		{
		case ATTACK_IN:
		case ATTACK:
		case ATTACK_OUT:
		case STAGGER:
		case DIE:
			break;
		default:
			m_state = AIR;
			break;
		}
	}

	//指定した高度よりしたに落ちたら死んで復活する
	if (m_pos.y <= DIE_POS_Y)
	{
		m_isActive = false;
	}

	if (m_isTransform == true)
	{
		switch (m_state)
		{
		case ATTACK_IN:
		case ATTACK:
			float rotY = atan2f(m_pos.x - m_targetPos->x, m_pos.z - m_targetPos->z);

			m_rot.y = rotY;
			break;
		}
	}

	//変身中は見た目を変える
	if (m_isTransform == true)
	{
		m_hndl = m_keepHndl[TRANSFORM_HNDL];
		
		//変身の時間がすぎたら解除
		m_transformTimeCount--;
		if (m_transformTimeCount <= 0)
		{
			m_dropCoin = TRANSFORM_COIN_NUM;
			m_transformTimeCount = TRANSFORM_TIME;
			m_isTransform = false;
		}
	}
	else
	{
		m_hndl = m_keepHndl[NORMAL_HNDL];
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



	//移動処理
	Move(_rotY);

	//ジャンプ処理
	RequestJump();

	//回避移行処理
	RequestDodgeroll(_rotY);

	//アイテム使用処理
	Item();

	//アイテムを手に入れていたら持ち上げる
	if (m_itemState == ITEM_STATE_GET)
	{
		m_itemState = ITEM_STATE_HAVE;
		m_state = ITEM_LIFT_UP;
	}

	//アイテムを取ろうとしていたら持っていない状態に戻す
	if (m_itemState == ITEM_STATE_PICK_UP && m_cpuState != CPU_STATE_PICK_UP_ITEM)
	{
		m_itemState = ITEM_STATE_NONE;
	}

	CCharacterBase::Step(_attackManager,_shotManager);

	//体力が増えすぎないように
	if (m_hp >= m_maxHp)
	{
		m_hp = m_maxHp;
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
	if (_hitObject->GetObjectType() == OBJECT_ATTACK)
	{
		//プレイヤーが回避中なら処理をしない
		if (m_isDodgeroll == true)return;

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

		//変身中の場合変身時間を減らす
		if (m_isTransform == true)
		{
			m_transformTimeCount -= attack->GetAtk();
		}

		//呼び出すエフェクトのID
		int effectId = CEffectData::GetId(EFFECT_ATTACK);

		//エフェクトを呼び出す
		CEffekseerCtrl::Request(effectId, GetCenter(), false);

		//アイテムを落とす
		m_itemState = ITEM_STATE_DROP;
		
		//行動状態をリセット
		m_cpuState = CPU_STATE_NONE;

	}
	//---------------------------------------------------------------------

	//アイテムの場合の処理-------------------------------------------------
	if (_hitObject->GetObjectType() == OBJECT_ITEM)
	{
		//アイテム保存用
		CItemBase* item = nullptr;

		item = dynamic_cast<CItemBase*>(_hitObject);

		//アイテムがオブジェクトタイプ以外の場合処理をしない
		//if (item->GetItemType() != ITEM_TYPE_OBJECT)return;

		if (m_cpuState == CPU_STATE_PICK_UP_ITEM && (m_state == WAIT || m_state == WALK))
		{
			//アイテムを拾う処理
			PickUpItem();

			m_cpuState = CPU_STATE_NONE;
		}

	}
	//---------------------------------------------------------------------

	//弾の場合の処理-------------------------------------------------------
	if (_hitObject->GetObjectType() == OBJECT_SHOT)
	{

		//プレイヤーが回避中なら処理をしない
		if (m_isDodgeroll == true)return;

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
		CEffekseerCtrl::Request(effectId, GetCenter(), false);

		//アイテムを落とす
		m_itemState = ITEM_STATE_DROP;

	}

	//---------------------------------------------------------------------

}

//-----------------------
//		移動処理
//-----------------------
void CCpuPlayer::Move(float _rotY)
{
	//待機状態と移動状態以外は移動を出来ないようにする
	switch (m_state)
	{
	case WAIT:
	case WALK:
	case AIR:
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

	//移動していたら歩きモーションに以降
	if ((speed.x != 0.0f ||
		speed.z != 0.0f) &&
		m_state != AIR)
	{
		m_state = WALK;
	}

	////カメラの角度がオールゼロの時に進む速度
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

	//移動方向を向く
	if (m_speed.x != 0 || m_speed.z != 0)
		m_rot.y = atan2f(-m_speed.x,-m_speed.z);

}

//-----------------------
//ジャンプの呼び出し処理
//-----------------------
void CCpuPlayer::RequestJump()
{
	switch (m_state)
	{
	case WAIT:
	case WALK:
		break;
	default:
		return;
	}

	if ((CControllerManager::IsTrg(BUTTON_A, m_padName) && !m_isFlying) ||
		(CheckHitKey(KEY_INPUT_SPACE) && !m_isFlying))
	{
		m_state = JUMP;

	}

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

		switch (object->GetObjectType())
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

			if (this == object ||object->GetObjectType() == OBJECT_ITEM)continue;

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

				if (object->GetObjectType() != OBJECT_ITEM)continue;

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

				if (object->GetObjectType() != OBJECT_ITEM)continue;

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

