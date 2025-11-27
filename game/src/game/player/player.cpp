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

//定義関連---------------------------

//プレイヤー関連--------------------------------
static const char MODEL_PATH[] =
{ "data/model/player/playerTransformTest.mv1" };		//ロードするファイル名
static const VECTOR INIT_POS = { 0.0f,1.0f,0.0f };		//初期座標
static const float SHADOW_SIZE = 0.5f;					//丸影の大きさ
static const int MAX_HP = 300;							//体力
static const int ATK = 20;								//攻撃力
static const float MOVE_SPEED = 1.2f;					//移動スピード
static const float RADIUS = 10.0f;						//半径
static const float DODGEROLL_SPEED = 1.5f;				//回避スピード
static const float JUMP_SPEED = 3.0f;					//ジャンプスピード
static const int TRANSFORM_COIN_NUM = 3;				//変身に必要なコインの数
static const int POWER_UP_ATK = 2;						//増加する攻撃力のような
static const int TRANSFORM_TIME = 10 * 60;				//変身している時間
static const float TRANSFORM_UP_SPEED = 0.3f;			//変身後のスピードアップ
//----------------------------------------------

//攻撃関連---------------------------
static const float ATTACK_SIZE = 12.0f;					//攻撃範囲
static const float ATTACK_LENGTH = 15.0f;				//攻撃の長さ
static const float ATTACKB_SIZE = 25.0f;				//攻撃B範囲
static const int ATTACKB_ATK = 100;						//攻撃Bの攻撃力
static const float ATTACK_MOVE_SPEED = 0.5f;			//攻撃時に前進する力
//-----------------------------------

//アニメーション一覧---------------------------

enum tagAnim {
	ANIMID_ATTACKA1,				//攻撃A1中アニメーション
	ANIMID_ATTACKA1_IN,				//攻撃A1前アニメーション
	ANIMID_ATTACKA1_OUT,			//攻撃A1後アニメーション
	ANIMID_ATTACKA2,				//攻撃A2中アニメーション
	ANIMID_ATTACKA2_IN,				//攻撃A2前アニメーション
	ANIMID_ATTACKA2_OUT,			//攻撃A2後アニメーション
	ANIMID_ATTACKA3,				//攻撃A3中アニメーション
	ANIMID_ATTACKA3_IN,				//攻撃A3前アニメーション
	ANIMID_ATTACKA3_OUT,			//攻撃A3後アニメーション
	ANIMID_ATTACKB1,				//攻撃B1中アニメーション
	ANIMID_ATTACKB1_IN,				//攻撃B1前アニメーション
	ANIMID_ATTACKB1_OUT,			//攻撃B1後アニメーション
	ANIMID_ATTACKB2,				//攻撃B2中アニメーション
	ANIMID_ATTACKB2_IN,				//攻撃B2前アニメーション
	ANIMID_ATTACKB2_OUT,			//攻撃B2後アニメーション
	ANIMID_ATTACKB3,				//攻撃B3中アニメーション
	ANIMID_ATTACKB3_IN,				//攻撃B3前アニメーション
	ANIMID_ATTACKB3_OUT,			//攻撃B3後アニメーション
	ANIMID_CHARGE,					//チャージ中のアニメーション
	ANIMID_CHARGE_IN,				//チャージ前のアニメーション
	ANIMID_DEFAULT,					//デフォルトのアニメーション
	ANIMID_DIE,						//死亡時のアニメーション
	ANIMID_DODGEROLL,				//回避のアニメーション
	ANIMID_GUARD,					//ガード中アニメーション
	ANIMID_GUARD_IN,				//ガード前アニメーション
	ANIMID_GUARD_OUT,				//ガード後アニメーション
	ANIMID_HIT,						//被弾のアニメーション
	ANIMID_ITEM_USE,				//アイテムを使用中のアニメーション
	ANIMID_ITEM_USE_IN,				//アイテムを使用する前のアニメーション
	ANIMID_ITEM_USE_OUT,			//アイテムを使用した後のアニメーション
	ANIMID_LIFT_UP,					//物を持ち上げるアニメーション
	ANIMID_PUT_DOWN,				//物を下ろすアニメーション
	ANIMID_SKILLA,					//スキルA使用中のアニメーション
	ANIMID_SKILLA_IN,				//スキルA使用前のアニメーション
	ANIMID_SKILLA_OUT,				//スキルA使用後のアニメーション
	ANIMID_SKILLB,					//スキルB使用中のアニメーション
	ANIMID_SKILLB_IN,				//スキルB使用前のアニメーション
	ANIMID_SKILLB_OUT,				//スキルB使用後のアニメーション
	ANIMID_THROW,					//物を投げる中のアニメーション
	ANIMID_THROW_IN,				//物を投げる前のアニメーション
	ANIMID_THROW_OUT,				//物を投げる後のアニメーション
	ANIMID_WAIT,					//待機状態のアニメーション
	ANIMID_WAIT_LIFTING_UP,			//物を持ち上げている待機状態のアニメーション
	ANIMID_WALK,					//歩きのアニメーション
	ANIMID_WALK_LIFTING_UP,			//物を持ち上げている歩きのアニメーション

};

