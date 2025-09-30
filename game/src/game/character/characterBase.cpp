#include "characterBase.h"
#include "../../lib/myMath/myMath.h"

static const VECTOR BACK_SPEED = { 0.0f,0.5f,-1.0f };
static const float BACK_DOWN_SPEED = 0.9f;

//------------------------------
//		コンストラクタ
//------------------------------
CCharacterBase::CCharacterBase()
{
	Init();
}

//------------------------------
//			初期化
//------------------------------
void CCharacterBase::Init()
{
	CActor::Init();
	
	m_gravity = 0.0f;
	m_hp = 0;
	m_maxHp = 0;
	m_atk = 0;
	m_rad = 0;
	m_state = WAIT;
}

//初期化(弾を出すキャラ用)
void CCharacterBase::Init(CShotManager* _shot)
{
	Init();
	m_shot = _shot;
}

//------------------------------
//		毎フレームする処理
//------------------------------
void CCharacterBase::Step()
{
	//重力処理
	Gravity();

	//状態によって行動を変える
	switch (m_state)
	{
		//待機処理
	case WAIT:
		Wait();
		break;

		//歩く処理
	case WALK:
		Walk();
		break;

		//ジャンプ
	case JUMP:
		Jump();
		break;

		//攻撃前
	case ATTACK_IN:
		AttackIn();
		break;

		//攻撃
	case ATTACK:
		Attack();
		break;

		//攻撃後
	case ATTACK_OUT:
		AttackOut();
		break;

		//アイテム前
	case ITEM_USE_IN:
		ItemUseIn();
		break;

		//アイテム中
	case ITEM_USE:
		ItemUse();
		break;

		//アイテム後
	case ITEM_USE_OUT:
		ItemUseOut();
		break;

		//怯み
	case STAGGER:
		Stagger();
		break;

	case DIE:
		Die();
		break;
	}

}

//------------------------------
//毎フレームする処理(座標取得用)
//------------------------------
void CCharacterBase::Step(VECTOR _pos)
{

}

//------------------------------
//			数値の更新
//------------------------------
void CCharacterBase::Update()
{
	//重力を速度に加算
	m_speed.y -= m_gravity;

	CActor::Update();

	//Hpが０以下になるとActiveをfalseに
	if (m_hp <= 0 && m_state != DIE)
	{
		m_hp = 0;
		m_state = DIE;
	}

}

//------------------------------
//	攻撃を食らった時にする処理
//------------------------------
void CCharacterBase::HitAttack(int _atk, float _rotY)
{
	//既に怯み状態なら処理をしない
	if (m_state == STAGGER)return;

	//ノックバックの速度を設定------------
	
	//プレイヤーが目の前にいる時に進む速度
	VECTOR defaultDir = BACK_SPEED;
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


	//怯み状態にする
	m_state = STAGGER;
	//Hpを攻撃力分減らす
	m_hp -= _atk;
}

//------------------------------
//		重力リセット
//------------------------------
void CCharacterBase::GravityReset()
{
	m_gravity = 0.0f;
}

//------------------------------
//			待機処理
//------------------------------
void CCharacterBase::Wait()
{

}

//------------------------------
//			歩く処理
//------------------------------
void CCharacterBase::Walk()
{

}

//------------------------------
//			ジャンプ
//------------------------------
void CCharacterBase::Jump()
{

}

//------------------------------
//			攻撃前
//------------------------------
void CCharacterBase::AttackIn()
{

}

//------------------------------
//			攻撃中
//------------------------------
void CCharacterBase::Attack()
{

}

//------------------------------
//			攻撃後
//------------------------------
void CCharacterBase::AttackOut()
{

}

//------------------------------
//		アイテム使用前
//------------------------------
void CCharacterBase::ItemUseIn()
{

}

//------------------------------
//		アイテム使用中
//------------------------------
void CCharacterBase::ItemUse()
{

}

//------------------------------
//		アイテム使用後
//------------------------------
void CCharacterBase::ItemUseOut()
{

}

//------------------------------
//			怯み
//------------------------------
void CCharacterBase::Stagger()
{

}

//------------------------------
//			死亡
//------------------------------
void CCharacterBase::Die()
{

}

//-----------------------
//		重力処理
//-----------------------
void CCharacterBase::Gravity()
{
	m_gravity += 0.09f;

}

//-----------------------
//	 ノックバック処理
//-----------------------
void CCharacterBase::MoveBack()
{
	//速度を徐々に下げていく
	m_speed = VScale(m_speed, BACK_DOWN_SPEED);
	//一定速度より遅くなったらノックバック
	if (VSize(m_speed) < 0.1f)
	{
		m_state = WAIT;
	}
}

