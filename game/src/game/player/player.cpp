#include "player.h"
#include "../data.h"
#include "../../lib/myMath/myMath.h"
#include <math.h>
#include "../common.h"
#include "../../lib/input/controllerManager.h"
#include"../../lib/input/keyInput.h"

//定義関連---------------------------

//プレイヤー関連--------------------------------
static const char MODEL_PATH[] =
{ "data/model/player/playerTest4-2.mv1" };			//ロードするファイル名
static const VECTOR INIT_POS = { 0.0f,1.0f,0.0f };	//初期座標
static const int MAX_HP = 300;						//体力
static const int ATK = 20;							//攻撃力
static const float MOVE_SPEED = 1.0f;				//移動スピード
static const float RADIUS = 10.0f;					//半径
static const float DODGEROLL_SPEED = 1.5f;			//回避スピード
//----------------------------------------------

//攻撃関連---------------------------
static const float ATTACK_SIZE = 12.0f;				//攻撃範囲
static const float ATTACK_LENGTH = 15.0f;			//攻撃の長さ
static const float ATTACKB_SIZE = 25.0f;			//攻撃B範囲
static const int ATTACKB_ATK = 100;					//攻撃Bの攻撃力

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
	ANIMID_SKILLA,					//スキルA使用中のアニメーション
	ANIMID_SKILLA_IN,				//スキルA使用前のアニメーション
	ANIMID_SKILLA_OUT,				//スキルA使用後のアニメーション
	ANIMID_SKILLB,					//スキルB使用中のアニメーション
	ANIMID_SKILLB_IN,				//スキルB使用前のアニメーション
	ANIMID_SKILLB_OUT,				//スキルB使用後のアニメーション
	ANIMID_WAIT,					//待機状態のアニメーション
	ANIMID_WALK,					//歩きのアニメーション

};

//---------------------------------------------


//---------------------------------------------------------