//---------------------------------------------

enum tagAttackNum
{
	ATTACK_NONE = -1,	//攻撃をしていない
	ATTACK_1,			//一段階目の攻撃
	ATTACK_2,			//二段階目の攻撃
	ATTACK_3,			//三段階目の攻撃

	ATTACK_NUM,			//攻撃の数
};

static const float ATTACK_MAGNIFICATION[ATTACK_NUM] =	//攻撃の倍率
{
	0.5f,
	0.8f,
	1.0f,
};

static const int ATTACK_BLOWN[ATTACK_NUM] =				//攻撃の吹き飛び度
{
	40,
	40,
	80,
};

//---------------------------------------------------------

//-----------------------
//	コンストラクタ
//-----------------------
CPlayer::CPlayer()
{
	m_transformTimeCount = 0;
	m_name = PLAYER_NONE;
	CCharacterBase::Init(nullptr);
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
	m_attackNum = ATTACK_NONE;
	m_powerUp = 0;
	m_dodgerollRotY = 0.0f;
	m_padName = PAD_NONE;
	m_weaponId = WEAPON_ID_HAND;
	m_itemState = ITEM_STATE_NONE;
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
void CPlayer::Init(CAttackManager* _attackManager, tagPlayerName _name, tagPadName _padName)
{
	CCharacterBase::Init(_attackManager);

	m_transformTimeCount = 0;
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
	m_powerUp = 0;
	m_padName = _padName;
	m_dodgerollRotY = 0.0f;
	m_weaponId = WEAPON_ID_HAND;
	m_name = _name;
	m_shadow.Init(m_pos, SHADOW_SIZE);
	m_objectTypy = OBJECT_PLAYER;

}

//-----------------------
//	モデルロード
//-----------------------
void CPlayer::Load(int _modelHndl)
{
	CObject::DuplicateModel(_modelHndl);
	m_keepHndl[NORMAL_HNDL] = m_hndl;
	m_keepHndl[TRANSFORM_HNDL] = MV1LoadModel(MODEL_PATH);
	m_shadow.Load();
}

//-----------------------
//毎フレームする処理
//-----------------------
void CPlayer::Step(float _rotY)
{

	//攻撃力の上昇
	m_atk = ATK + (m_powerUp * POWER_UP_ATK);

	//パワーアップが増えすぎないように
	if (m_powerUp >= TRANSFORM_COIN_NUM)
	{
		m_powerUp = TRANSFORM_COIN_NUM;
		m_isTransform = true;
	}
	else
	{
		m_isTransform = false;
	}

	//変身中は見た目を変える
	if (m_isTransform == true)
	{
		m_hndl = m_keepHndl[TRANSFORM_HNDL];
		
		//変身の時間がすぎたら解除
		m_transformTimeCount++;
		if (m_transformTimeCount >= TRANSFORM_TIME)
		{
			m_dropCoin = TRANSFORM_COIN_NUM;
			m_transformTimeCount = 0;
			m_isTransform = false;
		}
	}
	else
	{
		m_hndl = m_keepHndl[NORMAL_HNDL];
	}

	//移動処理
	Move(_rotY);

	//ジャンプ処理
	RequestJump();

	//回避移行処理
	RequestDodgeroll(_rotY);

	//アイテム使用処理
	Item();

	//アイテムを拾う処理
	PickUpItem();

	CCharacterBase::Step();

	//体力が増えすぎないように
	if (m_hp >= m_maxHp)
	{
		m_hp = m_maxHp;
	}

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
	attackPos.x = -sinf(m_rot.y) * ATTACK_LENGTH;
	attackPos.y = GetCenter().y;
	attackPos.z = -cosf(m_rot.y) * ATTACK_LENGTH;

	attackPos = VAdd(attackPos, m_pos);

	DrawSphere3D(GetCenter(), ATTACKB_SIZE, 16, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);
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

//終了処理
void CPlayer::Exit()
{
	CCharacterBase::Exit();

	for (int keepHndl_i = 0; keepHndl_i < HNDL_NUM; keepHndl_i++)
	{
		if (m_keepHndl[keepHndl_i] != -1)
		{
			DeleteGraph(m_keepHndl[keepHndl_i]);
			m_keepHndl[keepHndl_i] = -1;
		}
	}
}

//当たり判定後の処理
void CPlayer::HitCalc(CObject* _hitObject)
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

		CCharacterBase::HitAttack(attack->GetAtk(),attack->GetBlown(), rot);

		//変身中の場合変身時間を減らす
		if (m_isTransform == true)
		{
			m_transformTimeCount += attack->GetAtk();
		}
		//変身していない場合コインを落とす
		else
		{
			m_dropCoin++;
		}

		//呼び出すエフェクトのID
		int effectId = CEffectData::GetId(EFFECT_ATTACK);

		//エフェクトを呼び出す
		CEffekseerCtrl::Request(effectId, GetCenter(), false);

		//アイテムを落とす
		m_itemState = ITEM_STATE_DROP;

	}
	//---------------------------------------------------------------------

	//アイテムの場合の処理-------------------------------------------------
	if (_hitObject->GetObjectType() == OBJECT_ITEM)
	{
		//アイテム保存用
		CItemBase* item = nullptr;

		item = dynamic_cast<CItemBase*>(_hitObject);

		//アイテムがオブジェクトタイプ以外の場合処理をしない
		if (item->GetItemType() != ITEM_TYPE_OBJECT)return;

	}
	//---------------------------------------------------------------------
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

	//動いていたら歩き状態に移行
	if (m_speed.x != 0.0f ||
		m_speed.z != 0.0f)
	{
		m_state = WALK;
	}
	
	//攻撃の呼び出し
	RequestAttack();
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

	//攻撃の呼び出し
	RequestAttack();

}

//-----------------------
//		ジャンプ
//-----------------------
void CPlayer::Jump()
{
	m_state = WAIT;
}

//-----------------------
//		  回避
//-----------------------
void CPlayer::Dodgeroll()
{
	//回避のアニメーション
	RequestAnim(ANIMID_DODGEROLL, 1.0f);

	//進む速度
	VECTOR defaultDir = { 0.0f,0.0f,-DODGEROLL_SPEED };
	//上記を行列に変換
	MATRIX dir = CMyMath::GetTranslateMatrix(defaultDir);
	//Y軸回転行列
	MATRIX mRotY = CMyMath::GetYawMatrix(m_dodgerollRotY);
	//行列の合成
	MATRIX res = CMyMath::MatMult(mRotY, dir);

	//移動をスピードに代入
	m_speed.x = res.m[0][3];
	m_speed.y = res.m[1][3];
	m_speed.z = res.m[2][3];

	//回避の方向に向ける
	m_rot.y = m_dodgerollRotY;

	//アニメーションが終わったら待機状態に移行
	if (GetAnimEnd() == true)
	{
		m_isDodgeroll = false;
		m_state = WAIT;
	}
}

//-----------------------
//		攻撃前
//-----------------------
void CPlayer::AttackIn()
{
	//進む速度
	VECTOR defaultDir = { 0.0f,0.0f,-ATTACK_MOVE_SPEED };
	//上記を行列に変換
	MATRIX dir = CMyMath::GetTranslateMatrix(defaultDir);
	//Y軸回転行列
	MATRIX mRotY = CMyMath::GetYawMatrix(m_rot.y);
	//行列の合成
	MATRIX res = CMyMath::MatMult(mRotY, dir);

	//移動をスピードに代入
	m_speed.x = res.m[0][3];
	m_speed.y = res.m[1][3];
	m_speed.z = res.m[2][3];

	switch (m_weaponId)
	{
	case WEAPON_ID_HAND:
		switch (m_attackNum)
		{
		case 0:
			//攻撃前のアニメーション
			RequestAnim(ANIMID_ATTACKA1_IN, 1.0f);
			break;
		case 1:
			//攻撃前のアニメーション
			RequestAnim(ANIMID_ATTACKA2_IN, 0.8f);
			break;
		case 2:
			//攻撃前のアニメーション
			RequestAnim(ANIMID_ATTACKA3_IN, 0.8f);
			break;
		}

		break;
	case WEAPON_ID_SWORD:
		switch (m_attackNum)
		{
		case 0:
			//攻撃前のアニメーション
			RequestAnim(ANIMID_ATTACKB1_IN, 1.0f);
			break;
		case 1:
			//攻撃前のアニメーション
			RequestAnim(ANIMID_ATTACKB2_IN, 1.0f);
			break;
		case 2:
			//攻撃前のアニメーション
			RequestAnim(ANIMID_ATTACKB3_IN, 1.0f);
			break;
		}

		break;
	}

	//アニメーションが終わったら攻撃中に移行
	if (GetAnimEnd() == true)
	{
		m_state = ATTACK;
	}

}