//-----------------------
//	コンストラクタ
//-----------------------
CPlayer::CPlayer()
{
	Init();

	m_isPickUpItem = false;
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
void CPlayer::Init(CAttackManager* _attackManager, tagPadName _padName)
{
	CCharacterBase::Init(_attackManager);
	m_attack.Init(ATTACK_SIZE,ATTACK_LENGTH);

	m_pos = ZERO;
	m_rad = RADIUS;
	m_maxHp = MAX_HP;
	m_hp = m_maxHp;
	m_atk = ATK;
	m_isItemUse = false;
	m_isPickUpItem = false;
	m_isItem = false;
	m_isDodgeroll = false;
	m_attackNum = 0;
	m_padName = _padName;
	m_attackType = ATTACK_TYPE_NONE;
	m_weaponId = WEAPON_ID_HAND;
}

//-----------------------
//	モデルロード
//-----------------------
void CPlayer::Load(int _modelHndl)
{
	CObject::DuplicateModel(_modelHndl);
}

//-----------------------
//毎フレームする処理
//-----------------------
void CPlayer::Step(float _rotY)
{
	//攻撃の毎フレームする処理
	m_attack.Step();

	//移動処理
	Move(_rotY);

	//回避移行処理
	RequestDodgeroll();

	//アイテム使用処理
	Item();

	//アイテムを拾う処理
	PickUpItem();

	CCharacterBase::Step();
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
	//体力を表示
	DrawFormatString(32, 32, GetColor(255, 0, 0), "hp:%d", m_hp);

}

//-----------------------
//		更新処理
//-----------------------
void CPlayer::Update()
{
	CCharacterBase::Update();

	//速度のリセット
	ResetSpeed();

	//体力が増えすぎないように
	if (m_hp >= m_maxHp)
	{
		m_hp = m_maxHp;
	}

	//攻撃の更新
	m_attack.Update(GetCenter(), m_rot);

	//アイテムを取ろうとしているかを初期化
	m_isPickUpItem = false;
	//アイテムを使用したかを初期化
	m_isItemUse = false;
}

//-----------------------
//		待機処理
//-----------------------
void CPlayer::Wait()
{
	//待機アニメーションを再生
	RequestAnim(ANIMID_WAIT, 0.5f, true);

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
	//歩くアニメーション
	RequestAnim(ANIMID_WALK, 1.0f, true);

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

}

//-----------------------
//		  回避
//-----------------------
void CPlayer::Dodgeroll()
{
	//アイテム使用前のアニメーション
	RequestAnim(ANIMID_DODGEROLL, 1.0f);

	//進む速度
	VECTOR defaultDir = { 0.0f,0.0f,-DODGEROLL_SPEED };
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

	//アニメーションが終わったらアイテム使用中に移行
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
	switch (m_weaponId)
	{
	case WEAPON_ID_HAND:
		switch (m_attackNum)
		{
		case 0:
			//攻撃前のアニメーション
			RequestAnim(ANIMID_ATTACKA1_IN, 0.5f);
			break;
		case 1:
			//攻撃前のアニメーション
			RequestAnim(ANIMID_ATTACKA2_IN, 0.3f);
			break;
		case 2:
			//攻撃前のアニメーション
			RequestAnim(ANIMID_ATTACKA3_IN, 0.5f);
			break;
		}

		break;
	case WEAPON_ID_SWORD:
		switch (m_attackNum)
		{
		case 0:
			//攻撃前のアニメーション
			RequestAnim(ANIMID_ATTACKB1_IN, 0.5f);
			break;
		case 1:
			//攻撃前のアニメーション
			RequestAnim(ANIMID_ATTACKB2_IN, 0.5f);
			break;
		case 2:
			//攻撃前のアニメーション
			RequestAnim(ANIMID_ATTACKB3_IN, 0.5f);
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
	attackPos.y = GetCenter().y;
	attackPos.z = -cosf(m_rot.y) * ATTACK_LENGTH;

	attackPos = VAdd(attackPos, m_pos);

	switch (m_weaponId)
	{
	case WEAPON_ID_HAND:

		switch (m_attackNum)
		{
		case 0:
			//攻撃中のアニメーション
			if (RequestAnim(ANIMID_ATTACKA1, 1.0f))
			{
				m_attackManager->Request(attackPos, ATTACK_SIZE, m_atk, m_attackType);
			}
			break;
		case 1:
			//攻撃中のアニメーション
			if (RequestAnim(ANIMID_ATTACKA2, 1.0f))
			{
				m_attackManager->Request(attackPos, ATTACK_SIZE, m_atk, m_attackType);
			}
			break;
		case 2:
			//攻撃中のアニメーション
			if(RequestAnim(ANIMID_ATTACKA3, 1.0f));
			{
				m_attackManager->Request(attackPos, ATTACK_SIZE, m_atk, m_attackType);
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
				m_attackManager->Request(attackPos, ATTACK_SIZE, m_atk, m_attackType);
			}
			break;
		case 1:
			//攻撃中のアニメーション
			if (RequestAnim(ANIMID_ATTACKB2, 1.0f))
			{
				m_attackManager->Request(attackPos, ATTACK_SIZE, m_atk, m_attackType);
			}
			break;
		case 2:
			//攻撃中のアニメーション
			if (RequestAnim(ANIMID_ATTACKB3, 1.0f))
			{
				m_attackManager->Request(attackPos, ATTACK_SIZE, m_atk, m_attackType);
			}
			break;
		}
		break;
	}

	//攻撃の呼び出し
	RequestAttack();

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
			RequestAnim(ANIMID_ATTACKA1_OUT, 0.5f);
			break;
		case 1:
			//攻撃後のアニメーション
			RequestAnim(ANIMID_ATTACKA2_OUT, 0.5f);
			break;
		case 2:
			//攻撃後のアニメーション
			RequestAnim(ANIMID_ATTACKA3_OUT, 0.5f);
			break;
		}

		break;
	case WEAPON_ID_SWORD:
		switch (m_attackNum)
		{
		case 0:
			//攻撃後のアニメーション
			RequestAnim(ANIMID_ATTACKB1_OUT, 1.0f);
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
		m_attackNum = 0;
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
			m_attackManager->Request(GetCenter(), ATTACKB_SIZE, ATTACKB_ATK, m_attackType);
		}
		break;
	case WEAPON_ID_SWORD:
		//攻撃中のアニメーション
		if (RequestAnim(ANIMID_SKILLB, 1.0f))
		{
			//攻撃の呼び出し
			m_attackManager->Request(GetCenter(), ATTACKB_SIZE, ATTACKB_ATK, m_attackType);
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
		//アイテム使用フラグをtrueに
		m_isItemUse = true;
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
//		怯み
//-----------------------
void CPlayer::Stagger()
{
	//被弾のアニメーション
	RequestAnim(ANIMID_HIT, 1.0f);

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

	//移動ベクトル
	VECTOR speed = { 0.0f,0.0f,0.0f };
	speed.z = 0.0f;
	//コントローラー用前進後退
	if (isController == true)
	{
		speed.z = MOVE_SPEED * CControllerManager::GetLY(m_padName);
	}
	//キーボード用前進
	else if (CheckHitKey(KEY_INPUT_W) != 0)
	{
		speed.z = -MOVE_SPEED;
	}
	//キーボード用後退
	else if (CheckHitKey(KEY_INPUT_S) != 0)
	{
		speed.z = MOVE_SPEED;
	}

	//左右にどれだけ移動するか
	speed.x = 0.0f;
	//コントローラー用左右移動
	if (isController == true)
	{
		speed.x = -MOVE_SPEED * CControllerManager::GetLX(m_padName);
	}
	//キーボード用左移動
	else if (CheckHitKey(KEY_INPUT_A) != 0)
	{
		speed.x = MOVE_SPEED;
	}
	//キーボード用右移動
	else if (CheckHitKey(KEY_INPUT_D) != 0)
	{
		speed.x = -MOVE_SPEED;
	}

	//カメラの角度がオールゼロの時に進む速度
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

	//攻撃ボタンを押したか
	if (CheckHitKey(KEY_INPUT_J) != 0 ||
		CControllerManager::IsTrg(BUTTON_X,m_padName))
	{

		//攻撃中なら次に移行する
		if ((m_state == ATTACK ||
			m_state == ATTACK_OUT) &&
			m_attackNum<3)
		{
			m_attackNum++;
			m_state = ATTACK_IN;
		}
		//攻撃してない時に攻撃前に移行する
		else if (m_attack.GetIsCoolDown() == true)
		{
			m_state = ATTACK_IN;
		}
	}

	//攻撃ボタンを押したか
	if (CheckHitKey(KEY_INPUT_U) != 0 ||
		CControllerManager::IsTrg(BUTTON_Y,m_padName))
	{

		//攻撃してない時に攻撃前に移行する
		if (m_attack.GetIsCoolDown() == true)
		{

			m_state = ATTACK_CHARGE_IN;
		}
	}

}

//-----------------------
//	回避に移行する処理
//-----------------------
void CPlayer::RequestDodgeroll()
{
	//待機状態と歩いてる状態以外は処理をしない
	switch (m_state)
	{
	case WAIT:
	case WALK:
		break;
	default:
		return;
	}

	//攻撃ボタンを押したか
	if (CheckHitKey(KEY_INPUT_L) != 0 ||
		CControllerManager::IsTrg(BUTTON_RB, m_padName))
	{
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
	if (m_isItem == false)return;

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
//	   アイテムを拾う
//-----------------------
void CPlayer::PickUpItem()
{
	if (CheckHitKey(KEY_INPUT_I) != 0 ||
		CControllerManager::IsTrg(BUTTON_B,m_padName) == true)
	{
		m_isPickUpItem = true;
	}
}