//-----------------------
//		攻撃中
//-----------------------
void CPlayer::Attack()
{

	//攻撃の座標
	VECTOR attackPos;
	attackPos.x = -sinf(m_rot.y) * ATTACK_LENGTH;
	attackPos.z = -cosf(m_rot.y) * ATTACK_LENGTH;

	attackPos = VAdd(attackPos, m_pos);

	attackPos.y = GetCenter().y;

	//攻撃力を計算
	int atk = static_cast<float>(m_atk * ATTACK_MAGNIFICATION[m_attackNum]);

	int blown = ATTACK_BLOWN[m_attackNum];

	switch (m_weaponId)
	{
	case WEAPON_ID_HAND:

		switch (m_attackNum)
		{
		case 0:
			//攻撃中のアニメーション
			if (RequestAnim(ANIMID_ATTACKA1, 1.0f))
			{
				m_attackManager->Request(attackPos, ATTACK_SIZE, atk, blown, m_name);
			}
			break;
		case 1:
			//攻撃中のアニメーション
			if (RequestAnim(ANIMID_ATTACKA2, 1.0f))
			{
				m_attackManager->Request(attackPos, ATTACK_SIZE, atk, blown, m_name);
			}
			break;
		case 2:
			//攻撃中のアニメーション
			if(RequestAnim(ANIMID_ATTACKA3, 1.0f))
			{
				m_attackManager->Request(attackPos, ATTACK_SIZE, atk, blown, m_name);
			}
			break;
		}

		break;
	case WEAPON_ID_SWORD:
		switch (m_attackNum)
		{
		case 0:
			//攻撃中のアニメーション
			if (RequestAnim(ANIMID_ATTACKB1, 1.0f))
			{
				m_attackManager->Request(attackPos, ATTACK_SIZE, m_atk, blown, m_name);
			}
			break;
		case 1:
			//攻撃中のアニメーション
			if (RequestAnim(ANIMID_ATTACKB2, 1.0f))
			{
				m_attackManager->Request(attackPos, ATTACK_SIZE, m_atk, blown, m_name);
			}
			break;
		case 2:
			//攻撃中のアニメーション
			if (RequestAnim(ANIMID_ATTACKB3, 1.0f))
			{
				m_attackManager->Request(attackPos, ATTACK_SIZE, m_atk, blown, m_name);
			}
			break;
		}
		break;
	}

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
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
	case WEAPON_ID_HAND:
		switch (m_attackNum)
		{
		case 0:
			//攻撃後のアニメーション
			RequestAnim(ANIMID_ATTACKA1_OUT, 1.0f);
			break;
		case 1:
			//攻撃後のアニメーション
			RequestAnim(ANIMID_ATTACKA2_OUT, 0.8f);
			break;
		case 2:
			//攻撃後のアニメーション
			RequestAnim(ANIMID_ATTACKA3_OUT, 0.3f);
			break;
		}

		break;
	case WEAPON_ID_SWORD:
		switch (m_attackNum)
		{
		case 0:
			//攻撃後のアニメーション
			RequestAnim(ANIMID_ATTACKB1_OUT, 0.8f);
			break;
		case 1:
			//攻撃後のアニメーション
			RequestAnim(ANIMID_ATTACKB2_OUT, 1.0f);
			break;
		case 2:
			//攻撃後のアニメーション
			RequestAnim(ANIMID_ATTACKB3_OUT, 1.0f);
			break;
		}

		break;
	}

	//攻撃の呼び出し
	RequestAttack();

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
		m_attackNum = ATTACK_NONE;
		m_state = WAIT;
	}

}

//-----------------------
//	   攻撃チャージ前
//-----------------------
void CPlayer::AttackChargeIn()
{
	//アイテム使用前のアニメーション
	RequestAnim(ANIMID_CHARGE_IN, 0.3f);

	//アニメーションが終わったらアイテム使用中に移行
	if (GetAnimEnd() == true)
	{
		m_state = ATTACK_CHARGE;
	}

}

//-----------------------
//	   攻撃チャージ
//-----------------------
void CPlayer::AttackCharge()
{
	//アイテム使用前のアニメーション
	RequestAnim(ANIMID_CHARGE, 0.3f);

	//アニメーションが終わったらアイテム使用中に移行
	if (GetAnimEnd() == true)
	{
		m_state = SKILL_IN;
	}

}

//-----------------------
//		スキル使用前
//-----------------------
void CPlayer::SkillIn()
{
	switch (m_weaponId)
	{
	case WEAPON_ID_HAND:
		//攻撃前のアニメーション
		RequestAnim(ANIMID_SKILLA_IN, 1.2f);
		break;
	case WEAPON_ID_SWORD:
		//攻撃前のアニメーション
		RequestAnim(ANIMID_SKILLB_IN, 1.2f);

		//カメラの角度がオールゼロの時に進む速度
		VECTOR defaultDir = { 0.0f,0.0f,-4.0f };
		//上記を行列に変換
		MATRIX dir = CMyMath::GetTranslateMatrix(defaultDir);
		//Y軸回転行列
		MATRIX mRotY = CMyMath::GetYawMatrix(m_rot.y);
		//行列の合成
		MATRIX res = CMyMath::MatMult(mRotY, dir);

		//移動をスピードに代入
		m_speed.x = res.m[0][3];
		m_speed.y = res.m[1][3];
		m_speed.z = res.m[2][3];
		break;
	}

	//アニメーションが終わったら攻撃中に移行
	if (GetAnimEnd() == true)
	{
		m_state = SKILL;
	}

}

//-----------------------
//		スキル使用
//-----------------------
void CPlayer::Skill()
{
	switch (m_weaponId)
	{
	case WEAPON_ID_HAND:
		//攻撃中のアニメーション
		if (RequestAnim(ANIMID_SKILLA, 1.0f))
		{
			//攻撃の呼び出し
			m_attackManager->Request(GetCenter(), ATTACKB_SIZE, ATTACKB_ATK,0, m_name);
		}
		break;
	case WEAPON_ID_SWORD:
		//攻撃中のアニメーション
		if (RequestAnim(ANIMID_SKILLB, 1.0f))
		{
			//攻撃の呼び出し
			m_attackManager->Request(GetCenter(), ATTACKB_SIZE, ATTACKB_ATK,0, m_name);
		}
		break;
	}

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
		m_state = SKILL_OUT;
	}

}

//-----------------------
//		スキル使用後
//-----------------------
void CPlayer::SkillOut()
{
	switch (m_weaponId)
	{
	case WEAPON_ID_HAND:
		//攻撃後のアニメーション
		RequestAnim(ANIMID_SKILLA_OUT, 0.3f);
		break;
	case WEAPON_ID_SWORD:
		//攻撃後のアニメーション
		RequestAnim(ANIMID_SKILLB_OUT, 0.5f);
		break;
	}

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
		m_state = WAIT;
	}

}

//-----------------------
//	  アイテム使用前
//-----------------------
void CPlayer::ItemUseIn()
{
	//アイテム使用前のアニメーション
	RequestAnim(ANIMID_ITEM_USE_IN, 1.0f);

	//アニメーションが終わったらアイテム使用中に移行
	if (GetAnimEnd() == true)
	{
		m_state = ITEM_USE;
	}

}

//-----------------------
//	 アイテム使用中
//-----------------------
void CPlayer::ItemUse()
{
	//アイテム使用中のアニメーション
	if (RequestAnim(ANIMID_ITEM_USE, 1.0f))
	{

	}

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
		m_state = ITEM_USE_OUT;
	}

}

//-----------------------
//	 アイテム使用後
//-----------------------
void CPlayer::ItemUseOut()
{
	//アイテム使用後のアニメーション
	RequestAnim(ANIMID_ITEM_USE_OUT, 1.0f);

	//アニメーションが終わったら待機状態に戻す
	if (GetAnimEnd() == true)
	{
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
	RequestAnim(ANIMID_HIT, 1.8f);

	//被弾のアニメーションが終わったら戻す
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
	RequestAnim(ANIMID_DIE, 0.5f);

	//死亡アニメーションが終わったら消える
	if (GetAnimEnd() == true)
	{
		m_isActive = false;
	}
}

//-----------------------
//		移動処理
//-----------------------
void CPlayer::Move(float _rotY)
{
	//待機状態と移動状態以外は移動を出来ないようにする
	switch (m_state)
	{
	case WAIT:
	case WALK:
	case JUMP:
		break;
	default:
		return;
	}

	//コントローラーを使っているか
	bool isController = false;

	if (CControllerManager::GetLY(m_padName) != 0 ||
		CControllerManager::GetLX(m_padName) != 0)
	{
		isController = true;
	}

	float moveSpeed = MOVE_SPEED;

	//変身していたら速度を上げる
	if (m_isTransform)
	{
		moveSpeed += TRANSFORM_UP_SPEED;
	}

	//移動ベクトル
	VECTOR speed = { 0.0f,0.0f,0.0f };
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


	//移動していたら歩きモーションに以降
	if (speed.x != 0.0f ||
		speed.z != 0.0f)
	{
		m_state = WALK;
	}

	////カメラの角度がオールゼロの時に進む速度
	VECTOR defaultDir = { speed.x,0.0f,speed.z };
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
	case ATTACK_IN:
	case ATTACK:
	case ATTACK_OUT:
		break;
	default:
		if (m_attackNum != ATTACK_NONE)
		{
			m_attackNum = ATTACK_NONE;
		}
		break;
	}

	//アイテムを持ち上げている状態ではアイテムを投げる
	if (m_itemState == ITEM_STATE_HAVE)
	{
		//攻撃ボタンを押したら投げる
		if (CheckHitKey(KEY_INPUT_J) != 0 ||
			CControllerManager::IsTrg(BUTTON_X, m_padName))
		{
			m_state = ITEM_THROW_IN;
		}


		return;
	}

	//空中いるときは攻撃を出せない
	if (m_isFlying == true)return;

	//攻撃ボタンを押したか
	if (CheckHitKey(KEY_INPUT_J) != 0 ||
		CControllerManager::IsTrg(BUTTON_X,m_padName))
	{

		//攻撃中なら次に移行する
		if ((m_state == ATTACK ||
			m_state == ATTACK_OUT) &&
			m_attackNum >= ATTACK_1)
		{
			//最後の攻撃以外は攻撃を進める
			if (m_attackNum < ATTACK_3)
			{
				m_attackNum++;
				m_state = ATTACK_IN;
			}

		}
		//攻撃してない時に攻撃前に移行する
		else if(m_attackNum == ATTACK_NONE)
		{
			m_attackNum++;
			m_state = ATTACK_IN;
		}
	}

	//攻撃ボタンを押したか
	//if (CheckHitKey(KEY_INPUT_U) != 0 ||
	//	CControllerManager::IsTrg(BUTTON_Y,m_padName))
	//{
	//	m_state = ATTACK_CHARGE_IN;
	//}

}

//-----------------------
//ジャンプの呼び出し処理
//-----------------------
void CPlayer::RequestJump()
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
		m_gravity = JUMP_SPEED;
		m_isFlying = true;

	}

}

//-----------------------
//	回避に移行する処理
//-----------------------
void CPlayer::RequestDodgeroll(float _rotY)
{
	//アイテムを持ち上げている状態は処理をしない
	if (m_itemState == ITEM_STATE_HAVE)return;

	//待機状態と歩いてる状態以外は処理をしない
	switch (m_state)
	{
	case WAIT:
	case WALK:
	case ATTACK_IN:
	case ATTACK:
	case ATTACK_OUT:
	case ATTACK_CHARGE_IN:

		break;
	default:
		return;
	}

	//コントローラーを使っているか
	bool isController = false;

	if (CControllerManager::GetLY(m_padName) != 0 ||
		CControllerManager::GetLX(m_padName) != 0)
	{
		isController = true;
	}

	//入力方向ベクトル
	VECTOR vec = { 0.0f,0.0f,0.0f };
	//コントローラー用前進後退
	if (isController == true)
	{
		vec.z = CControllerManager::GetLY(m_padName);
	}

	//左右にどれだけ移動するか
	//コントローラー用左右移動
	if (isController == true)
	{
		vec.x = -CControllerManager::GetLX(m_padName);
	}

	//入力されていない場合前方向に移動する
	if (VSize(vec) == 0.0f)
	{
		m_dodgerollRotY = m_rot.y;
	}
	else
	{
		////カメラの角度がオールゼロの時に進む速度
		VECTOR defaultDir = { vec.x,0.0f,vec.z };
		//上記を行列に変換
		MATRIX dir = CMyMath::GetTranslateMatrix(defaultDir);
		//Y軸回転行列
		MATRIX mRotY = CMyMath::GetYawMatrix(_rotY);
		//行列の合成
		MATRIX res = CMyMath::MatMult(mRotY, dir);

		//移動をスピードに代入
		vec.x = res.m[0][3];
		vec.y = res.m[1][3];
		vec.z = res.m[2][3];

		m_dodgerollRotY = atan2f(-vec.x, -vec.z);
	}

	//回避ボタンを押したか
	if (CheckHitKey(KEY_INPUT_L) != 0 ||
		CControllerManager::IsTrg(BUTTON_RB, m_padName))
	{
		m_attackNum = 0;
		m_isDodgeroll = true;
		m_state = DODGEROLL;
	}

}

//-----------------------
//	   アイテム処理
//-----------------------
void CPlayer::Item()
{

	//アイテムを持っていなかったら処理をしない
	if (m_itemState != ITEM_STATE_HAVE)return;

	//待機状態と歩いてる状態以外は処理をしない
	switch (m_state)
	{
	case WAIT:
	case WALK:
		break;
	default:
		return;
	}

	//ボタンを押されたらアイテム使用前状態に移行
	if (CheckHitKey(KEY_INPUT_K) != 0 ||
		CControllerManager::IsTrg(BUTTON_A,m_padName) == true)
	{
		m_state = ITEM_USE_IN;
	}

}

//-----------------------
//	  アイテムを拾う
//-----------------------
void CPlayer::PickUpItem()
{
	//空中いるときは攻撃を出せない
	if (m_isFlying == true)return;

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

	switch (m_state)
	{
	case WAIT:
	case WALK:
		break;
	default:
		return;
	}

	//アイテムを取得・下ろす
	if (CheckHitKey(KEY_INPUT_I) != 0 ||
		CControllerManager::IsTrg(BUTTON_B,m_padName) == true)
	{

		//アイテムをすでに持っている場合はアイテムを下ろす
		if (m_itemState == ITEM_STATE_HAVE)
		{
			m_state = ITEM_PUT_DOWN;
			m_itemState = ITEM_STATE_PUT_DOWN;
		}
		//アイテムを持っていない場合アイテムを取得する
		else
		{
			m_itemState = ITEM_STATE_PICK_UP;
		}

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

